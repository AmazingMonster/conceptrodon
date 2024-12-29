<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::LeftReview`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-left-review">To Index</a></p>

## Description

`Pagelivore::LeftReview` accepts a predicate and returns a function. When invoked, the function returns true if the predicate evaluates to true for every relative-order-preserving pair of its arguments and returns false if otherwise.

<pre><code>   Pred
-> Arg<sub>0</sub>, Arg<sub>1</sub>, Arg<sub>2</sub>, ..., Arg<sub>i</sub>, Arg<sub>i+1</sub>, ..., Arg<sub>n-1</sub>, Arg<sub>n</sub>
->   Pred&lt;Arg<sub>0</sub>, Arg<sub>1</sub>&gt;::value && Pred&lt;Arg<sub>0</sub>, Arg<sub>2</sub>&gt;::value && ... && Pred&lt;Arg<sub>0</sub>, Arg<sub>i</sub>&gt;::value && Pred&lt;Arg<sub>0</sub>, Arg<sub>i+1</sub>&gt;::value && ... && Pred&lt;Arg<sub>0</sub>, Arg<sub>n-1</sub>&gt;::value && Pred&lt;Arg<sub>0</sub>, Arg<sub>n</sub>&gt;::value
  && Pred&lt;Arg<sub>1</sub>, Arg<sub>2</sub>&gt;::value && ... && Pred&lt;Arg<sub>1</sub>, Arg<sub>i</sub>&gt;::value && Pred&lt;Arg<sub>1</sub>, Arg<sub>i+1</sub>&gt;::value && ... && Pred&lt;Arg<sub>1</sub>, Arg<sub>n-1</sub>&gt;::value && Pred&lt;Arg<sub>1</sub>, Arg<sub>n</sub>&gt;::value
              &vellip;
  && Pred&lt;Arg<sub>i</sub>, Arg<sub>i+1</sub>&gt;::value && ... && Pred&lt;Arg<sub>i</sub>, Arg<sub>n-1</sub>&gt;::value && Pred&lt;Arg<sub>i</sub>, Arg<sub>n</sub>&gt;::value
              &vellip;
  && Pred&lt;Arg<sub>n-1</sub>, Arg<sub>n</sub>&gt;::value</code></pre>

## Type Signature

```Haskell
LeftReview
 :: template<auto...> class...
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
/**** IsNoGreater ****/
template<auto L, auto R>
struct IsNoGreater
{
    static constexpr bool value
    { L<= R };
};

/**** Test ****/
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
            LeftInspect<std::make_index_sequence<I>>
            // Note that each variable is kept inside `Vay`.
            ::template idyl<Predicate, Vay<Variables>...>()
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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGwA7KSuADJ4DJgAcj4ARpjEIAAcGqQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCcmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimGmujMh4mAq3R%2BdXN6f/xx%2BlwuwLMAGYIshvFhbiYwW4vI5aIQAJ5w7Ag8wQhhQrwwuFuZATdBYKjozG/I63ZTETA0VRfQ5AgiYFhpAwsgkEFHPZhsUi3JiI1Dkq5oHFPAjU2n02Fg%2B63AjELyYOFWK4gv57W4ANSYKMZB2ZrPZTE58KFRF1rTwTFi9FFlwmyoc1rRGsCFluc0cyFu4ommFUaWIguFtwAbmIVbDPXriLb7arAvc1bHU2D1cDKQDc99NVSAJJs%2BhsQRmnKGs4FvO1oEglkls2q%2BHc3msFsYq7Oryu0J0giFhgKZ6ukye8cZrMNk0cltuLIAL0wAH0CAA6TeFx09vsDocjzAOAnEkAgCJYVQrpQARxVEoJhc36/JYOwsI9Wdu38Vs%2BbXL/c03EtVBn3Rf0DAUT4aUwfBRBZAUYPpR90WfAU20YDtbgAeQYe5ERRdCeUwthnwAJQ%2BAh40TegFEdH9vRaX1/QEQMo1oMMrTwdAUVoCBlhBBidh2W4AHVMBYqoIgkggEAk2kFC8WgCE%2BLwsiMQVbn4Wh0FuIMQw%2BLIBFuVAIwSWF/A0cx/GskxLJfK4hJEgAVOTbjSJhkAAa1uAB3CTWgk7T8A0vBPjsjQKImai7VosD7MEn8AFpwNPEBYlQTwVwDFpBAJCAwLMGyipguD/3hXD8O5M92JVAUoqom1Yo%2BGro07VrvEwAS3zVTEU16jUrkbU0gOGucCRAsC3wgpgoOlWC8HgzsQV3KV%2ByoAgKIjd5fL6r8fzG8rgOFZ8YqTOiescn9VulVAiGUJhgFVK7v3HfaGO/H1FpY4cWWDUMMs8SM2sSj7Y3esGfxMABWKxoYzBc8GXNdn23N8IDSi8g2vTA71eecn03dEBJeyHXonUmyYY2kCA2BhQaphiCqJorrIgBnGbBrAoQwjnOaZvn%2BbB9bB2HUcCBPAh0DPFgmC81csavW97y2FCesuy4hc5s9DpZW5uN4glSsW5sBT1NF4TO2jUKJ9GSc1rWPuWDqVUFqnlm6iGycnDGpZluWFYYS8cbxh94SXTBUCoZ8ICtj5lluJLbi4ckJxTe3vf6zMPwd8mpwpXPfybIDJs3OOLq7Qu1IiYBqUeiS4QVGk7tQB6noJcupoxTM%2BvzwbrlrPMgS1W4ADE8GICZbmwVRWHZCT8xzQf/nrJftULBQolQABxWlm1DRfLl1%2BcQNuUIBVPsidyVXspQ3rfd8wfe9oZr6/Ry/SAcyjjauewu3rPgSRutwyLpgGsCLO04163GcpRKsQI34rlmkoNoEARZbR2o%2BTeO894smIOiM8bd5ypGTgKMwZCCEgF/p7AuWpl4nGHlSIQR4BC6RnnPeg8Caz0NOKva4IktoJCULcDQgog7JxWkxRaSCoIJAIBAMAYAz4DgwZgXa8J744KfngyhRCCRcAFCQ8htwzCUOoWqDgqxaCcGhrwPwHAtCkFQJwNw1hrDenWJsBu4IeCkAIJoSxqwvIgGhpIdcGgkhmDMAATmiVwaGESkhcECIEaQ1iOCSF4CwCQGhUj2Mcc4jgvAFAgFSP4hxljSBwFgDARAIB1gEDSIicglA0BsjoAkKIHZOCqCSP4JK/hJC3GAMgP0Uh1xmF4AtIgCZpYGP4IIEQYh2BSBkIIRQKh1AVNILoAxvliBMDSJwHgVibF2ICU4zg2FERNKlFHW4vT%2BmDOGaM5OYSzC3AgB4dp9BQxYi4MsXg5StCrAgEgNpaQOlkAoBACFUKQDACkOQmgykhGUFiBc2IERWgomObwLFzBiAomwrEbQR5ym%2BLaWWAguFaC4u2VgWIXhgDAVoLQEp3BeBYFlkYcQDKJ7krwGZDljigxHkRNsXxEQWTpMcciWIByiUeCwBcpUeBsmctIGZYgGUlCPB5cAZERgAmrCoAYYACgdQ7WwryPFazhCiHEKshZ8glBqAubs/QhhjBuMsPoPAsQSmQFWKgNIjQOVJWJI3UwlhrBmAKdq2ZLVg09EFc4CArhph%2BAMWEaSixRgGOKNkAQWa9BFsaAsEYiQDF2DTU0SY7RPCdD0LWhwfQG2VqqAW2wDbS01o7XmqtEhVgKE8VsYd%2BgzmkHybwQpDy%2BkDKGSMsZ7zPm4EICQWEPjAV%2BJNasOSTAsCJH4qQYJkgwTrmiWCVJGhJBmEkJZDQ0N/DRMnRkrJIAwRcHXP4Lg/gkjRKSf4UJ8Sr3%2BGnRcwpxTSm7oqaC2pYL6k3OaTCuFvyulsE4K0FgEZAhJSYDNDSXBonrm/aK/AMzuJ6BdUsp10gXUbPdds3Q5D9mHLxacjgtiIPbMKdcxpiITJUHnU8oZUJvXJxI2Rz53zIW/K3WCMwO7gWVMQ2hhILTYWoB%2BaMcTRhiNcFSCivBJSIAYu2QSnFdrLNEpJWShwdqqWMBpQwOlFzGXMtZeyu13LvV8scfgWkbbhUXLFcgCVdrpX1AufKxVKJlXbEcWqjVvjtW6swPqvzNcTV8HNZa61trNU0cdSs%2BjshGNbMcSxr1xqY1WD9fKoNJ7Q3hs4JGqW0bfUWHjbOxN3Fk0ntbY0FwQc%2B0hCDp2pYhbMjFtyE2go02Sg5Em92ob7aBhjbWwIfobQVvVp7Rt%2Bb2aDu7cHV26tI6x0rM49xmdlyOAicXYR2uxHSPhLXRRzd/zlN7tIAeo9lBOOZNINksEJHb2BGhtElJYI70PskAYu7UHbAwZU/B%2BAiGGm3M0%2Bp4gGHtjYeeSwBQEY/QRle3OCYUzPuzOo7IWjpX7UVY9Z%2B0gbGjmcpu%2Bc3jVzkN3OE6oInJOycU%2BbFPL52m5PmSxGCH7cGqngsl1CnHSvflUOQGkNIK5yfRJXJTggK5Bf0boCZ9FmLsVEusxb4lpLyWOe09S2l9KAuYCZSysQ3nNW%2Bd5YlrlArgstW2WFiLmqouyt4LFnFCXVUJhS7wNLmQMusiy8a%2BXZrHr5bUTaxgdrivLIkGV9ZbrKs6FZwYWrXX/WBvgCGsNOQOU7FPHVuNCaEhJqayO%2BodaRvuCO3oXNFQh2Ldm2N8ty2ztTdTW27bva%2B81q79P%2Bt8wJ%2Brdn/kY7cxTuD/OxO0dGxx0ArfbdyDnAHlC9J5GUXLJxfrpmQpgFQLfv/dGCe9JwPskxPXGCME0MEkI9yd/oEP%2BjxgUpwNBmUr9metDJeskoELkkkJIHElwJEkVG%2BmCNzqAUUrBiCpxpMiAbOmAdgYElqkIjkCAJIEAA%3D)

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/left_review/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/pagelivore/left_review.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/left_review.test.hpp)
