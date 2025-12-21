<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AllNonzero`

<p style='text-align: right;'><a href="../../concepts.md#varybivore-all-nonzero">To Index</a></p>

## Description

`Varybivore::AllNonzero` accepts a list of variables.
It returns true if no variable equals `0` and returns false if otherwise.

<pre><code>   Vs...
-> (...&&(Vs != 0))</code></pre>

## Structure

```C++
template<auto...>
concept AllNonzero = REQUIREMENT;
```

## Implementation

```C++
template<auto...Args>
concept AllNonzero = (...&&(Args != 0));
```

## Links

- [Source code](../../../../conceptrodon/metafunctions/varybivore/concepts/all_nonzero.hpp)
- [Unit test](../../../../tests/unit/concepts/varybivore/all_nonzero.test.hpp)
