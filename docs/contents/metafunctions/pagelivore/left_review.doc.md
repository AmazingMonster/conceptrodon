<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::LeftReview`

## Description

`Pagelivore::LeftReview` accepts a predicate and returns a function. When invoked, the function returns true if the predicate evaluates to true for every relative-order-preserving pair of its arguments and returns false if otherwise.

<pre><code>   Predicate
-> Arg<sub>0</sub>, Arg<sub>1</sub>, Arg<sub>2</sub>, ..., Arg<sub>i</sub>, Arg<sub>i+1</sub>, ..., Arg<sub>n-1</sub>, Arg<sub>n</sub>
->   Predicate&lt;Arg<sub>0</sub>, Arg<sub>1</sub>&gt; && Predicate&lt;Arg<sub>0</sub>, Arg<sub>2</sub>&gt; && ... && Predicate&lt;Arg<sub>0</sub>, Arg<sub>i</sub>&gt; && Predicate&lt;Arg<sub>0</sub>, Arg<sub>i+1</sub>&gt; && ... && Predicate&lt;Arg<sub>0</sub>, Arg<sub>n-1</sub>&gt; && Predicate&lt;Arg<sub>0</sub>, Arg<sub>n</sub>&gt;
  && Predicate&lt;Arg<sub>1</sub>, Arg<sub>2</sub>&gt; && ... && Predicate&lt;Arg<sub>1</sub>, Arg<sub>i</sub>&gt; && Predicate&lt;Arg<sub>1</sub>, Arg<sub>i+1</sub>&gt; && ... && Predicate&lt;Arg<sub>1</sub>, Arg<sub>n-1</sub>&gt; && Predicate&lt;Arg<sub>1</sub>, Arg<sub>n</sub>&gt;
              &vellip;
  && Predicate&lt;Arg<sub>i</sub>, Arg<sub>i+1</sub>&gt; && ... && Predicate&lt;Arg<sub>i</sub>, Arg<sub>n-1</sub>&gt; && Predicate&lt;Arg<sub>i</sub>, Arg<sub>n</sub>&gt;
              &vellip;
  && Predicate&lt;Arg<sub>n-1</sub>, Arg<sub>n</sub>&gt;</code></pre>

## Type Signature

```Haskell
LeftReview ::   template<auto...> class...
             -> auto...
             -> auto
```

## Structure

```C++
template<template<auto...> class>
struct LeftReview
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

- We will check if every relative-order-preserving pair of `0, 1, 2, 2` satisfies `IsNoGreater`.

```C++
template<auto L, auto R>
struct IsNoGreater
{
    static constexpr bool value
    { L<= R };
};

static_assert(LeftReview<IsNoGreater>::Page<0, 1, 2, 2>::value);
```

- Note that the order matters when the predicate is not commutative.

```C++
// Reverse 0 and 1
static_assert(! LeftReview<IsNoGreater>::Page<1, 0, 2, 2>::value);
```

## Implementation

For every variable in the list, we will check if it satisfies the predicate if paired with every variable behind it.
We will implement this process in two steps.

First, when given an index, we query the predicate with the pairs consisting of the variable at the index and every variable behind it.

```C++
template<typename, auto>
concept Prefix = true;

template<typename>
struct LeftInspect {};

template<size_t...I>
struct LeftInspect<std::index_sequence<I...>> 
{
    template<template<auto...> class Predicate, Prefix<I>..., typename OnDuty, typename...RestVariables>
    static consteval auto idyl()
    // We combine the results using a fold expression over `&&`.
    // The pack we are folding is `RestVariables...`.
    -> std::bool_constant<(...&&Predicate<OnDuty::value, RestVariables::value>::value)>;
};
```

Second, we perform the first step with every index and combine the results.

We will transform variables into types so that we can use them as parameter types in the declaration of `idyl`.

```C++
template<auto Variable>
struct Monotony
{ static constexpr auto value {Variable}; };
```

```C++
// Immediately invoked lambda.
[]<size_t...I>(std::index_sequence<I...>)
{
    return
    (...&&(
        decltype
        (
            LeftInspect<std::make_index_sequence<I>>
            // Note that each variable is kept inside `Monotony`.
            ::template idyl<Predicate, Monotony<Variables>...>()
        )::value
    ));
}(std::make_index_sequence<sizeof...(Variables) - 1>{})
```

Here is the entire implementation:

```C++
template<template<auto...> class Predicate>
struct LeftReview
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
                        LeftInspect<std::make_index_sequence<I>>
                        ::template idyl<Predicate, Monotony<Variables>...>()
                    )::value
                ));
            }(std::make_index_sequence<sizeof...(Variables) - 1>{})
        }; 
    };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIM1ykrgAyeAyYAHI%2BAEaYxP6BAA6oCoRODB7evhJmpMmpjgKh4VEssfEBtpj2hQxCBEzEBJk%2BfpV2mA7p9Y0ExZExcQm2DU0t2Vy5CqN9YQNlQwEAlLaoXsTI7BzmAMxhyN5YANQmO25ejrSEAJ6n2CYaAIK7%2B4eYJ2fI0%2BhYVHcPzyeAHoAFRgkFHACyAlQRAY1yO4JBQIBBEwLESBjRpzcTAuqCOADVGngmNF6P8ntNiF4HFCYXDbk8TAB2CxHaZMRzII5oBjTTCqRLEI54ohHABuYi871ZFmJxFJ5MwrIAIqd2WqNQCAaDwUdlMRMDRVIjwSinmiMViVWcCNdEoxWJhSKL8ZTHnzNokCAajSaPqqjgQabarMzgUijsFjQQAJL8x10pEWx5WzFc21ue2O5hsD3U2m%2BmNUeOJzq%2BuVanbhwFp9EZ7FnVIAL0wAH0CAA6HtxgshovR2MJhRJgg474gEBhLCqdtKACOMoYmxxcZ7Xf%2BO2wJ2ZbIBR0PwYbNpx6dPZzFqA3d15BgUCj9mHwojRrsNxrwqjXdw3rpzTpsEcADyDCqhc1z/g6gGYBuABKmDTAqSr0AoHpHhyDTcryAgClKtBuuKeDoNctAQEsB5HkCQJHAA6u8aBlHMwYIO8RoKF4tAEI%2BXipEYLHvPwtDoEcgrCohqQCEcqASnEJwAGwaOY8nKSYimbk8GHUUcAAqrFHIkTDIAA1kcADu7yNIJnj4PxeCPmpGgIUhJJkqhN7qZRh4ALS3pOIDRKgnjtnynKCDiEA3mYKnRR%2BL6ZjioHgfaU74TKrrOQQyFuYhqXSra2B5d4mAUdu2p7uqNY6pG%2BolgQCESngmBmWaYKpueCV2ienW4viN7bneTAPk%2B8VNvcVIDnSdUNU1Zk6vumlHh1Ta9UQG7ZcqaFlYth6FnShqwqgyhMMAKo7ScC2PBhGGcthoVokKIqBZ4kr5V511Vud11HiYACsVi/ZVbith23a9ncED%2BTOgrzpgS6MKuZzrj2dwUV930XbWGPY0cRoEOsDDvTjR6RSj0XKRARPE9dWAHABVPUyTDOM9ddUjmOE4EOgU4sEwxkdtDc6LsuiNuH2ZXbVdLPE1Oy3vMRpE4nFeCvi69IMId8I4htqG/ij27kczjNLEVMpGxjSylVj1NqpDXM83zAsMLOsPwyuWYg6gVAbhAOuIUsRzeUcXD/PuLKqmjUvfdWmrnTH1VR8e1o9Ve62uZt6FHrxYTAAaJ2yjsQYHUQx2ndr6fufr9xVRV5V1nqSKNymupRjpiHca1yIt03PddxGzxmHsK5vB85yXDcHrd2CRwAGJ4MQ0xHNgqisJi7zN/3cs4le0aujvcH9jSdJxgoESoAA4kambEPN1u7VhKs4fyD3Ckcz0EWlZ2J3K0Y4qcQZwQupVWs8d%2B63RVu2IaSgmgQGmpgRqzU1ynwvlfNEN9txTlLlmDQrpAhHFyPgu4psSp1ynhCIQnQBAiWXqvegndUy6hog1OISgjgaFFM7YOAJwHIEgQ%2BOIBAIBgDAEOUsM1EFI2QZfTA18iEgCwTiPBOD8GujMHIz%2BVsOArFoJwX6vA/AcC0KQVAnA3DWGsByNYGxZSDx4KQAgmgtErGMiAX6ZguwsjMJIAAHN436GgACcbiNDyW8TsfQnBJC8BYBIDQOCDFGJMRwXgCgQA4IcYYrRpA4CwBgIgEAawCCJAuOQSgjFEh0DiBEZ0nBVDePkt5eSkgjjAGQDyKQXYzC8GfIQEgxE9D8EECIMQ7ApAyEEIoFQ6hMmkF0IEMyxAmCJE4DwbRuj9GOOMZwYCFxim%2Bi9kcOpDSmktLacHSQnSjgQA8BiSpIpdhcCWLwDJWgVgQCQOUu5pSICfPoPEYAUhcg0C4iwyg0RNnRDCI0a4KzeCQuYMQa4wFojaArLC0gjE2CCFArQGFMysDRC8MAXEtBaCpO4LwLAvMjDiHxfPCseBZLkqMYKToFwth2LCGiHRMyrjREWYijwWBNkhjwDEilpBZLEECkoVU6JDDACuEYRxKwqAGGAAoQks1gK5nRYM4QohxBjP1ZMtQmy5n6AVSgcxlh9B4GiKkyAKxUA%2BnSOS7y3x/6mEsNYMwiSpWKiwI68iVQajpBcM7cYfhAghDmKUcoeh8hpAEFGxNKRk0MH6PGoYgQOhdAED0MYnhWh6DzbUQtswSiDHiLmmYqba29CzdWiQKwFBWM2C2iJHA9GkASbwJJhz6mNOaa09pFyzBXNwL0%2B5tinn2JVSsViTAsDxBDS4yQOwuwBJ2CySQGhJBeMUhoX68kAldqiaQGJOwuBdnklwUJATvH3t%2BpILgv1t3yV7ZspJKS0nzsyW8vJ7yCm7JKRQH5qBbl/OqWwTgjQWAShZN5Jgg1%2BJcACV2G9LL8BEEDQM2QwyjXSBNUoM1MzdC5AWUs2Fazu0bJmUknZRSLjSSoKKYgCGkMoYOAq4OGGsNXJuRUv5JxB5mDnS8rJwHflxG%2BTJ%2BI8HEPeR40YdDXAcHArQakiA4KZnwuhei/TiLkWoocOizFjACA4rxUYglRKSVkvRVShVtLbP0q6EyzZrLkDsvRVy6omy%2BUCuuEKrYRjRXirsVKmVmA5XUsVTnFVfB1Wau1bqiV%2BrCOjOI7IU10yjEUctcq71VhbV8uDc611uFOAeq5l6m1Fg/X9oDcRXKTrQ0MucBAVw9agjOybQsGteR021F60m2oA2E25uqJ1uodbi0TA6/mubja43NobUWrI0aRirarYNztbb1gdseV2ntfatkcHY5x5DqHc7ocw12dhEAp24dE9eiTC7SBLpXZQWjF6r0Yf3Syd9LIWQ7APZIJpgRzs/tsH%2ByTgH4DAcKXsuTkHhNVJqRweDJyWAKAlDyCU92bTTG6Thvp3NAiZcNdl8Z8hSP5Z0CAcJVHlkUto2d792zQP7LYzj5peOCeSmJ5mRe1z0d3LezsD7AHskfIl38tHUGhgE8SIkdsROAnthJwQSBHGml8DoFpsFEKoWIsM2bpFKK0USos9ihguLNl2eJWIRzErnM0rC5S9zjhPMzO875iV/meVGKC9C0LIrFSRd4NFlIsX5U0sS7LtVJ1UvNR1YwPVBGacSByxMhn5rmdFeMA1u1Dr4CVdqOSoEk4Su%2Bv9XEQNbWQ1lvDd1yNC3tuxr21N4bBR0hjZG%2BkSbOalvlvm1t0tM3lsVpH0Nzkm2S0bcrfMKbrb22jI5/RxJnAru4/x4TkXaIxcvZIG9x5zzPvfaGCGnl/3/AYZ2DsX6/jX1xKfyyUJX6GOcF/ekz766LInSwOXAUgASQO26XALIXaOw2%2B/av%2B/6rytGXS3%2BO%2BySiBTikqLC4akgQAA)

## Links

- [source code](../../../../conceptrodon/descend/pagelivore/left_review.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/left_review.test.hpp)
