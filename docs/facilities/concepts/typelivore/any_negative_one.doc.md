<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::AnyNegativeOne`

<p style='text-align: right;'><a href="../../concepts.md#typelivore-any-negative-one">To Index</a></p>

## Description

`Typelivore::AnyNegativeOne` accepts a list of elements.
It returns true if there exists an element whose value result equals `-1` and returns false if otherwise.

<pre><code>   Es...
-> (...||(Es::value == -1))</code></pre>

## Structure

```C++
template<typename...>
concept AnyNegativeOne = REQUIREMENT;
```

## Implementation

```C++
template<typename...Args>
concept JustAnyNegativeOne = Varybivore::AnyNegativeOne<Args::value...>;

template<typename...Args>
concept AnyNegativeOne
=   Omennivore::AllValuable<Args...>
&&  JustAnyNegativeOne<Args...>;
```

## Links

- [Source code](../../../../conceptrodon/concepts/typelivore/any_negative_one.hpp)
- [Unit test](../../../../tests/unit/concepts/typelivore/any_negative_one.test.hpp)
