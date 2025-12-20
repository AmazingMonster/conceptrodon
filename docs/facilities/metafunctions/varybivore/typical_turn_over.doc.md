<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::TypicalTurnOver`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-typical-turn-over">To Index</a></p>

## Description

`Varybivore::TypicalTurnOver` accepts a list of variables and returns a `Shuttle` packed with the previously provided variables but in reversed order.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> Shuttle&lt;V<sub>n</sub>, V<sub>n-1</sub>, ..., V<sub>0</sub>&gt;</code></pre>

## Type Signature

```Haskell
TypicalTurnOver
 :: auto...
 -> typename
```

## Structure

```C++
template<auto...>
struct TypicalTurnOver
{
    using type = RESULT;
};
```

## Examples

We will turn over `0, 1, 2, 2`.

```C++
/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** SupposedResult ****/
using SupposedResult = Shuttle<2, 2, 1, 0>;

/**** Result ****/
using Result = TypicalTurnOver<0, 1, 2, 2>::type;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
```

## Implementation

We will implement `TypicalTurnOver` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  1. Turn over several variables in the front of the list;
  2. Invoke `TypicalTurnOver` by the rest to turn them over;
  3. Switch the positions of these two flipped parts and concatenate them together.

We will use `ExtendBack` to concatenate two flipped parts.

```C++
template<typename...>
struct ExtendBack {};

template<
    template<auto...> class Sequence,
    auto...Variables
>
struct ExtendBack<Sequence<Variables...>>
{
    template<auto...Agreements>
    using Page = Sequence<Variables..., Agreements...>;
};
```

The result will be held inside a `Shuttle`:

```C++
template<auto...>
struct Shuttle;
```

Here's a simplified version of the implementation:

```C++
template<auto...>
struct TypicalTurnOver {};

template<auto First>
struct TypicalTurnOver<First>
{
    using type = Shuttle<First>;
};

template<auto First, auto Second>
struct TypicalTurnOver<First, Second>
{
    using type = Shuttle<Second, First>;
};

template<auto First, auto Second, auto...Others>
struct TypicalTurnOver<First, Second, Others...>
{
    using type
    = ExtendBack<typename TypicalTurnOver<Others...>::type>
    ::template Page<Second, First>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/typical_turn_over/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/typical_turn_over.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/typical_turn_over.test.hpp)
