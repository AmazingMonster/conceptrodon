<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::AllPegZero`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-all-peg-zero">To Index</a></p>

## Description

`Omennivore::AllPegZero` accepts a list of classes.
It returns true if the underlying template of every class is a `Peg` and all of the value results are `0`. It returns false if otherwise.

## Structure

```C++
template<typename...>
concept AllPegZero = REQUIREMENT;
```

## Implementation

```C++
template<typename...Args>
concept AllPegZero
=   AllPegful<Args...>
&&  Varybivore::AllZero<Args::value...>;
```

## Links

- [Source code](../../../../conceptrodon/metafunctions/omennivore/concepts/all_peg_zero.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/all_peg_zero.test.hpp)
