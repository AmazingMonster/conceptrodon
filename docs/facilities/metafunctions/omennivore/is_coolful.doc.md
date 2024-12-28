<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::IsCoolful`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-is-coolful">To Index</a></p>

## Description

`Omennivore::IsCoolful` accepts a type.
It returns true if the type is a packed `Cool` and returns false if otherwise.

<pre><code>   Type
-> Type == Cool&lt;Items...&gt; ? true : false</code></pre>

## Type Signature

```Haskell
IsCoolful
 :: typename...
 -> auto
```

## Structure

```C++
template<typename>
struct IsCoolful
{
    static constexpr bool value {RESULT};
}

template<typename>
constexpr bool IsCoolful_v {RESULT};
```

## Examples

```C++
/**** Vessel ****/
template<template<template<template<template<typename...> class...> class...> class...> class...>
struct CoolLike;

/**** Items ****/
template<template<template<template<typename...> class...> class...> class...>
struct SnowLike_0;

template<template<template<template<typename...> class...> class...> class...>
struct SnowLike_1;

/**** Tests ****/
static_assert(IsCoolful<CoolLike<SnowLike_0, SnowLike_1>>::value);
static_assert(! IsCoolful<int>::value);
```

## Implementation

```C++
template<typename>
struct IsCoolful
{ static constexpr bool value {false}; };

template
<
    template<template<template<template<template<typename...> class...> class...> class...> class...> class Consistency,
    template<template<template<template<typename...> class...> class...> class...> class...Silence
>
struct IsCoolful<Consistency<Silence...>>
{ static constexpr bool value {true}; };
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCAAzACspAAOqAqETgwe3r56KWmOAkEh4SxRMQm2mPYFDEIETMQEWT5%2BXJXVGXUNBEVhkdFxiQr1jc05bcPdvSVlgwCUtqhexMjsHAD0AFTbO7t7%2BzvrJhoAgls7ANQAkixJ9GyCTDUXu0en5wefB28nxycEmFuBgBJlibgIAE8koxWJhQdg/sNiF4HNcFB5PFQvLQ/iYAOwWC6TRzIC5oBjDTCqJLEC4RVCeC4ANzEXkwF3xFioYiU%2BIAIqDCfzBbjTgCgU84adQW4/hd5RdxXdJTKlcC4WC1SrNYDlSCdRL9eCoTC2AA6C3wskGBQKC1mq3IG12y2xbDWpi2%2B2O53et0e20XDwUvCUhjICGkOUKrVG2Ma8G69WqpPa43Q5jm13up2el0O/25r3ZgP5n15%2B1COiMVa4t2IgjI1FXdEM2hYnFg4NpMMRmVV%2BjhzB%2BhH16UEon1ElkgSU6m0%2BmMlnedmcxts4WxIV4gVb0VnL6fH4fTYXbCqVh3dmvP4nw%2BHfcni4ANUwtqqLwfYtTcZ/CfjKaGv%2Bf6qiambDiWRZloWvqQbBBY5vB8INk2BBBm2QQANYalY0rvLs1zigon7bD8AEGnqwFAYBlGgRmsIjqWjFQcxSFjicSIomhQgMKgADuWGYAA%2BhoIp4f8IEUcmUlpuR6amhBCFMXBFYqcWCEoVxFw8fxglCVwYm/PhlwACpvgQxE3qcxJ4MgQl5tEBAQC2GLttiMquYJ/a8QJeDYSJpDaT5ekGfWbogCAy5snMhk2XZDmNBAYBgGirkdjKwQEPCEVRZgMV7qcHALLQnDxLwfgcFopCoJwsqWNYRJLCsq5mLEPCkAQmhFQsmEgPEkhmhoAAcZhmAAnGNXDxMNQ1cHieLSCVHCSLwLASBoGikBVVU1RwvAKCAm2dZVRWkHAsAwIgIBLAQSReAQ5CUGgtzVsQoSwpwqhDQAbAAtN9kgXMAyCklIZpmLwmD4EQxB4Ogej8IIIhiOwUgyIIigqOoJ2kLobR8cQTBJJwPDFaV5VddVnAAPL3XdaGoFQFxfX9ANAyDFxg2YFwQB4L30LS5htXMvDHVoCwQEgz1JK9j0QNLr0gMAUhmHwdAAsQB0QBElMRMEDQQiTvB68wxAQtTETaJgDhG6Qz0PAQ1MMLQhs41gEReMAbhiLQB3cLwWAsIYwDiG7eDENbjhMm%2BlNUtb91rO1mVVJTtB4BEhNmx4WCU42eBrf7pDR8Q9JKHygLB2nRhdQsVAGMACjPngmB8dTGa24jwiiOIaOd5jaiU3j%2BjByg1jWPo6cHZACyoEkNR%2B79wzoKCfKmPVlhmDtxew1gU8QAsdiRxkLgMO4ngtP4p/TP0MRtHk6QCGMrTJKkD8MNfpQDBMVRHwIXSjOfcY7Rf61BGD0YIfRP631sGAp%2BehJiNA/rMLgB8mqrAkGTDgZUtqU12szH6/1AbA1BgNbmEBcCEBIByVqKDRY1wWAgTATAsAxH3qQXqkhYhmjGrEBaGhJBmEkN9Da8RvpjX0JwFapA1ptTNN9Lg30hpjVmt9fqU0eHfRwTjXa%2B1DodRrmdS6ktrp03unLBWAt3psE4A0FgTI8S/SYB6IwnMxpmi4INSG0MSBwwRrIZGPdpB9yUAPHGuhVYEyJkbTB2Dtq8F2rTW690LiM3wazQGuYXFcDcR4jQPM%2BYywFtQ2IZgRb6JOhLKWqB%2BbRHMdUwpAxMnK0mptGgtANZax1jjE2BtbY9LNhbK2NtC720YI7Z2rsqru09t7WgvtbaB0rmsKZ4cj7Rz9lVOOyAE622TktKqacM4G2zss0WsMC7tWLqXTA5cg5GCrqACpfB66N2bq3duhdO4BNRkE2Q/dsZVXCcPaua8rCWAnhEPeM854ZAXkvFeoLrCb3idvOGMdp7AIcMfCArg4FtECBAmYX8X75AyHiklb8kHEsPliv%2BsDAHPxpTUf%2B4Dig33gfS7IjKwFUtvqg5Y6CUESKwRTbRnA0mEOccAVx7jBo8woTDYptDyniwYUwlhlBMFSJkW4/heJ4hjXmrEARQjJBtDiVTPatg9Fi1OudK6N16Z1JqW9D6HBbFsxYAoJkpImTZLNOqYYXjKE7z8UjbuPz0byBCQCnQcRSCROJv7GJoqdo01MQzJmqhPXet9f6wNaFeb1NesU2IZTbWVJQMWgWzqGkxB9UkJIQk/VjSEgWoS2agnq2iJ03W%2BszZ9P7ebS2kdbajMEE7F2lNplex9n7dqiz7mnNIPgCOWL1mx1UPHAEuzBApxxoczOEITm53ObbK5qQbkV3ucER54tnlMAbk3FubdGAd38RGiQvyMYxsHvGgwIKx7gsOVC6qMLZycHWEvUe68LDIuqqi3e8AD4/1pX4HFp9yUErZVA3Ir8ajkvvjUXl8DUPMs5Rfb%2BHQ6VTEJeyiYFGgEINZZA5B/LmoYOFbE3B4rO0XC9T65k%2BbJTDHld4wWNDy30NIIw5hAw2FLW1SAcaZpYgJGmmajaam8SKK0Wmq1B0jrSY4fEbhc08QbSGpISaXARpmE0UtWIqb4mcDoRUzBEM9MuatRWhYxc0jOEkEAA)

## Links

- [Example](../../../code/facilities/metafunctions/omennivore/is_coolful/implementation.hpp)
- [Source code](../../../../conceptrodon/omennivore/is_coolful.hpp)
- [Unit test](../../../../tests/unit/metafunctions/omennivore/is_coolful.test.hpp)
