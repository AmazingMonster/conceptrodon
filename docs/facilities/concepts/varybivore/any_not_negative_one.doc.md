<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AnyNotNegativeOne`

<p style='text-align: right;'><a href="../../concepts.md#varybivore-any-not-negative-one">To Index</a></p>

## Description

`Varybivore::AnyNotNegativeOne` accepts a list of variables.
It returns true if there exists a variable that does not equal `-1` and returns false if otherwise.

<pre><code>   Vs...
-> (...||(V != -1))</code></pre>

## Structure

```C++
template<auto...>
concept AnyNotNegativeOne = REQUIREMENT;
```

## Implementation

```C++
template<auto...Args>
concept JustAnyNotNegativeOne = (...||(Args != -1));

template<auto...Args>
concept AnyNotNegativeOne
=   JustAnyNotNegativeOne<Args...>
||  AllNotNegativeOne<Args...>;
```

## Links

- [Source code](../../../../conceptrodon/metafunctions/varybivore/concepts/any_not_negative_one.hpp)
- [Unit test](../../../../tests/unit/concepts/varybivore/any_not_negative_one.test.hpp)
