<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Lullaby`

## Description

`Lullaby` accepts a list of items and returns a function.
When invoked by an operation, the function instantiates the operation with the items.

<pre><code>   Items...
-> Operation
-> Operation&lt;Items...&gt;</code></pre>

It also contains a regular function, `size`, which returns the total number of the items.

<pre><code>size() -> sizeof...(Items)</code></pre>

## Type Signature

```Haskell
Lullaby ::   template<template<template<template<typename...> class...> class...> class...> class...
          -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
```

## Structure

```C++
template<template<template<template<template<typename...> class...> class...> class...> class...>
struct Lullaby
{
    static constexpr auto size() -> size_t;

    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class>
    alias Grit = RESULT;

    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class>
    using UniGrit = RESULT;
};
```

## Examples

- We will create a `Lullaby` with items `Item_0, Item_1, Item_2, Item_3`.
Then, we will transport the items to `Operation`.

```C++
template<template<template<template<typename...> class...> class...> class...>
struct Item_0;

template<template<template<template<typename...> class...> class...> class...>
struct Item_1;

template<template<template<template<typename...> class...> class...> class...>
struct Item_2;

template<template<template<template<typename...> class...> class...> class...>
struct Item_3;

template<template<template<template<template<typename...> class...> class...> class...> class...>
struct Operation;

using PackedLullaby = Lullaby
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

using Result = PackedLullaby::Grit<Operation>;

static_assert(std::same_as<Result, SupposedResult>);
```

- We can check the size of a packed `Lullaby`.

```C++
static_assert(PackedLullaby::size() == 4);
```

## Implementation

```C++
template<template<template<template<template<typename...> class...> class...> class...> class...Items>
struct Lullaby
{
    static constexpr size_t size()
    { return sizeof...(Items); }

    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class Tranquil>
    struct Detail { using type = Tranquil<Items...>; };

    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...Tranquil>
    using Grit = Detail<Tranquil...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQDMpK4AMngMmAByPgBGmMQgAGxcpAAOqAqETgwe3r7%2BQemZjgJhEdEscQnJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlUbHxSSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BzmAeHI3lgA1CYBbsjj6FhUJ9gmGgCCd/cEmCypBi8nbi9vH5hfP3eTE%2Bp0BfwBryBIO%2BAE9UoxWJgAHQom6HfZMBQKFFItEYrE4vEGAmogLYdHE7EogCSPwUNye42IXgchxCXloBhiMKeJgA7FYHodhYdZo5kOiBONMKpUsRRXgAF6YAD6BAVyogSyeIuOAsOxEwBHWDA1mFQVBxEFprwU2oCFj1ABFeUKRWDgf9QZDwd7fp6If7oR7gz6A6C4Qi2ISyRTMVTcbH8QmifGY%2BTk%2Bm41jDgAVYiGACOXjoDLdwqZLPVTqNTDoesdXkyRkOBEjxwCTrzBYYxdLpxtLBTZJOjv5LodrvuupDXu%2BYdDQbns8DUOXC%2BXkeY0dJGcpWczu%2Bzw73aaPh6R%2BaLJdoZenIqb4WAhwA4sRCB2uzXmv23Ffeze6YgCAbbwqOvJ8hOgqPA8AD0ABUiFIchKGwU8CFIXm2BCLmQiHMhaFwShxEEVOOx7AcmAdmcAibKkBD0iODxPCufprquvrzkuAJboiB77ueAmJqeJLCYyBDMqyg4qho4HMQ8rFcexbGcYpoFRsiglnsJx78dpd6VlJPwqlwckwc8G4ceGSmqZZEbwtumk6Reqaia5J7iZJ6rSWYZksXZNnWWpAXqY5eluUmQnuemnlVoc0kBH5CkhSl3EqUFIW8TuzlRZF%2Bl5RFIkeQ8hnqgA8vCBYNEl9wYYhhwAGJ4MQ4yHNgqisO8VGkfJ9yPi2yhMMgADWmDoOynJMNyn5shyXI8sxpw6iK0kaKQxzlvFxkpBt97Cj563LftxmJYttyTr1/XPkIXipEUY0AEqYAoHLqicXYVfEwLZLyS2bath3/dtgN7VtrwqmYIO6glv3ndBTxXYcT0vbQb2docg0jWNE3zcBb6EF8n1VT9I4XeZYp4MgKrxvEBAQBcwEKIi1OMW4yOvetN13Rkj3Pa9Nz2vDRGYUImBoAw6BtR1vzdUhhHk804os0orQQJjo3jXNU0wozSqYFqn7vYckiC08HArLQnAAKy8H4HBaKQqCcG41jWKKawbFROw8KQBCaObKzDSAVsaEiZhmAAnAAHBoEdW1HiQBJIZh8pIiT6Jwki8CwEgaGtdsO07HC8AoIBrX79vm6QcCwDAiAgGsBCpF4BDkJQaBvHQ8SRIinCqAnAC0iSSIcwDIBKUhh7wY2ECQeDoHo/CCCIYjsFIMiCIoKjqJXpC6CkADuBapJwPAW9btv%2B47nBlS3zfqhahz94kQ8j2PE%2BSGHhwQB4nf0PK3sli8ArloFYEAkAd1SF3MgFAICQOgSAYAUhIY0FRvEUuEAYhXxiOEFoOtuC8BwcwYgMIyoxG0GLCuPsO5sEEGVBgtB8EOywDELwwA3BiFoKXAhpAsAsEMMAcQu98CGgcHgAAbs9K%2BMoxYty2D7cILxLa71oHgGIBYSEeCwFfCSeAc48MkcQGIPMaz8KMKoow/sVhUAMMABQAA1PAmAD6fTtj7JewhRDiHXh4reagr7730AIlArtLD6DUaXSAKxUD0WyNwgeFx3qmEsNYMwhdDHviwJErU3RKHZBcBLKYfgUihHCEMSoIwUhFCyAIIpehqkNHmMMBIYw6h5IEH0SYngOh6DsO0xoEwBhlIWJU2wgy6ljEGU0ipLSVgKA9psCQ58OA21IAXXgRcn6D2HqPcehxJ5mG/rgWeACzABC4EA32ViVgIEwEwLACQclB0CEiCOARU4aGTmnPOVtEgRwzhwLOpAc7nKRMkRIUdo5cESFbSQXArZvPTus6%2BxdbBlyuZXMBddwENzvi3NucDUB/27r3DgLQWDiL5APJgcYWxcAjkiLgSIHYzyIJkxesgV7eOkL4pQ/jd66EhkfJgJ8CHLNWciout8m4t0OI/cllLqW0ufPSxlzLv6/ygf/Y4ZyzCXJAVXHF8D/4EuNSMBVVKMRGHpVwNaqCXgtUoFg3eRC8Gn0IbgkhZCKEOHdaQGhjACD0MYVfFhbCOGcm4T7PhAihHMOankyR3CWWqFkS8P1ii6hX1UeovBWitgO10fon2hjjFKFMbGp8Vi%2BC2IcU4lxDk/UeK5WvHlsg/E7wdoKoJljklWDCTm7J0TYlSk4Akgg6AkmhIsGkjZGT55SKibksRzgICuAmcECW0zFhVIyDUnI3T8i7uKNkbdoy%2BkroGf0DdF6GidKGeUZpvTxmHuKWMuYwyn0XNWOsRZ37lESqvpsi1SqrUqoZUyjQRz8Bsp1ec/V1zSC3PuSMHJyigUgoZZ8vkCK%2BR8iTmYNOcK1lAc4CXdFBqsXwBxY3e%2BpqiVapJWwTg5KdlDnERKcRqq/jjGnjBueC8UjNq8a2je8g%2BWdp0CAIIwrRVnwBYB3eUq8UPyoIcVjI92Oce456VqP8GPQLgwEBDmLq4QIMya2BZqEgcbuiqLjEcVQ8YINTYgLBh58DoA6jBzqHaupIX6/zpDyGUL9QGuhDCmG8DDewzhUbouvFjQW6LCaxFJukam5AciM2CCzSotRGiYT5p0e%2BYtvBS0mMS%2BYqtpmbFMDsY45xrim2cpExINtm8JMBOkz24w07wkxCHY7EdDBuGwQZn21J6T4iZMXTk29%2BS12FNfXoUpj6Zn1L3Q0DdDTT2fo260noHSX15DfQt47H71s7vfV007z7LvlJ3XMhZa9xWXyU5wdTbm2MKA44cBzSJnPQZOXBi5wDEPIYeZQZZGGQCRyRAEAIVsQ5wrzojvkEKSMfdRaXcuiHnkMrwxoelnyuABBhXyMwsKAUBHe4XMjGLQHLLMHTjZDPKMrEMZkZwkggA)

## Links

- [source code](../../../conceptrodon/lullaby.hpp)
