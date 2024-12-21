<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::Disjunction`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-disjunction">To Index</a></p>

## Description

`Pagelivore::Disjunction` accepts a list of predicates and returns a function.
When invoked, the function returns true if its argument list satisfies any of the predicates and returns false if otherwise.

<pre><code>   Preds...
-> Args...
-> ... || Preds&lt;Args...&gt;::value</code></pre>

## Type Signature

```Haskell
Disjunction
 :: template<auto...> class... 
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

We will implement `Disjunction` using a fold expression.

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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKzSrgAyeAyYAHI%2BAEaYxCAAbAmkAA6oCoRODB7evgHSaRmOAqHhUSyx8Um2mPbFDEIETMQEOT5%2BgTV1WY3NBKWRMXGJyQpNLW15nWN9A%2BWVIwCUtqhexMjsHASYLCkG2yYAzG7bu/uYR25MXkQAdPdH2ADUyAYKCve3ysSY%2BKLbCkeJg0AEExsQvA4ngARPAKbReBgOLLAkEmADsVlBTxxT1OeyYB2O1zu9wAas08ExovRAYdsKjcU9wZCCE9vqgiMomMALtjcRisSCmUyZo5kC8BGNMKoUsQntFUJ4ngA3MRePnCkU4wUQT4YtwG76/PD/TB0twU4hUmnm/X0kAgNXeTCLDHQo5Cpnuz2MgX8nH486XEmoT5Wm20oEBp5eDJGdk8zBPI7Q9nETmobm8y4R6m0%2B0Mw5Cn3F1GogD0ACoa7W6/WK5W608ACrmggKJ51xug6v1/u1nto0HmQ5hV5eLAp45oJGYFId6PDkF9mvp34AfQ0XcHlYrTwASpgCGsGJ2CBDk3gqHiEMnmsAfIw2XCnsAfoS4rfDE8uBpbqiQafiGNxhg89KoiyULGugW7lpizJNOKkpntssryoqyrOhqKaYlQYhKKWFi4R6ZYjqCQFElcoFPAAkkuPwAI5eHgPydhAf7Tm4dFuqCUFsjBcHHPREEjghYqmih0roQqSq0Kq6rJoKF4akRJG%2BuRK7NoJXA7jWQ4VvuR4nsQZ54peTzXre97EI%2BbCCJZna0ueCA/v%2BgE7ASVGhoWkEqdBPywVw8HERJEqztJcqyVhim4RY%2BG0IR6KkcRRHlhRnnBsSNEiQyoJMSxbFPBAtFcU8Gi8WC/kCYFG7BcJS6CohhKSRFaFRZh8nYUpmIqRcyWeupZHLquVbrrBZh6VWBlGcep7nhZVkEHeTwPk%2BDmvpgKqMABGVnMB2WkgBolVRCAWbmYIXNchbUyh1ckKS6cUJUlKVDSWe1eRch2oHRDGYMxrHmsVpXmP4TyTamqblZV/HjRul0NSdTVhVJ7UYQ93VxX1alpZpo1PNgqisHsybdh5%2B3eaBnwgrZdJ5SCcZhMATwALLHkwVCIsiAjTmmsLwtz9SXIJGikPDXDi4JiMM462bfW4tPAB84FFh9VUtcgG5MO8cQEBA7NNFzSLC8cAC09XYI63VusNYXa7rLQGxzxs8wwlwy9bim20K9s60oTtgGAbMu0LKLHP4jxey6Pt%2BZrDsB/rhuc2HAiXGbntOt7GkjfutE3gwv1yiaZqOU8cqoCqeBYOgpB7tZj04a%2BYgAO5MAAnp2JgJBoL0XD3u0a%2BKCd6xAQcwnCCIm%2BHhoOiA8uXJLEPi4cUdZzHnocMstCcP4vB%2BBwWikKgnCGpY1jMqs6xKWYhw8KQBCaFvywANb5LcGiSFw6KHBo/gaGYJIZgAAcwD9CcEkLwFgEgNBiwPkfE%2BHBeAKBAGLR%2Bh8t6kDgLAGAiAQCrAICkG45BKBoF2HQOIERWCbFUMAhIZsEiSDfMgCUUhbhmF4CaIg1p0B6H4IIEQYh2BSBkIIRQKh1AYNILoSWLdiBMBSJwHg29d77yfsfTgAB5G4RC2SoBvLQ%2BhjDmGsMkOw4qHhyH0HlKOLgixeDoK0MsCASAyEpAoWQCgEA3EeJAMAKQZg%2BB0G2MQFBEBojqOiGEZo7clG8CicwYg7dNHRG0JgBwcTSBkPsgQTRDBaCxKkVgaIXhgBXFoIlTJWAWCGGAOIIpQNkTbRQVImU6SbibHvmEbYO8pG0DwNEeRSSPBYHURePA0DuC8G2sQRUShoQ7Fqf0owT9lhUAMMrMkeBMAt00SkRgmT%2BHCFEOIERRzxFqHUTI/QtSUDWGsPoAZKDIDLFQAuLILSzZjHQKmUw59LBmAQTMnh5p4DLDsOk%2BoLgGDuE8O0PQIQwiDAqMMSWhRMgCEmH4NF6QMUMDmEMeIksIVu16BMOFeRiW1EhT0cY/QkXzFRbYOlWK9AzBaASlFRLwVXw2BIFRHA96kHgbwRBTxDEMKYcAFhv4zGTQgLgQgJAUy3zsQ41Zyw7xMCwPECAr8QCSEOLcAAnIcdEkhP5mEkD3P%2BCRjXgI4JA0g0C763ASFwBIwDjXAI9YELg/hTXJBFRopBthUEP1WVg3BLj8E6OIV4nx1iqFsE4M0FgKp0RmyYC8AwCYuDGtuFwD%2BnD8DcOrnw2QgjTnSHOUoS5UjdCBLkQouJAqhXBsQdowhNwnj6NWsQdNmbs2vFqb%2BAtRbtwQEse46xKrDhmHsRGjBzjXGoCsXEEh3i10zuGGmjNZsR1GHzX%2BIJtAQlhIiVIhJMTMnXqSSktJGSplZLXTkvJBT1HFNKeUypz7qlLM2EffAPwmmgtaaodp2xMndNqOo/pgyYkjMAw460kz74zLmZgBZNSjDLNAMuvgGyFBbJ2Xsg5z6jlVuETW2QFzJFH0bTclZfyrCWEedEZ5erj7vKlJwL5BAfmHGhCx6wgLRXAurqCl5XQaXOAgK4VlktEVlEJXodF9RFOpFxfUTlCwqXdAEGS1oFLsUydJXS3TTL2XGdyKZ6zlnuUrDWHyuxDr23qLFXuodObR35sLR/YqiruFzrVUupxmrMDauGFx3pTqXUFs/uiAN6If6SCtYwyWHbODIPDY4zB2C8EEN0ZuxNlDqGpoHcYlgCgVQShVH584YwS1Kp4RWgRJzqOiPkHW%2BjOgQCHFIM2xRUy21qKkZ2uNeibxpqqzVurDXPxjAsdujxc7DiLryyulAK3rElZ28MWrKQUgbnq8ajcjWCDa0qzW4JcQL2ROiUk29j3kmpMhZk7Jz532FKA5gEpZSxC/vvv%2B3DyHSDAZpc09RbTkAdOg4IWDfSBlDPbkhsZqHMkYfSFhxZuHmaRvWTyYj2zdn7IPvfSjHWJA0bET1q5/WmPGHuWx%2BDnHXk8bPJwCs3y7n/IsGJ4%2BEmsBs7M1C%2BTMLNPKeRXprTRQsiafU1kBzbLqXmb6Jpkl9QjPK%2BJSykzbKLMMtU65hQvLhGjeFR5zg/aWCzdq6qBbAI2QKtLcq2xG2NWkC1TqygAq4sgDMAWw4hx/D/y/rA4P6JPWW/G9lsNaDPdv0kP4E1/hgGAONZIY1P8zVcAG70w4Y2EFx82wKjhMfi%2BhtL6QGZGRnCSCAA)

## Links

- [source code](../../../../conceptrodon/pagelivore/disjunction.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/disjunction.test.hpp)
