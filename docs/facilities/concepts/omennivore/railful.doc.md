<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::Railful`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-railful">To Index</a></p>

## Description

`Omennivore::Railful` accepts a packed vessel.
It returns true if the underlying vessel is a `Rail`.

## Structure

```C++
template<typename>
concept Railful = REQUIREMENT;
```

## Implementation

```C++
template<typename Arg>
concept Railful = Mouldivore::Confess<IsRailful, Arg>;
```

## Links

- [Source code](../../../../conceptrodon/concepts/omennivore/railful.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/railful.test.hpp)
