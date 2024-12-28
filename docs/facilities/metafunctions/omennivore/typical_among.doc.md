<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::TypicalAmong`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-typical-among">To Index</a></p>

## Description

`Omennivore::TypicalAmong` accepts a packed vessel.

- Suppose the vessel is a container containing elements. In that case, It returns a function. When invoked by an index, the function returns the element at the index via the member `type`.

<pre><code>   Container&lt;E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>I</sub>, ..., E<sub>n</sub>&gt;
-> I
-> E<sub>I</sub></code></pre>

- Suppose the vessel is a sequence containing variables. In that case, It returns a function. When invoked by an index, the function returns the variable at the index via the member `value`.

<pre><code>   Seq&lt;V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>I</sub>, ..., V<sub>n</sub>&gt;
-> I
-> V<sub>I</sub></code></pre>

- Suppose the vessel contains operations. In that case, its first layer accepts an index and returns a function. When invoked, the function instantiates the operation at the index with its arguments and returns the result.

<pre><code>   Vessel&lt;Oper<sub>0</sub>, Oper<sub>1</sub>, ..., Oper<sub>I</sub>, ..., Oper<sub>n</sub>&gt;
-> I
-> Args...
-> Oper<sub>I</sub>&lt;Args...&gt;</code></pre>

## Type Signature

```Haskell
-- Pick a `type`
TypicalAmong
 :: typename...
 -> auto...
 -> typename
 
-- Pick a `value`
TypicalAmong
 :: auto...
 -> auto...
 -> auto
 
-- Pick a `Mold`
TypicalAmong
 :: template<typename...> class...
 -> auto...
 -> template<typename...>
 
-- Pick a `Page`
TypicalAmong
 :: template<typename...> class...
 -> auto...
 -> template<auto...>
 
-- Pick a `Road`
TypicalAmong
 :: template<typename...> class...
 -> auto...
 -> template<template<typename...> class...>
 
-- Pick a `Rail`
TypicalAmong
 :: template<typename...> class...
 -> auto...
 -> template<template<auto...> class...>
 
-- Pick a `Flow`
TypicalAmong
 :: template<typename...> class...
 -> auto...
 -> template<template<template<typename...> class...> class...>
 
-- Pick a `Sail`
TypicalAmong
 :: template<typename...> class...
 -> auto...
 -> template<template<template<auto...> class...> class...>
 
-- Pick a `Snow`
TypicalAmong
 :: template<typename...> class...
 -> auto...
 -> template<template<template<template<typename...> class...> class...> class...>
 
-- Pick a `Hail`
TypicalAmong
 :: template<typename...> class...
 -> auto...
 -> template<template<template<template<auto...> class...> class...> class...>
 
-- Pick a `Cool`
TypicalAmong
 :: template<typename...> class...
 -> auto...
 -> template<template<template<template<template<typename...> class...> class...> class...> class...>
 
-- Pick a `Calm`
TypicalAmong
 :: template<typename...> class...
 -> auto...
 -> template<template<template<template<template<auto...> class...> class...> class...> class...>
 
-- Pick a `Grit`
TypicalAmong
 :: template<typename...> class...
 -> auto...
 -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
 
-- Pick a `Will`
TypicalAmong
 :: template<typename...> class...
 -> auto...
 -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
 
-- Pick a `Glow`
TypicalAmong
 :: template<typename...> class...
 -> auto...
 -> template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
 
-- Pick a `Dawn`
TypicalAmong
 :: template<typename...> class...
 -> auto...
 -> template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
```

## Structure

```C++
// Pick a `type`
template<typename>
struct TypicalAmong
{
    template<size_t>
    alias Page
    {
        using type = RESULT;
    };
};

// Pick a `value`
template<typename>
struct TypicalAmong
{
    template<size_t>
    alias Page
    {
        static constexpr auto value {RESULT};
    };
};

// Pick a `Mold`
template<typename>
struct TypicalAmong
{
    template<size_t>
    alias Page
    {
        template<typename...>
        alias Mold = RESULT;
    };
};

// Pick a `Page`
template<typename>
struct TypicalAmong
{
    template<size_t>
    alias Page
    {
        template<auto...>
        alias Page = RESULT;
    };
};

// Pick a `Road`
template<typename>
struct TypicalAmong
{
    template<size_t>
    alias Page
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
};

// Pick a `Rail`
template<typename>
struct TypicalAmong
{
    template<size_t>
    alias Page
    {
        template<template<auto...> class...>
        alias Rail = RESULT;
    };
};

// Pick a `Flow`
template<typename>
struct TypicalAmong
{
    template<size_t>
    alias Page
    {
        template<template<template<typename...> class...> class...>
        alias Flow = RESULT;
    };
};

// Pick a `Sail`
template<typename>
struct TypicalAmong
{
    template<size_t>
    alias Page
    {
        template<template<template<auto...> class...> class...>
        alias Sail = RESULT;
    };
};

// Pick a `Snow`
template<typename>
struct TypicalAmong
{
    template<size_t>
    alias Page
    {
        template<template<template<template<typename...> class...> class...> class...>
        alias Snow = RESULT;
    };
};

// Pick a `Hail`
template<typename>
struct TypicalAmong
{
    template<size_t>
    alias Page
    {
        template<template<template<template<auto...> class...> class...> class...>
        alias Hail = RESULT;
    };
};

// Pick a `Cool`
template<typename>
struct TypicalAmong
{
    template<size_t>
    alias Page
    {
        template<template<template<template<template<typename...> class...> class...> class...> class...>
        alias Cool = RESULT;
    };
};

// Pick a `Calm`
template<typename>
struct TypicalAmong
{
    template<size_t>
    alias Page
    {
        template<template<template<template<template<auto...> class...> class...> class...> class...>
        alias Calm = RESULT;
    };
};

// Pick a `Grit`
template<typename>
struct TypicalAmong
{
    template<size_t>
    alias Page
    {
        template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
        alias Grit = RESULT;
    };
};

// Pick a `Will`
template<typename>
struct TypicalAmong
{
    template<size_t>
    alias Page
    {
        template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
        alias Will = RESULT;
    };
};

// Pick a `Glow`
template<typename>
struct TypicalAmong
{
    template<size_t>
    alias Page
    {
        template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
        alias Glow = RESULT;
    };
};

// Pick a `Dawn`
template<typename>
struct TypicalAmong
{
    template<size_t>
    alias Page
    {
        template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
        alias Dawn = RESULT;
    };
};
```

## Examples

- We will pick out the element at index two from `std::tuple<int, int*, int**, int***>`.

```C++
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
```

- We will pick out the operation at index two from `Vessel<War_0, War_1, War_2, War_3>`.

```C++
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
```

Note that we must instantiate the operation before the comparison.
This is because the function returned by `TypicalAmong` is an alias template pointing to the actual operation in the packed vessel.
It is not quite the same as the actual operation.

```C++
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
```

## Implementation

If `TypicalAmong` or `Among` have been implemented in other namespaces, we will redirect the items extracted from the packed vessel to these functions.

Otherwise, we will transform the items into types and employ `Typelivore::TypicalAmong` to do the job.

We will implement a simplified version that picks out types and `Flow`s.

Since `Typelivore::TypicalAmong` exists, we will use it to deal with types.

```C++
template<typename>
struct TypicalAmong {};

template<template<typename...> class Container, typename...Elements>
struct TypicalAmong<Container<Elements...>>
: public Typelivore::TypicalAmong<Elements...>
{};
```

To pick out `Flow`s with `Typelivore::TypicalAmong`, we will wrap every `Flow` into a `Fly`.

```C++
template<template<template<template<typename...> class...> class...> class Sorrow>
struct Fly
{
    template<template<template<typename...> class...> class...Warehouses>
    using Flow = Sorrow<Warehouses...>;
};
```

Here's the implementation to pick out a `Flow`.

```C++
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
        // We warp each of `Flows...` into `Fly`
        // and invoke `Typelivore::TypicalAmong`. 
        using Flow = Typelivore::TypicalAmong<Fly<Flows>...>
        ::template Page<I>
        // The `type` we obtained is an instantiated `Fly`.
        ::type
        // We call the template member `Flow` with the arguments.
        ::template Flow<Arguments...>;
    };

    template<auto...Arguments>
    using Page = ProtoPage<Arguments...>;
};
```

[*Run this snippet on Godbolt*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxBIA7ACcpAAOqAqETgwe3r56KWmOAkEh4SxRMVwJtpj2BQxCBEzEBFk%2BflxVNRn1jQRFYZHRcYkKDU0tOe0jPX0lZUMAlLaoXsTI7BwA9ABUO7t7%2BwdbGyYaAILbuwDUACKYSa6MyHiYCpd7x2cXh9/7H6cn/zMAGZgshvFhLiYgW5kCN0FgqFDsACAV8tpcACoAT3utDwADcSOwQNiknhRLRTiwBMA3rs/sw2Aokkw1picdUCUTIbErGcAQRMCwkgZBVC3AQOYzMAA6OXYehsQQKJEAkbELwOdlkilUmk8qyxa5Qvn/M6C4WizDiyX3aWXABieGII1VZ3VmoI2vJYj1RnFTpdBDd/15AMuEcuFpFTDF0LSAC9MAB9L0ASRDkcuHq1ymIqCIyiYwEwBpMRpNKLOWejVvFiZT6czkeImAAjl5nS9LhAM0Djf2NPNw5Gc168wXUEWS%2BK%2B8jq5HyxZLl40kYoxzIf3Hc7XUDl%2BWB6aRxHa7HrdCmF4iHKZadgK2hYwCCqgfPTlnV8FadPS1DrpcE6FsWF5uPej5Ki%2Bt5IiAIC2hex4VvuVanGecYSlKrCloGIykBudpYZcQiYGgDDoHh8HSreADyBAINEr7vmO3q6tS/rQjhBB4cRpHkZctH0S60FviiYYLqeQoxuhDappcc4ntmBAarm%2BbASWkLiQaK5rrS8FbgBpI%2BpSbHAOKAkMcJ2CwWhpZAVOIGzpcAC0lxmDBcEciaPJHihNaSXW8Z4EmsnyZprYdl2ry9v%2B/5DgpzF2b%2Bs7NhGS7ad%2B%2BF/tunFeYelb8ppNn1kFjZySllzhZ2rZRX2A7XFww6aQlqn2TO0KhR%2Bi68ul656f%2BREkQI6C5Uhx6Ff557ileN5yuBmBPsq5Vfuuv76YBLVJdCc0LVBcqqsh/KjSheUFeceyOrQJA%2BgwdI7H8RXQg9EoTehT2UVhlmXGCTAKAon3fb9/0GL9REkPmADuIbMQ6l3ENdommn5lqTY9L2gW9mFsEDP1/Xtb5fcDuMygA6o0mAIMsSiMQpy20jDqDg2tQhgwz4qk62FOri8ln5aGPmnWiPxC0cqLnWmlo7bGGS3SLnzC/LstmmdVyGax%2BrvAKaM2pjF5MUpnosb6Jllkdp1vVrj069jIMeIITDBNEFFW/KirPtT7r61qqtGzS4q2w0DvEOKCo7UT%2B3viAlxJF4ER4sg2qcoSrawd7xm%2B9CIeQWHImHYa/NK0V/LQgp5vI69FvPWX6POzKSIEzj1vZ9g9eA3jzcA68ABqLx2KQCkbBslzYKoSmsl6hBCq8VD5iwlxMFHrIANaYOglz4j31S1%2BNVc2hXGMEVjbct03x%2BN7e9PgyqRd68pXqp36pnQt3v3VAGl2XzzOehojkZPdNqBlS/lmZqk4kqaSXApJGUl0Z7z3jXOuHcz6zWIMAHwbtypZgHpcYmpZwaNCSJcTArIECXFQFQSEAA2DQF8w5UMuMEIglDqGw3hlQyBkYsGGFXsEQky8mGkkTkSFOOIjIPxMFQmUGlOpZgjLTC6DM1oCLxEnYk98TJvyuqIBgGjL5Ih5ppLM1k0aAQcu1DBHDB4Ynokw%2BC4iNCXHBqWVAEQA4hG4a8Qw9CGBTEEHgc8q87H0zhlouxW9pEyOsp5AxFjsGlgpLQKM1ibKXDYKUaITCL52IcYQEhdFSyNFQVnMJMjIxGKrvIyGW0UFoOVJ/H%2BqVTZKygQFNw/9bynGqVnJaOkTHqX6olUxYFOluzqaJfOosFY/D%2BGiHcQYh6qFYCKUsGs5aTO%2BH8FEwJQTgiyhKLwSyQwTJ2JcVCMt7oVzacg4A7tThyNOf1NR6c3Bwmsvs%2Bg4oGF4QYVsL5ggdi/IILscOAJYKbSGdc/RpxIn3F5kc9EQh9l5BXgAJReF4WgXoVm3J6QipISL0CooUOir0/VvlbFhas45hLiVnIBHI6lGK1qoXFG5ESB0lYzIxC8TF9I1QNEcMgZMONogEAgC8kACgsJCtfG4BlXEiKItSCitFGKkTDnZXCtZvw4UDV4vMxZ9BaWUq1dqgW51n52CNahWBO9Ua2srtA7WB9ZRH0Qa6wmSDa5f2Yha1%2BGrjU3B8CwLEJzhnKitaXR1dqo0YWdZ6hBHq258tvhU5MGgKXWvtZGlp71D5evbom/Np8k0exTRfZMXAM3ZpRg6nN8D8ZuqLY2qGnsvTltZWNTNMbq2vXrQWhu7qB35uTQbctQIM0zIALKYAaFQLwDAHDSyxT2mBWa%2B3FqbYWjp1yQxyOnbO%2Bdi6BCKJEWrdibhfW0B0WmvC5b2iprMLe9%2ByZx1sojiAMFrL32ZKqRCpN/rlbHOuEGkN26akvgjTa7t67m3etbdgsmaaq1QbrXGwdrdh2loNuzFMlaAOcu5VaqYArpVKCaGKgg6BYKSrYNK69rK3A4ZvQh1sFakR4X3UwOdC7ahs0QxoPCTG8PIjfOqztgsTV3R1VY50q9h4GuWby41kmpNmquA6EgsMbrLpQzWldTrGAfXQyfWD/aMMtrLZpkg2j8PnS5SMV4WKsEAHE3BuC%2BqgYUdBuaokHm4Aw64uGXEnUITu7mqD21oGE4j5JSMioo1RiVUqfrigUhp4gWnxSce40emz2A%2B6aXS5ljiz6v0olExOvzAXaRBZC2FjzXn6BhJc25y4EW6B/T5VLQVwryMMALIpRLNGUwpeLoVqzxAbNuGy4e3jb4CvhKK9Z%2BjhyKsAY4IsWgnAACsvA/AcC0KQVAnA3DWGsNmZYqw/zAh4KQAgmgNuLEXiAbbkgZQaAABxmDMPEeIXBtufY%2BxUWI0gtscEkLwFgEgNACf24d47HBeAKBAAJ%2B7B2NukDgLAGAiAQDLAINHLiFAIBoEa9EUIWFOCqA%2BxQpyFDJCXGAMgeOUgZRmF4CvQgV0qPtH4IIEQYh2BSBkIIRQKh1Do9ILodo4NiBMCSJwHgm2dt7Ye0dzg1FryE9IeQ6ntP6eM%2BZ5cVnZgeweDJ8QSEN35i8DR1oRYEAkCk7JPQMgxPnfeZiMAKQj6aAYoYpQCIauIjBEaFiRXvAQ/MGIFiaiERtAkTR7d0nkFqIMFoOHyXWAIheGAK02gtBkfcF4FgFghhgDiCz12Rd68i%2BHcwKoEi151i3YYdUNXeIIhy5jx4LAaulJ4Ch8X0g69iARCVbcMvRg8RGAe4sKgBhrmd2eODaidoI8i%2BEBSIX0g%2BfyCUGoNX0v9Dl5QGdyw%2Bg8ARGR5ARYqAki1CL05OE/5TCWGsGYeHo%2B4ZYBvxARYdgieGQLgZE4wbQpAgQDsswgw7QeQ6QAgYBuQqQ8BDAMwAw5QHQQBAg3QYwngrQeggBuWOBvQUB6BBBowzQeBEwtgFBaBaS5QABl2awEgyuHAu2pAcOvACOlweudODOTOLOb2puEAuAXOlu5gQIDUtuc%2Biw9ETAWAMQ/%2BpAz2kgQIMo8QQIIOGgkgZgkgVCGg22FCiQYOEOpAUOkhMoFCXAFCH28QQOFCr2/2GhFCHBauCOSOKOd2c%2BmOOOjueOWu145AlAHuruFObAnAjQLA%2BIsQTk883064XA8QMoXA72HO%2BARAP%2Bege%2BAu4gwue%2BYuh%2Bkuugj6su8uEerB7BnB6uHAmuBO14OuPBNOfB9cCRSRKR9iEA5uLu6SEhZgNuXh6ODuTunm3RbuwRIxnuKA1WiRXAAmfugoLogeweoeMeG%2BUeYeceCeDgG%2BKez4aeGeau2eue%2BeheG%2Bpe5eleh2%2BArYNeLwauDeTegoG%2BbeYOh2ne3eWIve6wh2A%2BQ%2Bt2o%2B4%2BSgk%2BFx343hC%2BxYCgy%2BmAq%2B6%2Bw%2B2R2%2BEgu%2BsgBREuh2xRJ%2Bs%2Bb%2BVgF%2Bnef%2Bd%2BD%2BGQT%2BL%2B/YWJH%2BX%2B0QP%2Bdxt%2BmBuWIB7gVB4BkBxQZBsByBtQiBrJ%2BQGQdBcwkw1QWBdQFBHJNJtQxBPJMBNBPQwpUwTQ4pDBSwKwzBDU%2BgKurhku3BvBBu8RtIiRyR72PYohGRVukh/Rduj2pAchChlArBph5hSR2hsQ228QsQsQQIOhehkg7QVR7htgnhZpDuvhSA%2BOhOQRJOExoRlOHAkRBuLACg%2BI8c%2BIupVoIwaRYheAPOm%2BORO%2Bm%2BKJR%2BIAQIpApRCuxeFRqu6pGuARXoZCPBMZcZCZSZ54IwZu4ZPRwIQIpp3hfhIRjs7uLZMQ8ZeKyYiZ8QyYyZBAyYqg9OfAdACxyOEAQeku6xqxw%2BS5se8eieOxnmqe6emeVxmAOeeeYgpxw%2B5x0%2B3xJe1ejgte9xjeyAzezxgg7eku7xYeXx/ecMfxvAAJE%2BQoIJs%2BgxfAi%2BkJK%2Ba%2BjAG%2B8JguiJOZB%2BqJOg%2BZGJxg5%2BNguJ8A%2BJj%2BnAGwLypJlgn%2BXB3%2B6ZVJShhBtQdJwpTJ/Q9BSBXJCBDJVFKBcpBB/JRBQptFfJnQ2BtBpBlFkwLF2Q4BMpJBzJ3FjBipQupZap8OnANZDOsZ8Za8DZgoTZIh6RJAxpUhAx9ushRCVpShJhkOIAP2MoQIQI22AOnpMOxlsQNhElXBnAHhqOMhyhIAkg226hwOMOH2kgf2XAX2ZgLhYOQIZZkliOGl5pYO7ONl1R0hgxiwo%2BaQzgkgQAA)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/omennivore/among/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/omennivore/among.hpp)
- [Unit test](../../../../tests/unit/metafunctions/omennivore/typical_among.type.test.hpp)
