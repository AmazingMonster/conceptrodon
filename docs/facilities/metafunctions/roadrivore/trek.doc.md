<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Roadrivore::Trek`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#roadrivore-trek">To Index</a></p>

## Description

`Roadrivore::Trek` accepts an operation.
Its first layer accepts another operation for composition.
Then, it returns two commitment functions and twelve continuation functions.

- **Commitment**
  - **Conjuration:** When invoked, this function instantiates the first operation with the arguments. Then, it invokes the second operation using `Omennivore::Send` with the instantiated first operation as the packed vessel.
  - **Transition:** When invoked by a vessel, this function transports the conjuration function to the vessel.

- **Continuation**

  When invoked by another operation, the function returns a `Trek`
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
   >
   >
       &vellip;
   >
   ></code></pre>

## Type Signature

```Haskell
-- Compose with Mold
Trek
 :: template<template<typename...> class...> class...
 -> template<typename...> class...
 -> ...
 -> Commitment

-- Compose with Page
Trek
 :: template<template<typename...> class...> class...
 -> template<auto...> class...
 -> ...
 -> Commitment

-- Compose with Road
Trek
 :: template<template<typename...> class...> class...
 -> template<template<typename...> class...> class...
 -> ...
 -> Commitment

-- Compose with Rail
Trek
 :: template<template<typename...> class...> class...
 -> template<template<auto...> class...> class...
 -> ...
 -> Commitment

-- Compose with Flow
Trek
 :: template<template<typename...> class...> class...
 -> template<template<template<typename...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Sail
Trek
 :: template<template<typename...> class...> class...
 -> template<template<template<auto...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Snow
Trek
 :: template<template<typename...> class...> class...
 -> template<template<template<template<typename...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Hail
Trek
 :: template<template<typename...> class...> class...
 -> template<template<template<template<auto...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Cool
Trek
 :: template<template<typename...> class...> class...
 -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Calm
Trek
 :: template<template<typename...> class...> class...
 -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Grit
Trek
 :: template<template<typename...> class...> class...
 -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Will
Trek
 :: template<template<typename...> class...> class...
 -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment
```

```Haskell
-- End in Conjuration
Trek'
 :: Commitment
 -> template<template<typename...> class...>

-- End in Transition
Trek'
 :: Commitment
 -> template<template<template<template<typename...> class...> class...> class...>
```

## Structure

```C++
template<template<template<typename...> class...> class>
struct Trek
{
    struct Commit
    {
        template<template<typename...> class...>
        alias Road = CONJURATION;

        template<template<template<template<typename...> class...> class...> class>
        alias Snow = TRANSITION;
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
template<auto...>
struct Shuttle;

template<typename...>
struct Capsule;

template<typename...>
struct Capsule_1;

template<typename...>
struct Capsule_2;

template<template<auto...> class...>
struct Carrier;

/**** oper_0 ****//* Start */
template<auto Variable>
struct oper_0
{ 
    template<template<typename...> class...Containers>
    struct Detail
    {
        using type = Capsule<Containers<Shuttle<Variable>>...>;
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};
/**** oper_0 ****//* End */

/**** oper_1 ****//* Start */
template<auto Multiplier>
struct oper_1
{
    template<typename...>
    struct Detail {};

    template
    <
        template<typename...> class Container,
        template<auto...> class Sequence,
        auto...I
    >
    struct Detail<Container<Sequence<I...>>>
    {
       template<auto...J>
       using Page = Container<Sequence<Multiplier*I..., J...>>;
    };

    template<typename...Agreements>
    using Mold = Carrier<Detail<Agreements>::template Page...>;
};
/**** oper_1 ****//* End */

/**** oper_2 ****//* Start */
template<auto Variable>
struct oper_2
{
    template<template<auto...> class...Sequences>
    struct Detail
    {
        using type = Capsule<Sequences<Variable>...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = Detail<Agreements...>::type;
};
/**** oper_2 ****//* End */

/**** First Example ****//* Start */
using SupposedResult = Capsule<Capsule_1<Shuttle<10*2, '*'>>, Capsule_2<Shuttle<10*2, '*'>>>;

using Metafunction = Trek<oper_0<2>::Road>
::Road<oper_1<10>::Mold>
::Sail<oper_2<'*'>::Rail>
::Commit;

using Result = Metafunction::Road<Capsule_1, Capsule_2>;

static_assert(std::same_as<Result, SupposedResult>);

// The following `static_assert` shows how the operations are composed:
static_assert(std::same_as<
    Send
    <
        Send<oper_0<2>::Road<Capsule_1, Capsule_2>>
        ::Road<oper_1<10>::Mold>
    >
    ::Sail<oper_2<'*'>::Rail>
    ,
    SupposedResult
>);
/**** First Example ****//* End */
```

- In the second example, we will transport the conjuration function to `InvokeRoad`.

```C++
/**** Second Example ****//* Start */
template<template<template<typename...> class...> class RailArg>
struct InvokeRoadDetail
{
    using type = RailArg<Capsule_1, Capsule_2>;
};

template<template<template<typename...> class...> class...Args>
using InvokeRoad = InvokeRoadDetail<Args...>::type;

using Result_1 = Metafunction::Snow<InvokeRoad>;

static_assert(std::same_as<Result_1, SupposedResult>);
/**** Second Example ****//* End */
```

## Implementation

We will compose functions using `Omennivore::Send`.
For example, we can compose a `Road` and a `Rail` in the following way:

```C++
template<template<typename...> class...Args>
using Metafunction = Send<Road<Args...>>::template Hail<Rail>;
```

Note that in order to succeed, `Road<Args...>` must be a packed `Rail`, meaning it is of the form `Vessel<Items...>` where `Items...` all have signature `template<auto...>`. This requirement is not checked by `Trek`.

We will implement `Trek` by performing recursion manually, meaning the function will recurse only once for every invocation of a member template.
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

- `Radio` is a `Road` and
- `Car` is a `Mold` or `Rail`.

Here is the entire implementation.

```C++
// `Radio` is a `Road`.
template<template<template<typename...> class...> class Radio>
struct Trek
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
           template<template<typename...> class...Signals>
           using Road = Send<Radio<Signals...>>::template Road<Car>;

           // Helper function for the member template `Snow`.
           // This function transports the conjuration function `Road` without invoking it, 
           // allowing further process by other higher-order functions.
           template<template<template<template<typename...> class...> class...> class RoadVessel>
           struct Detail
           {
               // We transfer the conjuration function `Road` to `RoadVessel`.
               using type = RoadVessel<Road>;
           };

           /**** Transition ****/
           template<template<template<template<typename...> class...> class...> class...Agreements>
           using Snow = Detail<Agreements...>::type;
       };

       /**** Continuation ****/
       // This function composes the conjuration function `Road` and the `Agreements...`.
       // Note that even though `Agreements...` is variadic, it only allows a single argument.
       // This is because `Agreements...` will be used to invoke `Trek<*>::ProtoRoad`,
       // which has only one parameter `Car`.
       template<template<typename...> class...Agreements>
       using Road = Trek<Commit::template Road>::template ProtoRoad<Agreements...>;

       // This function composes the conjuration function `Road` and the `Agreements...`.
       // `Agreements` will be used to invoke `Trek<*>::ProtoSail.
       template<template<template<auto...> class...> class...Agreements>
       using Sail = Trek<Commit::template Road>::template ProtoSail<Agreements...>;
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
           template<template<typename...> class...Signals>
           using Road = Send<Radio<Signals...>>::template Sail<Car>;

           template<template<template<template<typename...> class...> class...> class RoadVessel>
           struct Detail
           {
              using type = RoadVessel<Road>;
           };

           /**** Transition ****/
           template<template<template<template<typename...> class...> class...> class...Agreements>
           using Snow = Detail<Agreements...>::type;
       };

       /**** Continuation ****/
       template<template<typename...> class...Agreements>
       using Road = Trek<Commit::template Road>::template ProtoRoad<Agreements...>;

       template<template<template<auto...> class...> class...Agreements>
       using Sail = Trek<Commit::template Road>::template ProtoSail<Agreements...>;
    };

    template<template<template<auto...> class...> class...Agreements>
    using Sail = ProtoSail<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKz%2BpK4AMngMmAByPgBGmMQgZpJcpAAOqAqETgwe3r4BQemZjgJhEdEscQlJKXaYDtlCBEzEBLk%2BfoG2mPYlDE0tBGVRsfGJybbNre35XQpTQ%2BEjlWM1AJS2qF7EyOwcAPQAVMcnp2fnh/smGgCCRycA1AAimKmujMh4mAoPp1e39wuQLO/xu1xuBEwLFSBkhJgAzG4CABPN7MNgPZRMZAAa0w6AAat87AjsOD5sQvA4HkJXA8TAB2KwMp4Iqy3cGQ6GwzAIpFQmFMOGIlFo1iYAB0UtJD2QBgUPw8giYSzID1FjHFUol2HobEEClJ5IIlOptIY6D5Suaqr5uqhjAICm1RvhZI5TPBD296oFPL5XMFwqRqM1bBdbtl8p%2BAHk3sQhdkjbcfQ8KVSCM9MDbaF6fft9g8AJIMABuqDx9IAbBo4/FEwITDWHgB3QgIdUITDVjT2/VOl01iV572MiwPLyZIzq0P0%2BFPB51hN9O16x3O6Vutn0lls8Ej33coW8kV%2B48B0PoyWb7BRpgK7U3YDETAOg3Jm6pyfhYAPABKqBMOgc4Li8OZ8k%2BL5vgON4gCAGp7h6rLwuyYK3IG/qnkewYYeeiJMF4RARrecr3huw6RqRCo0kQuLEKgqAsKQh5BiebgEURN53g%2BUq0gAjl4HzfB%2B6Zmq4fJNKgdEMSwEmYAJQnka67pgp6KY%2BrhOFnlp2FsRxqDEdxSmUdGi7xg2DAfqmomZmBKq5up3oFsWZYVt2Ta1uZK7Nm2BAdn57k1vxgkMLsSlDgeY4TlOv4aiBZn1iuiLBYpxHboyyGoQemlsTlAbaXphEGVxVHGSR0aPs%2Br79oaW6OdFP40vZ8V2XQEFVdBZVwQhKH7ruvUcgCwLDSC4KAocxbctBFm/CcoLjSNwKgmNhYeX%2BQFOB5Dx4D8TA9gBQEecO6EFflulnaxF5iuGJUVbdZH/htqAiSaGYPAAKi%2BOJ9ahqbjVmNARP%2BgHAX8B7OR57HEFtO0PHtHkALKeJaEX1XlWGXSKl5avd1FQ1ZPo2Zi9FEAdlr1WOB75qcDweCwLCEP2s3HKCqaE691J0wzBBU6OamfmzbP/Uq2jbDNYP1YLDwQzW634M9zaGMBkMtFtLTdmg0IZPiDxdi%2Bx0C1L3ro/y51Y9d14UeVZHakIeDAMwtC1SpRs%2Bt%2B05k/F5qWoicubcl9uO2VpLdQVwOHYi%2BNbgNaGG0bzkABI9PGDxUF4oV9KnJCdt2bArMQLE8j2QgMKgLZHbzQuFu9CCw2nGfZOqCYMAo6StD8AWygIovLo39cNAI%2B0g1tvkIFsmbhOWOKNYQzGV39hZiLQZeNWnrR6w8qT0WFPwxMiDyoAFBe18AesALQkFgBf930zrzxpp0Y5hpuYy/z8alehmlV/d1W0Z4eEmJD0AmrsiatQcnHKWlNJau2loWAA6t2E0hgFBUHiDnLuDAe4zRvo3Naw9mxECHkBIkCpgGo0gbA92sVZwIgXGTUhJJfbD2jr9WBGVEKx1gdLGmn0UFZEHhLShbMTaiMfm/PCIYLY/xtrjMqRlKpQRqiAo21CaSlxbC1bM9l2pKPXMRbqoZOFQP6llGBPDHjWnCF4cWc1K7ORrnXdOA8GBdy1koDuXZMHYMzrgwe%2BDDqKwtBgjykFqr6OlBQqWzlIiHyQQgIUDxMClkYJ2LYp8exhM6oODQ20filhaHgDayBmKEAPgwWg%2B8l5l12mmH89A4bEGAD4R0BtonV1rj8WGcRRCTkCrcDqNUcmtjoLQB4cRoo6yIZPNyPZPqYG%2BoiQ4IcQDKBJqgMmHlSD2MLC2WuyAOwJJ%2BAISp5TuypBaOKSEBcVbQyiYLMRZspFhktjKb%2BUosnKLqsItRns6EfS%2BlaRi3NQ66QASsnKxND4bJYW4T5ESracJ2R9TpqdnGZ01kUb4GC0BYLFr49FeDZYENyUrEJNZ4UGhyW0wWMsBl6PfD5UZ4zux9OAtM1ylYPLzMWW4ZZbo4JrOhUIeyNKRHiMea/fSMieJ/3eRKSlToVFuxik1Og8UeVAvpoQUFrFwUCvgmHIVRARVtURIq4OMdUwcJjtlCVErsY3Tlb/C1Kjfkg3isamFEc4WDIRa6Mxcd/ovEBt2U1YyhELxRU4hug9Yad0yAzAwBdO4eS9Zs5sWBQ3ASYDEVAKSxVwOLJmBJFp6CeI1vebsez4j9Pxs2WG8NZY6Pucbe1TyTbSrkTKxUqtvnWQ5pmL14bIr82iTTLmjNHTM0uJXImk6ebmOgcIv6E7u74sbpG2Bkr36OteSZWREo7YOzEM7e%2B3p3VAS9uJX2T0JKB1PWlA1kKR2Rz7WSW15jUw7skT%2BnCe6e2AbkQAxhwD%2B2wLAdotqX6fTLu4SqxqcV/kMKAbmZhEcP1sNdjawN3D/p8JbgI1xW7XZ/tyu21%2BH8cbOsPW83%2BdHD2uvA67NRJcy5aPAuav1VLYLwSMVawWOH9zmOFrIaxtiWaVzI1dF5QGFXcaVcxr8qq/nzgBQsrVILDVgs2c%2Bo16zdO%2BoZTBRFn7hHSafpIrtNHZUMdlUxl2gtWPNX%2BZqyOwKdXab1bp7Auqi7Dp0Vx4zlqsM7kysJuOFmJHBms3Z%2BR8qHMHmc%2Bq/5AWzVGfCTx0zWVTERYWotc480aYADE8DEHmA8bAqhWAwm7EI/LBWhH7jMPCcIcovBYDnG4XFuxUiKZUmNGmQgECEQIA0oRnaippVuETYbo36BIqGpYpgqQFBeHLTO0EoiAM3mNKaTM7FVvrZPIG7b0jdszcHbTFba36AAH0uCLYhA687iLLv7eu0d%2B7ZgnvCxaMQL4BcJsUefrFg9tnvnzv%2B4D37NMlx3dycDp5%2BkHgEkKbmhbkOrvw40D9ekaMQe/p2zZ8i1oVQRHKyoyD4EKZjqlmopDanDu3bYmT1UtU3BzYIGNtiaOAcY5PB%2B7AT7QtCcGpFwn/7XtxcUZl/rSWVMev%2BeA3Rcuup8beEi3L4v/rw64Jtzk4iUcI3W44GEMOscfb1z9O1HbidU6u%2BAnczJwvi%2B/adCmiJ55ndk8BtnFPtlfsm5xEnNJ5IhV2IHld1miyRSU9TwLbh/fxDkgpUKbEixPqF6O0LD9kdTalAAKWVRe1VWJgDuSZ7IcnKfkrh6EnyE3tAze0EB4cTPUpmKF6z8Y2D2uuF58o8TxL9U1FI1oMrJn0Pa9uBV0FtXEKjVMAryLvqrvY66/jHdswBuTr56IXzopMRMcqSJvDn7HpQtRbB9bWVKV09nvqgn6Dcc4P09VYzhczPjup4j8JREh%2BAupIq%2BtO6%2BtulGRuBeJOsunUbqKmLmamc%2BGW2SvGPUOWYBS2xwNIXgqQWK6Af43wpuu%2BNwrGOBeBBBt2mY/y3%2BmOSeN2x2D2EkI23OtBXAGghwZgzEYAHAhw3BykzENBmA2%2BTB82bEbBHBXBPBfB0c2eZm/0CM2ifixGditwY%2BihhK/iambmbgOOfIP2BqPm4IcEhm1uiIbBKy4%2BPsKkcEr6OhW%2B%2Bhbg3BvBHAKy60Zq1hIAC6sOjwFBRBQivyhBze8UChzQShxhsKghD2Ah9B32AaeWvC3wToxB8wiYyAd2ZE8QBAEA8w6AcECg4o6RHOvhzezEQgZB2s%2BBgRPMboawv2HS3Y/AtAy8bY04HkKRjgaRGRrQW0CgY8LYPwfRGCqAXk2Qu0L4bieBIAxoqRhRSgrQ2RBAuRIA%2BRbAhRfIB43scebg88mxiIuhiI%2BhvmIAhmkRKQn2LOwhMh884RPqphbg5hBqlhKiKiNhie5%2BfITh0hRxbhaGjm3oUeqYZRuBFRxRi6YINR3hjWQIRWjwtIuKwEVWNW42KhdwUJS08RjwJYU8mAnsSOEBHaL2vu0BwGPxNwTSL0H2WJbkZMKul%2BCuiGtCampJ5Jb6X2QhZxkRhxWuGBz2BJfJQ%2B0u4O8WLqTSj%2BJBqqVJeIqmC4kpOJIMSBZJwA6uaBGJWBoJxBARlBD2wR6hsafgIAbG5ciIsphhchCRFWQi7ReAnRZC8xOReRBR94fIoJUR2BwJSglRlBpItRKEHAGwtAnA/gvAfgHAWgpAqAnA2xlg1gaYWwOw7kLWPApABAmgfpGwOIAQkgEoGgAAHGYGYAAJwFlcD%2BC5k5lcAMgMjSABkcCSC8AsASAaAaCkAhlhkRkcC8AKAgDNkpmhl%2BmkBwCwAwCIAgDjypCETkCUCYp0DxCRDiicCqA5lVhnxViSAPDADIDIAPBSAShmC8D4iEAkB4C5EpD8CCAiBiDsBSAyCCCKAqDqB9mkC6ApAtgJipCcA8D%2BmBnBmpnhmcAxiETjmZioBUAPCLnLmrnrmbnblZk74QB0ypAzk3KJlrC8C9laAbAQBIDTn0BkAUAQA4VjDABSCcE0DN7xBdkQAxC/kxDhAtDIgfm8C0XMDEDIgxgxDaD1C9lJmaz9gxgVIMWPlYAxBeDADsRNFdncC8BYAsCGDADiBCVlZcV4ApKSVhmYCqD1CER7BJnhCQg1lhmt4xAJisUeBYC/kmh4ANlSWkApLEB5pKAvCyVGCt5GCpkbBUAGBKkEhfAth1ghlJlnnCCiDiDXlBV3lqC/nPn6ByUoDWDWD6B4AxBdmQAbDDG3ycBnw5F0KmDRmWBmBtl2UA5YApUQAbB1AuIuAWgzB%2BApChBLAVBVB6BFBEY1XNUZBEbDCNVjC1A9DKUCADDTCeAdB6AVV9CDWLDlCjAJC1ALBtWzWDBdXTUSDlVxm7ArX6Dfktm/ntlgVLkrlrkblbk7lwW4CHnIXwhcCoXJnuUbBdhARjBlWkAZmSDwgSgFnwhVkaCSBJA1gaD%2BBVgFmbW1n1kgCXUShVhcBVg5kFnllVj%2BDJD%2BAfVVjbWPntmdndk3V9mYXDlYWjmAUTn4WEXEBzlsCcAtAsClgMhnx7SkTThcAFkShcDZn7n4BEDFV6BBUXmhXSDhVKCRWPm6CcGvkraMVfkcBBmo1tn/kE3AWgXgUHV3j02M3M25LwWMSIW4X0gtZmDXXoX9l43E2TkEUa1IUoAGBGAM1sF8B0DXKUXUWPnMX0WMWkBO2sXsWcUOAu28WOj8WVK/nCWiXiVOwu0yVyUKVhn4AvgNCqW/kaVaWQgu16U9C/lGUmXIhmV7BhmWXWVJl2UOWYBOXh0/juV8BeUKA%2BWYB%2BVogu1c0hVXm82yARUPlhlC0xVuW5VWCWCJXJXwBpV9ajGZXZXzid3WAFW8D5rxDFXfB93dC9DZBVXuDDX5B1UWhLX5ztXFDZDzVpAdV9Dr1NW9Xz0DVzXL21Vz39X9ALAH09WTCDA70pGtA30zWrXbDrVXXA2S2tkT2cB7UQVrl02/gM1M3ZkPAQBnXs3a2XV623WkD3VXyUDi11mkANnwiM3fUMhI2Vnwg/WSCrkpDf1/kdm2CY36043wB41jmE1Tmm24Wk17AU2QUsAKClhbmljAM8jzCs3nXHmc2yDc0N03nyD80t06Bg2kAi3vlSXi1f07Uy0EBAUHzy1MMsNsMcPHgVbq3QhIVQPwgwPY0DnYW0PxDG3E0gCsO4F3bsMFl3acMEB3aqCrk23kXlaUAO1hlu2CVJmeMe1cXe3Aq%2B0CUB2YAiViVLySVJlh0uVZ3SVKUx0z2Pnx3IDaVJ2CAp2Plp30WZ0WUA6528D53axF0uUl0GOeXL4V2%2BX%2BW138P10SCN23kiNRXiMW3GDxXd1GWlX90ZUHD2mj35WFVT3Hkz2pUX2VUQCuA731VTUb0pAtV9A71zPZDP2jV9UuITUP2rPjXX0NXLULVDV5Dn2P2TXLCH2v3xkbU1myNo2/2ONrnMOsMPDWMSh2NgMQPZzmDQNoWwPwOPVIOg2FkSjwjwiBDfVsEaBAsMjQ1S0/3ENdk9mwMvX%2BDvUVkMhNk5mSDFlcB5lmAo01nwg/nXPENkPi17nQtENfPY0bB2WZDOCSBAA%3D%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/roadrivore/trek/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/roadrivore/trek.hpp)
- [Unit test](../../../../tests/unit/metafunctions/roadrivore/trek.test.hpp)
