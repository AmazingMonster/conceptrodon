<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::CognateHarvest`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-cognate-harvest">To Index</a></p>

## Description

`Mouldivore::CognateHarvest` accepts an operation and returns a function.
When invoked, the function collects the type result from its arguments and instantiates the operation with the collection.

<pre><code>   Oper
-> Es...
-> Oper&lt;Es::type...&gt;</code></pre>

## Type Signature

```Haskell
CognateHarvest
 :: template<typename...> class...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct CognateHarvest
{
    template<typename...>
    alias Mold = RESULT;
};
```

## Examples

We will instantiate `Operation` with the type results from `AddOne<0>, AddOne<1>, AddOne<2>, AddOne<2>`.

```C++
/**** AddOne ****/
template<auto I>
struct AddOne
{
    using type = std::integral_constant<int, I + 1>;
};

/**** Operation ****/
template<typename...>
struct Operation;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = CognateHarvest<Operation>
::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult = Operation
<
    std::integral_constant<int, 0 + 1>,
    std::integral_constant<int, 1 + 1>, 
    std::integral_constant<int, 2 + 1>, 
    std::integral_constant<int, 2 + 1>
>;

/**** Result ****/
using Result = Metafunction<
    AddOne<0>, AddOne<1>, AddOne<2>, AddOne<2>
>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

```C++
template<template<typename...> class Operation>
struct CognateHarvest
{ 
    template<typename...Crops>
    using Mold = Operation<typename Crops::type...>; 
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIJIAnKQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCUmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnhzsmGgCC%2B4cA1ACSLGn0bIJMjbdH51c3p3%2Bn30uF0uBEwTwMoJMgTcoPB70wUJhAE80oxWJgAHRYqHYW7IAwKBS3ADyqOI7xyOOBE2IXgctw8wGYoIAEq0AG6YCbAkwAdgst2Bt2Ft1hz3hiIIKLRbCxGLcxFQaQUVKuItuXiyRluAFlPOhBYEACIkskUgSS6XMNgMxXKkAgKWouVUwICnm8o1QqxXYG/f7HQH%2B27YVSsZ6YT5nP0BgE831mQIRfFeLCGtxoBhbNIEFWBbDx65HW6XdDoYmRKMHQFiiEI6FMLxEB6qy40ukEEtlisI338oUizURYCi6WGk0TdAOiKg4Dk2gAfUzc0EiJnpAegssty4rp9QM93sLwdJCXNDCrexrYPFkOhTplmOx%2BepBFp9NP5MaR99P2LOswFoqC8LMPi%2BYFawle8rXROVLmIYA8wLK4h21ACgJAhwcnHBlUCZeE2WITluWhT9z1bB09VodBEXgxCXRfN1j2LIQvDSYpMHQAAlLkvFoTtwJQrUR1Y9jMk4niFD4zsoRNMjv19aEB2FSdp0ETA5zEJcBBXAg10EDcNC3AVd3zUhlNuVSQBnDT520hhdP0ggNy4YydxxDcLKsmzNMXZcWlXaF11uMw3NM7BPLVEVvPU3z7McoKDJCsLWz3Zi7kk6TL0BVCR0y/icPQphgNAyklKi4VS3LSJEQ0Dyu2q%2Bs3HCjcqp7REzHqtqauhTqX0UgsmN/Is7gAFS5AToyuOZHGQBcmEJBICAgKyFHRea8zcfLnNuUSOO43j%2BJxZZvQ4VZaE4fxeD8DgtFIVBODcaxrEs9ZNkjcxAh4UgCE0M7VgAawCSQMQ0AAOMwzGSZIuH8cGwa4XleWkC6OEkXgWAkDQNFIG67oejheAUEAcd%2B26ztIOBYBgRAQHWAg0ibchKDQJ46ASKJ0U4VQwYANgAWl5yRbmAZBkB3EGzF4TjCBIPApy4GRBBEMR2CkJX5CUNQ/tIXRFYAd3JNJOB4c7LuunWCeJJtGc7VAqFuHmBaFkWxYljFQogDw2foYgty%2B5ZeDJrRVggJBWbSdmyAoCAI6jkBgCkMw%2BDoUFiGJiBYh12IIlaJETd4HPmGIJFiVibRMAcAvSFZ14CArWh8/J0gsFiLxgDcMRaGJ7heCwFhDGAcRm/wYhK8cYidcwVRK6bbZvps1G7toPBYnJEuPCwHW3zwTHe9ITliFicSjTBQeV6MP7VioAxEIANTwTB9dPG7vv4ZXRHEdX381lR1GbvW%2BhB4oGepYfQq9iaQFWEqRoPd%2BaTlkqYSw1gzD40PsQeWXJ4CrDsOPHILgGDuE8J0PQYQIjDCqKMRWxRsgCGmH4ahmRaEMAWCMRIitcFYQEP0KYxCCgcPqHg7hkxBjkMWFQ2wIj6F6DmG0VhlD2E4LelsCQZsOBXVxpbTgjs%2BaC2FqLcWUgPa3AgLgWWftPpcEDj9K%2BqwECYCYFgRIEBAZJECBiZIgRkYaEkGYSQvNsb%2BF5qkVG6NSCYy%2BhiXmXBeZg2SAjXm/hJCw08bzTRzcCZExJjY8mocaZhzpjbJmMc46%2B05mwTgrQWDsl5PzJgeIDDai4MkDEXBQbS3wEQDBCsNYqy/tIH%2Big/4610MnQ2TBja9zURovGvArZFLtg7J2eiGmDx3C0tpRkvaoB9gkf2ZhrHBwpgU0pCRmaxx2ZHX2KBGmJxhjjGg/EEgZyzs3Iuedq7vJLmXCuVd9610YPXBgjcdat3bp3Wg3dq793PtsO6o88GT2btPWeoJq6Lx1ivNeedN5wqDhgve31D7HyUKfAeRgL6gFyXwW%2BCgH5PxftXH%2BfS1YDNkEM7WACQDJ1uSA5BYCsWQJcfdHMOQ4EIONEgqwlhUFzPQZgoVODBFcL8BAVw0jFZkIqGwvQNDGgavSEwxo8ilgCN6MIgYBrOGNB4aI7VCiZFSL4QwyR8wxE6qsWsDYKjPWoxmVojgOjnbC3xGs5prTQYmLMV0/2Vig62NIPYxxoxhWhIxiAQILSfG8n8MkJGgRfH%2BOSek/GnAsmkyvpTfJSB6a23Oac4g5TthVJdiwBQ7JxbsnDXWCYHTzHyz0Myz%2BrKNYcv/ndXQwRxmTNNvoc2Ja5mcGtgzJstx7aO1be2zt3b4QTBMd7K5ezPqBEOZWk5lyo71ovdcjt7EFxduSAuHtBAFyqCFinJ56dKCvLul8pu30/0/PHtXAFggG5N3hZgNuHcu492%2BjCileKW54DHlhJFd0UXIDnui9SS9eBYvXkiXF28CXV2JSfM%2BFLhyVpvkwe%2Bj9n6olfrwIdqsJBssEGOkZGagGXyldYcBsRFUitgZwHYql%2BMyrQQkbpWCoE9CEaq9VzrSGEJNRIvVOQDWabKO6h1ZrFO2qtcqm1Ij1PsNdbw/ILrZF2ooaapR3q1bTIthk7Rb7hZto7bcB9GJn1Rs6SQWNp7cl2IcU4ygaiwmYyhhiQIgR/Bw2SdjeLvJYkLvumW2w2SjnLFcZIfwHjEa8mxmDFIXAuAQzMGk1GgRXOlsJjkkOaipYZcyU1/6B9nn4MkEAA)

## Links

- [source code](../../../../conceptrodon/descend/mouldivore/cognate_harvest.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/cognate_harvest.test.hpp)
