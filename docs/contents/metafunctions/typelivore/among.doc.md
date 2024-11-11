<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Among`

## Description

`Typelivore::Among` accepts a list of elements and returns a function.
When invoked by an index, the function returns the element at the index from the list.
<pre><code>...Element<sub><i>i</i></sub>... -> I -> Element<sub><i>i</i></sub></code></pre>

## Type Signature

```Haskell
Among :: typename... -> template<auto...>
```

## Structure

```C++
template<typename...>
struct Among
{
    template<auto...>
    alias Page = RESULT;
};
```

## Examples

We will pick the element at index `3` out of the list `int, int*, int**, int***`.

```C++
using SupposedResult = int***;

using Result = Among<int, int*, int**, int***>::Page<3>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Among<...>::Page` is implemented as a shortcut to `TypicalAmong<...>::Page<...>::type`:

```C++
template<typename...Elements>
struct Among
{
    template<auto...Agreements>
    using Page = TypicalAmong<Elements...>
    ::template Page<Agreements...>
    ::type;
};
```

## Links

- [source code](../../../../conceptrodon/typelivore/among.hpp)
- [unit test](../../../../tests/unit/typelivore/among.test.hpp)
