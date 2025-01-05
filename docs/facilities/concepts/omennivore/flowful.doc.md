<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::Flowful`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-flowful">To Index</a></p>

## Description

`Omennivore::Flowful` accepts a packed vessel.
It returns true if the underlying vessel is a `Flow`.

## Structure

```C++
template<typename>
concept Flowful = REQUIREMENT;
```

## Implementation

```C++
template<typename Arg>
concept Flowful = Mouldivore::Confess<IsFlowful, Arg>;
```

## Links

- [Source code](../../../../conceptrodon/omennivore/concepts/flowful.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/flowful.test.hpp)
