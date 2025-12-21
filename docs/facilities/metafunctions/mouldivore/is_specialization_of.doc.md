<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::IsSpecializationOf`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-is-specialization-of">To Index</a></p>

## Description

`Mouldivore::IsSpecializationOf` accepts a container and returns a function.

When invoked by a type, the function returns true if the type is created by an instantiation of the container and returns false if otherwise.

<pre><code>   Container
-> Entity
-> Entity == Container&lt;Es...&gt; ?
   true : false</code></pre>

## Type Signature

```Haskell
IsSpecializationOf
 :: template<typename...> class...
 -> typename...
 -> auto 
```

## Structure

```C++
template<template<typename...> class>
struct IsSpecializationOf
{
    template<typename>
    alias Mold
    {
        static constexpr bool value
        {RESULT};
    };

    template<typename>
    static constexpr bool Mold_v
    {RESULT};
};
```

## Examples

We will check if `PackedVessel` is a specialization of `Con_0` or `Con_1`.

```C++
/**** Dummy Containers ****/
template<typename...>
struct Capsule_0;

template<typename...>
struct Capsule_1;

template<typename...Args>
using Con_0 = Capsule_0<Args...>;

template<typename...Args>
using Con_1 = Capsule_1<Args...>;

/**** PackedVessel ****/
using PackedVessel = Capsule_0<int, int*, int**, int***>;

/**** Tests ****/
static_assert(IsSpecializationOf<Con_0>::Mold<PackedVessel>::value);
static_assert(IsSpecializationOf<Capsule_0>::Mold<PackedVessel>::value);
static_assert(! IsSpecializationOf<Con_1>::Mold<PackedVessel>::value);
static_assert(! IsSpecializationOf<Capsule_1>::Mold<PackedVessel>::value);
```

## Implementation

We will use partial template specialization to dissect a type.

Suppose the compiler discovers that the type is a packed vessel and deduces the vessel as the given container. In that case, the compiler will select the partial specialization instead of the primary template.

```C++
template<template<typename...> class Container>
struct IsSpecializationOf
{
    template<typename Type>
    struct ProtoMold
    { static constexpr bool value = false; };

    // This partial specialization will be chosen
    // if `Type` is deduced as `Container<Elements...>`.
    template<typename...Elements>
    struct ProtoMold<Container<Elements...>>
    { static constexpr bool value = true; };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/is_specialization_of/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/mouldivore/is_specialization_of.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/is_specialization_of.test.hpp)
