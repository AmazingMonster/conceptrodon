<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::ReturnTypeConstrainedMemberAccessThroughPointerToMemberOperatorAvailable`

<p style='text-align: right;'><a href="../../concepts.md#functivore-return-type-constrained-member-access-through-pointer-to-member-operator-available">To Index</a></p>

## Description

`Functivore::ReturnTypeConstrainedMemberAccessThroughPointerToMemberOperatorAvailable` accepts a class type, a predicate, a pointer to member function type, and a list of argument types.

It returns true if both of the following are true:
1. `->*` can be used on the class type and points to the pointer to member function type, and the result is invocable by the list of argument types.
2. The type of the expression satisfies the predicate.

It returns false otherwise.

## Structure

```C++
template<typename>
concept ReturnTypeConstrainedMemberAccessThroughPointerToMemberOperatorAvailable = REQUIREMENT;
```

## Implementation

```C++
template<typename Class, template<typename...> class Predicate, typename Member, typename...Args>
concept ReturnTypeConstrainedMemberAccessThroughPointerToMemberOperatorAvailable
= Predicate<decltype((std::declval<Class>()->*std::declval<Member>())(std::declval<Args>()...))>::value;
```

## Links

- [Source code](../../../../conceptrodon/concepts/functivore/return_type_constrained_member_access_through_pointer_to_member_operator_available.hpp)
- [Unit test](../../../../tests/unit/concepts/functivore/return_type_constrained_member_access_through_pointer_to_member_operator_available.test.hpp)
