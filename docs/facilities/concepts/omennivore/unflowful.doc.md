<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::Unflowful`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-unflowful">To Index</a></p>

## Description

`Omennivore::Unflowful` accepts a packed vessel.
It returns true if the underlying vessel is not a `Flow`.

## Structure

```C++
template<typename>
concept Unflowful = REQUIREMENT;
```

## Implementation

```C++
template<typename Arg>
concept Unflowful
=   Mouldivore::Deceive<IsFlowful, Arg>
||  Moldful<Arg>
||  Pageful<Arg>
||  Roadful<Arg>
||  Railful<Arg>
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

- [Source code](../../../../conceptrodon/metafunctions/omennivore/concepts/unflowful.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/unflowful.test.hpp)
