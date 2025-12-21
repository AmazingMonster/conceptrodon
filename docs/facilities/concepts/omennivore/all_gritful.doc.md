<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::AllGritful`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-all-gritful">To Index</a></p>

## Description

`Omennivore::AllGritful` accepts a list of packed vessels.
It returns true if all of the underlying vessels are `Grit`s.

## Structure

```C++
template<typename...>
concept AllGritful = REQUIREMENT;
```

## Implementation

```C++
template<typename...Args>
concept AllGritful = Mouldivore::AllConfess<IsGritful, Args...>;
```

## Links

- [Source code](../../../../conceptrodon/concepts/omennivore/all_gritful.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/all_gritful.test.hpp)
