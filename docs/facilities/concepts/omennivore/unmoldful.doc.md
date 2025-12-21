<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::Unmoldful`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-unmoldful">To Index</a></p>

## Description

`Omennivore::Unmoldful` accepts a packed vessel.
It returns true if the underlying vessel is not a `Mold`.

## Structure

```C++
template<typename>
concept Unmoldful = REQUIREMENT;
```

## Implementation

```C++
template<typename Arg>
concept Unmoldful
=   Mouldivore::Deceive<IsMoldful, Arg>
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
||  Glowful<Arg>
||  Dawnful<Arg>
;
```

## Links

- [Source code](../../../../conceptrodon/concepts/omennivore/unmoldful.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/unmoldful.test.hpp)
