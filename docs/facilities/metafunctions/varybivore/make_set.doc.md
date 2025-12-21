<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::MakeSet`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-make-set">To Index</a></p>

## Description

`Varybivore::MakeSet` accepts a list of variables and returns a set that:

- contains every variable in the list;
- doesn't contain repetitive variables;
- preserves the relative order of the list.

The result will be stored in a `Shuttle`.

<pre><code>   Args...
-> Shuttle&lt;(make set)&lt;Args...&gt;&gt;</code></pre>

## Type Signature

```Haskell
MakeSet
 :: template<auto...>
```

## Structure

```C++
template<auto...>
alias MakeSet = Result;
```

## Examples

We will turn `0, 1, 2, 2` into a set.

```C++
/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** SupposedResult ****/
using SupposedResult = Shuttle<0, 1, 2>;

/**** Result ****/
using Result = MakeSet<0, 1, 2, 2>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`MakeSet` is implemented as a special case of `Varybivore::TypicalDiversity`:

```C++
template<auto...Variables>
using MakeSet = TypicalDiversity<>
::ProtoPage<Variables...>
::type;
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/make_set/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/varybivore/make_set.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/make_set.test.hpp)
