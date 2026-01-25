<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::AllVolatileQualified`

<p style='text-align: right;'><a href="../../concepts.md#functivore-all-volatile-qualified">To Index</a></p>

## Description

`Functivore::AllVolatileQualified` accepts a list of function-like types.
It returns true if all of them are `volatile` qualified.

## Structure

```C++
template<typename...>
concept AllVolatileQualified = REQUIREMENT;
```

## Implementation

```C++
template<typename...Args>
concept AllVolatileQualified = Mouldivore::AllPassed<IsVolatile, Args...>;
```

## Links

- [Source code](../../../../conceptrodon/concepts/functivore/all_volatile_qualified.hpp)
- [Unit test](../../../../tests/unit/concepts/functivore/all_volatile_qualified.test.hpp)
