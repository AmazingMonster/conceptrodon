<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Minimum`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-minimum">To Index</a></p>

## Description

`Varybivore::Minimum` accepts a list of variables and returns the minimum.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (min) V<sub>0</sub>, V<sub>1</sub>, ...,V<sub>n</sub></code></pre>

## Type Signature

```Haskell
Minimum
 :: auto...
 -> auto
```

## Structure

```C++
template<auto...>
struct Minimum
{
    static constexpr bool value
    {RESULT};
};

template<auto...>
static constexpr auto Minimum_v
{RESULT};
```

## Examples

```C++
static_assert(Minimum<1, 2, 3>::value == 1);
static_assert(Minimum<1.0, 2.5, 3.5>::value == 1.0);
```

## Implementation

We will implement `Minimum` using `std::ranges::min`.

Note that we are not instantiating `std::array` directly. Instead, we let 'Class template argument deduction(CTAD)' decide the correct type for `array`.

```C++
template<auto...Variables>
struct Minimum
{ 
    static constexpr auto value 
    {
        []()
        {
            std::array array {Variables...};
            return std::ranges::min(array);
        }()
    }; 
};
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/minimum/implementation.ctad.hpp)
- [Example](../../../code/facilities/metafunctions/varybivore/minimum/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/minimum.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/minimum.test.hpp)
