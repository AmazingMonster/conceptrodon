<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::Roadful`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-roadful">To Index</a></p>

## Description

`Omennivore::Roadful` accepts a packed vessel.
It returns true if the underlying vessel is a `Road`.

## Structure

```C++
template<typename>
concept Roadful = REQUIREMENT;
```

## Implementation

```C++
template<typename Arg>
concept Roadful = Mouldivore::Confess<IsRoadful, Arg>;
```

## Links

- [Source code](../../../../conceptrodon/concepts/omennivore/roadful.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/roadful.test.hpp)
