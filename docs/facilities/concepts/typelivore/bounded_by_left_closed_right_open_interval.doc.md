<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::BoundedByLeftClosedRightOpenInterval`

<p style='text-align: right;'><a href="../../concepts.md#typelivore-bounded-by-left-closed-right-open-interval">To Index</a></p>

## Description

`Typelivore::BoundedByLeftClosedRightOpenInterval` accepts an element and two variables.
It returns true if the value result of the element is bounded by the left closed right open interval indicated by the variables.

<pre><code>   E, V<sub>0</sub>, V<sub>1</sub>
-> V<sub>0</sub> &leq; E::value &lt; V<sub>1</sub></code></pre>

## Structure

```C++
template<typename, auto, auto>
concept BoundedByLeftClosedRightOpenInterval = REQUIREMENT;
```

## Implementation

```C++
template<typename Element, auto LowerBound, auto UpperBound>
concept JustBoundedByLeftClosedRightOpenInterval
=   Varybivore::NoGreaterThan<LowerBound, Element::value>
&&  Varybivore::LessThan<Element::value, UpperBound>;

template<typename Element, auto LowerBound, auto UpperBound>
concept BoundedByLeftClosedRightOpenInterval
=   Omennivore::Valuable<Element> 
&&  JustBoundedByLeftClosedRightOpenInterval<Element, LowerBound, UpperBound>;
```

## Links

- [Source code](../../../../conceptrodon/metafunctions/typelivore/concepts/bounded_by_left_closed_right_open_interval.hpp)
- [Unit test](../../../../tests/unit/concepts/typelivore/bounded_by_left_closed_right_open_interval.test.hpp)
