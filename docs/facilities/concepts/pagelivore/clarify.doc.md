<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::Clarify`

<p style='text-align: right;'><a href="../../concepts.md#pagelivore-clarify">To Index</a></p>

## Description

`Pagelivore::Clarify` accepts a class template predicate and a list of variables.
It returns true if the predicate invoked by the variables returns true and returns false if otherwise.

<pre><code>   Pred, Vs...
-> Pred&lt;Vs...&gt;::value</code></pre>

## Structure

```C++
template<template<auto...> class, auto...>
concept Clarify = REQUIREMENT;
```

## Examples

`Clarify` turns a class template predicate into a concept so that it can be used for subsumption.

Since `Pred_0<***>::value` and `Pred_0<***>::value && Pred_1<***>::value` are both atomic.
Both candidates are considered equally good.
Thus, the call is ambiguous.

```C++
/**** Pred_0 ****/
template<auto...>
struct Pred_0
{
    static constexpr bool value {true};
};

/**** Pred_1 ****/
template<auto...>
struct Pred_1
{
    static constexpr bool value {true};
};

/**** fun ****/
template<auto...Args>
requires Pred_0<Args...>::value
constexpr bool fun(){return false;}

template<auto...Args>
requires Pred_0<Args...>::value && Pred_1<Args...>::value
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<1>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwCspK4AMngMmAByPgBGmMT%2BAGykAA6oCoRODB7evv5BaRmOAmER0SxxCWbJdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHAD0AFSH%2BwDUysSY6AD6GsdH%2B7smGgCCBJgsKQavJgDMbkxeRAAdMCfthHk9ZsQvA5TucrhpwSYAOxWZ7HdHHWZMRzIY5oBizTCqFLEY4xVCeY4ANzEXkwx2RFgIUMwyIAIj9UU92ZzEc8DkdYRdLlxbkcHs9Xu9Pqzfv8gSDvmDnpDoQQhVcuIiUeCMZimji8QJCcTSeTKTTvPTGcy6Tzvlz7Y7%2BXdjlQvAwxYcJS83h9sbK/gDUMDAU9iMAFKDwecAI5ePDnBQa64/NzhyOh0EgECWu3PfEmklkim0N0eiArRnnAibT1UMRKXlIjnPcFS/1fOXB0MZqNKmOYeOJzDJs7ChG/PtZpU5vPW6rmRIprVTiMKGfYOe01kF42vU0lynuhiV6uYWvET222VWFt8p4Cw7HAAqo/Vdx9u12x2wxGIJDgliOKXEwChKC01Aemmq7YJWVYOhway0JwAS8H4HBaKQqCcG41jWJiGxbAu3w8KQBCaEhawANYgAEiSAgAHIkUgBEiiSSAAnN87FmN8%2BicJIvAsBIGgaKQGFYThHC8AoIDiRRmFIaQcCwDAiAgBsBApAC5CUGg7x0PEkSsDsqjMQAtBxxzAMguJSICZi8BchAkHg6B6PwggiGI7BSDIgiKCo6hKaQuhcKQADuxBMCknA8MhqHoZR2GcAA8gCOnqqgVDHOZiRWZINl2ccDlmMcEAeIZ9CkuYpErLwilaGsEBIAZKRGWQFAQO1nUgMAUhmHwdCvMQckQDEKUxOEzQAJ7xbw03MMQs1pTE2h1IpZEGWwghpQwtDzaFWAxF4wB/LQtBydwvBYCwhjAOIx0jvUVKjilRJ1ACOxkeErwoaFtB4DEMUrR4WApcyeAiTdpBvcQ5JKGybwPUDRiUWsVAGJGABqeCYJFaUpIwC0BcIojiP5XnyEoagpeF%2BgPSg%2BGWPowNyZAayoCkvTXRZszoD8bKmJY1hmFJ8PEO572c10PRZC4DDuJ47R6KECzlJUeiFJkAhTH4EU670Qya6MEW1PUAj9JMKt5Ob3SbQ0cwmyMCTm3M%2Bt6FiLQu0sbtrAoRHbBIiUcGhEkpdJeWWdZtn2ZIjkVbgrm1XxXANeRGNrAgmBMFgCSVqQtGSN8gLcUikgaJIZiSIkYn0ZxAkcEJpAid8ZiAt8iRIox3yMQEARcDxnGMRHoXSbJ8mZ0pLXqa1mmZbp3W9TVJlsJw%2BWFXiBhGKVnGAlwgJYS5RBSx5EXUz5lPSNTQV06FuhDdFsULaH4eSbw0kZdpALHDl0cFWssgHewA94HyPhVKqHUaoMj4mYDOTVlLzxXvEPSPVUDVVGMAh6XBOJcHEjQWgo1xqTVCktOapNyErTWhtBwpMdqMAIPtQ6KUTpnQuldUmd1UY7Cwvgc4r13qhU%2Bsgb6pM/rdBSkDEGc1wa8MalLGGZF4aI0wMje6Rg0agBnnwbGCg8YEyJiTWGl8KZ%2BRvrIO%2BIUsKP0ZujEWVhWbSI5oXbmvNOD8wIILb4wsWYWHFp/SW0sXEBwdpbPwEBXCewiurMorttbpF1tkW2BtUiJONhreJ9t5ZWw9ikr2YTejW3mHEv2Xs8m5FSd7Epiwtbp3WJsYO9SAbv0jpwABW9sG71weAm4EBk6n1gfVRqWdSA5zzqMQutF8HiQBi3NuARARcQCJxMwqzqiMSHhxMeUlOCTwUhjFSc8kBaSymglBxA147GaCwayLAFBUlxFSHpMpZjOXwKfdynlZBX3MWTKx9MQD8WfnFG6b9krj3SovbKuVVB3IeU8l5AZZiQIwdA%2BIQzvgIMOcgtFnVzl4pqrmZAKQUiXGeZxS4ryCCXDhTfEa8QSFTRmitShLLVrrU2vQjBu0mEHSOnwzAp1zpiE4bDbhmj5GkH4Y7N611j6qC%2Bq8cRghJGA2BqDWacjIaKNJio9IaiUaaPCNo5quimC43xoTYmGEyKmN8hICxgVabWJ0ECuxxg/FsxiCE7CPMsjXV2ALZmotLABOwkErAvqLa9EVsrSpasla%2BzqWkooWRompqScms2ctHa5IGBmmNTsBjZrduMAt%2BT3YlsyWU%2BpgdGl%2BXBTsz%2B7S6XHHuY86kSLXgov6R8kgQz04jJntnXO%2BdKCh3mUCjuWy4FmDMFwRiGhEgrObalGStgp6IJWDREAJcD59wCNXb4ARl18XYk3b4ELdkbu3aHJya6J7T2amseGGRnCSCAA%3D%3D%3D)

By turning `Pred_0<***>::value` and `Pred_1<***>::value` into concepts, we allow compilers to perform proper subsumption.

```C++
/**** fun ****/
template<auto...Args>
requires Clarify<Pred_0, Args...>
constexpr bool fun(){return false;}

template<auto...Args>
requires Clarify<Pred_0, Args...> && Clarify<Pred_1, Args...>
constexpr bool fun(){return true;}

/**** Test ****/
static_assert(fun<1>());
```

## Implementation

```C++
template<template<auto...> class Predicate, auto...Variables>
concept Clarify = Predicate<Variables...>::value;
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwCspK4AMngMmAByPgBGmMQgAMwAbKQADqgKhE4MHt6%2B/kEZWY4CYRHRLHEJKbaY9qUMQgRMxAR5Pn6BdQ05za0E5VGx8UmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnhzsmGgCC%2B4cA1ACSLGn0bIJMjbdH51c3p3%2Bn30uF0uBEwTwMoJMiTcoPB70wULcTC8RAAdOiodhbsgDAoFLdlMRMPhRKDSLdkWj0QA1Vp4JgxegKTHAtAMLZpAi3NwGYh4KgAT1uUIAIgSiST4YjaXyGUz0ajMSAQAA3MReBGJKxXYG/f5nXVHW4AFUwE3xX0N%2BstOp%2BRsJxIA%2BhpPgarrDnlLoZTUAqWVcJsQvA5xU6NMCTAB2bWXW5x25zRzIbECCaYVRpYi3GKoTy3NXeTDC6MEIMIyMiqExqOVrURu13B3oR1cV0HQEeiGapEo30YxLYYGB4NcpstiPR4HxhMtJMphhpjNZnN5gsa4sWUsamtVie16sNg63KheBhtvYdsGeyHe3sKy7EYDMgfAokARy8eCJ%2BJ5dMFiLHDRyQfJ8/RfK42UXTNs1zWhj1PCBlijCwiQIDYzyoMQlF3Ct6xBK8u0RH170fZ9Byud9P2/bleX5AUAIlZ1gNIsCsXMZJ2Jov96OhMcuGY0D%2B3Iy5INBJcYLzE8GEQ5DUPQ24t01KxcNta4jVNCZz0BRM8GQR0mDxeICGoU9ES4TFEKQrUOFWWhOACXg/A4LRSFQTg3GsawE3WTYi3MRIeFIAhNBs1YAGsQACZJUQADmSKQAkjZJJAATkSJKzESfROEkXgWAkDQgKcly3I4XgFBAIDgucmzSDgWAYEQEB1gINIUXISg0CeOh4kiVhtlUOKAFpktuYBkGTKRUTMXhiUIEg8HQPR%2BEEEQxHYKQZEERQVHUGrSF0fiAHdiCYNJOB4Wz7MckLXM4AB5FE2q5VAqFuQbkhGyQxom24prMW4IA8br6CzfyuGWXhqq0VYICQLq0h6sgKAgBGkZAYApDMPg6FBYgKogGJbpicJWgFC7eBJ5hiAFe6Ym0TAHAp0guteAh7oYWhyf2rAYi8YAkVoWgKu4XgsBYQxgHEHmv0ZxwVTNW700ZlFtkC8JQTs/baDwGJTppjwsFu0s8Hy0XSAV4gcyUEUwUlnWjBC1YqAMJ9qTwTAjvutJGGZlbhFEcRNv9na1Fuw79EllBPMsfRdYqyBVlQTkchFoaJnQUVTEsawzBKy2%2BSwBPEJ6OWchcBh3E8To9FCcJhiqUZ%2BOKbIBGmPxm8yVuGAWEYEn4uwy4EfopmrgoB/qIemkmQZ68WJvbBn9u9DmNpe8b/vVgUHytgkK6OAc0hit4Ur3uG0bxsmyRpsB3B5rBzKIahp3VgQTAmCwBIS4iyRElRNLIySA0JIMwkhkiFSiilbKHBcqkHyokMwqIUiRhiokGKAQAhcHSilGKR9bqlXKpVIKTs6qNThs1J67UUZo1Bn1NgnAPpfWxAYIwf0Uqoi4KiFyc0iCF2WrINaQdpAhyUGHfauhsYnTOhTfeh9j53Q4I9VqKJbivTPp9UaOJJZsI4VwwGwNEag2FJlMwkNiE1VhvDVAIN4gdVRtYwxowtFGC4ClLgQEaC0DxgTIm%2B0qZk2Zv4mmdMGZM3NqzRg7NObcxcrzfmgthbM3FvbbYsTZYODwArEW3DVAq1BMzDW9Rbo6z1mTQ2qSoZ8jNoFS21tMC2wlkYB2oALF8Fdgod2ntva%2B3Nv7QRG1hGyFDntFyEjI6O2zlYWOJTi5JxTqmTg6cCCZ0SCKSZud87xELorROpcMnOAgK4Ze/E64VD7noFujRjnpC7o0deSwJ69GHkvMeHc9mNBHrPM5G8V4vPyG81eXyG4PK3jvDasibr7VPowzRLDgA6M4S6CAd9eHGICmY6GoVSBvw/qMb%2BBUgJa1gfAgIqJUoBBSmYSlZhkgxSwclPBULOCEKqiQ%2BqTUWrPTsTQ3q/VOCtBYKNFgCgVTJhVK41EXYJizXwLwxa/DVqBwGVteQoiRk6CSKQKR51RYQsZSVB6lCXpvVUEKkVYqJVSq5EDBxSM0WJAxWyqxNjkadVtaDVUyA0hpEdOKlKjorWOlNcI3G8QfHE1JjTQJkbab0zlszCJggOZc1unEgWYhEnm2SU0ippB8BEgyVkpWuTkCqwKYIIp2tdb6wFOU42VTma1MyPUu2TTwgtJhm0pgbsPZex9k5QKfSlUSEGdtNV4dNVwujjnaZ8d4BzMaCLHYGdp1TIsHnE%2BBdFo7JLoPfZfhDmV2uac4FC9Lk5Gueesoc9zmPKnp865e6Pkz3uQvQFj6X03p%2BRDNYGxd4/q1nI/BnB3pmtFfmS18JNLItlSQNFT9zEw1fu/T%2BlB97EqSIg%2BlJizBmC4DFDQyQKX6pPsy2wRDMXLHCiAX%2BHC0EBBAYkAIhHMpJWgYkSFBqyqIaxVrGaJGFHPwsasS2WRnCSCAA%3D%3D)

## Links

- [Example](../../../code/facilities/concepts/pagelivore/clarify/implementation.hpp)
- [Source code](../../../../conceptrodon/pagelivore/concepts/clarify.hpp)
- [Unit test](../../../../tests/unit/concepts/pagelivore/clarify.test.hpp)
