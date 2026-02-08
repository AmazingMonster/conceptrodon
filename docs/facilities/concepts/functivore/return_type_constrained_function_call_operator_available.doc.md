<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::ReturnTypeConstrainedFunctionCallOperatorAvailable`

<p style='text-align: right;'><a href="../../concepts.md#functivore-return-type-constrained-function-call-operator-available">To Index</a></p>

## Description

`Functivore::ReturnTypeConstrainedFunctionCallOperatorAvailable` accepts a function-like type, a predicate, and a list of argument types.

It returns true if both of the following are true:
1. The function-like type can be directly invoked by the argument types.
2. The type of the expression satisfies the predicate.

It returns false otherwise.

## Structure

```C++
template<typename>
concept ReturnTypeConstrainedFunctionCallOperatorAvailable = REQUIREMENT;
```

## Implementation

```C++
template<typename FunctionObject, template<typename...> class Predicate, typename...Args>
concept ReturnTypeConstrainedFunctionCallOperatorAvailable
= Predicate<decltype(std::declval<FunctionObject>()(std::declval<Args>()...))>::value;
```

## Links

- [Source code](../../../../conceptrodon/concepts/functivore/return_type_constrained_function_call_operator_available.hpp)
- [Unit test](../../../../tests/unit/concepts/functivore/return_type_constrained_function_call_operator_available.test.hpp)
