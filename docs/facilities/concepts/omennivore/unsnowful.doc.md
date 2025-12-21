<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::Unsnowful`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-unsnowful">To Index</a></p>

## Description

`Omennivore::Unsnowful` accepts a packed vessel.
It returns true if the underlying vessel is not a `Snow`.

## Structure

```C++
template<typename>
concept Unsnowful = REQUIREMENT;
```

## Implementation

```C++
template<typename Arg>
concept Unsnowful
=   Mouldivore::Deceive<IsSnowful, Arg>
||  Moldful<Arg>
||  Pageful<Arg>
||  Roadful<Arg>
||  Railful<Arg>
||  Flowful<Arg>
||  Sailful<Arg>
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

- [Source code](../../../../conceptrodon/concepts/omennivore/unsnowful.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/unsnowful.test.hpp)
