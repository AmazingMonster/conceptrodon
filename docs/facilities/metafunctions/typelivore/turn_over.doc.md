<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::TurnOver`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-turn-over">To Index</a></p>

## Description

`Typelivore::TurnOver` accepts a list of elements and returns a `Capsule` packed with the previously provided elements but in reversed order.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>n</sub>
-> Capsule&lt;E<sub>n</sub>, E<sub>n-1</sub>, ..., E<sub>0</sub>&gt;</code></pre>

## Type Signature

```Haskell
TurnOver
 :: template<typename...>
```

## Structure

```C++
template<typename...>
alias TurnOver = RESULT;
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
using Result = TurnOver<int, int*, int**, int**>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
```

## Implementation

`TurnOver` is implemented as a shortcut to `TypicalTurnOver<*>::type`:

```C++
template<typename...Elements>
using TurnOver = TypicalTurnOver<Elements...>::type;
```

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/turn_over/implementation.hpp)
- [Source code](../../../../conceptrodon/typelivore/turn_over.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/turn_over.test.hpp)
