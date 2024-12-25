<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::EasyKindredRepack`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-easy-kindred-repack">To Index</a></p>

## Description

`Omennivore::EasyKindredRepack` accepts a list of packed vessels and returns a function.
When invoked by an operation, the function concatenates the packed vessels and instantiates the operation with the result.

<pre><code>   Vessel<sub><i>0</i></sub>&lt;Items<sub><i>0</i></sub>...&gt;, Vessel<sub><i>1</i></sub>&lt;Items<sub><i>1</i></sub>...&gt;, ..., Vessel<sub><i>n</i></sub>&lt;Items<sub><i>n</i></sub>...&gt;
-> Oper
-> Oper&lt;Items<sub><i>0</i></sub>..., Items<sub><i>1</i></sub>..., ..., Items<sub><i>n</i></sub>...></code></pre>

## Type Signature

```Haskell
KindredEasyRepack
 :: typename...
 -> template<template<typename...> class...>
 
KindredEasyRepack
 :: typename...
 -> template<template<auto...> class...>
 
KindredEasyRepack
 :: typename...
 -> template<template<template<typename...> class...> class...>
 
KindredEasyRepack
 :: typename...
 -> template<template<template<auto...> class...> class...>
```

## Structure

```C++
template<typename...>
struct KindredEasyRepack
{
    template<template<typename...> class>
    alias Road = RESULT;
};

template<typename...>
struct KindredEasyRepack
{
    template<template<auto...> class>
    alias Rail = RESULT;
};

template<typename...>
struct KindredEasyRepack
{
    template<template<template<typename...> class...> class>
    alias Flow = RESULT;
};

template<typename...>
struct KindredEasyRepack
{
    template<template<template<auto...> class...> class>
    alias Sail = RESULT;
};
```

## Examples

- We first concatenate `std::tuple<int>`,  `std::tuple<float, float*>` and `std::tuple<double>`. Then we pack the result into `Container`:

```C++
/**** Container ****/
template<typename...Args>
requires (sizeof...(Args) == 4)
struct Container;

/**** SupposedResult ****/
using SupposedResult_0 = Container<int, float, float*, double>;

/**** Result ****/
using Result_0 = EasyKindredRepack
<
    std::tuple<int>, 
    std::tuple<float, float*>,
    std::tuple<double>
>::Road<Container>;

/**** Test ****/
static_assert(std::same_as<Result_0, SupposedResult_0>);
```

- We first concatenate `std::integer_sequence<int, 0>`,  `std::index_sequence<1, 2>` and `std::index_sequence<3>`. Then we pack the result into `Sequence`:

```C++
/**** Sequence ****/
template<std::make_signed_t<std::size_t>...Args>
requires (sizeof...(Args) == 4)
struct Sequence;

/**** SupposedResult ****/
using SupposedResult_1 = Sequence<0, 1, 2, 3>;

/**** Result ****/
using Result_1 = EasyKindredRepack
<
    std::integer_sequence<int, 0>, 
    std::index_sequence<1, 2>,
    std::index_sequence<3>
>::Road<Sequence>;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult_1>);
```

- We first concatenate `Warehouse_0<Con_0>`,  `Warehouse_1<Con_1, Con_2>` and `Warehouse_2<Con_3>`. Then we pack the result into `Warehouse`:

```C++
/**** Warehouses ****/
template<template<typename...> class...>
struct Ware;

template<template<typename...> class...>
struct Ware_0;

template<template<typename...> class...>
struct Ware_1;

template<template<typename...> class...>
struct Ware_2;

/**** Dummy Arguments ****/
template<typename...>
struct Con_0;

template<typename...>
struct Con_1;

template<typename...>
struct Con_2;

template<typename...>
struct Con_3;

/**** SupposedResult ****/
using SupposedResult_2 = Ware<Con_0, Con_1, Con_2, Con_3>;

/**** Result ****/
using Result_2 = EasyKindredRepack
<
    Ware_0<Con_0>, 
    Ware_1<Con_1, Con_2>,
    Ware_2<Con_3>
>::Flow<Ware>;

/**** Test ****/
static_assert(std::same_as<Result_2, SupposedResult_2>);
```

Here, we first concatenate `Stockroom_0<Seq_0>`,  `Stockroom_1<Seq_1, Seq_2>` and `Stockroom_2<Seq_3>`. Then we pack the result into `Stockroom`:

```C++
/**** Stockrooms ****/
template<template<auto...> class...>
struct Stoc;

template<template<auto...> class...>
struct Stoc_0;

template<template<auto...> class...>
struct Stoc_1;

template<template<auto...> class...>
struct Stoc_2;

/**** Dummy Arguments ****/
template<auto...>
struct Seq_0;

template<auto...>
struct Seq_1;

template<auto...>
struct Seq_2;

template<auto...>
struct Seq_3;

/**** SupposedResult ****/
using SupposedResult_3 = Stoc<Seq_0, Seq_1, Seq_2, Seq_3>;

/**** Result ****/
using Result_3 = EasyKindredRepack
<
    Stoc_0<Seq_0>, 
    Stoc_1<Seq_1, Seq_2>,
    Stoc_2<Seq_3>
>::Sail<Stoc>;

/**** Test ****/
static_assert(std::same_as<Result_3, SupposedResult_3>);
```

## Implementation

We will implement `Omennivore::EasyKindredRepack` by uniting `Cotanivore::KindredRepack`, `Sequnivore::KindredRepack`, `Stockivore::KindredRepack`, and `Warehivore::KindredRepack` into one function.
To do so, we need to detect the underlying vessels of the parameter pack in the template head of `Omennivore::EasyKindredRepack` to produce partial specializations.
Hence, we create the following helper classes.

```C++
// Detect packed `Mold`
template<typename>
struct IsMoldful
{ static constexpr bool value {false}; };

template<template<typename...> class Container, typename...Elements>
struct IsMoldful<Container<Elements...>>
{ static constexpr bool value {true}; };

// Detect packed `Road`
template<typename>
struct IsRoadful
{ static constexpr bool value {false}; };

template
<
    template<template<typename...> class...> class Warehouse,
    template<typename...> class...Containers
>
struct IsRoadful<Warehouse<Containers...>>
{ static constexpr bool value {true}; };

// Detect packed `Rail`
template<typename>
struct IsRailful
{ static constexpr bool value {false}; };

template
<
    template<template<auto...> class...> class Stockroom,
    template<auto...> class...Sequences
>
struct IsRailful<Stockroom<Sequences...>>
{ static constexpr bool value {true}; };
```

We will leave the functionality of `Sequnivore::KindredRepack` to the primary template.
In this way, we won't need to test whether the underlying vessels are `std::integer_sequence`s.
Here is the entire implementation.

```C++
template<typename...Packages>
struct EasyKindredRepack
: public Sequnivore::KindredRepack<Packages...>
{};

template<typename...Packages>
requires (...&&IsMoldful<Packages>::value)
struct EasyKindredRepack<Packages...>
: public Cotanivore::KindredRepack<Packages...>
{};

template<typename...Packages>
requires (...&&IsRoadful<Packages>::value)
struct EasyKindredRepack<Packages...>
: public Warehivore::KindredRepack<Packages...>
{};

template<typename...Packages>
requires (...&&IsRailful<Packages>::value)
struct EasyKindredRepack<Packages...>
: public Stockivore::KindredRepack<Packages...>
{};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCCSAOxcpAAOqAqETgwe3r56KWmOAkEh4SxRMfGJdpgOGUIETMQEWT5%2BlZj2BQx1DQRFYZHRsQm29Y3NOZWjvcH9pYMVAJS2qF7EyOwcAPQAVLt7%2BweH25smGgCCO3sA1AAimEmujMh4mApX%2Byfnl0c/B59npwBZgAzMFkN4sFcTMC3MgFAR0FgqNDsIDzKCGOCvJDoW4vI5aIQAJ4otFffZXDz1Bh4ABuJHYIAA0sF0MRMOgAEr3JjIADW7z2/2YbAUSV5mEpqGpdIZULiVnOgIImBYSQMKtxBCJDxFmAAdIbSed4cQvA5KUwkgovPRoYqAecVWqNZgtTrGKwDUbgaiTQQzRaWQw2RzueL%2BfKrHEbvayRdNlcLEwlJalCB4871UxNTCs673bqvYb9SiruCU28PIImDMyFdtUW2CXsPQ2IIFMazqbzQQrsHQ1yefzcdX6nXca3VYwCAoS6TfWiFYCrquG6rs7m3Pmc268x69fPfeWDAo3gB5B7EHMZLtrq49i13ce0FdrkzL873%2B9eNJGBselCwI3Fcl7RDeAiTm2M5zj6qLAg694frGCHxveO5bhhe7bgexZwSelYlmcwDstOHZ3muv7BMAVycqgTDoEBIHPrWr4wsRpHtrOR7YCAICNnuDrIXGSpfIm3LIKsaS0pKbgpuwmYbgWSowm%2Bq5YYWnrNvhFZnlKNZ1mcpBqeuLq7pph46aeVayLWITEDYJkCZZ%2BpTlx3akFCX5rs5eGudBggWAoxneepuHafq54EAg0SdipfrdgGvb9qy7JDhGfKjrZhlQWRBDdjxnljnZ0RWDCbkzkFhWgdFsU8UuiE%2BUp5l5s1mHhd6pbHrpF5XhBDAUauj59ixdAmR%2BjXflcVH/gJTEpSGaXhrymWhd%2BuImVNq5ydatrYRVggFYankHQQVVwSFZxbd%2BUUxcQsGlmtSG%2BnxWG0fR6C4mB16dAuk3yihQlrRprVme1TadWWPVESRmB5Z2i5rTNNF0Qx82jWxbgcXDXEPSir0eiJAIxkTS6xqJFwUkImAAI5eDS9LsnxA5LcOAofICepihKVzU3TDNyhNilg9hTD4qg9X%2BoGfZCAg%2BIEHaqEUyDOEQ5LiXSwtg7LZGQsk0rjoJkm8lpgpyttdhKti0QPEEXpfNeE8mCedbEuGgAag0eBMBE9AIwlw1a6zGW4g7Tu4p7xDe77rz1YjxP/SrVvi7bPWgX1v3x/egcY%2BNn5XVtyMAQ883ff1Edez7ftx/9wkG05Ftao3MKu6n1kw5xMGDdNf4ox96OYC%2BuLY/DPEEw8pP60DZxJ83qtac7Vyt1Zla87TjuYovvlsFcAAqHouynHuVzH/uAoHLNhmzofr%2BHML7w8nmR9H1dwV2QvA3Pyc2yvell5nCVs5JSfIPVied/o/l7sXSU0IQL/1vE9d8MJ4Q3mQAAfVEPCXE8J0B8RYEwPkmA0FpGACEdAaCCDYLwAALyIZQxcvoIDPyrq8BYNc86AzQk1EWTceEtyPl1bAdsHoj1xt3IuqNGKwNuKAsa7FYajzguPQSZNSZiVotUKSdJZLyQzObHhKk3ANz4XJARUNrJrzpk7IyxjNyizMd1CxYdN6OTWsvfUzCY4eS8gXVc7jPH0CCpddCHUSy3VimieOF9UpXxDjCZx6wAQwgCZgI6gjPIJMwGVNwKTzrpJqndPG8cP6%2BNMnY3h5T%2BE/0EcI9O4EAEmRzrI18a0SnXSLnNaRl90orU2kgoxiCpqy3lorHJJ96BpKfuMrJRTsDBOumucJ915yDKArxfiFt3oMS%2BhnW8DDa5Ty4epL%2Bc93HmMIoaURXcs6USgZIgeQ95Gdw7GPfihN66HP0eUwxtiCz7ghofap5z7a303jYz%2BJjt6LzOY41emTXGlKhXvcFiKOp7wRfefx0zvEmSxVHFhQSnKhMNEsuKSSA7AL7N0nWmV4mgsSbiXeRkrgpLSSiDJ9KsmMpsCy6ZeT2UFLqm/JU%2Bd0InJMTCoRad4GQRuUNSlMih6tNFYXKBnTgJB1ib01ZG1VlANwSAYIKpgDRGIZyvpU1dWlIWWuHBeCCFEJIWQih2CER8TSLQl1vp5k2qAagjBKZ6FuDtSAfBhDiF4FIRyL1wa3UgA9XQhc2AmHYoUGw46FqFkoMcOgzBQaQ1hsdZG51%2Ba40Jq9fBZNuS00rOtVtdlmb7yktrddfGGyRZbM%2BjCGVA19kcLUYi8VlTTFAthWeDuONrmANudRTtDywFPMnS8pRbyJ4fM4RTYSFNvjbF5kQfksombMhiT0yMHNzhcwjJKOoqAD2MxgfnZUQ6/kjrdjU6GwqNbJTksQKO0QB1J2JYI8%2BCrqVsyjHXaemxEzJlTHJdMwth2zwlQ4qV7df5vBvcgTy3833Aoepks%2BUtkpgbiW4LDN8rGb1me/FVxzIXPpaq%2BtuFz30WJ7d3JpSrSltNVbO9VcDdmyvI5ymjBskKfMNmKhjMnh2SuESx8dlyFFiLlT3WdQhWLzrkVjFTMFXkCUnhuw20GNGSXuto02ejDYaR%2BRCpDpzUMKYw3u29KLpMOZQ6OtDrH8OueQBi7hcmnMfv1JknF9mX3ydC/C4KRK1YktqvdSJFLNakd6fE/dSSRNUcSbMjJ%2B7smxeqs2z9vH6Oecq1FkL6G2Orw42prjYDlUQJnbNQCXST00szVa31lpf0vGIJRjeeWSwctyzMwqjbFlJbxjql67a7G8wXW4Br8EDnGd%2BUx5DwXvPObq0p/UVzyJqaLppug2nMbHe4iuwz66B1bpMxSAA6g0TACBD2MnS2eoUnMvTc3WFcV77IPv3og18l9gGEsHZo8Ri07t3t4HBCoiH22gNdmiYtLVutlyScBKZ2DOiEOo8wox8GC9FOzNqcDreX90djoesVOsRGv1Bi69fGENOsoGXsmJhK5WymQ7J5benPnDt%2BbW40hVucWuZo6R1jVDW3BM95%2Bw5Vm3IvbeFxZPy%2BHKcTvhuIqBAAxWgqAADul3h56eXYI5RRmB2mYklomSVnEPKWy1t0nkLRf7b8zT9zQWhc%2B%2Bh3rlzNPAsVch770LKvogRcHSHinGGSxx4cnF4GQHSUpZA2l9nZGA/c/HPZNl3qgdveyWn/lZfSvAZFYnbXoMkMx9qxLoTvbp3ys1jLnjdHvzy5Lp1rHp7Vp1tXL131COPvI6LyVYgkz9LF9Kvl6bq5a89YW29U3Fudn1L2et/t9dNfe6q2j0PDP9fKeebOI3s7t%2BW%2BkbnRdii7erpR8TDXH/4w7quAASQUAALKeDoBUC2iCi7D/CmbPjVB9gZQchQgABsGgQBtAn0SBT6SeeoGOCq/%2BKBIBtoDUD49QOa5YAg8ImAqgSQxAVwEQqAngVwtIYgjsUYVAYgSgkGAMAGje88LkfmaeOGQGp0LOgcuBwBoBmMaeuUuMcc/OCoRBqCpBDA5BlB1BtB9BjB3gD6FgSUboU8nBR%2BlM1w/%2BygTAJq4h4Bxw%2BOiY0BFocBUiSBJhJqJg6BTodOEM2BmsxhphmA4hhB2aSOihyhVBNBdBtADBTBWhrBtA7BehkG7uWuXmeGDOliI20KAiKSwhOBCgjhPhBBdKE2Fc%2BKp8MhfhxBARaAShKoKhIR6hERUYOhHBcR26FI/%2Bki5h56RsNhsBK08BzhGgkifRGBze7hUSWRbRBB9e8hJBFRQRqhoR4RmhLBbBuhgM%2Bh08tmnux%2BlsbhyeMOlO5e7IPqguZ%2BuxYe%2BoaeZKHhyUrRH0vhnOb2s%2BzOJRkx/hyAgRVRwRahYRGhzBE0DRsReO5IRhCgnIrE7Rv26iXRVwdhiB/RYCLhM8OxWBoxnhIJYJExCcUx5RZBHxcxtRixE0URMRqxTRNmjcdmiep%2BW40WreyRWGRxuGl%2BYWomOecOfYrR6JmMFG%2BRqRfOpRChMxuJNR3xdRfxZoKx9oax3%2BvwMpfw%2BOLRLoeU/UFhkBspaplhJOIu0OJh/I3hmRms2AKYRI32o%2BIA0JXgvsARDsAsR6JpuIOpfIep6sesn%2BUOuxDpepXY7IdMeA7IbwEA84ZgCB5gCBohqBdxbgHpJq/sfEPxmACwueyUhpCgxp%2BeGWkZK0Tpn6ZpSQFphIbxVIhgn2zMaZI4MIUZscZWuOrpSJfkFZLO3pXgvprwVwAZRoQZIZNxDEEZ9ZbacZCZbJVwyZqZw%2B3W5ZmZ0Z6sOZeZARNOoODIJZo5HOGZupk5VZ0YNZmBdZE5rwXp68zZ/pgZwZQZHJdAPZO5MZIA/ZiZFow5dp45q5lZdeZw05lpbxWGfIxZx6S5ZG9Zzp1Zju6pMpqp1wxuvp8IQ5qgrA6okoHRO6QFcpm6IIYIEIMCMIFR6wSQN%2BxSQJuwi%2Bc%2BKpQx0e0OZwxAwADZ%2B5fprZCaqAVAJYEApF5FCwTE0ikgA5rOfYkhBhP%2BQgXgSQeQV8NotAfYHRZ2fFAlQ4QlBAaCGg80XFbgRqnkVAZuOYSlKlBA2wnk6AKwMcf00p1w3IUlhF5wEirwto0lsl0id5pZo%2BE%2B8qBqBAfFoyRqAqUuDlTl2Eyl9EBAal3l2wDaa0IajlMFuI2leZe4/OC2AxMIXFB%2BzR1wu8rwIlEJiU/qlY0QBAEAIaCgXoaCKYuIhl5lMlGS4lqQglRVGgKICZ3FCFvwIFeF1MFRjE2AUFipxlhhtVhw/w8p1wmS7VKsBaDqEaUa5CpaBq5a9C2AREZFFFPpVFWVNCmAtF9FjFaaLFGqbFN5Ms5qNVvVpVSgkl5l7VYl/FZVh1wlaCXA80mSuIGgnkiQVwZgnkwIel8VeFhVwlx1dyZlF1V1VlRpdpFJ%2BqfERqmAJqxAZqBRMIilVwlVZeblINIYFBkNqRuID1ZgAVpSIarIyNSgUNbgL1xSUVH0w2d8cVT2CVSV7VrxeVZ4GVWVZauV%2BVMIH10lD1vFp1B1rNl1VVgFnViFHVu6u8H2xAzVrVMF7V8F/N3VuFu6c5KwSgbwHRO2xFpxF%2Bn6gcXOBhKtJxvB6tz5mtb2MlXBsmqtetYusOHFBxRCXAJtVJWpatFt6sht7IaCGNu1eFNwPgLARIVwjFPgME/VtZEUVxFo1Yxt2twdkMKJ36AgPNkdW5IdMdYdcd7t6xUdztCq4dhNUGVM%2B15Vn1olUCHNEl3NZg80Wtyucdd1%2Bkl1RUqd9dDAaChN5NPV71P1yVEBgIplUlbt801lP52qmxpSNOEdVdTdcNcyPi94o9ttMVcdD14d7tcyJko97t49zd78C29%2BuIWtrdste8VNHRNN6VjQDN41TNCMbgZdJVnNBd0ly91Vud/NAtP%2BxuKwjQCAkF0F9AktL9Atbdu6H5xAdBLAStKVOt1JNWvmydMs%2B6dtweu2SRTtGtCqWGEd6dptTGNJMDqWyU6Dc9mD9tuIOD4usD/mbtfNnt3tvt/tuMQdiRmdmsfMGD8RUD3mW1li8dRD1WHDg5LDadbD9ifDVtLDOd%2BlDV%2Bd51ndGpZwJ1pdHdzd118D%2BRxVXD7NtMbt42m9fab1u6rNX1s63NwI/dANNlkSAypS6DcNOWEdU9JkBDlGddXDy9Rx6D69YjW96y52XJKj%2B9gth9EFx9ZR6Cp9mV2Vl9BVijwIt9CjvdLdT9gIHASwtAnAAArLwH4BwFoKQKgJwEYpYNYA%2BB/YDuiDwKQAQJoMk0sHyCAGk5IPqBoAABxmBmAACcbTXAaTzTTTXAcQcQ0gqTHAkgvALAEgGgd1WTOTeTHAvACgIAd1lT2TyTpAcAsAMAiAIAKwBAuZPlFAEAaAaodA0QoQXonAqgTTCBAAtAgZIFcMAMgG8VIPqGYLwByIQCQHgLgokPwIICIGIOwFIDIIIIoCoOoMs6QLoIkObteEkJwDwCk%2Bk5k1U7k5wOePiLs1cLRVcBc9c7c/c481cM8%2BXRAB4Ec/QNQWUwsLwEs1oEsBAEgIc0kMc2QPs0yyyyAMAFIE9TQMJbFJQBECixEMEA0ESPC7wMK8wMQESOeBENoDAeK6QIc1xOeAwLQGKxC1gBEF4MAHJLQNEYq1gPgkYOIJq82TUDJPMxCxQZoiqIq6DUMzk4SBENeNKx4FgCiwGHgGM9wLwDJMQLQUoHcMa8AISEYFU0sMpaYQoO7C8ObmBFk%2BU788IKIOIEC8m6C2oCi1C/oIYMYNYNYPoHgBEPM5AEsKgFhRkFa1czgrAqYIU5YGYNM/61HFgKWxAEsFUDUM4BAK4OMK0KQIEDMCUGULkKkOkAIP22O/kBkH0CO4MG0B0LUFMFO4uzAcuz0HOwMDEJMD0KuyMJu8O9uxIJ2yU4C4ixwBk6QFM7wDMzi5czc3cw808w0yS7gB85SyCFwNSxUxG0sDFAxIMB26QLU5IMCPqG08CAMxoJIGYJIEgRoGkwgW0/oJwCM6QGM8CFwPqAgVwAgU02070wgfU105BwgdeyizM3Mws7%2B8s/Sxswy1sxi/iOQJQOyxS6c2wJwA0CwLSHEFc0wARP%2BFwG0/qNhzk%2B80QK23oMm/82m9IBm0oFmxC7oE9TC1aOKxe1eze6ixwOizs/iFi1QPe3i3cxWMJ6J%2BJ62WS8yxS1CCCGYD%2B7Sys4x%2Bx9EKxwc6gOS4MOZ1y503dbyyqPdAK0KyK9K4q5K6K7K/Kw4Iq8qzOKq%2Bqyi1qzq3qwa766QEa3m6azk/gOyBa68Ciza5JHaxlw6yi86660SO6xsDk16z6%2BU/64G5gMG9l9RBG3wAYORbG5gPG7qIq7J6m4Cwp7IJm%2BCzk6p7m%2BG/W1YJYEWyW/AOW5W2QZwDWwiHWwW42829EK24V2W7YO0Ouz23254C0P4CGFu3MDu8kOO50Pu3kBOwwJd6O2u9210Cu6dxMAd0uwIN0I0M9wuwe2MJ9wOygv90e1dye8sKsOsFD0M9p5R5wCZ4%2B0JzRCJ2J4062e%2B1J/Z1h053%2B6QAB1gDEMB0M%2Bh5h6JzB3EGk20/08CLB/B5IIkDp1R7YDR85/R/AIx9s7sx5258QJxxsDx/i2A7SG8bSOj66PCG8/gFJ18zJ7IHJ8N8C/IEp%2BNzoCADE%2Bp3C761p8ixCzM/p5i9i6oCLwoGLwwZL7uBBaS157Z9ELj8CPj3R6s4y3byy3z%2B7xS1ecgPxWghL202glL9Jabwp3QEF/MxAIKxC5F%2BFxl7HzK3Kwqxl/F4IIlxq7l5gNq7q2IOl%2BU1lya7V7wHl%2Bu5a0V6oLaxsOU%2BVxC5V6KzV561HA1369EM161ya%2B1y71G913GwmwN4r0NxICNyC2r9m5r1N/mw2zYM6%2B20t50Fa5sHajN9YE27ey2183t8B1250C4CGPu0O8UMe4kA93dyD9O49wD9d9vxu8D9kKD4d29399MIf5D7u7f2d2/8/7MC96ezD%2Be6h5e317TMkeofK4KL3F5W8VQNvbHiQFx7fsaWBPInkBwvbk8QA7TfUMCGBBpNumTPCZpgLiD4cKOBvTgNR0WYE9QOaTCDn0ziATMmmkgTplwBaZBkABwIIAbexIG0c6WF7V5kQOAGzNOB1TUgP6zSDOBJAQAA%3D)

## Links

- [source code](../../../../conceptrodon/descend/descend/omennivore/easy_kindred_repack.hpp)
- [unit test](../../../../tests/unit/metafunctions/omennivore/easy_kindred_repack.type.test.hpp)
