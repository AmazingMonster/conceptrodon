<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::AllNoexceptSpecified`

<p style='text-align: right;'><a href="../../concepts.md#functivore-all-noexcept-specified">To Index</a></p>

## Description

`Functivore::AllNoexceptSpecified` accepts a list of function-like types.
It returns true if all of them are `noexcept` specified.

## Structure

```C++
template<typename...>
concept AllNoexceptSpecified = REQUIREMENT;
```

## Implementation

```C++
template<typename...Args>
concept AllNoexceptSpecified = Mouldivore::AllPassed<IsNoexcept, Args...>;
```

## Links

- [Source code](../../../../conceptrodon/concepts/functivore/all_noexcept_specified.hpp)
- [Unit test](../../../../tests/unit/concepts/functivore/all_noexcept_specified.test.hpp)
