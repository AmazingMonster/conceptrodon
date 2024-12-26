<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::LeftInterview`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-left-interview">To Index</a></p>

## Description

`Pagelivore::LeftInterview` accepts a list of predicates.
Its first layer accepts a list of variables and returns a function.
When invoked, the function first binds the variables to the front of every predicate;
then, it returns the index of the first argument that satisfies all newly formed predicates, or `-1` if it cannot find the argument.

<pre><code>   Preds...
-> Vs...
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> (...&&Preds&lt;Vs..., Arg<sub>0</sub>&gt;::value) ? 0 : (
   (...&&Preds&lt;Vs..., Arg<sub>1</sub>&gt;::value) ? 1 : (
            &vellip;
   (...&&Preds&lt;Vs..., Arg<sub>n</sub>&gt;::value) ? n : -1
   ))</code></pre>

## Type Signature

```Haskell
LeftInterview
 :: template<auto...> class...
 -> auto...
 -> auto...
 -> auto
```

## Structure

```C++
template<template<auto...> class...>
struct LeftInterview
{
    template<auto...>
    alias Page
    {
        template<auto...>
        alias Page = RESULT;

        template<auto...>
        static constexpr std::make_signed_t<size_t>
        Page_v {RESULT};
    };  
};
```

## Examples

We will find the indices of `2` and `-1` in list `0, 1, 2, 2`.

```C++
/**** Equal ****/
template<auto I, auto J>
struct Equal
{
    static constexpr bool value
    {I == J};
};

/**** Metafunction ****/
template<auto...Args>
using Metafunction = LeftInterview<Equal>
::Page<Args...>;

/**** Tests ****/
static_assert
(Metafunction<2>::Page<0, 1, 2, 2>::value == 2);
static_assert
(Metafunction<-1>::Page<0, 1, 2, 2>::value == -1);
```

## Implementation

`Pagelivore::LeftInterview` is implemented based on `Varybivore::SensibleLeftInterview`. It changes the invocation order of the latter.

```C++
template<template<auto...> class...Predicates>
struct LeftInterview
{
    template<auto...Interviewers>
    struct ProtoPage
    {
        template<auto...Variables>
        using Page = Varybivore::SensibleLeftInterview<Variables...>
        ::template ProtoRail<Predicates...>
        ::template ProtoPage<Interviewers...>;
    };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKxcpK4AMngMmAByPgBGmMQS/makAA6oCoRODB7evgFBaRmOAmER0SxxCVxJtpj2xQxCBEzEBDk%2BfoG19VlNLQSlUbHxickKza3teV3j/YPllaMAlLaoXsTI7BwA9ABU%2BweHR8e72yYaAIJ7BwDUACKYKa6MyHiYCjeHZ5fXJ39H3wu5yBZgAzOFkN4sDcTKC3AQAJ5PAD6BGITEIClh2GB5nBDEhXmhsLcyHG6CwVGxuJ%2BhxuADUWgiYngAG4kdggISMDIxeghTBUAgASUE8VZbwA7p8DoDmGwFCkmJsGUyWeziJgYQB2KyXYEETAsFIGQ0kpheIgAOht1Mu42IXgcN25DF5/MFIrFxAlmEluN1wJuwZuhuNpswJLDJqYZrhFutttB2BukKYCgUNqtyk1%2BFEhqxyaDIYdToINxzqCIACUMbRi8GTIHLiHW6GjTG424E6gs3aLm2S2iyxXiFXUMomMBIy3BzqLDdZo5kKmBONMKoUsQbj2bqyxF4tU2LABaLhNu6whcXq80gdz6MR82W3s2i7ATVGxgEQs42eDrwMiMCspyPUE7lHcdJ2nEl30/NhBEzJMcVBPV70bbVL1Qu9W0fWNIzhPCux7Ptk1TAwMyzHNMDzfDfwbG5APCYAblrOgYXAyCazrElqNogtSJQtCb2w/VLiIgjuxfG4ADE8GIcZ%2B1LZ1XXdTABSFUVDR9KUSTkhSCH7Y8GIkqMOyfeMX0E8j0yQ7NczwfN3n7VtlPLStuLoBjjP/NtTMsxMrQ04Q8CwejfNc4dnQ8idQIY1tjxDeK5yXRzVzdQ1N23Xd928I8IrnHz0LnQcTH8Kx/DuCAlhuE9sUXAh0BAEAWCYABrTBkQyYAInQVESQyAAvTrDKLAqSowtCJumm48CodL1yymFxpm4MoD7MwADZzE2vjHLoklgqEUL3izUhZPkxTk2a3LDyWJZktWyabk1Ah1gYG4NCvHVLzE4qnpDOolEep7Ete97avPVCfpBkqL2q2Gksw28VpE4SVv8qTArgzAv0Qly5yY4DoLAiCYpJ2CP1xhCf0ElHirRnCQ0xzGSOQmzKLfKm8Z/AngyJli2NoDiybHTz6zhHGebs6lRKBZG5YNcz8OfIgLoM87d25NAGHQTWrJtAB5AgEHicKLjcl0eTwPl1M9LTxV0uF9PGc7tYEPWbmN02FLp/Vm2KlnleIg2rXqtNOfsmj9oLPmGsdaKxdQIXvIDkrWdDo6TvNkrLfJuLUd1JKVsi2M0p1xatx3aTbvy/7CrTgGYXKsqqpquqyPJZrWo6rq8B6mj%2BrhIaRrj1aiqbts5oWzKq8R6b1ttLadr2pzCzcLOwrO9WruwG6D0we754msHMDe4gPq%2B6Gbz%2ByfWyBrVp4r2ft2PkrF7D5ettXg64U306bRu0wDrdA2J955SPiXGap9z4fShteZGt877BgfrNeaz8NxbjfnOCA2DpqqRth6TS3pfT%2BjhN7M2ft67IOahJViPE4Q/wEshPBE1aHBy1BTP%2BnpjpbxYVAgG4DDw3DAGAWEEEzysNbA9ARJ8i5SLnODC%2BNwzAwksFbN0hC7bEO0qQkkFDfb8OoXfdh4Z8L0K8owhya8qHIMHKYzsnC4rcKFLwgBYcxrGMnkIgi15ZFw0QUCfxc4H4KOekoj6kjr6BMnvDGRXikZYSmg3JJTNBwZ2xtzGmOdCZARYiTEWXFYowUllk78MsixywSgrdGgcOFmTMSHQK4cKJ2SltkuOAsLHC3EUUlOpT4LlLporGpd4b5BKuP8KZAJgS/F2DcYU4YeZlwEDKfYgI5nTP%2BICJWjTJIZNfB4lMEc7JMOcp4y2wUHY6T9AGZJwYDlZmuaQs2cc85Jwpr5CeD56kBUOYyYgeAmC2xyQBPJIFpyFIBcyNkHJmoENtlckhTs3AAqBSC2xc4HERj6QwtwZyKl/mMdi8x%2BcSluGeVKShLCqmJPpiZX5WN/ktHRfQUFjFwUFN6WSySaLgVsuGcJUZf1NlbI2XSbAqhWAmi1F8WZWyZkiolQARy8GINZpxdmONVqgBZ%2Bs1YACklJRXLNgVVYg7kMVSiuDBS0YioE8HuA%2BqcLDChFr0o1wr5apKVbcAAsmfJgVAvAEgaBqwEjy3zEGAObLpAbmjBtDVkQpSLdEorNWqiWRLmpcLcBcaNhL6W0luAAFXeD%2BcNwJrXIlsvEQylwIDxqDSGhwWQSRmDASAXNGhzpBBUedDt10QC13dZxMwD05bVtra0YEjbA2JtbQIEkUS95ducW4HtNw%2B3JBUZ2kd4jelngnRYDgKxaCcH8LwPwHAtCkFQJwNw1hrCLjWBsI8YIeCkAIJoU9Kw2oBEkFaDQAAOMwZgACc4HqggeA1wbU2ppDno4JIXgLAJAaB7de2996OC8AUCAHt36b2ntIHAWAMBEAgDWAQFIlpyCUDQMaOg8RIisC2KoYDm0TybUkDcYAyAVxSCtGYXg0ciCAqakEfgggRBiHYFIGQghFAqHUMR0guggiSnRCkTgPAz0XqvT%2Bu9nBDaWlo%2BWVA80ONcZ43xgTW7AOqIgB4Jj9BX4fqWLwIjWgVgQCQIxlIzGyAUAgAFoLIBgBSGSDQWg2l8MQBiEZlkzBiAIl07wZLTJDYxG0MAojn7GM00NgwWgaW1NYBiF4YA3ZaC0Hw9wXgWBWpGHEOV%2BSeW2TvCMxuYBlotifvCIaJDt7aA23RKljwWAjNojwGhhrpBWTxHtUoB4zXgCjaMD%2BlYVADAxvpFKQ2Txr2fuk8IUQ4gFOneU2oIzGn9CGGME%2Byw%2Bgbb4cgCsVAKQGj1ZPOScRphLDWDMNhxbxAJNdfe90DrzgICuCmH4IIoRwhDAqCMAo6RMgCHh3oQomOGDzGGFUKHi7GgTDaJ4Doeg7DQ9J3MZHCw0e2DJ9joIsxWgE9R1UFYChX2bAkPpjgl7SBYd4Dhm41nuO8f44JxzNwIC4EICQNRoIuCea/VtlYpsmBYASNVUg/7JCgitOB0ECGNCSDMJITaGH/CbXA/oTgKHSBoZV1aTaXBNrAfA7Bza/hJDVBN5tYXRmcN4YI%2Br4jvmKN%2Bao2ZujIWwtudY2wTgLQWCsm1CeJgNlgJcHA1aLgQHRP4HE6FPQp3ZMXekFdpQN21O6GSFppgOmGsC6FyL4zHBTM0ctDcSz4vOOS5zyxPPBegNy5c4Ftzyvx1ea26R/zqBXPxHo6FpfU%2BRhpiMHnrgPaYtxcoIltTmXUvpdICfhE2XcsODP4V78xXStGYq1VmrdWz9NYe6129%2BBNStsW/V29HrZAPrM/QbOoIzUbGIcbBESbLYW9GbObT9UHZbTAVbT/ZiefHbKcBQfbP0Q7RgM/Cvc7eTavWQa7VTW9Bve7TbAHKwZ7SAt7PXT7b7TgX7Rqf7J7CwYHUXUHcHRg7nOoGnFwXWFnYIXWDnRYdHIoLIUQ3HBoCQxnanEnPoSYCnPIVnQQ5QsnBQonNncnXIBHJnOnMoQnfnVYdYPnVXB3QXQzNTMXCXWzLfEffPQvDQOXBXcTZXVXOfSPTXTAbXEYPXJDJ3F3fPc3bUfwcDeDUEC3K3f3YPOwzgMPQjefMjSjajczVfRPFjNjVPYgFgWzFgBQVkFcVkUfCMcYYvRXCTcvWQSvEgxTeQWvCgnQEAUEUgJvFvPTaw9vEPEzOPCzKzQo4o0o8ouicsZzdfILZXUENXbzEjGPbI4LBjKYtzYdZAFIFIZEMo8DZECoggZEVQHjPgOgA/BLJLcIJkM/C/K/PLW/JfIrErMrb/TASrarMQN/ebD/FrOAxrdrP/LrNTIAkA%2BbMA4bXgSA6A2A6bQFRA3gZA9IVAo0dAzbSPPgXbHAg7I7Qguo4giQUgpTZo27No6gx7QHeg17eAD7L7LIerbYLuWgoHEHeIPgqk4nBoYQ9wNQwwpHEwznHHDHBoWQwUrIHQqnTQhoFQ/QynDQnoAQKUsU1nZnbkqnbQ%2BnUwqwnnCw%2BTNvWw7DTgcXYYkovcMYgsCYjwpXPEbwiPHzPwgI3XAXEIkACDK0UEUEfwfwc3XfDQN07UT3BI/U3DWwcPeY%2B6fXEASQfwY3ODbUDDYDSQKDLgUDLaaw0EPU0XJIm039awkTAMjMoM0MlYUHDIZwSQIAA%3D%3D)$Done$

## Links

- [source code](../../../../conceptrodon/pagelivore/left_interview.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/left_interview.test.hpp)
