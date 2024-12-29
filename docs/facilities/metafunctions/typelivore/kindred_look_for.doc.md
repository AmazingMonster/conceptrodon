<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::KindredLookFor`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-kindred-look-for">To Index</a></p>

## Description

`Typelivore::KindredLookFor` accepts a list of elements and returns a function.
When invoked by a predicate, the function returns the index of the first element that satisfies the predicate, or `-1` if it cannot find the element.
This function is created to exhibit the power of fold expression and to compare with `Typelivore::Find`.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>n</sub>
-> Pred
-> Preds&lt;E<sub>0</sub>&gt;::value ? 0 : (
   Preds&lt;E<sub>1</sub>&gt;::value ? 1 : (
      &vellip;
   Preds&lt;E<sub>n</sub>&gt;::value ? n : -1
   ))</code></pre>

## Type Signature

```Haskell
KindredLookFor
 :: typename...
 -> template<typename...> class...
 -> auto
```

## Structure

```C++
template<typename...>
struct KindredLookFor
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

We will look for the indices of `int**` and `void` in list `int, int*, int**, int***`.

```C++
/**** IsIntDoubleStar ****/
template<typename Element>
struct IsIntDoubleStar
: public std::is_same<Element, int**> {};

/**** IsVoid ****/
template<typename Element>
struct IsVoid
: public std::is_same<Element, void> {};

/**** Metafunction ****/
template<template<typename...> class...Args>
using Metafunction = KindredLookFor<int, int*, int**, int**>
::Road<Args...>;

/**** Tests ****/
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
struct KindredLookFor
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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCAArAAcpAAOqAqETgwe3r56KWmOAkEh4SxRMQm2mPYFDEIETMQEWT5%2BXJXVGXUNBEVhkdFxiQr1jc05bcPdvSVlgwCUtqhexMjsHAD0AFTbO7t7%2B5vrJhoAgls7ANQAIphJrozIeJgKF7tHp%2BcHX3vvJ8d/ZgAzMFkN4sBcTIC3AQAJ53AD6BGITEICkh2H%2B5mBDFBXnBkLcyGG6CwVHRmI%2B3ypP3%2Bn02FwAkiwkvQ2IImDVXjtfnTqd9fv8CJhmQYhQTYXdmGwAHSy7CsxgENGAjGnYbELwOC4AaWC6GImHQAVQqAA1gAxEiYgDsVlOFwdFyFIo5mHFwpZrvFcMYrEwsul6IuoKYCheygN%2BFEYpV/0dF3VmoIFwjqCIACVUEx0HHHSZbbn4w7Jo5kMGBMNMKoksQLkwvEQLgA3MReN32osO/N2k6dzsmWJWWJXCBzC4AWiDxJAIBYTFNmHhaWAIXQiIJaQAXouCOSO328wX9wei9PZ/PF8vV%2BuoVud0G0F5BNEIbbx1x81dIT2T32DQRlgYQtf0dCAA3zNwIIgaxrEfZ8yBTSM8GjN0oXlYVFWVbAZxbbxMDmMdIXNCFjxA8snyFWsQAnD9AR/EDP1HYD40/b9gNYuiKV7R1nU9GNoQ9UVUOhH0pX9WUHwMMMAxOYADQwwQsOArw0iMC5M2zCFASuRC01QDScyhWT5LZJVwNjTjTg4ntaT5GlKUubBVFYFlMC5bYeTst4uKxEEwTc70ESRFElT3P4HO2RkFAZQQriWCJ6C6WtvNOXihMC302AudDTLCxMtQZaLYvixKRn%2Baiki8BLkITAh0BnPAFCXP0CRyxVSAuYICG2INu2sri6SigA1VA8HQdzDkFQSvShCVMrctrBDypEk2G0ac1OCqqtoGqz0a5q2FahVBA6pt1t6gtrS/SzwrOXYLgAWUweoqCfBwMgm340pmgSXX4uaxPM7BgykhQZOIYAlNOFTgmAR7nqYV6cU5SEdN1Bh9UNY0zUtYgCS6jqus2QnBG2Enus2MKZwMgkTghsGJIsmyIvpAAVZ4lU%2B/4S2Q%2BFQyURoICel63pqAlCpigg4u2zAkvRHDWwC7TUYuMw5jYtV6lLPmw2iAghYRpH3oEcWFBGsb5ZAXC2y066dPfdWbo4BZaE4WJeD8DgtFIVBOEgyxrATJYVgCoEeFIAhNGdhZTTiSRpQ0eIzDMABOFOuFiRP4i4a1rWkV2OEkXgWAkDQNFIT3vd9jheAUEBy8jr3ndIOBYBgRAQCWAhKoIchKDQZk6GiUI/U4VR4gANnHCfJAuYBkDLKRpTMXhDUIEgxr0fhBBEMR2CkGRBEUFR1Cb0hdDaAB3ZEkk4HgXbdj2o59zgAHkGx7i5UCoC5x6nme54LwuEvMwFwIAeEHvQWsWIuBzF4I3LQCwIBIAHkkIeZAKAQFQegkAwApBmD4HQSidcIARGfhEYIDQYR314BQ5gxAYSvwiNoTADgaGkAHqZV%2BDBaDULPlgCIXhgBuDELQOu3BeBYDnEYcQ/C8AGnek2Z4z8qysIbGscOXUqjPx2hEZEDCPBYGfkiPAJcJGkCUcQCIqRMA3GkcAHaRgo4LCoAYSGQ0niX1fpKdh29hCiHEAfPxx81DPwvvoQwxgYKWH0HgCIddIALFQEkGo4jxzElRqYAOlgzBV0scQMayjEntFYTUFwGMxitFIIEYIfRSgDDaHkdIAhKm5FSM0hg0x%2BgxAmFUUpnQRhNE8C0PQdh%2BkCCSj0WpMwGm2EGa0iYgyun1J6QsBQwdVgSAfhwd2Fdn7V1/pPaes956L3jqAiAuB17QLDnAiOziFgIEwNmAYo5SCx0kICaUKdAR5w0JIMwkgJ5l1iBPFO%2BhOBF1ICXQEXBpQTy4BPeIKds4T1iJIDOPyJ57LPtXWu9d7lNyQe3ZBncP4Nj7lg1AkDh6jw4A0FgTZrTjiYCDSJwCU7Sjhd7NeRACn1TaH43egTpDBKUKEs%2BugCHXyYLfCR2zdmV14NXd%2B3cGxfx/n/Y5bK1JcE5dysBEC0FQIhECNW8DnEtxQdS410RKXYKgSgAwRg9VcHLjQWgxDKBkLPnQqh7C/UMKYSwth5jOGKm4bw5%2BAihEiNoGI9hUjImyO9vgBRjglHiJ5aoNRQp2FaILt7XR%2BiYSGLWN7ExZjw6WOsUoOxybYaWtcUwdxnjvGMF8bIYV%2B9RWyBCafb2UqIlOKyVYGJuiElvOSakzg6S6qZOiRYXJyr8mFMnWsvpxs/AQFcAs6pGNlmzEae0moe6mk1EPbMsZW7Jl7uvTUSZl6elzO6HepZ0zulbMWMsTZsCIU7Kfrizghz/6zxDLq/VCcwFXL5aa2FdyEHR1IE8l5MQ3kFyhTCzl/zrSxBTrnQEAKgUYpxVXTg%2BKG6Wtbh3LuPd7U2vQSPNgnAGUAJYAoJsZYmx6ulEJYYq98B8s3oKrtASe2H3kOKgdOgQCAlIDKuV99/2Kv2W/clyZv6/zYxxrjPG%2BPJnAQxk1WJAQIao9amlGD%2B5GYGJxpISR4TcZTvCfT8JVAz0IZ66IJCfXe0DXw8O/ng2lPYeGwQka%2BGpswII4RojxHhyTTI8tkj5H9MzSonNyB1H5ufIW3gxaqFluMQUqtvAa02PrTIxtRK%2BBuLNm2nx5ihViYkL2o%2BUmwmyeHVE7JNgJ3wCSSkjI4j1jTlHdYZdPtV1YHXSUrd5T3DDPGPuo0H6VltPyBkM9J6MhPtGZuh98yltVPvQMqYa2j0vtGMd0Z77iifr/esn9%2B8FWAbIxwLTs92OcebHp10wxoOCZIHB2BFqiWPOeVgND2zMMgFTtKQEgJYiZwxWXRH1okWkeVeR2wBLEMEXeSASQsRvk52tGXeIkh05cCTmYbFBdARvexzXQliDtkryxy/Fn%2BOFiWLSM4SQQA%3D%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/kindred_look_for/implementation.hpp)
- [Source code](../../../../conceptrodon/typelivore/kindred_look_for.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/kindred_look_for.test.hpp)
