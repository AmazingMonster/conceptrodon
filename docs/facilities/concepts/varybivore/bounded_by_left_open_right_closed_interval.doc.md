<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::BoundedByLeftOpenRightClosedInterval`

<p style='text-align: right;'><a href="../../concepts.md#varybivore-bounded-by-left-open-right-closed-interval">To Index</a></p>

## Description

`Varybivore::BoundedByLeftOpenRightClosedInterval` accepts three variables.
It returns true if the first variable is bounded by the left open right closed interval indicated by the other two variables.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, V<sub>2</sub>
-> V<sub>1</sub> &lt; V<sub>0</sub> &leq; V<sub>2</sub></code></pre>

## Structure

```C++
template<auto, auto, auto>
concept BoundedByLeftOpenRightClosedInterval = REQUIREMENT;
```

## Implementation

```C++
template<auto Variable, auto LowerBound, auto UpperBound>
concept BoundedByLeftOpenRightClosedInterval 
=   LessThan<LowerBound, Variable>
&&  NoGreaterThan<Variable, UpperBound>;
```

## Links

- [Source code](../../../../conceptrodon/varybivore/concepts/bounded_by_left_open_right_closed_interval.hpp)
- [Unit test](../../../../tests/unit/concepts/varybivore/bounded_by_left_open_right_closed_interval.test.hpp)
