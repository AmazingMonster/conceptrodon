<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::AllClarify`

<p style='text-align: right;'><a href="../../../index.md#conceptualizations-1">To Index</a></p>

## Description

`Pagelivore::AllClarify` accepts a class template predicate and a list of variables.
It returns true if the predicate evaluates to `true` for every variable and returns false if otherwise.

<pre><code>   Predicate, Variables...
-> (...&&Predicate&lt;Variables&gt;::value)</code></pre>

## Structure

```C++
template<template<auto...> class, auto...>
concept AllClarify = REQUIREMENT;
```

## Examples

`AllClarify` turns a fold expression of a class template predicate over `&&` into a concept so that it can be used for subsumption.

The following code will fail since `(...&&Pred_0<*>::value)` and `(...&&Pred_0<*>::value) && (...&&Pred_1<*>::value)` are both atomic:

```C++
template<auto...>
struct Pred_0
{
    static constexpr bool value {true};
};

template<auto...>
struct Pred_1
{
    static constexpr bool value {true};
};

template<auto...Args>
requires (...&&Pred_0<Args>::value)
constexpr bool fun(){return false;}

template<auto...Args>
requires (...&&Pred_0<Args>::value) && (...&&Pred_1<Args>::value)
constexpr bool fun(){return true;}

static_assert(fun<1>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwCspK4AMngMmAByPgBGmMT%2BXKQADqgKhE4MHt6%2B/kGp6Y4CYRHRLHEJZkl2mA6ZQgRMxATZPn6Btpj2RQwNTQQlUbHxibaNza25HQrjA%2BFD5SNVAJS2qF7EyOwcBJgsyQa7JgDMbkxeRAB01yfYJhoAgjPEXg4A1MrEmOgA%2Bhr3DxMAHYrI83uC3jMmI5kG80AwZphVMliG8YqhPG8AG5iLyYN7AiwEF6YYEAEROoMBQIpxypAN2%2B0OpNO5yuN2Od0ez1eBA%2BX1%2BXABhIBEMhjRhcIEiORqPRmJx3nxhOJePJlOFNI1jwZewO0JZZwuqGulwexGACluAK%2BAEcvHgvgo3hBTeYAGwez7fP4nNzmy23EAgRV45YA%2BEylFojG0N5ULwMCDhkFfAgbBjxsRKDVanWPRn6o6s42mgNWzk2zD2x2YZ2um5mT1N72/f6nctBkO4zDLAlNj0ut0DlsCn5CjsWivYYOh3sR6W7WUxzEJpMpixpjNvVUsqx5wHciV4ZA/JgKJTNaiJv0T7DJ8N0jirWicAK8PwcLSkVCcNzWaxIXWTZlTMY4eFIAhNGfVYAGsQACd1LgADndKQAiBd1JAATmOTCwP0ThJF4FgJA0DRSE/b9fw4XgFBACioK/Z9SDgWAYEQEB1gIZILnISg0H2Oh4kiVhtlUVCAFosLeYBkFhKRLjMXhvkIEg8HQPR%2BEEEQxHYKQZEERQVHUZjSF0JIAHdiCYZJOB4F83w/aCf04AB5C5eL5VAqDeCT3WkyRZPkt5FLMF0PCE%2BhUXMcDll4JitFWCAkEE5JhLICgIDSjKQGAKQzD4OhdmIeiIBiFyYnCJoAE97N4KrmGIGq3JibRaiYiDBLYQQ3IYWg6rMrAYi8YAzloWh6O4XgsBYQxgHEIbazqLE6xcpFagubYIPCXZXzM2g8BiGzmo8LAXOJPBSOm0hVuIdElDJPZ5sOoxoNWKgDEtAA1PBMEstzkkYerDOEURxAM7T5CUNQXIs/R5pQADLH0I76MgVZUGSHopskmZ0BOMlTEsawzGou7iA0taMc6bpMhcBh3E8No9FCeYygqPQCgyARJj8JJuZ6QYOZGaoug6%2BpZj5vQajqAQ%2BmaYXhgSaopeZ3JVf6JXFhV1YFGArYJEcjh30olyaL8qSZLkhTJCUl1cDUmKwK4eLIPe1YEEwJgsASZNSHgyRjkuXCgUkDRJDMSR3XIxDsMIjhiNIUjwMuND3WQ7DkK4d0AkkLgAlw90zbMmi6IY93mOSjiUq4zy%2BKynLotEthOCaFgsSBSSmDhAwjFC7DLi4S5v1UohKc0pIod0iHpCh4zYbM3RCus2z6uN02qN4GiPJ4i43h8t52877ve/mgeh5HiLUCi%2BJ%2B2OMw3cSlja6b%2BJ%2BOym/0uikBj675A%2B75WwlwCiNBaAlTKhVMyjVaogxgc1Vq7UHAg26owAgfUBouWGqNcak0QazRetsb8%2BAvgrTWmZDayAtog12l0Fyh1jq1TOkQhKlNroQTug9TAT05pGFeqAKufAvoKF%2Bv9QGwMbrT3BvpOesgF6mW/MvBGb1iZWBRgw9G/ssY404HjAgBNjhE2RhYMm28KZU00XrcWcs/AQFcNLJIbNSjKy5mkHmWR1b8xSG4oW7MXFizpvLNWOQvGyx6ArOYzidYy2CSzTWis/HRNdmsDYhtkn7U3ubTgR9iAdy7j3AB58uCD2HhoB2%2BBx731dglD2pAvY%2BxGP7faScU6DwjkCQuQIgTHEjtHfOJdqKcHLoxd6rEa5IG4l5D%2Bb9iAt22O3GSLAFBYlhFiYplxmQzBUhU9Sk9QYzxkaDeRcMQDHFIKvOy00N7OVLu5eu3lfILKCkslZ2J1mbL5BASK3876xWOE/UZr8v4ZWmcCn%2BKzkjJB%2BGs7CPwPlnlyVhIq4D4iQMqtVZqcCMUtTah1FBN8eroP6oNYhmARpjTEHgm6BC%2BEsNICQiWq0pqj1UJtXYNDBB0IOkdE6NVmEXTYSDThaRuHPT4eEARSUhFMB%2Bn9AGQNPwQSkXpCQsijIwwUToU5yjjDGNRjESxP5saZCmgAenxkjEmlhTE/nMVgQ1YT6Z2MZg44IjNtacwFj4zIrrBaZA9aLWmEsgn9FdY6kNCSomerGKGzxMStaJM9XrA2%2BlrkDO3tkp5bwXmrPeQaGY5SnZVIBVXT23tfaUGNi0/wg9jjHACAECOICNB1swshdNrlaK2Ars/ZYcEQBByHscZCecwKNvdGBTCCdjg3MGV23txtlIdrLpXJKqw7rpGcJIIAA%3D%3D)

By turning `(...&&Pred_0<*>::value)` and `(...&&Pred_1<*>::value)` into concepts, we allow compilers to perform proper subsumption.

```C++
template<auto...Args>
requires AllClarify<Pred_0, Args...>
constexpr bool fun(){return false;}

template<auto...Args>
requires AllClarify<Pred_0, Args...> && AllClarify<Pred_1, Args...>
constexpr bool fun(){return true;}

static_assert(fun<1>());
```

## Implementation

```C++
template<template<auto...> class Predicate, auto...Variables>
concept AllClarify = (...&&Predicate<Variables>::value);
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwCspK4AMngMmAByPgBGmMT%2BABykAA6oCoRODB7evv5BaRmOAmER0SxxCWbJdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHASYLCkGeyYAzG57B0eYp25MXkQAdE%2Bn2ADUyAYKCq/KxJj4oj2pFed0eTwAas08EwYvQFC8TBoAIJoBjbFIEV5I2i0NwGYh4KgAT1epwAIq8IE8HuYAGx037/PCA65nSEEmFwl4gEAANzEXkwK1OVmRiKRAHoAFQy2Vy%2BUS8XS2WvAAqmFm3zliuRyvl%2BplOqR4ouhyYxzOoNQ1IRyNmxC8Dh%2Bf3QAH0NOKTAB2UVI17%2B16zc3M94CWaYVQpYivGKoTyvfneTCkn0EB3XL1kkWezPZsXI01XG5Wm0nbDi%2B2OzGMt1cHO%2BgOBpqOZChhjhyPR2PxxOClMWNOC71Zk6%2B4d540F/Zmi23e7Wp5I4jAeFl8V/ACOXjwf2%2B2Nx%2BMJRJuNfdwKXK9L5eRqI7UZjcdoryoXgYEGFPr%2BBE2DGfYiU2a5vmSKFuarJzmCDwXqu15LpgW47hqWI4niULEieLpnliy4KFepJmPSBHIQeaHHmcp5cOeOFXuKt57J2D7xi%2Bb4fhYX4/q8g6slYQGTkiQYtq6TBfPEBDUK%2BNx1mW77CqOHBrLQnABLwfgcFopCoJwbjWNYgYbFsybmCcPCkAQmjyWsADWIABJIDwaJIXBeicGgBBoBG0tUySKRwki8CwEgaBopCqepmkcLwCggMFZlqfJpBwLAMCICAGwECk9zkJQaAHHQ8SRKwOyqIktIALS0pIrzAMgrZSA8Zi8EyRAEugej8IIIhiOwUgyIIigqOocWkLolEAO7EEwKScDwClKSp5kaZwADy9wZZiqBUK8xVlRVVU1a8dVmJSHi5fQ0ZGVwKy8LFWhrBASA5SkeVkBQECPc9IDAFIZh8HQezEFFEAxAtMThM0RLTbwoPMMQRJLTE2h1LFJk5WwghLQwtAQ0NWAxF4wC3DiUXcLwWAsIYwDiDjiH1LyGoLRGdT3DsJnhHsPnqbQeAxBNsMeFgC1pngAUk6QdPELGShkvsFNc0Y5lrFQBgruCeCYKNS0pIwkO9cIojiD17XyEoagLSN%2BgUygOmWPo3NRZAayoBiWTE6VszoOSpiWNYZhheLLX0w7XQ9FkLgMO4njtHooQLOUlR6IUmQCFMfiUYnvRDHHoyUbU9QCP0kyR3kOfdEjDRzJnIwJDncwp3oQYtJXSzV2sCj6dsEizRwykhQt4VbSV5WVdVtV2UdEC4IQJD4cZV2mQrawIJgTBYAk76kNZkgnA8ACcJxepIDlmJItJBQEtI7/onB%2BaQAXGQ8tJcLSiQ74kT%2B2VwAR77SvdDeFkXRXnnFO6yV7qpVWplV670zoFTYJwZoLBeRelKkwd4BgjAHR3g8Lg9lGr4GangVqlEjadQNtII2/VTZDV0D9cak1IZdx7qFXg4UVrpXuK8DaIJiCIOQagj4FNMHYPssdVAp14gzzMHPG68UwHQPiFlN6YinpnRAAgpBpUBFGC4DvLgwUaC0H%2BoDYGQ1obgx1mY2G8NEYOB1qjRgBAMZYwWrjfGhNaDExMmTWWOx1L4D%2BLTemQ1GbIGZjrNm3QFpcx5uDfmvjroEhFiZcWktMDS3JkYOWoBgF8GVgoVW6tNba1FiQ/W3VyGyEoYNdSNCLbyy9lYG20T7brydr0V27tPbWwsL7Fh/tCGB3XrnXoYcI65FTsEcOTd45p3SEnbIRcJnpyyNM7Owcy751ros%2Bupc859ArrHKu9ctnjOOQMVZLd1ibA7pdK%2B3d5p/04Nw3hKC0GCJ0cIjQlJJ7NRnpda6C9SBLxXqMdePkb53ywQ5L0X8vTOUkMfCqlFmGLQirYQBMiQHwDAWlNaij5HEFgTsBBu0WAKF5K2XkHyrizDwVPFqbVZCkPKbrKpZsQAnFIHQqaJNGEPLCstCB61NoksqmSilCZqVgVmKI8R50zAnBONIhWCUHrKOevi9VqiKUpBSK6KlO9XQ0oIEJHhFVfqGPiMYkGYNYYWNtXDBGSM7FiLRo4zG2M/GYDxgTMQHidbeMyfE0g/iy502JupEJYTRYRI5rwaJvMiRxMFoknWKT0hpJlpk8I2Tbq5KYCrNWGstaqRMqUrqEgKl9RNtUnQHK6nGG6bbGILTHbOzDJwCU7srbe0sL0jS/SsCtvWXs0ZddKIxzKEc2ZRQsjjtSHMjOhzm47JDpsgY87hnl3OcumZ4wN3bJrjuqdK7blt2ud1Plv8BUcGeaS8llKpV7BlRPfB08LrKuAYvZeq9KBdwhf4LBiqAhuUckFRVXpn7XpYZwABMVAWbwCLvAIiQCI70kDvZy%2B8uCcp8icflMG0WYq7g1aDqKAVfrFla0OkggA)

## Links

- [source code](../../../../conceptrodon/pagelivore/concepts/all_clarify.hpp)
- [unit test](../../../../tests/unit/concepts/pagelivore/all_clarify.test.hpp)
