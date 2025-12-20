<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AreGreaterThan`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-are-greater-than">To Index</a></p>

## Description

`Varybivore::AreGreaterThan` accepts a variable and returns a predicate.

When invoked, the predicate returns true if all the arguments are greater than the variable;
otherwise, the predicate returns false.

<pre><code>   Target
-> V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (V<sub>0</sub> &gt; Target) && (V<sub>1</sub> &gt; Target) && ... && (V<sub>n</sub> &gt; Target)</code></pre>

## Type Signature

```Haskell
AreGreaterThan
 :: auto...
 -> auto...
 -> auto
```

## Structure

```C++
template<auto>
struct AreGreaterThan
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
= AreGreaterThan<1>
::Page<Args...>;

/**** Test ****/
static_assert(Metafunction<2, 3, 4>::value);
static_assert(! Metafunction<1, 2, 3>::value);
```

## Implementation

We will implement `AreGreaterThan` using only `<`, meaning <code>Variable > Target</code> is expressed as:

```C++
Target < Variable
```

Here's the entire implementation:

```C++
template<auto Target>
struct AreGreaterThan
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr bool value
        { (...&&(Target < Variables)) };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Variables>
    static constexpr bool Page_v
    { (...&&(Target < Variables)) };
};
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/are_greater_than/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/are_greater_than.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/are_greater_than.test.hpp)
