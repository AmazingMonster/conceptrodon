<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::Deceive`

<p style='text-align: right;'><a href="../../concepts.md#mouldivore-deceive">To Index</a></p>

## Description

`Mouldivore::Deceive` accepts a class template predicate and a list of elements.
It returns true if the predicate invoked by the elements returns false and returns false if otherwise.

<pre><code>   Pred, Es...
-> not Pred&lt;Es...&gt;::value</code></pre>

## Structure

```C++
template<template<typename...> class, typename...>
concept Deceive = REQUIREMENT;
```

## Examples

`Deceive` turns a class template predicate into a concept so that it can be used for subsumption.

Since `(not Pred_0<***>::value)` and `(not Pred_0<***>::value) && (not Pred_1<***>::value)` are both atomic. Both candidates are considered equally good. Thus, the call is ambiguous.

```C++
/**** Pred_0 ****/
template<typename...>
struct Pred_0
{
    static constexpr bool value {false};
};

/**** Pred_1 ****/
template<typename...>
struct Pred_1
{
    static constexpr bool value {false};
};

/**** fun ****/
template<typename...Args>
requires (not Pred_0<Args...>::value)
constexpr bool fun(){return false;}

template<typename...Args>
requires (not Pred_0<Args...>::value) && (not Pred_1<Args...>::value)
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<int>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwDspK4AMngMmAByPgBGmMT%2BAGykAA6oCoRODB7evv5BaRmOAmER0SxxCWbJdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHAD0AFSH%2BwDUysSY6AD6GsdH%2B7smGgCCBJgsKQavJgDMbgQAnilGKxMAA6cE/bCPJ6zYheBync5XDTQkwBKzPY5Y46zJiOZDHNAMWaYVQpYjHGKoTzHABuYi8mGOaIsVDESjRABEfhinlyeajngcjoiLpcuLcjg9nq93p9MD8/oDgWxwaDIdDYfCCKKrlxUejodicU18YSBCSyRSqTT6d4mSy2bQOQFud9efz3YKnsLDscqF4GJLDtKXm8PniFb8AUDmKrwU9iMAFBrnucAI5ePDnBTHCAMVA6s5ilG/RPJtWQkAgO2MlbQomW8mU6m0f2BiD19HnAibINOjle13e2URr7R5VxsEJpMp75QtOYTPZzC5/OF3XXRXlhSV%2BfV2uYFbM6rmRJ5gtFpHi7ezvfYA8Mo8Ni2vK0tmkBhidlk9vvHAg4SjKxh2eaFfROAAVVcdTuUNdl2Y5sGIYgSE1U08GQS4mAUJQWmoQNFXCAhIU7et3Q4NZaE4ABWXg/A4LRSFQTg3GsawcQ2LYHTMb4eFIAhNEotYAGsQBoxJQQADkSKQaICRJJAATm%2BBTeP0ThJF4FgJA0DRSAYpiWI4XgFBAfTBMYyjSDgWAYEQEANgIFIvAIchKDQd46HiSIQU4VQZIAWkU45gGQAkpFBMxeAuQgSDwdA9H4QQRDEdgpBkQRFBUdQrNIXQuFIAB3YgmBSTgeCo2j6KE5jOAAeVclydVQKhjgCxJgskULwuOSKzDzDwvPoClzD4lZeEsrQ1ggJBPJSbyyAoCB5sWkBgCkMw%2BDoV5iDMiAYlqmJwmaf4Kt4Y7mGIf56pibQ6ks/jPLYQR6oYWgzryrAYi8YA3DEZ1ztILAWEMYBxC%2Bld6lpVdatJOpXJ2fjiO6WraDwGJSuujwsFqwC8B07heBh4gqSUTk3jB9GjCEtYqAMZMADU8EwIr6tjIHkuEURxAyrnsrUWqCv0MGUHYyx9AxszIDWVAUl6MyOEC2Z0B%2BTlTEsawzCMkniAS2GZa6HoshcBh3E8do9FCBZykqPRCkyAQpj8QqHd6IZbdGQranqAR%2BkmC28m97oHoaOYPZGBJvbmZ29FxFoI6WKO1gULjtgkKqODogzauM9qgpCsKIskKK81wOLRt4rgJoE2m1gQTAmCwBJO1IMTJG%2BUEVICSQNEkMxJESPSJKUjSOC00gdO%2BMxQW%2BRIAik74pJomiuFUpSpJzvLjNM8za6smb7Nmxymtc9yVtQYafL8jgOq6wkDCMPqlNBLhQSY2KiD1xLCq51LeekPzJQgs8q6C2iVMq51M7Z0MrwYyjVnKuWOK1fOnUQrIEfsAZ%2Br936DUvgtEaJ5p41ymtZY%2Bq0RrnwoaMDBYMuBKS4PpGgtBdr7UOnlS6p0gacOurde6DggbPUYAQN6H1arfV%2Bv9WggMibA0pkYCGTF8DnGhrDPK8NkCIyBijaieV0aY1OjjHYTF8aE34iTMmmAKagwUeEUAB8%2BAMwUMzVm7NGCc1kP/dKgDZAC1ykxMBIsaYaysBLfR0tW5ywVpwZWBBVbfHVuLCw2s4G631hElOIdfZ%2BAgK4WOhVrZlEjvbdIjtsiBxdqkUp7sbbFODsbP2McKlxyyb0f28wilJzjk03IlT44dMWHbau6xNjp2GbomBudOCoPvrQp%2B9CcE3AgOXL%2BRDq6TTrqQBuTdRitzEow/SuiJ5TxoqCZSNElJmEudUKSa9FJbyMpwXeFlaY2SPkgJyzUqH4MWr5NgnBmgsBCiwBQtICS0gWfKWYMV8BfwSklTxPNvGZXkMA/xOgQDfGKqVcqRNoE1W3g1U%2BLU2qqGBaC8FkLIyzDwVfSu3xvgkNeeQn5lDlrUISGClIKRLgQqUpcKFBBLhksATteIbCjonWutwqVN07oPUEZfF6Ij3qfSUZgH6f0AaK34iDKmxjeDKNDjDRWH9VAI1eNowQqM9EYyxv8IxeM9ZmOJvESx1iqZ2NefTJgTMWZsw5rIv%2BSKJA%2BKymioWmKgnGCSZLGIGTmLyyyIrXYKsxaa0sCk5iaSsAJp9r0U25telWzNonIZVSihZHyRWspZavZG1Do0gY1b81hwGHWqO4xm3NOju22pXThmp1GelfFDy4HTJFccEFYK6RUteDS5ZsKSBrKZQfeujdm6UEzsczFM87m8TMIergUkNCJAuWOuqJlbB71ISsUSIAO6vyXjRfu3waKnt4gpMe3wCWPKvbezO0UL0733tNNYJMMjOEkEAA%3D%3D)

By turning `(not Pred_0<***>::value)` and `(not Pred_1<***>::value)` into concepts, we allow compilers to perform proper subsumption.

```C++
/**** fun ****/
template<typename...Args>
requires Deceive<Pred_0, Args...>
constexpr bool fun(){return false;}

template<typename...Args>
requires Deceive<Pred_0, Args...> && Deceive<Pred_1, Args...>
constexpr bool fun(){return true;}

/**** Test ****/
static_assert(fun<int>());
```

## Implementation

```C++
template<template<typename...> class Predicate, typename...Elements>
concept Deceive = not Predicate<Elements...>::value;
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwDspK4AMngMmAByPgBGmMQgAMwAbKQADqgKhE4MHt6%2B/kEZWY4CYRHRLHEJKbaY9qUMQgRMxAR5Pn6BdQ05za0E5VGx8UmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnhzsmGgCC%2B4cA1ACSLGn0bIJMjbdH51c3p3%2Bn30uF0uBEwTwMoJMiTcoPB70wUJhAE80oxWJgAHRYqHYW7IAwKBS3ZTETD4USg0i3AgotFsLEY7AvRgEBQ44FoBhbNIEW4AEUwWzwADdMLcoXzbgxULySWS8BSEdCmWCWQoGTiQCBhWIvEqrFdgb9/mcjUdbgAVTATIlfM0mu2Gn7muXoAD6Gk%2BpqusOe8MRNNRzHp2MS2GBE2IXgcxNJ7o0wJMAQNl1uaduc0cyDxAgmmFUaWItxiqE8tx13jFSYsVDESiTfKhKYbTcTzrurrdXC9B0BvohSuRQfRGrDEYIUZjna4ieTwPTGZaWZzDDzBaLJbLFb14uTtdo9YCjcSzaPrad13NVC8DB7ez7YL9kOhgbpmKxl2IwDZY6upIAjl4eCkkSApCqKiKdhoVKft%2Bo7hlcnJroWxalrQtzXgwEDLNWpIEBst77vWJ4the/b%2Bi%2BtLBu%2BGKwT%2BCGfpggHAda/KCpgIqDlBMFfuqoa4uYySCWx4FcXGXY8XB/EcrmoLrqhZaYdhuGYPhxC3hOeqtmeF7Gpa1q8o6lyZgqbpMIS8QENQN6IuEBA4thOEnhwqy0JwACsvB%2BBwWikKgnBuNY1gZusmxVmYiQ8KQBCaC5qwANYgO5yQYgAHMkUjuQEySSAAnIk2URfonCSLwLASBo0Heb5/kcLwCggNBMU%2BS5pBwLAMCICA6wEGkXgEOQlBoE8dDxJE6KcKo6UALQ5bcwDINmUgYmYvDykQxB4Ogej8IIIhiOwUgyIIigqOoLWkLoXCkAA7sQTBpJwPCuR5XmxX5nAAPL9X1vKoFQtxTcks2SPNi23MtZi3BAHgjfQRbmJFyy8M1WirBASDDWko1kBQEBYzjIDAFIZh8HQoLEA1EAxO9MThK0SJPbwdPMMQSKfTE2iCs1UXDa8BCfQwtCMxdWAxF4wBuGIB5M6QWAsIYwDiKLLEOJxDUXfmgr9dsUV2fU720HgMT3WzHhYO9E54OV3C8KKxAlkoAoK0YRtGLFqxUAY34AGp4JgN2fUGsu7cIojiEdoenWo71XfoisoEFlj6MbDWQKsqA8jkGvTRM6ASqYljWGYNX25tWBp9hPTczkLgMO4nidHooThMMVSjNdxTZAI0x%2BJ3mTdwwCwjAk112DXAj9FMjcFGP9QT00kyDK3iwd7YS%2B93ocxtMP7ej6sCihVsEgvRwnmkNVvC1YDM1zQtS2SCt0O4IQJDihFXDI9FHurAgmBMFgBIVdEqSESBifKARJAaEkGYSQyRKrJVysVDgpVSDlUSGYDEKQAipUSKldy7kuAFVyqlC%2B71ar1Uat/Fq6NOoY26j9fqg18aoDhmNCaHAgYgzxAYIwENcoYi4BiXy60SBbR2rIfaEdpBRyUDHC6uhSZ3QekzU%2B59L4fQ4N9Xq/Vbj/RvsDOa%2BJFb8MEcI6GsNsbw3fhgr%2BqNWr0IJvDZhTjRjGKMFwXKXBoI0FoBTKmNMLoswZrLYJbMOZcwcLLPmLJBbC3emLCWUtaAy1tnLMEitla%2BXwKSNWooNYiNUNrUEst9ZuQukbE2DNzbbF8lbG2UV7aO0wM7TJ4RQA0L4N7BQfsA5B0YCHSR4dDoyNkNHc6vlFHx3doXKwydKmVwzlnXMnBc4EHzokPkszi6l3iOXa08AD7zzVs4CArhN7XRbhUEeegu6NAuekAejRd5LDnr0SeG8Z592ricxe8wV43LHp8/I3zt7L2uXvE%2BawNjH0/sg9R5DOAGO4e44ApihGeggC/DaNjP4ox/qQP%2BADRjAIqtBcpqD0HuQxHldyuUzD0rMMkVKRCcpkIuhQ2wVD7G0PgPQnqv0XGsKsewtgnBWgsDmiwBQwpszCk8RiAcEw1r4A2uI66ocpEjOOvIOREydBJFuvdR6ts1FvQ5V9Rhf0AaqClTKuVCqlW8hhsKnGNjEh2I9m1TGrrnF41cQkWVaQ0hunlblN0Tq3S2pkeTeIATab0zZqExN7NObc2iaw/mcSRbZMwOLSW0sNZRXlpk2pvAck13ye9LWyAdalMEAbCpxtTZIhqZbTaDS7bxGaa0127SvVeyYL7f2gdg5pM1cMiQoyTp6tjoa3hxgk42AWYcvyyzVycB2HnRORdLAlyvmXLaBz04/MaHXBuILm71xeWvO5OQHl3rKACyFbyF5T3aF8rexzGjvpvaPdeAwHlgr/VCw%2BMLDpmvZTVJF0bbjStleWR18IJjP1VW/RGeLqFo1/v/QBlBT6UqSJg1lEUzBka4KlDQyQ6VQavpwShTUCUgLAUQ/BMDEjuSoxFbKyDEjmug3VLDcVkGrVo5o/FNDVj2yyM4SQQA)

## Links

- [Source code](../../../../conceptrodon/mouldivore/concepts/deceive.hpp)
- [Unit test](../../../../tests/unit/concepts/mouldivore/deceive.test.hpp)
- [Example](../../../code/facilities/concepts/mouldivore/deceive/implementation.hpp)
