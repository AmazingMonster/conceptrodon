<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Diversity`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-diversity">To Index</a></p>

## Description

`Typelivore::Diversity` accepts a set of nonrepetitive elements and returns a function.

When invoked, the function appends the arguments to the previously provided set such that the resulting list:

- contains every element from the previously provided set and the arguments;
- doesn't contain repetitive elements;
- preserves the relative order of every element;

The resulting list will be held inside a `Capsule`.

<pre><code>   Es...
-> Args...
-> Capsule&lt;(make set)&lt;Es..., Args...&gt;&gt;</code></pre>

## Type Signature

```Haskell
Diversity
 :: typename...
 -> template<typename...>
```

## Structure

```C++
template<typename...>
struct Diversity
{
    template<typename...>
    alias Mold = RESULT;
};
```

## Examples

We will use `Diversity` to append `int, int*, int**` to `int*, void`:

```C++
/**** Capsule ****/
template<typename...>
struct Capsule;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Diversity<int*, void>
::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult = Capsule<int*, void, int, int**>;

/**** Result ****/
using Result = Metafunction<int, int*, int**>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Diversity` is implemented as a shortcut to `TypicaDiversity<*>::type`:

```C++
template<typename...Elements>
struct Diversity
{
    template<typename...Agreements>
    using Mold = TypicalDiversity<Elements...>
    ::template ProtoMold<Agreements...>
    ::type;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/diversity/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/typelivore/diversity.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/diversity.test.hpp)
