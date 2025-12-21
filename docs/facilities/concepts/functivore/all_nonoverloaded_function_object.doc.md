<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::AllNonoverloadedFunctionObject`

<p style='text-align: right;'><a href="../../concepts.md#functivore-all-nonoverloaded-function-object">To Index</a></p>

## Description

`Functivore::AllNonoverloadedFunctionObject` accepts a list of function-like types.
It returns true if all of them are nonoverloaded function objects.

## Structure

```C++
template<typename...>
concept AllNonoverloadedFunctionObject = REQUIREMENT;
```

## Implementation

```C++
template<typename...Args>
concept AllNonoverloadedFunctionObject = Mouldivore::AllConfess<IsNonoverloadedFunctionObject, Args...>;
```

## Links

- [Source code](../../../../conceptrodon/metafunctions/functivore/concepts/all_nonoverloaded_function_object.hpp)
- [Unit test](../../../../tests/unit/concepts/functivore/all_nonoverloaded_function_object.test.hpp)
