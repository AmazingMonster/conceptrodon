<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::IsWillful`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-is-willful">To Index</a></p>

## Description

`Omennivore::IsWillful` accepts a type.
It returns true if the type is a packed `Will` and returns false if otherwise.

<pre><code>   Type
-> Type == Will&lt;Items...&gt; ? true : false</code></pre>

## Type Signature

```Haskell
IsWillful
 :: typename...
 -> auto
```

## Structure

```C++
template<typename>
struct IsWillful
{
    static constexpr bool value {RESULT};
}

template<typename>
constexpr bool IsWillful_v {RESULT};
```

## Examples

```C++
template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
struct WillLike;

template<template<template<template<template<auto...> class...> class...> class...> class...>
struct CalmLike_0;

template<template<template<template<template<auto...> class...> class...> class...> class...>
struct CalmLike_1;

static_assert(IsWillful<WillLike<CalmLike_0, CalmLike_1>>::value);
static_assert(! IsWillful<int>::value);
```

## Implementation

```C++
template<typename>
struct IsWillful
{ static constexpr bool value {false}; };

template
<
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class Sunshine,
    template<template<template<template<template<auto...> class...> class...> class...> class...> class...Perseverance
>
struct IsWillful<Sunshine<Perseverance...>>
{ static constexpr bool value {true}; };
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISRqkrgAyeAyYAHI%2BAEaYxCBmAOykAA6oCoRODB7evv6BaRmOAqHhUSyx8Um2mPbFDEIETMQEOT5%2BATV1WY3NBKWRMXEJyQpNLW15nWN9A%2BWVIwCUtqhexMjsHASYLCkG2yYAzG4EAJ4pjKyYR9gmGgCCY8ReDgDUAJIKAOp0tFRetDu9xMiQsrxmjmQrzQDDGmFUKWIr2iqE8rwAbmIvJhXiCLFQxEoQQARI5gklkoFA7a7fbXB5HNxA14s140vZMA7Hdl0xk8znXbk7Dlck7C3lC2kCxlMLxEAB0ipu0IMCgUivlyuQqvVSsO2BVTDVGq1OpN%2BsNxr1Bu1RoUryEXlhCDCmFIzNZ/NFXsFYql3vF0slIt9soV1stus1FttVujNrNEdjUdNdo1yjiSnRcUMGyp%2BqBTxeBA%2B31%2B/0Bx0dztdjIzxCzOYYG3NtwLDNB4KakOhAjhCKRKLRmO8OLxBGe10SpMO5OnlIZDwA9AAqNfrjebpdA1fr14AFUwY3tG%2B3y83F9PVIePr5gYD/t9t%2BDEr9IZlctQrcj3%2BTv8T8Y/kmAE3IWE7Fq8Py0LQoQANaClYi73M%2Bb6vih6H3qGn7/mmwG4YBf54XGoEPEWbxuGILBwZgAD6GgLsCN6YXej4se%2BL5BqhnFhl%2BREpjGIECfhqbEe2jzgeRlHUTRXAMWBnJ4MgNF2nEBAQJ8UF/ACjKadRjIUbQVF4PBdGkK8BlGSZskFvqIAgCO2KLAxEKKcpaqqRAYBgKWmkVoyYQEDcdkOZgTmzhwyy0JwACsvB%2BBwWikKgnBMpY1jgqs6xjmYhw8KQBCaBFyywSA0VmPKiRmJIAAc1XRRoACcZUaAAbNVhz6Jwki8CwEgaIE8WJclHC8AoICBAVCURaQcCwDAiAgKsBApHK5CUGgux0HEERXJwqjVS1AC0LWSK8wDIFCUjymYvCYPgRDEHg6B6PwggiGI7BSDIgiKCo6hTaQuhcKQADuxBMCknA8JFMVxYVSWcAA8nKK0lqgVCvPtR0nWdF2vFdZivBAHibfQSLmLliy8JNWjLBASAbSkW1kBQECM8zIDAFIZh8HQ2wNpQ0Tw9EYTNKcUO8CLzDEKciPRNomAOBLpAbWwgiIwwtDiwDWDRF4wAGbQY3cLwWAsIYwDiDreDEIrjjZsbiXworcqbHlAW1PDtB4NE4Myx4WDwxOeC9SbpDZsQKJKMSOwW97RiFcsVAGMACgAGp4JgIOIxc8V5a9wiiOIX0F79ajw0D%2BgWyg1jWPoPtjZAyyoCk9TG4dYzoEcxKmGllhmENEePVgjcQMsdh21kLgMO4njtHoISuvMwzA4UmQCJMfir%2Bk68MHMQzxMDE8OD04ytHPeRH7Uk8CL0LT7xUK%2B2Gfm96DM99LwfEjj5lGzf51HBYqkEGrwYamMDrHVOudS6khrpE1wIQEguIcpcCpvlROywECYCYFgeIY9SAlUkIceUDVDiJACJIKqLV%2BrRRag1AB3VSC9VyvKFqXA2oNWquw6KkguDRVIS1YB8NhqjXGugqadN5r00WijVarN2Zkx2mwTgzQWDokSIdJghojD4wavKLg8onb3RIE9F6sh3rF2kKXJQ5cAa6B5mDCGEsYaALhgDYayNlpyleOjV4qj1GaO0cAXR%2BjDFExJkzMmyDDhmDQTTaa0iFFxDWmzVApNhj%2BI0baIwXAGpcECDQWg/MxoQCFgDKWYtlYVJlnLBWSsw6q0YAQDWWt4a631obY2eUzZx02IlfAtsT4O3hs7ZArtlYeyigDb2vsxYBz6dTR6oc8oRyjpgGO5sjDx1ABIvgKd06Z2zrnZWBcLGfSsbIMu/1Er2KrgnXuVhLD12iKPZurcsjt07t3B51gB6gKHk9I88Bx7XxPs4CArhX7A0XmUL%2B28ihZChakHe9QH4LCvt0W%2BL8L5by6DfBoZ80VP3fufXIuKSVEsPj/NYf9UEAKASAhGHA/HEDURorR2Tgm5NCRoeBxjyYoLiRg0gWCcHDHwVMxhzC9EaEkIkfhiREiHEoZIE6wNGUiNsGI%2BJkj4DSKWqjFJSTiBKM2KonGLAFDoihOibldIxi3X5aY4Gpyi7nO%2BvIGx1ydAgA6o4yGJsXEMuEUjWRaMMbmtOpa61GI7UCjGOEtJkS4jRMOEK3ZiSk3MyNVmsm9lkApBSDRW1DUaL2oIMpVlJ1eZFMzILYWosZZVMbbLeWdtlaNPVprbW/TMB6wNmII2yselbIWaQAZk9hkA1GeMsOkyvY%2Bz9qceZQclnK1WekdZsctlhB2bTPZTBU4ZyzjnRgJzzFuokBcn6XqK6%2BrucYWuTyZmvKSu8vsnAlydxrn3CwfykoApHsCvFYK/AQpnkimFgxH6H2RQijeOK9Br1RZ/GDb9QX1DvqS%2BeGL8VYcpW/bFZLCOzFQ%2Bi6lWV/5TODe4zgLKWAWqtTauN2wE0QAQQ9aJqDqbCtFbgygLipUJD0YcQ40V6q8P6qJxIbUhG0ZGlqiawrCGJGuvKrgUgGqysSKQrgyQpmHDcUNTgPGJEuJunJ4zCmdXLAjhkZwkggA)

## Links

- [source code](../../../../conceptrodon/omennivore/is_willful.hpp)
- [unit test](../../../../tests/unit/metafunctions/omennivore/is_willful.test.hpp)
