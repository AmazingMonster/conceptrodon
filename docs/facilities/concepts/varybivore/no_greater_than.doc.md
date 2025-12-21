<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::NoGreaterThan`

<p style='text-align: right;'><a href="../../concepts.md#varybivore-no-greater-than">To Index</a></p>

## Description

`Varybivore::NoGreaterThan` accepts two variables.
It returns true if the first variable is not greater than the second and returns false if otherwise.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>
-> V<sub>0</sub> &leq; V<sub>1</sub></code></pre>

## Structure

```C++
template<auto, auto>
concept NoGreaterThan = REQUIREMENT;
```

## Implementation

```C++
template<auto LeftSide, auto RightSide>
concept NoGreaterThan
=   LessThan<LeftSide, RightSide>
||  EqualTo<LeftSide, RightSide>;
```

## Links

- [Source code](../../../../conceptrodon/metafunctions/varybivore/concepts/no_greater_than.hpp)
- [Unit test](../../../../tests/unit/concepts/varybivore/no_greater_than.test.hpp)
