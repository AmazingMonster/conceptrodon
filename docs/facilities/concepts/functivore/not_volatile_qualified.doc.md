<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::NotVolatileQualified`

<p style='text-align: right;'><a href="../../concepts.md#functivore-not-volatile-qualified">To Index</a></p>

## Description

`Functivore::NotVolatileQualified` accepts a function-like type.
It returns true if it is not `volatile` qualified.

## Structure

```C++
template<typename>
concept NotVolatileQualified = REQUIREMENT;
```

## Implementation

```C++
template<typename F>
concept NotVolatileQualified = Mouldivore::Failed<IsVolatile, F>;
```

## Links

- [Source code](../../../../conceptrodon/concepts/functivore/not_volatile_qualified.hpp)
- [Unit test](../../../../tests/unit/concepts/functivore/not_volatile_qualified.test.hpp)
