<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::AllGlowful`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-all-glowful">To Index</a></p>

## Description

`Omennivore::AllGlowful` accepts a list of packed vessels.
It returns true if all of the underlying vessels are `Glow`s.

## Structure

```C++
template<typename...>
concept AllGlowful = REQUIREMENT;
```

## Implementation

```C++
template<typename...Args>
concept AllGlowful = Mouldivore::AllConfess<IsGlowful, Args...>;
```

## Links

- [Source code](../../../../conceptrodon/metafunctions/omennivore/concepts/all_glowful.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/all_glowful.test.hpp)
