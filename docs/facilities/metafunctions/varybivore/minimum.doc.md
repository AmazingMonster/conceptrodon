<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Minimum`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-minimum">To Index</a></p>

## Description

`Varybivore::Minimum` accepts a list of variables and returns the minimum.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (min) V<sub>0</sub>, V<sub>1</sub>, ...,V<sub>n</sub></code></pre>

## Type Signature

```Haskell
Minimum
 :: auto...
 -> auto
```

## Structure

```C++
template<auto...>
struct Minimum
{
    static constexpr bool value
    {RESULT};
};

template<auto...>
static constexpr auto Minimum_v
{RESULT};
```

## Examples

```C++
static_assert(Minimum<1, 2, 3>::value == 1);
static_assert(Minimum<1.0, 2.5, 3.5>::value == 1.0);
```

## Implementation

We will implement `Minimum` using `std::ranges::min`.

Note that we are not instantiating `std::array` directly. Instead, we let 'Class template argument deduction(CTAD)' decide the correct type for `array`. [Check out this test to see CTAD in action.](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGwArKSuADJ4DJgAcj4ARpjEIACcpAAOqAqETgwe3r4BwemZjgLhkTEs8YkpdpgO2UIETMQEuT5%2BQbaY9iUMjc0EZdFxCcm2TS1t%2BZ0KE4MRw5WjSQCUtqhexMjsHOYAzBHI3lgA1CZ7bs3ETACe59gmGgCCj0%2Bz6CAgV7cnTGcA7BYuKQTmYTP8ACLnKzPV6zJiOZAAfSYCiULQg70%2BClYmBRCnObiwRwIN1SmAgTDWJyxX2I1zuFwiBBBYL2D3ZK2hrzhBA%2BdIZJ1iAKBADoNKzxSC9uLwVC9jCXs94Yj8eiCJi%2BdjcfjCcTaKTyRBYtTad9GUSNrF6NL7vcuQqOGtaJxArw/BwtKRUJw3NZrDSNltMGczHseKQCJonWsANYgQJmUX/MySAAcacCGiSiY0/jTe30nEkvBYEg0Eo9Xp9HF4ChAEqjnqdpDgsBgiBAGwIqS8LIoEDQLFSdASUVxnFUaf8AFp/JITsBkMgTlJRWZeJh8ERiHgPsD%2BIIRGJ2FIZIJFCp1M3SLpgQB3a6pTg8Z2u93R72cADyfd7BBOVAqBOKdZ3nRdl1XSR1xOCAPGHUdiFDcMVl4JstDWCAkCHEd6DIAccMQkBgCkMw%2BDoAgEnrY1P1iCJmhuF9eDo5hiBub9Ym0OomwjIc2EEb8GFoRibywWIvGAS5aFoetuF4LAWEMYBxFEvBiG4vAADdMFkr1MFUOo%2Bx2CNmW6T9aDwWJrjYjwsE/AhdzLOTSG04hYgyTAIUwRSjAsoxozWKgDGABQADU8Ewe9v3JD0I0PYRRHEM94svNRPzvfQlJQf1LH0Sz60gNZUFSXpZJnd5zghUxLGsMxq1c3csAKiA1lqepnAgVwpj8YEwgWCoqj0IosgEbqhoyEaGCGAbRmBNren6SZPHaPR5oaOZppGRI5rmMadoGTalm21qg22CQ3w4N1SCrXgaxA6c5wXJcVzXMxYNwQgSGQrhUMjAK1gQTAmCwRIWtIeNJBlJI9n%2BSQNEkVN/ArQJ/BSF0OBLUgy3DUV/C4fMkjTfHAkkLhAmh/xrs/Gs6wbP7m0wjssK7P8%2B3IShCLw8c2E4ZoWE0/4Zz%2BI4lNXJJRS4cVN23Eg9z0eLjyS6QUqUNKb10MjHyYZ85Iuq6bq/Dhfx7PtAOAvmBaFk4RaMMWJfFWD4NwhJkLMX70JbZnOYSdnB1QBC8LpfnBZtkiki4CUaANKjKFiWj6LYpjSBYhiOK4hwk74xgCEE4TPzEiSpJkpOFKUlSvXwdT6m03TNwM5AjKT0z0a9CyrIY2ydi9By8CciNXPcpQvJ85SIlABm%2BGCsKIqimKk4VxLT2V2RUuvL0Ncy/zqqsXK2%2BaoqSuyMqKr2KqcosOrboavcdPgVrug0jquuW/JeoYdBDsG4Fht6Pa0gm3on9ZpdB6OtAYf81oCEWvMcoW1Vq7Rfj1cYB1%2BpwJ%2BusTYZ10Ho31tTTgvxiDBytqHO2ksNDvRlkhfYP00L/VIIDYGowwbo0xtjcW8N/jk3%2BP8PYCNJDzmBAbGmtg6Ye0ZvAZm3Z/y%2B29sQbmOw%2BbgRYAoTSK5NJcHFgYSisxpafUavLWQisl7nnkKrNeOgQCFi1jrV8RZLofhvDWY2/4zYEJYEolRaiNGii0TpACcF/bOyoWGPY7sAqtmwoExCMiomB1UakVISJ1FJCRL42YKJCHznItHYg1E443hTonZyhT2KcW4pnf2/Ec5CREhXTA4lJJiGLs5Uuvku7yTUhpGun59KGUok3QQZkbxt2sjcTu9lHJJwHh5YeZcx7hKCkwEK4VIrRUYPPQxi8JDLwvGY9KljN7GHPnlWI%2B9vSHwELJAA9FibetV6oJEarfQqIDH5%2BE6u/P%2BfVYFHXGsUbIf8f7ZCAdtV57U%2BgILyEgyBEKUE/K/sgpaUL4FwsWF/E6mDTx6wcdWfBiiFzKNUScZJPiER%2BIoXo76YSGYAyBiDSgF1WEgDMOLPYexAhZlJhWNl/x8xU0cZwWmjY6EQ3%2BOuThXApBJA4dDLg/w7F7BxbdQV9MMIXQ3Py3FtZVUxhclRbIIBJBAA%3D%3D%3D)

```C++
template<auto...Variables>
struct Minimum
{ 
    static constexpr auto value 
    {
        []()
        {
            std::array array {Variables...};
            return std::ranges::min(array);
        }()
    }; 
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIIEapAAOqAqETgwe3r4BwemZjgLhkTEs8YnJtpj2JQxCBEzEBLk%2BfkG19dlNLQRl0XEJSSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwA9ABU%2BweHR8e72yYaAIJ7BwDUACKYqa6MyHiYCjeHZ5fXJ39H3wu5yBZkCEWQ3iwNxMgTcYmAJEICBYMOwwPMYIYEK8UJhcOIxCYAE9Ueifv8KQDgb9djcAJIsVL0NiCJgNT4HQE0yn/QHAgiYRkGAV4pheIgAOilADUWngmLF6ApSZdxsQvA4bgBZCJ4Fg%2BdEAdgs0MuN3NN1mjmQNzQDHGmFUqWINzFRBuADcxF5MKaLhbocbgQGAyZ/FZ/HcIEtgyHzSYg2a4yHxugQCAWoSia6CcTAxZZcR5Yr3lKJQm7jCrEnkxbiJgCOsGJaCGmQISjO90ywIhBM8SY4Fq/7kxXo7H44bK0O/RWq2SrjyqeTbthVKwmb6vtSl9vLsCrXhkAB9JgKJStCA6hh6g2wrikG5mR%2BBVHpr3eX0w6d3G5cQfDoeJ5nheBBXrq%2BooveEopE%2BEr%2BC%2B8FviAH4%2BtCgQ/n%2BMEARwKy0Jw/i8H4HBaKQqCcG41jWJaawbF%2BoI8KQBCaLhKwANYBJIMEABxmGYACc/FcP4GjcdxXCGoa0j4Rwki8CwEgaCkxGkeRHC8AoIApMxJG4aQcCwDAiAgGsBCpOK5CUGgjJ0AkUSsFsqjcQAbAAtM5kg3MAyA2lIEpmLwmD4EQRZpg%2B/CCCIYjsFIMiCIoKjqLppC6A%2BADuhKpJwPB4QRREsWRnAAPLiuZBA3KgVA3E5bkeV5Pl/lxZg3BAHg2fQLoYv%2BvA6VoKwQEg1mpLZZAUBAQ0jSAwBSM%2BNC0AKxCaRAsQFbEEQtES2W8GtzDEESRWxNomAOFtpDWSyBBFQwtCbclWCxF4wBwrQtCadwvBYCwhjAOId14PWDh4B6XbJY6x3ilsjERAKMmkbQeCxISe0eFgBUEEWCnvaQwPELEGSYA8X1GPDRgsSsVAGMACjSm8aVFU8xGMRFwiiOIsXMwlagFal%2BjfSgVGWPoCOaZAKyoKkDRva5qbfqYljWGYqk46FXai90x0NC4DDuJ4HR6GEERDJUIwPkUWQCFMfimxk5sMPMwyJA%2Bdga70ExtLr%2BRO3ULsCH0rT28bju2G7lt6LM/uGwsJsrAotGbBIuUcIRpAqbwanVS57med5vlNS1uCECQ0IMUsPVkysCCYEwWCJNGpAcZIgQSvxgRSRokhmJIzlKf4zn8fonByaQCmBFwErOVwzncfx4nOf4kjCS3zkpwVakaVpTFk/pRkDSZpUWWNE0dfZbCcC0LAeoarlMLaBhGH%2B/ESmPpFBYXoV6MzUVs9IHNKFzyW6GfBlJgWV3qJ2TqnQqHASpmXFBVKqNUs632%2Bg/J%2BMEWptWGh1YugQzCl03rpfqg1UDtQSJZcaJCsEjAhN9LgQkUhzQWktFayUdobVOmwvaB0jonSxudRgl1rq3VIvdR6z1XqnU%2Bt9X6Ij/ou2Bm9F%2BqhwYClOtDOoBV4aIw2ijLYpF0Z6lOjjPGShCbSIiKAQhfBKbU1pvTRgp1P6sxij/WQnMkqkUAbzUmcsrCCy0SLOu4tJacGlq2WWAsLCKzTsrPAWBAkx29oDZwEBXChwfAbcoDs9BmwaOktINsGgB0WF7HovsQ4eyturZJjQ3bFJNsHfo%2BTw4DEjtk/8qx1jxw6TJCBq9OAZ1qp5Gh986FoI0PnYKRcur4N6qxUgldq4jDrjJIeI9H7t0NP4fiklAgdy7gvFeyU162A3nM/qO8kCmTKuQo%2BdkHJn2ICwOqLAFAehtB6MZwp3gEEClM9%2B4VZBfxcXFeQf8PE6CSKQYBoCcoDyTvlY5xV97lUqtVF5byPlfLZD8jBlCRo4MCLMreu87mjSsvijqKFkCpFSMeT5/FjzfPGMeVQHk%2BB0CYZQFhpFOG3UYny7hGtTr8MEFdG6BVRFPTEBIrGUjiZ6I%2BnIwGCiCpg2QBDNRggNHJS0UjIkui0YYyMQkExBNBTmNJlYimTAqY00wHTBmjigXOIkK4%2BK4LuZQrvsYSJQtYgJLIhLbIb1tipn5vLSw0SyKxPifARJZS/CpO1vkzJRsSkFOKNkfJuTsj1KDs7Gpft3Z5CqYWhoxb81hwqaW6tcw2mBwTp0uiTbemItUgMtlnlXnvM9NigU4xJlvxwd1AhfUK5VxrpQROayQACQlIEQI/gRILyUouw0U8jkdvUqc7S5d64gEkP4ZuElDRKW4pIISXBeJmGXjJQI7a06cDLoQxOAUt1Pp3eclYONMjOEkEAA%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/minimum/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/minimum.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/minimum.test.hpp)
