<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::EqualTo`

<p style='text-align: right;'><a href="../../concepts.md#varybivore-equal-to">To Index</a></p>

## Description

`Varybivore::EqualTo` accepts two variables.
It returns true if two variables are not equal and returns false if otherwise.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>
-> V<sub>0</sub> != V<sub>1</sub></code></pre>

## Structure

```C++
template<auto, auto>
concept UnequalTo = REQUIREMENT;
```

## Implementation

```C++
template<auto LeftSide, auto RightSide>
concept UnequalTo
=   LessThan<LeftSide, RightSide>
||  LessThan<RightSide, LeftSide>;
```

## Links

- [Source code](../../../../conceptrodon/concepts/varybivore/unequal_to.hpp)
- [Unit test](../../../../tests/unit/concepts/varybivore/unequal_to.test.hpp)
