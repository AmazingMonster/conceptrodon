/**********************/
/**** Dependencies ****/
/**********************/

#include <cstddef>

/************************/
/**** Implementation ****/
/************************/

template<template<typename...> class...Containers>
struct Among {};

/**** Base Step ****/
template<template<typename...> class First>
struct Among<First>
{
    template<size_t I>
    struct ProtoPage {};

    template<size_t I>
    requires (I==0)
    struct ProtoPage<I>
    {
        template<typename...Agreements>
        using Mold = First<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

/**** Recursive Step ****/
template
<
    template<typename...> class First,
    template<typename...> class Second,
    template<typename...> class...Others
>
struct Among<First, Second, Others...>
{
    template<size_t I>
    struct ProtoPage 
    {
        template<typename...Agreements>
        using Mold = Among<Others...>
        ::template ProtoPage<I - 2>
        ::template Mold<Agreements...>;
    };

    template<size_t I>
    requires (I==0)
    struct ProtoPage<I>
    {
        template<typename...Agreements>
        using Mold = First<Agreements...>;
    };

    template<size_t I>
    requires (I==1)
    struct ProtoPage<I>
    {
        template<typename...Agreements>
        using Mold = Second<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

/***********************/
/**** First Example ****/
/***********************/

#include <concepts>

/*** Dummy Containers ****/
template<typename...>
struct Con_0;

template<typename...>
struct Con_1;

template<typename...>
struct Con_2;

template<typename...>
struct Con_3;

/**** Metafunction ****/
template<auto...Args>
using Metafunction
= Among<Con_0, Con_1, Con_2, Con_3>
::Page<Args...>;

/**** SupposedResult ****/
using SupposedResult = Con_3<int, int*, int**>;

/**** Result ****/
using Result = Metafunction<3>::Mold<int, int*, int**>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);

/************************/
/**** Second Example ****/
/************************/

/**** Vehicle ****/
template<template<typename...> class...>
struct Vehicle;

/**** First Test ****/
// If the following assertion passes
// , then `Metafunction<3>::Mold` and `Con_3` are considered the same.
static_assert(std::same_as<
    Vehicle<Metafunction<3>::Mold>,
    Vehicle<Con_3>
>);

/**** Second Test ****/
// If the following assertion passes
// , then `Metafunction<3>::Mold` and `Con_3` are considered different.
// Some compilers might fail on both assertions.
static_assert(not std::same_as<
    Vehicle<Metafunction<3>::Mold>,
    Vehicle<Con_3>
>);