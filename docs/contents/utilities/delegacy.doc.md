<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Delegacy`

## Description

`Delegacy` accepts a warehouse and returns the warehouse via member `Road`.

<pre><code>Warehouse -> Warehouse</code></pre>

## Type Signature

```Haskell
Delegacy ::   template<template<typename...> class...> class...
           -> template<template<typename...> class...>
```

## Structure

```C++
template<template<template<typename...> class...> class>
struct Delegacy
{
    template<template<typename...> class...>
    alias Road = RESULT;
};
```

## Examples

This function injectively maps a warehouse to a type.
In the following example, We will create an overload set of `fun` using warehouses `War_0` and `War_1`.

```C++
template<template<typename...> class...>
struct War_0 {};

template<template<typename...> class...>
struct War_1 {};

constexpr auto fun(Delegacy<War_0>) { return false; }

constexpr auto fun(Delegacy<War_1>) { return true; }

static_assert(not fun(Delegacy<War_0>{}));

static_assert(fun(Delegacy<War_1>{}));
```

If we only want compilers to perform an argument-dependent lookup, we can utilize `decltype` and `std::declval` to avoid defining the function body.

```C++
constexpr auto gun(Delegacy<War_0>) -> std::false_type;

constexpr auto gun(Delegacy<War_1>) -> std::true_type;

static_assert(not decltype(gun(std::declval<Delegacy<War_0>>()))::value);

static_assert(decltype(gun(std::declval<Delegacy<War_1>>()))::value);
```

## Implementation

```C++
template<template<template<typename...> class...> class Warehouse>
struct Delegacy
{
    template<template<typename...> class...Containers>
    using Road = Warehouse<Containers...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxCAAbKQADqgKhE4MHt6%2BASlpGQKh4VEssfFJdpgOmUIETMQE2T5%2BgVU1AnUNBMWRMXGJtvWNzbltwz1hfWUDCQCUtqhexMjsHASYLMkGGyb%2BbhtbO5h7B5vbTLv7BACeyYysmAB0L3vYANTIBgoKL09vn2%2BCneAHUGpgEEslG8TBoAIIKAjELwOd4AEUw9GATGQN1hcJMAHYrPD3mT3ocLlczkdLidrncHmw/gCvkwfn8PIImFNiAoYaTyV50kZ3gAlVBMdDvPZo0HgyHC%2BluLn1Xm/V7%2BbB7EkEwlonX4/EAegAVOaLZarcaTZb3gAVbBCe1Cd6Wm3ws1W70Wj0E%2BGU46nQN04OM5jMzUfNkcqP4xHI1Fg4gAfQ0MuJRIN/l1%2BJD1Pzytu9wjzyjgPZGv%2BWvjSJRBHlqa4Gas%2BsN8NtFveADE8HyG/bMIi3b6jfC0AxEZhVMliO8mF4iO8qF4GBAMVicXj9sm0285i33sRMARlgxl2JoTmMwaO%2BOBFOZ3OF0uV2uN5hsbjTruuPvD8ep7EOedb0hYN5jgi9SOMgKaVnEBAQAwqANm%2B66Yp%2BW4/g0e41pm%2BpzHM7b%2BlBlx4LB8GNNQq7oZu347jhf54a2aKEcRnbmu8QjVAI0qDsO7qQeY/hhF8XhYDK%2ByLnQhDbtqd5whOj6zvOi6oO8wA0R%2BX7bm4u4aP%2BAC0AKIugIAgFQl6YCmxZgZBSkbE%2BqlLpp74YTp2FNkZJkEGZICgTZjLsfCiJkRRPwIUhKHvFgXy2dANGmeZsW0AAbmIpzaVhDGpgZNZahAhFzOZ6XeJgRE5pBoUwXBEVUSl8WuRASUgClpWZe52V6YxMIFUVJViF45U6hwCy0JwACsvB%2BBwWikKgnBuNY1jvAoSwrJgMpmP4PCkAQmijQsADWIATZITwaJIXCEv4GgTRoZgJAkZgABwvfonCSLwLASBoGikDNc0LRwvAKCA/37bNo2kHAsAwIgIBLAQySLuQlBoFsdBxBEjycKoL0JIZCSSBpyDIO8UhPGYvCYPgRDEHgZlcDIggiGI7BSCz8hKGoB2kLozMAO7EEwyScDwY2TdNfPAwA8ouKMNqgVDvPjhPE6T5OU2Y7wQB4mP0HOwlcHMvCQ1oCwQEgGPJFjZAUBANt2yAwBSGYfB0BsfKUNEfPRGEDQ3OLvD%2B8wxA3LL0TaNUkO7RjbCCLLDC0EHUOkFg0ReMAbhiLQYPcLwWAsIYwDiGn%2BDHjUqVDnz07VIuay7WEGzjWntB4NEIvhx4WB80ieA/QXpDV8Q0RpJgGLF0Y7dGAdCxUAYwAKAAangmCC7LJbB1zbPiJz/CCIoKjqGnAv6CXKDLZY%2Bgd2DkALKgySOA%2BnCGaZsqmJY1hmEDI8M1gd9Cq2Awh0PwEBXCjD8MzEIUxSjlD0KkdIz8sieBaAggoyDehwIGMzdoyCugjFQbkXBID8ETCwf0eIuCJiQL0KFRoFCZhUIWGtZYqwJCSw4FNAGMtOCqwJkTEmwAyYU3OjrCAuBCAkC2jtU2e054LAQJgKUAwgEnUkP4J4ABOfwhJJCXTMJIBIf0JoJC0R9DgX1SA/R2k8BIXAEgvS0S9BxZ0uATR0UkQGvBgag3BvIqGlt4ZW0RgrVGDsnaGxxmwTgDQWCpUJIZJgFZRRcC0U8LgF0aZ0xIIzPQB9hCiD3tIApR9eanxAO7YWotg6cO4d4%2BanB5bI0XO8ZW85iDxMScktkqT0mZPTHrVABs4gyLMHI820MQmRLiGjR2wzbaGxAHEhJhlemuy0Vwf6NBaBezBhAX2adQ6B23sc8Okdo4OG3vHRgBAk4pz5hnLOOdaB523kXEuZc5oVxjngau%2Bc5p12QA3bezdMR83bp3QOPc1hzX7oPXaI8x5KEnp8sIoBAl8EXivNeG8t5DwKbvDmJTZBlJPnNXQ7sDCz0/lYa%2BkLAEPyfpkfOb9fIfyvhYH%2BPi/6MxrvfYB9hkEuAYO4IhUCgiisYfA5miDCgoJyBKuVmDYGULoaQ2oNDxXqqFZq7o0qcFDG6LQ6h%2BrVVMI4YsNhHM6nSzTsDDpXSkkpOABTfpF1daSPpjIk2ZsFGkCUSo%2BIQDW5WJseky6hIPGEhupIQxxNmYNN8bYfxkygnwBCUjRWcyZnEGiWsOJGsWAKFSuTVKaSnjHERNkqR/98myCJRIElh8ebkp0HkapYsC62p4fappYSlYq0LSTYtpb3jlvSVWhsQyRlG22v4CZc8YbWwWXbHNq6lmluSMkFME6UxTrgp04mHtdlxH2YcuaZzU67SvRcmO1zhkJzucnVO3zMCZ2zrnfOu0PnT1hYXPsvz/m11UPXDYoLBDgrbh3LuNwYV9wZgi3gSLx6ounuipdC8mBL1XuvTejBt6EqKcSrmZK%2Ba6ECNS4wnKb7REZfNZlL8ODGiSrS7%2Bv84j/35UAvBmQRVisVXoGBJQ1WyowZkE1%2BQkGZANVQwVvzOhasEyQ3VimzUiYtaawhymjUMPNTKlh612EmwsfU3hHBHVFpLWWitU7PU5LnbIv1gTFHKKwMGzhYbKnpP8P4Ca90rp/V84SRxvagacD8RDf16iJraImi9R6WjJBaJurorglHOD%2BDteFkGASLacOpmFnxEW8uHWHmevjkggA)

## Links

- [source code](../../../conceptrodon/delegacy.hpp)
