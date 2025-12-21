<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::Unpegful`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-unpegful">To Index</a></p>

## Description

`Omennivore::Unpegful` accepts a class.
It returns true if the underlying template of the class is not a `Peg` and returns false if otherwise.

## Structure

```C++
template<typename>
concept Unpegful = REQUIREMENT;
```

## Implementation

```C++
template<typename Arg>
concept Unpegful
= Mouldivore::Deceive<Pagelivore::IsSpecializationOf<Peg>::ProtoMold, Arg>;
```

## Links

- [Source code](../../../../conceptrodon/concepts/omennivore/unpegful.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/unpegful.test.hpp)
