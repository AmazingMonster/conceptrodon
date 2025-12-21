<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::Glowful`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-glowful">To Index</a></p>

## Description

`Omennivore::Glowful` accepts a packed vessel.
It returns true if the underlying vessel is a `Glow`.

## Structure

```C++
template<typename>
concept Glowful = REQUIREMENT;
```

## Implementation

```C++
template<typename Arg>
concept Glowful = Mouldivore::Confess<IsGlowful, Arg>;
```

## Links

- [Source code](../../../../conceptrodon/concepts/omennivore/glowful.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/glowful.test.hpp)
