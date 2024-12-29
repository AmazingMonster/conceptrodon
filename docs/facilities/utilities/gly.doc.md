<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Gly`

<p style='text-align: right;'><a href="../utilities.md#gly">To Index</a></p>

## Description

`Gly` accepts a `Glow` operation and returns the operation via member `Glow`.

<pre><code>   Oper
-> struct { using Glow = Oper; }</code></pre>

## Type Signature

```Haskell
Gly
 :: template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...> class...
 -> template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
```

## Structure

```C++
template<template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...> class>
struct Gly
{
    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
    alias Glow = RESULT;
};
```

## Examples

This function injectively maps a `Glow` to a type.
In the following example, We will create an overload set of `fun` using operations `Op_0` and `Op_1`.

```C++
/**** Operations ****/
template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
struct Op_0 {};

template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
struct Op_1 {};

/**** fun ****/
constexpr bool fun(Gly<Op_0>) { return false; }

constexpr bool fun(Gly<Op_1>) { return true; }

/**** Tests ****/
static_assert(not fun(Gly<Op_0>{}));
static_assert(fun(Gly<Op_1>{}));
```

If we only want compilers to perform an argument-dependent lookup, we can utilize `decltype` and `std::declval` to avoid defining the function body.

```C++
/**** gun ****/
constexpr auto gun(Gly<Op_0>) -> std::false_type;

constexpr auto gun(Gly<Op_1>) -> std::true_type;

/**** Tests ****/
static_assert(not decltype(gun(std::declval<Gly<Op_0>>()))::value);
static_assert(decltype(gun(std::declval<Gly<Op_1>>()))::value);
```

## Implementation

```C++
template<template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...> class Operation>
struct Gly
{
    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...Args>
    using Glow = Operation<Args...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGzSrgAyeAyYAHI%2BAEaYxCCSAKykAA6oCoRODB7evgHSaRmOAqHhUSyx8Um2mPbFDEIETMQEOT5%2BgTV1WY3NBKWRMXEJyQpNLW15nWN9A%2BWVIwCUtqhexMjsHAD0AFR7%2BweHR/tbJhoAgrv7ANQAkiwp9GyCTPXXB6cXV8c/x5/nZ3OBEwDwMwJMAGY3MDQa9MJDoSDHnCETDkeCoWiwfDMUjsai8SjcbCMdCAJ4pRisTAAOjpkOw12QBgUCjpNIZTJZbPpEMZzKYrPZnIFQt5/O5wr5XMFPI50tFCmuAHlKcRXlkGYCxsQvA5rgBxWhkwEmADsVgu12t1yxRMRJJxDvRTrtpLdrsJ7q9ropVLYUolssDMrF8qDYZFkvFoblUeDdPOxGACi1VptXgyRkNtFQAHdrpCACIqtUagQIpMpwOQy0As1F2umr6/VsfQHfHbXABieGIY2u2FUrEemHeJw7ban/0nN1VcXLDCV7YuHoJjvXLs3%2BOJW93O%2BdB4IfuYAZjipDF/P0fDscvN/jkb52oIuv1qoA%2BhpCxbzY2IXWgJrvu9rAYeoE%2BtuEEbpiJ7UveCa3leSEPgqqERnGaGIWm5w6nqBClh%2BXA/lYDZNhcs57NcVBeAw457P8aBLsCqgpMQ1zRKgnjUbREBGiaUKfhoDKLCR1zEJgBBrHRVBiEotY/o2FEXExYyYKx7GcdxNEMHxxoIp%2BXAiWJElScQdGvl4OIWIpzaXAc1wACqYGMy4ThcMyOMgH6ynEBAQAwqAETpekCW4Qlar%2BDaLIs5G4U0Xk%2BayfnULx/EGSkRGRaRRYxXFlFTr8/ydtcQiYEx6CDsOoJjiu9mFa2M4UWYEJhMyXhYIWsGUh%2Br5MIQqbPsp9VUcAtH0TsjECGpGnXEwXhENcY26elgmZcJfKiQAtJyYzoCAICybQSi9X6%2BUqdNLFsXNC2oEtaX6WtWWbdcO3SntB2WZgp2UudI1ds5rkTf8nl4N5vktAFQXXFgzLHpS0C8R9ICw7QABuYgIqt4XrVqfIQDFiwHRj3iYLFAEvhq4PJZDqPw5giO6cjqMk1jj04892AMgTMXE2IVnkxYHDLLQnCJLwfgcFopCoJwbjWNY1wKKs6xjuYEI8KQBCaMLywANYgIkkg0hoAAcZhmAAnJbXCJGbptcGaZrSKLHCSLwLASBoGikJL0uyxwvAKCAPva1LwukHAsAwIgICrAQKQLeQlBoA8dBxBE1KcKopv%2BFtgRLcgyDXFINJmLwmD4EQxB4PtXAyIIIhiOwUgN/IShqDrpC6PXebqiknA8CLYsS13AfKgticEagVDXDnecF8ARcl8bZjXBAHhp/Q7Hq1wiy8GHWjLBASCpyk6dkBQEBnxfIDAFIZh8HQwL9pQ0Rd9EYTNGSg%2B8J/zDEDJMqaI2hyph01qnZ4BBlQMGNF3LA0QvDADcGIY6v9SBYBYIYYA4hw4YL7GAvAaMXJd3UuVBamxNZhGBK7aWtA8DRHVIAjwWAu6vjwJ7bgvBiHEE4koIsIJsH0KMDrZYVADApgAGp4EwHmecktNb8EbqIcQrclHtxUOoPBPd9DYJQArSw%2BgGHB0gMsVAKR6jBw4FtPaxZTCWGsGYf2PCa5YBMQTLohDnAQFcJMPw9cQhhEGBUYY9dCiZAEH4vQ4T6hzCGPEeudgvENHGK0Tw7Q9BJIcD0VJcSQkJNsKkqJiTclBPmKE5Yys1gbAkMPDg4tfZj04HPXO%2BdJCF2LqXNeEBcCEBIIWFqe8D6iOWAgTATAsDxA8QbSQEIaSWwhM7DQkgzCSH8N7RI/hLb6E4O7UgnsNY0n8FwfwptLYO38EbW2Cz/CNLwQHIOIctaiMjjHE%2BcdJ5Jyvjfbemc2CcGaCwNGZotpMBlNmLglsaRcBNhXKuJBa56HUU3VR0h1GKE0V3XQj8%2B5MAHlwupDS/a8HHp86es955tPBcAEuUKYXfg3qgLecQBkQjMPvZ54dj6nyZefbeydr68tvgKIwkKuA%2BxoLQF%2BwcIDvzwf/b%2B6CFWAOAaAhw6DIGMGgbAn%2BeCEFIJQbQNBXCMGCKMLg6W%2BAJLZOIVY6WZDkAUPQdQ2oXd6GMO/iwzY0t2GcM1jwvhmABFYPNWEUAXK%2BASIUNI2R8j0HIpUS3NFsgMWd20SAR%2BBgRH2KsIY917izEWKyFYmxBB0B2IMRYJxJKXG1xIaYzx2TvG%2BPSXkAJDB0B5IWGE9IETsitv8akXtsSynxMybUZJvQJgDvHd0AQU7%2BijvyZkopM6SmzCXd2ypKsal7x2fU0e9zmmUoLiKmlkLoUm3Xr06urKhmcqPqM8ZkzKB1L2QcqFyyzSJEtk7CEKy1mSHrsSmWnBHmhxeVHWO8cp4Cp%2BRnLOHBAUFxYAoNGxc0YXuxGMOFfTXFItkCipNbdU1aOlroCEpBcX4qHvuolTSOATwTgta4M854obQxhrDcIByMuZTvFqEIOWHwju8%2BDl8U5Cu3iAdDKRMqYcth%2BbDBAPyqE6JK6Vb8P5f0AUqnTQCQFgI1UyqBMC4F6swIg5BqCrGa0wUI71vArWENtaQ1Q5DgTOsEK6vB7qmFki9WwmufruFxEDcGoRYaXniKYFImRcjKQKN4Am5uEhk2CFI1ikAlGs3GErUY6IBaZZFumpwLYH0c2OOcXEVx9aPFZPqC4DtxTSCBLKGOntRQsgtZiVkLtoTG31AXS1hrOSN3teXeu6duRB0zBaP1hJ27qkt0JYe/2x6OPoeuApmkynr3woExrYTIzSBjImcMDxrt30ZqhRCCEiQ7ZAe9nds0py7nrcDrYJ5ImYqkBmYkeZjszTe1NpIG2XBzZmFua7CEa2SVgYfbrfd5d3vw8%2Bz95YPCMjOEkEAA)

## Links

- [Example](../../code/facilities/utilities/gly/implementation.hpp)
- [Source code](../../../conceptrodon/gly.hpp)
