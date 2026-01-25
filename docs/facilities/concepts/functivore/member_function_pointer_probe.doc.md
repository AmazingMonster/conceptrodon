<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::MemberFunctionPointerProbe`

<p style='text-align: right;'><a href="../../concepts.md#functivore-member-function-pointer-probe">To Index</a></p>

## Description

`Functivore::MemberFunctionPointerProbe` accepts a function-like type.
It returns true if it is a member function pointer.

## Structure

```C++
template<typename>
concept MemberFunctionPointerProbe = REQUIREMENT;
```

## Implementation

```C++
template<typename FP>
concept MemberFunctionPointerProbe
= Mouldivore::Passed<std::is_member_function_pointer, FP>;
```

## Links

- [Source code](../../../../conceptrodon/concepts/functivore/member_function_pointer_probe.hpp)
- [Unit test](../../../../tests/unit/concepts/functivore/member_function_pointer_probe.test.hpp)
