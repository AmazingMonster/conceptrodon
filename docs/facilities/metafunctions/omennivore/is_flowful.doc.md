<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::IsFlowful`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-is-flowful">To Index</a></p>

## Description

`Omennivore::IsFlowful` accepts a type.
It returns true if the type is a packed `Flow` and returns false if otherwise.

<pre><code>   Type
-> Type == Flow&lt;Items...&gt; ? true : false</code></pre>

## Type Signature

```Haskell
IsFlowful
 :: typename...
 -> auto
```

## Structure

```C++
template<typename>
struct IsFlowful
{
    static constexpr bool value {RESULT};
}

template<typename>
constexpr bool IsFlowful_v {RESULT};
```

## Examples

```C++
/**** Vessel ****/
template<template<template<typename...> class...> class...>
struct FlowLike;

/**** Items ****/
template<template<typename...> class...>
struct RoadLike_0;

template<template<typename...> class...>
struct RoadLike_1;

/**** Tests ****/
static_assert(IsFlowful<FlowLike<RoadLike_0, RoadLike_1>>::value);
static_assert(! IsFlowful<int>::value);
```

## Implementation

```C++
template<typename>
struct IsFlowful
{ static constexpr bool value {false}; };

template
<
    template<template<template<typename...> class...> class...> class Sorrow,
    template<template<typename...> class...> class...Warehouses
>
struct IsFlowful<Sorrow<Warehouses...>>
{ static constexpr bool value {true}; };
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCAAzACspAAOqAqETgwe3r56KWmOAkEh4SxRMQm2mPYFDEIETMQEWT5%2BXJXVGXUNBEVhkdFxiQr1jc05bcPdvSVlgwCUtqhexMjsHAD0AFTbO7t7%2BzvrJhoAgls7ANQAkixJ9GyCTDUXu0en5wefB28nxycEmFuBgBJlibgIAE8koxWJhQdg/sNiF4HNcFAAxWioADuVC8tD%2BJgA7BYLpNHMgLmgGMNMKoksQLhFUJ4LgA3MReTAXYkWKhiJTEgAioNJwtFhNOAKBTzhp1Bbj%2BF2VF2ld1lCrVwLhYK1Gt1UJhbAAdKb4VSDAoFKbjebkJbrWbYtgLUwrRchCRiDjSEqVXqQbrAerA%2BDDcwTU6Xfa3Y7bc7XVabQB1BqYBBLJQKQnOxEEZGoq4YrG4/EKz3Eb3YhWp4jpzOYOPw5vyklk%2BoUqkCWn0xnM1kc7zc3n5rni2JiokiieSs5fT4/D6bC7YVSsO7c15/Jfzw6zpcXABqjbsLz3UuD2s1l/14Jvoch0IjmBtdodr4TMaTUbzBYIF0xHEggAax1Kx5XeXZrmlBQz22H4Ax1O8ZQfcNYQ/aN3x/U4kRRf8ACVUCYdAQMwAB9DQJQg/57yQxDNTQyN40w2MMN/PCLkI4jSLIrgqN%2BSDLgAFUbAhYK3HCOzwZAyNjaICAgItANLAkwWU0iFS4ki8FAijSE4ojtN0vjc2dEAQEHLk5n48lpNkq15IgMAwDRZS8VUtxggIeFzMszBrJnU4OAWWhOHiXg/A4LRSFQThFUsawySWFZhzMWIeFIAhNGChZgJAeJJGNDQAA4zDMABOcquHiEriq4IkiWkUKOEkXgWAkDQNFISLotijheAUEAuqyqLgtIOBYBgRAQCWAgki8AhyEoNBbjoaJQlhThVGKgA2ABaHbJAuYBkEpKRjTMXhMHwIhiDwdA9H4QQRDEdgpBkQRFBUdRRtIXQ2mxYgmCSTgeBCsKIuymLOAAeQW%2Bb/1QKgLm2/bDuO06LnOswLggDxVvoRlzHSuZeBGrQFggJAVqSNayAoCAabpkBgCkMw%2BDoAFiEGiAIihiJggaCFQd4AXmGICEYYibRMAcEXSBWh4CBhhhaGF36sAiLxgDcMRaEG7heCwFhDGAcQNbwOsHDwNlGyhulZYWtYMq8qoodoPAIiBiWPCwKH8zwdrDdIW3iGZJQhUBU2PaMbKFioAxgAUQ88EwbEYafeWnuEURxHe7OvrUKH/v0U2UGsax9E9wbIAWVAkhqA29uGdBQSFUwEssMxetDu6sBriAFjsWWahcBh3E8Fp/HH6Z%2BhiNo8nSAQxlaZJUiXhhZ9KAYJiqEfOhGJpJ/Gdp94ELpGi32YJkPle9EmS/gj6bf56H5LVgkcGOHC7qob6lHdoHSOidM6hUcYQFwIQEgPI0pcFJplOOCwECYGIgMQepA8qSFiMacqsRGoaEkGYSQO1OrxB2uVfQnBWqkHaulY0O0uA7WKuVOqO0CrVVwTtX%2Bv0%2BoDSGgg0alMppUxmvDBaS1GaoAJutTaHAGgsDZESPaTBXRGCxuVY0XAipXRuiQe6j1ZAvTztIAuSgi6/V0OzQGwMRZfx/j1XgfU4ZzQWhcJGAC0ZHRjGorgGitEaFxvjWmhMYGxDMPA8mY0RFM0JhImJAxvGsyql1GgtAuY8z5r9MWQt5bZIllLGWctg6K0YMrVW6toqa21rrWg%2Bt5bG2jmsSplt962wNtFB2yAnby1ds1aKHsvZC19k0smd0g4ZVDuHTAkcTZGBjqAQRfBE7J1TunTOwds5GLeiY2QhcfrRUsaXWOHcrCWCrhEAedcG4ZCbi3NuJzrDd0cb3e6dta6n2ts4CArg75tECE/GYO8175AyL84FG8r5AuHp82ot9j6r2hTUC%2BPQAVz3vnC7ICLD6QtfosZYH84GUO/pDHhnAPFANUcAdRmiiq40gbdUJcCyaINIMg1BMR0HNWobQjRBCiTxHKg1WIhDiGSDaA46G/VbD8MiUI%2BAIjZoIziVI4JMi2CcHkejFgCg2SUjZL4402phg6KgX3Axz1c7bI%2BvIMx%2BydBxFINYkGhs7Ekt6rDMRiNkaqC1TqvVBqjX/jxiqumoTYgRLjuNamIbYkM3iTEXVSQkhkX1eVMigayI%2BpMZzaIGT%2BaCwlrkgtktpYj3liUwQKs1ZQyqTrPWBsMoNLmSM0g%2BAraODafbVQjsAQ9MEG7X6AzvYQmGf7MZ8tJmpGmVHOZwQFkUyWUwJOKc04Z0YFnQxlqJA7M%2Bra4uDqDDHIrmcgZlyYrXO7JwdYLdy6dwsE8mKLz%2B7wCHnvGFY8J6YuntpYoaKF7rxqGCxeNQcX3zfUijFU9d4dHPti1FL90XdDBQ/FFv6EOEoUO/N6rruHuo4CjX1ur2QBtlMMOluiiawIjYIpBKCsAcq/tykAFVjSxASDVMVnU2NEiYbhxxnA%2BHDRZZg%2BIOD6pEk6sVSQVUuClTMFw5qsQ3X8albKr%2Bl0%2BOSuZTRkOuaMggEkEAA%3D)$Done$

## Links

- [source code](../../../../conceptrodon/omennivore/is_flowful.hpp)
- [unit test](../../../../tests/unit/metafunctions/omennivore/is_flowful.test.hpp)
