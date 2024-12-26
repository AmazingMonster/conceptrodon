/**********************/
/**** Dependencies ****/
/**********************/

#include <utility>
#include <cstddef>

/**** ExtendFront ****/
template<typename...>
struct ExtendFront {};

template<template<auto...> class Sequence, auto...Variables>
struct ExtendFront<Sequence<Variables...>>
{
    template<auto...NewVariables>
    using Page = Sequence<NewVariables..., Variables...>;
};

/**** Val ****/
template<auto Variable>
struct Val
{ static constexpr auto value {Variable}; };

/**** Prefix ****/
template<typename, size_t>
concept Prefix = true;

/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** RemoveValues ****/
template<typename...>
struct RemoveValues {};

/**** Base Case ****/
template<auto...I>
struct RemoveValues<std::index_sequence<I...>>
{
    template
    <
        // We use `Prefix<I>...` to enumerate `FrontTargets`.
        Prefix<I>...FrontTargets,
        // We drop the next argument.
        typename,
        typename...BackTargets
    >
    static consteval auto idyl()
    // Note that `Shuttle` is instantiated by values
    // extracted from the template parameters.
    // This is because we will pack every variable
    // into `Val`.
    -> Shuttle
    <
        FrontTargets::value...,
        BackTargets::value...
    >;

    template<auto...Agreements>
    using Page = decltype(idyl<Val<Agreements>...>());
};

template<auto...I, auto...J>
struct RemoveValues<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template
    <
        // We use `Prefix<I>...` to enumerate `FrontTargets`.
        Prefix<I>...FrontTargets,
        // We drop the next argument.
        typename,
        // We use `Prefix<J>...` to go across the distance
        // between two targets.
        Prefix<J>...MiddleTargets,
        // We drop the next argument.
        typename,
        typename...BackTargets
    >
    static consteval auto idyl()
    -> Shuttle
    <
        FrontTargets::value...,
        MiddleTargets::value...,
        BackTargets::value...
    >;

    template<auto...Agreements>
    using Page = decltype(idyl<Val<Agreements>...>());
};

/**** Recursive Case ****/
template<auto...I, auto...J, typename...OtherSequences>
struct RemoveValues<std::index_sequence<I...>, std::index_sequence<J...>, OtherSequences...>
{
    template
    <
        // We use `Prefix<I>...` to enumerate `FrontTargets`.
        Prefix<I>...FrontTargets,
        // We drop the next argument.
        typename,
        // We use `Prefix<J>...` to go across the distance
        // between two targets.
        Prefix<J>...MiddleTargets,
        // We drop the next argument.
        typename,
        typename...BackTargets
    >
    static consteval auto idyl()
    -> ExtendFront
    <
        typename RemoveValues<OtherSequences...>
        ::template Page<BackTargets::value...>
    >
    ::template Page
    <
        FrontTargets::value...,
        MiddleTargets::value...
    >;

    template<auto...Agreements>
    using Page = decltype(idyl<Val<Agreements>...>());
};

/**** Capsule ****/
template<typename...>
struct Capsule;

/**** Send ****/
template<typename...>
struct Send {};

template<template<auto...> class Sequence, auto...Variables>
struct Send<Sequence<Variables...>>
{
    template<template<auto...> class Operation>
    struct Detail
    {
        using type = Operation<Variables...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = Detail<Agreements...>::type;
};

template<template<typename...> class Container, typename...Elements>
struct Send<Container<Elements...>>
{
    template<template<typename...> class Operation>
    struct Detail
    {
        using type = Operation<Elements...>;
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};

/**** TypicalPop ****/
template<auto...>
struct TypicalPop {};

template<auto First>
struct TypicalPop<First>
{
    using type = Shuttle<>;
};

template<auto First, auto Second>
struct TypicalPop<First, Second>
{
    using type = Shuttle<First>;
};

template<auto First, auto Second, auto...Others>
struct TypicalPop<First, Second, Others...>
{
    using type
    = ExtendFront<typename TypicalPop<Others...>::type>
    ::template Page<First, Second>;
};

/**** CognateSegment ****/
template<template<auto...> class Operation>
struct CognateSegment
{
    template<size_t I, size_t...J>
    struct Detail
    {
        template<size_t...K>
        requires (...&&(K < J))
        using Hidden_t = Operation<I, J-K...>;
    };

    template<auto...Agreements>
    using Page = Send<typename TypicalPop<Agreements...>::type>
    ::template Rail<Detail<Agreements...>::template Hidden_t>;

// Indices can also be passed using `std::index_sequence`.
    template<typename>
    struct Hidden {};

    template<size_t I, size_t...J>
    struct Hidden<std::index_sequence<I, J...>>
    {
        template<size_t...K>
        requires (...&&(K < J))
        using Detail_t = Operation<I, J-K...>;

        using type = Send<typename TypicalPop<I, J...>::type>
        ::template Rail<Detail_t>;
    };

    template<typename...Agreements>
    using Mold = Hidden<Agreements...>::type;
};

/************************/
/**** Implementation ****/
/************************/

template<template<auto...> class Operation>
struct CognateRemove
{
    template<size_t I, size_t...J>
    using Detail_t = Capsule<std::make_index_sequence<I>, std::make_index_sequence<J-1>...>;

    template<size_t...I>
    struct ProtoPage
    {
        template<auto...Variables>
        using Page = Send
        <
            typename Send
            <
                typename CognateSegment<Detail_t>
                ::template Page<I...>
            >::template Road<RemoveValues>
            ::template Page<Variables...>
        >
        ::template Rail<Operation>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** Operation ****/
template<auto...>
struct Operation;

/**** Metafunction ****/
template<auto...Args>
using Metafunction = CognateRemove<Operation>
::Page<1, 3, 5>
::Page<Args...>;

/**** SupposedResult ****/
using SupposedResult = Operation<0, 2, 4>;

/**** Result ****/
using Result = Metafunction<0, -1, 2, -3, 4, -5>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);