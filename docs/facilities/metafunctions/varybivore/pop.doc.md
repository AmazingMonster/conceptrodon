<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Pop`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-pop">To Index</a></p>

## Description

`Varybivore::Pop` accepts a list of variables and pops the last one. The result is stored in `Shuttle`.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n-1</sub>, V<sub>n</sub>
-> Capsule&lt;V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n-1</sub>&gt;</code></pre>

## Type Signature

```Haskell
Pop
 :: template<auto...>
```

## Structure

```C++
template<auto...>
alias Pop = RESULT;
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

`Pop` is implemented as a shortcut to `TypicalPop<*>::type`:

```C++
template<auto...Variables>
using Pop = TypicalPop<Variables...>::type;
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/pop/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/pop.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/pop.test.hpp)
