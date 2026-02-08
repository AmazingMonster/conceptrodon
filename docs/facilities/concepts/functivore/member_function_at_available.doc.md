<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::MemberFunctionAtAvailable`

<p style='text-align: right;'><a href="../../concepts.md#functivore-member-function-at-available">To Index</a></p>

## Description

`Functivore::MemberFunctionAtAvailable` accepts a class type and a list of argument types.

It returns true if the class type has a member function called `at` that can be invoked with the given argument types, and false otherwise.

## Structure

```C++
template<typename>
concept MemberFunctionAtAvailable = REQUIREMENT;
```

## Implementation

```C++
template<typename Class, typename...Args>
concept MemberFunctionAtAvailable
= Typelivore::Nice<decltype(std::declval<Class>().at(std::declval<Args>()...))>;
```

## Links

- [Source code](../../../../conceptrodon/concepts/functivore/member_function_at_available.hpp)
- [Unit test](../../../../tests/unit/concepts/functivore/member_function_at_available.test.hpp)
