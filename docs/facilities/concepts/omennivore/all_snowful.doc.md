<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::AllSnowful`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-all-snowful">To Index</a></p>

## Description

`Omennivore::AllSnowful` accepts a list of packed vessels.
It returns true if all of the underlying vessels are `Snow`s.

## Structure

```C++
template<typename...>
concept AllSnowful = REQUIREMENT;
```

## Implementation

```C++
template<typename...Args>
concept AllSnowful = Mouldivore::AllConfess<IsSnowful, Args...>;
```

## Links

- [Source code](../../../../conceptrodon/metafunctions/omennivore/concepts/all_snowful.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/all_snowful.test.hpp)
