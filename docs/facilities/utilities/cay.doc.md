<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Cay`

<p style='text-align: right;'><a href="../utilities.md#cay">To Index</a></p>

## Description

`Cay` accepts a `Calm` operation and returns the operation via member `Calm`.

<pre><code>   Oper
-> struct { using Calm = Oper; }</code></pre>

## Type Signature

```Haskell
Cay
 :: template<template<template<template<template<auto...> class...> class...> class...> class...> class...
 -> template<template<template<template<template<auto...> class...> class...> class...> class...>
```

## Structure

```C++
template<template<template<template<template<template<auto...> class...> class...> class...> class...> class>
struct Cay
{
    template<template<template<template<template<auto...> class...> class...> class...> class...>
    alias Calm = RESULT;
};
```

## Examples

This function injectively maps a `Calm` to a type.
In the following example, We will create an overload set of `fun` using operations `Op_0` and `Op_1`.

```C++
/**** Operations ****/
template<template<template<template<template<auto...> class...> class...> class...> class...>
struct Op_0 {};

template<template<template<template<template<auto...> class...> class...> class...> class...>
struct Op_1 {};

/**** fun ****/
constexpr bool fun(Cay<Op_0>) { return false; }

constexpr bool fun(Cay<Op_1>) { return true; }

/**** Tests ****/
static_assert(not fun(Cay<Op_0>{}));
static_assert(fun(Cay<Op_1>{}));
```

If we only want compilers to perform an argument-dependent lookup, we can utilize `decltype` and `std::declval` to avoid defining the function body.

```C++
/**** gun ****/
constexpr auto gun(Cay<Op_0>) -> std::false_type;

constexpr auto gun(Cay<Op_1>) -> std::true_type;

/**** Tests ****/
static_assert(not decltype(gun(std::declval<Cay<Op_0>>()))::value);
static_assert(decltype(gun(std::declval<Cay<Op_1>>()))::value);
```

## Implementation

```C++
template<template<template<template<template<template<auto...> class...> class...> class...> class...> class Operation>
struct Cay
{
    template<template<template<template<template<auto...> class...> class...> class...> class...Args>
    using Calm = Operation<Args...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGzSrgAyeAyYAHI%2BAEaYxCCSAKykAA6oCoRODB7evgHSaRmOAqHhUSyx8Um2mPbFDEIETMQEOT5%2BgTV1WY3NBKWRMXEJyQpNLW15nWN9A%2BWVIwCUtqhexMjsHAD0AFR7%2BweHR/tbJhoAgrv7ANQAkiwp9GyCTPXXB6cXV8c/x5/nZ3OBEwDwMwJMAGY3MDQa9MJDoSDHnCETDkeCoWiwfDMUjsQimF4iAA6UmQ7DXZAGBQKUnE8mU6m0skQilUpg0ukM9mcllspnXADyKTiryy5MBY2IXgc1zcTAAnoCTAB2KwXa6a65YlG42EYxH6nGG9HGnUGwkkvmMjnM%2Bmsm28%2B3821ch08u3nYjABQSjVarwZIxysQsa6QgAiQpFxDFAgRXp9buwkPVAJVEdTyq%2Bv1zH0B3x21wAYnhiGNrthVKxHph3icC3mm/9GzdhaL6gp63t/uazXjdSb8XrTaiBxaiahk467dymdOPQv53zJQRpbLhQB9DThtWqzMQtOAvtjo2n0cj4dDweWqfWxf35fOmdL10ri5SmUEaObri7qwZlmFytns1xUF4DDdjs/xoAwYyYKoKTENc0SoJ4YEQRA8pKlCW4aOSiz/tcxCYAQayQVQYhKKmu6ZsBFywfBiHIah6HgQwWGKgiW5cARREkWRxCQWuXg4hYtHZpcBzXAAKpgYxdvmH5NI4yCbracQEBADCoN%2B7GcThbh4RKe4ZosixAecMyqepNKadQmHYdxKS/iZAERuZlkgU2vz/IW1xCJgsHoJW1agnWSlST5uYtsBZgQmEVJeFg4aYgqIqbmuTCEL6rKSf5wAQVBMECExSHXLe1yFRxTm4S5%2BGsoRAC0DJjOgIAgJRtBKJl6ViZJjHAsxFWTlVjlcXVrmNdcLUOm1HUiZgvUil5OY3HJCnFauYpqRpLTabp1xYFSBB9dAmHzSAx20AAbmICK1UZ9USqyEDmYsHV3d4mAWYe202XtWnXadIrnRxl3XV9D0TU9U0pq972fWIom/RYHDLLQnCJLwfgcFopCoJwbjWNY1wKKs6x1uYEI8KQBCaOjywANYgIkkjEhoAAcZhmAAnLzXCJFznNcCqKrSJjHCSLwLASBoGikLj%2BOExwvAKCACv03j6OkHAsAwIgICrAQKREuQlBoA8dBxBErCbKonP%2BE1gRVcgyDXFIxJmLwmD4EQxB4O1XAyIIIhiOwUgh/IShqAzpC6MHADusYpJwPAY1jONxyrgpEqb36oFQ1wO07LvAG7Hvs2Y1xYagVv0Mh1NcIsvBa1oywQEglspNbZAUBA3e9yAwBSGYfB0MC5aUNEcfRGEzQKmnvBz8wxAKoK0TaEFWu05bzwEIKDC0Iv2ukFg0ReMA8q0N1S9nyChjAOIp/4CRDh4Dd8lxwhQVEpstNhGBJLfGtA8DRFjGvDwWA45rjwLLbgvBP7EFQkoCMD8jCgKMAzZYVADA%2BgAGp4EwIndsuNab8FDqIcQkcKHRxUOoU%2BCd9CPxQCTSw%2BgwHq0gMsVAKROycCam1SMphLDWDMMrJBAcsBcLel0beWQXAMHcJ4doegQhhEGBUYYwdCiZAEJMPwOj0h6IYHMIY8Rg52HkQIXoEwVF5EsbUaxDRxj9A0fMbRthXEGL0DMFoZitEWOWOTNYGwJAZw4NjRW2dODF0ds7SQrt3ae2rhAXAhASDhnis3Vu2DlgIEwEwLA8RZEs0kBCYkvMITiw0JIMwkh/Dy0SP4Xm%2BhODS1ILLGmxJ/BcH8JzXmIt/Bs0FlU/w0TT4qzVhrOm2DdYG07kbPOZt%2B6DwbrbNgnBmgsBuiqJqTAbTBi4LzYkXAOY%2Bz9iQQOehaFh2odIWhih6Fx10GPZOTBU4IIiVEpWvAc7LILkXEuCTDnAA9ics5O5a71ziFkiEZgW6zO1h3Ludce4N3NgPNFQ92RGGOVwBWNBaCT3VhAGep8V4LzvpSteG8t4ODvnvRgB8j4n3xufS%2B19b4IPviwR%2Bz92VlnkZ/dWp8f7ID/nfQBtQ46gPAQvKBmx8awPgbTJBKDMBoL5RgsIoBkV8DwQoQhxDSF31uVQiODzZBPNjowkAY8DBYJEVYdhcqZE8L4VkUVgiCDoGEWwiw4i/mSMDl/bhcj37OAgK4Hxwd1FlHMXoXR9RY2pGMfUAJCxHHdBsd4%2BxhiI31FsW4hNgTfF5tyAWvxJbNFZuCRTMJzc2mRKzpM2JwKXa4rBcc05HMa7pP9nCnJSL275MKcUygESOldJObUlUiReZiwhHUhpkhg6/IJpwaZms5l60NsbfOmK1k2ztls4gLAXYsAUDdd2N0e3YjGBcjJUibmyDuZaqONqGH410BCUg7zPnp2bT8mJHBc4myJNcQuxdL3XtvfeuEFZoXothdTCEiK2460WcevuFtsUNxADelILk72803A%2Bggm5VCdCJSS6es955r2pYx9em9t6MrrvvQ%2Bx844cqvmIbltMsDaqfkq3gr9hVfzFaoX%2BwIpWCBlafOVECFSKpgQHVViC4gaq1fy3VczcFMAIUQkhIoyG8HNeHCQVrBBfpeSAP9jrjABo4dEd1BNPWlU4FseazqxESLiFIsNsirGRr8NGpRqb421s8cmrIqa4slHcYm7Nzji2ptC0W1xmbPHVoy9l5LZam0hMpuE4Drblbttgze64pHiQUf7Zcxu2SMN5NIAUopwxZGS2nfak5EIISJCFmu%2BWA2VT9ImZV1WtgZmYfMqQMpiRKmixVPLTmkgBZcG5mYcZksIQVb%2BVukdjNm3e0m4d6bc3lhIIyM4SQQA%3D)

## Links

- [Example](../../code/facilities/utilities/cay/implementation.hpp)
- [Source code](../../../conceptrodon/cay.hpp)
