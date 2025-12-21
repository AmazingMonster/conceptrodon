<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AreUnequalTo`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-are-unequal-to">To Index</a></p>

## Description

`Varybivore::AreUnequalTo` accepts a variable and returns a predicate.

When invoked, the predicate returns true if all the arguments are unequal to the variable;
otherwise, the predicate returns false.

<pre><code>   Target
-> V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (V<sub>0</sub> != Target) && (V<sub>1</sub> != Target) && ... && (V<sub>n</sub> != Target)</code></pre>

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
struct AreUnequalTo
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
= AreUnequalTo<1>
::Page<Args...>;

/**** Test ****/
static_assert(! Metafunction<1, 1.0>::value);
static_assert(Metafunction<0, 2, 3>::value);
```

## Implementation

We will implement `AreUnequalTo` using only `<`, meaning <code>Variable != Target</code> is expressed as:

```C++
(Target < Variable) || (Variable < Target)
```

Here's the entire implementation:

```C++
template<auto Target>
struct AreUnequalTo
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr auto value
        { (...&&(Variables < Target || Target < Variables)) };
    };
    
    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Variables>
    static constexpr bool Page_v 
    { (...&&(Variables < Target || Target < Variables)) };
};
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/are_unequal_to/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/varybivore/are_unequal_to.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/are_unequal_to.test.hpp)
