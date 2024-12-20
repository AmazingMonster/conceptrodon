<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::AnyClarify`

<p style='text-align: right;'><a href="../../concepts.md#pagelivore-any-clarify">To Index</a></p>

## Description

`Pagelivore::AnyClarify` accepts a class template predicate and a list of variables.
It returns true if there exists a variable for which the predicate evaluates to `true` and returns false if otherwise.

<pre><code>   Pred, Vs...
-> (...||Pred&lt;Vs&gt;::value)</code></pre>

## Structure

```C++
template<template<auto...> class, auto...>
concept AnyClarify = REQUIREMENT;
```

## Examples

`AnyClarify` turns a fold expression of a class template predicate over `||` into a concept so that it can be used for subsumption.

Since `(...||Pred_0<***>::value)` and `(...||Pred_0<***>::value) && (...||Pred_1<***>::value)` are both atomic.
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
requires (...||Pred_0<Args>::value)
constexpr bool fun(){return false;}

template<auto...Args>
requires (...||Pred_0<Args>::value) && (...||Pred_1<Args>::value)
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<1>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwCspK4AMngMmAByPgBGmMT%2BAGykAA6oCoRODB7evv5BaRmOAmER0SxxCWbJdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHAD0AFSH%2BwDUysSY6AD6GsdH%2B7smGgCCBJgsKQavJgDMbkxeRAAdMCfthHk9ZsQvA5TucrhpwSYAOxWZ7HdHHWZMRzIY5oBizTCqFLEY4xVCeY4ANzEXkwx2RFgIUMwyIAIj9UU92ZzEc8DkdYRdLlxbkcHs9Xu9Pqzfv8gSDvmDnpDoQQhVcuIiUeCMZimji8QJCcTSeTKTTvPTGcy6Tzvlz7Y7%2BXdjlQvAwxYcJS83h9sbK/gDUMDAU9iMAFKDwecAI5ePDnBTHCCh5FudNnYUI37hyOgkAgS10lbg/Emklkim0N0eiCllHnAibT1UMRKXlIjnPcFS/1fOXB0N5qNKmOYeOJzDJ1MgpEZ%2BdZ%2BE/NwjgtF2mYFYM6rmRIptPzzNwkUrtdKwvFrdl42vU1Vynuhj1xlNlvHW2yqxdvlPAWHY4ABVp3VO4fV2XZjmwYhiBIcEsRxS4mAUJQWmoD0Vy1JV61LB0ODWWhOACXg/A4LRSFQTgM0saxMQ2LZrTMb4eFIAhNHwtYAGsQACRJAQADkSKQAiRRJJAATm%2BUSmP0ThJF4FgJA0DRSFI8jKI4XgFBAFS2LI/DSDgWAYEQEANgIFIAXISg0HeOh4kiVgdlUQSAFoxOOYBkFxKRATMXgLkIEg8HQPR%2BEEEQxHYKQZEERQVHUfTSF0LhSAAd2IJgUk4HgCKIkj2IozgAHkAUs9VUCoY4XMSdzJE87zjl8swUw8Oz6FJcxmJWXg9K0NYICQWyUnssgKAgYbRpAYApDMPg6FeYhtIgGJCpicJmgATxy3h1uYYhNuKmJtDqPSWNsthBGKhhaG2pKsBiLxgD%2BWhaG07heCwFhDGAcR7qneoqWnQqiTqAEdhY8JXkIpLaDwGJMoOjwsEK5k8EUj7SCB4hySUNk3h%2BuGjHYtYqAMSMADU8EwNLipSRgdti4RRHEGLwvkJQ1EKlL9B%2BlBrGsfR4e0yA1lQFJene1zZnQH42VMGjLDMdTseIELgdFroeiyFwGHcTx2j0UIFnKSo9EKTIBCmPxUot3ohlN0ZUtqeoBH6SYDbyZ3ulOho5gdkYEmduZrb0LEWgDpYg7WBR6O2CQ8o4YjVMKjTqrcjyvJ8yQ/JTXAgs6piuB61iSbWBBMCYLAEnrUhuMkb5AUkpFJA0SQzEkRJlN48TZI4eTSEU74zEBb5EiRfjvn4gIAi4KTxP4lOko0rSdNL/SBpMwazLKqzxsmjrHLYTgarqvEDCMJrxMBLhAXIwKiDV0LUvZyLWekdn4q5pLdDmjKsp2onZOaleAaVKhZAExxKrp1qh5ZAF9gBXxvnfVqqB2rxB3MPEufUDLbwPvEayE00EjQ6igBBXBxJcBUjQWgi1lqrSSntLajMmEHSOidBwjMLqMAINdW6hUHpPRem9RmX1CY7HIvgc4gNgZJVBsgcGjMobdEKnDBGW1kYSN6mrDGLFsa40wPjb6RgiagA3nwcmCgqY0zpgzTGr8WbRQ/rIL%2BiVyK/15sTBWVhLBCxiCLWu4tJacGlgQWW3x5YCyVireIT8Na1xdr0XW%2Btcg22CHrSOZtbbpEttkT2aS7ZZEyU7LWvs3Yh3yWHH2rs%2Bj%2BxNoHMOFTUmNIGMU6O6xNjx2Ln3YBqdOAwLPvAn6SDb43AgPnR%2BmDi69TLqQCuVdRi124lQlSMMB5DwCICCSARxJmF2dUfic8xJL3UpwVeukSaGS3kgcy5VCH4OIEfHYzQWAeRYAoKkuIqQUMBDKWYAV8CPxCmFWQb8nFM1cdzEA3x0qZWyh9IBBVl4lV3hVKqqg3kfK%2BT8v56oIBtRIRgrq3xsGXLwcQ0a9yKWkM%2BSkFIlxvniUuLiy4GKP4LXiPQtaG0DosJ5YdY6p0uFoMurwm6d1JGYEes9MQIjMZiJMVo0gUjfZA3evfVQYNXhKMECo2G8NEabU0ajHRjN9HpEMQTEx4QzH9QsUwSm1Nab01IixBxUUJDOLipzNxOhoWeOMFEmwaiAliwllkd6uwZb80VhYZWoDVbq1DaUmpyTQ6pWNmUBp2SihZHTakHJ9t6lRyqdrcpAx82JL9q04tWTxgVsqcHGtWaS3dNjp06KiKTmgP6Wy447zPnUhxQGWYedAUkCmaSje5dK7V0oIndZ0KR5HKYmYNdXB%2BIaESDs7tRVNK2DXjglYXEQANxvlPAI7dvgBC3UxUSfdvhItOfuo9id/K7pXuvfqaxsYZGcJIIAA%3D%3D)

By turning `(...||Pred_0<***>::value)` and `(...||Pred_1<***>::value)` into concepts, we allow compilers to perform proper subsumption.

```C++
/**** fun ****/
template<auto...Args>
requires AnyClarify<Pred_0, Args...>
constexpr bool fun(){return false;}

template<auto...Args>
requires AnyClarify<Pred_0, Args...> && AnyClarify<Pred_1, Args...>
constexpr bool fun(){return true;}

/**** Test ****/
static_assert(fun<1>());
```

## Implementation

```C++
template<template<auto...> class Predicate, auto...Variables>
concept AnyClarify = (...||Predicate<Variables>::value);
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwCspK4AMngMmAByPgBGmMQgAMwAbKQADqgKhE4MHt6%2B/kEZWY4CYRHRLHEJKbaY9qUMQgRMxAR5Pn6BdQ05za0E5VGx8UmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnhzsmGgCC%2B4cA1ACSLGn0bIJMjbdH51c3p3%2Bn30uF0uBEwTwMoJMiTcoPB70wULcTC8RAAdOiodhbsgDAoFLdlMRMPhRKDSLdkWj0QA1Vp4JgxegKTHAtAMLZpAi3S4MACebgMxDwVF5tyhABFbhB0aiTAB2NzytyE4l4UkI6G0oUMpmYkAgABuYi8mGWUKsV2Bv3%2BZytR1uABVMBN8V87Ta3ZafvaVegAPoaT62q6w57wxGU1AyllXCbELwOAlE/0aYHyi2XW5Z25zRzIbECCaYVRpYi3GKoTy3I3eTBiuUWAjxhFy8XmtOt9te64%2B5N%2BrhBg6A0MQjVIlFRjGJbDAuMJrm%2B/sdjPZnMtPMFhhFktlitVmsm%2BuN5vytuJDOnrtA713KheBiDvbDsFhyHQyMyy7EYDM6fAokAI5eHgRL4jy/KCsKvKIouGjkl%2BP7Rn%2BVxstupblpWtC3HeDAQGaDZEgQGwPlQYhKO2nbdiO4bvhOn7fr%2BM5XIBwGgdyfICnSIowX2cHcgxSFYuYyTCexEFcdB0KLlw8ECVOTGXKhoI7hhVY4Xh6aEcRtxNiaFFtt21qOs6XKepcuZqn6TB4vEBDUPeiJcJieFmueHCrLQnABLwfgcFopCoJwiqWNYObrJsdbmIkPCkAQmjuasADWIABMkqIABzJFIARyskkgAJyJLlZiJPonCSLwLASBocG%2Bf5gUcLwCggHBcV%2Be5pBwLAMCICA6wEGkKLkJQaBPHQ8SRKw2yqJlAC0eW3MAyD5lIqJmLwqpEEK6B6PwggiGI7BSDIgiKCo6jtaQugyQA7sQTBpJwPAeV5PnxQFnAAPIooNXKoFQtwzck82SIty23KtZhSh4Y30GWUVcMsvBtVoqwQEgo1pONZAUBAmPYyAwBSGYfB0KCxDNRAMTvTE4StLyT28LTzDELyn0xNomAOIzpCja8BCfQwtAM5dWAxF4wBIrQtDNdwvBYCwhjAOIosgVzjgGs673FlzKLbDF4Sgp5l20HgMT3azHhYO9TZ4FVcukJrxAVko4pgkrptGPFqxUAYP7UngmA3Z9aSMDze3CKI4jHRHZ1qO9136ErKDWNY%2Bhm81kCrKgnI5LLs0TOgEqmCFlhmPVTvbVrWc9OrOQuAw7ieJ0eihOEwxVKMMnFNkAjTH43eZL3DALCMCQyXYdcCP0UzNwUE/1FPTSTIM7eLF3tgr/3ehzG0o%2Bd%2BPqwKOFWwSC9HDeaQdW8A1gNzQtS0rZIa1SrghAkGKJWI8j3urAgmBMCwAkPCpBkqSESKiQqcpJAaEkGYSQyQaqpXymVDgFVSBVUSGYVEKQ5TpUSOlAIAQuBFXyulK%2B70GpNRarFb2nUeroz6j9IauN8Zw0mmwTgQMQbYgMEYCG%2BVURcFRP5TaJA8A7RkhHA60dpCxyUPHS6ugSZ3Qeozc%2Bl9r4fQ4N9AaKJbj/TvsDBaOIlYCKESI6GqBYbxE/lgpGtD2powxtYrGcNhp41cQTUxRguD5S4HBGgtByaU2ppdZm9MeYRNZuzTm3MHZ80YALIWIt/JiwllLGWPMFYe22GktWDg8Ca1lqI1QutQQ80NvUd6ptzb0ytnk5GQp7YxSdi7TAbtFZGE9qAJxfA/YKADkHEOYcHbSKjkdORsg44XX8sopOXsS5WEsOnGImcQE50aPnQuxdU5lwrvEKu6yj6L0Kc4CArht4yTbhUMeege6NCuekIejR95LAXr0aeW854D1rmc5e8w153Int8/Ivzd6r1uQfM%2BawNin0RqgzRlDOBGJ4T44A5jhGBggG/Ladjv6ONRn/ABQDKBJWqnBY26DMEBFRAVAI%2BUzCMrMMkdKJC8oUMulQ2wNCUYdS6r1fqv0PFsImlNTgrQWALRYAoA0%2BYDR%2BNRKOCYG18BbQkbtWQMjJknXkAo2ZOgkikFUY9OWGi3pcq%2Bswv6ANVDStlfKxVyquQQBhm42xUVEgOL5c4lAXj3GsP9aMOVaQ0h%2BgVflP0zq/R2rkWTeIoSaZ01ZlE5NbMObqx5okwQgthbvXSZLMQWSHY5O6Y00g%2BAiSFOKdrMpyA9aVMENUk2ZsLb8gwOW22LTeBtMyB0923Twi9NRv0pg/tA7B1Dr5GK4zDoSCmadfVCcjV8OMHsmwtTjkBVzoWTgOxC4p1LhYcuN9K4SOriAye/yG5NzBa3RubyN4PJyE859ZQgXQo%2BUvGe7Qfk71OY0H9j7x6bwGE8iFwGYXHzhUdc1nL6ootjbcGVcrqxOvhBMV%2BaqP4I29b/Ug/9AGjBAVSyqSRsHspKmYajXB0oaGSAy%2BDN9ODUNavhsBECSGELgYkAI9GSq5VQYkC1CHGqEoSqg9aTHtE/ycasJ2WRnCSCAA%3D%3D)

## Links

- [Source code](../../../../conceptrodon/pagelivore/concepts/any_clarify.hpp)
- [Unit test](../../../../tests/unit/concepts/pagelivore/any_clarify.test.hpp)
- [Example](../../../code/facilities/concepts/pagelivore/any_clarify/implementation.hpp)
