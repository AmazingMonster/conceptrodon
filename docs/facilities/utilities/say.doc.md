<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Say`

<p style='text-align: right;'><a href="../utilities.md#say">To Index</a></p>

## Description

`Say` accepts a `Sail` operation and returns the operation via member `Sail`.

<pre><code>   Oper
-> struct { using Sail = Oper; }</code></pre>

## Type Signature

```Haskell
Say
 :: template<template<template<auto...> class...> class...> class...
 -> template<template<template<auto...> class...> class...>
```

## Structure

```C++
template<template<template<template<auto...> class...> class...> class>
struct Say
{
    template<template<template<auto...> class...> class...>
    alias Sail = RESULT;
};
```

## Examples

This function injectively maps a `Sail` to a type.
In the following example, We will create an overload set of `fun` using operations `Op_0` and `Op_1`.

```C++
/**** Operations ****/
template<template<template<auto...> class...> class...>
struct Op_0 {};

template<template<template<auto...> class...> class...>
struct Op_1 {};

/**** fun ****/
constexpr bool fun(Say<Op_0>) { return false; }

constexpr bool fun(Say<Op_1>) { return true; }

/**** Tests ****/
static_assert(not fun(Say<Op_0>{}));
static_assert(fun(Say<Op_1>{}));
```

If we only want compilers to perform an argument-dependent lookup, we can utilize `decltype` and `std::declval` to avoid defining the function body.

```C++
/**** gun ****/
constexpr auto gun(Say<Op_0>) -> std::false_type;

constexpr auto gun(Say<Op_1>) -> std::true_type;

/**** Tests ****/
static_assert(not decltype(gun(std::declval<Say<Op_0>>()))::value);
static_assert(decltype(gun(std::declval<Say<Op_1>>()))::value);
```

## Implementation

```C++
template<template<template<template<auto...> class...> class...> class Operation>
struct Say
{
    template<template<template<auto...> class...> class...Args>
    using Sail = Operation<Args...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGzSrgAyeAyYAHI%2BAEaYxCCSAKykAA6oCoRODB7evgHSaRmOAqHhUSyx8Um2mPbFDEIETMQEOT5%2BgTV1WY3NBKWRMXEJyQpNLW15nWN9A%2BWVIwCUtqhexMjsHAD0AFR7%2BweHR/tbJhoAgrv7ANQAkiwp9GyCTPXXB6cXV8c/x5/nZ3OBEwDwMwJMAGY3MDQa9MJDoSDHnCETDkeCoUwvEQAHR4yHYa7IAwKBR4nEEokksn4iGE4lMUnXADyKTiryyBMBY2IXgc1yETAAnoCTAB2KwXa7S65osHwqFylGKpHyhFY3G0%2BnU8mUhmk8nnYjABRcqUyrwZIwCph0a6QgAiLLZxA5AgRRpNurpkMlALFDt9oq%2Bv1DH0B3x21wAYnhiGNrthVKxHph3icI2Gs/9MzdWez6gp03t/kqMYjYeWywq3BrUN7tYyaRS6VSmw3uQRefzWQB9DT2iXiwMQv2A6uo1XKivomt1httg1axfNs3nHl8gjO3tcQdWANBi65vbXKheBjFnb/NAMMaYVQpYjXaKoTyn88QQUiqF9jQExZ7tcxCYAQawXlQYhKL6g6BkeFw3neD5Pi%2Bb5ngwn7CgifZcP%2BgHAaBxAXl2XgKhYMHBpcBzXAAKpgYxFuGFwzI4yC9k2cQEBADCoFuaEYd%2Bbi/lyQ4BosiyHuuTQsWxpIcdQH5flhKQ7sJ%2B4OmJEnHlmvz/JGAqYDe6CJsmoJpoxlHaaGOZHmYEJhMSXhYPaipCmyvZdraBCmj6cEWSewDnpe14CIhj7XHW1wBehik/spf50gBAC0lJjOgIAgBBtBKO5rmkRRCHAkh4XYqgkUKZhsUqQl1zJa2qXpcRmA5WymkhjctH0UFnYcqx7EtFxPHXFgxIELl0AfvVIDDbQABuYgIjFglxVydIQGJizpXN3iYOJo7ddJfWcdNo1suN6GTdNW0LRVS1VdgBJrWJm1iCRu0WBwyy0JwiS8H4HBaKQqCcG41jWNcCirOsabmBCPCkAQmgfcsADWICJJIOIaAAHGYZgAJx41wiTY1jXBimK0hfRwki8CwEgaBopB/QDQMcLwCggIzCP/R9pBwLAMCICAqwECk2LkJQaAPHQcQRKwmyqFj/iJYEkXIMg1xSDiZi8Jg%2BBEMQeBpVwMiCCIYjsFIpvyEoaiI6QugmwA7q6KScDwn3fb99us8y2Ji1uqBUNcivK6rwDq5rGNmNcEAeNL9BPjDXCLLw3NaMsEBIFLKQy2QFAQDnecgMAUhmHwdDAvGlDRPb0RhM0Qru7w9fMMQQrMtE2gGdzcNS88BDMgwtBNzzpBYNEXjALWtBZc348goYwDiGP%2BDAQ4eAzXR9v3gZ2KbHDYTAlTAO0Hg0Suu3HhYPbXZ4HT3C8FvxAvkoDqL0YZ9GIjyxUAYJoADU8CYCdvmP6cN%2BBm1EOIK2kCbYqHUGPR2%2Bgl4oFBpYfQ58OaQGWKgFIhZOCJVSo6UwlhrBmBZs/Q2WBsFrS6D3LILgGDuE8O0PQIQwiDAqMME2hRMgCEmH4Xh6R%2BEMDmEMeIJs7AMIEL0CYrC8hSNqDIho4x%2BicPmDw2wajBF6BmC0cR3DJHLAhmsDYEhPYcB%2BkzH2nAQ5KxVpINWGstYxwgLgQgJB7S2RTmnH%2BywECYCYFgeIdDUaSAhDiPGEIKYaEkGYSQ/gGaJH8HjfQnAaakDprDHE/guD%2BCxnjUm/h0ZE2if4GxY9Wbs05vDH%2BfNBZZ2Fv7cWBci6JzlmwTgzQWAzTFIlJgbZrRcDxjiLgmNdb6xIEbPQcDzYwOkHAxQCD7a6HLi7JgbtH6WOsczXgvsWmB2DqHRxQzgCa1GeMgccdUAJziN4iEZhU51J5pnbOtzc6JwloXD5xcGRGBGVwRmNBaBVw5hAWuY9W6N3ntC9undu4OHnv3Rgg9h6jwBhPKeM856PwXiwJeK9MVxgYVvDmY9d7IH3vPI%2BtR7Znwvo3a%2BmwAZ3wfnDZ%2Br9MDvwJZ/MIoBXl8H/goIBICwHzzmdAy2izZDLLtkgkA5cDDf1IVYDBDLaG4PwVkclRCCDoBIegiwFD9lUKNtvHB9CN7OAgK4XRJsOFlAkXoPh9R7WpBEfUQxCwlHdFkTohRQirX1Dkeop1Ri9EBtyEG/RYauE%2BpMZDcxKd0lWO9lUuxJzVb/POSMsZmNY4eINg83xLyM4BKCSEygljMnZNGXEsUiQ8bkwhPExJkgTZ7MBpwGpXN6n8yFiLAO3z2my3lt04gLBVYsAUDNDWM083yjGJMzx1DZmyHmdK62crEEA10BCUgGytke1Tbs2xHA/ai2xNcIOIdp2zvnYuuECYbl3KTrZCEzz068yaaO/OktfmJxAHOlIykF1417EuggvZVCdBBWCmudcG7t1hchjuXce7ItuQPIeI97ZYunmIXFcMsC8uXiy3ga9SXbwpaoPewIaWCDpWPBll8hTMtvobdlT84hcp5YS/l9S/5MEAcA0BbJwG8ElRbCQMrBA7tWSAA9yrjBGswdETVgNtUhU4FseqqryGULiNQi1dDpHWr8La5h7rHXxq0a6rI7qHMlA0c631KjQ3uvMyGtR3qtGxq8751zEaU2mKhhY096aWaZvvXO644GcRQcLVM99sMv3%2BNIIE4Jww6FU1rYq0ZEIISJGJh2hmRWxQFMqdFtmthanfrEqQcJiQolkzFAzLGkhCZcBxmYCpVMIRRf2T2stSNU062q8N2rDXljPwyM4SQQA)

## Links

- [Example](../../code/facilities/utilities/say/implementation.hpp)
- [Source code](../../../conceptrodon/say.hpp)
