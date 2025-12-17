<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::IsSame`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-is-same">To Index</a></p>

## Description

`Typelivore::IsSame` accepts a target and a list of elements.
It returns true if the target is the same as every element;
otherwise, it returns false.

<pre><code>   Target, E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>n</sub>
-> (Target `same as` E<sub>0</sub>) && (Target `same as` E<sub>1</sub>) && ... && (Target `same as` E<sub>n</sub>)</code></pre>

## Type Signature

```Haskell
IsSame
 :: typename...
 -> typename
```

## Structure

```C++
template<typename...>
struct IsSame
{
    static constexpr bool value
    {RESULT};
};

template<typename...>
constexpr bool IsSame_v
{RESULT};
```

## Examples

```C++
static_assert(IsSame<int, int, int, int>::value);
static_assert(! IsSame<int, double, int>::value);
```

## Implementation

We will implement `IsSame` using `std::is_same_v`.

Here's the entire implementation:

```C++
template<typename Target, typename...Elements>
struct IsSame
{ static constexpr bool value
{(...&&std::is_same_v<Elements, Target>)}; };

template<typename Target, typename...Elements>
constexpr bool IsSame_v 
{(...&&std::is_same_v<Elements, Target>)};
```

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/is_same/implementation.hpp)
- [Source code](../../../../conceptrodon/typelivore/is_same.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/is_same.test.hpp)
