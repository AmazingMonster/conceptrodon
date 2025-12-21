<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::Unwillful`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-unwillful">To Index</a></p>

## Description

`Omennivore::Unwillful` accepts a packed vessel.
It returns true if the underlying vessel is not a `Will`.

## Structure

```C++
template<typename>
concept Unwillful = REQUIREMENT;
```

## Implementation

```C++
template<typename Arg>
concept Unwillful
=   Mouldivore::Deceive<IsWillful, Arg>
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
||  Glowful<Arg>
||  Dawnful<Arg>
;
```

## Links

- [Source code](../../../../conceptrodon/concepts/omennivore/unwillful.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/unwillful.test.hpp)
