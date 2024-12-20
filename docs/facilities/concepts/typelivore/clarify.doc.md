<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Clarify`

<p style='text-align: right;'><a href="../../concepts.md#typelivore-clarify">To Index</a></p>

## Description

`Typelivore::Clarify` accepts a callable type predicate and a list of variables.
It returns true if the predicate invoked by the variables returns true and returns false if otherwise.

<pre><code>   Pred, Vs...
-> Pred{}(Vs...)</code></pre>

## Structure

```C++
template<typename, auto...>
concept Clarify = REQUIREMENT;
```

## Examples

`Clarify` turns a callable type predicate into a concept so that it can be used for subsumption.

Since `(Pred_0{}(***))` and `(Pred_0{}(***)) && (Pred_1{}(***))` are both atomic.
Both candidates are considered equally good.
Thus, the call is ambiguous.

```C++
/**** Pred_0 ****/
using Pred_0 = decltype([](auto...){return true;});

/**** Pred_1 ****/
using Pred_1 = decltype([](auto...){return true;});

/**** fun ****/
template<auto...Args>
requires (Pred_0{}(Args...))
constexpr bool fun(){return false;}

template<auto...Args>
requires (Pred_0{}(Args...)) && (Pred_1{}(Args...))
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<1>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwCspK4AMngMmAByPgBGmMQSABykAA6oCoRODB7evv5BaRmOAmER0SxxCVzJdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHAD0AFSH%2BwDUysSY6AD6GsdH%2B7smGgCCXhlGp%2BdXNyYAzAAixywyFoBAAnilMBATAErAE/hAmF4iAA6VErEwAdgs5wImwYxwIxC8mF%2BVgxf3RPysz0eTwORw%2BF0uXFuRwez1e4WAjKuLN%2BAKBIPBkOhsPhiJRaMx2MwuOI%2BMJxNJmIpyppz3ph2OVC8%2BLu7KeBEwLBSBiNvzcEtQqORT2IwAUv2wtPOAEcvHhzgpjhAzkyNNKVRA7Q6bSt0c80AxZphVCliMcYqhPNrdRB0VicXjtWIlMrybTaUaTWaST9LUjraiQ46fs7nm6PV6fX6voHycH7QowytjuYAGwDlufZnt%2BE1nu0qMxuMJpMpnUMdPSrPyglEstkv6FjV3Y4AFUws1ZhwNu12x2wxGIJFpsyYjmQlyYCiULWouotXCd6cpFg4ay0JwAS8H4HBaKQqCcG41jWMcCgbFsmB9mYPw8KQBCaABawANYgAE/bIok/ZSAEGL9pIACcPzkah%2BicJIvAsBIGgaKQYEQVBHC8AoIBsZh4EAaQcCwDAiAgBsBApEi5CUGgJp0PEkSsDsqjEQAtBRxzAMgyDHFIyJmLwFyECQeDoHo/CCCIYjsFIMiCIoKjqIJpC6FwpAAO7EEwKScDwgHAaBWGQZwADySLSQQxyoFQxxqf2mmSNpun6ZIhk%2Bh4Cn0Am5hoSsvACVoawQEg8kpIpZAUBA5WVSAwBSGYfB0EaxC8RAMQhTE4TNKC/m8N1zDEKCYUxNodQCeh8lsIIYUMLQfWuVgMReMAlq0LQvHcLwWAsIYwDiEtnoTXgABuR4hbGdRIjs6HhEaQGubQeAxD5w0eFgIWEngzHbaQ53EEmSh/Ma%2B3PUYWFrFQBgOgAangmCeWFEJgehVnCKI4j2ejTlqCF7n6PtKCwZY%2BgvbxkBrKgKS9Ft6mzOg/KmJY1hmJxAPEOZF2U10PRZC4DDuJ47R6KECzlJUeiFJkAhTH4HnS70QwS8svMnQI/STMLeQebU9Qa3MysjFU4wDHLej3i0RtLFUawIZs2wSIFHAgexIVcfFGlaTpekGWYPq4KZuWoVwBUYZDawIJgTBYAk6akHhkg/Mi1EYpIGiSGYkj9qxBGUfRHCMaQzE/GYyI/P2GKJD8iQBAEXA0ZRyQcbwXE8Xx4eCSVYmlRJkUydVtU5cpbCcAlSXHMC%2B36ZRyJcMiEEmUQnMWR56M2Vj0g40oeOuboTXeb5/XO67LehRwEVSUiMVxePWlT%2B8XCz/PNwQFlFU5Shpdh0VQm90P8RZI1VQNlUYD8GqUS4GxGgIJ4jtU6q5QavV%2BqkCQcNUa40HAoOmowAgc0FohWWqtdam0UG7TBjsCC%2BBzj1HOltReqhrpGhQfdboIVnqvV6h9ShhVOa/XQgDIGmAQZ7SMODUAXc%2BAwwUPDRGyNGAoPXpjOyW9ZC4xchBfehMIbMysKTDhFN47U1ppwemBBGb/F0azdm8QV7c3jnrXoAsha5HlsEQW1tJYK3SDLbI2s3GKyyJ41WjiGhzHNrrbo6s%2BiG3FsbC24T/EJIGME226wHZ2RPsFVyHs77JXATPOeC8A74GXl/UOhUI6kCjjHUY8c8JQLYo9IuJcAjIiogESiZgulmH7IkBuFE3Y5M4O3fikNhI9yQJJKKQCAHEBHjsZoLAtIsAUKdPSp0n7IlLLMYypSzKrwchjWyEhVGOR3honQIAfheR8n5baWShmcXCv3aKsV4orLWRsrZOzopvxAR/eIX8fg/3Gf/AFlVZkQpyiAdZKQUiXE2ZRS4vzLiqEGTA1q8Cuo9WGigtBI0xoTWwSAmaeD5qLSoZgFaa0xCkL%2BuQsRPDSDUJOnQy6jDkA3RYYINhT0XpvVBNwr6fCUGCPSMI0GYiuTjOhkwOGCMkYo0UbIDeKijnqPxtc7RxgSY2AMfAKmNMshbV2AzYmLNLBs1bhzLmhi7ZRP1n4CArgInuPQKkqWPjehusCSUOJNsLaOt6JrVoSTIl8wNikgNXjTZa1cckq2Mblh20Qo7UOBdT7u04B85Kqz1nHCRdsh8R4/mBzKXlCpndiqR2jrHSgzsWnXLLgM1CZh23VA0P2TpTzW4jNsB3X%2B4YE4gCTnPGuARM4/ACF21C5EC4/Gyc87i1bsIFyMr28%2BlSu5rABhkZwkggA%3D%3D%3D)

By turning `(Pred_0{}(***))` and `(Pred_1{}(***))` into concepts, we allow compilers to perform proper subsumption.

```C++
/**** fun ****/
template<auto...Args>
requires Clarify<Pred_0, Args...>
constexpr bool fun(){return false;}

template<auto...Args>
requires Clarify<Pred_0, Args...> && Clarify<Pred_1, Args...>
constexpr bool fun(){return true;}

/**** Test ****/
static_assert(fun<1>());
```

## Implementation

```C++
template<typename Predicate, auto...Variables>
concept Clarify = Predicate{}(Variables...);
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwCspK4AMngMmAByPgBGmMT%2BABykAA6oCoRODB7evv5BaRmOAmER0SxxCWbJdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHAD0AFSHR8cnp0e7JhoAggdHANQAkiwp9GyCTL13xxfXt2f/Zx%2BV0uVwImGeBjBJgAzG4CABPFKMViYO7KYiYfCiMGkO5MLxEAB0xIAas08EwYvQFDDsCC0AxtikCHc3AZiHgqPC7jCACJojFYj6YEwAdisot5EDJHMp1OJhJWMKs1xBfwB5zVxzuABVMLMFF9Nb8NScgVr7ujMQB9DRGw5ArwZIwCm12vl3LDIWgIpEQEwBKwBKX4onEpXijEETYMO4EYheEXQiW8pXJkEWw6u9DWrj2/aO53AbO5nnQ/len2IzD%2BwMBkME1AKiMWKMxuMJpMptMq4Em%2B5ULyx74gsEQ4UwtyhpvEq7EYA06F064YgCOXjwGMNbPJXMnVpzGlxc4XCtp9IEs0wqhSxDuMVQnjug4YEBbbeIsaoYiUyrFvIza4xxeCdYWnBUT0XZc50wddN31Vl2U5eF90FW1j3nBQzyXHkzAANnMPDEN3FDYQPXMMNPYlz2uBkrxvO8HyfF83zFVtMGjT8O0TP9JUAm5tT1WZ8yBWYPjwZBrSYBQlBaagh0nLhaTfHsODWWhOACXg/A4LRSFQTg3Gsaw7gUDYtlRcxoR4UgCE0NS1gAaxAAI8MJRI8KkAJRTwyQAE5oR8sxoX0ThJF4FgJA0I8dL0gyOF4BQQCPOzdLU0g4FgGBEBADYCBSAlyEoNBnjoeJIhRThVA8gBaXy7mAZBkDuKRCTMXhMUIEg8HQPR%2BEEEQxHYKQZEERQVHUNLSF0LhSAAd2IJgUk4Hh1M07T7P0zgAHkCQKllUCoO5qrwurJAapqWskNq7ggDxSvoO8rK4FZeFSrQ1ggJASpSMqyAoCAfr%2BkBgCkMw%2BDoMFiCSiAYk2mJwmaeEVt4BHmGIeFtpibQ6lSmySreAhtoYWhkamrAYi8YAp1oWgku4XgsBYQxgHEcn4PqAA3fVNuvOoCR2GzwjBDSptoPAYkWjGPCwTb4zwSKGdIbniAfJReXBFnxaMey1ioAwFxJPBMDm7akR0mz%2BuEURxBGq3xrUTaZv0FmUGMyx9AlpLIDWVBmSyematmdA%2BVMSxrDMOKVY5LBvbfLoeiyFwGHcTx2j0UIFnKSo9EKTIBCmPxZrz3ohmz0ZZtqeoBH6SY07ySvulxho5jLkYEkruZC70MSWjbpYO7WMzNm2CQ1o4LTSFi3h4uO2r6sa5rWrMW7cC6p7gpet7dbWBBMCYLAEnj5zJGhQkAtFSQNEkMxJDw6LXL80KOHC0hIuhMxCWhPDRUSaFEgCAELggU/LJGnltBKthkq2V1hlbKX1cp7UKgDIGj0KpsCqvPc63oWYtT8oSLghI9KdSIDHPqshBq22kPbJQjspq6HBgtJaKNx6T3AfFXa%2BUCR3EOnPU69UcEui4Pgwhdo7qoAevEXCH9XowLSp9b6EjfqPSKoDJRwNBGgz8lwI8NAfTxBhnDKaaMkYo1ICYjGWMcYODMQTRgRMSZkz0hTKmNM6ZmKZlrHYziOaOG5vTYhqh%2BZgjMcLbom1xaSyRjLbxb0OSKxsirNWmANbMyMNrUA8i%2BAGwUEbE2ZtGBmKtpQ4a1DZAO0mnpBhLsdZhysB7SJcdfb%2B0vJwIOBAQ7ljqRHKO8QY48x9gnZuzgICuG7rNTOZR2653SPnbI9ci6pFmaXLO0zG6Jxrl3BZPcm7Vz6K3VZA8e5bNyIs3u8wplHJeusEew1WEbSmrPE6Z07iaLwQQohq98CkOkVvORH1d770PpQJyUUjyi1fu/AIhJ/IBD8mYeF%2BFEjAN8lPTa8VErQPeulTKOU8r7VUag8qlUODNBYPVFgChObNU5sIwkkJ9QEA6t87qvVZrFJtqU0a8haGVJ0CAEKTDloM3uWix5O0kEHSOqoClVKaV0oZcJcRkiN7QmhLI7FCiUDqJUSgnVoxqUpBSNaWlflrSKoINaGV1DIYGMoEYvSFiyY2SdVY3GtiJGE2JqTTaLjqZiHcUrTx6TYmkHwBiLmPMpp82QALUJghwliwllLeEMS5bxLMUk9IKTNbpPCJkj62SmCG2Nqbc2RSKGcokGUsavKnYCpqcYd2NhGnwGab0emuxg5u3DpYSOM9o49QGfHKuvRk6p1ORnFO/cc7F2WVkcZSyihZBnRXIZeza6tG2es4Z%2ByBiro7uMAYi7zkHrHjciy57RZsPRZwY6srqV3FNfS4USq14/OehqnepA94H1GPHCFEUBWfxRcFMw4GuCJA0HhOFYq4qcExSlb9J8z7AIATfaEARoPBR8s/aEDz4OQM1ePdqcGZ4If%2BQ5ZWBik6SCAA%3D%3D)

## Links

- [Source code](../../../../conceptrodon/typelivore/concepts/clarify.hpp)
- [Unit test](../../../../tests/unit/concepts/typelivore/clarify.test.hpp)
- [Example](../../../code/facilities/concepts/typelivore/clarify/implementation.hpp)
