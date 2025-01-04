<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::Unvaluable`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-unvaluable">To Index</a></p>

## Description

`Omennivore::Unvaluable` accepts a class.
It returns true if the class does not contain a static constexpr data member `value` and returns false if otherwise.

<pre><code>   Class
-> not requires {static constexpr auto Class::value;}</code></pre>

## Structure

```C++
template<typename>
concept Unvaluable = REQUIREMENT;
```

## Implementation

```C++
template<typename Structure>
concept Unvaluable = not requires 
{
    requires std::is_const<const decltype(Structure::value)>::value;
    requires Ominuci::ImmediateValue<Structure::value>;
};
```

## Links

- [Source code](../../../../conceptrodon/omennivore/concepts/unvaluable.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/unvaluable.test.hpp)
