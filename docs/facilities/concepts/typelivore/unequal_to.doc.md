<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::UnequalTo`

<p style='text-align: right;'><a href="../../concepts.md#typelivore-unequal-to">To Index</a></p>

## Description

`Typelivore::UnequalTo` accepts an element and a variable.
It returns true if the value result of the element does not equal the variable and returns false if otherwise.

<pre><code>   E, V
-> E::value != V</code></pre>

## Structure

```C++
template<typename, auto>
concept UnequalTo = REQUIREMENT;
```

## Implementation

```C++
template<typename LeftSide, auto RightSide>
concept JustUnequalTo
=   Varybivore::LessThan<LeftSide::value, RightSide>
||  Varybivore::LessThan<RightSide, LeftSide::value>;

template<typename LeftSide, auto RightSide>
concept UnequalTo
=   Omennivore::Valuable<LeftSide>
&&  JustUnequalTo<LeftSide, RightSide>;
```

## Links

- [Source code](../../../../conceptrodon/concepts/typelivore/unequal_to.hpp)
- [Unit test](../../../../tests/unit/concepts/typelivore/unequal_to.test.hpp)
