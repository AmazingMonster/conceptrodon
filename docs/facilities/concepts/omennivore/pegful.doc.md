<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::Pegful`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-pegful">To Index</a></p>

## Description

`Omennivore::Pegful` accepts a class.
It returns true if the underlying template of the class is a `Peg` and returns false if otherwise.

## Structure

```C++
template<typename>
concept Pegful = REQUIREMENT;
```

## Implementation

```C++
template<typename Arg>
concept Pegful
= Mouldivore::Confess<Pagelivore::IsSpecializationOf<Peg>::ProtoMold, Arg>;
```

## Links

- [Source code](../../../../conceptrodon/metafunctions/omennivore/concepts/pegful.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/pegful.test.hpp)
