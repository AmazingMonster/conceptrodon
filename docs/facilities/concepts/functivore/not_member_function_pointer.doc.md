<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::NotMemberFunctionPointer`

<p style='text-align: right;'><a href="../../concepts.md#functivore-not-member-function-pointer">To Index</a></p>

## Description

`Functivore::NotMemberFunctionPointer` accepts a function-like type.
It returns true if it is not a member function pointer.

## Structure

```C++
template<typename>
concept NotMemberFunctionPointer = REQUIREMENT;
```

## Implementation

```C++
template<typename MFP>
concept NotMemberFunctionPointer
= Mouldivore::Deceive<std::is_member_function_pointer, MFP>;
```

## Links

- [Source code](../../../../conceptrodon/concepts/functivore/not_member_function_pointer.hpp)
- [Unit test](../../../../tests/unit/concepts/functivore/not_member_function_pointer.test.hpp)
