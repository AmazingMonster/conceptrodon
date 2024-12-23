/**********************/
/**** Dependencies ****/
/**********************/

#include <cstddef>

/************************/
/**** Implementation ****/
/************************/

template<template<typename...> class...Containers>
struct Among {};

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
// GCC compiles.
// Clang and MSVC fail.
static_assert(std::same_as<
    Vehicle<Metafunction<3>::Mold>,
    Vehicle<Con_3>
>);

/**** Second Test ****/
// Clang and MSVC compile.
// GCC fails.
static_assert(not std::same_as<
    Vehicle<Metafunction<3>::Mold>,
    Vehicle<Con_3>
>);