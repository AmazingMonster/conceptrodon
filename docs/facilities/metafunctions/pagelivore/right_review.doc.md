<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::RightReview`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-right-review">To Index</a></p>

## Description

`Pagelivore::RightReview` accepts a predicate and returns a function. When invoked, the function returns true if the predicate evaluates to true for every relative-order-reversing pair of its arguments and returns false if otherwise.

<pre><code>   Predicate
-> Arg<sub>0</sub>, Arg<sub>1</sub>, Arg<sub>2</sub>, ..., Arg<sub>i</sub>, Arg<sub>i+1</sub>, ..., Arg<sub>n-1</sub>, Arg<sub>n</sub>
->   Predicate&lt;Arg<sub>1</sub>, Arg<sub>0</sub>&gt; && Predicate&lt;Arg<sub>2</sub>, Arg<sub>0</sub>&gt; && ... && Predicate&lt;Arg<sub>i</sub>, Arg<sub>0</sub>&gt; && Predicate&lt;Arg<sub>i+1</sub>, Arg<sub>0</sub>&gt; && ... && Predicate&lt;Arg<sub>n-1</sub>, Arg<sub>0</sub>&gt; && Predicate&lt;Arg<sub>n</sub>, Arg<sub>0</sub>&gt;
  && Predicate&lt;Arg<sub>2</sub>, Arg<sub>1</sub>&gt; && ... && Predicate&lt;Arg<sub>i</sub>, Arg<sub>1</sub>&gt; && Predicate&lt;Arg<sub>i+1</sub>, Arg<sub>1</sub>&gt; && ... && Predicate&lt;Arg<sub>n-1</sub>, Arg<sub>1</sub>&gt; && Predicate&lt;Arg<sub>n</sub>, Arg<sub>1</sub>&gt;
              &vellip;
  && Predicate&lt;Arg<sub>i+1</sub>, Arg<sub>i</sub>&gt; && ... && Predicate&lt;Arg<sub>n-1</sub>, Arg<sub>i</sub>&gt; && Predicate&lt;Arg<sub>n</sub>, Arg<sub>i</sub>&gt;
              &vellip;
  && Predicate&lt;Arg<sub>n</sub>, Arg<sub>n-1</sub>&gt;</code></pre>

## Type Signature

```Haskell
RightReview ::   template<auto...> class...
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
template<auto L, auto R>
struct IsNoLess
{
    static constexpr bool value
    { L >= R };
};

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

First, when given an index, we query the predicate with the pairs consisting of the variable at the index and every variable behind it.

```C++
template<typename, auto>
concept Prefix = true;

template<typename>
struct RightInspect {};

template<size_t...I>
struct RightInspect<std::index_sequence<I...>> 
{
    template<template<auto...> class Predicate, Prefix<I>..., typename OnDuty, typename...RestVariables>
    static consteval auto idyl()
    // We combine the results using a fold expression over `&&`.
    // The pack we are folding is `RestVariables...`.
    -> std::bool_constant<(...&&Predicate<RestVariables::value, OnDuty::value>::value)>;
};
```

Second, we perform the first step with every index and combine the results.

We will transform variables into types so that we can use them as parameter types in the declaration of `idyl`.

```C++
template<auto Variable>
struct Vay
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
            RightInspect<std::make_index_sequence<I>>
            // Note that each variable is kept inside `Vay`.
            ::template idyl<Predicate, Vay<Variables>...>()
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
                        ::template idyl<Predicate, Vay<Variables>...>()
                    )::value
                ));
            }(std::make_index_sequence<sizeof...(Variables) - 1>{})
        }; 
    };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwA7KSuADJ4DJgAcj4ARpjEIIHSAA6oCoRODB7evgHBaRmOAuGRMSzxicm2mPbFDEIETMQEOT5%2BQTV1WY3NBKXRcQlJ0gpNLW15nWN9A%2BWVIwCUtqhexMjsHOb%2BEcjeWADUJv5uXo60hACex9gmGgCC27v7mEcnyGPoWFQ3d48PAHoAFQgoEHACyAlQRAYlwOoKBAL%2BBEwLBSBhRxzcTDOqAOADVmngmLF6L8HmNiF4HBCoTDrg8TIELAcZo5kAc0AwxphVCliAccUQDgA3MReV5MiyE4jE0mYJkAEWOLKVKr%2Bf2BoIOymImBoqnhoKRDxRaIxCpOBEuKUYrEwpEFuPJ9y5GxSBB1eoNb0VBwIVMtVkZgIRBwASnhgAgCABJbm2mkIk33M3opiYq02u1sF2U6meyPRuMJzA0qVq/zB/6p1HpzNuDIAL0wAH0CAA6LuxvMBgsRqMx%2BMKRMELGfEAgCJYVStpQARwlDA2WNjXY7v382COjOZfwOB/9dYtWLTJ5OQtQ65unIMCgUXsw%2BFEKMduv1eFUq5u68d1ttzBsAcADyDCKmclx/tmgGYOu4aYGMMpyvQCguoerJNOynICDyYq0E6wp4Ogly0BAiz7oeAIAgcADqrxoBUESvAQCCvHqCheLQBAPl4GRGP6rEHPwtDoAcvL8ghGQCAcqAigkRwAGwaOYCkqSYSkbg86FUQcAAqgkpEwyAANYHAA7q8zSvMJ%2BD8XgD7qRo8GIUSJIodeGkUQeAC0N4TiAsSoJ4rZcjMghYhA15mKp0Xvs%2BGaWm4zkEEhbkIZOeESo6oHgdaGXipa2D5d4mDkVu6q7sqVYaqG2pFjG8EingmBmUaIIpmeCWnseXUXri15breTD3o%2B8WZrcFJ9jS9UEI1zVmRqe5aYenUNpe66pfKqHlctB75jSurQqgyhMMACq7UcS33Oh6FsngHKhSifICoFniigVXk3RWF03YeJgAKxWP9VWNngLbtuuPZbhA/nTryc6YIujArica5djc5E/b9l3VtjeMHHqBBrAwn344ekXo9FKkQKTZM3Vgez/ud1103jNNY6zv0zcOo7jgQ6CTiwTDGW2cOzguS4o24UO3DtLOc/jk6ra8REkVicX3QljqQgwR2wlim0oT%2B6PQ5j8sK4eizFRKtNk4sZW43TSow/zgvC6LDAzgjSPLolzaYKgVDrhAhsIYsBzeQcXC/HugSKmbeOVqqF1JzV5vK1i61dqH20TebvERMAOqnZK/h%2BodRAnWdBuuVtA2y9WqchvcWoIm3yaamGukIdxbWIp37eD/3zdPMuLxvKc5xXC6A8ggcABieDEGMBzYKorDoq8HfNxnfXCqEjqXhGvZUjSsYKFEqChJJi2O3tmH3dh3JPfyByvfhmXM%2BhUoHKEbyy36cMl0qqNzjhVGsd1kCtmGkoFoEAZpzRaquC%2BV8b5bknFXRKGhHRcEdGYPBNxralXAbPMEQgywCFEmvDe9A%2B4pk1NRRqCQlAHA0IKT2Uc/iQOgfeBIBAIBgDAAOYsiCFqoxQdfe8hCQCYKxLg1heCCHoJAJ/B2HBli0E4P9XgfgOBaFIKgTgbhrDWFZKsdYkozD%2BB4KQAgmh1HLGMiAf6ZgOyBDMJIAAHJ4/6GgACcLiNAKU8f4fQnBJC8BYBIDQ2DdH6MMRwXgCgQDYLsXo9RpA4CwBgIgEAqwCApDOOQSgDEUh0ASFEe0nBVCeIUt5BSkgDjAGQByKQHYzC8CfIQEgRE9D8EECIMQ7ApAyEEIoFQ6h0mkF0LgsyxAmApE4DwDRWidH2IMZwYCZxCmekDgcGpdSGlNJaVHSQ7SDgQA8GicpApthcEWLwNJWhlgQCQKUm5xSIDvPoIkYAUh8E0C4swygsR1mxAiM0S4SzeDguYMQS4wFYjaDLGkmxDE2CCFArQKFUysCxC8MAbEtBaDJO4LwLAQsjDiFxUvFFeA5Kkv0byMsZxNg2IiCiTRUyLixHmfCjwWB1kBjwFEslpA5LEECkoRUqJDDAAuEYexywqAGGAAofE81gIAWhaM4QohxAjP6fIJQah1kzP0HKlAJjLD6DwLEZJkBlioA9FkUl3lPjHEVKYSw1gzDxIlbKLADqyJdDpc4CArhJh%2BFwWEJi8xhi4MKJkAQUa9BJvqHMIYiRcF2DDQ0cYrRPDtD0LmhwPQC2ZoqAm2wBbU05orXGrNEhlgKHMRsZtYSODaNIHE3gCT9m1PqY05prSzlmAubgbptyrH3MeUq5YrEmBYESCGpxkh/Adj8UESQGhJAeKUhof6Ck/GdoiaQKJ1iOwKS4MEvxnib3/UkFwf6W6FI9vWQkpJKTbFKsyTk15eTtlFIoF81A1yfmVLYJwZoLARSBG8kwIa/EuB%2BI7FwDsTL8BEEDX02QgyDXSCNeM01UzdD4LmQs6FKyu1rKmQkrZBSzgySoIKYgsH4OIb2HKqOqH0NsMuWBspPyjhWLMA8n96SXlvMEx8kD3zhgwbg95LjRgUNcGwYClEy8QVgohfCnVsLIWIuRQ4HV6LGAECxTi/ReKCVEpJTqilcrqU2dpWWhl6zmXIFZTqjltR1k8r5ZcAVmx9HCtFTYiVUrMAyspfKwuv6VWnXVZq7VYqjX4eGYR2QxHJn6LIxaxV3qrA2p5cGp1LqcKcHdfzT1xXfX%2BoSIG9KjrQ1lvDZGoteQY2e0rQsRN6Rk3ZC69G0g6ash9eraW%2BovQJgjZLbUPNs3%2BiNqrdmmtfQ60bZaJN7NLa23DOo923tGyOCsfYwhpDRcUNoYwxOrDJARPWPE08hxpBF3LsoNRs9F7UO7sCC%2BwIgR/B7skA03BJ3P22G/a9l5/6kD5J2Z8%2BTxBIObBg0clgCgRQchFDdi0YxOkPZw7gjL%2Bqsu6ty2agIpAKOLLJUd2j8TNlAd2SxjHjSsc49FPjhKK8BPgfktsfwL3f0AZR8jmTPyVHIBSCkVseO/GtgJwQaBbGGl8DoFp5JEBQVTMM/psVBuEVIpRWZsDGLLMMGxes2zhKxAObFU5qloXyVuccB5qZXmfNir81y/RgXIUhaFbKCLvAovpBi7KqlCXJN8FVSllqWrGA6rJ0MiQ2WxkmryzoGnBgivWpsGV%2BAFX6ikoBBOerlg/V9oDURFrIbptZBcJ7LbsayhNoG0ULIW3xslFW/1trM3a3zZzYt9r%2BbZgD6myP3Io2Zg7en3tlYax233M7cdj9nBzuY%2Bx7j3nKJ%2BeTuw092dEnnkLswEu4YIauU/ZAGYVD/h/D/V8U%2BmJz/AjBPfXRzgX7UnzqkBrqBDtIA5cBSB%2BL/ZbpcDBBcr%2BBM59p/7n5vZcodI/7M6JLIH2zirMLN6SBAA)

## Links

- [source code](../../../../conceptrodon/descend/pagelivore/right_review.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/right_review.test.hpp)
