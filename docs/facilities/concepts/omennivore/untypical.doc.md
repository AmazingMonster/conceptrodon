<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::Untypical`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-untypical">To Index</a></p>

## Description

`Omennivore::Untypical` accepts a class.
It returns true if the class does not contain a type alias member `type` and returns false if otherwise.

<pre><code>   Class
-> not requires {typename Class::type;}</code></pre>

## Structure

```C++
template<typename>
concept Untypical = REQUIREMENT;
```

## Implementation

```C++
template<typename Structure>
concept Untypical = not requires 
{typename Structure::type;};
```

## Links

- [Source code](../../../../conceptrodon/metafunctions/omennivore/concepts/untypical.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/untypical.test.hpp)
