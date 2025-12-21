<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::BoundedByClosedInterval`

<p style='text-align: right;'><a href="../../concepts.md#typelivore-bounded-by-closed-interval">To Index</a></p>

## Description

`Typelivore::BoundedByClosedInterval` accepts an element and two variables.
It returns true if the value result of the element is bounded by the closed interval indicated by the variables.

<pre><code>   E, V<sub>0</sub>, V<sub>1</sub>
-> V<sub>0</sub> &leq; E::value &leq; V<sub>1</sub></code></pre>

## Structure

```C++
template<typename, auto, auto>
concept BoundedByClosedInterval = REQUIREMENT;
```

## Implementation

```C++
template<typename Element, auto LowerBound, auto UpperBound>
concept JustBoundedByClosedInterval
=   Varybivore::NoGreaterThan<LowerBound, Element::value>
&&  Varybivore::NoGreaterThan<Element::value, UpperBound>;

template<typename Element, auto LowerBound, auto UpperBound>
concept BoundedByClosedInterval
=   Omennivore::Valuable<Element> 
&&  JustBoundedByClosedInterval<Element, LowerBound, UpperBound>;
```

## Links

- [Source code](../../../../conceptrodon/concepts/typelivore/bounded_by_closed_interval.hpp)
- [Unit test](../../../../tests/unit/concepts/typelivore/bounded_by_closed_interval.test.hpp)
