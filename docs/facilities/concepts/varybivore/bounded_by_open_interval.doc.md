<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::BoundedByOpenInterval`

<p style='text-align: right;'><a href="../../concepts.md#varybivore-bounded-by-open-interval">To Index</a></p>

## Description

`Varybivore::BoundedByOpenInterval` accepts three variables.
It returns true if the first variable is bounded by the open interval indicated by the other two variables.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, V<sub>2</sub>
-> V<sub>1</sub> &lt; V<sub>0</sub> &lt; V<sub>2</sub></code></pre>

## Structure

```C++
template<auto, auto, auto>
concept BoundedByOpenInterval = REQUIREMENT;
```

## Implementation

```C++
template<auto Variable, auto LowerBound, auto UpperBound>
concept BoundedByOpenInterval 
=   LessThan<LowerBound, Variable>
&&  LessThan<Variable, UpperBound>;
```

## Links

- [Source code](../../../../conceptrodon/concepts/varybivore/bounded_by_open_interval.hpp)
- [Unit test](../../../../tests/unit/concepts/varybivore/bounded_by_open_interval.test.hpp)
