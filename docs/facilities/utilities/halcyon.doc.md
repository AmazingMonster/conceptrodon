<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Halcyon`

<p style='text-align: right;'><a href="../utilities.md#halcyon">To Index</a></p>

## Description

`Halcyon` accepts a list of items and returns a function.
When invoked by an operation, the function instantiates the operation with the items.

<pre><code>   Items...
-> Operation
-> Operation&lt;Items...&gt;</code></pre>

It also contains a regular function, `size`, which returns the total number of the items.

<pre><code>size() -> sizeof...(Items)</code></pre>

## Type Signature

```Haskell
Halcyon
 :: template<template<template<template<auto...> class...> class...> class...> class...
 -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
```

## Structure

```C++
template<template<template<template<template<auto...> class...> class...> class...> class...>
struct Halcyon
{
    static constexpr auto size() -> size_t;

    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class>
    alias Will = RESULT;
};
```

## Examples

- We will create a `Halcyon` with items `Item_0, Item_1, Item_2, Item_3`.
Then, we will transport the items to `Operation`.

```C++
/**** Items ****/
template<template<template<template<auto...> class...> class...> class...>
struct Item_0;

template<template<template<template<auto...> class...> class...> class...>
struct Item_1;

template<template<template<template<auto...> class...> class...> class...>
struct Item_2;

template<template<template<template<auto...> class...> class...> class...>
struct Item_3;

/**** Operation ****/
template<template<template<template<template<auto...> class...> class...> class...> class...>
struct Operation;

/**** Packed Vessel ****/
using PackedHalcyon = Halcyon
<
    Item_0, 
    Item_1, 
    Item_2, 
    Item_3
>;

/**** SuppsedResult ****/
using SupposedResult = Operation
<
    Item_0, 
    Item_1, 
    Item_2, 
    Item_3
>;

/**** Result ****/
using Result = PackedHalcyon::Will<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

- We can check the size of a packed `Halcyon`.

```C++
static_assert(PackedHalcyon::size() == 4);
```

## Implementation

```C++
template<template<template<template<template<auto...> class...> class...> class...> class...Items>
struct Halcyon
{
    static constexpr size_t size()
    { return sizeof...(Items); }

    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class Tranquil>
    struct Detail { using type = Tranquil<Items...>; };

    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...Tranquil>
    using Will = Detail<Tranquil...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQDMpK4AMngMmAByPgBGmMQgAOwArKQADqgKhE4MHt6%2B/kEZWY4CYRHRLHEJKbaY9qUMQgRMxAR5Pn6BdQ05za0E5VGx8UmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimGmujMh4mAq3R%2BdXN6f/xx%2BlwuwLMAXCyG8WFuJgCbmQE3QWCosOwIJBfwBWIOQMxtwAkiw0vQ2IImI0vodcdiaWd0VcCJgiQZGbC3IzmeTMGyOcSuTymXzWXDeSzuXCmF4iAA6WWo26QpgKBSy6XyxXK1XqgyauUBbAKnUq2X4jkKVEgibELwOW4ACTEyAAngJ0YkrFdbl7bnNHMgFQIJphVGliD68AAvTAAfQI4ajEGWIO9MPdt2ImAIGwY8cwqCoqogpqZCiTAQsqfu9MuKdF/JFgrFAs5wvZjfrbZb4s7Qu7kpleoNGuNav1hqVI%2B1E61Y%2BHM6HRtuABViIYAI5eOgWz3eq02uOPFp0VMVrxZIy3AhO54wgL3Zerhgbrdw4ssSf62EVkyJKvl6u1u2rZ1sBQHdiB4Fgc2vZsv2qDzuOuqjgu06DohH4oUhU5ISu66brQ241t6Z7hMAtwAOp0LQt73oeTAvm4uFPvh84gCAV7PF%2Bbp/h6wK/LSWLUncABieDEBMtzYKorDEpglI4hiAkAkC6JghCUJyWyaAMFsaQEOan5XIpdxvp83wghB0FNg2XZWR2cEIXOaFOch6HzpaBDWrab7RhoXFGQyUE2TBwXWT2YUOc5RqOdFUWochHleXGPlcP5fGXJZoUdpl4X2VK8FxVhs6xa5LmEXu3kctGZhpRZQW5aBtlZa2kWlSV2EYW5g6JfuBJVQEtX8XcADyzyrhS5mBU1DWQdNOU5a1HUxfFS2FRhPW2qN8Tkjkg3XEctzKEwyAANaYOgtwAGofHY8l0lcJEXkdp3nQ6tDOgINH2o6LoMOicLJt6PkaKQMI7l6KWg4DENVWYUPg31TLRgNRmfv%2BAX7XcQheGkaRKOgABKHxeLQcaTZcj1kdjuOZOdRMKCTcawveW3jbtqNuNDiMsL58NETDSNcHzKY%2BXDYP89zyP/Wi6PpXi9OM3dQKU7cCuk19z1negb0fX4ICUbQBFwqzO2umjvHGQcy4fGTVIeTtyDRhO8QEBAiJsQorAxkqbJqwQoPU8UdPE6TqJlhbQ1KacQlW0ImDaRdUkyfQSuW1HgLVr6eCO87bQQJrr0/c4IBZAmyw0cztySOHHCrLQnDJLwfgcFopCoJwnOWNYPrrJsmlgjwpAEJoterCdIDJJI0oaAAHGYZgAJwL1wySzzPXCJIk0j1xwki8CwEgaCDzet%2B3HC8AoIAg8PLe16QcCwDAiAgOsBBpFK5CUGgRJ0PEkRe5wVQM8ABsABaYBkhbjAGQP6KQ0ozC8HOoQEgeB0B6H4IIEQYh2BSBkIIRQKh1C31ILoIWAB3VcaROA8Drg3JuI826cGGlKd%2BcZ8y3CAWAiBUCYG3DgWYW4EAPA/3oGGcwAQuDLF4DfLQqwIBIG/mkX%2BZAKAQEUcokAwApBwxoKTeIl8IAxAYTEcIrQnTUN4CY5gxAnTDRiNoeON9B7f1JAQYaDBaDmOIVgGIXhgBuDELQS%2B3BeBYBYIYYA4hvFiUcXgAAbh8BhwZ45Sm2IPcIjId6t1oHgGIq4bEeCwAwzyeAD4hNIAk4gMRaaPHCUYHJRgR6rCoAYYAChLrvDIVtZug8MHCFEOIXBfSCFqAYaQ/QESUDWGsPoXJl9ICrFQHpHIwTQGImZqYLulgzCn0qcQVBiSFk9Fic4CArhph%2BCFqEcIwwqijCFsUbIAgLl6EeY0BYIwEhCzsCcpokx2ieE6HoH5Dg%2Bj/I%2BXcr5th/kvO%2BeCm5ix7mrAUL3LYEhaEcEbqQE%2BvAz4cJAeAyB0DYFTwERAXAyCxEDykUPJpqwECYCYFgBIiZSDj0CNKBeAQt4aEkGYSQwCj7JGAQvfQnA96kAPhI6UwCuDAJngvdewDJ4ry5cA7FDCz4XyvrS2%2Bcin7yJfiwj%2Bqj1GiP/mwTgrQWBxMSKApg44LxcAXtKLg09EH4CIPstBQs%2BlYMGdIYZShRnEN0HDChTAqEhIxVinFjCODMLflKW47DOGEsdWRZ1rrp6COEUo0RMIwRmBpTIu%2BhqzXxE/mo1AIjRiKiMM6rgINdGMnEpQIxxCrFmIsaQLtNi7EOIcD2lxjA3EeK8a3HxfiAmG2CYPMJESomTpiaChJwTW7JOQKkntGT6gMJyXksxhTtitxKWUwelTqlKFqYu0iTS%2BCtPaZ07pPa/UDJwYG2QIyiGtzDRMxpmyrCWFmTEeZrKlmNFWesu8gHrA7NxXsg5YHkX1F%2BS4Bg7hAUFCuRhiFSwHmZCebkLDlz0iEfeQiz5wLUOgoEP0KYJHqO9Do/CioVG4UDFhdC%2BYlHIXorWBsNFkixWYvocQvFabuH1szS6t1GhBEUq9YWiRJa6WkAZUy0YrKd4SqlS63lKQF6bwCHygVkghZxq1bYHVpb9XwENa/VhVaK3EAtdsa13D3xxP9HErNYoJgespag9Bsh/UfrwfIYNP6dAgCCBGqNNCROxs1Uw41bCqAcM8wobztxfMuv83GIRNb83xGUwEVTer74KOK8o5zNXREgG87jaMeXowFejKoCBfA6CtoMR21ufavGD0GwOxxw6a2uPcZ4hhU7/GBLnaEpki6T2hJXY4NdSTVApMZDuwQe7iEHvyU6Y9xT9nnt4JempS36l3sqy0pgbSOmYC6c8HpvA33YIkJ%2B/BUWxmxf/cYaZwGD3IbbsswMnAdju1g9s3Z8RvWHNZSCxo6HMP5FI9ctjfGCMlByFxt5OQ8P3OObRv5nHGPfJo40ejgxeP4e4wx9HwLWO3Pw8i1FOCY1idPpwTLkCvM%2Bb81yCS5LPUkGU5I6RamNPMsoBi3TIBF7SgCAEZIq9zNHxV4keVGrxOcG1dfNT7Lkico3okI%2BM9JDLy4HPMw6qd4BG57i/XurZEYoQbrnn59XejwqfonI/ggA%3D%3D%3D)

## Links

- [Example](../../code/facilities/utilities/halcyon/implementation.hpp)
- [Source code](../../../conceptrodon/halcyon.hpp)
