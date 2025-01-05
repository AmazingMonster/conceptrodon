<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::Unrailful`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-unrailful">To Index</a></p>

## Description

`Omennivore::Unrailful` accepts a packed vessel.
It returns true if the underlying vessel is not a `Rail`.

## Structure

```C++
template<typename>
concept Unrailful = REQUIREMENT;
```

## Implementation

```C++
template<typename Arg>
concept Unrailful
=   Mouldivore::Deceive<IsRailful, Arg>
||  Moldful<Arg>
||  Pageful<Arg>
||  Roadful<Arg>
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

- [Source code](../../../../conceptrodon/omennivore/concepts/unrailful.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/unrailful.test.hpp)
