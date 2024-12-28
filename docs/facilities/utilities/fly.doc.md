<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Fly`

<p style='text-align: right;'><a href="../utilities.md#fly">To Index</a></p>

## Description

`Fly` accepts a `Flow` operation and returns the operation via member `Flow`.

<pre><code>   Oper
-> struct { using Flow = Oper; }</code></pre>

## Type Signature

```Haskell
Fly
 :: template<template<template<typename...> class...> class...> class...
 -> template<template<template<typename...> class...> class...>
```

## Structure

```C++
template<template<template<template<typename...> class...> class...> class>
struct Fly
{
    template<template<template<typename...> class...> class...>
    alias Flow = RESULT;
};
```

## Examples

This function injectively maps a `Flow` to a type.
In the following example, We will create an overload set of `fun` using operations `Op_0` and `Op_1`.

```C++
/**** Operations ****/
template<template<template<typename...> class...> class...>
struct Op_0 {};

template<template<template<typename...> class...> class...>
struct Op_1 {};

/**** fun ****/
constexpr bool fun(Fly<Op_0>) { return false; }

constexpr bool fun(Fly<Op_1>) { return true; }

/**** Tests ****/
static_assert(not fun(Fly<Op_0>{}));
static_assert(fun(Fly<Op_1>{}));
```

If we only want compilers to perform an argument-dependent lookup, we can utilize `decltype` and `std::declval` to avoid defining the function body.

```C++
/**** gun ****/
constexpr auto gun(Fly<Op_0>) -> std::false_type;

constexpr auto gun(Fly<Op_1>) -> std::true_type;

/**** Tests ****/
static_assert(not decltype(gun(std::declval<Fly<Op_0>>()))::value);
static_assert(decltype(gun(std::declval<Fly<Op_1>>()))::value);
```

## Implementation

```C++
template<template<template<template<typename...> class...> class...> class Operation>
struct Fly
{
    template<template<template<typename...> class...> class...Args>
    using Flow = Operation<Args...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGzSrgAyeAyYAHI%2BAEaYxCCSAKykAA6oCoRODB7evgHSaRmOAqHhUSyx8Um2mPbFDEIETMQEOT5%2BgTV1WY3NBKWRMXEJyQpNLW15nWN9A%2BWVIwCUtqhexMjsHAD0AFR7%2BweHR/tbJhoAgrv7ANQAkiwp9GyCTPXXB6cXV8c/x5/nZ3OBEwDwMwJMAGY3MDQa9MJDoSDHnCETDkeCoQQAJ4pRisTAAOiJkOw12QBgUCiJBJJZIpVOJENJ5KYlOuAHlccRXlkSYCxsQvA5rgAxWhYwEmADsVgu13l1zRYPhmKRytRapRmJxeLY1NpLMp%2BqZdNZDIJ52IwAUfLlCq8GSMotoqAA7tdIQARDlcnkCBGW63G7CQ2UAqWe0OSr6/WMfQHfHaivDEMbXbCqViPTDvE4JuMF/75m6cuJ%2BhgKXN7f5KrWI2EY%2BvolXQnXMPWM5n04Omo2d/kEQXCzkAfQ0Hpl0sjELDgNrjfnLcXqLb%2BJ7hvNBu7/YuAqFBB9I64E6sEajF2Le2uVC8DCrO3%2BaArwNUKWI12iqE819vEDFEqhUcNBJRYT2uYhMAINY7yoMQlFDCdIwvC4nzGTBX3fT9vxvBg/3FBFRy4ECwIgqDiDvQcvBVCxEOjS4DmuAAVTAxkreNdyaRxkBHM04gICAGFQA8cLwgC3CAvlJwjRZFnPc4Zi4njKT46hf3/AiUiPSTT09GS5MvAtfn%2BRNriETAn3QdNM1BHN2PowzYyLC8zAhMJyS8LAPW1XER0HJhCBtJk6JM4Bb3vR8BDQjDriYLwiGuULcPUwDNOAplQIAWlpMZ0BAEBYNoJRfJ1fSUMil83xiuLUAStT8JSrT0uuLKTRyvLKMwYrcVK%2Byr2Y1jwoHHluN4loBKE64sHJbFcWgX82pAKbaAANzEBFkvE1K%2BSZCAZMWPLVu8TBZJnIbFNG/ilpmzA5twhalsO9b6s2xqQx2vaDrEKiTosDhlloThEl4PwOC0UhUE4NxrGsa4FFWdYc3MCEeFIAhND%2B5YAGsQESSQCQ0AAOMwzAAThJrhEkJgmuClKVpABjhJF4FgJA0DRSBBsGIY4XgFBAdm0dBv7SDgWAYEQEBVgIFI4vISg0AeOg4gifFOFUAn/AywIEuQZBrikAkzF4TB8CIYg8FyrgZEEEQxHYKRrfkJQ1HR0hdCt11uRSTgeH%2BwHgdd7n2TimWD1QKhrnVzXteAXX9bxsxrggDxFfod8ka4RZeEFrRlggJAFZSJWyAoCBC%2BLkBgCkMw%2BDoYFU0oaJXeiMJmixH3eBb5hiCxdlom0czBZRhXngIdkGHFV2sGiLxgDcMRCo70gsBYQxgHEIXl5TQe8GWljXfQ8y4s2FGwmBBmwdoPBom5HuPCwV3BzwFnuF4PfiE/JRPRBNer6MdHlhUAMNaAAangTArpSwgxRvwG2ohxAO1gU7FQ6hN7u30GvFA0NLD6GvnzSAyxUApHqHzDgGUcpelMJYawZgubv3NlgfBu0ug72cBAVwkw/BWxCGEQYFRhhW0KJkAQnC9BCPqHMIY8QrZ2FYQ0cYrRPDtD0LIhwPQFGSP4dI2wCjREyI0bw%2BYAjlhwzWBsCQfsOBAw5oHTgkcNZa0kDrPWBtE4QFwIQEgHoXKZ2zgA5YCBMBMCwPEZh2NJAQgJCTCEdMNCSDMJIfwbNEj%2BBJvoTgTNSAs2RgSfwXB/AExJtTfwuMKbRP8DYze3Neb81RgAkW4t86SxDrLUu5c04qzYJwZoLBlpSgykwU0TouAkwJFwfGxtTYkAtnoJBtsEHSCQYoFBrtdA109kwb2r9LHWM5rwIOLSw4Ryjo4oZwB9ajPGeOZOqBU5xG8RCMwWc6lCzzgXW5Rc05yzLh8iuLIjAjK4OzGgtB658wgE3TeXc25L2hT3PuA8HBLxHowMeE926b2nrPeetBF6v2Xj/IwG8wb4AgmovepCwaH2QMfJeZ9aiuyvjfNu99Nhgyfi/FG79P6YG/qvIlYRQCvL4MAhQYCIFQKXnM%2BB9tFmyGWS7NBIAa4GH/lQqwOCmVMMIcQrIpDyEEHQJQ7BFhaH7PoRbfeBCWFqLYRwpReRuEMHQJohYgj0jCOyA6rhqQPUSMMVIlRtQ5G9AmN6oN3QBChv6AGrRKjdHhv0bMWNbqTHw3MZndJViA5VLsSc7W/zzkjLGfjJOHizYPN8S83OASgkhMoJYzJ2TRlxKlIkEmtMITxMSZIK2ezwacBqQLeposJZS1Dt89pytVYcB6drFgChlp62WsW5UYxJmeIYbM2Q8zZWOwVagsGugISkA2Vs32Wbdm2I4MHaWcVrjh0jvOxdy7V1wjTDcu56cXIQmeTnYWTSp0l3lr8tOIAl0pE0iukmI410EBHKoToIKwWN2bq3HusL0O937oPZFtzR7j0npizAM854L1ISjFev82W8FJTvClB9VBH2BHSwQDLN5MtvliVlj9zacrfnEHlfLf6CvqUApgoDwGQNxNA3g0q7YSDlYIA9qyQAntVcYE1uDojavBrqyKnAthtXVTQuhcQGFWuYao%2BoLhnV6NIDwsogb3VFCyPZ8RWRXUCJtfUaN9nrPqOTU5uNSaw25B9TMFoXnpFprMfbHZOauZ5ufUu640GCRwbLVM79yM/3%2BNIIE4JwxmEMybcq0ZEIISJEpr2tmlWpQFMqUlnmthan/pkqQcJiQok0ylGzAmkhyZcCJmYCpDMISJf2YO6tGMs1Gya1Nlr7XljvwyM4SQQA%3D%3D%3D)$Done$

## Links

- [Example](../../code/facilities/utilities/fly/implementation.hpp)
- [Source code](../../../conceptrodon/fly.hpp)
