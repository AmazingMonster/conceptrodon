<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::AnyValuable`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-any-valuable">To Index</a></p>

## Description

`Omennivore::AnyValuable` accepts a list of classes.
It returns true if there exists a class that contains a static constexpr data member `value` and returns false if otherwise.

<pre><code>   Classes...
-> (... || (requires {static constexpr auto Classes::value;}))</code></pre>

## Structure

```C++
template<typename...>
concept AnyValuable = REQUIREMENT;
```

## Implementation

```C++
template<typename...Structures>
concept JustAnyValuable
= (...||Valuable<Structures>);

template<typename...Args>
concept AnyValuable
=   JustAnyValuable<Args...>
||  AllValuable<Args...>;
```

## Links

- [Source code](../../../../conceptrodon/omennivore/concepts/any_valuable.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/any_valuable.test.hpp)
