<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::BoundedByOpenInterval`

<p style='text-align: right;'><a href="../../concepts.md#typelivore-bounded-by-open-interval">To Index</a></p>

## Description

`Typelivore::BoundedByOpenInterval` accepts an element and two variables.
It returns true if the value result of the element is bounded by the open interval indicated by the variables.

<pre><code>   E, V<sub>0</sub>, V<sub>1</sub>
-> V<sub>0</sub> &lt; E::value &lt; V<sub>1</sub></code></pre>

## Structure

```C++
template<typename, auto, auto>
concept BoundedByOpenInterval = REQUIREMENT;
```

## Implementation

```C++
template<typename Element, auto LowerBound, auto UpperBound>
concept JustBoundedByOpenInterval
=   Varybivore::NoGreaterThan<LowerBound, Element::value>
&&  Varybivore::NoGreaterThan<Element::value, UpperBound>;

template<typename Element, auto LowerBound, auto UpperBound>
concept BoundedByOpenInterval
=   Omennivore::Valuable<Element> 
&&  JustBoundedByOpenInterval<Element, LowerBound, UpperBound>;
```

## Links

- [Source code](../../../../conceptrodon/concepts/typelivore/bounded_by_open_interval.hpp)
- [Unit test](../../../../tests/unit/concepts/typelivore/bounded_by_open_interval.test.hpp)
