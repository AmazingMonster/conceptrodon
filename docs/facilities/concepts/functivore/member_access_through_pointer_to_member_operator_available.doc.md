<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::MemberAccessThroughPointerToMemberOperatorAvailable`

<p style='text-align: right;'><a href="../../concepts.md#functivore-member-access-through-pointer-to-member-operator-available">To Index</a></p>

## Description

`Functivore::MemberAccessThroughPointerToMemberOperatorAvailable` accepts a class type, a pointer to member function type, and a list of argument types.

It returns true if `->*` can be used on the class type and points to the pointer to member function type, and the result is invocable by the list of argument types.

## Structure

```C++
template<typename>
concept MemberAccessThroughPointerToMemberOperatorAvailable = REQUIREMENT;
```

## Implementation

```C++
template<typename Class, typename Member, typename...Args>
concept MemberAccessThroughPointerToMemberOperatorAvailable
= Typelivore::Nice<decltype((std::declval<Class>()->*std::declval<Member>())(std::declval<Args>()...))>;
```

## Links

- [Source code](../../../../conceptrodon/concepts/functivore/member_access_through_pointer_to_member_operator_available.hpp)
- [Unit test](../../../../tests/unit/concepts/functivore/member_access_through_pointer_to_member_operator_available.test.hpp)
