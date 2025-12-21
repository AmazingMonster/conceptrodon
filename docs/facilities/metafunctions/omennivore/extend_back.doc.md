<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::ExtendBack`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-extend-back">To Index</a></p>

## Description

`Omennivore::ExtendBack` accepts a packed vessel and returns a function.

When invoked, the function appends its arguments to the back of the packed vessel.

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

## Links

- [Example](../../../code/facilities/metafunctions/omennivore/extend_back/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/omennivore/extend_back.hpp)
- [Unit test](../../../../tests/unit/metafunctions/omennivore/extend_back.test.hpp)
