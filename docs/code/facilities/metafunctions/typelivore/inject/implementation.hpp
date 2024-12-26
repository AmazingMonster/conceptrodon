/**********************/
/**** Dependencies ****/
/**********************/

#include <utility>
#include <cstddef>

/**** Prefix ****/
template<typename, size_t>
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
            // We use `Prefix<I>...` to enumerate `FrontTargets`.
            Prefix<I>...FrontTargets,
            typename...BackTargets
        >
        static consteval auto idyl() ->
        // `NewVariables...` are injected in the return type.
        Operation<FrontTargets..., NewElements..., BackTargets...>;
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
            // Note that we use a parameter pack in the template head
            // even though the function only allows one operation.
            template<template<typename...> class...Agreements>
            using Road = decltype
            (
                Enrich<std::make_index_sequence<Index>>
                ::template ProtoMold<NewElements...>
                ::template idyl<Agreements..., Elements...>()
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