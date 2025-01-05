<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::LessThan`

<p style='text-align: right;'><a href="../../concepts.md#typelivore-less-than">To Index</a></p>

## Description

`Typelivore::LessThan` accepts an element and a variable.
It returns true if the value result of the element is less than the variable and returns false if otherwise.

<pre><code>   E, V
-> E::value &lt; V</code></pre>

## Structure

```C++
template<typename, auto>
concept LessThan = REQUIREMENT;
```

## Implementation

```C++
template<typename LeftSide, auto RightSide>
concept JustLessThan = Varybivore::LessThan<LeftSide::value, RightSide>;

template<typename LeftSide, auto RightSide>
concept LessThan
=   Omennivore::Valuable<LeftSide>
&&  JustLessThan<LeftSide, RightSide>;
```

## Links

- [Source code](../../../../conceptrodon/typelivore/concepts/less_than.hpp)
- [Unit test](../../../../tests/unit/concepts/typelivore/less_than.test.hpp)
