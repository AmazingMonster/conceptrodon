<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::IsSameAs`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-is-same-as">To Index</a></p>

## Description

`Typelivore::IsSameAs` accepts a element and returns a function.
When invoked by an argument, the function returns true if the argument is the same as the element and returns false if otherwise.

<pre><code>   Target
-> E
-> E `same as` Target ?
   true : false</code></pre>

## Type Signature

```Haskell
IsSameAs
 :: typename...
 -> typename...
 -> auto
```

## Structure

```C++
template<typename>
struct IsSameAs
{
    template<typename>
    alias Mold
    {
        static constexpr bool value
        {RESULT};
    };
};
```

## Examples

```C++
/**** Metafunction ****/
template<typename...Args>
using Metafunction = IsSameAs<int>
::Mold<Args...>;

/**** Tests ****/
static_assert(!Metafunction<int*>::value);
static_assert(Metafunction<int>::value);
```

## Implementation

We will use partial template specialization to detect if the two arguments are identical.

If two arguments are identical, the compiler will select the partial specialization instead of the primary template.

```C++
template<typename Target>
struct IsSameAs
{
    template<typename Element>
    struct ProtoMold
    { static constexpr bool value {false}; };

    // This partial specialization will be chosen
    // if `Element` is deduced as `Target`.
    template<>
    struct ProtoMold<Target>
    { static constexpr bool value {true}; };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;

    template<typename...Args>
    static constexpr auto Mold_v 
    {ProtoMold<Args...>::value};
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCAAzAAcpAAOqAqETgwe3r56KWmOAkEh4SxRMQm2mPYFDEIETMQEWT5%2BXJXVGXUNBEVhkdFxiQr1jc05bcPdvSVlgwCUtqhexMjsHAD0AFTbO7t7%2BzvrJhoAgls7ANQAkixJ9GyCTDUXu0en5wefB28nxycEmFuBgBJlibgIAE8koxWJgLgAVBrATAEUHYP7DYheBzXBRCWEnBR/EwAdispwulIuAKBT0woPBUJhbAu2HujFRsXRFKpmOxBAuymIqCIAFlPOg/lSLqSLBdJo5kBc0AxhphVEliBcIqhPBcAG5iLxw2VUMRKUkAEVBcqtNuJPMp63WCIQeAUFyS3TwYnl0OQPtoeAAXk8MhcAO50WjauHIBCpRhSqnOi54KgygBsGjZgI5JmzaY9WHQ2Mw6AuTA9BY0iOIyNR2YAdMnKTS7nSGWjW/KCFicUKRahxbRJWC6w3u46ZWTe2GlSq1RqtTq9YbvCayX3jXbYraSda9w6TtL28D6WDIdDmGwm3eTsBiJg84IiVye140kYLiOK6DLYKwpihKDIPk%2BL4EAod4tu%2BR6nD2Z6dpeTI3pg0EnPWb7cievL1IqyoCEumqVl4RA/hKAD6%2BoytOsqDsBo6gZh0FoiAIDrjuB72vBXFwb87xfJ8PwfJsrKqKwdxwq8fwiYJhzHiJP4okwVBeAwDjhtJpyISCyHXrC6GYVOJyfsEwBKfUqnqc8/64vibCEgywScthbG/kxwBQXe3Z8TJuwIpgwwelphJ4XgyAUVWSiNBAYBgKKylWRpAhOYImysexRqYHM3GhfOkUKNFBAQAlllqclDCpS5bEcdluUcAstCcAArLwfgcFopCoJwbjWNY8pLCsJpmLEPCkAQmgNQsADWIDNZITYaPEZhmAAnKtXDNUt8RcCSJLSE1HCSLwLASBoGikO1nXdRwvAKCAF0TR1DWkHAsAwIgIBLAQSSkeQlBoLcdDRKEsKcKo8SZgAtJmkgXMAyBKlITZmLw5aECQeDoHo/CCCIYjsFIMiCIoKjqM9pC6G0EbEEwSScDwjUtW1k1dZwADypG/QKqAZhD0Ow/DiMXMjZgXBAHhA/QWrmKNcy8E9WgLBASCA0kwNkBQEBqxrIDAFIZh8HQALEPdEARKzETBA0EIM7wVvMMQELsxE2iYA4dukIDDwEOzDC0LbFNYBEXjAG4Yi0Pd3C8FgLCGMA4hB3gT4afqgWs%2Bq7ukWsY3OVUrNBhEtNOx4WCs32eCndHpBp8QOpKJagLx0GRiTQsVAGJ5ABqeCYBG7PXp7uPCKI4hE8PpNqKzVP6PHKB9ZY%2Bh4BE92QAsqBJDUUdQ8MY6WqYljWGY1218QWPp2v7TuzULgMO4ngtP4d/TP0MRtHk6QCGMrTJKkn8MC/UoAwJhVGvp0EYTQH7jCvhVLojRAGzAmBA7%2BehJjwOCH0IBb8FgKEGqsCQTMOCtUuqzG6Fx%2BYwzhgjJGC0xYQFwBjGWI0uDy3Gm3BYCBMBMCwDECAM0QCSFiE2VasR9oaEkGYSQ2YNDNUzKtfQnBjqkFOqNJsmYuCZniKtHamZ5qbREZmEhFMbp3Qemw56ysPoqy%2BlzP6WsdbS1BmwTgDQWD6hJFDJgyoDDfi4KtJsXBFpo3wEQM%2B2M2jD3xmPaQE8lBTwproQ2NM6Z20IcQq6vAbqcx%2BqRC4vNyGQ0od4%2BOIt/GBI0OLSW6tpYyhGmYVhisXrWIcdEf62tUBSwGMgHx%2BsNoXRoLQE2ZsLYUwdjbT2YynYuzdh7au3sOR%2BwDqzYOodw60Ejp7WOzc1idXwCnRwaco6dUzsgbOns86HU6oXYuEJS47IVmfKuY1a710wI3OORgW6gAsXwTuCge59wHowIesgomExibISe5NOqJNnq3A%2BVhF6F1Xnwrqm8Mjb13v%2BBFR8T7RDCRfVFdgwHOAgK4FBbRAgYJmMA3%2B%2BQMgUrpf/BBtLiWwOQVAn%2BbKahwJ6NS1%2BqCOXZC5RAll2DFjLHwSwhRRCWbGM4AUgWcNuklL8QExa4sGGhNqXLBW7DSCcO4QMVFh0lEqP8eIkkzVVp7ViBIqRkg2gZLZrdWwZjGmWPgNY763M2ktOIE4tYrjBYsAUPqJU%2Bo1XnmGMExhWMcagtHuC4m8g4nQp0HEUgyT6bRzSXK66HNbE8z5iGsNEao10mGJUjp1Tog6tiA0tur1VY1o1n61t0t2LICSEkKifiKLRoIBRVQsMjaDOiMMy21snYTOnc7V219PbzMEIswOuzMAhzDhHKOY0tmfPuaQPZYDDkZ1UFnAE5zBD5wptcm2dzy6PM9i8xM7zm5mSbR3Jg3de790HtXSJSaJAQpJmm6emaenz0Pki5eKL17osIpwdYu9IOIosMfTJp9z6wZgTfMld9GVUuKAK9%2Bf8aiMo/jUMVqDQHsu6Iy7l4Cpj8qwYKujnLWPoKIyx6VuDJWEzzUYgtHByGlvDQaCtAIq30JCSQHVLC9UWI4VwnhlBCFmpAGtJssRYjNS2o6862mSSaME5kzgpjHr6tmpIZqwjdoknOvESQG0uDLTMIYw6sR82mddR6whqMTMuoU0rBYtc0jOEkEAA%3D)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/is_same_as/implementation.hpp)
- [Source code](../../../../conceptrodon/typelivore/is_same_as.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/is_same_as.test.hpp)
