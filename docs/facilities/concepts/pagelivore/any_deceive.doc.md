<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::AnyDeceive`

<p style='text-align: right;'><a href="../../concepts.md#pagelivore-any-deceive">To Index</a></p>

## Description

`Pagelivore::AnyDeceive` accepts a class template predicate and a list of elements.
It returns true if there exists an element whose value result fails the predicate and returns false if otherwise.

<pre><code>   Pred, Es...
-> (...||(not Pred&lt;Es::value&gt;::value))</code></pre>

## Structure

```C++
template<template<auto...> class, typename...>
concept AnyDeceive = REQUIREMENT;
```

## Examples

`AnyDeceive` turns a fold expression of a class template predicate over `||` into a concept so that it can be used for subsumption.

Since `(...||(not Pred_0<***>::value))` and `(...||(not Pred_0<***>::value)) && (...||(not Pred_1<***>::value))` are both atomic.
Both candidates are considered equally good.
Thus, the call is ambiguous.

```C++
/**** Pred_0 ****/
template<auto...>
struct Pred_0
{
    static constexpr bool value {false};
};

/**** Pred_1 ****/
template<auto...>
struct Pred_1
{
    static constexpr bool value {false};
};

/**** Vay ****/
template<auto I>
struct Vay
{
    static constexpr auto value {I};
};

/**** fun ****/
template<typename...Args>
requires (...||(not Pred_0<Args::value>::value))
constexpr bool fun(){return false;}

template<typename...Args>
requires (...||(not Pred_0<Args::value>::value)) && (...||(not Pred_1<Args::value>::value))
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<Vay<1>>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwapK4AMngMmAByPgBGmMQB/qQADqgKhE4MHt6%2BAUGp6Y4CYRHRLHEJ/kl2mA6ZQgRMxATZPn6Btpj2RQwNTQQlUbHxibaNza25HQrjA%2BFD5SNVAJS2qF7EyOwcAPQAVAd7ANTKxJjoAPoaR4d7OyYaAIIEmCzJBi8m/m5MXkQAdICvtgHo8ZsQvA4TmdLhpQSYAOxWJ5HVFHGZMRzII5oBgzTCqZLEI4xVCeI4ANzEXkwR0RFioYiUiIAIl9kY9Wez4U99odoecLlwbod7k8Xm8Ppgvj8/qhAf9gaDwZCCALLlx4UjQWj0Y0sTiBPjCcTSeSqd5afTGbRmQi2f4OVzHTzHnyDkcAGpMACeIoOYuer3emOl31%2BRCOAEklU8VVDvT6tRzdRiDbjjUSjhHUJTqVakTH7dyns6nbzbkcqF4GP67qCJSHPt8CD7koxWJgFY9iMAFLGe5gAI5ePBnBRHCAKxFuGcQBioNWnQVw749vsgEAWmnAzfbzDLZagjMvE0ksm0Ks1iBHpFnAgbWs25ku4ul8XBqUy1vt5hsbu9v2/ggk8ZwjmOmATlOQIIrOsHzou6pXDK64KHu%2Ba7lu%2BaHnSZgAGzmHhk7TrBc4LkuMJCihgHoZamH7oex5GqeWZmpe1YMDe9L3o%2BRwEBCYZWG%2BnIVvyAAqkFqrcgY7DsRzYMQxAkMq%2Bp4MgFxMAoSjNNQNYyomMqasBwI3kejocKstCcAArLwfgcFopCoJws6WNY6LrJsVpmP4PCkAQmgWasADWIDWXh/wABx4VI1kInhkgAJz%2BPFPn6Jwki8CwEgaEE9mOc5HC8GhQQBQ5FmkHAsAwIgIDrAQyR/OQlBoG8dDxJEnacKo0UALQJUcwDINiUj/GYvDnIQJB4Ogej8IIIhiOwUgyIIigqOo5WkLoXCkAA7sQTDJJwPCWTZdmBU5nAAPJ/I1aqoFQRw9Xh/WSINw1HKNZiTh4bX0MS5i%2BcsvBlVoqwQEgrXJO1ZAUBA0OwyAwBSGYfB0C8xBoRAMSXTE4RND6J28PjzDED610xNotRlX5rVsII10MLQRNbVgMReMAPy0LaxOkFgLCGMA4hsxBdQUpBl0ErUfzbH54QvFZW20HgMSHeTHhYJd/F4Nl3C8BLxCkkoLKvELKtGIFqxUAYfaengmB7ddv58/NwiiOIK1u%2BtaiXTt%2BhCyg1jWPoqtoZAqyoMkPRoRwvUzOgXwsqYbmWGYBWG8QM2SxHnTdJkLgMO4nhtHooTzGUFR6AUGQCJMfi7TXPSDJXIy7TUdQCH0Ewl7k7ddDT9SzC3wwJO3sz13oGLNCPixj6sCieVsEhnRwtmkPlvCFc9fUDUNI2SGNk64FNgM%2BVwIP%2BVbqwIJgTBYAkN6kKFkj%2BP8yUIpIGiSGYkh4bl4VErpQ4JlUg2V/BmH%2BP4PCCJIr%2BEitZayXAUqJUihvS6hViogFKlbSqNVIZ1Tuk1eGiMAadTYN1Xe71kAGCMF9RK/wuD/EcpNIgWdZq7TdotT20hvZKF9ltXQaMDpHWJqvdem8rocFug1P4RxHo71egNGhQt6GMOYb9VA/14i4QgZfMGFUCGkPiM1BGWiYYAxQLQlGiUuBBBoLQTG2NcZbVJoTPmbjyaU2pg4Pm9NGAECZizS67NObc15vrfmZsjAi0cvgM44tJZbWlsgWWfMFZdEuirNWhNNbbEcjrPWflDbG0wKbQWMTwigHKtbW2Ch7aO2dowV2shuHLV4bIH2m1HJCIDpbFOVhLChxiOHJ%2BUcY6cHjgQRO/hk7BzThneI7Cc5Pw7j0QuxccgN2CEXWeVdG5pFrlkXu2ym6ZD2W3POg8u4TxOVPAendejDwrqPKetytlvP6Bc%2BeawNjLwvsAiRGDOCKLejiaxaimHXAgCfNhuiL6g2vqQW%2B98RhP1CnYoIStQHgOsv8JK1lEpmCJfhSKyCEroK2pg2w2Cr41LwfAAh9V7qmOMcQch2wmgsAGiwBQFJsQUi4AwqUMwJr4DYTNOarSPbtNWvIfh3SdABH2odY6%2BtxEXSpTdIhD0nqqB5XygVQr/girVBAP6FidFA38Po3BRjzGw1ZQ6yx/LkjJAuIKxKFxTUXH1bwjG8RnF4wJuTDxIaKZUxpn4rRDNAnM1ZnEzAHMuZiAiX5AW5t8m8HiYPCWscWGqBli8dJghMnK1VurH0eTtZZyKQbeIpTynmyqbgm2TA7YOydi7SJXCZUSA6WtBVftlXWKDqnGw2TRmR2jpkWOOwE5jsGRYdOW9M7ZynVcx5GzJ67XLqUV5BzCiZB3SkQ5zcXlz3ufnG5/QT1rKHl8i9%2Byxi3ruePR9%2B7L0AsXn85aGrKUFRBX6o4vL%2BWUmNaa4%2B4qSDwttTUm%2Bd8H6UFXjigIkDyU%2BTMFhrgkUNB4UJQBrenAsE4Pg8/EAr9GHwOsj/fw1k8M%2BXisA/wmrANFTpeDVe41CNSMRWRw26RnCSCAA)

By turning `(...||Pred_0<***>::value)` and `(...||Pred_1<***>::value)` into concepts, we allow compilers to perform proper subsumption.

```C++
/**** fun ****/
template<typename...Args>
requires AnyDeceive<Pred_0, Args...>
constexpr bool fun(){return false;}

template<typename...Args>
requires AnyDeceive<Pred_0, Args...> && AnyDeceive<Pred_1, Args...>
constexpr bool fun(){return true;}

/**** Test ****/
static_assert(fun<Vay<1>>());
```

## Implementation

```C++
template<template<auto...> class Predicate, typename...Elements>
concept AnyDeceive = (...||(not Predicate<Elements::value>::value));
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwapK4AMngMmAByPgBGmMQgkv6kAA6oCoRODB7evgFBaRmOAmER0SxxCUm2mPbFDEIETMQEOT5%2BgTV1WY3NBKVRsfGJyQpNLW15nWN9A%2BWVIwCUtqhexMjsHAD0AFR7%2BweHR/tbJhoAgrv7ANQAkiwp9GyCTPXXB6cXV8c/x5/nZ3OBEwDwMwJM/jcwNBr0wELcTC8RAAdKiIdhrsgDAoFNdlMRMPhRMDSNcCABPFKMViYVHI7BPRgEBTowFoBgbFIEa7nBjkgAimA2eAAbphrhD%2BdcIHSTAB2NzytwQBiobn4wl4YlwyEMkFMhQgEAisReHXYI0m7yYRaLCFWC6A76/E5Og7XAAqmDGuI%2BbpdfsdX3dGvQAH0NO9XRdoY9YfDESi0f5sICxsQvA48QTwxpAfKHedrsXrjNHMhMQIxphVCliNcYqhPNcrWaJXKLFQxEp5fz7fm5X3/IX/Xts4Sw1wo3t/rGwTqEUjULKU2mCBms6HJwPCyXS01y5WGNXa/XG83W%2BKC13aD3B/3Hffh/ngzcAGpMcnTnazkFx8GQomqB3KyFzppm3IfuSO6AnuZZakeJ51tcQEtqaV4drcvYPgCT4jq%2BY5UF4DDfr%2BMIAVClLUmwdLnMQwAsquFwEgAjl4eAErivICkKmCiguW5BDy9EKCuqYXOySFnk2tDXERDAQHaHYEgQawkTePbPveQZAn%2B87whSVLMDRqJ0QxoF0ZgbEcd6PJ8oKwpivCgmkmZonJhi5gAGzeXZPGOQJOaTq5IliWyVbAqeDYyXJxGKQWKlqWSGY6lY2kAgROyet63KBuc8HIGGTA4vEBDUMR8JQfCXCsimil2sOHDLLQnAAKy8H4HBaKQqCcIqljWKWqzrFeZj%2BDwpAEJoTXLAA1iArVeciAAcXlSK1cpeZIACc/ibWN%2BicJIvAsBIGhBJ13W9RwvCGkEU1dU1pBwLAMCICAqwECkSLkJQaAPHQ8SRDSnCqKtAC0W3XMAyAVlIyJmLwmpEMQeDoHo/CCCIYjsFIMiCIoKjqI9pC6FwpAAO7EEwKScDwzVtR1009ZwADySLfdyqBUNcYNeZDkjQ7D1zw2Y0oeAD9D1uY42LLwD1aMsEBIP9KSA2QFAQKr6sgMAUhmHwdDAsQhoQDEzMxOEzTknTvCW8wxDkqzMTaEKD0Tf9zwEKzDC0DbJNYDEXjAAitC3rbpBYCwhjAOIAc2Q4/GGiTNZCkimwTeEwItSTtB4DE1OOx4WDM%2BueCndwvBisQjZKIK0dGHnRjTcsVAGAxb54JgFOs0ZEeY8IojiHjA%2BE2ozNk/oMcoNY1j6PnhqQMsqBclkyfg2M6CSqYA2WGYV3V6jWCL4pXRu1kLgMO4njtHooThIMFTDOThSZAIkx%2BC/6RvwwcxDAk5M7DnwEL0CYN88iANqMAho4x%2BgP3mM/WwsCP56BmC0P%2BT8AHLAUMNDYEgGYcHaqQS6vBrq8whlDGGcNJAI2lLgQgJAJRjS4HLSaLdlgIEwEwLACRT7zSSMiXacpJAaEkGYSQXlzqLW2odDgx1SCnX8GYZE/gvJymWv4ZarVWpcD2ttZaxDmbXVuiAe6LdnpvWVh9DmP1NbaylsDNgoMKGCyxDHEW21kRcGRN1ZGJA0YY1kNjYe0hR5KHHiTXQBsqY01tgQohJCWYcHZl9JE1xubkP5lDNxRgPFeJ8eLVAkt4hMKUawhWT0rH2PiL9LWRS1ZSxQAYIwXBtpcCCDQWgxtTbmxJvba2Ed%2BmO2dq7BwEdPZMh9n7Zmgdg6h3DpXSOIIY5x26vgAkicxTJ18aoNOwII5Z1qMzPOBdrbF02N1MuFcJrV1rpgeuKzwigEeq3duChO7d17owfuQSh641CbIMexNupRKns3HeVhLDzxiCfZeq8qycA3gQLe/h%2BQQusPvUhh80bengNgqBidnAQFcCg8m98yj/z0K/eopLUjf3qBghYkDuggOQeAz%2BZ9CUwNmPAylgC2W5A5WguBFLMH4JWGsPBLDZEJKMZwTJAtMTNOAHk7xkYID0JRqUlh8t2GkE4dw4YfCzpBBzvIxRrVkQ7VattMwtqzBeWWrorahiSbGNsKYthLyLHwCsZ9TmtTqnEEcZsZoLAoYsAUCKCsIpWnInnGMJG%2BAUYBPJgPYJ/z8byHCcCnQARKbU1ppXeJTM3VsxsVzHmqgI1RpjXGhN3IIASwaSUmW/hynmKqfU9Wgbu2NOjSkFIYZY3bTDA2sM1bQlG3iD0i2VtHaDPnU7F2btxlFK9lM/2azMBBxDmIBZE0o4rIubwdZ58tnM1TsgdOBzBBHNzvnQu5Jzml1Rtcqu8Q7kPMbk88xbcmAdy7j3Puiz01/IkACgmOaJ75uVTPXeNgTmwp6vC48nAtib3g5CiwmKerYuPnizl9RL7X0FXfK%2BjLEHUqyLS6jJReViuZdA0BrR2WoIJfUFjlGAFIL6LS4V3HxU4MlbjEtrqrrysndcSN0aWz1thGMOhybGEyx1V6xWHCuE8MoAQ81ARlHOrGmYYzXBloaC8ja8TpDOAmLMS8uaIwvGaNamI/wrVzNjU2rI/wpaJM3XUzNWRiMrNJN1fZ0g1cMjOEkEAA%3D%3D)

## Links

- [Source code](../../../../conceptrodon/pagelivore/concepts/any_deceive.hpp)
- [Unit test](../../../../tests/unit/concepts/pagelivore/any_deceive.test.hpp)
- [Example](../../../code/facilities/concepts/pagelivore/any_deceive/implementation.hpp)
