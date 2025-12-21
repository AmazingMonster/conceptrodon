<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Among`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-among">To Index</a></p>

## Description

`Typelivore::Among` accepts a list of elements and returns a function.

When invoked by an index, the function returns the element at the index from the list.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>I</sub>, ..., E<sub>n</sub>
-> I
-> E<sub>I</sub></code></pre>

## Type Signature

```Haskell
Among
 :: typename...
 -> template<auto...>
```

## Structure

```C++
template<typename...>
struct Among
{
    template<auto>
    alias Page = RESULT;
};
```

## Examples

We will pick the element at index `3` out of the list `int, int*, int**, int***`.

```C++
/**** SupposedResult ****/
using SupposedResult = int***;

/**** Result ****/
using Result = Among<int, int*, int**, int***>::Page<3>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Among<*>::Page` is implemented as a shortcut to `TypicalAmong<*>::Page<*>::type`:

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

- [Example](../../../code/facilities/metafunctions/typelivore/among/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/typelivore/among.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/among.test.hpp)
