<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::IsFlowful`

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
template<template<template<typename...> class...> class...>
struct FlowLike;

template<template<typename...> class...>
struct RoadLike_0;

template<template<typename...> class...>
struct RoadLike_1;

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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISRqkrgAyeAyYAHI%2BAEaYxCBmAOykAA6oCoRODB7evv6BaRmOAqHhUSyx8Um2mPbFDEIETMQEOT5%2BATV1WY3NBKWRMXEJyQpNLW15nWN9A%2BWVIwCUtqhexMjsHASYLCkG2yYAzG4EAJ4pjKyYR9gmGgCCY8ReDgDUAJIKAGK0qADuVC8tDu9xMiQsrxmjmQrzQDDGmFUKWIr2iqE8rwAbmIvJhXmCLFQxEowQARI4QskUkEg7a7fbXB5HNwg15s150vZMA7HTkM5l87nXXnnS5sAB0kpusIMCgUkvF0uQsvlUsO2BlTDlryEJGI/1IrPZgp5Jx2XNNZwuzAlao1yq1qsV6s1coVAHVmpgEKslAoaeqQU8XgQPt9fgCgczdcR9X9mZ7iN7fZgnTd00zwZCmtDYQIEUiUWiMdjvHiCQRntdEuTDpSa9SmQ8APQAKnbHc7XebILbHdeABVUwQFK9Oz2W12p%2BOaQ8TcKzfShQLzfyRdargqlSqty6HW67UHKyHXj9/qEANbCqxN%2B7zldLy2im2YXf2neHh7Bt4AJVQTHQS9MAAfQ0RtQTnVdl15KCnw3W1nXfR03yPZ5f3/QC8CvYCuHAo9uTwZBgMdOICAgT4z0jYFjkooDmT/ACgNA0hXgYzDsNwwN1RAEBS1xRZwKhQjiLlUiIDAMAw0owFqLcMICBuHi%2BMwAS6w4ZZaE4ABWXg/A4LRSFQTgWUsaxIVWdZyzMQ4eFIAhNHU5YLxALSzHFRIzEkAAOLytI0ABOVyNAANi8w59E4SReBYCQNECPSDKMjheAUEBAns/T1NIOBYBgRAQFWAgUi8AhyEoNBdjoOIIiuThVC84KAFpgskV5gGQGEpHFMxeEwfAiGIPB0D0fhBBEMR2CkGRBEUFR1Ey0hdC4Ug/mIJgUk4HgNO03SHMMzgAHkSuK0NUCoV56qalq2o614urMV4IA8Sr6BRcwbMWXgMq0ZYICQCqUiqsgKAgAGgZAYApDMPg6G2YhUogaI9uiMJmlOTbeBR5hiFOA7om0TAHAx0gKrYQQDoYWh0YWrBoi8YA3DEWhUu4XgsBYQxgHEGm8CTBw8ExVM9sRQmSs2Wz5NqPbaDwaI1pxjwsD2ys8Bi1nSEF4g0SUUkdk5mWjAc5YqAMYAFAANTwTA/gO61idG4RRHEKaHdmtQ9qW/ROZQaxrH0WXUsgZZUBSeoWcasZ0COUlTFMywzESzXBqwQOIGWOxCfqFwGHcTx2j0EIwkGCphmWwpMgESY/DL9IK4YOYhniZaM/5gRegmPO8mb2pM56cZ%2BiL%2BZS9sfuq70GYWgbkum/TiyNgkbaOB00gEt4JKLoa5rWvazrJG6x7cEIEh8WsrhPrso3lgQTAAOGNPSGcyRDnFfzDkSAJJE84K4q04L/IijgUVSAxRsuKYKXBQr%2BS8hArSkguBaVfsFFee0kopTShfTKv08p/QKsdEqZVQaoBetVWqHBmgsExIkRqTBNRGDuv5cUXBxQGT6kfZOI1ZDjWdtIV2Sh3YLV0NDVa60MaL2XqvfaHAjpFRKq8M6rxyGUOobQ4A9DGHMMes9QGr0T6HDMOfb6WUcFg1egQkxwxFFUIdEYLg/kuCBBoLQOGCMkYLSxmjYm7icZ4wJkTdWpNGAEAplTPatN6aM1oMzYm7N9abAMvgPmjhBYsxYaoUW2xiaS00gtGWcs0aKziV9QaatbKa21pgXWHMjAG1AJgvgpsLZWxtnbdWDsuGTR4bIN280DKCK9obWOVhLD%2B2iKnYOocsjh0jtHQZ1gE5ryTkNIWQcui92cBAVwY9lqFzKI3PQ5d6hbNSLXeoU8Fjd26G3Uendq6rNbg0fuZzh4T1aDc8ejzB57LPisNY89vnZPESgzgCjiAUKoTQ6xqjbHqI0Affqx93pny%2BpfUg19b7xHvtkoBICGEaEkIkBBiREiHE/pIFqy0JGoNsOgwxWD4A4MKidMxRDtEkLYJwch10WAKExDCTE0KGRjF6vC9hy02lOw6dNeQfCek6BAOFYRG1WZiN2gtJK0iTpyPOpy1q3LeVYgFUKMYmiWVA10YcAxRtsr/VNaYkG5j4i8pSCkYC/L/LAUFQQYioKWowycXEFxyNUY408cG3G%2BNM7EwCeTSm1N4mYDpgzJmLNbIxOqYU0gCTe7JOFmk5AYtMmCCljk2W8tTgFOVsU4mZT0gVL1tUsItSfr1KYGbS21tbaMHtpwiVEhOkzRlR7eV/TjC%2B2GbksZhkJn5k4M2SOPs44WHmYZRZKd4Dpx7vc7Oudci3J2cXc5xyihZCOQcrITym53PqO3V5u7x6buvR83Z093l9COS8i9C8fmWS/QC1ViVgU6teHqvlhrtjGogIfAauikUYJ%2BlfG%2BWAMWL2xQkBhhxDhaT8nAuKGHEihWQWqzgaD0oosfokbqBKuBSH8nixIr8uDJGyYcf9a9iNwccgAnqhGAPJQ44sZYmsMjOEkEAA)

## Links

- [source code](../../../../conceptrodon/omennivore/is_flowful.hpp)
- [unit test](../../../../tests/unit/metafunctions/omennivore/is_flowful.test.hpp)
