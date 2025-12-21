<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::NegativeOne`

<p style='text-align: right;'><a href="../../concepts.md#varybivore-negative-one">To Index</a></p>

## Description

`Varybivore::NegativeOne` accepts a variable.
It returns true if the variable equals `-1` and returns false if otherwise.

<pre><code>   V
-> V == -1</code></pre>

## Structure

```C++
template<auto>
concept NegativeOne = REQUIREMENT;
```

## Implementation

```C++
template<auto Arg>
concept NegativeOne = EqualTo<Arg, -1>;
```

## Links

- [Source code](../../../../conceptrodon/metafunctions/varybivore/concepts/negative_one.hpp)
- [Unit test](../../../../tests/unit/concepts/varybivore/negative_one.test.hpp)
