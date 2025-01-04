<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::AllDawnful`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-all-dawnful">To Index</a></p>

## Description

`Omennivore::AllDawnful` accepts a list of packed vessels.
It returns true if all of the underlying vessels are `Dawn`s.

## Structure

```C++
template<typename...>
concept AllDawnful = REQUIREMENT;
```

## Implementation

```C++
template<typename...Args>
concept AllDawnful = Mouldivore::AllConfess<IsDawnful, Args...>;
```

## Links

- [Source code](../../../../conceptrodon/descend/omennivore/concepts/all_dawnful.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/all_dawnful.test.hpp)
