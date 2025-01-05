<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::AllSailful`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-all-sailful">To Index</a></p>

## Description

`Omennivore::AllSailful` accepts a list of packed vessels.
It returns true if all of the underlying vessels are `Sail`s.

## Structure

```C++
template<typename...>
concept AllSailful = REQUIREMENT;
```

## Implementation

```C++
template<typename...Args>
concept AllSailful = Mouldivore::AllConfess<IsSailful, Args...>;
```

## Links

- [Source code](../../../../conceptrodon/omennivore/concepts/all_sailful.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/all_sailful.test.hpp)
