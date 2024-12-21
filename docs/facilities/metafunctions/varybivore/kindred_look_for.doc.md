<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::KindredLookFor`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-kindred-look-for">To Index</a></p>

## Description

`Varybivore::KindredLookFor` accepts a list of variables and returns a function.
When invoked by a predicate, the function returns the index of the first variable that satisfies the predicate, or `-1` if it cannot find the variable.
This function is created to exhibit the power of fold expression and to compare with `Varybivore::Find`.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> Pred
-> Preds&lt;V<sub>0</sub>&gt;::value ? 0 : (
   Preds&lt;V<sub>1</sub>&gt;::value ? 1 : (
      &vellip;
   Preds&lt;V<sub>n</sub>&gt;::value ? n : -1
   ))</code></pre>

## Type Signature

```Haskell
KindredLookFor
 :: auto...
 -> template<auto...> class...
 -> auto
```

## Structure

```C++
template<auto...>
struct KindredLookFor
{
    template<template<auto...> class>
    alias Rail
    {
        static constexpr std::make_signed_t<size_t>
        value {RESULT};
    };

    template<template<auto...> class>
    static constexpr std::make_signed_t<size_t>
    Rail_v {RESULT};
};
```

## Examples

We will look for the indices of `2` and `-1` in list `0, 1, 2, 2`.

```C++
template<auto I>
struct IsTwo
: public std::bool_constant<I == 2> {};

template<auto I>
struct IsMinusOne
: public std::bool_constant<I==-1> {};

template<template<auto...> class...Args>
using Metafunction = KindredLookFor<0, 1, 2, 2>
::Rail<Args...>;

static_assert(Metafunction<IsTwo>::value == 2);
static_assert(Metafunction<IsMinusOne>::value == -1);
```

## Implementation

The central part of the implementation is this immediately invoked lambda expression:

```C++
[]() -> std::make_signed_t<size_t>
{
    std::make_signed_t<size_t> counter {-1};
    return
    (...||(++counter, Predicate<Variables>::value)) ? 
    counter : -1;
}()
```

The function contains two main components:

1. A fold expression over `||`;
2. A counter that produces side effects.

The comma operator discards the result of counter incrementation, leaving the predicate's result to the fold expression.
The fold expression will short-circuit as soon as `true` is obtained.
Hence, the counter will stop incrementing once the right variable is found.

If no variable satisfies the predicate, then the fold expression is evaluated to `false`. In that case, `-1` is returned.

Here's the entire implementation:

```C++
template<auto...Variables>
struct KindredLookFor
{
    template<template<auto...> class Predicate>
    struct ProtoRail
    {
        static constexpr auto value
        {
            []() -> std::make_signed_t<size_t>
            {
                std::make_signed_t<size_t> counter {-1};
                return
                (...||(++counter, Predicate<Variables>::value)) ? 
                counter : -1;
            }()
        };
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKzSrgAyeAyYAHI%2BAEaYxCCS/qQADqgKhE4MHt6%2BAdKp6Y4CoeFRLLHxibaY9kUMQgRMxATZPn6B1bWZDU0EJZExcQlJCo3Nrbkdo739ZRXDAJS2qF7EyOwc5gDMYcjeWADUJltuXo60hACex9gmGgCC27v7mEcnyKPoWFQ3d48PBEwLGSBkBxzcTDOqAAdLCAGpNPBMaL0BS/B6jYheBwHADSYXQxEw6GCqFQAGsAGIkP4mADsVgeB2ZB0BwNBmHBbJBTDBJ0hRFh0JuBz2TAUCgOyiJ%2BFEfNuTJZmOxBClxFQRAASkw6H8WUcGXr9UrGo5kKKBKNMKpksQDgLUAcAG5iLycxXGg2M%2B6ez0mfxWfwAEQgCwOAFoRZ8QCAWExyZgAPrpYDhdCJgjg9IALyTma2Cp9vv19O9xeL0dj8aTKbTGazeFz9YLFq8gjiXvDXHpQeOZfLnqJBFWDCNA/1ECF9Lc04g1msaDbgLIauJeDlnJOCOISJRmDRBZjLu8mAWYeOlKOHvHzMX7btIAj3a2/YHPdDY%2BNPb7n%2B/L9p17chyXJAjyfIQlCU4tmKEpCvcwBEkCjAEAehb6l46RGAc2p0G8QZqhqqA4bQ4LwYhbCCAoUG3P%2BDx/t6fwAPQAFSsWx7EcYxTHsQcAAq%2B4oQc7FcQ8LEceJbEif8jxmDsDB7F4hzgmcdBXOi0lAbym4QUQBwAJLqcqOJ6QovEAO6oH8j7JF4KLrgclbRGStCJmgDDTII4J6Xhxz4WYIqlvRAH3Jp4EOvphkEFixkKAAsmEGEAPLhFZBw2XZ5qOc5rmWo0nknAZWy9kVXYBYadLFQxAKgcBJyhdpDrUaKBiwbC9zEMAqF/BhYTAAcsWYI0VBtg4mR4XiBIyqSFLUsQ4IaKQBxcItZgrepMbEaRHVUbCvy0dJ0xmom4pKM0EADUNI11F5pkWTcR6uq8vm%2BQcZgLD%2BGKmuux0SnEBDnYNTDDfJ10FXFCUKMlm7YA9J4%2BUVT7vS%2BHBLLQnD%2BLwfgcFopCoJwM6WNYDkrGsT2yTwpAEJoKNLOSAR0tCWwABwAGx0lsbMaMz7MAJxbPonCSLwLASBoC1YzjeMcLwCggAtVPYyjpBwLAMCICAKwEDZBDkJQaDAnQcQRKwGyqKz4Ys5IBzAMg5pSNCZi8GuRA7ugej8IIIhiOwUgyIIigqOoiukLoy1mcQTDJJwPCo%2BjmPU7jnCJWc2sHKgVAHGbLMW1bNt25IDsHBAHgG/QdrbFwCy8ArWhLBASD68khtkBQECN83IDAFIq00LQy6yxA0QJ9EYRNJc0e8CPzDEJciXRNomAOBPpD6xRBDJbQ4/B1g0ReMAEK0LQsvcLwWBxkY4jb3gRKjU6%2B4J9ai9nBsFNhICaPBxc0QRzPHhYAnUU8AixPqQO%2BxAnJKCDECQwwALhGGpksKgBhOpwjwJgMyiVkiMGXh7YQohxC%2B1wQHNQCdQ76BgSgeclh9B4GiLLSASxUDJDqMfcMnxfKmEJpYMwkswGu3vgwzoi86guAYO4TwbQ9AhDCAMcoQxloFAyAICYfgFFpCUQwWYgx4jLTsMI7oYwWgSNyLomo%2BiBA9GaFouROjbCGJUXoaYViZFzHkUsBQJN1gSFjhwDGpAJa8Clpnc2ltra2yWgXMwRdcCEBIEccmVdKYIKWAgTATAsDxFDKQOmkgtjQj5nSSQGhJBmEkCzMW/gWY8wFhwIWpARZbC4NCFmXAWZMx5kzVpgQuD%2BD5izfxCcpYyzlkkxWdc1b1w1inM4us26oFLkbE2nAmgsCdHScMTBmowKWjzaETScbOxIHgN2y1cFewIdIIhSgSHB10KtcOkcJ4%2BL8QExOHBk5azOGnDOKy1kbK2VhLguz9lFxLk3Mu8SthvWrgg5WDd5ngriLM9uZcQC/PWWKIwQKuALV7v3SgQ9g5TzHsvYlM854LyXiA1eyEN5bxxjvPeB8j7LzPjAy%2BDLr76LvsfA5qgn6AmXm/GoCcv4/0uH/DYONAHAIpmAiBmAoHn1gb1WFSCmAoLQRgrBWMKZnPwT7S5shiFBxxnc8h8DOFWGoV/ehWSmEsM4Gwgg6AOFUIsDwwJfDjkCKyXo0azgICuAcctaRpRtF6EUXUENKR1F1GsfMUxXQLH2OMaooRAb6iGITfIuxvQY1OL6C4iNldlirC8aWj%2BLzBmcHtMQVZ6zNmYr6kCvZ0INDRPwC7SFlcYVjJSWkjJlAfF1Iabs4pdJel0nZiUspkhlqvKGbYEZNclYq3VprbWyKEXN2NmwZZ9bQksAUE6c0TpW0clGE7LtRyTl%2Bzwd7CQRr/bXNNToEA/MHlRxPs8%2BOwcpYfNTunOtLAj0nrPRerSoxQU7ohdsLYiTV113hQsluetYNDFPckZIiZz080TJeggx1D2XLoPiwew9R4z1JVR2e89hHLxpYIOlCdGX7zECykBbKL5StPly2%2B99g6P2QM/IV7YP44zFWPSVACdyyt4PKtIiroEX1VWMvgyCFCoPQZg7BID9WPsIca19pCP0WuMO6mhdD4CMOYZkY%2BjFoxWusJ63G3qsB2vcWYzNojxE5HTWG2RibY2FEyDGqNmQc22P9XUSxRj/OOO87F7NxabGONTQl3RKXw1pdLR48tPtf0DP/bWlZYHT3Okg4CaDEAYndoroh5JpBUnpKGFkj%2Bo6QBmF2VsLY/h/DFJxVzLYdI2nFclpwYZ8sms5LMM0rgUKWZQp5i0sw5S6Q1K2H%2Bib0tRm1x8Y7cbgTJt7ZpqAuI6RnCSCAA%3D)

## Links

- [source code](../../../../conceptrodon/varybivore/kindred_look_for.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/kindred_look_for.test.hpp)
