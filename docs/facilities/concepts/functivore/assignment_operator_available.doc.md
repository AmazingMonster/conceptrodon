<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::AssignmentOperatorAvailable`

<p style='text-align: right;'><a href="../../concepts.md#functivore-assignment-operator-available">To Index</a></p>

## Description

`Functivore::AssignmentOperatorAvailable` accepts two types differentiated by the left-to-right order.

It returns true if the objects of the first type can be assigned to by the objects of the second type, and false otherwise.

## Structure

```C++
template<typename>
concept AssignmentOperatorAvailable = REQUIREMENT;
```

## Implementation

```C++
template<typename To, typename By>
concept AssignmentOperatorAvailable
= Typelivore::Nice<decltype(std::declval<To&>()=std::declval<By>())>;
```

## Links

- [Source code](../../../../conceptrodon/concepts/functivore/assignment_operator_available.hpp)
- [Unit test](../../../../tests/unit/concepts/functivore/assignment_operator_available.test.hpp)
