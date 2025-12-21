<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::Willful`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-willful">To Index</a></p>

## Description

`Omennivore::Willful` accepts a packed vessel.
It returns true if the underlying vessel is a `Will`.

## Structure

```C++
template<typename>
concept Willful = REQUIREMENT;
```

## Implementation

```C++
template<typename Arg>
concept Willful = Mouldivore::Confess<IsWillful, Arg>;
```

## Links

- [Source code](../../../../conceptrodon/concepts/omennivore/willful.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/willful.test.hpp)
