<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::Trip`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-trip">To Index</a></p>

## Description

`Mouldivore::Trip` accepts an operation.
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
 :: template<typename...> class...
 -> template<typename...> class...
 -> ...
 -> Commitment

-- Compose with Page
Trip
 :: template<typename...> class...
 -> template<auto...> class...
 -> ...
 -> Commitment

-- Compose with Road
Trip
 :: template<typename...> class...
 -> template<template<typename...> class...> class...
 -> ...
 -> Commitment

-- Compose with Rail
Trip
 :: template<typename...> class...
 -> template<template<auto...> class...> class...
 -> ...
 -> Commitment

-- Compose with Flow
Trip
 :: template<typename...> class...
 -> template<template<template<typename...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Sail
Trip
 :: template<typename...> class...
 -> template<template<template<auto...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Snow
Trip
 :: template<typename...> class...
 -> template<template<template<template<typename...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Hail
Trip
 :: template<typename...> class...
 -> template<template<template<template<auto...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Cool
Trip
 :: template<typename...> class...
 -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Calm
Trip
 :: template<typename...> class...
 -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Grit
Trip
 :: template<typename...> class...
 -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Will
Trip
 :: template<typename...> class...
 -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment
```

```Haskell
-- End in Conjuration
Trip
 :: Commitment
 -> template<typename...>

-- End in Transition
Trip
 :: Commitment
 -> template<template<template<typename...> class...> class...>
```

## Structure

```C++
template<template<typename...> class>
struct Trip
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

- In the first example, we will compose `OperationA<Capsule>::Mold`, `OperationB<10>::Mold`, and `OperationC<'*'>::Rail`.

```C++
/**** Capsule ****/
template<typename...>
struct Capsule;

/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** Oper_0 ****/
template<template<typename...> class Container>
struct Oper_0
{ 
    template<typename...Agreements>
    using Mold = Container<Agreements...>;
};

/**** Oper_1 ****/
template<auto Multiplier>
struct Oper_1
{
    template<typename>
    struct ProtoMold {};

    template<template<typename...> class Container, typename...Elements>
    struct ProtoMold<Container<Elements...>>
    {
       template<auto...J>
       using Page
       = Shuttle<Multiplier*Elements::value..., J...>;
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
using Metafunction = Trip<Oper_0<Capsule>::Mold>
::Road<Oper_1<10>::Mold>
::Sail<Oper_2<'*'>::Rail>
::Commit;

/**** Result ****/
using Result = Metafunction::Mold
<
    std::integral_constant<int, 2>,
    std::integral_constant<int, 3>
>;

/**** Tests ****/
static_assert(std::same_as<Result, SupposedResult>);

// The following `static_assert` shows how the operations are composed:
static_assert(std::same_as<
    Oper_2<'*'>::Rail<
    Oper_1<10>::Mold<
    Oper_0<Capsule>::Mold<
        std::integral_constant<int, 2>,
        std::integral_constant<int, 3>
    >
    >::Page
    >,
    SupposedResult
>);
```

- In the second example, we will transport the conjuration function to `InvokeMold`.

```C++
/**** InvokeMold ****/
template<template<typename...> class MoldArg>
struct InvokeMoldDetail
{
    using type = MoldArg
    <
        std::integral_constant<int, 2>,
        std::integral_constant<int, 3>
    >;
};

template<template<typename...> class...Args>
using InvokeMold = InvokeMoldDetail<Args...>::type;

/**** Result ****/
using Result_1 = Metafunction::Flow<InvokeMold>;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult>);
```

## Implementation

Since every member template of different signatures is given a unique name, we know which member to pull out when asked for a template of a specific signature.
For example, we can compose a `Mold` and a `Road` in the following way:

```C++
template<auto...Args>
using Metafunction = Road<Mold<Args...>::template Mold>;
```

Note that

- `Road` has signature `template<template<typename...> class...>` and
- `Mold` has signature `template<typename...>`.

This means in terms of signatures, a `Road` can always be invoked by a `Mold`.

We will implement `Trip` by performing recursion manually, meaning the function will recurse only once for every invocation of a member template.
We will showcase a simplified version that handles `Mold` and `Rail`.

Note that in the following code,

- `Radio` is a `Mold` and
- `Car` is a `Mold` or `Rail`.

```C++
// `Radio` is a `Mold`.
template<template<typename...> class Radio>
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
           template<typename...Signals>
           using Mold = Car<Radio<Signals...>>;
           
           // Helper function for the member template `Flow`.
           // This function transports the conjuration function `Mold` without invoking it, 
           // allowing further process by other higher-order functions.
           template<template<template<typename...> class...> class MoldVessel>
           struct Detail
           {
               // We transfer the conjuration function `Mold` to `MoldVessel`.
               using type = MoldVessel<Mold>;
           };

           /**** Transition ****/
           template<template<template<typename...> class...> class...Agreements>
           using Flow = Detail<Agreements...>::type;
       };

       /**** Continuation ****/
       // This function composes the conjuration function `Mold` and the `Agreements...`.
       // Note that even though `Agreements...` is variadic, it only allows a single argument.
       // This is because `Agreements...` will be used to invoke `Trip<*>::ProtoRoad`,
       // which has only one parameter `Car`.
       template<template<typename...> class...Agreements>
       using Road = Trip<Commit::template Mold>::template ProtoRoad<Agreements...>;

       // This function composes the conjuration function `Mold` and the `Agreements...`.
       // `Agreements` will be used to invoke `Trip<*>::ProtoSail.
       template<template<template<auto...> class...> class...Agreements>
       using Sail = Trip<Commit::template Mold>::template ProtoSail<Agreements...>;
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
           template<typename...Signals>
           using Mold = Car<Radio<Signals...>::template Page>;

           template<template<template<typename...> class...> class MoldVessel>
           struct Detail
           {
              using type = MoldVessel<Mold>;
           };

           /**** Transition ****/
           template<template<template<typename...> class...> class...Agreements>
           using Flow = Detail<Agreements...>::type;
       };

       /**** Continuation ****/
       template<template<typename...> class...Agreements>
       using Road = Trip<Commit::template Mold>::template ProtoRoad<Agreements...>;

       template<template<template<auto...> class...> class...Agreements>
       using Sail = Trip<Commit::template Mold>::template ProtoSail<Agreements...>;
    };

    template<template<template<auto...> class...> class...Agreements>
    using Sail = ProtoSail<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKz%2BpK4AMngMmAByPgBGmMQgZhpcpAAOqAqETgwe3r4BQemZjgJhEdEscQlJKXaYDtlCBEzEBLk%2BfoG2mPYlDE0tBGVRsfGJybbNre35XQpTQ%2BEjlWM1AJS2qF7EyOwcAPQAVMcnp2fnJ/smGgCCRycA1ACSLKn0bIJMfQ%2BnV7f3F0BFz%2BN2ud32DxMADYNAAlJj4VDQjQPPAKB5MSEwgCynnQyIAdGCCJhXgYSSYAMxuElkr6YKk0gCeqUYrEwBM5VOwD2QBgU6PhiO5YPmxC8DgeABViHhUmCTAB2Ky3B5qh4Aw4PAAimBoEQesNQCJ%2BlzB6o1EORbhayNR6MxyNxtHxMKJqvVtLe9MZXvJDOpBBZbLYnKJlJ5fKYAoeNuIIo9arFEoID2UxFQRCNCPN6qVKpuFvVmtjqBYLEIH1Tv1zReTko85cItYt%2BZbRbVJY8DG02y%2B2VNxxBHaL%2BytMKFTjthnQWI0cenxEwvLLRUws4Q8Q57Y7Y4eADE8MR5qQHgB3ZfheaGRz0ueTpEwjEMWeoGLNcIYudB1nMNiEndRwhKVNwYU8L1RBgADdUAAa2Xa1bSfM9CAQB4CE3B4lwULxaEcIxv2DP8GTdQCLT9H1AyI9kwyEPBgGYWgFATQsR3VLxMgI51ZypbVY1takH0ZOiGLEBQwxFCMqQLNi80TNi9wACR6VliAeKgvAYBoBHUkh0MwtgVjUiiSTnfdaFQM8APkkc9xAtF1M07SGHQ4hDAUdJWnRDDlzQHs%2B2%2BDStO%2BJ08TtFCMK2VNwhg2DwmAVECFPMjiwhMQLJQgiNNaTc1NSDNdhjGImQeTNcoeBB6NygBaEgsDUoLnPElK1RMgMaVJb0KUDTr/V9ajQy5CNeX5cShsjUaHm4gA1TABR6FjZKTAhxUlXUP1oFrIWVLaLT3AB1ZcVvcqh4n03yBF7NzAqckKcTCp8iDnGa5rsazWKW9jOISn8EMpPiXvmzbqW4ySZKWpVtWkhUbN3U5pTchhigHGtYaLNrfV6yiOrpbrmV/GjxpG6MxvDCaSbDG5gCXUlGAIZipLRi0OPig8Mshf6dUwDbGSpmmq1J7kQBAX7obRyGxdBNGu1kcIvH7HTUY%2BvbgMq9FGu%2BNBXgyObzpXfzroHDWB1Cl1pxfPXkT5zBacEQXSOliFIkzI6EC%2BB5MCgxh9K2YA0Kt6mbYFiSnwcqCWjwBE8GQU9CFKhhaBK9LLIdB5vvoDFiGAHw6fdZXUulNX7QeOJRA4hCYWt236ZDlEUNoWgS%2BXcvZyemK4IrjQZTlRlDiFkB00zVBs1dDRSEAvcz0q5A0Ld9EBET%2BPl1SFp2RJNTEPjB389arG8YxqiCcGsniYFSnA%2BrhnsEAlmCJHjm%2BO7%2BVqUbCsCGFtqprCiMP735dB6zMafE1Iq7B3GpLCeqsHLGx0lrNc3lMJ%2BSugrFyMCXKm1Hs%2BVumEA78zpvbDQedbLjluBfAW4U6CNziA8Fu6FUCQVip3J%2Bvd%2B4ANQEIJgdAiEdgPjjLq7VeFMC8EQCSw0oxnyJuI0moD8GLQ7LfBKHC6APwRj3F%2BZY36/1xsuUGP8RZ/zTBmIgSjgZuBkXbUR19KTgzVBLaxMNla8KcQNDkkjRrnzwXbORaoFGGiASothI9eZkPwZYiB8kSy6n1MuExg5DjDgLvZdWt0BwOR8mnPAFYDDGRwTCQJQC7RYGibOJgMRUBe24Z2CETxUxuxfPQBBvlozLinluOcC5Q6p2RPCOg71yJ/0xtowZ/DGRCJEW4imEyYwLkZsresqY2EmJbG2aW8NX6VjpnEhJdYVoplLE2AggEVk71HGsy6AUUZmiZp6AZh8QyuIJCJRiV8tq%2BO4iomZbghLUieWJSxWj%2BFpiYMAAMViCxbScbcvhfU7nEUsafQWYjJqAzerMz68yuY82ubYna2LmbfXQsGFRKKFog2/mCradjwV4pLDKdyWRFZXJOf0oZPVWXQuxr9OFUzEXkwkQScx9NvFsV8eZSyKj1qcNMYK3lH9gySxHFShxtkzmCDligrZgFIXsq5YTE%2BUiPFB1kWi%2BRBL768VUc/Nw6z376O0V/M2ejP75JzCAkJFjwH2NuFqqF2qRnUjGageFBqeWGsvsKr6rNYkWuYeog5AL/QOuAdgBNd5FlSuCZ4munqbHbShl6qWjjfXFvZYG4N7jQ2chlcK3x0bObpt6W6rNvKIGKnzdSu4QIu1KxLIeY8qZsCqFYG8ZcPbu3jpBAqMwlJwh8i8FgDmbg/K7FSEK2ZYIuxMFSDhDOStnFHweSxDFNpt24QDB2ksQgEDCIILuplgjhFBvAbcDFV6b30HCZ2x4AB5VSAB9FEe6S3%2Bvxvc8tJNSyfCWPGWZGLf3xAAwqZUkJ5L7rA1W91a7r7yTeXiD5shOERBg2YzDLaC1Ku9f8eG8HiB/q4Jq24D6nrYlwo4N4eB4hHt2ZKGjdGkO5rQ8RYVGK2HvLbG2z9LKQOCb1dyBFkGPxEdPLq4%2B2B3jGuw3M7jCyjGoF0dagj0HGRqcvmEk1OLc03NLY%2BsMAApCNPiCXKGBQycWnM30EFve1FjeE5S0A48QQ4JmBbC3Dt4B5p5bNmdzRRwtUmYWge5QK0jNaCVifrbp/TMrotIfbQ4ksvGzAMZuEx%2Bh00I6lI/bB7TDxCv8ZbH6hLZaeUPCEJgAAjl4RguxhM1clb0%2BSxyRUEt%2BiotrnXuvtXK7KSroKFV5gk%2BR1DwGms2crcl5tqXWY9Mbha/r0rSP/JFvK8ji2L3wyEF4VIa50Cwjmqx4rtars3buzu1MFqPNecZFwDQhwzCnh%2B4cSkp4wAcEOKDsG%2BX4bYm5kwNBj20uw/hzG2UVreMaEZCendoLha6M08LIJ1JeNcG%2BxjvReOwTCyWUT/9ZhGSg/BxwfuO2WLCxtZ%2Bksr2HtK18VzvCxKkcpOcCAUG3rqQtnmOgYW4QSTUzEH%2Bvy15BCMhl6eOnEZx7yUl9LwQmA5e0AVwIJXhzqSq4eJSFikPKNfuONKOa9NivXkcMgP9JN4gEAgNrkACh2Su4Zl8%2B7eFTyXeuzrW7geTfYDWBz1Wy5%2BAN0sqzZETvo5%2B6UK0O0CgEApwquK9JqBVIoIdEuFc2slBS9FM0Z3af3ee4IFL73vvoyMhbHV6kDOId6JZ%2BL%2BSxPSf93063/9ZPrVbuxwP7%2BbgyJe5l3rtyBvFfNGV6bwQavuSa%2BZTP3X%2BvDdIyXybtwZuLfmY5pp1sejnMguWRrlsIeXsR4VBGaPS2bfjqBCCS99QBCzkHcOu9Q4N039u1J0qNHgnhoIO53kgMdVfUXFwMYxuIbgs4uNVpUxwDGFuJ9t6scMRsiULVEDkDBse9N968ddZd59d9jcVdV8Hh1dsAN82It9yD5dF8bxqCkpzdhUrdQQzsHFGtOU4D1skDgAXlbhfF0DIC8MLUJD4JMDYdG0zEs5ZVjtWQOd4Y%2BdqwmVecI86MBdmg0FhYxUrJqQZDMAKcX9aV7dHcq9U83dWg68G8fc2A/dGQNC6Ng9nsw8NDuRn8LAOANhaBOB/BeA/AOAtBSBUBOAp9LBrA04tgdgEJp0eBSB34wj/CNhYIAhJACQNAAAOMwMwAATkKK4H8DyNyK4EVEVGkECI4EkF4BYAkA0DHlCPCMiI4F4AUBADHlSK0A2DgFgBgEQBACilSGEXIEoDgToHiEiHZE4FUFyKhGqihEkAeGAGQGQAeCkAJDMF4HXEIBIDwClxSH4EEBEDEHYCkBkEEEUBUHUDSNIF0BSDPDclSE4B4ACKCJCM0F4HaO/WETGNTFQCoAeAWKWJWLWI2K2OyKKwgEbFSGmI3iSLWF4F6P8NIAgCQCmPoDIAoAgGxLGGACkH%2BxoDwniC6IgBiB%2BNIBiHCBaCZHeN4FpOYGICZG/RiG0HqFSOSK1irG/QTgZIeKwBiC8GABtAbi6O4F4CwBYEMGAHECFKPC5LwC9klPCMwFUHqGET2GSNn1qPCP8xiDclZI8CwGpJWkyUZNIC9mIDKSUF1FlKMH8yMB%2BI2CoAMBEOmg4zPHg1COSNOOEFEHECuIDNuLUGpKeP0DlJQGsGsH0DwBiC6MgA2ALz6ElOqkl14lMBiMsCSF%2BJtNlCwCTIgA2DqGchcBfBmD8BSFCCWAqCqD0CKAZRyE8A6EbIyGbOGHrLGFqB6GVIEAGGmFbPyF7N6EaAWC7NGASFqAWCrL0GvFaEnKMgkFLPiN2BXP0C%2BNIFaN%2BM4FBMWOWNWPWM2O2NhNwAOKRMpC4BRJSNdI2E3ARDGBLNIEyMkEpAJEKMpGqI0EkDMEkBhA0H8ChEKM3LqIaJACvIJChC4ChFyMKIqKhH8EkFKM/KhG3OpPaM6O6NvLSP6KGMxJGIBPGLxIJOIFmLYE4BaBYCgkVGqkxCjAIi4EKIJC4ByL2PwCIELL0ADPOODOkFDKUHDIeN0H%2BxeK3UZM%2BI4GCPQoeL%2BKIqBJBLBMPOJkYuYtYpRDhNXERMhGnTMBvLRP6KxK0pxImPxOMrGAYqJJKLHlJPXgpKpIeOZPpKtKctZPZM5IcCtN5Lpn5MTmpOFNFPFKYitJlLlIVPCPwCXAaFVOpI1K1JJCtL1OpMNONKZFNL2HCItMaKlOtPiDtMwAdLCvildL4A9IUC9MwB9N/CtJ4qDMuP4tkDDPuPCJEqjJdOzKsEsHjMTPgBTNXWyHTMzP%2Bg6usDzIiILKOLml6u6DHOcAgFcDnJrJfCXIbJSCbL6EWrSA7L6BWp7Jmv7P6FnOHOrP2uckHMWHKCnPnKOryBOoXIuuWFWtXO2HXOvNAukp3IiL3KUohMsq2LUpyIeAgHPM4p0qvP0rvNIAfPqkoEkvqNIEaMpGYp/MVH8EKKqMpF/P/OQpkraM4Cwp6JKoGOGNGOIsmPMrIrmI4CoohJYAUCgk2KgiYoJH9HmHYovKOO4tkF4vquuPkEEuap0AgtIDEreKlMko%2Bows4H%2BIIEBNKkUtpvpsZuZtZtTE0teG0vMEpEpAhtwoxKMo1pMpIoppAAZuuz/SZsKL/VVr/VUBWL4DoDssoAcvCNcsFOSLdvcq5K8o0R8oFP8swBFLFPSklOSNCqdIyulKVOiqmoeLiuQG1MSt131N4BSvpPSvNNlGyuSJtPysKqdOKr1vdOBXKu9N9Jqu5rqokAapuIFojOFoMHatjK6sNOLL6rTM4H2G1xGtzLaImqLOmrLL6ArPcGOr0FrMuuXLWu2uyE2vWuyF2unNOr6HOs2qHvHMGEXuusGDXonLrKureoUDXMuIlu%2BNku%2BsVoZoeEtpZvpHmCBpBr0i1uvNRMhuhqfLhvAqKIJG1sCB/J%2Bw0G1sVFgtxt3I6NsGwoMoyJAEkH8A/MqMVGaNyMkBKK4HyLMDQtqMpDPrxvAagdAt2NAa%2BrwchptMyGcEkCAA%3D)

## Links

- [source code](../../../../conceptrodon/mouldivore/trip.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/trip.test.hpp)
