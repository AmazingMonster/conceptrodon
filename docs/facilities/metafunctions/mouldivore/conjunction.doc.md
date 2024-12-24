<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::Conjunction`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-conjunction">To Index</a></p>

## Description

`Mouldivore::Conjunction` accepts a list of predicates and returns a function.
When invoked, the function returns true if its argument list satisfies all of the predicates and returns false if otherwise.

<pre><code>   Preds...
-> Args...
-> ... && Preds&lt;Args...&gt;::value</code></pre>

## Type Signature

```Haskell
Conjunction
 :: template<typename...> class... 
 -> typename...
 -> auto
```

## Structure

```C++
template<template<typename...> class...>
struct Conjunction
{
    template<typename...>
    alias Mold
    {
        static constexpr bool value
        {RESULT};
    };
    
    template<typename...>
    static constexpr bool Mold_v
    {RESULT};
};
```

## Examples

We will combine `Pred_0`, `Pred_1`, and `Pred_2` into a new predicate using `Conjunction`.

```C++
/**** Pred_0 ****/
// Returns true if the argument is less than 10.
template<typename...>
struct Pred_0
{ static constexpr bool value {false}; };

template<typename I>
requires (I::value < 10)
struct Pred_0<I>
{ static constexpr bool value {true}; };

/**** Pred_1 ****/
// Returns true if the argument is greater than 0.
template<typename...>
struct Pred_1
{ static constexpr bool value {false}; };

template<typename I>
requires (0 < I::value)
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

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Conjunction<Pred_0, Pred_1, Pred_2>
::Mold<Args...>;

/**** Tests ****/
static_assert(Metafunction<std::integral_constant<int, 2>>::value);
static_assert(Metafunction<std::integral_constant<int, 4>>::value);
static_assert(! Metafunction<std::integral_constant<int, 5>>::value);
static_assert(! Metafunction<std::integral_constant<int, -2>>::value);

// If no predicate is provided,
// the value is always `true`.
static_assert
(
    Conjunction<>
    ::Mold
    <
        std::integral_constant<int, 1>,
        std::integral_constant<int, 2>,
        std::integral_constant<int, 3>
    >::value
);
```

## Implementation

We will implement `Conjunction` using a fold expression.

Note that we are not providing an initiator. The default initiator for `&&` is `true`. We place `...` on the left side of the expression to do a left-fold.

<pre><code>   ... && Predicates&lt;Elements...&gt;::value
-> true && ... && Predicates&lt;Elements...&gt;::value
-> (...((
       true
    && Predicate<sub>0</sub>&lt;Elements...&gt;::value)
    && Predicate<sub>1</sub>&lt;Elements...&gt;::value)
    && ...
    && Predicate<sub>Last-1</sub>&lt;Elements...&gt;::value)
    && Predicate<sub>Last</sub>&lt;Elements...&gt;::value
</code></pre>

In our case, left-fold and right-fold produce the same result since `&&` is commutative.

Here's the entire implementation:

```C++
template<template<typename...> class...Predicates>
struct Conjunction
{
    template<typename...Elements>
    struct ProtoMold
    {
        static constexpr bool value
        {(...&&Predicates<Elements...>::value)};
    };
    
    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxCAAHBqkAA6oCoRODB7evgGp6ZkCoeFRLLHxSbaY9o4CQgRMxAQ5Pn6BdpgOWQ1NBCWRMXGJyQqNza15HeP9YYPlw0kAlLaoXsTI7BwA9ABU%2BweHR8cH2yYaAIJ7BwDUAJIsKfRsgkx1DDeHZ5fXJ38n3wu5wuBEwjwMoJM/jcoPBb0wUJhAE8UoxWJgAHRYqHYG7IAwKBRYjHKYiYfCiUEKHHAsbELwOG4eBjaLwMboCYEmADsVkuNwFN1hT3hiIIKLRbGJ2GejAI1P82GBgpudIZBBupNQRAAsp50MrBTy%2BRcVSqxm88Mg8QIxphVCliDdoqhPDcAG5iLwI/lmgXGiDE8wANhDpPJVvhCrcMrBcqJ2MVIBAnu8mCWPIAIlCTSqsznDf7fQLhRCEdDxajmFKsbGXvKacWbl4MkYbnraOgblDM5riNrUB2DdC6/Gg4qC5d8/4TcDfv8joD5zdsKpWE9MJ9TnOFwCuVOzP4wvivFhuxWJQB9AjEJiEBVKqc/Q598mXjRb/ZL7Y3ABKmAIdYGAUIV6U3PAqCFBBNyaYAfDlG48BA%2BhCSgwwbi4DQMWBUtRQvKt0XHR8LjVRlw3Qd8uV5VVGkca00GA0EHSdF03VTb1u15KgxCUacLE47MZ33EEwRFSF8MlTc7kbC4yQARy8PAyRAiA7mTdjN0RDCNAzS5SI1cjKOhaSJynaiLTom1GPtR1nVdWgPS9TTeRvb0%2BIEycgWfW5DK4T9dm/P8AKAkDXPAyCCGgm5YPgwREJA4AyXhJ1IvQrCcNEssxQlatMUTYj9NfCiuCo/iLKtKy7WYuy2KcziLG42heO5QT%2BL44TcPE5ECLYe4ZPkxTlJuCAPy0tSUyc3SSNcsiyWKxETOI40aMtejbSY2zWIcjT6rC9z2qfK4X0Msx/MC/9AOIYDQI4iCoJg4g4PreKbkwd1GGwy5OvLbrJKI2kZoMubLzMUqVsshiqs2%2BzHLTerGua1qPKEw7vuynqpP6zAFKUzAVPGnbzAAVhuU6ex7G4dIB%2BlZrfUHjJk5byrW6zqq22GOONPaWpzZHZ28/Z2wApgqDZDkPi%2BDK4S6ys/qxWTgAfYEWzCYAhcaUX2Xec9e2ZVktayRFDOSIrLy4UhTfp4jkyHREFYTbCJxRryjtuAAVPH5TOgHVsvJhCTiAgIB1YXNfFxExnQZMwlBRKxEvSHGkEREY4tq2cXUybPOZv2A%2BaYPQ7F94I4IKOQBjzA49oBP1sMAgU8EC3JBpJMJrTDNnZz/2lHzsAwHVkWi8N6FI%2BjwRK9vavE7rhuCAtomW%2BwTP2%2Bz2irVznug77gew%2BLkfS7H2PJ5rxiZ%2BhVObgAWnT1uNI7/mrh/O5IIYVAbkdCNKXAkDHVQd08CwOgUgc4fyRU3DtJC0VaAAHcmBIhAiYYMGg9pIM%2BtNX23dA7AggIWJkAh9bh2hDJFUNt9S4MRLg80B9y7jyrifC0ydz6NwwjiYBTYqFlwrnQ6ejC3AXytmw00foaKcNocfHh9cmFzxuP4YhRpb5OWBPfDgKxaCcCJrwPwHAtCkFQJwNw1hrCqjWBsTSh4eCkAIJoFRKwADWIAiaSAxBoBIZgzAAE53FcCJi4hIXBuTcmkGojgkheAsAkBoZIWidF6I4LwBQIBkhWO0So0gcBYAwEQCANYBAUheDnhQCAaBHh0DiBEdEnBVAJGDJfYMkgbjAGQNaKQGIzC8AjEQYgAC9D8EECIMQ7ApAyEEIoFQ6gUmkF0ObaBt4UicB4Ko9RmjrG6M4AAeXyXkjUqBIJVJqXUhpTSMJONOhADwJT6BOnMP4LgSxeDJK0CsCASBikpFKWQQprz3kgGAFIMwfA6CgmIAkiA0QVnRDCE0JE8zeAQuYMQJEazojaC6MkixxT6xrIYLQaFEysDRC8MANwYgmowtIFgFghhgDiDxbjbo70EkTPtF0fJWwLEV2CTo2geBoi3gRR4LAKybx4HCdwXg71iAuiUJmMEVLuVGGsSsKgBhFYADU8CYGgWsqsZLenCFEOIIZerRlqBWVM/QVKUCGMsPoHlCTIArFQCkd4jLL6Rx7KYSw1gzAxIlV0rA9qIArE6OLFwDB3CeDaHoEIcwygVD0GkDI7xJh%2BHNomooDABhxuGObEN7xegTEjXkXNNRUU9BmFmoY8Rc0zBTXoC0zRK0LGrcGkxmwJCLI4Bo0g0TeCxJuHs2p9TGnNJOcNXAhASDdnMXcyxiqVjQSYFgeIQbSD2MkP4DE7j/CBI0JIMwkgkEaCJsGdx%2BhOChNIOEm5GJgxcGDAkdxfjgyOO8du4MPaVmxPiYkudKSnmZOedkzZ%2BTyCUC%2BZc8pbBOBNBYO6bkl8mB4gMG2Lg7iMRcGce0/AnTunmz1f0w10hjVKFNRM3Q/yZlMDmWKzt3be2rI4Bs3J%2BSbg7IHdUodyGqUYXQ5hj8ZzUAXLiNO/wZhZ0PNSUBiDcQwNFKE28y5KAUO/K8ckGgtAgUgrBRMuFUKyV6YRUilFDgyUYrlFinFKz8WEuJbQUlYryWyqMDSnR%2BAyT0rxis5lyBWVko5Ss7lvKoUCq2Do4VoqLESqlZgGVlKXOq0VXwFVCh1Wau1YwXVshCODOI7IE14ydEUYtQqz1VgbVBcDY651WRXXuv8JmMr3rfVxH9V5h11RahZDDRG3IqagjhqbfGtNhRk1Fv6%2Bm94Q2c2dbLfUWt4362lvFgW2YpQq31oW31zbfRpsttWOsdttzz1duWRM/tg6Dn4h42hjDzjx04andc259z52kEXcuygnbL3XvQ3u7kRN3EBP8Puw9khzYMe/bYX9kmAPwCAzkrZcmZPECg1sWDByWAKHdNad0t2yxjGw5O/1PTssGty8M%2BQpHCs6HyFRmjCyTv0a/eskD2zdmY%2Bx7j/HUYNSCeE1cw8/gJNJekwp95yPxdKZxykFIl48fuMvATggl5VB1IBZpuI2nwWQoRQZ3XiLkWorM0JzF2LcVucwASolJLGUWIpXKsLvB3NloZd51QLLQT%2BfHpy3gQW%2BVIlC0KrpkXxVxBi3FuViX/3JaYGqjVWqdWOYI%2BTiQeWRnU7NfkFTVqvUVbtfAarLrODbFHk1ywPq%2B1%2BoAe11debusQFcHW82Mb1vNoTaNrIzeChJqyHtpbXX5t9G7/XofjbY0bZrcPxbU/x9t%2BG62w7gy6NnZiZwAdnOcceh51SPnE7OmiZe3%2Bx5C7MBLuGKu4JP2QAeIxP4fwRMfHg8iff7kD7P3nc4D%2BpJb311Ey3f4tyJEgkJIF4lwK4mYB%2BsEv4Kvn2l/sfjYidm0h/mvnEggUsCsBKhkM4JIEAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/mouldivore/conjunction.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/conjunction.test.hpp)
