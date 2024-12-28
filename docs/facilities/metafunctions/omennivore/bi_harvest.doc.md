<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::BiHarvest`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-bi-harvest">To Index</a></p>

## Description

`Omennivore::BiHarvest` accepts a list of elements.

Suppose every element has an alias member `type` and a static constexpr data member `value`. In that case, it returns two functions.

- When invoked by a container, the function collects the type results from the elements and instantiates the container with the collection.

<pre><code>   Es...
-> Oper
-> Oper&lt;Es::type...&gt;</code></pre>

- When invoked by a sequence, the function collects the value results from the elements and instantiates the sequence with the collection.

<pre><code>   Es...
-> Oper
-> Oper&lt;Es::value...&gt;</code></pre>

## Type Signature

```Haskell
-- Collect `type`
BiHarvest
 :: typename...
 -> template<template<typename...> class...>

BiHarvest
-- Collect `value`
 :: typename...
 -> template<template<auto...> class...>
```

## Structure

```C++
template<typename...>
struct BiHarvest
{
    template<template<typename...> class>
    alias Road = RESULT;

    template<template<auto...> class>
    alias Rail = RESULT;
};
```

## Example

- We will collect the type results from `Crop<0>, Crop<1>` to instantiate `Oper_0`.

```C++
/**** Crop ****/
template<int I>
struct Crop
{
    using type = std::integral_constant<int, I>;
    static constexpr int value {I};
};

/**** Operation ****/
template<typename...>
struct Oper_0;

/**** Metafunction ****/
template<template<typename...> class...Args>
using Metafunction_0 = BiHarvest
<
    Crop<0>,
    Crop<1>
>
::Road<Args...>;

/**** SupposedResult ****/
using SupposedResult_0 = Oper_0
<
    std::integral_constant<int, 0>,
    std::integral_constant<int, 1>
>;

/**** Result ****/
using Result_0 = Metafunction_0<Oper_0>;

/**** Test ****/
static_assert(std::same_as<Result_0, SupposedResult_0>);
```

- We will collect the value results from `Crop<0>, Crop<1>` to instantiate `Oper_1`.

```C++
/**** Operation ****/
template<auto...>
struct Oper_1;

/**** Metafunction ****/
template<template<auto...> class...Args>
using Metafunction_1 = BiHarvest
<
    Crop<0>,
    Crop<1>
>
::Rail<Args...>;

/**** SupposedResult ****/
using SupposedResult_1 = Oper_1<0, 1>;

/**** Result ****/
using Result_1 = Metafunction_1<Oper_1>;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult_1>);
```

- Note that the `crops` are not required to have both member `type` and `value`. In the following example, we will collect the type results from `std::type_identity<int>, std::type_identity<int*>` to instantiate `Operation_2`

```C++
/**** Operation ****/
template<typename...>
struct Oper_2;

/**** Metafunction ****/
template<template<typename...> class...Args>
using Metafunction_2 = BiHarvest
<
    std::type_identity<int>,
    std::type_identity<int*>
>
::Road<Args...>;

/**** SupposedResult ****/
using SupposedResult_2 = Oper_2<int, int*>;

/**** Result ****/
using Result_2 = Metafunction_2<Oper_2>;

/**** Test ****/
static_assert(std::same_as<Result_2, SupposedResult_2>);
```

## Implementation

```C++
template<typename...Crops>
struct BiHarvest
{
    template<template<typename...> class Operation>
    struct Detail
    {
        using type = Operation<typename Crops::type...>; 
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;

    
    template<template<auto...> class Operation>
    struct Hidden
    {
        using type = Operation<Crops::value...>; 
    };

    template<template<auto...> class...Agreements>
    using Rail = Hidden<Agreements...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxBJcAJykAA6oCoRODB7evnrJqY4CQSHhLFExXPG2mPb5DEIETMQEmT5%2BXJXV6XUNBIVhkdGxCQr1jc3ZbcPdvcWlgwCUtqhexMjsHAD0AFTbO7t7%2BzvrJhoAgls7ANQAkiyJ9GyCTDUXu0en5wefB28nxycEmFuBgBJgAzG4CABPRKMViYAB0iLcxFQiQUYOwf2GxC8DguFjwAAkGgA3TDDP4mADsVlOF3pFwBQKemDBEMBdxZbKhMOYbER8IxF2QBgUCguAHkYcQnukMX8GRdsbiCBcACKYep0BUM6m0k6KxVeVJGRnQzAXMFqyXS2UCbnmvkW5GohQgEA8hGI%2BWgiyWum6qlqsH6nX0pmckHgiPA1nRx1wgVCkVMMUCk7AYiYQGMAjo0GYgP043BYAXABKqCY6EtoOtGq1tDZGazOcECiTBfdnpDlKL/oNDJjXOjHNjbKYXiInewwtF4ql0TtDHl/eVeMJeHQWBX/b1YcNJdNntr1sXMpqbJdaPdJLEXi9goLIYHiupwd9fcH4bHI/ZzKjNxJ2nb0CznVMO0RFtswePNV2/C4jzLcsmDoU8Lk3bdGGbTMYNzSCn2wbtzV7U531I353i%2BajXj%2BD5NguAAxPBiGGC5sFUVg7gtWiqJomifkpMxQWCEUvCwWs3DQBhVkSODnzIvjtgua8XkOP5h0A4JVSueD11Va9KRpA8kLNGF0OGdB3W0zBMzEAB9aTJkENltNIa4fX1RVJkcZBhQEYZMFURJiAubSLjvbwLT1XSgwo8jP0Us5dhtJdnl4/5f0Az0nRnLECBxPFz3sjR4qUhiAFlNSYKgvBk9L1NOTS43/SMWpyxNQNnFM0yg4hgHzQsTlMqr6lq%2Br0hK9CCWJYgyQpMjwQPQzwVKgtSGWlFEjZLh4Pg91K2rZt%2BoIzyv3oi4hC8RJckwdBy3JLxaFVDLTKum6Ujuh6FCeggpqtVLiBKyklrXAgrJAGy7NoRyAvqFzwTci41uwDawYhqGZRhpz4YIVzBHc3aFN%2BZ9Eso5LLm%2B361O2H5TKp57/rrC5RpquqHEmta3GKlGyop5SABVyRexqTh8vBkHsiDogICBLPdBQ4Sl/M3AZv6NHc97bvux7GZRuY%2Bfo/jPh%2BC6hEwaSaw4rj6BpzZTeNgTzpS89lztn5monKdUDy059MB%2ByidDcqWeq8aOYEd2NKy9qY69kDCPA3r4ROE74JGsP2ZqQPpqJUlhZBtxNtRNkUbRhCVrcImhv2kAUO1cFU4GvKybolKtc%2BnWfueqPTje67tbVnOAeKom3A1i5q8NlK1d74aTWQ3W/q4dDWfD7Ox9Hs6kouoW2Iy8XJelxo5fBhWldTNkh7aS6B876%2BMQN1vysdvYHcuAWEBYq3OKBHjRaNq/UWbdLiuwarTaOAF2oJn5F1fKhVVTFTMNPS4a8s7pDnp7UcUCHS8k6onHqBEm6DT%2BBnMa6CBD2TMLnWa808aLSLujYiMJ7JblzIQSE%2BM8brQPPLD05pWE7kcFCLhmw9rEwOlWdAx1m5wOfvzBiHclBd2pq9Bet8PrKKHtQke0oqFcPctpMRpNg4KIrEvOe9Ml5UNXpnCalDkHgiQdvcmu9hZz0PsrJQJ8%2BGKzYMrK%2B1izCazvlooJj8KIcAWLQTgABWXgfgOBaFIKgTgRdLDWCVEsFY0VhI8FIAQTQUSFgAGsQCxMkPCDQAAOMwZg4hxC4LEmp1SuBUipNIGJHBJC8BYBIDQGtEnJNSRwXgboNaFKSVE0gcBYAwEQCAJYBBEhTnIJQNAtw6DRFCHCTgqhqkADYAC0BzJAXGAMgPyUh4RmF4HdQgJAtx6H4IIEQYh2BSBkIIRQKh1BTNILoNoAB3GUiROA8GiXEhJRSUmcAlFOFZqpUBUAuPs45pzzmXMnpU6hEAPCbPoKFcwoIuBzF4JMrQCwIBIA2YkLZZAKAQFpfSkAwApDBJoM9aIboIARBhREYIDRITgt4AK5gxBIQSgiNoC2kz8kbNghKBgtBhX/KwBELwwAgK0FoG6bgvAsAsEMMAcQaqWKyrwPNGFQULZTjWPkmyXTkm0DwBEGUEqPBYBhQVPAfT9WkDJMQCIn0NRGqMC6owRSFhUAMANAAangTAQLFyJPyS84QohxCfPTT8tQMLAX6GNSgaw1h9CurdJABYqIah6qOZZK0pgMmWDMMMwNxA2EVogAsOwFrnAQFcGMVopBAjBD6CUAYbRchpAEIOnIKRp0MGmP0Mo7Re21BGE0TwLQ9A9ojuuqYo6ZgTtsBu2dEwN1LvHWUbt2TVgSEhRweJpAhm8BGaiw5JyzkXKuTii4EBcAPKJXkslBSo0LAQJgasAwu2kDKZIUE8I4igg6RoSQZhJAHIGbEg5CQuk9NIH0kl8IDlcAOdUuIrSDkVKaUhg5z6YUjLGSACZUaZnzOpYshFqzGXMsJTstgnAGgsBJFSI5TBwKmniPCLgVS7n4CIO2qybR01vKzdIHNSg83/N0MEkFTAwX6ofU%2Bl9sKODwuWVOC4yL33orOSmSTcRpNVL/fiulhLLTCTMCBil0yOO8eiGsplqACUDHs2yxpGtOUAlYpQPl/yxVCpFaQBLEqpUyocElhVuYlUqpheqzV2rdVJcNca01yT8BZg5la/5NrkB2qS46mFLq3VCs9WsZJPq/X5MDcGpQobSullYzGpg8bE3Jt5EllTmaPnqdkLmv5ySdOFsjY2qwlgy0RE7VWuS6Ra31rrKt6wLbX1to7fAbtVQ10uAYO4Ld4xh03cvbMSd86ahnqSK99IT3j27pqF0UYd2h2/c6Bew9y6d2nsBxDg9RRweksWMsO98OunGYY5wGzn6JNlikzJjQf6AMKY8yS7zYHSAQagzEGDeHekgFBI51DVJYlxHaaCNDGHJBtBM4x2wzHQNTKpexpASzEWBf88QfjawhMYpYAoEkfkSRSdjMMOTgGnnKdkKpmbXz5CaYWzoWnpA9MGYhfoKF9H/kjPM4iqzKLVDS9l/LxXLI2J4uC256IRPQQk/5zMmlbv6Wi/94SkAcubr2QV3EeySu/p2/U3QaLPK4vJJS6q/JKe0uysy8FxVyrVXlcwBqrVYgiv%2BpK%2BG9rBrzVVfJNa1QtqAQNcEFUJrrr3WQja969tXXeA9ZDYCAbkaffDdG0mlNk2NfTYkLN75uv80G4MCtkt63mtbZSTtgKnB1jy0O821t0RFM18rauvd13btZCHSO2HV6515HSO9qdNRvsruBwIf7m7z87su3ut/T/ocA4/%2BejDmOs9jeojh8kZtChbujrHhcDLnLhFE7gCC7gTiQETqSuSqTuTlgJTg%2Bvhn0vUvCKCKCLEs0hzgMkQVSGRubsMpwExixvzqUiAJILEohm0lSAMtUpII0lwLUmYHRl0qCJATQaMnzpSg%2BrctQa%2BrQaIcUgGtyukEwUAA)

## Links

- [Example](../../../code/facilities/metafunctions/omennivore/bi_harvest/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/omennivore/bi_harvest.hpp)
- [Unit test](../../../../tests/unit/metafunctions/omennivore/bi_harvest.test.hpp)
