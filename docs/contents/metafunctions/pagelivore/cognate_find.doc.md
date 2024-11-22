<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::CognateFind`

## Description

`Pagelivore::CognateFind` accepts a list of predicates and returns a function.
When invoked, the function returns the index of the first argument that satisfies all predicates, or `-1` if it cannot find the argument.

<pre><code>   Predicates...
-> Arguments...
-> Found ?
   index : -1</code></pre>

## Type Signature

```Haskell
CognateFind ::   template<auto...> class...
              -> auto...
              -> auto
```

## Structure

```C++
template<template<auto...> class...>
struct CognateFind
{
    template<auto...>
    alias Page
    {
        static constexpr std::make_signed_t<size_t> value
        {RESULT};
    };

    template<auto...>
    static constexpr std::make_signed_t<size_t> Page_v
    {RESULT};
};
```

## Examples

We will find the indices of `2` in list `0, 1, 2, 3` and `0, 1, 3`.

```C++
template<auto I>
struct IsTwo
: public std::bool_constant<I == 2> {};

template<auto...Args>
using Metafunction = CognateFind<IsTwo>
::Page<Args...>;

static_assert(Metafunction<0, 1, 2, 3>::value == 2);
static_assert(Metafunction<0, 1, 3>::value == -1);
```

## Implementation

`Pagelivore::CognateFind` is implemented based on `Varybivore::Find`. It changes the invocation order of the latter.

```C++
template<template<auto...> class...Predicates>
struct CognateFind
{
    template<auto...Variables>
    using Page = Find<Variables...>
    ::template ProtoRail<Predicates...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxCAAHADspAAOqAqETgwe3r4BaRlZAqHhUSyx8cm2mPaOAkIETMQEuT5%2BgXaYDtmNzQSlkTFxiSkKTS1t%2BZ0TA2FDFSPJAJS2qF7EyOwc5v5hyN5YANQm/m4EAJ6pmAD6BMRMhAqn2CYaAIK7%2B4eYJ2fI43QWCoLzenw%2BAHoAFQwqFHABqzQu0TwADcSOwQAAxMLoI6wqEQ6Gwo59Fr42EQsEETAsVIGGmnNxMLxEAB0HNBH3GxC8DiOOIY6DBJiSVg%2BR0lRxpdIZmCZMvpTEZZxZ7M5/mwRwOTAUCg5bOUxEw%2BFENOemrBUqOPL5BCORtQRAASo9aFapaKLDamo5kNqBONMKpUsQjmrUEdUWIvL8vQBaLiigAip29KbTIolUsVcoVtKVKuZrNQBpe2oMeoN72AxtpjAIFte2clXkyRiOrrof2TDuITtQXfdZxrdbYgn1Gte/nFnySqZnWfeueV8tVJYFeGI4y571t/MFwrOOO3BF3Xo9kpXReva%2BL6rZ5Z1VY5RpNeDNmCbl59vP5jpdN0fy9T0W2tH1lQ/AMGCDEMwwjKMYzjMDrQvFDwMlEwAFYrCw5MIGWI543LQEQBAFgmAAa1uTJgHCdA7iZTIAC9bjPS10IwtD3gw3ipTwKhoNg0MjigMszAANnMCS31NVcLTcE8d01Mjo28TBlmWH8%2BNQsUjmNAgNgYI4NDTE55yXHTeNqJRtKs8zvQMoyiKTGdzNTTjwJTAi7MwizFzAjMAvBHicwLPMzlvJkIzLTUK11Sc2VHTB6wnXdrTbMJgE7N0ez7AchyZZLUsbWLp1nIKKo%2BKL1yITdT1IcMNyEboBHQRqYo5AB5AgEDib9uXuO1NyFJklIIRqWrQIVGp6vrtzKkUxR/GrznC1dopLMr4pfQ1jTk810qlfd7QAwcgMCvTMM88ZIP9abhPgjc1NjE5PO4%2ByThw7D8MI4i4tI8iqJovA6JNRizhYtijqsj7Pv4wSHppODfJ0sTOUk6TZI/eSxq3ZTsFUpDNNRviQKc4hjNMtyMw%2BUnrNoJQjgEoTkdDemMPRx9Mck7HPwUqa2peIn1JJzyyb0injNc9MLLp8WGaZlmkeDdmFc5jmdMPJk5v6xb1Z0sjb3ywC6CZPn5P10L4fAkXXrAMBTl7RNNetLSDd09MPd4qWjjME5LBGo83F1hap1d3ijfWmkTfOs2zgt80rZtjC7bXL3rfh2mQpTo4bPlb2/MczBDMplyzOzz7vPdzPdIXWc68zeXM9W1bOsfOLn0S4rx0bGGjkyjshzys7CpHWsUt7xLQWCyqwWJGEESRFF0WNMjDwpGEiQJI5sCFTfCSXBe4Q8OjVw3glt5JMl7Uv6lo7vNutqnHbEsTr9dxOo5T%2BYGltbp5aYEn4PkRMQPATBoj0AGpnQe2VlBMGAHGfwvZtZnFAeAyBX5k5SijrKVcscx5uHftPS0s9/KzmPt/VAZ8/64gPlfRee88R32bsfAk7Ct7zx3gAFS/I2ehXCOFCMPs3L4DADheGOEyaaWxUh9w4iFYBkYACSn8hr8mUQobhAB3VAYIQBHFSF4SBUFAbRFQJ4G4SNDDsTcMonsTs/blgvOQpcSjqzEGANA2BRwACyJcmBUC8OI%2BoxlHE/3PriJkmidF6IUWReBiCiqeJIeVJct0/Q3ASnEAgEB/FNCCSE7ITINCNS4I1MwjV/DCxAC9JBC5exmC0sFDJH4sl6hyXkgJhSegCBKWUqpNS6kOOQS5Zps4OCrFoJwLCvA/AcC0KQVAnA3DWGsDadYmw4xmH8DwUgBBNCTNWJREAWFJBsg0JILgSR/AaCwhoSSEkzAJASPoTgkheAsAkBoUp8zFnLI4LwBQIBSkHIWZM0gcBYAwEQCAdYBAjETQoBANAdI6BxAiKwbYqgEgSXjBJSQRxgDIH9FINkZheDviIGA9Aeh%2BCCBEGIdgUgZCCEUCodQ4LSC6HKdoh4qROA8CmTMuZhylmcC6qyRFRxUCCRxXiglRKSVHDJf7CAHg0X0DDLsLgyxeBgq0KsCASBUWpHRWQZFprzUgGAFISpNBaA0m3JQaIYqUTMGIBcQVvB3VIi6tEbQ3QwV7NRb3LqDBaBeq5VgaIXhgDMloIzb1pAsAUSMOIaNW4g1oi/GK4M3RWTbD2WEGk0yuW0DwNEB4nqPBYDFfcPAXzuC8FRHEcxShky0kMMACtRhDmrCoAYLx8I8CYG0V1a48y9n0uEKIcQLKZ3srUGKnl%2Bhu0oDWZYfQlbgWQFWKgOR2RgUcHjICJ2phLDWDMP81txAaW5r3TUOo2QXBCimH4cpIR5jlEqHodImRQnvr/UUUJgwf0jHKV0XpDAb5Acg7UbNDRZhgeGPESDsw4O2GQ9%2B1DEhVgKE2VsPDbyOCzNIH83gAKjjyvxYS4lpLzlqtwIQEgAddl6v2f21YfUmBYHiARUgJzJD%2BDZAATn8EkSQlyzCSAkj8rCElRMkY%2BaQL5uy2QSS4BJBIomEhabOVwLC4mJLkbFQCoFILOPgqNTC41cKpWsnIJQK1WrMVsE4M0FgqIkjxiYPFDsXBRNsi4Bcyl%2BBqV4FpeUmdjL53SEXUoZdXLdCVL5UwAVzbhWkdFVygFkqEWshlYJTz3nfP%2BeyoF4LFzRIarNVqtjTT9X9shSa1Amq4hOZRW1urIwSs%2BZ1EYQLXBSkOqdcCiArquW%2Bs9cm6bFx/WBocMm0NDZw2RrFTGuNCak3NpTV29N2xFn4GND0Vtx7Fn5uQIW5NJbahiorVWpEtbDv6rAU2vZt722YE7WmntWVmuDoQQoEdY6J2MGTTFudzL4uyCXZyxZKW119ovVYLdD3d0CYPaE49p6CBHmTCjq9N64j3ox/hhD0HX3uE8O0PQX6yi4fKf%2B4oOQaf5CZyB7IKHFhoafYhmDGG2cfr59Bm%2B3Pf3of6Jh26LRxcQfw4R5lWWyMUfFRwcMxAvM%2Bb8wNirQWQsaFEsx6lbHdVNes9xzAvGRgCbLSptTQXLlJCM0kG5kgZMEvKar8zthLMGohVC2F8LEWdZcxirFHnNeKpYAoVE/pUSVblOMMLLGaV0tkLF6HrL5CJfhzoAoaWMtCpIyrszEqHP2llRrlg0fY/x8T/Je06ruvmrY/4Dj/ujWtfaxa5zLetW1OQKkVINwE%2BiZuEnggWSo/xboGNl1bqwhIlm0vz1C2g3Lba2GiNUajuYFjfGsQO29mpu7Rmo7WbTu5q5Zd67u3btlsWQ96tFxnv1re8mz7GRvv7b%2B326zfAQ6wOo646k6EOGeUOEgMObKueK6BQBgyOm6Ng6O8A%2B6h6gYnAEIpEhOlg16lGt6pOqBIuoSVOmG9OCwEuhQAG2QmGzOoGOGPOegUGoSsGQuTBFOLB2GDOjBkukwbBvBcw3BEuCuGwRGuqJeOW/ynA1eteceUYDe5oTexurGOqHeXGpAPGfGlAWW9uIAZgQW/g/gWE9yVyPyhhSQ2mpmuWnAFmoK6hQmWEYmWECQkkomkgomNyEmXAgQZa/gkhlGNhVmhqWWFKVhUhgKQRRypAt6mQzgkgQAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/pagelivore/cognate_find.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/cognate_find.test.hpp)
