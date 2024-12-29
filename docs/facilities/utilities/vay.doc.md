<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Vay`

<p style='text-align: right;'><a href="../utilities.md#vay">To Index</a></p>

## Description

`Vay` accepts a variable and returns the variable via member `value`.

<pre><code>   V
-> struct { Vay = V; }</code></pre>

## Type Signature

```Haskell
Vay
 :: auto...
 -> auto
```

## Structure

```C++
template<auto>
struct Vay
{
    static constexpr auto value
    {RESULT};
};
```

## Examples

This function injectively maps a variable to a type.
In the following example, We will create an overload set of `fun` using values `0` and `1`.

```C++
/**** fun ****/
constexpr bool fun(Vay<0>) { return false; }

constexpr bool fun(Vay<1>) { return true; }

/**** Tests ****/
static_assert(not fun(Vay<0>{}));
static_assert(fun(Vay<1>{}));
```

If we only want compilers to perform an argument-dependent lookup, we can utilize `decltype` and `std::declval` to avoid defining the function body.

```C++
/**** gun ****/
constexpr auto gun(Vay<0>) -> std::false_type;

constexpr auto gun(Vay<1>) -> std::true_type;

/**** Tests ****/
static_assert(not decltype(gun(std::declval<Vay<0>>()))::value);
static_assert(decltype(gun(std::declval<Vay<1>>()))::value);
```

## Implementation

```C++
template<auto Variable>
struct Vay
{
    static constexpr auto value
    {Variable};
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGxcpK4AMngMmAByPgBGmMQgAMwAHKQADqgKhE4MHt6%2BAUEZWY4CYRHRLHEJKbaY9qUMQgRMxAR5Pn6BdQ05za0E5VGx8UmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnhzsmGgCC%2B4cA1ACSLGn0bIJMjbdH51c3p3%2Bn30uF0uBEwTwMoJMiTcTC8RFuADVWngmDF6FDsMCJsQvA5EUwAJ7AkwAdisV1ulNuc0cyFuaAYE0wqjSxFusPhADcxF5MMCqbdSRYkcQUWi%2BSSACJQ8lAqUy4k/f7Kr7A357W4AMTwxAmt2wqlYz0wnzOapVFsB5ruVC8DFNB0BDKZLLZMVQnlutoYECRROhGgxy0FZNuxEwBA29qoYiUMpD0quwOdoNdt3dnu9vsJULcXCDIYsYYjUduBBxfMSRdJiaBSruABVMBMFA69oCaXhkAB9JgKJRtCAMVAEL127P%2BtyBxKYsk15bLBVXTs9vsDgjUcd%2B3P5mdC%2BeLquK64Wy3Wg63ISYBnofWG8Em1X10//K1JsyJcLIbxYQXQggEmkmDduWTCEAoGLHuqtzAHabZOgILqsuycKoDBW45gGBYALQYtSBDoCAIAxrQSggYBlaysmiGpshHJobBPrbtCu7YMGuEzvhhEgOWvLkUBS51iejbNgQrZPpcK69v28QbsOo5YN%2BAFAdA44TNxim0NytC5sxU6QTOEALssRHabyh6ylJa6yRAmnKZgqk%2BupRGadpumYXmBnYEZC6mTymAWRwqy0JwACsvB%2BBwWikKgnBuNY1jUusmwmuYiQ8KQBCaEFqwANYgKFkgAHQaMkZhmAAnBVXChaVyRcCSJLSCFHCSLwLASBoGikJF0WxRwvAKCA3VZVFQWkHAsAwIgIDrAQaRwuQlBoE8dDxJErDbKoyT%2BNh/iSDByB0lIRVmLwmD4EQoqEUE/CCCIYjsFIMiCIoKjqGNpC6EEADuxBMGknA8MFYURdlMWcAA8nCC2jqgVC3Ntu37Ydx3FWYtwQB4q30GyaVcMsvCjVoqwQEgK1pGtZAUBAFNUyAwBSGYfB0KCuqUDE4MxOErQEkDvDc8wxAEpDMTaNeo0ZStrwEJDDC0Hzn1YDEXjADCtCkfzpBYCwhjAOISs6hLeCcs24PMtecLbBl4Sgi10W0HgMT/cLHhYOD5Z4B13C8KbxDukokpgnrjtGNlqxUAYwAKAieCYD9kNAZFGV3cIojiM9qdvWo4PffoesoAllj6E7Q2QKsqBpI0Q0cNh6lQpKpiWNYZh9X711m%2BXPTG84ECuNMfhBKE4TDFUoxFJk2QCAPejFFPDALCMCRBHYPdNJM7SeJ0eirw4fQb4vY/L7YG8zyvB8j4s4%2BrAoyVbBIIMcOFPXg/1iM7XtB3AEdtwnRjEC4EICQQUH4CZE3DqsBAmAmBYASEZUg%2BVJCJCKhVRITUNCSDMJIfwXVQr%2BAqvoTgbVSAdXSkVQI/hkgVXqv4QqNVUH%2BBfp9fqg1hqZXDhNaaZNZow0WjTOmuMNpsE4K0FgnISTYSYPSAwRhf4VSKlwEq51LokDwDdF6adHoSGkFnJQOdPq6GZn9AG/NH7P16rwfq0N5pwluPDd%2ByMDrfj1nIhRJVMbY0prjEBiQzCE3YWNUm5NUA43iEtWmISvGjGcUYLg1Vuo0FoGzIaEBOafUFrzLWGThai3Fg4LW0tGCy3loraKytVbq01j7bWwcjAGzKUbPepsa7RQtsgK2Wtbb1HBo7Z2vM3bbGip7b2GU/YB0wEHXWdTwigECXwKOMc44JyTlrVOD0M46NkNnD60VDH5zDk3Kwxdell3gZXaunA64EQboclubd4gd1OTfeoa8XAMHcFvAoQ93mHyWBPEoOQz7pEno0X549u57wEP0KYnzB4QsaNCwYl8l471PrC1F8xkVHwfmsDY98CaEKfmDZhnAHGf2kS4uJbiNCY0AVdHxYCAkk0gdA2BlBH7ENIfIjBJJQoVUaokTB2DJBBAsRDAatg2HE3GpNGac1YbhIEetTaIjiAsBRiwBQnI6ScipRCUSyigHXT0Gs9OT1NmvT0TsnQSRSDGMBj7MxxK%2BpQ14XDBGqgNVap1Xq94okPGRKpj4xI/jpVBJQIG3GirI2jG1WkNI3ZdUVW7PqiY3ZPU6NZvEFJaTorZMVhlfNuSJYFJCTLOWCtwblLVmIKpGUdYh0GbwfA4Ymlm0%2Bm0jp1Sun214L0l2BIBke1FCM328RxmTJDjMjhkcmDR1jvHROjBVmyHWeajR2zc62pkcYIuNgTnwArlXHINcdjOVuZYVulj25qM7vA3ejQ3kfPyHC4eFQUX/PnkCueoKsV/PhfvAYQKH2AbaGC4%2BcwYUvoxWBv919cUpRxS1cxr9SUZtuJq7Vtwk1FVTaOABKi8agNDRA0gUCYGjHgS1TlIBKpFUSIkUKtURVdQYySShTCXUSqGiNUjiDQooIaiSLqyRJDVS4GVMwjCWqJGdZYzg4DAmPzOpx%2BTEqw2rD9lkZwkggA)

## Links

- [Example](../../code/facilities/utilities/vay/implementation.hpp)
- [Source code](../../../conceptrodon/vay.hpp)
