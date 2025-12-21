<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::AllConstQualified`

<p style='text-align: right;'><a href="../../concepts.md#functivore-all-const-qualified">To Index</a></p>

## Description

`Functivore::AllConstQualified` accepts a list of function-like types.
It returns true if all of them are `const` qualified.

## Structure

```C++
template<typename...>
concept AllConstQualified = REQUIREMENT;
```

## Implementation

```C++
template<typename...Args>
concept AllConstQualified = Mouldivore::AllConfess<IsConst, Args...>;
```

## Links

- [Source code](../../../../conceptrodon/concepts/functivore/all_const_qualified.hpp)
- [Unit test](../../../../tests/unit/concepts/functivore/all_const_qualified.test.hpp)
