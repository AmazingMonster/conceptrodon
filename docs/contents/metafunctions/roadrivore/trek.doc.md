<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Roadrivore::Trek`

## Description

`Roadrivore::Trek` accepts an operation.
Its first layer accepts another operation.
Then, it returns two commitment functions and twelve continuation functions.

- **Commitment**
  - **Conjuration:** When invoked, the function instantiates the first operation with the arguments. Then, it invokes the second operation using `Omennivore::Send` with the instantiated first operation as the packed vessel.
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
        auto I
    >
    struct Detail<Container<Sequence<I>>>
    {
       template<auto...J>
       using Page = Container<Sequence<Multiplier*I, J...>>;
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

- In the second example, we will transport the conjuration function to `InvokeRail`.

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
       // This is because `Agreements...` will be used to invoke `Trek<...>::ProtoRoad`,
       // which has only one parameter `Car`.
       template<template<typename...> class...Agreements>
       using Road = Trek<Commit::template Road>::template ProtoRoad<Agreements...>;

       // This function composes the conjuration function `Road` and the `Agreements...`.
       // `Agreements` will be used to invoke `Trek<...>::ProtoSail.
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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxCBm/lykAA6oCoRODB7evgGp6ZkCoeFRLLHxicl2mA5ZQgRMxAQ5Pn6BNXUCDU0EJZExcQlJto3NrXkdY31hA%2BVDVQCUtqhexMjsHAD0WwDUQngsKbR4NJjouyYAbBpCrtcau1ReDF0MAHQmGgCCBJhHBj%2BJn8bgIAE8UoxWJhdsomMgANbnABqmAUdmB2C%2B3wUBGIXgc%2B1clwA7FYSQARYFWH7Yv4AphAkH046MzDA0EQqFsd68zG7ZAGdG7DyCJizMi7cGQ5g83nYehsQQKTHY3H4wl3BjoDmixoSjkK/6MAgKXmffxYy3Ykxk7G7B1S/6spmg52A9nMrmyzDm/mCpjCgDykOIjKyqp%2Bjt26oJBF2FMw%2Bto9sdO12AEkGAA3VBIy43ENxcMCB67ADuhAQUoQMIeRqVpr9N0%2BUcdtosuy8GSMUq5l38FN2RbDjlLIIbJrNfOt/k7tqpc5tbYdLI9HLXbI33uhfstAqF0/e32AxEwxuVke%2B0e7YWAuwASqgmBdgUPE8mOSezxemzPsCAIDSp6NLfAu1LLr87pbsy0GupurpMF4RB7tgB6Bke/qHvsRCIsQqCoCwpBOgyiHIagqHoei5p3AAjl4jAbCq1o/LGmr3CCDSoHhBEsBydEMa8aKoVeHapqucGem6pFSQhUlISh/5UZh%2B4BsGoYlgwV7Rmx8YfuKKYrrs6ZZrm%2BYPCOmllpWBDVrZdY3AJjHCXyLbiaSna3r2wEDkOlljlpnGYPRzkqVa86UhBtJGXJG6SXFMkcgpFFKWpYXKea37no2zFYkZXn3kIBm%2BQmSYGV%2Bp7ZVOqGAcBUVgZFS7RWBPzpg8D4vk4ZZ4AouxMAWGhPi%2BDytlBiWweN0kurJO5yhaaFpZRaWPp1qBXrpuwACpngiNp2kZWwAFTHYdpU0OEj7PhcJ2HTsp09M0uy3e5bU3G4TTdb1/UPAAsp4OpuTF8UTdN24yruqXYe9xDaY6G3KPhRBDTqRliUZaY3SKhEsIQjZPSdd04b0T1bO5cN4nGWMsDjBBkw6aPXtGTPGZjoraGsmn48dhMPfGz3o8zr2DatZaGK%2Bb0fTcfVngKhFpEoFy1meo3M0zsUg%2BuXrg3NWEYTReDAMwtC5XTTMFZdL4lVqOogh1%2BBrZxBtG2FmK1ZJFs2240Oqk1jOqw6R0nVjDDs6OWRc7dR27Ng2ok5B/vtgLTOB8dW1hgwGQBRHPPTHHSfRumAASmC0KGTwvG8TwkDWMJsPMxAkdNA2F%2BVgN%2B/76abQgPXl68Wd4oYChpM0vX2bLIcc1nzx9%2BHDxXSmUs2QgqzxmEZl3rshDEabBd7GItCoJWvbPM0Su7Ck%2BFMb10RgrsqD2Q33fAErAC0JBYA309vGaO%2BOurU2awATBIB8FZq%2BkhnrCB1EoG9WRqidEJdYYJw2vpOgv96b7XbgnAOewADqMIB4ZyoHEGu49Q6cy/lndqV0yxEAGnAtEGI27YLNj2e8Pk3we3gRiW2NDZygRYeBX26DG6AP/uI4GnJtbgPmhlGBS1DyZUqr%2BE2%2BdHTmyEAwQ%2BJVUEphBFlFRNUgJcnqiwlOp1tqDyKAwbOUcY7XVJknIRAjBas2xrjE0tjTr2Lzi1LBAc3GCDCF4TmN0c7E35v44yewu490oeHNARx0holIWgCeYcBC90rtQ4aUsxakIeAYnKzYNAq0FnsCI98CEIEZLsTA2ZGA1lWM/AaRTqquUeD3bMTQ8CdWQMRQgd8GC0FvvvQ%2BX0Yx3noNLYAPgTRlOTjE7uvUe6xFEN2ByPxlHFI6RWOgtBdixC7ArKUqBN45jzJs7amBdogiMQje%2BqBkYPFIKbdM5Zu7IGrDU3qAgRlDJhCkJo0I/gNweN7ZhzMJGTWAj6BRkDjzbKnEgm8bCPYlWubcr27iCBuxkh7V2QF3YPKRnwtwbTlQiWEUnTuyyslZ0SfLFJY80nkKnhXKhNxnl5NjmPQpSLKUdIWbvVpArTTWX2YcmEGyLh0LXpcgamKOT3MRqgIqdBhV/0kdC0GIJkrwugbIxavIKXipYlEjRxVOFKpBB4amhA8VN2eZaR1HpYSqvVXo8lYqXa%2B1VuY4OjgGAhKzmEuxsdInRmcfHLVMLtVgINUeU1qj27m2RiVElTyyXJqpS4gJQdEznRhOmsN3iI2OL8QXTGhbZj7GKqWomj1I1piWXEjl4ce5jwyDjAwDc%2BU3Ezdyx4WAi0XCYNEVADThUmXjDU7U9BR61gFIGGEHy4ibIhZ0iZ7VW6lPcjqsRkj9XyJgSKD65qdIU0JJmz17kGb%2BrcfaggeMG2818arDadqaam3vdggNbNJ7h1fbnZtCcD3ANhRDI1ijeQHENmIFNLC01XSthxNwdsuqO3g8bKlAEiX4tvba894URH/oEGyoDBNw0OJjQnANliM7WK8Y2vmFaWHgfgtq%2BN0jE28dPQwhBei8pRMvRqPSZU0FqIwXmpDaKOGDi4YwxBvDhr8JEdG5q7GuNxp07qqR3IZG60NUZ9KxrEU/hyii1WGitHlh0RJr1Ob/y1RMX6v9mMGOZ0o9zaj77mYaaiWRp9L6qNlpo5p1xQc9TBNCaFljfm1bab05BnWqkYPmaqpeC9zNkOW2tTtXUOLXVsgJS6/DTdB3Zp9bm2j0YOOySPeRPj0GEXJqsw6S1dAMUFdtUV8rbrnV4bku6x5hHvUWfafNUxkXU7ReDbFnzYWEukkXKBfdSXD2TWPS14zaXWs%2BpRZ1g5nCb3lX0dV/80382pxrRdT1zGfGRIC9icxN1uYvZOptbAQhNoEw%2B29sJkFzD%2BDCIKLwWABxuGQnQQgYJRI/H/tt9aV74xCAQMhAg9B6p0m4wZkSrEUdnpSAoLwWPqVjWSwmy7BOxNE5J/QAA%2BlwbHCPcdwupziQn71iek8wAzswLOKebb00jvbu3hOfqaMQPAcRBcBv8lka8wGIkVsR%2BRXYyIenjrJxLwnCuBB%2BI7JcIGumxFU520ePU4pwjEEQ%2BTWnui72YP9ubeTQ5uf06klbiUzE3Bo4x2Ttwmvpfa89FabANXUaNTWyb5LbOoMmaURNrLwnUUb3TZwx353k9/nmi5yE2Po//dTvrhgSu4uPYrcX06pfOzK6barxrdCfqk8cMcGXMNzUbVr3tGT4jzcopQQ5jyz3Y/rlRiCHe/eeOnu9zb15%2Bc1eKQt0SEKQkF8ieSpmO92WHRD8/L1sUBogpr42ByDMPtw9O5k7GkXTXeQACl2vHI3nCYAdYFNz9lyfwSZ%2BQQt9oDbxODiEOgzGIgf1wyuxW0Fzq3jzmja13xf17D%2BloFfE/ylw7w5Cz3G0yzNSG2JSYHf0jwalW2r2HA0gCjrwr3LUgnlwoKyDcGYzfUiSXzOWD16WiB1zVD13oIEDcF73W1N2AVFwWnSyciEjtz30J0dyjxv3UTk37E4Q91534mCl/zRA5HYND0xGIKjSLwiwkiELImX0TxNQO0QLTStQU2wKczz2MQL2EX0O%2BDoOLACkYIbUr1oMxgADE8Bbd4xsBVBWBjgYR69WNsQNEvAUgmV0AHw0RW8SplDA8ki%2BdmdOJ0cCBMcpIuANBDozBiIwAOBDpCjL9iIUj%2Bd%2BIMisiOQci8iCiiiSjZwr9ydzYfoyp4lMl8sbkORS8wIQQBcytBtsRAJnU3Ae8QQcjCUUCbZhNAIxtS9%2BCQRCjiiOBCUOo0FzVAIv1CBBc014jACSo2jGgOi/AQBRjyjkg6decKi1NmpcRwxkAGcMI4gCAIBcR0BAIFBoQnjfc4j6cCBiIhAoiYi/jW9MRFg5clkYR%2BBaAD4j57wHh7jHBHjnjmgywFBl5yxepMTSFUBeCM5pYYRGVkkPjuCHifilBmg3iCAPiQAvi2AfiOR3JrYd9%2BD84WSQReiOQBi8NzimAedGdLjyieTn9dgRiyVxi3BJiytpiUUUU5izsxj8TFi3BljGjeSztU9HQN9owgToiSTQTACbRLQITfYA1fD/Do4giARQjqDws/EA07g0kLhAjgjpkwjfF6sEpKcZ8LdE0Vo6BvhiBgBkdadTJLlkYZCGoZNXdFCFN1jaAgyQyiMBTUiyj%2BTPcbiSNaQnCccjCGsYUB8xdTN0skyU1zZwykQM8FNKzMBIyHMvxgywp88QJII9j/imdDj2j21nAQBNFD5z8Lkqy%2BFsy/EkS8AUSEEqT3jPjvjAwORDSCAmdATgSDT9jaYTT6pHTagBAXTrSQiHty0OBlhaBOAABWXgPwDgLQUgVATgfgywawGMVYdYOsKoXgXFa8485YBEEAM8swd4K4M8gATjMDMH/K4H8H8GAskCuGSFPI4EkF4BYAkA0A0FICvJvLvI4F4AUBAHQs/K0GWDgFgBgEQBABXhSGQnIEoEZToDiAiGhE4FUAAA4rgX4rhJBdhgBkBkBdgpB3gzBeBzhCASA8APjkh%2BBBARAxB2ApAZBBBFAVB1AvzSBdBkhywwwUhOAeATzzzLzNBeBsKgxkIqL4xUAqBdhWL2LOLuLeL%2BLJBBLdgIA7UUh6KwUlgPzDLiKkA6L6AyAKAIA/KhhgApB8iaBAC4g8KIBohDLSBogwgmgwQdLeAErmBiAwQgxohtBahPyeBSBElGwgxhlkrVKsBogvBgB3pYS8LuBeAsAWBDBgBxAyq/Dcq8AGlaqbzMBVBahkJNh8qwg/gEKbyThogwwMqPAsA4q8RDgUrSAGliAJ0lBExGqjATgjBvK%2BADBgAFBkQZdywiwrz8qpLhBRBxB5LTqlK1A4r1L9AmqUBrBrB9A8Bog8LIBlg8SApaqX53i3xTBHzLAzAsLFrpcsB3qIBlhOgAoXBtQJg/BkgQhZgygKg9B5ZrF4a0bCgAp%2BgUahhqgS52ruhphMaCb7AApeZcbBh4hqgSbPA2g9B7jmgqb64JAoaXyNg2b9B9KMK4rsKrK2KOKuKeK%2BKBKzBnLcBRKPKkhFgvKvzFhlhawXwhhIbSBfzJB/B3hgL/ASRJANBJAzBYK0KzyrhgLubELkKAguBAKuArgWLgKWLbazzJAuAQL/ArhebVLsLcL8LSBCLjzSASLyLKLqLArgriBGK2BOAmgWBswSQX5%2BoAxewuBgL3hrbur8AiAwa9BTqZKLrpArqlAbrVLdB8jNL%2BSUq9KOALzPasLOATKCAzK75LKY646E70Jk7U707nLXL3LLhEgzBZa/atqIBfK5Z3KaKgrx7/KQBW746k7QrgKci%2BA6BQVorYrVK0qkr5qt6MqsqcqHB5rCqTRiqRk4ryrKrqrjZ5qGqmqWqbz8Azw6hOq4qeq%2Bq/h5qhqS44qxqJqwQprNgbzZqUK6qFq4hlrMBVq767wtqqAdq9qDqjr5rc7zq5KC7ZBrqVKbzS77rNqAarBLAXq3r4BPqUhvrOBfqaT/qnqgaQa4gwa0QSHbBCa3hYb3B6a8hEbtQWbUbkh0a3COGEaCgvNihkbqbGaWGKa6bcghHob6hpgeH8bRhehSblHmaxHWauB2a1hOatHzaa7MKjLOBpZY747E6DBO6073hHgIBJas7%2B6Za5aiLFbMBlb4hVaEKkLSAULoLrHJASQQKSQSR/ADbYKXba6jGcLbBfb/biKyLR6KLTLQ7aLp6GKmKOAY7bKWAFBsw%2BLswU73gPRcRhLM6xKJKFKzrZKJB0HFKi6sGdB8hy7tK6qq6DG%2Bb66knzKW7iAWAsmcm8mCmin4wXLUnpb/Ah7YnA6x6jgJ6w7RmQBcnoiGd8ngKGchmnienOKV7IrbdKAN6bzd7Sr8rDn97cqj7sYT6Srz7MAKqqr95ar8rb71rAH6q2rn7GHVK37kB%2BrP7BBv7VLf6kqAGZrpcQH8rFqIGoH1qYH5btrCCEHMBDqZRkHZA860GKnMHbr8gLHjAaGbAxqIbSHyHtgZz8HrBgajLQbxLGGPrmHyasg2HVGkbShxG%2BHsaGDBGsaRGGBFGaa6WiaGBeZVG5HibeheXGbpGGbaaxWNHeHtHXyuaEK2mvbjHMmuLsncndgVnCm2RcQJbSnpatGnHvzSAlaP5KAq6vGUKzBU6oKzyzz9aciNAoKSQ7aInbzOAfaCLvKfyQB/H3gQmNAgn/G2KbgzzoLzb/ADKVWonYmq6hL3Xvbh75blhFqMhnBJAgA%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/roadrivore/trek.hpp)
- [unit test](../../../../tests/unit/roadrivore/trek.test.hpp)
