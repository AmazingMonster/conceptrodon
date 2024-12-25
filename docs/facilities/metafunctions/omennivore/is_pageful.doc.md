<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::IsPageful`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-is-pageful">To Index</a></p>

## Description

`Omennivore::IsPageful` accepts a type.
It returns true if the type is a packed `Page` and returns false if otherwise.

<pre><code>   Type
-> Type == Page&lt;Items...&gt; ? true : false</code></pre>

## Type Signature

```Haskell
IsPageful
 :: typename...
 -> auto
```

## Structure

```C++
template<typename>
struct IsPageful
{
    static constexpr bool value {RESULT};
}

template<typename>
constexpr bool IsPageful_v {RESULT};
```

## Examples

```C++
/**** Vessel ****/
template<auto...>
struct PageLike;

/**** Tests ****/
static_assert(IsPageful<PageLike<0, 1>>::value);
static_assert(! IsPageful<int>::value);
```

## Implementation

```C++
template<typename>
struct IsPageful
{ static constexpr bool value {false}; };

template<template<auto...> class Sequence, auto...Variables>
struct IsPageful<Sequence<Variables...>>
{ static constexpr bool value {true}; };
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISRqkrgAyeAyYAHI%2BAEaYxCBmAMykAA6oCoRODB7evv6BaRmOAqHhUSyx8Um2mPbFDEIETMQEOT5%2BATV1WY3NBKWRMXEJyQpNLW15nWN9A%2BWVIwCUtqhexMjsHAD0AFR7%2BweHR/tbJhoAgrv7ANQAkiwp9GyCTPXXB6cXV8c/x5/nZ3OBEwDwMwJMiTcBAAnilGKxMBDsICxsQvA47gplExgJgqF5aICTAB2CzXGaOZDXNAMMaYVQpYjXaKoTzXABuYi8mGuJIsVDEShJABEIWSRWKiRdgaDXojITLHnKIW4mF4iAA6LVI6kGBQKa5CTAAR25DA2pGuas1WoAas08ExovQFEiUQQ0RjblicXiCSqjabGBsVfbiI7nZgFFqNW7EsiLnzyU1KdSBHSGUyWWzOd4eXyPdyJYlxcTRSWpZdfj9/t8dtdsKpWI8eR9AXXqydK3Xrrao3Z3l3pSCleDIdbUDG3RdUeiCNdsbjQgBreVWRNfA7XAAqUYIBrbM5TeGQAH0mPq4gQIN7F37CZC7yv5W5AtcuHHsCAQLnuYtJUerwnuel4tBAYBgJid74g%2BbhhAQSLfr%2BmD/iWHDLLQnAAKy8H4HBaKQqCcG41jWOSqzrPmSQ8KQBCaOhyzLiAWGSBqGgABxmGYACc3FcFhHHsVwxLEtImEcJIvAsBIGiBHhBFERwvAKCAgR0fh6GkHAsAwIgICrAQKTquQlBoA8dBxBECKcKo7EAGwALR2ZI1zAMgVJSBqZi8Jg%2BBEOG6B6PwggiGI7BSDIgiKCo6gaaQuhcKQADuxBMCknA8Bh2G4fRhGcAA8uqRnzqgVDXLZjnOa57nvqxZjXBAHjmfQTLmIkXCLLw6laMsEBIGZKQWWQFAQANQ0gMAUhmHwdDAsQKkQNEuXRGEzTQhlvArcwxDQvl0TaJgDgbaQZnPAQ%2BUMLQ61xVg0ReMAqq0LQKncLwWAsIYwDiDdeDEIdjjslGuX0od6qbDR8G1LltB4NEqU7R4WC5R6eDSa9pCA8QLJKMKIKfTDRj0csVAGMACi2ngmBJflcJ4TRwXCKI4gRQz0VqLlCX6J9KCkZY%2BiwypkDLKgKT1C9DljOgELCqYljWGYCmYwFQNC10/1ZC4DDuJ47R6CEYSDBUwyJYUmQCJMfgm%2BkZsMHMQzxIldjqwIvQTDreSO7UzsNOM/QG/Mxu2L7Ft6DMLR20bDvLAoFEbBIWUcDhpDybwinlfZTkuW5Hl1Q1uCECQvLUZ1tFE8sCCYEwWDxBAjH%2BIkGrcYkokaJIZiSHZslYXZ3H6JwkmkNJ7UanZXB2ex3FCXZLH8U3dnJ7linKappcab1ul9fpRXGSNY0tVZbCcM0LDssSDlMLqn3vtxGpcGxPl%2BSQeCBYlDOhcz0is0o7Nxbo00pWlDaCck4pzyhwQqhl1TXFKunSqLlkAGCMNfW%2BbEGpNUGi1IuiQzAl26ppTee84gmVGqgZqwwEGfS4HxQINBaBzQWktOKW01rHWYTtPaB0jro1Oowc6l1roEVuvdR6z1jrvXxpsQRv11aAxegREGyAwbHUhuJAiMM4ZrURpIrq4Y0Y0UxtjTAuMPpGAJqANefBSbk0ptTWmx035M3Cp/WQbNYoET/lzQmssrB83UYLWuhFRZZHFpLaW3j5aKziMrfx0cvYOA1hAVwIdEr6zKPbPQpt6jJNSNbeoEcFie26C7YO7tLZq3icU2Y/t0mOxKbkMpYc/ZpMjvHFYaw44dT7onHKcU04VUzpfJBVCUEaDzo/Vqxcupl1IBXKuwwAniQHkPG%2BrdiRYW4iJRIbcO6SESqApetgV54PXvATeBlirEMIcQA%2Bmxj5VRYAodkVJ2TDLBHuB%2BBcApBVkO/JxkV5DfzcToEAyQAHpVesAnpCkCrbxKmVVQ9zHnPNeXKMYaDSEYLiFgxIuCiZaX6hioalzCUtR/MgFIKRTwvO4qeN5YxTwIs/rNOIDDlqrR2qw9lu19r/WOjwwQF0rq5SEQ9MQoj0biNMdo0g%2BA/rxNkcDVQoNgTKMEFDOK6j4bQi0cjXRx0DHpCMXjUxYRzE9UsTiaxVMaaMHsT8xxEhnFRUBRzEFnjjC8xsH4%2BAwsgnpk4FsSWPM5aWAVqnJWz8VYBKdhUvwiStbZNSYbApOSihZGyZkrI%2BTA4xvqK7VopTQ5xLzb7bNDsg59GyY0strSY7tPCpChevTODlURU8jkKLgRoogPnfyWCOpTLXuXSu1dKAJyWQkG%2BiREhYQErs2S07iTjybdCpShy1LTKYpILCjdhLElkuxSQfEuCcTMPPcSiQoWp04IOnqCdvIruvWu45yxMYZGcJIIAA%3D%3D%3D)$Done$

## Links

- [source code](../../../../conceptrodon/omennivore/is_pageful.hpp)
- [unit test](../../../../tests/unit/metafunctions/omennivore/is_pageful.test.hpp)
