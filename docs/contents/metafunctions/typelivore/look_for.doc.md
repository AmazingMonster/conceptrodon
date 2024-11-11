<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::LookFor`

## Description

`Typelivore::LookFor` accepts a list of elements and produces a function.
When provided with predicates, the function returns the index of the first element that satisfies all predicates, or `-1` if it cannot find the element.
This function is created to exhibit the capability of fold expression and to compare with `Typelivore::Find`.
<pre><code>   Arguments...
-> Predicate
-> Found ?
   index : -1</code></pre>

## Type Signature

```Haskell
LookFor ::   typename...
          -> template<typename...> class...
          -> auto
```

## Structure

```C++
template<typename...>
struct LookFor
{
    template<template<typename...> class...>
    alias Road
    {
        static constexpr std::make_signed_t<size_t>
        value {RESULT};
    };

    template<template<typename...> class...>
    static constexpr std::make_signed_t<size_t>
    Road_v {RESULT};
};
```

## Examples

We will lookfor the indices of `int**` and `void` in list `int`, `int*`, `int**`, `int***`.

```C++
template<typename Element>
struct IsIntDoubleStar
: public std::is_same<Element, int**> {};

template<typename Element>
struct IsVoid
: public std::is_same<Element, void> {};

template<template<typename...> class...Args>
using Metafunction = LookFor<int, int*, int**, int**>
::Road<Args...>;

static_assert(Metafunction<IsIntDoubleStar>::value == 2);
static_assert(Metafunction<IsVoid>::value == -1);
```

## Implementation

The central part of the implementation is this immediately invoked lambda expression:

```C++
[]() -> std::make_signed_t<size_t>
{
    std::make_signed_t<size_t> counter {-1};
    return
    (...||((++counter, Predicate<Elements>::value) ? true : false)) ? 
    counter : -1;
}()
```

The function contains two main components:

1. A fold expression over `||`;
2. A counter that produces side effects.

The comma operator discards the result of counter incrementation, leaving the predicate's result to the fold expression.
The fold expression will short-circuit as soon as `true` is obtained.
Hence, the counter will stop incrementing once the right element is found.

Here's the entire implementation:

```C++
template<typename...Elements>
struct LookFor
{
    template<template<typename...> class Predicate>
    struct ProtoRoad
    {
        static constexpr auto value
        {
            []() -> std::make_signed_t<size_t>
            {
                std::make_signed_t<size_t> counter {-1};
                return
                (...||( (++counter, Predicate<Elements>::value) ? true : false)) ? 
                counter : -1;
            }()
        };
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;

    template<template<typename...> class Predicate>
    static constexpr auto Road_v
    {
        []() -> std::make_signed_t<size_t>
        {
            std::make_signed_t<size_t> counter {-1};
            return
            (...||( (++counter, Predicate<Elements>::value) ? true : false)) ? 
            counter : -1;
        }()
    };
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwA7KSuADJ4DJgAcj4ARpjEIJIAbKQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCUmpCi1tHQXdEwNDldVjAJS2qF7EyOwc5v4RyN5YANQm/m5ejrSEAJ6n2CYaAIK7%2B4eYJ2fIE%2BhYVHcPzyeBEwLDSBmBpzcBGuaUYrEwADokdh6GxBAp/k8JsQvA4jqFUKgANYAMRIAJMgSsTyOtKOwNB4MwkIZYKYELO0NhzDYSIRdyOByYCgUR2UxEw%2BFEHPuNLp2NxBDFxFQRAASqgmOgAXSTlSdbr5S1HMhBQIJphVGliEcmBdUEcAG5iLzMuWGvXUx4ej0mACsVj9ABEIMsjgBaAXfEAgFhMImYAD6WWAkXQiYIkKyAC8k5n/LLvT7dZSvcXi9HY/Gkym0xms3hc/WC2avIIEp7w1xKUHTmXyx6JQQNgwDQPdRA%2BZS3NOIEcINZrGg28CyMrJXhpcyziiQYwCBiCzHnd5MGHTiT6Tj3iAjlQxEpluf/Jex%2BPacv2zbb12%2B2/iz2ob/nSPZ/u6eq9v4XpvqyTIsiCbIclCMJwrySICkKIp8o8wASnu6KYkWtJeFkRhHBqWofEGyqqqgFHamcOF4WiB5TgWYGAkR9IIXBnI8ey27Idy8JsdggoGCK65SgJhG6nMJpmgwFpWjadpEORmrpo6b6lsBtL%2BoGIZhpGLaVnGCbJngqaSs2bg5nmsk%2Brp4EVgQ6AxuZNZWXW%2BZ2Y2Dktp%2Bq6dt2gSQf2A5DiOemGpO6GBDOCVzgulhLusX6kFJm4yTuqL7oe2DHi6Z4fJeBDXkct73rQj7Pq%2BLk%2BkFHY/t2UExYByw6WFHGgW1TwAgA9AAVCNo1jQNg2jQAKtgQhTaNE1PMNY0rYtnEvAwBxeMckIXHQNyEQCsE5UJqHvLuLGEQqeIAJIKDdghBussT0P0xAAreaReC9m5HJWeAKMm8KQhd%2B6ZREBAjQKundX1nHHUhXJnUcoOCFd5WKkcd0AGqoHg2pPJ931XKa/2AwowO5fhBCZY6eMMWJMPhRSQL8YjbOCUjPKIuhgUSQo2HEMABUAiRETAEcACymAtFQbYODkVH4oSpLkmcEPg4IQ2a5D2tHBDUPsYTID0ZCjxCwLvP3HDALyZuibCkobQQNLsvy40kJ3Q9BBPcTmBvXcRWnlRpzUWYnVw3byAOyKCQEC7MtMHLm0e2cOP04HIAnq6If%2BNRXYRxYHCrLQnB%2BrwfjcLwqCcDOqWWH96ybO8uw8KQBCaMXqxEiAfqBAi/gABzJIE/gjxoQ%2BjwAnP4%2BicJIvAsBIGgaKQldaKQNccLwCggKvHccFoqxwLAMCICA6wEF9NMUBAaCgnQCRRPCnCqMP4bJJIRzAMgppSAiZheAbiIMQfGeh%2BCCBEGIdgUgZCCEUCodQh8dB6AAO7ECYGkTgPAS5lwrp3TenAADyFxr5HFQFQI4b9kgfy/j/P%2BkgAHzg8A/egNpW7LF4AfI%2BpAIBIHvmkR%2BZBb4CKESAYAUgzB8DoKuXeEBYgENiBEVo1xsG8CUcwYg1wiGxG0JgBwajSD3xYkQhgtBVHINIFgWIXhgBuDEDVQxWA4xGHEJY/AEoFaOkwLvSxlp9EXG2G3CG9QCFXFiBgrRHgsAEPKngJeVdSDeOILETImAgwgkMMAK4RhO6rCoAYYW2M8CYFQUQ7khiIHCFEOIWBVSEFqAIboLg%2BgskoEXJYfQeBYi70gKsVAaRGi%2BPDN8UOph64WDMBvVAyTQFYF6aGHo%2BjGguAYO4TwnQ9BhAiMMKoowWnFGyAIaYfgDmZCOQwBYIxEgtLsMsvokx2gbIKLc%2Bo9yBBvUGDsxY%2BzbCPJOXoOYbQrl7JuasBQTctgSFwRwcua8CFbyoe/T%2B39f5HH/mYecuBCAkBOGYfwXBOHtzyasBAmAtSjEWT3SQ/gEQz0CJIDQkgzApBXn6ZIU854cAXqQJeBKETJC4MkQeU9B5Cr9JILgfoZ6pHXtXTgO897EuQcfM%2BfCL6kIuOQSgoi2HPzYJwVoLBHSBHDEwcSWT0VTwRFwBEG9gEkDAS0qpUDanSHqUoRpljdBSPQZgtRMK4VysIRwEhV8LjkMoUak1ZqLVkS4Na21GhmGoFYR2XY4cuF5N4fw1Ngi2HarvnmsR0bTVCiMAmrgq8aC0FkZQBRliNEqMMU2rROi9EGMScY/cpjzEEOsbY%2BxtBHGJOcVktxG8PH3O8b4%2B1qgAnAkMSE0uljwmROuNE7YG84kJLbsk1JSgMkuOyeLbNBSmBFJKWUipiSXU1Jge62QDSkEbx9a03J4yrCdPCQs/pgycjDNGXnT91gpnV1mfjHx8BwVvIVs4CArgAUtO2RUa5ehDmNCQ%2Bkc5jQQVLFeb0D5/znmnKWXBpojy8O/KBU8/IpGaNUbBWsDYULCVcqDQizgtpiDGtNea8tEsE02rtVi/AIC8UEqJdwrupAyUUsSIsldPK%2BXWqZYEaVgRR7MpSJK%2BFlit6Kv3tmk%2B59L7X0Lbqp%2BL8OBGpRSwBQjpTSOiE0yCYQCxOOvcs62QrqH1wPkJ6l9KDZ5%2BqwVXQN%2BD9PEM1UqCh3GWB2Yc05lzAkJgprTew/F/gpPGdzRlizxa2FZ2QGkNIiZnNT0TK5ggDseOf2kbWhIciG0b1bRYtubX23LMMd2wQvaLGTswDYuxDjfFtzHa4rdvAp1eKg34%2BdyBAlLvbCujea6VGbtiaA3dvB91pKPeO09Kq%2BCFIUMU0p5TGCVJ8/eiQj74GBaaQEd9xgOk2B/dBze/7zScAGtGEDlgwObwg/Mz7dzyOrPWXRrZazGPoZwzkLDGGchw4I%2B8ijAwsPg8aJ81HfzMckcBZR75aG2MQpYzAiLenplcds1/ezjmnQpeBGliA2LxMcKzSq0l5KsAKZhcpkAZhrX%2BH8H6P0TKq0TyCMK6n8rt62CVdJp8pBqVmAFVwfwZhkha6noK7XGhggrv8JFmnCvlcwsAXLkNXOj6rGSVkZwkggA)

## Links

- [source code](../../../../conceptrodon/typelivore/look_for.hpp)
- [unit test](../../../../tests/unit/typelivore/look_for.test.hpp)
