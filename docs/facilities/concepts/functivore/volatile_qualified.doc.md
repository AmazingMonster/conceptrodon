<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::VolatileQualified`

<p style='text-align: right;'><a href="../../concepts.md#functivore-volatile-qualified">To Index</a></p>

## Description

`Functivore::VolatileQualified` accepts a function-like type.
It returns true if it is `volatile` qualified.

## Structure

```C++
template<typename>
concept VolatileQualified = REQUIREMENT;
```

## Implementation

```C++
template<typename F>
concept VolatileQualified = Mouldivore::Confess<IsVolatile, F>;
```

## Links

- [Source code](../../../../conceptrodon/functivore/concepts/volatile_qualified.hpp)
- [Unit test](../../../../tests/unit/concepts/functivore/volatile_qualified.test.hpp)
