<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AnyNegativeOne`

<p style='text-align: right;'><a href="../../concepts.md#varybivore-any-negative-one">To Index</a></p>

## Description

`Varybivore::AnyNegativeOne` accepts a list of variables.
It returns true if there exists a variable equal to `-1` and returns false if otherwise.

<pre><code>   Vs...
-> (...||(V == -1))</code></pre>

## Structure

```C++
template<auto...>
concept AnyNegativeOne = REQUIREMENT;
```

## Implementation

```C++
template<auto...Args>
concept JustAnyNegativeOne = (...||(Args == -1));

template<auto...Args>
concept AnyNegativeOne
=   JustAnyNegativeOne<Args...>
||  AllNegativeOne<Args...>;
```

## Links

- [Source code](../../../../conceptrodon/varybivore/concepts/any_negative_one.hpp)
- [Unit test](../../../../tests/unit/concepts/varybivore/any_negative_one.test.hpp)
