<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Add`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-add">To Index</a></p>

## Description

`Varybivore::Add` accepts a list of variables and sums them up.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> V<sub>0</sub> + V<sub>1</sub> + ... + V<sub>n</sub></code></pre>

## Type Signature

```Haskell
Add
 :: auto...
 -> auto
```

## Structure

```C++
template<auto...>
struct Add
{
    static constexpr auto value
    {RESULT};
};

template<auto...>
static constexpr auto Add_v
{RESULT};
```

## Examples

We will sum up `1, 2, 3`.

```C++
static_assert(Add<1, 2, 3>::value == 6);
```

## Implementation

We will implement `Add` using a fold expression.

Note that the initiator is on the left side of the expression. This means we are doing a left-fold.

<pre><code>   Init + ... + Variables
-> (...((Init + Variable<sub>0</sub>) + Variable<sub>1</sub>) + ...) + Variable<sub>Last</sub>
</code></pre>

In our case, left-fold and right-fold produce the same result since `+` is commutative.

Here's the entire implementation:

```C++
template<auto Init, auto...Variables>
struct Add
{ 
    static constexpr auto value 
    { (Init+...+Variables) }; 
};

template<auto Init, auto...Variables>
constexpr auto Add_v 
{ (Init+...+Variables) }; 
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/add/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/varybivore/add.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/add.test.hpp)
