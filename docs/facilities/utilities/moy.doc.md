<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Moy`

<p style='text-align: right;'><a href="../utilities.md#moy">To Index</a></p>

## Description

`Moy` accepts a `Mold` operation and returns the operation via member `Mold`.

<pre><code>   Oper
-> struct { using Mold = Oper; }</code></pre>

## Type Signature

```Haskell
Moy
 :: template<typename...> class...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct Moy
{
    template<typename...>
    alias Mold = RESULT;
};
```

## Examples

This function injectively maps a container to a type.
In the following example, We will create an overload set of `fun` using containers `Con_0` and `Con_1`.

```C++
template<typename...>
struct Con_0 {};

template<typename...>
struct Con_1 {};

constexpr auto fun(Moy<Con_0>) { return false; }

constexpr auto fun(Moy<Con_1>) { return true; }

static_assert(not fun(Moy<Con_0>{}));

static_assert(fun(Moy<Con_1>{}));
```

If we only want compilers to perform an argument-dependent lookup, we can utilize `decltype` and `std::declval` to avoid defining the function body.

```C++
constexpr auto gun(Moy<Con_0>) -> std::false_type;

constexpr auto gun(Moy<Con_1>) -> std::true_type;

static_assert(not decltype(gun(std::declval<Moy<Con_0>>()))::value);

static_assert(decltype(gun(std::declval<Moy<Con_1>>()))::value);
```

## Implementation

```C++
template<template<typename...> class Container>
struct Moy
{
    template<typename...Elements>
    using Mold = Container<Elements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIABykrgAyeAyYAHI%2BAEaYxBIAzKQADqgKhE4MHt6%2BASlpGQKh4VEssfFcSXaYDplCBEzEBNk%2BfoHVtQL1jQTFkTFxibYNTS257SO9Yf1lg5UAlLaoXsTI7BwEmCzJBpsmCW6b27uY%2B4cAnsmMrJgAdPf72ADUyAYKCk8egkzTxI8mGgAggoCMQvA4ntgWHh3o1zgDASYAOxWIFPdFPI47Jh7A4ES7XNj3W7YehsQQKf5ojFedJGJ4AWU86Ce%2BwAIp9ZD9wn8DqStowCApif8EqjEUi2ftxQiAPQAKkVSuVKtlcuVTwAKtghJqhE9lWqgQqVaalUbEUCsSczvirswiQ8EtgESCwRCvgB9DSslHIqVihEI604054gkOu5Ol1At3ggichieri%2BqyS6VB40agBieGIIK1mALhszgLQDBBmFUyWITyYXiITyoXgYEChMIUcLOXo0j3mqaexEwBBWDCbYiU0t9UqBCPLlertfrjebrfbsOI8IOXq4fYHQ5HxDHoK8YYs09LIJxeGQnqY7ziBAgDFQCdXbehG63bh7/z9kvmeYM1nWMGkcW97yUJpqBbD8Oy7bcBGTP80zZQDgMtQETUVJ4hBqAQWU1IsExLWczASMJXi8LBWQOBs6EILcY0w%2BdNkXOsG1QJ5gFg9dO03bskN7Z1%2BwAWkeJ4QXQEAQCoCdME9O0z1LViqxrDjGx4tdP3478dz3cTnUkghpJAE8FKUjDXTAm87wfaCXwTLBXiU6BYKkmTnNoAA3MQzj4hCfyE0VsAgQD5hk3zvEwIDAxA4EbIg%2Byny81ytIgDyQC8qL/J0wL9OdR4wsAyKxFPWKLA4RZaE4ABWXg/A4LRSFQTg3GsaxJOWVZMFZcieFIAhNCqxYAGsQFqyRbg0SQuCRBINFqjQzAANhWsx/ECGqOEkXgWAkDQNFIRrmtajheAUEAjqGpqqtIOBYBgRAQGWAhkgbchKDQbY6DiCIbk4VR/BW0SVskbjkGQJ4pFuMxeEwfAiGIPBpK4GRBBEMR2CkdH5CUNRhtIXQ0YAd2IJhkk4HhqrqhrCbOgB5Bt3oTVAqCeIGQbBiGoZhswnggDwfvoWtzASLh5l4G6tEWCAkG%2B5JfrICgIAVpWQGAKQzD4OhNnzShokJ6IwjhKneGN5hNwZ6JtBqG6Bu%2B8kCAZhhaHOQmsGiLxgDcMRaEu7heCwFhDGAcRbtIfAh1qbyi0JqsagbdYBrCTZtua2g8GicnNw8LBCdBPB9sD0hY%2BIaI0kwNktlDzOjGGxYqAMYAFAANTwTASYZ%2B0zdxzHxBx/hBEUFR1Aj4n9FDlAOssfQs8uyBFlQZJHAEAPRKk9lTEsawzFOsvkawBewtsTB7FXvwIFcMY/DRkJplKco9FSdIL5v5%2BCgvvpH7mU/z7qSY780YdAvt0Jo38BgVGGD0IB0DwEP0gRIRYChuprCQfoWmx16acA5sDUG4NgCQ2hlNfmbZEYkD6uLSWg0G6LAQJgJgWB4gn3GpIBItwACcCQkSSBmmYSQK1Dq1RWhwjBO09ogHFrcFaXAVr%2BA4f4WRk0uC1S4StLBEczoXSujQ26ssnpyxeszD6Ks1Yi3%2BmwTgjQWDeSRKJJgLwDD0i4Bw24XBprw3IYfPQQ9hCiAHtIXxI8CbjxANrMmFMzY0w4PVDRp1OBMzeg2J4bM6zEBsXYhxrxQ7Q1ce4n0gtUDCziJQsw1DpZ3UMWYuIn1VZFMViLEA1jbGiWyUYFxXAjo0FoHrS6EBDYRwtqbEuQyrY2ztr3R2goXZuw9pgL2Ps/YBwGsHWu6xmpRztngWOAdmoJ2QEnXuqcz6E0ztnOEed1lS2RsXAaZcK5KGriHIwddQB6L4M3NuHcu49xLr4/u2NAmyGCWPZquhtZOOMDPGwZzj5LxXpkdem8Ehsm3lYSwe9eCoAPijOOi8/5bOcFfBg7hPCtD0PfEoiC0Yv0KFkMluQaWf0yBA2YUCQEAJgQy2%2BBLOgMDAVMKlbK9BXlGNykVkxWVPwlksFYaCZXbViSdLFODmmZMcTklxbjpoC1wIQChYsJZS1oaQehjDBgn22rtUg%2B0EiuJmkiVRSJ5qSH4WDNGyqWqcG0ddBu90DFIFeizWp1TiAWPWNY7mLAFDeSht5LVJwQSeP1d4tG/z/GAtxiCwmugkgRMpoHaJSrsEcESSzFJ7NI3g2jbGp48bXGJoTIU4potyIJHKX6qp9SlYhu7Y02NyRkienrZ6Rtd50lgx1j0uIfSBnNVGe7EZJsxm2wcJMopTsZmLo2fM72vtaD%2B17qsl5VzI55i2Ts%2BOqhE6bCOYIE5Eczk53OJcguNze73Mrk82uYQ3kyw%2BUwFu7dO7d0YL3dNWMJBAuHvjUFOhJGT3rmi6wc9ohwpagitenBZQeWQxi/ecRD54pPhyol19xV3xJVK3%2BtK34UfyK/FlCDhXALPoS/lgD6OkY4z0aj7LOM5B5aKwVMxpXINQdjItdNNGqondWmNcaE2hgLGQlNlCjW6JlnQhhTDKDROtftMwriEgJFqktWah0TNIjkXElV51bA6IqYBUgrDaqcNqv4VaHDJAcPmtwyoYiEjSfifZpz0S4a2a9aFk1Zd0jOEkEAA%3D%3D%3D)

## Links

- [source code](../../../conceptrodon/moy.hpp)
