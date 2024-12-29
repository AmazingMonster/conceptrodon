<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Day`

<p style='text-align: right;'><a href="../utilities.md#day">To Index</a></p>

## Description

`Day` accepts a `Dawn` operation and returns the operation via member `Dawn`.

<pre><code>   Oper
-> struct { using Dawn = Oper; }</code></pre>

## Type Signature

```Haskell
Day
 :: template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...> class...
 -> template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
```

## Structure

```C++
template<template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...> class>
struct Day
{
    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
    alias Dawn = RESULT;
};
```

## Examples

This function injectively maps a `Dawn` to a type.
In the following example, We will create an overload set of `fun` using operations `Op_0` and `Op_1`.

```C++
/**** Operations ****/
template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
struct Op_0 {};

template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
struct Op_1 {};

/**** fun ****/
constexpr bool fun(Day<Op_0>) { return false; }

constexpr bool fun(Day<Op_1>) { return true; }

/**** Tests ****/
static_assert(not fun(Day<Op_0>{}));
static_assert(fun(Day<Op_1>{}));
```

If we only want compilers to perform an argument-dependent lookup, we can utilize `decltype` and `std::declval` to avoid defining the function body.

```C++
/**** gun ****/
constexpr auto gun(Day<Op_0>) -> std::false_type;

constexpr auto gun(Day<Op_1>) -> std::true_type;

/**** Tests ****/
static_assert(not decltype(gun(std::declval<Day<Op_0>>()))::value);
static_assert(decltype(gun(std::declval<Day<Op_1>>()))::value);
```

## Implementation

```C++
template<template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...> class Operation>
struct Day
{
    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...Args>
    using Dawn = Operation<Args...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGzSrgAyeAyYAHI%2BAEaYxCCSAKykAA6oCoRODB7evgHSaRmOAqHhUSyx8Um2mPbFDEIETMQEOT5%2BgTV1WY3NBKWRMXEJyQpNLW15nWN9A%2BWVIwCUtqhexMjsHAD0AFR7%2BweHR/tbJhoAgrv7ANQAkiwp9GyCTPXXB6cXV8c/x5/nZ3OBEwDwMwJMAGY3MDQa9MJDoSDHnCETDkeCoWiwfDMUjsai8SjcbCMW4mF4iAA6amQ7DXZAGBQKamU2n0xnMmkQukMphMlls3n8rk8jkC7nsvmc1kSoUKa4AeRScVeWVpgLGxC8DmuABEmABPQEmADsVgu10t1yxRMRJJxdvRDptpJdzsJro9DvJVJFkuFMtFUvFQYDgrFfrlIf90vOxGACnVFqtXgyRj1TAA7gxrpDdYrlcRVQIEXGEyHIeaASbdZXjV9fo2PoDvjtrgAxPDEMbXbCqViPTDvE4tptj/6jm5KlX1eXNi5ugn2pdOlf44mrjfrx3bn2oaNRyMRwMxg/H8PBo%2BXwMaghanVKgD6GlzZtNtYhVcBi63tp/O7/L010A5coT3M9rwvMNZXPGDILg6DQ2lJNzk1bUCALR8uFfKwazrC5Jz2a4qC8HN53ONAGDGTBVBSYhrmiVBPGI0iIH1I0oSfDRaUWHDrmITACDWHMqDEJRK1fWsCIuSjqNo%2BjGOYkiGDYw0ESfLgeL4gShOIHM7y8HELEk%2BtLgOa4ABVMDGOcRwuGZHGQR8pTiAgIAYVAMOU1SOLcLj1TfGtFkWfDUKaRznKZVzqFY9j1JSLCAtw3VgtCwix1%2Bf5W2uIRMEo9Be37UEh3I1sMr%2BUzzAhMIGS8LBc0xA1lUfO8mEIRNuVM7LgFI4c9n%2BWTgXk6492uHqVLiziEu47leIAWjZMZ0BAEBRNoJQWqaozTMGmi6JGilUDG2K1KmxLZuuBaJSWlaDMwTblTShsbismy%2Bp2f4HLwJyXJadzPOuLAGQILboFYm6QCB2gADcxARSa/Om9VuQgYLFhW2HvEwELP1vVUfqiv6oZB5UwZUiGocx%2BHTsR87sFpVHgoxsRDJxiwOGWWhOESXg/A4LRSFQTg3GsaxrgUVZ1iHKqeFIAhNA55YAGsQESSRKQ0AAOMwzAATl1rhEi1zWuBNE1pC5jhJF4FgJA0DRSD5gWhY4XgFBAB35f5jnSDgWAYEQEBVgIFIKXISg0AeOg4giVhNlUTX/DmwIxuQZBrikSkzF4TB8CIYg8GWrgZEEEQxHYKQS/kJQ1AV0hdGLzMixSTgeE57nebrl2FQpUOMNQKhrgTpOU%2BANOM/VsxrggDwo/oeiZcWXgva0ZYICQSOUmjsgKAgTft5AYApDMPg6GBbtKGiOvojCZoDVb3gb%2BYYgDQVaJtDyr3Zcj54CAVBhaD329qQLA0QvDADJLQdaD8QEgkMMAcQwD8ACQcHgaG1k640TyhSTYsswjAktgLWgeBohFhfh4LAdc7x4FttwXg6DiCMSULqOBRhiFGAVssKgBgEwADU8CYEzNOPmst%2BCl1EOISuYjq4qHUMAhu%2Bh4EoFFpYfQJD3aQGWKgFIs5OBzSWnmUwlhrBmGdgwguWANGoy6J/LILgGDuE8O0PQIQwiDAqMMYuhRMgCEmH4Lx6QfEMDmEMeIxc7C2IEL0CYTi8jhNqJEho4x%2BhuPmJ42wyS/F6BmC0EJHiwnLAlmsDYEh24cB5o7LunAh6J2TpIVO6dM5TwgLgQgJBcxmAhFwJectOHLAQJgJgWB4jWJVpICElJdYQnNhoSQZhJD%2BHtokfwut9CcGtqQW2XTKT%2BC4P4TWusTb%2BDVobKZ/hKnAJdm7D2vTvZrwDuvIOvcw6733vPWObBODNBYNDE0c0mCSnTFwXWlIuAaxznnEghc9DSLLpI6Q0jFCyLrroE%2BTcmAtzoWUipTteDd2ef3Qew86mAuABnEFYKXwz1QHPOIHSIRmB6SvH2jy3lxHDnvGlW954oAMEYYFXAHY0FoOfd2EAr7AKfnfGBUqX5vw/g4GBP9GB/wAUAgWoDwGQOgXQ2BLB4GII1V2Wx6D3bAKwcgHBMD8G1DrsQ0hd8KGbAFtQ2hssGFMMwCw/VbCwigDuXwHhCh%2BGCOETA2FEiK4ItkEi2u8iQAnz5cYFRNh7VWK0TorIZr9EEHQIYlNpi8XmMLhgzRNjUHOAgK4LJxdXFlFCXobx9Qa2pECfUPJCx4ndCiZk2J/jy31GiSk%2Bt%2BTsm9tyP2nJw73GdsKZLEp3S1nlM7pc6pxKU68iBRSjW09Wn53pd05efTSADKGcMaxlsNlbJBbMk0iRdZmwhHMhZkhi64sFpwa5ntOG%2BweUgYOfcOVsuIB8zY3yU4sAUNDdO0NgWUmxGMCFbSLEwtkHCqNVdY1yIFroCEpB0WYrbkunFVSOA9xDhSa4A8h4QagzBuDCGMLUtpQvTpEImU/tZVy7eQHuM8ugykBKsHdaPkY4%2BVQnRhWisvtfW%2BL8ZVydfu/T%2BSqaW/3/oAuumqIFiB1bLLAPqEHOt4Mgk1GDzWqGwcCa1ghbXAPtWQg0TqqEFzdfQuInrvUGr9T%2B7hTA%2BECKEcqERvAI3lwkNGwQWGUUgDw0m5RxjVFpvgBm3R2wbpGKsJYQtgti2WJSwOuxVaHEtrrTO9JTasgtsqyUVJDau2JKHS2iJFakmzDq6O8J47nFdfayO2dKxikV2xSu52a7aPQeuMJ%2BDcIewtMhaxrpHG7n9MGcMygZSr0JpBRCCEiQjavvtrtk0%2ByLljddrYG5zLgqkDGYkSZpsTT201pIA2XBtZmHOZbCEo28WftuavMp2czt/Yu9d5YDCMjOEkEAA%3D%3D%3D)

## Links

- [Example](../../code/facilities/utilities/day/implementation.hpp)
- [Source code](../../../conceptrodon/day.hpp)
