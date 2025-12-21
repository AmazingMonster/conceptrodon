<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::All`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-all">To Index</a></p>

## Description

`Varybivore::All` accepts a list of variables. It returns true if all variables can be evaluated to `true` and returns false if otherwise.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (bool)V<sub>0</sub> && (bool)V<sub>1</sub> && ... && (bool)V<sub>n</sub></code></pre>

## Type Signature

```Haskell
All
 :: auto...
 -> auto
```

## Structure

```C++
template<auto...>
struct All
{
    static constexpr bool value
    {RESULT};
};

template<auto...>
static constexpr auto All_v
{RESULT};
```

## Examples

```C++
static_assert(All<1, 2, 3>::value);
static_assert(! All<0, 2, 3>::value);
static_assert(! All<nullptr, 2, 3>::value);
```

## Implementation

We will implement `All` using a fold expression.

Note that we are not providing an initiator. The default initiator for `&&` is `true`. We place `...` on the left side of the expression to do a left-fold.

<pre><code>   ... && Variables
-> true && ... && Variables
-> (...((true && Variable<sub>0</sub>) && Variable<sub>1</sub>) && ...) && Variable<sub>Last</sub>
</code></pre>

In our case, left-fold and right-fold produce the same result since `&&` is commutative.

Here's the entire implementation:

```C++
template<auto...Variables>
struct All
{
    static constexpr bool value
    { (...&&(static_cast<bool>(Variables))) };
};

template<auto...Variables>
constexpr bool All_v
{ (...&&(static_cast<bool>(Variables))) };
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/all/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/varybivore/all.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/all.test.hpp)
