<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Morning`

<p style='text-align: right;'><a href="../utilities.md#morning">To Index</a></p>

## Description

`Morning` is a vessel for `Will`.

It also contains a regular function, `size`, which returns the number of items it holds.

## Type Signature

```Haskell
Morning
 :: template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
```

## Structure

```C++
template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
struct Morning
{
    static constexpr auto size() -> size_t;
};
```

## Examples

We will create a `Morning` with items `Item_0, Item_1, Item_2, Item_3`.
Then, we query its size.

```C++
template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
struct Item_0;

template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
struct Item_1;

template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
struct Item_2;

template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
struct Item_3;

using PackedMorning = Morning
<
    Item_0, 
    Item_1, 
    Item_2, 
    Item_3
>;

static_assert(PackedMorning::size() == 4);
```

## Implementation

```C++
template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...Items>
struct Morning
{
    static constexpr size_t size()
    { return sizeof...(Items); }
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQDMpK4AMngMmAByPgBGmMQgAQBspAAOqAqETgwe3r7%2BQemZjgJhEdEscQnJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlUbHxiSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BzmAeHI3lgA1CYBbsjj6FhUJ9gmGgCCd/cEmCypBi8nbi9vH5hfP3eTE%2Bp0BfwBryBIO%2BkPBoNhwP%2BpyYXiIADoMTdDvsmAoFBi0VicXiCUSDCTMQFsNjyfjKdTiXTCVSabimQBJH4KG5PcbELwOQ4AWRIDHCwCeJgA7FYHod5YdZo5kNiBONMKpUsRFXgAF6YAD6BB1%2BogSyeCuOMsOxEwBHWDBNmFQVAJEE5rwU5oCFitABFJVKAz7JQ8APQAKij0ZjsbDT0j0cOABVsEJk0JDjH4%2BHY3ns6HHmZdgx9l4jl80KXMKkCNyqYWwYiIb9m/DW9Cm52Ed2O0i3Cj0fTWRTmQzaaSWYzJ%2BO2TOR0yeQ8%2BQLjR6WAaNCdZY8Hl3%2B/uW1CDz2T32j3CB6jUPPp8O72OF7eJ/eX2PeQR%2BYL1wauNvG6eF5tjC57tseQG9uByLXs%2Bc6vnBj4PmSCHIaOS73Cu34/AaZj/g8TyHmBl6ESBUGkcRgHQUOiFvqhi5TrRDEoUxaENsun6rocP4BHhu73F4mRGIcyhMMgADWmDoCKxBikJJx%2BsKoripKpwWgqP4aKQxxyup2FcFpanyj%2BZgGTpRnYTx%2BENiG%2BHscCeDIAabLxAQEAieJknSbJoAgJkppLMcATBgpkjejuHArLQnAAKy8H4HBaKQqCcG41jWIqawbJgxzFjwpAEJoEUrGJIDRRoaJmGYACcAAcGhVdFNVJAEkhmFKkgpFFHCSLwLASBomnxYlyUcLwCggJpBUJRFpBwLAMCICAawEKkqLkJQaBvHQ8SRKwWyqE1AC0SSSIcwDICqUgVbwkmECQeDoHo/CCCIYjsFIMiCIoKjqNNpC6PpADuxBMKknA8JFMVxYVSWcAA8qiq3Gi6hwHUkx2nedl2SBVhwQB4W30NqOxcEsvBTVoKwQEgm2pNtZAUBAtP0yAwBSCZNC0C8xDjRAMQwzE4QtAAnuDvCC8wxDC3DMTaJgDhi6Qm1sIIcMMLQot/VgMReMAA60LQ43cLwWAsIYwDiFreC2g4eAAG6YEbiUavLqJbHl4QvF1iW0HgMQg1LHhYDDn54H1xukA7xAxBkmB%2Bq85u%2B0YhUrFQBjAAoABqeCYIDcOpIwivPcIojiB9xffWoMMA/o5soGllj6H742QCsqC1tkRuHRc8mmJY1hmMNUfEA9jvwCsdjyw0LgMO4ngdHooThEMlQjPpRRZAIUx%2BOvGSbww8zDAk%2BmT7bAh9JM8/5CfdRT70EwDMvCxr7YD/b3osytIfq/HxPmWbBISGHBYqkCGrwEaqMjonTOhdQ4V0zB41wHdYmuUyb5RTisBAmAmBYASGaUgJVAhoiqgEdqGhWodQGtFJIVV9CcB6qQPqAQuBoiSFwJINVarsOipILg0USEpDAbDUatgJroOmlTBa1MlqIzWozZmRNdpsE4C0FgdspSHSYKyISXAqpohYc7fARAR6PX0sXV6ZdpAVyUFXP6ugTLA1BmLIBIChEjQRitVEhwUaqPUZo7RwA4F6IMXjAmdMiY5QCGYNBFMZrSIUfEdaTNUCExGL4jROIjC6K4JpTm3Neb8z%2BhLEWitilSxlnLBWEdlaMAIGrDWMNta631obRWptE5bESvgG2jgHZOxuqoV2LxFaezqDDX2/sRZB06eTEe4c8pRxjkoeOZsjBJ1ABIvg6cs45zzgXeKeVzGl3elY2QldfqJXsbXZOfcrCNwmS3fB7cGhdx7kFW5A8h7xBMWPVu3Q77OAgK4d%2B%2Bkl7lCPnoDeDQQVpD3g0b%2Biwb49HPm/K%2BO9/ln0aA/BFL9P5tDRR/bFT8IWk1WOsABpKuquJhhA9J/jMmBN0fotEGhEFGJIJE0m5MMGkCwTgkY%2BCuoMKYXo8hUp%2BFSilC1MwHVeGgJpZwMaYjYmSPgNI5aSMkkJOIEorYqjoEsAUHbFUdsmV/HGDddlJinqyAsScz68gbEXJ0IkUgjiwbGxcdDP67jZHIyoIcfVp1DXGsOKavR5rjT4xSeE%2BIkSAgxJTrNGmMb6ZatTUTEAxrUipANOGg0kanLEBYCdPgdB8mUEKYlMpms8o1oqVPRWNTVbq01l0zAOs9ZiFaRHdpayZmkG6XfPpMMXbIDdiMwQYy/oTIDsLaZIc5mK0WbHFZidxRJrTkwDO2dc750LhHI5b0JCnK%2Bk66urqDA3IbjYB548kodzVJwMMFx6790sIPcBw9R6PInrfTFM8555HRWCleiLYXFGyDCqF2QcXHwxQ0C%2B%2BLgMf3/Yhol4Kf6Ev6DCvFcHAFkqygRql3rhqcEDcWg1RqTVmsROMNlyDOWJokZg7BuDKBAOFSAaqaIAgBGimVXhA0%2BNSg4fKn1irRGTR5YQvRkqNC6PIVwZI0UpRmB4XQjgARSPgMkyqoBZgdPCO5SxyO8RMjOEkEAA%3D)

## Links

- [source code](../../../conceptrodon/morning.hpp)
