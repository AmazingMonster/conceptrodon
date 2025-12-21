<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::AnyPegful`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-any-pegful">To Index</a></p>

## Description

`Omennivore::AnyPegful` accepts a list of classes.
It returns true if there exists a class whose underlying template is a `Peg` and returns false if otherwise.

## Structure

```C++
template<typename...>
concept AnyPegful = REQUIREMENT;
```

## Implementation

```C++
template<typename...Args>
concept AnyPegful
=   Mouldivore::AnyConfess<Pagelivore::IsSpecializationOf<Peg>::ProtoMold, Args...>
||  AllPegful<Args...>;
```

## Links

- [Source code](../../../../conceptrodon/concepts/omennivore/any_pegful.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/any_pegful.test.hpp)
