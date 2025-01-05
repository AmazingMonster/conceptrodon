<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::ClassicModifyTypes`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-classic-modify-types">To Index</a></p>

## Description

`Omennivore::ClassicModifyTypes` accepts a list of `std::index_sequence`, which indicates distances between adjacent indices.
Its first layer accepts an operation and returns a function.
When invoked, the function transforms the arguments from its argument list according to the `std::index_sequence`s using the operation.
The result will be stored inside `Capsule`.

<pre><code>   std::make_index_sequence&lt;I<sub>0</sub>&gt;,
   std::make_index_sequence&lt;I<sub>1</sub>&gt;,
                    &vellip;
   std::make_index_sequence&lt;I<sub>n</sub>&gt;
-> Oper
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>m</sub>
-> Capsule
   <
             Arg<sub>0</sub>,
             Arg<sub>1</sub>,
              &vellip;
       Arg<sub>I<sub>0</sub>-1</sub>, Oper&lt;Arg<sub>I<sub>0</sub></sub>&gt;::type, Arg<sub>I<sub>0</sub>+1</sub>,
       Arg<sub>I<sub>1</sub>-1</sub>, Oper&lt;Arg<sub>I<sub>1</sub></sub>&gt;::type, Arg<sub>I<sub>1</sub>+1</sub>,
              &vellip;
       Arg<sub>I<sub>n</sub>-1</sub>, Oper&lt;Arg<sub>I<sub>n</sub></sub>&gt;::type, Arg<sub>I<sub>n</sub>+1</sub>,
              &vellip;
             Arg<sub>m</sub>
   ></code></pre>

## Type Signature

```Haskell
ClassicModifyTypes
 :: typename...
 -> template<typename...> class...
 -> template<typename...>
```

## Structure

```C++
template<typename...>
struct ClassicModifyTypes
{
    template<template<typename...> class>
    alias Road
    {
        template<typename...>
        alias Mold = RESULT;
    };
};
```

## Examples

We will apply `UnaryMinus` to elements of indices `1, 3, 5` from `Vay<0>, Vay<1>, Vay<2>, Vay<3>, Vay<4>, Vay<5>`.
To do so, we will calculate the distance from one index to its immediate next.

We will keep the first index, `1`, since it represents how many elements we must pass to reach the first target position. We subtract an additional one from the rest since we only need the number of elements separating two targets.

<pre><code>   1, 3, 5
-> std::make_index_sequence&lt;1&gt;,
   std::make_index_sequence&lt;3-1-1&gt;,
   std::make_index_container&lt;5-3-1&gt;</code></pre>

We will pass these sequences to `ClassicModifyTypes`.

```C++
/**** Vay ****/
template<auto I>
struct Vay
{ static constexpr auto value {I}; };

/**** UnaryMinus ****/
template<typename Val>
struct UnaryMinus
{
    using type = Vay<-Val::value>;
};

/**** Capsule ****/
template<typename...>
struct Capsule;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = ClassicModifyTypes
<
    std::make_index_sequence<1>,
    std::make_index_sequence<3-1-1>,
    std::make_index_sequence<5-3-1>
>
::Road<UnaryMinus>
::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult = Capsule<Vay<0>, Vay<-1>, Vay<2>, Vay<-3>, Vay<4>, Vay<-5>>;

/**** Result ****/
using Result = Metafunction<Vay<0>, Vay<1>, Vay<2>, Vay<3>, Vay<4>, Vay<5>>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will perform recursion over the total number of the `std::index_sequence`s.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  - Handle several `std::index_sequence`s from the front of the list;
  - Invoke itself to deal with the rest;
  - Concatenate two resolved parts.

We will use the following helper class template to concatenate two parts.

```C++
template<typename...>
struct ExtendFront {};

template<template<typename...> class Container, typename...Elements>
struct ExtendFront<Container<Elements...>>
{
    template<typename...NewElements>
    using Mold = Container<NewElements..., Elements...>;
};
```

The index pack within each `std::index_sequence` will be wrapped into `Prefix` to produce concept packs.
Then, we expand the concept packs alongside the arguments to reach the items at the intended positions.

```C++
template<typename, auto>
concept Prefix = true;
```

`Capsule` is used to store the result. We declare `Capsule` as follows.

```C++
template<typename...>
struct Capsule;
```

Here is a simplified version of the implementation.

Note that we wrap the elements inside `std::type_identity`.
This ensures we can create objects to invoke the ordinary function.

```C++
template<typename...>
struct ClassicModifyTypes {};

/**** Base Case ****/
template<auto...I>
struct ClassicModifyTypes<std::index_sequence<I...>>
{
    template<template<typename...> class Operation>
    struct ProtoRoad
    {
        template
        <
            typename Target,
            typename...BackArgs
        >
        static consteval auto idyl
        (
            // Expand `Prefix<I>...` to count arguments before the target.
            Prefix<I> auto...front_args,
            // Transform the next argument.
            Target,
            // Collect the rest.
            BackArgs...
        )
        -> Capsule
        <
            typename decltype(front_args)::type...,
            typename Operation<typename Target::type>::type,
            typename BackArgs::type...
        >;

        template<typename...Agreements>
        using Mold = decltype(idyl(std::type_identity<Agreements>{}...));
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

template<auto...I, auto...J>
struct ClassicModifyTypes<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template<template<typename...> class Operation>
    struct ProtoRoad
    {
        template
        <
            typename FirstTarget,
            typename SecondTarget,
            typename...BackArgs
        >
        static consteval auto idyl
        (
            // Expand `Prefix<I>...` to count arguments before the first target.
            Prefix<I> auto...front_args,
            // Transform the next argument.
            FirstTarget,
            // Expand `Prefix<J>...` to go across the distance between two targets.
            Prefix<J> auto...middle_args,
            // Transform the next argument.
            SecondTarget,
            // Collect the rest.
            BackArgs...
        )
        -> Capsule
        <
            typename decltype(front_args)::type...,
            typename Operation<typename FirstTarget::type>::type,
            typename decltype(middle_args)::type...,
            typename Operation<typename SecondTarget::type>::type,
            typename BackArgs::type...
        >;

        template<typename...Agreements>
        using Mold = decltype(idyl<Agreements...>());
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

/**** Recursive Case ****/
template<auto...I, auto...J, typename...OtherSequences>
struct ClassicModifyTypes<std::index_sequence<I...>, std::index_sequence<J...>, OtherSequences...>
{
    template<template<typename...> class Operation>
    struct ProtoRoad
    {
        template
        <
            typename FirstTarget,
            typename SecondTarget,
            typename...BackArgs
        >
        static consteval auto idyl
        (
            // Expand `Prefix<I>...` to count arguments before the first target.
            Prefix<I> auto...front_args,
            // Transform the next argument.
            FirstTarget,
            // Expand `Prefix<J>...` to go across the distance between two targets.
            Prefix<J> auto...middle_args,
            // Transform the next argument.
            SecondTarget,
            // Collect the rest.
            BackArgs...
        )
        -> ExtendFront
        <
            decltype
            (
                ClassicModifyTypes<OtherSequences...>
                ::template Road<Operation>
                ::idyl(BackArgs{}...)
            )
        >
        ::template Mold
        <
            typename decltype(front_args)::type...,
            typename Operation<typename FirstTarget::type>::type,
            typename decltype(middle_args)::type...,
            typename Operation<typename SecondTarget::type>::type
        >;

        template<typename...Agreements>
        using Mold = decltype(idyl(std::type_identity<Agreements>{}...));
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCBmGgDMpAAOqAqETgwe3r56KWmOAkEh4SxRMXGJdpgOGUIETMQEWT5%2BXLaY9gUMdQ0ERWGR0bEJtvWNzTltCmN9wQOlQxUAlLaoXsTI7BwA9ABU%2BweHR8e72yYaAIJ7BwDUACKYSa6MyHiYCjeHZ5fXJ39H3wu5yBZniwWQ3iwNxM8TcXkctEIAE8YdhgcDfrsbthVARXAAxYiyT4HQF4lhJAx4mFuAhIp7MNgAOhZqOB02IXgc2NxBKJgmhAHYrIK7jCrJdgeTKUxqbDpVTMDS6QzWJgWUzUTcIUwFB8PIImHMyDcVYw1RrsPQ2IIFGzLhyuQQeXiGOhCbIaQb6saaVbMDaCAoNWz4mjJcLgTdo6aAzK5bT6ebmSzQpgAO7%2BwN2sNRmNeNJGG4AWU86Gh8TuN29RpCxBpacz1sYQY1pGxzdtIdz8QlQNF4vRP0ON2UxEwNFUJP2ZLjiuVScZmHbTHhqHtFzQDE2SWdY4neCnMKrBE5St7Q6uI7cTCSCi89Gnpylc9l58TqpTmtzDtPTurt73vQg6SsO/zgV8GIjgAkhSnb1F0T6ApiEH/ICL5wW%2BC6fuqrI/hcjrcm4Bh6ngyClvgVBIgAKkmHwmJGA4XqBV63BYuqYABShIRh8bvquRAatBG6Ec6xG6mk5EYHgVG0U8OZuNM6AgCAwRYKoAD6SgAI5eC877Qd2aL4QxfYxrGmEJgqWHyouFp4dg2okR8ADyTzELKGQbuZomjkSRAAEqoEw6B5tGplheZFl8ZF5k0rFUXRmaS43NRDTAJgBCkAliXJfZTLscgADWFzEMAdqXIl4X4VVNzTJ5yDagI0yYAAbmINwCagNx4OgSK0DlNwQIN5nbNsPJJIY5YmAAbBo%2B6TjSwlhiGc2mt1aBeAK6U%2BC2HxRPw46mggnFjBlBCapVtUxgth5LVqXUalQ/IEBp6UKNlV3XTcY2pR5DAKIdLDHZxIS4p1ZW7YIl0XN90ZpWVmWfbDcO/VknQgzc47TDDcM3IVJVlcGrJfVFSyDQAtFqN53g%2BSqk3FsIjTGeVsDcWAQma1AvW9RNLCpZptszSV2WzbnRJ5AjYcmnEI%2BdAtJqiCtPMjeOs5xBOleVyu4bjVWhn2g3WVZou6xcwDjgGe3eVVBbBMAJZlhWVYc7QXO9f1EBKTrGm9S2yI0ublvZmyjF3BqSzk8xKPhUxhuk8b76J9LS5GU5EkakHmBW7aNvRnbRZBSFzt%2BaggXBaFsJZznrYOSB/ZitHvHzrCj0stBK5rhqABSIl/kRzlkRRMk0XRNLe6pbqYJpOl6duBlGe2E9qdPWmYLp%2Bk0t3RkbhFCevlZB9J6bac6nqNzix5XR53V/d7v5qBF6FpN7zHUXJwzMbxZ/uWmzc%2BJ4GINMOWSNhamj/kIaoAh0AgKymA9WGpNZE0GjfHyCEyJNQBnidqtBOprh6n1AaP8hpgN%2BjiSabpoRzVuqoe6K1WRrSIE1LazodrZhuAdEgp0To3BoEA50Z1Mp62%2BjQuhjk25MmerIXm5VVao3GtRf6gMSDAwIDwsGrDIaBmEddAB/DYFyO%2BmQ1QFDprUPHItWEvd6GakYd1YA3UmDICJOfNRnF8D1XnhwzK6Zs4MFNOmbqgjWxgNEVYh6XcWQsF6ugegMiPqkIUUooGmMNEQ2AFDC6YDIFbhgelUBxDRrjXRtUARPDsZZMKTGJB5UQzEPJsQqmYYAK02AsQ7%2Bb9arq3ZtUN2SZubSPevzEAgsWSGOut0y%2BksGApzVP/QBwD8kEB1krEZSZxldL/q7Lm0T0CxMwPE4ZoymQbKqpM9y0zZlsxydA2BKyww61Ob/HC%2BMnGE21msp4dTOlfx7PHH5SUj5XLNhbbOIcaq20LA7UstBpqVh6ZzfpHsBpV1BTXYm35sAQEjvXOKcdLzmWTvKIFtkcKn2cpnNF4LwxvwLg7J%2BJcxxl0fhXQOVK9o7ybvilimIbgBWqOsNIrVOI3m4pBS4RKbyRKZB3PBgkWTd3bAglkLk3HEEgRveeOYaW%2BXEqRKSlFR7yXHgQZSk91Jr01ZsJai9b5mpXjPdec9rVWNtaqk66qnX6QxbvSM%2B9LJJxJR%2BGW5KJIXwudfCF0ZfJMvLiFSKr8ulAvaUzKpIsXl6MWYjOBabwEvJuW6Ax8CT4shqRVAFFYaW1Xqo4RqW4Wo4Lld1ZFg1hq5uMaYqh80LF3VhMtbAq0NDrWYdtLRe1vGHW4ZxPh0xTRLJ0bVMJbh%2B1Nqejzd6Tyoq/UUYYZRxBVHqOnpojJ2iwGZoIEW9t41yFTS7Uu6xA6GFDqYQ4zqzjUgfDcezPAnjNjeIIL4xgASglLODKEnttDwnNIkbs/Z8TN1FL%2BrulJX60lsJbAuqqBa8nZoQzGNGngMZfoqZhxKZbvm1QaRWppjkcSundC9FBqaK3mW2YrXNbaWNVT1ZJYeskx6wnddEDVzr3g71zeZAWR8%2BWssExGryUa8Y3BUsiiAZaIqigjmAqjtVUExikwGx2sKmNuGLS8tjTwBmCEOTrIWubzkS0jcGlK567mfPPNgR5ZmZYIr6ZZ2DcShm2bGd5lKUynPdOw25s0qyYspuMv8pNAbgWUuDtbRT5k6VGbhS7Xp7tCFe1NT7P2ggA6orS7nXMYcI5RzMl/blQJ/UxWJcl0lIaHLpz1KlsF6Wq35ihTJ4ux5S5xsrm4au2ZOWGwa1BVC4rWL7B5KwSknF5soVQuhSUoJwSQk4jSLcO4gy7zAotgAakwJEPEJVBq6jcft7I743HOyiCMFhb4NUwS1ExxAm03BwXpIUFhhJxyFI3f5vK5DMGIEiYswQCxXYuJK7p52UU6se5DhoMO4flsTf1%2B2ea9vwuezSCmKOVL/Y8/XBiYPLy8ppkBVbpJm42Wc/lPunIiKATplTk7WJiyZSYFQLaNQBAI6RyWpkWttXAiy/z%2BoQvtyIWGzxoe0l%2BPGslMxtBZqWBMCKgch1lrRM0i4KicZE9df699lPR1Vr3zxAplwR3ZvIoW71wbm3RvN6wgAKwUwd6bky%2BEVJPxpBj6HsOGAFg3CpGFY2pdTdpyOIQXgkh5EwOgflQFnTzayyntPqQM9Z4fM6ZXXPgKwmJ7CDQZunsXZJ4H7A7Yq9uDMLXlv/v2/19hJILvKJYQUx96GBLSfbjF7dgjrL4/S/wrl4L4XTmW817DM37vbhG%2Br/763vvNJ4g757/vtwQ%2Bewj55SOai7wc9M9/A1N6epogEEK2ahQao780mn%2B2fP6fM/vBL6iWrwIHAKwtAnAPuvAfgHAWgpAqAnApmlg1gdUawGwe2oIPApAyykBQBKwRUIAPukgTIGgAAHGYGYAAJykFcA%2B5EGEFcCCiCjSAgEcCSC8AsASAaAaCkAQFQEwEcC8AKAgAcEYFaArBwCwAwCIAgBrAEBJDwjkCUBoAUh0DRChBqicCqCEEzQUwzSSA3DADICNRSBMhmC8AZ6EAkC9R6D8CCAiBiDsBSAyCCCKAqDqCYGkC6BtDpgeRJCcA8DAGgHgGaC8A8EuTwgyHOioBUA3DqGaHaG6H6E3CGFmBDQeCKH0A/bmDxBcBLC8BCFAGkAQBIAKFJBKFkAUAQBFElEgDABSBmB8B0B4hAKUARCBGkARDBCY4%2BG8BtFQ5IguQRDaClKdGkAKGBguQMC0BIgtFYARBeDAA3i0C0D8HcC8BYC65GDiCuH4Djg1DCpLFQHTwCp4hDHBB4iMFQGIgRAeTQ4eBYAtGnh4CsHLGkDCrEARCF4PBrHACIhGCBErBUAGDlSnZvDpjiwQFoFWHCCiDiD2EQlOFqAtHuH6CGDGDWDWD6B4ARD8GQArCoC7gZBLEUxKTHimDwGWBxBBEvHEB%2BxYnYrtCdAZAuBugTCtCkCBBzAlBlC5CpDpACDMlcn5AZD9AclDBTAdClK1AzB8min0kCA9CNBCmDAxBTCSmeAtB6D1TynsmKkSArAKBIGbA6n6D%2BGcEtE8FREaFaE6F6EGH4FJEQC4BmHpGoHZHoG/ErAnQhRDC0k4GSDxBMikHxD0EaCSBmCSBzQaA%2B4zSkFGlMEsEgCZFMgzRcAzSEGkE0EzR4GUEBkzQmmuE8F8ECGumYEiHiEFGSGhGyFlEVFpEqFsCcANAsCtSCgUxMDpxFhcCkFMhcAEEmH4BEBUnKRtAQk2HQnSCwlKDwmuG6C1GeG3idF%2BEcBgG5ncGcAhHSHwg3ARHmkxE6E6jtmdndlDoQApHFFpHQighmAum5EiGFGoCpHRByHlF3mnlDB7nVEUEcE0BuzRD8EQDNGuHdEdFPGAXQ59EDEOBDEjEthjETFTGYAzFzFiCLFDGrHIkbFQFbHim7EtEHHIDwhbBoEnEdAtEXFXFIg3FbBQH3GPFoEvFvFKAfFoX2y/F8AAkKBAkZiglDHDlQl2FjmyBwkuFQHTlIk/EklWCWDomYnwA4l4nNScCEmmrEmolkncGUnUkyV0ninOAQCuBSmslugKkLBKnJDcldD6V5A8kMBGWcnSnaXdAqnZAslVAi4OW9A2UimjC9D6UamzDFDalZGrDrAGmBWMFLlcFBGcDbmWltkOwdldkEFDQOn9nnmZFXlumkAelYAxC0mMHMGkCsHxCdnBmCg%2B6kF0HxAhlhmSBtARXQGcAFmCEsWiESFSFhGPnVnKGqEcANmxEsAKCtSNStTxWKjTC9mOkWFDmyAjl8UOHyATlCU6DxmkCzneHLELnhWmmrkVnhGRGqB9UDVDUjVvizrHnPklGpXxDpXFn5G3n3mlHyHnVpEgCDVp4aTDWkEaSjWvT7Vjn1E/lNEtEgWTHAXtGgX9GDFPFQWCAwUg0YXwWzHzHIVPGoXrGUUrGAJYXvA4WqCHEEW8BEVnG8CkWY4UV3FUk0W8B0XvEBhMU/E3X/FMCAnAlcVPE8W2ESD8WOELUInLUGBiUqU2AXE0myVdBLHbDeziXWDknQHqVYAi1aWuWMnuCqmTAGXoAeUmWWXmWq0sna2ClanGXqlimuVylNC63G0yluWan%2BVG3KneUW32023zC2W6n6l2EbUBF5lRW/U3D9WDV/bHV4inXJUkCpVZE5EZVZVekLn5WsFkFMjxDxA%2B5UE1XsFJ2CgpnLmRW8G2CFnXnYEgCSA%2B7%2Bm0GCjsGEGSAUFcDEFmA5mMHxBe0rm50F0xnGHZ31Ut0ZUvFpDOCSBAA%3D)

## Links

- [Example](../../../code/facilities/metafunctions/omennivore/classic_modify_types/implementation.hpp)
- [Source code](../../../../conceptrodon/omennivore/classic_modify_types.hpp)
- [Unit test](../../../../tests/unit/metafunctions/omennivore/classic_modify_types.test.hpp)
