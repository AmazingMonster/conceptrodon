<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::Trip`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-trip">To Index</a></p>

## Description

`Pagelivore::Trip` accepts an operation.
Its first layer accepts another operation for composition.
Then, it returns two commitment functions and twelve continuation functions.

- **Commitment**
  - **Conjuration:** When invoked, this function instantiates the first operation with the arguments and then the second operation with the corresponding member of the result.
  - **Transition:** When invoked by a vessel, this function transports the conjuration function to the vessel.

- **Continuation**

  When invoked by another operation, the function returns a `Trip`
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
   Oper<sub>n-1</sub>&lt;
       &vellip;
   Oper<sub>1</sub>&lt;
   Oper<sub>0</sub>&lt;
       Args...
   >::Member
   >::Member
       &vellip;
   >::Member
   ></code></pre>

## Type Signature

```Haskell
-- Compose with Mold
Trip
 :: template<auto...> class...
 -> template<typename...> class...
 -> ...
 -> Commitment

-- Compose with Page
Trip
 :: template<auto...> class...
 -> template<auto...> class...
 -> ...
 -> Commitment

-- Compose with Road
Trip
 :: template<auto...> class...
 -> template<template<typename...> class...> class...
 -> ...
 -> Commitment

-- Compose with Rail
Trip
 :: template<auto...> class...
 -> template<template<auto...> class...> class...
 -> ...
 -> Commitment

-- Compose with Flow
Trip
 :: template<auto...> class...
 -> template<template<template<typename...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Sail
Trip
 :: template<auto...> class...
 -> template<template<template<auto...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Snow
Trip
 :: template<auto...> class...
 -> template<template<template<template<typename...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Hail
Trip
 :: template<auto...> class...
 -> template<template<template<template<auto...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Cool
Trip
 :: template<auto...> class...
 -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Calm
Trip
 :: template<auto...> class...
 -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Grit
Trip
 :: template<auto...> class...
 -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Will
Trip
 :: template<auto...> class...
 -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment
```

```Haskell
-- End in Conjuration
Trip
 :: Commitment
 -> template<auto...>

-- End in Transition
Trip
 :: Commitment
 -> template<template<template<auto...> class...> class...>
```

## Structure

```C++
template<template<auto...> class>
struct Trip
{
    struct Commit
    {
        template<auto...>
        alias Page = CONJURATION;

        template<template<template<auto...> class...> class>
        alias Sail = TRANSITION;
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

- In the first example, we will compose `OperationA<Shuttle>::Page`, `OperationB<10>::Mold`, and `OperationC<'*'>::Rail`.

```C++
template<auto...>
struct Shuttle;

/**** OperationA ****//* Start */
template<template<auto...> class Sequence>
struct OperationA
{ 
    template<auto...Agreements>
    using Page = Sequence<Agreements...>;
};
/**** OperationA ****//* End */

/**** OperationB ****//* Start */
template<auto Multiplier>
struct OperationB
{
    template<typename>
    struct ProtoMold {};

    template<template<auto...> class Sequence, auto...I>
    struct ProtoMold<Sequence<I...>>
    {
       template<auto...J>
       using Page = Sequence<Multiplier*I..., J...>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};
/**** OperationB ****//* End */

/**** OperationC ****//* Start */
template<auto Variable>
struct OperationC
{
    template<template<auto...> class Sequence>
    struct Detail
    {
        using type = Sequence<Variable>;
    };

    template<template<auto...> class...Agreements>
    using Rail = Detail<Agreements...>::type;
};
/**** OperationC ****//* End */

/**** First Example ****//* Start */
using SupposedResult = Shuttle<10*2, 10*3, '*'>;

using Metafunction = Trip<OperationA<Shuttle>::Page>
::Road<OperationB<10>::Mold>
::Sail<OperationC<'*'>::Rail>
::Commit;

using Result = Metafunction::Page<2, 3>;

static_assert(std::same_as<Result, SupposedResult>);

// The following `static_assert` shows how the operations are composed:
static_assert(std::same_as<
    OperationC<'*'>::Rail<
    OperationB<10>::Mold<
    OperationA<Shuttle>::Page<
        2, 3
    >
    >::Page
    >,
    SupposedResult
>);
/**** First Example ****//* End */
```

- In the second example, we will transport the conjuration function to `InvokePage`.

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

Since every member template of different signatures is given a unique name, we know which member to pull out when asked for a template of a specific signature.
For example, we can compose a `Page` and a `Road` in the following way:

```C++
template<auto...Args>
using Metafunction = Road<Page<Args...>::template Mold>;
```

Note that

- `Road` has signature `template<template<typename...> class...>` and
- `Mold` has signature `template<typename...>`.

This means in terms of signatures, a `Road` can always be invoked by a `Mold`.

We will implement `Trip` by performing recursion manually, meaning the function will recurse only once for every invocation of a member template.
We will showcase a simplified version that handles `Mold` and `Rail`.

Note that in the following code,

- `Radio` is a `Page` and
- `Car` is a `Mold` or `Rail`.

```C++
// `Radio` is a `Page`.
template<template<auto...> class Radio>
struct Trip
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
           // First, we instantiate `Radio` and obtain a `typename`.
           // Then, we invoke `Car` with the resulting `typename`.
           template<auto...Signals>
           using Page = Car<Radio<Signals...>>;
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
       // This is because `Agreements...` will be used to invoke `Trip<*>::ProtoRoad`,
       // which has only one parameter `Car`.
       template<template<typename...> class...Agreements>
       using Road = Trip<Commit::template Page>::template ProtoRoad<Agreements...>;

       // This function composes the conjuration function `Page` and the `Agreements...`.
       // `Agreements` will be used to invoke `Trip<*>::ProtoSail.
       template<template<template<auto...> class...> class...Agreements>
       using Sail = Trip<Commit::template Page>::template ProtoSail<Agreements...>;
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
           using Page = Car<Radio<Signals...>::template Page>;
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
       using Road = Trip<Commit::template Page>::template ProtoRoad<Agreements...>;

       template<template<template<auto...> class...> class...Agreements>
       using Sail = Trip<Commit::template Page>::template ProtoSail<Agreements...>;
       /**** Continuation ****//* End */
    };

    template<template<template<auto...> class...> class...Agreements>
    using Sail = ProtoSail<Agreements...>;
    /**** Define Sail ****//* End */
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwArKSuADJ4DJgAcj4ARpjEEgDs0gAOqAqETgwe3r4BwemZjgLhkTEs8YlcKbaY9iUMQgRMxAS5Pn5BdQ3Zza0EZdFxCcnSCi1tHfndEwNDFVVjAJS2qF7EyOwcAPQ7ANQmAGwaAEpM%2BKjHGvt4CvtMhyfKTMCY1wB0JhoAggSYLFSBn%2BJn8bn%2BgOB7zBTC8RA%2BCNB2H2yAMCnu50uSO%2BPwmxC8Dn2ABViHhUjiTEkrL99rT9jsAFRMhn7AAimBokX2p1QF32zIZexZ/Ta/J2OLp9IO1zcrWut3uj2uAFlPOhPhK6RCgUwQWDtVDQeCAJ6pRisTAIr7%2BZGopjo/ay4jYml0vEEgj7ZTEVBEHkXTW0ynUn6SumM5mO1AsFiENiCfnMoX7EWewWByXuwkeGOEDN04P5sP0gVRhjaDa67KJpnJ1NiothvZPM4XJzywzoFtOjvETAo6NFTBdhAJS2NyXNgBieGIE1I%2BwA7v2InNBHhdf3rpj2ycHgwu6hYi0Ig8WwRTea2BrXcXwwciaOGAvl7cGAA3VAAay3Jx7e8XQgEH2AhR32PsFC8WhHCMc9L2Ya8Ti%2BW87xAgEdT1WU4VQK0hDwYBmFoBQXVDVDaS8TJYJeN5Dn8VlHTlMEdyuME8IIsQFCtbEbVBEMyNpCMmTLCtiCrAQa0FRl9mwA8G1%2BCcCxQu9BJZElDGKasBTrSY03FJTi2bAAJeozWIfYqC8BgHGrfgzNA/s2EqBI0MhTcWyEJg6BvUiyObR87nMyzrPEghRIYBR0jae57IHctK0aQKrIS65qPeACgPWT0Ik/L8ImAW4CAXBSBIOMRaFQQDYIstpRzM1IfS2B1YmNfZfVq/YEHw2qAFoSCwMyLKS7JOOKlyMOhcF0MNfUps3I1YXhREbRRNFOKW21Vq9V5MAANUwdF6hI/j9izT12RPWhRsLfTfIOAB1ftQvUqhnJitA4tEhLBuChgW1S%2BUiD%2B7a9oOy6kNGyUKLykDL1o%2BjUpBuwjX%2Bnj/D4/jKVZXiKRuyUDTmmbXMw/HMIWnD1pW%2B01utDaqatH5gD7AFGAIYieNxukodgjy6DhtlMAuo0GaZ%2BNWa4m0QBAC8zWxjmBNLNTwqycStKkmSu3TG7MdlnzJ1LHNYwIUWJOTdW5J%2BRsVLLGCvDE37VeFHTzeUh9Ovub6ErQQEMn2kCwPekS7cSn6gbeDtZJi65hcwZnBGp7yXf2KJfUehBdX2TB30YP31mAYCo8ZmPRfjvcAvfVoN3wZAF0IVqGFoFqyoqxUTry%2BgHmIYAfBZ5DdfvYk3YVfZ4lECjf1%2BQvY7FxF0toWhh/7Meu0B7Lv3HkkySNBkkUl71fVQf11ROUhLYORdOuQYC0/uAQG7r/tUlaC1/jMmU5XBm6SYmr%2BjWlq9LQpnadE9NJ7FyOsWLm%2BVD58w3uSMEBtCCSy/ltMOEspazX%2BF6H0fpeTqjBNHKe8dUYhlPgPAKHtqxeyHNFf2AhA5fSCslZ421w7LzAgXEWLMS4aF7onDhRcuHykAnPBe%2Bwl4gVQG%2BHK69SRwLcNvNBe8iA81oLw4sP9CbjV/hgiaZNxa02AYA1aIDOFx3AWGSBKZPLz1BPRWBRoEEECQTolB0JsDOKJv2JRqAVFC1AVw/ROtlL61kBEW2CUHbSVkprXW2s0Y411hoyanjf7wQtPoymhiPgELAezXWljoG2KwfvQ%2BfjTHTxpkE8MpZ2Scn7NAyJZsYkZitrUiI/YVEmykvWGJk5XbkMYdWAKMVMixgMHZdhzxsEH1wfKLAdSuxMFiKgLOaiSr7AAJKejTgeegND%2ByiCUEuWq49/w3ACkqE45wvIf0STo7RKTNHTSwotGmmSiEGPuD2PJmZQoemKco6xGZrp93lpGRxxtIk9L0qCk6fzszRkNo2EFx0rYeA%2BkHKFTten8SSXohEbFCJs2wKNSxqU%2BbfLcMxI0hKOL6I8eNVx3F0a%2BRCRiiJSY1bRJhaNK2isNIq05Y7AYztcX3KeQTZJWiYTYQyUAj57zXGI0Oj8/ip1%2BaCzlocKkENyKUXyn/PmCN9pIzBCjEl8StVxJIVqpJdrxUvPJm8%2BVcrjEIhyYI1VZFLGdKKedIF%2BD/Fx3pVLS8VTWWRn5cre2QqokaxhXea1lsQm5iNizLpLImk8pumi0JDBwmaVjdCxs9rHkmjNAhABzq3XZKDazcxkN9XclwTA2RDjEWIPQZ4plaDkHeNKYG8pHydYlodaW6VjrXV0yMdO2tQ6G2cybb6uixI23wI7U4rtjLzUMqhACnxAa3AeuDetcNetwV5oLYK2sXL43AqSFjS1FsULjueXi2VM6slIneSYgRZivViKXdYo10zfGDr/RU5lLSakcnaVY3mjTuUUgfSO34KkBQYdrDiPl%2B1WYm2w5hwjWH5LyTMP4CIqIvBYFom4OEdBCDGhIjid9rySLqqEAgOEBB6CoZ%2BFbAA8qZO2oYsUipia%2ByV%2BLq1UxTJgAAjl4RgWw2Pws9IJhIwnkMWEOC%2Bh1Unj31oA2S7afMhDycU1ZCaBnh1PqTWh0s6nPrZBE7GrNCSBNCcaNp0TopxN6ewvsZUUFHBAjwAkFT%2BJCSObtiQnVumy1/0rQ29V3jVS0C7IWFDtn4sTpY06798rZMKaU5gBcUmNnJdU/utLeC3BmeK5Zo0GzAkAZReo/zryABSC69XQ3JUU%2BrFnlNgiC9BMktAwvEAZM1hEC5OstZZdqx9Nq7kJbSWwX9hCG2WJqyB/eNWykQZs7F5bBHIzRa8xmuN5sztCQu9kNwV3i2/Dy/sHaFclk8byeq%2B7Ag3BaYzBJ0mH7pMOkGyVyrkWzoCyBShNrECm2GoG%2BZiHYJ3ukk%2B24s9dnn2rdyx1/Ly0XXurrcSjMBTgN%2Bph15cDhCQ1/xHVlkMHmNONEe4hu9JG%2BOlhnHOT02BVCsCBP2HzukcQ%2Bq8KkIc6BTj7WC6ZzjBBuMTS4BoBkZgFyq4ZP4BcYAOAMj11BrnO2YcUPEkU%2BxYJfsMAtqxRXyud4gHNTiSWA63DW6sGCVXjuDt5MlmB93nmHtGj1wbjgjvrmXT9yARxvGCly%2BgnzZUpvBnOCdywsEGv9j%2BCN7juYjhkAAH0qYJAIBACY6BJYKAtMXtmVKE%2BFRTJL6XsvILQSRMsXjfkwL8DnhVaG1x894CLyXto8oFAIGbh1Cqft%2ByoCDwIRUfYBzeyUJXnEQ%2BR8HTaOXggleQDV7YLXo0GZrf/bBKHw3aDI8n5Qh7o03u0G%2B/%2B3fhfNuaX26%2B%2B49PqCX%2Bwv2FnjnnDq1ooiwsAdgCfChEIM3j7DLg3hSDaJ3k%2BlbLzhMNJILpCCLq5khlzlbGZu9F2ALkLu3KLubEDroiDgVptKlD8J3BFv8hsh%2BGvJHv6l5PJHFvkojrDEUjQXQZnguDnsQshqdlzuQfNJQUTjWrQcAGTr8JYowdIpHnzAocwdYqwVHkep3B8kgmGtlj8PHm3gQIXlwEninkNGngHioT%2BDfkIVzpvrXkoDvhXlXjXvaEaK3sFsYQuNAVLrAR4e3ogTrHgZgAQegcQVgTepmtyhwKsLQJwIELwH4BwFoKQKgJwP9pYNYCdOsJsFuGRjwKQE4skTEasF%2BCAIEJIB8BoJIDUP4BoIEBoGYEcEcGYAABytH6CcCSC8AsASAaAaCkBJEpFpEcC8AKAgADFFFaCrBwCwAwCIAgCZSpBwjkCUBUJ0AJBRAWicCqCtFHDdRHCSD7DADIDID7BSAfBmC8DDiEAkB4CV5cAyCCAiBiDsBSBPHyBKBqCaA6B6CLiiSpCcA8CxHxGJE/GpGcD8ZwjLGeioBUD7C7H7GHHHGnHnGVFmD7AQA5ipAbGvz5HLC8BTExGkAQBIDrH0BkAUAQDkmjDABSAa40DQQJDjEQCxDgmxARCtDGhAm8AcnMDEDGj8axDaAhFFEFFeyiz8b1zcnFGkBYCxBeDACyhzzjHcC8BYAsCGDADiCyn4B9jWRZyqkpGYCqAhFwjbAFERD/BxGykTaxCiQCkeBYDgmhR4C9FqmkBZzEDLJKDsialGATZGA/GrBUAGAyE7RhaLjqZJEFH8DPGiDiDvFxmfEqDqCym6CPEGBBmmCZGWD6B4CxDjGQCrDz6NCqndQV62I5lWCWBmDDFemkhYBFkQCrB2CinZAuAHjTB%2BCPFhDtKLCjCPFFDRrdl6DDmNALAjDVA9DtkCCpijmPFtk/SpiTlOTTlzBTCeCdB6AbmDD9lTkSCtk5FbCHmdEcAJGDHgkjEIl7EHFHEnFnEXEYkQC4C3F4n%2BBcAEmFHBmrCjgXCjAtmkBlGSD%2BAfAACc/gKQ1RZgkgJw9RRwYFZ53RpAvRH5HwRwXARwrRYFrRmFFRXAgQEFRwl5spIxYxEx35xRMx8xpJix0JKxVJNJxAWxbAnArQLA74SQ3UjwdosEXAYFHwXAVR1x%2BARAjZegyZLxiZ0gyZigqZ4JugGu/xTAgJapIJ55YJpFkJ9FsJ8J7FnF3FlMfFAlQlNwWJg4uJhwZGZgX5RJMxZJFlFJqx1Jjlow%2BlXFvFdJYFqufAdAL8LJbJspfJXJPJpAwVApQpIpDgoVEpLMUpDc4J8pipypREoVGpWpOpKRep7Zhp4JJpZp/woVVp9Q4JdpDpxoTp2wKRrp7pBRXpPpmAfpGVeUwZfAYZCgEZmAUZFaoVklCZbxMlsgcl3x6ZIAGuWZxg1g1g%2BZhZ8AJZqQZZnAFZe%2BVZU1tZ9ZCQjZ%2B0c1M5P0nZ7gW5%2BQvZB4q5SwQ5GQI5h1PZpA452Qp1g5u1jQ85V1O59Qs5TQOk9165OkC5tgn1%2B5a5p5Cgx5bx6lF5QxvA157lhlnl5xJlVRmJr5YlVlH5tlP5pAf5/UlA6lyFqFAl1RSQhFSQSQ/gkgMFhxjxENEJoxtgFFdlJJNFSASxDFaxrlzF2xHA7FyJLACg74Zx74/FHwUIEwIlb59xElsgUlA1Hxw1aZKRugOuylqlwJZ54NV52lBAMJrUelxALA3NvN/Ngtwtno5lgIll5g/g/gaNVFJJDlZtTljFbNIAfNUuheAtYFhextxeuthxvlTJc4lAgVKR4VMpBRIdkVopMViKcV0piVmACpSpZUqpBR6VAZVV6ps4OV21sp%2BVyA5pRVggJVtpBZ5VlVLppItVvA9VPsTVAZLVNtoZrwHVkZ0ZvVkt/VEgg1ggstClAQ%2BgWpKAa1NgdpzZ81i1uwzh1Z1gdZkNDZ9x21xZj1HZEArgv1fZ5QB551AqOQL1W90aX1r1vQc5P1u9S9x98wANZ1f1Awv1u5B9n5awGwJ5D9NpatWlHAHcetRxPNfN%2Bw7tQtm4aBL5olJAKNn5hJ6NmNAFONPRY1AlltgQDRNR/RltSQWFJFwxnA5Fkx6NwFgQ4FgQrRTRYFkgYFJNkFXAOuNp/gmlmDNNdl6lVxGDkNWDlF0xqwXpmQzgkgQAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/pagelivore/trip.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/trip.test.hpp)
