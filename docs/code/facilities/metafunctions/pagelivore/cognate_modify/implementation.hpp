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

/**** Vay ****/
template<auto Variable>
struct Vay
{ static constexpr auto value {Variable}; };

/**** Prefix ****/
template<typename, auto>
concept Prefix = true;

/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** Omennivore::ModifyValues ****/
namespace Omennivore {

template<typename...>
struct ModifyValues {};

/**** Base Case ****/
template<auto...I>
struct ModifyValues<std::index_sequence<I...>>
{
    template<template<auto...> class Operation>
    struct ProtoRail
    {
        template
        <
            // We use `Prefix<I>...` to enumerate `FrontTargets`.
            Prefix<I>...FrontTargets,
            // We will transform the next argument.
            typename Target,
            typename...BackTargets
        >
        static consteval auto idyl()
        // Note that `Shuttle` is instantiated by values
        // extracted from the template parameters.
        // This is because we will pack every variable
        // into `Vay`.
        -> Shuttle
        <
            FrontTargets::value...,
            Operation<Target::value>::value,
            BackTargets::value...
        >;

        template<auto...Agreements>
        using Page = decltype(idyl<Vay<Agreements>...>());
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

template<auto...I, auto...J>
struct ModifyValues<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template<template<auto...> class Operation>
    struct ProtoRail
    {
        template
        <
            // We use `Prefix<I>...` to enumerate `FrontTargets`.
            Prefix<I>...FrontTargets,
            // We will transform the next argument.
            typename FirstTarget,
            // We use `Prefix<J>...` to go across the distance
            // between two targets.
            Prefix<J>...MiddleTargets,
            // We will transform the next argument.
            typename SecondTarget,
            typename...BackTargets
        >
        static consteval auto idyl()
        -> Shuttle
        <
            FrontTargets::value...,
            Operation<FirstTarget::value>::value,
            MiddleTargets::value...,
            Operation<SecondTarget::value>::value,
            BackTargets::value...
        >;

        template<auto...Agreements>
        using Page = decltype(idyl<Vay<Agreements>...>());
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

/**** Recursive Case ****/
template<auto...I, auto...J, typename...OtherSequences>
struct ModifyValues<std::index_sequence<I...>, std::index_sequence<J...>, OtherSequences...>
{
    template<template<auto...> class Operation>
    struct ProtoRail
    {
        template
        <
            // We use `Prefix<I>...` to enumerate `FrontTargets`.
            Prefix<I>...FrontTargets,
            // We will transform the next argument.
            typename FirstTarget,
            // We use `Prefix<J>...` to go across the distance
            // between two targets.
            Prefix<J>...MiddleTargets,
            // We will transform the next argument.
            typename SecondTarget,
            typename...BackTargets
        >
        static consteval auto idyl()
        -> ExtendFront
        <
            typename ModifyValues<OtherSequences...>
            ::template Rail<Operation>
            ::template Page<BackTargets::value...>
        >
        ::template Page
        <
            FrontTargets::value...,
            Operation<FirstTarget::value>::value,
            MiddleTargets::value...,
            Operation<SecondTarget::value>::value
        >;

        template<auto...Agreements>
        using Page = decltype(idyl<Vay<Agreements>...>());
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

}

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
namespace Varybivore {

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

}

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
    using Page = Send<typename Varybivore::TypicalPop<Agreements...>::type>
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

        using type = Send<typename Varybivore::TypicalPop<I, J...>::type>
        ::template Rail<Detail_t>;
    };

    template<typename...Agreements>
    using Mold = Hidden<Agreements...>::type;
};

/************************/
/**** Implementation ****/
/************************/

template<template<auto...> class Operation>
struct CognateModify
{
    template<template<auto...> class Hormone>
    struct ProtoRail
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
                >::template Road<Omennivore::ModifyValues>
                ::template ProtoRail<Hormone>
                ::template Page<Variables...>
            >
            ::template Rail<Operation>;
        };

        template<auto...Agreements>
        using Page = ProtoPage<Agreements...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** UnaryMinus ****/
template<auto I>
struct UnaryMinus
{
    static constexpr auto value
    {-I};
};

/**** Operation ****/
template<auto...>
struct Operation;

/**** Metafunction ****/
template<auto...Args>
using Metafunction = CognateModify<Operation>
::Rail<UnaryMinus>
::Page<1, 3, 5>
::Page<Args...>;

/**** SupposedResult ****/
using SupposedResult = Operation<0, -1, 2, -3, 4, -5>;

/**** Result ****/
using Result = Metafunction<0, 1, 2, 3, 4, 5>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);