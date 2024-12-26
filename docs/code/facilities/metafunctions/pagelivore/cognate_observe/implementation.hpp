/**********************/
/**** Dependencies ****/
/**********************/

#include <utility>
#include <cstddef>
#include <algorithm>
#include <array>

/************************/
/**** Implementation ****/
/************************/

/**** stare ****/
template<template<auto...> class Operation, bool...Phenomena>
static consteval auto stare()
{
    // `std::index_sequence<I...>` is created
    // for the length of `Phenomena...`.
    return []<size_t...I>(std::index_sequence<I...>)
    {
        
        // `std::index_sequence<I...>` is created
        // for the count of `true` in `Phenomena...`.
        return []<size_t...J>(std::index_sequence<J...>)
        {
            constexpr auto result = []()
            {
                // We make `std::array phenomena` so that
                // we can access items of `Phenomena...` using [index].
                std::array phenomena {Phenomena...};

                // We will sort `std::array indices`.
                std::array indices {I...};
                
                // We will use this comparison function to sort.
                auto comp = [&phenomena](size_t i, size_t j)
                {
                    return
                    // If `phenomena[i]` is `true` and
                    // `phenomena[j]` is false, then `i` is less than `j`.
                    // Therefore, an index of `true` is always less
                    // than an index of `false`.
                    // As a result, indices of `true` will
                    // assemble in the front of the array.
                        (phenomena[i] && ! phenomena[j])
                    // If `phenomena[i]` and `phenomena[j]` are both `true`,
                    // then we return `i < j` to preserve relative positions.
                    ||  (phenomena[i] && phenomena[j] && i < j);
                };
                
                // `indices` will be reused for the result.
                std::ranges::sort(indices, comp);
                
                // return the result.
                return indices;
            }();

            // `result` is a `std::array`.
            // We collect its front part,
            // which contains all the indices of `true`.
            // Then, we instantiate `Operation`.
            // We return `std::type_identity` to avoid constructing
            // an object of type `Operation<*>`.
            return std::type_identity<Operation<result.at(J)...>> {};
        }(std::make_index_sequence<(...+Phenomena)>{});
    }(std::make_index_sequence<sizeof...(Phenomena)>{});
};

/**** CognateObserve ****/
template<template<auto...> class Operation>
struct CognateObserve
{
    template<auto...Phenomena>
    using Page = decltype
    (stare<Operation, static_cast<bool>(Phenomena)...>())
    ::type;
};

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** Operation ****/
template<auto...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation
<
    static_cast<size_t>(1),
    static_cast<size_t>(3)
>;

/**** Result ****/
using Result = CognateObserve<Operation>::Page<0, 1, nullptr, 3.0>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);