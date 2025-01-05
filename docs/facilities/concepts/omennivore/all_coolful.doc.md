<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::AllCoolful`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-all-coolful">To Index</a></p>

## Description

`Omennivore::AllCoolful` accepts a list of packed vessels.
It returns true if all of the underlying vessels are `Cool`s.

## Structure

```C++
template<typename...>
concept AllCoolful = REQUIREMENT;
```

## Implementation

```C++
template<typename...Args>
concept AllCoolful = Mouldivore::AllConfess<IsCoolful, Args...>;
```

## Links

- [Source code](../../../../conceptrodon/descend/omennivore/concepts/all_coolful.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/all_coolful.test.hpp)
