<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Warehivore::TypicalPaste`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#warehivore-typical-paste">To Index</a></p>

## Description

`Warehivore::TypicalPaste` accepts a list of packed warehouses.
It concatenates them together and uses the first warehouse to hold the result.

<pre><code>   Ware<sub><i>0</i></sub>&lt;Cons<sub><i>0</i></sub>...&gt;, Ware<sub><i>1</i></sub>&lt;Cons<sub><i>1</i></sub>...&gt;, ..., Ware<sub><i>n</i></sub>&lt;Cons<sub><i>n</i></sub>...&gt;
-> Ware<sub><i>0</i></sub>&lt;Cons<sub><i>0</i></sub>..., Cons<sub><i>1</i></sub>..., ..., Cons<sub><i>n</i></sub>...></code></pre>

## Type Signature

```Haskell
TypicalPaste
 :: typename...
 -> typename
```

## Structure

```C++
template<typename...>
struct TypicalPaste
{
    using type = RESULT;
};
```

## Examples

Here, we paste `Warehouse_0<Con_0>`,  `Warehouse_1<Con_1, Con_2>` and `Warehouse_2<Con_3>` together:

```C++
/**** Vessels ****/
template<template<typename...> class...>
struct Warehouse_0;

template<template<typename...> class...>
struct Warehouse_1;

template<template<typename...> class...>
struct Warehouse_2;

/**** Items ****/
template<typename...>
struct Con_0;

template<typename...>
struct Con_1;

template<typename...>
struct Con_2;

template<typename...>
struct Con_3;

/**** SupposedResult ****/
using SupposedResult = Warehouse_0<Con_0, Con_1, Con_2, Con_3>;

/**** Result ****/
using Result = TypicalPaste
<
    Warehouse_0<Con_0>, 
    Warehouse_1<Con_1, Con_2>,
    Warehouse_2<Con_3>
>::type;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will implement `TypicalPaste` using recursion over the total number of packed warehouses.

- **Base Case:** Handle several amounts directly;
- **Recursive Case:**
  1. Concatenate several packed warehouses at the front directly and place the result into the first warehouse;
  2. Invoke `TypicalPaste` with the newly packed first warehouse and the unhandled warehouses.

```C++
template<typename...>
struct TypicalPaste {};

// Base Case:

template<typename PackedWarehouse>
struct TypicalPaste<PackedWarehouse>
{
    using type = PackedWarehouse;
};

// Recursive Case:

template
<
    template<template<typename...> class...> class WarehouseA,
    template<template<typename...> class...> class WarehouseB,
    template<typename...> class...ContainerAs, 
    template<typename...> class...ContainerBs,
    typename...Others
>
struct TypicalPaste<WarehouseA<ContainerAs...>, WarehouseB<ContainerBs...>, Others...>
{
    using type = typename TypicalPaste
    <
        WarehouseA<ContainerAs..., ContainerBs...>,
        Others...
    >::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCAA7AAcpAAOqAqETgwe3r56KWmOAkEh4SxRMQm2mPYFDEIETMQEWT5%2BXJXVGXUNBEVhkdFxiQr1jc05bcPdvSVlgwCUtqhexMjsHAD0AFTbO7t7%2BzvrJhoAgls7ANQAkixJ9GyCTDUXu0en5wefB28nxycEmFuBgBJgAzG4CABPJKMViYAB0iLB2D%2Bw2IXgcFwAKtC8KJaMomMNMBcTLErLEACJgqynP7rdYXCxEkluFkgP5/AFAp6YMEQ6GwtgXQnIADWmHQAHUGpgEEslMjUQR0ZicUk8WJCcT%2BaKJdLZfKvIrQSi6eS/hcrRdjcFgBcoTDSaDKSKmOLJTLiHKFXzQbTflSaZz3oyAEqYZDLNIAN1Z7JD/0Bd15nPBlut3JTIPBWeBfoFMOYbER8ORF2QBgUClL5crRIUFy9PuNmBOpAzVrzqdzyfz/MdQoRSNNFarNZH2DHDabht9Nk7Dr7PcLQ9ro/r1dLHkewWiJwUpFJp2tS55OdXxeHZY34%2B3siYe%2BIFkPi8HV9LAHkCAhogo02aB4qhiBDYri%2BLahezZGkovzgju9RPge67YEe0HzvyCGPiEz4TjeqEXN%2Bv7EHhSrmgGp62kYDqCs6rrvnCYEahBRIgie1r8oup7oa2cFuFhSF4UeAk4S%2BKEduxp5WkRf61pJzrYCAICDsG5rUv6iYfF8ew/FpFzYKorB3CSrz0tp3yJuYoLBJWXhYM6bhoAwqxJAQ/6mppuwXAAapg1ZVI2pmnN2F4hQWDElpO05bpOyqqqBPFKAA%2Bhoqm/MFy6hZl4WCh%2BUWbqRHmnGiIGzt6MGYElXBpVy2UDnVua5XCKHRYVgElZiiWVWYNXvF5VzcoFhy1eeOVFs1sXFcBmI7ilvVJqNA5NZF%2BFxaVs3VRpdIZYtjXjStZFAfFFyzT1W3pQt2ZjWuk1HetAhJaC816UIXhJHkkoRgoXi0KBQUnFR9qve9qSfX5P2gWCrpdXN8EPRowkPW0J0PWYiMMI9SrnWZlxfRDLzDacgMXHjv10UxmoEqxfJ0um8kw6lcMY4zBGLjDm38Uj6NJWdqFs3OrY85hD1PUVcGKcpgrPV5WJ%2BX9hNAU8eJJQ20QEBAwzoEpChwir7luKTBBHsDH3oIbyJzPNHALLQnAAKy8H4HBaKQqCcG41jWBcChLCsJJWTwpAEJo1sLGKIB25I8IaPEZhmAAnPHXB2zH8RcLEsTSLbHCSLwLASBoCNOy7bscLwCggAjwfO9bpBwLAMCICASwEEkXhGxQEBoLcdDRKEcKcKo8QAGwALTD5IFzAMgyAXFI8JmLwkqECQeBa20/CCCIYjsFIMiCIoKjqDXpC6G0ADuxBMEknA8Db9uOyHrucJ%2B7dt6BqBUBcQ9jxPU8z3PKOZgLgQA8D3egxBSRmFBFwOYvBq5aAWBAJA3cNQQPIJQVBvcYjACkGjGgv0/yUAiE/CIwQGiQlvrwMhzBiCQk/BEbQkZq6B27g8Agn4GC0EoSfLAEQvDADZLQWgFduC8CwCwQwwBxC8LwN6BweA4yiJdpgVQkZ25rEDsEAE2cXa0DwBEK%2BdCPBYCfiqPA%2BcxGkDjMQCIoNKSAikfoowIcFhUAMMABQ3k8CYHPp%2BIsVD97CHxLvaQm95BKDUE/M%2B%2BgpEoE9pYfQBiK6QAWKgVyGRRGj01lDUwlhrBmBLjY4ga8/LwAWHYZhGQXAMHcJ4Fo/hanTH6DENoeR0gCDGK0ZIqQOkMGaaUAYEwqhVIEF0UY9TxjtFGbUEYPQ9wzCGbYOZXS9CTEaAM2YsDFjLFWBIe%2BHAHakGLrwUu38R7j0ntPWe89gEQFwCvSBAc4FB1cQsX8TAsAxAgGHEAkhQTwnjqCTOGhJBmEkMPQudth7x30JwXOpB84wPhMPLgw94jxzTsPSOycgXD2OU/Uu5dK6vJrkgxuyDm5v3bhgruqBwF9wHhwBoLAYyxFHkwac1EuDx3hFwaOS98BEBKevIJ29xB73CYfKJJ9dBo0vtfKhByjknOfhwV%2Brd24XE/uc3%2Bk96zct5fyjQICwFoOiFA0EZgXkINrpSrB6DO4OoGAa3BScEYEIBCRYhpDyF0MCTQihDCmEOECWwxgHCuE8JdnwgRQiRGBIkU4tYMa5FVKUU/VR6iASBO0VUJ%2B%2BjDEUJMSm%2BBJTLGBxsXYpQDjJFGGcaAMlfAPFeJ8X4gJVjwnitCUE6Vx8XZytiS4vJVhEmFpST812GSBBZJyS6EdBSinRBFWU1J0yFHOAgK4VZbRAgLJabkXpNQd09PyBkTZSzKkbtmd0E9V6ajjPmcUA9EwVmTO6esp9fRBmtIqb7PZ2zs4qsJZwXVlyuX2h5Xy6OICHnCstbA%2BBbzSAfK%2BZQA5CKkW8tBbEO28cM6gjBRCyQbRVVEtsCS215L4CUpbu/WlzriD9zYJwFlf8WAKBjLPGMUH8zDEFY8teegu0hIkGE2QfbokgFBKQBVN8xHKsfifUuGr37aq/qodjnHuO8d5MMU19LzVPOgaCG1ri64oMM9ghjVmIEgC4%2B9JKPH45JT4wQJKmmwl0C9RXCAJCT6Bv9VYwL9DGHMLDfS9hnDuFP1jYIsQCarFJvraW0g%2BB5GOAzSfLNUYc1WLzbo3ghajGQhLWY8tgSq32McfWu05n3FME8d43x/jGCBJEzvMTvbIn9p0NJodxgEk2HHeUqdNRRHrE1vE/JlhCmnOKaUidFSRnXpqXU7I3S93Pp/Yes9nT327b6Re1p66H1vo22slbZ2pj7p26%2B29B37sbNu1sv9uzd6KYJcp0DnmLgca4xcZz8I3OwaFSQBDZmyXvMwJ8gYk7s6YZAAneEoJQR2xTiRwuqPYjoq%2ByXTgxKq7IfDpIO2gL06xELvESQScuCxzMPi7OoIlP47LqSxBBzF549OQT9nodrF/mqZIIAA%3D%3D)$Done$

## Links

- [source code](../../../../conceptrodon/warehivore/typical_paste.hpp)
- [unit test](../../../../tests/unit/metafunctions/warehivore/typical_paste.test.hpp)
