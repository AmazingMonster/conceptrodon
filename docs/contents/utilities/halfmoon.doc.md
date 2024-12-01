<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Halfmoon`

<p style='text-align: right;'><a href="../../index.md#identities">To Index</a></p>

## Description

`Halfmoon` accepts a `Hail` and returns the `Hail` via member `Hail`.

<pre><code>Hail -> Hail</code></pre>

## Type Signature

```Haskell
Halfmoon ::   template<template<template<template<auto...> class...> class...> class...> class...
           -> template<template<template<template<auto...> class...> class...> class...>
```

## Structure

```C++
template<template<template<template<template<auto...> class...> class...> class...> class>
struct Halfmoon
{
    template<template<template<template<auto...> class...> class...> class...>
    alias Hail = RESULT;
};
```

## Examples

This function injectively maps a `Hail` to a type.
In the following example, We will create an overload set of `fun` using operations `Op_0` and `Op_1`.

```C++
template<template<template<template<auto...> class...> class...> class...>
struct Op_0 {};

template<template<template<template<auto...> class...> class...> class...>
struct Op_1 {};

constexpr auto fun(Halfmoon<Op_0>) { return false; }

constexpr auto fun(Halfmoon<Op_1>) { return true; }

static_assert(not fun(Halfmoon<Op_0>{}));

static_assert(fun(Halfmoon<Op_1>{}));
```

If we only want compilers to perform an argument-dependent lookup, we can utilize `decltype` and `std::declval` to avoid defining the function body.

```C++
constexpr auto gun(Halfmoon<Op_0>) -> std::false_type;

constexpr auto gun(Halfmoon<Op_1>) -> std::true_type;

static_assert(not decltype(gun(std::declval<Halfmoon<Op_0>>()))::value);

static_assert(decltype(gun(std::declval<Halfmoon<Op_1>>()))::value);
```

## Implementation

```C++
template<template<template<template<template<auto...> class...> class...> class...> class Operation>
struct Halfmoon
{
    template<template<template<template<auto...> class...> class...> class...Args>
    using Hail = Operation<Args...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGwAnKSuADJ4DJgAcj4ARpjEIADMABykAA6oCoRODB7evgHBmdmOAuGRMSzxiam2mPZlDEIETMQE%2BT5%2BQfWNuS1tBBXRcQnJaQqt7Z2FPZODw1U14wCUtqhexMjsHASYLOkGeyZJbnsHR5gnZ/uHTMen53cPNxf3V6dMXkQAdH8n2AA1MgDAoFH8fgDgaDwf8kkCQUwwRCoYiwYCAPLpBL3XIAkwaACCk2IXgcgIAEmIqCxUAICYSTAB2KxEwHswFPS7XLnvHm3bmPAV8z7fVAo%2BHQpGwyGStEy1EwiGE4jABT4tkcrzZIyUph0QEnAAimOxxFx9NOKrVEuwJ1ZjKZRvtDIZAHoAFRe70%2B31u90%2BwEAFWwQiDQkBPv9RM9vrj3ujjKJvJeKY%2Br2e6bT1y%2BvzhCKV%2BalyKL8ttDJJZIIpoA%2BhpDSzmc6kg6GdmhW9U8Ku5307nxaXC7KC9LbcWFfCKwRSeSsTWuA2rE6XUSA97AQAxPDESbBzC7qOuoloBiTTCqdLEQH9wFULwMCBU2g0ukMa5zjQAlaLwHETAETYGFvMQlHtBtnVXY8BDPC8rxvO8HyfF9LTcOcuC/H8/wA4ggOnLwPgscCj2JVpHGQGtpQSAgIAYVBqwQx9qVpFCP3xRsnRWFYVyTEjcXIyj2moe9GOfZi31ONC2KXI1OO4tcvUBIRMBPdA9wPBNiPMJIIhBLwsENU5vjoQgAE8NR4k8YMva8xUBYBhKQsT33SOsMIAWihSZ0BAEAqBAzAawIEzsTkqDTz2WCbKIOyHKY19nPndzPIIbyQDwgKgpCltiPmMiKLBKiaLowEsBBTLMGgYSvJ80raAANzEa5HPiiSXM/Sd4QgTiVh8hrvEwLjssg3i8oE6javKyqH2qkBar6pq4pYlz0I67Aus43qxHwwaLA4NZaE4ABWXg/A4LRSFQTg3GsaxAQUDYtkwQ0zCSHhSAITQ9rWABrEBDskH4NEkLgmSSDRDo0Mx/H8MwUjSA6OEkXgWAkDQNFIU7zsujheAUEB0Y%2Bs69tIOBYBgRAQA2Ah0m%2BchKDQA46ASKJWB2VQUn8Nz/EkOzkGQQEpB%2BMxeEwfAiGIPBvK4GRBBEMR2CkGX5CUNRPtIXRpYAd3NdJOB4fajpOtXsYxb4aerVAqEBdnOe53n%2BcFsxAQgDxGfoK8tK4FZeEJrQ1ggJAGfSJmyAoCAg5DkBgCkMw%2BDoPYd0oWI1diCI2hMvXeFT5hiBMjFYm0ZTCbehm2EEDEGFoDOidILBYi8YA3DEWg8e4XgsBYQxgHEGv8D/Bw8Dq/c1fPZTvh2N6Ij2BHztoPBYnNXOPCwNXpzwFG29IIfiFiLJMCNfYu7noxPrWKgDDVAA1PBME1rFGEzpW5fERX%2BEERQVHUGuNf0LuUBuyw%2Bh5540gGsVA6Qmitzcl5Y0phLDWDMFjbeEssAgK6r0IuuQXAMHcJ4LoegwgRBGNUMY0sSg5AEDMPwZCsgUIYIsUYiRpZ2EwQIAY0w8GFGYQ0VhzQphDCIUsUhth%2BFUL0PMdoDCSFMLWPdTY2wJAGw4MdDGxtODWw5lzHmwA%2BYCwBk7CAuBCAkGeq9b271T5rAQJgJgWBEjoN%2BpIJIPxAhJCZJIIGZhJD%2BDRodHoCMkakBRq9H4/guD%2BBSIEFI4T/pcEOq4/wqia7Y1xvjCxRN/bkwDpTM2tMw4R3dizNgnA2gsDqkyNyTApS6i4IEH4XBAYizFiQSWeg37CFEC/aQ7SP6q2/iAWO2smC6zbkolRmNeAm1yRbK2pTymVOqcAAWdSGn1hdqgN2CRTFmHMb7Ym2SCkJDpuHDZwd3YgDmRUxERhalcHRjQWgCc8YQGTjXbO6dH7vNzvnQuDhH6l0YAQCuVc1Z1wbk3WgLdH4dyPjsc6fdMFD1budUeyBx6Pyng0NWc8F7p2XnCn2EsN5vW3rvJQB9O5GGPqADJfAL4KGvrfe%2Bp03rtOfgrbpshelf3OroWOBgT5wKsIAnFaCwEQNyFAmBSQjRCoQUghIKDh6gIwQPZwEBXBiOloQyojC9DkKaFqjItCmhSOWNwvobDRGcOoaqpo7CBG6ukeI61BRbUSMdcQ81siHoKK9voQ2SSsbqMuQs65Szan1MBs7Ix4tTFex9pY0g1jbFjHQQE5GyQ6lAyZPEpkoNJBeO5tLCZF1OCpIJqfEmWSkBU3Nscw5xAik7FKXbFgCg6r8zqpGy4kwmnGJQW02Q7KJCcvfirHlOhkikCGSM/WAblFG2SZwU21NviAktteYgLA20dq7T294u51mbI9i9JIuyq0HNOSHBt17zmdvSC5btgQay9oIBRbd3M46PISM81550vnVzeoBn5Rd/kbLLkCyu1d4WYHro3Zurc3owqpQS2u25EXDxrqi9Fm9MUz14DixeJl8WryJY/Ule8KVHwiDSv2dKmBXxvnfbELLeBss6RypW3K1a6CSL/QVACbCivgOKyBnA3TVTlZYRBkzkGS2Veglhaq/AapwUanVXrhEGtyEanT5RBF6otbwh1RrlP2v4Wa4RHqzOWcM86/1cjHqKIXeMtRHAt07p5u2ztgJn0/DfTG5pp6zGJoyVYmxdjKBKMCSjMwdSkhJEOhDYGaNEtMgiUGyZ5bbBpL2ZxUgjjDouMOikKGgRJCBFBm4rg/GEZJCXcGnG6S/ZKOFllstzX8trG3tkZwkggA%3D%3D%3D)

## Links

- [source code](../../../conceptrodon/halfmoon.hpp)
