<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::IsRailful`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-is-railful">To Index</a></p>

## Description

`Omennivore::IsRailful` accepts a type.
It returns true if the type is a packed `Rail` and returns false if otherwise.

<pre><code>   Type
-> Type == Rail&lt;Items...&gt; ? true : false</code></pre>

## Type Signature

```Haskell
IsRailful
 :: typename...
 -> auto
```

## Structure

```C++
template<typename>
struct IsRailful
{
    static constexpr bool value {RESULT};
}

template<typename>
constexpr bool IsRailful_v {RESULT};
```

## Examples

```C++
/**** Vessel ****/
template<template<auto...> class...>
struct RailLike;

/**** Items ****/
template<auto...>
struct PageLike_0;

template<auto...>
struct PageLike_1;

/**** Tests ****/
static_assert(IsRailful<RailLike<PageLike_0, PageLike_1>>::value);
static_assert(! IsRailful<int>::value);
```

## Implementation

```C++
template<typename>
struct IsRailful
{ static constexpr bool value {false}; };

template
<
    template<template<auto...> class...> class Stockroom,
    template<auto...> class...Sequences
>
struct IsRailful<Stockroom<Sequences...>>
{ static constexpr bool value {true}; };
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISRqkrgAyeAyYAHI%2BAEaYxCAAzNIADqgKhE4MHt6%2B/oGp6Y4CoeFRLLHxSbaY9kUMQgRMxATZPn4B1bWZDU0EJZExcYnSCo3Nrbkdo739ZRXDAJS2qF7EyOwcAPQAVLt7%2BweHe5smGgCCO3sA1ACSLMn0bIJMdVf7J%2BeXR99HH2enZwImHuBiBJgSbgIAE9koxWJhwdgAaNiF4HLcFAAlJh0KheWgAkwAdgsV2mjmQVzQDFGmFUyWIV2iqE8VwAbmIvJgrsSLFQxEpiQARcGk4WiwnnIEgl4I87gtwAq7Kq7Sh6yhVq0EIiFMLxEAB0RsRVIMCgURoNJuQZoUVwaqGQAGtiCyWKQlSqtRrdfrUJbrbbLUJMABHLkMdYKQkJJHnFFoggY7G4/EKh3O12oFjpsMRqMB2OIwkksmNClUgS0%2BmM5msjnebm8giohFEkUJMXtiXyz4/b5/L7bK7YVSsB7c94Aof946Si77K4ANUw5pqbznUuB6rBEO9u7cesNxtjpqY5sLcbOCfRKdooSdOqsvYX1xu0rtU63MoPR/9J6vG8k2UJhgEwB9MAAfQ0Ht/m/HcdUPP1L2RFtEyuECwIgyCuFg6dFwAFVXAhP03a9yzwZBIPPJRmggG4sRxWg8QJCE7wghVMPAvBH2g0gMNA7jeNwotYxAEAGy5BZYPJSjqLXOiwDAZMmJYhUwgIRFxMkzBpM7DglloTgAFZeD8DgtFIVBOEVSxrDJFY1ibMwEh4UgCE0AylidEBjMkA0NAADjMMwAE5Qq4YygsCrgiSJaQjI4SReBYCQNECczLOsjheAUEBAg8iyDNIOBYBgRAQBWAhkn1chKDQe46DiCJ4U4VRAoANgAWg6yQrmAZBKSkA0zF4TB8CIYg8HQPR%2BEEEQxHYKQZEERQVHUIrSF0LhSAAd2IJhkk4HhDJMszPKszgAHl9RqpNUCoK52u63r%2BsGq5hrMK4IA8Rr6EZcxXIWXhCq0JYICQBrkiasgKAgKGYZAYApDMPg6CBYg8ogaILuiMImihY7eDx5hiChK7om0TAHCJ0gGqeAgroYWhCc2rBoi8YBD1oWg8u4XgsBYQxgHENm8GIanHDZVcLrpan9Q2NyNJqC7aDwaIDrJjwsAuls8FS/nSGl4hmSUIVgWFtWjE8pYqAMYAFCXPBMF2q7YXMty5uEURxGWr21rUC7tv0YWUGsax9HVvLICWVBkjqPmutGdBwSFUw7MsMwsuNqasGjiAljsSXMhcBh3E8No9BCMIBnKIYdoKDIBAmPwG7SJuGFmQZ4h2ouHG6MYWgr3Je5qYuBB6Zou7rnvbEHlu9GmKea7mevC8c9YJFOjhTNITLeGyp7Op6vqBqG/yvogXBCBIHkXK4YH3JtpYEEwJgsHiAvSB8yQEgNUKEjxQ0JIMwkgOrpWMh1UK%2BhODJVIKlVyBoOpcA6oFUKMUOp%2BUigAjqe8LrZVyvlJ%2BRVwblQhpVW6tU4YI3%2Bi1NgnAmgsDZESLqTAzxGA%2BqFA0XAApjQmiQaas1ZALV9tIf2ShA6bV0Kjfah0ibb13vvS6HAbrVX1FcB6R8Xp9RtMLTh3CArfV%2BtDf6d8EhmEfqDYq5CaFxDqvDbMJihi6KMFwCKgQaC0AxljHGm0SYE1pv4smFMqY00NvTRgjNmas0suzTm3Nea00FpbDYsTxbF2lnzSyctkAK1psrRKlk1YawJtrVJIMpoGzcsbU2mBzZCyMFbUAJC%2BD20ds7V27taZexEUtMRsgA4bUstIkO1t05WEsJHaI%2BdY7x0yInZOqdxnWCzgfHO00ZYx06OPPwEBXALx2tXUo3c9CNzqAc0gZzMjT3mKPLoE957D1bts/uDyZgrxOb3R5ORnlLz6B8meW9lirE3g/GBO9zqbUPs9E%2B7DgD6J4Rob619JpmIfiDZ%2BpBX7vyGF/RKcCEFcOAUSYyoU4pJFAb1HaSiCG2CIVY0h8ByFVTuvY2xxA6EbEYa9FgCg2SUjZG4g02pRh8JvrnIR80fZ9JWvICRQydCJD2gdI6/MFGQqytdSh91HqqB5XygVQqRVJh%2Bo4mGZiEiWJtiVSGZr/psrtUMflyRkiQUFaFSCxrIJ6rEejOIPjcb4zJoEoN5NKaS1phEwQTMWYXTiVzMQiTDbJMaeU0g%2BAJb90ybLVQ8sgT5MECrTaxTNZQjKbrSptMalpDqRbRpYRmlg1aaBdpLs3aMG6cI6VEh%2BmrXlUHJVBgxnh0mcUmZVk5lVk4JsZOYcM4WFWVZdZed4CFzHq83Z%2BynlVzLjc%2Bulz27nO3W3Qo1yAW3JeXUSeQ8fmL3XVewee7Z5/IuX8p9QKFAbyWuqvBULOBPX1fy9kRrZSjGRfwgG98rUkJfm/D%2BlBt4EpAGFA0CQEjGSipILg6U0NElQb%2BzVOU6UFUxT/Yy/9YpEnSoFSQEUuDBTMLgxKCQNUH04BimD4LRoEbY0RhlSxjbpGcJIIAA%3D%3D)$Done$

## Links

- [source code](../../../../conceptrodon/omennivore/is_railful.hpp)
- [unit test](../../../../tests/unit/metafunctions/omennivore/is_railful.test.hpp)
