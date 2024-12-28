<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Phantom`

<p style='text-align: right;'><a href="../utilities.md#phantom">To Index</a></p>

## Description

`Phantom` accepts a list of stockrooms and returns a function.
When invoked by an operation, the function instantiates the operation with the stockrooms.

<pre><code>   Stockrooms...
-> Operation
-> Operation&lt;Stockrooms...&gt;</code></pre>

It also contains a regular function, `size`, which returns the total number of the stockrooms.

<pre><code>size() -> sizeof...(Stockrooms)</code></pre>

## Type Signature

```Haskell
Phantom
 :: template<template<auto...> class...> class...
 -> template<template<template<template<auto...> class...> class...> class...>
```

## Structure

```C++
template<template<template<auto...> class...> class...>
struct Phantom
{
    static constexpr auto size() -> size_t;

    template<template<template<template<auto...> class...> class...> class>
    alias Hail = RESULT;
};
```

## Examples

- We will create a `Phantom` with stockrooms `Stockroom_0, Stockroom_1, Stockroom_2, Stockroom_3`.
Then, we will transport the stockrooms to `Operation`.

```C++
/**** Items ****/
template<template<auto...> class...>
struct Stockroom_0;

template<template<auto...> class...>
struct Stockroom_1;

template<template<auto...> class...>
struct Stockroom_2;

template<template<auto...> class...>
struct Stockroom_3;

/**** Operation ****/
template<template<template<auto...> class...> class...>
struct Operation;

/**** Packed Vessel ****/
using PackedPhantom = Phantom
<
    Stockroom_0, 
    Stockroom_1, 
    Stockroom_2, 
    Stockroom_3
>;

/**** SuppsedResult ****/
using SupposedResult = Operation
<
    Stockroom_0, 
    Stockroom_1, 
    Stockroom_2, 
    Stockroom_3
>;

/**** Result ****/
using Result = PackedPhantom::Hail<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

- We can check the size of a packed `Phantom`.

```C++
static_assert(PackedPhantom::size() == 4);
```

## Implementation

```C++
template<template<template<auto...> class...> class...Stockrooms>
struct Phantom
{
    static constexpr size_t size()
    { return sizeof...(Stockrooms); }

    template<template<template<template<auto...> class...> class...> class Melancholy>
    struct Detail { using type = Melancholy<Stockrooms...>; };

    template<template<template<template<auto...> class...> class...> class...Melancholy>
    using Hail = Detail<Melancholy...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQDMpK4AMngMmAByPgBGmMQgAOwArKQADqgKhE4MHt6%2B/kEZWY4CYRHRLHEJKbaY9qUMQgRMxAR5Pn6BdQ05za0E5VGx8UmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimGmujMh4mAq3R%2BdXN6f/xx%2BlwuwLMAXCyG8WFuJgCbmQE3QWCosOwIJBfwBWIOQMxtwAkiw0vQ2IImI0vodcdiaWd0VcCJgiQZGbC3IzmeTMGyOcSuWymF4iAA6UWo26QpgKBSi4XiyXS2XNVDIADWxFQqBYClRIImxC8DluygQhiILHRiSsV1uttuc0cyAlAgmmFUaWI9rwAC9MAB9Ahe30QZYgu0wq23YiYAgbBhBzCoKiyiDKtUarUKUMBCwR%2B70y7h3ks7lw4v8stMvmsyucmtuQUisUBbASgyK5uthUyzttqWfACy9UMyAQngAnrqbXb9YbA48WnQI7mvFkjLcCOPnjCAvdbkODAxRxO2Wn1ZrtbLdTm87DrcDp7by/Xn6X2VWSzyPxWG0LUFeWz7Ds5UA7sAK7dse2FA8RzHWhJxbMM7VXcJgFuAAJJgl1hPcFyw2g2Rgo84PHcCQBATdnjvS18xzAtMVpE5qTuAAxPBiAmW5sFUVhiUwSkcQxRiASBdEwQhKF%2BLZNAjyeAgdUQq4hLufEOU%2Bb4QVfL86zfRt/17MDOz1AgDSNM8MxYP0NGopSGW/F97N0v9wKAqCp0uWczKIdMLz9LgbIfS4tNrasnKbECIP7cDjNMwNzN8swAs0xztNCgVnIMyDoquTy4u888tT9AIkt%2BI5bgAeWeYhyRyAS6TsnTUs/ELmt/cL5SyzKoqMnKTLnCqqpqgQSuuMrlCYNVMHQW4ADUPjsOqgRQ9dxsm9ATTNLUdz3DbBC1dE4SQ214sKjRSBhR9bhOyyuHOo6rvyiy/TMO7LuuoqDrROjbNGu4hC8NI0iUdAACUPi8WhAw0q5lrQ/7AcyKawYUCHAxwgb4iGhgDrce73rOi7Cztd7bsJ8N3pesnice3ziqUxDvsCvFkdRxaQVh24Wch7bjQm1Upt281yMwug2UqzHGmve9lIOW4ABUPihqljJq5A/X7eICAgRFyIUVh/SlNkuYIc74eKJHwch1Fs2l0rhP%2BZjZaETAZOm7jePoNm7ftpiCwdPA1Y1toIFW/n1tNPaWF1n1MBDbb0ckG2OFWWhOGSXg/A4LRSFQThccsax7XWTYpLBHhSAITRk9WVUQGSSRhQ0AAOMwzAATjbrhkmbpuuESRJpFTjhJF4KOuA0M7M%2Bz3OOF4BQQDOyus%2BT0g4FgGBEBAdYCDSIVyEoNAiToeJIn1zhVCbgA2ABaS/JFuYBkCdKRhTMXgpsIEg8HQPR%2BEEEQxDsCkDIQQigVDqGXqQXQt0ADu1U0icB4CnNOGcq4504OVIUu9AxJluBfG%2Bd8H5P1uC/MwtwIAeCPvQT05gAhcGWLwJeWhVgQCQIfNIx8yAUAgOwzhIBgBSBejQSG8R54QBiGgmI4RWjjkQbwKRzBiDjnKjEbQLsl7l0PqSAg5UGDwTQVgGIXhgANloLQee3BeBYBYIYYA4hIH4GjA4PAAA3D4aC3QuyFNscu4RGRD2zrQPAMRqpKI8FgNBJk8BR0saQNxxAYiI0eDYowQSjBV1WFQAwwAFAzXeDA8Wmdy5/2EKIcQwCSlgLUGg6B%2BhbEoGsNYfQwT56QFWKgNIjQLHX0RDhUwBdLBmGnvE4g393FtJ6OonILgGDuE8J0PQoRwjDCqKMW6xRsgCGmH4dZmRNkMAWCMBIt07BTIEP0KY8yCgnPqGcpokxBjLMWGs2wDztl6DmG0Q5qzjmrAUMXLYEhkEcHTqQKevAZ54Kvrfe%2Bj9n4NzIRAXAn8aFlwYRXDJqwECYCYFgBIIZSC10CMKNuAQB4aEkGYSQl8J7JEvm3fQnAR6kCjnQ4Ul8uCXybm3Xul965d1JZfMFaCZ5zwXhi5eLCN6sK3lgve3DeHUNPmwTgrQWAuMSNfJgfZ1xcDbsKLgjd374CIKMn%2Bt0SkAPKdISpShqmQN0C9OBTAEGWOBaC8F6COCYJ3kKW4uD8Ewp1WhPVBrG7kMoRw6hMIwRmHRUwleMrFXxH3jwrUUbRiSiMHq8efA6CMg4pQCRkCFEyLkaQUtSiVFqIcOWrRjAdF6NkQ4zARiTFiHMeW6xtj7HZ0cVMtxFjs6eOQN48tfj6hoKCSEmR4TtjZyiTE8u8TElKGST21CGS%2BDZNyfkwp5bLVlKATa2QVSIHZ0dXU9J/SrCWGaTEVpBKOldM4D0gg6A%2BmNMGcM%2BIZrxkEtOc45wEBXDvNuksioRy9AbMaGB9IezGjfKWDc3o5y3lXJ2ZMoD9z5hPKgyc9D%2BRMOfMeZBn5QK1gbEBfQxlILUGQMhYGwhWaQ36sNRochyLTUxrofGzFpBsW4tGASoezLWX6opSkNu/cAiUupZIW6nrRW2HFQmqV8AZXb2wam5NxBlXbDVYQ7ULinQuNDSWCYxqUXf1/rIK1x6QHyDteenQIAgjOtdUg2jHqRUYLlTgqgeCjMKBM7cMz%2BqLOBgoemzhPGAh8clavNhMXqE6ZS6MEzgM/Thb9JFv0qg755pEYW8RkjpFKPLZW5Rqj1F1q1No3R%2BiW1ttMZ22J3bUnzqsexAd7jIEjrHbEidATeDTtCeOOdkTRlLt4CupJTIN3pMS1kpgOS8mYAKc8IpvBD2AIkCe0BzmaluavcYL9Nhp2PvaZ0nIFidg6xvdYIZEKRljKu1hxoMy5lEcWbMpDLyYM5Dg4DsoeHyMobuRc9oGGPm3Ow1D/7xzXkDDgyRxHFH/lUaAe6%2Bj09OBBfvsZ0z5muScSRSakgPH6GMP44JvFlBgViZAO3YUAQAjJG7gpiebPEhcuFQxzgYrF78aJckElfdEgTybpITuXAW5mCFUPAIuOIWC4lcw4Fb9%2Bd49nur6ucTRHTMkEAA%3D)$Done$

## Links

- [Example](../../code/facilities/utilities/phantom/implementation.hpp)
- [Source code](../../../conceptrodon/phantom.hpp)
