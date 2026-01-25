<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::NotNoexceptSpecified`

<p style='text-align: right;'><a href="../../concepts.md#functivore-not-noexcept-specified">To Index</a></p>

## Description

`Functivore::NotNoexceptSpecified` accepts a function-like type.
It returns true if it is not `noexcept` specified.

## Structure

```C++
template<typename>
concept NotNoexceptSpecified = REQUIREMENT;
```

## Implementation

```C++
template<typename F>
concept NotNoexceptSpecified = Mouldivore::Failed<IsNoexcept, F>;
```

## Links

- [Source code](../../../../conceptrodon/concepts/functivore/not_noexcept_specified.hpp)
- [Unit test](../../../../tests/unit/concepts/functivore/not_noexcept_specified.test.hpp)
