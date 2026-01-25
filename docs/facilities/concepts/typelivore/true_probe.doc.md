<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::TrueProbe`

<p style='text-align: right;'><a href="../../concepts.md#typelivore-true-probe">To Index</a></p>

## Description

`Typelivore::TrueProbe` accepts an element.
It returns true if the value result of the element can be converted to `true` and returns false if otherwise.

<pre><code>   E
-> bool(E::value) == true</code></pre>

## Structure

```C++
template<typename>
concept TrueProbe = REQUIREMENT;
```

## Implementation

```C++
template<typename Element>
concept TrueProbe = static_cast<bool>(Element::value);
```

## Links

- [Source code](../../../../conceptrodon/concepts/typelivore/true_probe.hpp)
- [Unit test](../../../../tests/unit/concepts/typelivore/true_probe.test.hpp)
