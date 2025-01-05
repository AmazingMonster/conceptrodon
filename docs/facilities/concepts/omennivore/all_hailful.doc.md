<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::AllHailful`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-all-hailful">To Index</a></p>

## Description

`Omennivore::AllHailful` accepts a list of packed vessels.
It returns true if all of the underlying vessels are `Hail`s.

## Structure

```C++
template<typename...>
concept AllHailful = REQUIREMENT;
```

## Implementation

```C++
template<typename...Args>
concept AllHailful = Mouldivore::AllConfess<IsHailful, Args...>;
```

## Links

- [Source code](../../../../conceptrodon/descend/omennivore/concepts/all_hailful.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/all_hailful.test.hpp)
