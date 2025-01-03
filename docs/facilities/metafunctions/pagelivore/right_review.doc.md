<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::RightReview`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-right-review">To Index</a></p>

## Description

`Pagelivore::RightReview` accepts a predicate and returns a function. When invoked, the function returns true if the predicate evaluates to true for every relative-order-reversing pair of its arguments and returns false if otherwise.

<pre><code>   Pred
-> Arg<sub>0</sub>, Arg<sub>1</sub>, Arg<sub>2</sub>, ..., Arg<sub>i</sub>, Arg<sub>i+1</sub>, ..., Arg<sub>n-1</sub>, Arg<sub>n</sub>
->   Pred&lt;Arg<sub>1</sub>, Arg<sub>0</sub>&gt;::value && Pred&lt;Arg<sub>2</sub>, Arg<sub>0</sub>&gt;::value && ... && Pred&lt;Arg<sub>i</sub>, Arg<sub>0</sub>&gt;::value && Pred&lt;Arg<sub>i+1</sub>, Arg<sub>0</sub>&gt;::value && ... && Pred&lt;Arg<sub>n-1</sub>, Arg<sub>0</sub>&gt;::value && Pred&lt;Arg<sub>n</sub>, Arg<sub>0</sub>&gt;::value
  && Pred&lt;Arg<sub>2</sub>, Arg<sub>1</sub>&gt;::value && ... && Pred&lt;Arg<sub>i</sub>, Arg<sub>1</sub>&gt;::value && Pred&lt;Arg<sub>i+1</sub>, Arg<sub>1</sub>&gt;::value && ... && Pred&lt;Arg<sub>n-1</sub>, Arg<sub>1</sub>&gt;::value && Pred&lt;Arg<sub>n</sub>, Arg<sub>1</sub>&gt;::value
              &vellip;
  && Pred&lt;Arg<sub>i+1</sub>, Arg<sub>i</sub>&gt;::value && ... && Pred&lt;Arg<sub>n-1</sub>, Arg<sub>i</sub>&gt;::value && Pred&lt;Arg<sub>n</sub>, Arg<sub>i</sub>&gt;::value
              &vellip;
  && Pred&lt;Arg<sub>n</sub>, Arg<sub>n-1</sub>&gt;::value</code></pre>

## Type Signature

```Haskell
RightReview
 :: template<auto...> class...
 -> auto...
 -> auto
```

## Structure

```C++
template<template<auto...> class>
struct RightReview
{
    template<auto...>
    alias Page
    {
        static constexpr bool value
        {RESULT};
    };
};
```

## Example

- We will check if every relative-order-reversing pair of `0, 1, 2, 2` satisfies `IsNoLess`.

```C++
/**** IsNoLess ****/
template<auto L, auto R>
struct IsNoLess
{
    static constexpr bool value
    { L >= R };
};

/**** Test ****/
static_assert(RightReview<IsNoLess>::Page<0, 1, 2, 2>::value);
```

- Note that the order matters when the predicate is not commutative.

```C++
// Reverse 0 and 1
static_assert(! RightReview<IsNoLess>::Page<1, 0, 2, 2>::value);
```

## Implementation

For every variable in the list, we will check if it satisfies the predicate if paired with every variable behind it.
We will implement this process in two steps.

- First, when given an index, we query the predicate with the pairs consisting of the variable at the index and every variable behind it.

We will expand the constraint `Prefix<***>` alongside the arguments to pick out the element at the index.

```C++
template<typename, auto>
concept Prefix = true;
```

`RightInspect` will help us translate `std::index_sequence` into a pack of indices.

```C++
template<typename>
struct RightInspect {};

template<size_t...I>
struct RightInspect<std::index_sequence<I...>> 
{
    template
    <
        template<auto...> class Predicate,
        typename Inspector,
        typename...RestElements
    >
    static consteval auto idyl
    (
        Prefix<I> auto...,
        Inspector,
        RestElements...
    )
    -> std::bool_constant
    <(...&&
        Predicate
        <
            RestElements::value,
            Inspector::value
        >
        ::value
    )>;
};
```

- Second, we perform the first step with every index and combine the results.

We will encode value information into types by `Vay` to avoid defining the body of helper functions.

```C++
template<auto Variable>
struct Vay
{
    static constexpr auto value {Variable};
};
```

```C++
[]<size_t...I>(std::index_sequence<I...>)
{
    return
    (...&&(
        decltype
        (
            RightInspect<std::make_index_sequence<I>>
            ::template idyl<Predicate>(Vay<Variables>{}...)
        )::value
    ));
}(std::make_index_sequence<sizeof...(Variables) - 1>{})
```

Here is the entire implementation:

```C++
template<template<auto...> class Predicate>
struct RightReview
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr bool value
        {
            []<size_t...I>(std::index_sequence<I...>)
            {
                return
                (...&&(
                    decltype
                    (
                        RightInspect<std::make_index_sequence<I>>
                        ::template idyl<Predicate>(Vay<Variables>{}...)
                    )::value
                ));
            }(std::make_index_sequence<sizeof...(Variables) - 1>{})
        }; 
    };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGwArKSuADJ4DJgAcj4ARpjEIACcABykAA6oCoRODB7evgHBmdmOAuGRMSzxiam2mPZlDEIETMQE%2BT5%2BQfWNuS1tBBXRcQnJaQqt7Z2FPZODw1U14wCUtqhexMjsHAD0AFSHR8cnp/u7JhoAggdHANQAIpjprozIeJgKd8cX17dnAJOvyulxBZgAzBFkN4sHcTOC3F5HLRCABPeHYUHmSEMaFeWHwtzISboLBUDFYv7HO7KYiYGiqb5HYEETAsdIGVmEgiol7MNikO5MJGoCnXNC454EGl0hlw8EPO4EYheTDwqzXUH/fZ3ABqTFRTMOLLZHKYXIRwqIeraeCYsXoYqukxVDht6M1AHYLHd5o5kHcJZNMKp0sQhSK7gA3MSquHe/XEO0OtWeh7q%2BPp8EakFUwH5n5a6kASXZ9DYgnNuSN5yLBfrwLrhzuACU8MAEARiwwFC83YXrqyy%2Ba1QieXzWKPMdcXV43W2O12e33pSZvWusznQUOzRa3NkAF6YAD6BAAdBfi07Z/P253u73MA5CSSQCAIlhVMelABHVWSwliwvM8KXBbA4S9HM7mgpVTU5NVrhg%2BU3FBJCkJ3eDCStVBgIxQMDAUL5aUwfBRFZUhULQ6Dx0YSc7gfFcSAoxCqKVXlaLYYCW0%2BAhsHLRgCAUSjoKdJC/TwAMg1ZGNaAja08HQVFaGEu4IBUpDiIZQC8Ow4DmKuVj6OXJ8iDIdSYO4yY%2BLZASFFwljoJWFSAFo8NfEBYlQTxjykwwCBUwkIFwsx/HMUKHLQ4jSJHcyRIRWK0Ms3j%2BMEBQ3xk1V9MMpCGJMkh0tjBCDNY0TWIK7wiqQpywPVLE01qzU82bBdO24qMPgAdxrE1hz3DCYstEVcLA/CmEImUSIkgbp2dZU52lFqCDazq6qgmD%2Br3XSL0TZN6CEmqIpvaVaVQIhlCYYBKpgtc1qo8TJIEYNQ3DTzPGjQqEpuhKkJMQIrECLN9zwI9T2Aq8wIgdyPxDb9MD/N5RzcICLwxJyIsMr70ey6C6QITYGG%2B1igpRkKwrUrHsaQrBoRownsfJ4rKcpxbcufBF3JYJgAGsT2hr9f3/bZtJqg7GaZ7K3w2zA7gUpTCSiqaLWwCB9XRBEdvtPaKXXNNgLRsXxZglZytVOm0JWarbuyjdIYIdA305nnjz52H4YA9ngcwVAqGAlXbU1z4VjuZy7i4bWrDTfWMfq7MILFjcGtzMWpawobtv9lN9pmpCvGyIwaQu6X4UVE6zsLwkNcz4bMWzOrN0pG56wLYFtTuAAxPBiEmO5sFUVgOWlgdG6bwFGyanViwUKJUFCT4viHlPButUJBWw1trzmt1J%2Bn2fCNWlT7sDR7WWeu5XtkjKrpE707lCeUa8VFtM0ThPa8a4fmwAFR47rQXu48xpKHaBARay1MAdUAlPGec8MRvnOpdQkGhBRcEFGYVBsCQCX0tg3bUI9Tgt2pEIJ8Ah0A9z7mWQezImx4PwTg3YrZMBRgSEoO4GghQMFIWHGcrR/QAMIgkAgEAwBgFbHeJajCVoIm3tAveYE4HlwRCg1hqD0FyMwYVS2HA1i0E4IEXgfgOBaFIKgTgKFLDWF9BsLYRcIQ8FIAQTQWi1hcxAIESQZ4NApDMGYJISQuCBE8SkLgnpPTSB0RwSQvAWASA0EggxRiTEcF4GlJBDjDFaNIHAWAMBEAgA2AQdISJyCUDQOyOgCQoiTk4KoFI/hnL%2BEkHcYAyAAxSDPGYXgk1TIKT0PwQQIgxDsCkDIQQigVDqHSaQXQKCOrECYOkTgPBtG6P0Y44xnAADySJCnSm9ncGpdSGlNJaaHdxZhVIeDKfQcM2IuArF4GkrQawIBIFKekcpZAKAQDeR8kAwApBoJoLQVkXdKCxDWbECIbRUSLN4JC5gxBUQbNiNoEysLSClIrAQDZDBaAwsmVgWIXhgBuDELQNK3BeBYE5kYcQBLO4mTwEwilRiQxPiRDsOxERWThKMSiWIczEUeCwGs5UeBomUtIEw4gnklBPBpcAFERhHFrCoAYYAChdSdQ2XydFfThCiHEMM/VYy1BrOmfoQwxhrDWH0HgWIaVIBrFQOkJoFLnIkmLqYcxlgzAJOlUmLAjqIBrDsIy5wEBXAzD8CgsIEQRjVDGCgkoOQBDRr0CmpoixRiJBQWGhw/QpgdE8F0PQ%2BamgDHaNmxNubbBFvTXmot1blh3PWJsbYEhlkcD0aQeJvBEn7NqfUxpzTWlnNUrgQgJA4S2PufYlVawECYCYFgRIIbSAuMkOCM8SRwShI0JIMwkh/CxMCP4JI%2BhOCRNINE8EXAzz%2BC4P4FIqQn1uP8bu/wva1mJOSSAVJKrMk5JeXk7ZRSvk/OuZUtgnA2gsCjJ6ZyTBRr5y4EkM897WX4G6fbFB%2BqBlGukCapQZrJm6DQbM%2BZsKu09r7esjgWyClIjuHsg5w6UPAFDuhzDFzUBXISDO8EZg52PIySByDCRinfL4%2B865KADBGDQ1wJBQKQVpQgOCyZ8LoXou04i5FqKHDosxQJHFeK1mEuJaS2g5L0XUqtXSox%2BA6QFuZWstlyAOXou5Q0NZ/LBWomFTsIxYqJV2OlbKzA8qHMRFAOk1V6rNXat1ZK/DhqhlEdkKaiZRjyOWuVd6qwlg7UOvgM611uR3WeoVIV6wfr%2B0BoUp8MrvRw1%2BEjRwhtIQOHNqTRkLIqa8glsKMmgbWb41LD6%2BWwtgwuvTYEJWoYE2c1lvrcNmNdaFjLZrZ2tt1jdvhNoz%2Bzgg7DmNOhFarjGGPETuw9O25ImF2kCXSusY67wnXtvehg9npAhJBCeCQ9x7JAoLo7%2B2w/753xaA/AED%2BSdlSYk8QaDOw4NHJYAoKMAYoxobPPBSYnS7uBt6bIAjGWRnyBIzlnQIBwSkEowsylNHVmTMSYxnZLGqD7PR5j7HuP8fSggJc2TAnsTgke9D8TMmPmI%2Bl3JrH6R0jHhx0kY8AvjyqAaXwOgamwUQqhYi3TBukUorRZKkzggzP4qc5gIlJKyUUrsfZ2lwWqUMtc81yZHmvOSp87y3g/noVBdFUmMLvAItZCi2yGLyrodqoukl8BOrGB6tJ%2BliQmXRlU/NbT/L1qfU2H5cG8rbrOC7FfLV31/qEiBua061rBaI1RvW3oONlQVujdKLkLrmbci9drfN5oa2CgbcH4t/vq3Zst8bVt9vO3W0KCsR21th2WcJJO5rxpGOsfRn5yObuEBJ2mUE3ch5T2XursoF2z7IAfFnnBOCQIASQexIf56Z937WecD/QB%2BLziQCSCBA7rBKeixIpCSB%2BJcBeIhSXocDghr79rf5Q5PJdodKf7r5JLIFOJSrMK5AAFAA%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/right_review/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/pagelivore/right_review.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/right_review.test.hpp)
