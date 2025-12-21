<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::AnyZero`

<p style='text-align: right;'><a href="../../concepts.md#typelivore-any-zero">To Index</a></p>

## Description

`Typelivore::AnyZero` accepts a list of elements.
It returns true if there exists an element whose value result equals `0` and returns false if otherwise.

<pre><code>   Es...
-> (...||(Es::value == 0))</code></pre>

## Structure

```C++
template<typename...>
concept AnyZero = REQUIREMENT;
```

## Implementation

```C++
template<typename...Args>
concept JustAnyZero = Varybivore::AnyZero<Args::value...>;

template<typename...Args>
concept AnyZero
=   Omennivore::AllValuable<Args...>
&&  JustAnyZero<Args...>;
```

## Links

- [Source code](../../../../conceptrodon/concepts/typelivore/any_zero.hpp)
- [Unit test](../../../../tests/unit/concepts/typelivore/any_zero.test.hpp)
