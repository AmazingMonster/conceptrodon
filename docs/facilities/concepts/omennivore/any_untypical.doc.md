<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::AnyUntypical`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-any-untypical">To Index</a></p>

## Description

`Omennivore::AnyUntypical` accepts a list of classes.
It returns true if there exists a class that does not contain a type alias member `type` and returns false if otherwise.

<pre><code>   Classes...
-> (... || (not requires {typename Classes::type;}))</code></pre>

## Structure

```C++
template<typename...>
concept AnyUntypical = REQUIREMENT;
```

## Implementation

```C++
template<typename...Structures>
concept JustAnyUntypical = (... || Untypical<Structures>);

template<typename...Args>
concept AnyUntypical
=   JustAnyUntypical<Args...>
||  AllUntypical<Args...>;
```

## Links

- [Source code](../../../../conceptrodon/concepts/omennivore/any_untypical.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/any_untypical.test.hpp)
