<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Rise`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-rise">To Index</a></p>

## Description

`Varybivore::Rise` accepts a list of variables and returns a function.
When invoked by an operation, the function sorts the variables in ascending order and instantiates the operation with the result.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> Oper
-> Oper&lt;V<sub>i<sub>0</sub></sub>, V<sub>i<sub>1</sub></sub>, ..., V<sub>i<sub>n</sub></sub>&gt; where V<sub>i<sub>0</sub></sub> &lt; V<sub>i<sub>1</sub></sub> &lt; ... &lt; V<sub>i<sub>n</sub></sub></code></pre>

## Type Signature

```Haskell
Rise
 :: auto...
 -> template<template<auto...> class...>
```

## Structure

```C++
template<auto...>
struct Rise
{
    template<template<auto...> class>
    alias Rail = RESULT;
};
```

## Examples

We will sort `2, 2, 1, 0` and use the result to instantiate `Operation`.

```C++
/**** Operation ****/
template<auto...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<0, 1, 2, 2>;

/**** Result ****/
using Result = Rise<0, 1, 2, 2>::Rail<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Rise` is inspired by the talk [Adapting C++20 Ranges Algorithms for Most Metaprogramming Needs in Fewer Than 1,000 Lines of Code](https://youtu.be/69PuizjrgBM?list=PLPqbaGB3rnNmIaWPvuu4U6LWt1XooNi-L) from Daisy Hollman and Kris Jusiak.

The primary mechanism is implemented within the helper function `arise`.
The talk [Understanding The constexpr 2-Step](https://youtu.be/_AefJX66io8?list=PLPqbaGB3rnNmIaWPvuu4U6LWt1XooNi-L) by Jason Turner provides a relatively detailed explanation of the usage of `std::array`. Here, we will only walk through general ideas.

```C++
template<template<auto...> class Operation, auto...Variables>
static consteval auto arise()
{    
    // `std::index_sequence<I...>` is created
    // for the length of `Variables...`.
    return []<size_t...I>(std::index_sequence<I...>)
    {
        constexpr auto sorted = []()
        {
            std::array original {Variables...};
            // `original` will be reused for the result.
            std::ranges::sort(original);
            return original;
        }();
        // We use `std::type_identity` to avoid construct
        // an object of type `Operation<*>`.
        return std::type_identity<Operation<sorted.at(I)...>> {};
    }(std::make_index_sequence<sizeof...(Variables)>{});
};
```

Finally, we will make an interface to accept arguments:

```C++
template<auto...Variables>
struct Rise
{
    template<template<auto...> class...Agreements>
    using Rail = decltype
    (arise<Agreements..., Variables...>())::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEAQCcpAAOqAqETgwe3r4BwemZjgLhkTEs8Yn%2BKXaYDtlCBEzEBLk%2BfkG2mPYlDE0tBGXRcQnJts2t7fldCpNDESOVYzUAlLaoXsTI7BwA9ABUR8cnp2cHeyYaAIKHxwDUACKYqa6MyHiYCvcnlzd350Bpz%2B1yuoLMgQiyG8WHuJkCbi8jlohAAnvDsGDzJCGNCvLD4W5kHN0FgqBisRCoTDMHCEWJgCRCAgWBSbtjqfjaYSWsQmOjApj2f8gaLgWCAQd7gBJFipehsQRMPo/Y4gyVioEgiUne4tPBKVVHEEETBygymwmm83KzA8pGoAB0zox92hTAU3wA8q8%2BX1SHqHc7HQA1fVMWL0BRs65zZV4ZBugRzTAANzEgaIeuIBswEFWWIA7BZ7qW4Tcy/c9ns4QA2DQkkAgCJYVQAfSUAEcvO87QjpcGKfX7ga3cRMLb0GDK9X7vxiPcCAhafQjEv7qgqHWNGGcxGo4P647p2XxwQtgw4f4rP5HoTMgAvTBtgjB6UYiCN5sMVsdzDd3tCQHF1BQLCsyxMYsT0rUs0AYFNVFSBcmAde4FBIU10DpR4rxvR582gmDIKscCYJgr9eX5Dcc2ACIM2I3c8H3L5B0LO9AhI64yLI2cTHrJlaOYWg%2BI0e4AHc6Foe54nuccvCULD50XZdZK%2BLxaFfQjuLQgh0CbPkjC%2BJt0NaCABLo2gCw4rTuLPC9qLwQSxHhTjtMg/CrNc7jZwAdVpeTuXrL8CFRV42zwLBBDRETF1QPVU1QCKk3gghiC8BwbNLWdDA3WJtHqAgNy3ELXm3H0EnjARCQOIcNGPUiYLs4hL2C0LnwixhHBCwlyr9bJ7wwzB0EdZUIGlVZB0FV1iPclzCPcz9dKbFgmAAa3an9MHbLse1xPs3EfTBN2DCBGOYhQrMxKC2M8ot2M4nUHgAJVzI0LjBa15Vte0iGDM7Iy%2BGM5jShx7hepQiy80tPotfaYe%2B%2BkgxA7A3QMT1g2uYBxzNTroymhr5IiYAwaYOhsPuLBoRKu0GogfUIYRTHscVAgFGDAN/oPZH81WJtqbm9k2IF0ERU1X5HqOe5sFUVh5VpcXRbF40sUVqVesqy8FeueHLUR37kbBYH0sK9W%2BmFiWpSELxUiKIanrUjS3pBQmjHuK2bYyO2HcK%2BEcNN/qEQ0AMuADMxQ4pazhVuXV7YUdTCq1l3idj%2BPyfB/ag/uEP7jDnOMSbJ7SeEhF/aqqbI5F6OHgAFS%2BBO1UN5pHGQNsPSUUyvwUVhnw9QkU40gN3dt9B%2B4IDFPI4dZaE4fxeD8DgtFIVBODcaxrDQzZtm5CEeFIAhNEn9ZVoCSRHQ0AAOMwzCSJIuH8C/z64QtC2kaeOEkXgWAkDQg/nxfl44LwBQIAg77wXpPUgcBYAwEQCATYBBUhInIJQNAco6AJCiN3Tgqhz61gALS1kkPcYAyBExSEdGYXgQ1CBMj0iHfgggRBiHYFIGQghFAqHUOA0gugQ5iT5KkTgPAp4zzngfJenAvRIkQYVTc9wcH4MIcQ0hWdT5mHuBADwaD6ALmxFwVYvAwFaHWBAJAqDUjoLIBQCA5jLEgGAFIMONANIJGARAWI4jYh0WIKiIRvAvHMB8V6PKBU/GkFQSzL0DBaC%2BO4VgWIXhgBuDELQYB3BeBYBWkYcQcS8DjgaKmIy3Ctr1CRLsXeERTRv0XiiWIfIfEeCwOI1KeAv7pNIIU4gsRPbPCycAFERgD7rCoAYYACgQyfDEuVeeu8GHCFEOIVhcyOFqHEbw/QhhjBr0sPoPAsRgGQHWKgVIfQ0l4JJL7UwlhrBmH/p0nMWADn5m6L0bILgfzTD8CHMIiwKhVD0EULIAhPkAoyEChgww/ljBDnUBoAgBhTE8B0PQsK%2BgIoWOUUYiQYXzBBTiwYkKsUSHWOhLYOxiX6FEaQP%2BvAAHyNwQQohJCyFqI0bgGhuid4GL3kM9Yy4mBYESM84%2BkhAiOiSIEF%2BGhJBmEkPWDQ/hawpDfh/UgX9AhcEdLWLgtZz5JEfrWfwkg74StrNS8RACgEgJ5eAkxMDTFwOkUg6xtidGYLYJwFoLBUyFjwUwVGmys5JEdJqxe1CiAPL0HMphizpDLKUKs7hugw78KYII9JIiOCz3NdwgBUiEFIiKvSxRRD3Suy4MG0NGitEWJ0XCCEZhuVGIgQ611CRkE2NQNosYZaHG3yDs400xA3EeO4QElosTd7jqCSEhwYSImdSiTE8R8TEnJNoKksJmTNk5MXvgfJjhClpLDaoUppowmVJ6OI2p9TUSNN2IvFpbTd6dO6UoXpO6iZDL4KM8ZkzplhOjQslhcbZArK4YvZNGzBlXKsDs2pTyjknOyGci5gRHiwZuXchIDyjKHJeQVN5EBXB4pCD%2BQlyxsVpDBX0UjgK%2BgUf%2BTCnohH4W4qRfkZjry2MEt%2BUS/FiK8hfImLxzFlGKWkq3hSt%2B2aaUSI4MWxlAby2VrPmy/AEb60aqbby0g/LBWUEzaq9VwbpWFhqM/QIMq5XGpzf/TgVrQHfqgbA%2BBMiO1tuIO63YXqlEsAUKmRMqYK2OlhnMKhGnaFRtkDGkDbD5AJogzoEAwRU3puEZSrNYjc2SKdbIrcqg/MBaCyFsLhVNFdtrQkLTgQdO2sgWYyrliPNNZ0SAQLNs2zBaSG2MrbZCtxroEOkdnjvGTv8WN4J%2BU53tIXYIJdsS92YASUklJaTd7buyQ%2BjJeTCNHvESU5AZSL2CCvdwm9E773NJzM%2B3gr6elmk/YM%2BrIymBjImZgKZrwZm8CA8wiQoH2GJbWSl6DWzrnwb2YhpeyHkycD2I2TDlhbm0vuR1aHqKiMkY48Jn5YmmPUeKNkOjNHsiMehQRuF/R2NCZRSxqn6LydUbjIJ5FAmMVLCYySze5L9GZdkxazg8iiuBfuN10Lto5jqY5Vp/RhjdP6bGM8lVn8QDX0dIEQI/h77Gp/prwsuq7O0oc7Ya1zbVhHxAJIfw4qn6Fh/ufSQt8uCXzMGat%2BgRsv2cATa4xmbKFG/k/L216xOmZGcJIIAA%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/rise/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/rise.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/rise.test.hpp)
