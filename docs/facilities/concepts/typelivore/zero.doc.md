<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Zero`

<p style='text-align: right;'><a href="../../concepts.md#typelivore-zero">To Index</a></p>

## Description

`Typelivore::Zero` accepts an element.
It returns true if the value result of the element equals `0` and returns false if otherwise.

<pre><code>   E
-> E::value == 0</code></pre>

## Structure

```C++
template<typename>
concept Zero = REQUIREMENT;
```

## Implementation

```C++
template<typename Arg>
concept JustZero = Varybivore::EqualTo<Arg::value, 0>;

template<typename Arg>
concept Zero
=   Omennivore::Valuable<Arg>
&&  JustZero<Arg>;
```

## Links

- [Source code](../../../../conceptrodon/typelivore/concepts/zero.hpp)
- [Unit test](../../../../tests/unit/concepts/typelivore/zero.test.hpp)
