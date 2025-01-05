<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::DifferentFrom`

<p style='text-align: right;'><a href="../../concepts.md#varybivore-different-from">To Index</a></p>

## Description

`Varybivore::DifferentFrom` accepts two variables.
It returns true if two variables are different and returns false if otherwise.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>
-> V<sub>0</sub> `different from` V<sub>1</sub></code></pre>

## Structure

```C++
template<auto, auto>
concept DifferentFrom = REQUIREMENT;
```

## Implementation

```C++
template<auto LeftSide, auto RightSide>
concept DifferentFrom
=   Pagelivore::Clarify<IsDifferent, LeftSide, RightSide>
&&  Pagelivore::Clarify<IsDifferent, RightSide, LeftSide>;
```

## Links

- [Source code](../../../../conceptrodon/descend/varybivore/concepts/different_from.hpp)
- [Unit test](../../../../tests/unit/concepts/varybivore/different_from.test.hpp)
