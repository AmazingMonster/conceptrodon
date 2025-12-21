<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::NotVariadic`

<p style='text-align: right;'><a href="../../concepts.md#functivore-not-variadic">To Index</a></p>

## Description

`Functivore::NotVariadic` accepts a function-like type.
It returns true if its parameter list is not variadic.

## Structure

```C++
template<typename>
concept NotVariadic = REQUIREMENT;
```

## Implementation

```C++
template<typename F>
concept NotVariadic = Mouldivore::Deceive<IsVariadic, F>;
```

## Links

- [Source code](../../../../conceptrodon/metafunctions/functivore/concepts/not_variadic.hpp)
- [Unit test](../../../../tests/unit/concepts/functivore/not_variadic.test.hpp)
