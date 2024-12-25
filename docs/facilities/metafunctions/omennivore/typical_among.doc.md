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
struct War_0;

template<template<typename...> class...>
struct War_1;

/**** Test ****/
static_assert(std::same_as<Flow_2<War_0, War_1>, Metafunction<War_0, War_1>>);
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

[*Run this snippet on Godbolt*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxBIA7ACcpAAOqAqETgwe3r56KWmOAkEh4SxRMVwJtpj2BQxCBEzEBFk%2BflxVNRn1jQRFYZHRcYkKDU0tOe0jPX0lZUMAlLaoXsTI7BwA9ABUO7t7%2BwdbGyYaAILbuwDUACKYSa6MyHiYCpd7x2cXh9/7H6cn/zMAGZgshvFhLiYgW5kCN0FgqFDsACAV8tpcACoAT3utDwADcSOwQNiknhRLRTiwBMA3rs/sw2Aokkw1picdUCUTIbErGcAQRMCwkgZBVC3AQOYzMAA6OXYehsQQKJEAkbELwOdlkilUmk8qyxa5Qvn/M6C4WizDiyX3aWXABieGII1VZ3VmoI2vJYj1RnFTpdBDd/15AMuEcuFpFTDF0LSAC9MAB9L0ASRDkcuHq1ymIqCIyiYwEwBpMRpNKLOWejVvFiZT6czkeImAAjl5nS9LhAM0Djf2NPNw5Gc168wXUEWS%2BK%2B8jq5HyxZLl40kYoxzIf3Hc7XUDl%2BWB6aRxHa7HrdCmF4iHKZadgK2hYwCCqgfPTlnV8FadPS1DrpcE6FsWF5uPej5Ki%2Bt5IiAIC2hex4VvuVanGecYSlKrCloGIykBudpYZcQiYGgDDoHh8HSreADyBAINEr7vmO3q6tS/rQjhBB4cRpHkZctH0S60FviiYYLqeQoxuhDappcc4ntmBAarm%2BbASWkLiQaK5rrS8FbgBpI%2BpSbHAOKAkMcJ2CwWhpZAVOIGzpcAC0lxmDBcEciaPJHihNaSXW8Z4EmsnyZprYdl2ry9v%2B/5DgpzF2b%2Bs7NhGS7ad%2B%2BF/tunFeYelb8ppNn1kFjZySllzhZ2rZRX2A7XFww6aQlqn2TO0KhR%2Bi68ul656f%2BREkQI6C5Uhx6Ff557ileN5yuBmBPsq5Vfuuv76YBLVJdCc0LVBcqqsh/KjSheUFeceyOrQJA%2BgwdI7H8RXQg9EoTehT2UVhlmXGCTAKAon3fb9/0GL9REkPmADuIbMQ6l3ENdommn5lqTY9L2gW9mFsEDP1/Xtb5fcDuMygA6o0mAIMsSiMQpy20jDqDg2tQhgwz4qk62FOri8ln5aGPmnWiPxC0cqLnWmlo7bGGS3SLnzC/LstmmdVyGax%2BrvAKaM2pjF5MUpnosb6Jllkdp1vVrj069jIMeIITDBNEFFW/KirPtT7r61qqtGzS4q2w0DvEOKCo7UT%2B3viAlxJF4ER4sg2qcoSrawd7xm%2B9CIeQWHImHYa/NK0V/LQgp5vI69FvPWX6POzKSIEzj1vZ9g9eA3jzcA68ABqLx2KQCkbBslzYKoSmsl6hBCq8VD5iwlxMFHrIANaYOglz4j31S1%2BNVc2hXGMEVjbct03x%2BN7e9PgyqRd68pXqp36pnQt3v3VAGl2XzzOehojkZPdNqBlS/lmZqk4kqaSXApJGUl0Z7z3jXOuHcz6zWIMAHwbtypZgHpcYmpZwaNCSJcTArIECXFQFQSEAA2DQF8w5UMuMEIglDqGw3hlQyBkYsGGFXsEQky8mGkkTkSFOOIjIPxMFQmUGlOpZgjLTC6DM1oCLxEnYk98TJvyuqIBgGjL5Ih5ppLM1k0aAQcu1DBHDB4Ynokw%2BC4iNCXHBqWVAEQA4hG4a8Qw9CGBTEEHgc8q87H0zhlouxW9pEyOsp5AxFjsGlgpLQKM1ibKXDYKUaITCL52IcYQEhdFSyNFQVnMJMjIxGKrvIyGW0UFoOVJ/H%2BqVTZKygQFNw/9bynGqVnJaOkTHqX6olUxYFOluzqaJfOosFY/D%2BGiHcQYh6qFYCKUsGs5aTO%2BH8FEwJQTgiyhKLwSyQwTJ2JcVCMt7oVzacg4A7tThyNOf1NR6c3Bwmsvs%2Bg4oGF4QYVsL5ggdi/IILscOAJYKbSGdc/RpxIn3F5kc9EQh9l5BXgAJReF4WgXoVm3J6QipISL0CooUOir0/VvlbFhas45hLiVnIBHI6lGK1qoXFG5ESB0lYzIxC8TF9I1QNEcMgZMONogEAgC8kACgsJCtfG4BlXEiKItSCitFGKkTDnZXCtZvw4UDV4vMxZ9BaWUq1dqgW51n52CNahWBO9Ua2srtA7WB9ZRH0Qa6wmSDa5f2Yha1%2BGrjU3B8CwLEJzhnKitaXR1dqo0YWdZ6hBHq258tvhU5MGgKXWvtZGlp71D5evbom/Np8k0exTRfZMXAM3ZpRg6nN8D8ZuqLY2qGnsvTltZWNTNMbq2vXrQWhu7qB35uTQbctQIM0zIALKYAaFQLwDAHDSyxT2mBWa%2B3FqbYWjp1yQxyOnbO%2Bdi6BCKJEWrdibhfW0B0WmvC5b2iprMLe9%2ByZx1sojiAMFrL32ZKqRCpN/rlbHOuEGkN26akvgjTa7t67m3etbdgxoaaq1QbrXGwdrdh2loNuzCtE7zpcpGFaqYArpVKCaGKgg6BYKSrYNK69rK3A4Y0HhHDla3x4X3UwOdC7ahs0Q8xhDxBcNvvVZ2wWJq7o6qsc6Vew8DXLN5caiTkmzVXAdCQWGN1l0oZrSup1jAProZPrB/tGGW1lo0yQbRAHOXcteFirBABxNwbgvqoGFHQbmqJB5uAMOuLhlxJ1CE7q5qg9taBhOI%2BSUjIqKNUYlVKn64oFLqeIJp8UnHuNHus9gPumlUvpY4s%2Br9KI3yiZQlg3zhhaQBaCyFtzHn6BhKcy5y4YW6B/T5VLQVwryMMALIpeLNGUxJeLvlyzxBrNuEy4e3j7GUsTam%2B2w5ZWM0cEWLQTgABWXgfgOBaFIKgTgbhrDWGzMsVYf5gQ8FIAQTQ63FiLxAFtyQMoNAAA4zBmHiPELgW2PvvYqLEaQm2OCSF4CwCQGhmN7YO0djgvAFAgGY3d/b63SBwFgDARAIBlgEGjlxCgEA0CNeiKELCnBVDvYoU5ChkhLjAGQPHKQMozC8BXoQK6VH2j8EECIMQ7ApAyEEIoFQ6g0ekF0O0cGxAmBJE4DwDb23dv3cO5wai14CekPIVTmndOGdM8uCzswPYPCk%2BIJCa78xeCo60IsCASASdknoGQInTvPMxGAFIR9NAMUMUoBEVXERgiNCxAr3gwfmDECxNRCI2gSKo5uyTyC1EGC0DDxLrAEQvDAFabQWgSPuC8CwCwar4hM9dkXevQvB3MCqBItedYN2GHVFV3iCIsvo8eCwKrpSeBIdF9IOvYgEQlW3FL0YPERh7uLCoAYa5ndnjg2onacPwvhAUkF9IXn8glBqFV1L/Q1WUCncsPoPAEQkeQEWKgJItRC9OThP%2BUwlhrBmDh8PuGWAr8QEWHYBPGQLgZE4wbQpAgQDsswgw7QeQ6QAgIBuQqQsBDAMwAw5QHQABAg3QYwngrQeg/%2B2WWBvQEBqBeBowzQOBEwtgZBKBaS5Qf%2BF2awEgSuHAO2pAsOvA8OlwuutO9OjOzOr2JuEAuAnOFu5gQIDUNuM%2Biw9ETAWAMQv%2BpAT2kgQIMo8QQIwOGgkgZgkgVCGgW2FCiQoO4OpAkO4hMoFCXAFC728QgOFCL2f2ahFCbBqu8OiOyOt2M%2BGO2ODuuOmu145AlA7uLu5ObAnAjQLA%2BIsQTk883064XA8QMoXAb27O%2BARAX%2BegO%2B/O4gQuO%2Bou%2B%2BEuugj6Mucu4ezBrB7BauHAGu%2BO142uXB1OPB9ccRCRSR9iEAZuzu6SYhZg1uHhaO9uju7mnRrugRQxHuKAfmXuv2zGvugoLoAeQeIe0ea%2Bkeoese8eDga%2Byez4qe6equWeOeeeBea%2BJeZe6wB2%2BArYVeLwqudeDegoa%2BLeoOB27eneWI3e5xNucMA%2BN2w%2Bo%2BSg4%2BZe34nhc%2BxYCgi%2BmAy%2Bq%2Bg%2BmRm%2BEg2%2BsgeR4uB2hRR%2B0%2BL%2BVgZ%2B7eP%2BN%2Bd%2BGQD%2BT%2B/YGJb%2BH%2B0QX%2BNx1%2B6B2WQB7gFBoB4BxQJB0BiBtQ8BzJ%2BQGQNBcwkw1QGBdQZBbJVJtQhBXJUBVBPQgpUwTQopdBSwKwjBDU%2BgyuzhEunB3B%2BusRtI8RiRb2PYwhaRlu4hvRtuD2pAMhchlAzBxhphCRmhsQW28QsQsQQIWhOhkg7QFRrhtg7hJp9u3hSAeOBOARxOYxwRFOHA4R%2BuLACg%2BI8c%2BI2pVoIwKRIheA3O6%2BWRW%2B6%2BSJB%2BIAQIpAxR8uReZRKuqp6ufhXoZCXBUZMZcZCZ54hG7RoZXRwIQIxpnhPhQRjsbuTZMQsZeKyY8Z8QyYiZBAyYqgdOfAdAcxSOEAgeEuqxyxg%2BC5MeceCeWx7mKeaeGeFxmA2eueYgxxg%2Bpxk%2BnxpAlxAB1etx9eyAjejxggreEurxoeHxve3xa%2BfxY%2BQoQJ0%2B/RfA8%2B4JS%2BK%2BjAa%2BsJAu8JWZe%2ByJOguZaJxgp%2BNg2J8AuJ9%2BnAGwLyxJlg7%2BHBn%2BqZFJCh%2BBtQNJgpDJ/QtBCBHJcBdJ5FSBMpeBvJBBApVFPJnQmB1BxBZFkwjF2QoBUpRBjJHF9B8pguxZKpcOnAVZ9O0ZsZa8dZgoDZ%2BpJAhpEhfRdu0hRCFpChRhEOIA32MoQIQIW2/27p0O%2BlsQVholHBnAbhKOUhihIAkgW2qhQO0O72kgv2XAn2ZgThoOQIJZYlCOKlppoObOFllRkh/Riww%2BaQzgkgQAA)$Done$

## Links

- [source code](../../../../conceptrodon/descend/omennivore/among.hpp)
- [unit test](../../../../tests/unit/metafunctions/omennivore/typical_among.type.test.hpp)
