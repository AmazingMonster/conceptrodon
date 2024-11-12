<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::LookFor`

## Description

`Varybivore::LookFor` accepts a list of variables and returns a function.
When invoked by predicates, the function returns the index of the first variable that satisfies all the predicates, or `-1` if it cannot find the variable.
This function is created to exhibit the power of fold expression and to compare with `Varybivore::Find`.

<pre><code>   Arguments...
-> Predicate
-> Found ?
   index : -1</code></pre>

## Type Signature

```Haskell
LookFor ::   auto...
          -> template<auto...> class...
          -> auto
```

## Structure

```C++
template<auto...>
struct LookFor
{
    template<template<auto...> class...>
    alias Rail
    {
        static constexpr std::make_signed_t<size_t>
        value {RESULT};
    };

    template<template<auto...> class...>
    static constexpr std::make_signed_t<size_t>
    Rail_v {RESULT};
};
```

## Examples

We will lookfor the indices of `2` and `-1` in list `0, 1, 2, 3`.

```C++
template<auto I>
struct IsTwo
: public std::bool_constant<I == 2> {};

template<auto I>
struct IsMinusOne
: public std::bool_constant<I==-1> {};

template<template<auto...> class...Args>
using Metafunction = LookFor<0, 1, 2, 3>
::Rail<Args...>;

static_assert(Metafunction<IsTwo>::value == 2);
static_assert(Metafunction<IsMinusOne>::value == -1);
```

## Implementation

The central part of the implementation is this immediately invoked lambda expression:

```C++
[]() -> std::make_signed_t<size_t>
{
    std::make_signed_t<size_t> counter {-1};
    return
    (...||(++counter, Predicate<Variables>::value)) ? 
    counter : -1;
}()
```

The function contains two main components:

1. A fold expression over `||`;
2. A counter that produces side effects.

The comma operator discards the result of counter incrementation, leaving the predicate's result to the fold expression.
The fold expression will short-circuit as soon as `true` is obtained.
Hence, the counter will stop incrementing once the right variable is found.

If no variable satisfies all the predicates, then the fold expression is evaluated to `false`. In that case, `-1` is returned.

Here's the entire implementation:

```C++
template<auto...Variables>
struct LookFor
{
    template<template<auto...> class Predicate>
    struct ProtoRail
    {
        static constexpr auto value
        {
            []() -> std::make_signed_t<size_t>
            {
                std::make_signed_t<size_t> counter {-1};
                return
                (...||(++counter, Predicate<Variables>::value)) ? 
                counter : -1;
            }()
        };
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKzSrgAyeAyYAHI%2BAEaYxCCS/qQADqgKhE4MHt6%2BAdKp6Y4CoeFRLLHxibaY9kUMQgRMxATZPn6B1bWZDU0EJZExcQlJCo3Nrbkdo739ZRXDAJS2qF7EyOwc5gDMYcjeWADUJltuXo60hACex9gmGgCC27v7mEcnyKPoWFQ3d48PBEwLGSBkBxzcTDOqAAdLCAGpNPBMaL0BS/B6jYheBwHYKoVAAawAYiQ/iYAOxWB4HGkHQHA0GYcH0kFMMEnSFEWHQm4HPZMBQKA7KYiYfCidm3am0zHYgjC4ioIgAJSYdD%2BtKOlI1mpljUcyD5AlGmFUyWIB05qAOADcxF4mdLdVqqfdnc6TP4rP4ACIQBYHAC0vM%2BIBALCYBMwAH10sBwuhowRwekAF4x5NbKVu92aimu3O50PhyMxuMJpMpvDpytZo1eQRxF2BrgUn3HAuF52igirBg6ruaiDciluUcQazWNANwFkBVivASpknBHEJEozBorNhu3eTALAPHIlHJ2DmnTxsWkBB1tbTtdtv%2Bge6tsd5%2Bvu9k08sxnMoGs9kIShEc635QVuXuYBRSBRgCC3bNNS8dIjAOVU6DeH0FSVVA0NocFIOgthBAUEDbk/B4P1dP4AHoACp6IYxjqJohiABVsCEViGOYh46MY/ieP%2BR4zB2Bg9i8Q5wTOOgrnRISfzZZcgKIA4AEk5NlHFVIUViAHdUD%2Ba9ki8FFFwOYtonxWhozQBhpkEcFVIw45MLMXl80or97gUwCrTUjSCCxLSFAAWTCJCAHlwkMg5jNMw0LKsmzjUaByTnUrZ20ylt3O1cksqogF/1/E4fKUq1SL5AxwNhe5iGAeC/iQsJgAOELMEaKgGwcTIMNxfFiVJE4NFIA4uFGsxRq2OSw1w/D6pI2FfnIoTpgNaMBSUZoIHazrurqRydP0m4d3tV4XJcg4zAWN8MX1RcNsFOICB2jqmC6sSDvS0LwoUKLl2wU692czKbxuu8OCWWhOH8Xg/A4LRSFQTgx0saxzJWNZzpEnhSAITRIaWAkAnJaEtgADgANnJLZqY0CmaYATi2fROEkXgWAkDQRvhxHkY4XgFBAEb8YRyHSDgWAYEQEAVgIYyCHISg0GBOg4giVgNlUKnA0pyQDmAZBDSkaEzF4BciDXdA9H4QQRDEdgpBkQRFBUdQxdIXRxt04gmGSTgeChmG4YJpHOAis4FYOVAqAObXKd1/XDeNyRTYOCAPFV%2BgLW2LgFl4UWtCWCAkBV5I1bICgIDLiuQGAKRJpoWhZyFiBolD6IwiaS4A94TvmGIS4IuibRMAcXvSBVoiCCi2ge49rBoi8YAIVoWghe4XgsAjIxxAXvBRR6m1N1D00x7ODZcbCQFoY9i5ol9wePCwUPArwTnN9IY/iEspQfSBQwwALhGAJksKgBgGpwjwJgXSEVkiMAnrbYQohxBOyQa7NQocvb6EASgSclh9B4GiELSASxUDJDqBvQMnwXKmDRpYMwfNv5WxPqQzoY86guAYO4TwbQ9AhDCAMcoQxxoFAyAICYfhRFpHEQwWYgx4jjTsBw7oYwWi8NyEomoKiBA9GaPI4RijbBqMkXoaY%2BjBFzBEUsBQmN1gSCDhwWGpBea8H5nHHWesDZGzGqnMw6dcCEBIEcHG%2Bc8agKWAgTATAsDxH9KQYmkgtjQmZuSSQGhJBmEkJTbm/hKaM1ZhwdmpBOZbC4NCSmXBKbk0ZuTKpgQuD%2BGZpTFxod%2BaC2FuEsWxdpYl1lpHM4Stq6oCzurTWnAmgsBtOSQMTAqqALGozaE5TEYWxIHga240kH21QdIdBShMEe10JNH2fte6OOca4sOHAI7yzONHWOkzpmzPmShLgSyVnp0zuXbOIStjXQLqAiWpcRk/LiEMmu2cQBPJmfyIw7yuAjSbi3Sg7cPb927hPDFg9h6j3Hp/KesFZ7z0RovZeq914T23oAvepKD4qOPhvVZqhz6AgntfGood76P0uM/DYiM34f1xt/X%2BmB/47yAS1IF4CmCQOgbA%2BB8NcbbJQY7PZsgMHu0RscnBIC6FWAIffEh8TyGUM4NQgg6BaH4IsIwtxzCNmsPiconqzgICuFMeNARpQFF6DEXUT1KQZF1AMfMLRXRdEmI0VI9hrr6hqNDSI4xvRA3mL6JY31edlirHsVm2%2Bly2mcEtMQKZMy5lwtau85Z0INABPwJbP5edAXdMidE2JlBHHFNKUsjJ5Imnkhppk7JkhxpXPabYTphdxaSxlnLBWELQUVw1mwCZJavEsAUDaQ0Noq2MlGObet6zNnO2QQ7CQ6qXYHK1ToEALNTn%2B03hckOHt%2Ba3KjjHYtLB12bu3buxSowvmLt%2BdsLYYSp3FxBaMyuysgNDC3ckZI0Yd2M2jHuggG0117LoCituHcu6DyxfhoeI8OET0JYIYlocyUrzEJSz%2B1Ld78q3vSo%2BJ8PZn2QBfdljZb6I25d3Plr81xCt4CKtIYqAG7yld0vgECFBQJgXAhBn8VVnrQRqq9WDb26uMDawhxD4BkIoZkDe1FQz6usHapGDqsDGpsdouNXCeE5Bjd6oRYag2FEyIG/1mRE1GJdXUPR6iXNmIc0FhNGbDFmKjaFpRkWfXRazbYnNjsn2tJfUWyZ36t22j/YCADEBAkNtzmBiJpAokxKGPE2%2BXaQBmCWVsLY/h/AZMRfTLY5JqkZb5pwDpItyuJLMBUrg/zKb/MZpUswOTySFK2M%2B3rAsulF0cWbHrbi%2BvLcJl/OI6RnCSCAA%3D)

## Links

- [source code](../../../../conceptrodon/varybivore/look_for.hpp)
- [unit test](../../../../tests/unit/varybivore/look_for.test.hpp)
