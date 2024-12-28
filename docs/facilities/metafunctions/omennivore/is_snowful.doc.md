<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::IsSnowful`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-is-snowful">To Index</a></p>

## Description

`Omennivore::IsSnowful` accepts a type.
It returns true if the type is a packed `Snow` and returns false if otherwise.

<pre><code>   Type
-> Type == Snow&lt;Items...&gt; ? true : false</code></pre>

## Type Signature

```Haskell
IsSnowful
 :: typename...
 -> auto
```

## Structure

```C++
template<typename>
struct IsSnowful
{
    static constexpr bool value {RESULT};
}

template<typename>
constexpr bool IsSnowful_v {RESULT};
```

## Examples

```C++
/**** Vessel ****/
template<template<template<template<typename...> class...> class...> class...>
struct SnowLike;

/**** Items ****/
template<template<template<typename...> class...> class...>
struct FlowLike_0;

template<template<template<typename...> class...> class...>
struct FlowLike_1;

/**** Tests ****/
static_assert(IsSnowful<SnowLike<FlowLike_0, FlowLike_1>>::value);
static_assert(! IsSnowful<int>::value);
```

## Implementation

```C++
template<typename>
struct IsSnowful
{ static constexpr bool value {false}; };

template
<
    template<template<template<template<typename...> class...> class...> class...> class Silence,
    template<template<template<typename...> class...> class...> class...Sorrow
>
struct IsSnowful<Silence<Sorrow...>>
{ static constexpr bool value {true}; };
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISRqkrgAyeAyYAHI%2BAEaYxCAAzNIADqgKhE4MHt6%2B/oGp6Y4CoeFRLLHxSbaY9kUMQgRMxATZPn4B1bWZDU0EJZExcYnSCo3Nrbkdo739ZRXDAJS2qF7EyOwcAPQAVLt7%2BweHe5smGgCCO3sA1ACSLMn0bIJMdVf7J%2BeXR99HH2enZwImHuBiBJgSbgIAE9koxWJhwdgAaNiF4HLcFEIGKgAO5ULy0AEmADsFiu00cyCuaAYo0wqmSxCu0VQniuADcxF5MFcSRYqGIlCSACLgskisVE85AkEvBHncFuAFXFVXGUPOWK9WghEQ7WavXAjVgvUwuFsAB0VsR1IMCgUVotNuQdod1oS2FtTHtjudrquQjojHWpGVqv1JshRp1WujBshZuYlvdnpd3rdTo9Xp9KezGaEJGIuKJHuRBFR6JumOxeIJisD9AY63rhdxvtLpYVpPJjUp1IEdIZTJZbM53h5fPL3IlCXFxNFs6lFx%2B3z%2BX22V2wqlYDx57wB65XxyX66uADVMPaam9j9K45GI7qo7KH/en9DYUnMO3U66f3n/zTHNMyRc4UTRAgAxrUIAGtdSsBVPn2W4ZQUG9dj%2BR9Yxfd83y1RN4UAv9cyAjNETLCtIIAMVoXFYMwAB9DRJUQwE8MNHDsONd8COTECAJI4iQIoiCrhoui8DghiuBY/4kOuAAVS8CDQ/cwN7PBkAY9M4gICAqyxXF8UJCFDJxejFXE8zJMYwIxNo6ypJkjtsBAEAx25BZZIpTTtKvZoIDAMAMTM4zFTCAhETcjzMC82cOCWWhOAAVl4PwOC0UhUE4JVLGsckVjWCczASHhSAITQEqWGCQGSyQLQ0AAOMwzAATlarhkqaxquGJYlpCSjhJF4FgJA0QJ0sy7KOF4BQQECCqMoS0g4FgGBEBAFYCGSLwCHISg0HuINiAieFOFURqADYAFpLskK5gGQKkpAtMxeEwfAiGIPB0D0fhBBEMR2CkGRBEUFR1CW0hdC4UgcWIJhkk4HhEpStLKqyzgAHldp2yDUCoK4Lpuu6Hqeq4XrMK4IA8I76CZcxSoWXhFq0JYICQQ7kmO/aIC546QGAKQzD4OggWIOaIGiDHojCJooWR3hZeYYgoSx6JtEwBxFdIQ6ngILGGFoBWoawaIvGANwxFoObuF4LAWEMYBxFNvBiC1xx2UvDH6S13aNjKiKagx2g8GiBHVY8LAMfLPBRrt0gveIFklGFYEndDoxKqWKgDGABQzzwTAcSxz8df%2B4RRHEEGK/BtQMZh/QnZQaxrH0MO5sgJZUGSOpbeu0Z0HBYVTDyywzCmpPvqwTuICWOwPcyFwGHcTw2j0EIwgGcohlhgoMgECY/D3tID4YWZBniWGF4cboxhaNfcmvmpF4EHpmgvner9se%2Bj70aYP5bzmLveehV1gSFRhwVKpBJq8GmkTK6t17qPWevVKmEBcCEBILyEqXBmblWzksBAmAmBYHiHPUgNVJAJAtK1BI/UNCSDMJIS641kqXVavoTgw1SCjVKhaS6XBLqNVaj1S6dVOp0MujAjG01ZrzQIUtdm60OabVxrtXm/N6anTYJwJoLB2TEmukwL0RgKatQtFwBq71PokB%2Bn9WQgNq7SFrkoeuUNdAi3hojRWkDoGwMxhwHG21dpXAJggkm900xmK4BYqxGhqa025vTHBCQzD4NZstVRWi4iaNQHTIY0ShYdUCDQWg4tJbSyhsreWOsamq3VprbWCc9aMANkbE2mUzYWytrQG2OsHYZw2F0t2i8va20yr7ZA/sdZB0GplUO4d5ZR2GSzb68cypJxTpgNOjsjCZ1AEovgecC5FxLmXBOFcnHAxcbIOukNMqeKblnUeVhLDt2iLPbuvdMj90HsPV51gJ5wKnj9b2XdOivz8BAVwf9Yab1KJfPQ%2B86hwtICizIn95jPy6G/X%2Bj9j6QtvnimYQCkXX3xTkQlAC%2Bhkq/hA5YqxwF4K4VA9GUN4HEyQaY4A5jLENWppgr6qS8Es0IaQYhpChgUMGjwvhFjGHEmSq1PqSRmF3VhgEuRtgFGZOUfAVRW08Z5IKSdM6HB9GkxYAodkVJ2SxItDqUYNisHTwcQDKuNzQbyDcQ8nQiQ4YIyRnbPx7KprY3UfjQmqgrU2rtQ6p1kEab5OSXEVJCQMnZxWpzFNPMKB81zfTdyyBkjJAYva1qDFE0MRjS4sWcRKkyzlqrOpza1Yaw9jrVpghDbGwxt0y21tbZlUGfs1ZpB8Du1vuMn2qg/ZAlmYIYOUNFkRyhCsmO6ydZbLSDs9O%2BywiHLZscpg%2BdC7F1LowcujjPUSFuWDX1DcA0GBea3d5iyvlZR%2BQOTgmxB4tzHhYYFWVQUz3gPPF%2BxLoWwoJRvFeWLd7otPqi2DJ9CiYrpdioldR34Pypf/SDOH74Ie/jStFNKSMMoUGA4GoaZEcs4ETWNtqOQJrlKMQVtiGa4MzUoohJCyGUEgXKkAbULQJASMlLqkguDjQk8SYR9Hw0zR1QtcVVDkq0N6sScajVJAdS4M1Mw0jBoJDDXAzgYq%2BOsrekpizKm9VLCTukZwkggA%3D%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/omennivore/is_snowful/implementation.hpp)
- [Source code](../../../../conceptrodon/omennivore/is_snowful.hpp)
- [Unit test](../../../../tests/unit/metafunctions/omennivore/is_snowful.test.hpp)
