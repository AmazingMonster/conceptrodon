<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::NoLessThan`

<p style='text-align: right;'><a href="../../concepts.md#varybivore-no-less-than">To Index</a></p>

## Description

`Varybivore::NoLessThan` accepts two variables.
It returns true if the first variable is not less than the second and returns false if otherwise.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>
-> V<sub>0</sub> &geq; V<sub>1</sub></code></pre>

## Structure

```C++
template<auto, auto>
concept NoLessThan = REQUIREMENT;
```

## Implementation

```C++
template<auto LeftSide, auto RightSide>
concept NoLessThan
=   LessThan<RightSide, LeftSide>
||  EqualTo<LeftSide, RightSide>;
```

## Links

- [Source code](../../../../conceptrodon/varybivore/concepts/descend/no_less_than.hpp)
- [Unit test](../../../../tests/unit/concepts/varybivore/no_less_than.test.hpp)
