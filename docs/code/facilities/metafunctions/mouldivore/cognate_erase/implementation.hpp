/**********************/
/**** Dependencies ****/
/**********************/

#include <type_traits>
#include <utility>
#include <cstddef>

/**** Prefix ****/
template<typename, auto>
concept Prefix = true;

/************************/
/**** Implementation ****/
/************************/

/**** Ditch ****/
template<typename>
struct Ditch {};

template<size_t...I>
struct Ditch<std::index_sequence<I...>>
{
    template
    <
        template<typename...> class Operation,
        typename...BackTargets
    >
    static consteval auto idyl
    (
        // Expand `Prefix<I>` to count the arguments from the front.
        Prefix<I> auto...front_targets,
        // Remove the next.
        auto,
        // Collect the rest.
        BackTargets...
    )
    -> Operation
    <
        typename decltype(front_targets)::type...,
        typename BackTargets::type...
    >;
};

/**** Expunge ****/
template<typename, typename>
struct Expunge {};

template<size_t...I, size_t...J>
struct Expunge<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template
    <
        template<typename...> class Operation,
        typename...BackTargets
    >
    static consteval auto idyl
    (
        // Expand `Prefix<I>` to count the arguments from the front.
        Prefix<I> auto...front_targets,
        // Expand `Prefix<J>` to count the unwanted arguments.
        Prefix<J> auto...,
        // Collect the rest.
        BackTargets...
    )
    -> Operation
    <
        typename decltype(front_targets)::type...,
        typename BackTargets::type...
    >;
};

/**** CognateErase ****/
template<template<typename...> class Operation>
struct CognateErase
{
    template<size_t...>
    struct ProtoPage {};

    template<size_t Index>
    struct ProtoPage<Index>
    {
        template<typename...Elements>
        using Mold = decltype
        (
            Ditch<std::make_index_sequence<Index>>
            ::template idyl<Operation>(std::type_identity<Elements>{}...)
        );
    };

    template<size_t Start, size_t End>
    requires (Start <= End)
    struct ProtoPage<Start, End>
    {
        template<typename...Elements>
        using Mold = decltype
        (
            Expunge
            <
                std::make_index_sequence<Start>,
                std::make_index_sequence<End-Start>
            >
            ::template idyl<Operation>(std::type_identity<Elements>{}...)
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

/***********************/
/**** First Example ****/
/***********************/

#include <concepts>

/**** Operation ****/
template<typename...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<int, int**, int**>;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = CognateErase<Operation>
::Page<1>
::Mold<Args...>;

/**** Result ****/
using Result = Metafunction<int, int*, int**, int**>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);

/************************/
/**** Second Example ****/
/************************/

/**** SupposedResult ****/
using SupposedResult_1 = Operation<int, int**>;

/**** Metafunction ****/
template<typename...Args>
using Metafunction_1 = CognateErase<Operation>
::Page<1, 3>
::Mold<Args...>;

/**** Result ****/
using Result_1 = Metafunction_1<int, int*, int**, int**>;

/**** Test ****/
static_assert(std::same_as<SupposedResult_1, Result_1>);