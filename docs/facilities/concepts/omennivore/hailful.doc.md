<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::Hailful`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-hailful">To Index</a></p>

## Description

`Omennivore::Hailful` accepts a packed vessel.
It returns true if the underlying vessel is a `Hail`.

## Structure

```C++
template<typename>
concept Hailful = REQUIREMENT;
```

## Implementation

```C++
template<typename Arg>
concept Hailful = Mouldivore::Confess<IsHailful, Arg>;
```

## Links

- [Source code](../../../../conceptrodon/metafunctions/omennivore/concepts/hailful.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/hailful.test.hpp)
