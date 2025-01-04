<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::NegativeOne`

<p style='text-align: right;'><a href="../../concepts.md#typelivore-negative-one">To Index</a></p>

## Description

`Typelivore::NegativeOne` accepts an element.
It returns true if the value result of the element equals `-1` and returns false if otherwise.

<pre><code>   E
-> E::value == -1</code></pre>

## Structure

```C++
template<typename>
concept NegativeOne = REQUIREMENT;
```

## Implementation

```C++
template<typename Arg>
concept JustNegativeOne = Varybivore::EqualTo<Arg::value, -1>;

template<typename Arg>
concept NegativeOne
=   Omennivore::Valuable<Arg>
&&  JustNegativeOne<Arg>;
```

## Links

- [Source code](../../../../conceptrodon/descend/typelivore/concepts/negative_one.hpp)
- [Unit test](../../../../tests/unit/concepts/typelivore/negative_one.test.hpp)
