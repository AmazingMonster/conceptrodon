/**********************/
/**** Dependencies ****/
/**********************/

#include <utility>
#include <cstddef>

/**** Tyy ****/
template<typename Element>
struct Tyy
{
    using type = Element;
};

/**** Prefix ****/
template<typename, auto>
concept Prefix = true;

/************************/
/**** Implementation ****/
/************************/

/**** Midst ****/
template<typename>
struct Midst {};

template<size_t...I>
struct Midst<std::index_sequence<I...>>
{
    template<typename Target>
    static constexpr auto idyl
    (Prefix<I> auto..., Target, ...)
    -> Target::type;
};

/**** Amidst ****/
template<typename...Elements>
struct Amidst
{
    template<size_t I>
    struct Detail
    {
        using type = decltype
        (
            Midst<std::make_index_sequence<I>>
            ::idyl(Tyy<Elements>{}...)
        );
    };

    template<auto...Agreements>
    using Page = Detail<Agreements...>::type;
};

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** SupposedResult ****/
using SupposedResult = int***;

/**** Result ****/
using Result = Amidst<int, int*, int**, int***>::Page<3>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
