<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::NonoverloadedFunctionObjectProbe`

<p style='text-align: right;'><a href="../../concepts.md#functivore-nonoverloaded-function-object-probe">To Index</a></p>

## Description

`Functivore::NonoverloadedFunctionObjectProbe` accepts a function-like type.
It returns true if it is a nonoverloaded function object.

## Structure

```C++
template<typename>
concept NonoverloadedFunctionObjectProbe = REQUIREMENT;
```

## Implementation

```C++
template<typename FO>
concept NonoverloadedFunctionObjectProbe = requires {&FO::operator();};
```

## Links

- [Source code](../../../../conceptrodon/functivore/concepts/nonoverloaded_function_object_probe.hpp)
- [Unit test](../../../../tests/unit/concepts/functivore/nonoverloaded_function_object_probe.test.hpp)
