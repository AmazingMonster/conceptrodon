<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::AllLvalueReferenceQualified`

<p style='text-align: right;'><a href="../../concepts.md#functivore-all-lvalue-reference-qualified">To Index</a></p>

## Description

`Functivore::AllLvalueReferenceQualified` accepts a list of function-like types.
It returns true if all of them are lvalue reference qualified.

## Structure

```C++
template<typename...>
concept AllLvalueReferenceQualified = REQUIREMENT;
```

## Implementation

```C++
template<typename...Args>
concept AllLvalueReferenceQualified = Mouldivore::AllPassed<IsLvalueReference, Args...>;
```

## Links

- [Source code](../../../../conceptrodon/concepts/functivore/all_lvalue_reference_qualified.hpp)
- [Unit test](../../../../tests/unit/concepts/functivore/all_lvalue_reference_qualified.test.hpp)
