<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::AllUnvaluable`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-all-unvaluable">To Index</a></p>

## Description

`Omennivore::AllUnvaluable` accepts a list of classes.
It returns true if none of the classes contains a static constexpr data member `value` and returns false if otherwise.

<pre><code>   Classes...
-> (... && (not requires {static constexpr auto Classes::value;}))</code></pre>

## Structure

```C++
template<typename...>
concept AllUnvaluable = REQUIREMENT;
```

## Implementation

```C++
template<typename...Structures>
concept AllUnvaluable = (...&&Unvaluable<Structures>);
```

## Links

- [Source code](../../../../conceptrodon/omennivore/concepts/all_unvaluable.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/all_unvaluable.test.hpp)
