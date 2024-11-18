<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::Conjunction`

## Description

`Pagelivore::Conjunction` accepts a list of predicates and returns a function.
When invoked, the function returns true if the argument list satisfies all of the predicates and returns false if otherwise.

<pre><code>   Predicate<sub>0</sub>, Predicate<sub>1</sub>, ..., Predicate<sub>n</sub>
-> Arguments...
->   Predicate<sub>0</sub>&lt;Arguments...&gt;::value
  && Predicate<sub>1</sub>&lt;Arguments...&gt;::value
        &vellip;
  && Predicate<sub>n</sub>&lt;Arguments...&gt;::value</code></pre>

## Type Signature

```Haskell
Conjunction ::   template<auto...> class... 
              -> auto...
              -> auto
```

## Structure

```C++
template<template<auto...> class...>
struct Conjunction
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

We will combine `Pred_0`, `Pred_1`, and `Pred_2` into a new predicate using `Conjunction`.

```C++
/**** Pred_0 ****/
// Returns true if the argument is less than 10.
template<auto...>
struct Pred_0
{ static constexpr bool value {false}; };

template<auto I>
requires (I < 10)
struct Pred_0<I>
{ static constexpr bool value {true}; };

/**** Pred_1 ****/
// Returns true if the argument is greater than 0.
template<auto...>
struct Pred_1
{ static constexpr bool value {false}; };

template<auto I>
requires (0 < I)
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
using Metafunction = Conjunction<Pred_0, Pred_1, Pred_2>
::Page<Args...>;

static_assert(Metafunction<2>::value);
static_assert(Metafunction<4>::value);
static_assert(! Metafunction<5>::value);
static_assert(! Metafunction<-2>::value);

// If no predicate is provided,
// the value is always `true`.
static_assert(Conjunction<>::Page<1, 2, 3>::value);
```

## Implementation

We will implement `All` using a fold expression.

Note that we are not providing an initiator. The default initiator for `&&` is `true`. We place `...` on the left side of the expression to do a left-fold.

<pre><code>   ... && Predicates&lt;Variables...&gt;::value
-> true && ... && Predicates&lt;Variables...&gt;::value
-> (...((
       true
    && Predicate<sub>0</sub>&lt;Variables...&gt;::value)
    && Predicate<sub>1</sub>&lt;Variables...&gt;::value)
    && ...
    && Predicate<sub>Last-1</sub>&lt;Variables...&gt;::value)
    && Predicate<sub>Last</sub>&lt;Variables...&gt;::value
</code></pre>

In our case, left-fold and right-fold produce the same result since `&&` is commutative.

Here's the entire implementation:

```C++
template<template<auto...> class...Predicates>
struct Conjunction
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr bool value
        {(...&&Predicates<Variables...>::value)};
    };
    
    template<auto...Variables>
    using Page = ProtoPage<Variables...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKxmpK4AMngMmAByPgBGmMQgAGyJpAAOqAqETgwe3r4BQemZjgJhEdEscQnJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlUbHxSSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwEmCypBjsmAMxuO3sHmMduTF5EAHQPx9gA1MgGCgoPd8rEmPiiOwUTxMGgAguNiF4HM8PAxtF4GA5siDQSYAOxWMHPbHPM77JiHE43e4PABqLTwTBi9CBR2wKJxzwhUIIzx%2BqCIyiYwEuWJx6MxoMZjNmjmQrwE40wqlSxGeMVQnmeADcxF5eULhdiBRAvuZEvqfn88ADMLS3OTiJTqWa9XSQCBVd5MEt0QARY6Cxnuz0M/l87F4i5XYmoL6W6004EB55eTJGNnczDPY5utnEDmoLk8q4Rqk0u30o6Cn3FlEogD0ACoa7W6xXK7WACrYIRN2sNsHVus9zuosHmI7hN5eLApk5oRGYVIEWn0gdduvpv4AfQ0z3rlYrzwASpgCOsGApcZDk3gqLiEMmWsAfIxWXhjzTjwQEIZnlwNHcUUGCZcibcYaPHSKLMtCRroGu5YYkyzRihKR47DKcoKkqTrqimGJUGISilhYmEemWC6gr%2BhLXIBzwAJLRqCvwAI5eHgvzHhAlHjm4H4aK6YJgayEFQSc1EgQOMGiiaCFSsh8qKrQKpqsmAoEKeeEEb6xHdjWy6QVwG4dluu77oeL6ns856XtexC3mwgimcewC/H%2Bcqvu%2BX4/rs%2BJkaGhagUpLJaSuXDQfhYnipOkmytJaHyZhFjYbQuFooR%2BF4eWYKkf%2B5FEFRNH0YxzHPBA65XFR3Hgr54G/NpVxCfOqKiXB4lhUhEWobJ6EKRivmXIlnqqUR/aghpVb%2BWYuk1n2FbbnuB7EEeJ4YWZr4WVZ962c8mDKow35pe5wYASS37CWVkIVauZhBbBBKNZKzUoTJcnOjFcUJUlfUljt5x/iGFE1SiuVMWaBVseY/jPKNqaps8XE%2BSdfGVSu52CTRAqXfBTXSi193tTFXUqSl6lLtgqisPsyabh9HkZV5Dy0cAc4onG4TAM8ACy%2B5MFQCJIgI45prC8KIg0Vz8RopD%2BVwYv8YjtUOtmGW058wFFu9ZVXcgK5MB88QEBAbPNJzgvIic0sOu1rr9SFGta60uvswb3MMFckhPKb8nm4Klua0oNtgGArN21zQsnP4LuOm7amq2KVvezrvv%2B/rgdG24AC0Jth867upYN26UReDCoM8srGqaa2yqgyp4Fg6CkPpS0PQtx5iAA7kwACex4mIkGi41322Rya0faxA/OJwIVyh3LVwS2DYtHKHZuehwKy0Jw/i8H4HBaKQqCcG41jWEyawbApZhHDwpAEJoS8rAA1gEkh3BokhcGiRwaP4GhmMkZgABw//onBJC8BYBIDQosN5bx3hwXgCgQCi0vpvJepA4CwBgIgEAawCCpFuOQSgaA9h0HiJEVgWxVA/0SMnRIkhnjAGQOKKQdwzC8GNEQK06A9D8EECIMQ7ApAyEEIoFQ6hEGkF0BLJuxAmCpE4DwZeq915X23pwAA8rcbBrJUAXjIRQqhNC6EfgfqNYeqACH0DlIOLgSxeAIK0CsCASB8GpEIWQCgEBHHOJAMAKQQQaC0B2MQWBEAYiKJiOEForcZG8FCcwYgrdlExG0JgBwkTSD4OsgQZRDBaARJEVgGIXhgDXFoPFFJWAWCGGAOIXJAMkSbVgSI6USTbhbHPuEHYK8RG0DwDESRsSPBYEUUpPAIDuC8E2sQBUSg3S7AqV0owV8VhUAMHTUkeBMBN2UakRgKTOHCFEOIPhuzBFqEUWI/QFSUD70sPobpsDIArFQDObI9Tk7jHQKmUwlhrBmEgeMthZp4ArDsEkhoLgGDuE8B0PQoRwhDEqCMCWRQsgCCmH4RFGRkUMHmMMBIEtgUOz6JMSF%2BQ8V1BBb0CYAxYULARbYSlqK9CzFaNi%2BFuKgVH02BIORHA16kAgbwKBzxtGUOobQ%2BhhiCq4EICQFMp9LHWIWSsK8TAsAJAgLfEAkgjh3AAJxHDRJIJ%2BZhJBd3fokHVACOBANICAs%2BdxEhcESD/HVP9HX%2BGfv4PVKR%2BVKOgbYOBF8FnILQfYjBaicGuPcWY4hbBOAtBYMqNEycmCvAMAmLgOq7hcEfsw/ArDK4cNkNwg50gjlKBOSI3QQQJFSMidy3lPqoGqKwbcZ4mjnjxsTcm1NFSPyZuzeuYxpj4iyqOGYKxgbEF2IcSYpxZjcFuNnR4ztSa3gVIzZ%2BPgdB/GBOCSI6J4SUkHtifExJyTRmpJMekzJ2TFF5IKUUkpF6ymzK2FvfAvxakAoaaoJpOwUltLqIorpPTwn9LfdYq0Izz7jMmZgaZ5SjBzNAFOvgyyFCrPWZs7ZF7dnFt4aW2QxzhFbyrec%2BZnyrDXJA3c9V28nmSk4K8gg7yjhuko98358R/m0aBWSh2YKIV5DRcEcFLLFjouKNkBlknMXidpfihohK2jEpE4pilcxqU4sZfS1TOnNPlG05Y1Y6xOXGY6Q2xRgqV3drXem/tj9JV5plRYidNjr6kGVaqyg3LrW2szU/NEnq0Sv0kMaqhEtG2cBgQG9zdiQ1IEweohdUaiEkLjcQFguiWAKGVOKZUGa7gXHGLm6VbDC1cP2QR/h8hy0kZ0CAI4pAa3SNGfWhRIim3ho0ReeN2Xcv5cK8V1kQ650jsHEcNzQbQ2pZcXgpdZjHTIFSKkFcBWdUrmGxrTLVCt1%2BPiLukJYTYlHuO3EhJIKUlpPvDenJ77MD5MKWIJ958X1IYg6QD95K6mKMacgZpAHBBAc6d03prdwODKgyk2DGR4MzKQ0zINSzuQYbWRsrZG9z54aqxIQjAi6unMa%2BR4wVybA0cBfRho9SKxvMuV8ywPyBV/MrgC%2B53RyXOAgK4GTon0DydxWkDFDQedIoaPzxl/GlO6eExLnoAhlPi7xdLqFSuDNwok%2By0zvD2t8qs5wDtO3qE5byyqIbf5xhObK6O%2BVk7bFKswCqkYdGOl%2BZAGYTNRwjj%2BA/s/MBnu0ROt1516L/r4GKtIHfSQ/hdX%2BB/l/HVkgdWv31VwJrHSjgdcgSHuL3KmFB6z36nPpBxmZGcJIIAA)

## Links

- [source code](../../../../conceptrodon/pagelivore/conjunction.hpp)
- [unit test](../../../../tests/unit/pagelivore/conjunction.test.hpp)
