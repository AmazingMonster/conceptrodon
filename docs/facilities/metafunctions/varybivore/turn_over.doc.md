<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::TurnOver`

<p style='text-align: right;'><a href="../../../index.md#list-modifications-7">To Index</a></p>

## Description

`Varybivore::TurnOver` accepts a list of variables and returns a `Shuttle` packed with the previously provided variables but in reversed order.

<pre><code>   Variable<sub>0</sub>, Variable<sub>1</sub>, ..., Variable<sub>n</sub>
-> Variable<sub>n</sub>, Variable<sub>n-1</sub>, ..., Variable<sub>0</sub></code></pre>

## Type Signature

```Haskell
TurnOver :: template<auto...>
```

## Structure

```C++
template<auto...>
alias TurnOver = RESULT;
```

## Examples

We will turn over `0, 1, 2, 2`.

```C++
template<auto...>
struct Shuttle;

using SupposedResult = Shuttle<2, 2, 1, 0>;

using Result = TurnOver<0, 1, 2, 2>;

static_assert(std::same_as<SupposedResult, Result>);
```

## Implementation

`TurnOver` is implemented as a shortcut to `TypicalTurnOver<*>::type`:

```C++
template<auto...Variables>
using TurnOver = TypicalTurnOver<Variables...>::type;
```

## Links

- [source code](../../../../conceptrodon/descend/varybivore/turn_over.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/turn_over.test.hpp)