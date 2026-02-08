<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::FunctionCallOperatorAvailable`

<p style='text-align: right;'><a href="../../concepts.md#functivore-function-call-operator-available">To Index</a></p>

## Description

`Functivore::FunctionCallOperatorAvailable` accepts a function-like type and a list of argument types.

It returns true if the function-like type can be directly invoked by the argument types, and false otherwise.

## Structure

```C++
template<typename>
concept FunctionCallOperatorAvailable = REQUIREMENT;
```

## Implementation

```C++
template<typename FunctionObject, typename...Args>
concept FunctionCallOperatorAvailable
= Typelivore::Nice<decltype(std::declval<FunctionObject>()(std::declval<Args>()...))>;
```

## Links

- [Source code](../../../../conceptrodon/concepts/functivore/function_call_operator_available.hpp)
- [Unit test](../../../../tests/unit/concepts/functivore/function_call_operator_available.test.hpp)
