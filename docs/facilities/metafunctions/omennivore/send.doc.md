<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::Send`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-send">To Index</a></p>

## Description

`Omennivore::Send` accepts a packed vessel and returns a function.
When invoked with an operation, the function extracts the list of items from the vessel and instantiates the operation with the result.

<pre><code>   PackedVessel
-> Oper
-> Oper&lt;(unpack)PackedVessel&gt;</code></pre>

## Type Signature

```Haskell
Send
 :: typename...
 -> template<template<typename...> class...>

Send
 :: typename...
 -> template<template<auto...> class...>

Send
 :: typename...
 -> template<template<template<typename...> class...> class...>

Send
 :: typename...
 -> template<template<template<auto...> class...> class...>

Send
 :: typename...
 -> template<template<template<template<typename...> class...> class...> class...>

Send
 :: typename...
 -> template<template<template<template<auto...> class...> class...> class...>

Send
 :: typename...
 -> template<template<template<template<template<typename...> class...> class...> class...> class...>

Send
 :: typename...
 -> template<template<template<template<template<auto...> class...> class...> class...> class...>

Send
 :: typename...
 -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>

Send
 :: typename...
 -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>

Send
 :: typename...
 -> template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>

Send
 :: typename...
 -> template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
```

## Structure

```C++
template<typename>
struct Send
{
    template<template<typename...> class>
    alias Road = RESULT;

    template<template<auto...> class>
    alias Rail = RESULT;
    
    template<template<template<typename...> class...> class>
    alias Flow = RESULT;
    
    template<template<template<auto...> class...> class>
    alias Sail = RESULT;
    
    template<template<template<template<typename...> class...> class...> class>
    alias Snow = RESULT;
    
    template<template<template<template<auto...> class...> class...> class>
    alias Hail = RESULT;
    
    template<template<template<template<template<typename...> class...> class...> class...> class>
    alias Cool = RESULT;
    
    template<template<template<template<template<auto...> class...> class...> class...> class>
    alias Calm = RESULT;
    
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class>
    alias Grit = RESULT;
    
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class>
    alias Will = RESULT;
    
    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class>
    alias Glow = RESULT;
    
    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class>
    alias Dawn = RESULT;
}
```

## Examples

We will send `Capsule<int, int*, int**, int***>` to `Operation`:

```C++
/**** Capsule ****/
template<typename...>
struct Capsule;

/**** Operation ****/
template<typename...>
struct Operation {};

template<>
struct Operation<int, int*, int**, int***>
{ static constexpr bool value {true}; };

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Send<Args...>::template Road<Operation>;

/**** Test ****/
static_assert(Metafunction<Capsule<int, int*, int**, int***>>::value);
```

## Implementation

`Omennivore::Send` uses partial template specialization to extract items from a packed vessel. We will showcase a simplified version that handles `Mold`.

```C++
/**** Primary template ****/
template<typename PackedVessel>
struct Send {};

/**** Partial template specialization ****/
// We extract `Elements...` from a `PackedVessel`.
template<template<typename...> class Container, typename...Elements>
struct Send<Container<Elements...>>
{
    template<template<typename...> class Operation>
    struct Detail
    // Invoke `Operation` with the `Elements...`.
    { using type = Operation<Elements...>; };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/omennivore/send/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/omennivore/send.hpp)
- [Unit test](../../../../tests/unit/metafunctions/omennivore/send.test.hpp)
