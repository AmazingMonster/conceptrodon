<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::SubtractFrom`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-subtract-from">To Index</a></p>

## Description

`Varybivore::SubtractFrom` accepts a variable and returns a function.

When invoked, the function subtracts all arguments from the variable.

<pre><code>   Target
-> V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> Target - V<sub>0</sub> - V<sub>1</sub> - ... - V<sub>n</sub></code></pre>

## Type Signature

```Haskell
SubtractFrom
 :: auto...
 -> auto...
 -> auto
```

## Structure

```C++
template<auto>
struct SubtractFrom
{
    template<auto...>
    alias Page
    {
        static constexpr auto value
        {RESULT};
    };

    template<auto...>
    static constexpr auto Page_v
    {RESULT};
};
```

## Examples

We will subtract `1, 2, -2, 2` from `3`.

```C++
/**** Metafunction ****/
template<auto...Variables>
using Metafunction = SubtractFrom<3>::Page<Variables...>;

/**** Test ****/
static_assert(Metafunction<1, 2, -2, 2>::value == 0);
```

## Implementation

We will implement `SubtractFrom` using a fold expression.

We will place the initiator on the left side of the expression.
This means we are doing a left-fold.

<pre><code>   Init - ... - Variables
-> (...((Init - Variable<sub>0</sub>) - Variable<sub>1</sub>) - ...) - Variable<sub>Last</sub></code></pre>

Here's the entire implementation:

```C++
template<auto Target>
struct SubtractFrom
{
    template<auto...Variables>
    struct ProtoPage
    { 
        static constexpr auto value 
        {(Target -...- Variables)}; 
    };
    
    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Variables>
    static constexpr auto Page_v
    {(Target -...- Variables)};
};
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/subtract_from/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/subtract_from.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/subtract_from.test.hpp)
