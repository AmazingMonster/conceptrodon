<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::KindredLookFor`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-kindred-look-for">To Index</a></p>

## Description

`Varybivore::KindredLookFor` accepts a list of variables and returns a function.
When invoked by a predicate, the function returns the index of the first variable that satisfies the predicate, or `-1` if it cannot find the variable.
This function is created to exhibit the power of fold expression and to compare with `Varybivore::Find`.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> Pred
-> Preds&lt;V<sub>0</sub>&gt;::value ? 0 : (
   Preds&lt;V<sub>1</sub>&gt;::value ? 1 : (
      &vellip;
   Preds&lt;V<sub>n</sub>&gt;::value ? n : -1
   ))</code></pre>

## Type Signature

```Haskell
KindredLookFor
 :: auto...
 -> template<auto...> class...
 -> auto
```

## Structure

```C++
template<auto...>
struct KindredLookFor
{
    template<template<auto...> class>
    alias Rail
    {
        static constexpr std::make_signed_t<size_t>
        value {RESULT};
    };

    template<template<auto...> class>
    static constexpr std::make_signed_t<size_t>
    Rail_v {RESULT};
};
```

## Examples

We will look for the indices of `2` and `-1` in list `0, 1, 2, 2`.

```C++
/**** IsTwo ****/
template<auto I>
struct IsTwo
: public std::bool_constant<I == 2> {};

/**** IsMinusOne ****/
template<auto I>
struct IsMinusOne
: public std::bool_constant<I==-1> {};

/**** Metafunction ****/
template<template<auto...> class...Args>
using Metafunction = KindredLookFor<0, 1, 2, 3>
::Rail<Args...>;

/**** Tests ****/
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

If no variable satisfies the predicate, then the fold expression is evaluated to `false`. In that case, `-1` is returned.

Here's the entire implementation:

```C++
template<auto...Variables>
struct KindredLookFor
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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKzSrgAyeAyYAHI%2BAEaYxAH%2BpAAOqAqETgwe3r4B0ilpjgKh4VEssfH%2BiXaYDhlCBEzEBFk%2BfoG2mPaFDPWNBMWRMXEJtg1NLTntCmP9YYNlw5UAlLaoXsTI7BwA9ABU%2BweHR8e72yYaAIJ7BwDUACKYSa6MyHiYCjeHZ5fXJ39H3wu5yBZgAzGFkN4sDcTKC3AQAJ5PAD6BGITEIClh2GB5nBDEhXmhsLcyGm6CwVGxuJ%2B/zpAOBv12NwAkiwkvQ2IImN1PgdAUz6f9AcCCJh2QYxSSmF4iAA6BUANUaeCY0XoWNBOMu02IXgcNwA0mF0MRMOhgqhUABrABiJFxAHYrJcbm6bmKJTzMCTPRzvdLZagFXLsTdIUwFB9lGb8KIpVrge6brr9QQbjHUEQAEoY2hJ90mZ0F5Nu6Y8vDIcMCaaYVRJYg3GVEG4ANzEXh9rtLbqLLouPZ7Jn8Vn8dwgSxuAFow%2BSQCAWExrZhkWlgOF0KiSWkAF4rgjU7uDwvFo/H0tzhdLldrjdbuG7/dhtBeQRxGHOqdcIt3WH98%2BDmaBDrAwJYAe6EAhkWbjQRA1jWC%2Bb5kBmsaVgGcLKsQqrqu82Lzu23iYEsk6wraMJnuB1avmKjYgNO36gv%2B4E/hOYHJj%2Bf5gRxjE0gO7p%2BpKPpwgJ6FuM2wYKs%2BBhRiGFzAGa4qMAQmranxbpeGkRg3LmdAwqCdwoVmqA6fmcJyQpXLKVBiY8Zc3H9oyQoMrStzYKorAcpgfL7AKTlfLxTKsgoAAqADuqDeacoriv6CZiUGrKHhcqYGiyIXhcCdFJF46qVimBDoPO0RWrQyJoAw5aCCSLJ6b%2B%2Bk3GYYZ9vZAWHEFACyYQaQA8uEkWAiJcXiYliY6miaYdV1Ci9V2FxZTltB5ZexWeGVNYNFVcIsrCdV3F%2BTXFo6dUOS5%2Bw3O1mANFQr61AI/XRV6cWDUJ8XypJWrhtJCiycQwAqcCGlhMA52XUw10EryO1GiasaWja9rECSGikDcXAo2YKOgkl84mSSFy/d9704rZQKncywXvMp91jRWyDIpGShNBAF1XTd3TVelqB4SABGdrVUNmEsnE044dMM3EBDM6D4O3aBW0KJ1DA9eE3O815O1Q1%2BQuMRwKy0Jw/i8H4HBaKQqCcDBljWCmawbOrYI8KQBCaLrKzWrkcoaAAHGYZgAJx%2B1w/je17XCOo60j6xwki8CwEgaMjxum%2BbHC8AoIDI87Ju66QcCwDAiAgGsBDZQQ5CUGg7J0HEESsFsqhewAbFOjeSDcwDIFWUhymYvDmoQJB4IVaP8IIIhiOwUgyIIigqOo2ekLoaOheiSScDwesG0bLtm5w3WyqXNyoFQNwN83rft53qOSD3NwQB4Vf0I2eJcEsvBZ1oKwQEgldJNXZAUAgL/f%2BIBgBSAxjQWgNF04QGiDvaIYRGgInXrwBBzBiAIm6tEbQNQs6O0rpZXqtBkELywNELwwAxK0FoOnbgvAsCLiMOIUheAzS1FbO8HedYaiyi2I7MIYoo6m0WtEdEGCPBYB3miPAcc6GkA4cQYqSgHiMOAItIwLsVhUAMH9RUbxQrdSeMbR2o9hCiHEFPUxs81A7yXvoQwxh4KWH0HgaI6dIArFQEkbotCpzkh2qYK2lgzDJwUVhLA7iJwdC6BkFwDB3CeFaHoEIcxSjlD0PkdIAgJh%2BDRpk7oAw0nDDRtUWWvRxiJJyCUzouC6gzEKUMeIJSZg5L0OWJoDSFhNJWAoW2mwJCbw4IbUgSdeAp1Pk3FubcO5dxvmYO%2BuAB7Pwdm/J2miVgIEwEwLA8Qonu0kKCOUftQQRw0JIMwkhG4J38I3P2%2BhOAx1IHHUEXA5SNy4I3L2ftQ6N0CEHY5jcRk7xTmnDOazs5fwLt/IuB9ZTlyAagR%2BNc66cEaCwVsjopxME%2Bg41Gfs5SvNNv3Ig4S9CmPHhY6QVilA2IXroDGK8mBrzoYM4Zozd4cH3iXWUR8T5nymTirSXB8WErvg/P%2BT8YRgkFu/TRucf6IolXEeFwCn4oAMEYYVXBkaQOgZQOBC80FIJQaQI1GCsE4IcCaghSkiEkNNmQihVCaEmoYQ45hDrWG1I4bQolqgeFihNQIzoO8RFiIRBIrYptpGyMdgopRmAVHuqBnK7RTBdH6MMYwE15LzGTypbIax89Tb0vsRowJVhnEiMiZ47xGRfH%2BP0hW6wISxlhKHpwjx0TanOAgK4VpaMUklEaRk1IWTMiVNyckMdBTUkjuqTEgQ5TmiTraTUsp9S51dLaS01dzS%2BidPSa/VY6x%2BnHqjmy4FnAJnnzbhGIVIrPYLPwCSqVLzVkf1dqQTZ2zhhRKjo855%2BKzmOn8H7cOoJzmXMkGjdlILbBgs/ZC%2BA0Li6lxVYq/%2Btc2CouICwC%2BLAFCtirK2YVcpBLTD7i%2Bwew9p5mInhIAtM8aXFp0CAUEpBGXMo3vcoZ28F4py5YfY%2Bp8CNEZI2Rij6Z76YclXiUEH65XQtVcqwBKn4jEaSEkZEpG/bIik8iVQrc%2BB0D1bA%2BBiCMEmrNZg7BuDrWIsIQwYhO9HWULEC6uRbqmFRvoV69hnCF7cOQLwoNb4hG8DDUgyNUisKxt4PG1IibxTJo0RCvgOiFB6MwAYoxObZAUvzXRottj2NlscUEmw1b4C1p8ZwbYc5m3BNCXEcJnaomlO6HEhJ2Qp1DvmEe6dBQMgDqG%2BOw9xTu0br6KNzrdSD1bsG%2B0ldvWd0LeHdu49vTT2T1Zfx5O16jNt0I8RtsknvTTGfUst9r9ZUQo2VsnZlBBmAZAP7OUoJQSVDOdqjQn3HSfKBQJzgoLM7rNIPs/wRyw6OgTl7SQgcuA%2BzMICqOoJ9tjJB%2BCz%2Bgze5A4O6nbHX6FFpGcJIIAA%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/kindred_look_for/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/kindred_look_for.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/kindred_look_for.test.hpp)
