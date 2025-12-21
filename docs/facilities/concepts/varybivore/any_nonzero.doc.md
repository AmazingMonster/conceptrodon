<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AnyNonzero`

<p style='text-align: right;'><a href="../../concepts.md#varybivore-any-nonzero">To Index</a></p>

## Description

`Varybivore::AnyNonzero` accepts a list of variables.
It returns true if there exists a variable that does not equal `0` and returns false if otherwise.

<pre><code>   Vs...
-> (...||(V != 0))</code></pre>

## Structure

```C++
template<auto...>
concept AnyNonzero = REQUIREMENT;
```

## Implementation

```C++
template<auto...Args>
concept JustAnyNonzero = (...||(Args != 0));

template<auto...Args>
concept AnyNonzero
=   JustAnyNonzero<Args...>
||  AllNonzero<Args...>;
```

## Links

- [Source code](../../../../conceptrodon/concepts/varybivore/any_nonzero.hpp)
- [Unit test](../../../../tests/unit/concepts/varybivore/any_nonzero.test.hpp)
