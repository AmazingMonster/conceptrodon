<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::Pageful`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-pageful">To Index</a></p>

## Description

`Omennivore::Pageful` accepts a packed vessel.
It returns true if the underlying vessel is a `Page`.

## Structure

```C++
template<typename>
concept Pageful = REQUIREMENT;
```

## Implementation

```C++
template<typename Arg>
concept Pageful = Mouldivore::Confess<IsPageful, Arg>;
```

## Links

- [Source code](../../../../conceptrodon/concepts/omennivore/pageful.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/pageful.test.hpp)
