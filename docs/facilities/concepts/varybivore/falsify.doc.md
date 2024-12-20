<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Falsify`

<p style='text-align: right;'><a href="../../concepts.md#varybivore-falsify">To Index</a></p>

## Description

`Varybivore::Falsify` accepts a callable predicate and a list of variables.
It returns true if the predicate invoked by the variables returns false and returns false if otherwise.

<pre><code>   Pred, Vs...
-> not Pred(Vs...)</code></pre>

## Structure

```C++
template<auto, auto...>
concept Falsify = REQUIREMENT;
```

## Examples

`Falsify` turns a callable predicate into a concept so that it can be used for subsumption.

Since `(not Pred_0(***))` and `(not Pred_0(***)) && (not Pred_1(***))` are both atomic.
Both candidates are considered equally good.
Thus, the call is ambiguous.

```C++
/**** Pred_0 ****/
constexpr auto Pred_0 = [](auto...){return false;};

/**** Pred_1 ****/
constexpr auto Pred_1 = [](auto...){return false;};

/**** fun ****/
template<auto...Args>
requires (not Pred_0(Args...))
constexpr bool fun(){return false;}

template<auto...Args>
requires (not Pred_0(Args...)) && (not Pred_1(Args...))
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<1>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwCspK4AMngMmAByPgBGmMQSABykAA6oCoRODB7evv5BaRmOAmER0SxxCVzJdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHAD0AFSH%2BwDUysSY6AD6GsdH%2B7smGgCCaAyzmKopxMdMXkSn5yuNxMAGYACLHEwBKwBMEQX5EAB0yJWJgA7BZzgRNgxjlQxEpQVY0WCiY8nuSDkcARdLlxbkcHs9Xu9Pt8EagaVd6aCIVCYXCOcjEaiMVicXiCZgySSyc9KXc8V5cXcmU8CJgWCkDBrQW4hcinsRgApQdhyecAI5ePDnBTHCAMVAELnXCBGk3Clao5kCVlfY4xVCeJUMCCizGYbHEXH42iEkHE0ny54arU66Ug/V/VDCj2mkHm55Wm12h1Ol1nWkad3GhRelaQswANnMzfLztdXFrnpRPpefo1bMDwdoofD6Mj0dxBGIXkzSfJCupABVMLMGYc1btdsdsMRiCRybMmI5kJcmAolC1qMq9VwzeHUYmOGtaJwArw/BwtKRUJw3GsaxjgUDYtkwJsQR4UgCE0V81gAaxAAJm0RRJmykAI0WbSQAE4QWwswQX0ThJF4FgJA0DRSG/X9/w4XgFBAajYJ/V9SDgWAYEQEANgIFI/nISg0C1Oh4kiVgdlUdCAFocOOYBkGQY4pERMxeAuQgSDwdA9H4QQRDEdgpBkQRFBUdQ2NIXQuFIAB3YgmBSTgeDfD8vzgv9OAAeT%2BASXVQKhjmk5s5MkBSlJUyQ1IdDxRPob5zCglZeFYrQ1ggJARJSMSyAoCBstykBgCkMw%2BDoDViCYiAYk8mJwmaABPFzeHq5hiEa7yYm0OpWOgkS2EEbyGFoZqrKwGIvGAfVaHjFrSCwFhDGAcRxttXq8AAN3XTyPjqP4dmg8INXfKzaDwGJHI6jwsE82c8Ao7heG24ggyUMFNWW86jDgtYqAME0ADU8EwOzvJSRh5v04RRHEEzofMtRPJs/RlpQIDLH0C6mMgNZUBSXomI4GTZnQXlTEsawzDol7iB0nbca6HoshcBh3E8do9FCBZykqPRCkyAQpj8WyBd6IZeeWJmNoEfpJg5vJbNqepZbmCWRiqcYBmFvQTxadWliqNZQM2bYJDcjhPxozz6OC2T5MU5TVLMB1cC0xKiK4FKYN%2BtYEEwJgsAScNSCQyQQURfC0UkDRJDMSRmyolDcJIjgyNICiQTMREQWbNFEhBRIAgCLgCNw5JaN4ejGOYn22Iy7jMt4vzBPywqEokthOBCsLjmQAwjBU3DES4RFf00og6d02zocMuHpARpQkas3QyocpyWotq3K68jhfP4v5jkCu3Qvk/vlqHkex9i1B4viSCzG9tL2Kb9v4iEgrb5yhKUAHkrcK4NRGgtBKrVVqlZNqTV5qQI6l1HqDh5oDUYAQYao1PITSmjNOaT0FqfSMKtX8%2BBzj1G2kTceqh9oanmsdbonlzqXSajdHYv57qPWgi9N6mAPpLXweEUA9c%2BAAwUMDUG4NIY4NnrDYyC9ZCI0sr%2BVeqMfoUysJjehOMQ740JpwEmBAybghUVTGm8Qp4MxDsrXorN2a5BFsENmBs%2Bai3SILbICtbFiyyA4qWFiGhzB1krboMs%2Bhqx5hrXWfi3HhIGF4o26xTbGS3h5Kytse5nz/pfUeNwIBu0npBL2qVfakH9oHUYIckKAOoqddOmcAiIjwgEXCZhGktkSKXHC1tkmcBrixX6HFG5ID4v5D%2Bb9iCdx2M0Fg8kWAKE2spTaXBh4ZlmBpfAk8dJ6VkHPaRpl5BL3kToEAxF17OSeokjpdEfItwCkFVQUyZlzIWYiJZLoIBxW/vfJKIIn69Nfl/XKwy/k/1mSkFIlx5m4UuM8y4tyF4VXiGAuqDUOrQKRZ1bqvVEG30GigkaY1CGYEmtNMQ2DoKLS%2Bsw3gRCNqkN2hQ5AB1qGCFoWdC6V1GpMLunTNhz14icO4V9PhvT/pMCBiDMGENvzQUkUZCQMizJ7ORocpRxgMY2HUfAPGBMshE12KTdGlNLDUyrrTemGjjaBJVn4CArh/F2PQDE/mzjei2o8SUUJhtdYWt6HLVokSAnM1VtE91jitbyxsVE/WwbljGzAmbL2qdt4204MFO5szjjgqeaedcLyckkDyd8%2BufsA5B0oBbaphzs5tKImYGt1QNDNgaecquXTbC12ft6UOIBw4j0LgEOOIIAj1qIthVOIIkkXIYnXdKFt1JNt3gUwtpAXoZGcJIIAA%3D%3D%3D)

By turning `(not Pred_0(***))` and `(not Pred_1(***))` into concepts, we allow compilers to perform proper subsumption.

```C++
/**** fun ****/
template<auto...Args>
requires Falsify<Pred_0, Args...>
constexpr bool fun(){return false;}

template<auto...Args>
requires Falsify<Pred_0, Args...> && Falsify<Pred_1, Args...>
constexpr bool fun(){return true;}

/**** Test ****/
static_assert(fun<1>());
```

## Implementation

```C++
template<auto Predicate, auto...Variables>
concept Falsify = not Predicate(Variables...);
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwCspK4AMngMmAByPgBGmMT%2BABykAA6oCoRODB7evv5BaRmOAmER0SxxCWbJdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHAD0AFSHR8cnp0e7JhoAggdHANQAkiwp9GyCTL13xxfXt2f/Zx%2BV0uVwImGeBjBJgAzG4mF4iHdlMRMPhRGDSHd4UQAHR4gBqzTwTBi9AUMOwILQDG2KQIdwAYmIMlQAJ53GEAETuDFQ9ORqLw6MwEEJxGJpMwCjxOJWMKs1xBfwB5yVxzuABUpQQFF9Vb8VScgWr7gL0AB9DR6w5A6mzTCqFLELEI1BIlEWq1cjkBKwBTkQbGoGVygDsFhRBE2DDuVGZmHlJlDnMTioNpo95q41v2toE9sdzqD7tRWY50O5Jl9VYDQZDSYjmCjxBjcdoSkTydTwPTh1jXhj3xBYIhHwTsLreKuxGA5OhlOuKIAjl48CjdUz23g2TC3GbLZjp7OZRSqfmwYW7jFUJ5%2BwwIGHG83W/HOym06DwS8x7vJzij3OC7TpgK5rlKjLMturK7vuGiHjO0p4hSHJmAAbOYqEQVuO6wvuXDwceSHzmeDAFk6V43rQd4Pg2kbRncBDEF445WF2H7Kpq2o5kCswfEK5pMAoSgtNQA67lwFIPnK0IWBway0JwAS8H4HBaKQqCcG41jWHcCgbFsmAodCPCkAQmhyWsADWIABKhOKJKhUgBKGqGSAAnNCLlmNC%2BicJIvAsBIGhwSpakaRwvAKCAcFmapcmkHAsAwIgIAbAQKQIuQlBoM8dDxJErA7KoDkALSuXcwDIMgdxSDiZi8IKRDiugej8IIIhiOwUgyIIigqOocWkLo%2BEAO7EEwKScDw8mKcp5nqZwADyCIZfSqBUHcxWoWVkgVVVNWSHVdwQB4uX0M65jGSsvCxVoawQEgOUpHlZAUBAT0vSAwBSGYfB0GCxBRRAMTzTE4TNKyU28GDzDEKyi0xNodSxSZOVvAQi0MLQkODVgMReMAcK0O2UOkFgLCGMA4i42B9QAG5SvNDp1AiOwmeEYIKYNtB4DE41wx4WDzYxeCBdwvAM8Q15KJy4KUzzRjmWsVAGLO%2BJ4JgI2LSkjCk21wiiOI3X631ajzcN%2BiUyg2mWPovNRZAayoHSWRRRwJWzOgXKmJY1hmGFkvNYzjtdD0WQuAw7ieO0eihAs5SVHohSZAIUx%2BPhye9EMCejPhtT1AI/STNHeR590yMNHM2cjAkedzGnei8S01dLLXax6Zs2wSDNHBKaQoW8OFm2leVlXVbVZjHbghAkEZXDXaZStrAgmBMFgCQPqQ1mSNCOIeaGkgaJIZiSKhwW2W5vkcP5pCBdCZg4tCqGhok0KJAEARcJ5bnJAPC0RbYaKi84r3WSg9VKK1MpvQ%2BudAqbBOBbR2ncZABgjA1TcjiLgOI1KNRIHgFq%2BF9YdSNtIE2SgzaDV0L9MaE0oY9z7n/cKy10oIjuOtYe21yooMpugzB2DjqnWeudIyZgF63XiuAmB8QsrvVQGdUY3CjBcDclwOCNBaAAyBiDQaMMIak10XDBGSMHCkzRowDGWMcZqTxgTImJNxZkzlkYam1jaaOAZm7HBqgWZglJhzbo80eZ8whoLHYakRZixMpLaWmBZYU2ceEUAIC%2BCqwUOrTW2tdYOKIYbLqpDZCmwGmpKhltFY%2BysLbIJDtN7O16G7D2BAvYVnKX7AO8Qg7VPbuXAufgICuAbvhOOZQa5J3SCnbIJd06pDGVneOIyy5h0LvXSZjdum9CLvMYZrdG7LNyFMpumzFiJ3nusTuXV6FzUGkPRBXDUHAF4Vgq0EBp5NTnmIpepAV5r1GJvayqi4JcxvnfAIOJ3IBDcmYCFaFEhf1cv3ea4VIpAPEaA%2BA4C0qrRkVI4gcCdjNBYOVFgCg6bVTpsonEkJtQNXwE1fBrVZDELyT1eQ5Cik6BAD5Ghk1xYXPhVcpakC1obVUIS4lpLyWUtmAIuRQj4hGWhO85JkiZUvSxSq86IASUpBSOaMlblzSSoIOaEVpD/rxC0aDcGcN9FWvhojZGpi5Ho0xtjeaNjCZiHsSZcm8swm8HwCiemjNBrM2QKzPxggAnc15vzVkoThbikiRLeIMS4ny0SUrFJTA1Yay1jrFSJkcmdQkPk3qrLzYctKcYG2NgqnwCdi7fMnBdie2tr7Sw/tB6B3wcHTe%2BdegRyjns2OkcW7HOmUULIAyJ3jLHbnUOFclkDGnf2yuAw5213GMulZdd11zO2ScjuBlu5XwYQizgm1RUkruHqilY4pXPJpbPS688bofK%2BevSgPcgUcofrC7yZhANcESBoVC4K%2BVhU4EimKHzt67y/u/Y%2B0IAige8i5K%2B0JLmQYASinu9UIODyg8Au6axJYZGcJIIAA%3D%3D%3D)

## Links

- [Source code](../../../../conceptrodon/varybivore/concepts/falsify.hpp)
- [Unit test](../../../../tests/unit/concepts/varybivore/falsify.test.hpp)
- [Example](../../../code/facilities/concepts/varybivore/falsify/implementation.hpp)
