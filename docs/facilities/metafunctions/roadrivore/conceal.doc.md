<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Roadrivore::Conceal`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#roadrivore-conceal">To Index</a></p>

## Description

`Roadrivore::Conceal` accepts an operation and returns a function.
When invoked, the function instantiates the operation with the arguments and returns the result using alias member `type`.
Overall, `Conceal` turns an operation into its `Typical` counterpart.

<pre><code>   Oper
-> Args...
-> struct { using type=Oper&lt;Args...&gt;; }</code></pre>

## Type Signature

```Haskell
Conceal
 :: template<template<typename...> class...> class... 
 -> template<typename...> class...
 -> typename
```

## Structure

```C++
template<template<template<typename...> class...> class>
struct Conceal
{
    template<template<typename...> class...>
    alias Road
    {
        using type = RESULT;
    };
};
```

## Examples

We will conceal `Operation`.

```C++
/**** Dummy Arguments ****/
template<typename...>
struct Con_0;

template<typename...>
struct Con_1;

template<typename...>
struct Con_2;

template<typename...>
struct Con_3;

/**** Operation ****/
template<template<typename...> class...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<Con_2, Con_3, Con_0, Con_1>;

/**** Metafunction ****/
template<template<typename...> class...Args>
using Metafunction = Conceal<Operation>
::Road<Args...>;

/**** Result ****/
using Result = Metafunction<Con_2, Con_3, Con_0, Con_1>::type;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

Here's the entire implementation of `Roadrivore::Conceal`:

```C++
template<template<template<typename...> class...> class Operation>
struct Conceal
{
    template<template<typename...> class...Sequences>
    struct ProtoRoad
    { using type = Operation<Sequences...>; };

    template<template<typename...> class...Sequences>
    using Road = ProtoRoad<Sequences...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCAArADMpAAOqAqETgwe3r56KWmOAkEh4SxRMQm2mPYFDEIETMQEWT5%2BXJXVGXUNBEVhkdFxiQr1jc05bcPdvSVlgwCUtqhexMjsHAD0AFTbO7t7%2BzvrJhoAgls7ANQAkixJ9GyCTDUXu0en5wefB28nxycEmFuBgBJnibgBQKemFB4MBdyhMIIAE8koxWJgAHRY0HYC7IAwKBRYjE4vEEhQXADyqOITwyOL%2Bw2IXgcFw8DFWYj%2BJgA7FZThdBRcIfCQWCRcDoeKUWi2MTSfimITiUJMABHLyMVYKBkCoVMlkEC7KYioIgAJVQTHQfyFF15FguXjSRmFMvt8QAIlSaXSBDDVRqtZgidj4thQY7eZ7I9y9YKJQjxXDJYiZcw5WHcYrlVjA5qOSHdSc7c7gsALpbrR7vSazagqzawfng6GSeHY6do53fu8vp8fh9NhdsKpWHdMC9Dn8h/3p12u2Z4sF8V4sB63GhC0kCDqOwuzrsLp6fCwkRcTsRgD5GLup9sfomxeD0%2Bj5fuTgbWeyAPoaHt/E%2BUovqiGaYlmjIEMy34CD%2BXAAacQFpqBb4QacX5Gr%2BZgIf8KZJiBsrge2EboVBhpsrB8Q4UOPrRH6DD3psj54c%2BSHSihmbEWSSptsWGG0bSNTUUeQheEkeSYOg5ohl4tBGq8fxlq6oniakknSQoslGqC3rUnRQlglhpAUQwP6JCZf7Gb%2B8EdvE/K9oelwALKYPUVBeByzwKYhLHAWxBFge%2B2bksSl7AHuJEnEpFYuW5HkOBkNYmZytAwnpgn0h%2BIAgI2MJhbxtn2TOR4aVpjE/NFlYyXJSWxUw7meZlbhGRZ5m/hoVmwTZ2DZciqLCZcAAqIbyfOn71I4yA/jx0QEBAwzoNlCjotNe5uKVcnGSpElSdVBA4nMOEcAstCcLEvB%2BBwWikKgnBuNY1gXAoSwrJO5jxDwpAEJox0LAA1nEkgYhoAAcZhmAAnBDXCxKDINcDyPLSKdHCSLwLASBoHWXddt0cLwCggB131XcdpBwLAMCICASwEEkXgEOQlBoLcdDRKE6KcKoIMAGwALQ85IFzAMgyAXFIGJmLwkmECQeCLW0/CCCIYjsFIMiCIoKjqKTpC6G0ADutJJJwPAnWdF0/TdnCUgz9NGqgVAXNz/OC8Lovi0DZgXBAHis/QxD2kuXBzLwJNaAsEBICzSRs2QFAQDHccgMAUhmHwdAAsQhMQBEVsRMEDRIqbvAF8wxBIpSETaJgDgl6QLMPAQlIMLQxe61gEReMAbhiLQhPcLwWAsIYwDiB3eDELXjgAG4hlbmCqLXDNrJ9wQAij120HgES0hXHhYFbUF4Bjg%2BkHPxARGpnqAqP29GD9CxUAY4UAGp4JgBt6Zdn1K8IojiHVn/LWagrb630KPFAD1LD6B3oTSACxUA7gyAPPmC0dKmEsNYMwuML7EHlvPBB7Rp4ZBcAwdwngWj%2BHIdMfoMQ2h5HSAIMYrRkipCYQwWhpQBgTCqCQgQXRRiUPGMQhKAiRg9GCH0bh9DbASJYXoSYjQuGzBDosZYqwJDmw4OdUgONeB42drzAWQsRZiwlt7CAuBZaB3eiHMOj8FgIEwNaAYEB/ogEkPEDEEN4hIw0JIMwkgeZY1iDzCG%2BhOBo1IBjD6GIeZcB5iDCG8MeaxEkDDXxPM9FWzxgTImX1H7kyplHGmdsGZM0Tqgf27NOYcAaCwGePI%2BZMG4q6LgEMMRcGBtLfARB8EKw1v/VWEhpDAKUKA3Wuh05GyYCbQe2jdH6OthwW2dMGYXEdkY12QtFTtM6d0jQPs/axwDkHeIZhQ6FNJpHaO1TTnREqUnAOKADBGA6VwDqNA5LRBznnXWZci710BRXKuNc65n0breFubcrad27r3Wg/d67Dzvmsa6%2BAp4JTngPa6i9l4AnruvKoVtt67yLgfdFYd8Gn0%2BhfK%2BSgb4jyMPfUANy%2BAvwUO/T%2B3965/xVoAsZsgQE62utMiBD9MFWBgWS%2BB7ibrIIEKg9BXopXYNwdEAZhD5V2H4X4CArgFFtECFImYPC2H5AyEai1HCVHmt1WI2o8jhGsIdTUQRkjih0MUc67IrqJF2voQsZ6Gi1aLMtrrQxLsTFtIrB0rpwMfbWP6ec%2Bx1yI5OJcVgGI8qUbRNiZ0gJPJYgQ0RvEQJwSMk5MjZwfJxMikU2prTe2Tz7lxw5mwTgDS3YsAUDPMWM942SmGL0mx8s9D8oAWrIVmsJmip0CARIsz5lm0iToiNuMbblIdk7VQPa%2B0DqHVCYYxy21nPevEK54cyalOeY8hOd6Yj9vEj%2BQdEMfzDoID%2BPdYzM6/MoP866IL26fWA2C6e9coWCBhe3DFmAu49z7gPT6qKWVUtIJikhOKF5L2QCvIlggSW6zJXvJElKj40vrvS6%2Bt8WXliKc/Jgb8P5f1Any2QArp1DJFWAxdErjDQJsLK%2BAiDFUMAHusBaUCsGWBwQYvBBC5XBr4Y6shFC/XUPQIG3I7CajWsYTUbTvCOjiO6Nat1nQA2mu9RMX1VDbNTGszIrR6jXouZRks3JnBnb7v7RcN9GJP1Jr6SQVNV7HGkGca4nN2j80gEhhieI8RYiwwyVjJLPIknVs3fjWwBTr1zA8ZIWIPiEY8ixiDSQ0MuBgzMNklG8QN0GNrem36a6pbZea7lgrCwL5pGcJIIAA%3D)

## Links

- [Example](../../../code/facilities/metafunctions/roadrivore/conceal/implementation.hpp)
- [Source code](../../../../conceptrodon/roadrivore/conceal.hpp)
- [Unit test](../../../../tests/unit/metafunctions/roadrivore/conceal.test.hpp)
