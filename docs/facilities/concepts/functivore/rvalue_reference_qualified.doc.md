<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::RvalueReferenceQualified`

<p style='text-align: right;'><a href="../../concepts.md#functivore-rvalue-reference-qualified">To Index</a></p>

## Description

`Functivore::RvalueReferenceQualified` accepts a function-like type.
It returns true if it is rvalue reference qualified.

## Structure

```C++
template<typename>
concept RvalueReferenceQualified = REQUIREMENT;
```

## Implementation

```C++
template<typename F>
concept RvalueReferenceQualified = Mouldivore::Passed<IsRvalueReference, F>;
```

## Links

- [Source code](../../../../conceptrodon/concepts/functivore/rvalue_reference_qualified.hpp)
- [Unit test](../../../../tests/unit/concepts/functivore/rvalue_reference_qualified.test.hpp)
