<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AllZero`

<p style='text-align: right;'><a href="../../concepts.md#varybivore-all-zero">To Index</a></p>

## Description

`Varybivore::AllZero` accepts a list of variables.
It returns true if every variable equals `0` and returns false if otherwise.

<pre><code>   Vs...
-> (...&&(Vs == 0))</code></pre>

## Structure

```C++
template<auto...>
concept AllZero = REQUIREMENT;
```

## Implementation

```C++
template<auto...Args>
concept AllZero = (...&&(Args == 0));
```

## Links

- [Source code](../../../../conceptrodon/varybivore/concepts/all_zero.hpp)
- [Unit test](../../../../tests/unit/concepts/varybivore/all_zero.test.hpp)
