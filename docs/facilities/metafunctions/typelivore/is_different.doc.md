<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::IsDifferent`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-is-different">To Index</a></p>

## Description

`Typelivore::IsDifferent` accepts a target and a list of elements.
It returns true if the target is different from every element;
otherwise, it returns false.

<pre><code>   Target, E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>n</sub>
-> (Target `different from` E<sub>0</sub>) && (Target `different from` E<sub>1</sub>) && ... && (Target `different from` E<sub>n</sub>)</code></pre>

## Type Signature

```Haskell
IsDifferent
 :: typename...
 -> typename
```

## Structure

```C++
template<typename...>
struct IsDifferent
{
    static constexpr bool value
    {RESULT};
};

template<typename...>
constexpr bool IsDifferent_v
{RESULT};
```

## Examples

```C++
static_assert(IsDifferent<int, int*, int**, int**>::value);
static_assert(! IsDifferent<int, int, int*>::value);
```

## Implementation

We will implement `IsDifferent` using `std::is_same_v`.

Here's the entire implementation:

```C++
template<typename Target, typename...Elements>
struct IsDifferent
{ static constexpr bool value
{(...&&(not std::is_same_v<Elements, Target>))}; };

template<typename Target, typename...Elements>
constexpr bool IsDifferent_v 
{(...&&(not std::is_same_v<Elements, Target>))};
```

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/is_different/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/typelivore/is_different.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/is_different.test.hpp)
