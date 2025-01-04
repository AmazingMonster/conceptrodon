<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::Valuable`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-valuable">To Index</a></p>

## Description

`Omennivore::Valuable` accepts a class.
It returns true if the class contains a static constexpr data member `value` and returns false if otherwise.

<pre><code>   Class
-> requires {static constexpr auto Class::value;}</code></pre>

## Structure

```C++
template<typename>
concept Valuable = REQUIREMENT;
```

## Implementation

```C++
template<typename Structure>
concept Valuable
=   std::is_const<const decltype(Structure::value)>::value
&&  Ominuci::ImmediateValue<Structure::value>;
```

## Links

- [Source code](../../../../conceptrodon/omennivore/concepts/valuable.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/valuable.test.hpp)
