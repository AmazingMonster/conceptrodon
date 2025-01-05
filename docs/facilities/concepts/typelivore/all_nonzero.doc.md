<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::AllNonzero`

<p style='text-align: right;'><a href="../../concepts.md#typelivore-all-nonzero">To Index</a></p>

## Description

`Typelivore::AllNonzero` accepts a list of elements.
It returns true if no value result of an element equals `0` and returns false if otherwise.

<pre><code>   Es...
-> (...&&(Es::value != 0))</code></pre>

## Structure

```C++
template<typename...>
concept AllNonzero = REQUIREMENT;
```

## Implementation

```C++
template<typename...Args>
concept JustAllNonzero = Varybivore::AllNonzero<Args::value...>;

template<typename...Args>
concept AllNonzero
=   Omennivore::AllValuable<Args...>
&&  JustAllNonzero<Args...>;
```

## Links

- [Source code](../../../../conceptrodon/descend/typelivore/concepts/all_nonzero.hpp)
- [Unit test](../../../../tests/unit/concepts/typelivore/all_nonzero.test.hpp)
