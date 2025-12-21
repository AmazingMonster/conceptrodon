<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::NotLvalueReferenceQualified`

<p style='text-align: right;'><a href="../../concepts.md#functivore-not-lvalue-reference-qualified">To Index</a></p>

## Description

`Functivore::NotLvalueReferenceQualified` accepts a function-like type.
It returns true if it is not lvalue reference qualified.

## Structure

```C++
template<typename>
concept NotLvalueReferenceQualified = REQUIREMENT;
```

## Implementation

```C++
template<typename F>
concept NotLvalueReferenceQualified = Mouldivore::Deceive<IsLvalueReference, F>;
```

## Links

- [Source code](../../../../conceptrodon/concepts/functivore/not_lvalue_reference_qualified.hpp)
- [Unit test](../../../../tests/unit/concepts/functivore/not_lvalue_reference_qualified.test.hpp)
