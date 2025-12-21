<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AreNoLessThan`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-are-no-less-than">To Index</a></p>

## Description

`Varybivore::AreNoLessThan` accepts a variable and returns a predicate.

When invoked, the predicate returns true if all the arguments are greater or equal to the variable;
otherwise, the predicate returns false.

<pre><code>   Target
-> V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (V<sub>0</sub> &ge; Target) && (V<sub>1</sub> &ge; Target) && ... && (V<sub>n</sub> &ge; Target)</code></pre>

## Type Signature

```Haskell
AreNoLessThan
 :: auto...
 -> auto...
 -> auto
```

## Structure

```C++
template<auto>
struct AreNoLessThan
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
= AreNoLessThan<5>
::Page<Args...>;

/**** Test ****/
static_assert(Metafunction<5, 6, 7, 5>::value);
static_assert(! Metafunction<6, 2, 3>::value);
```

## Implementation

We will implement `AreNoLessThan` using only `<`, meaning <code>Variable &ge; Target</code> is expressed as:

```C++
not (Variable < Target)
```

```C++
template<auto Target>
struct AreNoLessThan
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr bool value
        { (...&&(not (Variables < Target))) };
    };
    
    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Variables>
    static constexpr bool Page_v 
    { (...&&(not (Variables < Target))) };
};
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/are_no_less_than/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/varybivore/are_no_less_than.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/are_no_less_than.test.hpp)
