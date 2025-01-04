<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::Sailful`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-sailful">To Index</a></p>

## Description

`Omennivore::Sailful` accepts a packed vessel.
It returns true if the underlying vessel is a `Sail`.

## Structure

```C++
template<typename>
concept Sailful = REQUIREMENT;
```

## Implementation

```C++
template<typename Arg>
concept Sailful = Mouldivore::Confess<IsSailful, Arg>;
```

## Links

- [Source code](../../../../conceptrodon/descend/omennivore/concepts/sailful.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/sailful.test.hpp)
