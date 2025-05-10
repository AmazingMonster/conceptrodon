<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::AllNotFunctionPointer`

<p style='text-align: right;'><a href="../../concepts.md#functivore-all-not-function-pointer">To Index</a></p>

## Description

`Functivore::AllNotFunctionPointer` accepts a list of function-like types.
It returns true if none of them is a function pointer.

## Structure

```C++
template<typename...>
concept AllNotFunctionPointer = REQUIREMENT;
```

## Implementation

```C++
template<typename...Args>
concept AllNotFunctionPointer = Mouldivore::AllDeceive<IsFunctionPointer, Args...>;
```

## Links

- [Source code](../../../../conceptrodon/functivore/concepts/all_not_function_pointer.hpp)
- [Unit test](../../../../tests/unit/concepts/functivore/all_not_function_pointer.test.hpp)
