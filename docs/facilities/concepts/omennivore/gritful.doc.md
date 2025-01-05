<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::Gritful`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-gritful">To Index</a></p>

## Description

`Omennivore::Gritful` accepts a packed vessel.
It returns true if the underlying vessel is a `Grit`.

## Structure

```C++
template<typename>
concept Gritful = REQUIREMENT;
```

## Implementation

```C++
template<typename Arg>
concept Gritful = Mouldivore::Confess<IsGritful, Arg>;
```

## Links

- [Source code](../../../../conceptrodon/descend/omennivore/concepts/gritful.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/gritful.test.hpp)
