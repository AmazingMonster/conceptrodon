<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::GreaterThan`

<p style='text-align: right;'><a href="../../concepts.md#typelivore-greater-than">To Index</a></p>

## Description

`Typelivore::GreaterThan` accepts an element and a variable.
It returns true if the value result of the element is greater than the variable and returns false if otherwise.

<pre><code>   E, V
-> E::value &gt; V</code></pre>

## Structure

```C++
template<typename, auto>
concept GreaterThan = REQUIREMENT;
```

## Implementation

```C++
template<typename LeftSide, auto RightSide>
concept JustGreaterThan = Varybivore::LessThan<RightSide, LeftSide::value>;

template<typename LeftSide, auto RightSide>
concept GreaterThan
=   Omennivore::Valuable<LeftSide>
&&  JustGreaterThan<LeftSide, RightSide>;
```

## Links

- [Source code](../../../../conceptrodon/typelivore/concepts/greater_than.hpp)
- [Unit test](../../../../tests/unit/concepts/typelivore/greater_than.test.hpp)
