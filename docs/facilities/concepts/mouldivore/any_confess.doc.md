<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::AnyConfess`

<p style='text-align: right;'><a href="../../concepts.md#mouldivore-any-confess">To Index</a></p>

## Description

`Mouldivore::AnyConfess` accepts a class template predicate and a list of elements.
It returns true if there exists an element for which the predicate evaluates to `true` and returns false if otherwise.

<pre><code>   Pred, Es...
-> (...||Pred&lt;Es&gt;::value)</code></pre>

## Structure

```C++
template<template<typename...> class, typename...>
concept AnyConfess = REQUIREMENT;
```

## Examples

`AnyConfess` turns a fold expression of a class template predicate over `||` into a concept so that it can be used for subsumption.

Since `(...||Pred_0<***>::value)` and `(...||Pred_0<***>::value) && (...||Pred_1<***>::value)` are both atomic.
Both candidates are considered equally good.
Thus, the call is ambiguous.

```C++
/**** Pred_0 ****/
template<typename...>
struct Pred_0
{
    static constexpr bool value {true};
};

/**** Pred_1 ****/
template<typename...>
struct Pred_1
{
    static constexpr bool value {true};
};

/**** fun ****/
template<typename...Args>
requires (...||Pred_0<Args>::value)
constexpr bool fun(){return false;}

template<typename...Args>
requires (...||Pred_0<Args>::value) && (...||Pred_1<Args>::value)
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<int>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwDspK4AMngMmAByPgBGmMT%2BAGykAA6oCoRODB7evv5BaRmOAmER0SxxCWbJdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHAD0AFSH%2BwDUysSY6AD6GsdH%2B7smGgCCBJgsKQavJgDMbgQAnilGKxMAA6cE/bCPJ6zYheBync5XDTQkwBKzPY5Y46zJiOZDHNAMWaYVQpYjHGKoTzHABuYi8mGOaIsBDhmDRABEfhinlyeajngcjoiLpcuLcjg9nq93p8Ob8AUDmGxwaDIdDYfCCKKrlxUejodicU18YSBCSyRSqTT6d4mSy2Yz%2Bd9eS63UK7scqF4GJLDtKXm8PniFX9AcDVeCnsRgAoNc9zgBHLx4c4KY4QNVotw5s5ilG/GNxyEgEB2xkraFEy3kynU2je30QKvo84ETZ%2BqhiJQCgLc57Q2Uhr6KiMqsHR2Px75QxOYFNpzAZrMQgK59f55E/NzFmfYMsVzArZnVcyJTPZ9d5pHind70vlhnH6sW15W%2Bs0n0MFss9ud44nQVKx%2B0FJ5hUOY4ABVlx1O5A12XZjmwYhiBITVTTwZBLiYBQlBaahfR3cICEhFsq1dDg1loTgAFZeD8DgtFIVBOFzSxrBxDYtgdMxvh4UgCE0Ki1gAaxAWjElBAAORIpFogJEkkABOb5FL4/ROEkXgWAkDQNFIRjmNYjheAUEADKEpiqNIOBYBgRAQA2AgUi8AhyEoNB3joeJIhBThVFkgBaJTjmAZACSkUEzF4C5CBIPB0D0fhBBEMR2CkGRBEUFR1Gs0hdC4UgAHdiCYFJOB4ai6IY4SWM4AB5NzXJ1VAqGOQLEhCyQwoi44orMTMPG8%2BgKXMfiVl4KytDWCAkC8lIfLICgIAWpaQGAKQzD4OhXmIcyIBiOqYnCZp/kq3gTuYYh/gamJtDqKyBK8thBAahhaHO/KsBiLxgDcMRaHM7heCwFhDGAcRvqXepaWXOrSTqNydgEkjujq2g8BiMqbo8LA6rZPBdJB0g4eIKklE5N4IcxoxhLWKgDDjAA1PBMGKhrlQurLhFEcRMpS%2BQlDUOrCv0CGUGsax9Cx8zIDWVAUl6YGgtmdAfk5UwOMsMxjLJ4hEvh%2BWuh6LIXAYdxPHaPRQgWcpKj0QpMgEKY/CKp3eiGe3RiK2p6gEfpJitvJfe6R6GjmL2RgSX25ldvRcRaKOlhjtYFG47YJGqjh6MMuqTI64LQvCyLJGizNcHisa%2BK4SbBPptYEEwJgsASFtSHEyRvlBVSAkkDRJDMSREn0yTlM0jhtNIXTvjMUFvkSAJpO%2BaTaNorg1OU6S8/ykyzIs%2BvrNmhy5qc5q3I81bUBG3z/I4TrusJAwjH65TQS4UFmLiogDaSorBbSvzaQgscoi3yrobapVyoXWzrnIyvATJNRcm5Y4bVC5dVCsgZ%2BwBX7v0/kNa%2Bi1RqnlnnXaaNlT5rVGpfKhowsEQy4MpLgBkaC0D2gdI6%2BUrpnW5twm6d0HoOG5i9RgBB3qfTqj9P6ANaBA25mDGmOxmL4HOLDeG%2BVEbIGRtzNGNF8qY2xmdPGSipoG2JgJMmFNMBU3BkYWmoAj58CZgoVm7NOaMG5gAvmGVgGyFAXlZiEDxZ0y1lYSwMsYhy3borZWnBVYEHVt8TWUsdZ63iL/I27c/a9HNpbXIbtggW2Tg7d26RnbZGDgUj2WRik%2BxNuHAOcdKkJzDv7Pokc7bRwTk0/J3SBi1NTusTYmda4TzgfnTg6DH70JfowvBNwICVx/iQ2uU0G6kCbi3UY7dxLMIMnoqeM9aKghUrRZSZhznVGkhvJSO9jKcH3pZemtkT5IGci1GhhClp%2BTYJwZoLBQosAULSAktI5nylmLFfAP9ErJVkIAnxPN/GixAN8EqZUKog1gbVXejVz6tXaqoQFwLQXgtDLMAhN9q7fG%2BGQ55lCvnUJWrQhIIKUgpEuGC5SlwIUEEuES4Bu14gcOOqdG6vCxW3Xuo9YR19XpiI%2Bl9ZRmBfr/UBsDASCi7EmNICo8OcNgZf1UEjV4OjBDo30VjHG/xjEEzMdzSx6RrHUzseEBxM0nFMBZmzDmXMSZePShIXx2VhYBJ0Ki4JxgUk2AMVEhWSssjA12GrSW2sLC6wQfrQ2cb6ltNyfHIqtsyhdNKUULIBbUhlM9p0lOLTTaNIGBW7JEd%2Bk1pKeMRtzTY6tuLbW0Z6dhkZWxXchBkyBXHCBSCukZLXgUsWdCkgKy6VH0bs3VulBs6HNRXPG5fEzD7q4NJDQiQzkjvqqZWwB9yErDEiALu78V60UHt8Wix6%2BKKQnt8HF9yL3XuzjFM9e9D4zTWGTDIzhJBAA%3D%3D)

By turning `(...||Pred_0<***>::value)` and `(...||Pred_1<***>::value)` into concepts, we allow compilers to perform proper subsumption.

```C++
/**** fun ****/
template<typename...Args>
requires AnyConfess<Pred_0, Args...>
constexpr bool fun(){return false;}

template<typename...Args>
requires AnyConfess<Pred_0, Args...> && AnyConfess<Pred_1, Args...>
constexpr bool fun(){return true;}

/**** Test ****/
static_assert(fun<int>());
```

## Implementation

```C++
template<template<typename...> class Predicate, typename...Elements>
concept AnyConfess = (...||Predicate<Elements>::value);
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwDspK4AMngMmAByPgBGmMQgAMwAbKQADqgKhE4MHt6%2B/kEZWY4CYRHRLHEJKbaY9qUMQgRMxAR5Pn6BdQ05za0E5VGx8UmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnhzsmGgCC%2B4cA1ACSLGn0bIJMjbdH51c3p3%2Bn30uF0uBEwTwMoJMiTcoPB70wUJhAE80oxWJgAHRYqHYW7IAwKBS3ZTETD4USg0i3AgotFsLEY7AvRgEBQ44FoBhbNIEW6XBhIjwMKiYQm3KEAEVuEAZJgCbjlbhJZLwFIR0KZYJZbMS2BAIAAbmIvJhllCrFdgb9/mcrUdbgAVUWsz62n4246Au13ZXoAD6GldB0BsOe8MRNNRzHp2N1wImxC8DmJpP9GmBcotl1uOduc0cyDxAgmmFUaWItxiqE8tyN3kw4oCFgIiYRAQl5oz7c7lvdPtTfq4Qb2IbBYch0MjdMxsew8ZbSd5vsHXazubzLQLRYYJbLFarNbrJsbzdbco7iSz557QL7B1uVC8DGHo7hE%2BRUfRDMuxGAOrnVykgAjl4eCkkS/KCgIIqEoiy4aFSP5/rKcZXJyu7lpW1a0A%2BT4QGaTakgQGzPlQYhKJ23a9iCY4QuqH7Tt%2Bv7/sCwGgeBfICkKME6kqA4IXyzEobi5jJKJnFQcKoq8cuXCIUJs4csWoJ7lhNaPgw%2BGZkRJHUmel7XtR1qOs6L7zu8qp%2BkwhLxAQ1BPoi4QEDi%2BFmpeHCrLQnAAKy8H4HBaKQqCcAqljWHm6ybA25iJDwpAEJoHmrAA1iA3nJBiAAcyRSN5ATJJIACciT5WYiT6Jwki8CwEgaAh/mBcFHC8AoIAIQlAUeaQcCwDAiAgOsBBpF4BDkJQaBPHQ8SROinCqNlAC0BW3MAyCFlIGJmLwKpEMQeDoHo/CCCIYjsFIMiCIoKjqJ1pC6HJADuxBMGknA8J5Pl%2BYlQWcAA8iNw28qgVC3PNyRLZIK1rbcG1mNKHiTfQFYxVwyy8B1WirBASATWkU1kBQEC4/jIDAFIZh8HQoLEK1EAxN9MThK0SJvbwjPMMQSK/TE2iYA4rOkBNrwEL9DC0Czt1YDEXjAG4Yi0K13C8FgLCGMA4iS2BfOOAaorfaWfMjdscVOfU320HgMTPZzHhYN9LZ4DVSukLrxBVkoEpgmrFtGIlqxUAYf4AGp4JgD2/VGAtHcIojiOd0dXWo333foasoNY1j6JbrWQKsqA8jkisLRM6CSqYYWWGYjWu3tWA5/hPTazkLgMO4nidHooThMMVSjHJxTZAI0x%2BP3mSDwwCwjAkcl2E3Aj9FM7cFDP9Rz00kyDN3ix97YG/D3ocxtJPvfT6sCiRVsEgfRwvmkA1vBNaDi3Lat62SJt0q4IQJDimVqPo37VYCBMBMCwAkBuqVJCJAxMVAIkgNCSDMJIZIdV0qFQqhwKqpAaqJDMBiFIARMqJEyt5byXASqFUynfb6TUWptXin7bqfVsYDQBiNMaRNUCI2mrNDgYMIZ4gMEYGGhUMRcAxIFHaJB9qHVkCdOO0gE5KCTrdXQFMnovVZtfW%2B98focH%2BkNEatxgZP3BstfEasRFiIkfDLheMka/1wWjBhnUsY4zsfjDhxMkYoCEWTQqXAEI0FoNTWm9Nbrs2ZgLSJnNua835s7IWLJRbi2%2BlLGWctaAKwFirb22xAr4FJA4PAutFaSNUIbUEAtTZeVuhbK2zNbb5PRntJ2cVXbu0wJ7VWRgfagFcXwQOCgQ5hwjowKOcjY5nUUbIRON1ApqNTr7cuVhLBZxiPXPOBdiycGLgQUuiQJQrOsFXB%2BNd9p61zo3YpzgICuH3nJLuFQp56AHo0B56Qx6NGPksFevR557yXiPa5jQF6b2eSfA%2BgL8jAsPuCnuvyz4XzOtor6t1H78PMX4qx4jAwQC/rtRx/8XGYyASAsBlAUq1QQrUrBODvIYiKt5QqZgWVmGSJlchBVqHos4HQ9qjCer9UGoDLxHikYzTYJwVoLBlosAUAaQsBouCiLohMba%2BBdoyLktHeR0yLryGUfMnQSRSAaNekrVFPLGp/TYUDEGqg5UKqVSqjEareQQARvY%2BIjjEjOIxl1Fh3j4hiu4QkRVaQ0h%2BmVYVP07q/SOsUVTeIYSGZM05tE9NXMebawFkkwQKSJYFMwNLWW8tFZxVyb05ppBClN1KfrCpyAjbVMEGbOpltrZQTtrdB2bTeAdMyF0r2vTwj9MxoMpgwdQ7h0js7XVUyJAzMuka5Opq/HpwrjYepmygrbJ3JwHYJdN2rIsKcoK5y67wDPqvG5fg7mtw%2BU8hFO83k5A%2BW%2BsoW8Xl/LXmCj5s871gp%2BTvOFAGN4gdPmsDYl9UYYJ0TQzgoMnWKtrK691n9NU/xRv6wBpBgGgNGA3Wl1Ukh4K5WVMwVGuCZQ0MkZl1qH58tsPQgNywqVQLEcQ7yiDEjeTo2VfKGDEhoptc1ElSUMFbUY3ogBrjViuyyM4SQQA%3D)

## Links

- [Source code](../../../../conceptrodon/mouldivore/concepts/any_confess.hpp)
- [Unit test](../../../../tests/unit/concepts/mouldivore/any_confess.test.hpp)
- [Example](../../../code/facilities/concepts/mouldivore/any_confess/implementation.hpp)
