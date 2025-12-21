<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::Unglowful`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-unglowful">To Index</a></p>

## Description

`Omennivore::Unglowful` accepts a packed vessel.
It returns true if the underlying vessel is not a `Glow`.

## Structure

```C++
template<typename>
concept Unglowful = REQUIREMENT;
```

## Implementation

```C++
template<typename Arg>
concept Unglowful
=   Mouldivore::Deceive<IsGlowful, Arg>
||  Moldful<Arg>
||  Pageful<Arg>
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
||  Dawnful<Arg>
;
```

## Links

- [Source code](../../../../conceptrodon/concepts/omennivore/unglowful.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/unglowful.test.hpp)
