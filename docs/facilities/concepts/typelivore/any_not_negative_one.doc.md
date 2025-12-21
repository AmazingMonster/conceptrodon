<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::AnyNotNegativeOne`

<p style='text-align: right;'><a href="../../concepts.md#typelivore-any-not-negative-one">To Index</a></p>

## Description

`Typelivore::AnyNotNegativeOne` accepts a list of elements.
It returns true if there exists an element whose value result does not equal `-1` and returns false if otherwise.

<pre><code>   Es...
-> (...||(Es::value != -1))</code></pre>

## Structure

```C++
template<typename...>
concept AnyNotNegativeOne = REQUIREMENT;
```

## Implementation

```C++
template<typename...Args>
concept JustAnyNotNegativeOne = Varybivore::AnyNotNegativeOne<Args::value...>;

template<typename...Args>
concept AnyNotNegativeOne
=   Omennivore::AllValuable<Args...>
&&  JustAnyNotNegativeOne<Args...>;
```

## Links

- [Source code](../../../../conceptrodon/metafunctions/typelivore/concepts/any_not_negative_one.hpp)
- [Unit test](../../../../tests/unit/concepts/typelivore/any_not_negative_one.test.hpp)
