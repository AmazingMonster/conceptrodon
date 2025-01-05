<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::Moldful`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-moldful">To Index</a></p>

## Description

`Omennivore::Moldful` accepts a packed vessel.
It returns true if the underlying vessel is a `Mold`.

## Structure

```C++
template<typename>
concept Moldful = REQUIREMENT;
```

## Implementation

```C++
template<typename Arg>
concept Moldful = Mouldivore::Confess<IsMoldful, Arg>;
```

## Links

- [Source code](../../../../conceptrodon/descend/omennivore/concepts/moldful.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/moldful.test.hpp)
