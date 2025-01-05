<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::NoGreaterThan`

<p style='text-align: right;'><a href="../../concepts.md#typelivore-no-greater-than">To Index</a></p>

## Description

`Typelivore::NoGreaterThan` accepts an element and a variable.
It returns true if the value result of the element is less or equal to the variable and returns false if otherwise.

<pre><code>   E, V
-> E::value &leq; V</code></pre>

## Structure

```C++
template<typename, auto>
concept NoGreaterThan = REQUIREMENT;
```

## Implementation

```C++
template<typename LeftSide, auto RightSide>
concept JustNoGreaterThan
=   Varybivore::LessThan<LeftSide::value, RightSide>
||  Varybivore::EqualTo<LeftSide::value, RightSide>;

template<typename LeftSide, auto RightSide>
concept NoGreaterThan
=   Omennivore::Valuable<LeftSide>
&&  JustNoGreaterThan<LeftSide, RightSide>;
```

## Links

- [Source code](../../../../conceptrodon/descend/typelivore/concepts/no_greater_than.hpp)
- [Unit test](../../../../tests/unit/concepts/typelivore/no_greater_than.test.hpp)
