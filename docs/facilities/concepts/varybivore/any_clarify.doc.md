<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AnyClarify`

<p style='text-align: right;'><a href="../../../index.md#conceptualizations-3">To Index</a></p>

## Description

`Varybivore::AnyClarify` accepts a callable predicate and a list of variables.
It returns true if there exists a variable for which the predicate evaluates to `true` and returns false if otherwise.

<pre><code>   Predicate, Variables...
-> (...||Predicate(Variables))</code></pre>

## Structure

```C++
template<auto, auto...>
concept AnyClarify = REQUIREMENT;
```

## Examples

`AnyClarify` turns a fold expression of a callable predicate over `||` into a concept so that it can be used for subsumption.

The following code will fail since `(...||Pred_0(*))` and `(...||Pred_0(*)) && (...||Pred_1(*))` are both atomic:

```C++
constexpr auto Pred_0 = [](auto...){return true;};

constexpr auto Pred_1 = [](auto...){return true;};

template<auto...Args>
requires (...||Pred_0(Args))
constexpr bool fun(){return false;}

template<auto...Args>
requires (...||Pred_0(Args)) && (...||Pred_1(Args))
constexpr bool fun(){return true;}

static_assert(fun<1>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwCspK4AMngMmAByPgBGmMQSAMykAA6oCoRODB7evv5BaRmOAmER0SxxCVzJdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHGgMs5iqKcQA1ExeRCfKxJjoAPoaJyaJACJPAVYBLxDnRAB0AJWJgA7BYbgRNgwTgRiF5MM8rMCXgiTBoAIKotF7A5HU6/VBXG73LhPV7vT7ffEAv5A0HgyHQ2HwxKI5EszGYgiYFgpAxc55uKkAtHEYAKZ7YTE3ACOXjwNwUJwg1JBblV11uDwgIrFKyB6OxXNxJxiqE8JyoXgYEFpYMwEOIUKoYiUKKRHPRXJ5fOZgouqGpOvFiUl6JlcoVSpVwLVMY19w02tFCj1TzMADZzOmowDVeqiXcuEndfqsQIcccTWbaBarTaQXaHVCYXC3cj0ZjZkxHMg7kwFEoWtQrQKuBKbUCWRw1rROAFeH4OFpSKhOGrLNYTgoNltMGnEjxSARNNO1gBrEABdN/AAc6akAWB6ckAE5Ek%2BzMlZxxJLwWBINA0UhF2XVcOF4BQQCA48l2nUg4FgGBEBADYCBSC5yEoNAeToeJIlYHZVDvABaZ8TmAZBkBOKQ/jMXhbkIEg8HQPR%2BEEEQxHYKQZEERQVHUWDSF0LhSAAd2IJgUk4HgZznBcTxXTgAHkLnQggTlQKgTiI9NSMkcjKOoyRaKVDwcPoU5zAPFZeBgrQ1ggJBsJSXCyAoCBnNckBgCkMw%2BDoLliEgiAYgUmJwmaABPaTeHC5hiEipSYm0OoYMPbC2EEJSGFoaLBKwGIvGAQVaFoSDuF4LAWEMYBxHy%2BVUrwAA3TByuXQ46guHZD3CLlv2XWg8BiCSEo8LAFJhPB/wq0gWuIU0lBebkasGowTzWKgDDFAA1PBMFEpSUkYGKeOEURxG4tj5CUNQFOE/QapQaxrH0IbIMgNZUBSXpyuI2Z0GeF5TA3SwzFAubiGY1r4DWWp6mcCBXCmPwRNCBZykqPRCkyARkax9IcYYIYMeWLoegaOY8ZEuHen6FpiZGKpxgGKnmfp9HGYkWGd22Ln9Dk4CFLA7SSLIiiqJoswlVwRjLM/LgbKPda1gQTAmCwBIbVIC9JESP432BSQNEkMxJHTQCrxffmfz/EADz%2Be90xvF8by4dMAkkLgAjfdNBcEsCIKgpXYIcpDHJQ1SMPczyLPwthOGaFgmuBYimBOZADCMaiXz%2BLg/na/AiEhliRKujiLukK6%2BNuwTdD88TJJi2SOHnP3QOUyP1M0s5iCTlO04zmrs9z/PTNQcz4n3MxFbsuDw5j%2BJMI88eXIskBE%2BT4jB6MLgXy4ICaFoQLgtCwS4qik7z4SpKUocE6MsYAhstyhSCqKkqypOqqVp2Zd8BueoLU2r0VUJ1LkJ1erdAUoNYaUUxq/1spDaah45oLUwEtaqRhVqgBDnwLaChdr7UOsdGaZdzpcUrrIauAllx1wemtYGVhLCvRiO9LWX0fqcD%2BgQAGrxGHWDBrwVAEMoZsNht0RqCMkaeHaHoNGZROYiWxr0VmyisgMyWEzGmFMWYyLyNTCR8M%2BhzA0ZjamlM9EozZvMBRmi%2Bbbk2LzBW1tW4gSEZwHufdU7p0zsAYeedHgQBlkXfcCtbLK1IKrdWowtbfl/KQf8iQc7G2BN7YEwJEgmzNp7Nu7jwK2CDrPUO8Bw6oTUkvBexA447ETmRFgCgmpUSarvP4PpZj0ULkxEup1y4UNOtQu6dsxISSkhVZurihYdzQhcDSWlan6XqY0k4zSc5tPUhAMyq9J5WUSDPda8EnIr1chUo5a9GkpBSHcFZdw1l9l7s%2BfyR94gnzChFBKl83mJWSqle%2B49MpPxynlP%2BmBCrFTEJ/Ga38sEINIP/RqQCFIdWQF1CBggoGCRgSNSK8CJpIJOqg9I6DlpYPCDg%2ByeCmA7T2gdI6i5DxkM4hIShvEbo0J0EM3xT0QY2BgWIlc30sjlQAPT/S5UwiwgiVwiKwHy7RUiGDuEsXIhVpjSZqNxkqpRBNeiqq0YY2mFjchWLlcYgYuq9BdkmJq6x5rnEON3Hzb8Ez/YePmScRZTSWlrOlp0uW1lwkhxVmrDWlBm7xP/GYHOiREgBACMbfeGho1PhvLkxS%2BTILQQiTrPW1Qbwe0/HG9Mn4nzW0SPJF1%2BSinNzoqmgOwd7JrDmhkZwkggA)

By turning `(...||Pred_0(*))` and `(...||Pred_1(*))` into concepts, we allow compilers to perform proper subsumption.

```C++
template<auto...Args>
requires AnyClarify<Pred_0, Args...>
constexpr bool fun(){return false;}

template<auto...Args>
requires AnyClarify<Pred_0, Args...> && AnyClarify<Pred_1, Args...>
constexpr bool fun(){return true;}

static_assert(fun<1>());
```

## Implementation

```C++
template<auto Predicate, auto...Variables>
concept AnyClarify = (...||Predicate(Variables));
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwCspK4AMngMmAByPgBGmMT%2BGqQADqgKhE4MHt6%2B/kGp6Y4CYRHRLHEJZkl2mA6ZQgRMxATZPn6Btpj2RQwNTQQlUbHxibaNza25HQrjA%2BFD5SNVAJS2qF7EyOwcBJgsyQa7JgDMbkxeRADUysSY%2BKK7pJfnRAB07wBqTXhMMfQKJ2wJg0AEE0AwtskCJcQQwAJ5uAzEPBUOGXE4AEUuEHerxMAHY3AS3Dc7ngHpgIF9kb9/stlicrKDgSCAPQAKk5XO5PNZLI5XMuABVMDMFJduXzQQKebLOVKQSzwTNMKpksRnhdUNdbugAPoadHHLEmAJWAIYiAvVC4hn4iy3AgbBiXAjELyYRkEjFe5mg5W7NUa606u56rhGk1m02W622gkOzBO4gut0er34n3HJmK0G7faHT2nOPvEHEYAA45A0G3ACOXjwt3FsIRSJRcJOJN1BqeZYruMBSoEKqDlxiqE8lyoXgYEDtieTLqoYiUGZ9fpB%2BYOTCOxa1uL7lerZcw9cboph8MR31RndJ%2BqSMPLCgHVfRZgAbOYP5fWzeO6c97hr2z6vseAaquqY4TrQU4znOCaOs6rrukWViZiyLIzDu5J6kwChKM01Azp2XCAnODLZhwqy0JwAS8H4HBaKQqCcESljWJcCjrJsmDvscPCkAQmjUasADWIABJIrwaJIXD4scGgBBon4fmYAAc6n6Jwki8CwEgaEkjHMaxHC8AoIBJMJTHUaQcCwDAiAgOsBDJBc5CUGg%2Bx0PEkSsNsqjqR%2BAC0H6SJcwDIMglxSK8Zi8GSRDIugej8IIIhiOwUgyIIigqOoNmkLoXCkAA7sQTDJJwPA0XRDEiSxnAAPIXG50KoFQlyBSFYURVFMXSWY2IeN59AauYAnLLw1laKsEBIF5yQ%2BWQFAQIty0gMAUhmHwdC7MQFkQDEDUxOETRwtVvCncwxBwk1MTaLU1mCV5bCCE1DC0BdhVYDEXjAGctC0BZ3C8FgLCGMA4g/eedQAG6ig1qq1Bc2yCeEuy0YVtB4DEFW3R4WANW6eD6aDpAI8Q45KBieyQzjRgiasVAGBWHx4JgpVNckjCXTlwiiOI2VpfIShqA1xX6JDKDWNY%2Bi4xZkCrKgUKZCDwUzOgmKmBxlhVLwqCU8liNK503SZC4DDuJ4bR6KE8xlBUegFBkAiTH4JUuz0gyOyMJU1HUAh9BMNu5P7XRPfUsw%2B8MCT%2B7M7t6NhzQx4scerNxGxbBItUcPRpDGQbnBdUFoXhZF0WxUNEC4IQJD8VwU1CUzqwIJgTBYAkc6kBJkjHK8ACcxz4pIslmJIH6GQEH4D9pHC6aQ%2BkCa8H5cB%2B6kD%2Bpa9SVwARDx%2BBcNaZ5mWc3NlzY583Oa17mretY1%2BWwnBNCwcP4sFTCXMgBhGDFA%2BvFwGSCV8BJTwClEqIsMpC2kCLPK4tCq6B2uVSql1c750Lo1DgLVXIXEuB1Z4xBX7v0/t/SGf8AEyWGqgUa8R%2BJmCbjNWyV977xA8mtahS0xogBfm/YKpCjBcAHlwJINBaD7UOsdQq11zp82kbde6j0HB81eowAgH0voNV%2Bv9QGwM%2Bbg3ptsZi%2BBbjw0RoVZGyBUZ8wxl0BqOM8bnUJoY6ayIyaCUptTTAtMIZGAZqAc%2BfBWYKHZpzbmvNyaQMFllGBsg4EFWYogqWjMdZWEsPLGIitu4qx6OrTW2tZZ6xMkbMBJtu4Bx6Jba2OQPbBCtqnJ2ns0iuyyKHGpXtMj1L9mbSOQcE6tKThHQOvRo4O1jknPp1Txn9E6enNYWcspoPqoVUyBCiEfy/j/YA5DAGGhriA%2BuE1G7TRbqQNuHcRjdyxgvJe/9ZL4j3viBSkhx5hRKhg4%2BthT6MIvvAK%2BLk2psJYcQR%2B2wX69RYAoOG0U4aCNeIWGYwC67JVSrIKB0T%2BZxIliAY4ZUKpVVBosw%2Byzmo33ap1MF4UIVQsuDC/%2B8LoQQBGpw2hE1jgMKZnZBaHDlqAu5VwqFyRkh6lpXqeleFCFhV2mI%2BIEiTpnVurI%2BVd0HpPWUdQt6ajPrfSMZgP6AMxC6PJvo3xzjSDGMjgjEGzELFWPJjYrGzF7H4wRBgU1JM3G8A8WkLxdNfHhH8bNQJTA2Ycy5jzRiglImZQkDE3KYt4k6GxUk4wBSbD2MycrVWw5OCsk1jLXWFh9YsWKVgDN3ShmVMTiVe2pQxmNMKJkKtKQmne1GWnAZ5ten9CbeUqO0y20NLGN2/p8d%2B21vbY3OZvEc5z3QUfYuFLLhUuhbC%2Bl2Ja5JQbuy8%2Brd26d0oLna5/h/7HGOAEZSclDKnvxOvIlJlOAnysic3uARB4BHUp%2BAekgB4KWHlwHFWNjhLPvWZM%2Bs1c7xTvUXUD3zViU3SM4SQQA%3D%3D)

## Links

- [source code](../../../../conceptrodon/varybivore/concepts/any_clarify.hpp)
- [unit test](../../../../tests/unit/concepts/varybivore/any_clarify.test.hpp)
