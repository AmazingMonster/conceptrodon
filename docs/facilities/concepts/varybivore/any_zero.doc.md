<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AnyZero`

<p style='text-align: right;'><a href="../../concepts.md#varybivore-any-zero">To Index</a></p>

## Description

`Varybivore::AnyZero` accepts a list of variables.
It returns true if there exists a variable equal to `0` and returns false if otherwise.

<pre><code>   Vs...
-> (...||(V == 0))</code></pre>

## Structure

```C++
template<auto...>
concept AnyZero = REQUIREMENT;
```

## Implementation

```C++
template<auto...Args>
concept JustAnyZero = (...||(Args == 0));

template<auto...Args>
concept AnyZero
=   JustAnyZero<Args...>
||  AllZero<Args...>;
```

## Links

- [Source code](../../../../conceptrodon/concepts/varybivore/any_zero.hpp)
- [Unit test](../../../../tests/unit/concepts/varybivore/any_zero.test.hpp)
