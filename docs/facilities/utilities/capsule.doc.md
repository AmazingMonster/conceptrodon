<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Capsule`

<p style='text-align: right;'><a href="../utilities.md#capsule">To Index</a></p>

## Description

`Capsule` accepts a list of elements and returns a function.

When invoked by an operation, the function instantiates the operation with the elements.

<pre><code>   Es...
-> Oper
-> Oper&lt;Es...&gt;</code></pre>

It also contains a regular function, `size`, which returns the total number of the elements.

<pre><code>size() -> sizeof...(Elements)</code></pre>

## Type Signature

```Haskell
Capsule
 :: typename...
 -> template<template<typename...> class...>
```

## Structure

```C++
template<typename...>
struct Capsule
{
    static constexpr auto size() -> size_t;

    template<template<typename...> class>
    alias Road = RESULT;
};
```

## Examples

- We will create a `Capsule` with elements `int, int*, int**, int**`.
Then, we will transport the elements to `Operation`.

```C++
/**** Operation ****/
template<typename...>
struct NewPacker;

/**** PackedVessel ****/
using PackedCapsule = Capsule<int, int*, int**, int**>;

/**** SupposedResult ****/
using SupposedResult = NewPacker<int, int*, int**, int**>;

/**** Result ****/
using Result = PackedCapsule::Road<NewPacker>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

- We can check the size of a packed `Capsule`.

```C++
static_assert(PackedCapsule::size() == 4);
```

## Implementation

```C++
template<typename...Elements>
struct Capsule
{
    static constexpr size_t size()
    { return sizeof...(Elements); }

    template<template<typename...> class Container>
    struct Detail { using type = Container<Elements...>; };

    template<template<typename...> class...Containers>
    using Road = Detail<Containers...>::type;
};
```

## Links

- [Example](../../code/facilities/utilities/capsule/implementation.hpp)
- [Source code](../../../conceptrodon/utilities/capsule.hpp)
- [Unit test](../../../tests/unit/utilities/capsule.test.hpp)
