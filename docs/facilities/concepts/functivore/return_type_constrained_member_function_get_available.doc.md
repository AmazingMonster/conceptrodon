<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::ReturnTypeConstrainedMemberFunctionGetAvailable`

<p style='text-align: right;'><a href="../../concepts.md#functivore-return-type-constrained-member-function-get-available">To Index</a></p>

## Description

`Functivore::ReturnTypeConstrainedMemberFunctionGetAvailable` accepts a class type, a predicate, and a list of argument types.

It returns true if both of the following are true:
1. The class type has a member function called `get` that can be invoked with the given argument types.
2. The type of the expression satisfies the predicate.

It returns false otherwise.

## Structure

```C++
template<typename>
concept ReturnTypeConstrainedMemberFunctionGetAvailable = REQUIREMENT;
```

## Implementation

```C++
template<typename Class, template<typename...> class Predicate, typename...Args>
concept ReturnTypeConstrainedMemberFunctionGetAvailable
= Predicate<decltype(std::declval<Class>().get(std::declval<Args>()...))>::value;
```

## Links

- [Source code](../../../../conceptrodon/concepts/functivore/return_type_constrained_member_function_get_available.hpp)
- [Unit test](../../../../tests/unit/concepts/functivore/return_type_constrained_member_function_get_available.test.hpp)
