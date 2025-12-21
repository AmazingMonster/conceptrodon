<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AreLessThan`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-are-less-than">To Index</a></p>

## Description

`Varybivore::AreLessThan` accepts a variable and returns a predicate.

When invoked, the predicate returns true if all the arguments are less than the variable;
otherwise, the predicate returns false.

<pre><code>   Target
-> V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (V<sub>0</sub> &lt; Target) && (V<sub>1</sub> &lt; Target) && ... && (V<sub>n</sub> &lt; Target)</code></pre>

## Type Signature

```Haskell
AreLessThan
 :: auto...
 -> auto...
 -> auto
```

## Structure

```C++
template<auto>
struct AreLessThan
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
= AreLessThan<5>
::Page<Args...>;

/**** Test ****/
static_assert(Metafunction<2, 3, 4>::value);
static_assert(! Metafunction<6, 2, 3>::value);
```

## Implementation

Here's the entire implementation:

```C++
template<auto Target>
struct AreLessThan
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr bool value
        { (...&&(Variables < Target)) };
    };
    
    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Variables>
    static constexpr bool Page_v
    { (...&&(Variables < Target)) };
};
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/are_less_than/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/varybivore/are_less_than.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/are_less_than.test.hpp)
