<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Maximum`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-maximum">To Index</a></p>

## Description

`Varybivore::Maximum` accepts a list of variables and returns the maximum.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (max) V<sub>0</sub>, V<sub>1</sub>, ...,V<sub>n</sub></code></pre>

## Type Signature

```Haskell
Maximum :: auto... -> auto
```

## Structure

```C++
template<auto...>
struct Maximum
{
    static constexpr bool value
    {RESULT};
};

template<auto...>
static constexpr auto Maximum_v
{RESULT};
```

## Examples

```C++
static_assert(Maximum<1, 2, 3>::value == 3);
static_assert(Maximum<1.0, 2.5, 3.5>::value == 3.5);
```

## Implementation

We will implement `Maximum` using `std::ranges::max`.

Note that we are not instantiating `std::array` directly. Instead, we let 'Class template argument deduction(CTAD)' decide the correct type for `array`. [Check out this test to see CTAD in action.](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGwArKSuADJ4DJgAcj4ARpjEEhqkAA6oCoRODB7evnppGY4C4ZExLPGJXLaY9kUMQgRMxAQ5Pn5B1bVZDU0EJdFxCUm2jc2teVUKo30RA%2BVDXACUtqhexMjsHOYAzBHI3lgA1CbbbmLAJIQILCfYJhoAgjt7B5jHp03ETACet/dPjym6BAIE%2BP0OTGOAHYLFVDmYTFCACInKyPf5TJiOZAAfSYCiUzQgQJBClYmDxChObiw%2BwI3xSmAgTGWhxJoOIX1%2BpwiBFI8L%2B22wi1R/wxBGBHK5h1i0NhADpkvDFfztorESjtmiAQ9MdjKYSCMSJaTyZTqbTaPTGRBYqz2WDuTTVrF6KrBcLURxlrROIFeH4OFpSKhOG5rNY2at1m8djxSARNN7lgBrECBMzyqFmSQADlzgQ0AE4Mxp/LntvpOJJeCwkslA8HQxxeAoQMlE0HvaQ4LAYIgQKsCCkvHyKBA0CwUnQElFyZxVLn/ABafySQ7AZDIQ5SeVmXiYfBEYh4YFVfiCERidhSGSCRQqdRd0i6KoAdy%2BKU4PB9foDSZDTgAHlRxHAhDlQKhDkXFc1w3Lcd0kPdDggDwpxnYhjjMbYll4TstGWCAkEnad6DIccSIwkBgCkMw%2BDoAgEjbW0ANiCImm%2Bb9eDY5hiG%2BIDYm0TAHC40hJzYQQgIYWhOOfLBYi8YAzloWg224XgsBYQxgHEOS8GIYTHAAN0wNTg0wVRhNHTZ415GoANoPBYi%2BPiPCwACCBPOt1NIEziFidJMCRTAtKMRyjCTZYqAMYAFAANTwTA3yAxlA3jC9hFEcRbwyh81AA199G0lAI0sfQnLbSBllQFI6jU5cgROJFTEsawzCbPyTywSqIGWOxDKyFwGHcTw2j0MJZjKCp8nSTIBHGPwqgKOaGH6KaFk6AaBB6MZRomTaHG6aY1sGSoRl6Ba9ExZoTvmSo%2BujDYJF/Dh/VIRteGbaCl1XddN23XczBQ3BCBILCcMWPDIuWBBMCYLBEl60g00kNUi22KFJA0SQc38DQNECfwiyrDga1IOscPlfwuHLItcxpwJJC4QJ0f8d6AObVt2wTSKe37IjB1A0dyEoSiyLnNhOCaFgjKhZdIX2bSdyLeUuEVA8j0uM870y68JGkXKlHy59dDoj8mC/dSXrej7AI4EDh1HCCoOl2X5cORWjGV1XFRQtDSIScGzEhnmu0I4jUHQsiRYnSOA8SV25c9miiy4ZIaCtJjKFiVj2L40SeI4gShJEnzxMYAgpJkgD5MU5TVNEzTtN04N8AMw6TLMg9LOQazRLs31n0c5yOLczZg08vBvPjPyAqUYLQp0iJQDDvgYvixLktS0SMqvbKDdkPKn2DU2ioilqrDK4eeuq2qsnqxrtma0qLHaz7OtPUz4D6motr8CBXCXSqBNUop0ZqFCyEA1Is06i3WmpMX%2Bh1trTCgf1JB9RjqTTAZMFBe1FrnRulgu6z0VhrCeksEmNsOacAhMQGWcsFYGC9lwFWasNDA01phOMId8LJlILDeGQwkaDzJhTFW2MoQsyhFCbYONJBriqLbTmthua8MIvzJAQ4wIxzFrOecHBpZwRYAoIy24jIsPlAYRiUwNagy6noXeWUbwH3vEbY%2BOgQCVnNpbH8lD/zPmbA7MCztaEsCMSYsxFirGmXAqhOOGFwbbB4bzAWujyKi3iWREApiUgpBxOYosOJolTDxHQtc9FM7EGYjnZ8hd84%2BTqfxQShlRLl0ktJWSrdMAKSUmIBuPkm5hXHhpfSA1O4AQslZRi/dBD2SHk5Fy3wx4eS8qJWegUF7N2XrzaKTBYoJSSilRgO9ZB72cTrI%2BBVPFn2MC/cqsQb4hjvgINSAB6EkF82odQSF1L%2BVUDp1CGiNXI%2BCQFzHgdAiB808HgJWnAjaaC6g7RaDChBXRkG9HhWda6KKQVXUwaA4hFCFCPRvNbfxTYaGGPXMY0xhwCmWKxDEjhdjwa4VDgRGGcMEaUBeqIkAZgVbbG2IEQsTN8bCqhOWdmATOBcw7NDZGIBJBQj3JIrgUgiwSPRlwKEJNtgUs%2BnKjlfDB77hlZSlsJrFjLD8hkZwkggA)

```C++
template<auto...Variables>
struct Maximum
{ 
    static constexpr auto value 
    {
        []()
        {
            std::array array {Variables...};
            return std::ranges::max(array);
        }()
    }; 
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQDspK4AMngMmAByPgBGmMQgZmakAA6oCoRODB7evv5BaRmOAmER0SxxCUm2mPbFDEIETMQEOT5%2BgTV1WY3NBKVRsfGJyQpNLW15nWN9A%2BWVIwCUtqhexMjsHOYAzOHI3lgA1CbbbmLAJIQILCfYJhoAgjt7B5jHp83ETACet/dPjwImBYKQMQJOZy8RAAdLCAGrNPBMGL0BR/R5jYheByHACyTFUeBYPn%2BJgCFmOj0O1MOM0cyEOaAYY0wqhSxEOTChqEOADcxF43v8acdycKRTSTABWKxSgAiEEW4oloqsVJVErG6BAIE%2BP05xC%2B31VCOISJRmAUsOhZLlJzVDw1EuImAIawYtII2pAXyMlp1LAJED13yV2wdTttiuVort4cpTwCcYd/wA9AAqTNZ7OptNZgAq2CE%2BazuceGezlbLAIedLwyAA%2BkwFEoWhB8YTiTdTlxSIdkodtrcdfzvELtnG5YOww6643m62CO2CUSST3oRo%2B2ZoVK%2B9sd8OQKPBe9J4OdzOOMtaJwpbw/BwtKRUJw3NZrLTVushWZtjxSAQmhXssADWIBStuARmJIAAcMFShoACcEEaAAbDB2z6Jwki8CwEgaJuD5Pi%2BHC8AoICboBj5XqQcCwDAiAgKsBApFC5CUGgIJ0PEkSsJsqgwahAC0qGSIcwDIAyUjQmYvCYPgRBmtqvb8IIIhiOwUgyIIigqOo1GkLovYAO5fCknA8Net73kBz6cAA8lCrEEIcqBUIcAnCaJ4mSYc0lmIcEAeFx9AcjsXCLLwVFaMsEBIJxKTcWQFAQAlSUgMAUjJDQtBAsQ5EQDEtkxOEzTfBZvAlcwxDfPZMTaJgDgVaQnFsII9kMLQ5UGVgMReMAZy0LQ5HcLwWCBkY4g9XgLoOHgvL%2BgZrKNVCmz/uEQI3gZtB4DEXw1R4WC2QQZp4aNpALcQMTpJgcrAoYwA7UYQHLFQBjAAocJ4Jgxn2SkjDNapwiiOIWlA7pai2UZ%2BgPSg76WPou3kZAyyoCk9QjUJWonHKpiWNYZjEZdSn%2BijXSNfULgMO4njtHooThIMFTDL2hSZAIkx%2BKz6TswwcxDAkvZ2BTPTjK0tN5ELtQiwIvQtPzzOC7YYuc3oMzy4z8ws8sChfhsEhWRwd6kERvAkR5gkiWJElSZIMmBbghAkMcv4RVFL3LAgmBMFgCSKqQYGSPuiHbAEkgaJI0GoQRUqoYhWEcDhpB4X%2B0KoVw6GITBGdSpIXBSiHqEm7ZJFkRRAEvbRDFxUxTlsSlaWhbxbCcM0LC8gEQlMIyBhGH5iHQlwG5yQplzKdpwMaRI0jg0okMGboySmUw5mjYbxum3ZHCOSxUKue5bcd13PcPf3g8boFwWJaFLvbGYkUV9RsXxagIXxOxqWv9fwyH53%2BwPVwRCXBNw5TygVIqBkqplWalAmqdUGpNXOq1RgBAOpdVsr1fqg1hrNXGg9KaT58CzUcAtEaT5lrIFWs1DatRbI7T2mVQ6mwnwnSJM1S610lB3Qmo9cIoAn58Hep9b6v1/oPn/EDdSoMZ6yAhvpJ8i8YbPTxlYBG9Dkb%2BzRhjTgWMvQ4xUQTIm8QSYaJ1tLOazgICuFVr2BmZQBZ6DZvUGxqQeb1AVgsKW3RZYqwllzcmFiGhiw8SzZWfQXHq36JrBxEUVhrH1rEraG8S6cANO3Tu3d/590AefDQDtR5hVdg/aKwFSBex9sMf2W0k4pwHhHAIBcAgBG2JHSQoleyb1LrYcuJTYrVyQMxZyH9G48T4q3YgLBvIsAULyBkvIclgktAQEeTslJ6EkSDTSMidJz3kToEAmFl6r0sgnZJBkSI72cvvNJUyZlzIWUwIEYxL5fySrfbYxTK41xGclDirzQpHmQCkFIDZ5mIQbIssYTYJmiT4HQMBlAIFPlgd1f8KL4EU2asg9qnVuqEMwH1AaYgcHnTwZNZhY0Zoi1IbZChVDzo0K2k%2Beh%2B1vhMOOqddh8ROG3XupNPhlc3pMA%2Bl9H6f0AbnQ2VPMGsjdlQwOUo4w8MbDqPgKjdGWQRqpi1HDfGlhCZm2JngLApiAmUysdTFxdimaeNcUULILinFZBCUrYWgS5bi1yP4t19QPUurVr4r1AbZjRMVgbOJ35w1JJsuc1JbdbmzL5A8p5LkICO0UrfN2j8Yqe29r7SghsamJAHtsbYUoEJ5wIqWgI6Fi6xtIt0yiHsA75Bkg0rgUhEL1JDlwIIW1tgxuIpwd2T9DayTrUOhtvTliXQyM4SQQA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/varybivore/maximum.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/maximum.test.hpp)
