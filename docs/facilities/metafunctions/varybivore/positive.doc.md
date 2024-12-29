<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Positive`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-positive">To Index</a></p>

## Description

`Varybivore::Positive` accepts a variable and applies unary `+` to it.

<pre><code>V -> +V</code></pre>

## Type Signature

```Haskell
Positive
 :: auto...
 -> auto
```

## Structure

```C++
template<auto>
struct Positive
{
    static constexpr bool value
    {RESULT};
};

template<auto>
static constexpr auto Positive_v
{RESULT};
```

## Examples

```C++
static_assert(Positive<1>::value == 1);
static_assert(Positive<-1.0>::value == -1.0);
```

## Implementation

```C++
template<auto I>
struct Positive
{ 
    static constexpr auto value 
    {+I}; 
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQBspK4AMngMmAByPgBGmMQSAOykAA6oCoRODB7evv5BaRmOAmER0SxxCVzJdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHAD0AFSHR8cnp0e7JhoAggdHANQAkiwp9GyCTL13xxfXt2f/Zx%2BV0uVwImGeBjBJgAzG4mF4iI8YdgQbNiF4HHdlOlMgA3TAgkyJCx3EF3cl3WYfPDIO5oBizTCqFLEO7wxG4sReTCk64U0nE6wPIkAERhJMJiTF0Ks1xBfwBJyBCru2FUrBePO%2B8sVgMJ1ypjmQAH0mAolC0INiinh8TC3FxkSAQJzvDyYdKRXcuCtxaimkbTeb4gQrTjHHbYQBaLgAOg0TpdXPd0M9dxj8d9Mo4a1onAArLw/BwtKRUJw3NZrJSNlt3WZoTxSARNDm1gBrED5yTxgAcZjMAE5B1x8xpe73qolpHmOJJeCwJBoNKRi6XyxxeAoQCuWyWc6Q4LAYIgQBsCCkEeRKGhnnR4pFWDtVL2AlGApI7sBkLSpLGzLwmD4EQxB4Ogej8IIIhiOwUgyIIigqOo%2B6kLoXCkAA7sQTApJwPC5gWRatmWnAAPIIpeBB3KgVB3C%2Bb4fl%2BP7ej2Zh3BAHh3vQrLmI2Ky8HuWhrBASC3ik95kBQEBiRJIDAFIZh8HQYLENuEAxMRMThM0ACeeG8FpzDEDppExNodR7k2t5vAQpEMLQekoVgMReMAcK0LQ27cLwWAsIYwDiE5eDEBZtqYF5pZMnUCI7E24RgrOpa0HgMTYcZHhYMRBCgYu3mkPixAxOkmAiuC/nJUYrZrFQBjAAoABqeCYBhpEpIw%2BnwcIojiHBkHyEoajEWh%2Bj%2BSgVaWPoKXbpAayoCkvReVGszoB6piWNYZjrgVoFYNNEBrLU9TOBArhTH46GhAs5SVHohSZAIZ23eGWRDNdyxdD0DRzI96GHb0/QtK9IxVOMAw/aDgNXcDEgHbW2ww/ohGrsRG50a%2B76ft%2Bv6sexuCECQpINj6AlVWsCCYEwWAJPtpCdpI0KxoO0LThokhmIEy75gEg6I3OC4gI2sYBFwAS9oOk4BN2o5M0Ea68BuW47s2VWHieIlnhRV5STJ3GPmwnDNCwuKJFGTB0gYRjeoOsZxpFwEkGBEGyNBPXSH1iGDShuiKVhOH6QRHCFsjKEbuRF4ItRtH0Rj5v%2BVbNvxuxnHidxhPQmY/HK/uwmiagXHxNe0l5ynozIBb8kjiuNC0CpakaShhm6R1jfGaZ5kOB11mMLZ9mOaWzmue5nkdb55U7P3wWhfiEWAao0Vgh18XdMRyWpbpGXjwJOUdQVRVKKVflGBVoDZ3wtUNU1LVtcWTZ9S7sFu7IHvIaW3sjZVa1WBNq97bN81ZItZaq1xoWE2vLbaYFwrwAOt0UKx1TqeHaHoS6ZRoboTur0cGGCXpQyWCDP6X0waILyL9WBR0%2BhzCBngvQVJJjEPOhDeYqDqE%2BnWJseGrDZxBzliRDgaMGKfjLnHLg1tba43tjxImmdBJtlIOTSmowaaznnKQRc0Jras0SPmQciREjQjZoESQ6EeEK1sErGRwk1ZIHPJRQuOsHxPgNsQFgjEWAKFxLSXEIjYyQnCgQQCEjHboTvt1B%2BnVn5DQFphbCuFvIB24SjMimsqI0Toq49xnjvG%2BNmEnYuEk07QmkSrdW9jJI3jydxF0yAUgpGNF4wcxpskEGNKoD8Ska7xDrppbSxlm49JMmZCync842Tsg5YiA83JiGHnlUeR9N6kHwCFeo09iJRWQDFReghl4oVXmlHSG8srbzyrvYqB9yrhBPkJM%2BTA6qNWaq1dqeUQkwQkI/BCA0X46CieXMa61v5TWgWWf%2BAgvK7GWn8r%2BoCtrxB2lAmaH04F%2BBOgwdw9DkGoqoTddBz0HropxTaEouDsWIvIQDVo%2BLSX/UocS96tCKW5AYfSrFyxYbsNgvEoiIdOBpM/G4jxdx6k%2BI%2BH48R%2BNJF8RJtnMmFMqaUADioxcQ5YzQmhPmMcRjlyqsSKLYO65OCK13KTWm/h8yMynMuXskgRxcH7GYIIs5oRcv1ZuLOQkA4AT1fLA1brZEFQyM4SQQA%3D)

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/positive/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/positive.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/positive.test.hpp)
