<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::AllNotVariadic`

<p style='text-align: right;'><a href="../../concepts.md#functivore-all-not-variadic">To Index</a></p>

## Description

`Functivore::AllNotVariadic` accepts a list of function-like types.
It returns true if none of their parameter lists is variadic.

## Structure

```C++
template<typename...>
concept AllNotVariadic = REQUIREMENT;
```

## Implementation

```C++
template<typename...Args>
concept AllNotVariadic = Mouldivore::AllFailed<IsVariadic, Args...>;
```

## Links

- [Source code](../../../../conceptrodon/concepts/functivore/all_not_variadic.hpp)
- [Unit test](../../../../tests/unit/concepts/functivore/all_not_variadic.test.hpp)
