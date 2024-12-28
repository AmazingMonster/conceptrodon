<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Deceive`

<p style='text-align: right;'><a href="../../concepts.md#varybivore-deceive">To Index</a></p>

## Description

`Varybivore::Deceive` accepts a callable predicate and a list of elements.
It returns true if the predicate invoked by the value results collected from the elements returns false and returns false if otherwise.

<pre><code>   Pred, Es...
-> not Pred(Es::value...)</code></pre>

## Structure

```C++
template<auto, typename...>
concept Deceive = REQUIREMENT;
```

## Examples

`Deceive` turns a callable predicate into a concept so that it can be used for subsumption.

Since `(not Pred_0(***))` and `(not Pred_0(***)) && (not Pred_1(***))` are both atomic.
Both candidates are considered equally good.
Thus, the call is ambiguous.

```C++
/**** Pred_0 ****/
constexpr auto Pred_0 = [](auto...){return false;};

/**** Pred_1 ****/
constexpr auto Pred_1 = [](auto...){return false;};

/**** Vay ****/
template<auto I>
struct Vay
{
    static constexpr auto value {I};
};

/**** fun ****/
template<typename...Args>
requires (not Pred_0(Args::value...))
constexpr bool fun(){return false;}

template<typename...Args>
requires (not Pred_0(Args::value...)) && (not Pred_1(Args::value...))
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<Vay<1>>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwapK4AMngMmAByPgBGmMQgZgCspAAOqAqETgwe3r4BQemZjgJhEdEscQnJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlUbHxiSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwA9ABU%2B7sA1MrEmOgA%2BhqHB7vbJhoAgmgM45iqqcSHTF5Ex6cXVxM/gAIocTEkrElgRBvkQAHQIpYmADsFlOBHWDEOVDESiBVmRwPx9weJL2Bz%2BZ3OXGuBzuj2er3en1hqEpFxpQNB4Mh0NZCLhSNR6Mx2NxmGJhOJjzJN0OADUmABPWn7ekPAiYFipAyaoFuVmHACSQOwJPGxC8DgVypJKKsj0OTsOs0cyEOjM1zK%2BPzZADcxF5MGDUSapf4HaTw5HZRSqF4sTd1ZrtbqJf43AQlalGKxMAKHsRgApTSTTgBHLx4U4KQ4QBioAjsy4QQvFkAgAPefOIpEMgRMj6HGKoTzYhMQIVozAY4hYnG0PERlFEmWPFM6ph6jNZnPMNgFosl/xmx4Vqs1usNpsnKkaVtHjtdoMCpZLMFmABs5k/V8bza4B9207QMe0FPsngHL0hxHMd4wYSd7RFOdDgIS10wJVdSUecl9kOAAVTBxlVW4yW2Q5sGIYgSHNZo3XOJgFCUVpqATfVFSVfUuFLE9JyRCMOBWWhOCSXg/A4LRSFQTg3GsawXTWDZg3MfweFIAhNEElYAGsQCST84QADk/KQkmRT9JAATn8cyzH8fROEkXgWAkDQgnEyTpI4XgFBAIINIkwTSDgWAYEQEA1gIVIfnISg0G1Oh4kiPNOFUYyAFoLMOYBkHdKQ4TMXgzkIEg8HQPR%2BEEEQxHYKQZEERQVHUQLSF0LhSAAd2IJhUk4HghJEsTNKkzgAHkfmiptUCoQ40s/TLJGy3LDnysw6w8BL6E%2BFSuCWXgAq0FYICQeLUkSsgKAgU7zpAYApDMPg6E1YhfIgGJhpicIWiVPreE%2B5hiCVUaYm0TAHF%2B0h4rYQRRoYWgfparAYi8YADVoRcIawFhDGAcREerMHHD9IjhreMGfi2NTwk1YSWtoPAYm6wGPCwYa0LwFzuF4YniBHJRgS1HH6aMTSVioAxi3lPBMA60a9whyrhFEcQ6sVxq1GGtr9BxlA5MsfQGd8yAVlQVIGl8jh0vGdAuVMSxrDMTyeeIMqSeN7pCeyFwGHcTwOj0UJwiGSoRnaoosgEKY/DDjII4YeZhgSdq7E9gQ%2BkmP38mTupU8aCYBiDhZQ9sfOo70WZWgTkOk5WBRFM2CQBo4UTSA83gvNmjKspyvLJAKutcBK7a7N2/bRZWBBMCYLAEknUhdMkfw4Ws5FJA0SQzEkT83P0yyHI4JzSBc/wzDhfxP2RQz/EMpIki4GzLMM1vhq8ny/PU0XgrC46IommLLuultZKbBUpd0WsgAwRgVqWThFwOEklipEBduVdqitqoq2kGrJQGsWq6Ael1Hqv0m4tzbiNDg40oo/EONNTu80soQJxtA2B8D1qoE2vED8J89of0CkdE6bCzpbVildARN0GFGC4JZLgQQaC0Geq9d6LV/rfQhsowGwNQbgy5pDNh0MCCw3hsNJGKM0YY20VjIWWxJL4FOA4PAxMLYINUOTTUENqZ1GGvTRm30WZWP2i7TmakeZ80wALbGRhhagF4XwCWCgpYyzlowBWsh0G1UwbIdWzVJJ4O1iLO2Vh9ZeKNnPU25tOBWwIDbEE%2BSHZO3iMgt2c8U52OcBAVwZd2qB3KInPQ4cGgdLSLHBoVdFjZx6GnUumdo4exaXnOYhcenJ0mXkaZFcC7dOro3VY6wG67X3iQl%2BnBaELQ9JA4ATC4FXAgIPJBnDR48MOhPKeM9KA6VckEWmh9j5JDhFZJIlkzAAq/IZe%2BFln4tVfrYd%2BB0gohXCpFSawjAFJRShwFoLAsosAUH6d0fpJFwjTOMIq%2BAkFlQqik5WaT6ryGwVknQAROrdV6lzYhQ0IVjT/lNGaqhMXYtxfiwlTYIAbUERwlS/huEwr4SgURQiAGypGDi1IqRzh4ssucQV5weWYKevEBRH0vqA1UYaoGINCYQyhowfRcMEbWMwMjVGYgzFqQsREvxpAbGewcaTZxyAKZuMEB4umDMmZKl8WzAJENgkZFCYLCJ4QomHRiUwSW0tZby20WgylEh0kNVpZrBlZzdb20KYbeAJszbZAttsa2xaCkWEdu3Z2rtim1xzrM72vsVkBx9iM4ufTsgDIHaUBZmyxm53Tm0KZ5d20NEnX2pOJd%2BgDLWQurZdcdm1VZeCzyRztWHCxTiw4aqCVbiIkKm5JA7mSvHqQSe08Rhz0%2Bc5AIp9QV2TMJ%2BrghkNCfn%2BTu9unA37%2BVvQvJe98b4b38EkX9dlzL738Gy3d3kHlaX3oVADZCx68JWDzTIzhJBAA%3D%3D)

By turning `(not Pred_0(***))` and `(not Pred_1(***))` into concepts, we allow compilers to perform proper subsumption.

```C++
/**** fun ****/
template<typename...Args>
requires Deceive<Pred_0, Args...>
constexpr bool fun(){return false;}

template<typename...Args>
requires Deceive<Pred_0, Args...> && Deceive<Pred_1, Args...>
constexpr bool fun(){return true;}

/**** Test ****/
static_assert(fun<Vay<1>>());
```

## Implementation

```C++
template<auto Predicate, typename...Elements>
concept Deceive = not Predicate(Elements::value...);
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwapK4AMngMmAByPgBGmMQBAKykAA6oCoRODB7evgFBaRmOAmER0SxxCf7JdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHAD0AFSHR8cnp0e7JhoAggdHANQAkiwp9GyCTL13xxfXt2f/Zx%2BV0uVwImGeBjBJn8biYXiId2UxEw%2BFEYNIdwIAE8UoxWJgAHRE7CvRgEBTQ7AgtAMbYpAh3AAidUweAAbpg7tDGXcGKgGUiUXg0ZgICTwWSFCAQGyxF5CUSVtCrNcQX8Aec1cc7gAVTCzBRfTW/DUnIFa%2B6C9AAfQ0RsOQJps0wqhSxDucIRVttXP8PJMiSsiUZEE9qCJBKVAHYLMiCJsGHcqGIlMqTFHGWnVSbLcibVx7ftHQJna73WHEXnrQXuVzAwGQ2GI9HY5h48RE8naKn/FYM1ngTnDncAGpMLGFoFgiEfTDQ2Hw1CPSkg2bELwOUfjkHplVXO4Hu6zD7Cu5OsFlj2Lu6y7yc3cPdOZ3s7/sv7M3bVULyJ74g6cvLO87YrizBsBGVzEMAFL%2BFS1zIgAjl4eDIoazLbOyc4wt6QR3JB0ERiu1zni6bp3DEqCeEmP4QC2cYJkmKZYX2mYfgBkJYW4IF4uBRL4TBcGQZgSEofqTIsph844Ri/GEbBXJmAAbOYiniRhHJSVWXAyVBChyYJJGXhRVHfgwtG7vRHaYuuzFPjuQ77Lq%2BoMn%2B1zHo4yDWkwChKC01A/vOY5YvOXArrBtFKr2HBrLQnCJLwfgcFopCoJwbjWNYR4bFs95mP4PCkAQmjRWsADWICJIpBIAByKVIiRRopkgAJz%2BI1eX6Jwki8CwEgaEEiXJalHC8FKQRFUl0WkHAsAwIgIAbAQKTwuQlBoM8dDxJE%2BKcKotUALRNXcwDIMgdxSASZi8EKRDEHg6B6PwggiGI7BSDIgiKCo6iTaQujaQA7sQTApJwPAxXFCXFSlnAAPLwstDKoFQdx7Yph2SMdp3nZIl13BAHgbfQ7rmPlKy8BNWhrBASDrSkm1kBQEB0wzIDAFIZh8HQYLEFKEAxNDMThM0WJg7wQvMMQWKwzE2h1BNBXrW8BCwwwtCi79WAxF4wCwrQ3Zi6QWAsIYwDiJron1ByUq/S6dTwjsBXhGCsW/bQeAxMDUseFg0MEHdvXcLwHLEBRSjMibRju0YxVrFQBjQSOeCYADsOgYbT3CKI4jvZnX1qND/36KbKAZZY%2Bge1KkBrKg9JZDb%2B2zOg3KmJY1hmENId3VgVe0V0PRZC4DDuJ47R6KECzlJUeiFJkAhTH42mz70QxT6M2m1PUAj9JMo95Bv3Tyw0cyryMCQb3MC96MeLSn0s59rAo2XbBIEMcPFpCDbww2owdR0nWdC6Zh8a4EICQBSZMKaxzWAgTATAsAJD7uVSQ/gCStSjJIDQkgzCSEUv1SqzVOocG6qQXq/gzAEn8IpKM1V/DVUSIkLgbVmrVU/tDYao0QDjVjtNOaNMFoIxWkzFmxNtpsF2n/TGyADBGHOs1AkXACTJRuiQe6j1ZAvRztIPOSgC6/V0JzIGIMxZvw/l/GGHB4ZLXhHcZGv90ZHWkabORCilH40JvTYmECzDk0Kjw/hIj4irWZqgImownFGC4M1LgQQaC0B5nzAWv0JYi0NikqWMs5YOENkrMkqt1bQy1jrPWBsg5G3BKbc2yV8DIitvqaGdtkAO0Ns7bo0N3aexFj7HYyV/Z4EDgVEOYdMAR0qeEUAk044JwUEnFOadGAZw0dnN62jZD5x%2BslAxxcY6tysOXDpvca51xLJwRuBBm5%2Bl2e3Tu8Ru71Orv3I%2BzgICuCvtpCeZQz4z3SHPbIe9F6pB%2BSvSeXyD4D23pff519D5bz6CfEF99r6QtyACm%2B8xPmIq4I/Z%2Bb1TFQ1%2Bj/NGGMzwyOAC4xRdoxT4FuhArFUDJkwLgQgygZU%2BpBFdiQshiQCQtUSM1Mw/KlLVSYU1NhBLOCcO4ZM3h8B%2BGLURsEwJxAxE7GaCwI6LAFBsjOmyKJBIOKzGutS1RD1tKZ00Ssj68hdEbJ0AEUgRjQZBzxWKoacNBFIxRqoDVWqdV6oNQyAmoTPHxAgf4XxlMpoBODQzRVMbiYymQCkFI1pdXNWtAG603rtHc3iIkwWwspZpMLdLWW8scmhOVvkjW1TMDa11mIUpBVjaVJ6bwGpR9rYNNUPbMELTBBtLdh7L2WJul%2BwDobIZ6QRkVKjuMnh8cmCJ2TqndOZTzXLIkKsz6NrC72tJaXNu%2BzK7wCOb0G2uwm6Hr2RYDu38u73XuX3TevQh4jxRePYed9p5LyBVkN5gKihZG/evR5sKd6tChWCp5cKBggfPuMAYAG0XwdfusTYL8sVELMewzgqMfXapvP62cswQHGpJnlOlfiGWkFgfA0YfcOU9QCBQkVeUzAca4NVDQik%2BWuu/hK2wXDqNU1ZSghRdDEjYOqDxvKjUiH%2BHxW6kaImSpEKuvxix9LROkBDhkZwkggA%3D)

## Links

- [Example](../../../code/facilities/concepts/varybivore/deceive/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/concepts/deceive.hpp)
- [Unit test](../../../../tests/unit/concepts/varybivore/deceive.test.hpp)
