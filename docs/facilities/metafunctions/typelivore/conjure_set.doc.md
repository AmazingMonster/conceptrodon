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
ConjureSet
 :: template<typename...>
```

## Structure

```C++
template<typename...>
alias ConjureSet = Result;
```

## Examples

We will turn `int, int*, int**, int**` into a set.

```C++
/**** Capsule ****/
template<typename...>
struct Capsule;

/**** SupposedResult ****/
using SupposedResult = Capsule<int, int*, int**>;

/**** Result ****/
using Result = ConjureSet<int, int*, int**, int**>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`ConjureSet` is implemented as a shortcut to `TypicalConjureSet<*>::type`:

```C++
template<typename...Elements>
using ConjureSet = TypicalConjureSet<Elements...>::type;
```

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/conjure_set/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/typelivore/conjure_set.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/conjure_set.test.hpp)
