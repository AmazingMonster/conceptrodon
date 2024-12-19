<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::AnyDeceive`

<p style='text-align: right;'><a href="../../../index.md#conceptualizations-1">To Index</a></p>

## Description

`Pagelivore::AnyDeceive` accepts a class template predicate and a list of elements.
It returns true if there exists an element whose value result fails the predicate and returns false if otherwise.

<pre><code>   Predicate, Elements...
-> (...||(not Predicate&lt;Elements::value&gt;::value))</code></pre>

## Structure

```C++
template<template<auto...> class, typename...>
concept AnyDeceive = REQUIREMENT;
```

## Examples

`AnyDeceive` turns a fold expression of a class template predicate over `||` into a concept so that it can be used for subsumption.

The following code will fail since `(...||(not Pred_0<*>::value))` and `(...||(not Pred_0<*>::value)) && (...||(not Pred_1<*>::value))` are both atomic:

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

template<auto I>
struct Vay
{
    static constexpr auto value {I};
};

template<typename...Args>
requires (...||(not Pred_0<Args::value>::value))
constexpr bool fun(){return false;}

template<typename...Args>
requires (...||(not Pred_0<Args::value>::value)) && (...||(not Pred_1<Args::value>::value))
constexpr bool fun(){return true;}

static_assert(fun<Vay<1>>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwArKSuADJ4DJgAcj4ARpjEIGYA7KQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCUmpCi1tHQXdEwNDldVjAJS2qF7EyOwcBJgsaQa7Jv5uTF5EAHRXx9gmGgCCE8ReDgDUysSY6AD6Gnf3JmSVger1BrzmjmQrzQDAmmFUaWIr1iqE8rwAbmIvJhXoCLFQxEpAQARY7AgHJUn%2Bcn/Xb7Q6YY6nc6oK4XG7/J4vAjvT4/Lj/PH/MHglqQ6ECOEIpEotGY7w4vEE2hEylkwVq6mCh50g5MI4nM5EV4ASQ5Dy5bwAsgJUEQGABPDXkkUQvBQmFSxGvI2oDFYxVAs2amkh7X3XUMpkEB1pRisTBs%2B7EYAKc3JzAARy8eE%2BCleEDZgLcxYgDDtvK%2BvyZydTIBA8uxN3rjcwy2W/09u2lyNRtFeVC8DAgHaBnwIGwYA8JjK1aoetL2eoNbhjceYbCTKbT/luD0%2B2dzmHzheuyRL57LFY%2BVb%2BJ1rChbAebDYD7dxZgAbOZPwWi%2BfS3LHkb35GttyfBUX1bdtO0lbtvVlftB2HUcLHHSdXgIZ5ZysecAQtMV3W%2BJgFCUNpqCHJkbSAgQnROAVdxuEcO2pDhVloThAl4PwOC0UhUE4EtLGscF1k2RUzH8HhSAITQ2NWABrEBAk/C4AA5PykQJkk/SQAE5/B0yT9E4SReBYCQNA0UgeL4gSOF4R9rNk3i2NIOBYBgRAQHWAg0nOchKDQfY6ASKIE04VQNIAWl015gGQKEpAuMxeC%2BQgSDwdA9H4QQRDEdgpBkQRFBUdRXNIXQuFIAB3YgmDSTgeHYzjuLk/jOAAeXOfyeVQKhXiiz9YskeLEteZKzALDwQvoJFzCk5ZeBcrRVggJBgrSUKyAoCBNu2kBgCkMw%2BDoXZiEfCBYna2IIlaB0mt4W7mGIB1OtibRMAcR7SGCthBE6hhaAeiqsFiLxgFOWgVR%2BrAWEMYBxFBo8HDwdFj3a%2BEvvObZpIiXYOIq2g8FierXo8LB2qwvALO4Xh0eIFElGJPYEeJow5NWKgDFTAA1PBMBqzr1x%2B3LhFEcQirF0q1Haqr9ARlBrGsfQScfSBVlQNJGkfDhoomdBjmJUxhMsMw7IZ4gsoxjWei%2BxoXAYdxPE6PQwgiYYqlGarimyARpj8H3Mj9hgFhGRJqrse2%2BkmdoXYKSP6mjgR%2BjaMOvYj2xY4DvQ5jTj3Fm91YFDErYJBajguJs9r7MGmK4oSpLJBSgtcAy%2BbJK4JaZM51YEEwJgsESEdSCUyR/AuAzkkkDRJDMSRPyslS9JMjgzNICypIuTTPzUvS1K4T9AkkLhAgMz9q4q%2BzHJAZzOfcrz1p8nqAt2/a5vCthOFaFh0WSaKmDQgMEYCaekLhcAuHxdKRArbZWqmLfKktpDSyULLCqugTp1Qao9CuVdbK8Hst1Py5xXj9R9MQX%2B/9AHIGAcAUB4DIHTVQLNBIH5/BmG7itNyT934JECntZhW05ogB/n/aKNCEZcD0lwayNBaDnUutdCqz17o/RUa9d6n1vp01%2Bsw/6BBAbA3amDCGUMYY6LhmzbYfF8CfFRujXWUDVDY12D9fG9R2rE1JvdCm1jlpW1ptJBmTNMAs3hkYdmoBXJcx5gofmgthaMFFrIRBhVkGyBluVPiGCFYcxNlYSwqtYjqxHlrHWnB9YEENv4Y2yszYWwSLAm2I8o6o2cBAVwOdqruwqOHPQvtGhdPSMHRo6cliJ16CnbO8dA52zaU0WOYzvZZwGEMvOgwC59K7msDYZdtmEzwTXTg5DKEAKAQjehECNCt3wDAthXdlq91IP3QeowR6E3XpvMBs9khn2SMkfwc8F4n0vnZTgN877RIfvAJ%2Bvler8N4cQT%2B2wf5xRYAodEUJ0RSIuAyCYaVbmZTgcVcWBUJDpJKqgrJOgAi1Xqo1OmuC2pXy6i/PqA1UWjXRZijEOK8U8ggDNIRrCFr%2BE4ffHhgjtoIqlcIzFaQ0jfGxXpb4/LiIUN0qdeRCRFE3Tuq9NR%2Bq3ofXtj9P6jADFAxBjYzA4NIZiHMdJSxES/GkFsdHBxmNnHIBxm4wQHiiYkzJg6XxVMAk/WCZkUJrMIkRCiatPgsT4lCxFjohBEs0kksyXLWltClamxsF4kpmttY5F1gAegNvmgpFhzYEMttbYtcyHYdKdkMnpntxnDJKDkIZAychLMzq0xoqc475FmcOmO8xNkZ1ztM8dc7p29NndskuuzCpMtBQQ45nLXjcqxXy/Ux4BVtzuQtB5Pdol9wHkPSgFdPlJDAf4IIgRZ4yI0M%2BnSakt0dQcrYW%2Bl7VqKRAOPcB/g1LH0kq%2Bz8kkdKr38MysFf6uHtlXqlH919APyVIAzLIzhJBAA)

By turning `(...||Pred_0<*>::value)` and `(...||Pred_1<*>::value)` into concepts, we allow compilers to perform proper subsumption.

```C++
template<typename...Args>
requires AnyDeceive<Pred_0, Args...>
constexpr bool fun(){return false;}

template<typename...Args>
requires AnyDeceive<Pred_0, Args...> && AnyDeceive<Pred_1, Args...>
constexpr bool fun(){return true;}

static_assert(fun<Vay<1>>());
```

## Implementation

```C++
template<template<auto...> class Predicate, typename...Elements>
concept AnyDeceive = (...||(not Predicate<Elements::value>::value));
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwArKSuADJ4DJgAcj4ARpjEAdIADqgKhE4MHt6%2BAcGp6Y4C4ZExLPGJ/tJ2mA6ZQgRMxATZPn5Btpj2RQwNTQQl0XEJSbaNza25HQrjAxFD5SNVAJS2qF7EyOwcBJgsyQa7Jv5uu/uHmMduTF5EAHQPx9gA1MgGCgrPysSY%2BKK7pGeBAAnslGKxMA87th6GxBAoniYNABBNAMLbJAjPZEMYEAEVqmDwADdMM9jnjnhAoSYAOxuOluCAMVBY76/PD/S4nGF7RgEBQgEDEsRebnYIUi7yYZbLY5WFFI5EAegAVOqNZqtcqlWqNc8ACqYGafTU6lF6rVW9Xm5FKs4HJhHE43e6PfzYJUzYheBxfH7oAD6GiVdIVyOekeeMydnNeAhmmFUyWIz1iqE8zylYvJtIsVDESjpePlodpJf84fte0dzuut1QNI9XoIPr97KDXDL4aj0cajmQ8YYieTqfTmezZLDBdoRfLpcV88roZRDouV1dqGeAElESjvb6sQBZASsgTA7tK3sxgdDkcp56brOiqd53dLqsflfItdO7mnUFwTYKFkWIYAEWbFEfgARy8PAfk%2BHF8UJEl/w7YNAVA8Cm09FE0XvMcM1oZ4qC8BgIDlPMfgIDYGBIwtuSsedFVXGt1xOEEwWYYCHiwiDcNAzBYPg41sVxAktlQq50I0TCwIUHDyTMAA2cxlLE5DJNJaSA0DLg5Ow90BPw3ZRzTIiSLIiiw2o2igR9Rji2/G9OUDJgPgSAhqDIq4TxZIhcSuLtmw9Ci5UrDhVloThAl4PwOC0UhUE4BlLGsaN1k2KczH8HhSAITRItWABrEBAkkO4NEkLhaX8DRAg0FTlLMAAOFr9E4SReBYCQNFk%2BLEuSjheEFWSCoSyLSDgWAYEQEB1gIZJbnISg0H2OgEiiCFOFUFrlIAWmUyRnmAZBBykO4zF4DkiGIPB0D0fhBBEMR2CkGRBEUFR1Am0hdH0gB3YgmGSTgeCimK4sKpLOAAeVuJasVQKhnl2g6jpOs7nguswqQ8db6FTcxcuWXhxq0VYICQNbkg2sgKAgGm6ZAYApDMPg6F2YhBQgWJodiCImmBMHeAF5hiGBWHYm0Wpxryta4QIWGGFoYXfqwWIvGAa5aFnEXSCwFhDGAcR1ZEupSUFX6k1qW5tjyiJdmi37aDwWJgYljwsGh1s8B67heFJYh0yUAkjaMV2jEK1YqAMcCADU8EwAHYa4/WnuEURxHejOvrUaH/v0Y2UGsax9DdwVIFWVBMUyK39pmdAKVMNLLDMQag7urBK4ozpukyFwGHcTw2j0MJ5jKCo9AKDIBEmPx9JnnpBknkZ9JqOoBD6CYR9ydeull%2BpZhX4ZEnX2Z570GNmhPxYz9WBRMq2CQIY4WLSAG3ghtRvbDuO07zoVVxhAXAhASBKRJmTaOqwECYCYFgRIvdSqSH8HcAAnP4WkkgqpmEkMpPqgRlJoI6hwLqpAeq5TuMpLgykWpoJajQ8qXBAgYOUh/aGQ0RogDGtHKas0qbzQRstBmTNCZbTYJwJoLBiS0n2kwV4BgjDYzQXcLglVrr4FuvdR6sgXrZ2kLnJQ%2Bdfq6HZkDEGItX7v0/jDDg8NFq3GeMjR8xBpGyPkW8Y2yjVGVTxqgAmCQIFmFJvlXhAjREJBWozfxtNCYgCkTI/anijBcDQVwWSNBaBcx5nzX6Yshb63yRLKWMsHD6wVvyZWqtoYay1jrPWAcDZ7GNqbRK%2BAfgW2NNDG2yA7b60dl0aGrt3ZCy9tsRKvt/Z5SDiHTAYcWkRFABNGOccFCJ2TqnRg6ddFZzegY2QecfqJVMUXKOLcrCWHLrEHu1da4Jk4A3AgTd/B4nOdYduX9O73S6VXPuh9nAQFcJffS49Sin2nmkWeWRd4L1IEvTIt8p7737lvC%2BMKr4H03r0Y%2BE9wXn36MCsY/REVrwfk/N6Vioa/W/gk9xCivGpJ8RoKkoDboQK4CE8mRVSCwPgSMXuzsyEUJUVVWkLDaS1UkLgo6%2BkbGcNsNw0Jyy%2BHwAEQtRGUSInEHEdsKRGMWAKGJIOYkjKLgzA0WAruOjnq7IkPsz6Rijk6ACKQcxoMA6UvYdSuGQikYoz1cdA1Rqsymr/DMPxASiY5X8JysJ1MYl001QmuJRrkjJEDCatBgYzUEDcq4o6HMskJByfzQWEtCllsltLWW5T/GKyqWrNpmBNbazEA0vKhsWnjN4O0w%2BltumqFtrsfpghBkuzdh7YEYyfZ3SmYHBIsz5kR0Wbw2OTAE5JxTmnRpGc9F7I%2BvIR1BcXWKOMKXS5wyblJTucOTgypG4l1bhYD5SUvnd3gA/TFPRB7DxyLC0FCwkVwshT0Ql8Lii4rvhilF2KCXouRf82DN9INAevi0eDRLkNgqgxytYGxn64edtYjhnAXEsH1Ya41obdjhpAZo8BxMOVQOWTAuBCDKCvyFSAMwKj/BBAatVPqfHaS0K9YNTgXCeEsdIMgwI6DAgtRUmgyQaDaqYK4P4Eh/gqXieGkqimr8rpia/hJ/T3Kg7pGcJIIAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/pagelivore/concepts/any_deceive.hpp)
- [unit test](../../../../tests/unit/concepts/pagelivore/any_deceive.test.hpp)
