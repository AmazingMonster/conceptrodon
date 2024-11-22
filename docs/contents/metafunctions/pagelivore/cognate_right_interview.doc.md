<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::CognateRightInterview`

## Description

`Pagelivore::CognateRightInterview` accepts a list of predicates.
Its first layer accepts a list of variables and returns a function.
When invoked, the function first binds the variables to the end of every predicate;
then, it returns the index of the first argument that satisfies all newly formed predicates, or `-1` if it cannot find the argument.

<pre><code>   Predicates...
-> RightSides...
-> Arguments...
-> Found ?
   index : -1</code></pre>

## Type Signature

```Haskell
CognateRightInterview ::   template<auto...> class...
                        -> auto...
                        -> auto...
                        -> auto
```

## Structure

```C++
template<template<auto...> class...>
struct CognateRightInterview
{
    template<auto...>
    alias Page
    {
        template<auto...>
        alias Page = RESULT;

        template<auto...>
        static constexpr std::make_signed_t<size_t>
        Page_v {RESULT};
    };  
};
```

## Examples

We will find the indices of `2` and `-1` in list `0, 1, 2, 2`.

```C++
template<auto I, auto J>
struct Equal
{
    static constexpr bool value
    {I == J};
};

template<auto...Args>
using Metafunction = CognateRightInterview<Equal>
::Page<Args...>;

static_assert
(Metafunction<2>::Page<0, 1, 2, 2>::value == 2);
static_assert
(Metafunction<-1>::Page<0, 1, 2, 2>::value == -1);
```

## Implementation

`Pagelivore::CognateRightInterview` is implemented based on `Varybivore::SensibleRightInterview`. It changes the invocation order of the latter.

```C++
template<template<auto...> class...Predicates>
struct CognateRightInterview
{
    template<auto...Interviewers>
    struct ProtoPage
    {
        template<auto...Variables>
        using Page = SensibleRightInterview<Variables...>
        ::template ProtoRail<Predicates...>
        ::template ProtoPage<Interviewers...>;
    };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGEgKykrgAyeAyYAHI%2BAEaYxBJmGqQADqgKhE4MHt6%2BASlpGQKh4VEssfFcibaY9o4CQgRMxATZPn5cgXaYDpkNTQTFkTFxCUkKjc2tuR22EwNhQ2UjlRoAlLaoXsTI7BzmAMxhyN5YANQm%2B25ejrSEAJ4X2CYaAIIHRyeY55fI4%2BhYVEezzerwA9AAqSHg04ANSad2ieAAbiR2CAhIx0tF6AAlPDABAEACSgjiSLwmAA7qcoeDQcCCJgWMkDIyLm4mNdUAA6XlA17jYheBynDEMLG4/GEkmM4jkqnAkwAdisr1O6tOjOZrMw7K1LKYbMunKIvO5j1OxyYCgUZuUxEw%2BFEjIU/JeGtOguFBFO9tQRBxTDowI9ytV7o9Gv1OvZJp5fP2TzVkfVXpFfqIyiYwF1yZTYc9jUcyEtAnGmFUyWIpzjpyRYi8XzDAFouMqACIXCznJWd/bhkMpzVMg1Gjlcs0vYAOpmMAiuxODlNedJGX3Zpv7du%2B4j%2B1BZnPsqcztiCW0Jp79pc9vsDvPD7WG3WXaNP2MTi%2BWgw2u0Op1PhckwjdUVzCYBTkDOhvm3DNUEg2h2XtR08GdTBz3NRcr1eDsu0VV5XzHWsADE8GIcY3TTH0xQlTA8QJYlSTlClKXZEiyIIN0w2vAjnzcHj31NT8rR/XkkP/F03Q9Sidz3eDry4%2B8PX440P25OjCSEPAsEA68pIIIV013TMN10jUC3VUyU3GQ0UNLcVGUrata3rbwm0UocFOAod838Kx/HbCBVlOZsLT%2BEAQBYJgAGtMAAfXSYBwnQWKOMudIAC84tSoDvO8zzcoK048CoOzy0c853MKjUoDNcwADZ6rElCANY0jxlICCpWELS0NqxNwpcxtVlWSyqp7bsHQILYGFODQuxvPCvLGjUaiUUaqoLSbpuCtt%2BwWyrco7QL1rM3tcIOnCsJBJaoxHGMVME7lj0wWcz0kodQLXA9Nxgoz9xMy5nte%2Bc%2BsvcNQzOq7uLut8XxhwjVItYT0KB0953ekDV3A%2BDoJkgMgwQwHpxetH0KBKHIbvF5lPHIhTjY9qay5UVugEdAOrjM0AHkCAQOIdIFfTvRZ8U8GxWiuplMlmNa9iOoxNAGHZ04eb5sjQcVFVocfMcac5oTv3QprUIFrzpNguT73yoc9dU9Tuu0jHI3Nv7vtG8yKpuqyi1sxWyqrJm6cGtyvcja3lpMXzI4CoKQsTQt0HCyKYvi/EkpS9kMqyp2Nq1g6quK0qHIDk6CpqvkzAayvjZay4GYIDr7c07TQYGhtMGG0vDpVU4tuIGa5r2nDsPzwrVq%2BQu/eL6su%2B88vzUrxq/2aiTLgVtnG665veovNvXM70eCs2zApv705du7YfruWlNx6Kkqp4rKtZ6HCAX4K6ixcleipaYhVLlVvzDWh8xrhR4hBAmiFl4m2AaHG%2BpwwHwy%2BG7S4Tcepk0XCAqqe9GynDAGAC425Wzv0jCNLBHke4kO8n3GaZhziWBFjRe2v95QsQAbzIBF4qFDkQTrL4clLg1xdLA%2BB3leGjmQQDNwaCW5cPIQVHBz5L7yLDmdEecCx60DWioiGE0T7bWIUPNRGj8y9mOiAy64MKG3kWt5W2j1UZzlNt5T64Fvq41gigtwjizwayuhDGx6ilJIL1CEh68YMLYC/NaFGxNgbOI1K4iBUFCF4zgpAomJ4nF%2BIHJTRaEIoTrhzLcFEDpwoeESk%2BZhjFWE0ihPSfCYS%2BJNP1pE6JIluRCLQhRIWIoKnMEZNU2UrDNZWPVPYiJLDmL8ydi7PcbsrZ51DhMs0cJiB4CYOLBJy4sZFJ%2Bowr%2BEsf41JlpcNZGytkiJ4SAcBFsMluC6RgnK1zbmuykVMqknDInnS8pY2xt0%2BECQieczZ9BtmnCSe41JnipEgsuVwimgTroFNpKi2kDSXgouhAAFTQvOOpkIMVYrRaijFiozCHAYMcLwZx2TXDoPcTijTAXhNOESDmzMABSPSDI%2BmwAARy8GIUZ15rLFiLk/as0RUCeDrO3eSKoiTQVSdyvJ2E1XXRWbyF4xBgCmySQAWRPkwKgXgqV1Bmqk/pVTJYnP/m4AVQrCZAXCl4nVeqcmLTFShWKMS4gcVeBAI1jRTXmsyOyMwjxXVSKSOfDqZh41RpAMHZVW5ThmBGldb1yBfU2n9cCINxrQ09AEOyQx2Bo2HkuLGrg8bE39WTe3VNRCuCZosBwdYtBOD%2BF4H4DgWhSCoE4G4aw1hPSbG2E2ClPBSAEE0B29YUUQD%2BCVNyfYAAOOqSp9hbo0Bu7dABOfY%2BhOCSF4CwCQGgkh9oHUOjgvAFAgCSHO/tHbSBwFgDARAIBNgEGSNccglA0DMjoHECIrBdiqE3c2OqkhTjAGQCWKQ3IzC8GQkQdZida38EECIMQ7ApAyEEIoFQ6hX2kF0LWykxAmDJE4DwTt3be3zsHZwLm1x/0%2BlQCVKDdUYNwYQ0hyQKHTgQA8CB%2BgM9p2rF4C%2BrQ6wIBIGA8kUDZAKAQGU6pkAwApAJpoLQWUj6IDRBY4iZgxA7j0d4GZ%2BEXNojaG6C%2BmdwG0ZcwYLQSz5GsDRC8MADktAtFWdIFgSKRhxBedIo55EaEWMVm6NcXYM6wiMi7eR240QaMWY8FgFj%2Bk8AXu4LwJEcRpVKHbEyQwwBbhGHnesKgBg9UwmYlzZIjAgs4eEKIcQhGOskbUCxyj%2BhKsoFHZYfQYtH2QHWKgZIFrH0cGbH8QhphLDWESLwVAxXiCYZi1N6otRMguCVlMdoQQlaDFKOUPQqR0gWpO9dgoFqLvDAqPtqL9Q5j3drV0EtDA%2BjNGe0sV71lJieDaHoEH8wSgvYkOsBQE6diw5PRwHtpAb0bc4KcXj/H4OIfPsJuhEBcCEBIPQ/YrbZO1fWHzJgWB4iBVIEuyQ%2BxuRHqVJIDQkgzCSDqle/wdUD3I7PaQC95PuR1S4HVddB712S/8JIDoR66po5Y3eh9T7Z21ffV%2BxTP6OMAfU5pyT4G2CcCaCwJESpmxMGiWuLgB7uRcG5AO9DJAtJ6A63h7r0hetKH6%2BR3QCbqO0as4xlHzHyN3vY3%2B64pxuM1mIBbq3NurR24d07jQonxMqck2TjNlPX0KaU6gCTcRAMaZLznkY5vLfNlTzpg9XAkj6cM5QEz5GbMWaC53u4dmHMOCCy5ucbmPMse875/zgXCvBYq2F3YA78AOh6MV%2BbLvVDxcZEF5LNQWPpcy3cbL8/ZPrIKzOrbpXMDldC1VsCWv6vZgUE1qkLW2vT8911gjPvZB9bIwOwPQ2asVsrAxt0tJsGcZs5tOBFsCB0BltRsLB1tB0tsdswC4cah3s/AIBXAvszt0BAcrta0btCgsgwdph8hbtMh8Dlg3tft/sWhSDTsfsLU6CqDgdPsGCIc5hWCkd4cthEdW1kdUd0dWMOAE8k9rdbdwJ7dHdndRNicMMycKdNdC9qdMBacRgGdUthdRcHdOclR/AD0lRt0ucecFcVdI9OB1dn0tcP1v1f1ONy8jcwMIMzdE9YNTgWAFAkQSwkRpCdRxg0N8AMN3dsNZAvdP8iN5A/df8dAQBj1g86NCsw8hDVc2N9cuMSpzd3DPDvC6w/CAIfQxNK9VMyd9gZNlD5N31i9S81MgNijJNk1kBkhkhYpfCD1Yp/CCBfU3Cfc6BW9jNTMwh4Ru8hiLM%2B9HNB8S9XN3NPMF9MAfM/MxAp8Z0QtKtwsF9Itl8YtyM4tkAEst9SRUsB0994RD9csT8gtz80hL9Z8b8atC8%2BAGtH9mtWs%2B0Z1398MJAv9iNoiBs4iADjB4DxtohUDB1ZtMh5tQQwogC1tb1kD0F4A0CDtnAsDjsODa0QgFhLtqCiC7t0TyDiDuDvt0DaD2CchGCSTmCuCsSYdvsyTwc6T%2BgiS4cEcCNkiI9b1Mcsi4McifD8iXRCj5DScDglC5MF1SAac6dKAw9tCQAzAHd9h9h/B/BOcm8919glQpdzDOT71bANcxThpGcQAudxcuB9hK5zSD0JdK4NAlRkd9gOSMddSDSw9UNtSnSC95N1gtt0hnBJAgA%3D)

## Links

- [source code](../../../../conceptrodon/pagelivore/cognate_right_interview.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/cognate_right_interview.test.hpp)
