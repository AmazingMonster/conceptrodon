/**********************/
/**** Dependencies ****/
/**********************/

#include <utility>
#include <cstddef>

/**** Vay ****/
template<auto Variable>
struct Vay
{ static constexpr auto value {Variable}; };

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
    template<auto...NewVariables>
    struct ProtoPage
    { 
        template
        <
            template<auto...> class Operation,
            // We use `Prefix<I>...` to enumerate `FrontTargets`.
            Prefix<I>...FrontTargets,
            typename...BackTargets
        >
        static consteval auto idyl() ->
        // `NewVariables...` are injected in the return type.
        // Note that `Operation` is invoked by values
        // extracted from the template parameters.
        // This is because we will pack every item
        // of `Variables...` into `Vay`.
        Operation<FrontTargets::value..., NewVariables..., BackTargets::value...>;
    };

    template<auto...NewVariables>
    using Page = ProtoPage<NewVariables...>;
};

/**** CognateInject ****/
template<template<auto...> class Operation>
struct CognateInject
{
    template<size_t Index>
    struct ProtoPage
    {
        struct Slash
        {
            template<auto...NewVariables>
            struct ProtoPage
            {
                template<auto...Variables>
                using Page = decltype
                (
                    // Note that we use a parameter pack in the template head
                    // even though the function only allows one operation.
                    Enrich<std::make_index_sequence<Index>>
                    ::template ProtoPage<NewVariables...>
                    ::template idyl<Operation, Vay<Variables>...>()
                );
            };
        };

        template<auto...Agreements>
        using Page = Slash::template ProtoPage<Agreements...>;
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

/**** SupposedResult ****/
using SupposedResult = Operation<0, 10, 11, 1, 2>;

/**** Result ****/
using Result = CognateInject<Operation>
::Page<1>
::Page<10, 11>
::Page<0, 1, 2>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);