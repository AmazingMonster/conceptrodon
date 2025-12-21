<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AddTo`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-add-to">To Index</a></p>

## Description

`Varybivore::AddTo` accepts a variable and returns a function.

When invoked, the function sums up the variable and the arguments.

<pre><code>   Target
-> V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> V<sub>0</sub> + V<sub>1</sub> + ... + V<sub>n</sub> + Target</code></pre>

## Type Signature

```Haskell
AddTo
 :: auto...
 -> auto...
 -> auto
```

## Structure

```C++
template<auto>
struct AddTo
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

We will add `1, 2` to `3`.

```C++
/**** Metafunction ****/
template<auto...Variables>
using Metafunction = AddTo<3>::Page<Variables...>;

/**** Test ****/
static_assert(Metafunction<1, 2>::value == 6);
```

## Implementation

We will implement `AddTo` using a fold expression.

We will place the initiator on the right side of the expression to conform to other similar functions in the library.
This means we are doing a right-fold.

<pre><code>   Variables + ... + Init
-> Variable<sub>0</sub> + (... + (Variable<sub>Last-1</sub> + (Variable<sub>Last</sub> + Init))...)
</code></pre>

In our case, left-fold and right-fold produce the same result since `+` is commutative.

Here's the entire implementation:

```C++
template<auto Init>
struct AddTo
{
    template<auto...Variables>
    struct ProtoPage
    { 
        static constexpr auto value 
        {(Variables+...+Init)}; 
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Variables>
    static constexpr auto Page_v 
    {(Variables+...+Init)}; 
};
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/add_to/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/varybivore/add_to.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/add_to.test.hpp)
