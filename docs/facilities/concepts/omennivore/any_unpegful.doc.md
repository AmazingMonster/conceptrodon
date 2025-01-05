<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::AnyUnpegful`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-any-unpegful">To Index</a></p>

## Description

`Omennivore::AnyUnpegful` accepts a list of classes.
It returns true if there exists a class whose underlying template is not a `Peg` and returns false if otherwise.

## Structure

```C++
template<typename...>
concept AnyUnpegful = REQUIREMENT;
```

## Implementation

```C++
template<typename...Args>
concept AnyUnpegful
=   Mouldivore::AnyDeceive<Pagelivore::IsSpecializationOf<Peg>::ProtoMold, Args...>
||  AllUnpegful<Args...>;
```

## Links

- [Source code](../../../../conceptrodon/omennivore/concepts/any_unpegful.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/any_unpegful.test.hpp)
