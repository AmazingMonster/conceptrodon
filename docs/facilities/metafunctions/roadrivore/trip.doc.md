<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Roadrivore::Trip`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#roadrivore-trip">To Index</a></p>

## Description

`Roadrivore::Trip` accepts an operation.
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
 :: template<template<typename...> class...> class...
 -> template<typename...> class...
 -> ...
 -> Commitment

-- Compose with Page
Trip
 :: template<template<typename...> class...> class...
 -> template<auto...> class...
 -> ...
 -> Commitment

-- Compose with Road
Trip
 :: template<template<typename...> class...> class...
 -> template<template<typename...> class...> class...
 -> ...
 -> Commitment

-- Compose with Rail
Trip
 :: template<template<typename...> class...> class...
 -> template<template<auto...> class...> class...
 -> ...
 -> Commitment

-- Compose with Flow
Trip
 :: template<template<typename...> class...> class...
 -> template<template<template<typename...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Sail
Trip
 :: template<template<typename...> class...> class...
 -> template<template<template<auto...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Snow
Trip
 :: template<template<typename...> class...> class...
 -> template<template<template<template<typename...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Hail
Trip
 :: template<template<typename...> class...> class...
 -> template<template<template<template<auto...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Cool
Trip
 :: template<template<typename...> class...> class...
 -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Calm
Trip
 :: template<template<typename...> class...> class...
 -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Grit
Trip
 :: template<template<typename...> class...> class...
 -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Will
Trip
 :: template<template<typename...> class...> class...
 -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment
```

```Haskell
-- End in Conjuration
Trip
 :: Commitment
 -> template<template<typename...> class...>

-- End in Transition
Trip
 :: Commitment
 -> template<template<template<template<typename...> class...> class...> class...>
```

## Structure

```C++
template<template<template<typename...> class...> class>
struct Trip
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
/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** Capsule ****/
template<typename...>
struct Capsule;

/**** Oper_0 ****/
template<auto Variable>
struct Oper_0
{ 
    template<template<typename...> class Container>
    struct Detail
    {
        using type = Container<Shuttle<Variable>>;
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};

/**** Oper_1 ****/
template<auto Multiplier>
struct Oper_1
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
using SupposedResult = Capsule<Shuttle<10*2, '*'>>;

/**** Metafunction ****/
using Metafunction = Trip<Oper_0<2>::Road>
::Road<Oper_1<10>::Mold>
::Sail<Oper_2<'*'>::Rail>
::Commit;

/**** Result ****/
using Result = Metafunction::Road<Capsule>;

/**** Tests ****/
static_assert(std::same_as<Result, SupposedResult>);

// The following `static_assert` shows how the operations are composed:
static_assert(std::same_as<
    Oper_2<'*'>::Rail<
    Oper_1<10>::Mold<
    Oper_0<2>::Road<
        Capsule
    >
    >::Page
    >,
    SupposedResult
>);
```

- In the second example, we will transport the conjuration function to `InvokeRoad`.

```C++
/**** InvokeRoad ****/
template<template<template<typename...> class...> class RoadArg>
struct InvokeRoadDetail
{
    using type = RoadArg<Capsule>;
};

template<template<template<typename...> class...> class...Args>
using InvokeRoad = InvokeRoadDetail<Args...>::type;

/**** Result ****/
using Result_1 = Metafunction::Snow<InvokeRoad>;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult>);
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

We will implement `Trip` by performing recursion manually, meaning the function will recurse only once for every invocation of a member template.
We will showcase a simplified version that handles `Mold` and `Rail`.

Note that in the following code,

- `Radio` is a `Road` and
- `Car` is a `Mold` or `Rail`.

```C++
// `Radio` is a `Road`.
template<template<template<typename...> class...> class Radio>
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
           template<template<typename...> class...Signals>
           using Road = Car<Radio<Signals...>>;

           // Helper function for the member template `Snow`.
           // This function transports the conjuration function `Road` without invoking it, 
           // allowing further process by other higher-order functions.
           template<template<template<template<typename...> class...> class...> class RoadVessel>
           struct Detail
           {
               // We transfer the conjuration function `Road` to `RoadVessel`.
               using type = RoadVessel<Road>;
           };

           /**** Transition ****/
           template<template<template<template<typename...> class...> class...> class...Agreements>
           using Snow = Detail<Agreements...>::type;
       };

       /**** Continuation ****/
       // This function composes the conjuration function `Road` and the `Agreements...`.
       // Note that even though `Agreements...` is variadic, it only allows a single argument.
       // This is because `Agreements...` will be used to invoke `Trip<*>::ProtoRoad`,
       // which has only one parameter `Car`.
       template<template<typename...> class...Agreements>
       using Road = Trip<Commit::template Road>::template ProtoRoad<Agreements...>;

       // This function composes the conjuration function `Road` and the `Agreements...`.
       // `Agreements` will be used to invoke `Trip<*>::ProtoSail.
       template<template<template<auto...> class...> class...Agreements>
       using Sail = Trip<Commit::template Road>::template ProtoSail<Agreements...>;
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
           template<template<typename...> class...Signals>
           using Road = Car<Radio<Signals...>::template Page>;

           template<template<template<template<typename...> class...> class...> class RoadVessel>
           struct Detail
           {
              using type = RoadVessel<Road>;
           };

           /**** Transition ****/
           template<template<template<template<typename...> class...> class...> class...Agreements>
           using Snow = Detail<Agreements...>::type;
       };

       /**** Continuation ****/
       template<template<typename...> class...Agreements>
       using Road = Trip<Commit::template Road>::template ProtoRoad<Agreements...>;

       template<template<template<auto...> class...> class...Agreements>
       using Sail = Trip<Commit::template Road>::template ProtoSail<Agreements...>;
    };

    template<template<template<auto...> class...> class...Agreements>
    using Sail = ProtoSail<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKz%2BpK4AMngMmAByPgBGmMQgZhpmpAAOqAqETgwe3r4BQemZjgJhEdEscQlJKXaYDtlCBEzEBLk%2BfoG2mPYlDE0tBGVRsfGJybbNre35XQpTQ%2BEjlWM1AJS2qF7EyOwcAPQAVMcnp2fnJ/smGgCCRycA1ACSLKn0bIJMfQ%2BnV7f3F0BFz%2BN2ud32DxMADYNAAlJj4VDQjQPPAKB5MSEw2GoBHIgB0YIImFeBmJJgAzG5iaSvphKdSSW86QyCABPVKMViYfG8ynYB7IAwKBS8wkUgVCpgih7wxH8sHzYheBwPAAqxDwqTBJgA7FZbg8jQ8AYcHgARTA0CKy3HoH6XMHGk0Q5FuFrI1HozHIgCynnQBKdxppzPJVNDZPpEY5XLYYv5guF6PdxAVhuNSpVBAeymIqCIOLxGaNeoNN2dxtNDw8LBYhA%2BOd%2BwcrWdVtfrBBbzrL3crRurHgY2m2X2yDuOIP7lf2ruxCKcnsM9rdHphGOImEFqFeGUw9oQ8R5ff7s4eADE8MR5qQHgB3LfheaGRx0rFwhdI9fLh6oGLNcIMXfdlOWYNggxLacXXVQ8GFvB9UQYAA3VAAGst1XNN1zvQgEAeAhDweTcFC8WhHCMYDYzA%2BkYUJSDp0jFkIyZKNWSo7kEwlJNpVFXkhDwYBmFoBR0wrKCjS8TIKKLFcKXNGsPSpOVFypfjBLEXjxWwBUKXLE8ZwhAAJHpOWIB4qC8BgGgEcySHwwi2BWMzGOJd8hAYVA7wgsTxLPNUEDRczLOshh8OIQwFHSVp0QIrc0GHUdvgsqzvmRGTPRwgithzcIUNQ8JgFRAhb3050zzEWhPIKoLWkPMzUnzXYZRiNlf1isyAuAOqAFoSCwMzkpC0VSpDFimMZWlwwmsNo2m1iY1Aji%2BS4qURU4yVk3W7iZRkgA1TARR6UTxKNNsc0tADaBG0t9WugyHgAdS3AhwoYBQqHiey4oEEdwqS4LUuxO1PSId89oOuxvJOytJOqkCMLk20EX2w6rqU4GJUpctob1c0sZ1ejT1OdVXuKcdm0JysXNm6nWTGqbaYWuMeWWjaeK21bNMTTmxRuYBNxJRgCBEzHKedWGKPczzIURi6mDoBk%2BYFxsuYlEAQHh/HKdxrXQUpwdZHCLwxxsimfLKiF/MCwbvjQXclBiwj4t%2Bk3Qpt8c0uB78GHtWL3yVzBBcELnaP0s9IgLZ6EC%2BB5MCQxh7K2Lr/f5wOVYTddAqQlo8AXZBb0IX8GFoVqKs870Hik4B6A3YAfCFujzarS2AvRQK4lESSMJhAOg%2BFjOURw2haAeOIHi733UEQvLu40DUtQZQ5%2BXVvMC1QdKYVIMOITvALkDw6P0QEEui63VIWm5YkzMwqH%2B0Zubxvh6iOc23le5V47%2BwlwqZJl%2BT5%2B1FSDshB1bUyRoGNWGt6ZblXoWDGbh35C1VtpXSBMm4DhbtbAG447ZFAOl9bcCU/rjndjZT2eJva%2B0IsiRBwcB6N2nGeGhqc%2B4iWwnQEeY8J74SnrlNCs8AGL2XiAWBqAhDy1oAwu%2B0C6aTRpjIqkTAvBEBfuzVm21NK0OFp/GGVcHjiLoH/EmC8gE7k7KA6B4DhFgNEQYtGCCWHp1ZrrHsuo8aoNuN2e%2B3j2LxnUTzN%2BjikE6PHno3%2BlJ5KiPSlSLRyDdbdmrJaa0W47ETkOFOZuMEsEpXHIFP2mR6wGGctQmEUSvYoiwMk%2B0TAYioHjlIjBzwczRx9vQR2cVpRbl3ked8qZPSBR9POBWodILeIUQ/KaSiVH%2BNflpDRCk0yi3NmdXM%2BYiB2O7L2fWxNgEEEbGkjJrYXrZhrGYwg%2BktnoJnDsn6iVyaOjFqNORsiZpsUWn4uZAT8RqSEiLbSjyJJhLtEYvpSlPwMh%2BRpdaFi5G5iYMAaMKC9IAvwuMsZzzmIYupL4lmnzZnc3xStZM4CUaQyWdDFZcsFYosudDY0398KxiMeDVGDJolIrujrDxesrllWJhqCKWRTYPN5U815mLxUTPkVip%2BS08VqPlWtGZCrYkhOnAyqWd4jFUvsbE6FGtYwuP7Fy5FVyDaCCNq7A5%2Bl0WStlR8glKqgnBzVYC6q4TEaCNMXWEBUDYXsphTNVZa9okOOVkg9a8TKa2vmlKhkUzUCqKVYqzRzrtHkq/no1JETjGALcLswNUYrGQJsWssREjFZpridy1x7jTXOhjY/cZCak3II0bzKtISNUSKMbYitMSq2Ru5SatBpogTjpBNWS814czYFUKwN4W4zZjvHYCEEOozAUnCEKLwWAZZuHirsVI6b/k8urEIBAyiCA1zNvfFtzjbgrIvVe%2BgUa7g7KYKkEiN6RU%2BPebi0SKz3RftItGU11YADypkAD6KJb3NuUVPXaOcamvqWSsqD8RYM6n1JCUZaK0U4tbacz4SxFmnudJSzAl1Nm3TFgy%2BGILZDywiIstwz6CDXtmshzUqHEU6WxsaEdnj8MysI/%2B1tHbw0uozW66SwKc06srdJ/urNQGGuHW4t9kGYNcGtbcO9iGHi%2BlIo4N4eB4iAeOaqTDxBoNcBw4Jo0f7mYhJWaI/0tAVy3S08O0TrzIIMhteJ5mxGhwAVY1vaNCHpkpv0ZgAAjl4RguwotXPvfiJ4mzZOV2szmDzAYGThZY5Z1SiXktWVmk8IdKCKNCbo1cwzsWABSrrQnVWUPChG8litkYheVlLs0TNkS1LQCzxBDjVd5LeZrNWjU3TrWghtIXn6BJU387sDLPOyUiWW7bym04RucZpxbIn32PFs9Bsw%2BmbhNaQyhmIaHT0YZg2YRzXiCNYoy46mUQgBuVbc3li01GK2BYa1BBjTKc1/aS4NhkPHc6Pf4zW%2Brp2eXLbE19xDkm1uHZk3VuTP8e2KZBwrAd639WaxO9p4mQgvCpDwegWEB1TM3Y1fTxnzPv05hzcB79s0ONcYZFwDQhwUgPDABwQ4kudIcrO9WX0IPSGhTNltpX2CyGes1Hmy7GgGRvcgeysE6tQ2XYc1SEXwj9tLPVhsqkl2DduEl9Ljgwj4Rk9PerXZNPHhc9Z6rsJLOyJGMV80ZXJv4F89AwJ0d/KDrCxu8%2BRwyBoM8XiAQCA8x0DqwUNyVPIs3B%2B7IreOnDO9xM6D12CUaxtMty3PwYeVUKLIiT3gFPafWiegUAgcuDwe9ar9qgUyrtvSbm3PbfcIBFTNGT/npQrRM8EGzyAXPbB89Bcgg7hkzuZeG/7W4bsZvhd68gdbg/m%2BYMn7cAb7AEe8RUlKlH19gWcvCM6wi7L2A0vOlL5zyvOpq8fdV1V1J1ad6gBB7Q50F0f1JwwQV1gDzh11/hiYnhkJ%2BFf54NMc7UVs5Ufs21OZwEbhiBgArNlRVRUCZ4ZIlNPFwd6U9FGMc0ZIiCSCgFP1%2BcY8aC0ciRPtsCZUiNlVk08DeZiCNtbgGUKD0CFNEYJD0IqDSddURDKcNNwNiYi8mwRUGU1D7MQ91cclnAQBNUGQZDMAjc/Nztjh1R49E8Z8285909F9l9V9MB18lJK97MS8Ody81D%2BQa9dIOANhaBOB/BeA/AOAtBSBUBOAD9LBrBK4tgdgMJN0eBSACBNB/CNhUIAhJB8QNAAAOMwMwAATkKK4H8DyNyK4F1F1GkECI4EkF4BYAkA0A0FIFCPCMiI4F4AUBABaNSLCP8NIDgFgBgEQBAGylSGUXIEoFwToHiEiG5E4FUFyKhG6ihEkAeGAGQGQAeCkHxDMF4H3EIBIDwGzy4BkEEBEDEHYCkHOPkCUDUDSNIF0DOLvHClSE4B4ACKCJCMeI6Ig2UQmJzFQCoAeCWJWLWI2K2J2OyOuwgFrFSFmOviSLWF4D6K0A2AgCQBmPoDIAoAgGxLGGACkBSBoDIniG6IgBiEeJiHCBaDZA%2BN4BpOYGIDZAgxiG0HqD6OSLtkbAg2LnpP6NICwBiC8GAHdGHm6O4F4CwBYEMGrj2HCPwE3AaHjklPCMwFUHqGUT2GSPCGJFqPCLGxiHChZI8CwEeJejwEaKlNIHjmIFqSUEtFlKMDGyMDSI2CoAMGAAUF2gszvEw1COSP4AuNEHEBuODLuJUHUEFOeP0DlJQGsGsH0DwBiG6MgA2CHz6ElO6izwiVMBiMsCSF4DqXiE1CwDTIgA2DqBChcB9hmD8DONCCWAqCqD0CKCFRyE8A6DbIyA7OGBbLGDOOrL6AGGmC7PyCHJ6E5MaAWH7NGASCHIWHrL0GfFaDnKcgkCrPiN2E3P0G%2BNaN%2BM4FBOWNWPWM2O2N2NhNwCOKRIpC4BRJSPdI2EPARDGErNIEyMkApHxEKIpGqI0EkDMEkBhA0H8ChEKL3LqIaJADvPxChC4ChFyMKIqKhH8EkFKN/KhAPMFI6K6J6MfP6IxJGMxLGIBMmLxIJOIHmLYE4BaBYCQl1G6kxClAoi4EKPxC4ByIOPwCIDLL0AjMuLDOkAjMUCjMeN0BSFeM/QZK%2BI4GCOwvaM4H%2BIIEBN/BBLBNPO4lYvYs4pRDhJ3ARJxMhE3TMAfLRIGJIsoqmPxIMsRJQAMCMDYpFz4DoCvgpKpMFKZLpIZNIC8pZLZI5IcB8p5KFj5JLkeOFNFPFOEh8plLlPEEFKVOnNVMeI1K1OJB8r1J6EeKNJNLZDNIVNRM1GtOSLtIdMwCdPioKndL4C9J9L9IDJ8oEtDOuOEtkFEoeJjMSDjLdPzKsEsGTNTPgAzOPWyGzNzLkj6usCLIiLtLLIOmGu6F6GyFrPcHHIbOCB9nXNbLOPbL6GXN2t7L6G2sHKWunIEFHLaHWpXKnJCkupOoXMmEGAOqerXObPnN3IUG3OuNkvkraOLKPI0ohJYsKjYo4pyIeAgGvN4uMrvLMqfNIBfP6koFkvqNIEaIpHYoAt1H8EKKqIpEAuAvQoUoBs6NsHwvMqIvgBIvGPIumNspxOor2DoohJYAUCQm2KQjBqjHmG4pvJOP4tkEEtatuI6ujPCN0ApFICkveKlN%2Bp%2BJwqUrIqBPUtZvZs5u5rpHmEhvhMRNhopHhsIsGKxIZviGssopAA5oZ2gy5sKOgx5oIGg1UDWJcrJOvEoA8vCL8oFOSO9oCs5OCrMVCv5IiswBFLFIqklOSLipdMKqFKvGSoWsFLSuQG1MysEGysFNyrpIKotOKp8rKr3EqpdOqqNs9PhXqswH9NAiaqFpaokDasEDFvEpgp6uMETIGqNIrJGqzM4H2CzwTILIsBmpLOIHmu7rOprIgFcBeqbPKA%2BsOrJgEBer2uyAepuuWouqXOusnM3v6FnPeo3MXOep3tesWHnqPq3O2B3PvMgr%2BsPI4FBLVo5oeFtvxAdshuhrsnMDhtRIRqRrfNRugqKPxApApECAApFw0DAd1EQpJoiM4Dwt6IRs/P8B/MqN1GaNyMkBKK4HyLMCwtqIpAVsUrJsptkv2PgdwoIvRI2DtMyGcEkCAA%3D%3D%3D)$Done$

## Links

- [source code](../../../../conceptrodon/roadrivore/trip.hpp)
- [unit test](../../../../tests/unit/metafunctions/roadrivore/trip.test.hpp)
