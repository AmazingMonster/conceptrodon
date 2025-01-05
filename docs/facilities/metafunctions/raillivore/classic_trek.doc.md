<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Raillivore::ClassicTrek`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#raillivore-classic-trek">To Index</a></p>

## Description

`Raillivore::ClassicTrek` accepts an operation.
Its first layer accepts another operation for composition.
Then, it returns two commitment functions and twelve continuation functions.

- **Commitment**
  - **Conjuration:** When invoked, this function instantiates the first operation with the arguments. Then, it invokes the second operation using `Omennivore::Send` with the type result of the instantiated first operation as the packed vessel.
  - **Transition:** When invoked by a vessel, this function transports the conjuration function to the vessel.

- **Continuation**

  When invoked by another operation, the function returns a `ClassicTrek`
  - that is instantiated by the conjuration function and
  - whose first layer is instantiated by the new operation.

In general, this function composes operations together in a similar fashion to `.` in Haskell.

<pre><code>   Oper<sub>0</sub>
-> Oper<sub>1</sub>
       &vellip;
-> Oper<sub>n-1</sub>
-> Oper<sub>n</sub>
-> Args...
-> Oper<sub>n</sub>&lt;
   (unpack)Oper<sub>n-1</sub>&lt;
       &vellip;
   (unpack)Oper<sub>1</sub>&lt;
   (unpack)Oper<sub>0</sub>&lt;
       Args...
   >::type
   >::type
       &vellip;
   >::type
   ></code></pre>

## Type Signature

```Haskell
-- Compose with Mold
ClassicTrek
 :: template<template<auto...> class...> class...
 -> template<typename...> class...
 -> ...
 -> Commitment

-- Compose with Page
ClassicTrek
 :: template<template<auto...> class...> class...
 -> template<auto...> class...
 -> ...
 -> Commitment

-- Compose with Road
ClassicTrek
 :: template<template<auto...> class...> class...
 -> template<template<typename...> class...> class...
 -> ...
 -> Commitment

-- Compose with Rail
ClassicTrek
 :: template<template<auto...> class...> class...
 -> template<template<auto...> class...> class...
 -> ...
 -> Commitment

-- Compose with Flow
ClassicTrek
 :: template<template<auto...> class...> class...
 -> template<template<template<typename...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Sail
ClassicTrek
 :: template<template<auto...> class...> class...
 -> template<template<template<auto...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Snow
ClassicTrek
 :: template<template<auto...> class...> class...
 -> template<template<template<template<typename...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Hail
ClassicTrek
 :: template<template<auto...> class...> class...
 -> template<template<template<template<auto...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Cool
ClassicTrek
 :: template<template<auto...> class...> class...
 -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Calm
ClassicTrek
 :: template<template<auto...> class...> class...
 -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Grit
ClassicTrek
 :: template<template<auto...> class...> class...
 -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Will
ClassicTrek
 :: template<template<auto...> class...> class...
 -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment
```

```Haskell
-- End in Conjuration
ClassicTrek'
 :: Commitment
 -> template<template<auto...> class...>

-- End in Transition
ClassicTrek'
 :: Commitment
 -> template<template<template<template<auto...> class...> class...> class...>
```

## Structure

```C++
template<template<template<auto...> class...> class>
struct ClassicTrek
{
    struct Commit
    {
        template<template<auto...> class...>
        alias Rail = CONJURATION;

        template<template<template<template<auto...> class...> class...> class>
        alias Hail = TRANSITION;
    };

    template<template<typename...> class>
    alias Road = RECURSION;

    template<template<auto...> class>
    alias Rail = RECURSION;

    template<template<template<typename...> class...> class>
    alias Flow = RECURSION;

    template<template<template<auto...> class...> class>
    alias Sail = RECURSION;

    template<template<template<template<typename...> class...> class...> class>
    alias Snow = RECURSION;

    template<template<template<template<auto...> class...> class...> class>
    alias Hail = RECURSION;

    template<template<template<template<template<typename...> class...> class...> class...> class>
    alias Cool = RECURSION;

    template<template<template<template<template<auto...> class...> class...> class...> class>
    alias Calm = RECURSION;

    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class>
    alias Grit = RECURSION;

    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class>
    alias Will = RECURSION;

    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class>
    alias Glow = RECURSION;

    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class>
    alias Dawn = RECURSION;
};
```

## Examples

We will see two examples that demonstrate conjuration and transition.

- In the first example, we will compose `oper_0<2>::Rail`, `oper_1<10>::Mold`, and `oper_2<'*'>::Rail`.

```C++
/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** Shuttle_1 ****/
template<auto...>
struct Shuttle_1;

/**** Capsule ****/
template<typename...>
struct Capsule;

/**** Carrier ****/
template<template<auto...> class...>
struct Carrier;

/**** Oper_0 ****/
template<auto Variable>
struct Oper_0
{ 
    template<template<auto...> class...Sequences>
    struct ProtoRail
    {
        using type = Capsule<Sequences<Variable>...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

/**** Oper_1 ****/
template<auto Multiplier>
struct Oper_1
{
    template<typename...>
    struct Detail {};

    template<template<auto...> class Sequence, auto...I>
    struct Detail<Sequence<I...>>
    {
       template<auto...J>
       using Page = Sequence<Multiplier*I..., J...>;
    };

    template<typename...Agreements>
    struct ProtoMold
    {
        using type = Carrier<Detail<Agreements>::template Page...>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

/**** Oper_2 ****/
template<auto Variable>
struct Oper_2
{
    template<template<auto...> class...Sequences>
    struct Detail
    {
        using type = Capsule<Sequences<Variable>...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = Detail<Agreements...>::type;
};

/**** SupposedResult ****/
using SupposedResult = Capsule<Shuttle<10*2, '*'>, Shuttle_1<10*2, '*'>>;

/**** Metafunction ****/
using Metafunction = ClassicTrek<Oper_0<2>::Rail>
::Road<Oper_1<10>::Mold>
::Sail<Oper_2<'*'>::Rail>
::Commit;

/**** Result ****/
using Result = Metafunction::Rail<Shuttle, Shuttle_1>;

/**** Tests ****/
static_assert(std::same_as<Result, SupposedResult>);

// The following `static_assert` shows how the operations are composed:
static_assert(std::same_as<
    Send
    <
        Send<Oper_0<2>::Rail<Shuttle, Shuttle_1>::type>
        ::Road<Oper_1<10>::Mold>
        ::type
    >
    ::Sail<Oper_2<'*'>::Rail>
    ,
    SupposedResult
>);
```

- In the second example, we will transport the conjuration function to `InvokeRail`.

```C++
/**** InvokeRail ****/
template<template<template<auto...> class...> class RailArg>
struct InvokeRailDetail
{
    using type = RailArg<Shuttle, Shuttle_1>;
};

template<template<template<auto...> class...> class...Args>
using InvokeRail = InvokeRailDetail<Args...>::type;

/**** Result ****/
using Result_1 = Metafunction::Hail<InvokeRail>;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult>);
```

## Implementation

We will compose functions using `Omennivore::Send`.
For example, we can compose a `Rail` and a `Road` in the following way:

```C++
template<template<auto...> class...Args>
using Metafunction = Send<Rail<Args...>>::template Flow<Road>;
```

Note that in order to succeed, `Rail<Args...>` must be a packed `Road`, meaning it is of the form `Vessel<Items...>` where `Items...` all have signature `template<typename...>`. This requirement is not checked by `ClassicTrek`.

We will implement `ClassicTrek` by performing recursion manually, meaning the function will recurse only once for every invocation of a member template.
We will showcase a simplified version that handles `Mold` and `Rail`.

We will use a simplified version of `Send` to compose operations.

```C++
template<typename PackedVessel>
struct Send {};

template<template<typename...> class Container, typename...Elements>
struct Send<Container<Elements...>>
{
    template<template<typename...> class Operation>
    struct Detail
    // Invoke `Operation` with the `Elements...`.
    { using type = Operation<Elements...>; };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};

template<template<template<auto...> class...> class Stockroom, template<auto...> class...Sequences>
struct Send<Stockroom<Sequences...>>
{
    template<template<template<auto...> class...> class Operation>
    struct Detail
    // Invoke `Operation` with the `Sequences...`.
    { using type = Operation<Sequences...>; };

    template<template<template<auto...> class...> class...Agreements>
    using Sail = Detail<Agreements...>::type;
};
```

Note that in the following code,

- `Radio` is a `Rail` and
- `Car` is a `Mold` or `Rail`.

Here is the entire implementation.

```C++
// `Radio` is a `Rail`.
template<template<template<auto...> class...> class Radio>
struct ClassicTrek
{
    /**** Define Road ****/
    // `Car` is a `Mold`.
    template<template<typename...> class Car>
    struct ProtoRoad
    {
       /**** Commitment ****/
       struct Commit
       {
           /**** Conjuration ****/
           // `Radio` and `Car` are composed here.
           template<template<auto...> class...Signals>
           using Rail = Send<typename Radio<Signals...>::type>
           ::template Road<Car>;

           // Helper function for the member template `Hail`.
           // This function transports the conjuration function `Rail` without invoking it, 
           // allowing further process by other higher-order functions.
           template<template<template<template<auto...> class...> class...> class RailVessel>
           struct Detail
           {
               // We transfer the conjuration function `Rail` to `RailVessel`.
               using type = RailVessel<Rail>;
           };

           /**** Transition ****/
           template<template<template<template<auto...> class...> class...> class...Agreements>
           using Hail = Detail<Agreements...>::type;
       };

       /**** Continuation ****/
       // This function composes the conjuration function `Rail` and the `Agreements...`.
       // Note that even though `Agreements...` is variadic, it only allows a single argument.
       // This is because `Agreements...` will be used to invoke `ClassicTrek<*>::ProtoRoad`,
       // which has only one parameter `Car`.
       template<template<typename...> class...Agreements>
       using Road = ClassicTrek<Commit::template Rail>::template ProtoRoad<Agreements...>;

       // This function composes the conjuration function `Rail` and the `Agreements...`.
       // `Agreements` will be used to invoke `ClassicTrek<*>::ProtoSail.
       template<template<template<auto...> class...> class...Agreements>
       using Sail = ClassicTrek<Commit::template Rail>::template ProtoSail<Agreements...>;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;

    /**** Define Sail ****/
    // This function is the similar the `ProtoRoad` defined above.
    // It handles the case where `Car` is a `Rail`.
    template<template<template<auto...> class...> class Car>
    struct ProtoSail
    {
       /**** Commitment ****/
       struct Commit
       {
           /**** Conjuration ****/
           template<template<auto...> class...Signals>
           using Rail = Send<typename Radio<Signals...>::type>
           ::template Sail<Car>;

           template<template<template<template<auto...> class...> class...> class RailVessel>
           struct Detail
           {
              using type = RailVessel<Rail>;
           };

           /**** Transition ****/
           template<template<template<template<auto...> class...> class...> class...Agreements>
           using Hail = Detail<Agreements...>::type;
       };

       /**** Continuation ****/
       template<template<typename...> class...Agreements>
       using Road = ClassicTrek<Commit::template Rail>::template ProtoRoad<Agreements...>;

       template<template<template<auto...> class...> class...Agreements>
       using Sail = ClassicTrek<Commit::template Rail>::template ProtoSail<Agreements...>;
    };

    template<template<template<auto...> class...> class...Agreements>
    using Sail = ProtoSail<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKz%2BpK4AMngMmAByPgBGmMQgZpIAzKQADqgKhE4MHt6%2BAUEZWY4CYRHRLHEJSal2mA45QgRMxAR5Pn6Btpj2pQzNrQTlUbHxiSm2LW0dBd0K08Pho1XjtQCUtqhexMjsHAD0AFQnp2fnF0cHJhoAgsenANQAIphprozIeJgKj2fXdwel2B5wBtxutwImBYaQMUJMyTcBAAnu9mGxHsomMgANaYdAANR%2BdgR2AhC2IXgcjyErkeJgA7FYGc8EVY7hCoTC4ZgEUjobCmPDESi0axMAA6KWkx7IAwKX4eQRMZZkR6ixjiqUS7D0NiCBSk8kESnU2kMdB8pUtVV83XQxgEBTao3JMkcpkQx7e9UCnl8rmC4VI1Gatgut2y%2BW/ADy72IQpyRruPseFKpBBemBttC9PoOB0eAEkGAA3VB4%2BkANg0cfiiYEJhrjwA7oQEOqEJhqxp7fqnS6axK897GRZHl4skZ1aH6clno86wn%2Bna9Y7ndK3Wz6Sy2RCR77uULeSK/ceA6H0ZLN9go0wFdrbsBiJgHQbk7dU5PwsBHgAlVAmHQOcF1eHM%2BSfF83wHG8QBADU9w9VlknZcE7kDf1TyPYMMPPREmC8IgI1vOV7w3YdI1IhUaSIXFiFQVAWFIQ8gxPNwCKIm87wfKVaQARy8T4fg/dMzVcPlmlQOiGJYCTMAEoTyNdd1wU9FMfVwnCzy07C2I41BiO4pTKOjRd4wbBgP1TUTMzAlVc3U70C2LMsK27Jta3MldmzbAgOz89ya34wSGD2JShwPMcJynX8NRAsz6xXRFgsU4jt0ZZDUIPTS2JygNtL0wiDK4qjjJI6NH2fV9%2B0NLdHOin8aXs%2BK7LoCCqugsq4IQlD913XqOUBEFhtBCEgSOYtuWgiy/lOMFxpGkEwTGwsPL/ICnA8x48F%2BJge3WtqIvQgr8t007WL5fTDNK67TPW/BUBEk0M0eNxozwZAABUXxxPrUNTcasxoCJ/0A4D/gPZyPPY4gtp2x49o8gBZTxLSOz8NJOrCLpFS8tRK0yYasn0bMxeiiAAoDIrUjHU0eQGPBYFhCH7WaTjBOnvVJxnmYIA8fTHfnOYZgRtB2GaIfqzn6dWmt7s25tDGA6HWi21puzQGFMnxR4uxfYcpc5vLscw9iitusjtSEPBgGYWhapU6Wvxi/9moRBdzUtXGxQxeXHuSm27a6%2BDQ2Jp3Hm6grQapxEia3Aa0Npp3nIACV6eNHioLxQv6TOSE7bs2FWYgWJ5HsU/sjyDaT6XnM%2BhB4aznOcnVBMGAUDI2l%2BALZVF8Xc6bxoBH2yufPbbZM3CcscUawhmKFunnLEWhUDbacs7aPXHjSeiwt%2BGJkUeVAApLhvgD1gBaEgsBLwf%2BmdBfU2N/kzpNvCX5xs3OIo8rLYJv%2Bf5GVdnQIkCpehhydqTVqDka6c0FobcOzkADq3YTSGAUFQeIBde4MDFsuFud8W5rVHhodUqAR4gOJOA9G4dObfmnHFd2wDaCgJJIiA6uZ47/VoRlRCidaH0zOI8b66DsjD0lrAumz9pFYw/qbK6/8eKAJuoo8ikFqrrggdLehv4K50BatmSuiJ1GdWIt1UOCdpa8ITgvEWghwheAlnNWxhZ66N2zkPBgvctZKG7l2HBeCZqEOHsQw6pClbYI8iYmqg4NDV1roWSIx9UEICFI8TApZGCdm2OfHs0T1yxO2r8UsrQ8AbWQMxQgR8GC0EPsvVeu00w/noAjYgwAfCOnicLVxDdfjwziKIScgU7gdRidKMetBaCPDiNFHWRBtquUrNDd6X0fp8iOKSOCyhyaoEpmjDQpAXGtgbsgDsqTfgCFqdU7saRWjiihCXFWsMaFG1kdIvG4ZVGVSgjVLR3odHR2VvOV6KzvqYF%2BrHRivNI66WYZs%2BCUdtnH12WDdqPyCk3j4UctxvxgleM1sUH42C0C4P7gQjxudQm5kVhaSJNZ8kGliV0xessRnovfBMqZMyhnAXmVPNyPY3pkQ%2BmCiFbgNlui2TsoQ9lmVPzeQq1%2BX9irKIql8qUDKnR/IatOGV%2BimFCoVCKtZkKmaEBhaxOFkqEWwqRUQPVnC3CarKnw1M1isr1RkUqjUV4LZKOdRAgFez4p2pRTHJ1oyMU/yxfVQGrxgbdgdWzK4kMenuObsPeGPcsjMwMCXHuHlQ17K2lgBNwEmAxFQJkuVzkiyZlSRaegfiNb3m7C2PWwyibNnhojOWJC5Ves/s/BRqqAEylKq9VWdUk6k1DQ66m3DF5CJ5izR0yaOac25lCwgC94GSIBsuvu%2BDxHOIQfK71siR3jrVRKa2tsxAO0fj6INbtgWewvD7bsfsJKBwfWYkO7xtWpgtWXedscp1khsWezGF7YNDsvebdVo6lHXrIsw1h4Dp0CKgYYtq0HRw0wEc%2Bl2jDgUcIw46jhrpF1O3dfufDgingiPbmIrxEiBGDtNpx9%2BV6TJjr4yhgTajI3viw7QgFeiplMOgWijRjLYIAZPDRgW/UPWSLsY4Bgjjc7sdeXBrjHzrzIeE%2ByrVYm6ZBrBvFQ1WRVngqtNuggIHjxWuwM5qEZNkXFuMSJmC0aoOSO4zpT%2BvHf6CbCyZuTZnHZ0Jdkmg1oKTVuBXU5m1lqqPWpyp5%2B1RiI2mZdZYlTmV6NJyC7lBD39UPhaMt8qLj76oAvi8CuduXnVpRsapkrC1FoXHmkIgAYngYgCxHjYFUKwWE3YJHdZ6xI/cZhkjhDlF4LAc43Akr2GkaLXWhFCAQIRAgLSJHDsQ9Gu4pM9sHfoDG%2B4u39sEEO5gAA%2BlwddnIKsqqeqaTMl2Hv0BezdhmTA0gKC8Ed09kI3mGbSud561J2Ig7B0pnbTwYbEG%2BCXY7iqQunaqy62H33J3EHR/EQHQilxPdIVjpV%2BlHgElKRW6707SYU40H9eknrsfyNx0Jq28kQphQgbOnZVH6p7qdgC0jC4Eeg6Z24FKoVhKInp%2BjxnJ5sDtZo3RwapWuc8Z5xF2rnVA0uw4SGkXrXfMFayp1nXgMKevepzj%2BZSMweOFhBjr7L0Hd/WylDz9MOZ1w9srhqTnpbf8Jg/BmnBugEK72MxEdRYhfB6zOBZK/OhJ8iLO1mLBHlPehO9/AAUtqgFWJgDuTfZnxXfJXe0Hd7QDHRwc9SmYsXzX1Nis6/PUO6HGqrcp8J6GlGtBLRi8I9okjs4DWtBJ7DREMmfP5fhVlivRnqNd5u73gzAeB8r/Mzq38o%2BgULhH6jWTpjMUde74ne38YntmDe8dGP8yVdlJiEzlSLOH9mF95z/TfXSrXnXiGvQXQ/HDcCCfAvf5afd4azYHWXNiePJXNwd/NXUkTvCfW/P3QA4MULGrffOrE3RqM3aTUPS/MZH%2BcxQDG/MnJ4IQLwNIQldAP8H4N3Z/W4RrJglgtg2XTMWfRHOXX7R7PkLgDQI4MwZiMADgI4GQ0kZiEQ/7LgMQiQqQx4GQuQjgZSegk4R4JGQxPFTggFAwloIwhLYVOzMVVnPkP/a1DLFSOCbzNwH3REcQ%2BFE/D8OCMDFw3/PkTQ%2BQ%2BwoxRwkAFLXQiaPgjgiRINdghveKUwpgPFJw3LJQzARQ%2B7R7AHLhFHPQz6H4J0TghYRMZAJ7MieIAgCABYdAOCBQcUUo2qNwSIhvRQng7WVg2IvmN0dYQHHpbsfgSZVeRqDyIoxwEosotoLaBQBABpXWVebBVALyHIXaF8bxFgkAY0Yo%2BopQNoSoggaokAWotgeovkA8d9MXRER%2Bd9REGwxEOwtzEADLeXDI%2BgdIq7Z7FQzLCxPPOmJw1Fa4h/D4twdw61Tww/YDRTSKQ/bw3LCnOwtwAI7QoItqQ/Q5eqRg5gtopovmDkLo8I2bXrMaXbBoAQYCMbCbcHdmQk/E4EZaIaJ4EsaeTAM3J3LjPXfA2PFRYzZhW4NpL3akBktyDhGTD0GjSXGfMjeyHk4ACSZ4tImkWUrIyDG3HAl/aPNU7nYAw3JDKU%2BrLgl2AUvEMg4FA0pk%2ByJfJ1NpYOHqNTQGLE4w03Dol7eIwwilHIOCSTbPRZU05EpUnIiaPIkbCREYj6LY8o3Y/Yw457e8PkLEl7FojEpQdo/g0kbolCDgTYWgTgfwXgPwDgLQUgVATgNwawawNMbYXYdyBbHgUgJzPM9MzYHEAISQCUDQAADjMDMAAE5OyuB/A2zWyuAGQGRpBMyOBJBeAWAJANADlcz8zCyOBeAFAQADlaytBNg4BYAYBEAQAJ40hCJyBKACU6B4hIhxROBVBWyqwL4qxJBHhgBkBkBHgpAJQzBeB8RCASA8BqiuAZBBARAxB2ApBfz5AlA1BNAdA9AWwEw0hOAeAMysyczwKCzOAYxCI9zMxUAqBHgLyryby7yHynzmyn8IBGY0hjzHkqz1heBVz0zSAIAkAjz6AyAKAIBGLxhgApApCaAG94glyIAYgkKYhwhWhkRYLeAhLmBiBkQYwYhtAGhazqzNZ%2BwYwalRK6zSAsAYgvBgB2JJklzuBeAsAWBDBgBxB1L8AXxGhMl9L8zMBVAGhCJ9hqzwgoRRz8ym8YgEwpKPAsAkKTQ8BJyDLSBMliBK0lBXhjKjAm8jBwLNgqADBgAFACRvgWw6xczqz%2BA/zRBxAgLMqQKVB1B1LdAfyDAYrTBLBrB9A8AYglzIBNgFj75OAL4qj3ZyqrBLAzA5yQr0csBaqIBNh6hPEXALRZg/AfzQhlhKhqg9BihWNRqZrMhWMRgprxgfzBr%2BhBgZhPBOg9B1qmhFhlqxgEg1rFh5qTqhhDri4JABryy9hrr9AELSBZzeB5zsLLzrzbz7zHznziLcAPyKLkguAqKazYrNguwgJxh%2BrSBGyUgJROzkhhyNBJAkgawNB/AqxOyHqxyJyQBAaJQqwuAqxWzOyByqx/BJBez4aqwnqkL5zFzlyQa6z1ytz6Kdy0L9yWK2LiBTy2BOBWgWBSwGQL49pSJpwuBOyJQuAWy3z8AiAeq9A8r/ycrpA8rFACqkLdApCoLgcxL4KOBsyab1L5zUKCB0Kj4sKcKPq7wxaJapbSESLGIyKmL6QFszBgaaL1yGLHbyKDzWLvamKUBSqOKeyDluKHk%2BKBL1KJKRKxLSBo6pKZK5KHBY6lLHQVLakkLNLtLdL7ZY6jKTKzL8yLL5K8BrKkK7KHKoRY6XLegkKPKvLkQfL9h8z/LArqyQqwrMAIqC6fxYq%2BAEqkqUq0rY7FbsrAKVbZA1awKirEh9ATKUASzLAqqar4B6qtslimqWr5w2rrBOqXruqvyfhV6eg%2Bg3SIBXAzrggLRLrpqfzZr%2BhL776cgb7VqT6S6BBNr2htqCg1reh36BgDrJqjrdrTrv6xqpgLqgGrqgatgdg7qYHRyDbnrkKOA3rcLbzRbfxxbJaWzHgIA/q5aXbAb3bQbSBwab5KA9bxzSBJzkgJakaGR/BOyhzkhkbJAbyfzkG6bbAGaPa6KWakBdyObDz/aTyzyOB%2Ba8KWAFBSxHzSxsGeQFgZb/qvyFbZAlbx7gKp7Cr8zdBUhtaYKDK9akHaaUL2aMKLapGZG5GFHjwRsHaYRyKiHkgSGma6KvbHGmLfauaQBZHmCnt5HOyntFGCAntVAby%2BA6Bw7KBI78z461Lqz4nE75KU6oU07VLM7MAtKdLl59Lqz86orm7DKhsS6y71KK7kBHLq7BBa71L66RKm6/L0c27eAO7tZu6ore63H4qmBErkrMBUq0QR71Gx6JAJ7BBtGNbca56yrF6bAPK%2Bq17GrDgqiF6KqOqur4geqj66q36hrz6RqwG9AJqKhgG77FqH6jnzmShn6oHb69mNrQH8hwG9qP7AHTnoGIGtrnmQHIGPnb6bq4HALjHEKjbOBsKrHZHHhAmJQQm8GCH85zBiHqLSHyHIaqGcauyJRkhkhAgkbxCNAcWGQibDa5zOB6aVzSGYb/A4bByGRpzWzJAeyuB2yzBqbRzkhQWyWFzGa1y9bXzSWXryXeX6zgreK3TJAgA%3D)

## Links

- [Example](../../../code/facilities/metafunctions/raillivore/classic_trek/implementation.hpp)
- [Source code](../../../../conceptrodon/raillivore/classic_trek.hpp)
- [Unit test](../../../../tests/unit/metafunctions/raillivore/classic_trek.test.hpp)
