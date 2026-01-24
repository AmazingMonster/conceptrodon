<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Yes`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-yes">To Index</a></p>

## Description

`Typelivore::Yes` accepts a list of elements and returns `true`.

<pre><code>   Es...
-> true</code></pre>

## Type Signature

```Haskell
Yes
 :: typename...
 -> auto
```

## Structure

```C++
template<typename...>
struct Yes
{
    static constexpr auto value
    {RESULT};
};
```

## Examples

```C++
static_assert(Yes<int>::value);
```

## Implementation

```C++
template<typename...>
struct Yes
{
    static constexpr bool value {true};
};
```

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/yes/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/typelivore/yes.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/yes.test.hpp)
