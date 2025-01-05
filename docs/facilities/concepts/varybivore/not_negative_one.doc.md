<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::NotNegativeOne`

<p style='text-align: right;'><a href="../../concepts.md#varybivore-not-negative-one">To Index</a></p>

## Description

`Varybivore::NotNegativeOne` accepts a variable.
It returns true if the variable does not equal `-1` and returns false if otherwise.

<pre><code>   V
-> V != -1</code></pre>

## Structure

```C++
template<auto>
concept NotNegativeOne = REQUIREMENT;
```

## Implementation

```C++
template<auto Arg>
concept NotNegativeOne = UnequalTo<Arg, -1>;
```

## Links

- [Source code](../../../../conceptrodon/varybivore/concepts/descend/descend/not_negative_one.hpp)
- [Unit test](../../../../tests/unit/concepts/varybivore/not_negative_one.test.hpp)
