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
            typename...BackArgs
        >
        static consteval auto idyl
        (
            // Expand `Prefix<I>` to count the arguments from the front.
            Prefix<I> auto...front_args,
            // Collect the rest.
            BackArgs...
        )
        -> Operation
        <
            typename decltype(front_args)::type...,
            NewElements...,
            typename BackArgs::type...
        >;
    };

    template<typename...NewElements>
    using Mold = ProtoMold<NewElements...>;
};

/**** Inject ****/
template<typename...Elements>
struct Inject
{
    template<size_t Index>
    struct ProtoPage
    {   
        template<typename...NewElements>
        struct ProtoMold
        {
            template<template<typename...> class...Agreements>
            using Road = decltype
            (
                Enrich<std::make_index_sequence<Index>>
                ::template ProtoMold<NewElements...>
                ::template idyl<Agreements...>(Tyy<Elements>{}...)
            );
        };

        template<typename...NewElements>
        using Mold = ProtoMold<NewElements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

/*****************/
/**** Example ****/
/*****************/

/**** Operation ****/
template<typename...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<int, double, double*, int*, int**>;

/**** Result ****/
using Result = Inject<int, int*, int**>
::Page<1>
::Mold<double, double*>
::Road<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);