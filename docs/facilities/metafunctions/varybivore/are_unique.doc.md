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

[*Run this snippet on Godbolt*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKxcpK4AMngMmAByPgBGmMQgABxBAA6oCoRODB7evgGp6ZkCYRHRLHEJybaY9o4CQgRMxAQ5Pn6B1bVZDU0EJVGx8UlBCo3NrXkdo739ZRXDAJS2qF7EyOwcAPQAVLt7%2BweH25smGgCCO3sA1AAimCmujMh4mApX%2Byfnl0c/B59npwBZgAzOFkN4sFcTMC3AQAJ4PAD6BGITEICmh2EBgO%2B2yuADUmHD3nt/gRMCwUgZydC3EwvEQCU08EwYvRMYDRsQvA4mXDsQB2CxXaaOZBXNAMUaYVQpYhXemMgBuYi8mChQsJxBZbMwJgFN2hwv1huBVnOOP2VyECAZBHoJN2ZIpVKYNJhitQADofRzzlyeQRrbaCPa9WbsV8rWdiJgAPJK%2BIGFIpcLAR3HQHkynU8N0hnen0ASSlDwcmHQWp19AxwKx/pRgauMfjieIydTRkBICuKS8bLw4sJ/JhJYUZfJleZrJrmJ9XsF5rOVxXIsbvLujTogNXGqXu932dd7vzRHnfuXB5XAd5ymIqCIyiYwD15yvK/1wq8GSMV3hDyhYEbiuJVUDwdAjQ1U191XE0jUjC5NiuAAlTBkFWDJEyuOklBAHdVyPXNaU9K4xwnNMqxnTBSAVAt51Q0ZKN1Wt60va91yDO8H1QJ8X3wj8hX4g9NiQkwADYNE3NFaHEjQrgAdzoWg11QFIrljdDiAyAQaKYZAEBeJU0xFBASAIABaZ41i8QgFzfd9v2M/91WhYDRnQEAUAEfA6mYGT7KvWkhPfNcPJAPAFERGImCURFUCoWlh1pMi0McIwmPZOtSBbBMkyYFM00xTyVW8aioQCkLbkwLdaBo4L3xytsO0K0dS1SisMteecaJShwKOnXULxCoqQGczzCLddUuMfZ88wYghOoUc863GhFwyXer2LdQcJQEaVZXlGJUE8EDVRcoV3M8iLEQUVhMERJVaWcmjQPAjkDXgiq4IjC0viQiwYvVHD2CEiaTxI3q0uATqhtXG9OPvGa%2BNa8dUv67UqNhgSYKvRzf2cwC3IIMLJR8rIxE2wC3Ep3dLvCyLoti%2BLEqJZK2r69KBsy7AaMavKCq7FaQBKtU6oqkLXvQUgadXG07UytxIY6rmup9Hr2ahmG60pkbnM%2BtiD0p0Udslfa5SuI6TpF86LAYB9QquyLbrYB6nrWl6wIg7WPp%2Bg3vo2iqwbzT150WrGrjx9NeJcoCrmmnjZpZjHmOWrFff9hDcV%2BbPMyja4ixzClGEaXyM3%2BLOc5%2Bf4sxdIiPQLK4ADE8C0haVd0uifXmsPtYbbleRbOQGDwABHNVFyE43xVN8kDot47lOt8q/cE8XVzAMBm1jXL23yztgFpZvW611iQvG2vJrjxOYW7lWlt9XuDd3YqzqEjOLR9gOLkrnPy6tI/RhXGwKoVgVJ1QfEtD/X41cGzbWQIiGKShmgQEHsPMeeYNA0SCFcMwNFzJcBGtbBY%2Bsp4IIUEgggEAN5b0wEPUe48YSYKuNg3BVx8FYMIWdYhZoOBLFoJwfwvA/AcC0KQVAnBqaWGsCKFYawXIgh4KQAgmheFLAANYBEkF6DQiQzBmAAJz6K4P4HRyQBQCmkPwjgkheAsAkBoTBwjRHiI4LwBQIBMHKJEbw0gcBYAwEQCAFYBA%2BwEHIJQNAlI6DxEiHdTgqhEhiXMmJSQVxgDIHFFIL0ZheAVkICQcCeh%2BCCBEGIdgUgZCCEUCodQ3jSC6CCPJVEKROA8D4QIoRKixGcDjAyUJVx4pXASUklJaSMnMK0WYK4EAPBRPoPKcwwIuALF4F4rQSwIBIEiameZ4SIDbOiQkYAUhcE0FoOSLSlAYhdJiOEJocJWm8FucwYgcI4wxG0KlR5pBIlsEEHGBgtAHl1KwDELwwA6S0FoO47gvAsAsEMMAcQIKW5o0TDC0RMo0IMg2Io8I5IrGiNoHgGIqJXkeCwF0lEeA7GwtIG2I6Sg7gIqMMSowKilhUAMMABQ%2BIXjyTjA8YRijinCFEOICporqlqC6Q0/QiKUDWGsPoEl7jIBLFUr5GF5l3KuVMFIywZhnFtm1FgNVEAlh2DRs4CArgJh%2BCCKEcIAxyhDAKBkXy9q9BpA9VkWYgwEgjBqNahgPRxieDaHoK1fV6hjD6M6uYbrbBxq9SMON/rXWBstbI9YEh2kcEEaQJxvAXFDMSck1J6TMmTOmbgfJCyFErKURypYCBMBMCwAkC1pANGSGBF6fRwILEaEkGYSQEkND%2BDEvo/QnAbGkDsUsr0YkuBiUSPo5IYl/CSGMYOsSRaukuLcR45t3iNkBM2UEvpDI9kHPmbEtgnAmgsCVAKcyTAJQGF/FwfRXouDaNyT5ApHkgiitKRK6QUqlAyrqboXBTT8qPPzYW4t3SOC9JCQyAZVAy0jNSeCRFzDf3/rkjM1Acz4hQhBGYJtayfGXrvfEW95GdlDAI0YH9XBMFnIue4iA1y6nPPud8oTrz3mfIcN835xcAVAq6aC8FkLoXfPhYi5Foj8AaUcOirpWL0Lkm%2BfimoXTiWkvuRSjYojqW0sUQy9ImBmVqbTByvg3LeX8sFYwb5YHxXlMg7IaVtTRFwfley/VVhLAqpiOajVKQtWcB1cTPVSrDXGviKa148BLXBpjX4W1DB3ARryI6grGb5juqKNkIrDrSA%2Bsq2VpN0bfJhpaNVqNOXmvpoTQGqNKa2tppmN1zNeblirFzcs2dBbOl1NLcMitn7CM/r/do2tQGG1LNoy20gbaO1DG7VY%2Bdi7f0joFP4fR5jgSjvHTug9M3ODHs8S5vxgTgmhOYxR4gD6NjPtGSwBQSpxRKiW7mUYgH62FNA7IcDfnKnyGg0FnQIBgSkAQy02FyHpvOJ6deoMgzVC/f%2B4D4Hk1AFkY%2B1R4EwJNtnt8Vsljhz3usYSADlMD0f2IhBwQRE%2BPIN0F41cm5dzXkiaF28j5Xy6XSf%2BYC4FGnMBgohWIZTdLVOsss3C1FfUdN1L0ziwzghjN1NM2SuEFmqXahs7wOzTKKROfZTTrlz53OYAFUK7zUPfMSH81U%2BHsqkeheMClmwpmYtiLi1kGFmxLrhesEaktJrwKZfVZ0ENLgCupuCKVob5XauFE9f13PvrijZ8ax17ofXcg1aa%2BXwbpQesDfDZX3rteXXlezWN8pGPbtY44EMgnAOQLE/JKTutRB1vLNWVtnbnbKD5sOyAAxXpKf%2BBMTuhxlOBRru7yW%2B7tgT10YWOokAkh/ADq4OYhxiRJBGK4Losw%2B6rHAkxzv1xp71n5pydvtDk%2Bz1LDbNpPwSQIAA)$Done$

## Links

- [source code](../../../../conceptrodon/descend/descend/varybivore/are_unique.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/are_unique.test.hpp)
