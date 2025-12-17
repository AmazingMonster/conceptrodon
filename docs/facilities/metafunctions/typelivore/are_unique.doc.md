<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::AreUnique`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-are-unique">To Index</a></p>

## Description

`Typelivore::AreUnique` accepts a list of elements. It returns true if no two elements in the list are the same and returns false if otherwise.

## Type Signature

```Haskell
AreUnique
 :: typename...
 -> auto
```

## Structure

```C++
template<typename...>
struct AreUnique
{
    static constexpr bool value 
    {RESULT};
};
```

## Examples

We will check if `int, int*, int**, void` are unique. Then, we will append `int*` and check again.

```C++
static_assert(AreUnique<int, int*, int**, void>::value);
static_assert(! AreUnique<int, int*, int**, void, int*>::value);
```

## Implementation

`AreUnique` is implemented as a special case of `Typelivore::AreOverlapping`:

```C++
template<typename FirstElement, typename...RestElements>
struct AreUnique
{
    static constexpr bool value 
    {
        ! AreOverlapping<FirstElement>
        ::template Mold<RestElements...>
        ::value
    };
};
```

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/are_unique/implementation.hpp)
- [Source code](../../../../conceptrodon/typelivore/are_unique.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/are_unique.test.hpp)
