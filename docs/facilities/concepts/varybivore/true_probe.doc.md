<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::TrueProbe`

<p style='text-align: right;'><a href="../../concepts.md#varybivore-true-probe">To Index</a></p>

## Description

`Varybivore::TrueProbe` accepts a variable.
It returns true if the variable can be converted to `true` and returns false if otherwise.

<pre><code>   V
-> bool(V) == true</code></pre>

## Structure

```C++
template<typename>
concept TrueProbe = REQUIREMENT;
```

## Implementation

```C++
template<auto Variable>
concept TrueProbe = static_cast<bool>(Variable);
```

## Links

- [Source code](../../../../conceptrodon/concepts/varybivore/true_probe.hpp)
- [Unit test](../../../../tests/unit/concepts/varybivore/true_probe.test.hpp)
