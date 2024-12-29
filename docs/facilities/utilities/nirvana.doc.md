<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Nirvana`

<p style='text-align: right;'><a href="../utilities.md#nirvana">To Index</a></p>

## Description

`Nirvana` is a vessel for `Dawn`.

It also contains a regular function, `size`, which returns the number of items it holds.

## Type Signature

```Haskell
Nirvana
 :: template<template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...> class...>
```

## Structure

```C++
template<template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...> class...>
struct Nirvana
{
    static constexpr auto size() -> size_t;
};
```

## Examples

We dawn create a `Nirvana` with items `Item_0, Item_1, Item_2, Item_3`.
Then, we query its size.

```C++
/**** Items ****/
template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
struct Item_0;

template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
struct Item_1;

template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
struct Item_2;

template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
struct Item_3;

/**** Packed Vessel ****/
using PackedNirvana = Nirvana
<
    Item_0, 
    Item_1, 
    Item_2, 
    Item_3
>;

/**** Test ****/
static_assert(PackedNirvana::size() == 4);
```

## Implementation

```C++
template<template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...> class...Items>
struct Nirvana
{
    static constexpr size_t size()
    { return sizeof...(Items); }
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQDMpK4AMngMmAByPgBGmMT%2BAKykAA6oCoRODB7evv5BaRmOAmER0SxxCZLJdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHAD0AFSHR8cnp/u7JhoAggdHANQAIpgprozIeJgKd8cX17dnAJOvyulxBZgC4WQ3iwdxMATcyFm6CwVDh2FBoP%2BgOxh2BWLuAEkWCl6GxBExet8jnicbTzhjrgRMMSDEy4W4mSyKZh2ZySdzecz%2BWz4XzWTzRULxYKuSKOVKBfCmF4iAA6dVou5QpgKBTq1Wa7W6/WGgzGjUBbBas16i1Wo22g2W606x2m136gmchRo0GzYheBx3SJ4YgAN0MTAxAHYrNc7gm7rMKXhkFqBLNMKoUsQk3gAF6YAD6BDzhYgK1BidhsbuxEwBE2DDLmFQVH1EC9zIUlYCFhrDxjg77DJudJ%2BmOOd2wqlYJMwVNxk/HS%2Buy8OhO9i/pjIVcrFivlsolR%2BFJ4P%2B7356v7OVartLvNTvtNpNzodb5fHofH5/r7tfoEAGQZdiwRYaHCcYgrux4ymecHSpKsFIfBKGIae6F3qgn6Pm677/s%2BuE4b%2BhEke6T6%2Btc/qBqWoFFlwkGjhe17IRhh7MQh7E3mhh5YcRBHkXhX4Ufh36kQJokieiVFATRm7MkWZiMWuMGoWxl6sRxPEaWpWluHxf5iYJ/FGZJQlEYZUmAcBtGckWATKdBY73MoTDIAA1pg6B3AAap8djbsCXgZEYdyuR5XkhuGkawgEDzBqGEbMBi8JVomdEaKQsLxuldlcFlaUJnRZgFTlRV2Q5a6Wo5677HcAAqnylhOMkpsgRauvEBAQOFnnoFFSVMCAIAZOWKyxcO8WSL2FgcGstCcIkvB%2BBwWikKgnBuNY1hJhsWwLuYAQ8KQBCaHNazuSAiSSKqGgABxmGYACcT1cIk913Vw0bRtIC0cJIvAsBIGiZSta0bRwvAKCAmWnatc2kHAsAwIgIAbAQKQquQlBoMSdDxJErA7Kod0AGwALSk5IdzAMgaZSKqZi8F5hAkHg6B6PwggiGI7BSDIgiKCo6jw6Quj5QA7sQTApJwPDzYty1netnAAPIqpjpZtncJMU1TNN03cDNmHcEAeHj9C5odXArLwcNaGsEBILjKT42QFAQC7bsgMAUglTQtBMsQ0MQDEysxOEzQAJ5y7wEfMMQUeqzE2h1HDx242SBCqwwtAx6LWAxF4wD6bQtDQ9wvBYCwhjAOIBehmneBhp8ytZnUKo7Md4RMn9a20HgMTS4nHhYMrQF4EDlekC3xAxOkmBPDXRgD0YZ1rFQBjAAoPkfBLqsvCtx1c8IojiPzJ9C2oyvi/otcoNtlj6IP0OQGsqApL0Ffk0icIPKYlhrBmHBrPYg7NW5vy6D0LILgGDuE8O0PQoQFjlEqHoQomQBBTD8PlDBvQhioNGPlWo9QBD9EmAgvIxDuhNzIXMAhIwEjELmNgvQyYWgMKWEwtYCg9rbAkArDgS1SBg14BDHWZNKbU1pvTG6JsIC4FZlbcENs7brzWAgTATAsAJArKQS6gRVRPQCD9DQkgzCSFJiDRIpMnr6E4ADUgQMjqqlJlwUmd0nqfVJtdN6xjSYiOVhDKGMMTrr0RijJ2aMNZYw9l7S2hM2CcGaCwMM0ZyZMBdKFLgT1VRcFuszfARAwEc3yifHm59pCXyUNfUWugSpSxlrHQRwjREqw4OrDGKo7ja11lIrJwAja5PyRoU25tXaW1hOCMwtswnw0ds7VAFt4jY09ksiZoxtRGByVwTKAcg4hzDqLeO0dY6kBOYnZOqcHBnMzowbOud85rULsXUu5cznV1rvXZ5jd6gtwrmtduyBO5nJ7t0ZWA8h7R1HjsNaE8p7HVnvPJQS8vnhFAPMvgW8d57wPowM55Sz58yqbIK%2BIs1r1LvmvABVgn6Qtfnoj%2BX9OA/wIOgP%2BNKgEgPiCUiBeiSG9FgfA3IODghwM4Wg3B6RMHZEoaKvBWQJVEKgbQvoLC5VsJoaQtVAwlVMPGAMVhzDdUoMYQI9Ymx%2BE23sUIpWotxF9P1lswZOS8m3VNoo4pUyjqzPtudUgmjtGjD0X9RxzjclmOjIkJ630AjmMsZIfKbTgm2FCX6x2kSkDo01qs%2BJBMibJOICwfWLAFBhjTGGV14pZiFKUezTmsgKnEoFvIGp5KdAgCCI02WlcWl2vBmrGJWsqA6xLWWitVbuSzDGest23qAi%2BvCVEvN7scazstiActKQUhFkrU9Is1aCBFlUFTPgdADmUCOWtC5%2Bdjo3quWnW5Sys45zzsrF5JcxDvOnp8lesKq6/McP8tuqgO5MlBYIcFotIXDyjjC8eYCEW8CRQvVFK90XhM3kwbeu9MD70PgSxtRKJAksFm2m%2BnaqXGEfjYel8B36fyyBXXYSIH6AMsMAsRoDwEMp4VqwVEBXBGrFegPV6DpW9GEwqkopquGaugXQw1GrqEKZ1Rw2TkqDUUJFWw%2BhGmiE8L4XzPtgT7WcFHdTUt5a7h7tVIej1RSSDetUXMh2GitE6MoIIsNIBnqqgCAERI71E0gwC9GDxpmB2Q1TbDdR%2BikhGK%2BtGEGd1JCvS4A9MwAS/oBH7WIzgaj5mCKZpF/L0X01rFnhkZwkggA%3D%3D)

## Links

- [Example](../../code/facilities/utilities/nirvana/implementation.hpp)
- [Source code](../../../conceptrodon/nirvana.hpp)
