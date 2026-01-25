<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::FalseProbe`

<p style='text-align: right;'><a href="../../concepts.md#varybivore-false-probe">To Index</a></p>

## Description

`Varybivore::FalseProbe` accepts a variable.
It returns true if the variable can be converted to `false` and returns false if otherwise.

<pre><code>   V
-> bool(V) == false</code></pre>

## Structure

```C++
template<typename>
concept FalseProbe = REQUIREMENT;
```

## Implementation

```C++
template<auto Variable>
concept FalseProbe = not static_cast<bool>(Variable);
```

## Links

- [Source code](../../../../conceptrodon/concepts/varybivore/false_probe.hpp)
- [Unit test](../../../../tests/unit/concepts/varybivore/false_probe.test.hpp)
