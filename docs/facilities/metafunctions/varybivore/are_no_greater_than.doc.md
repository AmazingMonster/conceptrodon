<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AreNoGreaterThan`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-are-no-greater-than">To Index</a></p>

## Description

`Varybivore::AreNoGreaterThan` accepts a variable and returns a predicate.

When invoked, the predicate returns true if all the arguments are less or equal to the variable;
otherwise, the predicate returns false.

<pre><code>   Target
-> V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (V<sub>0</sub> &le; Target) && (V<sub>1</sub> &le; Target) && ... && (V<sub>n</sub> &le; Target)</code></pre>

## Type Signature

```Haskell
AreNoGreaterThan
 :: auto...
 -> auto...
 -> auto
```

## Structure

```C++
template<auto>
struct AreNoGreaterThan
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
= AreNoGreaterThan<5>
::Page<Args...>;

/**** Test ****/
static_assert(Metafunction<2, 3, 4, 5>::value);
static_assert(! Metafunction<6, 2, 3>::value);
```

## Implementation

We will implement `AreNoGreaterThan` using only `<`, meaning <code>Variable &le; Target</code> is expressed as:

```C++
not (Target < Variable)
```

```C++
template<auto Target>
struct AreNoGreaterThan
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr bool value
        { (...&&(not (Target < Variables))) };
    };
    
    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Variables>
    static constexpr bool Page_v 
    { (...&&(not (Target < Variables))) };
};
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/are_no_greater_than/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/varybivore/are_no_greater_than.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/are_no_greater_than.test.hpp)
