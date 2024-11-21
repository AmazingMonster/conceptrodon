<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::LookFor`

## Description

`Typelivore::LookFor` accepts a list of elements and returns a function.
When invoked by predicates, the function returns the index of the first element that satisfies all the predicates, or `-1` if it cannot find the element.
This function is created to exhibit the power of fold expression and to compare with `Typelivore::Find`.

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

We will lookfor the indices of `int**` and `void` in list `int, int*, int**, int***`.

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
    (...||(++counter, Predicate<Elements>::value)) ? 
    counter : -1;
}()
```

The function contains two main components:

1. A fold expression over `||`;
2. A counter that produces side effects.

The comma operator discards the result of counter incrementation, leaving the predicate's result to the fold expression.
The fold expression will short-circuit as soon as `true` is obtained.
Hence, the counter will stop incrementing once the right element is found.

If no element satisfies all the predicates, then the fold expression is evaluated to `false`. In that case, `-1` is returned.

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
                (...||(++counter, Predicate<Elements>::value)) ? 
                counter : -1;
            }()
        };
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxCBm0gAOqAqETgwe3r4BpClpjgKh4VEssfGJtpj2hQxCBEzEBFk%2BfoF2mA4Z9Y0ExZExcQnSCg1NLTntY31hA2VDiQCUtqhexMjsHOb%2BYcjeWADUJv5uXo60hACex9gmGgCC27v7mEcnyKPoWFQ3d48PBEwLCSBkBxzcBEuSUYrEwADoEdh6GxBApfg9RsQvA4DsFUKgANYAMRIfxMAHYrA8DjSDoDgaDMOD6SCmGCTpDocw2Ai4TcDnsmAoFAdlMRMPhROzbtTaZjsQRRcRUEQAEqoJjoP60o6U7U6uUNRzIAUCUaYVRJYgHJhnVAHABuYi8TNlBt1VPu7vdJgArFZfQARCCLA4AWn5nxAIBYTAJmAA%2BmlgOF0AmCOC0gAvRMZ/wyr3enUUz1FotRmNxxPJ1PpzN4HN1/OmryCOIesNcCmB46lsvu8UENYMfX9nUQXkUtxTiDWaxoVuAshKiV4KVMk5IoGMAho/PRp3eTCLUPHIlHN1jmkLtvWkDhrv%2BPv97sh0cG7u99%2Bfp9ky8sxlmSBVl2QhKEYR5BF%2BUFYVeXuYBxW3VF0ULGkvDSIwDnVTU3kDJUVVQbCtROeDEJRXdJ3zL8Hh/T0/gAegAKmYljWPohiWIAFWwIROJY9iHiY1jhIE/5HjMHYGD2LxDnBM46CuFC/gAtkNzArlYQOLdyJQ%2BUcQASQUfTBEDVZonoHpiD%2Be8ki8cy1wOCs8AUJNYXBbSd1IA4wgIZj%2BRLWi/3uFTQM5CDXg8wRdIILEDIUAA1VA8C1B4bLsi4TSclyFDczdkU8x0kuI7APUCmiAWAwCOUq1TmXA7l4Sg5sYIUODiGAPcC3QsJgAOABZTAGioVsugEXDcXxYlSROHyvJ8xi5sEZjFt8xiUOjIjwXudrWqa25f3K%2B5RjZNcEyFJQmggAahpG2pwUM4yCFM9LMEsm4D2dV5jh7fw8LMRZqKOo1TvOuICCuwamGGqS7pOQzEuS96QEPF1cO%2Bh8AafDhlloThfV4PwOC0UhUE4adLGsRzVnWL6JJ4UgCE0bHlgJEBfXJOF/AADgANnJfw%2BY0bn%2BYATkCXGOEkXgWAkDQNFIQnidJjheAUEB5cZonsdIOBYBgRAQFWAhbIIchKDQYE6DiCJYU4VRebDHnJAOYBkBNKQ4TMXhVyIYhkr0fhBBEMR2CkGRBEUFR1C10hdC4UgAHdiCYJJOB4HG8YJpmSc4AB5M4TYOVAqAOe2ecd53XfdyRPYOCAPEt%2BhrW2LhFl4TWtGWCAkAtpIrbICgIF7/uQGAKQzD4OglzViBomz6IwkaS4094BfmGIS5c%2BibROk1%2BmLfI3OGFoZeY6waIvGANwxFoNXuF4LBYyMcQz7wcUugdTA7%2BJi1OjOTZ6Y%2BWqNnC40Rk4bw8FgbOMU8Ay3vqQT%2BxBoipEwIGIEhhgAXCMEzZYVADAdXingTACdc5chXuHYQohxBh0DvIJQahs5x30BglAc5LD6DwNENWkBlioCSLUO%2BYZPjfVMBTSwZglaIL9lgbhIYqg1AyC4Bg7hPCtD0CEWYpRyh6HyOkAQEw/Dx10bUfoWihjxw6KNOo0wDF6EsbUSyMwSiDHiBYmxqichuN6KYlxEhlgKGphsPx%2BhM4K2zsrUuDsnYuzdgcD2Zg664EICQI4dM24MxwcsBAmBNRDDkazSQ/g4Ri3JJIDQkhEg8zlr6HmIsQmS2lgELgcIeZcB5lzEWXM2m%2BkkFwX0YseZhJjsrVW6sMlay7vrbuhsC5nDNkPVAjdra2w4I0FgDpyRhiYAKAwmEuAizhM0n%2B%2BBfb%2B3jrQ4O1DpC0MjgwmOugJ5JxTivDOHB8ZDKVnnWZipi42mIOszZ2zBR7IOUcuuDc%2B5N1Sf4f67ccE6x7osyFcR5nDybiANZGywzArHiLLg8saC0GnpQOeMc15L3IeSjeW8d4OHIQfHcR8T7Z3Ppfa%2BtBb7kMfhgl%2BxN8Dv0cJ/b%2B3tVB/0BOQoBEtiagPAZcSBmxiYwLgfTRByClBoKfpgnq8K8FMAIUQkhZD4EXKoaHa5shbnR2Jg85h2DRFWHYaA2RvD%2BEZEEcI369rrASN4KgKRyUv7wH8dUXeiiICuFsfHDRzj5iuLyKkPRmQPGGPjQUDIPjY12JDVYxxkb5GhoEI4jN2ivHjGTXY6YxbzH%2BMCaHV57zFa%2Bs4H8gFWydkYLiaCuEGhEknJSS3dJHdmakGybk%2BIciJZS1IDLfwBzynkn6eSfmFTJBO3jo2nOKtbBjKHZM%2BA0yjYm1RUi/uNs2CcDWdElgCgHQmgdPsuEjJRjez7dIgOshLlmooZaxhuQnmp3vvWrOwyvnGzOEXEul7nbXtvY6B9T7FT1xPVC7Y/hB3wumWilFg8sPxFvUkJICZ70iwTAhs6/ynaTyJXEGepLiZUtPvTBjNLd70sWYfY%2Bp8%2BWYAvlfG%2Bd96bcufgqh%2Bb9Q1Cuzr/ZA/8JVtilbwGVS95XQL9sq3gqqUEap5dqiZfB8EJQNaQxg5CTUhwkOaiO9CrU6FyLs4wbCbBOqDSTV1ZpOD0SjF68Rki4jSMDTw/NVilEqOyCm6NcwS2psTXm4x6bNG%2BIsdmhx7jQtZoUYWyt8XM2luaOWnLVbXE1rWEE1u9SG3hObVBg4MG73wdUqMXtyTm5pLhRMrJOSsDjteVOmWZgDn%2BH8L6X05T8VC38OSdpHym1brVhrTJpAClmBaVwGFPMYUi1aWYKp5J6n%2BGA58rdu7Xleym5u1rndliILSM4SQQA%3D%3D)

## Links

- [source code](../../../../conceptrodon/typelivore/look_for.hpp)
- [unit test](../../../../tests/unit/metafunctions/typelivore/look_for.test.hpp)
