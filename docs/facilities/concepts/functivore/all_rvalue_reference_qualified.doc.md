<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::AllRvalueReferenceQualified`

<p style='text-align: right;'><a href="../../concepts.md#functivore-all-rvalue-reference-qualified">To Index</a></p>

## Description

`Functivore::AllRvalueReferenceQualified` accepts a list of function-like types.
It returns true if all of them are rvalue reference qualified.

## Structure

```C++
template<typename...>
concept AllRvalueReferenceQualified = REQUIREMENT;
```

## Implementation

```C++
template<typename...Args>
concept AllRvalueReferenceQualified = Mouldivore::AllPassed<IsRvalueReference, Args...>;
```

## Links

- [Source code](../../../../conceptrodon/concepts/functivore/all_rvalue_reference_qualified.hpp)
- [Unit test](../../../../tests/unit/concepts/functivore/all_rvalue_reference_qualified.test.hpp)
