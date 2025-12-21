<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Nonzero`

<p style='text-align: right;'><a href="../../concepts.md#varybivore-nonzero">To Index</a></p>

## Description

`Varybivore::Nonzero` accepts a variable.
It returns true if the variable does not equal zero and returns false if otherwise.

<pre><code>   V
-> V != 0</code></pre>

## Structure

```C++
template<auto>
concept Nonzero = REQUIREMENT;
```

## Implementation

```C++
template<auto Arg>
concept Nonzero = UnequalTo<Arg, 0>;
```

## Links

- [Source code](../../../../conceptrodon/metafunctions/varybivore/concepts/nonzero.hpp)
- [Unit test](../../../../tests/unit/concepts/varybivore/nonzero.test.hpp)
