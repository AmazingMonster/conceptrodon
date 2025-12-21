<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::AllFlowful`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-all-flowful">To Index</a></p>

## Description

`Omennivore::AllFlowful` accepts a list of packed vessels.
It returns true if all of the underlying vessels are `Flow`s.

## Structure

```C++
template<typename...>
concept AllFlowful = REQUIREMENT;
```

## Implementation

```C++
template<typename...Args>
concept AllFlowful = Mouldivore::AllConfess<IsFlowful, Args...>;
```

## Links

- [Source code](../../../../conceptrodon/concepts/omennivore/all_flowful.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/all_flowful.test.hpp)
