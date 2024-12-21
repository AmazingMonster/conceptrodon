<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::LookFor`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-look-for">To Index</a></p>

## Description

`Pagelivore::LookFor` accepts a predicate and returns a function.
When invoked, the function returns the index of the first argument that satisfies the predicate, or `-1` if it cannot find the argument.

<pre><code>   Pred
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> Pred&lt;Arg<sub>0</sub>&gt;::value ? 0 : (
   Pred&lt;Arg<sub>1</sub>&gt;::value ? 1 : (
                &vellip;
   Pred&lt;Arg<sub>n</sub>&gt;::value ? n : -1
   ))</code></pre>

## Type Signature

```Haskell
LookFor ::   template<auto...> class...
          -> auto...
          -> auto
```

## Structure

```C++
template<template<auto...> class>
struct LookFor
{
    template<auto...>
    alias Page
    {
        static constexpr std::make_signed_t<size_t>
        value {RESULT};
    };

    template<template<auto...> class>
    static constexpr std::make_signed_t<size_t>
    Page_v {RESULT};
};
```

## Examples

We will look for the indices of `2` and `-1` in list `0, 1, 2, 2`.

```C++
template<auto I>
struct IsTwo
: public std::bool_constant<I == 2> {};

template<auto I>
struct IsMinusOne
: public std::bool_constant<I == -1> {};

static_assert(LookFor<IsTwo>::Page<0, 1, 2, 2>::value == 2);
static_assert(LookFor<IsMinusOne>::Page<0, 1, 2, 2>::value == -1);
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
template<template<auto...> class Predicate>
struct LookFor
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr auto value
        {
            []() -> std::make_signed_t<size_t>
            {
                std::make_signed_t<size_t> counter {-1};
                return
                (...||( (++counter, Predicate<Variables>::value) ? true : false)) ? 
                counter : -1;
            }()
        };
    };
        template<auto...Variables>
    using Page = ProtoPage<Variables...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCAAzAAcpAAOqAqETgwe3r56KWmOAkEh4SxRMQm2mPYFDEIETMQEWT5%2BXJXVGXUNBEVhkdFxiQr1jc05bcPdvSVlgwCUtqhexMjsHOaxwcjeWADUJrFuXo60hACeB9gmGgCCG1s7mPuHyMPoWFSX13e3BJgsSQMfwObj%2BAKBmBBTGOqAAdPDLrttkwFApdspiJh8KJgbErrdhsQvA5dgFUKgANYAMRI3xMAHYrLddizdmDAUxcW5oUR4bCAGoNPBMCL0BRfZmswnEgjo4ioIjKJjASGSlkMpk3Vna3aTRzIJECYaYVRJYi7HmoXYANzEXlVWp16sZ3ydTpMAFYrB6ACIQOa7AC0iLeIBALCYFMwAH00sAQuhowQQWkAF4x5N411u7Ua7M5p2h8ORmNxhNJlN4dMVvGGryCaL7RmBrgMn0HTUFt2YgjLBj5rusiB8hluUcQXYQazWND1v5kOVYvA4yGHQXEYWizDivFh23eTABg5UtlEp4gXZUMRKOZH2IngeDusN80Xlsdx9utv%2Bz/O9uxTtWTbD81R1dkIShGE%2BXXTcxQlR0WS8NIjHRZUngOH05QVVAlRVEEYJFMURyzAC6Xpf9NW%2BAB6AAqOj6IYxiqOohjdgAFW3Ag0QY5jbloxiBPo3ifjuMxNgYbYvD2EFjjoc54O%2BcDOVXbkYV2ABJeDpRJdSFDYgB3VBvgvJIvFFZddQIdAwwiclaGjNAGEmQQQXU55/0wsxETzciQJEpSuUtDStIIIkdIUABZYIkIAeRCYzdlM8yDSLWzPAco16hcw43IwjCg1bWsfIoukCXqfVoxRJRGggMlKRpYhXL0wzLjDXCVI0UhdjaXYzC6rzdxAfd7Xc/KzDmPy9WXSrUWiAhavJalaRyyLooUOLV2wNq0JBTruv6/rWqGu10NiDyComgCOAWWhOA9Xg/A4LRSFQTgx0saxdSWFZ0LEnhSAITRroWCkQA9elYQSAA2elYhhjQElhgBOWJ9E4SReBYCQNE6x7ntejheAUEBOsBp7rtIOBYBgRAQCWAhTIIchKDQAE6GiUJWDWVR4ihwMockXZgGQA0pFhMxeCXIgN2stp%2BEEEQxHYKQZEERQVHUcnSF0Np9OIJgkk4Hgbruh6gZezgYuORndlQKhdh5vmBaFkXuskcXJw8Nn6HNDYuDmXgya0BYICQVmknZsgKAgcPI5AYApD6mhaHnYmIAic2ImCBoziN3gs%2BYYgzhiiJtEwBw89IVm2EEOLaFzrWsAiLxgG5WhaGJ7heCwCMjHERu8ExBw8GtbdzZNcvjjWf7gj%2BW6tdOCJ9aLjwsHN0K8CxrvSFH4hbKUH1/kMYBTiMIGFioAxgAUfk8EwfSYqSRhK/l4RRHEFXX/VtRzZ1/Rj5QNOSw%2Bg8ARGJpABYqAkg1E7oGN4GFTAfUsGYfGu8ZZjwge0cuNQXAMHcJ4Fo/g8HTH6DENoeR0gCDGK0ZIqRKEMBIaUAYEwqjYM6CMJoBDxhYOHgILojRGGzAmBw6hehJgCOCH0JhZCFgKG%2BqsCQJsOD3VIHjXgBMHa835oLYWot3ZmEnLgQgJB9h/QDgDc%2BCwECYCYFgGI/pSCg0kLEWEKN6SSA0JIMwkgoY4w9FDJGaMOAY1IFjWIXBYRQy4FDeISN4jRI9JILgHoUZQ1UebAmRMSYWPJiHGmoc6bW2OMzGOqBvYcy5pwBoLBrT0kDEwJEBgUJcCRrCCJz0pYkDwLLVWb8lYSGkF/JQP8ta6D6nrA2eclEqLURbDgVsGbHFtvbaptT6mNOPt1Vp7TPZlIjj7UxsRxqB3PpTMOezI4lNjj7EAqy6nIiMC0rgnVk6p0oBnLWBcc6Vy%2BUXEuZcK7b2rowAgdcG7PSbi3NuHdK492Pv3CFg82Gj07h01Qk8/iV1nlUc2i9l5nFXmsZ6G8t7/V3vvTAh9e4n2CKAXJfAr43zvg/J%2Bj1/qv0Vh/QZshv6a2emM/%2BZ9EFWGAYvcBDioEwM4HAqyCCgEWBQeotB3SMEOLsGw5wEBXCiLaIESRMxmG0PyBkHVRr6GCMNeq3htQRFcJoVamo/Cej6tIWI212R7UcItTIxYywFH%2ByCTMjJnALTEBqXUhpDzgBbLabCDQhj8DS0Of7E5uSrE2LsZQJRISwmtM8fSFJ9JYZeJ8Uk9JWtMm2GyUHCmVNab00Zlci5PtOZsCqWG52LAFDWgNNaFpsIITDElomrpPSOXv2VtytWwy%2BU6DiKQCZhsu7TLNhWy2RTZR21DSwTt3be39sHbKCAXt9mNg2LEcxNaQ7nPKVHFmzaBg9qSEkaMfakbRkPZVDtgy6BvPTpnbORcfmAeLqXbBldgW1wYPXc2kLW5iBhdvOFfciXdyRcPFF490XICnlihs89np4pzoS9eG5SW8HJakSlR8%2B60tOZfZUTL76P2ftvcd/TP48pnb/edTTjDypAWA%2BAkDoEZE7lRUMwrrCKpesqrA4rZGsOtbg/BHqiHoG9bkOhNRTUUJqJplhHQ%2BHusIYZjVNqpguukW67oprxHOuKK6gNci/XKxXeW/GIbqm7p7TaA9ylhgJuMb7Mxqbg7ptsQMBx88c0gDMK02IsQPQek8c8hGsR6QxI8%2BozgWTSaWMcSALxkSuBHKhkcpGUSzC%2BPpEE2Iq7POExyeFoJEtstzLC8DHe0Q0jOEkEAA%3D)

## Links

- [source code](../../../../conceptrodon/pagelivore/look_for.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/look_for.test.hpp)
