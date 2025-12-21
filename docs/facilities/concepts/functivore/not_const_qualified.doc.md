<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::NotConstQualified`

<p style='text-align: right;'><a href="../../concepts.md#functivore-not-const-qualified">To Index</a></p>

## Description

`Functivore::NotConstQualified` accepts a function-like type.
It returns true if it is not `const` qualified.

## Structure

```C++
template<typename>
concept NotConstQualified = REQUIREMENT;
```

## Implementation

```C++
template<typename F>
concept NotConstQualified = Mouldivore::Deceive<IsConst, F>;
```

## Links

- [Source code](../../../../conceptrodon/metafunctions/functivore/concepts/not_const_qualified.hpp)
- [Unit test](../../../../tests/unit/concepts/functivore/not_const_qualified.test.hpp)
