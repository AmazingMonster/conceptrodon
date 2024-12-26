<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::ClassicTrip`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-classic-trip">To Index</a></p>

## Description

`Pagelivore::ClassicTrip` accepts an operation.
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
ClassicTrip
 :: template<auto...> class...
 -> template<typename...> class...
 -> ...
 -> Commitment

-- Compose with Page
ClassicTrip
 :: template<auto...> class...
 -> template<auto...> class...
 -> ...
 -> Commitment

-- Compose with Road
ClassicTrip
 :: template<auto...> class...
 -> template<template<typename...> class...> class...
 -> ...
 -> Commitment

-- Compose with Rail
ClassicTrip
 :: template<auto...> class...
 -> template<template<auto...> class...> class...
 -> ...
 -> Commitment

-- Compose with Flow
ClassicTrip
 :: template<auto...> class...
 -> template<template<template<typename...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Sail
ClassicTrip
 :: template<auto...> class...
 -> template<template<template<auto...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Snow
ClassicTrip
 :: template<auto...> class...
 -> template<template<template<template<typename...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Hail
ClassicTrip
 :: template<auto...> class...
 -> template<template<template<template<auto...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Cool
ClassicTrip
 :: template<auto...> class...
 -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Calm
ClassicTrip
 :: template<auto...> class...
 -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Grit
ClassicTrip
 :: template<auto...> class...
 -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Will
ClassicTrip
 :: template<auto...> class...
 -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment
```

```Haskell
-- End in Conjuration
ClassicTrip
 :: Commitment
 -> template<auto...>

-- End in Transition
ClassicTrip
 :: Commitment
 -> template<template<template<auto...> class...> class...>
```

## Structure

```C++
template<template<auto...> class>
struct ClassicTrip
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
/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** Oper_0 ****/
template<template<auto...> class Sequence>
struct Oper_0
{
    template<auto...Agreements>
    struct ProtoPage
    {
        using type = Sequence<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
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
using SupposedResult = Shuttle<10*2, 10*3, '*'>;

/**** Metafunction ****/
using Metafunction = ClassicTrip<Oper_0<Shuttle>::Page>
::Road<Oper_1<10>::Mold>
::Sail<Oper_2<'*'>::Rail>
::Commit;

/**** Result ****/
using Result = Metafunction::Page<2, 3>;

/**** Tests ****/
static_assert(std::same_as<Result, SupposedResult>);

// The following `static_assert` shows how the operations are composed:
static_assert(std::same_as<
    Oper_2<'*'>::Rail<
    Oper_1<10>::Mold<
    Oper_0<Shuttle>::Page<
        2, 3
    >::type
    >::Page
    >,
    SupposedResult
>);
```

- In the second example, we will transport the conjuration function to `InvokeRail`.

```C++
/**** InvokeRail ****/
template<template<auto...> class PageArg>
struct InvokeRailDetail
{
    using type = PageArg<2, 3>;
};

template<template<auto...> class...Args>
using InvokeRail = InvokeRailDetail<Args...>::type;

/**** Result ****/
using Result_1 = Metafunction::Sail<InvokeRail>;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult>);
```

## Implementation

Since every member template of different signatures is given a unique name, we know which member to pull out when asked for a template of a specific signature.
For example, we can compose a `Page` and a `Road` in the following way:

```C++
template<template<auto...> class...Args>
using Metafunction = Road<Page<Args...>::template Mold>;
```

Note that

- `Road` has signature `template<template<typename...> class...>` and
- `Mold` has signature `template<typename...>`.

This means in terms of signatures, a `Road` can always be invoked by a `Mold`.

We will implement `ClassicTrip` by performing recursion manually, meaning the function will recurse only once for every invocation of a member template.
We will showcase a simplified version that handles `Mold` and `Rail`.

Note that in the following code,

- `Radio` is a `Page` and
- `Car` is a `Mold` or `Rail`.

```C++
// `Radio` is a `Page`.
template<template<auto...> class Radio>
struct ClassicTrip
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
           // Then, we invoke `Car` with the type result of the obtained `typename`.
           template<auto...Signals>
           using Page = Car<typename Radio<Signals...>::type>;
           
           // Helper function for the member template `Sail`.
           // This function transports the conjuration function `Page` without invoking it, 
           // allowing further process by other higher-order functions.
           template<template<template<auto...> class...> class PageVessel>
           struct Detail
           {
               // We transfer the conjuration function `Page` to `PageVessel`.
               using type = PageVessel<Page>;
           };

           /**** Transition ****/
           template<template<template<auto...> class...> class...Agreements>
           using Sail = Detail<Agreements...>::type;
       };

       /**** Continuation ****/
       // This function composes the conjuration function `Page` and the `Agreements...`.
       // Note that even though `Agreements...` is variadic, it only allows a single argument.
       // This is because `Agreements...` will be used to invoke `ClassicTrip<*>::ProtoRoad`,
       // which has only one parameter `Car`.
       template<template<typename...> class...Agreements>
       using Road = ClassicTrip<Commit::template Page>::template ProtoRoad<Agreements...>;

       // This function composes the conjuration function `Page` and the `Agreements...`.
       // `Agreements` will be used to invoke `ClassicTrip<*>::ProtoSail.
       template<template<template<auto...> class...> class...Agreements>
       using Sail = ClassicTrip<Commit::template Page>::template ProtoSail<Agreements...>;
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
           template<auto...Signals>
           using Page = Car<Radio<Signals...>::template Page>;

           template<template<template<auto...> class...> class PageVessel>
           struct Detail
           {
              using type = PageVessel<Page>;
           };

           /**** Transition ****/
           template<template<template<auto...> class...> class...Agreements>
           using Sail = Detail<Agreements...>::type;
       };

       /**** Continuation ****/
       template<template<typename...> class...Agreements>
       using Road = ClassicTrip<Commit::template Page>::template ProtoRoad<Agreements...>;

       template<template<template<auto...> class...> class...Agreements>
       using Sail = ClassicTrip<Commit::template Page>::template ProtoSail<Agreements...>;
    };

    template<template<template<auto...> class...> class...Agreements>
    using Sail = ProtoSail<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKz%2BpK4AMngMmAByPgBGmMQSAJwAzKQADqgKhE4MHt6%2BAUEZWY4CYRHRLHEJXCm2mPalDEIETMQEeT5%2BgfWNOS1tBOVRsfFJqQqt7Z0FPZODw5XV4wCUtqhexMjsHAD0AFSHR8cnp0e7JhoAggdHANQAkixp9GyCTE13xxfXt2f/Zx%2BV0uN12dxMADYNAAlJj4VCQjR3PAKO5McFQ5RMYCYREAOhBBEwzwMRJMyTcRJJH1xFKYXiIeKZ5Owd2QBgUqNh8JZIMmxC8Djubg5WWQABViHg0iCTAB2KzXO7Ku5/fZ3AAimBoETu0NQcK%2B5xBKtVYMRbjaiORqPRiIAsp50PiTSqqS8aeTKcSPWSKQQAJ5pRisTBMgnJVnspic4VWyOu5X8wUEO7KYioIj6uGJ8EK3MqtXC1AsFiEN6p74FpMEAVCjylwjVvOKq6m9vKoseBjaTYfHJGw5Ajvt3bmqHcpzWwzoDEaS3EafETBskvFTCzhDxMPN01ju4AMTwxEmpDuAHcV%2BF5oI8DS55OEVC0QxZ6gYq1wmi54Hg8w2C6SojoWYLiluDBnpeyIMAAbqgADWK4Wlaz7noQCB3AQW6YUGK7LgoXi0KmqBUJh2Hvp%2BESzoiv4hgBUIEkBwGYT6pK0paDKoOGQh4MAzC0AovJMcBXhZEYabYkhyQanGi7%2Brh/4ro%2BXo8XxYgKOGLIgCAtG8skrbMcqu4gXcAASDTBsQdxUF4DAOAO/BWVhK5sFU8QsdSRJzkITB0IBbaGfuYEotZtn2QImHEIYCgZO0qLOauPZ9p8Nl2Z8iJYji1poVhGypuEcHweEwDIgQZ7GZ2YJiLQqBoeJNntFuVlpBm2yxjEAZ3JmTV3AgvFNQAtCQWBWal4UMBpFUeb67HumxXpzZ6dKcZpkZsqKq1RqKEk4gAapgnINEJAXMcmQpap%2BtBTfKBmGXuYIAOorrW0VUO5CVoElUUpWF6WYpJ1pEHOmWYPth1XQxU2mqJxU4cG4LSTtoMHXYXog3pt3MfKGrkq2U1FpK0XZBFVbCSOi1%2Bt6nmzaxS0cYyzJrdGnKbetMYaUyVzAMuxKMAQgkJmTHYw%2BJPl0AjMkXb5V0UlzPMVhzEbYNpun6c22O47KQuqscxa3gwXj9iTxra0FfWomNnxoM8mQHWRK6fb230Ob9A4ZQDz4zvbc5y5gvOCIr/kjvukSZs9CAfHcmAwYwZEbMAGGIr7/v85pz4hTBbR3vgyBnoQXUMLQnXVbVtp3GJwD0GixDAD4fOMSd913MFqIhXEoiiUhULJwradImhtC0HccR3J3s5AwVCFd/Oop4BKUoyhS%2BxaSA6aZqg2bOlCpDNvu559cgGER6iAhFwXK5pG0oZElZyGLpD2sUzT1MLQpoas8zis93zAvYM2IslU3hLYUs957Si9A2MsBAVa0y8ujSMMDqZpgzFmA0zpZbcz9r3Rmf81bXF3qBc2oU0oDmtuueK2FHbJRdiQiK7ssqe1fN7JOmCU6Bwfo3EyLD5Y/2ynQIeI8x6YVQNBQq08RTsznpKcBS8V5ryIGLWgDdyawOfjNBaqivT0gZkrNmLMcF6K/qwhWx0RwALuIo4BEjORSIXhAksUDEEzSRivJ%2ByD16KK9N/AOm1NbCQ1ng4Ewkn4aJfvJP878DGf3DN4/mpiVTmKAeSGS8iN5oK8cYn%2BvjAm5iLFqHUK5LGk0bmbEKlsBwhQSlkMsBgnLYQyigtJOZnxYAKbOJgMRUAx2USZB4qYI6vnoBQh2MYVz723HOBc1oQp2gnNLIObpNH%2BiWVTdRy0dEskMR/baUzBaNzOqmVJnj/H5lNrrSB5Y%2BaDn2MODsBziyNgIOrU5nCOxdgEE7I2DBrm3OYiE9ZXEmSqX4r/Ka5iQZWPjG4ZSFJgXqU2k4tiLiEw5O1qaf5qz5rLLCfTQFujolRO2iDMGqM9l3XuVLPyaKVQ3ShsqcxtFgHEpRkdCk8DcGY2AgEvG1LOy60JhNYm3zil3QxWKlZ2i8WbIJfijanNMkB3icxcxljkmakwJdDJPCfE4JVrhPxry8w41RYa95%2BtDafBFR2cVOLaKKW2ezGJCq4lkuFhXPUaCrGgOkYvNwFzoE6VUci5WgakGpM3lqrBWScEGubDatZmK6aSodfo2Vjr5XapdX/bWKrpZeskWA31/rEX3nZSWuBjTPEYMzYHFFnLuVa0bvGrFibKbJsJemtNqbYmguErm8WaqjnzOrVGnVStY1ymNTym4AJZ3FKLEeE8qZsCqFYC8Fc8651bqBLKMwyRwjsi8FgBGbhPrbDSFmxtRYhAIAZAQKuxSMXtvHdce5N6730Fjb8XWAB5SyAB9JEj6VlPpWh22MQhMAAEcvCMG2Mde5f74iAdlC89FEqwN4h7Uq8utYUzuKIOjE5nLobusZWqyDMG4PsR7dk%2Btk6v1Nowzo7Drr6XuohYOxp8C3C0ZjTkhjJqixIeIP%2BrgPzCTMZEfaQijgXh4HiAhvDQoRNidQ5ysVb8AJsdw3WQ5jTHS0GovmQT070O2qkym1ElHYN2UwGeZ9DwcP3NSYZ9BbgbPUa9A8bJ2bG60sfpZpkAApHDCSOOSWAZ5uzXoZNEWlLQBTxB9g%2BaZGeYLdHcwNvwcEkDWmwwZtHZevt7q3NMoM06SNbDMv4NM1e39AGzASeuKBoGu0s4dM/XsxDjX1O5mbUmzD0rtrRfgzpilGr5nEd3Ay3CUXoO2bG24drUpOu0g5VlurOWmMWZxc%2B4bnbWN%2BdI7DWEA7EaUplrx51taQ2qzxltoJM77hCC8Gkdc6BoQHVk81q4Kq3sfa%2BwRIiUXb0EHvexLgGh9hmDPFD/YqQ7hgA4PsZHGN6v3HtJN8pxshwgnMVj1oOPvlqusWKH1XpVMaBUmDiHciAZ7O0hGikqmuBeihyvNzx1tJVrcKpswXpkeo44CvM7Ms/PaX9YxosQOfvFMSd9kHarCdMGJ9pHjsO7jJHR9tgmB1%2Ba/fmI4ZA/72bxAIBASY6BtIKFDKbgW0LFdlQsQD22n2ncshWNLwhK5%2BCD1qrDRERu5726UO0a0CgECl16rVb2qBLJfNtMuVcNslDW75K0Y3ofzeW4INbkAtu2D269LmfnguUdo4QSAMXJfhKs/Z9TqvXOKSl4A43jztOushp47uTX2v/FV90gP7vANh872Eq997bvZdEVlJGL3Qmt3bpBNezAn1ZwrrXQ%2Bk2z2l8Ah3d%2B%2B4DxYJTzF79gbbahtMyJZJK4NclN6ceCfxCYvLt9ZK7DcjiMQZ3%2BAF6PvOuwIj2kmu2Ca%2B21%2Bh2Ncvaf27qx%2BYiZ%2BaqcBp%2B0sb%2BssUBCKOk%2Bqi%2B9wM%2BlYO%2BCuwOBAYmwCKuauIAvOSBL%2Bw6G2uu/K%2BuhumeIeZu7Que%2BehemAxeFIuBYmZ4k%2BgOHu8%2BuMHAawtAnA/gvAfgHAWgpAqAnAbg1g1g5cGwWwSEe6PApA0CUhwhaw8EAQkgeIGgAAHGYGYIkIkFwP4EYYYVwHKHKNIKIRwJILwCwBIBoBoKQJIdIbIRwLwAoCAO4ZoVoGsHALADAIgCAHlGkAyOQJQGQnQPEJEKGJwKoIYRCANBCJIHcMAMgMgHcFIHiGYLwBuIQCQHgNblwDIIICIGIOwFIJUfIEoGoJoDoHoOeFFGkJwDwCIWIRIc0TIZwD%2BgyFEcRKRCkWkRkVkTkXkfoU1hAA2GkPEbfGoSsLwIEcIaQBAEgHEfQGQBQBANsWMMAFILDjQERPEH4RADEH0TEOEG0AGJ0bwDccwMQAGD%2BjENoGvpoeodbBWD%2BoXPcVoaQFgDEF4MAJaIPH4dwLwFgCwIYJXDsNIfgMuPZDHJCdIZgKoGvgyDsOoeEESA4dIYljEFFC8R4FgH0bWHgC4VCaQDHMQJ0koFqLCUYIlkYM0WsFQAYMAAoLtApueEhpIeofwFUaIOIHUcKQ0SoOoICboBUQYGyaYJYNYPoHgDEH4ZAGsPHk0JCQNFbskoqVYJYGYF4XSVKFgOqRAGsHYJ8TkC4K%2BDMH4BUaEOECMG5DUOkJkEKg6XoMUEKosKMO6daeNAMNMJ4F0HoEGU0CGUMC6UsGMBUfMKGfkI6bYFMDGRUAGRIFacodsFmfoD0R4X0d4XcGMekZkdkbkfkbMbgCUUsckFwCsRoeyWsFuHCGMJaaQLoZIMkHiCkHYRoJIGYJIFCBoP4BCIkPmY4c4SAPWXiBCFwBCIYYkNYRCP4JIBYSkBCIWYCd4b4f4U2VocEWEZsREUMdEXsQccQIkWwJwG0CwDBHKANOiNGOJLUHiFwAYUUfgEQGaXoBKdUWKdIBKYoFKX0boLDm0UwB0VCd0RwOIduV4QMWeSMSWakWWWzK%2BYkO%2BQYXcHMWuIseCHumYI2WscEVsfhTsTEfsRRWMC%2BUceYe4acTfBcVcYCU8XcQ8aQOxS8W8R8Q4JxT8XzH8UXH0cCaCeCQJJxTCXCeIICUiTaaiX0RiViUSJxXiQ0H0USSSQGGSQiasVKNSeoXSQyZgEyTJcVOyXwFyTyXyQKZxf%2BaKbUUBbICBU0TKSALDvKcYAoZYCqWqfAJqRejkDqXqdJAadYMabwF0vEGaQdAFb0Dac4BAK4N6U6a%2BP6W6T6Z6U0KlR6SUDkBlcsAmQ0Ilc0GmblZGf0GmYVfGamYMBVdVbGZmQ2esJsLmS1Q4fBZ4VFZwKheMZkXRXkVhR%2BUiBADWT%2BYRfWSRc2aQK2SNJQLBU4aQC4ckFhQOXKP4IkLYckIOcOeuQhT1T4bYPuaRRsceUgJEeebETRVeUkRwHeRMSwAoDBLkTBG%2BWxJMF%2BbWWUX%2BbIABU5fUa5dKdIboKkJBdBV0ZOV1UWUhQQMMV1KMY9c9a9e9TSJMLhfMQReYMkMkNNYeRseRc8IsVRZeSAC9e9v%2Bm9YkP%2Bh9UQaoBkXwHQMxZQKxdIdxQCeoezbxZ8QJQ4kJf8aJZgCCWCdVJCeodJSyXpUCceApXFYCcpcgNiWpYIBpYCVpXcbpRSQZZxcZbbGZSyRZfjZydiDZZgPyX%2BPZX9Y5RIM5YIEDWBTOfoHCSgD5TYESRaYFdqZwLsFbi7UqUaSaTFWUXFRqQleNHae4GGQUGlegDVe6b6TlVHSmQnQVU1ZlcVX0AINGRVSVcGY1RmenXVUmeGQmfna6UVdmW1bUbBdDTub1fTZkU9S9XcFTXiLTbheNSQJNQ2asTNXNe2YtdOaYXiDjYEAOVDhoDjXKIuQdf0UdX4QETNV2f4L2TYXKG4YYZIOYVwMYWYFuQ4ckL0XXUdaRbBYUbPbuQeUEWsHSVkM4JIEAA%3D%3D)$Done$

## Links

- [source code](../../../../conceptrodon/pagelivore/classic_trip.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/classic_trip.test.hpp)
