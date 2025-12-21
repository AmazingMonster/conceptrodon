<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::AllNotNonoverloadedFunctionObject`

<p style='text-align: right;'><a href="../../concepts.md#functivore-all-not-nonoverloaded-function-object">To Index</a></p>

## Description

`Functivore::AllNotNonoverloadedFunctionObject` accepts a list of function-like types.
It returns true if none of them is a nonoverloaded function object.

## Structure

```C++
template<typename...>
concept AllNoNonoverloadedFunctionObject = REQUIREMENT;
```

## Implementation

```C++
template<typename...Args>
concept AllNotNonoverloadedFunctionObject = (...&&NotNonoverloadedFunctionObject<Args>);
```

## Links

- [Source code](../../../../conceptrodon/concepts/functivore/all_not_nonoverloaded_function_object.hpp)
- [Unit test](../../../../tests/unit/concepts/functivore/all_not_nonoverloaded_function_object.test.hpp)
