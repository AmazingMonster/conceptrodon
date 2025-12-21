<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::EqualTo`

<p style='text-align: right;'><a href="../../concepts.md#typelivore-equal-to">To Index</a></p>

## Description

`Typelivore::EqualTo` accepts an element and a variable.
It returns true if the value result of the element equals the variable and returns false if otherwise.

<pre><code>   E, V
-> E::value == V</code></pre>

## Structure

```C++
template<typename, auto>
concept EqualTo = REQUIREMENT;
```

## Implementation

```C++
template<typename LeftSide, auto RightSide>
concept JustEqualTo = Varybivore::EqualTo<LeftSide::value, RightSide>;

template<typename LeftSide, auto RightSide>
concept EqualTo
=   Omennivore::Valuable<LeftSide>
&&  JustEqualTo<LeftSide, RightSide>;
```

## Links

- [Source code](../../../../conceptrodon/concepts/typelivore/equal_to.hpp)
- [Unit test](../../../../tests/unit/concepts/typelivore/equal_to.test.hpp)
