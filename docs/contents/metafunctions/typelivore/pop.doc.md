<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Pop`

## Description

`Typelivore::Pop` accepts a list of elements and pops the last one. The result is stored in `Capsule` and returned via alias member `type`.
<pre><code>   Element<sub>0</sub>, Element<sub>1</sub>, ..., Element<sub>n-1</sub>, Element<sub>n</sub>
-> Element<sub>0</sub>, Element<sub>1</sub>, ..., Element<sub>n-1</sub></code></pre>

## Type Signature

```Haskell
Pop :: template<typename...>
```

## Structure

```C++
template<typename...>
alias Pop = RESULT;
```

## Examples

We will pop the last element from `int, int*, int**, int**`.

```C++
template<typename...>
struct Capsule;

using SupposedResult = Capsule<int, int*, int**>;

using Result = Pop<int, int*, int**, int**>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Pop` is implemented as a shortcut to `TypicalPop<...>::type`:

```C++
template<typename...Elements>
using Pop = TypicalPop<Elements...>::type;
```

## Links

- [source code](../../../../conceptrodon/descend/typelivore/pop.hpp)
- [unit test](../../../../tests/unit/typelivore/pop.test.hpp)
