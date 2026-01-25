<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::NoexceptSpecified`

<p style='text-align: right;'><a href="../../concepts.md#functivore-noexcept-specified">To Index</a></p>

## Description

`Functivore::NoexceptSpecified` accepts a function-like type.
It returns true if it is `noexcept` specified.

## Structure

```C++
template<typename>
concept NoexceptSpecified = REQUIREMENT;
```

## Implementation

```C++
template<typename F>
concept NoexceptSpecified = Mouldivore::Passed<IsNoexcept, F>;
```

## Links

- [Source code](../../../../conceptrodon/concepts/functivore/noexcept_specified.hpp)
- [Unit test](../../../../tests/unit/concepts/functivore/noexcept_specified.test.hpp)
