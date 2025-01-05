<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::AllPegful`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-all-pegful">To Index</a></p>

## Description

`Omennivore::AllPegful` accepts a list of classes.
It returns true if the underlying template of every class is a `Peg` and returns false if otherwise.

## Structure

```C++
template<typename...>
concept AllPegful = REQUIREMENT;
```

## Implementation

```C++
template<typename...Args>
concept AllPegful
= Mouldivore::AllConfess<Pagelivore::IsSpecializationOf<Peg>::ProtoMold, Args...>;
```

## Links

- [Source code](../../../../conceptrodon/descend/omennivore/concepts/all_pegful.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/all_pegful.test.hpp)
