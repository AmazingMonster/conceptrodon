<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::FalseProbe`

<p style='text-align: right;'><a href="../../concepts.md#typelivore-false-probe">To Index</a></p>

## Description

`Typelivore::FalseProbe` accepts an element.
It returns true if the value result of the element can be converted to `false` and returns false if otherwise.

<pre><code>   E
-> bool(E::value) == false</code></pre>

## Structure

```C++
template<typename>
concept FalseProbe = REQUIREMENT;
```

## Implementation

```C++
template<typename Element>
concept FalseProbe = not static_cast<bool>(Element::value);
```

## Links

- [Source code](../../../../conceptrodon/concepts/typelivore/false_probe.hpp)
- [Unit test](../../../../tests/unit/concepts/typelivore/false_probe.test.hpp)
