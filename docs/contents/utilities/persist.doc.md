<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Persist`

<p style='text-align: right;'><a href="../../index.md#transportations">To Index</a></p>

## Description

`Persist` accepts a list of items and returns a function.
When invoked by an operation, the function instantiates the operation with the items.

<pre><code>   Items...
-> Operation
-> Operation&lt;Items...&gt;</code></pre>

It also contains a regular function, `size`, which returns the total number of the items.

<pre><code>size() -> sizeof...(Items)</code></pre>

## Type Signature

```Haskell
Persist ::   template<template<template<template<template<auto...> class...> class...> class...> class...> class...
          -> template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
```

## Structure

```C++
template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
struct Persist
{
    static constexpr auto size() -> size_t;

    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class>
    alias Dawn = RESULT;

    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class>
    using UniDawn = RESULT;
};
```

## Examples

- We will create a `Persist` with items `Item_0, Item_1, Item_2, Item_3`.
Then, we will transport the items to `Operation`.

```C++
template<template<template<template<template<auto...> class...> class...> class...> class...>
struct Item_0;

template<template<template<template<template<auto...> class...> class...> class...> class...>
struct Item_1;

template<template<template<template<template<auto...> class...> class...> class...> class...>
struct Item_2;

template<template<template<template<template<auto...> class...> class...> class...> class...>
struct Item_3;

template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
struct Operation;

using PackedPersist = Persist
<
    Item_0, 
    Item_1, 
    Item_2, 
    Item_3
>;

using SupposedResult = Operation
<
    Item_0, 
    Item_1, 
    Item_2, 
    Item_3
>;

using Result = PackedPersist::Dawn<Operation>;

static_assert(std::same_as<Result, SupposedResult>);
```

- We can check the size of a packed `Persist`.

```C++
static_assert(PackedPersist::size() == 4);
```

## Implementation

```C++
template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...Items>
struct Persist
{
    static constexpr size_t size()
    { return sizeof...(Items); }

    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class Tranquil>
    struct Detail { using type = Tranquil<Items...>; };

    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...Tranquil>
    using Dawn = Detail<Tranquil...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQDMpK4AMngMmAByPgBGmMQgAGxcpAAOqAqETgwe3r7%2BQemZjgJhEdEscQnJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlUbHxSSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BzmAeHI3lgA1CYBbsjj6FhUJ9gmGgCCd/cEmCypBi8nbi9vH5hfP3eTE%2Bp0BfwBryBIO%2BkPBpyYXiIADoUTdDvsmAoFCikWiMVicXiDATUQFsOjidjSeT8VSkQBJH4KG5PcbELwOQ7KeKZcZPEwAdisD0OosOs0cyHRAnGmFUqWI4rwAC9MAB9AhK1UQJZPMXHIWHYiYAjrBhazCoKg4iCM14KXUBCwGgAi/JFYrBwP%2BoNh3ohv39vsD0K9ob94ZDPrcCOR1IpmLpRMThLJCZJuLTtNTNMpOfTCkOABViIYAI5eOgsj2itkczUuk1MOgG51eTJGQ4EACeqUwxwCLuLpYYFarpztLCTZJOzsFbqd7vu%2BrD0dXAaha4jW6jG7hMN38MRqHz2fjZ8zuZT57zN%2Bvl4LOJL5crtGry7F7fCwEOLqYAHdzROIdG2acc3GfUdXxzEAQB7PtZ35AUF2FR4HgAegAKmwnDcLw9CniwnDi2wIQiyEQ5cIIjC8Noqilx2PYDn7L40AYTZUgIZkZweJ512DTc9yDA9BIE/dYxPO8M2TaSs1vB8L3fOtOUnNUNEQ3iHn4kT920vTty%2BCTT3kmTpyvWTzLM1kCHZFSfjVLgNLQ54DLE4T9MPHThKMqSzMfXzjPvJSbPrQ5VLMJy%2BNcrzI1EmKdzinyFJMuSgtSiz/MvazbM1VSAkirToo8uLit06KktMwKMsU9K/Jq24HmUzUAHk%2B1LBoCvuIjsMOAAxPBiHGQ5sFUVh3n7ejNPuL9O2UJhkAAa0wdBuUGvAhuArkeXWgh%2BVOPUxVUjRSGOGswvslJTo/UVwpOg6bvs/LeJnRcppmn8hC8VIimWgAlTAFC8WhNU21r4mBbI9rce7zteNS7rO1TLph26rv1PK9tuV7nPew5/sB4GByHObFuW1beQIWC/0Ar4wfayGXtQ6yIeQNVE3iAgIAuWCFFYdVMS%2BfGgYIE7Pu%2BjI/oB4WbkdJmaOIoRMDY9BhtG34Jpw6jnIlPBWfZ1oIBJpaVu28YeZVTAdSJzbJFlp4OBWWhOAAVl4PwOC0UhUE4aHLGscU1g2FizACHhSEpj2HZWBaQGdjQkTMMwAE4AA4NCT52U8SAJJDMAVJESfROEkXgWAkDRjvdz3vY4XgFBAY6I60FY4FgGBEBANYCFSRFyEoNA3joeJIj5zhVCzgBaRJJEOYBkClKQE94ZbCBIPB0D0fhBBEMR2CkGRBEUFR1Ej0hdBSf9S1STgeEdl23c0Xga%2BaxEe81K1DnHxIp5nueF8kBOhwIAeEHvQRUOwuBLF4E3B2pAIBIAHqkIeZAKAQEQcgkAwApBmD4HQF4g1KAxEfqQGI4QWjdhvrwUhzBiDdmajEbQSsI5hwHmwQQzUGC0AoafLAMQvDABjLQWg9duC8CwCwQwwBxA8IGkwvAAA3AGxC5RK0RFsMO4QXhO1PrQPAMRSy0I8FgYhNk8Bl1EaQRRxAYgS0bBIowuijCPxWFQAwwAFAADU8CYH/GDd2Yct7CFEOIfegSj5qGIeffQkiUDWGsPoPR9dIArFQJxbIIiJ4XGAqYP2lgzDVyscQdeSjkndDkc4CArgph%2BBSKEcIQxKgjBSEULIAhql6BaQ0eYwwEhjDqOUxoEw2ieA6HoOwAy%2BitG6Y03ptghntLGEM6ZixIGrHWJsCQd8OCu1IFXJ%2BnBP6T2nrPeehxF5mCAbgVe4CQ6QOgc4lYCBMBMCwAkHUpAY6BCREnAI%2BcNC5wLhXZ2iQk5Fw4CXUgZdQ5ImSIkFOqcuCJGdpILgzsfmFz2V7TgdcG7h2cXA9u8DO6v17qg9BYCR5sE4C0Fg8iBQTyYAmTsXAk5Ii4EiT2K8iBFI3ikQJO8QnSDCUoCJp9dA4Mvkwa%2Boitk7Mxc/El78qCHBpXShlTKfwsrZRyoBICkFgOOCHMwUC8WRxbgg1AoD4h9zQZa/VIxVX0oxEYFlXBjo0GBjyQhxDqHkMoSQshtD6GMIcP61hjACAcK4cQ3h/DBHCP9eIyR0jPb4GNA4BRSjT4qOQGo/1mi6jEN0fo8hRitie1MeYsOVibFKDscm78%2BLXFMHcV4nxfj/X8uCXvIVshwkn09uK6JTiclWEsAkmIST3mpIaBkrJg5R3WHyU/QpxSp0rHGRmipVSRn5FqQwdAyymlpAyK0nIu6aknuKNkI9szN0NEmcMvIl7729CWfUhYx7ZiTAvWM995QembLWUHID2i5XEJriq4gtL6WMudZq1l7KNCXPwNyw1ocTUwKWI855rzKBbIhVC1l/yBRooFAKHOZgC4ot2RB7FthcVYYJfAIlXc342vJcPUeHAaXHKnPIqU8itV/HGMvVDa9eUHyCbvCQvbD4ioHToEAQRJXStvmC8Dp8FXd0RIcD%2BvGZ78cE8J70Q1gF2uQehgImH8VEs4yg/uFmwEgAE99NUQmk5qhEwQNm0Hp64M9QQiARDT6%2Btof6sLdCGFMLDZathkbOHcNTZgPhAixAJosUmhx5axGyIzYokRnLVCqJePmwQhadF6IMd2MtJiilVt4DW2xrwG1OLNXwNxnjvG%2BL7P43gXaZOhL7QpyJynh3GDieO4t66vZpJlJwdC3NF15IKfEHlJT3mvu3QehZwQD23o6aehou3Ok3o/YBvpPQBCPt21twZcxzszL/f0W7/6GkrI3YHDZqywMPy0wcgzhwjOHA80ibzKHrnobuaa5uOGXkjHedowjIBk5IgCAEZ2ccUUV3RwKOFtH/u1wY43B5Hz/CsvIxoFl/yuABCRQKMwyKwUBD%2B9XejWGtlmFZ/sonHPLHbWcJIIAA%3D%3D)

## Links

- [source code](../../../conceptrodon/persist.hpp)
