<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::ClassicTrek`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-classic-trek">To Index</a></p>

## Description

`Mouldivore::ClassicTrek` accepts an operation.
Its first layer accepts another operation for composition.
Then, it returns two commitment functions and twelve continuation functions.

- **Commitment**
  - **Conjuration:** When invoked, this function instantiates the first operation with the arguments. Then, it invokes the second operation using `Omennivore::Send` with the instantiated first operation as the packed vessel.
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

This function has multiple signatures.

```Haskell
-- End in Conjuration
-- Compose with Mold
ClassicTrek ::   template<typename...> class...
       -> template<typename...> class...
       -> ...
       -> template<typename...> class

-- Compose with Page
ClassicTrek ::   template<typename...> class...
       -> template<auto...> class...
       -> ...
       -> template<typename...> class

-- Compose with Road
ClassicTrek ::   template<typename...> class...
       -> template<template<typename...> class...> class...
       -> ...
       -> template<typename...> class

-- Compose with Rail
ClassicTrek ::   template<typename...> class...
       -> template<template<auto...> class...> class...
       -> ...
       -> template<typename...> class

-- Compose with Flow
ClassicTrek ::   template<typename...> class...
       -> template<template<template<typename...> class...> class...> class...
       -> ...
       -> template<typename...> class

-- Compose with Sail
ClassicTrek ::   template<typename...> class...
       -> template<template<template<auto...> class...> class...> class...
       -> ...
       -> template<typename...> class

-- Compose with Snow
ClassicTrek ::   template<typename...> class...
       -> template<template<template<template<typename...> class...> class...> class...> class...
       -> ...
       -> template<typename...> class

-- Compose with Hail
ClassicTrek ::   template<typename...> class...
       -> template<template<template<template<auto...> class...> class...> class...> class...
       -> ...
       -> template<typename...> class

-- Compose with Cool
ClassicTrek ::   template<typename...> class...
       -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
       -> ...
       -> template<typename...> class

-- Compose with Calm
ClassicTrek ::   template<typename...> class...
       -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
       -> ...
       -> template<typename...> class

-- Compose with Grit
ClassicTrek ::   template<typename...> class...
       -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
       -> ...
       -> template<typename...> class

-- Compose with Will
ClassicTrek ::   template<typename...> class...
       -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
       -> ...
       -> template<typename...> class

-- End in Transition
-- Compose with Mold
ClassicTrek ::   template<typename...> class...
       -> template<typename...> class...
       -> ...
       -> template<template<template<typename...> class...> class...>

-- Compose with Page
ClassicTrek ::   template<typename...> class...
       -> template<auto...> class...
       -> ...
       -> template<template<template<typename...> class...> class...>

-- Compose with Road
ClassicTrek ::   template<typename...> class...
       -> template<template<typename...> class...> class...
       -> ...
       -> template<template<template<typename...> class...> class...>

-- Compose with Rail
ClassicTrek ::   template<typename...> class...
       -> template<template<auto...> class...> class...
       -> ...
       -> template<template<template<typename...> class...> class...>

-- Compose with Flow
ClassicTrek ::   template<typename...> class...
       -> template<template<template<typename...> class...> class...> class...
       -> ...
       -> template<template<template<typename...> class...> class...>

-- Compose with Sail
ClassicTrek ::   template<typename...> class...
       -> template<template<template<auto...> class...> class...> class...
       -> ...
       -> template<template<template<typename...> class...> class...>

-- Compose with Snow
ClassicTrek ::   template<typename...> class...
       -> template<template<template<template<typename...> class...> class...> class...> class...
       -> ...
       -> template<template<template<typename...> class...> class...>

-- Compose with Hail
ClassicTrek ::   template<typename...> class...
       -> template<template<template<template<auto...> class...> class...> class...> class...
       -> ...
       -> template<template<template<typename...> class...> class...>

-- Compose with Cool
ClassicTrek ::   template<typename...> class...
       -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<template<typename...> class...> class...>

-- Compose with Calm
ClassicTrek ::   template<typename...> class...
       -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<template<typename...> class...> class...>

-- Compose with Grit
ClassicTrek ::   template<typename...> class...
       -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<template<typename...> class...> class...>

-- Compose with Will
ClassicTrek ::   template<typename...> class...
       -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<template<typename...> class...> class...>
```

## Structure

```C++
template<template<typename...> class>
struct Trep
{
    struct Commit
    {
        template<typename...>
        alias Mold = CONJURATION;

        template<template<template<typename...> class...> class>
        alias Flow = TRANSITION;
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

- In the first example, we will compose `OperationA<Shuttle>::Road`, `OperationB<10>::Mold`, and `OperationC<'*'>::Rail`.

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
    template<typename...Vay>
    struct ProtoMold
    {
        using type = Capsule<Sequence<Vay::value>...>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
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
    struct ProtoRail
    {
        using type = Capsule<Sequences<Variable>...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};
/**** OperationC ****//* End */

/**** First Example ****//* Start */
using SupposedResult = Capsule<Shuttle<10*2, '*'>, Shuttle<10*3, '*'>>;

using Metafunction = ClassicTrek<OperationA<Shuttle>::Mold>
::Road<OperationB<10>::Mold>
::Sail<OperationC<'*'>::Rail>
::Commit;

using Result = Metafunction::Mold
<
    std::integral_constant<int, 2>,
    std::integral_constant<int, 3>
>::type;

static_assert(std::same_as<Result, SupposedResult>);

// The following `static_assert` shows how the operations are composed:
static_assert(std::same_as<
    Send
    <
        Send
        <
            OperationA<Shuttle>::Mold
            <
                std::integral_constant<int, 2>,
                std::integral_constant<int, 3>
            >::type
        >
        ::Road<OperationB<10>::Mold>
        ::type
    >
    ::Sail<OperationC<'*'>::Rail>
    ::type
    ,
    SupposedResult
>);
/**** First Example ****//* End */
```

- In the second example, we will transport the conjuration function to `InvokeRail`.

```C++
/**** Second Example ****//* Start */
template<template<typename...> class MoldArg>
struct InvokeMoldDetail
{
    using type = MoldArg
    <
        std::integral_constant<int, 2>,
        std::integral_constant<int, 3>
    >::type;
};

template<template<typename...> class...Args>
using InvokeMold = InvokeMoldDetail<Args...>::type;

using Result_1 = Metafunction::Flow<InvokeMold>;

static_assert(std::same_as<Result_1, SupposedResult>);
/**** Second Example ****//* End */
```

## Implementation

We will compose functions using `Omennivore::Send`.
For example, we can compose a `Mold` and a `Road` in the following way:

```C++
template<auto...Args>
using Metafunction = Send<typename Mold<Args...>::type>::template Flow<Road>;
```

Note that in order to succeed, `Mold<Args...>::type` must be a packed `Road`, meaning it is of the form `Vessel<Items...>` where `Items...` all have signature `template<typename...>`. This requirement is not checked by `ClassicTrek`.

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

- `Radio` is a `Mold` and
- `Car` is a `Mold` or `Rail`.

Here is the entire implementation.

```C++
// `Radio` is a `Mold`.
template<template<typename...> class Radio>
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
           template<typename...Signals>
           using Mold = Send<typename Radio<Signals...>::type>::template Road<Car>;
           /**** Conjuration ****//* End */

           
           /**** Transition ****//* Start */
           // Helper function for the member template `Flow`.
           // This function transports the conjuration function `Mold` without invoking it, 
           // allowing further process by other higher-order functions.
           template<template<template<typename...> class...> class MoldVessel>
           struct Detail
           {
               // We transfer the conjuration function `Mold` to `MoldVessel`.
               using type = MoldVessel<Mold>;
           };

           template<template<template<typename...> class...> class...Agreements>
           using Flow = Detail<Agreements...>::type;
           /**** Transition ****//* End */
       };
       /**** Commitment ****//* End */

       /**** Continuation ****//* Start */
       // This function composes the conjuration function `Mold` and the `Agreements...`.
       // Note that even though `Agreements...` is variadic, it only allows a single argument.
       // This is because `Agreements...` will be used to invoke `ClassicTrek<*>::ProtoRoad`,
       // which has only one parameter `Car`.
       template<template<typename...> class...Agreements>
       using Road = ClassicTrek<Commit::template Mold>::template ProtoRoad<Agreements...>;

       // This function composes the conjuration function `Mold` and the `Agreements...`.
       // `Agreements` will be used to invoke `ClassicTrek<*>::ProtoSail.
       template<template<template<auto...> class...> class...Agreements>
       using Sail = ClassicTrek<Commit::template Mold>::template ProtoSail<Agreements...>;
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
           template<typename...Signals>
           using Mold = Send<typename Radio<Signals...>::type>::template Sail<Car>;
           /**** Conjuration ****//* End */

           /**** Transition ****//* Start */
           template<template<template<typename...> class...> class MoldVessel>
           struct Detail
           {
              using type = MoldVessel<Mold>;
           };

           template<template<template<typename...> class...> class...Agreements>
           using Flow = Detail<Agreements...>::type;
           /**** Transition ****//* End */
       };
       /**** Commitment ****//* End */

       /**** Continuation ****//* Start */
       template<template<typename...> class...Agreements>
       using Road = ClassicTrek<Commit::template Mold>::template ProtoRoad<Agreements...>;

       template<template<template<auto...> class...> class...Agreements>
       using Sail = ClassicTrek<Commit::template Mold>::template ProtoSail<Agreements...>;
       /**** Continuation ****//* End */
    };

    template<template<template<auto...> class...> class...Agreements>
    using Sail = ProtoSail<Agreements...>;
    /**** Define Sail ****//* End */
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwAbKSuADJ4DJgAcj4ARpjEIGYArFykAA6oCoRODB7evnqZ2Y4C4ZExLPGJZv7SdpgOuUIETMQE%2BT5%2BQbaY9qUMLW0E5dFxCUmptq3tnYVpCjMjEWNVE7WSAJS2qF7EyOwcAPRHANRCeCzptHg0mOinJoEaQq5PGqdUXgxNAgB0Jg0AEECJgrgZQSZ/G4CABPdKMViYU7KJjIADW9wAapgFHYodhAUDFsQvA5zq5HgB2KxUgAiUKswKJoPBTEh0NZ13ZmChMPhiLYf2FBNOyAMeNOHkETBWZFOcIRzCFwuw9DYggUBKJJLJBApDHQfOlrTlfLVYMYBAUwoB/kJ9qJJhpRNOboVYO5HJhnohvM5AuVmFtovFTElAHkEcR2bltcD3addeS6ZhTbRXe6TqcAJIMABuqExj2eUYSsYE71OAHdCAgFQhke8LRrrSHngCE%2B7nRZTl5skYFQLHv46acyzGBub1VabSLHf5e86GYunV23Vy/XzNzzt4GkSH7WKJXO/kDgMRMJbNfGgYn%2BxFgKcAEqoJgPKFj1Ppvnny/Xtt52wEAQEVf0mSBZdGTXEFfV3Tk4O9HdvSYLwiEPbBj3DU9QxPc4iAxYhUFQFhSA9NkULQ1AMKwvFbVeABHLxGAOLVHWBZN9VeQ0%2BRaVBCOIlheMwJiWNxDDbx7TMN0Q/0fQouTkLk1D0KA2icKPMNI2jCsGFvRNONOb9ZQzddTmzPNC2Ld4J10qtawIetHKbZ5GOYn5xJFDtpOpXsH0HMCRzHWyp2hNyxI0h0l3paDmTMpTt1kxKFL5FTqLUrTIvU20/yvVs2MJMz/KfIQTKCoy0xM38Lzy2cMJAsDYsgmLVzioEjgAKi6jqpRPPBkAAFUvdFTm6jqjiJbN3mfd8nCrPAFFOJgSw0ABZTwjW84EEoQlKAyVA8Mrwmb8FQW9DLcPrBuGp0XTMzruoqmhIhfN8HjGk4eqGdpRom%2B6zneNw2nmxblvedbaE2jROzvd0dvkr1FP3FU7UwzKpWB9jYbdQzlCIohX3fHypLMrMxqlEiWEIVtRu6z78OGX6fPdC7KcIZm3RJ7HE0TB6uophhtD2XTaa6%2Bnvv1caOZ5qbnhOubniWw0VqB4gqzaZE0CuLJ7lORtLxhnmjfhsCg3ovBgGYWgCul%2B8ByfCGP1HA0jX2wVkXls6wotq3IoagUCQa2TXqJ6FVe1VruaN8zyelIXJ1yUXxs605sGVqW2ujxNbbJx6hsMEpE4%2BlOJaZ0mjezAAJPpo0%2Bb5fgYT4SAbZE2DWYhyMRlaADFaFQat3kNrO3WzAaEAWuufgGBUYwYBRMnaRbnLFAR45Fr4p8T8GNvsutdn1CIrMfU5CDInOR7OMQ%2B9rQcvnafXTnSIjWMW2JYVOVBnI78fgH1gBaEgWAO4bwbjac%2Bncty7URslaBbszZHWwjRdGjscR4j6PpYeSYCCkhTJVOg4CuaYJlmcAA6sibBBcqAJBbivQWwtp4gOntvSGVYiArRQbifEW0o6YOKkOBE5UOFoIzNCR2EcIJEKgpHcBJskpQMgfyA6KNcKIIQXRYUuUAI23LjzPhvd%2B7lWMvg6Emj8r1VAgHSORC%2BY9XznPHIAgk70zTu9P6PDqQrgkRXWObMCA02Lj1FxZdII6JsQLRwDAvAiwCQzH6Gd3Gj3HotRhictbFFxDQtAdCE6OJSY45hUMlYPGXu8UxdUvLQ2ltmKIn9yEIHZKcTA%2BZGANl2L/FaZTNTtg%2BBPfMbQ8CzWQGRQgH8GC0HflffuoMkyPnoEtYgwAfBWiHsQ04Y8J4T3iKIfsLlgQ1S0d0msdBaCnHiH2JQxTUAnwLEWXZl1sL9SGpgdEfIOqBxAHjT%2BqBCZQ1IFUs41Zx7IHrPUxaAhxmjOROkNoSJQQd0BsDbh0dZF7UUe7JBJ4cr7Pyhg3R9sQ5OzHPcvEjybph18UHBSpwxH2kpV3T5BM3rVX/GYoCTV/lrKSZPBuK9tZKCXo2Wha8GH1yYc8MRitDDFMFaU7F5SARIorgDZ4nTrS71oCcs5OzLnXKsncq6TyXnQjebSj5%2BNUClToCsxMKLYEIwUWlDFqjUbZQ0XKm8WNo58MtScz8vUHnXWecaCloFg40uAqGqlDKLVVRMe6wCqMmrRzCSaCIUTp4xKCfE7OLUII%2BVtQo02h0XWZSxSy2cuLznHx%2BeVaNPzmW1S6Wyqxud%2Bapmeh7N6TiU5ZrcT5MJ7aVjnDKjE0u2asxnHWck0VicJ7L2yFTAwHcSnPDrUyxWWAO0PCYLEVAzTrUWX1PUw09ABWa3DMiQFCQ7mIp6dM6aVVFUyVRQW%2BCQMqJOvUSWvC4dPUs2wXqFE5qfXEzugknxLAqZ%2BKtN2r6SxgnR1ZpB9mOjCGYJTavehRc6Yl3g%2BO4eJtkbBmFBcS2YhtHuLtsfR25VuKuzRUGF8s0vZuFI77cxjVTVKWHcYtwv6orgIw9k6JOHAnpz7To3m5M7GF0caOvDbiiGvqQnIhjxaVFfo04tIR%2BI/3D0MkY0ylHuxgaIe6PhgU/U6fQaIneC4vHDykXmyTcNVPKaRko4j37nVabLY2tVems56OvoYvBIi3Cqr9hYhESb0PSdnrJxumbxPSyc1UiDUH/GidTilzO3jHqpsiSJsWuHGb4ZtW5tzRHP2nki5W8z%2BKa1%2BuJdkQNRq%2BMhu4%2BGulfogNfPrXG8tTbE3SJ0e5mBDqP1qKyqWt1Q2AuFXcd6sqzWDVko68hggPWeTUrsxG7j0aQODf85FWLMsfGCDTcV5OYnXGgc8TBCrL7KuosddNmrfmtGVuW3QWtwHY0RfjadltI9yaDpej62DOW7vMlzTBGxY1Edi0mtJ3E1onEo6R1j%2BJTpagRHFF4LAI43BoToIQWEkltqqbe4mjiAHyRCAQGhAg9B2VU5fdVtldOcH6iBukBQXhWejdgs917U3vOaaxhdNoxA8AJDZ%2B1cmIVch3nk2Vtx43oQ060xSUSHlzr0/1MrgQITmpLnilVzztosRiErbjc1YizJoaNhZ4czWmD88F3JcK%2BvoQ29oCBPp3h/TYAkiDjxCunt2qLSjOrgW%2BE0b9dGmlgP5vA7zXD4EYTjcMFV9l3t8Olc6QGL2NXcSNfU6otSwXjhrhy7VlLw345i%2B5Azw5iBb6Y9ebt03wzvk0t5efdHyvqkJeLR9wcMiNOcw955xVH8YURLuQOHyHMYfFs5vb65sXo%2BABS9W3R8NRMAJszsJ9yVWjXvAdeEgdTX8KMiu%2Bw/t4H6bqPhbOdniB7PwDyed5O9My9XxUs2dlVll3l2hEMwbS%2By42DmP273s3u0j232j0/zjw3wa2ow2j%2By%2BRT0i2f1ugeyzyL3LBLyhwLzamzxbwEDcChzHQrx3yuRt1lx3SF0W0MhzzcFunb013fVH18xIyXwih/3JDrSqgAK30wICjd1AI9wFyF1YyEI8jYjcGYIGViDYIIIAKILfxQMLRH3SjH0%2BxxXj0axW2djEN43wObQzx0KoNINyFoOSxh1NzCW7jwGIEWFTlUFYGuGRDL0ljcW9S8HSHSXQGfFxBr3Kj53kO9yZwIBZzki4A0A6jMDIjAA4A6gyIJDIkZ2ZwUOSI6n8HSMyOyIXAEzagT0qjyUblWwDUNT5Bz0gjCniMSPeXDSJBAgGzcBzysGhGSPaL206JACOx6OoLyD5AyKyI4HeRmmMUWxAg8E2wVz4QiPkP1Cs2qJnWcBAEd2aK4LMkWHQBAgiFBAvDEAAH0slFhDACA%2BRTiyIzAcifIjiTjBBMBzjaAriBAbjBB7jBAyJ/BJIuNLFnNiRWhHBkALjsIEgCAIBXiQAFAkRoSVC1ia9ciQiwi0TaA7j7RNgFdElkR%2BANV%2B5j53gbjISUSlB2gqwFAEApk9YDFl5UBxjQZLxeUwiQAdQIT%2BoqTYT4SCBjjETkTww%2BQfI6NiZoRbYJTJMxSXN3QmjeJWi2CQI9izM5TjNENBS3iziYwvjrjWg/joQHjTgnj7Q/l5SjYETTiPi9Tvi55DTcS3ATSgTAss53lGpZS3T3QuimVoRei%2BQBjTUOjJN/YYsndAsQJRjODJjSiZjTU5iREMC3QwzeQzILTuYhBMSdZwjIicSnQ8Smo3CPCvDsAfDwR/D89ctXDyZXgskHgyzfC5kAjgleCu8atdtIYgQFkDc59LJblHYoDYd29XcBErMNpuzgBJSDjKNrT3jPj7TfinSTSzTsAMys45zdTLiDTbj/iCBATK0PTQTCCFc2zP8BCzwFkKM%2BF%2BzMRE9nZbzMBBywtfwryONjzKjGs8yCALiuBBEtjN4dj9EB5oRHyOjhcKTeSYT2gBShSkS2AUS%2BRsSfy0hzhsyLlkKCR8TI4wk6yBAGzyy/DyDxMOBtgA8OBkheA/AOAtBSBUBOAuDLBrAkxdh9gmxageBSAtsaLSLth0QQBkhJA/gNBJAuAqR/ANBkgNAzBAhAgzAAAOeS/QTgSQXgFgCQDQDQUgai2i%2BijgXgBQEALS7irQbYOAWAGARAEAfedINCcgSgNJOgBIKIJETgVQeSwIP%2BQISQU4YAZAZAU4KQP4MwXge4QgEgPAY4tIfgQQEQMQdgKQGQQQRQFQdQHi0gXQNIasGMdITgHgMizgSi7SzQXgPSiMNCWy/UVAKgU4dyzy7y3y/ywKoSswU4CAJY9IJy%2BFDizYXgEy0i0gCAJARy%2BgMgCgCAEaiYYAKQNImgHEhIQyiAWIEq0gWICINoWEPK3gNa5gYgWECMWIbQRobizirWVsCMMZTa9KrAWILwYAIGDVQy7gXgLAFgQwYAcQa6jw46vAZpJ62izAVQRoNCQ4Tim08i2im4WIGMPajwLAFa7BS4La0gZpYgXdJQVMN6owG4IwEq7YKgAwYABQLEOXasMsaizimK4QUQcQRKqmlKtQFazK/Qd6lAawawfQPAWIQyyAbYFkgYJ6v%2BI4z8UwJiywMwXS1G2XLAHmiAbYBoBuFwQ0OYPwNIMIFYSoaoIoLIBxPITwLobWxLUYTWiYBYPoH6gQCWFWvQBWgYCWY28YRIBYJYa2524YB29uCQeW1ig4L25SiiqilavS2qjyrynyvygKoK1qiAXAcK7q/wLgXqrivG7YRsd8CYOW0gfiyQfwP4AATn8CpEkBErMEkGeEksCDzv9tUtIHUoTr%2BECC4ECHkrzvkqbsEq4GSALuCB0tKs4AMqMuTp4rMssqGusoqrsvGsmuIBcrYE4DaBYHzCpD/mWjDEHC4Dzr%2BC4GEtCvwCIGlr0CpritpukHpqUEZvSt0DSOyo9y2oKoDuKvSrKonqqpqoXqXpXqwnXs3u3o%2BHapIk6tGseFqDMCTv6rMuGoAa6vsomqgdGpAHfuXrXumrzuSL4DoDhUWuWvSp2o2uRtwb2oOqOocGRrOqtAuvGRWpuruoeutmRteves%2BtovwEvCaD%2BpWsBuBtBGRvBpWqhphthDhsOFosRvUuepRoSHRswExsYcfDxr4EJuJtJvJuRqPppoStPtkAZrStoqvpZtxtFqsEsE5u5vgD5vSAFs4CFsFJFvZvFsloSGltxDMd6H6FyCVvcH1vmBCENA9q1rSGKF1tdoyB1oGD8dNtcYtsGBdq8dVsiYbnto1sdptpiYKDiZuPaHCadu9r2F9sTv9qKt7ros4HmUXuXtXoMG/q3uEratjv3uAYTrAZTtIDTqAUoHvprrrs3pEqpC7qpHEskFLu8rSCKb0oHuMvkfMqspssnocrgectco4AXoapYAUHzACvzA3r%2BD9EWF3rjsisPtkGPo0aSvkHPp0Z0ACFIBvtyuevvsKaDs4HKoIEqo/jfuIBYBWbWY2a2Z2f1H/quC6oaf8CaeHsGsgcBdGpgenpAHWdCIuM2bzouL%2BehI%2Be8vQfms8MoGwdooIaus4rxaIeOtIcpnIcuqocwFuvuqvies4oYexuEZeu%2BrYecfSs4eQBBp4feIht4H4Y2qEYRtlzEc4tRqkZkexrkbBYJqYCJpJswDJqVFUaOfUYkE0eSvOaZqucqeMDsZsChtlvMcseOFeMMesAltKqlsiucd5viYGA8eCfVoqGSYCdCccNicNt1qyZtvNoSdSYNrNrcctqWC9bdtmHddDeWCdc9vyYUB9oSvucDqfpKeWZ8tWfWdOERe2Z5C8Jjr3ubnMEab6uadaYzo6bUqSE3v8H8GSCktEs0qrapGbsft0v7tsEHvAb4pAEkGSHzuSHkpkrzskDzvEsLq4GKPIv8ETZbf0qHtMvvpCubb7pnY7Ykc8PcckCAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/mouldivore/classic_trek.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/classic_trek.test.hpp)
