<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::TypicalPop`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-typical-pop">To Index</a></p>

## Description

`Typelivore::Pop` accepts a list of elements and pops the last one. The result is stored in `Capsule`.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>n-1</sub>, E<sub>n</sub>
-> Capsule&lt;E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>n-1</sub>&gt;</code></pre>

## Type Signature

```Haskell
TypicalPop
 :: typename...
 -> typename
```

## Structure

```C++
template<typename...>
struct TypicalPop
{
    using type = RESULT;
};
```

## Examples

We will pop the last element from `int, int*, int**, int**`.

```C++
/**** Capsule ****/
template<typename...>
struct Capsule;

/**** SupposedResult ****/
using SupposedResult = Capsule<int, int*, int**>;

/**** Result ****/
using Result = TypicalPop<int, int*, int**, int**>::type;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will implement `TypicalPop` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**

  1. Preserve several elements from the beginning of the list.
  2. Invoke `TypicalPop` with the rest.
  3. Extend the front of the resulting list by the preserved elements.

We will use the following function to concatenate the preserved and the recursed parts.

```C++
template<typename>
struct ExtendFront {};

template<template<typename...> class Container, typename...Elements>
struct ExtendFront<Container<Elements...>>
{
    template<typename...Beginnings>
    using Mold = Container<Beginnings..., Elements...>;
};
```

The result will be held inside a `Capsule`:

```C++
template<typename...>
struct Capsule;
```

Here is a simplified version of the implementation:

```C++
template<typename...>
struct TypicalPop {};

template<typename First>
struct TypicalPop<First>
{
    using type = Capsule<>;
};

template<typename First, typename Second>
struct TypicalPop<First, Second>
{
    using type = Capsule<First>;
};

template<typename First, typename Second, typename...Others>
struct TypicalPop<First, Second, Others...>
{
    using type
    = ExtendFront<typename TypicalPop<Others...>::type>
    ::template Mold<First, Second>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/typical_pop/implementation.hpp)
- [Source code](../../../../conceptrodon/typelivore/pop.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/typical_pop.test.hpp)
