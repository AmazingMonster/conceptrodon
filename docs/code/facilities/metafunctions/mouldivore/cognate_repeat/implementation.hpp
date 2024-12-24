/**********************/
/**** Dependencies ****/
/**********************/

#include <cstddef>

/**** ExtendBack ****/
template<typename...>
struct ExtendBack {};

template<
    template<typename...> class Container,
    typename...Elements
>
struct ExtendBack<Container<Elements...>>
{
    template<typename...Agreements>
    using Mold = Container<Elements..., Agreements...>;
};

/**** Capsule ****/
template<typename...>
struct Capsule;

/**** Typelivore::TypicalReiterate ****/
namespace Typelivore {

template<typename...Elements>
struct TypicalReiterate
{
    template<auto...>
    struct ProtoPage {};

// Base Case:
    template<auto I>
    requires (I == 0)
    struct ProtoPage<I>
    {
        using type = Capsule<>;
    };

    template<auto I>
    requires (I == 1)
    struct ProtoPage<I>
    {
        using type = Capsule<Elements...>;
    };

// Recursive Case:
    template<auto I>
    requires (2 <= I)
    struct ProtoPage<I>
    {
        using type = ExtendBack<typename ProtoPage<I - 2>::type>
        ::template Mold<Elements..., Elements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

}

/**** Send ****/
template<typename...>
struct Send {};

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

/************************/
/**** Implementation ****/
/************************/

template<template<typename...> class Operation>
struct CognateRepeat
{
    template<size_t Amount>
    struct ProtoPage
    {
        template<typename...Elements>
        using Mold = Send
        <
            typename Typelivore::TypicalReiterate<Elements...>
            ::template ProtoPage<Amount>::type
        >
        ::template Road<Operation>;
    };

    template<size_t...Agreements>
    using Page = ProtoPage<Agreements...>;
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

/**** SuppoesedResult ****/
using SupposedResult = Operation<
    Vay<0>, Vay<1>,
    Vay<0>, Vay<1>,
    Vay<0>, Vay<1>,
    Vay<0>, Vay<1>
>;

/**** Result ****/
using Result = CognateRepeat<Operation>
::Page<4>
::Mold<Vay<0>, Vay<1>>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);