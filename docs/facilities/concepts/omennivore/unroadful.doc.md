<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::Unroadful`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-unroadful">To Index</a></p>

## Description

`Omennivore::Unroadful` accepts a packed vessel.
It returns true if the underlying vessel is not a `Road`.

## Structure

```C++
template<typename>
concept Unroadful = REQUIREMENT;
```

## Implementation

```C++
template<typename Arg>
concept Unroadful
=   Mouldivore::Failed<IsRoadful, Arg>
||  Moldful<Arg>
||  Pageful<Arg>
||  Railful<Arg>
||  Flowful<Arg>
||  Sailful<Arg>
||  Snowful<Arg>
||  Hailful<Arg>
||  Coolful<Arg>
||  Calmful<Arg>
||  Gritful<Arg>
||  Willful<Arg>
||  Glowful<Arg>
||  Dawnful<Arg>
;
```

## Links

- [Source code](../../../../conceptrodon/concepts/omennivore/unroadful.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/unroadful.test.hpp)
