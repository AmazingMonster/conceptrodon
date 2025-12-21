<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::AllNotLvalueReferenceQualified`

<p style='text-align: right;'><a href="../../concepts.md#functivore-all-not-lvalue-reference-qualified">To Index</a></p>

## Description

`Functivore::AllNotLvalueReferenceQualified` accepts a list of function-like types.
It returns true if none of them are lvalue reference qualified.

## Structure

```C++
template<typename...>
concept AllNotLvalueReferenceQualified = REQUIREMENT;
```

## Implementation

```C++
template<typename...Args>
concept AllNotLvalueReferenceQualified = Mouldivore::AllDeceive<IsLvalueReference, Args...>;
```

## Links

- [Source code](../../../../conceptrodon/metafunctions/functivore/concepts/all_not_lvalue_reference_qualified.hpp)
- [Unit test](../../../../tests/unit/concepts/functivore/all_not_lvalue_reference_qualified.test.hpp)
