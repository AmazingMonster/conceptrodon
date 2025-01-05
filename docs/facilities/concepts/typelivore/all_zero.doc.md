<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::AllZero`

<p style='text-align: right;'><a href="../../concepts.md#typelivore-all-zero">To Index</a></p>

## Description

`Typelivore::AllNegativeOne` accepts a list of elements.
It returns true if the value result of every element equals `-1` and returns false if otherwise.

<pre><code>   Es...
-> (...&&(Es::value == 0))</code></pre>

## Structure

```C++
template<typename...>
concept AllZero = REQUIREMENT;
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

- [Source code](../../../../conceptrodon/typelivore/concepts/all_zero.hpp)
- [Unit test](../../../../tests/unit/concepts/typelivore/all_zero.test.hpp)
