<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::AllNotRvalueReferenceQualified`

<p style='text-align: right;'><a href="../../concepts.md#functivore-all-not-rvalue-reference-qualified">To Index</a></p>

## Description

`Functivore::AllNotRvalueReferenceQualified` accepts a list of function-like types.
It returns true if none of them are rvalue reference qualified.

## Structure

```C++
template<typename...>
concept AllNotRvalueReferenceQualified = REQUIREMENT;
```

## Implementation

```C++
template<typename...Args>
concept AllNotRvalueReferenceQualified = Mouldivore::AllFailed<IsRvalueReference, Args...>;
```

## Links

- [Source code](../../../../conceptrodon/concepts/functivore/all_not_rvalue_reference_qualified.hpp)
- [Unit test](../../../../tests/unit/concepts/functivore/all_not_rvalue_reference_qualified.test.hpp)
