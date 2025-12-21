<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::NotNegativeOne`

<p style='text-align: right;'><a href="../../concepts.md#typelivore-not-negative-one">To Index</a></p>

## Description

`Typelivore::NotNegativeOne` accepts an element.
It returns true if the value result of the element does not equal `-1` and returns false if otherwise.

<pre><code>   E
-> E::value != -1</code></pre>

## Structure

```C++
template<typename>
concept NotNegativeOne = REQUIREMENT;
```

## Implementation

```C++
template<typename Arg>
concept JustNotNegativeOne = Varybivore::UnequalTo<Arg::value, -1>;

template<typename Arg>
concept NotNegativeOne
=   Omennivore::Valuable<Arg>
&&  JustNotNegativeOne<Arg>;
```

## Links

- [Source code](../../../../conceptrodon/concepts/typelivore/not_negative_one.hpp)
- [Unit test](../../../../tests/unit/concepts/typelivore/not_negative_one.test.hpp)
