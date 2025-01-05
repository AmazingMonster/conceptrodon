<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::AllPageful`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-all-pageful">To Index</a></p>

## Description

`Omennivore::AllPageful` accepts a list of packed vessels.
It returns true if all of the underlying vessels are `Page`s.

## Structure

```C++
template<typename...>
concept AllPageful = REQUIREMENT;
```

## Implementation

```C++
template<typename...Args>
concept AllPageful = Mouldivore::AllConfess<IsPageful, Args...>;
```

## Links

- [Source code](../../../../conceptrodon/omennivore/concepts/all_pageful.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/all_pageful.test.hpp)
