/**********************/
/**** Dependencies ****/
/**********************/

#include <cstddef>

/**** Typelivore::TypicalAmong ****/
namespace Typelivore {

template<typename...Elements>
struct TypicalAmong {};

template<typename First>
struct TypicalAmong<First>
{
    template<size_t I>
    struct ProtoPage {};

    template<size_t I>
    requires (I==0)
    struct ProtoPage<I>
    { using type = First; };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>::type;
};

template<typename First, typename Second, typename...Others>
struct TypicalAmong<First, Second, Others...>
{
    template<size_t I>
    struct ProtoPage 
    { using type = TypicalAmong<Others...>::template ProtoPage<I - 2>::type; };

    template<size_t I>
    requires (I==0)
    struct ProtoPage<I>
    { using type = First; };

    template<size_t I>
    requires (I==1)
    struct ProtoPage<I>
    { using type = Second; };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

}

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

/************************/
/**** Implementation ****/
/************************/

/**** Bind ****/
template<template<typename...> class Operation>
struct Bind
{
    template<typename...Elements>
    struct ProtoMold
    {
        template<typename...Replacements>
        struct Detail
        {
            template<typename Element>
            struct Hidden 
            { using type = Element; };

            template<typename Element>
            requires Pegful<Element> && Nonzero<Element>
            struct Hidden<Element>
            { 
                using type = Typelivore::TypicalAmong<Replacements...>
                ::template Page<Element::value - 1>
                ::type; 
            };

            using type = Operation<typename Hidden<Elements>::type...>;
        };

        template<typename...Agreements>
        using Mold = Detail<Agreements...>::type;
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
using Metafunction = Bind<Operation>
::Mold<Peg<2>, Vay<-2>, Peg<1>, Vay<-4>>
::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult = Operation<Vay<3>, Vay<-2>, Vay<1>, Vay<-4>>;

/**** Result ****/
// The `void` at the end has not effect.
using Result = Metafunction<Vay<1>, Vay<3>, void>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);