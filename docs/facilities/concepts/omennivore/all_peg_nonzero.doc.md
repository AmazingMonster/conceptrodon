<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::AllPegNonzero`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-all-peg-nonzero">To Index</a></p>

## Description

`Omennivore::AllPegNonzero` accepts a list of classes.
It returns true if the underlying template of every class is a `Peg` and none of the value results are `0`. It returns false if otherwise.

## Structure

```C++
template<typename...>
concept AllPegNonzero = REQUIREMENT;
```

## Implementation

```C++
template<typename...Args>
concept AllPegNonzero
=   AllPegful<Args...>
&&  Varybivore::AllNonzero<Args::value...>;
```

## Links

- [Source code](../../../../conceptrodon/metafunctions/omennivore/concepts/all_peg_nonzero.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/all_peg_nonzero.test.hpp)
