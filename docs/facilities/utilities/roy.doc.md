<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Roy`

<p style='text-align: right;'><a href="../utilities.md#roy">To Index</a></p>

## Description

`Roy` accepts a `Road` operation and returns the operation via member `Road`.

<pre><code>   Oper
-> struct { using Road = Oper; }</code></pre>

## Type Signature

```Haskell
Roy
 :: template<template<typename...> class...> class...
 -> template<template<typename...> class...>
```

## Structure

```C++
template<template<template<typename...> class...> class>
struct Roy
{
    template<template<typename...> class...>
    alias Road = RESULT;
};
```

## Examples

This function injectively maps a warehouse to a type.
In the following example, We will create an overload set of `fun` using warehouses `Ware_0` and `Ware_1`.

```C++
/**** Operations ****/
template<template<typename...> class...>
struct Ware_0 {};

template<template<typename...> class...>
struct Ware_1 {};

/**** fun ****/
constexpr bool fun(Roy<Ware_0>) { return false; }

constexpr bool fun(Roy<Ware_1>) { return true; }

/**** Tests ****/
static_assert(not fun(Roy<Ware_0>{}));
static_assert(fun(Roy<Ware_1>{}));
```

If we only want compilers to perform an argument-dependent lookup, we can utilize `decltype` and `std::declval` to avoid defining the function body.

```C++
/**** gun ****/
constexpr auto gun(Roy<Ware_0>) -> std::false_type;

constexpr auto gun(Roy<Ware_1>) -> std::true_type;

/**** Tests ****/
static_assert(not decltype(gun(std::declval<Roy<Ware_0>>()))::value);
static_assert(decltype(gun(std::declval<Roy<Ware_1>>()))::value);
```

## Implementation

```C++
template<template<template<typename...> class...> class Warehouse>
struct Roy
{
    template<template<typename...> class...Containers>
    using Road = Warehouse<Containers...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGz%2BpK4AMngMmAByPgBGmMQgkgCspAAOqAqETgwe3r4BQemZjgJhEdEscQnJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlUbHxiSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwA9ABU%2BweHR8cH2yYaAIJ7BwDUAJIsqfRsgkwNN4dnl9cnvydfF3OFwImEeBhBJgAzG4QWC3pgoTDQU94YiCABPVKMViYAB0%2BKh2BuyAMCgU%2BNxhOJpIUNwA6i1MAg1kpCUDxsQvA4bgAlVDooEmADsVkuN3FN1hKIh0Kl4IRssx2LYFKpJKYZIpHle4XiCjZYolXkyRl5qCY6BuUIAIvTGczjQq3NrmrriOSCZDsFDRYChdafYLvn8Q58gT9djcAGJ4d0EG7YVSsJ6YD6ncOhzMAjO3ADyWOIb2ytLDlzlqNlyPlaKVzBVnqJ6s1DfZBE53IZxEwAH0NFaRcKA5DfUDyzKkXDxxisXW8Q3qRqPZSva32/HOz2uP2rP7A5cc/sblQvAw0/sAWgGONMKpUsQbjFUJ4jyeIHyBdCN73CUttzcuwQ6ynlQYissO/YBvulyXtet73o%2Bz7Hgwb78oiX5cD%2Bf4AUBkqcgqFgQUGVyHDcAAqmDjCW6aXLMjjIN2i7xAQEAMKg8ZIShH5uF%2BGhsgO/pLEse4XLReD0YxrTUK%2B75oYy3YYSu/HWoJwkHpmfwAhGNxCJgl6Womyb0GeuyaepobZvuZiQuEJJeFgVqKli3ZtkwhD6iuUHEbcwAnsZF4CLBd43EwXhEDcPnITJn5ybxXq/gAtFS4zoCAIAgbQSjOUqqnQQFIJwcFoWoOF0modFXbyZhiVejcyWpW2Xg9tO%2BFEVp5GUX5rZFuJZJMSxbE3FgJLNdAr51SAQ20AAbmIiJRdxMVsl6ECCUsqUzd4mBCcOXV0QxvWSZNI0RRA42TRtc1lQtFUKd6y2retYiNdtFgcCstCcEkvB%2BBwWikKgnBuNY1i1WsGypuYkI8KQBCaG9KwANYgEkki4hoAAcZhmAAnNjXBJBj6NcEKQrSB9HCSLwLASBoGikD9f0AxwvAKCAdOw79b2kHAsAwIgIBrAQqSheQlBoI8dDxJEOKcKo6P%2BPF/iSOFyDIDcUi4mYvCYPgRDEHgKVcDIggiGI7BSMb8hKGocOkLoRsAO6FqknA8O9n3fbbTO5qFwvxqgVA3HLCtKyrasa2YNwQB4Ev0PekNcEsvAc1oKwQEg4upJLZAUBAmfZyAwBSGYfB0CC7qUDEtsxOELToq7vA18wxDormMTaLpHPQ%2BLLwELmDC0PXnOkFgMReMAbhiBlDcj6ChjAOIw/4F2Dh4FNFG2zeumhVs0PhCC5N/bQeAxIWLceFgtttng1PcLw6/EI%2BSjWnPRjH0YcMrFQBjAAoABqeBMAO3zIwGe/ATaiHEBbcBVsVDqGHvbfQ88UDA0sPoE%2BrNIArFQKkBorMODxWSjaUwlhrBmEZg/fWWBMErW6J3bILgGDuE8B0PQoRdQLBGEbIoWQBBTD8NwjIvCGDzGGAkI2dh6ECD6JMFh%2BQJF1CkY0CYAwOFiL0LMWReQBG2BUaIyoXCVgKDBpsCQ7sOBfXpl7TgQd5aK2VsAVW6tUaRwgLgQgJArRWUTsnT%2BKwECYAtCMWhSNJCQlxNjSEpMNCSDMJIfwtMkj%2BGxvoTglNSDUyhrifwXB/Do2xkTfwKN8aRKCAzXgTMWZsxhp/bmfN04C19iLXO%2Bc47SzYJwFoLAppCnikwBcpouDY1xFwNG2tdYkANnoGBpsoHSBgYoOBttdAlydkwF2d9zGWPKf9TgPshahRuAHWxIdlbqkGcM0ZfZo6oFjvELxkIzBJxqZzNOGdblZzjqLPOHyC7nKLnjOmNBaDl1ZhAKuw8m51xnlClubcO4OBnj3RgfcB5Dz%2BqPcek9aDTzvrPFg89F4YtjPQ9e%2BC/pb2QDvGe%2B86i22PqfOuF8th/WvrfaGD8n6YBfgSt%2B4RQCvL4D/f%2BgDgEzjAbIWZ5t5myEWTbBBIAS4GA/iQqwaCGU0Owbg4snBCEEHQMQ1BFhyEVMoQbDeWC6Gr2cBAVw/C2FMP0YsQRxRsj2pdcIp1XCrUNBkW0OROjJHWuUXMNRBjxG6P6O6yNrQvXiKMSY82WzPbDyZic%2BxAzgDq0uWjKO7i9YPJ8S81O/jAlYASLQ8m6TMnDJiUKJI2MSaQlifEyQRsdmVNsNUlOXMeb80Fn7b5rSpYyw4F00OLAFBTTVlNIZuJ5TjHGR4qh0zJWQOlZbOV8C/q6EhKQNZGy3apIsSmxmeymn%2B0DqoCdU6Z1zoXfGG5dz45WUhM8ntbyUC/K%2BS079Ixp2pFSN2Wd2NuwPu7Ne%2BZZc9SV2rrXFuML4Ot3bp3JFtze790HrbTFE8p74OhlgXlC8WW8GXqSjew9KXUrxbSw%2BvAGVn3RMyq%2B%2Bt2X33iFynlhL%2BW1O/kwX%2BACgEgJ%2BtDGZ66JAysEFu5ZIA93KuMEa9BMRNX/W1QFTg2w6qqrIRQ%2BIVCLW0KDQ0RhzDtEOvQHGvQPCGjRus9kSzCiejSJUdGozvQ9FhudTG/1ZmJEefKOoxOqx1imKC%2BTbZ1iOBBxvdOm4IH53wnGHmiZL6obvr8aQAJQSK3mOrYq4ZkJIRJAJm22mhWhR5KsamzgVT2YZdCUkCJxMhS03RpIPGXBMZmCCOTSEp6Kk1eLfDY9WsqtnuZkNwSpAH6ZGcJIIAA%3D%3D%3D)$Done$

## Links

- [Example](../../code/facilities/utilities/roy/implementation.hpp)
- [Source code](../../../conceptrodon/roy.hpp)
