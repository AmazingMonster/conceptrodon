<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::Unpageful`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-unpageful">To Index</a></p>

## Description

`Omennivore::Unpageful` accepts a packed vessel.
It returns true if the underlying vessel is not a `Page`.

## Structure

```C++
template<typename>
concept Unpageful = REQUIREMENT;
```

## Implementation

```C++
template<typename Arg>
concept Unpageful
=   Mouldivore::Deceive<IsPageful, Arg>
||  Moldful<Arg>
||  Roadful<Arg>
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

- [Source code](../../../../conceptrodon/metafunctions/omennivore/concepts/unpageful.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/unpageful.test.hpp)
