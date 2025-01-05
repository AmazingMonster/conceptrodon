<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::AllRailful`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-all-railful">To Index</a></p>

## Description

`Omennivore::AllRailful` accepts a list of packed vessels.
It returns true if all of the underlying vessels are `Rail`s.

## Structure

```C++
template<typename...>
concept AllRailful = REQUIREMENT;
```

## Implementation

```C++
template<typename...Args>
concept AllRailful = Mouldivore::AllConfess<IsRailful, Args...>;
```

## Links

- [Source code](../../../../conceptrodon/omennivore/concepts/all_railful.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/all_railful.test.hpp)
