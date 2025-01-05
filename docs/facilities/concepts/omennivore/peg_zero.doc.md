<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::PegZero`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-peg-zero">To Index</a></p>

## Description

`Omennivore::PegZero` accepts a class.
It returns true if the underlying template of the class is a `Peg` and the value result is `0`. It returns false if otherwise.

## Structure

```C++
template<typename>
concept PegZero = REQUIREMENT;
```

## Implementation

```C++
template<typename Arg>
concept PegZero
=   Pegful<Arg>
&&  Varybivore::Zero<Arg::value>;
```

## Links

- [Source code](../../../../conceptrodon/omennivore/concepts/peg_zero.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/peg_zero.test.hpp)
