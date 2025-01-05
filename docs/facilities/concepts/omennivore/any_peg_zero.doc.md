<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::AnyPegZero`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-any-peg-zero">To Index</a></p>

## Description

`Omennivore::AnyPegZero` accepts a list of classes.
It returns true if there exists a class whose underlying template is a `Peg` and whose value result is `0`. It returns false if otherwise.

## Structure

```C++
template<typename...>
concept AnyPegZero = REQUIREMENT;
```

## Implementation

```C++
template<typename...Args>
concept AnyPegZero
=   AllPegful<Args...>
&&  Varybivore::AnyZero<Args::value...>;
```

## Links

- [Source code](../../../../conceptrodon/descend/omennivore/concepts/descend/any_peg_zero.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/any_peg_zero.test.hpp)
