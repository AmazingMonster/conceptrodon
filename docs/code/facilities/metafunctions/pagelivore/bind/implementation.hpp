/**********************/
/**** Dependencies ****/
/**********************/

#include <cstddef>

/**** Peg ****/
template <size_t I>
struct Peg
{ static constexpr size_t value {I}; };

/**** IsPeg ****/
template<typename>
struct IsPeg
{
    static constexpr bool value
    {false};
};

template<auto I>
struct IsPeg<Peg<I>>
{
    static constexpr bool value
    {true};
};

/**** Pegful ****/
template<typename Arg>
concept Pegful = IsPeg<Arg>::value;

/**** Nonzero ****/
template<typename Arg>
concept Nonzero = (Arg::value != 0);

/**** Among ****/
template<auto...Variables>
struct Among {};

template<auto First>
struct Among<First>
{
    template<size_t I>
    struct ProtoPage {};

    template<size_t I>
    requires (I==0)
    struct ProtoPage<I>
    { static constexpr auto value {First}; };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

template<auto First, auto Second, auto...Others>
struct Among<First, Second, Others...>
{
    template<size_t I>
    struct ProtoPage 
    { 
        static constexpr auto value 
        {Among<Others...>::template ProtoPage<I - 2>::value};
    };

    template<size_t I>
    requires (I==0)
    struct ProtoPage<I>
    { static constexpr auto value {First}; };

    template<size_t I>
    requires (I==1)
    struct ProtoPage<I>
    { static constexpr auto value {Second}; };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

/************************/
/**** Implementation ****/
/************************/

template<template<auto...> class Operation>
struct Bind
{
    template<auto...Variables>
    struct ProtoPage
    {
        template<auto...Replacements>
        struct Detail
        {
            template<auto Variable>
            static constexpr auto Hidden_v {Variable};

            // This specialization will be used
            // if `Pegful<decltype(Variable)> && Nonzero<decltype(Variable)> == true`.
            template<auto Variable>
            requires Pegful<decltype(Variable)> && Nonzero<decltype(Variable)>
            static constexpr auto Hidden_v<Variable> 
            {
                // `Replacements...` are the arguments of the finally-returned function
                Among<Replacements...>
                ::template Page<Variable.value - 1>
                ::value
            };

            using type = Operation<Hidden_v<Variables>...>;
        };

        template<auto...Agreements>
        using Page = Detail<Agreements...>::type;
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
using Metafunction = Bind<Operation>
::Page<Peg<2>{}, -2, Peg<1>{}, -4>
::Page<Args...>;

/**** SupposedResult ****/
using SupposedResult = Operation<3, -2, 1, -4>;

/**** Result ****/
// The `nullptr` at the end has not effect.
using Result = Metafunction<1, 3, nullptr>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);

