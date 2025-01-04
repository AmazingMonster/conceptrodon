<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::AnyTypical`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-any-typical">To Index</a></p>

## Description

`Omennivore::AnyTypical` accepts a list of classes.
It returns true if there exists a class that contains a type alias member `type` and returns false if otherwise.

<pre><code>   Classes...
-> (... || (requires {typename Classes::type;}))</code></pre>

## Structure

```C++
template<typename...>
concept AnyTypical = REQUIREMENT;
```

## Implementation

```C++
template<typename...Structures>
concept JustAnyTypical = (... || Typical<Structures>);

template<typename...Args>
concept AnyTypical
=   JustAnyTypical<Args...>
||  AllTypical<Args...>;
```

## Links

- [Source code](../../../../conceptrodon/omennivore/concepts/descend/descend/any_typical.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/any_typical.test.hpp)
