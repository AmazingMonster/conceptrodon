<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::NoLessThan`

<p style='text-align: right;'><a href="../../concepts.md#typelivore-no-less-than">To Index</a></p>

## Description

`Typelivore::NoLessThan` accepts an element and a variable.
It returns true if the value result of the element is greater or equal to the variable and returns false if otherwise.

<pre><code>   E, V
-> E::value &geq; V</code></pre>

## Structure

```C++
template<typename, auto>
concept NoLessThan = REQUIREMENT;
```

## Implementation

```C++
template<typename LeftSide, auto RightSide>
concept JustNoLessThan
=   Varybivore::LessThan<RightSide, LeftSide::value>
||  Varybivore::EqualTo<LeftSide::value, RightSide>;

template<typename LeftSide, auto RightSide>
concept NoLessThan
=   Omennivore::Valuable<LeftSide>
&&  JustNoLessThan<LeftSide, RightSide>;
```

## Links

- [Source code](../../../../conceptrodon/metafunctions/typelivore/concepts/no_less_than.hpp)
- [Unit test](../../../../tests/unit/concepts/typelivore/no_less_than.test.hpp)
