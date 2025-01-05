<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Diversity`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-diversity">To Index</a></p>

## Description

`Varybivore::Diversity` accepts a set of nonrepetitive variables and returns a function.
When invoked, the function appends the arguments to the previously provided set such that the resulting list:

- contains every variable from the previously provided set and the arguments;
- doesn't contain repetitive variables;
- preserves the relative order of every variable;

The resulting list will be held inside a `Shuttle`.

<pre><code>   Vs...
-> Args...
-> Shuttle&lt;(make set)&lt;Vs..., Args...&gt;&gt;</code></pre>

## Type Signature

```Haskell
Diversity
 :: auto...
 -> template<auto...>
```

## Structure

```C++
template<auto...>
struct Diversity
{
    template<auto...>
    alias Page = RESULT;
};
```

## Examples

We will use `Diversity` to append `0, 1, 2` to `1, -1`:

```C++
/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** Metafunction ****/
template<auto...Args>
using Metafunction = Diversity<1, -1>
::Page<Args...>;

/**** SupposedResult ****/
using SupposedResult = Shuttle<1, -1, 0, 2>;

/**** Result ****/
using Result = Metafunction<0, 1, 2>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Diversity` is implemented as a shortcut to `TypicaDiversity<*>::type`:

```C++
template<auto...Variables>
struct Diversity
{
    template<auto...Agreements>
    using Page = TypicalDiversity<Variables...>
    ::template ProtoPage<Agreements...>
    ::type;
};
```

[*Run this snippet on Godbolt*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIAAcwQAOqAqETgwe3r4BaRlZAuGRMSzxiSm2mPaOAkIETMQEuT5%2BQTV12Y3NBKXRcQnJwQpNLW35nWN9A%2BWVIwCUtqhexMjsHAD0AFR7%2BweHRztbJhoAgrv7ANQAIpiprozIeJgK1wenF1fHv4df5zOgLMgQiyG8WGuJkCbgIAE9HgB9AjEJiEBTQ7BAoE/HbXIQILwEAj0D77AEETAsVIGSnQtxMImoAB0rMxQLGxC8DnxhOJ9GhVguOIO1wAakw4WS9hSqTSmHSYYyiOLmngmLEBYEsRdOdyCKq4diAOwWa4zRzIa5oBhjTCqVLEa7K1DXABuYi8mChpolxHVmswJmNt0FPtDgSFgO%2BooAKgi8KJaLc8G6Epl4dKTkDKdTaUGlUzWcyAJK2x4OTDoP0B%2BgY7UclH667x1KJsQptPEDNwkDXVJeTWJw30ssKCuU6tqjV1zHFk1RrZba4AJUwyDWmTT1wZShAQOuh%2BuuflioZTOuY4nEWANZnmFIzqLrLXYzvgfrOvOR/NTZ5ymIVAiGUJhgCDC4f2DKMfx/LxMiMY8EW9aFbl/dAQBQAR8HqZhaAPGDD3pfCCJ/MZ0JAPAFERWImCURFUCoekJSNGEr3XRwjHfLVsEfVt22TVN00IFjsAwj1vAfKEIJIn8%2BKTTshPhR9iJklsE3kwTu2E0dy3YqsuLeYtHzYhwbwM9lpIIzEMPhR4bLlfNrgAoDUBAsD6VfAgDIUedtRspDBRU4MIyjHFlwsWjvV3dgVJPfN6RdS9dNMzjp0DCzvyPPV/0A4DQILNwTI4280u4oLTRU2D4OARDHihQJULIjCbWw7IxEqo8iMs1SmooqiaLohimMlHTx3YszSoLHi1LbDSux7ayQHEr1lO6mSCSJEkCqK/TJp8tltVWzLVN5TatUK5LJ28oykrGlKSv9e8MpkxbbILaDOpDQLhW6uKFQKl1i2856jzgm8nPy%2BrUOcvL3Jha6DqxSMTRC7EYz%2BDHPhFG4SzzKlGCaHCswBXFMb%2BAEcwc/6EufZlgYbXU/wNBStPhBdYqps9AdZc5gGITB8cET8VLBhC3OQhqZv4lmFvhvbfK/H97Lzf6nNy1z8vpXn%2BcFgh9uZEHD38x5vsBL7kZ%2By4yf%2BbG9mubBVFYGlvSx9HrZlNHgVBBhwS8SF6RtDZUj1jLbbxDb%2BRd8lKZVrnaYy7KDQjrbTbD64AFlMCaKgvB9onXfOP646IYtzmIYBhYuUWasz7Pc9MgQobuTTZbcLhHwAWi4DKMPFrXy/19kLejK2biELxUnSJR0FfLxaANAvq/xCep6rWf56b5Pzvb64u8fDRHzMIfQrdvF14X6Oq%2Bq1c3jng0UIzrOmBzvPsnpA/rh3o%2BG2HtPYzeC%2BHtGYKkTIiWiSgWgQF6goVgmAwH1jcOfR849J4ZDXrfeemJFiCg4MsWgnB/C8D8BwLQpBUCcDcNYaw5pVjrGQiCHgpACCaFwcsAA1gESQzINBJDMGYAAnPwrg/geFJC4MaY00h8EcEkLwFgEgNAH2IaQ8hHBeAKBAAfZhJDcGkDgLAGAiAQCrAIAOAg5BKBoGpHQBIURYGcFUEkAAbB3JxkhrjAGQFaKQzIzC8CrIQEgeB0Lt34IIEQYh2BSBkIIRQKh1A6NILoduAB3VEqROA8DwQQohLCyGcAAPJEjMdcBi1xHEuLcR4rxn8uFmGuBADw1j6BOnMIELgixeDaK0MsCASArFthaRYiAAybGJGAFIMwfA6CUm7JQWIeTYgRGaL2bgvAlnMGIHCApsRtDsUybwKxbBBAFIYLQVZpCsCxC8MABktBaAaLWaQLALBDDAHEIk/A/NTJpkeaQ%2B064iSbEYRESk0jSG0DwLEVEWyPBYDySiPA8inldliGg%2B4ryjCQqMCw5YVADAVzFK8FJBTHjEMYWE4QSYonSEpXEtQeTkn6DeSgKhlh9BQo0ZAZYqBg7ZEeR3MiKFTCWGsGYFRXZ/RYC5RAZYdhxrOAgK4SYfh25hAiIMCowx25T2KDkTw7Q9C6pwnMIYiR27yobgwXoEwDX5AtbUBV1rxj9A1fMbVtgXUqr0DMFopqtXmrlbQjYEhskcEIaQZRvBVHlOca49xnjvF1IabgQJrSGGdKYbi5YCBMBMCwIkWVpAOGSECMyfhgRJEaEkGYSQTjFH%2BCcfw/QnBZGkHke05kTiuBOKSPwsRTj/CSGERWpxka8mqPUZorNOjemGL6cY4pRJhmjJaXYtgnBmgsDdMaDuTBrQGAQlwfhzIuDcP8dhIJISYlUsiRIWlsh6UJNIboKZaSmAZLWWGiNUb8kcCKaYokpSqCxsqe48EbzP4nrPRoBpTTBkJChCCMwmbum6IXauhIK7UDNOGBBowx6uAHxoPPdM8zFnLK2Qc0gGyVk7L2Q4ajRyCanPOXkq5Ny7kPOoy8t5HzLl4G%2BY4X5eSAUbkpNR0FtQ8mQuhSsuFmxSGIuRYw1F6KqR8ZvLivgBKFBEswCSsl1HKURPENEulSgGWJNfcynFIqrDstkzKnlfKBACqFQ1ezYqJUJClW8eAcrHVWpcAwdwdrVUhFC/6hYOqig4W9bFjM2RosestThG1rRws%2BqC%2Bll1KXzWer6Alwrfq3VmtDSsNYIaOktvDbkxJMaKnxoPZB49p7uEpsvem9pqHs2kFzfm4YRbpFto7Se6txp/D8IkYEGtdbh3joa5wKdWjtP6KMSYsx2HcPEHXZsLdVSWAKDdFaN0bX8xjAvWm4JegTPUvvTep9jKQDBHfZ%2BrJtWf0TsKUug0ZTVCHeO6d87/0xhwZwwh7rgReuzr0f0iHYztuQ6WsgSeiIzv8MRBdggiIAe0pmWRiACzEm0ao080n2zdn7Kecxk5ZyLm8A47csQ3Gnm8axYpxngnxoicSWJoFknBDScSbJmFcIFMIv9Cp3gamlAYs0zi2H%2BLQJ6eJaSxgxnZCmZpY9yzz6dAvds8YNlNgnMBbIa520nAthNS85YcV0bJXBP89yroTqQthbyBF9VZRyuJb1cV41yWysBuy90BoXqssOvD862YIeYslcy17n1eX4/aqDVVqJ376sqM4OUwHJ33Qg8pGDiAqaiDdY6V0vrA2C2UDDaNkAAjmSBECP4ERw7FGt%2BNL2xbue1G2GnWhxY7CQCSH8OW8RxpFFJEkEIrgvCzBjukYEHP0blszp6WGvxff18D%2BH8sea2Qx9AA)

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/diversity/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/diversity.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/diversity.test.hpp)
