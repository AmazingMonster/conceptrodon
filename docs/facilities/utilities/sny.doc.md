<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Sny`

<p style='text-align: right;'><a href="../utilities.md#sny">To Index</a></p>

## Description

`Sny` accepts a `Snow` operation and returns the operation via member `Snow`.

<pre><code>   Oper
-> struct { using Snow = Oper; }</code></pre>

## Type Signature

```Haskell
Sny
 :: template<template<template<template<typename...> class...> class...> class...> class...
 -> template<template<template<template<typename...> class...> class...> class...>
```

## Structure

```C++
template<template<template<template<template<typename...> class...> class...> class...> class>
struct Sny
{
    template<template<template<template<typename...> class...> class...> class...>
    alias Snow = RESULT;
};
```

## Examples

This function injectively maps a `Snow` to a type.
In the following example, We will create an overload set of `fun` using operations `Op_0` and `Op_1`.

```C++
template<template<template<template<typename...> class...> class...> class...>
struct Op_0 {};

template<template<template<template<typename...> class...> class...> class...>
struct Op_1 {};

constexpr auto fun(Sny<Op_0>) { return false; }

constexpr auto fun(Sny<Op_1>) { return true; }

static_assert(not fun(Sny<Op_0>{}));

static_assert(fun(Sny<Op_1>{}));
```

If we only want compilers to perform an argument-dependent lookup, we can utilize `decltype` and `std::declval` to avoid defining the function body.

```C++
constexpr auto gun(Sny<Op_0>) -> std::false_type;

constexpr auto gun(Sny<Op_1>) -> std::true_type;

static_assert(not decltype(gun(std::declval<Sny<Op_0>>()))::value);

static_assert(decltype(gun(std::declval<Sny<Op_1>>()))::value);
```

## Implementation

```C++
template<template<template<template<template<typename...> class...> class...> class...> class Operation>
struct Sny
{
    template<template<template<template<typename...> class...> class...> class...Args>
    using Snow = Operation<Args...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGwAnKSuADJ4DJgAcj4ARpjEIADMABykAA6oCoRODB7evgHBmdmOAuGRMSzxiam2mPZlDEIETMQE%2BT5%2BQfWNuS1tBBXRcQnJaQqt7Z2FPZODw1U14wCUtqhexMjsHASYLOkGeyZJbnsHR5gnZ/uHTMen53cPNxf3V48AnumMrJgAdICTtgANTIAwKBSA/7AsEQqFApKg8FMSHQ2EoyEggDyP2I91ywJMGgAgpNiF4HCChAxUAB3KhiWjEkkmADsVlJIO5IKel2ufPeAtu/MeIqFXx%2BzDY6KRcNRCJhcsxiox8OhJOIwAURK5PK82SM1NpdJBJwAIji8QSBNdNdrZdgTpzWWzzc6WSyAPQAKj9/oDga93oDIIAKtghGGhCCA8HSb7A0n/fHWaTBS8Mx9Xs9s1mBd9fjLEcj1SX5WjyyrHSzyZSCFaAPoaM0c9nupIuln5sVvTPi/t9vOF6UAqtlpWlhWOiuqpG1ggUqm4xtcVtWN0e0kh/0ggBieGIk3DmGPcc9pLQDEmmFU6WIIKYXiIIKoXgYEBp9MZtGZpxXGjAis64gsQmAEJsDCvmISjOq27rbpeAg3neD5Pi%2Bb4fl%2BDJMtcK5cEBIFgRBxBQYuXgfBY8EXmSrSOMgjYKgkBAQLSDaYZ%2BJo/n%2BbgAUSbZuisKxbmmtEEgxTHtNQ76cd%2BuH/ukq78Ru5pCSJO5%2BtSmBXugJ5nimNHmEkETgl4WBmqcz50IQny6qJV4ofej7PqgILADJ2HcXhimAUiwEALSwpM6AgCAP5KI2BCFupSHXnsqHOS%2B7lYVx8m8YpBF%2BSCgVysFoXkZgkXRZ2NHzPRjGQsxrGoA2WDglFPzQDJeUgHVtAAG5iNcnlpXx85IhAQkrKFnXeJgwklYhYnlZJLFtQ1mBNR%2BLVtaN3Wpb%2B3lKf12CDUJI1iBRE0WBway0JwACsvB%2BBwWikKgnBuNY1gggoGxbJgZpmEkPCkAQminWsADWIAXZI/waJIXBskkGgXRoZj%2BP4ZgpGk50cJIvAsBIGgaKQN13Q9HC8AoIB4/9t2naQcCwDAiAgBsBDpM%2B5CUGgBx0AkUR/JwqgpP4/n%2BJIbnIMgIJSP8Zi8Jg%2BBEMQeAhVwMiCCIYjsFIyvyEoagA6QuhK3S%2BLpJwPBnZd1260T2LPszDaoFQIJ8wLQsi2LEtmCCEAeBz9APkZXArLwFNaGsEBIOz6Sc2QFAQBHUcgMAUhmHwdB7EelCxLrsQRG0nwm7w2fMMQnzYrE2jaRTv3s2wgjYgwtB55TpBYLEXjAG4TKk9wvBYCwhjAOITf4GBDh4O1p667e2nPjsv0RHs6N3bQeCxPixceFguuLng2Pd6Q4/ELEWSYOa%2Bz98vRgA2sVAGNqABqeCYHSuKMPnmuq%2BIGv8IIigqOoTf630P3FAz1LD6BXqTSAaxUDpCaF3fywULSmEsNYMwhMD7yywJAwavQK65BcAwdwnguh6DCBEEY1QxhKxKDkAQMw/DUKyLQhgixRiJCVnYPBAgBjTGIYUDhDQuHNCmEMchSwqG2BEfQvQ8x2isMoewtYb1NjbAkGbDgV18aW04I7fmgthbAFFuLcGHsIC4EICQL6P1A5/SvmsBAmAmBYESDgkGkgkj/ECEkNkkhIZmEkP4XGF0ejo0xqQbGP1/j%2BC4P4FIgQUgxLBlwC6Xj/BaKbkTEmZNbGU1DnTMODMbYsxjnHX23M2CcDaCwdqbJ/JMHlEaLggR/hcAhtLWWJAFZ6G/sIUQn9pA9N/jrABIBk6GyYMbbu6jNEE14FbIpdsHZVJqXUhpwBxbNNaS2L2qAfYJCsWYGxwcqYFNKQkVmsddmR19iAZZtSURGCaVwPGNBaBp1JhATOTdC65zfj84updy4ODftXRgBA64N11i3NuHdfxd1%2Br3c%2BOw7rDzwePLud0p7IBnm/eeDRdbL1XrnDeyKg7y13r9A%2BR8lCnz7kYC%2BoBcl8FvgoB%2BT8X43V%2Bj0j%2B6sBmyCGf/O6uhk4GEvsgqwYDCXYOgbA3I8DEFJHNOK1B6CEiYInlA3Bo9nAQFcNIpWZDKhsL0DQpo%2BqMhMKaPI5YAi%2BjcKkXwhhWqmg8NEUahRMiHUFCdbIt1FCbVKPeqogO%2BhzbpMJjou5qyHnrKaS0iGntzFyysQHIOdjSAOKcWMHBoSsbJGaZDNkKS2Qw0kP4oWStZn3U4Fk8mV9qb5KQIzW2FyznEHKTsKpLsWAKHamLdqcbLiTHaRYzB3TZA8okHyn%2B2tBU6GSKQcZkzTaho0RbDJnBrZM2fCCe2j5iAsG7b2/tg73jHh2Xsv230khHPracq5UdW0PpuX29IikB2BEbEOggjED1CxTm8hIHyvl3X%2BY3X6YHAUVxBbsmu4L66NxRZgVu7dO5v0RfS0lzdDxoonk3LFOK954sXrwQla9Pgkq3uSt%2BVLj60vPhERlIdmVMHvo/Z%2BUo37cr6byzWArda6CSEAsVoCbBSvgDKuBnAvR5WVZYNBcyMEKw1Tgzh2q/C6sIeaw1/qJGmtyOa/T5QxHGttUI115q1MupEdaiRvrLM2ZMx6kNyiPpqNXTM7RHB92HuFj2vtIIP3/G/YmjpV7rFptyfYxxzjKDqLCdjMwzSkhJAuvDKGuMUtslieGuZNbbDZOOUJUgbiLqeIuikRGgRJCBBht4rgQn0ZJHXRG4mOSQ7qKlrl6tbWitrAPtkZwkggA%3D)

## Links

- [source code](../../../conceptrodon/sny.hpp)
