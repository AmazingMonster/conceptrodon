<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Vehicle`

<p style='text-align: right;'><a href="../utilities.md#vehicle">To Index</a></p>

## Description

`Vehicle` accepts a list of containers and returns a function.
When invoked by an operation, the function instantiates the operation with the containers.

<pre><code>   Containers...
-> Operation
-> Operation&lt;Containers...&gt;</code></pre>

It also contains a regular function, `size`, which returns the total number of the containers.

<pre><code>size() -> sizeof...(Containers)</code></pre>

## Type Signature

```Haskell
Vehicle
 :: template<typename...> class...
 -> template<template<template<typename...> class...> class...>
```

## Structure

```C++
template<template<typename...> class...>
struct Vehicle
{
    static constexpr auto size() -> size_t;

    template<template<template<typename...> class...> class>
    alias Flow = RESULT;
};
```

## Examples

- We will create a `Vehicle` with containers `Container_0, Container_1, Container_2, Container_3`.
Then, we will transport the containers to `Operation`.

```C++
/**** Items ****/
template<typename...>
struct Container_0;

template<typename...>
struct Container_1;

template<typename...>
struct Container_2;

template<typename...>
struct Container_3;

/**** Operation ****/
template<template<typename...> class...>
struct Operation;

/**** Packed Vessel ****/
using PackedVehicle = Vehicle
<
    Container_0, 
    Container_1, 
    Container_2, 
    Container_3
>;

/**** SuppsedResult ****/
using SupposedResult = Operation
<
    Container_0, 
    Container_1, 
    Container_2, 
    Container_3
>;

/**** Result ****/
using Result = PackedVehicle::Flow<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

- We can check the size of a packed `Vehicle`.

```C++
static_assert(PackedVehicle::size() == 4);
```

## Implementation

```C++
template<template<typename...> class...Containers>
struct Vehicle
{
    static constexpr size_t size()
    { return sizeof...(Containers); }

    template<template<template<typename...> class...> class Warehouse>
    struct Detail { using type = Warehouse<Containers...>; };

    template<template<template<typename...> class...> class...Warehouses>
    using Flow = Detail<Warehouses...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQDMpK4AMngMmAByPgBGmMQgAOwArKQADqgKhE4MHt6%2B/kEZWY4CYRHRLHEJKbaY9qUMQgRMxAR5Pn6BdQ05za0E5VGx8UmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimGmujMh4mAq3R%2BdXN6f/xx%2BlwuwLMAXCyG8WFuJgCbmQE3QWCosOwIJBfwBWIOQMxtwAkiw0vQ2IImI0vodcdiaWd0VcCJgiQZGbC3IzmeTMGyCABPZ7MNgAOhFqNukKYCgUIqFHjJ4XiClRIImxC8DluADVMAg8JDuVcTIkrFdbmbbnNHMhxQIJphVGliBa8AAvTAAfQIzrdEGWIPNMONt2ImAIGwY3swqCoMogcpaCuICj9AQsgfu9MuAY5xK5PKZudZcJzLO5xf5jFYmBlYolUprAWw4oMUtuAHVWjr1kplabzar1V7HgnaIG014skZbnznjCAvd252EN2y2540xE9LRY3YWmjRnU5nswXS/nOUX2Se8%2BWBVWG0261uhbWW0%2BOyHlxOPr2s%2BaJ%2BFgFuAAxWhUAAdznBdhw3Wg2XfLsvyfVEQBAGcyxNYFEgPDCMVpLFqTuIC8CTL1sFUVhiUwSkcVwvD/iBdEwQhKEqLZNAGC2NICCVHdDV%2BI4CQ5T5vhBEtr3ZCtBWrbc0SuAcNXXRN3Q0XdMzEi80Kk%2B8VQINUFNkDcImId0uFUvjLnU1dNLvGSdL0r1FKM90zDM4EGSvDTJJs59eMueSHIMpSAlc2iDluAB5Z5iHJHJqLpdzzysjyrK84UZObSUkN8/yIqimKBBC/i7mUJhkAAa0wdAtQ%2BOw4qBf8pxK8rKu1XV9Ug6q2vodE4X9c1HPiZTSBhPszQG4yuGGvqxsCpyzCm0bbnG91gsNHdD3MvEhC8NI0iUdAACUPi8WgvREq4GsA7bdsySqjoUE6vVhBdIvifKGB6txpqW2bBo0Bbfxm%2BUnMmkbAZ%2B4HBvmsGA2W1bgXWnCirC%2B7HrqkFLtuVHTo6pqKvQVq9XEEAQPAtlXuixplQ2tzrgEgAVD4zqpHSYuQd1MviAgIERFCFCrDmeLcbGCGG67iju47TtRFMkbpuj6NCvZbiETB2KqsiKPodHkYVwFM0tPVBaUNoIDxlqdSJ9gQCyH1lkg57bkkWWOFWWhOGSXg/A4LRSFQTgvssawLXWTZWLBHhSAITRXdWMqQGSSQhQ0AAOMwzAATgzrhklTlOuESRJpHdjhJF4FgJA0f7vd9/2OF4BQQH%2B6Ofdd0g4FgGBEBAdYCDSLxRYoCA0CJOh4kiKtOFUFOADYAFoZ8kW5gGQa0pCFMxeEqwgSDwdA9H4QQRDEdgpBkQRFBUdRW9IXRJrA6K0k4Hg3Y9r2Y79zhwoH/uvWjW5p7z0XsvVetx15mFuHGVAo96BOnMAELgyxeAty0KsCASAR5pDHmQIemDsEgGAFIeaNBTqKkoDED%2BMRwitF5M/XgVDmDEF5OFGI2g1Yt0jiPUkBBwoMFoLQm%2BWAYheGAG4MQtBG7cF4FgFghhgDiEEcRdheAABuHwP72jVgPbYkdwiMhLr7WgeAYjRSYR4LAH9dJ4ArlI0gajiAxFuo8WRRgjFGBjqsKgBhgAKE1O8MCr1vaR0PsIUQ4gz4hMvmoD%2Bd99ByJQNYaw%2BhjGN0gKsVAXEciSLnoiZ6pgg6WDMLXexxA97qLST0ZRzgICuGmH4SaoQFSLFGJNYo2QBB1L0G0xoCwRgJEmnYKpTRJjtE8J0PQgyHB9BGb0qoLTbAjM6QMmZTS%2BkSFWAoUOWx1n6DfqQGuvA64ANngvJeK815JwgRAXAO84ERyQVHDxqwECYCYFgBIvpSDx0CEKDOAQi4aEkGYSQM8q7JBnhnXZpdy4gAQUKGeXAZ4pwzvnGeicc5/Jnvsj%2BdcG5N0ea3NBXd0E9x/gPcglA8GwInmwTgrQWAqMSHPJgGUpxcAzkKLgyct74CIKU/ek0QnH3CdISJShok310PNB%2BTAn5SNfhwT22Kb512/n3Aetx/6ANOaywC7LOXJ0gR4GB8QYRgjMA8lBbcSVUviBS4e0CsGwJQAYIw7KuD/RIYyJM5DKHUKYXQ0gDCaEsLYQ4QNXDGA8L4QI32QiRFiNoBIwNMi5EKLjUoqZajJG%2B00cgbRga9H1A/kYkxNDzHbF9lYmxkd7GOKUM4tNAEPF8G8b4/xgTA1CrCafUVsgonX19lKuJ7j8lWEsMkmIqTPkZMaNk3J84x3WCKYckpZTp0bPqEMlwDB3BjIKA03dsylitMyO03I%2B76npDPT01Zcz%2BmVKmQIfoUxL0TK3U%2B4Z8w70noWQMJZf62jHpaRsrZp8FVKoOZ/DgxygFLwlGyjlXKNCQJuXys1CDLVPNIC8t5oxPklzLqQCuAQOWApSBnQuAQgUgskJNKDuLbD4qtUS%2BAJLe6/3tba4gNLtj0uASwBQKjrQqP1aWCYPLbl7wPrIYVvbz7yHFYOnQsLSAyrlS/KFkGcVfzJX/KgACBNCZE2JrkEwjWOuwRhgIWHCXtwwZZ2BXHHOjGE7td0omM7unEwQd0qhF58DoN6xuEAKE32DQG2xEXmGsPYRG6B3DeH8I/vG0R4jJGR1Ta4yt0jM2OGzRo1QWjGSFsEMWm%2BpbTG8grZY0pNbeB1qcUyJt7i7NeKYD4vxmAAkCi7bJntEg%2B0XyUzE1TrrjCJInaWjdftMm2k4DsXmS7CnFPiPy8pnzJmNB3Xu/IV7GkVDWaekoOQAPdJyMBh9W3pn/rfQMj9jQX2DB/fMuYr69sTJWYd%2B9OzNkbG2YgrT78VWcEM0vQTwnbieaFD51DvKSAYcQcg7DuH3mUAVURiumchQBACMkXOdGq648SEi5VtdOB4ubth75yRfkF0SFXFOkhs5cDTmYLFJcAjA/J/XAlqCFWbzJ4cinfPY52MVDkfwQA%3D%3D%3D)

## Links

- [Example](../../code/facilities/utilities/vehicle/implementation.hpp)
- [Source code](../../../conceptrodon/vehicle.hpp)
