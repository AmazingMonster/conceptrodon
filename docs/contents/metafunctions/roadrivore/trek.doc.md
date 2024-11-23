<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Roadrivore::Trek`

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
Trek ::   template<template<typename...> class...> class... 
       -> template<typename...> class...
       -> ...
       -> template<template<typename...> class...>
       
Trek ::   template<template<typename...> class...> class... 
       -> template<auto...> class...
       -> ...
       -> template<template<typename...> class...>
       
Trek ::   template<template<typename...> class...> class... 
       -> template<template<typename...> class...> class...
       -> ...
       -> template<template<typename...> class...>
       
Trek ::   template<template<typename...> class...> class... 
       -> template<template<auto...> class...> class...
       -> ...
       -> template<template<typename...> class...>
       
Trek ::   template<template<typename...> class...> class... 
       -> template<template<template<typename...> class...> class...> class...
       -> ...
       -> template<template<typename...> class...>
       
Trek ::   template<template<typename...> class...> class... 
       -> template<template<template<auto...> class...> class...> class...
       -> ...
       -> template<template<typename...> class...>
       
Trek ::   template<template<typename...> class...> class... 
       -> template<template<template<template<typename...> class...> class...> class...> class...
       -> ...
       -> template<template<typename...> class...>
       
Trek ::   template<template<typename...> class...> class... 
       -> template<template<template<template<auto...> class...> class...> class...> class...
       -> ...
       -> template<template<typename...> class...>
       
Trek ::   template<template<typename...> class...> class... 
       -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<typename...> class...>
       
Trek ::   template<template<typename...> class...> class... 
       -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<typename...> class...>
       
Trek ::   template<template<typename...> class...> class... 
       -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<typename...> class...>
       
Trek ::   template<template<typename...> class...> class... 
       -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<typename...> class...>

-- End in Transition
Trek ::   template<template<typename...> class...> class... 
       -> template<typename...> class...
       -> ...
       -> template<template<template<template<typename...> class...> class...> class...>
       
Trek ::   template<template<typename...> class...> class... 
       -> template<auto...> class...
       -> ...
       -> template<template<template<template<typename...> class...> class...> class...>
       
Trek ::   template<template<typename...> class...> class... 
       -> template<template<typename...> class...> class...
       -> ...
       -> template<template<template<template<typename...> class...> class...> class...>
       
Trek ::   template<template<typename...> class...> class... 
       -> template<template<auto...> class...> class...
       -> ...
       -> template<template<template<template<typename...> class...> class...> class...>
       
Trek ::   template<template<typename...> class...> class... 
       -> template<template<template<typename...> class...> class...> class...
       -> ...
       -> template<template<template<template<typename...> class...> class...> class...>
       
Trek ::   template<template<typename...> class...> class... 
       -> template<template<template<auto...> class...> class...> class...
       -> ...
       -> template<template<template<template<typename...> class...> class...> class...>
       
Trek ::   template<template<typename...> class...> class... 
       -> template<template<template<template<typename...> class...> class...> class...> class...
       -> ...
       -> template<template<template<template<typename...> class...> class...> class...>
       
Trek ::   template<template<typename...> class...> class... 
       -> template<template<template<template<auto...> class...> class...> class...> class...
       -> ...
       -> template<template<template<template<typename...> class...> class...> class...>
       
Trek ::   template<template<typename...> class...> class... 
       -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<template<template<typename...> class...> class...> class...>
       
Trek ::   template<template<typename...> class...> class... 
       -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<template<template<typename...> class...> class...> class...>
       
Trek ::   template<template<typename...> class...> class... 
       -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<template<template<typename...> class...> class...> class...>
       
Trek ::   template<template<typename...> class...> class... 
       -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
       -> ...
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

- In the first example, we will compose `OperationA<2>::Rail`, `OperationB<10>::Mold`, and `OperationC<'*'>::Rail`.

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

/**** OperationA ****//* Start */
template<auto Variable>
struct OperationA
{ 
    template<template<typename...> class...Containers>
    struct Detail
    {
        using type = Capsule<Containers<Shuttle<Variable>>...>;
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};
/**** OperationA ****//* End */

/**** OperationB ****//* Start */
template<auto Multiplier>
struct OperationB
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
using SupposedResult = Capsule<Capsule_1<Shuttle<10*2, '*'>>, Capsule_2<Shuttle<10*2, '*'>>>;

using Metafunction = Trek<OperationA<2>::Road>
::Road<OperationB<10>::Mold>
::Sail<OperationC<'*'>::Rail>
::Commit;

using Result = Metafunction::Road<Capsule_1, Capsule_2>;

static_assert(std::same_as<Result, SupposedResult>);

// The following `static_assert` shows how the operations are composed:
static_assert(std::same_as<
    Send
    <
        Send<OperationA<2>::Road<Capsule_1, Capsule_2>>
        ::Road<OperationB<10>::Mold>
    >
    ::Sail<OperationC<'*'>::Rail>
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

Note that in the following code,

- `Radio` is a `Road` and
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


// `Radio` is a `Road`.
template<template<template<typename...> class...> class Radio>
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
           template<template<typename...> class...Signals>
           using Road = Send<Radio<Signals...>>::template Road<Car>;
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
       // This is because `Agreements...` will be used to invoke `Trek<*>::ProtoRoad`,
       // which has only one parameter `Car`.
       template<template<typename...> class...Agreements>
       using Road = Trek<Commit::template Road>::template ProtoRoad<Agreements...>;

       // This function composes the conjuration function `Road` and the `Agreements...`.
       // `Agreements` will be used to invoke `Trek<*>::ProtoSail.
       template<template<template<auto...> class...> class...Agreements>
       using Sail = Trek<Commit::template Road>::template ProtoSail<Agreements...>;
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
           using Road = Send<Radio<Signals...>>::template Sail<Car>;
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
       using Road = Trek<Commit::template Road>::template ProtoRoad<Agreements...>;

       template<template<template<auto...> class...> class...Agreements>
       using Sail = Trek<Commit::template Road>::template ProtoSail<Agreements...>;
       /**** Continuation ****//* End */
    };

    template<template<template<auto...> class...> class...Agreements>
    using Sail = ProtoSail<Agreements...>;
    /**** Define Sail ****//* End */
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMxmpK4AMngMmAByPgBGmMQSABzSAA6oCoRODB7evgFBaRmOAmER0SxxCVzJtpj2xQxCBEzEBDk%2BfoG19VlNLQSlUbHxSdIKza3teV3j/YPllaMAlLaoXsTI7BwA9NsA1EJ4LCm0eDSY6HsmAGwaQq43GntUXgwOWQB0JhoAggSYxwM/xM/jcBAAnilGKxMHtlExkABrC4ANUwCjsIOw3x%2B42IXgcB1cVwA7FYSQAREFWX44/6ApjA0H0k6MzAgsGQ6FsD68rF7ZAGDF7DyCJjheKkPYQqHMHm87D0NiCBRYnF4gkEIkMdAc0XNCXEDmKgGMAgKXlffzY604kxknF7J3SgGsplg11A9nMrlyzCW/mCpjCgDyUOIjKyat%2Bzr2GsJFMwBtojuduz2AEkGAA3VDIq63MPxSMCR57ADuhAQ0oQsMeJuV5oDty%2BMed9osey8GSM0q5V38FL2RYjDWNSrNFr5tv8nftVNndrbTpZXo5q7Z699MID1oFQqnHx%2BwGImFNKujP1j3fCwD2ACVUExLiCh4nkxzj6fz03p9gQCAMrejSPzztSS5/J6m7MlB7obu6TBeEQu7YPuwaHoGB4HEQSLEKgqAsFK8Hem4iHIX%2BaEYpa9wAI5eIwmyqravzxlq9w6hyTSoLh%2BEsJxmB0Qx6IoZeHapiusEkcR66SRyZGoChlEYXuQahuGJYMJesasXs77iimy57OmWa5vmjwjhpZaVgQ1Y2XWty0fRbzCXyLbiaSnY3r2QEDkOFljqCjlCcpNpzpS4G0oZ0kwQycGyaC8mKapIVKZaX5no2THYoZXl3kI%2Bm%2BbpSb6Z%2BJ4ZZOKEAUBEWgeFi6RaBvzpo897Pk4ZZ4AoexMAWGiPs%2BjytpBsVSfFHojVuso7hRyVJVhrX4Kgl46QAKqeiJ2g6hnbAAVHtO1FTQEQPk%2Blz7TtuwHX0rR7Bd7nNbcpFGrceydd1vUALKeLqblRWN0WclN8pWqhyUii0WnOjpyh4UQ/W6oZYmGWm50igRLCEI2t37Zd2H9Ld2zuVDBD4oSHgsBjBBE06SNXrG9NGajoraOsGnY3tuPXVqd3IwzD19W1S0vYYL6PRDwungKBGFBcey1qeQ0M/TAMq9uwOYeh1F4MAzC0Fl1P07lJ3PoV7G6qCC3tYF2u6yFWJVZJxvm24T1qvVdNK06u37WjDAs6OWTsxdu17NgOoExBnvtrz9Pe3texrYYRSB%2BdnMTNzhMx7G6YABJ1OGzyvO8AjPCQNawmwFTxC6I29TnJW/R7nvpitCBvS8bwNNKEYMAoaStF1dlS37rNdx3xcML1p0pi91kIGsWrhKZt6vQQUoG9n%2BxiLQqCVr2LytPLewpHhjFdTE4J7KgdnEHL2vywAtCQWC3%2BPDQWhvzoq/9P8TT6QP%2BhmgeOamsgHoSdmiDEdRIZRx0npOgn8aZbSblHL2%2BwADqsISZJyoNXIeaAR4BxLm/QOLVTpliIL1eGkDMSN1QYbHsd4fKvggeiTEFtyEzhAvQsC7tEE1zdKNP%2B41BEyWEUBP0ICqJgOkSDVKvJ0o/n1lnZ0RshAMF3oVeBKZQSKMypVQCXIar0LjgdROvdMgl1TiHMOZ1M4oKQQubhfMmbo0xmaIOuNbERwakrUxvtHAMC8GzaxV104%2BIcUZfYrd25Fy7mgY46R0Tl2Hv7NmJCS5kIGsLcOQ9Hh6Iqq5DQis%2Bb7EiNfLBCBGR7EwNmRgNY1jAGrPksqSjmxPDetmFoeA2rIClIQK%2BDBaCX23rvLqPVGH0G6sQYAPgzQlNjtEtuXU3pxFEN2eyvxWn6KKRWOgtA9hxC7EoS4lCl55k2WtTAG1QQGJhtfVA8NHikANumcsbdkDViqV1AQwzBmwhSC0GE/xb6PFdnQhm39xFq0AXI2aCjtmThgdeRhTtCpXJuS7NxBAHa1yedaXFgi4Sw0eZwtwBSVQiT4THFuyzC6d0DgkmWg9aypNHoHDJk8sk/SeCLFJLTvw7K%2BBCxZvUKXmisvsw5sINmnNQK9HMFzeoYo5Hckl%2BU6ALNjFC0RMVdWkSQgpGRKV4VHkRReZikS1EFRYSq0E5NKaEq9E7e2gFHb3KIBqnR5LzW/hBsYlxPt9ThGCV3UJodw48ybrwkC7kdVrn/tyWFGtZHiuUU3I28NCoetJQNXRvq7bu2zqjRMR1YRZvDd4qN90S2YDLQcAq4auYRM3gnOlnLXosthBkDGBhb55NuDmp5L0sBlsuEwGIqA6lauMlqKpOp6BdoFMGWE7z4ibPBR08ZVCG7FLjb/fVANErGqkV1V2lrtIk01MSh5Xr3K0z8a4im7jBCeJDs2qNSsdIOsIAbB9qD/HM3ZVYnG77wmftQfG6CgMk2nq1jrMQ6b6GZtOqbB4FtBacRtohql/43W1zvfaiGXD%2BGAYEGksNoGDpVvsaR1G5jk4gY5mB/GEGo5QbiuI/6MK4MnuNawqBOjsqRMvaTLU2j%2BH/vocclezDBwCfYW4fFoVJN1VjSoiSXGtOHu4wA3jcLgF8bNYKpFF7UFqI0eWLRxUEH5pM5Sv8VUjFFoA/RnujHJ6VsjfYpWMbXlPspljLzdjI6BvjsGoJISqN4xumx7VB6E0wckUZtNyLVGoqzba9aepsVOrZC6gl%2BGiVDrJWmql6nIkcaEfq49BnQF1dTQWtLTprV0HRdl%2B1uWivOuU3l/4N7PUlTs%2BVBz/qXOx1cYIENUXmPUe8/etToXNM6e04l2rKaTWGeMyNiVZmWuoq9dm9VQ2fX2b9W7ZxXta31sO8FiJfmGqmPOhzHEccVrYCECtHGr3nvPdo7SMw/hwiCi8FgAcbgkJ0EIOCUSvwj2GpEixK9hIhAICQgQegNU6S6dg3%2BdUyOtSkRSAoLwmPqXDUPTxvHSOxPg2J6TzAAB9LgWO4c4%2BS/6mn16ick/oIzswrOKeJfh%2BRBrdsudkxaMQPA8RBf%2BP8lkK8TbwP2JF/KlE3SJ1k%2BEzpBXAhGq1TnH9Vb0GJHTTF5afU4oIjECQ8TWnEnEbIM9kbOTQ4ecM5y2KQ0TE3Co/R2TtwGvpda%2B9DabA5WFtOKWwI4X7PzcbbSk1vbMneyZfkxJ4bbTHOGKhFjxbTVUZ64YEr6LNGILy/Ug0TsyvWOq7GvJPYH1SeOBODLo0lrddV6yLG53X94/qxT3AmzByxIF4N/FiaiNQQb1Vnp/jVvDQvKzmr09RJBLOWXyJ2rGZ71D4J0VD8nXvc2/4hvzYHIMy4eRVJyfNWEe8gAFLNdT3eeEwA6zycX6fwKAknIX9BGb1oFb1OHiB2iv15ClEf2v3G1JGj18X72hXn22yUWRSNi%2BloBfC/yl3bw5Ez1Ox2yyj61hHf2TRI1pHH0r2LGrzfTmxC0eyL27wEDcFoJiwzmx2EUb2Dx6RiG13x1p2LzcE2ku1j1Nwbwfwt15CCmcjtydGHw/CdxEJRVk37BYQ90D2kMYg5G4NDyxEjyd3gIn0QJW3v1F0TwRTO1kNfwfBtQzxH1KksIMWqj4UoMYOoKyBYLu2rULx9gADE8BbctRsBVBWAThYRa9Yt7E1EvAUgZZ0B7x0QW9Cp1CSIUjmdOI0cCAMcSIuANAdogg9gwAOAdoii3ZsApQ0iBdApMjsiORcj8ipQiiSiOAyiLsIJ0DioO0strkORi9QJQQqi8NlMcQAJ8U3Bi8rBQRcjXUMDzZhMAJCNximDsgOQmjSjCtWpbN5iQAf0qZydM1EjgDCoPpOi4kshRiyU0iuAKimB6c%2BdBjBdZhHBkBGd0J4gCAIBxh0AAIFAYRXjfcEjec14DgYi4jASW8sQlg5cllYR%2BBaAd4947xHgni8AXi3jWgywFB55ywupsSUlUBljxlJYmUklvj8dIw0SoFWhPiCBviQBfi2B/iOR3IzY98hCs5WTQQ%2BiORBiLi80XZbjecmdri6chT%2BdWis4%2BTnYJi6iNAZjvob8U8FiTtBDVjij1ihihthNYwt9YwhBQTSTwTgC7RrQoT3Z/F/DAjQ4QjARwiy95sGCfZ7gCFLhgjQipkIj2C2cTdONKdkDzCxcbC6AfgZlloD8TILl4ZHdDd3JXdVD5NNjaAQzgA9RBSGdmcbi7imcHiXDDCOCTC48kDcdJCSzkz00jYIzkR08hxKzMAoz7DdEZkQonM899iMtDiCBmdjjTiGVnAQB1Fd5L9FUqzOEVMGoUTKSlBqSvifi/jgwOQjTOyRT9TYjDSOzISap/FnSBBXSbSwjWCaMOAVhaBOAABWXgPwDgLQUgVATgIQywawOMNYDYOsQHHgUgHFK8o8lYREEAU8swD4a4U8gATjMDMH/K4H8H8GAskGuGuJPI4EkF4BYAkA0A0FIEvOvNvI4F4AUBAHQs/K0BWDgFgBgEQBAAXhSCQnIEoCZToHiEiBhE4FUESGuAfmuEkD2GAGQGQD2CkA%2BDMF4AuEIBIDwG%2BOuP4EEBEDEHYCkBkEEEUBUHUC/NIF0GuPLAjBSE4B4GPLPIvM0F4GwpDCQioq1FQCoD2BYrYo4q4p4r4skAEr2AgHJhSHotBTfKWF4EIqPNIAgCQDovoDIAoAgACpGGACkCCBoGAPiDwogBiAMtIBiHCBaHBG0t4CSuYGIHBBDBiG0EwAcDStIASUbBDCGVSpUqwBiC8GAFInhLwu4F4CwBYEMGAHEAqoCPyscDqXquvMwFUHyqQi2HfPCH%2BAQuvNOBiAjCyo8CwASpJiOEKrqWIEnSUETGaqMFOCMAMpWCoAMGAAUBRBl3LCLEvPfMkuEFEHEDkvOsUrUASrUv0BapQGsGsH0DwBiDwsgBWAJPfk4Afi%2BNfFMAfMsDMCwqWulywE%2BogBWDsE6vOIgFcCmD8GuNCAlAWBGGuMKEsWyE8A6D0CxoaHmGGCqG6DhoEC5iRr0Fhoni5iJqrhJtmEmFxryGuMZoGDRuJokBhufM2C5v0D0owoSuwsstYvYs4u4t4v4rMCctwBEvcv8C4E8o/O2pWFrGfBGGhtIF/MkH8A%2BGAv8BJEkA0EkDMFgrQtPOuGAv5sQuQoCC4EAq4GuESGAsSEdtPMkC4BAv8GuEFpUuwtwvwuVq/OIrIr8oopMuouCtCuIEYrYE4BaBYGzBJAfh6iDF7C4GAo%2BHtt6vwCIAhr0HOukquukBuqUDupUt0CCA0tuLSt0o4HPN9qws4GMoIFMqvgsoTqTpTrQnTszuzqcpcrcquEBzMCVu8uIv8uljcpopCqnsCpAE7uTrTvCuAtyL4DoBBVivipUoypSsKt3qypyryoKoaqKvRjNFKuGQSsquqtqr1kKqaparauvPwFPHeG6oSr6oGv%2BEKpGrqASomqmvBBmq2GvPmpQtPqWpWswDWqftvG2r4D2oOqOpOsKsLsutkpLtkFuuUuvMrseq2qBqsEsDeo%2BvgG%2BpSF%2Bo4H%2BtpMBpepBrBviAhvRHIdJonhcB1EppRp1DpsWExvSGxq4dIAJqyF4YxrYYaApuZuRokd6HTjEYZvTiEbZoUb5oUB5tkrrobswsMs4GmUTuTtToMF7qzo%2BCeAgFlrzuHoVrHpVtIDVpfkoDrqQtIBQugrMckBJBApJBJH8BNtgo9sbt0ZwtsEDvHt8tDqQEosjtornoYqYo4ATpspYAUGzF4uzAzo%2BC9HGCEtztEvEvkoupkokCwYUrLtwZ0ACFIGrq0oaq0f0r9ubojrMo7uIBYGSdSfScyeya1Gcriflv8FseDt8snuOGnqjv6ZADSdiMZwyeAsZx6deLaY4vXuitt0oG3uvIPvKvfO2aPs6sKuKovrKuvswCqpqu3nqvfMfo2tAcao6vfpYZUq/uQEGt/sEH/pUsAZSpAbmulwgffKgaSVgY2vgeGd2qYH2sOswGOtlDQdkCLswcKZwfuqqeMeMHoZsAmqhooaoe2BnKIesFBsMvBrEpYa%2BtkecARs4ekb0FRrKE5v4Y8yEZEZKA5vpqprqDJsaCUdpdZq5ZpvkfZb4dsF5dyBkZUeFYxu5vWF5sVutu0aFr0aSc4pSbSb2DmaybZHGBlryflsVq8rsYcY1ucdtrMEzqgtPNPONtyI0CgpJCdqCZvM4ADoIrse1pJA%2BD8Y0B8c8dYtuFPOgutv8AaabpCfHrrsEqdf9qDqIpWCWoyGcEkCAA%3D)

## Links

- [source code](../../../../conceptrodon/descend/roadrivore/trek.hpp)
- [unit test](../../../../tests/unit/metafunctions/roadrivore/trek.test.hpp)
