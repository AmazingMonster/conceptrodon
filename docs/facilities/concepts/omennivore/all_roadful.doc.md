<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::AllRoadful`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-all-roadful">To Index</a></p>

## Description

`Omennivore::AllRoadful` accepts a list of packed vessels.
It returns true if all of the underlying vessels are `Road`s.

## Structure

```C++
template<typename...>
concept AllRoadful = REQUIREMENT;
```

## Implementation

```C++
template<typename...Args>
concept AllRoadful = Mouldivore::AllPassed<IsRoadful, Args...>;
```

## Links

- [Source code](../../../../conceptrodon/concepts/omennivore/all_roadful.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/all_roadful.test.hpp)
