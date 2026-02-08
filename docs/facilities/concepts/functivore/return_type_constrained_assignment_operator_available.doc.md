<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::ReturnTypeConstrainedAssignmentOperatorAvailable`

<p style='text-align: right;'><a href="../../concepts.md#functivore-return-type-constrained-assignment-operator-available">To Index</a></p>

## Description

`Functivore::ReturnTypeConstrainedAssignmentOperatorAvailable` accepts a type, a predicate, and another type.

It returns true if both of the following are true.
1. The objects of the first type can be assigned to by the objects of the second type;
2. The type of the expression satisfies the predicate.

It returns false otherwise.

## Structure

```C++
template<typename>
concept ReturnTypeConstrainedAssignmentOperatorAvailable = REQUIREMENT;
```

## Implementation

```C++
template<typename To, template<typename...> class Predicate, typename By>
concept ReturnTypeConstrainedAssignmentOperatorAvailable
= Predicate<decltype(std::declval<To&>()=std::declval<By>())>::value;
```

## Links

- [Source code](../../../../conceptrodon/concepts/functivore/return_type_constrained_assignment_operator_available.hpp)
- [Unit test](../../../../tests/unit/concepts/functivore/return_type_constrained_assignment_operator_available.test.hpp)
