<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::IsDawnful`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-is-dawnful">To Index</a></p>

## Description

`Omennivore::IsDawnful` accepts a type.
It returns true if the type is a packed `Dawn` and returns false if otherwise.

<pre><code>   Type
-> Type == Dawn&lt;Items...&gt; ? true : false</code></pre>

## Type Signature

```Haskell
IsDawnful
 :: typename...
 -> auto
```

## Structure

```C++
template<typename>
struct IsDawnful
{
    static constexpr bool value {RESULT};
}

template<typename>
constexpr bool IsDawnful_v {RESULT};
```

## Examples

```C++
/**** Vessel ****/
template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
struct DawnLike;

/**** Items ****/
template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
struct WillLike_0;

template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
struct WillLike_1;

/**** Tests ****/
static_assert(IsDawnful<DawnLike<WillLike_0, WillLike_1>>::value);
static_assert(! IsDawnful<int>::value);
```

## Implementation

```C++
template<typename>
struct IsDawnful
{ static constexpr bool value {false}; };

template
<
    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...> class Sunlight,
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...Sunshines
>
struct IsDawnful<Sunlight<Sunshines...>>
{ static constexpr bool value {true}; };
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCAAzACspAAOqAqETgwe3r56KWmOAkEh4SxRMQm2mPYFDEIETMQEWT5%2BXJXVGXUNBEVhkdFxiQr1jc05bcPdvSVlgwCUtqhexMjsHAD0AFTbO7t7%2BzvrJhoAgls7ANQAkixJ9GyCTDUXu0en5wefB28nxycEmFuBgBJlibgIAE8koxWJhQdg/sNiF4HNcFAARJgAdwYVC8tD%2BJgA7BYLpNHMgLmgGMNMKoksQLhFUJ4LgA3MReTAXYkWKhiJTE9Gg0lCkWE04AoFPOGnUFuP4XJUXKV3GXy1XAuFgzXqnWAtUg/XSo3gg1ajXmvVuJheIgAOkd8KpBgUCkd9udyFd7qdsWwLqYbo9Xp9If9geDfoD3qDvs9EdjbouQi8DFoeGACAIpEVyt1poL2rNJuLRctpYrhuLtod0cj8dDcfDMbD9aTjcTbYTrebjtTNIQwUwCkJ/sRBGRqKuGOxuPx8oHGazBEXaYUQ5CnYR47lJLJ9QpVIEtPpjOZrI53m5vMnXLFsVFROFj4lZy%2Bnx%2BH02F2wqlYdzcq8fzfh%2Bhxvt%2BFwAGojnYLzgZKVqFkhZYoVWFrGtW6HWuWYK1qgLYNoRHbEd2TZRj2RHtmRu4nEiKIEBcmI4kEADW2pWHK7y7NcUoKPB2w/LhJZYZhGEieJwnCfhpF9pRJHUXJ5HblRPYTlOjEAOp0LQbGYAA%2Bho4pcf8aFiThZkSRZlbmaaMmKRRymyY5XZKa5LkIqc9GotptC6Xg7H6Vwxm/NxlwACojgQ/HAV5h54Mg%2BlxtEBAQDOzHzgSYIZXp8q%2Bf5gUaKQFz5XpQXwvCIAgFeXJzCF5IJUlbopRAYBgGiGV4llbjBKu/pVTVmB1a%2BpwcAstCcPEvB%2BBwWikKgnAKpY1hkksKw3mYsQ8KQBCaGNCysSA8SSPaGgABxmGYACcV1cPE51nVwRJEtIE0cJIvAsBIGhFTNc0LRwvAKCARW7bNY2kHAsAwIgIBLAQSR2uQlBoLcdDRKEsKcKoZ0AGwALS45IFzAMglJSPaZi8Jg%2BBEMQeDoHo/CCCIYjsFIMiCIoKjqODpC6G0WLEEwSScDw42TdNe3zZwADydqI4xqBUBcOME0TJNkxcFNmBcEAeGj9CMuYW1zLwYNaAsEBIKjSTo2QFAQLb9sgMAUhmHwdAAsQwMQBE0sRMEDQQmLvCB8wxAQrLETaJgDih6QqMPAQsvpiHfNYBEXjADafnA9wvBYCwhjAOIGd4MQceOGyI7S3Scd2ms229VU0sZhEwuRx4WDS5OeBfQXpA18QzJKOigIlxmRh7QsVAGMAChQXgmBYrL0IzdtzPCKI4gc1v3NqNLAv6CXKDWNY%2Bh4BEwOQAsqBJDU%2Bf48M6CguipjLZYZj/cP9NYDfEAFh2CrhkFwDB3CeBaP4cB0x%2BgxDaHkdIAgxitGSKkJBDBYGlAGBMKoICBBdFGJA8Y7R8G1BGD0YcMwcG2AoSgvQkxGhYNmFwIBa1VgSAlhwKapA/q8ABqrPGhNiak3JidXWEBcCEBIDyTarDzYzwWAgTATAsAxEAaQQ6khYj2iurEF6GhJBmEkLjH68RcZXX0JwD6pAvpbXtLjLguMzpXUerjY6d09G414dLAGQMQY7RnpDGG1s4YKyRo7Z2RtMZsE4A0FgbIiT4yYIGIw2srr2i4KdamtMSAMyZrIVmu9pD7yUIfPmugPZCxFqHLhPC%2BEyw4PLBGdoLjK0EerYmsY0lcAyVkjQesDZ2yNrI2IZgzaBPBlbG2qBDbRGRk7WZwyBjdLdrdIqNBaDe19v7Pm4dg4J32ZHaOsd46DyTowFOadpaZ2zrnWg%2BdtpF0nmsOa%2BBK4ODwDXfOc167IEbgnFub05rt07hCburzzb0wHttYeo9MDj2LkYKeoApl8HnovZeq914Jy3kU9mJTZAH15nNSpJ9p4fysJYS%2B194B3wfhkJ%2BL836UusN/fhv8Ga11vqQz5zgICuHoW0QIVC4G5HQTUIVaD8gZGYTQ4BfLyHdClQqmohDKHFDFRMOhxDUGMI1X0bB8C2HLA4awqx3CpZ8wEWrYRqTgDpMyadPWUi6ajPkZMy2SiVFqMoFwmxdiMmGKJPEK6z1YhGJMZINoDS/G2ACRbCGUNYbw0VgsqJGMsYcHiRrFgCg2SUjZL0%2B0Wphg5OkX/ApLMd4Es5vIMpJKdBxFINU0WBc6lWv%2BnLcJSsVaqFzfmwtxbS2MX1ks%2B2ozYgTMTdMlA46jbpvnQMAtSQkj6SLVdfSI79L9pKV7aIOyA5B0joc49UcY5VwThcwQqdaDpzeZgLOOcxAPITs85FkLSDvJAd8uuqgG4AkBYIVufNQXBwhb3aFCc4WpARRPZFwRUWW3RUwBeS8V5r0YLiwpNaJCEq5g2o%2BzaDAUvPtS9uAD6WP04OsF%2BZ9P4WHZfNTl/86W8pqGAiB2RUEis1Ua8VMrkG6oExguV8D2OdB1dxhheDFXqrEwwqTUDtVTFFfx81Ch2Hsw7T461nBVYDoLeyYdMphgutycbOR07FGkGUaogYGi3oBpANde0sQEj3WjT9dzRJnG6a7YDeNoMbNaPiLop6RIfpnUkLdLgF0zDeLerETt/DOAKKmVwqm/nUuBZnQsYeaRnCSCAA)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/omennivore/is_dawnful/implementation.hpp)
- [Source code](../../../../conceptrodon/omennivore/is_dawnful.hpp)
- [Unit test](../../../../tests/unit/metafunctions/omennivore/is_dawnful.test.hpp)
