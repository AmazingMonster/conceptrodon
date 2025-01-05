<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::BoundedByLeftOpenRightClosedInterval`

<p style='text-align: right;'><a href="../../concepts.md#typelivore-bounded-by-left-open-right-closed-interval">To Index</a></p>

## Description

`Typelivore::BoundedByLeftOpenRightClosedInterval` accepts an element and two variables.
It returns true if the value result of the element is bounded by the left open right closed interval indicated by the variables.

<pre><code>   E, V<sub>0</sub>, V<sub>1</sub>
-> V<sub>0</sub> &lt; E::value &leq; V<sub>1</sub></code></pre>

## Structure

```C++
template<typename, auto, auto>
concept BoundedByLeftOpenRightClosedInterval = REQUIREMENT;
```

## Implementation

```C++
template<typename Element, auto LowerBound, auto UpperBound>
concept JustBoundedByLeftOpenRightClosedInterval
=   Varybivore::LessThan<LowerBound, Element::value>
&&  Varybivore::NoGreaterThan<Element::value, UpperBound>;

template<typename Element, auto LowerBound, auto UpperBound>
concept BoundedByLeftOpenRightClosedInterval
=   Omennivore::Valuable<Element> 
&&  JustBoundedByLeftOpenRightClosedInterval<Element, LowerBound, UpperBound>;
```

## Links

- [Source code](../../../../conceptrodon/descend/typelivore/concepts/bounded_by_left_open_right_closed_interval.hpp)
- [Unit test](../../../../tests/unit/concepts/typelivore/bounded_by_left_open_right_closed_interval.test.hpp)
