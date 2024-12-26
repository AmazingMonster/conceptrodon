/**********************/
/**** Dependencies ****/
/**********************/

#include <cstddef>

/************************/
/**** Implementation ****/
/************************/

template<template<auto...> class...Sequences>
struct Among {};

template<template<auto...> class First>
struct Among<First>
{
    template<size_t I>
    struct ProtoPage {};

    template<size_t I>
    requires (I==0)
    struct ProtoPage<I>
    {
        template<auto...Agreements>
        using Page = First<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

template
<
    template<auto...> class First,
    template<auto...> class Second,
    template<auto...> class...Others
>
struct Among<First, Second, Others...>
{
    template<size_t I>
    struct ProtoPage 
    {
        template<auto...Agreements>
        using Page = Among<Others...>
        ::template ProtoPage<I - 2>
        ::template Page<Agreements...>;
    };

    template<size_t I>
    requires (I==0)
    struct ProtoPage<I>
    {
        template<auto...Agreements>
        using Page = First<Agreements...>;
    };

    template<size_t I>
    requires (I==1)
    struct ProtoPage<I>
    {
        template<auto...Agreements>
        using Page = Second<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

/***********************/
/**** First Example ****/
/***********************/

#include <concepts>

/**** Sequences ****/
template<auto...>
struct Seq_0;

template<auto...>
struct Seq_1;

template<auto...>
struct Seq_2;

template<auto...>
struct Seq_3;

/**** Metafunction ****/
template<auto...Args>
using Metafunction
= Among<Seq_0, Seq_1, Seq_2, Seq_3>
::Page<Args...>;

/**** SupposedResult ****/
using SupposedResult = Seq_3<0, 1, 2>;

/**** Result ****/
using Result = Metafunction<3>::Page<0, 1, 2>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);

/************************/
/**** Second Example ****/
/************************/

/**** Carrier ****/
template<template<auto...> class...>
struct Carrier;

/**** Tests ****/
// GCC compiles.
// Clang and MSVC fail.
static_assert(std::same_as<
    Carrier<Metafunction<3>:: Page>,
    Carrier<Seq_3>
>);

// Clang and MSVC compile.
// GCC fails.
static_assert(not std::same_as<
    Carrier<Metafunction<3>:: Page>,
    Carrier<Seq_3>
>);