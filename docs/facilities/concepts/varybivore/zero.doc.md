<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Zero`

<p style='text-align: right;'><a href="../../concepts.md#varybivore-zero">To Index</a></p>

## Description

`Varybivore::Zero` accepts a variable.
It returns true if the variable equals zero and returns false if otherwise.

<pre><code>   V
-> V == 0</code></pre>

## Structure

```C++
template<auto>
concept Zero = REQUIREMENT;
```

## Implementation

```C++
template<auto Arg>
concept Zero = EqualTo<Arg, 0>;
```

## Links

- [Source code](../../../../conceptrodon/varybivore/concepts/zero.hpp)
- [Unit test](../../../../tests/unit/concepts/varybivore/zero.test.hpp)
