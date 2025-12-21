<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::AllValuable`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-all-valuable">To Index</a></p>

## Description

`Omennivore::AllValuable` accepts a list of classes.
It returns true if every class contains a static constexpr data member `value` and returns false if otherwise.

<pre><code>   Classes...
-> (... && requires {static constexpr auto Classes::value;})</code></pre>

## Structure

```C++
template<typename...>
concept AllValuable = REQUIREMENT;
```

## Implementation

```C++
template<typename...Structures>
concept AllValuable 
= (...&&(
    std::is_const<const decltype(Structures::value)>::value
    &&  Ominuci::ImmediateValue<Structures::value>
));
```

## Links

- [Source code](../../../../conceptrodon/metafunctions/omennivore/concepts/all_valuable.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/all_valuable.test.hpp)
