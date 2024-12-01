<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::Trek`

<p style='text-align: right;'><a href="../../../index.md#higher-order-modifications-2">To Index</a></p>

## Description

`Pagelivore::Trek` accepts an operation.
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
   >)
   >)
       &vellip;
   >)
   ></code></pre>

## Type Signature

This function has multiple signatures.

```Haskell
-- End in Conjuration
-- Compose with Mold
Trek ::   template<auto...> class...
       -> template<typename...> class...
       -> ...
       -> template<auto...> class

-- Compose with Page
Trek ::   template<auto...> class...
       -> template<auto...> class...
       -> ...
       -> template<auto...> class

-- Compose with Road
Trek ::   template<auto...> class...
       -> template<template<typename...> class...> class...
       -> ...
       -> template<auto...> class

-- Compose with Rail
Trek ::   template<auto...> class...
       -> template<template<auto...> class...> class...
       -> ...
       -> template<auto...> class

-- Compose with Flow
Trek ::   template<auto...> class...
       -> template<template<template<typename...> class...> class...> class...
       -> ...
       -> template<auto...> class

-- Compose with Sail
Trek ::   template<auto...> class...
       -> template<template<template<auto...> class...> class...> class...
       -> ...
       -> template<auto...> class

-- Compose with Snow
Trek ::   template<auto...> class...
       -> template<template<template<template<typename...> class...> class...> class...> class...
       -> ...
       -> template<auto...> class

-- Compose with Hail
Trek ::   template<auto...> class...
       -> template<template<template<template<auto...> class...> class...> class...> class...
       -> ...
       -> template<auto...> class

-- Compose with Cool
Trek ::   template<auto...> class...
       -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
       -> ...
       -> template<auto...> class

-- Compose with Calm
Trek ::   template<auto...> class...
       -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
       -> ...
       -> template<auto...> class

-- Compose with Grit
Trek ::   template<auto...> class...
       -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
       -> ...
       -> template<auto...> class

-- Compose with Will
Trek ::   template<auto...> class...
       -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
       -> ...
       -> template<auto...> class

-- End in Transition
-- Compose with Mold
Trek ::   template<auto...> class...
       -> template<typename...> class...
       -> ...
       -> template<template<template<auto...> class...> class...>

-- Compose with Page
Trek ::   template<auto...> class...
       -> template<auto...> class...
       -> ...
       -> template<template<template<auto...> class...> class...>

-- Compose with Road
Trek ::   template<auto...> class...
       -> template<template<typename...> class...> class...
       -> ...
       -> template<template<template<auto...> class...> class...>

-- Compose with Rail
Trek ::   template<auto...> class...
       -> template<template<auto...> class...> class...
       -> ...
       -> template<template<template<auto...> class...> class...>

-- Compose with Flow
Trek ::   template<auto...> class...
       -> template<template<template<typename...> class...> class...> class...
       -> ...
       -> template<template<template<auto...> class...> class...>

-- Compose with Sail
Trek ::   template<auto...> class...
       -> template<template<template<auto...> class...> class...> class...
       -> ...
       -> template<template<template<auto...> class...> class...>

-- Compose with Snow
Trek ::   template<auto...> class...
       -> template<template<template<template<typename...> class...> class...> class...> class...
       -> ...
       -> template<template<template<auto...> class...> class...>

-- Compose with Hail
Trek ::   template<auto...> class...
       -> template<template<template<template<auto...> class...> class...> class...> class...
       -> ...
       -> template<template<template<auto...> class...> class...>

-- Compose with Cool
Trek ::   template<auto...> class...
       -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<template<auto...> class...> class...>

-- Compose with Calm
Trek ::   template<auto...> class...
       -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<template<auto...> class...> class...>

-- Compose with Grit
Trek ::   template<auto...> class...
       -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<template<auto...> class...> class...>

-- Compose with Will
Trek ::   template<auto...> class...
       -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<template<auto...> class...> class...>
```

## Structure

```C++
template<template<auto...> class>
struct Trep
{
    struct Commit
    {
        template<auto...>
        alias Page = CONJURATION;

        template<template<template<auto...> class...> class>
        alias Sail = TRANSITION;

        template<template<template<auto...> class...> class>
        alias UniSail = TRANSITION;
    };

// Compose with Mold
    template<template<typename...> class>
    alias Road = RECURSION;

// Compose with Page
    template<template<auto...> class>
    alias Rail = RECURSION;

// Compose with Road
    template<template<template<typename...> class...> class>
    alias Flow = RECURSION;

// Compose with Rail
    template<template<template<auto...> class...> class>
    alias Sail = RECURSION;

// Compose with Flow
    template<template<template<template<typename...> class...> class...> class>
    alias Snow = RECURSION;

// Compose with Sail
    template<template<template<template<auto...> class...> class...> class>
    alias Hail = RECURSION;

// Compose with Snow
    template<template<template<template<template<typename...> class...> class...> class...> class>
    alias Cool = RECURSION;

// Compose with Hail
    template<template<template<template<template<auto...> class...> class...> class...> class>
    alias Calm = RECURSION;

// Compose with Cool
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class>
    alias Grit = RECURSION;

// Compose with Calm
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class>
    alias Will = RECURSION;

// Compose with Grit
    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class>
    alias Glow = RECURSION;

// Compose with Will
    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class>
    alias Dawn = RECURSION;
};
```

## Examples

We will see two examples that demonstrate conjuration and transition.

- In the first example, we will compose `OperationA<Shuttle>::Rail`, `OperationB<10>::Mold`, and `OperationC<'*'>::Rail`.

```C++
template<auto...>
struct Shuttle;

template<typename...>
struct Capsule;

template<template<auto...> class...>
struct Carrier;

/**** OperationA ****//* Start */
template<template<auto...> class Sequence>
struct OperationA
{ 
    template<auto...Variable>
    struct Detail
    {
        using type = Capsule<Sequence<Variable>...>;
    };

    template<auto...Agreements>
    using Page = Detail<Agreements...>::type;
};
/**** OperationA ****//* End */

/**** OperationB ****//* Start */
template<auto Multiplier>
struct OperationB
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
    using Mold = Carrier<Detail<Agreements>::template Page...>;
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
using SupposedResult = Capsule<Shuttle<10*2, '*'>, Shuttle<10*3, '*'>>;

using Metafunction = Trek<OperationA<Shuttle>::Page>
::Road<OperationB<10>::Mold>
::Sail<OperationC<'*'>::Rail>
::Commit;

using Result = Metafunction::Page<2, 3>;

static_assert(std::same_as<Result, SupposedResult>);

// The following `static_assert` shows how the operations are composed:
static_assert(std::same_as<
    Send
    <
        Send<OperationA<Shuttle>::Page<2, 3>>
        ::Road<OperationB<10>::Mold>
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
template<template<auto...> class PageArg>
struct InvokePageDetail
{
    using type = PageArg<2, 3>;
};

template<template<auto...> class...Args>
using InvokePage = InvokePageDetail<Args...>::type;

using Result_1 = Metafunction::Sail<InvokePage>;

static_assert(std::same_as<Result_1, SupposedResult>);
/**** Second Example ****//* End */
```

## Implementation

We will compose functions using `Omennivore::Send`.
For example, we can compose a `Page` and a `Road` in the following way:

```C++
template<auto...Args>
using Metafunction = Send<Page<Args...>>::template Flow<Road>;
```

Note that in order to succeed, `Page<Args...>` must be a packed `Road`, meaning it is of the form `Vessel<Items...>` where `Items...` all have signature `template<typename...>`. This requirement is not checked by `Trek`.

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

- `Radio` is a `Page` and
- `Car` is a `Mold` or `Rail`.

Here is the entire implementation.

```C++
// `Radio` is a `Page`.
template<template<auto...> class Radio>
struct Trek
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
           template<auto...Signals>
           using Page = Send<Radio<Signals...>>::template Road<Car>;
           /**** Conjuration ****//* End */

           
           /**** Transition ****//* Start */
           // Helper function for the member template `Sail`.
           // This function transports the conjuration function `Page` without invoking it, 
           // allowing further process by other higher-order functions.
           template<template<template<auto...> class...> class PageVessel>
           struct Detail
           {
               // We transfer the conjuration function `Page` to `PageVessel`.
               using type = PageVessel<Page>;
           };

           template<template<template<auto...> class...> class...Agreements>
           using Sail = Detail<Agreements...>::type;
           /**** Transition ****//* End */
       };
       /**** Commitment ****//* End */

       /**** Continuation ****//* Start */
       // This function composes the conjuration function `Page` and the `Agreements...`.
       // Note that even though `Agreements...` is variadic, it only allows a single argument.
       // This is because `Agreements...` will be used to invoke `Trek<*>::ProtoRoad`,
       // which has only one parameter `Car`.
       template<template<typename...> class...Agreements>
       using Road = Trek<Commit::template Page>::template ProtoRoad<Agreements...>;

       // This function composes the conjuration function `Page` and the `Agreements...`.
       // `Agreements` will be used to invoke `Trek<*>::ProtoSail.
       template<template<template<auto...> class...> class...Agreements>
       using Sail = Trek<Commit::template Page>::template ProtoSail<Agreements...>;
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
           template<auto...Signals>
           using Page = Send<Radio<Signals...>>::template Sail<Car>;
           /**** Conjuration ****//* End */

           /**** Transition ****//* Start */
           template<template<template<auto...> class...> class PageVessel>
           struct Detail
           {
              using type = PageVessel<Page>;
           };

           template<template<template<auto...> class...> class...Agreements>
           using Sail = Detail<Agreements...>::type;
           /**** Transition ****//* End */
       };
       /**** Commitment ****//* End */

       /**** Continuation ****//* Start */
       template<template<typename...> class...Agreements>
       using Road = Trek<Commit::template Page>::template ProtoRoad<Agreements...>;

       template<template<template<auto...> class...> class...Agreements>
       using Sail = Trek<Commit::template Page>::template ProtoSail<Agreements...>;
       /**** Continuation ****//* End */
    };

    template<template<template<auto...> class...> class...Agreements>
    using Sail = ProtoSail<Agreements...>;
    /**** Define Sail ****//* End */
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwAbKSuADJ4DJgAcj4ARpjEIMEADqgKhE4MHt6%2BASlpGQLhkTEs8YnBdpgOmUIETMQE2T5%2BQbaY9o4CdQ0ExdFxCUm29Y3NuW0Ko30RA2VDgQCUtqhexMjsHAD0WwDUQngsybR4NJjouyaBGkKuVxq7VF4MNQIAdCYaAIIEmEcGvxM/jcBAAnslGKxMLtlExkABrc4ANUwCjsQOwny%2BU2IXgc%2B1clwA7FYiQARIFWb5Y37/JiA4G0470zBAkHgyFsN7cjG7ZAGNG7DyCJizMi7MEQ5hc7nYehsQQKDFYnF4ggEhjoNnC%2Bpitlyv6MAgKbkffyY81YkwkrG7O0Sv7Mhkgx0A1mMjnSzCm3n8piCgDyEOI9Myyu%2B9t2qvxZMwutotvtO12AEkGAA3VCIy7XIMJUMCe67ADuhAQEoQ0PuBoVxp91w%2BEft1osuy86SMEo5l38ZN2eZDXQY%2BvlRpNPMt/lb1opU6tTbtTLdbKXLJXnqhPvNfIF47eX2AxEwhsV4a%2BkfbEWAuwASqgmBcgX3Y/G2Qejye6xPsCAQJL3VSXwzpS84/K6a6MuBzqrs6TBeEQW7YDu/p7r6u77EQCLEKgqAsKQDp0rB8GoIhyFoqatwAI5eIwGxKpa3zRuqtyamydSoFhOEsGxmDUbRqKIWeLaJouUHui6hHiTB4lwQh35kah25%2BoGwYFsODHnvaTG7C%2BooJguuzJmmmbZvcA5qUWpYEOW1lVtcVE0S8Ak8g2InEq2l6dv%2BPZ9uZQ48XxTmKRa07kiB1IGdJK5idFklsrJJHycpwUKaa77HrW9GYgZnnXkIek%2BTpcZ6W%2Bh4ZWOiG/v%2B4VAWFc4RUB3zJvcN4Pk4RZ4AouxMDmGiwsArKud8UWQXFwIJaRyW3m1qBntpAAqR7wlaNoGVsABUm3rUVNCRLe94XFt607NtPSNLsx1uc11xuA0HVdT19wALKeFqQ2aaJY0SU6UkbjKZpIVNt3EGekbaco2FEHeD5ucJBlJkdQq4SwhC1hdW0nRhvQXVsblaQQuL4h4LAowQeN2nDH2RpGG1bUjDDaGsano5tmNneql3w9Thl7C1M1FoYj43Xd1zdUefK4akSgXJWR6NlT3MET98XERReDAMwtBZeT1O5TCTADYVLFasCrX4LNwIHBrYjBRiVViftMPAsDyr1Qr3O05t9OM4OmQs8dG27Ngmo46BiuRjrNOI4thjpEO/ts9Modc9TyYABIdMGjzPK8DCPCQFbQmw8zEErbq9fldD3PL4dJns80IJ12cvPHBOx6kjRdbZEsM0z8dPC3fv3P1g0PFZCCrOqEQmVeuyEPhkd191tC0Kgpadk8jSy7syTYXRXWxKCuyoLZpeN8AssALQkFgpcD7nJqL59yujS/33LuNqtJbuk3oSPKJog6KDWuUYCZqiKq%2BFOEdVru1rsmAA6tCNuDAFBUASIXHuPtmb33jsPA2o8JSoF6v/VE6J3ogN1h2a83knz6wGgA9EwIR6u0AhQ4Cbsn5lwgu/bhI1bpfwBqlb%2BKE0plU/NrKB9o9aV1oIVXSVdgTpXEZVP8HIaoUM9ttGOKDCh5yOpjYOh1cYp3Yawj2iNiakzRvowOhjk6NVgZo%2BmjgGBeGZjY06SdOaOPro3LqOC/ZoCOGkVEGC0C919gIZuudiH4IFiHbu9wlGZXrBoGuHs9hRBPkghA9JdiYHTIwCsqwL69WSRVFyDwm7pgaHgNqyB8KEGPgwWgR8xCr2LA9KMV56Bi2AD4I06TU6%2BKbk3eIoh2x2W%2BGIlJlSSx0FkfENs0tCFzwzFmKZi1MDLWBOtO2IAIYn1QNDN6GhSA62TMWRuyByy5K6gIVpzToTJAaFCX4pd7gu3IdzPhvy/remEeRbk5TTwaUVnrE5hUtk7LcJYwg9tJJ0PdD%2BP8DtDlQwOqVD8syAY1QuSM/xOd45BKlqE7u4SsH9yJUPa4zDRaCwwUkmZFSPjfOGWU5lp5RalhXrsJZkyLhEDWSZTZS02R7PNL%2BdFqAZFDMjL8mKr8P78LkoI5Kv8RHAs5caYBlDZ4yKhWK52yN4WosRcwyVZqfowkhjKkqijtW2zdorJxOoIhuPjh4oOIdvHQNnIBNyCqvr/i9BqoF%2B5HW6uWbPSFtDpUnKxeVRUglnUIzprGXa0JIVersd4q6iMM2zH2AVL17N7E0wJdE%2BOTdu7pBRgYUuiTaW2oTaLLAmaLhMFiKgQpcqjLqlyZqegXdKx8n9NCK5CQplfKqV0vmVc2VcOgoqnhRFVVoU1Wq9CLswX40JuqaVMjYYwJdRYk1BBrEY0DmW313NtJwrJiYk9IDXUCEpX7UtXjjGwPlSuia3IraawkT%2BqRVCkVGzuKbfmlt1ZAZTSi6SxaFGwrupOMxcCz0RPcVe7aubv2cKcdouOH6cNY3Ore2uQa358P/VuzdG7BQkMAQmXdtdtLyP0iBimz6KHRq8t2ON%2BCGFAKYXEtDnDTFhxAVR5VNGBEMZSuqrV2KxxRvBWBg1tCOOJuUd%2BKqajU0YbpkR3RCdbE%2Bu/YrSTKdX0k1RkaMzuGLNSdTphlxHqSOs2vV%2BnWMneH/LDXuEFOrWMXjA7G3suxoXanPQi61FqENopbZih1Knk3fjxSnPzy6vq0YU4F0RaWQvZVgdIgqtDovGrswQOL5cEu1ZZDao5R7UtJq/LiwzUc6ZutcdhrzTmjHHv9S5pdUkV1yfXUpH%2BgKguRtC2VughVD32rcMFp16HDIFswJmpDsic3OepHVANTUjqnbO9%2BwjqJjQJyxJos7p38PUjMP4CI/IvBYB7G4eCdBCCgiEsNP98mNLaSEAgeCBB6CZbAsGgLGXGJgKJkwZICgvCQ44QD4NgPJuA2m7i%2BH%2B6hQNGIHgBIUOnF%2BUyOeT92NvHZZkkDnHKECSBQ2HNBH6oKcCAcS2S4kUseJTeEiWpXa0clbBuziBJUDKU3DnrGhkXbrI9R%2BJBy/E2RC%2BJyL5FKaNvWYcb%2B3LAi1tRr1iPORxVkNrZUdVDhR3buI05wwKnpG8OgXJ6pIcrZqfke/RNohT1UeOGOCTkGwOJeO4DTx0b64pSbjh1TdjFvZHCTtw1A31H%2BeBeZ45DY%2BFaMpijYn18lteI5/EimeDx6Nv2j96aAAUmpu0pv8EQZZ%2BJAPtAg8nASOtCv3J8J1510NqH6fZOw4jUV4DYXZ4vVoI%2BBXROQ9sm0618R%2BzEMjyH4d4bJ26YR8c96wbDV3f5iHG4A/N7ff892BrupsRRcqnDx7zIbgVobbpyrbHQi3iq6CoXiX2m0uUe0%2B/GEIhUiuKOaObgv%2BdE6uwu9%2B2uGWnWeuga42meM2hWbWU%2BoGMa5WkWK%2Bq2jq1uBmkeO%2BXwJ%2BkSWQB%2Brux%2BiMAAYngMQFMEHKoKwMcNCN7hzN%2BtIl4MkKSugDeKiIHuAUjpASrmDgQBDuJFwBoOtGYPhGABwOtIoRiPhKDuDlATIetP4AoUoSoZOCFKBHrE9MVAElEhVkam4I7kBJbBIVIfsglliL%2BAmsCBHmyDIfsrPibCVr%2BC1lYc/gIK/sCIocoRwPsq1Aoj4SAA%2BlDhCkIZ3oVCYfUGYX4AcmJm4PIbsP4CwqBFMKGMgAAPooQJAEAQBTDoC/gKBQhFH0RuCCGQEEBqG8H8H1GB4YiLBk6%2BLQj8Arxryzz3B5GOCFHFGNBFgKATydK7ATEYKoABEoJizQgkohIVGP75E1FKCNBlEEAVEgBVFsA1FshuTGywzAiRzHGuFzE2HQF2Gi5SrpGZHZEGGRzOEpb%2BGn6ZBWDAgeGWpeFRpRq%2BEraO5BFuAhH6EooREsZi72jnIGRCDNHLGtGd5WjmgdFuxOIMFMHqjYCsH/AcEu4HYOJOK3DhIXDYlsG9KcH2If6fxf5TQjxfDEDABs4E7GQbIjyAG1QbZy4CaRb0mMlsgPE5Hb5Q7UkqoC75bAqMnAZ6ysmIhm60KykqD4IEEMnADBT6YQixHhbxEEAFFcCJGmHUrOAgB%2BGKmOHo7Yj1BDHrElFbE7F7GYAHGmw6l6lNF8EIk6ntE1REnVACCkk4nsHUEWYcDLC0CcAACsvAfgHAWgpAqAnAr%2Blg1gUYqw6wVYz2PApANWMZIZyw8IIA4ZkgbwGgkgXARI/gGg4ZGgZggQgQZgAAHPWfoJwJILwCwBIBoGctGbGfGRwLwAoCAGctmVoMsHALADAIgCAJPMkPBOQJQCSnQAkFEFCJwKoPWYEJfIEJILsMAMgMgLsFIG8GYLwOcIQCQHgBUVwDIIICIGIOwFINefIEoGoJoDoHoMWCGMkJwDwKGRGVGa%2BXGZwAGPBDOeqKgFQLsGuRuVuTuXuQeUWWYLsBAMTMkIuR8hmYsLwMOSGaQBAEgAufQGQBQBAARUMMAFIPITQJ3gkAORALEABbEBEA0KCN%2BbwIxcwMQKCAGLENoNUNmZmUErWAGC0ixTmaQFgLEF4MALdCvAOdwLwFgCwIYMAOIGJfgEeDUIUnJbGZgKoNUPBJsJmREL8GGWJScLECGJxR4FgABQTIcKxaQIUsQN2koLGEpUYCcEYK%2BcsFQAYGqUiCTsWHmNGZmfwDeaIOIA%2BWFU%2BSoOoGJboFeQYF5aYEmZYPoHgLEAOZAMsLMUOHJZfOUU%2BClVYJYGYD2U5cTlgFlRAMsFULnC4JqOMH4FeWELMKUOUHoFLLok1Z1QUEOP0O1UMFeXVUOOzD1cNR0HxbUNMANYMIkMNdMONSML0LNSXBILVamRsOtc2RwJGaQN2bwL2ZBeuZudubufuYeYhRALgGeehf4FwJhVmd5csJWA%2BEMDVaQPmZIP4G8AAJz%2BBEiSAllmCSDXCVmBC/U7WtmkDtn3VvCBBcCBD1m/X1mI2FlcDhn/XBAHWAV9m2CDlPU5mjkTl4VTkgWznEWkXEDLlsCcANAsDphEiXw9R%2BidhcC/VvBcDFknn4BECVV6DRW3mRXSDRWKCxUAW6DyEflI6sW/m7X/liW9nAUECgXHwQX02M3M3IRs0c1c0PDIWSxoWXDPZmCPXYWjn4WG2EVzkkVW1DAa1M2s3kW/UyF8B0DvK0X0ViXsXMUOU%2B2cXcW8UOAOWCVGjCWtIAUSVSUyVawOWKXKWqWxnqVTVaUAW6X6W/AOXGUdAAXmWWWgjWWbCxl2XtnyWOUJAuWYBuUJ1XjeV8B%2BUKABWYBBVSgOWC0RX3ki2yBi0vnxUgDyFJXGDWDWDpWZXwA5XJB5WcAFXbFFXD2lXlUJCVWojj3tCdCZANXuCeAtB6CtUlBzW9XEaBHb25BXldX9VtUH0TXr3dCLUn3NVr1TW30rWX1rULW9BLV5GNCrUdUPUrBrBbV/2mV7U41HUO1a1O0Hm63FlIU3V83G33Vm3PWkCvW3yUBy3Q2w0c0llEiY1EjlmSAg1blXmgOcD9kE3m24Uk1IDTkU3zl23U0rkcD00wUsAKDpj7npjs1vBuhTA823UXkC2yBC2d2Pk91xWxm6A6HS1fnyVy0gMAVK3k1gXq3EAsCsPsOcPcO8PqgG1HBG3mD%2BD%2BBINE24WW36PW2U0MMgAcN8EFFcO/UFE6NFFqNblu3UVMGUBe2xn%2B2iWZm%2BOB18Uh3Ixh0iWR2YCSXSXtJyWZnx0eVF0KWMEp0r1iXp3IAGVZ2CA51mUZX52F22XE6l2ZlOWV3V0eW12mO%2BUGyN2BXBVt3CMd0SBd2CDiMS0BD6DKUoDz02DmXVUT1T3bDlFdOpUWBlWHUVUXkr3ZWP31UQCuBLV71zC/2kDn0v732H26I/1DUzOjV305AP0jXTUv371v3LVjDrPv3f2v2/0bUAP3nyMK09mcBizqPblsMcO7AOM8MsjMHXW80FyGMPVYXIOoPvUYNtn90c1GPhlVmlmdlGNEhI37WKNkP41DnINfXhl/Xhn1k1m/WSC/XlkA1cA6GmX%2BCPOHWovm1y3HnIuK1UvINOXpDOCSBAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/pagelivore/trek.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/trek.test.hpp)
