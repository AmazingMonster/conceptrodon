<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Vehicle`

<p style='text-align: right;'><a href="../../index.md#transportations">To Index</a></p>

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
Vehicle ::   template<typename...> class...
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
template<typename...>
struct Container_0;

template<typename...>
struct Container_1;

template<typename...>
struct Container_2;

template<typename...>
struct Container_3;

template<template<typename...> class...>
struct Operation;

using PackedVehicle = Vehicle
<
    Container_0, 
    Container_1, 
    Container_2, 
    Container_3
>;

using SupposedResult = Operation
<
    Container_0, 
    Container_1, 
    Container_2, 
    Container_3
>;

using Result = PackedVehicle::Flow<Operation>;

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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQDMpK4AMngMmAByPgBGmMQgAGxcpAAOqAqETgwe3r566ZmOAmER0SxxCcm2mPbFDEIETMQEuT5%2BgTV12Y3NBKVRsfFJKQpNLW35o%2BP94YMVw8kAlLaoXsTI7BzmAeHI3lgA1CYBbshj6FhUJ9gmGgCCd/cEmCypBi8nbi9vH5hfBAAnqlGKxMAA6SE3Q77JgKBSQ8EeQRMObEBQ3J5jYheByHABqmAQeH2/weJgA7FYHodaYcxkxHMgYQIxphVKliPS8AAvTAAfQI3L5ECWTzpxyph2ImAI6wYwswqCoiIgyKaaIUYoCFklABEnuK6T93oz/qcTX8Aa9TZ8LcDQWxEdDYfDnQFsDCDPDDgB1ZpEtZKTE0unY3FCvWy1G0SW6ryZIyHIEg44BPV%2BgMIIPmtzq1ERdHu246/UnamPUO0y1m62/WsWm1W%2B0g5hOqEer1whEdz2unvg/0y7MJzAYj1G2kJ8LAQ4AMVoqAA7mmM1GNbQvkPA6OBzcQCAU%2BaK5SDTrDQ8APQAKlvd/vD8vTxvd8OABVsEI30JDven1eH0Av8L0eMxdgYfYvCOL40AgzBUgIcdbnJB4aztb4HTbCFeyxAgcTxfM0X5DRyxAtDcyPLDi1w/ChUIwt%2BS4UiUOeJsGww1swWoh5wwI2QC3ifkzGYytWPrdDKK4nCeLwiNDnowSAhEp5yLrW0KMwqTwRdb09wnGTaMOAB5EFiEZbJlIA185zwdEhWwVRWHeTBfzvf9ROnJNlCYZAAGtMHQQliVJVcCSJEl6ENU5J3k/iiI0UhjirWKUSIlIkvuCUFOIITEpi7L%2BSU8kJ3PFjPNnIQvFSQoAoAJTHLxaCFE4MxM%2BJzIEKK3HyuKGISjKst6wT0p61KGLMPLkoKorHhKk8HnKw56oURrmvTQ5vL8gKgoi9gQAXZcvjasz6kxUrRIZJl%2BW7eICAgC4DwUMFrvHNxltWxLKuqjI6oapqbm1eb7hfW9DiETBYPQQ4HKc%2BhXNvdzcPM5AXqUFoIE2/zAvC0lHt5TBRVXFrDkkQGng4FZaE4ABWXg/A4LRSFQThussax6TWDYXJ2HhSAITQKZWXyQGpjRwTMMwAE4AA4NEl6npcSAJJDMClJESfROEkXgWAkDQEvpxnmY4XgFBABL%2BYZinSDgWAYEQEA1gIVIvAIchKDQN46HiSIwU4VRFYAWkSSRDmAZBmSkcXeACwgSDwdA9H4QQRDEdgpBkQRFBUdQrdIXQUiXMzUk4HhKZpumBaZzgjNdl2hWVQ4A8SYPQ/DyPJHFw41VQL36C5Hmll4S2tBWCAkE91JvbICgIEn6eQGAKQJpoJr4jNiAYirmJwmaQFS94HfmGIQEjJibQIct3nPbYQQjIYWh97zrAYi8YA3DEWgze4XgsBYQxgDiGfrZS%2BeAABuY4q7sghq7LYvNwgvCpnnWgeAYhmRPh4LAVc8J4F1j/UgEDiAxB%2BlGf%2BRgUFGAFisKgBhgAKHxHgTAS42r015snYQohxAZ3YdnNQVcC76AASgaw1h9CoLNpAFYqAELZG/oHC4LVTBs0sGYI2hDiAJ0gZIrooDnAQFcJMPwKRQhzHKJUAoGQsgCEMRYoo2QBhmOGKMWouiGgzBsc47oAhegtAcUMBI0w%2BgeNsDMPxCwAkrAUJzTYEhy4cFpqQQ2vBjZNyDiHMOEdDhRzMN3XAccB5gS4EPPmVCVgIEwEwLACRRSkGFoEcEksAhqw0CrdW%2BtqaJElprDg2tSC6wCFwcEyREjSxllwRI1NJBcGpo0jWSTq4m1sObEpVsx723Ho7Ourt3Zz17lPfuvs2CcGaCwMBFJA5MC7EmLgktwSDMZrHIgGjE4pHYanLh0geFKD4XnXQE0i5MBLj/OJCT5nG1rs7V2hxG4nLORcq5s4bl3PBBobuHg%2B7xGOGBMwxSR7Ww2fPfuOzCXDFhec2ERgblcASqvF46JKBbzzkfPeB9SDMpPmfC%2BDhWU30YAQe%2Bj8q4vzfh/WgX9WV/wAUAxm%2BAZQOHAZAvO0DkCwNZQg2oVcUFoL3pgrYjMcF4N5oQ4hShSFSpnFQvgtD6GMOYa2VlbzOHp0%2BbIXhudGZ/MEZQpRVhLBiJiBImp0j6hyIUemH11hVHJPUZowNkSXHyr0QYzw7Q9AmLKP42xVicgpqmGkSx9QwnmM8a4nxrRc1GJ0YmtxfQi1OJCUEitegGS%2BNMZmopqx1gxI7Ug0FVcUlkvhRSxFtz7m5PwE8rFAzcWlNIOUypwwalIN6f025LSKQzIpBSZWZh1ZTMSf2zgptll4rWfADZTt67Er2dPQ5WwTnpJYAoMBzIwFIr%2BGMGOE744vMzhwtOEgXVZ2%2Be6nQIAggAqBWXbpfa87gq2Q3KghwH2hyfS%2Bw4b7bkfqFD3DFBSAgBBnasm2E8b1EtniShIL7qr8kw/ybD11iAsBDnwOgdKN6MsZuyp%2BvNuOcsvjy3ut9%2BUPyfjKzAr936f2/rzSV5C9W/xAfKiB38HmqBgS8NVggNXINQegwEursEaMNbwY1JDXjmsocRmhTA6EMKYSwh1sh3nOr/W6/h4GvXGBEX6rVcamYyNZJwS8D0I0qLUfEZ5Wial2FcS4Bg7gm3GIS3WgJ%2Ba7HWKS%2Bl7NqXm0JvqGW4JsXq1lty4EiYWWW2zAzeE2JnauZ1d7ZXODnBkNMcfc%2B1976zRjHHfkqdRTh6zvnVUygcSV0gCluCAj1NRZTP1gRikIyD0tcWWbC2s66m3K3RoG5LSuABAmRSMwkzukBGa0bI9KzR5xLMBd5JV3T0rEIZkZwkggA%3D%3D%3D)

## Links

- [source code](../../../conceptrodon/vehicle.hpp)
