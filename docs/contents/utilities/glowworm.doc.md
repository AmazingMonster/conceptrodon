<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Glowworm`

<p style='text-align: right;'><a href="../../index.md#identities">To Index</a></p>

## Description

`Glowworm` accepts a `Glow` and returns the `Glow` via member `Glow`.

<pre><code>Glow -> Glow</code></pre>

## Type Signature

```Haskell
Glowworm ::   template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...> class...
           -> template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
```

## Structure

```C++
template<template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...> class>
struct Glowworm
{
    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
    alias Glow = RESULT;
};
```

## Examples

This function injectively maps a `Glow` to a type.
In the following example, We will create an overload set of `fun` using operations `Op_0` and `Op_1`.

```C++
template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
struct Op_0 {};

template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
struct Op_1 {};

constexpr auto fun(Glowworm<Op_0>) { return false; }

constexpr auto fun(Glowworm<Op_1>) { return true; }

static_assert(not fun(Glowworm<Op_0>{}));

static_assert(fun(Glowworm<Op_1>{}));
```

If we only want compilers to perform an argument-dependent lookup, we can utilize `decltype` and `std::declval` to avoid defining the function body.

```C++
constexpr auto gun(Glowworm<Op_0>) -> std::false_type;

constexpr auto gun(Glowworm<Op_1>) -> std::true_type;

static_assert(not decltype(gun(std::declval<Glowworm<Op_0>>()))::value);

static_assert(decltype(gun(std::declval<Glowworm<Op_1>>()))::value);
```

## Implementation

```C++
template<template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...> class Operation>
struct Glowworm
{
    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...Args>
    using Glow = Operation<Args...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGwAnKSuADJ4DJgAcj4ARpjEIADMABykAA6oCoRODB7evgHBmdmOAuGRMSzxiam2mPZlDEIETMQE%2BT5%2BQfWNuS1tBBXRcQnJaQqt7Z2FPZODw1U14wCUtqhexMjsHASYLOkGeyZJbnsHR5gnZ/uHTMen53cPNxf3V4%2B3l9dP359vLwIAE90oxWJgAHRQk7YADUyAMCgUUIhMPhiOR0KScIRTCRKLRuPxWJxGIJ2PReMxqIpRIUsIA8qDiPdcjCTBoAIKTYheBywgDitFQAHcRSQWBzOSYAOxWLmwxWw37vH5fVX/Z4fV5atUA7UqwHqwEgsFscmkqkWynEmmW22Eskkm3Ux1WqGc4jABTshVKrzZIyC4Ui2EnAAijOZrIE1093otJ3l0pl4aTUqlAHoAFS5vP5guZrP52EAFWwQlLQlh%2BaLXJzBcbebr0q5hoNxo7%2Br1us1fx1/fbP1NzHNzrp1on46ddpdk5nbod2KlPL5BCjAH0NGG5bK00lk1Kh32NQPT8ez0buyeTaDR5Dp%2B7Z1PnwvaW/7a730/fdyCLz%2BSZDcuB3KxU3TLlizzWEADE8GISYy0wRDawzLk0AYSZMFUdJiFhJgvCIWEqC8BgICFUVxWISVTiAjQYRWUDYWITACE2BhiLEJQkx3NNIPQgQsJwvCCKIkiyIosUJWuICuAYpiWLY4gOP/LwPgsXi0L/VlkA3KkEgICAGFQddxPIkMqJotw6PZXdUxWFYINbbTHF0/T2moUjzMo6TaPSYDbLA8MHKcqDc1hIRMAw9AkJQ5stPMJIIgRLwsDDU5CLoQggV/KUMKE3D8MI1BYWALzJMsmT/Po7FGIAWjRSZ0BAEAqC4zAN2BUFQoEzC9mEoqiLKiSLN86z/Lk2rYQaikmpa1SOq69StPmVy9KRAyjJM2EsARJboC8uaQF22gADcxGuCqxps5dsQgByVha87vEwRyDxW1o1vcwyTv24aICOk7nsu0bqKqgLbuwe6HKesQ1LeiwODWWhOAAVl4PwOC0UhUE4NxrGsWEFA2LZMDDMwkh4UgCE0JG1gAaxAVHJAhDRJC4GUkg0VGNDMfx/DMFI0hRjhJF4FgJA0DRSEx7HcY4XgFBAaWaaxpHSDgWAYEQEANgIdJCPISg0AOOgEiicFOFUFJ/Dq/xJFK5BkFhKQITMXhMHwIhiDwZquBkQQRDEdgpAD%2BQlDUWnSF0f2RRZdJOB4ZG0YxqP5YZQiDfXVAqFha3bftx3nddsxYQgDxTfoPDEq4FZeFVrQ1ggJATfSM2yAoCBW/bkBgCkMw%2BDoPYEMoWIo9iCI2iBRPeAn5hiCBBlYm0KLVapk22EEBkGFoae1dILBYi8YA3DEWgle4XgsBYQxgHEff8BYhw8FO5Co%2BwqLCJ2KmIj2EXsdoHgWILIF4eCwFHf8eAJaX1IK/YgsQsiYHDPsW%2BgCjC0zWFQAw3oABqeBMAiiZIwGeYcg7iFDvwQQigVDqH3jHfQt8UAE0sPoIBStIBrFQOkJoF86pNQjKYSw1gzByzgT7LA7D7q9FXrkFwDB3CeC6HoMIEQRjVDGP7EoOQBAzD8JorI2iGCLFGIkf2dgZECAGNMRRhQzENAsc0KYQxVFLA0bYJxui9DzHaMY9Rpi1jE02NsCQycODoxlmnTgecbZ2wdsAJ2LsWalwgLgQgJByaUzrtTDBawECYCYFgRIUjGaSCSBCQISQZSSDZmYSQ/gpaox6CLMWpAJaUwhP4Lg/gUiBBSF05mXBUYVP8BE/e8tFbK2yWrJu2tm660zobTu3cq4WzYJwNoLBToyjqkwSkQYuCBAhFwVmHsvYkF9noShwhRDkOkFc6hkc6EgAHnHJgCdL6hPCbLXg6cFnZ1zhsrZOy9nABdoc4525y6oErgkDJZgskN3VnM5ZCQjZd2hW3KuIBAXbNxEYA5XBpY0FoMPJWEAx77znlPEhVKF5LxXg4EhG9GAEG3rvKOh9j6n1oOfEh19UE7Gxo/GRr8L7Yw/sgL%2BJDf4NCjoA4BU8wGCvrj7aBVM4EIKUMgm%2BRg0GgGmXwbBCg8EEKIZjKmVyyEhzubIB5tDsa6AHgYdBgirAsPlZIzh3Dci8P4UkcMrrhGiISOIt%2BHDpHP2cBAVwnj/YqMqCYvQWimixoyAYpovjlh2L6JYjxNi9ERqaFY5xCa/FeLzQUAt3iS1qKzQEkmwTa76BTqMuWUScXArxaCg5RzWZl1Sd7DJtd645NIHkgpYwpHNPFskQ5bMZRDJlJzSQtT7b%2B2%2BTjTgEyVYYI1rMpAess5opRcQVZOwNmFxYAoU6ztTo9suJMU5aTxGXNkFaiQNqqER3tToZIpBXnvKTs2sJqcxmcAzvrQisIc74Wope69t773vEQlCmF1cKZJARbu5FGL27Htw1im96R/J3sCBuB9BA9JwbuUPBIZKKXY1pXvKmTH6WryZdCzerKd57yFZgI%2BJ8z4Xypvy3VyqD7wRFW/feEqpUwJlf/Xg8qQFAiVRA1VJCNWIO1agiI%2BrG6GqYLg/BhC7wkMtTc61Yc7VR10EkBhLrmE2A9fAL1PDOCZjmoGywIifliN9mGqR5jI1%2BGjfI1N8ba1uOTbkVNMXyguMTdmhxxbU3BaLU4zNbjq1pcy4lstTbAmkxCcBr5kSOCwZYPBm9sJSMQgo/2s56HMkjumbk/JhTKChJaRLMwhykhJFRjzdmUsBsym6a2n5W7bCTMRQ5UgJTUblNRikPmgRJCBE5pUrg9mRZJFA22hWUzG6hPdpNzdR25trDgdkZwkggA%3D)

## Links

- [source code](../../../conceptrodon/glowworm.hpp)
