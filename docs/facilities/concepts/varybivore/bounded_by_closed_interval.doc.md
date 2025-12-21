<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::BoundedByClosedInterval`

<p style='text-align: right;'><a href="../../concepts.md#varybivore-bounded-by-closed-interval">To Index</a></p>

## Description

`Varybivore::BoundedByClosedInterval` accepts three variables.
It returns true if the first variable is bounded by the closed interval indicated by the other two variables.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, V<sub>2</sub>
-> V<sub>1</sub> &leq; V<sub>0</sub> &leq; V<sub>2</sub></code></pre>

## Structure

```C++
template<auto, auto, auto>
concept BoundedByClosedInterval = REQUIREMENT;
```

## Implementation

```C++
template<auto Variable, auto LowerBound, auto UpperBound>
concept BoundedByClosedInterval 
=   NoGreaterThan<LowerBound, Variable>
&&  NoGreaterThan<Variable, UpperBound>;
```

## Links

- [Source code](../../../../conceptrodon/concepts/varybivore/bounded_by_closed_interval.hpp)
- [Unit test](../../../../tests/unit/concepts/varybivore/bounded_by_closed_interval.test.hpp)
