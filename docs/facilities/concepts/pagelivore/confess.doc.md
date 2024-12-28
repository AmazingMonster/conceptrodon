<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::Confess`

<p style='text-align: right;'><a href="../../concepts.md#pagelivore-confess">To Index</a></p>

## Description

`Pagelivore::Confess` accepts a class template predicate and a list of elements.
It returns true if the predicate invoked by the value results collected from the elements returns true and returns false if otherwise.

<pre><code>   Pred, Es...
-> Pred&lt;Es::value...&gt;::value</code></pre>

## Structure

```C++
template<template<auto...> class, typename...>
concept Confess = REQUIREMENT;
```

## Examples

`Confess` turns a class template predicate into a concept so that it can be used for subsumption.

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

/**** Vay ****/
template<auto I>
struct Vay
{
    static constexpr auto value {I};
};

/**** fun ****/
template<typename...Args>
requires Pred_0<Args::value...>::value
constexpr bool fun(){return false;}

template<typename...Args>
requires Pred_0<Args::value...>::value && Pred_1<Args::value...>::value
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<Vay<1>>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwapK4AMngMmAByPgBGmMQB/qQADqgKhE4MHt6%2BAUGp6Y4CYRHRLHEJ/kl2mA6ZQgRMxATZPn6Btpj2RQwNTQQlUbHxibaNza25HQrjA%2BFD5SNVAJS2qF7EyOwcAPQAVAd7ANTKxJjoAPoaR4d7OyYaAIIEmCzJBi8m/m5MXkQAdICvtgHo8ZsQvA4TmdLhpQSYAOxWJ5HVFHGZMRzII5oBgzTCqZLEI4xVCeI4ANzEXkwR0RFgIEMwiIAIl9kY9Wez4U99odoecLlwbod7k8Xm8Pszvr8AUD/CCnuDIQQBZcuPCkaC0ejGlicQJ8YTiaTyVTvLT6YyaVz/BzbfbebcjgA1JgATxFBzFz1e70x0p%2Bf1QRwAksDQcqoW73ZqOTqMfrcUaiUdZSHzTS6Ujwwi2XbNfnHY8%2BQcjlQvAwvXdQRL/Z9vgR3clGKxMID/o9iMAFBGnmcAI5ePBnBRqq5fNxdnsgECZ9vy7Cz%2Beg5MvY0ksm0cuViDLelnAgbKtUMRKbl5nm%2ByUBydNlvMNgd6e9hWgwfD0fjuHfF/L6kLv8wL/hadJmAAbOY4Hjhqv7dgoIE0h2wFzgBq6GuuqamtuFYMHuB6YEexBVta0pWJeTygqWxwACqYDM1Y%2BjsOxHNgxDECQkZ6ngyAXEwChKM01CVpOMaTrBIIKnu%2B52hwqy0JwACsvB%2BBwWikKgnBuNY1jousmyWmY/g8KQBCaHJqwANYgIp4H/AAHOBUiKQi4GSAAnP4rlGfonCSLwLASBoQSqepmkcLwCFBGZalyaQcCwDAiAgOsBDJH85CUGgbx0PEkRtpwqiOQAtG5RzAMg2JSP8Zi8OchAkHg6B6PwggiGI7BSDIgiKCo6ixaQuhcKQADuxBMMknA8PJSkqeZGmcAA8n86WqqgVBHEV4GlZI5WVUc1VmEcEAeDl9DEuYxnLLwMVaKsEBINlyS5WQFAQE9L0gMAUhmHwdAvMQCEQDE80xOETTulNvBg8wxDuotMTaLUMUmdlbCCItDC0JDA1YDEXjAD8tC0Ah3C8FgLCGMA4i4yOyN4BS9HzQStR/NsJnhC8CkDbQeAxONcMeFg82MnggVk6QjPEKSSgsq8VO80Y5mrFQBg9i6eCYCNi0PlD3XCKI4hda18hKGo81DfoVMoDplj6HzCGQKsqDJD0pPFTM6BfCypiWNYZhhVLxBNUzTudN0mQuAw7ieG0eihPMZQVHoBQZAIkx%2BMNqc9IMScjMNNR1AIfQTLHuQF109PF7MufDAkBezBnegYs0teLPXqwKPpWwSDNHDKaQoW8OFm0lWVFVVZINXHbgDUXUZXDXaZyurAgmBMFgCR7qQ1mSP4/yeQikgaJIZiSOBwW2e5vkcP5pCBf4Zj/P44EIvZ/j2YpilcF57n2YP81wqRRANFZW8UkoPRSitDKb0PrnXymwQqY9drIAMEYA67l/hcH%2BOpeqRBg7NWGibdqRtpAm16ubAauhfpjQmlDPuA8h4LQ4MtNKfwjjrVHttMqqCqYYKwTg46p1nrnTAo/Jet04qQLgfETK71UBnRGLwowXB3JcCCDQWgAMgYgwGjDCGet9FwwRkjBwes0aMAIJjbG808YEyJiTPWFMFbbHUvgM4dRGak1waoVmLw9acy6PNXm/MIZC1cTdYO4sTJSxlpgOWlMjCK1ALFFWasFAay1jrRgetiGG06mQ2QFD%2BrqWoVbJWvsrB2xCY7beLs3acA9gQL2/gfa2wsAHYeQcQ61M7pXIufgICuCbsNBOpQ64pzSGnLIZdM4pCmTnROEyK4R2rv0EZ4cq69Brks9uzdG6zP2f0NuydF5rA2D3M53NGGAM4FwnaOI0HAH4dg64EBZ74LEYvG6K9SBrw3iMbe1l1FBG5nfB%2Bil/geUUu5MwsKIL2R/m5ABA0gG2BAcvVJ4D4CQNSqtORMjiAIO2E0FgZUWAKApNiCkqj/hShmHVfA%2BCmotVkCQgp%2BtikWwCKNcak0yYMLmqipa0C1obVUOSyl1LaX0tVCdBRIj4hiP8BIsB0iFUvQJRq86c5kDJGSBcGl7kLiyouBKsh/14g6NBuDOGhjbXw0RsjcxCj0ZWKxjjNxmB8aEzEI4iWzikkRNIO4%2BmXjma%2BOQGzAJgggk8z5gLd04SRZRL1rEtI8T5ZJPCCku6fB0mZO1rrCWeSOoSEKT1M2JSdA8qeTbP21SHbwGdq7TIpMdie3rVUjpgd4gENDtvQuPQo4xxyHMsZCxTnzMKJkDZ2dMgnPzpsgZJcWiHJWVs1di765jHWeu3drddmnM7t3TqgqUVhTueao4FKqWUhlQGBi7ymUkC%2Baq1Jq916b0oH3cFAQn5IqMmYYDXB7IaHAjCi9w9ODANAR%2BneIA95YI/opU%2B/hFLgaMq5G%2B/ghWXoipiu6fdapQeYT8%2BDUt0jOEkEAA%3D%3D)

By turning `Pred_0<***>::value` and `Pred_1<***>::value` into concepts, we allow compilers to perform proper subsumption.

```C++
/**** fun ****/
template<typename...Args>
requires Confess<Pred_0, Args...>
constexpr bool fun(){return false;}

template<typename...Args>
requires Confess<Pred_0, Args...> && Confess<Pred_1, Args...>
constexpr bool fun(){return true;}

/**** Test ****/
static_assert(fun<Vay<1>>());
```

## Implementation

```C++
template<template<auto...> class Predicate, typename...Elements>
concept Confess = Predicate<Elements::value...>::value;
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwapK4AMngMmAByPgBGmMQgkv6kAA6oCoRODB7evgFBaRmOAmER0SxxCUm2mPbFDEIETMQEOT5%2BgTV1WY3NBKVRsfGJyQpNLW15nWN9A%2BWVIwCUtqhexMjsHAD0AFR7%2BweHR/tbJhoAgrv7ANQAkiwp9GyCTPXXB6cXV8c/x5/nZ3OBEwDwMwJM/jcwNBr0wELcTC8RAAdKiIdhrsgDAoFNdlMRMPhRMDSNcCABPFKMViYVHI7BPRgEBTowFoBgbFIEa4eBhUTA464QgAieIJRNh8IZIKZChAIAAbmIvLS0f5sPKld44f4rBdAd9ficDQdrgAVAXM97Gr5Gw7/E03fGEgD6Gmte3%2B0MekshiJRauwgLGxC8DjFro0gJMAHY9edronrjNHMhMQIxphVCliNcYqhPNctSqhXGCKG4THhRD47Hq7ro7aneKXVwPTsvSCfeC/UjUHTWRcQ2Huc70K3o3HAUnk01U%2BmGJns7n84Xi5hSxZyyq6zXJ/Xa029tcAGpMcntzswnsIvt3QfnYfhs/kyfxmcpvBp9lLnPXf2oEWyobrGFi3LuDb6lWe76keOzXFQXgMJegLemCOpQpS1JsHS5zEMALLqoCBIAI5eHgBK4ry/I4vCY5uqSeEEQOREXD%2BwLLnmBa0AhSEQIsoEEgQazIVQYhKHu0GwUCXbofCFJUswOGokxhFBhcpHkZRPICDRhFuPRQTXKpLEYuYABsFk6XyAr6fRXCMfhCimWyGYcX%2Bq48YhDD8YJmDCcQyHbjqVhSQCcHmpaKFDnOX4ukwOLxAQ1BIfCL7wlwrLqvxAm6hwyy0JwACsvB%2BBwWikKgnBuNY1jJqs6wgWY/g8KQBCaPlywANYgEV5nIgAHOZUhFTG5mSAAnP4Y3NfonCSLwLASBoQRlRVVUcLwcpBO15X5aQcCwDAiAgKsBApEi5CUGgDx0PEkQ0pwqhDQAtON1zAMgaZSMiZi8IShAkHg6B6PwggiGI7BSDIgiKCo6h7aQugOQA7sQTApJwPAFcVpUdZVnAAPJIhd3KoFQ1zPeZb2SB9X3XD9ZjXBAHi3fQubmC1iy8LtWjLBASA3Skd1kBQEBCyLIDAFIZh8HQwLEHKEAxPjMThM05JY7wavMMQ5KEzE2iYA4WukDdzwEITDC0JriNYDEXjAAitC0HK3C8FgLCGMA4h2xRxuOAqAr41mxtIpsrXhMChWI7QeAxOjeseFg%2BPlngS3u6QQfEPmSjCiC3tx0YHXLFQBgESeeCYCjhOKabYPCKI4jQw3cNqPjyP6N7KC1ZY%2Bjx3KkDLKgXJZG7L1jOgIqmJY1hmOt2fEMDwdD10AdZC4DDuJ47R6KE4SDBUwwOYUmQCJMfgn%2BkZ8MHMQwJA5djrwIvQTDveSP7Uz8NOM/QH/Mx9bC/wvnoGYLQ75HwfssBQDUNgSBxhwEqpA1q8A2pTV671PrfUkL9ZmuBAYc2alwbmbUS7LAQJgJgWAEj8VID1JIyIpoxkkBoSQZhJDmRWn1Cac0OALVIEtfwZhkT%2BHMjGAa/gBpFSKlwaaE0BrIPxhtLaIAdolwOsdAWp0SaXTFhLdmD02BPQwbTLE3sGYTWRFwZEFUAZECXiDByDcIbN2kK3JQ7dEa6FlmjDGWsEFIJQQTDgxNzpImuOTdB1N3pmKMBYqxNjmas2FuzIUzUzAkN5vtLR%2Bj4hXXFqgNmwxYnSwmlwIINBaAKyVirRGOsNam3qXrA2RsTaZ3NkyK2Nt8b20ds7V2ptPaF02BVfABIHB4CDm7Wxqgw7AlNlHWo%2BM44Jw1snEZPMl4Z1atnXOmB85eyMEXUAe1S7lwUJXautdGD11kC4qGbjZBtwRhVbxXdi4zysH3FZg9aEj3qOPSe09e4WHnqgxey9fnQK/hM5wEBXAgIcvvMo989Cn3qIi1I196gQIWJ/boL9gHv0vmvWFP9Zj/1RY/IluQSVgL/iiyB8CVhrDgcQ3hgSlGcCiTTTEBg4lcEsdY90EB8H2LSVzHmZDSAUKocMWhPVylBBjvwwRRVkSTSKhNMw2qzDmQGrI8aijEbKNsKo0hpyNHwC0WdUm%2BTcnEEMZsZoLB3osAUAqNMCpBXInQmMf6%2BB7HA1BncpuDyYbyA8S8nQARSC%2BMxu7AJeMTVEx0WTCmqg3Ueq9T6v13IWaFJSfECV/hMnqJyYWkW9rK3s0VMgFIKQXTeomi6PNLpM1uPlvEGpqt1Z60aX2/WhsA6mw6YILpttRmYAdk7MQAzM5DKORs0gYz15TJDrM5A4cFmCCWbHeOidyTrNTls02uz0j7ILkc8IJy%2BZ8HOZcmuddM7OLDRIR5sMo0d1jfy4wIL%2B4xChZVUeGZOBbEnj3WelgwWVQhVgIDT8yWb23rSveW9cWAPRVkTFWGSiUqZfi7%2Br9WjEtATC%2BoxGMMPyAX0TF9KqPMpgayqGSbjXrW5R2647rPVFlzbCMYeDA0kAlcQqVpzyGUOoZQBBqqAjCMNekswZguADQ0OZLVbHUGcBUWo8TdCRhWMkUVNh/gipqeamNXh/hk3sc2havmCC/qaeCWJhzWdu0b0kEAA%3D%3D%3D)

## Links

- [Example](../../../code/facilities/concepts/pagelivore/confess/implementation.hpp)
- [Source code](../../../../conceptrodon/pagelivore/concepts/confess.hpp)
- [Unit test](../../../../tests/unit/concepts/pagelivore/confess.test.hpp)
