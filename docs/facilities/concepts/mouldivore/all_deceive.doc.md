<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::AllDeceive`

<p style='text-align: right;'><a href="../../concepts.md#mouldivore-all-deceive">To Index</a></p>

## Description

`Mouldivore::AllDeceive` accepts a class template predicate and a list of elements.
It returns true if the predicate evaluates to `false` for every element and returns false if otherwise.

<pre><code>   Pred, Es...
-> (...&&(not Pred&lt;Es&gt;::value))</code></pre>

## Structure

```C++
template<template<typename...> class, typename...>
concept AllDeceive = REQUIREMENT;
```

## Examples

`AllDeceive` turns a fold expression of a class template predicate over `&&` into a concept so that it can be used for subsumption.

Since `(...&&(not Pred_0<***>::value))` and `(...&&(not Pred_0<***>::value)) && (...&&(not Pred_1<***>::value))` are both atomic.
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

By turning `(...&&(not Pred_0<***>::value))` and `(...&&(not Pred_1<***>::value))` into concepts, we allow compilers to perform proper subsumption.

```C++
/**** fun ****/
template<typename...Args>
requires AllDeceive<Pred_0, Args...>
constexpr bool fun(){return false;}

template<typename...Args>
requires AllDeceive<Pred_0, Args...> && AllDeceive<Pred_1, Args...>
constexpr bool fun(){return true;}

/**** Test ****/
static_assert(fun<int>());
```

## Implementation

```C++
template<template<typename...> class Predicate, typename...Elements>
concept AllDeceive = (...&&(not Predicate<Elements>::value));
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwDspK4AMngMmAByPgBGmMQgAMwAbKQADqgKhE4MHt6%2B/kEZWY4CYRHRLHEJKbaY9qUMQgRMxAR5Pn6BdQ05za0E5VGx8UmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnhzsmGgCC%2B4cA1ACSLGn0bIJMjbdH51c3p3%2Bn30uF0uBEwTwMoJMiTcoPB70wUJhAE80oxWJgAHRYqHYW7IAwKBS3ZTETD4USg0i3AgotFsLEY7AvRgEBQ44FoBhbNIEW6XWi0AAimC2eAAbphblDBbcIAzzMkFRAGKheSSyXgKQjoUywSy2YlsCAQGKxF5MMtllCrFdgb9/mc7UdbgAVTATIlfJ0Or22n7O9XoAD6Gk%2BjqusOe8MRNNRzHp2MNwImxC8DmJpODGmBJgCNsut0LtzmjmQeIEE0wqjSxFuMVQnlupu8ktzFioYiUucF1pzAR7iXz3oOGbJQa4YYOgMjEO1yLj6PlSauKbTasz477%2BaLxZapfLDEr1dr9cbzfNUrzHdoXf7vdtd8HOf9dyoXgYk7207BUch0NjdKYlilzEMABrYMCpIAI5eHgpJEvyQoipg4pzoGIZUiBYFLhBVyckeNZ1g2tC3G%2BDAQFaeakgQGwfteXZPnefogj%2Bs4xrS8ZARiWHgZBmAwXB7p8gKwqihKiLoRomGgQoOFSmYioKcJSFiWhG5cNJ2GJrhlz4aCx5EY2ZEUW21G0dSqbalYTFAi%2BI5uhMn6AiWmpBkwhLxAQ1Dvoi4QEDiFFWoOHCrLQnAAKy8H4HBaKQqCcG41jWMW6ybK2ZiJDwpAEJoIWrAA1iA4XJBiAAcyRSOFATJJIACciTVRl%2BicJIvAsBIGhSdFsXxRwvAKCAUk5TFIWkHAsAwIgIDrAQaReAQ5CUGgTx0PEkTopwqjlQAtDVtzAMgZZSBiZi8BqRDEHg6B6PwggiGI7BSDIgiKCo6gjaQugaQA7sQTBpJwPChRFUW5XFnAAPLzXNvKoFQtxbcku2SPth23MdZiyh4K30LW5iZcsvDDVoqwQEgy1pKtZAUBAFNUyAwBSGYfB0KCxADRAMRgzE4StEigO8DzzDEEiEMxNoIrDVly2vAQEMMLQ/MfVgMReMAbhiDeAukFgLCGMA4jK4JDioQNH1ViK83bFlfn1GDtB4DEf0ix4WBgwQl3tdwvASsQ9ZKMKetGA7Ri5asVAGGBABqeCYN9ENxtrt3CKI4hPcnr1qGDX36PrKBJZY%2BiOwNkCrKgPI5Gb20TOg0qmJY1hmD1vuXVgJcUT0ks5C4DDuJ4nR6KE4TDFUowacU2QCNMfjj5kk8MAsIwJBpdhdwI/RTP3BQr/Ua9NJMgzD4sY%2B2Af096HMbSL6Py%2BrAoqVbBIwMcJFpDdbwvUIzte0HUdkgnbKXAhASDyQJkTMOqwECYCYFgBIHdCqSESBieqARJAaEkGYSQyROrFVqs1DgrVSDtUSGYDEKQAilUSKVcK4UuANVqqVN%2BYNer9UGtlMOY1Jpk2mtDeai1aaoBxmtDaHBEbIzxAYIw6NaoYi4BiWK50SBXRurIe6adpAZyUFnD6uhma/X%2BgLZ%2Br937gw4FDWa81bhwy/kjPa%2BJ9bSNkfIrGgjKa41AWYQm7CRqk3Jq4qm/C6a4xQJIxmtUuBSRoLQNmHMuYfSFnzbWCSRZiwlg4bWMsWTy0VmDFWasNYCjNllXW%2BtDaxXwKSE2EozYKNUJbUE2tbZhQ%2Bg7J2fNXbbFih7PAXssq%2B39pgQOpTwigB8XwSOCgY5xwTowJOqjU6PQ0bITO71Yq6NzqHeuVhC6tPbmXCuFZODVwILXRIgotmN2bvEVu7p4B313ibZwEBXDnw0kPCoS89AT0aK89Ic9GjXyWDvXo68z5bxnp3R5%2B95hH0%2BSvMF%2BQIWX0Ph8m%2BT81gbEflwIxoMPqfzEXY0Jji5GhggEAi6oDsXgJ8ZA6BsDKAFQ6lJZphDiHhQxHVcKtUzDcoUqVOhNUmF4s4KwoaHDxpTRmjDQJ/jcbrTYJwVoLA9osAUGKMsYouAyNnBMM6%2BALrKI0snNRiznryC0asnQSRSD6IBt7HFQqeqQ14bDeGqgVVqo1VqjEOreQQGxm4%2BIoDEheOJqNbhQT4gyqEQkdVaQ0hBk1bVIMvqgzuo0azeIsTua8xFkk3NotxaSwyYI2W2SlblMwKrdWmsim8BKcHTp9bjaOGqWDC2yAraNMEHbFpjtnZIg6e7T22t%2BmZEGWCYZocxkRyYNHWO8dE7ezNSaiQSyXoWuzta0J%2BcG47OLncuKBzDycB2DXXd2yLBNw/i3K6tzS6QsaD3PuiLB690BSfb5ORflfrKLCtFwK94b3aOCi%2BDzGjAY/cvU%2BAxfnIqg%2Bi%2B%2BmLHoOpMfij16qmzet9YA/VID8ZUu8STWlMDRgdxZW1JIpCBUZTMHRrgpUNDJC5Y6j%2BIrbBsLDZaUgCCkF0OoRgxI4UmMZWqvgxIuKnV9SI3lfBp1WOmOpcR0gvssjOEkEAA%3D)

## Links

- [Source code](../../../../conceptrodon/mouldivore/concepts/all_deceive.hpp)
- [Unit test](../../../../tests/unit/concepts/mouldivore/all_deceive.test.hpp)
- [Example](../../../code/facilities/concepts/mouldivore/all_deceive/implementation.hpp)
