<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::Conjunction`

## Description

`Pagelivore::Conjunction` accepts a list of predicates and returns a function.
When invoked, the function returns true if its argument list satisfies all of the predicates and returns false if otherwise.

<pre><code>   Predicates...
-> Arguments...
-> ... && Predicates&lt;Arguments...&gt;::value</code></pre>

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

We will implement `Conjunction` using a fold expression.

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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKxmpK4AMngMmAByPgBGmMQgAGyJpAAOqAqETgwe3r4BQemZjgJhEdEscQnJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlUbHxSSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwEmCypBjsmAMxuO3sHmMduTF5EAHQPx9gA1MgGCgoPd8rEmPiiOwUTxMGgAguNiF4HM8PAxtF4GA5siDQSYAOxWMHPbHPM77JiHE43e4PABqLTwTBi9CBR2wKJxzwhUIIzx%2BqCIyiYwEuWJx6MxoMZjNmjmQrwE40wqlSxGeMVQnmeADcxF5eULhdiBRAvuZEvqfn88ADMLS3OTiJTqWa9XSQCBVd5MEt0QARY6Cxnuz0M/l87F4i5XYmoL6W6004EB55eTJGNnczDPY5utnEDmoLk8q4Rqk0u30o6Cn3FlEogD0ACoa7W6/WK5W688ACpmggKZ51xtg6v1/u1nuosHmI7hN5eLApk5oRGYVId6PD0F9mvpv4AfQ0XcHlYrzwASpgCOsGJ2CJDk3gqLiEMmWsAfIxWXhOzTzwhDM8uBo7iigwSlxErcYaPHSKLMtCRroFu5YYkyzRihKZ47DKcoKkqTrqimGJUGISilhYOEemWI5ggBhLXCBzwAJJLr8ACOXh4L8nYQDR05uN%2BGiumCkGstBsEnHR4EjvBoomshUpofKiq0CqarJgKF7qoRxG%2BmRK7NoJXA7jWQ4VvuR4nsQZ64pezzXre97EI%2BbCCJZnbAL8gFygQn4MM8v7/rs%2BKUaGhYQSpUG/DBXBwUREnirO0myrJmGKThFh4bQBFoiRRGEeW5G%2BcGwFELR9GYExLFms8EDblctG8eCwUCaFG7hcJS4CghBKSTFqFxRh8lYUpGIqZc6WeuppHLquVbrjBZh6VWBlGcep7nhZVnuTZdnPo5zyYMqjB/jl5yASGIGBXxdVTRuZgRW1SGddK3VyQpzpJSlaUZaNJYHX5QFUQVIn0mCjHMax5UceY/jPDNqapl5NX8RdV3NaJqLiYhHWSl16GPX1SWDWpWWaRNzzYKorD7Mm3Y%2BYd/knQ8oK2bSAOgnG4TAM8ACyx5MFQCJIgI05prC8KIg0VyCRopAXVwkuCYjTMOtmP308AnxgUWn21e1yAbkwHzxAQECc80PMi8iJxyw6fWumNUU63rrSG1zJt8wwVySE8luKdbgq27rSgO2AYAc07vOiyc/ge46XsaZrYp2/7BuB8Hxuh2bbgALQW1Hzre9lK77jRN4MKgzyysappbbKqDKngWDoKQe7WU92Gvs8YgAO5MAAnp2JiJBoeP9/tscmvH%2BsQELqcCFckeK1c0uQ5LRyR1bnocCstCcP4vB%2BBwWikKgnBuNY1hMmsGxKWYRw8KQBCaOvKwANYBJIdwaJIXBokcGj%2BBoZjJGYAAHIA/QnBJC8BYBIDQEtd770PhwXgCgQASzvnvdepA4CwBgIgEAawCCpFuOQSgaA9h0HiJEVgWxVCAMSOnRIkhnjAGQOKKQdwzC8GNEQK06A9D8EECIMQ7ApAyEEIoFQ6g0GkF0NLduxAmCpE4DwDeW8d73wPpwAA8rcAhrJUA3mobQ%2BhjDmHflfjNCeqBSH0DlKOLgSxeCoK0CsCASASGpDIWQCgEA3EeJAMAKQQQaC0B2MQJBEAYhqJiOEFoXdFG8CicwYgXcNExG0JgBwcTSAkPsgQDRDBaCxMkVgGIXhgDXFoKlTJWAWCGGAOIIppUkS7SQZI6U6TbhbBvuEHYm9JG0DwDEORSSPBYDURePAkDuC8F2sQBUSg3S7Fqf0ow98VhUAMCrUkeBMDtw0akRgmS%2BHCFEOIYRRyxFqDUdI/QtSUAn0sPoAZSDIArFQAubILT07jHQKmUwlhrBmDgTM7hZp4ArDsOkhoLgGDuE8B0PQoRwhDEqCMaWRQsgCCmH4NFGQMUMHmMMBI0sIUuz6JMOF%2BRiV1Ehb0CYAwkULFRbYOlWK9CzFaASlFRLwXn02BIZRHBt6kFgbweBzwDF0IYUwlhZjyq4EICQFMV87EONWSsO8TAsAJAgE/EAkgjh3AAJxHDRJId%2BZhJD9x/okQ1oCODgNIJA6%2BdxEhcESIAw1gC3X%2BA/v4Y1KQRXqIQbYZBt9VkYOwS43B2jCFeJ8dYihbBOAtBYMqNE6cmCvAMAmLghq7hcDfhw/AXDa68NkAI050hzlKEuZI3QQRZHyLiQKoVgb4FaPwbcZ4ei27EFTemzNbxanfjzQW7cFirHxCVUcMw9iw1oOca4yx7jrFEO8cu3xKa03pyHUYXNP4%2BB0BCWEiJkiEkxMyeepJKS0kZKmVkyxOS8kFLUcU0p5TKn3uqUsrY%2B98C/CaaC1pqh2k7Eyd0uoaj%2BmDJiSM39DirSTJvjMuZmAFk1KMMs0AC6%2BAbIUFsnZeyDn3qORWoRVbZAXIkfvetNyVl/KsA86DzydUH3eZKTgXyCA/KOG6BjAKgXxBBSx8F1KXbQthXkbFwQYWcsWDi4o2RWUKbxXJplJKGhkraBS6TGnaVzAZYStlLKdPGYM%2BUIzdjVjrD5VZ3pra1Fiq3QOrNw7c35rfnK4tirbFzscQ/UgGqtWUAFQ6p1eb35oj9WiL%2BkgLX0Olm2zgiDQ3%2BecZGpAeCdFrvjeQyhya%2B1GJYAoZU4plTuYuOMItCruFlv4Sc8jIj5A1uozoEARxSCNoUVMltqjJHtpjbom8KaislbKxVwC4xyoeEnTYq%2BRw/PhqjblzxxCN3WMdMgVIqQNzlcNRuSrBAdaFarUe%2BIJ7InRKSZeq7yTUmQsydk58z7Cl/swCUspYhP032/Zh%2BDpB/00uaWotpyAOngcEJBvpAyhldzg2MxDmSUMZDQ4szDrNw3rO5Ph7Zuz9m7xvqRhrEgKOiJa1c9rdHjD3JsMxsFbGGgtIrN8u5/zLCAtFcC2uoKXndBpc4CArhlMyfQGpolaRcUNGF%2BihoYu2Vic0yZqT8uegCC03L4lSv4Wa/M8i%2BTPKbNCN68KxznBe0sFG6VlUE3ASsggPKrh06VXzqceqzAmqRisd6WFkAZg81HCOP4X%2BH9oEB7RO6k3/XkshpQWq0gz9JD%2BCNf4QB/9DWSENV/E1XAOu9KOH1uB0e0sCvYZHwvwbi%2BkBmZkZwkggA)

## Links

- [source code](../../../../conceptrodon/pagelivore/conjunction.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/conjunction.test.hpp)
