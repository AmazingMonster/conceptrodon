<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::AllNotMemberFunctionPointer`

<p style='text-align: right;'><a href="../../concepts.md#functivore-all-not-member-function-pointer">To Index</a></p>

## Description

`Functivore::AllNotMemberFunctionPointer` accepts a list of function-like types.
It returns true if none of them is a member function pointer.

## Structure

```C++
template<typename...>
concept AllNotMemberFunctionPointer = REQUIREMENT;
```

## Implementation

```C++
template<typename...Args>
concept AllNotMemberFunctionPointer
= Mouldivore::AllDeceive<std::is_member_function_pointer, Args...>;
```

## Links

- [Source code](../../../../conceptrodon/metafunctions/functivore/concepts/all_not_member_function_pointer.hpp)
- [Unit test](../../../../tests/unit/concepts/functivore/all_not_member_function_pointer.test.hpp)
