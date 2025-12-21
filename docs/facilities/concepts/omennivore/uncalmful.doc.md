<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::Uncalmful`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-uncalmful">To Index</a></p>

## Description

`Omennivore::Uncalmful` accepts a packed vessel.
It returns true if the underlying vessel is not a `Calm`.

## Structure

```C++
template<typename>
concept Uncalmful = REQUIREMENT;
```

## Implementation

```C++
template<typename Arg>
concept Uncalmful
=   Mouldivore::Deceive<IsCalmful, Arg>
||  Moldful<Arg>
||  Pageful<Arg>
||  Roadful<Arg>
||  Railful<Arg>
||  Flowful<Arg>
||  Sailful<Arg>
||  Snowful<Arg>
||  Hailful<Arg>
||  Coolful<Arg>
||  Gritful<Arg>
||  Willful<Arg>
||  Glowful<Arg>
||  Dawnful<Arg>
;
```

## Links

- [Source code](../../../../conceptrodon/concepts/omennivore/uncalmful.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/uncalmful.test.hpp)
