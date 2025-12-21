<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::Snowful`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-snowful">To Index</a></p>

## Description

`Omennivore::Snowful` accepts a packed vessel.
It returns true if the underlying vessel is a `Snow`.

## Structure

```C++
template<typename>
concept Snowful = REQUIREMENT;
```

## Implementation

```C++
template<typename Arg>
concept Snowful = Mouldivore::Confess<IsSnowful, Arg>;
```

## Links

- [Source code](../../../../conceptrodon/metafunctions/omennivore/concepts/snowful.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/snowful.test.hpp)
