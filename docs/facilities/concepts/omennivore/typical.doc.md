<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::Typical`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-typical">To Index</a></p>

## Description

`Omennivore::Typical` accepts a class.
It returns true if the class contains an type alias member `type` and returns false if otherwise.

<pre><code>   Class
-> requires {typename Class::type;}</code></pre>

## Structure

```C++
template<typename>
concept Typical = REQUIREMENT;
```

## Implementation

```C++
template<typename Structure>
concept Typical = requires 
{typename Structure::type;};
```

## Links

- [Source code](../../../../conceptrodon/concepts/omennivore/typical.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/typical.test.hpp)
