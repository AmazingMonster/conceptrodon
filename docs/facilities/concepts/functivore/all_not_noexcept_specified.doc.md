<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::AllNotNoexceptSpecified`

<p style='text-align: right;'><a href="../../concepts.md#functivore-all-not-noexcept-specified">To Index</a></p>

## Description

`Functivore::AllNotNoexceptSpecified` accepts a list of function-like types.
It returns true if none of them are `noexcept` specified.

## Structure

```C++
template<typename...>
concept AllNotNoexceptSpecified = REQUIREMENT;
```

## Implementation

```C++
template<typename...Args>
concept AllNotNoexceptSpecified = Mouldivore::AllDeceive<IsNoexcept, Args...>;
```

## Links

- [Source code](../../../../conceptrodon/metafunctions/functivore/concepts/all_not_noexcept_specified.hpp)
- [Unit test](../../../../tests/unit/concepts/functivore/all_not_noexcept_specified.test.hpp)
