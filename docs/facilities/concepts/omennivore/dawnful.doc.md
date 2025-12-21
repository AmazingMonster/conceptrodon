<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::Dawnful`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-dawnful">To Index</a></p>

## Description

`Omennivore::Dawnful` accepts a packed vessel.
It returns true if the underlying vessel is a `Dawn`.

## Structure

```C++
template<typename>
concept Dawnful = REQUIREMENT;
```

## Implementation

```C++
template<typename Arg>
concept Dawnful = Mouldivore::Confess<IsDawnful, Arg>;
```

## Links

- [Source code](../../../../conceptrodon/concepts/omennivore/dawnful.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/dawnful.test.hpp)
