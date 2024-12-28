<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::AllConfess`

<p style='text-align: right;'><a href="../../concepts.md#mouldivore-all-confess">To Index</a></p>

## Description

`Mouldivore::AllConfess` accepts a class template predicate and a list of elements.
It returns true if the predicate evaluates to `true` for every element and returns false if otherwise.

<pre><code>   Pred, Es...
-> (...&&Pred&lt;Es&gt;::value)</code></pre>

## Structure

```C++
template<template<typename...> class, typename...>
concept AllConfess = REQUIREMENT;
```

## Examples

`AllConfess` turns a fold expression of a class template predicate over `&&` into a concept so that it can be used for subsumption.

Since `(...&&Pred_0<***>::value)` and `(...&&Pred_0<***>::value) && (...&&Pred_1<***>::value)` are both atomic.
Both candidates are considered equally good.
Thus, the call is ambiguous.

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
requires (...&&(not Pred_0<Args>::value))
constexpr bool fun(){return false;}

template<typename...Args>
requires (...&&(not Pred_0<Args>::value)) && (...&&(not Pred_1<Args>::value))
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<int>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwDspK4AMngMmAByPgBGmMT%2BAGykAA6oCoRODB7evv5BaRmOAmER0SxxCWbJdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHAD0AFSH%2BwDUysSY6AD6GsdH%2B7smGgCCBJgsKQavJgDMbgQAnilGKxMAA6cE/bCPJ6zYheBync5XDTQkwBKzPY5Y46zJiOZDHNAMWaYVQpYjHGKoTzHABuYi8mGOaIsVDESjRABEfhinlyeajngcjoiLpcuLcjg9nq93p9MD8/oDgWxwaDIdDYfCCKKrlxUejodicU18YSBCSyRSqTT6d4mSy2bQOQFud9efz3YKnsLDscqF4GJLDtKXm8PniFb8AUDmKrwU9iMAFBrnucAI5ePDnBTHCBq8yJQsQBioHVnMUo36J5OQkAgO2MlYraFEy3kynU2j%2BwMQFvo84ETZBp0cr2u72yiNfaPKuNghNJlPfKFpzCZ7OYXP5iHVYul8tI66KmvL7D1xuYZvMvfVPMF2%2BJEtl3Xik9LusNhlXlvPNuvK1OxpAMGD7FlB2HY4CDhKMrAnZ5oV9E4ABUtx1O5Q12XZjmwYhiBITVTTwZBLiYBQlBaahA0VcICEhPsW3dDg1loTgAFZeD8DgtFIVBODcaxrBxDYtgdMxvh4UgCE0Zi1gAaxANjElBAAORIpDYgJEkkABOb4tPE/ROEkXgWAkDQNFILieL4jheAUEBLOk7jmNIOBYBgRAQA2AgUi8AhyEoNB3joeJIhBThVDUgBabTjmAZACSkUEzF4C5CBIPB0D0fhBBEMR2CkGRBEUFR1Bc0hdC4UgAHdiCYFJOB4Fj2M4mTeM4AB5fy/J1VAqGOKLEliyR4sS45krMPMPBC%2BgKXMCSVl4ZytDWCAkGClJQrICgIE27aQGAKQzD4OhXmIByIBidqYnCZp/ia3hbuYYh/k6mJtDqZzJOCthBE6hhaAeiqsBiLxgDcMRnUe0gsBYQxgHEEHN3qWkt3a0k6n8nZJNo7p2toPAYnq16PCwdroLwMzuF4NHiCpJROTeBHCaMGS1ioAxkwANTwTAas62MYdy4RRHEIqRdKtR2qq/QEZQQTLH0ImHMgNZUBSXoHI4aLZnQH5OVMSxrDMGy6eILL0bVroeiyFwGHcTx2j0UIFnKSo9EKTIBCmPxqq93ohnd0ZqtqeoBH6SYnbyUPui%2Bho5iDkYElDuZfb0XEWiTpYU7WBQRO2CQWo4DirPa2zBpiuKEqSyQUrzXAMvm8SuCWqT2bWBBMCYLAEj7UgFMkb5QT0gJJA0SQzEkRILKUnSjI4EzSDM74zFBb5EgCFTvhUti2K4fSdJUsuKts%2BzHPbly1s89bvJ6/zAr21BZrCiKOCGkbCQMIwJp00EuFBDxdKRALbZWqiLfK4tpCSyUNLCqugTp1Qao9YupdrK8Fst1Xy/ljj9UrsNOKyBv7AF/v/QB01n5bTmjeVebcVquVvvtOaj8mGjCIQjLgOkuCWRoLQc6l1roVWevdGGwjXrvU%2Bg4GGv1GAEABkDdqoNwaQ1oNDGmsNmZGCRjxfA5xUbowqpjZA2MYZ41YhVQmxN7pkx2DxSm1NJJ0wZpgJm8MtHhFAFfPgXMFC835oLRgwtZCQMKtA2QUtyo8QQXLNmRsrBK0sarfuGstacF1gQfW3xDaKwsKbDB5tLZJLznHcOfgICuHTtVV2ZRk6e3SN7bI0c/apHqYHN2tTY62wjmnJpGcSm9EjvMGpOcM49NyM0zOQzFge1busTYhdZnmLQeXTg%2BDP7sJ/pwshNwICNxATQ1uy0O6kC7j3UY/cFLcMsuYpeK82Kgl0mxHSZhnnVBUgfbSJ8bKcHPk5dmbkb5IB8r1FhlDtrhTYJwZoLA4osAULSAktItnylmGlfAICso5WCWLUJxV5CwMiToEA3xar1UajTVBbVT5dXvn1AaqhYXwsRciyMswKEv2bt8b4dD/mMLBcw3arCEgIpSCkS4SKdKXBRQQS4DLoFnXiAIm6d1XqiJVW9D6X1pHPz%2BnIwGwMdGYDBhDKG2tJJwxZrY3guj45o21kA1QWNXimMEPjCxRMSb/BsRTC2DjabxGca4lmHj/mcyYDzPmAshbqIgTiiQYSSoEplsSmJxgcnKxiEU3imssja12HrBWxtLB5N4gUrAWaw69Hto7cZLsHbZxmS0ooWRKlNoaQ2kONt47dIGK2ytCcBgdpTuMXtvTU6DvaSM2Z%2Bd5mFUpV8jBqy5XHDhQiukLLXhst2eikgByeVX07t3XulBi63OJWvD54kzDXq4CpDQiQnkLo6nZWwF96HNgHiAIe/8d5sUnt8Ni97xJaQXt8Kl3yX3vuLqlJ9Z9L6rTWHTDIzhJBAA)

By turning `(...&&Pred_0<***>::value)` and `(...&&Pred_1<***>::value)` into concepts, we allow compilers to perform proper subsumption.

```C++
/**** fun ****/
template<typename...Args>
requires AllConfess<Pred_0, Args...>
constexpr bool fun(){return false;}

template<typename...Args>
requires AllConfess<Pred_0, Args...> && AllConfess<Pred_1, Args...>
constexpr bool fun(){return true;}

/**** Test ****/
static_assert(fun<int>());
```

## Implementation

```C++
template<template<typename...> class Predicate, typename...Elements>
concept AllConfess = (...&&Predicate<Elements>::value);
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwDspK4AMngMmAByPgBGmMQgAMwAbKQADqgKhE4MHt6%2B/kEZWY4CYRHRLHEJKbaY9qUMQgRMxAR5Pn6BdQ05za0E5VGx8UmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnhzsmGgCC%2B4cA1ACSLGn0bIJMjbdH51c3p3%2Bn30uF0uBEwTwMoJMiTcoPB70wUJhAE80oxWJgAHRYqHYW7IAwKBS3ZTETD4USg0i3AgotFsLEY7AvRgEBQ44FoBhbNIEW6XWi0DwMKiYQm3KEAEVuEAZ5mScpJZLwFIR0KZYJZbMS2BAIAAbmIvJhllCrFdgb9/mcLUdbgAVUWsz7Wn5W46Am13RXoAD6GmdB0BsOe8MRNNRzHp2O1wImxC8DmJpN9GmBJgCZsut2ztzmjmQeIEE0wqjSxFuMVQnluBu8mHFGYI8YRAQlprTrfb5tdXuTPq4Ab2QbBIch0PDdMx0ewsabCd53v7HczOdzLXzhYYxdL5cr1drRobFjnLbbiUz6bPF57B1uVC8DEHw7hY%2BREfRDMuxGAWpnV1JACOXh4KSRL8oKAgioSiKLhoVJfj%2BsoxlcnLbmWFZVrQd4PhAJoZqSBAbI%2BVBiEo7adt2IIjhCqpvpOn7fr%2BwKAcBoF8gKQpQVqbiwfBjFIbicpyuxEHCqK3GLlwfGIdOHJFqCO4YdW94MLh6YWARRHUs25FtpRlr2o6T6zu8yo%2BkwhLxAQ1APoi4QEDiuEmueHCrLQnAAKy8H4HBaKQqCcG41jWLm6ybPW5iJDwpAEJormrAA1iAHnJBiAAcyRSB5ATJJIACciQ5WYiT6Jwki8CwEgaHBPl%2BQFHC8AoIBwbFvmuaQcCwDAiAgOsBBpF4BDkJQaBPHQ8SROinCqBlAC0uW3MAyAFlIGJmLwSpEMQeDoHo/CCCIYjsFIMiCIoKjqG1pC6FJADuxBMGknA8G5nneXF/mcAA8oNA28qgVC3DNyTzZIi3Lbcq1mNKHhjfQ5aRVwyy8K1WirBASCjWk41kBQEBYzjIDAFIZh8HQoLEE1EAxB9MThK0SLPbwdPMMQSJfTE2iYA4TOkKNrwEF9DC0IzV1YDEXjAG4Yi0E13C8FgLCGMA4hiyB3OOHqoofSW3ODds0X2fUH20HgMQPWzHhYB9TZ4JV8ukFrxCVkoEpgsrptGHFqxUAYP4AGp4Jgt1fRGvP7cIojiCdEfnWoH03foysoMFlj6GbTWQKsqA8jkcuzRM6CSqYljWGYdVO9tWCZ7hPQazkLgMO4nidHooThMMVSjFJxTZAI0x%2BD3mR9wwCwjAkUl2PXAj9FMLcFJP9TT00kyDB3izd7Yq8D3ocxtGPXcT6sChhVsEivRwXmkLVvD1UDc0LUtK2SGt0q4IQJDisVSMo97qwIJgJgWAEi1ySpIRIGICoBEkBoSQZhJDJGqilPKpUODlVIJVRIZgMQpACGlRIaUPIeS4IVPKaVr4fXqo1ZqMVvYdW6hjXqv1BrDXxqgOGE0pocGBqDPEBgjCQzyhiLgGI/KbRIDtPashDrR2kLHJQ8crq6FJvdR6TML5Xxvp9DgP1%2BqDVuADe%2BIMFr4mVoI4RoiYbsOxvDL%2BWDka0LaujTG1icasIJvDFA/DiZ5S4HBGgtAKZUxpldFmDNeZhLZhzLmPMHb8xZELEWH1xaS2lgKOW0VFYe22H5fApIHB4C1nLMRqg9agl5kbdyV1TbmwZlbHJKNtr22ik7F2mA3ZKyMJ7UATi%2BB%2BwUIHYOodGDh2kVHY6cjZBx0un5ZRScvYlysGnGpNds65yLJwAuBAi6JAlIssuFd4hV21lnOuBTnAQFcDvKS7cKjjz0L3Ro1z0jD0aAfJYi9egz23vPQeZzGizzXncw%2Bu8fn5D%2BXvIFncPnH1PsdDR70rp3x4SY7x5iRH%2BggO/Ladif6OLRv/QBwDKCJSqnBKp6DMEeQxPlDyeUzD0rMMkNKJDcoUKRZwahLU6GdR6n1P67jXHw0mmwTgrQWALRYAoPUBY9RcCETRCYG18BbUkVJCOMiJmnXkAomZOgkikFUU9eWCL2V1W%2Bsw/6gNVCSulbK%2BVGJFW8ggLDGx8Q7GJAcajdqjCPHxEFRwhIMq0hpB9HKvKPonU%2BhtXI8m8Rgm03pmzCJSb2acw1rzeJghEmi1yZgCWUsZYZIVu7LpDTSB5PrkUnWpTkD6wqYIY21SzYWyRPUm2TTeatMyO00tKtwg9LRn0pgAcg4hzDg7DV4yJCTLOrqhOBrvEp1LssjO8A1mNDljsQuy6lkWHLrfSuO0Tm1ynucvwlym7PNudCzejycjPPvWUde9zPnL0Bc8s9ALV7vM3pCz9P6X0gqRmsDYZ8QNVM0ZQzgQNbUyprA6p1b8VWf0Rl6v%2BpAAFANGLXClFUkjYNZcVMwJGuBpQ0MkOlZrb6ctsDQ71yxSXgOEQQjycDEgeQo8VHKqDEiIvNQ1fF8VUHrWo9o3%2BTjVhOyyM4SQQA)

## Links

- [Example](../../../code/facilities/concepts/mouldivore/all_confess/implementation.hpp)
- [Source code](../../../../conceptrodon/mouldivore/concepts/all_confess.hpp)
- [Unit test](../../../../tests/unit/concepts/mouldivore/all_confess.test.hpp)
