<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Warehivore::KindredRepack`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#warehivore-kindred-repack">To Index</a></p>

## Description

`Warehivore::KindredRepack` accepts a list of packed warehouses and returns a function.
When invoked by an operation, the function concatenates the packed warehouses and instantiates the operation with the result.

<pre><code>   Ware<sub><i>0</i></sub>&lt;Cons<sub><i>0</i></sub>...&gt;, Ware<sub><i>1</i></sub>&lt;Cons<sub><i>1</i></sub>...&gt;, ..., Ware<sub><i>n</i></sub>&lt;Cons<sub><i>n</i></sub>...&gt;
-> Oper
-> Oper&lt;Cons<sub><i>0</i></sub>..., Cons<sub><i>1</i></sub>..., ..., Cons<sub><i>n</i></sub>...></code></pre>

## Type Signature

```Haskell
KindredRepack
 :: typename... 
 -> template<template<typename...> class...>
```

## Structure

```C++
template<typename...>
struct KindredRepack
{
    template<template<template<typename...> class...> class>
    alias Flow = RESULT;
};
```

## Examples

Here, we first concatenate `Warehouse_0<Con_0>`,  `Warehouse_1<Con_1, Con_2>` and `Warehouse_2<Con_3>`. Then we pack the result into `NewVessel`:

```C++
/**** NewVessel ****/
template<template<typename...> class...>
struct NewVessel;

/**** Vessels ****/
template<template<typename...> class...>
struct Warehouse_0;

template<template<typename...> class...>
struct Warehouse_1;

template<template<typename...> class...>
struct Warehouse_2;

/**** Items ****/
template<typename...>
struct Con_0;

template<typename...>
struct Con_1;

template<typename...>
struct Con_2;

template<typename...>
struct Con_3;

/**** SupposedResult ****/
using SupposedResult = NewVessel<Con_0, Con_1, Con_2, Con_3>;

/**** Result ****/
using Result = KindredRepack
<
    Warehouse_0<Con_0>, 
    Warehouse_1<Con_1, Con_2>,
    Warehouse_2<Con_3>
>::Flow<NewVessel>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Warehivore::KindredRepack` is implemented similarly to [`Warehivore::TypicalPaste`](./typical_paste.doc.md). Intermediate results are kept in `Vehicle`. After all containers are collected, the `Operation` will be invoked.

A simplified version will be as follows:

```C++
template<template<typename...> class...>
struct Vehicle;

template<typename...>
struct KindredRepack {};

// Base Case:

template<template<template<typename...> class...> class Warehouse, template<typename...> class...Containers>
struct KindredRepack<Warehouse<Containers...>>
{
    template<template<template<typename...> class...> class Operation>
    struct Detail
    {
        using type = Operation<Containers...>;
    };

    template<template<template<typename...> class...> class...Agreements>
    using Flow = Detail<Agreements...>::type;
};

// Recursive Case:

template
<
    template<template<typename...> class...> class WarehouseA,
    template<template<typename...> class...> class WarehouseB,
    template<typename...> class...ContainerAs, 
    template<typename...> class...ContainerBs,
    typename...Others
>
struct KindredRepack<WarehouseA<ContainerAs...>, WarehouseB<ContainerBs...>, Others...>
{
    template<template<template<typename...> class...> class Operation>
    struct Detail
    {
        using type = KindredRepack
        <
            Vehicle<ContainerAs..., ContainerBs...>,
            Others...
        >::template Flow<Operation>;
    };

    template<template<template<typename...> class...> class...Agreements>
    using Flow = Detail<Agreements...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxBIa0gAOqAqETgwe3r56icmOAkEh4SxRMVxxtpj2uQxCBEzEBOk%2Bflzllak1dQT5YZHRsdIKtfWNmS2Dnd2Fxf0AlLaoXsTI7BwA9ABUm1vbO7vrqyYaAIIbWwDUACKY8a6MyHiYCmfbB8enex87r0eHJ9tnADVMAg8Mh6M8tt8CJgWPEDNCTABmNzQ2HwzBIlEATxuzDYADpCUjsGcwUwFApCfjib9BsQvA5AcDQfQkVZjr93p9uZtvlyzgBJNEwxi1KoQ3mcnnS/a/X6ouFMBHIgg4xisTBUmnHOkMghnADSwXQxEw6AAStcmMgANZnEwAdisDoubLlb1WZws5MwZzcPpA7qOCvRmJDSoxKphiuV2NxGq1iJJZIpieTBgpZwA6nVgQslKQzuHY6r4wSiUnSRnKYSPIImMFogptUddYyjQwTWbLfFrTbMTnTQh85G3HXao3iDXqUmW472Uczkui9HQ1G0RGw6vNyq1XjNRX0%2BTp8Sq8ezgB5G7EJWpFvLs5t/VXCe0X4P%2Bfvh/LrzJIxFtV7URC5L2vW8BExccGxCKc0zdY4PxdeCfgQ5di1HdCtw3Es9wTQ8z1TfCU2nI5gFNEVBGbWdUKXX9gmAM4ADFaFQAB3ICQJfBs32RUjyLYSi0xAEBS0jBdHVdRFxI9M5LWQRZkgAN19f0lEDDljkwjlkS/JdMPXGMMNw8sZyPQjTIIp5BzzX9MCOUhdJXbCMO3HCywPCziLTSzs1zYdbJsRz9LjdUTNPLza1kaDolbQsgtcoz3O8iL8SgycLAUByaIApLCQvAgECbOVqNbAh6XbY1TQtK1bQHPyRx%2BZE0pg1s00Laz/KUKwmqi9KTyTQt8sK2DDzlJ14ucrDDKmtcQv3ZLqwW88r2icCGHvZcn0uTBX0cz9sofOj/1EjjDUq7sav7A7l0xRzv2XIEQTBUdmpi6dC1e4gMrau77svAqmy1a6l2JYT0KYljWMxFabyqGkpL2pCEY0xc0ISmadxRdHd1yzzFqI/H8T4zAKIIKjsEco6GOYtjTq4uhMWJ0n%2BuwMG1WQiSObeGUXilc5sFUVg4V9XnuZ5yUUfMRFgjBLwsCAtw0AYZZ4jJucxc2M5QkwVigQpCoJVlTTsaxyacdCjzwsJlstu13XHjsLm/nOPW7CeUXgxN4LRPmgnjzgnUyr1XyhxHAB9DQne9r3jMtysUptoPGQ68OuCjr2Y9xq3/dGwPyv1FPbLDswnf5AVUXdyF5Uzi2A9K/O/QECP07Nua8NM2kk/1Osw7T5GUM91uffbxOG57kv%2B%2BrofY7rrae8RUv/iELx4myC6FC8Wh9Q9qmzmX1eknXzf9SREC7ddipIKbjQPqblpG4YYvb8fhfZ0njX1lkx5j8N75d8tDeW9Todi7NVXstVtJuEcoXJQzceqP0jgNe02UYGYF7lfR%2B99x7EiyqjJcqDi4YLDq/Cm2lWYgBplDZE58HaXzftJZ2msAAqjxt5V0DreZAYdjzRAIBAQY6BhIKA1NwqibgAHH0LPvNe1VAEEGJDMJ2HA5i0E4AAVl4H4DgWhSCoE4FAyw1hHwLCWL6KWPBSAEE0MouYNoQBqMkPiDQAAOMwZgACc7iuBqJcc4rgDoHTSFURwSQvAWCxBvlonReiOC8AUCAG%2BVjtHKNIHAWAMBEAgAWAQeIXgCDkEoGgWEdBoihA1JwVQziABsABaKpkgzjAGQMgM4Uh8RmF4GaQgJA8CCJaPwQQIgxDsCkDIQQigVDqGSaQXQLRWI3niJwHgKj1GaOsbozgF48m5P1KgKgZxKm1PqY05prTHFmDOBADwxT6DEHtGYREXAZi8CSVoOYEAkBFPiCUsgFAIBfJ%2BSAYAUgzB8DoNCKclAIjrIiMEOoWIlm8FhcwYgWILwRG0JgBwiLSBFIEgQC8DBaAIumVgCIXhgD%2BloLQeJ3BeBYBYIYYA4hSV4FNA4PAylaU6MwKoLFeSVgWOCNCYJOjaB4AiDeVFHgsDrLKngcJdLSDKWIBEQ%2BVxGVGHFUYaxcwqAGGAAoAEDxWIrS0RYgZwhRDiFGZaiZah1mzP0EylA1hrD6AlfEyAcxUCq1SLSmpAjT6mEMZYMw0SVXEF6Y8eAcw7BYqqC4TsIxmikECI2KYfQWjZBSAIFNWQki5oYJMXoJRWgJvaEMBongmh6HjRygQHR6glqKFm2wVb81jCrS26YTz5iLGWBIFZHANGkCibwGJBzql1IaU0lpbSLkQFwN0u55jnmWN1XMQqTAsAxAgLYkAkhET4ncYiQJcQzCSCqRoDQaiqnuP0JwUJpBwmPPxFUrgVTnHuL8VUhx3jT1VLHesmJcSEkbuSe8jJHysnbLyQU/5qAbmlPKRwOoLBFIOhqUwM8/4uDuPxFwJxnT8BECjX0sZVrhkSGkHapQDrpm6FBfMpgiy6XDtHeOjZHAtk5LyWcPZU6jkNLJHhgjRGNCXOud8259zERmHXa8lJMGAW3IQ6pvoongVeJvjQLeTYoUwrhainFyL4XosxdipVeLRSEuJesslFKqU0pxQyplLKdH4HZY4Ll6zeX8uhDi4VFR1nislfCmVKwdHysVRYlVaqlAavc/RXVfADVGpNWanFlqhk2to7Ie1UydFMedTqkNVhLAeoiF6/dui/UCADUG4C5XrDhonZG6NNW40VArc4CArhO1ps7D2ttOaqiDbG6kEbZb61VCbdWjIqbZuVomBm0tdaO01tGO21bBR1t9oUCYwdfbgmcZA5wITM7cMMXw4Rpxlzl1kbk08l5m7SDbt3ZQYdz7X0EbiA6NR7iAmIkkJe%2BpLQuOgdsOBpTUH4AweyTs9TSGZMobYJwdDxyWAKEUi0xSt30SDBIyu3pegcvWpGfl8Z9Gis6BAIiUgLG2PLMfSOtZ0yYm8Z2QJ/Zqgsc47xwTiMgwpMo5%2BXJxEinUsqbF2pv5GmYi49XmHfH7iw6E4IGHPntHwUGYgNC6ZZmTNKqN2ijFCacU2cEHZklnnMDkspWIFzSq3Naqi/StlFbfPTP8/JQLSrguit4GFqVWJItyqjbF3g8X1UwmSzqyDaWmCGuNTrLLSryfUdtQVmnjr6eleMG6yrYWut1aqLS1YAjXWhosG13RHWsCl%2BW31gbW3U3pr262stk281t4LTkKba2u91p6w26om3Fsj7aI27tQ/e07eGH3rtu2ejD4O0dkZHH2fRIu9rs42PcdnFV/iDXD3SMkGe1LyDW7MA7r6LV4JP2QAePxIiREaifGSFKBoN/Dov3AY504DA0STezsUkDURPX8QdBvWcUkC8S4FcTMCA2CURG3wnSAIgzeWHQ6QAJ31iUwJsWVSbFSEPSAA)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/warehivore/kindred_repack/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/warehivore/kindred_repack.hpp)
- [Unit test](../../../../tests/unit/metafunctions/warehivore/kindred_repack.test.hpp)
