<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::ExtendBack`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-extend-back">To Index</a></p>

## Description

`Omennivore::ExtendBack` accepts a packed vessel and returns a function. When invoked, the function appends its arguments to the back of the packed vessel.

<pre><code>   Vessel&lt;Items...&gt;
-> Args...
-> Vessel&lt;Items..., Args...&gt;</code></pre>

The returned function also handles `std::integer_sequence`.
The arguments are cast to match the value type of the packed `std::integer_sequence`.

<pre><code>   std::integer_sequence&lt;Type, Integers...&gt;
-> Args...
-> std::integer_sequence&lt;Type, Integers..., Args...&gt;</code></pre>

## Type Signature

```Haskell
--Extend a packed `Mold`
ExtendBack
 :: typename...
 -> template<typename...>

--Extend a packed `Page`
ExtendBack
 :: typename...
 -> template<auto...>

--Extend a packed `Road`
ExtendBack
 :: typename...
 -> template<template<typename...> class...>

--Extend a packed `Rail`
ExtendBack
 :: typename...
 -> template<template<auto...> class...>

--Extend a packed `Flow`
ExtendBack
 :: typename...
 -> template<template<template<typename...> class...> class...>

--Extend a packed `Sail`
ExtendBack
 :: typename...
 -> template<template<template<auto...> class...> class...>

--Extend a packed `Snow`
ExtendBack
 :: typename...
 -> template<template<template<template<typename...> class...> class...> class...>

--Extend a packed `Hail`
ExtendBack
 :: typename...
 -> template<template<template<template<auto...> class...> class...> class...>

--Extend a packed `Cool`
ExtendBack
 :: typename...
 -> template<template<template<template<template<typename...> class...> class...> class...> class...>

--Extend a packed `Calm`
ExtendBack
 :: typename...
 -> template<template<template<template<template<auto...> class...> class...> class...> class...>

--Extend a packed `Grit`
ExtendBack
 :: typename...
 -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>

--Extend a packed `Will`
ExtendBack
 :: typename...
 -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>

--Extend a packed `Glow`
ExtendBack
 :: typename...
 -> template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>

--Extend a packed `Dawn`
ExtendBack
 :: typename...
 -> template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
```

## Structure

```C++
template<typename>
struct ExtendBack
{
    template<typename...>
    alias Mold = RESULT:
};

template<typename>
struct ExtendBack
{
    template<auto...>
    alias Page = RESULT:
};

template<typename>
struct ExtendBack
{
    template<template<typename...> class...>
    alias Road = RESULT:
};

template<typename>
struct ExtendBack
{
    template<template<auto...> class...>
    alias Rail = RESULT:
};

template<typename>
struct ExtendBack
{
    template<template<template<typename...> class...> class...>
    alias Flow = RESULT:
};

template<typename>
struct ExtendBack
{
    template<template<template<auto...> class...> class...>
    alias Sail = RESULT:
};

template<typename>
struct ExtendBack
{
    template<template<template<template<typename...> class...> class...> class...>
    alias Snow = RESULT:
};

template<typename>
struct ExtendBack
{
    template<template<template<template<auto...> class...> class...> class...>
    alias Hail = RESULT:
};

template<typename>
struct ExtendBack
{
    template<template<template<template<template<typename...> class...> class...> class...> class...>
    alias Cool = RESULT:
};

template<typename>
struct ExtendBack
{
    template<template<template<template<template<auto...> class...> class...> class...> class...>
    alias Calm = RESULT:
};

template<typename>
struct ExtendBack
{
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
    alias Grit = RESULT:
};

template<typename>
struct ExtendBack
{
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
    alias Will = RESULT:
};

template<typename>
struct ExtendBack
{
    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
    alias Glow = RESULT:
};

template<typename>
struct ExtendBack
{
    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
    alias Dawn = RESULT:
};
```

## Example

We will append `void, void*` to the back of `Capsule<int, int*>`.

```C++
/**** Capsule ****/
template<typename...>
struct Capsule;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = ExtendBack<Capsule<int, int*>>
::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult = Capsule<int, int*, void, void*>;

/**** Result ****/
using Result = Metafunction<void, void*>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will implement the case where we append elements to a packed container.

```C++
template<typename>
struct ExtendBack {};

template
<
    template<typename...> class Container,
    typename...PreexistingElements
>
struct ExtendBack<Container<PreexistingElements...>>
{
    template<typename...NewElements>
    using Mold = Container<PreexistingElements..., NewElements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCCSZqQADqgKhE4MHt6%2BekkpjgJBIeEsUTFxtpj2eQxCBEzEBBk%2BflzllWk1dQQFYZHRsfEKtfWNWS2Dnd1FJf0AlLaoXsTI7BwA9ABUm1vbO7tbqyYaAIIbWwDUAJIsCfRsgkxVZ9sHx6d773svR4dHBJjXBj%2BJgAzG4CABPBKMViYEHYH6DYheBxnbCqP4MdAWJjIADWZxMAHYrISACIgqzHH5/AEPWFU0E/M7Ms40m50kFgyHQtgAOn5cLOyAMCgUZw892C0VITJZEKhzD5/OUxEwmFUeEGwWA2FujAICh%2BcIRBCRKLRGKxONxnIltSlxE5KrVGq1Rl1/31Cn5vONwPhVOJsuZbMBsNB8p5mB9oUwAHcPXcDcbjiyzl4UkYzgBZTzoAnA0ni2RMB1O1XqzWOd16wTe/mkM6xhO1g0%2Bv2U75kilG14fd5fN7rVGqVg3TBPfY/If9qdUqlmYHBYVeLAFtxoBjLBLJ/29k7bcVMBIKLz0SebL6hjkR7mK6MCvfHRHIghHk9n8Od6eH7OYWpUF4W6PM81L/OyQK3gqMI%2BkcxDAIaT5HBm2o5v%2BTCAcBaQFkWFquNieK2sep70JywQEI25HrH6AZHCAIC5rQ6CcnBCHtnuwLfn25xCF4CQ5Jg6AAEqYCRb6gccKFZrx/HJIJIliTh74keGbjkZRgjrI2ABuqB4OgOl6eg1EcVxB7nApZ7iXOyGZsAZyWbQb4gkWf4AUBDhpJyun6YZ%2BkmfCnH7kOZwACqidZl4mg8eDIAA%2BkworRAQECDOg9EKDCCWIW4jkUWcMkCcJolWXCMw9scHBzLQnAAKy8H4HBaKQqCcG41jWGcCgLEsE7mMCPCkAQmhVXMuIgLVki8hoAAcZhmAAnAtXC1bNM1cIShLSDVHCSLwLASBoGikI1zWtRwvAKCAx3DU1VWkHAsAwIgIALAQCReBRFAQGg1x0NEoQwpwqgzQAbAAtKDkhnMAyDIGcUi8mYvCCYQJD6Xo/CCCIYjsFIMiCIoKjqHdpC6C0cbEMenA8NVdUNSNLWcAA8p9H1vqgVBnCDENQzDcMI1NZhnBAHh/fQxAEouXAzLwt1aHMEBIL9CT/WQ30q2rIDAFI8Q0E50RXRAESMxEwR1OCNO8GbzDEOCzMRNomAOFbpC/UmzMMLQluk1gEReMAbhiLQV3cLwWAsIYwDiL7eCqp52miYz6rO59KyDeRFSM7QeARFTdseFgjOmngB1h6QifEBEcmkv8Uc50YI1zFQBgIQAang8bMwqrtY8IojiPjfdE2ojPk/oUcoB1lj6LnV2QHMqA7mkofg2lLmmJY1hmGdlfEPpScL60ztVC4mIjM0pCBFKUx9C0OSpAIF/ZMkj8MJMvQxGMFQn%2B0QwNJ4Joeg7C/wEB0eoH9ih31sP/Z%2BYx/6QOmDLeYixlgSDphweqJ1GbnW5mDSG0NYbw0RsLCAuA0aS36jLOWTc5gIEwEwLAMQIBjViMCXkC1gRbQ0HESQoMjq1VBgtfQnA9qkAOgNXkoMuCgxmgtdaoNJorU4aDbBpNzqXWukNJuD1npK1emzT65BKCawloDNgnA6gsG0oScGTAhQGCzFwBavIuDTRRvgIg%2B90otD7jjQe0hh5KFHqTXQ8RKbUzDhgrBp1eDnVZu9T6ZxOZ4N5tDYUUcEYuLcRoEWYtVYSylsCMwsttF3UVsrVA4tpQayqQUvoGSjDOK4MdfWfxiBGxNqTG2FtXY9Ltg7J2Lty7u31J7b2jM/YByDrQEOrsI71xWM1fA8dHCJ1Ds1FOyA06u0zjtZqOc84W0LksuW%2B8y6DUrtXJQtdI5GAbqAcpfBW4KA7l3Hu5c/EDzxoE2QI8SbNTCRPRum8rAz0OfPFhLVl4CFXuvQsoLt672iN4w%2BUKQGeWcBAVwcCr6YkQdAh%2BVRcVErSASr%2Bx9MXVFgYA0YlKqjgK6DfT%2BwCaWZEvuMCBzKoFfzmN1VBeNokM3UZwVJBCHGZOca46aItyFeKKdQspCs6EMKYZQDBYiJEuJ4YSWqC1NrAl4VDFosSmYXVsFo%2BW91HovTeuzYxP06lq3MSsKxfMWAKG0vDbSUqwyDA8RQjGvjZD%2BJ%2BQTeQwSAU6BAMCUgESEhWyFWos6LNDEcy5qod1nrvW%2BrpIMPJTrCn9WBKUq1FSUCFpqSYytMQvX8Tij6hacU/UEDipmwJdB2mdNNubO2fTe320difV2ozBDjJ9sszA/tA7B1DoNBZ9zTmkBWb/dZydVCpz%2BLswQWdSaHPzuCE5xdzmuyuTXOu9ztQ6Jbkwdunc4zd0YL3EN3yJC/MJpGseMbgXGGnjYCF8BF4woYKHVYaUp5b0sDvOJe8D6Qr5T/KlZ93C0svtfQoLL76v2Jahl%2BuQyXcqQfSv%2BnRcUYoZQgwj0DOUAPZayiYVHeUoN6ugkRmDhUpo4NzLNXqziNt5C22VniSAKtLbQ0g9DGF9ChTtTVIBFq8mBMCWqq1JAtI0Epwksjk1xM4Jom64nxqSFqhwjahIjozUkMtLgc0zCqJ2sCDjunzVlowcjHTZqaHlLmJXFIzhJBAA%3D)

## Links

- [source code](../../../../conceptrodon/omennivore/extend_back.hpp)
- [unit test](../../../../tests/unit/metafunctions/omennivore/extend_back.test.hpp)
