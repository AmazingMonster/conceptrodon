<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::AllCalmful`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-all-calmful">To Index</a></p>

## Description

`Omennivore::AllCalmful` accepts a list of packed vessels.
It returns true if all of the underlying vessels are `Calm`s.

## Structure

```C++
template<typename...>
concept AllCalmful = REQUIREMENT;
```

## Implementation

```C++
template<typename...Args>
concept AllCalmful = Mouldivore::AllConfess<IsCalmful, Args...>;
```

## Links

- [Source code](../../../../conceptrodon/concepts/omennivore/all_calmful.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/all_calmful.test.hpp)
