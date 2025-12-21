<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Nonzero`

<p style='text-align: right;'><a href="../../concepts.md#typelivore-nonzero">To Index</a></p>

## Description

`Typelivore::Nonzero` accepts an element.
It returns true if the value result of the element does not equal zero and returns false if otherwise.

<pre><code>   E
-> E::value != 0</code></pre>

## Structure

```C++
template<typename>
concept Nonzero = REQUIREMENT;
```

## Implementation

```C++
template<typename Arg>
concept JustNonzero = Varybivore::UnequalTo<Arg::value, 0>;

template<typename Arg>
concept Nonzero
=   Omennivore::Valuable<Arg>
&&  JustNonzero<Arg>;
```

## Links

- [Source code](../../../../conceptrodon/concepts/typelivore/nonzero.hpp)
- [Unit test](../../../../tests/unit/concepts/typelivore/nonzero.test.hpp)
