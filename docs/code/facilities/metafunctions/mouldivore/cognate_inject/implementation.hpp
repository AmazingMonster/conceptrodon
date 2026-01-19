/**********************/
/**** Dependencies ****/
/**********************/

#include <utility>
#include <cstddef>

/**** Prefix ****/
template<typename, auto>
concept Prefix = true;

/**** Tyy ****/
template<typename Element>
struct Tyy
{
    using type = Element;
};

/************************/
/**** Implementation ****/
/************************/

/**** Enrich ****/
template<typename>
struct Enrich {};

template<size_t...I>
struct Enrich<std::index_sequence<I...>>
{
    template<typename...NewElements>
    struct ProtoMold
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
            // Collect the rest.
            BackTargets...
        )
        -> Operation
        <
            typename decltype(front_targets)::type...,
            NewElements...,
            typename BackTargets::type...
        >;
    };

    template<typename...NewElements>
    using Mold = ProtoMold<NewElements...>;
};

/**** CognateInject ****/
template<template<typename...> class Operation>
struct CognateInject
{
    template<size_t Index>
    struct ProtoPage
    {
        struct Slash
        {
            template<typename...NewElements>
            struct ProtoMold
            {
                template<typename...Elements>
                using Mold = decltype
                (
                    Enrich<std::make_index_sequence<Index>>
                    ::template ProtoMold<NewElements...>
                    ::template idyl<Operation>(Tyy<Elements>{}...)
                );
            };
        };

        template<typename...Agreements>
        using Mold = Slash::template ProtoMold<Agreements...>;
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
using SupposedResult = Operation<int, double, double*, int*, int**>;

/**** Result ****/
using Result = CognateInject<Operation>
::Page<1>
::Mold<double, double*>
::Mold<int, int*, int**>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);