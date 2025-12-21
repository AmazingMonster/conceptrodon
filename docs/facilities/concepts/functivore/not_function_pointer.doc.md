<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::NotFunctionPointer`

<p style='text-align: right;'><a href="../../concepts.md#functivore-not-function-pointer">To Index</a></p>

## Description

`Functivore::NotFunctionPointer` accepts a function-like type.
It returns true if it is not a function pointer.

## Structure

```C++
template<typename>
concept NotFunctionPointer = REQUIREMENT;
```

## Implementation

```C++
template<typename FP>
concept NotFunctionPointer = Mouldivore::Deceive<IsFunctionPointer, FP>;
```

## Links

- [Source code](../../../../conceptrodon/concepts/functivore/not_function_pointer.hpp)
- [Unit test](../../../../tests/unit/concepts/functivore/not_function_pointer.test.hpp)
