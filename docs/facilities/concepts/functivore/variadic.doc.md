<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::Variadic`

<p style='text-align: right;'><a href="../../concepts.md#functivore-variadic">To Index</a></p>

## Description

`Functivore::Variadic` accepts a function-like type.
It returns true if its parameter list is variadic.

## Structure

```C++
template<typename>
concept Variadic = REQUIREMENT;
```

## Implementation

```C++
template<typename F>
concept Variadic = Mouldivore::Confess<IsVariadic, F>;
```

## Links

- [Source code](../../../../conceptrodon/metafunctions/functivore/concepts/variadic.hpp)
- [Unit test](../../../../tests/unit/concepts/functivore/variadic.test.hpp)
