<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AllNegativeOne`

<p style='text-align: right;'><a href="../../concepts.md#varybivore-all-negative-one">To Index</a></p>

## Description

`Varybivore::AllNegativeOne` accepts a list of variables.
It returns true if every variable equals `-1` and returns false if otherwise.

<pre><code>   Vs...
-> (...&&(Vs == -1))</code></pre>

## Structure

```C++
template<auto...>
concept AllNegativeOne = REQUIREMENT;
```

## Implementation

```C++
template<auto...Args>
concept AllNegativeOne = (...&&(Args == -1));
```

## Links

- [Source code](../../../../conceptrodon/metafunctions/varybivore/concepts/all_negative_one.hpp)
- [Unit test](../../../../tests/unit/concepts/varybivore/all_negative_one.test.hpp)
