<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::PegNonzero`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-peg-nonzero">To Index</a></p>

## Description

`Omennivore::PegNonzero` accepts a class.
It returns true if the underlying template of the class is a `Peg` and the value result is not `0`. It returns false if otherwise.

## Structure

```C++
template<typename>
concept PegNonzero = REQUIREMENT;
```

## Implementation

```C++
template<typename Arg>
concept PegNonzero
=   Pegful<Arg>
&&  Varybivore::Nonzero<Arg::value>;
```

## Links

- [Source code](../../../../conceptrodon/omennivore/concepts/peg_nonzero.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/peg_nonzero.test.hpp)
