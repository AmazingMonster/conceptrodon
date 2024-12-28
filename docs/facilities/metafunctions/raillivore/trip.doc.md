<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Raillivore::Trip`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#raillivore-trip">To Index</a></p>

## Description

`Raillivore::Trip` accepts an operation.
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
-- End in Conjuration
Trip ::   template<template<auto...> class...> class... 
       -> template<typename...> class...
       -> ...
       -> template<template<auto...> class...>
       
Trip ::   template<template<auto...> class...> class... 
       -> template<auto...> class...
       -> ...
       -> template<template<auto...> class...>


```Haskell
-- Compose with Mold
Trip
 :: template<template<auto...> class...> class...
 -> template<typename...> class...
 -> ...
 -> Commitment

-- Compose with Page
Trip
 :: template<template<auto...> class...> class...
 -> template<auto...> class...
 -> ...
 -> Commitment

-- Compose with Road
Trip
 :: template<template<auto...> class...> class...
 -> template<template<typename...> class...> class...
 -> ...
 -> Commitment

-- Compose with Rail
Trip
 :: template<template<auto...> class...> class...
 -> template<template<auto...> class...> class...
 -> ...
 -> Commitment

-- Compose with Flow
Trip
 :: template<template<auto...> class...> class...
 -> template<template<template<typename...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Sail
Trip
 :: template<template<auto...> class...> class...
 -> template<template<template<auto...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Snow
Trip
 :: template<template<auto...> class...> class...
 -> template<template<template<template<typename...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Hail
Trip
 :: template<template<auto...> class...> class...
 -> template<template<template<template<auto...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Cool
Trip
 :: template<template<auto...> class...> class...
 -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Calm
Trip
 :: template<template<auto...> class...> class...
 -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Grit
Trip
 :: template<template<auto...> class...> class...
 -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Will
Trip
 :: template<template<auto...> class...> class...
 -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment
```

```Haskell
-- End in Conjuration
Trip'
 :: Commitment
 -> template<template<auto...> class...>

-- End in Transition
Trip'
 :: Commitment
 -> template<template<template<template<auto...> class...> class...> class...>
```

## Structure

```C++
template<template<template<auto...> class...> class>
struct Trip
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

/**** Oper_0 ****/
template<auto Variable>
struct Oper_0
{ 
    template<template<auto...> class Sequence>
    struct Detail
    {
        using type = Sequence<Variable>;
    };

    template<template<auto...> class...Agreements>
    using Rail = Detail<Agreements...>::type;
};

/**** Oper_1 ****/
template<auto Multiplier>
struct Oper_1
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

/**** Oper_2 ****/
template<auto Variable>
struct Oper_2
{
    template<template<auto...> class Sequence>
    struct Detail
    {
        using type = Sequence<Variable>;
    };

    template<template<auto...> class...Agreements>
    using Rail = Detail<Agreements...>::type;
};

/**** SupposedResult ****/
using SupposedResult = Shuttle<10*2, '*'>;

/**** Metafunction ****/
using Metafunction = Trip<Oper_0<2>::Rail>
::Road<Oper_1<10>::Mold>
::Sail<Oper_2<'*'>::Rail>
::Commit;

/**** Result ****/
using Result = Metafunction::Rail<Shuttle>;

/**** Tests ****/
static_assert(std::same_as<Result, SupposedResult>);

// The following `static_assert` shows how the operations are composed:
static_assert(std::same_as<
    Oper_2<'*'>::Rail<
    Oper_1<10>::Mold<
    Oper_0<2>::Rail<
        Shuttle
    >
    >::Page
    >,
    SupposedResult
>);
```

- In the second example, we will transport the conjuration function to `InvokeRail`.

```C++
/**** InvokeRail ****/
template<template<template<auto...> class...> class RailArg>
struct InvokeRailDetail
{
    using type = RailArg<Shuttle>;
};

template<template<template<auto...> class...> class...Args>
using InvokeRail = InvokeRailDetail<Args...>::type;

/**** Result ****/
using Result_1 = Metafunction::Hail<InvokeRail>;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult>);
```

## Implementation

Since every member template of different signatures is given a unique name, we know which member to pull out when asked for a template of a specific signature.
For example, we can compose a `Rail` and a `Road` in the following way:

```C++
template<template<auto...> class...Args>
using Metafunction = Road<Rail<Args...>::template Mold>;
```

Note that

- `Road` has signature `template<template<typename...> class...>` and
- `Mold` has signature `template<typename...>`.

This means in terms of signatures, a `Road` can always be invoked by a `Mold`.

We will implement `Trip` by performing recursion manually, meaning the function will recurse only once for every invocation of a member template.
We will showcase a simplified version that handles `Mold` and `Rail`.

Note that in the following code,

- `Radio` is a `Rail` and
- `Car` is a `Mold` or `Rail`.

```C++
// `Radio` is a `Rail`.
template<template<template<auto...> class...> class Radio>
struct Trip
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
           // First, we instantiate `Radio` and obtain a `typename`.
           // Then, we invoke `Car` with the resulting `typename`.
           template<template<auto...> class...Signals>
           using Rail = Car<Radio<Signals...>>;
           
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
       // This is because `Agreements...` will be used to invoke `Trip<*>::ProtoRoad`,
       // which has only one parameter `Car`.
       template<template<typename...> class...Agreements>
       using Road = Trip<Commit::template Rail>::template ProtoRoad<Agreements...>;

       // This function composes the conjuration function `Rail` and the `Agreements...`.
       // `Agreements` will be used to invoke `Trip<*>::ProtoSail.
       template<template<template<auto...> class...> class...Agreements>
       using Sail = Trip<Commit::template Rail>::template ProtoSail<Agreements...>;
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
           using Rail = Car<Radio<Signals...>::template Page>;

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
       using Road = Trip<Commit::template Rail>::template ProtoRoad<Agreements...>;

       template<template<template<auto...> class...> class...Agreements>
       using Sail = Trip<Commit::template Rail>::template ProtoSail<Agreements...>;
    };

    template<template<template<auto...> class...> class...Agreements>
    using Sail = ProtoSail<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKz%2BpK4AMngMmAByPgBGmMQSAJwAzKQADqgKhE4MHt6%2BAUEZWY4CYRHRLHEJXCm2mPalDEIETMQEeT5%2BgfWNOS1tBOVRsfFJqQqt7Z0FPZODw5XV4wCUtqhexMjsHAD0AFSHR8cnp0e7JhoAggdHANQAkixp9GyCTE13xxfXt2f/Zx%2BV0uN12dxMADYNAAlJj4VCQjR3PAKO5McFQ2F0REAOhBBEwzwMBJMyTcBKJH0wpPJhJeVJpTC8RBxrNJ2DuyAMCgUrLxyQ5XKYPLusPh7JBk2IXgcdwAKsQ8GkQSYAOxWa53LV3P77O4AEUwNAiotQcK%2B5xB2p1YMRbjaiORqPRiIAsp50LirdqKfSSWTfcTqQGAJ5pRisTB89mc7mo%2B3ECWa7VSmUEO7KYioIjQs2e5NatUaq7W7W6u4eFgsQhvdPfb2l1OyyvVggN61F9ulrXljwMbSbD45C2HIHd0u7W2YuFOR2GdAYjQJufETCc1DPTKYBcIeJRrvdyd3ABieGIk1IdwA7mvwvNBHgqYuxbOoWiGAvUDFWuE0YuCGGEZsF6Bbjja8q7gwl43siDAAG6oAA1mudoOm%2BV6EAgdwELudyrgoXi0I4Rj/oBzDAVCeKgeOgYMgGdJBoyzKoNGAqxsKvKskIeDAMwtAKEmJZgVqXhZCRWK0OCyT6hWDpki%2BCJktxvFiJx/LYBKyTFsJhbUYeYIABINOGxB3FQXgMA4w78KZOFrmwVTxNhDFPoiBlMNilEHhOYJyggKJmRZVkCNhxCGAoGTtKidnrv2g6fOZlmfIiEmOhhOEbOm4QIYh4TAMiBCXt51pHmItCoBhJHme0u6mWkWbbCKMQhnc2a1Xc/nALVAC0JBYKZiXBQwvLFT6Ln%2BrSlITbR03jcG9rMaxgpxkt7E8qtQoihJABqmA8g0gk6XcTbpoaP60KNhbqpdPl3AA6muBBhcNVBOTFaBxWFCVBcl06eUiRDPh5tC7ftF1eXpwmiXl2GAVJMk7Xtdg0qlAqktpOlqvq6MqpDJXHPKz0lMO9Z42NU3zTNlNzTSVNMSybJsZtakxszG0rayVzAKuhKMAQAlo2TIlifl7l0PDBqYOdNJczztYswKIAgAB4Y45DWNq8CkO9rI4ReEOIWk0Jt1%2BQFg2fGgm5KNFuEfQOX3WT9w4pcDc4fthuGIrLmC84ILMQ8bJVgpE2aPQgHx3JgcGMB7GxdYu3u%2B/z0ZvgFcFtI%2B%2BDIJehCtQwtAtWVFXOsdeX0GixDAD4fNUYHZa%2Bf5qIBXEoiiShUKJ/LKdIhhtCSXEdxtwugPZUh7caAqSo0vs7JK5m2aoLmcKIqQ3lHle/nIFh4eogIBd52uaRtJGBKmahiYBzRNP0RTtNkZG7McXynd8wLGmQ9D4l5hLk/KmSLaECVlTUUrtFbKzmhmLMOY8wy25j7LujMNJaVxnXHsDczZOxCpbYoe0PZrjtvFR2SVnZ/XBkieceCE5wKTv7DQtdxxHi9tQ%2BWaU6D9zXEPbCqBYI5XHr/aes8QDzyIEIYG9Dux0xvn6amt8yRMgZupNaCtlpP05sw1%2Bh1uyf3yqI8WpIZL8P/huVsQCIGo2wKYimkCF66IumSF%2Bfslqaw7KqbGyDrjtkkZNaRd9wzkSjIgpRz91F%2B00cLGGS8Fz6OsdA5e9iQnJ0QZrds5ZDTGjXLYkc%2Bwxz1wghg4hIUAoxSyNWAwtlPZQmEYvGBb4sDpIXEwGIqBo7iLQY8dM4cPz0Btvg4Ua4N57kXMuVOJcXb/Vac5WR3jGJSJmQtBRrMOaKOZrJRMgtA4nRiagWx7ZOzawJgAggtYsk5MbE9NMFZjGEG8ns1BE4DkCHtgbBgJybpeK8fIligS2ZcR4nxN%2BN1tEgL0dJVZKMZyKTcMpf5S1LHSIzEwYAwYkHFjedfaZdEMWzSmZ8x%2B61vlLMWRxYFIMkYHXWUdTZZ1XZC3BNdWl2ogUqxQqCxGYNwXYjRu4u5Li3GotpeWBU4VsiG0tLS956KJU4sWgS1RyzCVMyWQ4/mYSwJArFpJaJ1LOVuGVcooBgFnHdg1tyteDyHwMH1p8I2V8pnvPvmwPFak9WqsZSLU05pomGLcIcuFQYSWCOAVUyJsC5avycaayGUqfGzMxbi2V%2BL5VypdRSrR7rMlesVH/H1VyCB%2BqfOY/NBItk7PiWGxxSTuW8uSaBaNcyPkyqTYmoliaU3v0DkCjNoKqmlt1Qk5RyTXE1puACUdRtyynnPOmbAqhWAvDXOOsdS6gQqjMMkcIXIvBYCkm4D62w0gqvWSCcsQgEDMgIOXI2DaFnrM2ae899Bh3lgAPImQAPpIiveiz5dxtoZ0aY%2B295zZSvviB%2BlU6pwS1sld%2BxtLbURCEwAARy8IwbYqqqVSxpYHW5ar3XMolohlDaH5p/sVAB5FRqrp8pQdaOtca4OKuTf21VQKJIS21XYvt5bEnqQNarU1Q7I0jvuKB4gb6uCvOuNe7hrpCKOBeHgeIglNliYkxBjGWp7V%2BMjBh4D6YqnuloFE66Qn%2BWB3oxNeNTaEPIdQ5ZTAl5rMPD09KWUhmPQ0iI/Z9DZIHgRvbS4zTdHYMKIAFKuvCSRZQiKWUyW8yRmkcmiJKloEp4g%2Bx/OskvGFiNwWTXmZC3ah1AScRtvbECozUTu1QNQFV0N8Dw2VtRWZlBL731mCk1cGTv7/0xEA%2B21THWNOeJg9Km9KiRQJYc65i5nHdn0p5UyuG0Tpu%2BbcGRx8/XKNVu1AV2j5MY1YvmtZ%2BDwSeMAtAmx4GHGsM6r1bC5WhrBM0Y8b8AmQgvBpBwegaEe15Ndc7V9n7f2CJEUI2eggF75pcA0PsMwl4wAcH2EjzS5nyyuiw%2BbEmYqriVax5gl5map5kjUxoGkZhBHmJBErENpP31cBpLDwR9X1lK17WpynZIkco44FT0B7alaHKfQTUHAOjZsf%2B%2BD6JmPWjY%2BcCAVGULIfQ7R21gmco9r8y6/MRwyA30cXiAQCAkx0BKwUJGA3As3Bi6IpeT732ty/al22AUKwn0NzXPwPuFUYaIl13gfXhv2iOgUAgYuHUKqUNQCZZ5zpVzrittuEAkpWh66t0odoJuCBm5ABbtgVuaTtk5zSHnqOwFK%2BLwzpn5OwGs7cFXsDte3Bc4sYr0BDe8b3qh4%2B0CqrBExaRbsgUq9QIO5By7lUbuRdLrHUCE9mAPoLhnXOy9uPdSz8BOr%2B4Dx4Jj3Y1%2Bu1Y2junaY82s/qIJJXErip/Tjw9/IQkvNjxi3rTLfDBLK/N%2BlIq4G4O17Ws3Wx%2B9aoWXyNmTqz8lcl2eO7qu%2BvC7G0ScB%2B%2BwM829iUBj2zKM%2BhwooLugO7qtuBAEmEssuTA8ufgIAGqNISBj%2BAuWBeomukwOuaegeGeRu2eue%2BemAhe8kLuEm9uwOTuBB7I7uWkHAawtAnA/gvAfgHAWgpAqAnADelg1gx0GwWwKEa6PApAeashYhawiEAQkgOIGgAAHGYGYIkIkFwP4KYSYVwKqKqNIBIRwJILwCwBIBoBoKQDIXIQoRwLwAoCAF4ToVoGsHALADAIgCAJlGkMyOQJQNgnQPEJEJGJwKoCYRCN1BCJIHcMAMgMgHcFIDiGYLwNuIQCQHgGblwDIIICIGIOwFIDUfIEoGoJoDoHoFeGFGkJwDwOIZIdIW0fIZwM%2BsyLEemKgFQHcOkZkdkbkfkYUUYZ1hAJWGkEkWfJoSsLwCEWIaQBAEgIkfQGQBQBAAcWMMAFIAjjQERPEIERADEIMTEOEG0CGD0bwI8cwMQCGM%2BjENoIvjoVoZbLWM%2BvnC8boaQFgDEF4MAPaH3IEdwLwFgCwIYMAOIGCfgKuFZNHHCXIZgKoIvsyDsFoeEASM4XIWljEGFJ8R4FgIMU9HgO4fCaQNHMQE0koIaEiUYGlkYG0WsFQAYMAAoNtEpleKBjIVofwLUaIOII0RKc0SoOoGCboNUQYNyaYMoZYPoHgDEIEZAGsDHk0HCd1KbvomqVYJYGYL4cyYqFgDqRAGsHYH8TkC4B%2BDMH4NUaEOECMI5DUOkJkCKrkJ4F0HoMUP6YsKMD6Q6UNAMNMIGQUNUZGU0NGUMJ6UsGMPGVMB0LGW6bYBmWGd6RIPaWodsAWfoP0d4YMX4VMRkVkTkXkQUUUUsbgOUesckFwJsdoTyWsLuHCGMHaaQAYZIMkDiCkI4RoJIGYJIFCBoP4BCIkKWS4W4SAK2TiBCFwBCCYYkHYRCP4JINYSkBCOWWCX4QEUER2boWEZEXsdEaMXEccaccQCkWwJwG0CwHBKqN1OiEKCRLUDiFwMYaUfgEQNaXoLKXUdKdILKYoPKYMboAjp0UwN0fCX0RwFIYeb4cMTeeMZMdMTWexN%2BYkL%2BcYXcMsRuKsYceCGumYO2dsWEfsaRWsfEScfRYcSgCqecVYV4VcafLcfcWCe8c8a8aQPxZ8d8b8Q4IJYCXzMCQXIMRCVCTCfxIJYiciaiXIeiY6ViYMbifiQSIJcSQ0IMeSZSSGNSTsHIXSQyVocyayZgOySpXlDyXwPyYKcKaKYJaBVKQ0RBbIFBa0YqSAAjmxSgNYNYJqdqfAHqQejkIacadJKadYBabwM0vENaXtBFb0I6c4BAK4K6XoB6RUOGcGX6U0LldUSGU0HmcsPGQ0Jlc0BmaVRlVGbmSmYVemYMA1fMO0JVWmYWZsMWW2fOahT4UlZwFWTMTkV%2BflD%2BX%2BUiBAE2UBRRa2dRZ2aQN2f1JQMha4aQO4ckARWOaqP4IkA4ckOOZObuWhSNf4bYKeTRbsZeUgDEbeQkcxckakRwC%2BbMSwAoHBAUXBD%2BUGJMABc2ZUSBbIGBV5U0b5QqXIboKkPBYhb0YNQMUeRhQQGMa1NhZ9d9b9f9VSIwSRc8GsYtckMteebsXRYTYcYxfeSAD9d9m%2Bn9YkG%2BgDYQaoNkXwHQNxZQLxXIcJaCVoXzaJX8RJcYlJSCbJZgJCdCWVHCVocpZyWZQiWeBpWlWCdpcgASXpYIAZWCUZc8aZbSYqJZbwNZVuHZZyQ5WTXyYii5ZgCKX4u5WDZ5RIN5YIFDTBUufoMicFeqTYOSbaZFQaZwLsKbj7WaRYIlfIVaZUWlbqY1U0M6e4FmXlR%2BN1T6eVTkA1RnWUC1fmdVX0AIEmR1TVU1QsLnVVTme1cnW1V1eXT1esH1Q0chUNRWaNWzTkV9T9XcIzTiCzcRfNSQItW2VsStWtb2ZtYuRYTiMkMkIEGObDhoDPaqOuRdUMVdYEcEStQOf4MOfYaqJ4SYZIFYVwGYWYAec4ckMjehVdTRchSUavceWeaEWsMyVkM4JIEAA%3D%3D)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/raillivore/trip/implementation.hpp)
- [Source code](../../../../conceptrodon/raillivore/trip.hpp)
- [Unit test](../../../../tests/unit/metafunctions/raillivore/trip.test.hpp)
