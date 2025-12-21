<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Any`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-any">To Index</a></p>

## Description

`Varybivore::Any` accepts a list of variables.
It returns true if any of the variables can be evaluated to `true` and returns false if otherwise.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (bool)V<sub>0</sub> || (bool)V<sub>1</sub> || ... || (bool)V<sub>n</sub></code></pre>

## Type Signature

```Haskell
Any
 :: auto...
 -> auto
```

## Structure

```C++
template<auto...>
struct Any
{
    static constexpr bool value
    {RESULT};
};

template<auto...>
static constexpr auto Any_v
{RESULT};
```

## Examples

```C++
static_assert(Any<1, 2, 3>::value);
static_assert(Any<0, 2, 3>::value);
static_assert(Any<nullptr, 2, 3>::value);
static_assert(! Any<nullptr, 0, 0>::value);
```

## Implementation

We will implement `Any` using a fold expression.

Note that we are not providing an initiator. The default initiator for `||` is `false`. We place `...` on the left side of the expression to do a left-fold.

<pre><code>   ... || Variables
-> false || ... || Variables
-> (...((false || Variable<sub>0</sub>) || Variable<sub>1</sub>) || ...) || Variable<sub>Last</sub>
</code></pre>

In our case, left-fold and right-fold produce the same result since `||` is commutative.

Here's the entire implementation:

```C++
template<auto...Variables>
struct Any
{
    static constexpr bool value
    { (...||(static_cast<bool>(Variables))) };
};

template<auto...Variables>
constexpr bool Any_v
{ (...||(static_cast<bool>(Variables))) };
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/any/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/varybivore/any.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/any.test.hpp)
