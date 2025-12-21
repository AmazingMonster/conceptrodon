<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::AllNotConstQualified`

<p style='text-align: right;'><a href="../../concepts.md#functivore-all-not-const-qualified">To Index</a></p>

## Description

`Functivore::AllNotConstQualified` accepts a list of function-like types.
It returns true if none of them are `const` qualified.

## Structure

```C++
template<typename...>
concept AllNotConstQualified = REQUIREMENT;
```

## Implementation

```C++
template<typename...Args>
concept AllNotConstQualified = Mouldivore::AllDeceive<IsConst, Args...>;
```

## Links

- [Source code](../../../../conceptrodon/metafunctions/functivore/concepts/all_not_const_qualified.hpp)
- [Unit test](../../../../tests/unit/concepts/functivore/all_not_const_qualified.test.hpp)
