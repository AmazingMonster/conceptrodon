/**********************/
/**** Dependencies ****/
/**********************/

#include <utility>
#include <cstddef>

/**** Prefix ****/
template<typename, auto>
concept Prefix = true;

/**** Vay ****/
template<auto Variable>
struct Vay
{ static constexpr auto value {Variable}; };

/************************/
/**** Implementation ****/
/************************/

/**** Fore ****/
template<typename>
struct Fore {};

template<size_t...I>
struct Fore<std::index_sequence<I...>>
{
    template<template<auto...> class Operation>
    static consteval auto idyl
    (
        // Expand `Prefix<I>` to count the arguments from the front.
        Prefix<I> auto...targets,
        ...
    )
    -> Operation<decltype(targets)::value...>;
};

/**** Front ****/
template<auto First, auto...Variables>
struct Front
{
    template<size_t Amount>
    struct ProtoPage
    {
        template<template<auto...> class...Agreements>
        using Rail = decltype
        (
            Fore<std::make_index_sequence<Amount>>
            ::template idyl<Agreements...>(Vay<First>{}, Vay<Variables>{}...)
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
    
    template<template<auto...> class Operation>
    struct Detail
    {
        using type = Operation<First>;
    };

    template<template<auto...> class...Agreements>
    using Rail = Detail<Agreements...>::type;

    static constexpr auto value {First};
};

/***********************/
/**** First Example ****/
/***********************/

/**** SupposedResult ****/
constexpr auto SupposedResult = 0;

/**** Result ****/
constexpr auto Result = Front<0, 1, 2, 2>::value;

/**** Test ****/
static_assert(SupposedResult == Result);

/************************/
/**** Second Example ****/
/************************/

/**** Operation ****/
template<auto...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult_1 = Operation<0>;

/**** Result ****/
using Result_1 = Front<0, 1, 2, 2>::Rail<Operation>;

/**** Test ****/
static_assert(std::same_as<SupposedResult_1, Result_1>);

/***********************/
/**** Third Example ****/
/***********************/

/**** SupposedResult ****/
using SupposedResult_2 = Operation<0, 1, 2>;

/**** Result ****/
using Result_2 = Front<0, 1, 2, 2>::Page<3>::Rail<Operation>;

/**** Test ****/
static_assert(std::same_as<SupposedResult_2, Result_2>);