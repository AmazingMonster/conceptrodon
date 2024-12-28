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
Trip'
 :: Commitment
 -> template<auto...>

-- End in Transition
Trip'
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

- In the first example, we will compose `oper_0<Shuttle>::Page`, `oper_1<10>::Mold`, and `oper_2<'*'>::Rail`.

```C++
/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** Oper_0 ****/
template<template<auto...> class Sequence>
struct Oper_0
{ 
    template<auto...Agreements>
    using Page = Sequence<Agreements...>;
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
using Metafunction = Trip<Oper_0<Shuttle>::Page>
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
    >
    >::Page
    >,
    SupposedResult
>);
```

- In the second example, we will transport the conjuration function to `InvokePage`.

```C++
/**** InvokePage ****/
template<template<auto...> class PageArg>
struct InvokePageDetail
{
    using type = PageArg<2, 3>;
};

template<template<auto...> class...Args>
using InvokePage = InvokePageDetail<Args...>::type;

/**** Result ****/
using Result_1 = Metafunction::Sail<InvokePage>;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult>);
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
           template<auto...Signals>
           using Page = Car<Radio<Signals...>>;

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
       // This is because `Agreements...` will be used to invoke `Trip<*>::ProtoRoad`,
       // which has only one parameter `Car`.
       template<template<typename...> class...Agreements>
       using Road = Trip<Commit::template Page>::template ProtoRoad<Agreements...>;

       // This function composes the conjuration function `Page` and the `Agreements...`.
       // `Agreements` will be used to invoke `Trip<*>::ProtoSail.
       template<template<template<auto...> class...> class...Agreements>
       using Sail = Trip<Commit::template Page>::template ProtoSail<Agreements...>;
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
       using Road = Trip<Commit::template Page>::template ProtoRoad<Agreements...>;

       template<template<template<auto...> class...> class...Agreements>
       using Sail = Trip<Commit::template Page>::template ProtoSail<Agreements...>;
    };

    template<template<template<auto...> class...> class...Agreements>
    using Sail = ProtoSail<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKz%2BpK4AMngMmAByPgBGmMQSABwA7KQADqgKhE4MHt6%2BAUEZWY4CYRHRLHEJXCm2mPalDEIETMQEeT5%2BgfWNOS1tBOVRsfFJqQqt7Z0FPZODw5XV4wCUtqhexMjsHAD0AFSHR8cnp0e7JhoAggdHANQAkixp9GyCTE13xxfXt2f/Zx%2BV0uN12dxMADYNAAlJj4VCQjR3PAKO5McFQ5RMYCYREAOhBBEwzwMRJMAGY3ESSR9cZSmF4iHjmRTsHdkAYFKjYfDWSDJsQvA47gAVYh4NIgkzJKzXO7yu5/fZ3AAimBoETu0NQcK%2B5xBCsVYMRbjaiORqPRiIAsp50PiDQrqS9aRSqcSXWTKQQAJ5pRisTDMgnktkcphcu6m4h8uUKgVCgh3ZTEVBEbVwx3y6Wyq6GhVKqOoFgsQhvJPfLOGhPCjwlwhVhU5xv5xXHIsMbSbD45PWHIGt/O7Y1QnlOc2GdAYjTRifETDs4vFTBThDxIMtodggBieGIk1IdwA7gvwvNBHhadOxwioWiGFPUDFWuE0dPff7mGwHXHB/Lh6Ka4MIeJ7IgwABuqAANYLiaZp3kehAIHcBBrnc84KF4tCOEY75%2BgG35QgSv5/s6pJ0qajKoMGQh4MAzC0AosZ5n%2B8peFkuFYji4LkiqUZmpSN5urR9FiAowZ8qGFK5puhoAQAEg0/rEHcVBeAwDi9vwKmoQubBVPEKEeuR05CEwdA/ixrEASKCAoqp6maQIKHEIYCgZO0qK6Yunbdp8akaZ8iJcbiCFIRsSbhJBUHhMAyIEIeskFmCYi0KgiG4Wp7RripaSptskYxD6dxpjldx2cAOUALQkFgKkBU5DDiUl8pka63rGe17o0l6lFMiyobspy4kDWGw3JtimAAGqYFyDTMax8o1kmaovrQLXgjKG1yWCADqC4EK5TVUIZ3loL5rn%2BY5QWYpN5pENOIUzXN61EdtCrsbFKH4TxfFPbNdhuiFkm5otm0qtJUokYOhZim52TOZW0Otm1vWoxR6Nugy/UhmNEYjbjQ348GVzAPOxKMAQTFScj%2BafbhZl0L9qqYGtbqk%2BT5YE6yIAgB%2BdKg620oQ%2BSMm04WHgXgwXg9oj%2Bri2Ctn2Q1nxoM8mSzShaHnV2l1addvbBXdd6TlrsFQhzmAU4I3NvQrdyRGmB0IB8dyYOBjBaxslXTpb1tUxJd72eBbSXvgyCHoQJUMLQxWpellp3BxwD0GixDAD4lPEVZO2AfZ9lxKI7Hm9cZNW1zgdIohtC0HccR3MXU4PVF0El2KEpuvsPMgCmaaoBm9pQqQm4AUednIMhLuogIsfRwuaRtIGRIqXBMZ2znTqdWjW8Y/hX5BqNRNciTZf%2B9T2CbvTcUD8z7eSpSdalgQvPoxNOLd6/vfpjq9qUn7FejUhtcEeis7KohVr2NWy4vLawELrWWDAHKBUNrdd%2BJsHxm19qfABBJ14wxHKXTmlMmJhRrnXBcjcUKoDAtFNu4p75uC7qGXmX9UCM1oNnQcmMOo9QxjvLGVEJKDXDMfQ%2BIiCb/2IQtVsV87jsNvvQt0j9CAvx3m/Ok2BVG8OTKmIg7D2bYOIUIi%2BosqzCyAcCEi3Duqel3p%2BQMxij4SMMTbaRbFk5ah/szVhA8DFEJtsYixVZCxqg1AueRSMc42TAUgxqFpMFZFLAYHSaFgq6P7j/c0WAwlTiYDEVAHtOHJUeEmF2D56AwIXKIJQx4col1nEHROiJYQWTwZvXhbprHWOxtRMRw1HHiP4jGGmOdlo6L7vokizZxbtmUQQcsfZ9gDlbGMuZm5pkb1bBLOBfleyRLBt0wRzIRIMXPhtWRIVmazkEnCcclITliWMVo2x6iQZQ02fmLp/CeG2IETjVkTiBnjX%2Bi9Nxf4xmrXMutWmhoNlgw%2Bh4/m3jJrPUBpSYGUlTEwqbMkEWYsPlyXbHDJqCNEH7MWl8jpPzyJ/N6YTcRQLibMkka4kZYNZHyIpHxSFFk/4uIDqNF%2B%2BELGDnMViyxHztlSxlp8clnzvk2Jpd6PeDi%2BlMrxCyqmYKEVfRvly0UiiH7Fifs8kyGLNF8zUT4zJfL/ECtxkE2mlLfnUq6j0xloj6X9OZfys5tMOVQoUR3I19Zn6Wu0ea01V5WH6NteXIxgDxWwtxY6nOzqlWKrdUcr16qAUMp9Xav1OcA1M31TGqFfj40BMTTJFN4qQRKgBE2oEhZdz7iTNgVQrAXgLkiY2pt/wgRSjMOScIHIvBYB4m4c62w0hapGQ29sQgECMgIKnSJhz/kjLGcu1d9BU2FgAPLKQAPpIg3QqzddK83jSEJgAAjl4Rg2xmJjOPfEM9UoZTgisQq91Baq3zoviRC5k1mZ3sfc%2BiimruaYtrXi95R7T1cEWUCK9dxrRYUcC8PA8RX2HUTHcd9xAT1cC/YLVql6VXfjZfGAjwpWG2loFOZsdb8WGnTVmrdeNIwQafRpTAh5/14geGCsZjG7TCQffxl9lIHiBNo9mLaTq/3ZoAFLavcV9S5%2Bq%2BNQbdJh7CEpaC4eIPseTzJDxqYUxR8GqaONUfsWwE%2BhawWyKYyx3i4yiAecrWfGzX6EPAN%2BO2YjJ6zCocJKph6U1Q55P3du%2BjSYwtmHI1WTjvVhM3vxnI6T%2BnFNJySyzNmUzlMEtkUi3TeWBNuli%2BKeLGiRU4qCxKhzVLM2Zezdlz1MG3MeJabXfVPL1pxv84Kvmwr61scQ0urwaRlzoGhLNLDkXrgcrmwtpbmFsLgZXQQNdFEuAaH2GYQ8R39jkkPGADg%2BxrtvOCzcds1pWZMAgXLfsIJ3Mvbe4g/Vd83RhY0MJPbB3u7mpBLzXxlIwtkcpEd7uvmRm81jW4FLbpru3Y4N3AbzFeZrPrSF%2B4W2VuRNkcTnb%2BrnutB%2Bywu6lJTt3HJPdiVsNZpU1W1ceYjhkAnvxvEAgEBJjoF5goQMvPqZuHJwlORG2NaLeW9hVkKwD2gIXPwGu6UvqIi53gHnfP2jmgUAgBO5V0qYNQMpBBlp5yLnVkoYX/JWjc/F0odoguCDC5AKLtg4u3RVjR5SDHd3mEgBx5Sf3yG3Tw5D4jtwEeP1A/uSDhLFqMVx5hQzpnUyCtg7utn7Aw8SJCFl/bqXUpQzK4J49gdNeW1LswOdKcnbu3rvltXmvzaZv3AeBBVulyL3tavR61EIUrjp3w4KYUPfaEhWG2lkDiKfplsmmP4AbpM/M7FfijLFEsvCO9Rq9ORbZHT772B/Vp%2BYKz5e7ytwq/YMWv5ge9sUuOdk4VwQUjzMqevYNs4EAKOl%2BKgdOJi%2BKrOkwHOOueuc0buQuIuYuEYboUupGh4xe82cuZeFe0kHAawtAnA/gvAfgHAWgpAqAnAcelg1gScGwWwsEI6PApAz8xBOBawUEAQkgeIGgiQZgZgAAnLwVwP4FwYkFwMkMkNIHgRwJILwCwBIBoBoKQEQSQWQRwLwAoCAAoUwVoGsHALADAIgCABFGkIyOQJQFAnQPEJEIGJwKoIkBCFVBCJIHcMAMgMgHcFIHiGYLwCuIQCQHgMLlwDIIICIGIOwFIEEfIEoGoJoDoHoEeK5GkJwDwLgfgYQTEaQZwIeoyMYUmKgFQHcLYfYY4c4a4e4RwRFhAHWGkBYSvPQSsLwFoTgaQBAEgOYfQGQBQBAG0WMMAFIKdjQNhPEOoRADEOkTEOEG0D6EkbwOMcwMQD6IejENoA3kwQwWrOWIejHFMcwaQFgDEF4MAKaDXOodwLwFgCwIYCnDsCQfgPOJpB7CcSQZgKoA3oyDsAweEESJISQSZjEK5PMR4FgOkYdHgLIacaQB7MQPkkoGqBcUYCZkYDEWsFQAYMAAoFNLhkeO%2BkQQwfwMEaIOIOEXiZESoOoDsboIEQYIiaYJQZYPoHgDEOoZAGsBbk0CcVVELlyjSVYJYGYMoZCeKFgEyRAGsHYCsTkC4A%2BDMH4IEaEOECMAZDUOkJkKStKXoMUKSosKMEqWKY1AMNMJ4F0HoLqU0PqUMPKUsGMIEfMAafkDKbYFMOaRUNqRIKKTQdsK6foKkYoekSoQUXYQ4U4S4W4R4RUbgL4bUeSFwPUYwUiWsGuHCGMCKaQGwZIOSHiLweSOIRoJIGYJIFCBoP4BCLwV6VITISAFGXiBCFwBCIkLwSIRCP4JIIIZmRCD6TsSoWoRobGcwTofoS0YYdkSYZ0d0cQFYWwJwG0CwOBMkFVOiOGLhFwLwXiFwJwd4fgEQIKXoMSSEYSdIMSYoKSekboKdvEUwIkacSkRwAQe2coZkUObkfkYUYGUTIucuauUiJUUuDUeCCOmYDGY0Toa0d%2Be0aYV0SBWMAub0QIQoQMcvMMaMTsbMZMdMaQMhfMYscsQ4KhesZTJsbHOkXsQcUcYxKhecZceIDsbceKQ8ekc8a8USKhZ8Q0Okb8f8T6ICdcQ0eKGCQwZCdCZgLCRRbFEiXwKieiZidiahTuQSWEfubIIedEeSSAKdlScYNYNYPSYyfACyXOjkOyZybxNydYHybwAUvEIKbNDpb0OKc4BAK4GqbKQ%2BFqYqeqSqU0I5cqSUDkC5csNaQ0LZc0I6Z5Saf0I6b5VaQ6YMCFeFRaS6dGesJsB6QlZITeUoWZZwP6UUU4VBe4e%2BZwXcBAOGZub%2BVGQBXGaQAmXVJQFedIaQLIeSMuTmckP4LwWIeSLmfmc2beRlaobYN2YBc0f2UgEYcOWYRBWOdYRwFOcUSwAoOBG4eBEuXiORJMOuRGf4dubILuXJREYpWSSQboJdmeReckaWWlb6feQQDkSVE%2BbNfNYtctatUmF%2Bc8D%2BeYOSOSOVb2c0cBW9aBSORNSAAtfNiektbwSes9SeqoI4XwHQPBZQIhSQehdsQwSjZhSsThcanhVsYRZgPsYcalCcQweRfCVxbsXuDRVZTsfRcgG8UxYICxTsWxZMZxcCTxahfxRrEJfCSJT9SidiBJZgFiZ%2BNJdtbJRIPJYIPtceRWfoJcSgBpXSb8cKbpWyZwLsHAcZbyfyRZf4VZcyTZY1JKe4IaQUE5egBFUqRqR5WbfaTbT5XFa5f5X0AIGaSFQFXqbFc6c7VFbaUadad7QqX5W6UlWEVeRdR2ZlTDU4XNQtXcODStbSBAUVRuSQKVdGQ0RVVVUmbVeWXwXiJ9YEDmUdhoJ9ckLWT1RkX1eoZoRVamf4BmaIckPIYkJIAIbUDwW2ZIeSGkVHX1YBVeV4VXZ2T2doWsJCVkM4JIEAA%3D%3D)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/trip/implementation.hpp)
- [Source code](../../../../conceptrodon/pagelivore/trip.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/trip.test.hpp)
