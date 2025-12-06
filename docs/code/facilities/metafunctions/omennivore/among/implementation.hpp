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

/**** Florican ****/
template<template<template<template<typename...> class...> class...> class Sorrow>
struct Florican
{
    template<template<template<typename...> class...> class...Warehouses>
    using Flow = Sorrow<Warehouses...>;
};

/**** TypicalAmong ****/
template<typename>
struct TypicalAmong {};

template<template<typename...> class Container, typename...Elements>
struct TypicalAmong<Container<Elements...>>
: public Typelivore::TypicalAmong<Elements...>
{};

template
<
    template<template<template<template<typename...> class...> class...> class...> class Vessel,
    // Extract items from a packed vessel.
    template<template<template<typename...> class...> class...> class...Flows
>
struct TypicalAmong<Vessel<Flows...>>
{
    template<auto I>
    struct ProtoPage
    {
        template<template<template<typename...> class...> class...Arguments>
        // We warp each of `Flows...` into `Florican`
        // and invoke `Typelivore::TypicalAmong`. 
        using Flow = Typelivore::TypicalAmong<Florican<Flows>...>
        ::template Page<I>
        // The `type` we obtained is an instantiated `Florican`.
        ::type
        // We call the template member `Flow` with the arguments.
        ::template Flow<Arguments...>;
    };

    template<auto...Arguments>
    using Page = ProtoPage<Arguments...>;
};

/************************/
/**** Implementation ****/
/************************/

template<typename...PackedVessels>
struct Among
: public TypicalAmong<PackedVessels...>
{};

template<template<typename...> class Container, typename...Elements>
struct Among<Container<Elements...>>
{
    template<auto I>
    struct Detail
    {
        using type = Typelivore::TypicalAmong<Elements...>
        ::template ProtoPage<I>
        ::type;
    };

    template<auto...Agreements>
    using Page = Detail<Agreements...>::type;
};

/***********************/
/**** First Example ****/
/***********************/

#include <tuple>

/**** At ****/
template<auto...Args>
using At = Among<std::tuple<int, int*, int**, int***>>
::Page<Args...>;

/**** SupposedResult ****/
using SupposedResult = int**;

/**** Result ****/
using Result = At<2>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);

/************************/
/**** Second Example ****/
/************************/

/**** Vessel ****/
template<template<template<template<typename...> class...> class...> class...>
struct Vessel;

/**** Dummy Arguments ****/
template<template<template<typename...> class...> class...>
struct Flow_0;

template<template<template<typename...> class...> class...>
struct Flow_1;

template<template<template<typename...> class...> class...>
struct Flow_2;

template<template<template<typename...> class...> class...>
struct Flow_3;

/**** Metafunction ****/
template<template<template<typename...> class...> class...Args>
using Metafunction = Among<Vessel<Flow_0, Flow_1, Flow_2, Flow_3>>
::Page<2>
::Flow<Args...>;

/**** Dummy Arguments ****/
template<template<typename...> class...>
struct War_0;

template<template<typename...> class...>
struct War_1;

/**** Test ****/
static_assert(std::same_as<Flow_2<War_0, War_1>, Metafunction<War_0, War_1>>);

/************************/
/**** Third Example ****/
/************************/

/**** Forlorn ****/
template<template<template<template<typename...> class...> class...> class...>
struct Forlorn;

/**** First Test ****/
// If the following assertion passes
// , then `Metafunction` and `Flow_2` are considered the same.
static_assert(std::same_as<
    Forlorn<Metafunction>,
    Forlorn<Flow_2>
>);

/**** Second Test ****/
// If the following assertion passes
// , then `Metafunction` and `Flow_2` are considered different.
// Some compilers might fail on both assertions.
static_assert(not std::same_as<
    Forlorn<Metafunction>,
    Forlorn<Flow_2>
>);

