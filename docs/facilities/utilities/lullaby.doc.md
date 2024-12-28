<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Lullaby`

<p style='text-align: right;'><a href="../utilities.md#lullaby">To Index</a></p>

## Description

`Lullaby` accepts a list of items and returns a function.
When invoked by an operation, the function instantiates the operation with the items.

<pre><code>   Items...
-> Operation
-> Operation&lt;Items...&gt;</code></pre>

It also contains a regular function, `size`, which returns the total number of the items.

<pre><code>size() -> sizeof...(Items)</code></pre>

## Type Signature

```Haskell
Lullaby
 :: template<template<template<template<typename...> class...> class...> class...> class...
 -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
```

## Structure

```C++
template<template<template<template<template<typename...> class...> class...> class...> class...>
struct Lullaby
{
    static constexpr auto size() -> size_t;

    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class>
    alias Grit = RESULT;
};
```

## Examples

- We will create a `Lullaby` with items `Item_0, Item_1, Item_2, Item_3`.
Then, we will transport the items to `Operation`.

```C++
/**** Items ****/
template<template<template<template<typename...> class...> class...> class...>
struct Item_0;

template<template<template<template<typename...> class...> class...> class...>
struct Item_1;

template<template<template<template<typename...> class...> class...> class...>
struct Item_2;

template<template<template<template<typename...> class...> class...> class...>
struct Item_3;

/**** Operation ****/
template<template<template<template<template<typename...> class...> class...> class...> class...>
struct Operation;

/**** Packed Vessel ****/
using PackedLullaby = Lullaby
<
    Item_0, 
    Item_1, 
    Item_2, 
    Item_3
>;

/**** SuppsedResult ****/
using SupposedResult = Operation
<
    Item_0, 
    Item_1, 
    Item_2, 
    Item_3
>;

/**** Result ****/
using Result = PackedLullaby::Grit<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

- We can check the size of a packed `Lullaby`.

```C++
static_assert(PackedLullaby::size() == 4);
```

## Implementation

```C++
template<template<template<template<template<typename...> class...> class...> class...> class...Items>
struct Lullaby
{
    static constexpr size_t size()
    { return sizeof...(Items); }

    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class Tranquil>
    struct Detail { using type = Tranquil<Items...>; };

    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...Tranquil>
    using Grit = Detail<Tranquil...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQDMpK4AMngMmAByPgBGmMQgAOwArKQADqgKhE4MHt6%2B/kEZWY4CYRHRLHEJKbaY9qUMQgRMxAR5Pn6BdQ05za0E5VGx8UmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimGmujMh4mAq3R%2BdXN6f/xx%2BlwuwLMAXCyG8WFuJgCbmQE3QWCosOwIJBfwBWIOQMxtwAkiw0vQ2IImI0vodcdiaWd0VcCJgiQZGbC3IzmeTMGyOcSuTymXzWXDeSzuSKAJ7PZhsAB08tRt0hTAUCnlssVytV6s1Bm1CoC2CVerV8vxHIUqJBE2IXgctxCXloBhiEvRiSsV1u3tuc0cyCVAgmmFUaWIvrwAC9MAB9AgR6MQZYgn0wj23YiYAgbBgJzCoKjqiDmpkKZMBCxp%2B70y6p0X8kWCsUCznC9lNhvt1virtCnsEKWMViYHWG40q00asdaye6iejo0zhfj1W3AAqxEMAEcvHQrV6fTa7fHHi06GnK14skZbgPnjCAvd15uGDu93CSyxZ4bYZWTIlqwrGs6w7Nt6zA0D%2B0gls%2Bxg5tJWlYdlyXA1FxNZD0NQldvzQ%2Bd5Q3bdd1ofdax9K9wmAW4AHFiEIB8n1PJh3zcAjXyIhcQBAO9xU9YEAN/GtMVpE5qTuAAxPBiAmW5sFUVhiUwSkcQxYSASBdEwQhKFFLZNAGC2NICEtH8rhUu5P0%2Bb4QXAqDuzgzsbJ5QcZRHLCUKnXD9Q87CF2tAhbXtT8Yw0ATTIZaDGzsyLYOi%2BD2WcpC3Mw7z3LnLySKPQKORjLhQuBcKot7OLHNihyErlJK8JS5K0pwvyAvjIKzDy6yIqKhy2pK%2BLEIq6qqtqjD%2BpMy5Msa7KAha34jluAB5Z5NwpKyCpi9qIMKrqNvK1y%2BvS6car2obPLqq5Rtm%2BbyRySbrmm5QmGQABrTB0FuAA1D47CUukrnIm9boep7HWdJhXXoh0nRdN1TLhFMfSCjRSBhA9vSCrgEZh5HsrMNGkYJcb0R/ICwuuu4hC8NI0iUdAACUPideMlsuH7KNJ8nMiemmFDp0G5viC6BHxtx0dxplgux0iMZF1HEfF4WWBjLHpdTIKJqhtFCfy4mDluDmuYZpntdp2h41hJ8/se9BAYhziaMINkeYWy6Cd4sytbXD56apPyLuQGMJ3iAgIERTiFGHX3jLcHWjYRlninZw2CFRctnam1T/lErWhEwPTntk%2BT6E%2B9PU8BGs/TwH2/baCAzYB8HgYlYOo0wJN6JN25JCTjhVloThkl4PwOC0UhUE4QXLGsX11k2HSwR4UgCE0TvVnukBkkkWUNAADjMMwAE4d64ZJN43rhEkSaRu44SReBYCQNHh/vB%2BHjheAUEB4fngfO9IOBYBgRAQHWAQNIXgCDkEoGgIkdB4iRGHJwVQG8ABsABaBBkhbjAGQAGKQsozC8CeoQEgeB0B6H4IIEQYh2BSBkIIRQKh1Cf1ILoVGAB3TcaROA8C7j3PuC8h6cBmiA4B8YCy3Hgcg1B6DMG3GwWYW4EAPCQPoOGcwAQuDLF4B/LQqwIBIAgWkKBZAKAQD0QYkAwApBYxoEbeIr8IAxF4TEcIrR67cF4I45gxAJQzRiNoLOH9Z4QNJAQGaDBaAuMHlgGIXhgBuDELQV%2BrjSBYBYIYYA4gGH4EzA4PAAA3D4vCQxZxAdsWe4RGQX0HrQPAMRNyeI8FgXh/k8A30SXk4gMQ2aPBSUYKpRgF6rCoAYYACgXrvGYTzfus9SHCFEOIKh0zaFqF4Uw/QqSUDWGsPoapr9ICrFQIZHICSkGIhNqYMelgzCPzabRLAOykw9D8TkFwDB3CeE6HoUI4RhhVFGKjYo2QBDTD8H8zIAKGALBGAkVGdhHkCH6FMN5BRoX1FhU0SYgwvmLF%2BbYdFQK9BzDaBCn5ULVgKEnlsCQXCOC91IA/XgT9RGIJQWgjBWC16yIgLgAhyiZ7qLnv01YCBMBMCwAke5y9Aiyh3gEM%2BGhJBmEkAgu%2ByQEE730JwK%2BpAb6qNlAgrgCCN472Pgg1eB9pUINpbwp%2BL8378s/tov%2BOiAGCJAWA4xqBFHQNgRwVoLAcmJCQUwccN4uA71lFwdeeD8BEBuSQ2Q5C5nSAWUoJZDDdBY1YUwdhriqU0rpXwjgAigEgNuCIsRzLg2UVDeG9eciFH6KUTCMEZg%2BWaK/k6kxSi3WdtGMqIwoauDwysYyKSlB7EMPcc4jhbinGeO8b4hw07SCBMYME0J4TeCROibE50CTZ7JNSekiJklHl5ISYPQpyBilLrKfUXhVSanOPqdsQeTSWmzzaR0pQXTD0UX6XwIZIyxkTKXdMhNlCk2yEWfQwe6bVl9LOVYSwWyYh3L2QcoMnBjkEHQKcjZFyrnxBufk3ZDzsnOAgK4PFqNPkVEhXof5jRqPpFBY0IlSxkW9DhbixFwKyONHhRiujxL8U8fyHxglQnvkcdJeSyhuaeEMIZeWiRfaq1hojRoORXKY1NtUa2gVpAhUitGPci%2BmrtVhrlSkHep8AjysVZIVG%2BbrW2FtW2h18AnWAKEd2j1DavVsE4L6iRX4ckBhydWsUEwo3cqIXGshsyIPUPkCmmDOgQBBEzdmzh6rqWKcfvwl1wiqCiNCwocLtxIthui/GeR/mDF6YCAZ%2B139dENa7UYntCRwvkxjNVmMtWYyqFQXwOgI7bHjsHpOzxS6ZteJ8X4pdK7BAhLCbwrdMS4l7s3UyQ9L7N0nuyWegpqgimMhvYIO9DCH21IlM%2BxptF328E/Z0vbPS/2tcGUwYZozMDjOlKB%2BNSWJCQZoWl5ZmX4PGHwzYB9aGh4YYYAknYQdEPWEufS65RCSP3JheRvwlGXnMdo9J7FjGcjMYp2UTF9HOOosE8x/HAn0XsexZJpnrPacibUWsDYFLecXzzVazgZW0FhYi1Frk0lOXRpIHptRGjDPGdFZQKlFmQC71lAEAIyRD5ObvjrxIBrLVKc4Da9%2BhmJXJClSfRId8N6SH3lwLeZgLUXwCAV%2Bl5u7VaKpbg03hXn6%2B8XqQNpWRnCSCAA%3D%3D)$Done$

## Links

- [Example](../../code/facilities/utilities/lullaby/implementation.hpp)
- [Source code](../../../conceptrodon/lullaby.hpp)
