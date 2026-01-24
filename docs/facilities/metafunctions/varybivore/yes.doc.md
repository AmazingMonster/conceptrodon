<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Yes`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-yes">To Index</a></p>

## Description

`Varybivore::Yes` accepts a list of variables and returns `true`.

<pre><code>   Vs...
-> true</code></pre>

## Type Signature

```Haskell
Yes
 :: auto...
 -> auto
```

## Structure

```C++
template<auto...>
struct Yes
{
    static constexpr auto value
    {RESULT};
};
```

## Examples

```C++
static_assert(Yes<0>::value);
```

## Implementation

```C++
template<auto...>
struct Yes
{
    static constexpr bool value {true};
};
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/yes/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/varybivore/yes.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/yes.test.hpp)
