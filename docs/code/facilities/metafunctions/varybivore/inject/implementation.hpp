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
            decltype(front_args)::value...,
            NewVariables...,
            BackArgs::value...
        >;
    };

    template<auto...NewVariables>
    using Page = ProtoPage<NewVariables...>;
};

/**** Inject ****/
template<auto...Variables>
struct Inject
{
    template<size_t Index>
    struct ProtoPage
    {   
        struct Slash
        {
            template<auto...NewVariables>
            struct ProtoPage
            {
                template<template<auto...> class...Agreements>
                using Rail = decltype
                (
                    Enrich<std::make_index_sequence<Index>>
                    ::template ProtoPage<NewVariables...>
                    ::template idyl<Agreements...>(Vay<Variables>{}...)
                );
            };
        };

        template<auto...NewVariables>
        using Page = Slash::template ProtoPage<NewVariables...>;
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
using SupposedResult = Operation<0, 10, 11, 1, 2>;

/**** Result ****/
using Result = Inject<0, 1, 2>
::Page<1>
::Page<10, 11>
::Rail<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);