<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::AllFunctionPointer`

<p style='text-align: right;'><a href="../../concepts.md#functivore-all-function-pointer">To Index</a></p>

## Description

`Functivore::AllFunctionPointer` accepts a list of function-like types.
It returns true if all of them are function pointers.

## Structure

```C++
template<typename...>
concept AllFunctionPointer = REQUIREMENT;
```

## Implementation

```C++
template<typename...Args>
concept AllFunctionPointer = Mouldivore::AllConfess<IsFunctionPointer, Args...>;
```

## Links

- [Source code](../../../../conceptrodon/concepts/functivore/all_function_pointer.hpp)
- [Unit test](../../../../tests/unit/concepts/functivore/all_function_pointer.test.hpp)
