<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::AnyConfess`

<p style='text-align: right;'><a href="../../concepts.md#typelivore-any-confess">To Index</a></p>

## Description

`Typelivore::AnyConfess` accepts a callable type predicate and a list of elements.
It returns true if there exists an element whose value result satisfies the predicate and returns false if otherwise.

<pre><code>   Pred, Es...
-> (...||Pred{}(Es::value))</code></pre>

## Structure

```C++
template<typename, typename...>
concept AnyConfess = REQUIREMENT;
```

## Examples

`AnyConfess` turns a fold expression of a callable type predicate over `||` into a concept so that it can be used for subsumption.

Since `(...||Pred_0{}(***))` and `(...||Pred_0{}(***)) && (...||Pred_1{}(***))` are both atomic.
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
requires (...||Pred_0{}(Args::value))
constexpr bool fun(){return false;}

template<typename...Args>
requires(...||Pred_0{}(Args::value)) && (...||Pred_1{}(Args::value))
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<Vay<1>>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwapK4AMngMmAByPgBGmMQgZgCspAAOqAqETgwe3r4BQemZjgJhEdEscQnJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlUbHxiSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwA9ABU%2B7sA1MrEmOgA%2BhqHB7vbJhoAgl6ZRsenF1cm/gAih1jItAIAE9UpgICYklYkt8IEwvEQAHRIpYmADsFlOBHWDEOBGIXkwXysqO%2BKP8Vke9weewObzO5y41wOd0ez3CwDpF0ZX1%2B/0BILBEKhMLhiORaIxmCxxBxeIJRLRpIVlMeNP2hwAakwgUz9iyHgRMCxUgZDV83KLUIcAJJfbBU8b4hya7VUiVUw6ew6zRzIQ5oBjjTCqVLEQ6Ww4ANzEBMOEttJOVD0VSapaqOVC8OJu%2BsNxtNhP8bmBoOYbCRCIexGACjtVNOAEcvHhTgpDhAK2i3F2TvSNO6SRAqzWQCBo95MEsUY8A0GQ2GYqhPIdMwwICj0ZjsSuxEoFYmVQajSamGaiyXGKxMBXh7X/PbHo3m62O0iuz33pcBzDb6PxwSpzjMwADZzGA9tO1RbsoN7LlvyHasFD/GNJ2nB5Z0NedDkXZdV3XCUtxlXF8ULYlvjdVUbkOAAVTBxl1W4022Q5sGIYgSAdZpfXOJgFCUVpqCzc0tSBc0uDre91zJCwOBWWhOCSXg/A4LRSFQThu0saxvTWDZMCA/weFIAhNFklYAGsQCSYCEQADmAqQklRYDJAATn8ZyzH8fROEkXgWAkDQgmU1T1I4XgkKCEyVNk0g4FgGBEBANYCFSeFyEoNBjToeJIivThVHsgBaFzDmAZA/SkBEzF4M5CBIPB0D0fhBBEMR2CkGRBEUFR1Bi0hdC4UgAHdiCYVJOB4OSFKU0y1M4AB5eE0oIQ5UCoQ5CuAkrJDKirDiqsx2w8bL6DDcxDKWXhoq0FYICQLLUhysgKAgR7npAYApDMPg6ENYgkIgGI5picIWiBSbeFB5hiCBBaYm0TAHEh0gsrYQQFoYWgIf6rAYi8YALVoWgkO4XgsBYQxgHEXGWyRxxIzoubgyR%2BEtiM8JDXk/raDwGIxthjwsDmvE8ACsnSEZ4hFyUb4jSp3mjFMlYqAMGsNTwTBhoW0sUZa4RRHETr9Z6tQ5sG/QqZQaxrH0PmkMgFZUFSBpSaK8Z0B5UwtMsMxQql4hGqZx3unp7IXAYdxPA6PRQnCIZKhGIaiiyAQpj8ZOMlThh5mGBIhrsMOBD6SZo/yAu6iLxoJgGeOFiT2wa/TvRZlaXPE/zlYFF0zYJGmjhFNIELeDCzbitK8rKskar21werzq8rgruM5WVgQTAmCwBJ11ISzJH8BF3NRSQNEkMxJGAoLrNcnyOD80gAv8MwEX8YDUVs/xbKSJIuA81zbKHnNMKEUQBRWVnFRK91krLXSq9d6Z08psAKuPXaAIqYHVcgiLgCJVJ1SIIHJqQ19ZtSNtIE2Sgzb9V0D9Ua41Ib90HsPeaHAlqpXhGtDaW0dr%2BgMK8LgmDsFXAgCdJ6Z0DJmGXjdWKUD4HxAym9VAp0RhoKMPwrgQQaCAniIDYG/VobgxRvo2G8NEbIwlmjRgBBMbYzmnjAmRMSYowpgrLYql8CnAcHgRmpNcGqFZoaFGnM6hzV5vzcGQtXHXUDuLIyUsZaYDlpTIwitQAxRVmrBQGstY60YHrWQJCOpkNkKbPqqlqGWyVt7Kwlg7YxAdjvZ2rtODuwIJ7H4VTrB%2BxHgHIO9Su6V08c4CArhm5DTjuUPOegU4NFGWkLODR26LArj0YuTcy4Z1DoM6ucw66TILmsvIGzW61wmR3Puqx1i9yXrfRhQDOBj22qVFRHJ%2BFYJwbPfA%2BCDJL2uqvUg69N4jB3pZdRQRub30fkkBEbkkiuTMHCkCtlf4uUAf1YBthQErzSRA%2BAUCUorXkbI4giCtgtBYKVFgChIx%2BkjK8gs4xaqfIaoQrqBt2oSCKd1ChpSdABBGmNCaZMGGzTRYtGBq11qbQpVSmldLTx0VWsIxRoj4gGX8JI8BMjlXPUJdqs6Y5kCpFSOcWlrlzj0oIOcVQKLNH/R0SDMGsNDGOrhgjemKMLEYyxjjNxmB8aEzEI4iWzjkmRNIO4sO3jmZ%2BOQGzQJghgk8z5gLIEESRbRJRnEjICT5bJPZOA1WTB1aa21rrCWxDDaFNZSU82fLeHGBtjU0JfS1Iu2yKTbYHtrY%2BwsF0tSPSsAtsLlsiOUdDmx0joshu0zsizJnaUXZZzllVxLm0dZLcBkNFXVO/Ojd%2BizOOTu853dLkdWFai0K9zrW7UpdSqMcrDT0QgHPL5F0flYtumvDeW9KD9whQEZ%2ByKvJmBA1wWyGhgKwovSPTgICwFpIsiAfeWDP5JDPv4JIEGvLOVvv4EVl7wofrMrfGq0HmG/IQ5LbR4dJBAA)

By turning `(...||Pred_0{}(***))` and `(...||Pred_1{}(***))` into concepts, we allow compilers to perform proper subsumption.

```C++
/**** fun ****/
template<typename...Args>
requires AnyConfess<Pred_0, Args...>
constexpr bool fun(){return false;}

template<typename...Args>
requires AnyConfess<Pred_0, Args...> && AnyConfess<Pred_1, Args...>
constexpr bool fun(){return true;}

/**** Test ****/
static_assert(fun<Vay<1>>());
```

## Implementation

```C++
template<typename Predicate, typename...Elements>
concept AnyConfess = (...||Predicate{}(Elements::value));
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwapK4AMngMmAByPgBGmMQBAKykAA6oCoRODB7evgFBaRmOAmER0SxxCf7JdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHAD0AFSHR8cnp0e7JhoAggdHANQAkiwp9GyCTL13xxfXt2f/Zx%2BV0uVwImGeBjBJn8bgIAE8UoxWJg7spiJh8KIwaQ7vDEcw2AA6YnYV6MAgKaHYEFoBjbFIEO5XBhwjwMKiYBQKO7QgAidwgxMJJgA7G5RW40Ri8FjMKKrCLeRBSeDyQoQCAAG5iLyYFYraFWa4gv4A84m453AAqnIpX3NvzNJyBFvuUvQAH0NPbDkCvBkjKj0Z7vXy7lhkLQ8ZgICZElZEkqmF4iEKDSKLOiCJsGLjiLrDaLeQb/EbgY63cGPVwffs/QHgEGMdWef5%2BRGowiY3GE0mU6g0/Kszm8wXS0WS2XXYc7gA1Jhw2tAsEQj5ymHJoiPKkg2b5hxzhcg%2BUgu5nu6zD4yu602aYVQpYh3TeoO7a7wo%2BUPIuF42K3/ljclpUF4ubfCCK4vGu0Kwl2BKYEKVzEMAlL%2BNS1zogAjl4eDotyzKsgIHJcjB7pejiSEoUKO7XLeYIPk%2BMSoJ4dwgQwEDppmmDZsQuZUGISiFv%2BxrXJBkLrrB%2BLIohyGoehSGYNhuGckyLJssRqGSlWQRMrJ1FoTyZgAGzmEZqmEeynKaWRXAUXpxI0VcdH3o%2BdxMSxbEcUO3EjgQ%2BbrgqvLHhWM42rMS67k0jjIB6TBcvEBDUKBMHznCMFcDuaEcZOHBrLQnCJLwfgcFopCoJw4qWNYF4bFsn5mP4PCkAQmi5WsADWICJEZhIABxGVIiQikZkgAJz%2BMNDX6Jwki8CwEgaEExWleVHC8OqQQtSVuWkHAsAwIgIAbAQKQpuQlBoM8dDxJEyKcKo/UALQjXcwDIMgdxSISZi8NKRDEHg6B6PwggiGI7BSDIgiKCo6jbaQui2QA7sQTApJwPB5QVRWtWVnAAPIpqdjKoFQdwPUZz2SK972fZI30Ch4V30E%2B5iNSsvBbVoawQEgl0pNdZAUBA/OCyAwBSGYfB0GCxDqhAMS4zE4TNHCGO8MrzDEHC%2BMxNodRbU1l1vAQ%2BMMLQavw1gMReMAbhiLQ6rcLwWAsIYwDiFbyn1JqnK4/edQpjsTXhGC%2BXw7QeAxKj2seFguN%2BXg83O6QvvEExSi8uC7uR0YrVrFQBgobOeCYEj%2BP4urUPCKI4iQyD8hKGouOI/o7soNY1j6FH6qQGsqAMlkTuPbM6B8qYVWWGYK1pwDWC9xxXQ9FkLgMO4njtHooQLOUlR6IUmQCFMfi2QfvRDLvoy2bU9QCP0kwb3k1/dAbDRzBfIwJNfczH3ol4tB/JYX81gKFqtsCQWMOCFVIMtXgq1yZPRem9D6X0zAClwIQEghl2ac3zmsBAmAmBYASIvTqkh/CEnGiKSQGhJBmEkEZRa3VRrTQ4LNUg81/BmEJP4IyIper%2BF6okRIXAJqjV6jA3Gq11ogE2vnXaB1eZHSJmdYWosWa3TYPdRB1NIzu0%2BqNQkXBCSlT%2BiQQGwNZBgzrtIBuMNm7w10FLFGaN1aQOgbAvGHBCYnRTHcUmCDKYvT0YGLghjjHeggEzAWLNsFmA5s1eRSj1HxHOiLVAzNRghIlqNLgQQaBRniPLRW8NNaqyrmU7Wut9YOCrsbckZsLa42trbe2tBHZV1djnHYpV8Doh9n7eGAdkBByrqHbouNI7R1VnHHpnMAbJyamnDOmAs5uyMLnUA20C5FwUCXMuFdGBVwbtYiGtjZD2LhqVJxbc84TysJYbuMQF790HgIYeo9x6dynjPeIc8/Z9yXq/ZwEBXC/1stvMon997pEPtkR%2BJ9UiwvPjvaFz9l53x/giv%2BL9b59HfqioBf8sW5ERf/eYUKiVcBAWAiG7icbw3gRTKmN4DChPCSY9B%2BB/rYOpbg7Z%2BDCHEMoB1BaQRw7sM4YkQkY1EijTMPK4yvVREjUkYyzgMi5HbIUfAJRx1iZpJScQTROxmgsBeiwBQmoPqajCYScSsxfrcvMUDWyJza5nOrpcluARSAuPRs7elaqVoExUSTMmqgLVWptXah1jIokZJifEbB/gElcx2skxNgtDVZpZlqZAKQUgeltaND0caPSRtsTLIplASmlUqZbJqDbqkGzqRkk2jTLa9MwDbO2DsnZNS6RsuZpA%2Bmv19k7UxqhA5gjGYICZEco4x0IvHeGidFm8GWekVZ2cNnhC2dzPguz9nl0rind14MJDnOhk3K5OhfVsuMN8mwUyXllTeQwJ2uxR4d0nhYaecDZ6AwBYvG%2BvRV7r1JVvNegC96n2RVkcFSKihZFg1fIFeL76tGxei4F%2BKBhoa/uMAYSHyWEYgesTY4DqWsI8VIzg5Mo3WrfLGtc4VlTOtZg1PliSBWkAIUQ0Yi8JVzQCNwlVDUzBSa4L1DQRk5XBrgRq2wsjePc1FeQoxgjEh0OqHJhqw1WH%2BAZSGtaam2qsJ%2Boprx/L1OpyKSvSQQA%3D%3D)

## Links

- [Source code](../../../../conceptrodon/typelivore/concepts/any_confess.hpp)
- [Unit test](../../../../tests/unit/concepts/typelivore/any_confess.test.hpp)
- [Example](../../../code/facilities/concepts/typelivore/any_confess/implementation.hpp)
