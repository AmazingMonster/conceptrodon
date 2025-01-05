<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::Calmful`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-calmful">To Index</a></p>

## Description

`Omennivore::Calmful` accepts a packed vessel.
It returns true if the underlying vessel is a `Calm`.

## Structure

```C++
template<typename>
concept Calmful = REQUIREMENT;
```

## Implementation

```C++
template<typename Arg>
concept Calmful = Mouldivore::Confess<IsCalmful, Arg>;
```

## Links

- [Source code](../../../../conceptrodon/omennivore/concepts/calmful.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/calmful.test.hpp)
