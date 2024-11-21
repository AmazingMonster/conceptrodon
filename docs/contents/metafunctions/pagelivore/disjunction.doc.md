<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::Disjunction`

## Description

`Pagelivore::Disjunction` accepts a list of predicates and returns a function.
When invoked, the function returns true if the argument list satisfies any of the predicates and returns false if otherwise.

<pre><code>   Predicate<sub>0</sub>, Predicate<sub>1</sub>, ..., Predicate<sub>n</sub>
-> Arguments...
->   Predicate<sub>0</sub>&lt;Arguments...&gt;::value
  || Predicate<sub>1</sub>&lt;Arguments...&gt;::value
        &vellip;
  || Predicate<sub>n</sub>&lt;Arguments...&gt;::value</code></pre>

## Type Signature

```Haskell
Disjunction ::   template<auto...> class... 
              -> auto...
              -> auto
```

## Structure

```C++
template<template<auto...> class...>
struct Disjunction
{
    template<auto...>
    alias Page
    {
        static constexpr bool value
        {RESULT};
    };
    
    template<auto...>
    static constexpr bool Page_v
    {RESULT};
};
```

## Examples

We will combine `Pred_0`, `Pred_1`, and `Pred_2` into a new predicate using `Disjunction`.

```C++
/**** Pred_0 ****/
// Returns true if the argument is greater than 10.
template<auto...>
struct Pred_0
{ static constexpr bool value {false}; };

template<auto I>
requires (10 < I)
struct Pred_0<I>
{ static constexpr bool value {true}; };

/**** Pred_1 ****/
// Returns true if the argument is less than 0.
template<auto...>
struct Pred_1
{ static constexpr bool value {false}; };

template<auto I>
requires (I < 0)
struct Pred_1<I>
{ static constexpr bool value {true}; };

/**** Pred_2 ****/
// Returns true if the argument is even.
template<auto...>
struct Pred_2
{ static constexpr bool value {false}; };

template<auto I>
requires (I % 2 == 0)
struct Pred_2<I>
{ static constexpr bool value {true}; };

/**** Example ****/
template<auto...Args>
using Metafunction = Disjunction<Pred_0, Pred_1, Pred_2>
::Page<Args...>;

static_assert(Metafunction<-1>::value);
static_assert(Metafunction<2>::value);
static_assert(! Metafunction<5>::value);
static_assert(Metafunction<-2>::value);

// If no predicate is provided,
// the value is always `false`.
static_assert(! Disjunction<>::Page<1, 2, 3>::value);
```

## Implementation

We will implement `All` using a fold expression.

Note that we are not providing an initiator. The default initiator for `||` is `false`. We place `...` on the left side of the expression to do a left-fold.

<pre><code>   ... || Predicates&lt;Variables...&gt;::value
-> false || ... || Predicates&lt;Variables...&gt;::value
-> (...((
       false
    || Predicate<sub>0</sub>&lt;Variables...&gt;::value)
    || Predicate<sub>1</sub>&lt;Variables...&gt;::value)
    || ...
    || Predicate<sub>Last-1</sub>&lt;Variables...&gt;::value)
    || Predicate<sub>Last</sub>&lt;Variables...&gt;::value
</code></pre>

In our case, left-fold and right-fold produce the same result since `||` is commutative.

Here's the entire implementation:

```C++
template<template<auto...> class...Predicates>
struct Disjunction
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr bool value
        {(...||Predicates<Variables...>::value)};
    };
    
    template<auto...Variables>
    using Page = ProtoPage<Variables...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISWakrgAyeAyYAHI%2BAEaYxCAAbIEADqgKhE4MHt6%2BeqnpjgKh4VEssfEArACctpj2hQxCBEzEBNk%2BfgG19ZlNLQTFkTFxiYEKza3tuVy2EwNhQ2Uj1QCUtqhexMjsHASYLMkGeyYAzG57B0eYp25MXkQAdE%2Bn2ADUyAYKCk8PysSY%2BFEewULxMGgAguNiF4HK8PAxtF4GA5MmDwSYAOxWCGvXGvC6HJjHM53R5PABqLTwTGi9BBJ2waLxryhMIIrz%2BqCIyiYwGuOLxmOx4OZzPGRLwyHeAnGmFUyWIr2iqE8rwAbmIvPyRaLcUKID9zAkjX8AZKiZh6W5KcRqbTLYaGSAQBrvJgVpiACKnYXMr0%2BpmCgW4glXG6k1A/G12umg4OvLzpIwc3mYV6nT0c4hc1A8vk3aM0umOxknYX%2BstotEAegAVPWG43qzWGwAVbBCVsN5sQuuN/s99EQ8wnMIfLxYdNnNDIzDJAj0xnD3uNrMAgD6GleTZr1deACVMARNgwFPjoWm8FR8Qg0y1gD5GOy8Ge6WeCAhDK8uBoHmjQxa4b3JGzwMmirKwqa6CblWWIss0jhSjOsryoqyqqq6WrpliVBiEoFYWNh3qVsu4IAcStzAa8ACScbgv8ACOXh4P8Z4QNRU5uN%2BGgehCEHslBMFnLRYHDnB4qIdKp57KhSoqrQ6qammQoEBeBFEQGpF9vWa7QVw27druB5Hie74Xq8V43nexAPmwggWWewD/Baiofl%2Bv7/vshIURGJbgapbK6euXCwYREmSlJKEKnJGFKdhFi4bQ%2BEYsRhEEVWELkdcJJUSJS70ZgTEsZarwQFuNw0bxkIBZB/x6TceWhfBEpITKMnRehCmYcpWIBdcKU%2BhpJFDuC2m1kFZgGfWg7Vnuh7HsQp7nlhlkftZtlPg5ryYGqjB/plXlhjlZJ/qJ1XQrVG5mE14WtdJcodfJiluvFiXJalQ3lgdlyAcdqA0XRjHMaxpUceYFSvJNGYZq8PH%2BRdAl1eu13CXRQrNZJyHtWhT3dfFfXqelWmrtgqisIcaY7t93nZZRJ30cAi5oomYTAK8ACyR5MFQSIogIU6ZvCiLIg0NyCRopBBTME10c6ea0wz3ygaWX3VS165MF8cQEBAnPNDzIuomcKPYM63UesNt0a1rrS61zBt8wwNySC8ZtKRbwpW5rSi22AYAc/bvOi2cFSuy67uaWriHWz7Ot%2BwH%2BtB0bbgALQm27boexway0JwFS8H4HBaKQqCcG41jWCyGxbMpZgnDwpAEJo2drAA1iAFSSA8GiSFwGInBoFQaGYCRJAAHGP%2BicJIvAsBIGgS4XxelxwvAKCAEtN0X2ekHAsAwIgIAbAQyT3OQlBoAcdBxBErA7KoY8JCnCSSK8wDIFKUgPGYvBmkQtroD0PwQQIgxDsCkDIQQigVDqG3qQXQMwADuxAmDJE4DwHOecC7NxLpwAA8vcU%2B7JUDXgfk/F%2Bb8P7fi7pNCAHgr70EVCOLgKxeBby0GsCASBL7JGvmQCgEAeF8JAMAKQgQaC0D2MQdeEBog4OiGEFoABPdBvAFHMGIEovB0RtCYAcKo0gl87IEDwQwWgKi4FYGiF4YAtxaBJQMVgFghhgDiEscVFEu115wLlHo%2B4OwG5hD2LnOBtA8DRBQZojwWAcGqTwHPbgvBdrEGVEoT0%2BwXFhKMM3NYVADCM3JHgTAiC8HJEYAY4BwhRDiAgZU6BagcEIP0C4lAFdLD6HCevSAaxUDzkyN4lO4x0AZlMJYawZhl7JIAZaeAaw7B6IaC4Bg7hPAdD0CEBYpRyh5DSBkAQUw/AzHyHshggwtkjBmPMx2fRJirOmN0BZvQ5hnOGPES5cwDl6HFK0F5Sw3lzOrtsCQmCOD51IEvXgK9XhkOfq/d%2Bn8aGlVwIQEg6Y64sLYTktYt4mBYHiBANu/gTgPCqCcDEkge5mEkAkBeFQEg1BCTPUgc964PASFwBIY8qhjw5Z3Lg1QTgJHBTglea8N6NxybvA%2BXCj6ELPgIoRjDb5sE4C0FgaoMQpyYO8AwyYuBVAeFwbuv98D/zwIAmYlTQE1OkHUpQDS4G6ECMg1BqiQVgohbgjgBCT73FeCQ14aqNVap1S478BqjVbjoagBhcQ0UnDMKwiV29OHcJjbwxh59BHpuEUGzVHwXH6p/HwOgUiZFyLgeo5RBiq2aO0bo/RiTDExuMaY8xOCrE2LsQ4ptTjMk7GLvgf4niZk%2BNUH4vYBigl1BwWEiJyjokDrYbaBJDdkmpMwOk5xRgsmgBTXwfJChCnFNKeUptVrqngNtbIepsDi5Ouadk0ZVh2lzq6QSkufSZScEGQQYZJxPTPvGZMuI0z31zLqI85wEBXCfJmBskorydkFEyHB0gxyGi/O2ZcyD1yPl3MOQ8vD/QsMXNmP0ND3z5iIb%2BcC9YmwgUsKnqC7BcCoV5pDQWvVEbu5ItNai5hSb2Et1IDivFlAQVMpZQanuGJqgYn7gEalvdhVsc4GKzekq96H2PkQrNiqb531VcQFgFCWAKDVFKNU%2BqHhXHGCalFACgGyGtVeyB8h7V3p0CAE4pAXVoMSe61jy98FyuIdeNVZmLNWZs3Z9k0bY1MLricITWm02Jf0zmxhLpkDJGSOuazVR1xxY1iZl%2BJbJFxHLfIxRmia21a0TohZBijFPjbRYwdmBrG2LED2hufad1LtIEOx5XicG%2BOQP4qdggZ2hPCZEpRi7YkroMeutIm6Mk7tZpKvJvIj1FJKWUwuDcL1gIkNeqBnnGk%2BcfcYNpNg32zM/Q0bx1YhmtLGZYCZkKpnmpmd0ojiyYPLLQwhxY2H0O7IaGhjDmRSNvMB08ijBGvm4YaDc6j4OyNUco88zZSGmMKEBeAoLqmQscEDWV1%2B5nLPqlixacYfHHPxoxcmjh2LMC4pGB%2Bxls8QBmANScE4FQh69wXkLjEnKyeQvU7YcVwmViEskBUElFQx4jyqJIKo/cyVcF8yEk4wWZerzZyJkJP9pdesxSmtYyT0jOEkEAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/pagelivore/disjunction.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/disjunction.test.hpp)
