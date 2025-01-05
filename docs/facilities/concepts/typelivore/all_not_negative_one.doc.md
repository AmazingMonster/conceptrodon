<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::AllNotNegativeOne`

<p style='text-align: right;'><a href="../../concepts.md#typelivore-all-not-negative-one">To Index</a></p>

## Description

`Typelivore::AllNotNegativeOne` accepts a list of elements.
It returns true if no value result of an element equals `-1` and returns false if otherwise.

<pre><code>   Es...
-> (...&&(Es::value != -1))</code></pre>

## Structure

```C++
template<typename...>
concept AllNotNegativeOne = REQUIREMENT;
```

## Implementation

```C++
template<typename...Args>
concept JustAllZero = Varybivore::AllZero<Args::value...>;

template<typename...Args>
concept AllZero
=   Omennivore::AllValuable<Args...>
&&  JustAllZero<Args...>;
```

## Links

- [Source code](../../../../conceptrodon/typelivore/concepts/all_not_negative_one.hpp)
- [Unit test](../../../../tests/unit/concepts/typelivore/all_not_negative_one.test.hpp)
