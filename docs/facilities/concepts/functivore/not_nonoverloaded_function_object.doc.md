<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::NotNonoverloadedFunctionObject`

<p style='text-align: right;'><a href="../../concepts.md#functivore-not-nonoverloaded-function-object">To Index</a></p>

## Description

`Functivore::NotNonoverloadedFunctionObject` accepts a function-like type.
It returns true if it is not a nonoverloaded function object.

## Structure

```C++
template<typename>
concept NotNonoverloadedFunctionObject = REQUIREMENT;
```

## Implementation

```C++
template<typename FO>
concept NotNonoverloadedFunctionObject = ! requires {&FO::operator();};
```

## Links

- [Source code](../../../../conceptrodon/metafunctions/functivore/concepts/not_nonoverloaded_function_object.hpp)
- [Unit test](../../../../tests/unit/concepts/functivore/not_nonoverloaded_function_object.test.hpp)
