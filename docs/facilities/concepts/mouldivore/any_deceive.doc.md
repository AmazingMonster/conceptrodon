<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::AnyDeceive`

<p style='text-align: right;'><a href="../../concepts.md#mouldivore-any-deceive">To Index</a></p>

## Description

`Mouldivore::AnyDeceive` accepts a class template predicate and a list of elements.
It returns true if there exists an element for which the predicate evaluates to `true` and returns false if otherwise.

<pre><code>   Pred, Es...
-> (...||(not Pred&lt;Es&gt;::value))</code></pre>

## Structure

```C++
template<template<typename...> class, typename...>
concept AnyDeceive = REQUIREMENT;
```

## Examples

`AnyDeceive` turns a fold expression of a class template predicate over `||` into a concept so that it can be used for subsumption.

Since `(...||(not Pred_0<***>::value))` and `(...||(not Pred_0<***>::value)) && (...||(not Pred_1<***>::value))` are both atomic.
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
requires (...||(not Pred_0<Args>::value))
constexpr bool fun(){return false;}

template<typename...Args>
requires (...||(not Pred_0<Args>::value)) && (...||(not Pred_1<Args>::value))
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<int>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwDspK4AMngMmAByPgBGmMT%2BAGykAA6oCoRODB7evv5BaRmOAmER0SxxCWbJdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHAD0AFSH%2BwDUysSY6AD6GsdH%2B7smGgCCBJgsKQavJgDMbgQAnilGKxMAA6cE/bCPJ6zYheBync5XDTQkwBKzPY5Y46zJiOZDHNAMWaYVQpYjHGKoTzHABuYi8mGOaIsVDESjRABEfhinlyeajngcjoiLpcuLcjg9nq93p9MD8/oDgWxwaDIdDYfCCKKrlxUejodicU18YSBCSyRSqTT6d4mSy2bQOQFud9efz3YKnsLDscqF4GJLDtKXm8PniFb8AUDmKrwU9iMAFBrnucAI5ePDnBTHCBqtFuQsQBioHVnMUo36J5OQkAgO2MlYraFEy3kynU2j%2BwMQFvo84ETZBp0cr2u72yiNfaPKuNghNJlPfKFpzCZ7OYXP5iEBIt7ktl3XXRU15fYeuNzDN5nVcyJPMFvfF0vlpHi09LusNhnXlvPNtXitTsaQDBg%2BxZQdh2OAg4SjKwJ2eaFfROAAVLcdTuUNdl2Y5sGIYgSE1U08GQS4mAUJQWmoQNFXCAhIT7Ft3Q4NZaE4ABWXg/A4LRSFQTgi0sawcQ2LYHTMb4eFIAhNFYtYAGsQA4xJQQADkSKQOICRJJAATm%2BHTJP0ThJF4FgJA0DRSB4viBI4XgFBAazZN41jSDgWAYEQEANgIFIvAIchKDQd46HiSIQU4VQNIAWl045gGQAkpFBMxeAuQgSDwdA9H4QQRDEdgpBkQRFBUdQ3NIXQuFIAB3YgmBSTgeDYzjuLk/jOAAeUCgKdVQKhjhixJ4skRLkuOVKzDzDwwvoClzCklZeFcrQ1ggJBQpScKyAoCBtt2kBgCkMw%2BDoV5iCciAYk6mJwmaf4Wt4e7mGIf5upibQ6lc6TQrYQRuoYWgnqqrAYi8YA3DEZ1ntILAWEMYBxDBzd6lpLdOtJOpAp2aT6O6TraDwGJGvejwsE62C8As7heAx4gqSUTk3iR4mjDktYqAMZMADU8EwOrutjOH8uEURxBKsXyrUTqav0JGUGsax9BJpzIDWVAUl6JyOFi2Z0B%2BTlTGEywzDshniByzGNa6HoshcBh3E8do9FCBZykqPRCkyAQpj8Wqfd6IZPdGWranqAR%2BkmF28nD7ofoaOYQ5GBJw7mf29FxFoU6WNO1gUMTtgkNqOC4mzOvs4a4oSpKUskNK81wLLFskrgVpkzm1gQTAmCwBI%2B1IJTJG%2BUEDICSQNEkMxJESKyVL0kyODM0gLO%2BMxQW%2BRIAjU741I4jiuEMvS1Irqr7Mc5zO7cjbvM23y%2BsC4KDtQeaIqijgRrGwkDCMKa9NBFwUEfFMpECtrlWqYtCqS2kNLJQssqq6DOg1Jqz1S7l1srweyvV/KBWOINauo0ErIF/sAf%2BgDgGzVfjtBat514dzWu5e%2Bh0FrPxYaMEhSMuB6S4NZGgtBLrXVulVV6j04aiPep9b6Dg4b/UYAQIGINOrg0htDWgsM6bw1ZkYFGfF8DnHRpjKq2NkC4zhgTdiVViak0ehTHYfFqa02kgzJmmAWaIx0eEUAN8%2BA8wUPzQWwtGCi1kNA4qsDZAy0qnxJBCsOYmysJYVWMR1aDy1jrTg%2BsCCG2%2BMbZWZsLbxHATbQeEdeiO2drkAOwQna5y9oHdIvtsix2qUHLIdSw520TlHDOLSs4J0jn0ZOHtU5Z16VUsZAwOn53WJsYu7cl4YMrpwQh39OF/24RQm4EBm5gLoe3VaXdSA9z7qMQeSleHWUsSvNeHFQT6Q4npMwTzqhqSPrpM%2BdlOCXxcpzDyd8kB%2BX6mw6hu1IpsE4M0FgCUWAKFpASWkmz5SzAyvgMBOU8qhIluE0q8h4HRJ0CAb49VGrNTpugjq58eqPwGkNVQMK4UIqRZGWYVC36t2%2BN8BhfzmGgtYftdhCR4UpBSJcRFelLjIoIJcelsCLrxCEXdB671xHKo%2Bl9H6sjX4AwUcDUGejMAQyhjDXW0kEZs3sbwfRicMa6xAaoHGrxzGCEJlYkmZN/h2KplbJx9N4iuPcWzLxfzuZMD5gLIWItNFQOxRICJZV8VyyJXE4w%2BSbDWNSZrbWWRda7ANkrU2FhzZYMttbTNXTBkVMzrVd2ZRRkNKKFkatqRGnBxGXnfp9sekDGbWUpOUz231PGD2vp6cB11o7QswuczioUs%2BVglZsrjiwvhXSZlrxWU7LRSQfZ3Kb7d17v3SgpcblEo3u8ySZgr1cDUhoRIjz51dQcrYK%2BjDmxDxACPQBe8OLT2%2BBxO9kkdJL2%2BJSr5z632l3So%2Bi%2B191prAZhkZwkggA%3D%3D)

By turning `(...||(not Pred_0<***>::value))` and `(...||(not Pred_1<***>::value))` into concepts, we allow compilers to perform proper subsumption.

```C++
/**** fun ****/
template<typename...Args>
requires AnyDeceive<Pred_0, Args...>
constexpr bool fun(){return false;}

template<typename...Args>
requires AnyDeceive<Pred_0, Args...> && AnyDeceive<Pred_1, Args...>
constexpr bool fun(){return true;}

/**** Test ****/
static_assert(fun<int>());
```

## Implementation

```C++
template<template<typename...> class Predicate, typename...Elements>
concept AnyDeceive = (...||(not Predicate<Elements>::value));
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwDspK4AMngMmAByPgBGmMQgAMwAbKQADqgKhE4MHt6%2B/kEZWY4CYRHRLHEJKbaY9qUMQgRMxAR5Pn6BdQ05za0E5VGx8UmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnhzsmGgCC%2B4cA1ACSLGn0bIJMjbdH51c3p3%2Bn30uF0uBEwTwMoJMiTcoPB70wUJhAE80oxWJgAHRYqHYW7IAwKBS3ZTETD4USg0i3AgotFsLEY7AvRgEBQ44FoBhbNIEW6XBhIgAimC2eAAbphblDBbcIAyTAE3Aq3BAGKheSSyXgKQjoUywSy2YlsCAQGKxF5MMtllCrFdgb9/mcHUdbgAVTATIlfF1On32n6uzXoAD6Gk%2BzqusOe8MRNNRzHp2ONwImxC8DmJpNDGmBCrtl1uRduc0cyDxAgmmFUaWItxiqE8t3N3kl%2BaoYiUCsFtrzAR7iQLvoOWbJIa4EYOgOjEN1yIT6PlKauaYzGuz477BeLJZaZYrDCrNbrDabLctUoCFg7tC7/d79vvg7zgbuVC8DEne2nYJjkOh8Z0piWKXMQwBGtgwKkgAjl4eCkkS/JCiKmDinOwZhlSoHgUukFXJyR61vWja0Lc74MBANpXqSBAbJ%2BN5ds%2B94BiCv6znGtKJsBGLYRBUGYLB8GenyArCqKEqIhhGhYWBCi4VKZjJOYyQich4noRuXAyThyZ4ZcBGgsexFNuRlH5jRdHUumupWMxQKviOHoTF%2BgKltqIZMIS8QENQH6IuEBA4pRNqDhwqy0JwACsvB%2BBwWikKgnBKpY1glusmxtmYiQ8KQBCaGFqwANYgJFyQYgAHMkUiRQEySSAAnIktVZfonCSLwLASBo0mxfFiUcLwCggNJeVxWFpBwLAMCICA6wEGkXgEOQlBoE8dDxJE6KcKolUALR1bcwDIOWUgYmYvBakQxB4Ogej8IIIhiOwUgyIIigqOoY2kLoWkAO7EEwaScDw4VRTF%2BUJZwADyi0LbyqBULcO3JPtkiHcdtynWYsoeGt9B1uY2XLLwo1aKsEBIKtaTrWQFAQFTNMgMAUhmHwdCgsQQ0QDEEMxOErRIsDvB88wxBIlDMTaCKo05atrwEFDDC0ILX1YDEXjAG4Yi3kLpBYCwhjAOIqtCQ4aFDV91Yiot2w5QF9QQ7QeAxADYseFgEMENdnXcLwErEA2SjCgbRhO0Y%2BWrFQBjgQAangmC/VDCa6/dwiiOIL2p%2B9agQz9%2BiGyg1jWPoztDZAqyoDyOQW7tEzoNKpgpZYZh9f711YGXlE9NLOQuAw7ieJ0eihOEwxVKMWnFNkAjTH4k%2BZNPDALCMCRaXYPcCP0UyDwUa/1BvTSTIMo%2BLBPthH7PehzG0y/j6vqwKOlWwSKDHDRaQvW8P1SN7QdR0nZIM6spcCEBIApImJMI6rAQJgJgWAEhd2KpIRIGJGoBEkBoSQZhJDJG6qVeqrUODtVIJ1RIZgMQpACOVRI5VIqRS4E1eq5UP4Q36oNYauUI4TWmhTWasNFrLXpqgPGG0tocGRqjPEBgjCY3qhiLgGJ4qXRIDdO6shHoZ2kFnJQOcvq6FZv9QGQtX7v0/pDDgMN5qLVuAjH%2BKMDr4kNrI%2BRiicbCOpvjcBZhiacLGuTSm7iaaCIZvjFA0jmb1S4NJGgtAOZcx5l9EWAtdZJLFhLKWDhdZyxZIrZWEM1Yay1rQHWvs9ZgkNsbeK%2BBSRmwlBbJRqhragl1vbCKX0nYuwFu7bY8UvZ4B9jlf2gdMDBwqeEUAfi%2BDRwUHHBOSdGAp3UenZ6WjZDZ0%2BvFfR%2Bdw6NysJYEuMRO4VyrpWTgtcCD10SIKXZ1gW5fzbjdT08AH77zNs4CArhL5aRHhUFeegp6NC%2BekBejRb5LD3r0TeF8d5z27m8w%2B8wT5/LXtC/IsLr7H1%2BXfF%2BawNjPy4CY8GX1v4SIceE5xCjwwQBAVdcBBLIF%2BOgbA%2BBlAipdWkm04hpDIoYgapFeqZgBWKXKgwuqLDiWcHYSNLhk0ZpzThsEwJ%2BNNpsE4K0FgB0WAKDFOWMUXA5GzgmBdfAV1VFaVTholZr15A6I2ToJIpBDFA19oS8VfVob8PhojVQmrtW6v1RiQ1vIIC4w8fEcBiQfGk3GrwkJ8RFUiISDqtIaQQx6vqiGINIYfVaPZvEeJvN%2BZixSUW8WktpZZOEfLXJKsqmYHVprbWFscr6wqT03g1Se51IhlbZANsWmCAdu052rskTdM9t7XWQzMgjPKaHcZXCo5MFjvHROydSkWuWRIVZb1bW5wdeEwuTcbAdKOQlE5h5OA7DrkevZFg7kJQeR3Z5cLGh9wHmi4e/cwVnwBTkIFf6yhIuxRCg%2BW92gwqvq8xo4Gf2r3PgMIFGK4M4sfni56rqzEkt9Tq5sAag3AJNWAwm9LfFkyZXA0YXdOUdSSOQ0VWUzBMa4OVDQyR%2BVuq/pK2wHDo3WlIEglBDDaFYMSJFNjWVaqEMSES91A0yMFUIedTj5iGXkdIP7LIzhJBAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/mouldivore/concepts/any_deceive.hpp)
- [unit test](../../../../tests/unit/concepts/mouldivore/any_deceive.test.hpp)
- [Example](../../../code/facilities/concepts/mouldivore/any_deceive/implementation.hpp)
