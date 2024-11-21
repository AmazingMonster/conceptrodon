<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Roadrivore::ClassicTrip`

## Description

`Roadrivore::ClassicTrip` accepts an operation.
Its first layer accepts another operation.
Then, it returns two commitment functions and twelve continuation functions.

- **Commitment**
  - **Conjuration:** When invoked, the function instantiates the first operation with the arguments and then the second operation with the corresponding member of the result.
  - **Transition:** When invoked by a vessel, this function transports the conjuration function to the vessel.

- **Continuation**

  When invoked by another operation, the function returns a `ClassicTrip` that is instantiated by the conjuration function and whose first layer is instantiated by the new operation.

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
       auto I
    >
    struct ProtoMold<Container<Sequence<I>>>
    {
       template<auto...J>
       using Page = Container<Sequence<Multiplier*I, J...>>;
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
       // This is because `Agreements...` will be used to invoke `ClassicTrip<...>::ProtoRoad`,
       // which has only one parameter `Car`.
       template<template<typename...> class...Agreements>
       using Road = ClassicTrip<Commit::template Road>::template ProtoRoad<Agreements...>;

       // This function composes the conjuration function `Road` and the `Agreements...`.
       // `Agreements` will be used to invoke `ClassicTrip<...>::ProtoSail.
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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIaa4AMngMmAByPgBGmMQSABwA7KQADqgKhE4MHt6%2BeqnpjgLBoREs0bFcCXG2mPaFDEIETMQE2T5%2B0naYDpmNzQTF4VEx8UkKTS1tuVy2EwMhQ2UjlXEAlLaoXsTI7BwA9HsA1CYAbBoASkz4qKcah3gKh0zHZ%2BeoV7cAdCYaAIIEmBYyQMAJMAGY3ACgSDMODIYDgUxQRCCABPZKMViYT448HYQ7IAwKBQ475g/GEpjEw6Xa54n6/cbELwOQ5uInpZAAFWIeGSDJMCSsf0OosOewAVFKJYcACKYGihGnvdCHaUSg4yvotNV7Bli8VHW5uZq3e6PZ63ACynnQX31YqhiOR8OhSNhKPRmLYpLxBI5bNN5IdoqZLIIh2UxFQRDeHxFYsFwt%2BBrFkulbNQLBYhDYgjV0s1h21EY1IYNYdZHmzhHLiaFddT4vVmYY2i2SMyBalRZLusbqYOLwuVycZsMquNprOT2ImAJWfymFVCBi2IHBqHADE8MRxqRDgB3echcaGRzu4e0sczieHVCRJohJ7DtEY5hse0Jptpo5c1cMAex73AwABuqAANbzlOxBmoehAIIcBCrkhXqHHOCheLQEaoFQSEoQ%2BT6hJOZxvt6sJnN834/khCIwnCTr0Z675Yr65L%2BlSJI4kIeDAMwtAKPS1E/l46RGMqVzHGCsqBrBzHkTSo43BCPF8WIXFktgIAgGR9JgsmNFpi2Hhth29TdhqkqHNgDCqmWfwbomwlNumUqHDyhgFF26q9nM/bOYORwABK1BixCHFQXgMD0AgRSQ%2BHzmwSzhYxl63EIDCoIeX4poZhruQgDwRVFMUMEhxCeakLSPMh85oKZFXmZF0XmbccZ2jO8HIZsEYhOBEEhMA9wEAejmikOYi0Flg3FS0q7hck0Y7NSkSovetXhYVwDzQAtCQWDhc1pUkmNtFui6qUXXR7oMddF1eh%2B2K4uxlLEmxFIcu9HHUu1ABqmDErUQm5YZlYRvKT60KdSanZuRwAOrzgQFUMAoVAxAlC4NZ2sVHa1rwqmaRBXiq/2A1DlGw2KokzWRUkyX9AN2HC7V6QZeWCrK4LJqdl0eq6zr83zt3nULD2sc9H2cV9r0aX6sukr8wBzoCjAEIJwYBQaNPiRlWX03KmCQ3CSsq3m6vvdpun6adrkyh5qMZLFPlWTZdl6gFnPcwOduZjWBDmxZRZu/5vw%2B8ZsghF4ONlS7Wp%2BfZINwwVRV412aBAmkAOY/V7aNV2aexW1hO3rZmO3KbmCq4IcuUwFQ5hDGSMIEihyYKBjD4Zs23DpX1cW7iM5FaBzR4KOyAHoQ94MLQa2TVlFqHGJwD0LOwA%2BGrVFJ7%2BKePEV0SiKJ0FnH35u13c8G0LQhzRIcR%2BqsTfWQcfGjspxeDcry/IQpbIBRjGqBWZnFID7I4h5CrIEQi3R4AhZ7T3nMkZoWIAThRgjlH8wsUR3TFixH0ktvoaVPmrDW2ABw6yGu1A2b9iQfx5HyOE1YcwECttgiSdpyQsNFpGaMsZCYQiITXd63sHL1z/IVR4hcyoZyXDVFCuczIFxKvjC4Jc7h3lqr3ZWVcz6%2BjrtvcaRoT5aP7oJTqdBr633vkhVAIF%2Bov2oZyOh383C/3/kQIQTA6BbwwdgkWgs/FMRNF4IgMtPr4IVjiAR6tgYiWXsWTx19wQyQcbQr%2BDCsxMM4YLNheIskwm4QAjxdATbGJ0ZLYR%2BjmwZhMo4Bg0dzJx2smXROBovY2xEUnTBAtAlkUeqE6WkTSnEJidTOJlCkkFN4R8fhQzBHlPaUnX28pFTzkoY0kOidyxLIVAseJdAg5WT7C0ne/5U5KK7EVDR6QcwGBSihW4bjAGqMOFgFZqomCRFQB3bxO8ACSEYW62XoLIuqVJ5zgLXMOE0sEh6Lzagk9BjpfFYNFgEm6EImDBNQP0t64SAzQpGaGZG4ZJmoCKVDaiMN64R39oHRpRyPaVLBn7JhA4qWVM3BHbGDTCyHIToyvKZ1/EouFZCcWeDNIENJKpfiJDTrkLYVQoMbhrzKTcDK9Sv8%2BaRiYMAD0pCFmCt9iZPOMcDkyg2Yy22LYHZeWdry%2BO/RQ6Cq6a65F3T0VitwU9SVETfVhP9ZxNhZNmaaw5WKZlEMEVa3rOzQVd84l0wmYzcmLM%2BEGrjTRNpPMY2ijdaikVPT3W9IloG3FZa5YvQDVEuVuaE0zT1oeA2UbikzLNsQrVXoKlGptSjO1scHVNPdmyhIXNDUuRpUwulg7LUCmpdUyOdSzX0v5QOfNoqS0SvltW2Z0Sw2xJmuM6SbIOSpPoRCRhhA8mXlZhwnSrDHm3rcDWoRCy13Fo/QWoJIS8UDIrYrXdtbKkKvJVQ09n9z1uEvcw%2B9XDb1aVg9kx55KSntrmZpbtE6F2CCjsumdzSBX1jHTmzpn6N3usxT%2B/9v7y01sJfW3WCSDbIYRW27RHb5mZu2SsvZ191kEYFKOipDI7bqh7CJ6UXJsBCC5IWCTYmfJzrDmYMEIRCReCwFJNwwS6CEFRMDBkXTKPYvKX8ZlQgEDBIIPQYTfxXXip9cDZlJpkiYRs2%2Bv4vsADyYUY4phXU6xORmsWHF%2BqPD57nSFmeJayHzMQ/OCYsMcai66ekOZxY8GpnjQhySi0nZlj7CaUobFrBVSbj1ZYWHJdVlmCDWf5mF3kEX9Vs3LNmpTBpUues3Y5qtf66P7tGYelUzGeFPOmc%2BwDr6eZCYWd53z9R/P4eHR0%2Bb8X6hJYCzqILFGQtWiwo4YEeAYhOZixGOL%2BcBAzczfZ719GCtjZtLQScDZZskc674ylEJ31fp6xl1sREYggICsFqj26g1CEwAARy8IwHYwPKnGcOL8trg2iXMlZI8p77CoOyGyydlS0PYfRX5ij4M5O8utJK5U0HJnPgACl6NDfEsoXV0EKt46q3CSHMO4f8329hPktBjvEAlL8g89PX0Zra29jrSLfvpcGWhvdlPmdDWx6NgB2PUPsfQ61hysvPMtguzHTby3Q7ybcib%2BobhzXFlXXZ3bxNGtj0iJFhkzLreZDcIl8sXWXTGf%2Bzz4nOx7tncNsbYrmbtaJrQhM4PfO4Qu%2Ba/rpO7WOkfd%2B07un4PaOAfowqy4%2ByJktqhmxkxnaMTCcN78Nbl2sh29natlsO49wRmwKoVgwJ5xbdLIykDXhkhLnQOcAGB2lWuawvzCzVn3NuC4BoCUZgDxgA4BKVfelpcdIVVaI2TBJFgffhB5xXuBBhwhGYXJIB4MMm0k%2B0/DArAQgX1f7XYbtIoYhA/n3EJV/r44FfkXmXnltpNBrZr8IXmPthAbLvk0JInfnwlBkwJPu7h5oyE0I4MgAAPqcQxAEAQDjDoDaQKBYg4EawqpQEjTFiD7D6j5uYEB4irDgFDj/jzj8BXzTTiS3BniYFkFKAtBmgKAIALyHDCFNoaKoALaZAWhzgLiZxKBEEe4YEfx8F4EEEEBEEgAkFsBkFwjljf5wh/4b53pAF6HUQP5P7z4aCv62hmFJwP7n5uCX4mGIEbguZuawhfYIa6ReHaSs56qo7YAI4GhCA0FZwj6UECjkhMFzYt67jjDWSd7Qg97m6bJG4ZiQ71Sqgd5d6ry96hz%2B5CzFqK7UYVpsK/DEDACnYY4Ri/JgTPztSl6%2B7URlZx7HrtQVFVEXrIEeGp7p5hyO5Z5DEbolG56VpSy0aVFAYKp1F2JHoySzENEqhNH8JTGV4egkaQH0FYFcAwF77wEgCNpwiLFQQ35oE8EqG4EtDqGaHaGYC6EQh0EHY7EHihFD7hFPHYSMEVK%2ByZECDZFJHd6N4EYcDrC0CcAACsvAfgHAWgpAqAnAPulg1gS8mw2w0EKmPApAzCsJoJ6wEEIAJwkgnwcQGgJwYIGgYIYIkgcQJwEJYIAAnEkOCRwJILwCwBIBoBoKQDCXCQiRwLwAoCANyTiVoOsHALADAIgCAD1MkMEuQJQNInQDEGEFiJwKoLSTtESYcMAMgMgIcFIJ8GYLwMuIQCQHgEQTMPwIICIGIOwFIDIIIIoCoOoLiaQLoDMIeBVMkJwDwGCZCdCZoLwPyV5sEnKThHhBqScFqZIDqXqQacSWYIcBANWMkMqagpiasLwKKaCaQBAEgEqfQGQBQBAIWSMMAFIMvjQNhDEEKRAJEEGaQJECEM0KiL6bwM2cwMQKiF5pENoN0DiViRnObF5jPG2W6VgJEF4MACaFfEKdwLwFgCwIYCvLsHCfgHOD0B3POXCZgKoN0MErsFiSEACCyXCcLpEBVN2R4FgI2cjHgByQuaQB3MQJ8koPKMuUYMLkYEGesFQAYMAAoL9MdoeHFjCVidacIKIOIA6ZBc6WoI2R6foCuSgNYNYPoHgJEEKZAOsJIfUPOTtIQUkqYMiZYGYHyS%2BbyFgNhRAOsF0KVC4LZFMH4DMEEAsKUOUHkGkE7FkJ4O0Fxf2oMBxcsDUHUL0HMMxXoPRfUCWEJcMBULMP0JJTMGeC0HJclBIHRWiTsJpfoAGTyY2fyYcFGTGXGfqYaUmRALgGaRmWCFwFmdib%2BesKuFcCMLRaQASZIGCJ8AyWCAkJIBoJIGYJIGcBoBCScAyXpayeySAHZZ8CcFwCcHEAyXEIlRCZIFwBCb5ScAZW6fyYKcKY5bieKVKfmTKWGfKSWWWcQKqWwJwM0CwKBAkDtM8JSOJFwAyZ8FwJ8LufgEQFRXoJBbaTBdIHBUoAhW6boMvl6cge2f6RwFCblXyZwKGQQOGfeHhA1U1S1RxO1Z1d1XcCmYuOmccCpmYA5TmeKQWcdUWQqaWTdSMFtc1W1RWQyQvnwHQCgnWQ2W6Z2a2e2U2S2d2b2f2Q4ADcOWrKObPI2ZOdObOQJADUuSueIBObuAOXgNuY2XuQeQCADSebUI2ReVeaiDeWudmbyI%2BViS%2BW%2BZgB%2BcjYNL%2BXwABUBSBWBQDUNdBfaaNbIPBa6XCVNchT%2BSRVYJYBhVhfALhckPhZwIRRocRWhWRRRTEFRQDBLaJejc4BAK4MpaQGxSUPJQJTxTrfkDxepZxSpbUBrQ0BJXxdMOraVLJexQbSpTbTkCxYpWpU7RpfZRsFsDpT7SyYtbycGZwLOI1c1a1QYHtV1T1cmdZf1adXZRdU5aQC5QdJQPNWyaQByYyT1ZIAkFlQkAkNScFUSTMMHfCZwAVSKYzRKdKbKZVYqQ9TVWqRwA1dqSwAoKBPqaBB1Z8DCOMCaX1eaZaY6VBXaRINzU6eNXzToLFaQDNT6QufNUHYZStRVRGWHR3V3T3X3QPRGEdUCCdeYFScncVXmddUfbdVVc3SAN3UPlgb3QyVgfvTgcQCwESR9TWXuJQD9XCX9d2QDQAz2X2QOeDRkpDWOTDZgFOTOZNPOViUjV%2BWTaQBuejZjW6djcgIeXjYIATW6UTa2aTXeRTQDdTVnHTV%2BQzeff%2BbqizZgKBe%2BOzbIMNVzWPbzYhfPVHcYArTYBeTRZLdLfsIQahaRRYORcGZRRaarThfbfUIxe4Lbe7XrYsObSkNxTbko4bfUGbSJdJeJUpVoxbWJQII7frd7R7a0EY5Y7oxUFpX7faSvYGXlaHe3bGZ3d3YcE/f3e6AkVZcPbZfZdmSnWnW5ZnTFWYJ1VSRCRCYFQvpSX5UlUtSHQKbYIVZdfibFRCV1dlQyScHSVwNSWcGCFFWCM48takxk1Fcack5XZUynS%2BekM4JIEAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/roadrivore/classic_trip.hpp)
- [unit test](../../../../tests/unit/metafunctions/roadrivore/classic_trip.test.hpp)
