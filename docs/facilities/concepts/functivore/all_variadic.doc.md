<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::AllVariadic`

<p style='text-align: right;'><a href="../../concepts.md#functivore-all-variadic">To Index</a></p>

## Description

`Functivore::AllVariadic` accepts a list of function-like types.
It returns true if all of their parameter lists are variadic.

## Structure

```C++
template<typename...>
concept AllVariadic = REQUIREMENT;
```

## Implementation

```C++
template<typename...Args>
concept AllVariadic = Mouldivore::AllConfess<IsVariadic, Args...>;
```

## Links

- [Source code](../../../../conceptrodon/functivore/concepts/all_variadic.hpp)
- [Unit test](../../../../tests/unit/concepts/functivore/all_variadic.test.hpp)
