<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::IsCalmful`

## Description

`Omennivore::IsCalmful` accepts a type.
It returns true if the type is a packed `Calm` and returns false if otherwise.

<pre><code>   Type
-> Type == Calm&lt;Items...&gt; ? true : false</code></pre>

## Type Signature

```Haskell
IsCalmful
 :: typename...
 -> auto
```

## Structure

```C++
template<typename>
struct IsCalmful
{
    static constexpr bool value {RESULT};
}

template<typename>
constexpr bool IsCalmful_v {RESULT};
```

## Examples

```C++
template<template<template<template<template<auto...> class...> class...> class...> class...>
struct CalmLike;

template<template<template<template<auto...> class...> class...> class...>
struct HailLike_0;

template<template<template<template<auto...> class...> class...> class...>
struct HailLike_1;

static_assert(IsCalmful<CalmLike<HailLike_0, HailLike_1>>::value);
static_assert(! IsCalmful<int>::value);
```

## Implementation

```C++
template<typename>
struct IsCalmful
{ static constexpr bool value {false}; };

template
<
    template<template<template<template<template<auto...> class...> class...> class...> class...> class Perseverance,
    template<template<template<template<auto...> class...> class...> class...> class...Tranquil
>
struct IsCalmful<Perseverance<Tranquil...>>
{ static constexpr bool value {true}; };
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISVykrgAyeAyYAHI%2BAEaYxBKBAA6oCoRODB7evv5JKWkCoeFRLLHxXIF2mA7pQgRMxASZPn4Btpj2jgK19QSFkTFxCbZ1DU3ZrQojvWH9JYPlAJS2qF7EyOwcBJgsiQZbJgDMbgQAnomMrJiH2CYaAIKTxF4OANQAkgpuYixUXrS3dxMAHYLC9JkxHMgXmgGJNMKpEsQXtFUJ4XgA3MReTAvYEWKhiJTAgAih1BJLJAIBWx2eyu90ObgBLxZLxpuwhVyO7LpjJ5nL52w5%2B25Qt5RyYXiIADpZddoQYFApZdL5chFcq5QdsAqmEqVWqNQbtbqlS9lHElOi4oZ1qRmaz%2BSLjmKBaLaW6XR7nZKZVqdeq9ZrVSbA/r/abg4agyqACrEQwARy8dCp2oBj2eBHen2%2Bv3%2BRwtxCtNoY60Z8aTKdoxpu6YZILBdUh0IEcIRSJRaMx3hxeIITyuQNJB3Jw8pDPuAHoAFRz%2BcLxdTgGz%2BcvWOYSYKF4L5fTxcH3dU%2B5Orle4Vn0%2BC72X10%2BqWoWuRp9hqOho0R1%2B1jMDrMvL60CwoQANZclYk53Fe7oXteMHQeKXwPi%2BH4hgGKHRuGqE/k8rwABJMHQIGYAA%2BhoE6Aied63jesEIVBiF%2Bqhz6fuh74xv62F/vhhF4KBxFcORP4QngyDEUGcQEBAHwAT8fyMjJRGMtxtBEaRpAvMpqkCem2ogCAPbYgs5HgpCYlKhJEBgGAOYyfmjJhAQ1x6QZmBGaOHBLLQnAAKy8H4HBaKQqCcEyljWGCKxrH2ZgHDwpAEJoHlLMBIDeWY0pAmYkgABzZd5GgAJxpRoABs2UHPonCSLwLASBoGikP5gXBRwvAKCADUJQFHmkHAsAwIgIArAQiRSuQlBoDsdBxBElycKo2UlQAtCVkgvMAyBQlI0pmLwmD4EQxB4Ogej8IIIhiOwUgyIIigqOo3WkLogQAO4JoknA8J5Pl%2BYlQWcAA8lKo3ZqgVAvAty2retm0vNtZgvBAHhTfQSLmLFCy8F1WhLBASCTYk01kBQEAE0TIDAFIZh8HQWzFpQ0R/dEYT1Ccn28MzzDECcAPRNoVRdXFk1sIIAMMLQbOPVg0ReMAAG0O13C8FgLCGMA4hS3gxAC3g1qK4F8JVFKGxxQ57R/bQeDRAm3MeFgf0DngtVK6Q1rECiSjEtsauW0YiVLFQBjAAoABqeCYC9APnP5cVncIojiNdcd3Wof3PfoasoNY1j6Fb7WQEsqCJJ0sKcEtkzoIcxKmGFlhmM1btHVg%2BcQEslTVM4ECuGMfiBCEMzFKUejJKkJc98PeQl30g/zG0HQ1FM48VO0OtdFM08DGUww9Ev28NBvcxlG3kXrBI30cL5jV/S1EOLSta0bVtkg7YjuCECQuIxVwmPxf7SwIJgJgWB4it1IClSQBxpQFQOECSQGhJBZRKvVbyJUCqVQ4NVUgtVYrShKlwMqBVsr4O8gEby0CSpX0ei1NqHVf7dVxgNPGQ1gZjRJmTVGs02CcHqCwdEQIlpMF1EYOGBVpRcGlAbA6JBjqnVkBdRO0hk5KFTo9XQ1M3pMA%2Bkrc%2Bl8mq8BakDEaUoXhgxeDwvhAihHABEWIiRiNkaE1Rp/A4Zgf7Yx6kw9hcRxqk1QCjQY5j%2BGBiMFwAqXAGo0FoHTdqEBGaPU5qzdmpAEnc15vzBwSThaMAIGLCWf1pay3lorOKKsfYbECvgbW1Q9Z/UNsgY2SSzZeUepba2rM7blKxkdZ2cU3Ye0wF7VWRhfagHoXwIOodw6R2jkkuO8irqKNkCnB6gU1EZz9jXKwlhc7RBboXYu6RFblwIJXA41ds51wbnEJum54BtxXh3PwXcGDuE8M0PQ/ciibwnqPdIu8R75AYAfIey955rx3m87IoLV4MG6PvAe3yKiL0hb3Pe0wvmHzPssVYp9v7oN0dfTgZjiC8P4YI4J1jQm2I0K/KRaMv5uL/qQABQDBigOaZg7Boj4FAjIUCIEBwEGSFWoEPR/1Wq2Foe4hh8AmHDRBj4rxxBOEbB4dDFgCh0RQnRFSukkw9p0pkYEOZCcFk3XkMolZOgQAVQ0Vor6%2BLfpUMBiw0G4M1VrQ1VqjEurOSTHsX4xxcRnEHEZWMzxgaiaKsjajfSyBEiJGIjqgqxE9UEDEiS1aNMomWgZkzFm3MkkpJ5nzAWmS/EixyeLSWFTMAyzlmIBWSTSnDM6aQSpOsamPTqQ0l2TSLZWxticDpDtulJL6SkAZ3thlhFGTjcZTBg5hwjlHRgsy5GmokIs26lq042vWcYC5NhWl7KCgctsnApwVyzrXCw9d9GN2Orcguc8YUuBebvT5swQWkABWPFFPzAXAtnu3EucLGgAehY88DwGt7glGJBtFsGsUKBPldHRTrmpEo9S8L12rfVbH9RAN%2Bh1nHfyxkyllwDKDn05SAMwoiDgHG8vlAI9UmNAjKpQrDEr2qdSZeAoEO1eXlEkAVHl0CuBAnQQcTD%2BjOAUfoefXa3H5MSulUsN2qRnCSCAA%3D)

## Links

- [source code](../../../../conceptrodon/omennivore/is_calmful.hpp)
- [unit test](../../../../tests/unit/metafunctions/omennivore/is_calmful.test.hpp)
