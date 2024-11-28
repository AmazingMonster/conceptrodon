<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `AllFalsify`

## Description

`Pagelivore::AllFalsify` accepts a class template predicate and a list of variables.
It returns true if the predicate evaluates to `false` for every variable and returns false if otherwise.

<pre><code>   Predicate, Variables...
-> (...&&(not Predicate&lt;Variables&gt;::value))</code></pre>

## Structure

```C++
template<template<auto...> class, auto...>
concept AllFalsify = REQUIREMENT;
```

## Examples

`AllFalsify` turns a fold expression of a class template predicate over `&&` into a concept so that it can be used for subsumption.

The following code will fail since `(...&&(not Pred_0<*>::value))` and `(...&&(not Pred_0<*>::value)) && (...&&(not Pred_1<*>::value))` are both atomic:

```C++
template<auto...>
struct Pred_0
{
    static constexpr bool value {false};
};

template<auto...>
struct Pred_1
{
    static constexpr bool value {false};
};

template<auto...Args>
requires (...&&(not Pred_0<Args>::value))
constexpr bool fun(){return false;}

template<auto...Args>
requires (...&&(not Pred_0<Args>::value)) && (...&&(not Pred_1<Args>::value))
constexpr bool fun(){return true;}

static_assert(fun<1>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwCspK4AMngMmAByPgBGmMT%2BXKQADqgKhE4MHt6%2B/kGp6Y4CYRHRLHEJZkl2mA6ZQgRMxATZPn6Btpj2RQwNTQQlUbHxibaNza25HQrjA%2BFD5SNVAJS2qF7EyOwcBJgsyQa7JgDMbkxeRAB01yfYJhoAgjPEXg4A1MrEmOgA%2Bhr3DxMAHYrI83uC3jMmI5kG80AwZphVMliG8YqhPG8AG5iLyYN7AixUMRKYEAEROoMBQIpxypAN2%2B0OmBOZwuqGul1uAOerwIHy%2Bvy4AMJAIhkMaMLhAkRyNR6MxOO8%2BMJxNopJplJFmrpIsejIO0JZp3OV2uD2IwAU3MeXwAjl48F8FG8IJzzAA2T0QBiofmfb5/VkWq23EAgJV45bLAHw2UotEY2hvKheBgQGMgr4EDYMFMk41WTWPBl7Q1HE3szkh63HO62zAOp2YF1um5mL0dn1%2BgWB/6nGthiO4zDRgkdz2u90Tru%2B/2Cn7CgeW2vYcOR0cxx5x3ZyxOY1PpzMWbO5t4EF6F8l6p6SvDIH5MBRKZrUNOspfYDMxukcVa0TgAl4PwOC0UhUE4NxrGsSF1k2FUzGOHhSAITQ/1WABrEAAg9S4AA4PSkAIgQ9SQAE5jhIxD9E4SReBYCQNA0UgQLAiCOF4BQQGY1DQL/Ug4FgGBEBAdYCGSC5yEoNB9joeJIlYbZVAIgBaUi3mAZBYSkS4zF4b5CBIPB0D0fhBBEMR2CkGRBEUFR1D40hdCSAB3YgmGSTgeH/QDgLQ8DOAAeQuCT%2BVQKg3mUj01MkDStLeHSzFdDxZPoVFzCQ5ZeF4rRVggJAZOSOSyAoCBCuKkBgCkMw%2BDoXZiC4iAYn8mJwiaABPLzeFa5hiHawKYm0WpeOQmS2EEQKGFoTrHKwGIvGAM5aHVLrSCwFhDGAcRZubOosRbfykVqC5tmQ8JdgAxzaDwGJ3L6jwsH8i88AY7heH24h0SUMk9k266jDQ1YqAMK0ADU8EwFzAuSRhVrM4RRHEaz4bstR/Oc/RNpQaDLH0G6uMgVZUGSHouI4FSZnQE4yVMSxrDMNiPuIYyDsJzpukyFwGHcTw2j0UJ5jKCo9AKDIBEmPwklFnpBiFkZqi6Yb6lmCW9BqOoBD6ZpZeGBJqhV3ncn1/odcWPXVgUOCtgkHyOCAlj/PYyLVPUzTtMkXTXVwQz0sQrgspQwHVgQTAmCwBIM1ILDJGOS4KKBSQNEkMxJA9JicLImiODo0gGKQy5CI9PCyLwrgPQCSQuACCiPQdxz2M47jA74vLhPy0SQsk0ryrShS2E4JoWCxIEVKYOEDCMBKyMuLhLjAgyiGZkyknhiykekFGlDRxzdBqtyPK6237dY3h2OC8SLjecK3kH4fR/Hzap5nufktQVL4nHY4zADnL%2BPbnv4hSTKm/IqaUQC3xHsgCeVUyJcGYjQWg9VGrNUcj1Dqq00F9QGkNBwq0xqMAIJNaa/k5oLSWitN6a1fpGG2mBfAXw9oHUckdZAJ1VrnS6P5a6t0OoPW2GBZ6r1kIfS%2BpgH6G0aHhFAC3PgIMFDg0htDWGlDV6IyshvWQqMHJgV3pjAGtMrC424QTSOxNSacApgQKmxwaY4wsAzU%2BTMWYmItorDWfgICuFVkkAWpRdYizSGLLIhtJYpECTLQW/iFYc01gbHIoT1Y9C1nMPxZs1ZxL5sbbWkS0n%2BzWBsa2eTLrH0dpwG%2BxAh4jzHlAx%2BXBp6zw0F7fAi9P7%2B2ykHUgIcw4jEjpdHOedp5JyBNXIEQJjjJ1TpXOubFOCNx4oDASbckBiVCkAgBxA%2B7bEHupFgCgsSwixHUy4zIZj6WaUZZeNkEaWQkBo2yW9tE6BAMcUg%2B9PJvSPn5euQVO5hQits2Kuz9nYiOSc/kEAUqgI/hlY4P8Fn/xAcVNZiKwH7OSMkH4hyyI/DBY%2BCppFaqIPiMglqbU%2BoYLJf1Qaw08Fv3GoQqaM06GYHmotMQFDkLrT%2Bvw3g9Clb7TJvPVQx1djsMEJwq6N07rtT4U9ZmQj3rxFEeIv6UiFnAyYGDCGUMYYgWQqom5yNNEPPRs8vRxg7F4xiC48CJNMhkwAPSU2xnTSwDjwJOKwDaxJnNPHc28cEbmpthZS3CZkAN0tMjBvluzJWsT%2BgBp9fG7JqSQ1jATSE9JJsckhotlbKynzpmnzKQCt4QKDmgqNDMJpPtWlwpbsHUO4dKC236f4aexxjgBACEnOBGhO0kTwkWgKHFbBN1/tGKOIAY4z2OHhCuiEe0ekQiRLOxwvkzNHRO22elh0N2brlVYH10jOEkEAA%3D%3D)

By turning `(...&&(not Pred_0<*>::value))` and `(...&&(not Pred_1<*>::value))` into concepts, we allow compilers to perform proper subsumption.

```C++
template<auto...Args>
requires AllFalsify<Pred_0, Args...>
constexpr bool fun(){return false;}

template<auto...Args>
requires AllFalsify<Pred_0, Args...> && AllFalsify<Pred_1, Args...>
constexpr bool fun(){return true;}

static_assert(fun<1>());
```

## Implementation

```C++
template<template<auto...> class Predicate, auto...Variables>
concept AllFalsify = (...&&(not Predicate<Variables>::value));
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGwAzKSuADJ4DJgAcj4ARpjEIGakAA6oCoRODB7evgHBaRmOAuGRMSzxicl2mA5ZQgRMxAQ5Pn5Btpj2xQwNTQSl0XEJSbaNza15HQrjAxFDFSNmAJS2qF7EyOwcBJgsKQa7JoFuu/uHmMduTF5EAHQPx9gA1MgGCgrPysSY%2BKK7pGeN3uDwAak08ExYvQFE8TBoAIJoBhbFIEZ4I2i0ABiYgyVAAns9jgARZ4QB53cz%2BakQBiodHfX54f6XE7g4iQ6GYWGBbAgEAANzEXkwy2WxysiPhCIA9AAqRVK5Uq2UyhVK54AFR5BE%2ByrViI1KpNisNCJlZwOTCOJ2BqEpcMRM2IXgcXx%2B6AA%2BhoZSYAOxShHPEPPGY2lmvAQzTCqFLEZ6xVCeZ7C7yYYmBqh4y7%2BkmSv15gvSxFWi5Xe2Ovkyl1uxmer1cQtB0NhxqOZBRhgxuMJpMptOizMWbO0JQB/OBIMT4sW0t7a22663B0PBHEYC87Ayn4ARy8eB%2Bn0xOLxeEJVyZ3o0gPXm6r28RyJ78cTydozyoXgYEAlgZ%2BBAbAwn45gWRYlgiZY2myy4gncd5bjumD7oePIYliuJjueBKXg2N4YhuCgPsSZg0qR6GnlhF4nFeja3oRD4ys%2Buy9m%2BKZfj%2Bf4WABQHPAQrpslY4Fzgi4Ydl6TAfAkBDUN%2BVxNnyv4SlOHCrLQnAAKy8H4HBaKQqCcG41jWGG6ybBm5iBDwpAEJoqmrAA1iAGmSHcGiSFw/qBBoGkaKR/hmAAHIF%2BicJIvAsBIGg3jpekGRwvAKCAN62bpqmkHAsAwIgIDrAQKS3OQlBoPsdAJFErDbKogX%2BAAtP4kjPMAyCdlIdxmLwzJEJy6B6PwggiGI7BSDIgiKCo6hpaQuhcKQADuxBMCknA8GpmnaXZ%2BmcAA8rcBXoqgVDPNVdUNU1LXPG1Zjkh4pX0AmllcMsvCpVoqwQEgJUpGVZAUBAX0/SAwBSMkNC0LsxBJRAsSbbEERNASK28HDzDEAS22xNotSpdZJVsII20MLQiNTVgsReMA1xYkl3C8FgLCGMA4ik6hdSCjym2xrUtzbNZES7OpU20HgsSLWjHhYJt/F4JFtOkOzxBJkoJJ7IzwtGHZqxUAYm6gngmBzdtKSMEjo3CKI4gjf18hKGom0zfojMoMZlj6CLSWQKsqBolkNO1TM6CkqYljWGYcUKz1HOe503RZC4DDuJ4bR6GE8zlJUeiFJkAiTH4s1Zz0gzpyMs01HUAh9BMSd5KXXTY/UsxF8MiSl7Mud6OGzRN4sLerAoZlbBIa0cFppCxbw8XHTV9WNc1rWuddEC4IQJAkVZz02ZrqwIJgTBYIkv6kE5kiBHcACcgT%2BpI7lmJI/jRRp/hn6FHDhaQkVWXc/hcP4gVn4FP8XJcA0hffwY9NrxUSslTeaV3rZQ%2BrlPahU/oA3uhVNgnAmgsEFP6WqTBXgGCMJdM%2BdwuBuU6vgbqeBeqzWtoNS20hrbjTtlNXQyQFpLSRsPUe48tocF2vlW4zxDpAmINg3B%2BC3iM2IaQtyN1UB3QSGvFYL1NYZU%2Bgo7690ir/U0YDLBODapSKMFwM%2BXAbxgwhlDGGU0UYI1NnYtGGMsYOFNnjRgBBCbE02mTCmVMxym3pmrbYel8A/DZhzKaXNkA81NvzLom1haiwRhLEJL1OSy2sgrJWmAVYMyMOrUAsC%2BA6wUHrA2RsTZyzoRbYajDZDMMmnpNhjsNbBysK7JJHtD7ex6H7AOQcXYWDDhPCO1Co6HzLj0eOidch5xCAnbuGd87pGztkau8yC5ZCWSXGO9cK5tw2R3Ou5deiNzTs3Duhy5lXP6Ds3uawNiDyei/HhEDOCiPEXggh0jTGyI0OSZe3U15PVUbA7eu996UGHm/D%2BJD3L%2BhAf6Lykhb4NVmrwyBthoGvXSplHKeV9o6NQeVSqmCxFnRYAoQUnZBR/IuDMChK8ep9VkPQupZtGn2xAMEDhy1abcI2lNeKAj9rCKOlgyl1LaX0ugjMeRiiHpmECIEDeuL3oaMVcSvR90hTIBSCkL0dKz5egZQQCSFLGF0CsZQGxelHEk2sg65x2M3EKPxp4omJNQmYHJpTMQAS5ZBIKWk0gYT67sxpnpaJsS5bxMFnpJJYsCSpKlhk022T0i5NVgUiIRS3olKYLrfWhtjY6WsjUoaEh6ljVtk0nQPLWnGCGW7WI3SvY%2B2jJwWUAdnYh0sCM/SYysDtr2acmZ7dZqpzKJclZRQsiTtSKswuFye7HNjgc/oi6pkNzuau5ZYwt1HNbnumda6Xn9yecNQV4DhUfMlY1KlNLUyyt2PKpelDV6PTVVvUgO894jEPoLWFSQSEqo0r5Dy0UVX%2Bl/reuKnAoEpV/cfDS58NKBVImfSQZ8vKXy4MEQWgQhUIYSjAt6w8OrwYnoh8j9l5YJAyM4SQQA)

## Links

- [source code](../../../../conceptrodon/pagelivore/concepts/all_falsify.hpp)
- [unit test](../../../../tests/unit/concepts/pagelivore/all_falsify.test.hpp)
