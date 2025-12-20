<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::TypicalPop`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-typical-pop">To Index</a></p>

## Description

`Varybivore::Pop` accepts a list of variables and pops the last one. The result is stored in `Shuttle`.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n-1</sub>, V<sub>n</sub>
-> Shuttle&lt;V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n-1</sub>&gt;</code></pre>

## Type Signature

```Haskell
TypicalPop
 :: auto...
 -> typename
```

## Structure

```C++
template<auto...>
struct TypicalPop
{
    using type = RESULT;
};
```

## Examples

We will pop the last variable from `0, 1, 2, 2`.

```C++
/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** SupposedResult ****/
using SupposedResult = Shuttle<0, 1, 2>;

/**** Result ****/
using Result = TypicalPop<0, 1, 2, 2>::type;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will implement `TypicalPop` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**

  1. Preserve several variables from the beginning of the list.
  2. Invoke `TypicalPop` with the rest.
  3. Extend the front of the resulting list by the preserved variables.

We will use the following function to concatenate the preserved and the recursed parts.

```C++
template<typename>
struct ExtendFront {};

template<template<auto...> class Sequence, auto...Variables>
struct ExtendFront<Sequence<Variables...>>
{
    template<auto...Beginnings>
    using Page = Sequence<Beginnings..., Variables...>;
};
```

The result will be held inside a `Shuttle`:

```C++
template<auto...>
struct Shuttle;
```

Here is a simplified version of the implementation:

```C++
template<auto...>
struct TypicalPop {};

template<auto First>
struct TypicalPop<First>
{
    using type = Shuttle<>;
};

template<auto First, auto Second>
struct TypicalPop<First, Second>
{
    using type = Shuttle<First>;
};

template<auto First, auto Second, auto...Others>
struct TypicalPop<First, Second, Others...>
{
    using type
    = ExtendFront<typename TypicalPop<Others...>::type>
    ::template Page<First, Second>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/typical_pop/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/typical_pop.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/typical_pop.test.hpp)
