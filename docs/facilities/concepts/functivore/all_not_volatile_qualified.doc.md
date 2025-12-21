<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::AllNotVolatileQualified`

<p style='text-align: right;'><a href="../../concepts.md#functivore-all-not-volatile-qualified">To Index</a></p>

## Description

`Functivore::AllNotVolatileQualified` accepts a list of function-like types.
It returns true if none of them are `volatile` qualified.

## Structure

```C++
template<typename...>
concept AllNotVolatileQualified = REQUIREMENT;
```

## Implementation

```C++
template<typename...Args>
concept AllNotVolatileQualified = Mouldivore::AllDeceive<IsVolatile, Args...>;
```

## Links

- [Source code](../../../../conceptrodon/metafunctions/functivore/concepts/all_not_volatile_qualified.hpp)
- [Unit test](../../../../tests/unit/concepts/functivore/all_not_volatile_qualified.test.hpp)
