<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::IndependentLeftInterview`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-independent-left-interview">To Index</a></p>

## Description

`Mouldivore::IndependentLeftInterview` accepts a list of predicates.
Its first layer accepts a list of elements and returns a function.
When invoked, the function first binds the elements to the front of every predicate;
then, it returns the index of the first argument that satisfies all newly formed predicates, or `-1` if it cannot find the argument.

<pre><code>   Preds...
-> Es...
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> (...&&Preds&lt;Es..., Arg<sub>0</sub>&gt;::value) ? 0 : (
   (...&&Preds&lt;Es..., Arg<sub>1</sub>&gt;::value) ? 1 : (
            &vellip;
   (...&&Preds&lt;Es..., Arg<sub>n</sub>&gt;::value) ? n : -1
   ))</code></pre>

## Type Signature

```Haskell
IndependentLeftInterview
 :: template<typename...> class...
 -> typename...
 -> typename...
 -> auto
```

## Structure

```C++
template<template<typename...> class...>
struct IndependentLeftInterview
{
    template<typename...>
    alias Mold
    {
        template<typename...>
        alias Mold = RESULT;

        template<auto...>
        static constexpr std::make_signed_t<size_t>
        Mold_v {RESULT};
    };  
};
```

## Examples

We will find the indices of `int**` and `void` in list `int, int*, int**, int**`.

```C++
/**** Metafunction ****/
template<typename...Args>
using Metafunction = IndependentLeftInterview<std::is_same>
::Mold<Args...>;

/*** Tests ****/
static_assert
(Metafunction<int**>::Mold<int, int*, int**, int**>::value == 2);
static_assert
(Metafunction<void>::Mold<int, int*, int**, int**>::value == -1);
```

## Implementation

We will implement `IndependentLeftInterview` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:** Check several parameters at the front of the list.
If a match is found, then its index is returned.
Otherwise, drop the checked parameters and call itself with the rest.

Here's a simplified version of it:

```C++
template<template<typename...> class...Predicates>
struct IndependentLeftInterview
{
    template<typename...LeftSides>
    struct ProtoMold
    {
        struct Slash
        {
            template<typename...>
            struct ProtoMold
            { static constexpr auto value {-1}; };

            template<typename First>
            struct ProtoMold<First>
            {   
                static constexpr auto value 
                {
                    []() -> std::make_signed_t<size_t>
                    {
                        if constexpr 
                        ((...&&Predicates<LeftSides..., First>::value))
                        { return 0; }

                        else
                        { return -1; }
                    }()
                };
            };

            template<typename First, typename Second, typename...Others>
            struct ProtoMold<First, Second, Others...>
            {   
                static constexpr auto value 
                {
                    []() -> std::make_signed_t<size_t>
                    {
                        if constexpr 
                        ((...&&Predicates<LeftSides..., First>::value))
                        { return 0; }

                        else if constexpr 
                        ((...&&Predicates<LeftSides..., Second>::value))
                        { return 1; }

                        else if constexpr
                        (
                            ProtoMold<Others...>
                            ::value != -1
                        )
                        { 
                            return 2 + ProtoMold<Others...>
                            ::value; 
                        }

                        else
                        { return -1; }
                    }()
                };
            };
        };
        
        template<typename...Agreements>
        using Mold = Slash::template ProtoMold<Agreements...>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGz%2BpK4AMngMmAByPgBGmMQgAJzSAA6oCoRODB7evgFBaRmOAmER0SxxCcm2mPbFDEIETMQEOT5%2BgTV1WY3NBKVRsfFJ0gpNLW15nWN9A%2BWVIwCUtqhexMjsHAD0AFR7%2BweHRztbJhoAgrv7ANQAIpgprozIeJgK1wenF1fHv4df5zOgLMAGZwshvFhriYQW5kGN0FgqDDsEDzGCGBCvFCYW4CABPR4AfQIxCYhAUKLR3z%2BtP%2BQJ%2BO2uAEkWCl6GxBEx6h99gDGXS/gCgQRMGyDKLcaLxdzMFLCYxWJgAHSqlHXCFMBQKVXK5TETD4USiykg1EXMbELwOFkMLCPO2MfqYKgEZmCeIAN1eAHc0QB2KwXa4h67S9my%2BUOpW6kIu4R4LCm83nUPXS3WgjXfWoIgAWU86CBaZMgeLadDGZtQgMCgQ5Yr0LLwcbFfDErlsIJ0bYuqpLdbldJmezxFzqALtCLA8HTYs6aajmQGoEY0wqhSxGuTC8RGunrEXkwc4AtFxS7cYfOL1fqanZyH25GuwrmGxrgAxPDEMb9%2B8PqssxzfNC1xL8fwIP8HxDUt5xgmdoIXbk8GXNAGDXDctx3PcD28Y8G0QucCMI0MTAAVisMjbggRZrhPdUERAEAWCYABrTAiQyYAInQElcQyAAvDjILNYiSKIhDxLTPAqBXdDRUw6FJKkkMoD7Mx/HMfx9UNFDZVNNw41dIREzeXVSE/b9fzNJjcKPRZFjElS52uA0CDWBhrg0K8m0vC4nJU2olACqTYNczB3OITyzx8m9lMIi8aJC1sbxBIN/1nVL0uSx8xQjSUXx7Y9wLGCzu0Vd8hEwND0DK18Y1VAB5AgEHiZMcoXK0bWAidQNhEqCAsqqaos5rWp/PtRPiktA1I6bWxmJc5Iwzdt13VB90PfD5sbWCOsHcjKOo2j6LNBd0CYlj2M4vBuMNPjYUE4SoOciSMte64ZOWhTVv26C1LVDStJ0o19NxIyEyTczLIglFbK2hy/ofMK3I8rzYv9PzAR2wiguPL60JWrckdnAHlS04GDVBk1wfjEyodVIbqoEIsbJAOzMERnHEJRiK0fPNLfLvD60zxz7ZMJn7iBJwcIBl6CesnVm3DGtrJpTEXW3hvDrjAMAYVuOjz256DHJN5HZvlh9Uai64zGhSxR3HJXcVVia1Sm97NeubWj1i83Msx4Xvbxq2K15yLooF68g4DmbjpJrKOqT%2BKU69%2BD07DPKOyjCqVVVc5gANMUnXa%2BKvAyIxriV6EQUNmstSQEAn1FJ2QKnXFC%2BLzkCB1D3UTSgi04IlvOzxerewLovMBLwQy4yivwmAavC1rw3Fb6twu5nnu%2B/J0TB/8oPD%2Bxy5BXpGkbmwVRWHZY9PgZc%2BH/8y%2B9mriKmCoLxMR5Z/zlH3Ob587KnOMQYA89F5VzzB/L%2BP8shr1tPaJ4ggIbulFMQb0mA/SPQIBdEAeAFCcSVH%2BJiLtYSgPAerW8L8z5vwACpvF7ryPYAJFooSJFqJQLQgQQGgU0WBDgsi4nCAQPYcMQBkLcCIiyIidgyMEHseRoidjiI5mvA2dtHInzYcgDh2p4iQQuLwmB39BECFxJ6VAiZxGSOkZ9BRSjFH2OUaora6i65Gy0RYDgyxaCcDIrwPwHAtCkFQJwNw1hrDplWOsfCoIeCkAIJoHxyxWIgDIpIZUGgAAcZgzCJESFwMiOTslcH9P6aQfiOCSF4CwCQGgNCkCCSEsJHBeAKBAI0pJwSfGkDgLAGAiAQCrAICkXc5BKBoDZHQeIkQlScFUNk/wJ5/CSGuMAZAy4pDKjMLwXSRBiCJj0PwQQIgxDsCkDIQQigVDqB6aQXQXBSA%2BjJCkTgPBfH%2BMCck0JnBGq7jGVmVAslFnLNWeszZ1xtn2wgB4aZ9BibxMWLwbpWhlgQCQFMlIMyyAUAgFinFIBgBSDMHwOg6COkQBiD8mI4Rmj4nebwWlzBiD4kajEbQ1VukJKmT3RqDBaAMvuVgGIXhgBuDELQDp3BeBYBYkYcQwrvxcrwJ6N4Pz1zVV3JsBJIjag/NoHgGIZJWUeCwD80keA6kytIGq4gMR0iYHuPK4AhqjDJOWFQAw4CABqvpGoOkZVc4QohxCXJOfIJQagfmPP0IYYwkTLD6CNR0yAyxUApHqNKk8CIDamEsNYMwLS7WHKTPAZYdgVXOAgK4SYfgnmhHCIMCowwnmFEyAIOteh231DmEMBITzK1mIaOMVonh2h6CHfUXoLQ%2B0toHbYUdXbB2jrnQsLgFaYkbAkJ8jgASmk/NadcUFKy1kbK2ZkmFuBCAkAdiCDdKKPXLFakwLACQaKkDSZIEEypEgggqRoSQZhJD%2BAaWRfwiR9CcBqaQOp97lT%2BC4P4bJiRSn%2BAyUUv9QRmm8Fae0zpiSPV9MGRi4ZALxl4oJQiuZbBODNBYJ6f0J4mAagMFXLgiRlRcCyXs/AByjlPIjWcsN0gI03Ojfc3QpKXlMDeTK3d%2B6cO/I4P80Zu5rjAuPUs09rH41Qs49xjQ1xYWoHhfEO9ZhkWEZ6eizFpnsUIomfi%2BzhLNRGA41wRpNBaAUsoNS%2B5zL6VBsC6y9lnKHBBt5U6flgqfkirFRK2gUqg1yvjYqkJ%2BADSCLVdKkJmrkDaqDXqqpITDXGvpWazYITLXWoSXah1ShnVpaXkRr1TBfX%2BsDTaoToaLmidkOJu5ISpNxvdfmqwSayupo/RmrNnAc24LzYmiwRbcMltMtNittQq1%2BBrXaZdwQ7RrtbaQHtWQDtnZKE2%2BYJ2p09CXeOvIg7tvDpnf0a7/bJ0PdyPWxdswPvzp3SsNY26N1Qb3d8%2B5R6T3grc8vDjXGsnGevQcu9D7rNoufZgV9wwP1VJg3BzjgH/RkUSOUkEQGQOSCeUpvDtgCOot6f0oZIzAVOao7M%2BZHB6PgpYAoT0y5PQI47GMXjN7S3HNkMJvrwbBsxpACCZ5rzGUKchy0v55GgUgt5/zwXwv9JZhM2ZxFIIQRWcZ7ZlALnHOUet8MAXKQUhEiF4kIkIuCBElUKsslPm2p%2BZpXS1lwXA9so5VyyLpm%2BUCqFRlzAorxWSulQk1LCqquyuVdl9V9z8uFZtcVg1RqTX4kqxaw5tXeD1cdU1hVLWbN8G9QoP1WCA2MCDT185Eh%2BvXKjUNnQCvRsJoLZNlN5bQmZqyNKrYjFxuFuLfEUt6q01dB2y4fbj3fuNrKJ9tt6QO3ZHX923fvaAfruX6977E7nvdAEG947C6ZgTAPyu/7W/Adg4UFui5quD1Q84MenXAu%2B4%2BuJohuKOt66I6OFuWOOO76u6BOIA%2BSyopuZExS1ODSpu/oyGP%2B6ubS9OXST6n6IAkgZEv6ZS/oDS2SkghSXAuSGk4OIIauuGnAj6Nmu6uy2BTBuBUBtqbUWQRBQAA%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/independent_left_interview/implementation.hpp)
- [Source code](../../../../conceptrodon/mouldivore/independent_left_interview.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/independent_left_interview.test.hpp)
