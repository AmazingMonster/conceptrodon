<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::MakeSet`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-make-set">To Index</a></p>

## Description

`Typelivore::MakeSet` accepts a list of elements and returns a set that:

- contains every element in the list;
- doesn't contain repetitive elements;
- preserves the relative order of the list.

The result will be stored in a `Capsule`.

<pre><code>   Args...
-> Capsule&lt;(make set)&lt;Args...&gt;&gt;</code></pre>

## Type Signature

```Haskell
MakeSet
 :: template<typename...>
```

## Structure

```C++
template<typename...>
alias MakeSet = Result;
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
using Result = MakeSet<int, int*, int**, int**>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`MakeSet` is implemented as a special case of `Typelivore::TypicalDiversity`:

```C++
template<typename...Elements>
using MakeSet = TypicalDiversity<>
::ProtoMold<Elements...>
::type;
```

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/make_set/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/typelivore/make_set.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/make_set.test.hpp)
