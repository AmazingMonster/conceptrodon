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

/************************/
/**** Implementation ****/
/************************/

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

/***********************/
/**** First Example ****/
/***********************/

#include <tuple>

/**** At ****/
template<auto...Args>
using At = TypicalAmong<std::tuple<int, int*, int**, int***>>
::Page<Args...>
::type;

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
using Metafunction = TypicalAmong<Vessel<Flow_0, Flow_1, Flow_2, Flow_3>>
::Page<2>
::Flow<Args...>;

/**** Dummy Arguments ****/
template<template<typename...> class...>
struct Ware_0;

template<template<typename...> class...>
struct Ware_1;

/**** Test ****/
static_assert(std::same_as<Flow_2<Ware_0, Ware_1>, Metafunction<Ware_0, Ware_1>>);

/************************/
/**** Third Example ****/
/************************/

/**** Forlorn ****/
template<template<template<template<typename...> class...> class...> class...>
struct Forlorn;

/**** Tests ****/
// GCC compiles.
// Clang and MSVC fail.
static_assert(std::same_as<
    Forlorn<Metafunction>,
    Forlorn<Flow_2>
>);

// Clang and MSVC compile.
// GCC fails.
static_assert(not std::same_as<
    Forlorn<Metafunction>,
    Forlorn<Flow_2>
>);

