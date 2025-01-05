<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::AllNegativeOne`

<p style='text-align: right;'><a href="../../concepts.md#typelivore-all-negative-one">To Index</a></p>

## Description

`Typelivore::AllNegativeOne` accepts a list of elements.
It returns true if the value result of every element equals `-1` and returns false if otherwise.

<pre><code>   Es...
-> (...&&(Es::value == -1))</code></pre>

## Structure

```C++
template<typename...>
concept AllNegativeOne = REQUIREMENT;
```

## Implementation

```C++
template<typename...Args>
concept JustAllNegativeOne = Varybivore::AllNegativeOne<Args::value...>;

template<typename...Args>
concept AllNegativeOne
=   Omennivore::AllValuable<Args...>
&&  JustAllNegativeOne<Args...>;
```

## Links

- [Source code](../../../../conceptrodon/descend/typelivore/concepts/all_negative_one.hpp)
- [Unit test](../../../../tests/unit/concepts/typelivore/all_negative_one.test.hpp)
