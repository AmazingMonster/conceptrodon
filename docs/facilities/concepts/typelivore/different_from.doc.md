<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::DifferentFrom`

<p style='text-align: right;'><a href="../../concepts.md#typelivore-different-from">To Index</a></p>

## Description

`Typelivore::DifferentFrom` accepts two elements.
It returns true if two elements are different and returns false if otherwise.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>
-> E<sub>0</sub> `different from` E<sub>1</sub></code></pre>

## Structure

```C++
template<typename, typename>
concept DifferentFrom = REQUIREMENT;
```

## Implementation

```C++
template<typename LeftSide, typename RightSide>
concept DifferentFrom
=   Mouldivore::Confess<IsDifferent, LeftSide, RightSide>
&&  Mouldivore::Confess<IsDifferent, RightSide, LeftSide>;
```

## Links

- [Source code](../../../../conceptrodon/concepts/typelivore/different_from.hpp)
- [Unit test](../../../../tests/unit/concepts/typelivore/different_from.test.hpp)
