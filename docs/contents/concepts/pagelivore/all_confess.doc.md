<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::AllConfess`

<p style='text-align: right;'><a href="../../../index.md#conceptualizations-1">To Index</a></p>

## Description

`Pagelivore::AllConfess` accepts a class template predicate and a list of elements.
It returns true if the predicate evaluates to `true` for the value result of every element and returns false if otherwise.

<pre><code>   Predicate, Elements...
-> (...&&Predicate&lt;Elements::value&gt;::value)</code></pre>

## Structure

```C++
template<template<auto...> class, typename...>
concept AllConfess = REQUIREMENT;
```

## Examples

`AllConfess` turns a fold expression of a class template predicate over `&&` into a concept so that it can be used for subsumption.

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

template<auto I>
struct Vay
{
    static constexpr auto value {I};
};

template<typename...Args>
requires (...&&Pred_0<Args::value>::value)
constexpr bool fun(){return false;}

template<typename...Args>
requires (...&&Pred_0<Args::value>::value) && (...&&Pred_1<Args::value>::value)
constexpr bool fun(){return true;}

static_assert(fun<Vay<1>>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxBIA7KQADqgKhE4MHt6%2BASlpGQKh4VEssfFcSXaYDplCBEzEBNk%2BfoHVtQL1jQTFkTFxibYNTS257SO9Yf1lg5UAlLaoXsTI7BwEmCzJBpsm/m5MXkQAdGf72CYaAIIKBMReDgDUysSY6AD6GlfXJglWNyeQKedyYjmQTzQDDumFUyWIT2iqE8TwAbmIvJgnn8LPdMX8ACL7AG/BJE/wkn6bba7TD7Q7HVBnE4XH53B7PV7vD5cH44n7AkENcGQgQwuEIpEo9HeLE4vF0snEvlKil8m7UnZgukHI5EJ4ASVZN3ZjwITwAsgJUEQGABPFUkwWgkVQ8Xwp561BojFy/5G1WUwPq66a2n0gh25KMViYZnXYjABTGhOYACOXjwbwUTwgzPMADZC1zPt8DgmkyAQDL8f5sFWa5h5j83ZsJYjkbQnlQvAwIM3/m8CCsGN2xEplUqblStlq9gdI9HmGx44nk3Wfm8M1nMDm8%2BczEXDyWvvSKwoG76LpfZfNsYfC7n8w/j29Przy2ub7X69Xfc2blbWEPSlLsez7AcLCHEcngVSciWnE1hTwZAPiYBQlCaahe3pK0GBtAQHQOD9LjrftmwpDhFloTgAFZeD8DgtFIVBODcaxrBBZZVjlMx/B4UgCE0KjFgAaxAWiCxOAAOAspFohIC0kABOfxFL4/ROEkXgWAkDQNFIRjmNYjheAvAyhKYqjSDgWAYEQEBlgIZJjnISg0G2Og4giWNOFUWSAFolKeYBkAhKQTjMXh3kIEg8HQPR%2BEEEQxHYKQZEERQVHUKzSF0LhSAAd2IJhkk4HhqLohjhJYzgAHljhc81UCoJ5/ILILJBCsKngisxcw8Tz6ARcx%2BPmXhLK0RYICQDzki8sgKAgOaFpAYApDMPg6E2YgLwgaIauiMJGjtcreCO5hiDtOrom0GpLIEjy2EEOqGFoU7cqwaIvGAQ5aFoC9uF4LAWEMYBxE%2BndalRXcathGpjnWASwk2GjctoPBohKq6PCwGr7jwXSgdIGHiCRJQCS2MGMaMYTFioAwkwANTwTBCrqpczoy4RRHEdKkvkJQ1Bq/L9DBlAOMsfRMYvSBFlQZJHDFTgArudB9gJUxLGsMxjNJ4h4thuXbEwewlb8CBXDGPwCpCaZSnKPRUnSc3radgpzb6B25hNs26kmN2Co6c3uiaL2BgqYYekDqOw/tiOJEWBRuLWRPNI4ejDJqky2sC4LQvCyRItzXBYpGviuHGwS6cWBBMCYLB4n7UhxMkfwTlUhJJA0SQzEkAt9Mk5T0%2B00hdP4k45ILaTlOkrgC1oyQuFo1SCyz3KTLMkALLpmz7JmxzGtcpaVuGny2E4RoWFRBIAqYSEDCMXrlJOLgTmYmKiANhKCoFlK%2BekALLKwtcq6E2sVUqZ1KoZ2qhveqR9mqtSvjfO%2BD8wbP1fu/AaqAhpxHvP4MwVdJrWQPqfOIbllo4PmsNEAyDb7IEfutZSXADI0FoDtPaB1coXROlzHhV0bp3QcFzJ6jACCvXejVL6P0/oAy5iDam6xmL4DeNDWGuV4bIERlzFGpsaoYyxidXGSiJoGyJgJUm5NMCU1BkYGmoArL00ZgoFmbMOaMC5n/XmaVAGyGATlZiYCxa0y1lYKWBjZbNwVubQGqsCDq38JrSWFhda8FQPrQ2kSk6m3upkFwDB3CeFaHoO2JQE4FWdoULIRTcgVI9pkcOsxI7B39tHGpNtfa5K6JMRpjsg4B3aXoUEccylNLTsnFYqdK7p0zkZNJnBPTEGvrfe%2BDD0FcBfm/DQJd8Bf3wZXCaNdSB1wboMZuaNR7jxfj3BIK8EgJH8L3fuS917GU4FvHeji97wAPk5JqFCyHEHPusK%2BwUWAKFRBCVEGyTi0juNFXZcUf7c3/j47m/iRZ5AgWVIG0DZnZ3gc5Y4TwWqLJYGCiFUKYVwvNBAQa1C8GjX8EQ3epCqELQBeymhkLkjJA%2BNC5SHwaVoSWUpLa7C4icMOsdK6fCZXXVuvdERODnriLeh9ZRmBvq/TEHI4mCi7EmNICo3JMNAYf1UAjTYOjBB6PRpjbGdpjH4zMVzSxaRrFUzsWEBxU0%2BDONcezTmxMvGpQkL4zKQsAk6DyIwiW2twky3gPLRWmRAYAHo1bxrCSkvWcRv5G2bi05wlsCkx1KTMPp%2BQXaZBjpUz28cxlBxyZ0BgodmiDObX7bpPRek%2B2GR2nIHSB19oqEnFOaU8WwLeRwMlFLIVompdqO4Oyy77JZY42u9dG6UGgZckAZgX7%2BH8LRWiPcWEaGPYpaSrz5mmVsNvaum6W4gDbq/fw0lF58TPQWPiil07%2BGnXew5z60ZRVvbVe9xD5iLFJukZwkggA)

By turning `(...&&Pred_0<*>::value)` and `(...&&Pred_1<*>::value)` into concepts, we allow compilers to perform proper subsumption.

```C++
template<typename...Args>
requires AllConfess<Pred_0, Args...>
constexpr bool fun(){return false;}

template<typename...Args>
requires AllConfess<Pred_0, Args...> && AllConfess<Pred_1, Args...>
constexpr bool fun(){return true;}

static_assert(fun<Vay<1>>());
```

## Implementation

```C++
template<template<auto...> class Predicate, typename...Elements>
concept AllConfess = (...&&Predicate<Elements::value>::value);
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwArKSuADJ4DJgAcj4ARpjEAdIADqgKhE4MHt6%2BeqnpjgLhkTEs8YlmAGy2mPaFDEIETMQE2T5%2BQTV1mY3NBMXRcQlJtk0tbblco30DpeUgVQCUtqhexMjsHASYLMkG2yb%2Bbtu7%2B5iHbkxeRAB0d4fYANTIBgoKj8rEmPii26SPBAAnslGKxMHcbth6GxBAoHiYNABBNAMDbJAiPRG0WgeBhUTBvR6HAAijwgEPMlUpn2%2BeF%2B5yOUJ2jAIChAIAAbmIvAzsOyud5MItDlYkQjEQB6ABUMtlcvlEvF0tljwAKgTWY85Yqkcr5fqZTrEeKTnsmAcjldbvd/NhxQoCMQvA4Pl90AB9DTikwAdlFiMegceDvNdOeAgdmFUyWIj1iqE8jwFPKJfsdPN9xJF3p9Wf8/pNOzNFsu11QFNt9vTLppHq4Of9QeDTUcyHDDEj0dj8cTycwqYs6fOuezYpH%2Be9SNNZwuVtQjwAkvCkQ6nS6ALICVBEBiAhvipsh1vtzsxx5zpPc/u%2BixL8cF%2B%2BTxHT80M47A0FsCGI4jAOGVpEvgARy8PAvneLEcQEfE3guWtPX%2BH8/wrO0kRRU9uwTWhHioLwGAgYU/S%2BAg1gYHCxCUbMRzFKcixnI4gRBZgvzuJD/1Qn9MBAsCCUxbFcRg/83HgjREN/BQUKJKpKT4qC8QJIT4KmTFxJQ8V0O2Ls4ywnC8IIm9iNIgEnQZKxqONFcWzpd0mDeBICGoPCLk3BhtwEPcjnrStbQI4UJyRDhlloThAl4PwOC0UhUE4NxrGsYNVnWa8zH8HhSAITRAuWABrEBAkkG4NEkLgfX8DRAg0KpKjMAAOGr9E4SReBYCQNFE8LIuijheDZUSMoiwLSDgWAYEQEBVgIZJrnISg0F2OgEiiMFOFUGrKgAWkqSRHmAZA2ykG4zF4WkiGIPB0D0fhBBEMR2CkGRBEUFR1AG0hdCmAB3YgmGSTgeCCkKwsyqLOAAeWuKaMVQKhHlWjatp2vbHgOswyQ8eb6FjcxUsWXh%2Bq0ZYICQObkgWsgKAgEmyZAYApDMPg6G2Yg2QgWJgdiCJmkBP7eA55hiEBUHYm0TAHB50g5phAhQYYWhuderBYi8YBLmxNluF4LAWEMYBxAVniHDwDkCWBqNReuTY0oibZgte2g8Fib6BY8LBgcdPAWo10hjeIeMlGJHYdftoxMuWKgDD/AA1PBMA%2B0GmPFq7hFEcR7qTp61GB979B1lA4ssfQHbZSBllQdFMnV9aHXQElTEsawzE6n2zqwYuCK6UX6hcBh3E8do9DCCJBjKYYpnyDIBAmPwx7SCeGFmIZEimOxO56MZWj7yYO8NgRehaBeR6X6Zxk36fj/6Ie5lH5YFESjYJABjhQtIDreC62G1s27bdv2grUYgXAhASBSRxnjUOywECYCYFgRI7dcqSH8DcAAnP4H0kgipmEkJUNqgRKhIIahwJqpAWqpRuJULglQapIJqhQ/KXBAgoOqK/EG3VbAgD6qHIao0ibjQhtNCmVNMZLTYJwZoLAOQ%2BnWkwZ4BgjDIyQTcLghVjr4FOudS6sgbqp2kOnJQmdXq6Hpl9H6PNH7P2YV1cGk1riPGhueYg4jJHSJeDreRijCpo1QBjBIICzC43SpwnhgiEgzUpl40mmMQBiIketFxRguBIK4KJGgtAmYszZq9PmXNxZZIFkLEWYsvaSxZDLOWwNFbK1VrQdWaUtZB02JFfAXxDbG3VpFM2yALbi2trUYG9tHZcxdg0vGZ1PZpR9n7TAAdtZGGDqAAaYcI4KGjrHeOjBE6aJTndHRsgM4vUioYnOIc65WALv0tupdy4Rk4FXAgNd/DEhOQ3JuCQW4mxLtvLuEBXBTwHj3A%2B8wZ4FEyL8oFc8AWj0%2BWvPooKoW73XhCo%2BIYT45DPsii%2BJRF4PxWGse%2BXAzFA1eu/aJTiZGuISe4jQZJAGnRAfisBCyIFQJgZQR%2BRCSEKKKj6BhPpSqSEwVtKYFjOA9XYQEhZXD4A8ImpDUJwTiDCM2GIhGLAFAcjbByClZwHQqKAS3DR10tkSB2Y9PR%2BydABFIMY36GsCUv2BpYvhUMYbKu2qq9VSYtWvgdJ47xWMUr%2BH8fjQaQTwlkzlWGyJ6rkjJHdJqpB7ptUEBsg4raDNUkJHSezTmAsck5sFsLTu4timCFKfLRpmAlYqzENU8WdTZnDNIE01erTTaqHNtsbpghel2wdk7QEQy3ajPFhMtIUzA6zIiPMgmfAlkrLjgnL2SctHbIevIM1WdLWyOMPnGw5z4CXPqOrCU1c8710sI3N%2BzdzrvPbivHefhvk91hYPTFh88iz3qLC8e9REV6HvfUPeG9UX/tqKveFMxL5YuXuvWF6K/34pxUlbFttzEOs4PYlgKq1Uaq9dsH1ADVHAOxvS8VBMmXQOGO3W27KFgKP8EECqxU2oMZ9JQ%2B1RKRVsI4Yy0g8DAjIMCDVKoSDJBINKqgrg/gCH%2BEJZ1LjwbFiPyOhx%2BTrDFPLB9ukZwkggA%3D)

## Links

- [source code](../../../../conceptrodon/pagelivore/concepts/all_confess.hpp)
- [unit test](../../../../tests/unit/concepts/pagelivore/all_confess.test.hpp)
