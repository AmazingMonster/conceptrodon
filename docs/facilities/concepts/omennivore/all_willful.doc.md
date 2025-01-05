<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::AllWillful`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-all-willful">To Index</a></p>

## Description

`Omennivore::AllWillful` accepts a list of packed vessels.
It returns true if all of the underlying vessels are `Will`s.

## Structure

```C++
template<typename...>
concept AllWillful = REQUIREMENT;
```

## Implementation

```C++
template<typename...Args>
concept AllWillful = Mouldivore::AllConfess<IsWillful, Args...>;
```

## Links

- [Source code](../../../../conceptrodon/descend/omennivore/concepts/all_willful.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/all_willful.test.hpp)
