<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::AnyNonzero`

<p style='text-align: right;'><a href="../../concepts.md#typelivore-any-nonzero">To Index</a></p>

## Description

`Typelivore::AnyNonzero` accepts a list of elements.
It returns true if there exists an element whose value result does not equal `0` and returns false if otherwise.

<pre><code>   Es...
-> (...||(Es::value != 0))</code></pre>

## Structure

```C++
template<typename...>
concept AnyNonzero = REQUIREMENT;
```

## Implementation

```C++
template<typename...Args>
concept JustAnyNonzero = Varybivore::AnyNonzero<Args::value...>;

template<typename...Args>
concept AnyNonzero
=   Omennivore::AllValuable<Args...>
&&  JustAnyNonzero<Args...>;
```

## Links

- [Source code](../../../../conceptrodon/descend/typelivore/concepts/any_nonzero.hpp)
- [Unit test](../../../../tests/unit/concepts/typelivore/any_nonzero.test.hpp)
