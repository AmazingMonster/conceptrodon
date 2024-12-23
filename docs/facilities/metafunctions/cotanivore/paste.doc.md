<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Cotanivore::Paste`

<p style='text-align: right'><a href="../../../facilities/metafunctions.md#cotanivore-paste">To Index</a></p>

## Description

`Cotanivore::Paste` accepts a list of packed containers.
It concatenates them together and uses the first container to hold the result.

<pre><code>   Con<sub><i>0</i></sub>&lt;Es<sub><i>0</i></sub>...&gt;, Con<sub><i>1</i></sub>&lt;Es<sub><i>1</i></sub>...&gt;, ..., Con<sub><i>n</i></sub>&lt;Es<sub><i>n</i></sub>...&gt;
-> Con<sub><i>0</i></sub>&lt;Es<sub><i>0</i></sub>..., Es<sub><i>1</i></sub>..., ..., Es<sub><i>n</i></sub>...></code></pre>

## Type Signature

```Haskell
Paste
 :: template<typename...>
```

## Structure

```C++
template<typename...>
using Paste = RESULT;
```

## Examples

Here, we paste `std::tuple<int>`,  `std::tuple<float, float*>` and `std::tuple<double>` together:

```C++
/**** Container ****/
template<typename...>
struct Container {};

/**** SupposedResult ****/
using SupposedResult = Container<int, float, float*, double>;

/**** Result ****/
using Result = Paste
<
    Container<>,
    std::tuple<int>, 
    std::tuple<float, float*>,
    std::tuple<double>
>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Cotanivore::Paste` is implemented as a shortcut to the member `type` of [`Cotanivore::TypicalPaste`](./typical_paste.doc.md).

```C++
template<typename...Args>
using Paste = TypicalPaste<Args...>::type;
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIABs/qQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCcmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimGmujMh4mAq3R%2BdXN6f/xx%2BlwulwImBYaQMYJMgTcBAAns9mGwAHRomHYEETYheBy3AAqiLwoloyiYE0wtxMAHYrNT7jCrFcQTsdrcLOTKW5OSAQSCwRCoZgYXDEYxWJSycgANaYdyyJgRBIYrEEHF4wlpYliMkUkVS2XywSKyLEFXM2kg27W25eLJGW4I55UwL3W4GuUeY1Ks2BJnA%2BmMvm/NkAJUwyA2WQAblyecHQeDIUxoczYVabQLk9DYU7xaj0YFsLdkAYFJ8vS0fZdSBnrVmhSK88jMGiURiS2WKwqfTY646xS229h6GxBJcFKQqVcbQOkRLh6PGAQLJP%2B82F2iAPIEBAJBR8ouq9UEAlEkm6nNuSsmhLA2Ej8HLidtjFTm%2B9kWPscrhSvotTjue7EH%2BhaYha/qznaETAHOlIwm6mraqS5Kppcs4iv2s4fqa95uN%2Bz6gSiU4EYIq7/tgtYzrONpAfur7UdaGIgCAeZBhaDJ%2BgmfwArxBxAjxtwAJKCk%2BxqNF8hwCXxMlnAmDYpsKuaDpuKKXMQwAHkeVzQQ6l7wa6Z5aheqFKW46maRRLFsVxzK/LJ3wskctzYKorCQpSjn2Q5/EJuYgQRKWXhYC6cJeB55rAt5By3DhCSSb5VwKVeG4Fu22kTmquKnnFxBUpaga2VF1zOUI4XFHK4YKF4tCnl5ly6bBZVpBV6BVTVp4IbFPamiKEQEFOVC0KgKaDcNKZ7FO6DrLE9AqkVTl3O1tUJXJOn2rBy2dYZ%2BmHm4/a5ZhAH9hM6DWeFc2wv1b7TuhNqnedEWwkNI0DbcL0TW%2BJ0EGdrEXWZ01eLNSngfemILdFewEh8dVSaqKbEgA%2BuSShtBAD0gAoErI1pbhbVOzWtVtGLLIyHCrLQnD%2BLwfgcFopCoJw%2B2WNYtwKOsmzwWYgQ8KQBCaOTqzSgEkgohokhcNSgQaP4GhmEkSRmAAHEr%2BicJIvAsBIGgaKQtP04zHC8AoIC6/zdPk6QcCwDAiAgOsBBpF4A0UBAaAQnQCRRBKnCqErSQALRJJItzAMgyC3FIKJmLwcqECQeBnVwMiCCIYjsFIKfyEoagC6QujJwA7sQTBpJwPAU1TNN54bW7O07p6oFQtx%2B4Hweh%2BHkei2YtwQB4Hv0Hl/lcMsvDm1oqwQEg7taoP5CUDPnuJMAUhmHwdBgiBlCxHnsQRK08Ll7we/MMQ8JbrE2gRubvPuz%2BW4MLQh8W6QWCxF4wDcrQtAm9wvBYCwQwwBxAv3wMQa%2BeBYy/3ppgVQEZnbbF5v1eoedaB4FiCXM%2BHgsB5zVHgLWf9SCxmILETImBHiAKMGgowAtVhDSYJpAAau8QuW4kRHyzmncQmd%2BCCEUCodQL8C76CASgaw1h9DoJNpAVYqA0iNF/gHU6CFTAs0sGYA2xDiCJw%2BPAVYdgIHOAgK4aYfhk5hCVIsUYydijZAEKYvQtjGgLBGIkZOBiHB9EmO0TwnQ9AeMaP0NoLiqjWNsN4hx7jvEhKWCPNYGwtgSErhwamesa6cBbv7IOIcw4Ryjj3CAuB45D25iPMetDVh7iYFgRIEAhYgEkIEFEABOQI1JJDizMJIJIOt/BJGaWrDgGtSBax5iiJIXAkhK2aUrSZ/gJb%2BFaUkNJL9DbG1NnzWhVtbZT3tvXZ2883aoAHl7H2HBWgsGjNSAOTBOxAMjs0lEXAxax3wEQbRSdOEkgztIXh2cBF510GvYupcj7JNSfrXgtd9mN2bq3bJdyHRcEec8jQvd%2B6z3iv5Mwo9NkW0ntPY5mKyCu0XoPFABgjDIq4LrGgtV9zb13vvM%2BHCT4HwvlfBwHC77Lgfk/POb8P5fx/hwgBQCQH0zARAqBedYHwLBBw5BlMX5oIwQfbB2x6Z4IIbzYhpClAUPFTBLZ9CmEsLYYwDhfyuE/Kzvw3OQiQBr0pcYcRlhJGxGkXUhm8iciKOUa6VRVh1GaISB83RMieiGL8MYhg8p8hmJCHGmJYSnE5EiekTIdiGAprcVGzxAggk%2BITf4%2Bo0ai25v8RE3xBQonzEsa4pJ8TOZNuVRC9JHBMltxDqWe5yKnli17kU95VJSm4vHoLUgVSamUGScM0ZjzxbUkWdSKWkgunB2TpChmnB1lmy2dbO2DsG6HLJactgnALntxYAoaMEdoz9qFBMV5xTE56Gtd8iQvzZD2sEfTXQwQQVlz/uC6uqzOB10ds7W4TcW7Xtvfex9ikJjoqJUvUdgRAjjoPYSk5JKF5ofJXelqiMH3NMRk%2BggiNVDB3XvSreEAd4vzZSywhLHz6X2vty4599H7P0lZgd%2Bn8xAisIWKqhmr/54HAZ4mVL85WRgVYQpVqD0GYPhBq3B2idW8D1WQw1VDjX4r4AYM1mBWHsMIR%2B9OX67U5z/ToEAwQXViLUTYVVXrZG%2BoEL/HYD0g3WA0VCrROjPP5saC4ONGaLEVEbTYrNjQM1prKA20JeaAleIGBmjLhbompdieErLNbE1zGCfl6x%2BiOaJLiW2sDBsMk0ZDjeu9twyMoko0Ot5JAMNlLxRPSpmBqmjG9cq%2BdTrHmYf8LLCWOtMPUimSs%2BrRtbAbIncsepkh/AtP8EreWzTJDNKlm0rgznOCBDq1C3dfXJ3Kpjoty7y21urGIVkZwkggA%3D%3D)

## Links

- [source code](../../../../conceptrodon/cotanivore/paste.hpp)
- [unit test](../../../../tests/unit/metafunctions/cotanivore/paste.test.hpp)
