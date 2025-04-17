<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::ConstQualified`

<p style='text-align: right;'><a href="../../concepts.md#functivore-const-qualified">To Index</a></p>

## Description

`Functivore::ConstQualified` accepts a function-like type.
It returns true if it is `const` qualified.

## Structure

```C++
template<typename>
concept ConstQualified = REQUIREMENT;
```

## Implementation

```C++
template<typename F>
concept ConstQualified = Mouldivore::Confess<IsConst, F>;
```

## Links

- [Source code](../../../../conceptrodon/functivore/concepts/const_qualified.hpp)
- [Unit test](../../../../tests/unit/concepts/functivore/const_qualified.test.hpp)
