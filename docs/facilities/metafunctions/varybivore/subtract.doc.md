<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Subtract`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-subtract">To Index</a></p>

## Description

`Varybivore::Subtract` accepts a target and a list of variables.
It subtracts all the variables from the target.

<pre><code>   Target, V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> Target - V<sub>0</sub> - V<sub>1</sub> - ... - V<sub>n</sub></code></pre>

## Type Signature

```Haskell
Subtract
 :: auto...
 -> auto
```

## Structure

```C++
template<auto...>
struct Subtract
{
    static constexpr auto value
    {RESULT};
};

template<auto...>
static constexpr auto Subtract_v
{RESULT};
```

## Examples

We will subtract `1, 2, -2, 2` from `3`.

```C++
static_assert(Subtract<3, 1, 2, -2, 2>::value == 0);
```

## Implementation

We will implement `Subtract` using a fold expression.

Note that the initiator is on the left side of the expression. This means we are doing a left-fold.

<pre><code>   Init - ... - Variables
-> (...((Init - Variable<sub>0</sub>) - Variable<sub>1</sub>) - ...) - Variable<sub>Last</sub>
</code></pre>-

Here's the entire implementation:

```C++
template<auto Target, auto...Variables>
struct Subtract
{ 
    static constexpr auto value 
    {(Target -...- Variables)}; 
};
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/subtract/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/varybivore/subtract.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/subtract.test.hpp)
