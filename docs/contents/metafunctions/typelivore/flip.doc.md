<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Flip`

## Description

`Typelivore::Flip` accepts a list of elements and returns a `Capsule` packed with the previously provided elements but in reversed order.
<pre><code>   Element<sub>0</sub>, Element<sub>1</sub>, ..., Element<sub>n</sub>
-> Element<sub>n</sub>, Element<sub>n-1</sub>, ..., Element<sub>0</sub></code></pre>

## Type Signature

```Haskell
Flip :: template<typename...>
```

## Structure

```C++
template<typename...>
alias Flip = RESULT;
```

## Examples

We will flip `int, int*, int**, int**`.

```C++
template<typename...>
struct Capsule;

using SupposedResult = Capsule<int**, int**, int*, int>;

using Result = Flip<int, int*, int**, int**>;

static_assert(std::same_as<SupposedResult, Result>);
```

## Implementation

`Flip` is implemented as a shortcut to `TypicalFlip<...>::type`:

```C++
template<typename...Elements>
using Flip = TypicalFlip<Elements...>::type;
```

## Links

- [source code](../../../../conceptrodon/descend/typelivore/flip.hpp)
- [unit test](../../../../tests/unit/typelivore/flip.test.hpp)
