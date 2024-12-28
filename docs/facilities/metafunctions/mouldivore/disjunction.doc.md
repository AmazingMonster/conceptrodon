<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::Disjunction`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-disjuction">To Index</a></p>

## Description

`Mouldivore::Disjunction` accepts a list of predicates and returns a function.
When invoked, the function returns true if its argument list satisfies any of the predicates and returns false if otherwise.

<pre><code>   Preds...
-> Args...
-> ... || Preds&lt;Args...&gt;::value</code></pre>

## Type Signature

```Haskell
Disjunction
 :: template<typename...> class... 
 -> typename...
 -> auto
```

## Structure

```C++
template<template<typename...> class...>
struct Disjunction
{
    template<typename...>
    alias Mold
    {
        static constexpr bool value
        {RESULT};
    };
    
    template<auto...>
    static constexpr bool Mold_v
    {RESULT};
};
```

## Examples

We will combine `Pred_0`, `Pred_1`, and `Pred_2` into a new predicate using `Disjunction`.

```C++
/**** Pred_0 ****/
// Returns true if the argument is greater than 10.
template<typename...>
struct Pred_0
{ static constexpr bool value {false}; };

template<typename I>
requires (10 < I::value)
struct Pred_0<I>
{ static constexpr bool value {true}; };

/**** Pred_1 ****/
// Returns true if the argument is less than 0.
template<typename...>
struct Pred_1
{ static constexpr bool value {false}; };

template<typename I>
requires (I::value < 0)
struct Pred_1<I>
{ static constexpr bool value {true}; };

/**** Pred_2 ****/
// Returns true if the argument is even.
template<typename...>
struct Pred_2
{ static constexpr bool value {false}; };

template<typename I>
requires (I::value % 2 == 0)
struct Pred_2<I>
{ static constexpr bool value {true}; };

/**** Metafuntion ****/
template<typename...Args>
using Metafunction = Disjunction<Pred_0, Pred_1, Pred_2>
::Mold<Args...>;

/**** Tests ****/
static_assert(Metafunction<std::integral_constant<int, -1>>::value);
static_assert(Metafunction<std::integral_constant<int, 2>>::value);
static_assert(! Metafunction<std::integral_constant<int, 5>>::value);
static_assert(Metafunction<std::integral_constant<int, -2>>::value);

// If no predicate is provided,
// the value is always `false`.
static_assert
(
    ! Disjunction<>
    ::Mold
    <
        std::integral_constant<int, 1>,
        std::integral_constant<int, 2>,
        std::integral_constant<int, 3>
    >::value
);
```

## Implementation

We will implement `Disjunction` using a fold expression.

Note that we are not providing an initiator. The default initiator for `||` is `false`. We place `...` on the left side of the expression to do a left-fold.

<pre><code>   ... || Predicates&lt;Elements...&gt;::value
-> false || ... || Predicates&lt;Elements...&gt;::value
-> (...((
       false
    || Predicate<sub>0</sub>&lt;Elements...&gt;::value)
    || Predicate<sub>1</sub>&lt;Elements...&gt;::value)
    || ...
    || Predicate<sub>Last-1</sub>&lt;Elements...&gt;::value)
    || Predicate<sub>Last</sub>&lt;Elements...&gt;::value
</code></pre>

In our case, left-fold and right-fold produce the same result since `||` is commutative.

Here's the entire implementation:

```C++
template<template<typename...> class...Predicates>
struct Disjunction
{
    template<typename...Elements>
    struct ProtoMold
    {
        static constexpr bool value
        {(...||Predicates<Elements...>::value)};
    };
    
    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxCAAHBqkAA6oCoRODB7evgGp6ZkCoeFRLLHxSbaY9o4CQgRMxAQ5Pn6BdpgOWQ1NBCWRMXGJyQqNza15HeP9YYPlw0kAlLaoXsTI7BwA9ABU%2BweHR8cH2yYaAIJ7BwDUAJIsKfRsgkx1DDeHZ5fXJ38n3wu5wuBEwjwMoJM/jcoPBb0wUJhAE8UoxWJgAHRYqHYG7IAwKBRYjHKYiYfCiUEKHHAsbELwOG4AETwCm0XgY3QEwJMAHYrJcbkKbrCnvDEQQUWi2MTsM9GARqf5sMDhTc6QyCDdSagiABZTzoVXCvkCi5qtVjN54ZB4gRjTCqFLEG7RVCeG4ANzEXgRgotQtNEGJfLcodJ5Jt8KVbjlYIVROxypAIG93kwSz5TKhZrVWZzxsD/qFoohCOhktRzBlWLjL0VNOLNy8GSMNwNtHQNyhTO1xF1qA7RuhdYTIeVBcu%2Bf8ZuBv3%2BR0B85u2FUrCemE%2BpznC4BPKnZn8YXxXiw3YrUoA%2BgRiExCEqVVOfoc%2B%2BTLxot/sl9sbgAlTAEOsDAKCK9KbngVAiggm5NMAPgKjcrI3MAZLwi6BAIIYNxcBoGLAqW4oXlW6Ljo%2BFwaoyEboO%2BPL8uqjSOLaaDAaCToum6Hppr63b8lQYhKNOFg8dmM77iCYJipCRHSpudyNhcZIAI5eHgZIgRAOHnm49wplxGa0jemqvtRGiInJE5TnRVqMXaLGOs6rrurQXo%2BpupqGQivIiUJglicuVGXlwn67N%2Bf4AUBIEeYhkEYTBxBwfWiEgfQhJQVhuH4RJZYSlK1aYkmZEUVqAVcLRQnWTatkOmxjmca5PEWHxtACV5ObCZOQKXARUnIsRbD3PJSkqWpNwQHcun1YiNwaJmlxFcZgVmfJpr0daTH2qxDkcc5ekNR5gntaJT5XC%2BAVmMFoX/oBxDAaB3EQVBcUJQhSGYJ6jB4V1WWEb1MmkQZ9KUWS1FmGVq02cx1VbU5Lnpg1TUtd5h2zl9cI9ZWMkDRZCmYMpqmYOp42ppNZgAKw3OdPY9tNs3kYZQNvqD0LmWRK0Vetdk1dtsPce5YEHb5x3LnqAFMFQHLvBdmVo%2BWv15cSCnAA%2BwItmEwDtqL4ucpL1MsmyHJcgwiIBckC1cKQC1M2RKZDoiiuJnhE5HZ1J23AAKgTipS3NDE2peTCEnEBAQCLjRa4biJjOgKZhKCKFiJekONIIiKxxbAC0pVO9gE3ppmzvs/7gfNCHmsG%2B8kcENHICx5g8e0InG2GAQqeCBbVs4rnvr52ahcB0oJdgGAGth%2BXWSV9Xtf143LHN63BAW6TNLJsTecdX3xfB6HYtj9y0JRzHgh17eDdJ3P0Jpzc6cdyvek935P53JBDCoDczqRpS4Egc6qCengWDoFIHOH8sUeZfxuGIAA7kwJEIETAADYNAIwRIgz6dM1pFwHi3S4EBCw3CHsyVk7Jtbj2hPJNUNtDR4MRHgy0VdD5xxPjPK0KcL5t2wjiIBTY6GTyPtPM%2BrC3CXytlw80AZ6K8MYQnARLc2ELxuP4chJpb6uWBD3DgKxaCcFJrwPwHAtCkFQJwMMlhrDqjWBsNyh4eCkAIJoDRKwADWIBSaSAxBoBIZgzAAE5vFcFJh4hIXBeS8mkFojgkheAsAkBoZIeiDFGI4LwBQIBkh2P0Ro0gcBYAwEQCANYBAUheAXhQCAaBHh0DiBEdEnBVAJHgeneBkhkLIFtFIDEZheCRiIMQf%2Beh%2BCCBEGIdgUgZCCEUCodQGTSC6HNpA28KROA8E0do3R9jDGcAAPLFKKVqVAkE6kNKaS0tpbjzoQA8BU%2BgLpzD%2BC4EsXg6StArAgEgcpKRKlkFKe8z5IBgBSDMHwOgoJiApIgNEdZ0QwhNCREs3gULmDECRJs6I2gujpJseU%2BsmyGC0FhdMrA0QvDADcGIZqcLSBYBYIYYA4gCX426O9FJ0zHRdGKVsGxtdwkGNoHgaIt4kUeCwOsm8eBoncF4O9YgbolBMjBDS3lRh7ErCoAYJWAA1PAmBIGbKrBSgZwhRDiFGQaiZah1mzP0DSlA1hrD6D5SkyAKxUApHeMy9OUceymFMZYMwCSpW9KwI6iAKxOiGxcAwdwng2h6BCHMMoFQ9BpAyO8SYfhzbJqKAwAYCbhjmzDe8XoExo15HzTUdFPQZg5qGPEfNMw016CtM0atCxa2hosZsCQKyOA6NIPE3giSbiHMac04ArTsJnNGrgQgJBuzWIebY5VKxoJMCwPEENpBnGSH8Bibx/hQkaEkGYSQiCNCk3gd4/QnBImkGiXcjE8CuDwISN4oJ8DXH%2BL3fAvt6zEnJNSYujJLzcmvPyTs4p5BKA/OudUtgnAmgsE9LydOTA8QGDbFwbxGIuDuK6fgHpfTzYGqGca6QpqlDmumboQF8ymCLIld23t/aNkcG2YU4pNx9lDvqSOtDNLsJYZwx%2BC5qArlxDnf4MwC6nmZNA9BuIkGymiY%2BdclA6H/l%2BOSDQWgIKwUQumQimFFLDNIpRWihwFKsUKhxXi9ZhLiWktoOSiVlL5VGDpQY/AZJGUE3Way5A7KKVcvWby/lMKhVbAMaK8VNipUyswHK6l7m1bKr4GqhQmrtW6sYPq2QJGRlkdkGaqZBjqNWqVd6qwlh7XRGDc611WR3Wev8EySr1g/UDoDf/XzTrqi1CyBGqNuR01BEjS2xNGbCippLSNzN7xxt5r6xW%2Bo9aZuNvLYbItsxSg1sbat4be2%2BgLbbasdYnb7lXp7Ws6Zg7h3HPxPxzD2H3FTvw7O259zHlLtICutdlBu03rvVhw9vJSbeJCf4I9J7JDm2Y3%2B2wAGZPAfgKBgpuzFPyeILBrYCHjksAUJ6W0nontljGHhmdgb%2Bl5aNQVsZ8gKMlZ0PkWj9HlmXaY7%2BrZ4G9kHLxwTonJPoxahE2Jm5h5/DSdS3J5TnyMcy9U4TlIKRLzE%2B8ZeUnBBLyqCaUCnTcQ9OQuhUi4zRvkWovRZZ0T2LcX4s85gIlJKyXMpsVShVkXeBeYrUyvzqg2WgiC0fblvBQsCqRBFkVvSYuSriPFxLCqUtAbS0wDVWqdV6pc8RmnEhCvjIZxa/I6mbU%2BpsKFurhiGv2k4NsA%2BbXfX%2BriIGnrG6C0DYgK4Bt5s407dbUmqbWQO8FBTVkY763%2Bsrb6APlv4/m3xt23Wifa358z%2B7xN9tZ2RmMeuwkzgQ6%2BeE69ILqkwvp09Ik59wDzzl2YFXcMDd4TAcgB8Rifw/hSYBJh7El/vJn0/pu5wf9aS32W6pMu6wSvIsSCQkgfiXAniZg364S/gW%2BA6/%2BF%2BDil2nSv%2B2%2BSSqBSwKwUqGQzgkgQAA%3D)

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/disjunction/implementation.hpp)
- [Source code](../../../../conceptrodon/mouldivore/disjunction.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/disjunction.test.hpp)
