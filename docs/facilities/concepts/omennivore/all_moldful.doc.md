<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::AllMoldful`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-all-moldful">To Index</a></p>

## Description

`Omennivore::AllMoldful` accepts a list of packed vessels.
It returns true if all of the underlying vessels are `Mold`s.

## Structure

```C++
template<typename...>
concept AllMoldful = REQUIREMENT;
```

## Implementation

```C++
template<typename...Args>
concept AllMoldful = Mouldivore::AllPassed<IsMoldful, Args...>;
```

## Links

- [Source code](../../../../conceptrodon/concepts/omennivore/all_moldful.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/all_moldful.test.hpp)
