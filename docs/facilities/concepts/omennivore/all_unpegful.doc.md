<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::AllUnpegful`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-all-unpegful">To Index</a></p>

## Description

`Omennivore::AllUnpegful` accepts a list of classes.
It returns true if none of the underlying templates of the classes is a `Peg` and returns false if otherwise.

## Structure

```C++
template<typename...>
concept AllUnpegful = REQUIREMENT;
```

## Implementation

```C++
template<typename...Args>
concept AllUnpegful
= Mouldivore::AllDeceive<Pagelivore::IsSpecializationOf<Peg>::ProtoMold, Args...>;
```

## Links

- [Source code](../../../../conceptrodon/concepts/omennivore/all_unpegful.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/all_unpegful.test.hpp)
