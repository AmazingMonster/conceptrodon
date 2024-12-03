<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Day`

<p style='text-align: right;'><a href="../../index.md#identities">To Index</a></p>

## Description

`Day` accepts a `Dawn` and returns the `Dawn` via member `Dawn`.

<pre><code>Dawn -> Dawn</code></pre>

## Type Signature

```Haskell
Day ::   template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...> class...
           -> template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
```

## Structure

```C++
template<template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...> class>
struct Day
{
    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
    alias Dawn = RESULT;
};
```

## Examples

This function injectively maps a `Dawn` to a type.
In the following example, We will create an overload set of `fun` using operations `Op_0` and `Op_1`.

```C++
template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
struct Op_0 {};

template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
struct Op_1 {};

constexpr auto fun(Day<Op_0>) { return false; }

constexpr auto fun(Day<Op_1>) { return true; }

static_assert(not fun(Day<Op_0>{}));

static_assert(fun(Day<Op_1>{}));
```

If we only want compilers to perform an argument-dependent lookup, we can utilize `decltype` and `std::declval` to avoid defining the function body.

```C++
constexpr auto gun(Day<Op_0>) -> std::false_type;

constexpr auto gun(Day<Op_1>) -> std::true_type;

static_assert(not decltype(gun(std::declval<Day<Op_0>>()))::value);

static_assert(decltype(gun(std::declval<Day<Op_1>>()))::value);
```

## Implementation

```C++
template<template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...> class Operation>
struct Day
{
    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...Args>
    using Dawn = Operation<Args...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGwAnKSuADJ4DJgAcj4ARpjEIADMABykAA6oCoRODB7evgHBmdmOAuGRMSzxiam2mPZlDEIETMQE%2BT5%2BQfWNuS1tBBXRcQnJaQqt7Z2FPZODw1U14wCUtqhexMjsHASYLOkGeyZJbnsHR5gnZ/uHTMen53cPNxf3V4%2B3l9dP359vLyYXiIADowSdsABqZAGBQKMEgiHQ2Hw8FJKEwphwhFIzHYtEYlE49HIrGoxEkvEKSEAeXSCXuuQhJg0AEFJsQvA5IQARJgAT3QxEwrBZrJMAHYrGzIbLIb93j8vor/s8Pq81UqAeqFS9deqgaCCaT8RTCWTiebTbiicaqZaTeTWcRgApmTK5V5skZeUwAO4MSEnHm0%2BnERkCa7O12Wk7S8USnlxsVigD0ACpM1nsznU2ns5CACrYISFoSQ7N5tkZnO1rNV8Vs/VazWqv4a9vNtsqjs9w2oB32u22s2Owcjm0W4dTs1ijlcgihgD6GiDUslSaS8bFXd7euV%2B%2B1Lc7B51p%2Bu/fHM8n1spE7v14ft6t5Pd7IInO5dKXXDXVkTyZsvmWaQgAYngxCTEWmBQZWKZsmgDCTJgqjpMQkL9pCVBeAwEB8oKwqiqc34aBCKx/pCwoEJsgZUGIShxmuSZAQhAjIah6GYdhuH4UKIosNc35cGRFFUTR8qch8FhMfB76MsgS5kgkBAQAwqCLtxeECnxRFuCRzLromKwrIBjZyY4ClKe01A4VpBH8YJ6Q/gZ/48sZpnAZmkJCJgiHoNBsH1rJ5hJBEMJeFgQanMCdCEPyb5ioh7FoRhwKoJCwC2bxhECcRTmkei5EALRIpM6AgCAdG0EoS4EPy9IeaxSF7BxqVEBlWXaTljnOYVkIlSSZUVR%2BXiYLV9VSbJ8wWYpcLKap6mQlgMJ1fS0C2UNIDLbQABuYjXNlDl5SuzLohAxkrBVe3eJgJlblNrQzVZKnbatmDrbhm3bddB1dUdelOcJ6IQudxlXWIo13RYHBrLQnAAKy8H4HBaKQqCcG41jWJCCgbFsmBBmYSQ8KQBCaDDawANYgPDkgghokhcBKSQaPDGhmP4/hmCkaRwxwki8CwEgaBopDI6j6McLwCggKLZMozDpBwLAMCICAGwEOkwLkJQaAHHQCRRKwOyqCk/hFf4kgZcgyCQlIIJmLwmD4EQxB4OVXAyIIIhiOwUhe/IShqOTpC6J7frhuknA8LDCNIyHks0sCWuLqgVCQqb5uW9btv22YkIQB4%2Bv0OhIVcCsvDy1oawQEgevpAbZAUBA9eNyAwBSGYfB0HskGULEIexBEbT8tHvBD8wxD8jSsTaL58sk3rbCCDSDC0KPCukFgsReMAbhiNVY9b/shjAOIm/4MKDh4DtMEhyhvnAjsJMRHsfOo7QeCxOGU8eFgIcfjwELbgvBb7EFiFkTAPIT5GE/kYcmawqAGFdAANTwJgP0dJGBH34N7UQ4h/a4MDiodQm8w76FPigLGlh9BfxlpANYqB0hNBlhwIqZVgymEsNYMwEswFuywPQ86vR565BcAwdwnguh6DCBEEY1QxiexKDkAQMw/BKKyCohgixRiJE9nYURAgBjTCkYUfRDRDHNCmEMORSxFG2GsWovQ8x2g6IUXotYuNNjbAkLHDgiMxYJ04BnM2FsrbABtnbOm%2BcIC4EICQQmxMK6kwQWsBAIosCJGEdTSQSQQSBCSBKSQDMzCSH8CLeGPQ%2BYC1IELYmIJ/BcH8CkQIKQmm0y4PDAp/hAmb0ltLWWKSFY11VrXdWydtbN1biXI2bBOBtBYDtCURUmCkh9FwQIIIuD0ydi7Eg7s9BEJ9gQ6QRDFAkJDroLuEcmBRxAX4gJ4teCJwmandOCylkrLWcAO2mztmrkLqgYuCRElmGSVXRWYzpkJB1i3IFDcS4gA%2BcszERgNlcFFjQWgvcZYQAHpvCeI8j6EqnjPOeDgj5L0YAQVe68Q7b13vvWgh8QHHxYKfc%2BqNL6iNvqw1GD9kBPyPq/BoIdP7fxHn/HYqNAHAJJmAiBShoHstgREUAwy%2BDIIUGgjBWDkYkyOfgv2pzZDnODmQkAXcDDwK4VYGh4qhGMOYbkVh7CCDoE4dQiwvDnn8PdnfBhIjr7OAgK4JxntZGVF0XoZRTRw0ZE0U0NxyxzF9CMY40x6ig1NGMTYqN7jnEZoKFmlxeb5Eps8XjHx5d9Bx16RLYJyKvmop%2BRsrZ9MC5xNdok8uldUmkHSUwTJlA/E1LqZshmEoukSmZpIUpltPZPLRpwAZcsEFK1GUgDWKdYXQuILMnYCzs4sAUDtW2O022XEmLs%2BJAjDmyGOcagOZrSGo10EkUgNy7kx1rf4%2BOfTOBJ01sCSEacMLEBYMe0957L3vCgoC4FpciZJHBeuqF8LG67ow4is96QnIXsCEuK9BBFIQctt3bFCRcX4tRiSjeJM6NkvnpSoFy8aVrw3lyzAO894H1YSTLAKqz7St4Ny6%2BvL76qEfnsYVghRWb3FT/fkUqAFuzlaAhIiqoEwLPmq9dSCmCoPQZg%2Bk%2BreCGt9hIE1ggX2XOSBQm1XraGxEdWjZ1bFOCpiGranhfCEgCIDcIgxwa/ChokfGyN5b7GxtyPGmL5RbHRtTZY3N8bgs5uscm%2Bxpa0uZcSwWmtXj8a%2BN/Y8oJHBwOQaties9kICMgmI52vZSGkl9uGWkjJYxhHVMFpazZSQkjwzZozEWA2JTNPrc8ldthBkQuMqQHJ8N8nwxSBzQIkhAjM0KVwD9fMkj/obVLIZ1c/GO0m8uo7c21hgOyM4SQQA%3D)

## Links

- [source code](../../../conceptrodon/day.hpp)
