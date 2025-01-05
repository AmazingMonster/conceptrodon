<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::Unsailful`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-unsailful">To Index</a></p>

## Description

`Omennivore::Unsailful` accepts a packed vessel.
It returns true if the underlying vessel is not a `Sail`.

## Structure

```C++
template<typename>
concept Unsailful = REQUIREMENT;
```

## Implementation

```C++
template<typename Arg>
concept Unsailful
=   Mouldivore::Deceive<IsSailful, Arg>
||  Moldful<Arg>
||  Pageful<Arg>
||  Roadful<Arg>
||  Railful<Arg>
||  Flowful<Arg>
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

- [Source code](../../../../conceptrodon/omennivore/concepts/unsailful.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/unsailful.test.hpp)
