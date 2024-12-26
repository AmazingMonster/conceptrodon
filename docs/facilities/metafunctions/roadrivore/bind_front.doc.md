<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Roadrivore::BindFront`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#roadrivore-bind-back">To Index</a></p>

## Description

`Roadrivore::BindFront` accepts an operation.
Its first layer accepts a list of containers and returns a function.
When invoked, the function adds the containers to the beginning of the argument list and instantiates the operation with the result.

<pre><code>   Oper
-> Cons...
-> Args...
-> Oper&lt;Cons..., Args...&gt;</code></pre>

## Type Signature

```Haskell
BindFront
 :: template<template<typename...> class...> class... 
 -> template<typename...> class...
 -> template<template<typename...> class...>
```

## Structure

```C++
template<template<template<typename...> class...> class>
struct BindFront
{
    template<template<typename...> class...>
    alias Road
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
};
```

## Examples

We will bind `Con_0, Con_1` to the front of `Operation`.

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
using SupposedResult = Operation<Con_0, Con_1, Con_2, Con_3>;

/**** Metafunction ****/
template<template<typename...> class...Args>
using Metafunction = BindFront<Operation>
::Road<Con_0, Con_1>
::Road<Args...>;

/**** Result ****/
using Result = Metafunction<Con_2, Con_3>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The key is to halt the invocation of `Operation` until the argument list is fully provided.

Here's the entire implementation:

```C++
template<template<template<typename...> class...> class Operation>
struct BindFront
{
    template<template<typename...> class...Beginnings>
    struct ProtoRoad
    {
        template<template<typename...> class...Containers>
        using Road = Operation<Beginnings..., Containers...>;
    };

    template<template<typename...> class...Beginnings>
    using Road = ProtoRoad<Beginnings...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCAArADspAAOqAqETgwe3r56KWmOAkEh4SxRMQm2mPYFDEIETMQEWT5%2BXJXVGXUNBEVhkdFxiQr1jc05bcPdvSVlgwCUtqhexMjsHAD0AFTbO7t7%2BzvrJhoAgls7ANQAkixJ9GyCTDUXu0en5wefB28nxycEmFuBgBJgAzG4AUCnpgwRDAXdobCCABPJKMViYAB02LB2AuyAMCgU2MxuPxhIUFwA8mjiE8Mri/sNiF4HBcLMF0AAxYiyP4meJWU4XEUXSEIkHg8XAmFS1HotgkskEphEkkWTDAYIMYLABSM4Wi5msggXZS8ogAJVQTHQf1FFwFQpODod0sRUvhMqR8uYipxoLxKrV2I8j2C0X1gftrpFXjSRgu1ttjtBABFqbT6QJYRqtQwdUZidjSBcw/UI8Ri6To6DnQ6BWmwc6YyL3ZK4VCOyi0X6sQGgxT1Zrtbqo9hWxd47qkzb0KmM%2BbUFa57mRwWx0ray34k26/z3l9Pj8PpsLthVKw7pgXoc/qej3fTvyzKDggSvFhU240AxVkkCHHA8zl2C40x8FhkQuE5iGAHxGEA29th%2BdtZQhX0MS3CdTmNNkwwAfQ0ZtgNQn1e0wgcmQIFk8IEfCuGI59TlIuVyP9GtsJOXDTQIsxGN%2BZivQ9dC2P7DiqJoni6NBfj71AmlomzBgkM2FChO7dS0J7BUxOVIdKJw6iTUzRSalkw9LiELwkjyTB0EtTAFC8WhTVeP5p0TKybNSOyHKclyFxMukzPBAiNFLAi2jLOizAi6TGX3JiQMuABZTB6ioLw/2eNzBK7LTNLInSsPJVVqxgvUDRODzgAuNKMqyhwMkCjkGG5XlBFhBTgoZaNThAEBkztUK6PC6KGHoqqBqG2EKurBKWws7Yk0c5zXKfaqE1qvy1sC%2BqmEy7LercXi4ommTt2A08LgAFUc9bkKo%2BlkHwsrogICBhnQAaFAxV6ozcHaXNLLzbPs1aXNxOZzJODgFloThYl4PwOC0UhUE4NxrGsC4FCWFYb3MUEeFIAhNDhhYAGs4kkTENAADjMMwAE5ma4WIGfprh4niaQEY4SReBYCQNHClG0YxjheAUEBwrJ1G4dIOBYBgRAQCWAgki8AhyEoNBbjoaJQgxThVHpgA2ABac3JAuYBkGQC4pExMxeDswgSDwb62n4QQRDEdgpBkQRFBUdQFdIXQ2gAdzpJJOB4eHEeR8n0c4Klta101UCoC4zatm27Ydp3abMC4IA8A36GIR1Xy4OZeHlrQFggJB9aSQ2yAoCB287kBgCkWKaBcyNKAiVOImCBpkQT3hJ%2BYYhkSpCJtEwBxZ9IfWHgIKkGFoGeI6wCIvGANwxFoGXuF4LAWEMYBxEPvBiDXxwADdHNTzBVDX7W1hJ4IAT8zRrQPAEQ6SLw8FgVO1E8DCyvqQd%2BxAIg%2BTTICO%2BICjDkwWFQAweoABqeBMDRwUijEmvthCiHEEHchoc1CpyjvoO%2BKBsaWH0KAmWkAFioAAhkS%2BlsvpgjTKYSw1gzAS0QcQL2H9OHtBfhkFwbUxitFIIECMMwBhtDyOkAQSjcipG0QwaY/QYgTCqHIgQXRRieBaHoOw5jagjB6Go4xtjHG6ImI4oxpQNELDxssVYEgk4cCRqQcWvBJZ5wttbW29tHbOzLhAXAHsa5E3ro3LBCwECYFtAMCAVMQCSFBJiZmoJeYaEkGYSQ5tRaxHNszfQnBBakGFsTTE5suDm3pszLm5tYiSHZiU82oTU6S2lrLUmWClaq1burTO2tdY91QFXI2JsOANBYK/eIlsmClUTFwZmmIuB0zdvgIgkjvbBwoQHCQ0gaFKDoRHXQsVY5MHjlfIJISwlpw4BnTW2sLg50iQXW2Ko9kHKORoculcO7V1rqCMwDcJkKxbm3JZMLogLN7tXFABgjD7K4OFYeAIqxjwnlPReG957T2Xqvde8Ct4IV3vvVOR8T5n1oBfDeN90FrDRvgZ%2BTV36XzRl/H%2BAIN4AKqKnEBYDp6QN5Y3SRcCSaIOQUoVBt8jAYNAMivguCFAEKISQje5D/ZUNubIWh4c0ZPMYZg4RVhWEyo4Xk9GPCBB8IEemB1ojxHRHOdI11dimrOAgK4dxKi2peNmJo/RNQI1aJqNGjRsiQ0OO6BG4NNRLFOOKC4jxGbrHjFsJ45x3iTG%2BPxgE%2BuDTgkpwjhE/O0Tdm1X2Ycum5cklnLhWkpFzdMnZKwDEV1/MmktIOeU%2BIsRmY81BBUqp/ThkNs4GMuWkzlZqw1lnTFaLO7GzYJwdZhcWAKFfo7V%2BbaZTDBOckr2ehTWUMDhakO9zrU6BAKCUgLy3mJ1rZ8kZ6c5nZ1zqoY9p7z2XuhMMKFu7YVE1BIipuisZlYoxd3VDMQz02Xwhe5m%2BEr0EHwqB25dBiUywgOPCOVKKXwOo0vFeL8N4MsEEyg%2BfLMDH1PufS%2BJNuVaoVaQflcihWf2/sgX%2BErBBSojjK8ByJ5XQKVRvVVKC0Fat1JMnBTB8GEOIb2E1sgzVPsuVa%2BhH67XGBYTYZ18AuHuoYJfdYX1mEiMsGI8JEipEut8WYtNCj3BFuUaovN5a9H5AyAmuNGRk0mNTdmtxgXbG%2Bfi1MMtMaS2FuyMoyYjQYuBMWP4wOHz60S04HnMDZ6Li4cxARztpySA9sQxk0gWScnDqCWOkALNMSglBLEDm/TRa9fiJ0pdpWpa2HGUhuY%2BTJCxGKdzeIot6aSDZlwRmZghn81BCV8JK6%2B0U1ra7Mbe2JvTYWIgtIzhJBAA%3D%3D%3D)$Done$

## Links

- [source code](../../../../conceptrodon/roadrivore/bind_front.hpp)
- [unit test](../../../../tests/unit/metafunctions/roadrivore/bind_front.test.hpp)
