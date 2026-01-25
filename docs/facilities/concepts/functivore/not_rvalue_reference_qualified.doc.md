<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::NotRvalueReferenceQualified`

<p style='text-align: right;'><a href="../../concepts.md#functivore-not-rvalue-reference-qualified">To Index</a></p>

## Description

`Functivore::NotRvalueReferenceQualified` accepts a function-like type.
It returns true if it is not rvalue reference qualified.

## Structure

```C++
template<typename>
concept NotRvalueReferenceQualified = REQUIREMENT;
```

## Implementation

```C++
template<typename F>
concept NotRvalueReferenceQualified = Mouldivore::Failed<IsRvalueReference, F>;
```

## Links

- [Source code](../../../../conceptrodon/concepts/functivore/not_rvalue_reference_qualified.hpp)
- [Unit test](../../../../tests/unit/concepts/functivore/not_rvalue_reference_qualified.test.hpp)
