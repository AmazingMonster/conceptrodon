/**********************/
/**** Dependencies ****/
/**********************/

#include <utility>
#include <cstddef>

/**** Prefix ****/
template<typename, auto>
concept Prefix = true;

/**** Capsule ****/
template<typename...>
struct Capsule;

/**** ExtendFront ****/
template<typename>
struct ExtendFront {};

template<template<typename...> class Container, typename...Elements>
struct ExtendFront<Container<Elements...>>
{
    template<typename...Beginnings>
    using Mold = Container<Beginnings..., Elements...>;
};

template<template<auto...> class Sequence, auto...Variables>
struct ExtendFront<Sequence<Variables...>>
{
    template<auto...Beginnings>
    using Page = Sequence<Beginnings..., Variables...>;
};

/**** Omennivore::ClassicModifyTypes ****/
namespace Omennivore {

template<typename...>
struct InsertTypes {};

/**** Base Case ****/
template<auto...I>
struct InsertTypes<std::index_sequence<I...>>
{
    template<typename NewElement, typename...>
    struct ProtoMold
    {
        template<typename...BackArgs>
        static consteval auto idyl
        (
            // Expand `Prefix<I>` to reach the desired position.
            Prefix<I> auto...front_args,
            // Collect the rest arguments.
            BackArgs...
        )
        -> Capsule
        <
            typename decltype(front_args)::type...,
            NewElement,
            typename BackArgs::type...
        >;

        template<typename...Agreements>
        using Mold = decltype(idyl(std::type_identity<Agreements>{}...));
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

template<auto...I, auto...J>
struct InsertTypes<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template<typename FirstNewElement, typename SecondNewElement, typename...>
    struct ProtoMold
    {
        template<typename...BackArgs>
        static consteval auto idyl
        (
            // Expand `Prefix<I>` to reach the position for the first new element.
            Prefix<I> auto...front_args,
            // Expand `Prefix<J>` to reach the position for the second new element.
            Prefix<J> auto...middle_args,
            // Collect the rest arguments.
            BackArgs...
        )
        -> Capsule
        <
            typename decltype(front_args)::type...,
            FirstNewElement,
            typename decltype(middle_args)::type...,
            SecondNewElement,
            typename BackArgs::type...
        >;

        template<typename...Agreements>
        using Mold = decltype(idyl(std::type_identity<Agreements>{}...));
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

/**** Recursive Case ****/
template<auto...I, auto...J, typename...OtherSequences>
struct InsertTypes<std::index_sequence<I...>, std::index_sequence<J...>, OtherSequences...>
{
    template<typename FirstNewElement, typename SecondNewElement, typename...OtherNewElements>
    struct ProtoMold
    {
        template<typename...BackArgs>
        static consteval auto idyl
        (
            // Expand `Prefix<I>` to reach the position for the first new element.
            Prefix<I> auto...front_args,
            // Expand `Prefix<J>` to reach the position for the second new element.
            Prefix<J> auto...middle_args,
            // Collect the rest arguments.
            BackArgs...
        )
        -> ExtendFront
        <
            decltype
            (
                InsertTypes<OtherSequences...>
                ::template Mold<OtherNewElements...>
                ::idyl(BackArgs{}...)
            )
        >
        ::template Mold
        <
            typename decltype(front_args)::type...,
            FirstNewElement,
            typename decltype(middle_args)::type...,
            SecondNewElement
        >;

        template<typename...Agreements>
        using Mold = decltype(idyl(std::type_identity<Agreements>{}...));
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

}

/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** Varybivore::TypicalPop ****/
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

/**** Pagelivore::CognateSegment ****/
namespace Pagelivore {

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

}

/************************/
/**** Implementation ****/
/************************/

template<template<typename...> class Operation>
struct CognateInsert
{
    template<typename...Elements>
    struct ProtoMold
    {
        template<size_t I, size_t...J>
        using Detail_t = Capsule<std::make_index_sequence<I>, std::make_index_sequence<J>...>;

        template<size_t...I>
        struct ProtoPage
        {
            template<typename...NewElements>
            using Mold = Send
            <
                typename Send
                <
                    typename Pagelivore::CognateSegment<Detail_t>
                    ::template Page<I...>
                >::template Road<Omennivore::InsertTypes>
                ::template Mold<NewElements...>
                ::template Mold<Elements...>
            >
            ::template Road<Operation>;
        };

        template<auto...Agreements>
        using Page = ProtoPage<Agreements...>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** Vay ****/
template<auto I>
struct Vay
{ static constexpr auto value {I}; };

/**** Operation ****/
template<typename...>
struct Operation;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = CognateInsert<Operation>
::Mold<Vay<0>, Vay<2>, Vay<4>>
::Page<1, 2, 3>
::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult = Operation
<Vay<0>, Vay<-1>, Vay<2>, Vay<-3>, Vay<4>, Vay<-5>>;

/**** Result ****/
using Result = Metafunction<Vay<-1>, Vay<-3>, Vay<-5>>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);