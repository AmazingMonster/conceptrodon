<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::LessThan`

<p style='text-align: right;'><a href="../../concepts.md#varybivore-less-than">To Index</a></p>

## Description

`Varybivore::LessThan` accepts two variables.
It returns true if the first variable is less than the second and returns false if otherwise.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>
-> V<sub>0</sub> < V<sub>1</sub></code></pre>

## Structure

```C++
template<auto, auto>
concept LessThan = REQUIREMENT;
```

## Implementation

```C++
template<auto LeftSide, auto RightSide>
concept LessThan = LeftSide < RightSide;
```

## Links

- [Source code](../../../../conceptrodon/metafunctions/varybivore/concepts/less_than.hpp)
- [Unit test](../../../../tests/unit/concepts/varybivore/less_than.test.hpp)
