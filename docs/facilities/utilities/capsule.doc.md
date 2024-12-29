<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Capsule`

<p style='text-align: right;'><a href="../utilities.md#capsule">To Index</a></p>

## Description

`Capsule` accepts a list of elements and returns a function.
When invoked by an operation, the function instantiates the operation with the elements.

<pre><code>   Es...
-> Oper
-> Oper&lt;Es...&gt;</code></pre>

It also contains a regular function, `size`, which returns the total number of the elements.

<pre><code>size() -> sizeof...(Elements)</code></pre>

## Type Signature

```Haskell
Capsule
 :: typename...
 -> template<template<typename...> class...>
```

## Structure

```C++
template<typename...>
struct Capsule
{
    static constexpr auto size() -> size_t;

    template<template<typename...> class>
    alias Road = RESULT;
};
```

## Examples

- We will create a `Capsule` with elements `int, int*, int**, int**`.
Then, we will transport the elements to `Operation`.

```C++
/**** Operation ****/
template<typename...>
struct Operation;

/**** PackedVessel ****/
using PackedCapsule = Capsule<int, int*, int**, int**>;

/**** SupposedResult ****/
using SupposedResult = Operation<int, int*, int**, int**>;

/**** Result ****/
using Result = PackedCapsule::Road<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

- We can check the size of a packed `Capsule`.

```C++
static_assert(PackedCapsule::size() == 4);
```

## Implementation

```C++
template<typename...Elements>
struct Capsule
{
    static constexpr size_t size()
    { return sizeof...(Elements); }

    template<template<typename...> class Container>
    struct Detail { using type = Container<Elements...>; };

    template<template<typename...> class...Containers>
    using Road = Detail<Containers...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGEgJykrgAyeAyYAHI%2BAEaYxCAAzNIADqgKhE4MHt6%2BAaSp6Y4CoeFRLLHxSbaY9kUMQgRMxATZPn5cgXaYDpkNTQQlkTFxidIKjc2tuR22EwNhQ%2BUjSQCUtqhexMjsHAD0AFSHR8cnp/u7JhoAggdHANQAIpjJrozIeJgKd8cX17dnAJOvyulxBZgSYWQ3iwdxMCTcyHG6CwVDh2FBoP%2BgOxh2BWLuAEkWMl6GxBEw6t8jnicbTzhjrgRMMSDEy4W4CABPF7MNgAOgF2FJjAICjRoPGxC8DjubiYyQUXnoGIA7FZrndNXdxhS8Mg7mgGONMKpksRtXgAF6YAD6BAt1ogK1BWtharuxEwBE2DAdmFQVAFfIgQuZIoUzoSFjdDwZV1dTJZFMw7MTJOTqe5jFYmCDaINBgUXw85IWxHFGq1kul9qejTobujXnSRjuXJesISD1lsiYZfZobJorzCXRUZjcPVIMrmrTrJT8LnGcXWd5uYF%2BahTCLQZL9fCxDFo5dWubYWAdwASqgmOhO92633aOy932DwoR9gQCB2wupyYVVjKM4yxOlThpe4ADE8EPe1sFUVgSUwKlcUxMDAWBDFwUhaFkPZQ1tmSUUK2nG5jjuAB5F5iF1AQUPpRlmXTNkVx5HNPwlAgpRlKi4lohhJxA8jlCYZAAGtMHQAA1T47Ho4Ez1bETxMkuUFSVPCu1leVFWVeEwgIUg7gM/YjJM0zjMEQ5xWA640PuIQvGSApJMvT4lXtH5QUUi9HOctJXPc2h7ThbteJoup2QMsyrJighDji6zj1s0j8Tc3TPOpbyWwvdKPPvO5lIk9wdI079r1vdlwv4mz/z%2BciABVPky1Drh1RxkBtbclGaCAkW/BQcy6o83Dy4KjL8lz0DGgg0UjOqyPQgEIMOO4hG6AQ73gxD6Hk%2BylvAuN2r1YaeoICAitU0rxBAdJHRWe9QruSR5o4NZaE4ABWXg/A4LRSFQTg3GsaxtQ2LY8PBHhSAITQ3rWMSQE%2ByQ%2BQ0AAOMwzH8fwuE%2B9G0a4FUVWkD6OEkXgWAkDQNFIX7/sBjheAUEAadhv63tIOBYBgRAQA2Ahki8QyKAgNBiToOIIhzThVDRgA2ABaOXJDuYBkH1KQ%2BTMXhJMIEg8HQPR%2BEEEQxHYKQZEERQVHUdnSF0LhSAAdxo5JOB4d6vp%2BuGAc4CihcF%2B0AzuWXFeV1X1buTWzDuCAPHF%2BhzXMBIuBWXg2a0NYICQMXkglsgRdz/OQGAKQzD4OgmUPShoh96IwiaTl3d4evmGITkKOibRujZ6GxaHCiGFoJu7awaIvGAOVaFoZnuF4LAWEMYBxFHmCe7wAA3T4fZNbohZ2aGDJqH3aDwaIaPbjwsB9ri8EpufSC34hogCp5F6MU%2BjDhtYqAMYAFCkh8J2vFfrQ2NsIUQ4gLbgOtmoH2Dt9BLxQCDSw%2Bgz7M0gGsVARFMizwVkiUKphLDWDMPTJ%2BxADbb0wdUWomQXAMHcJ4NoegQgLDKBUPQBQMgCCmO0fIaRuEMEGOwkYjsug9AEH0SYTDpg0PXpIuYwjhjxDEXMXhegdTNCUUsFRawFDg22BIT2HBvq0x9gzEO8slYqzVhrFGMcQz4CIEnKGacYbfzWAgTAt4RhOlIIjSQCQ%2BT%2BASMTDQkgzCSDltTT6ctAik3JqQSmKc%2BRyy4HLNG/gCZy2RrjEJcszF2wZkzFm7j2ZZx5tnPmAchbkEoEXROUs2CcCaCwDeKoFZMALEvKO/g%2BRcFRjrJx%2BtDaO3AabKB0gYFKDgXbXQ5cXbymbsY0xdNeAM39gLIWdxg6h2sd01sHR%2Bmo1jvHPOidYTgjMG4jOHMqkNLiHU0WqAE4jC3EYDoXAaY0GCnEZmEBa521bo3ZupBgXt07t3BwoL%2B4ikHsPH2Y8J5TxnqCheS8V7/XwJ6HoW9Z7/V3sgfeoKj6k3%2Bqfc%2Bjcr47H%2Brfe%2B0Mn4vyUG/DF55v58D/gAoBIDQXjMgebKZshYG23%2BvMxBX8iFWFQRSjBfjsF1DwQQrskqSFkLiBQrAsq9E1HkX4CArh1GO1YaUZRnCBF1ENfwwomRtEcLETqiR9Q1EyL4eIuoUj5gmp0Ro51ORXWKLYaa1O6xNiGODaTVZ5jOCWLDird5F4jkDI0LHXAesXEpxuR40gXifHxD8QkimiQ%2BnhJVJ9fwRMkiROVo7NZvtGa2FKbcip8Aqn80Dk8h5xAmk7FaeHFgCgN76g3kc%2Bc4whlpoNkbWQEyBWW3kDMkVOhEjO1dss/QXtCn0z9jUoOVAQ59oHUOkdyZxinJeecuIlyEgJEzeUzmOdz35w7Y%2BxOIBB3ORtMO/wNpR0EBtKoZWFdfnVwBXXBu7dQXgo7l3HuMKXkDyHiPLFmBx6TzEKih%2B6KP40vnmvXF287aEuJQ/UlJ8z4X05NSm%2BFD6W8EZa/ZkrKv53t/kwf%2BgDMDAJ5Ly6d/KJCCqtgu%2BBy6DASpQTYGV8AsE4IELPXY/UVWWFIes8hlCtVyMdfQxhfqWEMNtaIq1gjLVcLqPplRGn3W%2BuYfa2hCj%2BhmZ9f0S1mjPWLDtXogx5sVneyKdGgDKt%2B2DruF%2Bvkv6U3DPTandOWac1YDzcYxJlMsZ8mvZ9PGkgvkaGvSqDJm71mcBKazLNATPrBMJiqamaNJA4y4BjMwBTSYJB81u%2BtTbjHazy3W6L5S1hP3SM4SQQA%3D%3D)

## Links

- [Example](../../code/facilities/utilities/capsule/implementation.hpp)
- [Source code](../../../conceptrodon/capsule.hpp)
