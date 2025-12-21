<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::Undawnful`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-undawnful">To Index</a></p>

## Description

`Omennivore::Undawnful` accepts a packed vessel.
It returns true if the underlying vessel is not a `Dawn`.

## Structure

```C++
template<typename>
concept Undawnful = REQUIREMENT;
```

## Implementation

```C++
template<typename Arg>
concept Undawnful
=   Mouldivore::Deceive<IsDawnful, Arg>
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
||  Glowful<Arg>
;
```

## Links

- [Source code](../../../../conceptrodon/concepts/omennivore/undawnful.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/undawnful.test.hpp)
