<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AreUnique`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-are-unique">To Index</a></p>

## Description

`Varybivore::AreUnique` accepts a list of variables. It returns true if no two variables in the list are the same and returns false if otherwise.

## Type Signature

```Haskell
AreUnique
 :: auto...
 -> auto
```

## Structure

```C++
template<auto...>
struct AreUnique
{
    static constexpr bool value 
    {RESULT};
};
```

## Examples

We will check if `0, 1, 2, -1` are unique. Then, we will append `1` and check again.

```C++
static_assert(AreUnique<0, 1, 2, -1>::value);
static_assert(! AreUnique<0, 1, 2, -1, 1>::value);
```

## Implementation

`AreUnique` is implemented as a special case of `Varybivore::AreOverlapping`:

```C++
template<auto FirstVariable, auto...RestVariables>
struct AreUnique
{
    static constexpr bool value 
    {
        ! AreOverlapping<FirstVariable>
        ::template Page<RestVariables...>
        ::value
    };
};
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/are_unique/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/are_unique.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/are_unique.test.hpp)
