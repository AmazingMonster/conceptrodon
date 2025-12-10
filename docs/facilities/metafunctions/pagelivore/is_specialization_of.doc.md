<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::IsSpecializationOf`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-is-specialization-of">To Index</a></p>

## Description

`Pagelivore::IsSpecializationOf` accepts a sequence and returns a function.

When invoked by a type, the function returns true if the type is created by an instantiation of the sequence and returns false if otherwise.

<pre><code>   Sequence
-> Entity
-> Entity == Sequence&lt;Vs...&gt; ?
   true : false</code></pre>

## Type Signature

```Haskell
IsSpecializationOf
 :: template<auto...> class...
 -> typename...
 -> auto 
```

## Structure

```C++
template<template<auto...> class>
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

We will check if `PackedVessel` is a specialization of `Seq_0` or `Seq_1`.

```C++
/**** Shuttles ****/
template<auto...>
struct Shuttle_0;

template<auto...>
struct Shuttle_1;

/**** PackedVessel ****/
using PackedVessel = Shuttle_0<0, 1, 2, 2>;

/*** Aliases ****/
template<auto...Args>
using Seq_0 = Shuttle_0<Args...>;

template<auto...Args>
using Seq_1 = Shuttle_1<Args...>;

/**** Tests ****/
static_assert(IsSpecializationOf<Seq_0>::Mold<PackedVessel>::value);
static_assert(! IsSpecializationOf<Seq_1>::Mold<PackedVessel>::value);
```

## Implementation

We will use partial template specialization to dissect a type.

Suppose the compiler discovers that the type is a packed vessel and deduces the vessel as the given sequence. In that case, the compiler will select the partial specialization instead of the primary template.

```C++
template<template<auto...> class Sequence>
struct IsSpecializationOf
{
    template<typename Type>
    struct ProtoMold
    { static constexpr bool value = false; };

    // This partial specialization will be chosen
    // if `Type` is deduced as `Sequence<Variables...>`.
    template<auto...Variables>
    struct ProtoMold<Sequence<Variables...>>
    { static constexpr bool value = true; };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;

    template<typename...Args>
    static constexpr bool Mold_v = ProtoMold<Args...>::value;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/is_specialization_of/implementation.hpp)
- [Source code](../../../../conceptrodon/pagelivore/is_specialization_of.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/is_specialization_of.test.hpp)
