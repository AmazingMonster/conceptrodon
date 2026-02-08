<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::StaticCastable`

<p style='text-align: right;'><a href="../../concepts.md#typelivore-static-castable">To Index</a></p>

## Description

`Typelivore::StaticCastable` accepts a candidate type and a target type.
It returns true if the candidate type can be converted to the target type by `static_cast`.

## Structure

```C++
template<typename>
concept StaticCastable = REQUIREMENT;
```

## Implementation

```C++
template<typename From, typename To>
concept StaticCastable = Nice<decltype(static_cast<To>(std::declval<From>()))>;
```

## Links

- [Source code](../../../../conceptrodon/concepts/typelivore/static_castable.hpp)
- [Unit test](../../../../tests/unit/concepts/typelivore/static_castable.test.hpp)
