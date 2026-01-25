<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::Uncoolful`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-uncoolful">To Index</a></p>

## Description

`Omennivore::Uncoolful` accepts a packed vessel.
It returns true if the underlying vessel is not a `Cool`.

## Structure

```C++
template<typename>
concept Uncoolful = REQUIREMENT;
```

## Implementation

```C++
template<typename Arg>
concept Uncoolful
=   Mouldivore::Failed<IsCoolful, Arg>
||  Moldful<Arg>
||  Pageful<Arg>
||  Roadful<Arg>
||  Railful<Arg>
||  Flowful<Arg>
||  Sailful<Arg>
||  Snowful<Arg>
||  Hailful<Arg>
||  Calmful<Arg>
||  Gritful<Arg>
||  Willful<Arg>
||  Glowful<Arg>
||  Dawnful<Arg>
;
```

## Links

- [Source code](../../../../conceptrodon/concepts/omennivore/uncoolful.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/uncoolful.test.hpp)
