<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::Unhailful`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-unhailful">To Index</a></p>

## Description

`Omennivore::Unhailful` accepts a packed vessel.
It returns true if the underlying vessel is not a `Hail`.

## Structure

```C++
template<typename>
concept Unhailful = REQUIREMENT;
```

## Implementation

```C++
template<typename Arg>
concept Unhailful
=   Mouldivore::Deceive<IsHailful, Arg>
||  Moldful<Arg>
||  Pageful<Arg>
||  Roadful<Arg>
||  Railful<Arg>
||  Flowful<Arg>
||  Sailful<Arg>
||  Snowful<Arg>
||  Coolful<Arg>
||  Calmful<Arg>
||  Gritful<Arg>
||  Willful<Arg>
||  Glowful<Arg>
||  Dawnful<Arg>
;
```

## Links

- [Source code](../../../../conceptrodon/descend/omennivore/concepts/descend/unhailful.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/unhailful.test.hpp)
