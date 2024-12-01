<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Deceive`

<p style='text-align: right;'><a href="../../../index.md#conceptualizations-3">To Index</a></p>

## Description

`Varybivore::Deceive` accepts a callable predicate and a list of elements.
It returns true if the predicate invoked by the value results collected from the elements returns false and returns false if otherwise.

<pre><code>   Predicate, Elements...
-> not Predicate(Elements::value...)</code></pre>

## Structure

```C++
template<auto, typename...>
concept Deceive = REQUIREMENT;
```

## Examples

`Deceive` turns a callable predicate into a concept so that it can be used for subsumption.

The following code will fail since `(not Pred_0(*))` and `(not Pred_0(*)) && (not Pred_1(*))` are both atomic:

```C++
constexpr auto Pred_0 = [](auto...){return false;};

constexpr auto Pred_1 = [](auto...){return false;};

template<auto I>
struct Monotony
{
    static constexpr auto value {I};
};

template<typename...Args>
requires (not Pred_0(Args::value...))
constexpr bool fun(){return false;}

template<typename...Args>
requires (not Pred_0(Args::value...)) && (not Pred_1(Args::value...))
constexpr bool fun(){return true;}

static_assert(fun<Monotony<1>>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwArKSuADJ4DJgAcj4ARpjEEgCcpAAOqAqETgwe3r4BwemZjgLhkTEs8YlcKXaYDtlCBEzEBLk%2BfkG2mPYlDE0tBGXRcQnJts2t7fldCpNDESOVYzUAlLaoXsTI7BxoDHOYqqnEANRMXkSnysSY6AD6Gqcm/gAiz4FWga8QF0QAdIDViYAOwWW4ELYMU5UMRKF5WEGvBEmDQAQVRaP2h2OZz%2BqGutweXGebw%2BXx%2B%2BMB/2BYIhUJhcMwKKRKPRmIImBYqQMnJebnxpwAki9sJi5sQvA5TgBZASoIgMACemNBVnRp01pzmTEcyFO2M5uPOlwJADcxF5MM8wSLWf51Rj7Y6OVyebrmf43AQlalGKxMNS0cRgApRZjbgBHLx4W4KU4QBgKwl3R4QYOhkAgC3eQNA4How1HE6nWKoTwwrwMCC08GYSHEaGw2jwh2g5Hs9Gc7m8z3e33%2BthBkNh/xi9FRmNxhNJggph4adMjrM5q3U1arZ5mABs5m3M%2BTN1TXCXmezlrzNILWIEOJLZYrVCrNbV9MbpwIks9iI7GPROr1e4mAUJRWmoKt%2BTlWcBBVL0uHDMca2BB0OHWWhOECXg/A4LRSFQTg3GsaxtU2bZrXMfweFIAhNFQ9YAGsQECbd/gADm3KRAhBbdJCSfxuLMfx9E4SReBYCQNA0UhsNw/COF4BQQCkmicNQ0g4FgGBEBATYCFSS5yEoNBuToBIogDThVHYgBaHjTmAZB9Skf4zF4O5CBIPB0D0fhBBEMR2CkGRBEUFR1FU0hdC4UgAHdiCYVJOB4NCMKw2i8M4AB5S59LnVAqFOKzt1syR7Mc05nLMBMPBM%2BgzgorhVl4FStHWCAkGM1JTLICgIE67qQGAKQzD4OhOWIRSIFidLYgiFolSS3hZuYYglUy2JtHqFSqOMthBEyhhaAWiKsFiLxgAFWgW0W0gsBYQxgHEE7Yy2vAzUwRSIqOepLl2KiIk5dCItoPBYni1aPCwdLPzwcTuF4d7iDLJRXi5B6QaMWj1ioAxQwANTwTAYsyv1sKo3zhFEcQgop0K1HSqL9AelAiMsfRQcUyB1lQVI%2Bk%2B6y5nQF5XlMSxrDMWTEeILyPvgdY6gaZwIFcaY/GisJFgqKo9CKLIBFVnWMj1hhhi1lZul6Rp5gN6KFb6AZWlN0ZqgmQYbddx3NediR5dInYfeEjhMOk9K5MKmy7IcpzJBchNcA8%2BrBMa5qsfWBBMCYLBEhrUhGMkfx/j4kFJA0SQzEkbdJOYlIgdE0hxMo/4OO3ViklYrht0CSQuECPjtxDiK5IUpTqKx9StPanScoM3r%2Brq8y2E4FoWDNEFrKYA0DCMCqkn%2BLh/lw9yiGl7zoop/zqekWmlHpiLdBGuKEsWlKg7SwesunvKCuX1f183h6d57wPtVVAtUEhbn8GYJqo9VJtQ6qArqdVDJ9QQQNH%2Ba9kBbyGkkLgUkaC0HGpNaaEVlrzRuqQ1a61NoOBurtRgBADpHXSqdc6l1rrw1umjIwT1cL4FuA0d6n1D6qB%2BpyG6AMejpRBmDeakNdi4RhnDKiiNkaYFRvdbhERQCwL4LjBQBMiYk0YDdc%2BVNApX1kHTcKuF75M0xqLKwbNpGcxzjzPmnABYECFm8Bx4tJYJBPrLLmFtXpKxVp4DoegNblG9tFXWfR3bxOyE7ZYLs7ZWzdhE/ItseihP6PMFJ2tbbWyyWrD2CwYmpIDgoP2gUX7BxkrwMO6C/6YIATUIBTwIDx2PhA5OMDWppwzlnSgL864N13qXEEvcQQgn8GXCu3cB6yU4MPZSY8NLaV0rlZBc8zIWQ4MvOyLAFBmn1GaDpvY5huXwMfLyPlZAX3McFeQN9rE6ACLFeKiV4b1Lfisjg2U9KXFOPlc4xAWDHNOecy5Ho5ggLAYnfw/hoEtTUpPPZPUjKoLqtmZAqRUj3AuUke4VyCBAQhTxUaBCEhEJmnNVa5CGVrQ2ltWhoC9oMMOsdXhmAzoXTEOwqid10byN4Hw16gj0rfWQL9cRghJHA1BuDJUcjobSyUQjBIqj1Hoy0WPHGTB8aE2JqTExjyzESAsSFN5DNPlYJZmLJxHM5Z4V5tkT6AB6QWjrHEWAlk0qWMsXHy1yYrPwysGDuFKVEqNhTzZJP1jGuJRs%2BjxrSWG%2B2JS8hlPSQIB2FSlhFPKe7HUntKlFN9lsf2jVA4NNDpwcFkLSonLOacYl/wyVx1uSQPpqLU6kHTpnMYOda5iRAGYXeyLAiBFLrgjQyLuKsWWU01ZtgR5oo3LnEA%2Bc97%2BFYl3QSs7tyCW4oHfw/zV3yQGXRQOrkV0ZWvZu9YiNMjOEkEAA%3D)

By turning `(not Pred_0(*))` and `(not Pred_1(*))` into concepts, we allow compilers to perform proper subsumption.

```C++
template<typename...Args>
requires Deceive<Pred_0, Args...>
constexpr bool fun(){return false;}

template<typename...Args>
requires Deceive<Pred_0, Args...> && Deceive<Pred_1, Args...>
constexpr bool fun(){return true;}

static_assert(fun<Monotony<1>>());
```

## Implementation

```C++
template<auto Predicate, typename...Elements>
concept Deceive = not Predicate(Elements::value...);
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwArKSuADJ4DJgAcj4ARpjEIGYAbKQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCUmpCi1tHQXdEwNDldVjAJS2qF7EyOwcBJgsaQa7Jv5uTF5EANTKxJj4orukFwQAnmmMrJgAdN/Y9GyCCmO2BMGgAgmgGFs0gQLgARTBbPAAN0wF2OsIuDFQMOutzw90wEF%2Be0YBAUIBASLEXi%2B32WxysYJBoIA9AAqDmcrnclnM9mci4AFUwEwUFy5vLB/O5Mo5ktBzIhE0wqjSxAuZ0uuPQAH0NGj/BiTIErIFYRBNahvp96QB2Cw3AgbBgXKhiJQMky22GeplgpW7VXqy1XG66rgGo0m43my3Wu0OzBO4gut20D3%2BKze30KsG7faHTDHU7nVAXACSQOZE2IXgcFwAsgJsQJnsyvYzQRduxc5o5kBcAyq1RrSxcqd5UR3K9nM%2B3Z53mfmDkwjicXm9mGxraDiMBAf5gWCbgBHLx4G5i%2BGIlHF7V6x67/fWqv%2BgTKoMXWKoTyurwMCAE0dZ1XXdIs52zP1QWXQtiw3d5t2%2BJ8DyPXdMDPC8RThBFMGRcC3HvDRHz3BQX0PNEUnMZJsJvfD7y4Yjn2%2BV9wXfQMR2/X8qH/QCO2AlMnlrcCsx9KC%2B3xHUmAUJQ2mof9iybLEiAYNsTi4KtD0A%2BlMw4VZaE4QJeD8DgtFIVBODcaxrF7dZNinMx/B4UgCE0XTVgAaxAQJJE%2BDRJC4W1/A0QINBSZIzAADgi/ROEkXgWAkDQiOM0zzI4XhySIlyTN00g4FgGBEBAdYCDSc5yEoNB9joBIog%2BThVAi5IAFpkkkC5gGQAcpE%2BMxeDxIhiDwdA9H4QQRDEdgpBkQRFBUdQctIXQGIAd2IJg0k4Hg9IMozXLMzgAHlzjKmFUCoC5GpatqOq6i4erMC4IA8ar6HVcxHOWXhsq0VYICQKq0hqsgKAgQHgZAYApDMPg6F2YhyQgWJ9tiCJWmeLbeFR5hiGeQ7Ym0BFsqcqr/gIQ6GFoDHFqwWIvGAU5aHTTHSCwFhDGAcQacwhw8PJRaVQRc5ticiJdn0xbaDwWJ1txjwsH2gghoS7heBRYhvyUeF2aMKWjFc1YqAMfcADU8EwFbDs3FmxuEURxGm225rUfblv0DmUCsyx9Gl8lIFWVBoRyfnmomdB0VMSxrDMVL1aGrA/cAnoiZyFwGHcTxOj0MIImGKpRgY4psgEaY/ELzJi4YBYRkSBi7BTgR%2BimTOCjr%2BoG6aSZBlzxYC9sLvS70OY2mr/Pa9WBRbK2CQdo4QzSBS3g0suprWvazrup8x6iXwQaKM%2B76DdWBBMCYLBEiTzzJH8T4AE5/FtSQ/LMSRkiSwJklvmKODi0gEscz4yQuDJAirfCKwDvJcECPfVIi8DrpVsCALKBs8qFX%2BsVE65VQbgzenVNgnBWgsCRLaZqTBBwGCMPdW%2BnwuC%2BX6rvEgw1RqyAmg7aQTslAu0WroGGa0NqY1nvPOBaVjqlXOBcc6GpiBEJIWQ5AFDgBUJob5J6L0gZvX3mYL6zkUHoJwQkCqYNUCvVGIQ4hzV5Ecy4LfLgREaC0HhojZGi1sboxZq43G%2BNCYOBZqTUkFMqb7VpvTRmzNVasz2BzLmpl8A3F5iifmplBbIGFizMW9R9pSxlujeW2xTJKzwCrJy6tNaYG1lEiIoAcqG2NgoM2FsraMBtiw%2B2U12GyGdgtUyPD3b60jlYb2WTE4ByDu%2BTgocCDh0NP06OscEjxxFPACe7debOAgK4QeDEc4VBrnoIujRNnpAro0UeSw269EbgPFuZdk6rM7vMHuuy65XPyDc4e3cdljxnmsDY08uCCL2otZeZjZHkI5ko2h%2Bod6EBIPvf5h9qnH1PufSgs9f7/2oX5W00DbSBUkC/NqDFhGcAykgnR1TUHwHQSVU6hj9HEDwdsQhN0WAKCRAOJE1jPiFgmPQmF8dmHjVaRIdps1OFdJ0AEUgfDNqqwBQvfaIjMFnQusy9qrL2Xji5TymEz1jHqISPvfw2ifq5T0fq4GdKLVvUpMgNIaQdSctvjqHVklpFtVhg4hITiUZo1xu4v1eMCZE18cYsmATqYxMwHTBmYgwlOTZlEvJvBYkpwSftZJqTwnpIlqZLJstni5MVsrFmJTMhlMibrSpKCjZMFNubS21twm21YW0ma8hxWuylQoz2UdBm%2ByWWZUZDB%2BYsjDr2gZFgY5LzjsNRZ/tbmNDThnV52d06nL7vsnIhyt1lEeV885Hcm7tGuUPFZjRj0btrv3AYhz3lXu%2BZPX5U15XEo4FIlgLK2Ucu1auEUurcD8rhSao%2BpAT5n1GEnCW6KkjUP8EEEK/kkrwdtCAhVQKSWIOQYi0gV9Ah30CBFFIt9JC30Cg/Lg/hv7%2BEBalTDprlizz6uhujCCGOrHVlkZwkggA%3D)

## Links

- [source code](../../../../conceptrodon/varybivore/concepts/deceive.hpp)
- [unit test](../../../../tests/unit/concepts/varybivore/deceive.test.hpp)
