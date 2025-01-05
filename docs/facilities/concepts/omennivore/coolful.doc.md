<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::Coolful`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-coolful">To Index</a></p>

## Description

`Omennivore::Coolful` accepts a packed vessel.
It returns true if the underlying vessel is a `Cool`.

## Structure

```C++
template<typename>
concept Coolful = REQUIREMENT;
```

## Implementation

```C++
template<typename Arg>
concept Coolful = Mouldivore::Confess<IsCoolful, Arg>;
```

## Links

- [Source code](../../../../conceptrodon/descend/omennivore/concepts/coolful.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/coolful.test.hpp)
