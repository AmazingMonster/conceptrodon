<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Confess`

<p style='text-align: right;'><a href="../../concepts.md#typelivore-confess">To Index</a></p>

## Description

`Typelivore::Confess` accepts a callable type predicate and a list of elements.
It returns true if the predicate invoked by the value results collected from the elements returns true and returns false if otherwise.

<pre><code>   Pred, Es...
-> Pred{}(Es::value...)</code></pre>

## Structure

```C++
template<typename, typename...>
concept Confess = REQUIREMENT;
```

## Examples

`Confess` turns a callable type predicate into a concept so that it can be used for subsumption.

Since `(Pred_0{}(***))` and `(Pred_0{}(***)) && (Pred_1{}(***))` are both atomic.
Both candidates are considered equally good.
Thus, the call is ambiguous.

```C++
/**** Pred_0 ****/
using Pred_0 = decltype([](auto...){return true;});

/**** Pred_1 ****/
using Pred_1 = decltype([](auto...){return true;});

/**** Vay ****/
template<auto I>
struct Vay
{
    static constexpr auto value {I};
};

/**** fun ****/
template<typename...Args>
requires (Pred_0{}(Args::value...))
constexpr bool fun(){return false;}

template<typename...Args>
requires (Pred_0{}(Args::value...)) && (Pred_1{}(Args::value...))
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<Vay<1>>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwapK4AMngMmAByPgBGmMQgZgCspAAOqAqETgwe3r4BQemZjgJhEdEscQnJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlUbHxiSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwA9ABU%2B7sA1MrEmOgA%2BhqHB7vbJhoAgl6ZRsenF1cm/gAih1jItAIAE9UpgICYklYkt8IEwvEQAHRIpYmADsFlOBHWDEOBGIXkwXysqO%2BKP8Vke9weewObzO5y41wOd0ez3CwDpF0ZX1%2B/0BILBEKhMLhiORaIxmCxxBxeIJRLRpIVlMeNP2hwAakwgUz9iyHgRMCxUgZDV83KLUIcAJJfbBU8b4hya7VUiVUw6ew6zRzIQ5oBjjTCqVLEQ6Ww4ANzEBMOEttJOVD0VSapaqOVC8OJu%2BsNxtNhP8bmBoOYbCRCIexGACjtVNOAEcvHhTgpDhATvSNO6SRAqzWQCBo95MBWlijHgGgyGwzFUJ5DpmGBAUejMdjF2IlArEyqDUaTUwzUWS4xWKOkf3a/57Y9G83W%2B3Ox8ezCr4PhwSx0s42YAGzmH%2BT7vAyr59tWCgfjGF4IuOVJToaM6HHOC5LiuErrjKuL4oWxLfG6qo3IcAAqmDjLqtxptshzYMQxAkA6zS%2BucTAKEorTUFm5pakC5pcHWN4rmSFgcCstCcEkvB%2BBwWikKgnBuNY1jemsGyYL%2B/g8KQBCaKJKwANYgEkf4IgAHH%2BUhJKif6SAAnP41lmP4%2BicJIvAsBIGhBNJsnyRwvCQUEOkyaJpBwLAMCICAawEKk8LkJQaDGnQ8SROenCqOZAC0NmHMAyB%2BlICJmLwZyECQeDoHo/CCCIYjsFIMiCIoKjqCFpC6FwpAAO7EEwqScDwYkSVJulyZwADy8JxQQhyoFQhyZX%2BOWSHlBWHEVZjth4yX0GG5iaUsvDBVoKwQEgSWpClZAUBAl3XSAwBSGYfB0IaxCQRAMRjTE4QtECg28L9zDEECE0xNomAOIDpBJWwggTQwtAA%2B1WAxF4wAWrQtCQdwvBYCwhjAOIqMtlDjiRmRY3BlD8JbFp4SGuJ7W0HgMR9aDHhYGNeJ4B5eOkJTxBzko3xGkTrNGLpKxUAYNYangmDdRNpYwzVwiiOIjXqy1ahjZ1%2BhEygSmWPobOQZAKyoKkDS41l4zoDypiWNYZi%2BULxCVVTlvdOT2QuAw7ieB0eihOEQyVCMXVFFkAhTH40cZLHDDzMMCRdXYfsCH0kzB/kGd1FnjQTAM4cLFHtgl/HeizK0qeR%2BnKwKKpmwSMNHCSaQPm8H5i3Zbl%2BWFZIxXtrg5X7U5XBHdp0srAgmBMFgCQrqQhmSP4CL2aikgaJIZiSH%2BXnGbZLkcG5pAef4ZgIv4f6oqZ/imUkSRcA5tmmV3Y1%2BQFIBBdLYWRXOtFaa8Vbr3T2mlNgGV%2B6rQBETDatkERcARLJMqRBPZVS6urOqWtpA6yUHrdqugXq9X6oDdundu7jQ4FNWK8I5oLSWitf0BhXhcEQcgq4EAdpXT2hpMw08TqhSAeA%2BICU7qoF2iMOBRh2FcCCDQQE8RPrfXasDf6MN1Gg3BpDaGAs4aMAIIjZGY00YYyxjjGGBMJZbFkvgU4Dg8CU1xqg1QtNDQw0ZnUMarN2b/S5rY46nt%2BZaSFiLTAYtCZGElqAEKMs5YKAVkrFWjA1ayBwQ1PBshdZtVksQw2UtnZWFNr4i2K9ra204PbAgjsfhFNdu7eIGDvYr0zo45wEBXDVy6mHcoac9AxwaN0tIScGj10WAXHo2cq55wTr7dpxc5hl36RnGZeQ5m11Ln0hubdVjrFblPU%2BlCv6cD7stXKMiOTsKQSg0e%2BB0EaSnsdWepB56LxGCvQy8igjM3PpfJICI7JJFsmYEF/5TKvxsp/dq39bC/xnnEgB8AgExRmuI0RxBIFbBaCwXKLAFCRj9JGa5BZxilXuRVTBTUNb1QkFk5qBDck6ACD1PqA08YUNGjCyaIDZrzUWniglRKSVHjIrNbhkjeHxA0v4QR/8RGSuuuixVe0hzIFSKkc4xLbLnFJQQc4qgoWKPeion6f1QaaPNWDCG5MYYGIRkjFGdjMDo0xmISxAtrHRMCaQexftnHUzccgOmnjBDeJZmzDmQIAk82CTDMJGQIni2ieyf%2BssmDy0VsrVWAtsGa0ydSnJ%2BsWWsOMCbGwpT4BWxttkXG2wHbGxdpYN2PcPZezKU3QuCyA5B3WaHQO4yK6DOyMM4dpRlk7MmUXHObRZk1y7Q0Gdg706V36MMzZy7dnN32Q1Tl0LfKnMNatfFhKowisNORCAY8HkHSeQi06c8F5L0oO3P5ARr6QqcmYb9XBTIaD/MC/dPdOA/z/nEgyIB15IMfkkPe/gkj/qctZU%2B/guUHv8vevSp8SpAeoc88DgtlH%2B0kEAA)

By turning `(Pred_0{}(***))` and `(Pred_1{}(***))` into concepts, we allow compilers to perform proper subsumption.

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
template<typename Predicate, typename...Elements>
concept Confess = Predicate{}(Elements::value...);
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwapK4AMngMmAByPgBGmMQBAKykAA6oCoRODB7evgFBaRmOAmER0SxxCf7JdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHAD0AFSHR8cnp0e7JhoAggdHANQAkiwp9GyCTL13xxfXt2f/Zx%2BV0uVwImGeBjBJn8bgIAE8UoxWJg7spiJh8KIwaQ7vDEcw2AA6YnYV6MAgKaHYEFoBjbFIEO4eBhUTAKBR3aEAEVR6MxH0wJgA7FYhVyIKTweSFCAQAA3MReTDEwkraFWa4gv4A85a453AAqbIpX11vx1JyBevuaIxAH0NKbDkCvBkjLz7Y7uXcsMhaHjMBATIkrIlxUwvEQVWqReiCJsGLjiEr1cKuWr/BrgeabXy7VwnfsXW7gB70PnOf4eb7/QjA8HQ%2BHI6ho8KLHGE0mU5m0xms9bDncAGpMOGFoFgiEC6FuCNER5UkGzZMOYejkFtkF3bd3WYfPDIO602aYVQpYh3OeoO4K7wotsPNOpzVi5/Zm76qheRPfEGTl7TjCAYEsqxJXMQwCUv41LXOiACOXh4OiHLMqy7Izra5ZBHc4GQSqi7XMeYJnheMSoJ4dxfgwEAxu2mDxsQiZUGISipq%2BmrXP%2BkKCkBdYgSquFQTB4GYAhSFskyAhoVBbiYQ6OKCfh0GcmYABs5iqZJLJsjJclcApEEKEpwlEae553GRFFUTRbYdoxXY8aKXIbjmg5GrM45Lk0jjIHaTDsvEBDUN%2BM4jnCM5cIu0E0X2HBrLQnCJLwfgcFopCoJwbjWNYu4bFs95mP4PCkAQmhxWsADWICJKphIAByqVIiRCqpkgAJz%2BC1hX6Jwki8CwEgaEEKVpRlHC8DKQSlalcWkHAsAwIgIAbAQKSRuQlBoM8dDxJEyKcKoDUALStXcwDIIeUiEmYvAYoQJB4Ogej8IIIhiOwUgyIIigqOoM2kLo%2BkAO7EEwKScDw8WJclZXpZwADykZrYyqBUHch2qSdkhnRddxXWYdwQB4230Be5hFSsvDTVoawQEgW0pDtZAUBADNMyAwBSGYfB0GCxAyhAMSwzE4TNHCEO8CLzDEHC8MxNodTTcVW1vAQ8MMLQ4v/VgMReMAs60LQMrcLwWAsIYwDiNr4n1HKbKw6edSRjsxXhGCCX/bQeAxKDMseFgsMEMQeADSbpB28QZFKFy4IW17RhlWsVAGJBQ54JgQPw/iEtfcIojiJ9L3yEoaiw4D%2BgWyg2WWPo3sypAayoAyWTG0dszoNypiWNYZijRHwdYPXNFdD0WQuAw7ieO0eihAs5SVHohSZAIUx%2BPpS%2B9EM8%2BjPptT1AI/STFPeS790isNHMW8jAku9zKveh7i0V9LDfawKHl2wSFDHBJaQI28GNdGx1TrnUupIa6hNcD3TJoVLglMSqJzWAgTATAsAJGHlVSQ/hCQdSFJIDQkgzCSFUkNGqbUeocD6qQAa/gzCEn8KpIUdV/B1USIkLgnU2p1T/rDMaE0QBTUTnNRadNlpI3WizNmpM9psAOsA7GfoLZ4zaoSLghI0p3SIAPZ6sg3oF2kEXH6pd/q6G5iDMGEtv6/3/nDDgiNVqRjuKjIBmNTqKPdFwFRajHRE1QCTeIKlaHwOprNURUj4gbVZn4xmpMUAGCMJ4rgQQaD%2BniALIW/0pZixzlkmWcsFYOBzirck6tNawx1nrA2Rsc5mzjjsNK%2BB0S23tv9R2yBnY5zdt0WGXsfZi39vUqmwdQ7FQjlHTAMdzZGHjqAGaScU4KDThnLOjAc5Fz0R9AxsgjF/TSqYiuCcu5WBrr0oejdm4CFbu3Tu1cLC9wAf3R69sG4j3Ps4CArh776VnmUa%2Bi90jL2yMfNeqQAWbznn80%2Bo8D532BQ/M%2B%2B8%2BiXwhS/B%2BsLcggsfvMX5qK4HrE2J/PFHtrG8M4C4rGR54mlk8ao9RkD8BaMCXAqmiDSDINQaMDBg0ggeyoTQxIhJ2qJDamYEVak6ocNajw/6fDbACIQXM4R8BRErWRpE8JxAZE7GaCwU6LAFBykPHKGl3FZi3QZQ9J6%2Bl1n502bnHZZcAikHMeDE2ViYYyoRuIlGaNVB6oNUak1AoPK%2BP8TA/w/hglCLCdEpm6rY2xMNSkFIdpjVtTtKaggdo/UGN5mkygGS0q5K1sVYt%2BTFZFL8arUpWsGmYF1vrMQ1Sw61OmYM0gjTz522Nho1QTswSdMEN0z23tfZwgGYHYZOcxnpAmbHaZ4RZk0z4AspZmds5hxte9CQWzvol12ToJ1VKq7dxOXXeA5zejG12O3E9xy7l93iAPZ5w8969HHpPDFM8J7PwXuvMFWQvmgqKFkX9O9XmIsPq0OFUK3lIoGGBm%2B4wBhAaxYhr%2B%2BL8oYeJR60aZKc13H1Yam8QawQhqgYy8mzKFU0yQSgtBlBv58oCHQyVhUzAca4HVDQqlhXSrw%2BNOVgi5mVRAFg1RLDEiEOqDxwqLUKH%2BFwwAzgLKRMUJuvx5TgmQkrDWBHDIzhJBAA%3D%3D%3D)

## Links

- [Source code](../../../../conceptrodon/typelivore/concepts/confess.hpp)
- [Unit test](../../../../tests/unit/concepts/typelivore/confess.test.hpp)
- [Example](../../../code/facilities/concepts/typelivore/confess/implementation.hpp)
