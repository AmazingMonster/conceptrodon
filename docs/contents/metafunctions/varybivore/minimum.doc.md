<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Minimum`

<p style='text-align: right;'><a href="../../../index.md#arithmetic-examinations">To Index</a></p>

## Description

`Varybivore::Minimum` accepts a list of variables and returns the minimum.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> min(V<sub>0</sub>, V<sub>1</sub>, ...,V<sub>n</sub>)</code></pre>

## Type Signature

```Haskell
Minimum :: auto... -> auto
```

## Structure

```C++
template<auto...>
struct Minimum
{
    static constexpr bool value
    {RESULT};
};

template<auto...>
static constexpr auto Minimum_v
{RESULT};
```

## Examples

```C++
static_assert(Minimum<1, 2, 3>::value == 1);
static_assert(Minimum<1.0, 2.5, 3.5>::value == 1.0);
```

## Implementation

We will implement `Minimum` using `std::ranges::min`.

Note that we are not instantiating `std::array` directly. Instead, we let 'Class template argument deduction(CTAD)' decide the correct type for `array`. [Check out this test to see CTAD in action.](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGwArKSuADJ4DJgAcj4ARpjEEhqkAA6oCoRODB7evnppGY4C4ZExLPGJXLaY9kUMQgRMxAQ5Pn5B1bVZDU0EJdFxCUm2jc2teVUKo30RA%2BVDXACUtqhexMjsHOYAzBHI3lgA1CbbbmLAJIQILCfYJhoAgjt7B5jHp03ETACet/dPjym6BAIE%2BP0OTGOAHYLFVDmYTFCACInKyPf5TJiOZAAfSYCiUzQgQJBClYmDxChObiw%2BwI3xSmAgTGWhxJoOIX1%2BpwiBFI8L%2B22wi1R/wxBGBHK5h1i0NhADpkvDFfztorESjtmiAQ9MdjKYSCMSJaTyZTqbTaPTGRBYqz2WDuTTVrF6KrBcLURxlrROIFeH4OFpSKhOG5rNY2at1m8djxSARNN7lgBrECBMzyqFmSQADlzgQ0AE4Mxp/LntvpOJJeCwkslA8HQxxeAoQMlE0HvaQ4LAYIgQKsCCkvHyKBA0CwUnQElFyZxVLn/ABafySQ7AZDIQ5SeVmXiYfBEYh4YFVfiCERidhSGSCRQqdRd0i6KoAdy%2BKU4PB9foDSZDTgAHlRxHAhDlQKhDkXFc1w3Lcd0kPdDggDwpxnYhjjMbYll4TstGWCAkEnad6DIccSIwkBgCkMw%2BDoAgEjbW0ANiCImm%2Bb9eDY5hiG%2BIDYm0TAHC40hJzYQQgIYWhOOfLBYi8YAzloWg224XgsBYQxgHEOS8GIYTHAAN0wNTg0wVRhNHTZ415GoANoPBYi%2BPiPCwACCBPOt1NIEziFidJMCRTAtKMRyjCTZYqAMYAFAANTwTA3yAxlA3jC9hFEcRbwyh81AA199G0lAI0sfQnLbSBllQFI6jU5cgROJFTEsawzCbPyTywSqIGWOxDKyFwGHcTw2j0MJZjKCp8nSTIBHGPwqgKOaGH6KaFk6AaBB6MZRomTaHG6aY1sGSoRl6Ba9ExZoTvmSo%2BujDYJF/Dh/VIRteGbaCl1XddN23XczBQ3BCBILCcMWPDIuWBBMCYLBEl60g00kNUi22KFJA0SQc38DQNECfwiyrDga1IOscPlfwuHLItcxpwJJC4QJ0f8d6AObVt2wTSKe37IjB1A0dyEoSiyLnNhOCaFgjKhZdIX2bSdyLeUuEVA8j0uM870y68JGkXKlHy59dDoj8mC/dSXrej7AI4EDh1HCCoOl2X5cORWjGV1XFRQtDSIScGzEhnmu0I4jUHQsiRYnSOA8SV25c9miiy4ZIaCtJjKFiVj2L40SeI4gShJEnzxMYAgpJkgD5MU5TVNEzTtN04N8AMw6TLMg9LOQazRLs31n0c5yOLczZg08vBvPjPyAqUYLQp0iJQDDvgYvixLktS0SMqvbKDdkPKn2DU2ioilqrDK4eeuq2qsnqxrtma0qLHaz7OtPUz4D6motr8CBXCXSqBNUop0ZqFCyEA1Is06i3WmpMX%2Bh1trTCgf1JB9RjqTTAZMFBe1FrnRulgu6z0VhrCeksEmNsOacAhMQGWcsFYGC9lwFWasNDA01phOMId8LJlILDeGQwkaDzJhTFW2MoQsyhFCbYONJBriqLbTmthua8MIvzJAQ4wIxzFrOecHBpZwRYAoIy24jIsPlAYRiUwNagy6noXeWUbwH3vEbY%2BOgQCVnNpbH8lD/zPmbA7MCztaEsCMSYsxFirGmXAqhOOGFwbbB4bzAWujyKi3iWREApiUgpBxOYosOJolTDxHQtc9FM7EGYjnZ8hd84%2BTqfxQShlRLl0ktJWSrdMAKSUmIBuPkm5hXHhpfSA1O4AQslZRi/dBD2SHk5Fy3wx4eS8qJWegUF7N2XrzaKTBYoJSSilRgO9ZB72cTrI%2BBVPFn2MC/cqsQb4hjvgINSAB6EkF82odQSF1L%2BVUDp1CGiNXI%2BCQFzHgdAiB808HgJWnAjaaC6g7RaDChBXRkG9HhWda6KKQVXUwaA4hFCFCPRvNbfxTYaGGPXMY0xhwCmWKxDEjhdjwa4VDgRGGcMEaUBeqIkAZgVbbG2IEQsTN8bCqhOWdmATOBcw7NDZGIBJBQj3JIrgUgiwSPRlwKEJNtgUs%2BnKjlfDB77hlZSlsJrFjLD8hkZwkggA)

```C++
template<auto...Variables>
struct Minimum
{ 
    static constexpr auto value 
    {
        []()
        {
            std::array array {Variables...};
            return std::ranges::min(array);
        }()
    }; 
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIGZmpAAOqAqETgwe3r4BwemZjgLhkTEs8YnJtpj2JQxCBEzEBLk%2BfkG19dlNLQRl0XEJSSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BzmgRHI3lgA1CaBbmLAJIQILCfYJhoAgjt7B5jHpy3ETACet/dPjwImBYqQMQJOZy8RAAdLCAGotPBMWL0BR/R7jYheByHACyETwLB8/xMAHYLMdHodqYdZo5kIc0AxxphVKliIcmFDUIcAG5iLxvf4047k4UimkmfxWfwAEQgS3FEtFVipyol43QIBAnx%2BnOIX2%2BKoRxCRKMwClh0LJspOqoe6olxEwBHWDFpBC1IC%2BRgt2pYEQguu%2BisC9sdNoVStFtrDlKepNj9v%2BAHoAFQZzNZlOpzMAFWwQjzmZzj3TWYrpYBDzpeGQAH0mAolK0IPiGITiacuKRDilDoFbtr%2Bd4hYFY7LDlxQ/baw2my2CG2CUSbt3oRpe2Zof5e4Ed0OQCPBe8J1ONzOOCtaJx/Lw/BwtKRUJw3NZrLS1hshWZAjxSAQmhXisADWATbqSZiSAAHNB/gaAAnP4ZgaAAbNBwQ3hwki8CwEgaJuD5Pi%2BHC8AoICboBj5XqQcCwDAiAgGsBCpFC5CUGgIJ0AkUSsFsqjQahAC0qGSIcwDIAyUjQmYvCYPgRCmlqPb8IIIhiOwUgyIIigqOo1GkLoPYAO5fKknA8Net73kBz6cAA8lCrEEIcqBUIcAnCaJ4mSVOkgyYcEAeFx9Acjs068FRWgrBASCcak3FkBQEDxYlIDAFIKQ0LQQLEORECxLZsQRC03wWbwxXMMQ3z2bE2iYA45WkJxbCCPZDC0GVBlYLEXjAGctC0OR3C8FgLCGMA4jdXgzoOHgvJ%2BgZrINVCWz/hEQJYU%2BtB4LEXzVR4WC2QQpp4SNpALcQsQZJgsrAhNO1GEBKxUAYwAKHCeCYMZ9mpIwTWqcIojiFpgO6WotlGfoE0oO%2Blj6Lt5GQCsqCpA0w1CZqJyyqYljWChvCoJdSl%2Bsj3QNQ0LgMO4ngdHoYQREMlQjD2RRZAIUx%2BKzGTsww8zDIkPZ2BTvQTG0tP5ELdQiwIfStPzzOC7YYuc3oszy4zCwsysChfpsEhWRwd6kERhOcB5gkiWJElSf5ZiBbghAkMcv4RQBz0rAgmBMFgiQKqQYGSPuCGBKSkgaJIUGoQR/ioQh%2BicDhpB4X%2B0KoVw6EIdBGf%2BJIXD%2BCHqEm7ZJFkRR7vUTFDGxUxTlsclqWhbxbCcC0LC8qSQlMIyBhGFOCHQlwG5yQplzKdpQMaRI0hg0oEMGboKSmUw5kjYbxum3ZHCOSxUKue5bcd13PcTf3g8boFwUJaFLuBGYSyRc9tFxagIUJOxKWv9fIyH53%2BwTVwBCXBNzZVyvlQqBlKqlSalA6qtV6qNXOi1RgBB2qdVsj1PqA0hpNTGg9LYT58CzUcAtYaT5lrIFWk1DadRbI7T2qVQ6BDIqnSapda6Sg7rjSMI9UAlc%2BBvQ%2Bl9H6f0Hz/kBupEGM9ZDg30k%2BRe0Mnq4ysPDehSN/ao3RpwTGnpsbKPxsRYmeAsDqJ1tLOazgICuFVj2Bm5QBZ6DZg0GxaQeYNAVosKWPRZYqwllzcmFjGhiw8SzZW/QXHqwGJrBx05VjrH1rErCG8S7m1/sff%2BfdAHnw0A7UeYVXYPwrtFT23tfaUENknFOA8I6kgLqSUkgRI6SFEj2TepdbDlyijROijFmLOQ/o3HifFW7EBYN5FgCheQMl5FksEFoCAjydkpPQEjgaaWkTpOecidAgGCMvVelkE5GxsgZEiO9nL731GMsSEypl8lmUwIE4xL5f0SrfQIhSukxRfm/JKHFXmhSPMgVIqR6wzIQvWOZ4xGyjNEnwOgYDKAQKfLArq/5UXwIpk1ZBbUOpdUIZgXq/UxA4POngnhzDSBEJFqQ2yFCqHnRoVtXg9D9rfCYcdVh512E3S4Q9CIfDooCKYO9T631fr/XOqsqeoMZFbMhrsxRxg4Y2DUfAFGaNsjDRTJqWGeNLAE2fEYkx6qAmUysdTFxdimaeNccUbILinHZBCUrYWgS5bizyP4t1DQPUurVr4r1Aa5jRMVgbOJ35w1JJOcRVJsKbmTOmQ8p5LkICO0UrfN2XySk%2BxGP7LClSkgD0CIEfw8E84ERLaSdCxdTmcDLpRD2AcQCSFJDJWpXApAIRqSHLgpIjmBBjWbUiRTgJHNkrW2NI7s0XQSJkZwkggA%3D)

## Links

- [source code](../../../../conceptrodon/varybivore/minimum.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/minimum.test.hpp)
