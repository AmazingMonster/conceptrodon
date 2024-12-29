<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Sunrise`

<p style='text-align: right;'><a href="../utilities.md#sunrise">To Index</a></p>

## Description

`Sunrise` is a vessel for `Grit`.

It also contains a regular function, `size`, which returns the number of items it holds.

## Type Signature

```Haskell
Sunrise
 :: template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
```

## Structure

```C++
template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
struct Sunrise
{
    static constexpr auto size() -> size_t;
};
```

## Examples

We will create a `Sunrise` with items `Item_0, Item_1, Item_2, Item_3`.
Then, we query its size.

```C++
/**** Items ****/
template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
struct Item_0;

template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
struct Item_1;

template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
struct Item_2;

template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
struct Item_3;

/**** Packed Vessel ****/
using PackedSunrise = Sunrise
<
    Item_0, 
    Item_1, 
    Item_2, 
    Item_3
>;

/**** Test ****/
static_assert(PackedSunrise::size() == 4);
```

## Implementation

```C++
template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...Items>
struct Sunrise
{
    static constexpr size_t size()
    { return sizeof...(Items); }
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQDMpK4AMngMmAByPgBGmMT%2BAKykAA6oCoRODB7evv5BaRmOAmER0SxxCZLJdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHAD0AFSHR8cnp/u7JhoAggdHANQAIpgprozIeJgKd8cX17dnAJOvyulxBZgC4WQ3iwdxMATcyFm6CwVDh2FBoP%2BgOxh2BWLuAEkWCl6GxBExet8jnicbTzhjrgRMMSDEy4W4mSyKZh2ZySdzecz%2BWz4XzWTzRULxYKuSKOQBPF7MNgAOjVaLuUKYCgUapVGq1Or1BoMRvVAWwmtNuvNlsNNv1Fqt2odBM5CjRoNmxC8DjuQi8DGIeCUGIA7FZrndo3dZhS8MhNQJZphVCliLG8AAvTAAfQImZzEBWoJjsIjd2ImAImwYhcwqCoeogbuZChLAQs5Ye4Z7nYZNzpP0xxzu2FUrBJmCpuJHQ9n1znh0J7pn9MZUoFktlEo5m7lYq3e53MuFu4IisYrEwxqd9tvdutD%2BdZsdj5dz/vtq9BB9ftbLC5hocKRiCG4ntuZ6ntKkEwceUGwUeF5Kten5PraL4OiaH4YV%2Bb6YQ%2BP5/gWAG5lwIEDoeB77ueNHQUhdGIQel7KjeuHofheHYa%2B3FYXeHGetc3q%2BiRnK5mYFGLuBCHwXBVG0RBskMYpyFXqq7E4ZxAn8ZpvFobpFpESJK7MrmASSWBg73MoTDIAA1pg6B3AAap8dhrsCXgZEYdw2fZjkBkGIbTnCDz%2BoGwahou8KljGpEaKQsJRnFYlcIlsXRqRZjpclmVieZ0Xov2UlWcuAAqnwFsOQlNI4yC5i68QEBAfkOeggWRewIAZEWKywgEfZhZIHYWBway0JwiS8H4HBaKQqCcG41jWLGGxbCF4I8KQBCaGNax2SAiSSCqGgABxmGYACcl1cIkZ2nVwYZhtIE0cJIvAsBIGgJTNc0LRwvAKCACU7bNY2kHAsAwIgIAbAQKReAQ5CUGgxJ0PEkTXpwqinQAbAAtLjkh3MAyCJlIKpmLwjmECQeDoHo/CCCIYjsFIMiCIoKjqGDpC6GlADuxBMCknA8ONk3Tbt82cAA8ojCMFo2dw4wTRMk2TdwU2YdwQB4aP0Bm5gBFwKy8KDWhrBASCoyk6NkBQEC2/bIDAFI2U0LQTLEEDEAxNLMThM08pi7wgfMMQ8qyzE2h1KDW2o2SBCywwtAh7zWAxF4wBuGItBA9wvBYCwhjAOIGd4FW9QAG6fNLqZ1IjOxbeETKvXNtB4DEwuRx4WDS7%2BeCfYXpC18QMTpJgTwl0YndGLtaxUAYwAKM5HwC7LSqhxzwiiOI7NM/IShqNL/P6KXKDLZY%2Bhd0DkBrKgKS9AX%2BNIqFpiWNYZh/WPwZYHfxYug9CyC4Bg7hPDtD0KEBY5RKh6EKJkAQUw/BpQQb0IYsDRhpVqPUAQ/RJgQLyNg7occGhzAwSMBI2C5jIL0HGFoFClhULWAoNa2wJASw4FNUgv1eD/RVnjQmxNSbk2OjrCAuBaZG02mbbaC81gIEwEwLACRAEHUCCqS6ARnoaEkGYSQuNvqJFxpdfQnB3qkE%2BibFUuMuC41OpdB6uMjq3S0bjHh0t/qA2BnIsGVtobW1hgrRGyMnaoANhjLGHBmgsGrmGfGTBnQ%2BS4JdFUXATrU3wEQP%2BjNZAs33tIQ%2BXMT6810NlIWItQ6cO4bwmWHB5bw0RncZWqshFJOAFrVJ6SNC631nbQ2sJwRmFkRbcGgTnaG1CRM0YWojApK4AlT23tfb%2B15uHYO291mR2jrHBw29E6MGTqndOc1M7Z1zrQfO29i6l3LqcyupDa4Fzmg3ZATdt6t26NLTu3dg59x2HNQew8tpjwnkoaetzwigD8XwZeq916b0YNvQ%2B%2BS2aFNkMUnmc0ynn3nh/Kw18fkAIfk/LIL834DXxV/H%2B8Q/513vkA0hzgICuFoWlaBZRKHwPSIg7IhCUGpB5egmBXLiHALwTQ/ldCSG4L6OQkVTC6GStyAK%2Bh8xOWKtNusTY7CtWvRqZ4zgAi1bE1mR0lJaSTq60kdkwZJsRnyNIIo5RoxAGvQsVY1JuiwyJEuk9AIeiDGSDSrUrxtgfGjP8fAQJcNFZTPCf0yJbBOAxPViwBQ1dEzVwteKWYmSpH01yczPeaKd6YtPiAIIFTRaF2qVLXm/0GmK2aVQFWaaM1ZpzdyWYvSE32ztQEB1MLxl9smY7aZCRM0pBSLmbNl1cy5oILmVQRM%2BB0GWZQVZc0tnpy2junZcd9nhKTinNO0szk5zzgXLaNzZ4AqLg8muddeavPeSPT57deA/J7vKf5A9gzAt4KCyeELZ5QoXrCpgK816YA3lvEeKKS0SHRZzY%2BWKdCVtxcYK%2BNgiXwBJc/TguwkSX0/pYb%2BfDf703pYAnBvRQHgJVVAsBjC4GoKFVkNlgqihZFY1gxlsr8GtClWKplcqBh8aoeMAYXG1WSY4dq9aCn9X1r%2BkaldxN02ZruHOlUi7rVZJIHa025tHXOpUZQThHqQBXRVAEAIiQ7rBu%2BvZsM9iPENs4N4kGjr1GJE0Y9MM31TqSBulwc6Zh3GvQCKpvhXnfGW04VTDzamAYJb2qPeIGRnCSCAA%3D%3D%3D)

## Links

- [Example](../../code/facilities/utilities/sunrise/implementation.hpp)
- [Source code](../../../conceptrodon/sunrise.hpp)
