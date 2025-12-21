<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::FunctionPointerProbe`

<p style='text-align: right;'><a href="../../concepts.md#functivore-function-pointer-probe">To Index</a></p>

## Description

`Functivore::FunctionPointerProbe` accepts a function-like type.
It returns true if it is a function pointer.

## Structure

```C++
template<typename>
concept FunctionPointerProbe = REQUIREMENT;
```

## Implementation

```C++
template<typename FP>
concept FunctionPointerProbe = Mouldivore::Confess<IsFunctionPointer, FP>;
```

## Links

- [Source code](../../../../conceptrodon/concepts/functivore/function_pointer_probe.hpp)
- [Unit test](../../../../tests/unit/concepts/functivore/function_pointer_probe.test.hpp)
