<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::GreaterThan`

<p style='text-align: right;'><a href="../../concepts.md#varybivore-greater-than">To Index</a></p>

## Description

`Varybivore::GreaterThan` accepts two variables.
It returns true if the first variable is greater than the second and returns false if otherwise.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>
-> V<sub>0</sub> > V<sub>1</sub></code></pre>

## Structure

```C++
template<auto, auto>
concept GreaterThan = REQUIREMENT;
```

## Implementation

```C++
template<auto LeftSide, auto RightSide>
concept GreaterThan = LessThan<RightSide, LeftSide>;
```

## Links

- [Source code](../../../../conceptrodon/concepts/varybivore/greater_than.hpp)
- [Unit test](../../../../tests/unit/concepts/varybivore/greater_than.test.hpp)
