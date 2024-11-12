<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Diversity`

## Description

`Typelivore::Diversity` accepts a set of nonrepetitive elements and returns a function.
When invoked, the function appends the arguments to the previously provided elements such that the resulting list:

- contains every element from the previously provided elements and the arguments;
- doesn't contain repetitive elements;
- preserves the relative order of every element;

The resulting list will be held inside `Capsule`.

<pre><code>   Elements...
-> Arguments...
-> MakeMathematicalSet(Elements..., Arguments...)</code></pre>

## Type Signature

```Haskell
Diversity ::   typename...
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
template<typename...>
struct Capsule;

template<typename...Args>
using Metafunction = Diversity<int*, void>
::Mold<Args...>;

using SupposedResult = Capsule<int*, void, int, int**>;

using Result = Metafunction<int, int*, int**>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Diversity` is implemented as a shortcut to `TypicaDiversity<...>::type`:

```C++
template<typename...Elements>
using Diversity = TypicalDiversity<Elements...>::type;
```

## Links

- [source code](../../../../conceptrodon/descend/typelivore/diversity.hpp)
- [unit test](../../../../tests/unit/typelivore/diversity.test.hpp)
