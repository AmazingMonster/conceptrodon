/**********************/
/**** Dependencies ****/
/**********************/

#include <utility>
#include <cstddef>

/**** Prefix ****/
template<typename, auto>
concept Prefix = true;

/************************/
/**** Implementation ****/
/************************/

/**** Fore ****/
template<typename>
struct Fore {};

template<size_t...I>
struct Fore<std::index_sequence<I...>>
{
    template<template<typename...> class Operation>
    static consteval auto idyl
    (
        // Expand `Prefix<I>` to count the arguments from the front.
        Prefix<I> auto...targets,
        ...
    )
    -> Operation<typename decltype(targets)::type...>;
};

/**** CognateFront ****/
template<template<typename...> class Operation>
struct CognateFront
{
    template<size_t Amount>
    struct ProtoPage
    {
        template<typename...Elements>
        using Mold = decltype
        (
            Fore<std::make_index_sequence<Amount>>
            ::template idyl<Operation>(std::type_identity<Elements>{}...)
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** Operation ****/
template<typename...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<int, int*, int**>;

/**** Result ****/
using Result = CognateFront<Operation>
::Page<3>
::Mold<int, int*, int**, int**>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);