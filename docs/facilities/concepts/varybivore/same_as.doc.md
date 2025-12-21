<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::SameAs`

<p style='text-align: right;'><a href="../../concepts.md#varybivore-same-as">To Index</a></p>

## Description

`Varybivore::SameAs` accepts two variables.
It returns true if two variables are the same and returns false if otherwise.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>
-> V<sub>0</sub> `same as` V<sub>1</sub></code></pre>

## Structure

```C++
template<auto, auto>
concept SameAs = REQUIREMENT;
```

## Implementation

```C++
template<auto LeftSide, auto RightSide>
concept SameAs
=   Pagelivore::Clarify<IsSame, LeftSide, RightSide>
&&  Pagelivore::Clarify<IsSame, RightSide, LeftSide>;
```

## Links

- [Source code](../../../../conceptrodon/metafunctions/varybivore/concepts/same_as.hpp)
- [Unit test](../../../../tests/unit/concepts/varybivore/same_as.test.hpp)
