<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Raillivore::ClassicTrek`

## Description

`Raillivore::ClassicTrek` accepts an operation.
Its first layer accepts another operation.
Then, it returns two commitment functions and twelve continuation functions.

- **Commitment**
  - **Conjuration:** When invoked, the function instantiates the first operation with the arguments. Then, it invokes the second operation using `Omennivore::Send` with the type result of the instantiated first operation as the packed vessel.
  - **Transition:** When invoked by a vessel, this function transports the conjuration function to the vessel.

- **Continuation**

  When invoked by another operation, the function returns a `ClassicTrek`
  - that is instantiated by the conjuration function and
  - whose first layer is instantiated by the new operation.

In general, this function composes operations together in a similar fashion to `.` in Haskell.

<pre><code>   Operation<sub>0</sub>
-> Operation<sub>1</sub>
       &vellip;
-> Operation<sub>n-1</sub>
-> Operation<sub>n</sub>
-> Arguments...
-> Operation<sub>n</sub>&lt;
   Unpack(Operation<sub>n-1</sub>&lt;
       &vellip;
   Unpack(Operation<sub>1</sub>&lt;
   Unpack(Operation<sub>0</sub>&lt;
       Arguments...
   >::type)
   >::type)
       &vellip;
   >::type)
   ></code></pre>

## Type Signature

This function has multiple signatures.

```Haskell
-- End in Conjuration
ClassicTrek ::   template<template<auto...> class...> class... 
              -> template<typename...> class...
              -> ...
              -> template<template<auto...> class...>
       
ClassicTrek ::   template<template<auto...> class...> class... 
              -> template<auto...> class...
              -> ...
              -> template<template<auto...> class...>
       
ClassicTrek ::   template<template<auto...> class...> class... 
              -> template<template<typename...> class...> class...
              -> ...
              -> template<template<auto...> class...>
       
ClassicTrek ::   template<template<auto...> class...> class... 
              -> template<template<auto...> class...> class...
              -> ...
              -> template<template<auto...> class...>
       
ClassicTrek ::   template<template<auto...> class...> class... 
              -> template<template<template<typename...> class...> class...> class...
              -> ...
              -> template<template<auto...> class...>
       
ClassicTrek ::   template<template<auto...> class...> class... 
              -> template<template<template<auto...> class...> class...> class...
              -> ...
              -> template<template<auto...> class...>
       
ClassicTrek ::   template<template<auto...> class...> class... 
              -> template<template<template<template<typename...> class...> class...> class...> class...
              -> ...
              -> template<template<auto...> class...>
       
ClassicTrek ::   template<template<auto...> class...> class... 
              -> template<template<template<template<auto...> class...> class...> class...> class...
              -> ...
              -> template<template<auto...> class...>
       
ClassicTrek ::   template<template<auto...> class...> class... 
              -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
              -> ...
              -> template<template<auto...> class...>
       
ClassicTrek ::   template<template<auto...> class...> class... 
              -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
              -> ...
              -> template<template<auto...> class...>
       
ClassicTrek ::   template<template<auto...> class...> class... 
              -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
              -> ...
              -> template<template<auto...> class...>
       
ClassicTrek ::   template<template<auto...> class...> class... 
              -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
              -> ...
              -> template<template<auto...> class...>

-- End in Transition
ClassicTrek ::   template<template<auto...> class...> class... 
              -> template<typename...> class...
              -> ...
              -> template<template<template<template<auto...> class...> class...> class...>
       
ClassicTrek ::   template<template<auto...> class...> class... 
              -> template<auto...> class...
              -> ...
              -> template<template<template<template<auto...> class...> class...> class...>
       
ClassicTrek ::   template<template<auto...> class...> class... 
              -> template<template<typename...> class...> class...
              -> ...
              -> template<template<template<template<auto...> class...> class...> class...>
       
ClassicTrek ::   template<template<auto...> class...> class... 
              -> template<template<auto...> class...> class...
              -> ...
              -> template<template<template<template<auto...> class...> class...> class...>
       
ClassicTrek ::   template<template<auto...> class...> class... 
              -> template<template<template<typename...> class...> class...> class...
              -> ...
              -> template<template<template<template<auto...> class...> class...> class...>
       
ClassicTrek ::   template<template<auto...> class...> class... 
              -> template<template<template<auto...> class...> class...> class...
              -> ...
              -> template<template<template<template<auto...> class...> class...> class...>
       
ClassicTrek ::   template<template<auto...> class...> class... 
              -> template<template<template<template<typename...> class...> class...> class...> class...
              -> ...
              -> template<template<template<template<auto...> class...> class...> class...>
       
ClassicTrek ::   template<template<auto...> class...> class... 
              -> template<template<template<template<auto...> class...> class...> class...> class...
              -> ...
              -> template<template<template<template<auto...> class...> class...> class...>
       
ClassicTrek ::   template<template<auto...> class...> class... 
              -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
              -> ...
              -> template<template<template<template<auto...> class...> class...> class...>
       
ClassicTrek ::   template<template<auto...> class...> class... 
              -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
              -> ...
              -> template<template<template<template<auto...> class...> class...> class...>
       
ClassicTrek ::   template<template<auto...> class...> class... 
              -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
              -> ...
              -> template<template<template<template<auto...> class...> class...> class...>
       
ClassicTrek ::   template<template<auto...> class...> class... 
              -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
              -> ...
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

- In the first example, we will compose `OperationA<2>::Rail`, `OperationB<10>::Mold`, and `OperationC<'*'>::Rail`.

```C++
template<auto...>
struct Shuttle;

template<auto...>
struct Shuttle_1;

template<typename...>
struct Capsule;

template<template<auto...> class...>
struct Carrier;

/**** OperationA ****//* Start */
template<auto Variable>
struct OperationA
{ 
    template<template<auto...> class...Sequences>
    struct ProtoRail
    {
        using type = Capsule<Sequences<Variable>...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};
/**** OperationA ****//* End */

/**** OperationB ****//* Start */
template<auto Multiplier>
struct OperationB
{
    template<typename...>
    struct Detail {};

    template<template<auto...> class Sequence, auto I>
    struct Detail<Sequence<I>>
    {
       template<auto...J>
       using Page = Sequence<Multiplier*I, J...>;
    };

    template<typename...Agreements>
    struct ProtoMold
    {
        using type = Carrier<Detail<Agreements>::template Page...>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};
/**** OperationB ****//* End */

/**** OperationC ****//* Start */
template<auto Variable>
struct OperationC
{
    template<template<auto...> class...Sequences>
    struct Detail
    {
        using type = Capsule<Sequences<Variable>...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = Detail<Agreements...>::type;
};
/**** OperationC ****//* End */

/**** First Example ****//* Start */
using SupposedResult = Capsule<Shuttle<10*2, '*'>, Shuttle_1<10*2, '*'>>;

using Metafunction = ClassicTrek<OperationA<2>::Rail>
::Road<OperationB<10>::Mold>
::Sail<OperationC<'*'>::Rail>
::Commit;

using Result = Metafunction::Rail<Shuttle, Shuttle_1>;

static_assert(std::same_as<Result, SupposedResult>);

// The following `static_assert` shows how the operations are composed:
static_assert(std::same_as<
    Send
    <
        Send<OperationA<2>::Rail<Shuttle, Shuttle_1>::type>
        ::Road<OperationB<10>::Mold>
        ::type
    >
    ::Sail<OperationC<'*'>::Rail>
    ,
    SupposedResult
>);
/**** First Example ****//* End */
```

- In the second example, we will transport the conjuration function to `InvokeRail`.

```C++
/**** Second Example ****//* Start */
template<template<template<auto...> class...> class RailArg>
struct InvokeRailDetail
{
    using type = RailArg<Shuttle, Shuttle_1>;
};

template<template<template<auto...> class...> class...Args>
using InvokeRail = InvokeRailDetail<Args...>::type;

using Result_1 = Metafunction::Hail<InvokeRail>;

static_assert(std::same_as<Result_1, SupposedResult>);
/**** Second Example ****//* End */
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

Note that in the following code,

- `Radio` is a `Rail` and
- `Car` is a `Mold` or `Rail`.

```C++
// Simplified `Send` function.
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


// `Radio` is a `Rail`.
template<template<template<auto...> class...> class Radio>
struct ClassicTrek
{
    /**** Define Road ****//* Start */
    // `Car` is a `Mold`.
    template<template<typename...> class Car>
    struct ProtoRoad
    {
       /**** Commitment ****//* Start */
       struct Commit
       {
           /**** Conjuration ****//* Start */
           // `Radio` and `Car` are composed here.
           template<template<auto...> class...Signals>
           using Rail = Send<typename Radio<Signals...>::type>
           ::template Road<Car>;
           /**** Conjuration ****//* End */

           
           /**** Transition ****//* Start */
           // Helper function for the member template `Hail`.
           // This function transports the conjuration function `Rail` without invoking it, 
           // allowing further process by other higher-order functions.
           template<template<template<template<auto...> class...> class...> class RailVessel>
           struct Detail
           {
               // We transfer the conjuration function `Rail` to `RailVessel`.
               using type = RailVessel<Rail>;
           };

           template<template<template<template<auto...> class...> class...> class...Agreements>
           using Hail = Detail<Agreements...>::type;
           /**** Transition ****//* End */
       };
       /**** Commitment ****//* End */

       /**** Continuation ****//* Start */
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
       /**** Continuation ****//* End */
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
    /**** Define Road ****//* End */

    /**** Define Sail ****//* Start */
    // This function is the similar the `ProtoRoad` defined above.
    // It handles the case where `Car` is a `Rail`.
    template<template<template<auto...> class...> class Car>
    struct ProtoSail
    {
       /**** Commitment ****//* Start */
       struct Commit
       {
           /**** Conjuration ****//* Start */
           template<template<auto...> class...Signals>
           using Rail = Send<typename Radio<Signals...>::type>
           ::template Sail<Car>;
           /**** Conjuration ****//* End */

           /**** Transition ****//* Start */
           template<template<template<template<auto...> class...> class...> class RailVessel>
           struct Detail
           {
              using type = RailVessel<Rail>;
           };

           template<template<template<template<auto...> class...> class...> class...Agreements>
           using Hail = Detail<Agreements...>::type;
           /**** Transition ****//* End */
       };
       /**** Commitment ****//* End */

       /**** Continuation ****//* Start */
       template<template<typename...> class...Agreements>
       using Road = ClassicTrek<Commit::template Rail>::template ProtoRoad<Agreements...>;

       template<template<template<auto...> class...> class...Agreements>
       using Sail = ClassicTrek<Commit::template Rail>::template ProtoSail<Agreements...>;
       /**** Continuation ****//* End */
    };

    template<template<template<auto...> class...> class...Agreements>
    using Sail = ProtoSail<Agreements...>;
    /**** Define Sail ****//* End */
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIaa4AMngMmAByPgBGmMQgZmbSAA6oCoRODB7evnrJqY4CwaERLNGxZlK2mPb5DEIETMQEmT5%2B0naYDul1DQSF4VExcQm29Y3N2VwjPX3FpXFSAJS2qF7EyOwcAPSbANRCeCyJtHg0mOg7JgBsGkKuVxo7VF4MnQIAdCYaAIIEmIcGvxMAGY3AQAJ6JRisTA7ZRMZAAazOADVMAo7MDsJ8vgoCMQvA49q4LgB2KwkgAiwKs32xv3%2BTEBIPpR0ZmGBoIhULYb15mJ2yAM6J2HkETBCMVIO3BkOYPN52HobEECkx2Nx%2BMJtwY6A5ovqEuIHMVf0YBAUvI%2BQKx1uxJjJ2J2Tulf1ZTNBroB7OZXLlmEt/MFTGFAHlIcRGek1d9nTsNQSCDsKZgDbRHc7tjsAJIMABuqCRF2uYZikYE9x2AHdCAhpQgYfcTcrzQHrh8Y877RYdl5UkZpVyLkCKTsSxGasalWaLXzbUDu/aqfO7R2nSyvRz12zN77oQHrQKhTO3l9gMRMKaVdGvrHeyFgDsAEqoJjnYEj5Opjmn8%2BXluz7AQBAGVvRpL5F2pFcfk9bdmRg90t3dJgvCIfdsEPYNj0DI89iIRFiFQVAWClRDvTcZDUIAjD0UtW4AEcvEYdZVVtb54y1O4QTqVB8MIlgOXoxiXjRNDry7dM13gsjSM3KSOQo1A0OorCDyDUNwzLBhr1jdjE0/cU01XHZMxzfNC3uMdNIrasCFrWyG2uQSmJEvk2wk0luzvfsQKHEdLInLjMAY5yVJtBdKUg2kjJkuCGQQuSQQUpS1NC5TLR/C9mxYrEjK8h8hAM3ykxTAzvzPTLpzQoCQMi8CIuXKLwO%2BTN7kfV8nArPAFB2Jgiw0Nq6HudtoLi6SEo9Ub5JQxSqJS5KcLa/BUGvXSRSPPBkAAFXPBE7QdIzNgAKmOw7ipoUInxfc4TsO7ZTu6Rodlu9yWuucijWuHYup6vqAFlPF1NzovGmLOVlPdZpw97tOdVblAIohn1fdzxKMjMbpFIiWEIZsnpOu7cJ6J7Nnc2G8QTTGWGxghSadVGb1jRnjIx0VtFWTS8eOgmHsTZ60aZ17%2Bva5bPsMN83oaCsGhhNBDhSM4dnrc9hqZxnQdBpLIcw2i8GAZhaGy2nGbyp9CvfIkdR3cG2FNpaBN1/XQuqrkYdVp1qqky7kZBaG5zAt30ZOzGGDZ8d0k526jp2bAdWJqCA7p/nGaOoPtsMPJw5u7nRl5kmk9jTMAAkqnDR5nleBhHhIOsYTYEoYhdUa%2BsL0qgYZgPM02hBvqeF4amlCMGAUZJGm6%2ByBQEUOOd7iu%2BoGtNPpshAVkTEIzPvL6CClI2C92MRaFQat%2ByeRolZ2RICOY7rIjBHZUHs4hFd1pWAFoSCwR%2BZ5qC0d%2BddWQYAZNRK015ray1jRcB3V56onRFUV2btVr6UGvnTs%2B124JydJmAA6jCPE6cqAN3HmgEO7N%2B5f3Dq1VuDwiBzwMjAjEbcMG3j7A%2BHy5toFogxCCeeaoGroNVhBPhv9JJAImm6MaoiNYgMgaAiBVp0JzV5BlP8hsUFOhNi3OgRUkFphBMorKVVgIuz4RglOx0dhpyHmkAQEcCYx2unnfhdN6r%2BwFizLGOMzS2KjvYuOjVVZmNOvqEIXgOZZyjjzPxTjjK7C7j3cu/dZa5DRDXCeJCw42PITYyhg1Rax3HvcfRlVXIaBVgLXYYR764IQIyHYmBcyMDrCsYAtZCnlRUa2B431cwNDwO1ZAUpCB3wYLQW%2B%2B9D7dV6iw%2BgPViDAB8GaMpydYnd26t9aIohewOW%2BO0gxJSqx0FoDsaIPYlDnBoWvAs2y3DrS2jtDkhj4b31QEjQGGhSBG0zJWbuyBaw1O6gIUZwyYSJAaNCX4j97jQ0YUzf%2BkjdzynkWlJRuzpzwOdCbV5RUbmYQ2ttTAu0fYeIIB7JuPDrSkvEbCBGLyrplV/Hs%2BRtVPkrPiX3cOST5Zj3rGkqeZCEkUOuDwvJ5yeVtIZcUj4MLll9SKVeRehzjkwi2ec1AX08xXL6ji9EeL7kgkeTSgqdAlmxjheI2SojNZIsUdao86VUVXlYtEk2Rqjnm21akO5BK9TEspV6U2g0KXAU9k8ogrr6UVRVKJExbig7BIYKE/u4TTq%2BL5ugwRYF3Jmo3D6a2/oZEoolY6nK6DMVXSKqG2l3s3Byv/EymNmCMbJnOjCLFybo6xzTS9JtmAW17EKu2yJabd4WNWWXdlNjvrj1SNjAwj8CnXEra8isWAW3nCYJEVADSTUmUTDUnU9BuUy2DDCb5MRrmS0%2Bt9XqOSF6lKzYA81sUn3kWkbasB77hS%2BxLTpcmhJK3hqMvTAJ7iqaeMEN4%2B6Ocomq1Wh4MDNMk7AYToE4OfLM74widB4dCds2wVfZRT9x59h6zEKo6JzCN7zyKtqXUubuStuFvbUjBtDE1SdRgv1bJ%2B2BrcN%2B2qpj3HpLCZhlNnbHHCOZqnQeGcbGDuw44jBeH4qSPGla7CH6NNyK01AuhnC4EcYTogkqyCKOoNcUwk2bDhwBtoPQgzbhyVhUkxm%2BOuHH05rEZ5qRhGdOyNSja2t5GMEaLNjZnREaOkAWdpCATKGMaWNk5XdtqbFNM1c0nVD8Hqa4xS%2BJtzychOOATSJrmWGiY4bVh5/DIE/T%2BftUW806L1EsK9m%2BGzHrdXeqJQhrjvxbOYj6zCJddK9EOrrbwzNSdlMSJfep1SdqC0nnG8FpmLqwsjk616wlfHfXBrJaVINpFqXPPDWNxroU4uFbjbIEJpXI5iYcSjFxBXG4vpm1NXzC3NPfbkUF%2BB62tHmwA4dmtK3o0Wak%2BY5tEoeNHLy092kL3GqBJulzbEZjNrYCEJtfGGO0do4k7SMwQIQiCi8FgIcbgUJ0EIGCMS3wfMzSZWxP9iYhAIBQgQegzLGdqbfStNnexOcEG55gAA%2BlwXnI13sIvzSznEQvyKJAUF4HnQi%2BeqctQL37l3WeakTO9YgeAYjS9Q/5dIN55MVccUznYyJekbvVyW1aFuBBNTqguYGWu5s64UYtt4TlhKradHDGlPCgNoLdlZwc7qmAq7V2RIPzEOQO%2BN07702AIfPaXFN9BH3gFff9x%2B/7hmWtUY2ydxGoOgvZ6R7n/HQc3cMCt6JjtiOPfm40jUbs1vHpprt79NXjgjgm6NE6133f0iZqj3/EGcvRJGWM6mDyGWPemuq0hP3ykiTBWElKBS2Z4HL9B8nsiWZeE/vM0bJnloABSzXTkbzhMABsNmz8ciH7QEfxwYiHSzFKHfnXumsjuvnPvCnmg1pGk1mXnGELpWv9LQLqJHpDpRt5LHh1g0MbqbiCBFudtAdlENrCEwK/sAbGGvg%2BhAQxlASogDq1oge1iOAgQDJFoypNntA3s1BjM3r3m3qllBF3qWDUG4JBoTP3rbvzjQmnn0pEM7uqELs3m4HtJDgXgRszn5ryGfiHnAQbsVF%2BCgTvDHpCNivHqrurm4Foano7rIZnmQagpwWASIu9pIeobrjQVlHQRXkDuFiZromDhdmxsYjPg4YIRkhkKIfwSjhjAAGJ4DEC4jRyqCsBHAwh965zYgupeCJDJLoCPhojD4mEJ7mEc5c7mFcAaCHRmBShgAcCHQ1GYhSglGi70CS4cjlGVHVG1H1FzjOaNQmy/QlRZKVzuq3L4o7bN7gQghmCDYgBObYhATLogg8FtEaAzEMHXhARnZuCKEcg1F1EcAzFzHfBATZaEDS6Yr5Hf5FQDH1BDELGn4i5i6NGPEtFS5%2BxQS4iRjIDi6YQxAEAQC4joBAQKDQg/EsSOaXFbx7BZE5F5FmE0zWgLBm4rIwj8C0AHxHwPj3CfGODfG/GNAVgKDLyVjdTEmpKoBT4CCTLngTxyxnIgDyFfFglKCNAAkEBAkgAglsBgkcjuS0Yowgg7z8lLGUkt4cjTFBrkoWEvGYDPGlES5vGARGKxawGxgLGjbbGilWAgjlFrEsGqnOgxbshAawGbGg47Egh7HdFKlHHoIfJGRCAwnyy5GQl2iIm1SoaxHxGJjYBJH/CpF8H5ZRFBy3DELnC%2BnJEzJpFRKqG35LY6a2ZfBzKC66GmRXLzwRZI6Q5GFv4jjzxJnAACQylynNEKnsH17S6xkuH1ZLYFnkYmxplIjUbmyNmYAZm%2BHfhzJOzKmgRQQXHwmS7XGDECrOAgCaJ%2BGtlzEa6K5Mn4n/GAnAmgnBgchwnD6S6NFOlnKrnf6YhIl8KoahkCDhl%2BkpERHiYcBLC0CcAACsvAfgHAWgpAqAnAShlg1gcYKwawDYJOPApAJKD5F5SwCIIA15kgbwGgkgXAJIQIGg15GgZglwlwZgAAHMhfoJwJILwCwBIBoO8veY%2Bc%2BRwLwAoCAO8v%2BVoEsHALADAIgCACvIkChOQJQEknQDEGENCJwKoMhZcC/JcJIDsMAMgMgDsFIG8GYLwGcIQCQHgECZMPwIICIGIOwBUPJfIEoGoJoDoHoJWBGIkJwDwJeTeXeZpU%2BZwCGChAxYmKgFQDsFxTxXxQJUJSJWBWYDsBAPBokKxZCj%2BQsLwORReaQBAEgCxfQGQBQBACFYMMAFIFUTQN/jECRRAJECZZECEA0GCPpbwKlcwMQGCCGJENoB0P%2Bb%2BbLM2CGCMhlQBaQFgJEF4MAOROiSRdwLwFgCwIYMAOIFVfgOeJ0A0k1Y%2BZgKoB0ChBsL%2BSEL8FeVVccJEBGLlR4FgCZXiAcJlaQA0sQJukoMmG1UYMcEYJpUsFQAYMAAoMiCbpWCWPeb%2BapYpeICpbIIoCoOoFVboJMAYHtaYG%2BZYPoHgJECRZAEsBSd/JwC/ICe%2BB9VYJYGYARWtcblgH9RAEsO0BXC4DqOMH4JMEEBKLMIMJMLkNYhkJ4C0DkCkPjTMAMLEJMEjTUDzGjXoFTV0DnGTfXBTVMGMITRMKzb0FjeTRIIjZ%2BesLzehRwLeaQPhbwIRbZdxbxfxYJcJaJa5RALgFJd5UCFwL5X%2BftUsPWK%2BIMAjaQMBZIECG8AAJxAgkiSAQUJDXCwWXDG1C2YWkDYWq1vCXBcCXDIXG3IVu2gVcDXmm2XCi0mWEXEWkUa0AWUU0VBV0UWWMXhWRXEDsVsCcANAsC5gkgvy9RBj9hcDG1vBcDgUSX4BECw16DXWiC3XSCqUPUaXPVxCkA6Xx6ZWGXC3GVVWEXmUECWV3w2Up1p0Z0YTZ25350PDuVESeWhUXAk5mDq3%2BWUXBVj1eVMURUL2hUgC93p1Z3RXG3lF8B0AQqJXJVVXZXpUrXH25X5WFUOArWlVmjlWjImU1V1UNUGwrWtXtWdWPndVFV4B9UmWDXDW/ArXjVVAmXTWzVgjzUbCPlLXYXNWrUxAbWYBbXv33j7V8BHUnVnUXUrVl1KUSCV33XqVPWPm6BVFvXGDWDWDfW/XwAA2JBA0cAg3slg2UOQ3Q0xCw1oi0OVDVDpAo3uDs3o2kCY1FA8240k3CGCPE1JZM1zCU1VDf0CA01SPyO8NKOM3c3M1005y02U0aOiNaNq3LCrAC1GOTUi1i2mUcCzKp3p2Z3kMiVD3gVuVK3F2T2q0z2a2kDa0fyUDN0O1O250QUkh%2B0kjQWSBW2QWB1t2cAh1kVoNUW0X0Wx3MUr1sUcUcAp0OUsAKC5jCW5g51vBei4iF3K0yWl2yA3XKUEOCDV3ENaVAj126VN1C0WNB1mUx1WU93EAsDZO5P5OFPFOJij2HBeXuNAiePh2BXz2jOhVL3x0gB5PZHi4FPG3i5DM/E9N8W73xXxGUCH2Pln2VW/lHMX1FXX1Yy30VUP2YC1X1X7xNW/lv07VQMtVxHf2/1VX/3IAjVAOCAgNTU/XgOQOLXG6wO/lrWIPIM7WoNTOHUkGYOYDnWyg4OVPl3VMyC1NEMmW6CNPkMoCsM2DTXw10MMObALng3WBQ3i0w0yVcP/U8OKN%2BAQCuC6PCM6iyM42kB42SNZBCM8vpCcss303qM9Bssiu1D6P9CGOc3itSvY0U180mPKXN1tMxPWNZP8U5N5M7CrNFNsgJGK1F3VzmAeN%2BVeM%2BO63%2BNYVxC51AhAjXlwWQW4X2skju3RMEWxO2Ch2z1AX%2BDXkm3XnIUIXG2SDG3QVm1cB4ucBAit2etEVh0UXN3iUevi1eu%2BvwPxF8OSBAA)

## Links

- [source code](../../../../conceptrodon/descend/raillivore/classic_trek.hpp)
- [unit test](../../../../tests/unit/metafunctions/raillivore/classic_trek.test.hpp)
