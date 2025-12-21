<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AllNotNegativeOne`

<p style='text-align: right;'><a href="../../concepts.md#varybivore-all-not-negative-one">To Index</a></p>

## Description

`Varybivore::AllNotNegativeOne` accepts a list of variables.
It returns true if no variable equals `-1` and returns false if otherwise.

<pre><code>   Vs...
-> (...&&(Vs != -1))</code></pre>

## Structure

```C++
template<auto...>
concept AllNotNegativeOne = REQUIREMENT;
```

## Implementation

```C++
template<auto...Args>
concept AllNotNegativeOne = (...&&(Args != -1));
```

## Links

- [Source code](../../../../conceptrodon/metafunctions/varybivore/concepts/all_not_negative_one.hpp)
- [Unit test](../../../../tests/unit/concepts/varybivore/all_not_negative_one.test.hpp)
