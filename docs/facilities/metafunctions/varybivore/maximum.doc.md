<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Maximum`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-maximum">To Index</a></p>

## Description

`Varybivore::Maximum` accepts a list of variables and returns the maximum.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (max) V<sub>0</sub>, V<sub>1</sub>, ...,V<sub>n</sub></code></pre>

## Type Signature

```Haskell
Maximum
 :: auto...
 -> auto
```

## Structure

```C++
template<auto...>
struct Maximum
{
    static constexpr bool value
    {RESULT};
};

template<auto...>
static constexpr auto Maximum_v
{RESULT};
```

## Examples

```C++
static_assert(Maximum<1, 2, 3>::value == 3);
static_assert(Maximum<1.0, 2.5, 3.5>::value == 3.5);
```

## Implementation

We will implement `Maximum` using `std::ranges::max`.

Note that we are not instantiating `std::array` directly. Instead, we let 'Class template argument deduction(CTAD)' decide the correct type for `array`.

```C++
template<auto...Variables>
struct Maximum
{ 
    static constexpr auto value 
    {
        []()
        {
            std::array array {Variables...};
            return std::ranges::max(array);
        }()
    }; 
};
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/maximum/implementation.ctad.hpp)
- [Example](../../../code/facilities/metafunctions/varybivore/maximum/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/maximum.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/maximum.test.hpp)
