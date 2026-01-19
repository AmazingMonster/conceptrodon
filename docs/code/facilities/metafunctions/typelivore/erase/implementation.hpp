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

/**** Ditch ****/
template<typename>
struct Ditch {};

template<size_t...I>
struct Ditch<std::index_sequence<I...>>
{
    template
    <
        template<typename...> class Operation,
        typename...BackArgs
    >
    static consteval auto idyl
    (
        // Expand `Prefix<I>` to count the arguments from the front.
        Prefix<I> auto...front_args,
        // Remove the next.
        auto,
        // Collect the rest.
        BackArgs...
    )
    -> Operation
    <
        typename decltype(front_args)::type...,
        typename BackArgs::type...
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
        typename...BackArgs
    >
    static consteval auto idyl
    (
        // Expand `Prefix<I>` to count the arguments from the front.
        Prefix<I> auto...front_args,
        // Expand `Prefix<J>` to count the unwanted arguments.
        Prefix<J> auto...,
        // Collect the rest.
        BackArgs...
    )
    -> Operation
    <
        typename decltype(front_args)::type...,
        typename BackArgs::type...
    >;
};

/**** Erase ****/
template<typename...Elements>
struct Erase
{
    template<auto...>
    struct ProtoPage {};

    template<size_t Index>
    struct ProtoPage<Index>
    {
        template<template<typename...> class...Agreements>
        using Road = decltype
        (
            Ditch<std::make_index_sequence<Index>>
            ::template idyl<Agreements...>(Tyy<Elements>{}...)
        );
    };

    template<size_t Start, size_t End>
    requires (Start <= End)
    struct ProtoPage<Start, End>
    {
        template<template<typename...> class...Agreements>
        using Road = decltype
        (
            Expunge
            <
                std::make_index_sequence<Start>,
                // `End-Start` is the number of elements we will erase.
                std::make_index_sequence<End-Start>
            >
            ::template idyl<Agreements...>(Tyy<Elements>{}...)
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

/**** Result ****/
using Result = Erase<int, int*, int**, int**>::Page<1>::Road<Operation>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);

/************************/
/**** Second Example ****/
/************************/

/**** SupposedResult ****/
using SupposedResult_1 = Operation<int, int**>;

/**** Result ****/
using Result_1 = Erase<int, int*, int**, int**>::Page<1, 3>::Road<Operation>;

/**** Test ****/
static_assert(std::same_as<SupposedResult_1, Result_1>);