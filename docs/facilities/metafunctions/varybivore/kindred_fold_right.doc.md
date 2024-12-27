<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::KindredFoldRight`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-kindred-fold-right">To Index</a></p>

## Description

`Varybivore::KindredFoldRight` accepts a list of variables.
It produces a function that accepts an initiator and whose first layer accepts an operation.
The function right-folds the list using the operation and the initiator.

<pre><code>   Oper
-> Init
-> Arg<sub>0</sub>, Arg<sub>1</sub>..., Arg<sub>n</sub>
-> Oper&lt;Arg<sub>0</sub>,
        &vellip;
   Oper&lt;Arg<sub>n-1</sub>,
   Oper&lt;Arg<sub>n</sub>,
       Init
   &gt;::value
   &gt;::value
        &vellip;
   &gt;::value</code></pre>

## Type Signature

```Haskell
KindredFoldRight
 :: auto...
 -> auto...
 -> template<auto...> class...
 -> auto
```

## Structure

```C++
template<auto...>
struct KindredFoldRight
{
    template<auto...>
    alias Page
    {
        template<template<auto...> class...>
        alias Rail
        {
            static constexpr auto value
            {RESULT};
        };
        
        template<template<auto...> class...>
        static constexpr auto Rail_v
        {RESULT};
    };
};
```

## Examples

We will right-fold 1, 3, 4 and 3 using a subtraction.
The process can be described as follows:

```C++
   1-(3-(4-3))
-> 1-(3-1)
-> 1-2
-> -1
```

```C++
/**** Subtract ****/
template<auto A, auto B>
struct Subtract
{
    static constexpr auto value
    { A - B };
};

/**** Metafunction ****/
template<auto...Args>
using Metafunction 
= KindredFoldRight<1, 3, 4>::Page<Args...>;

/**** Test ****/
static_assert(Metafunction<3>::Rail<Subtract>::value == -1);
```

## Implementation

We will implement `KindredFoldRight` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  1. Right-fold several parameters;
  2. Use the result as the initiator and perform recursion to fold the rest.

Here's a simplified version of it:

```C++
template<auto...Variables>
struct KindredFoldRight {};

// Base Case:

// Fold once.
template<auto Variable>
struct KindredFoldRight<Variable>
{
    template<auto Initiator>
    struct ProtoPage
    {
        template<template<auto...> class Operation>
        struct ProtoRail
        {
            static constexpr auto value
            { Operation<Variable, Initiator>::value };
        };

        template<template<auto...> class...Agreements>
        using Rail = ProtoRail<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

// Fold twice.
template<auto First, auto Second>
struct KindredFoldRight<First, Second>
{
    template<auto Initiator>
    struct ProtoPage
    {
        template<template<auto...> class Operation>
        struct ProtoRail
        {
            static constexpr auto value 
            { 
                Operation<First,
                Operation<Second,
                    Initiator
                >::value
                >::value
            };
        };

        template<template<auto...> class...Agreements>
        using Rail = ProtoRail<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

// Recursive Case:

// Write out the last two folds, handle the first two parameters,
// and recurse using the rest to obtain the initiator.
template<auto First, auto Second, auto...Others>
struct KindredFoldRight<First, Second, Others...>
{
    template<auto Initiator>
    struct ProtoPage
    {
        template<template<auto...> class Operation>
        struct ProtoRail
        {
            static constexpr auto value
            {
                Operation<First,
                Operation<Second,
                    KindredFoldRight<Others...>
                    ::template Page<Initiator>
                    ::template Rail<Operation>
                    ::value
                >::value
                >::value
            };
        };

        template<template<auto...> class...Agreements>
        using Rail = ProtoRail<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGxcpK4AMngMmAByPgBGmMQSXGakAA6oCoRODB7evgFBaRmOAmER0SxxCVxJtpj2xQxCBEzEBDk%2BfoG19VlNLQSlUbHxickKza3teV3j/YPllaMAlLaoXsTI7BwA9ABU%2BweHR8cH2yYaAIJ7BwDUAJIsKfRsgkwNN4dnl9cnvydfF3OFwImEeBhBJgAzG4mF4iAA6REANRaeCYMXoCih2CB42IXgcNwA0uF0MRMOgAGKedAAJTwwAQBBuJgA7FZWQARKFWS5A7bbG4WJhKG4wpQgIH8wXU2joG4CTbwoEgsFvTBQmFw1A3FHENEYjWQnGXPEE5kkhhkimyukMpmavUG%2BjYqXsoE3T03VVPdWa2FEe4MTJvEiuy5em5mwnKYioIjKJjADURr1s3kXSORn3go1uHN%2B6EB1CI5XGm7IAwKBQ3ADyKXibyy4czWc90eZsfjqFpTDoHrbLPdqcHXtmjmQFYE40wqhSxBuxZuADcxF4U63R5703WG8QmwJHaj0fRSEGQ0RiNiQCBV95MEPuZCM6O2U%2BMwO2wWIdDv3ni6W2IVlWCilhcwDkqCjAEFixqflmXgZEYNy9nQLKQpyNxdkQqG0Jq4GQS8MGAXBz7wW%2BPJSiO3qgr6P5agiiIEZgUGCLBJqbjciHhMAWFJg%2BUKYdhqCJsm%2BEQSxRGgYirpkXyXKUXy3wyjS3oAO54EqKq0bm/rajclJ4MQ4xnkuQiYGgVoth2xKkuSVI0vSjIEJqhnGQQZ7mZZ6Atum8F/npgZ3MGjihlecHUTZwmiRukZ%2BdR2Y6YW%2BZJfRAEyeWlYijW9aNg0LajlFcY4X2eEJWmw6cYVzQTlODAznOC5Lne64suVbY7vBW5erl%2B75dCbkmV13W7nlzbQl5AjoKQw0jV6wUXmG7Vbtet5rrFc1psaN4tRt3UUXJVUVe%2BVFHZ6AW/ql/7aiR2DAdlYESaxMEFYO3HIbh6FCcVPaleJhHQdJZY4odcUKYd/lXYFJZMU9UmvZ6728TFX1YT9MX/ZJgO3YpgLgx%2BykoRZ6wZMuD7iuwp0CjcADq%2BoggqcLeggD5VsyBBqTq/BygoZ4IIY6D0MzD40O56k6ikLSsJgILGTNhMCzc5LICTD5I8LSuYOM3o6qgMTNOEGvhItxDKpcF0MTqg0eYu%2BmTVapk3YitYECzxnWQQ%2BKEpa1oOXKTkOgNRkmTc9vTXWrvxEDvmVYlappfpC2hZeCNRp75po92GPUfFZ00fHeYW%2BlwP3dWo19eNHHVV7nY/bhs1Di%2BI3jppdUNfOtuBrtDdg03m3lweDCucHHk94OvWD5qYfy3nc0%2B/ZtoBy50Iu270cRbPI03n%2BfFidCSdoinG/92229XShf0r3uk/HyfkY7etY8ddta33k/Ward3y1gydy0HQTecLZFydiXLK1ZHoAzYqnSM6tPqCUziVfs0JmLPXXiDPuj5caQwLtDCBWMoG30RkhZG/FUbRX4pjVBOMIb4ypn8X4AIfi7BuNgVQrAngPk%2BPyeh/w6G3CEF4fW%2B5CRcPNlDIs%2BkLiO0DFYDeNkBFCKYA4N0GCW6Tksu3Jq%2Bkv6cR3JmAAtEKTBNDf6Am%2BIcG4ABZGWTAqBeAYA4LIHxTjaRwRIxi8ILjEGAOxIE6trHNDsQ494UoMK2StAvRy9pl5uCCDcSEZ5JCrQxsg7xaCsHmNuAAFS1syURFw1EAH1srxAIBAAJtj7GOMPNCSEq164TUEZ7JRy9sAP3vF9eB%2BiuBLB5BwFYtBOAAFZeB%2BA4FoUgqBOBuGsNYKMawNgCTMJCHgpACCaH6SsAA1iAIZkh4QaAABxmDMAATlOVwIZRzDlcFZKyaQgyOCSF4CwCQGgNCkDGRMqZHBeAKBAB89Z4z%2BmkDgLAGAiAQBrAICkOE5BKBoEeHQeIkRpacFUIc/w%2Bj/CSBuMAZAk4pDwjMLwCkhASB4HQHofgggRBiHYFIGQghFAqHUMC0gugghqX3CkTgPABnDNGRsyZnBaxwlhcyVAVAbgYqxTivFBKbhErMDcCAHgkX0AXOYFZSxeBAq0CsCASBEUpGRWQCgEATVmpAMAKQyQaC0Flv8iAMRhUxHCC0AAnny3g7rmDEE9bWGI2gLJAtWYioitYGC0G9eyrAMQvDABhLQWg/zuC8CwCwQwwBxBxqMqGvAZM00TNnMTEEPryCCDqMK2geAYj7gDR4LAwrPZ4Feem0gZNiAxHSJgTkoJs21qMBslYVADA%2BKRHgTAalcpjNWTS4QohxCMoXSytQwrOX6GzSgWZlh9B1v%2BZAFYqAUgNDTfo8YPkMKmEsNYMw3yu36iwIeiAKw7AFucBAVwUw/BBFCOEIYFQRgFHSJkAQP69CFDAwweYwwqjdA/Y0CYbRPAdD0O%2B6pSG5gAYWMB2wyGINBFmK0WDQGqhvoWZsCQAqOAjM%2BcKn5MrMXYtxfiwl%2ByVUQFwOSrVyyel6pHSsFmTAsAJFfaQHZkhITwlOZCe5GhJBmEkP4d5Qz/CnP0JwZ5pBXkrPhIEfwhzTk3P8Hsy5sn/D0fZT8v5AK1kjtBRCo1ULxVwotVazVqK2CcBaCwZcrJ9FMHushLgpz4RcAOaS/Al5KXUtkHS5d0hV1KHXey3QyRuVMF5emmjdGvm8B%2BWKmFTMpVMblbirKIWwsRY0Kq9VprNUsmWWYXV9ngWGuNagDV8R4WWq6w1kYlXbUXI%2BQ6p1lBXXsr9V6it02A1BpDQ4CtEboJRpjcK%2BNibk2porZmwdWwJn4GVo4ItwrS0q3LR28IIJHkTNrfWr1TaDt6v1O21ZXae1KH7VmowQ7QDtb4OOhQk7p2zorQuhLDKkuyDXWyiZ6Wt3DpvVYPd92X3HtPVkc9l7BLI7vQ%2B%2BIT6tbwDfXURDLgrSEeCFaUjiwQNFCyFTqDDRad4Yww0PokxUN5CI2TzDnOBg4bg%2Bhgj3Pf34ew2UYXPTVjrCozLx5eWGOcDKyx4LvFQvhYOaq7jl4ms6oE%2B1oTmARMjHE487TumwsKdZEM05dzISKeU5III%2BWRW/NsHZ/VIKwWQuhRK3rHmUVoo4L5%2BVLAFDLknMuTXuZxhRZ47FoIEOl1Q6ZfIFLcOdAgASZl7L/LNO0aFdZ0VrnJXStUOHyP0fY/qm1mq/rZr9eQla97jrKBG%2BasD53kYUeUgpEKTH05hS48EEKZXpLdBxsurdR6gNs25%2BBuDaG5bXXI3RtjYdzACak1iB2x2vbv3nukCOwW077Lztwi2Ks671b2X3YbZ6p7LbXsVo%2B7277g6eIObHUmYHU6Z0Gw51eAU96UJBodmVM8N0c9EdjBd0bA0cSdJlMdpxOBthL0d1b1LB70CtH1KVicj0ENMMKd3Axc9B/0pcyNINQMGgmcaCshWd4N2dehRdchxdmCBABdGCRd%2BgqdiNBdKC6cKM5cGVcti9vkVcJ8bgI8o8Vxa8QR69dcSB9d%2BM2sDVjdTcxMaNLcQAzl4RIRIQhkrkXd3kDDWRDMrMJCPd/lAVBMJMQBJAhkZNblWR3lDlJALkuBjkzBLNHlIRxCCtOBDd1DC8SVLDAiPc28Vgu0MhnBJAgA%3D)$Done$

## Links

- [source code](../../../../conceptrodon/varybivore/kindred_fold_right.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/kindred_fold_right.test.hpp)
