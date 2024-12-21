<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::ConjureSet`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-conjure-set">To Index</a></p>

## Description

`Typelivore::ConjureSet` accepts a list of elements and returns a set that:

- contains every element in the list;
- doesn't contain repetitive elements;
- preserves the relative order of the list.

The result will be stored in a `Capsule`.

<pre><code>   Args...
-> Capsule&lt;(make set)&lt;Args...&gt;&gt;</code></pre>

## Type Signature

```Haskell
ConjureSet :: template<typename...>
```

## Structure

```C++
template<typename...>
alias ConjureSet = Result;
```

## Examples

We will turn `int, int*, int**, int**` into a set.

```C++
template<typename...>
struct Capsule;

using SupposedResult = Capsule<int, int*, int**>;

using Result = ConjureSet<int, int*, int**, int**>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`ConjureSet` is implemented as a shortcut to `TypicalConjureSet<*>::type`:

```C++
template<typename...Elements>
using ConjureSet = TypicalConjureSet<Elements...>::type;
```

## Links

- [source code](../../../../conceptrodon/descend/typelivore/conjure_set.hpp)
- [unit test](../../../../tests/unit/metafunctions/typelivore/conjure_set.test.hpp)
