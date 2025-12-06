<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::ExtendFront`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-extend-front">To Index</a></p>

## Description

`Omennivore::ExtendFront` accepts a packed vessel and returns a function.

When invoked, the function appends its arguments to the front of the packed vessel.

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
/**** Capsule ****/
template<typename...>
struct Capsule;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = ExtendFront<Capsule<int, int*>>
::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult = Capsule<void, void*, int, int*>;

/**** Result ****/
using Result = Metafunction<void, void*>;

/**** Test ****/
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

## Links

- [Example](../../../code/facilities/metafunctions/omennivore/extend_front/implementation.hpp)
- [Source code](../../../../conceptrodon/omennivore/extend_front.hpp)
- [Unit test](../../../../tests/unit/metafunctions/omennivore/extend_front.test.hpp)
