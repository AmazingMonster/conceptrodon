<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::ExtendFront`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-extend-front">To Index</a></p>

## Description

`Omennivore::ExtendFront` accepts a packed vessel and returns a function. When invoked, the function appends its arguments to the front of the packed vessel.

<pre><code>   Vessel&lt;Items...&gt;
-> Args...
-> Vessel&lt;Args..., Items...&gt;</code></pre>

The returned function also handles `std::integer_sequence`.
The arguments are cast to match the value type of the packed `std::integer_sequence`.

<pre><code>   std::integer_sequence&lt;Type, Integers...&gt;
-> Args...
-> std::integer_sequence&lt;Type, Args..., Integers...&gt;</code></pre>

## Type Signature

```Haskell
--Extend a packed `Mold`
ExtendFront
 :: typename...
 -> template<typename...>

--Extend a packed `Page`
ExtendFront
 :: typename...
 -> template<auto...>

--Extend a packed `Road`
ExtendFront
 :: typename...
 -> template<template<typename...> class...>

--Extend a packed `Rail`
ExtendFront
 :: typename...
 -> template<template<auto...> class...>

--Extend a packed `Flow`
ExtendFront
 :: typename...
 -> template<template<template<typename...> class...> class...>

--Extend a packed `Sail`
ExtendFront
 :: typename...
 -> template<template<template<auto...> class...> class...>

--Extend a packed `Snow`
ExtendFront
 :: typename...
 -> template<template<template<template<typename...> class...> class...> class...>

--Extend a packed `Hail`
ExtendFront
 :: typename...
 -> template<template<template<template<auto...> class...> class...> class...>

--Extend a packed `Cool`
ExtendFront
 :: typename...
 -> template<template<template<template<template<typename...> class...> class...> class...> class...>

--Extend a packed `Calm`
ExtendFront
 :: typename...
 -> template<template<template<template<template<auto...> class...> class...> class...> class...>

--Extend a packed `Grit`
ExtendFront
 :: typename...
 -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>

--Extend a packed `Will`
ExtendFront
 :: typename...
 -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>

--Extend a packed `Glow`
ExtendFront
 :: typename...
 -> template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>

--Extend a packed `Dawn`
ExtendFront
 :: typename...
 -> template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
```

## Structure

```C++
template<typename>
struct ExtendFront
{
    template<typename...>
    alias Mold = RESULT:
};

template<typename>
struct ExtendFront
{
    template<auto...>
    alias Page = RESULT:
};

template<typename>
struct ExtendFront
{
    template<template<typename...> class...>
    alias Road = RESULT:
};

template<typename>
struct ExtendFront
{
    template<template<auto...> class...>
    alias Rail = RESULT:
};

template<typename>
struct ExtendFront
{
    template<template<template<typename...> class...> class...>
    alias Flow = RESULT:
};

template<typename>
struct ExtendFront
{
    template<template<template<auto...> class...> class...>
    alias Sail = RESULT:
};

template<typename>
struct ExtendFront
{
    template<template<template<template<typename...> class...> class...> class...>
    alias Snow = RESULT:
};

template<typename>
struct ExtendFront
{
    template<template<template<template<auto...> class...> class...> class...>
    alias Hail = RESULT:
};

template<typename>
struct ExtendFront
{
    template<template<template<template<template<typename...> class...> class...> class...> class...>
    alias Cool = RESULT:
};

template<typename>
struct ExtendFront
{
    template<template<template<template<template<auto...> class...> class...> class...> class...>
    alias Calm = RESULT:
};

template<typename>
struct ExtendFront
{
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
    alias Grit = RESULT:
};

template<typename>
struct ExtendFront
{
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
    alias Will = RESULT:
};

template<typename>
struct ExtendFront
{
    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
    alias Glow = RESULT:
};

template<typename>
struct ExtendFront
{
    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
    alias Dawn = RESULT:
};
```

## Example

We will append `void, void*` to the front of `Capsule<int, int*>`.

```C++
template<typename...>
struct Capsule;

template<typename...Args>
using Metafunction = ExtendFront<Capsule<int, int*>>
::Mold<Args...>;

using SupposedResult = Capsule<void, void*, int, int*>;

using Result = Metafunction<void, void*>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will implement the case where we append elements to a packed container.

```C++
template<typename>
struct ExtendFront {};

template
<
    template<typename...> class Container,
    typename...PreexistingElements
>
struct ExtendFront<Container<PreexistingElements...>>
{
    template<typename...NewElements>
    using Mold = Container<NewElements..., PreexistingElements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCCSZqQADqgKhE4MHt6%2BekkpjgJBIeEsUTFxtpj2eQxCBEzEBBk%2BflzllWk1dQQFYZHRsfEKtfWNWS2Dnd1FJf0AlLaoXsTI7BwA9ABUm1vbO7tbqyYaAIIbWwDUAJIsCfRsgkxVZ9sHx6d773svR4dHBJjXBj%2BJgAzG4CABPBKMViYEHYH6DYheBxnbCqP4MdAAMWIsjOJgA7FYCQAREFWY4/P4Ah6wymgn5nJlnak3WkgsGQ6FsAB0fLhZ2QBgUCjOHnuwWipEZzIhUOYvL5ymImEwqjwg2CwGwt0YBAUPzhCIISJRaIx2Nxgg54tqkuIHOVqvVmqMOv%2BeoUfJ5RuB8MpRJlTNZgNhoLl3Mw3tCmAA7u67vqjcdmWcvCkjGcALKedD44EksWyJj2jkx%2BO6wRevmkM5OtUaxxuyv672%2BinfUnkw2vD7vL5vdao1SsG6YJ77H6DvuTymUszA4JCrxYfNuNAMZYJJN%2BnsnbZipgJBReegTzZfEPs8NchVR/m746I5EEQ/H09hjtTg9ZzC1KheJujzPFS/xskCN7yjC3pHMQwAGo%2BRzplq2Z/kwAFAWk%2BaFuarg4rINpHie9AcsEBC1mR6y%2Bv6RwgCAOa0OgHKwfBba7sCX69ucQheAkOSYOgABKmDEa%2BIHHMhmY8XxyQCcJonYW%2BxFhm4ABuqB4OgtbqZp6wUYI%2BkEFR7Gcfu5zyaeYmzkhGbAGcFm0K%2BIKFr%2B/6AQ4aQcjpWlnN5xnwhxe6DmcAAqIlWRexoPHgyAAPpMCK0QEBAgzoHRCgwvFCFuA55FnNJ/FCSJllwjM3bHBwcy0JwACsvB%2BBwWikKgnBuNY1hnAoCxLOO5jAjwpAEJolVzAA1iANWSDyGgABxmGYACcC1cDVs0zVwBIEtI1UcJIvAsBIGgaKQDVNS1HC8AoIDHUNjWVaQcCwDAiAgAsBAJF45EUBAaDXHQ0ShDCnCqDNABsAC0oOSGcwDIMgZxSDyZi8AJhAkJpej8IIIhiOwUgyIIigqOod2kLoLSxsQR6cDwVW1fVw3NZwADyn0fa%2BqBUGcIMQ1DMNwwjU1mGcEAeH99DEPiC5cDMvC3VocwQEgv0JP9ZDfSrasgMAUjxDQjnRFdEARIzETBHU4I07wZvMMQ4LMxE2iYA4VukL9ibMwwtCW6TWARF4wBuGItBXdwvBYCwhjAOIvt4CqHmqSJjNqs7n0rANZEVIztB4BEVN2x4WCMyaeAHWHpCJ8QESySS/xRznRjDXMVAGPBABqeBxsz8qu1jwiiOI%2BN90TaiM%2BT%2BhRyg7WWPoudXZAcyoNuaSh%2BDqXOaYljWGYZ2V8QmlJwvrTO1ULiYiMzSkIEkpTH0LQ5KkAgX9kySPwwky9DEYwVCf7RDA0ngmh6DsL/AQHR6gf2KHfWw/9n5jH/pA6YMt5iLGWBIOmHA6onUZudbmYNIbQ1hvDRGwsIC4DRpLPqMs5ZNzmAgTATAsAxAgGNWIwIeQLWBFtDQcRJCgyOjVUGC19CcD2qQA6/UeSgy4KDGaC11qg0mitThoNsGk3Opda6g0m4PWekrV6bNPrkEoJrCWgM2CcDqCwVSBJwZMEFAYTMXAFo8i4NNFG%2BAiD7zSi0PuONB7SGHkoUepNdDxEptTMOGCsGnV4OdVm71PpnE5ng3m0MhRRwRi4txGgRZi1VhLKWwIzCy20XdRWytUDiylBrKpBS%2BgZKMM4rgx19Z/GIEbE2pMbYW1dj0u2DsnYu3Lu7PUntvaMz9gHIOtAQ6uwjvXFYTV8Dx0cInUOTUU7IDTq7TOO0mo5zzhbQuSy5b7zLgNSu1clC10jkYBuoByl8FbgoDuXce7lz8QPPGgTZAjxJk1MJE9G6bysDPQ588WHNWXgIVe68Cygu3rvaI3jD5QpAR5ZwEBXBwKvpiRB0CH5VFxUStIBKv7H0xdUWBgDRiUqqOAroN9P7AJpZkS%2B4wIHMqgV/OYXVUF42iQzdRnBUkEIcZk5xrjpoi3IV4op1CykKzoQwphlAMFiIkS4nhBIaoLU2sCXhUMWixKZhdWwWj5b3Uei9N67NjE/TqWrcxKwrF8xYAoVS8NVJStDIMDxFCMa%2BNkP4n5BN5DBIBToEAwJSARISFbIVaizos0MRzLmqh3Weu9b62kgw8lOsKX1YEpSrUVJQIWmpJjK0xC9XxWKPqFqxT9QQWKmbAl0HaZ0025s7Z9N7fbR2J9XajMEOMn2yzMD%2B0DsHUOA0Fn3NOaQFZv91nJ1UKnP4uzBBZ1Joc/O4ITnF3Oa7K5Nc673K1DoluTB26d1jN3RgvcQ3fIkL8wmkax4xuBcYaeNgIXwEXjChgodVipSnlvSwO84l7wPpCvlP8qVn3cLSy%2B19Cgsvvq/YlqGX65DJdypB9K/6dFxRihlCDCPQM5QA9lrKJhUd5Sgnq6CRGYOFSmjg3Ms1et8rmv4%2BayGeJIAq0ttDSD0MYX0KFO1NUgEWjyYEwIaqrUkC0jQSmCSyOTXEzgmibrifGpIGqHCNoEiOjNSQy0uBzTMKonawIOO6fNWWjByMdNmpoeUuYlcUjOEkEAA%3D)

## Links

- [Example](../../../code/facilities/metafunctions/omennivore/extend_front/implementation.hpp)
- [Source code](../../../../conceptrodon/omennivore/extend_front.hpp)
- [Unit test](../../../../tests/unit/metafunctions/omennivore/extend_front.test.hpp)
