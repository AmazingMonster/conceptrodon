<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::Ungritful`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-ungritful">To Index</a></p>

## Description

`Omennivore::Ungritful` accepts a packed vessel.
It returns true if the underlying vessel is not a `Grit`.

## Structure

```C++
template<typename>
concept Ungritful = REQUIREMENT;
```

## Implementation

```C++
template<typename Arg>
concept Ungritful
=   Mouldivore::Deceive<IsGritful, Arg>
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
||  Willful<Arg>
||  Glowful<Arg>
||  Dawnful<Arg>
;
```

## Links

- [Source code](../../../../conceptrodon/omennivore/concepts/ungritful.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/ungritful.test.hpp)
