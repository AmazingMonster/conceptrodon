<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::TypicalTurnOver`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-typical-turn-over">To Index</a></p>

## Description

`Typelivore::TypicalTurnOver` accepts a list of elements and returns a `Capsule` packed with the previously provided elements but in reversed order.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>n</sub>
-> Capsule&lt;E<sub>n</sub>, E<sub>n-1</sub>, ..., E<sub>0</sub>&gt;</code></pre>

## Type Signature

```Haskell
TypicalTurnOver
 :: typename...
 -> typename
```

## Structure

```C++
template<typename...>
struct TypicalTurnOver
{
    using type = RESULT;
};
```

## Examples

We will turn over `int, int*, int**, int**`.

```C++
/**** Capsule ****/
template<typename...>
struct Capsule;

/**** SupposedResult ****/
using SupposedResult = Capsule<int**, int**, int*, int>;

/**** Result ****/
using Result = TypicalTurnOver<int, int*, int**, int**>
::type;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
```

## Implementation

We will implement `TypicalTurnOver` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  1. Turn over several elements in the front of the list;
  2. Invoke `TypicalTurnOver` by the rest to turn them over;
  3. Switch the positions of these two flipped parts and concatenate them together.

We will use `ExtendBack` to concatenate two flipped parts.

```C++
template<typename>
struct ExtendBack {};

template<template<typename...> class Container, typename...Elements>
struct ExtendBack<Container<Elements...>>
{
    template<typename...Endings>
    using Mold = Container<Elements..., Endings...>;
};
```

The result will be held inside a `Capsule`:

```C++
template<typename...>
struct Capsule;
```

Here's a simplified version of the implementation:

```C++
template<typename...>
struct TypicalTurnOver {};

template<typename First>
struct TypicalTurnOver<First>
{
    using type = Capsule<First>;
};

template<typename First, typename Second>
struct TypicalTurnOver<First, Second>
{
    using type = Capsule<Second, First>;
};

template<typename First, typename Second, typename...Others>
struct TypicalTurnOver<First, Second, Others...>
{
    using type 
    = ExtendBack<typename TypicalTurnOver<Others...>::type>
    ::template Mold<Second, First>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/typical_turn_over/implementation.hpp)
- [Source code](../../../../conceptrodon/typelivore/typical_turn_over.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/typical_turn_over.test.hpp)
