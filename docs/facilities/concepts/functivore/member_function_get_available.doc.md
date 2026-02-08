<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::MemberFunctionGetAvailable`

<p style='text-align: right;'><a href="../../concepts.md#functivore-member-function-get-available">To Index</a></p>

## Description

`Functivore::MemberFunctionGetAvailable` accepts a class type and a list of argument types.

It returns true if the class type has a member function called `get` that can be invoked with the given argument types, and false otherwise.

## Structure

```C++
template<typename>
concept MemberFunctionGetAvailable = REQUIREMENT;
```

## Implementation

```C++
template<typename Class, typename...Args>
concept MemberFunctionGetAvailable
= Typelivore::Nice<decltype(std::declval<Class>().get(std::declval<Args>()...))>;
```

## Links

- [Source code](../../../../conceptrodon/concepts/functivore/member_function_get_available.hpp)
- [Unit test](../../../../tests/unit/concepts/functivore/member_function_get_available.test.hpp)
