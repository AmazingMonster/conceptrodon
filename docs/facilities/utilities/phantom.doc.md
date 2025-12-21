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

## Links

- [Example](../../code/facilities/utilities/phantom/implementation.hpp)
- [Source code](../../../conceptrodon/utilities/phantom.hpp)
- [Unit test](../../../tests/unit/utilities/phantom.test.hpp)
