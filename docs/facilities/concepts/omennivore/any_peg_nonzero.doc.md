<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::AnyPegNonzero`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-any-peg-nonzero">To Index</a></p>

## Description

`Omennivore::AnyPegNonzero` accepts a list of classes.
It returns true if there exists a class whose underlying template is a `Peg` and whose value result is not `0`. It returns false if otherwise.

## Structure

```C++
template<typename...>
concept AnyPegNonzero = REQUIREMENT;
```

## Implementation

```C++
template<typename...Args>
concept AnyPegNonzero
=   AllPegful<Args...>
&&  Varybivore::AnyNonzero<Args::value...>;
```

## Links

- [Source code](../../../../conceptrodon/omennivore/concepts/any_peg_nonzero.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/any_peg_nonzero.test.hpp)
