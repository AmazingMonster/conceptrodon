<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AreEqualTo`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-are-equal-to">To Index</a></p>

## Description

`Varybivore::AreEqualTo` accepts a variable and returns a predicate.

When invoked, the predicate returns true if all the arguments are equal to the variable;
otherwise, the predicate returns false.

<pre><code>   Target
-> V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (V<sub>0</sub> == Target) && (V<sub>1</sub> == Target) && ... && (V<sub>n</sub> == Target)</code></pre>

## Type Signature

```Haskell
AreBoundedByOpenInterval
 :: auto...
 -> auto...
 -> auto
```

## Structure

```C++
template<auto>
struct AreEqualTo
{
    template<auto...>
    alias Page
    {
        static constexpr bool value
        {RESULT};
    };
    
    template<auto...>
    static constexpr bool Page_v
    {RESULT};
};
```

## Examples

```C++
/**** Metafunction ****/
template<auto...Args>
using Metafunction
= AreEqualTo<1>
::Page<Args...>;

/**** Test ****/
static_assert(Metafunction<1, 1.0>::value);
static_assert(! Metafunction<1, 2, 3>::value);
```

## Implementation

We will implement `AreEqualTo` using only `<`, meaning <code>Variable == Target</code> is expressed as:

```C++
(not (Target < Variable)) && (not (Variable < Target))
```

Here's the entire implementation:

```C++
template<auto Target>
struct AreEqualTo
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr bool value
        { (...&&(not (Variables < Target) && not (Target < Variables))) };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
    
    template<auto...Variables>
    static constexpr bool Page_v 
    { (...&&(not (Variables < Target) && not (Target < Variables))) };
};
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/are_equal_to/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/are_equal_to.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/are_equal_to.test.hpp)
