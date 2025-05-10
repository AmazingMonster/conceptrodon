<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::AllMemberFunctionPointer`

<p style='text-align: right;'><a href="../../concepts.md#functivore-all-member-function-pointer">To Index</a></p>

## Description

`Functivore::AllMemberFunctionPointer` accepts a list of function-like types.
It returns true if all of them are member function pointers.

## Structure

```C++
template<typename...>
concept AllMemberFunctionPointer = REQUIREMENT;
```

## Implementation

```C++
template<typename...Args>
concept AllMemberFunctionPointer
= Mouldivore::AllConfess<std::is_member_function_pointer, Args...>;
```

## Links

- [Source code](../../../../conceptrodon/functivore/concepts/all_member_function_pointer.hpp)
- [Unit test](../../../../tests/unit/concepts/functivore/all_member_function_pointer.test.hpp)
