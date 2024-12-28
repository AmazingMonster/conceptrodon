<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Morning`

<p style='text-align: right;'><a href="../utilities.md#morning">To Index</a></p>

## Description

`Morning` is a vessel for `Will`.

It also contains a regular function, `size`, which returns the number of items it holds.

## Type Signature

```Haskell
Morning
 :: template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
```

## Structure

```C++
template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
struct Morning
{
    static constexpr auto size() -> size_t;
};
```

## Examples

We will create a `Morning` with items `Item_0, Item_1, Item_2, Item_3`.
Then, we query its size.

```C++
/**** Items ****/
template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
struct Item_0;

template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
struct Item_1;

template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
struct Item_2;

template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
struct Item_3;

/**** Packed Vessel ****/
using PackedMorning = Morning
<
    Item_0, 
    Item_1, 
    Item_2, 
    Item_3
>;

/**** Test ****/
static_assert(PackedMorning::size() == 4);
```

## Implementation

```C++
template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...Items>
struct Morning
{
    static constexpr size_t size()
    { return sizeof...(Items); }
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQDMpK4AMngMmAByPgBGmMT%2BAKykAA6oCoRODB7evv5BaRmOAmER0SxxCZLJdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHAD0AFSHR8cnp/u7JhoAggdHANQAIpgprozIeJgKd8cX17dnAJOvyulxBZgC4WQ3iwdxMATcyFm6CwVDh2FBoP%2BgOxh2BWLuAEkWCl6GxBExet8jnicbTzhjrgRMMSDEy4W4mSyKZh2ZySdzecz%2BWz4XzWTzRULxYKuSK3EwvEQAHQqtF3KFMBQKFVKtUarU6vUGA2qgLYdXG7Wm836q26s0WzV2gmchRo0GzYheBx3ACyJAY4WAGIA7FZrndI3dZhS8Mh1QJZphVCliNG8AAvTAAfQI6azEBWoKjsLDd2ImAImwY%2BcwqCoOogLuZCiLAQspYeoa77YZNzpP0xxzu2FUrBJmCpuKHA%2Bn1xnh0Jrqn9MZUoFktlEo567lYo3O63MuF24VyutjpN9ptlsNDttd5vTsfl7t7uunu9eebLGzGjh4YgmuR6biex7SqBEGHmBkEHmeqAvg%2BF5Ider6IbeyEYdeHoEF6Po/tmXAAX2%2B57ru26kRR5HgQelHsvB6HPphTGoShRosexV7vlcn74Zy2ZmMR87ATB0FQXRsFkSBYlwYqCHMVx95YZxb5KRxamKeiH64V%2BS7MtmARCUB/b3MoTDIAA1pg6B3AAap8dgrsCXgZEYdxmZZ1n%2BsQgZuXCDx%2BgGQYYvCxZRgRGikLCEbhfxXBRWFkYEWYCUxUl/GGfOZpGQu%2Bx3AAKp8eaDtpsbINmTrxAQEAeVZ6Deb5oAgBkBYrLCAQ9gFkhthYHBrLQnCJLwfgcFopCoJwbjWNY0YbFsk7mAEPCkAQmh9WsFkgIkkhKhoAAcZhmAAnEdXCJPte1cCGIbSANHCSLwLASBokUjWNE0cLwCggJFq2jX1pBwLAMCICAGwECkirkJQaDEnQ8SRKwOyqHtABsAC0qOSHcwDIPGUhKmYvDWYQJB4Ogej8IIIhiOwUgyIIigqOo/2kLo8UAO7EEwKScDw/WDcNa3jZwADyiqQ3m9Z3CjGNYzjeN3ATZh3BAHhw/QaaLVwKy8H9WhrBASCwyk8NkBQEAm2bIDAFIKU0LQTLEN9EAxMLMThM0ACefO8B7zDEF7osxNodR/ctsNkgQosMLQPus1gMReMA8q0LQ33cLwWAsIYwDiAneAVvUABunzC8mdSKjsy3hEyd1jbQeAxNzgceFgwu4XgT2Z6QpfEDE6SYE8OdGI3RhrWsVAGMACi2R8HOiy8I3LVTwiiOI9Or0zajC%2Bz%2Bi5yg02WPoTffZAayoCkvQZ%2BjSL%2BaYljWGY7198Q5Nl%2BfXQ9FkLgMO4njtD0KEBY5RKh6EKJkAQUw/DxQgb0IYoDRjxVqPUAQ/RJgALyMg7oYcGhzAQSMBIyC5jQL0DGFoBClhELWAoOa2wJACw4ENUgb1eAfRlmjTG2Ncb4x2irCAuBSZa3BDrPWE81gIEwEwLACRCykE2oEJUR0Ag3Q0JIMwkhUYvUSKjI6%2BhOAPVIE9JaSpUZcFRntI6l1UbbTOso1GLDhYfS%2Bj9FaE9AYgyNmDCWUMLZW01ojNgnBmgsGLiGdGTBHRuS4EdJUXBdrE3wEQN%2BFN4qrxphvaQW8lA71ZroFKXMea%2B0Ycw1hIsODiwhoqO40tZZcKicAJWsT4kaFVurU2mtYTgjMLrNx/1DbG1QBreI0NLZDI6aMDURgYlcEig7J2Ls3as39t7X2pAVmB2DqHBwazI6MGjrHeOY1E7J1TunNZ2dc752OYXXBpcM5jQrsgKuaza7dGFo3Zu3s247DGp3buy0%2B4DyUMPK5QZ3FTyYDPOemAF5LzWek9edMsmyG3izMa%2BT97jwflYY%2Bnyz5yMvtfTgt8CDoHvkfCwz82Gv3fgSmhODUF%2BAgK4Uh8VgFlEIeA9IkDsiYJgakHl8CQFcuwd/NBJD%2BVkMZb0dB8xOVULIZK3IAryHysWGAnW6xNj0K1XdUpTjOAcLltjKZjSYlxN2qrQRySulLV6frdapBJHSNGHIu6hjjGxLUSGRIR1roBHUZoyQ8UynONsK4x1htPFIHBpLUZ/iEZI2CcQFg8sWAKGLvGYuFrxSzESUI8mlNZAZORQzeQOT0U6BAEEQpvNM4lKFqzD6lTJY1KoDLdNmbs25u5LMNp4yzZ2oCA69xXjE3mxhoOzWIAs0pBSNmHNR1sx5oINmVQWM%2BB0AWZQJZY0Nnx2WgerZYddlDKjjHOOwsTkpzEOcnulzR6/KzrckuZdWZPJeT3N59deCfJbl7H5Hc34At4ECweoLR7gv6Xwaes956L0YAiktSKJAosZpW3eNasXGEpSfGI9LxpXyyBnXYSJD6P0sNS8atKsCEZQb0X%2B/8VVAL/pQzVgqihZDZZx3l7GkFf1wRKgYPGGN4IGPxoh4wRNSuIRJkViqtW0J1XTRtjjm1Go3djDNWa7hLqVKu61SSSB2tEX0g2EipEyMoIwz1IBjpKgCAERI50Q0vScyGCx6n3qcBcb9cR8ikhKKuiGF6e1JCnS4AdMwDi7oBCbT5z65mnV3SJt5thvnksrDWH3DIzhJBAA%3D%3D)$Done$

## Links

- [Example](../../code/facilities/utilities/morning/implementation.hpp)
- [Source code](../../../conceptrodon/morning.hpp)
