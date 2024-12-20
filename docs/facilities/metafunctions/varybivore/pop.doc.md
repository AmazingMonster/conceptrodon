<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Pop`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-pop">To Index</a></p>

## Description

`Varybivore::Pop` accepts a list of variables and pops the last one. The result is stored in `Shuttle`.

<pre><code>   Variable<sub>0</sub>, Variable<sub>1</sub>, ..., Variable<sub>n-1</sub>, Variable<sub>n</sub>
-> Variable<sub>0</sub>, Variable<sub>1</sub>, ..., Variable<sub>n-1</sub></code></pre>

## Type Signature

```Haskell
Pop :: template<auto...>
```

## Structure

```C++
template<auto...>
alias Pop = RESULT;
```

## Examples

We will pop the last variable from `0, 1, 2, 2`.

```C++
template<auto...>
struct Shuttle;

using SupposedResult = Shuttle<0, 1, 2>;

using Result = Pop<0, 1, 2, 2>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Pop` is implemented as a shortcut to `TypicalPop<*>::type`:

```C++
template<auto...Variables>
using Pop = TypicalPop<Variables...>::type;
```

## Links

- [source code](../../../../conceptrodon/descend/varybivore/pop.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/pop.test.hpp)
