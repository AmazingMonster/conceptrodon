<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::LvalueReferenceQualified`

<p style='text-align: right;'><a href="../../concepts.md#functivore-lvalue-reference-qualified">To Index</a></p>

## Description

`Functivore::LvalueReferenceQualified` accepts a function-like type.
It returns true if it is lvalue reference qualified.

## Structure

```C++
template<typename>
concept LvalueReferenceQualified = REQUIREMENT;
```

## Implementation

```C++
template<typename F>
concept LvalueReferenceQualified = Mouldivore::Confess<IsLvalueReference, F>;
```

## Links

- [Source code](../../../../conceptrodon/concepts/functivore/lvalue_reference_qualified.hpp)
- [Unit test](../../../../tests/unit/concepts/functivore/lvalue_reference_qualified.test.hpp)
