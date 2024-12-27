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
    template
    <
        template<auto...> class Operation,
        // We use `Prefix<I>...` to enumerate `Targets`.
        Prefix<I>...Targets,
        typename...
    >
    // Note that `Operation` is invoked by values
    // extracted from the template parameters.
    // This is because we will pack every item
    // of `Variables...` into `Vay`.
    static consteval auto idyl() -> Operation<Targets::value...>;
};

/**** Front ****/
template<auto...Variables>
struct Front
{
    template<size_t Amount>
    struct ProtoPage
    {
        template<template<auto...> class...Agreements>
        using Rail = decltype
        (
            Fore<std::make_index_sequence<Amount>>
            ::template idyl<Agreements..., Vay<Variables>...>()
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

/*****************/
/**** Example ****/
/*****************/

/**** Operation ****/
template<auto...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<0, 1, 2>;

/**** Result ****/
using Result = Front<0, 1, 2, 2>::Page<3>::Rail<Operation>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);