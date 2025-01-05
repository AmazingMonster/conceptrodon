<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::AnyUnvaluable`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-any-unvaluable">To Index</a></p>

## Description

`Omennivore::AnyUnvaluable` accepts a list of classes.
It returns true if there exists a class that does not contain a static constexpr data member `value` and returns false if otherwise.

<pre><code>   Classes...
-> (... || (not requires {static constexpr auto Classes::value;}))</code></pre>

## Structure

```C++
template<typename...>
concept AnyUnvaluable = REQUIREMENT;
```

## Implementation

```C++
template<typename...Structures>
concept JustAnyUnvaluable
= (...||(Unvaluable<Structures>));

template<typename...Structures>
concept AnyUnvaluable
=   JustAnyUnvaluable<Structures...>
||  AllUnvaluable<Structures...>;
```

## Links

- [Source code](../../../../conceptrodon/omennivore/concepts/descend/descend/any_unvaluable.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/any_unvaluable.test.hpp)
