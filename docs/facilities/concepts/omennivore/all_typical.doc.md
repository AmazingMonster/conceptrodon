<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::AllTypical`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-all-typical">To Index</a></p>

## Description

`Omennivore::AllTypical` accepts a list of classes.
It returns true if every class contains a type alias member `type` and returns false if otherwise.

<pre><code>   Classes...
-> (... && requires {typename Classes::type;})</code></pre>

## Structure

```C++
template<typename...>
concept AllTypical = REQUIREMENT;
```

## Implementation

```C++
template<typename...Structures>
concept AllTypical = (... && Typical<Structures>);
```

## Links

- [Source code](../../../../conceptrodon/metafunctions/omennivore/concepts/all_typical.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/all_typical.test.hpp)
