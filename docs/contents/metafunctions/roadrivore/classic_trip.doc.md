<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Roadrivore::ClassicTrip`

<p style='text-align: right;'><a href="../../../index.md#higher-order-modifications-4">To Index</a></p>

## Description

`Roadrivore::ClassicTrip` accepts an operation.
Its first layer accepts another operation for composition.
Then, it returns two commitment functions and twelve continuation functions.

- **Commitment**
  - **Conjuration:** When invoked, this function instantiates the first operation with the arguments and then the second operation with the corresponding member of the result.
  - **Transition:** When invoked by a vessel, this function transports the conjuration function to the vessel.

- **Continuation**

  When invoked by another operation, the function returns a `ClassicTrip`
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
   Operation<sub>n-1</sub>&lt;
       &vellip;
   Operation<sub>1</sub>&lt;
   Operation<sub>0</sub>&lt;
       Arguments...
   >::Member
   >::Member
       &vellip;
   >::Member
   ></code></pre>

## Type Signature

This function has multiple signatures.

```Haskell
-- End in Conjuration
ClassicTrip ::   template<template<typename...> class...> class... 
              -> template<typename...> class...
              -> ...
              -> template<template<typename...> class...>
       
ClassicTrip ::   template<template<typename...> class...> class... 
              -> template<auto...> class...
              -> ...
              -> template<template<typename...> class...>
       
ClassicTrip ::   template<template<typename...> class...> class... 
              -> template<template<typename...> class...> class...
              -> ...
              -> template<template<typename...> class...>
       
ClassicTrip ::   template<template<typename...> class...> class... 
              -> template<template<auto...> class...> class...
              -> ...
              -> template<template<typename...> class...>
       
ClassicTrip ::   template<template<typename...> class...> class... 
              -> template<template<template<typename...> class...> class...> class...
              -> ...
              -> template<template<typename...> class...>
       
ClassicTrip ::   template<template<typename...> class...> class... 
              -> template<template<template<auto...> class...> class...> class...
              -> ...
              -> template<template<typename...> class...>
       
ClassicTrip ::   template<template<typename...> class...> class... 
              -> template<template<template<template<typename...> class...> class...> class...> class...
              -> ...
              -> template<template<typename...> class...>
       
ClassicTrip ::   template<template<typename...> class...> class... 
              -> template<template<template<template<auto...> class...> class...> class...> class...
              -> ...
              -> template<template<typename...> class...>
       
ClassicTrip ::   template<template<typename...> class...> class... 
              -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
              -> ...
              -> template<template<typename...> class...>
       
ClassicTrip ::   template<template<typename...> class...> class... 
              -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
              -> ...
              -> template<template<typename...> class...>
       
ClassicTrip ::   template<template<typename...> class...> class... 
              -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
              -> ...
              -> template<template<typename...> class...>
       
ClassicTrip ::   template<template<typename...> class...> class... 
              -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
              -> ...
              -> template<template<typename...> class...>

-- End in Transition
ClassicTrip ::   template<template<typename...> class...> class... 
              -> template<typename...> class...
              -> ...
              -> template<template<template<template<typename...> class...> class...> class...>
       
ClassicTrip ::   template<template<typename...> class...> class... 
              -> template<auto...> class...
              -> ...
              -> template<template<template<template<typename...> class...> class...> class...>
       
ClassicTrip ::   template<template<typename...> class...> class... 
              -> template<template<typename...> class...> class...
              -> ...
              -> template<template<template<template<typename...> class...> class...> class...>
       
ClassicTrip ::   template<template<typename...> class...> class... 
              -> template<template<auto...> class...> class...
              -> ...
              -> template<template<template<template<typename...> class...> class...> class...>
       
ClassicTrip ::   template<template<typename...> class...> class... 
              -> template<template<template<typename...> class...> class...> class...
              -> ...
              -> template<template<template<template<typename...> class...> class...> class...>
       
ClassicTrip ::   template<template<typename...> class...> class... 
              -> template<template<template<auto...> class...> class...> class...
              -> ...
              -> template<template<template<template<typename...> class...> class...> class...>
       
ClassicTrip ::   template<template<typename...> class...> class... 
              -> template<template<template<template<typename...> class...> class...> class...> class...
              -> ...
              -> template<template<template<template<typename...> class...> class...> class...>
       
ClassicTrip ::   template<template<typename...> class...> class... 
              -> template<template<template<template<auto...> class...> class...> class...> class...
              -> ...
              -> template<template<template<template<typename...> class...> class...> class...>
       
ClassicTrip ::   template<template<typename...> class...> class... 
              -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
              -> ...
              -> template<template<template<template<typename...> class...> class...> class...>
       
ClassicTrip ::   template<template<typename...> class...> class... 
              -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
              -> ...
              -> template<template<template<template<typename...> class...> class...> class...>
       
ClassicTrip ::   template<template<typename...> class...> class... 
              -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
              -> ...
              -> template<template<template<template<typename...> class...> class...> class...>
       
ClassicTrip ::   template<template<typename...> class...> class... 
              -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
              -> ...
              -> template<template<template<template<typename...> class...> class...> class...>
```

## Structure

```C++
template<template<template<typename...> class...> class>
struct ClassicTrip
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

- In the first example, we will compose `OperationA<2>::Road`, `OperationB<10>::Mold`, and `OperationC<'*'>::Rail`.

```C++
template<auto...>
struct Shuttle;

template<typename...>
struct Capsule;

/**** OperationA ****//* Start */
template<auto Variable>
struct OperationA
{ 
    template<template<typename...> class Container>
    struct ProtoRoad
    {
        using type = Container<Shuttle<Variable>>;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};
/**** OperationA ****//* End */

/**** OperationB ****//* Start */
template<auto Multiplier>
struct OperationB
{
    template<typename>
    struct ProtoMold {};

    template
    <
       template<typename...> class Container,
       template<auto...> class Sequence,
       auto...I
    >
    struct ProtoMold<Container<Sequence<I...>>>
    {
       template<auto...J>
       using Page = Container<Sequence<Multiplier*I..., J...>>;
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
using SupposedResult = Capsule<Shuttle<10*2, '*'>>;

using Metafunction = ClassicTrip<OperationA<2>::Road>
::Road<OperationB<10>::Mold>
::Sail<OperationC<'*'>::Rail>
::Commit;

using Result = Metafunction::Road<Capsule>;

static_assert(std::same_as<Result, SupposedResult>);

// The following `static_assert` shows how the operations are composed:
static_assert(std::same_as<
    OperationC<'*'>::Rail<
    OperationB<10>::Mold<
    OperationA<2>::Road<
        Capsule
    >::type
    >::Page
    >,
    SupposedResult
>);
/**** First Example ****//* End */
```

- In the second example, we will transport the conjuration function to `InvokeRoad`.

```C++
/**** Second Example ****//* Start */
template<template<template<typename...> class...> class RoadArg>
struct InvokeRoadDetail
{
    using type = RoadArg<Capsule>;
};

template<template<template<typename...> class...> class...Args>
using InvokeRoad = InvokeRoadDetail<Args...>::type;

using Result_1 = Metafunction::Snow<InvokeRoad>;

static_assert(std::same_as<Result_1, SupposedResult>);
/**** Second Example ****//* End */
```

## Implementation

Since every member template of different signatures is given a unique name, we know which member to pull out when asked for a template of a specific signature.
For example, we can compose a `Road` and a `Rail` in the following way:

```C++
template<template<typename...> class...Args>
using Metafunction = Rail<Road<Args...>::template Page>;
```

Note that

- `Rail` has signature `template<template<auto...> class...>` and
- `Page` has signature `template<auto...>`.

This means in terms of signatures, a `Rail` can always be invoked by a `Page`.

We will implement `ClassicTrip` by performing recursion manually, meaning the function will recurse only once for every invocation of a member template.
We will showcase a simplified version that handles `Mold` and `Rail`.

Note that in the following code,

- `Radio` is a `Road` and
- `Car` is a `Mold` or `Rail`.

```C++
// `Radio` is a `Road`.
template<template<template<typename...> class...> class Radio>
struct ClassicTrip
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
           // Then, we invoke `Car` with the type result of the obtained `typename`.
           template<template<typename...> class...Signals>
           using Road = Car<typename Radio<Signals...>::type>;
           /**** Conjuration ****//* End */

           
           /**** Transition ****//* Start */
           // Helper function for the member template `Snow`.
           // This function transports the conjuration function `Road` without invoking it, 
           // allowing further process by other higher-order functions.
           template<template<template<template<typename...> class...> class...> class RoadVessel>
           struct Detail
           {
               // We transfer the conjuration function `Road` to `RoadVessel`.
               using type = RoadVessel<Road>;
           };

           template<template<template<template<typename...> class...> class...> class...Agreements>
           using Snow = Detail<Agreements...>::type;
           /**** Transition ****//* End */
       };
       /**** Commitment ****//* End */

       /**** Continuation ****//* Start */
       // This function composes the conjuration function `Road` and the `Agreements...`.
       // Note that even though `Agreements...` is variadic, it only allows a single argument.
       // This is because `Agreements...` will be used to invoke `ClassicTrip<*>::ProtoRoad`,
       // which has only one parameter `Car`.
       template<template<typename...> class...Agreements>
       using Road = ClassicTrip<Commit::template Road>::template ProtoRoad<Agreements...>;

       // This function composes the conjuration function `Road` and the `Agreements...`.
       // `Agreements` will be used to invoke `ClassicTrip<*>::ProtoSail.
       template<template<template<auto...> class...> class...Agreements>
       using Sail = ClassicTrip<Commit::template Road>::template ProtoSail<Agreements...>;
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
           template<template<typename...> class...Signals>
           using Road = Car<Radio<Signals...>::template Page>;
           /**** Conjuration ****//* End */

           /**** Transition ****//* Start */
           template<template<template<template<typename...> class...> class...> class RoadVessel>
           struct Detail
           {
              using type = RoadVessel<Road>;
           };

           template<template<template<template<typename...> class...> class...> class...Agreements>
           using Snow = Detail<Agreements...>::type;
           /**** Transition ****//* End */
       };
       /**** Commitment ****//* End */

       /**** Continuation ****//* Start */
       template<template<typename...> class...Agreements>
       using Road = ClassicTrip<Commit::template Road>::template ProtoRoad<Agreements...>;

       template<template<template<auto...> class...> class...Agreements>
       using Sail = ClassicTrip<Commit::template Road>::template ProtoSail<Agreements...>;
       /**** Continuation ****//* End */
    };

    template<template<template<auto...> class...> class...Agreements>
    using Sail = ProtoSail<Agreements...>;
    /**** Define Sail ****//* End */
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMxmpK4AMngMmAByPgBGmMQSkgAcpAAOqAqETgwe3r4BQemZjgJhEdEscQlSKXaYDtlCBEzEBLk%2BfoG2mPYlDE0tBGVRsfGJtc2t7fldCpND4SOVYzUAlLaoXsTI7BwA9HsA1CYAbBoASkz4qKcah3gKh0zHZ%2BeoV7cAdCYaAIIEmBYqQMAJM/jcAKBIMwYIhgOBTFB4IIAE9UoxWJhPtiwdhDsgDAoFNjvv48QSmETDpdrrifr85sQvA5Dm5CZlkAAVYh4VL0kwAdisf0OosOewAVFKJYcACKYGgRanvdCHaUSg4ygatNV7eli8VHW5uFq3e6PZ63ACynnQX31YshCKRcKhiJhyLRGLYJNx%2BPZrNNZIdosZzIIh2UxFQRDeHxFYsFwt%2BBrFkulrNQLBYhDYgjV0s1h21EY1IYNYZZHmzhHLiaFddT4vVmYY2i2iOyBalRZLusbqYOLwuVycZsMquNprOT2ImHxWaKmFVCHiWIHBqHADE8MQ5qRDgB3efhOaGRzu4c0sczieHVAxZrhJ7D1Ho5hse0Jptpo6c1cMAex73AwABuqAANbzlOxBmoehAIIcBCrkhXqHHOCheLQEaoFQSEoQ%2BT4RJOZxvt6MJnN834/kh8LQrCTr0Z676Yr6ZL%2BpSxLYkIeDAMwtAKHS1E/l4mRGMqVzHP4sqBrBzHkdSo43OCPF8WIXGktgIAgGRdL%2BMmNFpi2Hhth2fTdhqkqHNgDCqmWfwbomwlNumUqHNyhjFF26q9vM/bOYORwABI9OixCHFQXgMA0AgRSQ%2BHzmwyzhYxl63EIDCoIeX4poZhruQgDwRVFMUMEhxCeekrSPMh85oKZFXmZF0XmbccZ2jO8HIZsEbhOBEHhMA9wEAejmikOYi0Flg3Fa0q7hak0Y7FSMQovetXhYVwDzQAtCQWDhc1pXEmNtFui6qUXXR7oMddF1eh%2BWI4uxFJEmx5Lsu9HFUu1ABqmBEj0Qm5YZlYRvKT60KdSanZuRwAOrzgQFUMAoVDxAlC4NZ2sVHa1rwqmaRBXiq/2A1DlGw2KokzWRUkyX9AN2LC7V6QZeWCrKYLJqdl0eq6zr83zt3nULD2sc9H2cV9r0aX6sskr8wBzoCjAEIJwYBQaNPiRlWX03KmCQ7CSsq3m6vvdpun6adrkyh5qNZLFPlWTZdl6gFnPcwOduZjWBDmxZRZu/5vw%2B8ZsjhF4ONlS7Wp%2BfZINwwVRV412aBAhkAOY/V7aNV2aexW1hO3rZmO3KbmCq4IcuUwFQ6RDGSMIIihyYKBjD4Zs23DpX1cWziM5FaBLR4KOyAHoQ94MLQa2TVlFqHGJwD0LOwA%2BGrVFJ7%2BKePEVcSiKJ0FnH35u13c8G0LQhxxIcR%2BqsTfWQcfGhspxeBcjyfLgpbIBRjGqBWZnFID7I4h5CrIEQi3R4AhZ7T3nKkFomIAThRgjlH8wtkR3TFixH0ktvoaVPmrDW2ABw6yGu1A2b8iQf25LyWE1YcwECttgiSdoyQsNFpGaMsZCbgiITXd63sHL1z/IVR4hcyoZyXDVFCuczIFxKvjC4Jc7h3lqr3ZWVcz6%2BjrtvcaRoT5aP7oJTqdBr633vkhVAIF%2Bov2oRyOh383C/3/kQIQTA6BbwwdgkWgs/FMRNF4IgMtPr4IVtiAR6tgYiWXsWTx18wQyQcbQr%2BDCsxMM4YLNhuIsnQm4QAjxdATbGJ0ZLYR%2BjmwZhMo4Bg0dzJx2smXROBovY2xEUnTBAtAlkUeqE6WkTSnEJidTOJlCkkFN4R8fhQzBHlPaUnX28pFTzkoY0kOidyxLIVIseJdAg5WT7C0ne/5U5KK7EVDRmQcwGBSihW4bjAGqMOFgFZqomAxFQB3bxO8ACSEYW62XoLIuqlJ5zgLXMOE0sEh6Lzagk9BjpfFYNFgEm64ImDBNQP0t64SAzQpGaGZG4ZJmoCKVDaiMN64R39oHRpRyPaVLBn7JhA4qWVM3BHbGDTCyHIToyvKZ1/EouFRCcWeDNIEJJKpfiJDTrkLYVQoMbhrzKTcDK9Sv8%2BaRiYMAD0pCFmCt9iZPOMcDkyg2Yy22LYHZeWdry%2BOgxQ6Cq6a65F3T0VitwU9SVETfVhP9ZxNhZNmaaw5WKZlEMEVa3rOzQVd84l0wmYzcmLM%2BEGrjTRNpPMY2ijdaikVPT3W9IloG3FZa5YvQDVEuVuaE0zT1oeA2UbikzLNsQrVXoKlGptSjO1scHVNPdmygUXNDUuRpUwulg7LX8mpdUyOdSzX0v5QOfNoqS0SvltW2Z0Sw2xJmuM6SrJ2SpPoeCRhhA8mXlZhwnSrDHm3rcDWoRCy13Fo/QWoJIS8UDIrYrXdtbKkKvJVQ09n9z1uEvcw%2B9XDb1aVg9kx55KSntrmZpbtE6F2CCjsumdzSBX1jHTmzpn6N3usxT%2B/9v7y01sJfW3WCSDbIYRW27RHb5mZu2SsvZ191kEf5KOip9I7bqh7CJ6UnJsBCE5IWCTYmfJzrDmYfw4QCReCwFJNwwS6CEBRMDekXTKPYvKX8ZlQgEDBIIPQYTfxXXip9cDZlJpUiYRs2%2Bv4vsADyYUY4phXU6xORmsWHF%2BqPD57nSFmeJSyHz8Q/OCYsMcai66ekOZxY8GpniIhySi0nZlj7CaUobFrBVSbj1ZcWHJdVlmCDWf5mFnkEX9Vs3LNmpTBpUues3Y5qtf66P7tGYelUzGeFPOmc%2BwDr6eZCYWd53zfR/P4eHR0%2Bb8W%2BhJYCzqILFGQtWiwo4YEeB4hOZixGOL%2BcBAzczfZ719GCtjZtLQScDZZskc674yl4J31fp6xl1sRF4ggICsFqj26g1CEwAARy8IwHYwPKnGZJL8trg2iVMhZI8p77CoOyGyydlS0PYfRX5r819Bq8utJK5U0HJnPgACl6NDfEsoXV0EKt46q7CSHMO4f8329hXktBjvEAlGT7EB56fk8w6KdrHSPu/fS4MtDe7KfM6Gtj0bADseofY%2Bh1rDk3vybchdmOm3luh2NzKU3fQ3DmuLKuuzu3iaNbHjESL9JmU2%2ByG4RL5YusuiRzRx4PPic7Hu2dw2xtiuZu1omtCEzQ989hK75rBuk5y7DilsjgSg/Uc%2BANtXooFWXH2RMltUM2MmM7eiYTRvPMtm9wIO3/GVtZ9%2BL7Hce4IzYFUKwYE84tulkZSBrwqQlzoHOADA7SrXNYX5hZqz7m3BcA0BKIIhwwAcAlFvvSGalMKqtEbJgkiwPvwg84pvDAw7gjMLkkA8H6TaSfVfqw4JV/3512G7SKHwRX99%2BCFvjvhwPfqXpXnltpNBrZr8CXtPthAbEfs0JIs/nwlBkwHPh7h5gyM0I4MgAAPqcTxAEAQBzDoDaQKCYgEEawqpwEjTFhj4T5T5uYEC4irDQFDj/jzj8BXzTTiS3Bni4FUFKCtBmgKAIALyHDiFNoaKoALbZAWhzgLiZxKBkGe44EfxCFEEkEEBkEgAUFsBUGwjlj/6whAG753pgFGHUSv6wgf53pf6%2B7WFyECA35uB34WGoEbguZuYwhfYIa6R%2BHaSs56qo7YAI4GhCAMFZyT60H8hkhsFzYthd5zDWR95QiD4W6bIN4ZiQ71Sqi9796rxD6hwB5CzFpK757g4/Qqi/DEDACnYY4Ri/JgTPztQV5%2B7URlYJ7HrtS1H1EXroE%2BHp6Z6GY57dblHeoZZTGRJ1FAYKrNF2JHoyQLGtEqjtH8KzE14egkawHMF4FcAIHH7IEgCNqwgrFQSP5YECEaGEGtDaG6H6GYCGHghMEHb7EHiRHj7RGvHYSsEVK%2By5ECD5FpED726WocDrC0CcAACsvAfgHAWgpAqAnAvulg1gS8mw2w0EKmPApAzCCJEJ6wEEIAJwkgnwSQGgJw/gGg/g/gyQJw0J/gAAnAKPoJwJILwCwBIBoBoKQPCYiciRwLwAoCALyfiVoOsHALADAIgCAD1KkMEuQJQNInQPEJEJiJwKoEkCcDtKSYcMAMgMgIcFIJ8GYLwMuIQCQHgGQVwDIIICIGIOwFIHafIEoGoJoDoHoIeBVKkJwDwJCTCXCR6UiZwF5sEgqThHhFqTqXqQaUaSaWYIcBANWKkKqagjiasLwOKRCaQBAEgCqfQGQBQBAAWWMMAFIEEDQNhPECKRADEMGTEOEC0CiH6bwI2cwMQCiF5jENoPUPibiRnObF5jPC2QSaQFgDEF4MACaFfCKdwLwFgCwIYCvLsIifgHOA0B3HOYiZgKoPUMErsLieEACFCWOcLjEBVJ2R4FgMGcjHgFyfOaQB3MQJ8koPKEuUYMLkYB6esFQAYMAAoL9MdoeHFvCbifwPaaIOIM6RBa6SoOoGOboLaQYN%2BaYGiZYPoHgDECKZAOsLIX0HOTtKQUkmhVYJYGYAKc%2BTyFgDhRAOsHUKVC4LZNMH4LaaEIsBUFUHoEUE7DkJ4B0NxRkLxcMJxSsN0L0I0PMCxXoAxX0CWCJaMNULYFJfxfkLaWeK0ApclBIPRZiTsDpWyRwLCXycGYKYcNGbqZIPqYacaWSYmRALgJaemf4FwJmXiT%2BesKuFcGMHRaQMSZIP4J8Eyf4AKJIBoJIGYJIGcBoNCScEyYZRyaQFyS5Z8CcFwCcEkEyUkOldCZIFwNCcFScCZWOYKcKaKe5QSZKTKXmXKeGYqcWaWcQOqWwJwC0CwKBAKDtM8BSOJFwEyZ8FwJ8DufgEQNRXoLBQ6dBdILBYoPBcGboEEN6ega2QGUZUGSVaGXVZGbOO1Z1d1ShUNH1QNUNUmSmWmccCpmYG5dmZKfmYuGmUqSWfdYWSAG1R1TtD1eWUyavnwHQCgrWfWWOe2c2a2aQMDZ2d2b2Q4KDYOWrMObPMGROVOTOQJKDYucueIGOeuX2XgFucGbufuQCKDceT0MGeeZeSiNeauVmTyA%2Bbic%2Ba%2BZgO%2BRjYND%2BXwP%2BYBcBaBaDRNVBU6dNbILNe6YhSAEEAdSgNYNYJhdhfAHhakARZwERToSRZLeRZRfENRQDLLeJTjc4BAK4NJWxbZFpVxbaTxbbqpaxWkEJX0CbWJbJZJYMIbTraVPJRxYpTJSpXkFbRpQsOUB7a5RsFsPpYHaecZfybwGZW9XtRxL1f1YNXcA5SNfFOYC5ddR5aQF5QdJQKtYlclf1eFQKAVQKAKHSZFaSbaRHSGUKbYOVTdbmdVUgPKfVcqc9WqRqRwG1XqSwAoKBEaaBEddCHMOacnWNbabzY6YkC6ULQhYiboP4KQEtb6fOateHaZZtQQBGfeHhF3VZT3X3YcAPf1UPRGMmW3c5f4OnZVbmXdUCA9Q1efSAH3ePngUfXgSfQQcQCwKSb9dWXuJQIDYieDaObicA5DX2TDRknDSOYjZgJOdOZNHObiejZ%2BdTeObuDjXjWOQTcgAecTYIKTWeVhRTVTbebTaDQzVnMzZ%2BazdfX%2BbqpzZgCBe%2BDzbIJNfzdPW6bPZ6QveLaRVLeebRXLQrfsKQRLehRYBRZHVRdaVrbhS7X0Exe4JbXoOxf7dpWbTbT7io5o/2nbUpQ7QICWM7YY/0PMPo57U7To8pYMBY4HQoHpU6avetQKZwDtd3b3f3YPe6CkUnU5RdWnVmRnVnT5bnZyaLf1bSdCdCeFavjSSFRlcVa4zXSKWKRncSf4NCQNYVUyScAyVwHSWcLw5wP4C45HZwEE5VatWaUk%2BUzXTdesM%2BZkM4JIEAA%3D)

## Links

- [source code](../../../../conceptrodon/roadrivore/classic_trip.hpp)
- [unit test](../../../../tests/unit/metafunctions/roadrivore/classic_trip.test.hpp)
