<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Falsify`

## Description

`Pagelivore::Falsify` accepts a class template predicate and a list of variables.
It returns true if the predicate invoked by the variables returns false and returns false if otherwise.

<pre><code>   Predicate, Variables...
-> not Predicate&lt;Variables...&gt;::value</code></pre>

## Structure

```C++
template<template<auto...> class, auto...>
concept Falsify = REQUIREMENT;
```

## Examples

`Falsify` turns a class template predicate into a concept so that it can be used for subsumption.

The following code will fail since `not Pred_0<*>::value` and `(not Pred_0<*>::value) && (not Pred_1<*>::value)` are both atomic:

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

template<auto...Args>
requires (not Pred_0<Args...>::value)
constexpr bool fun(){return false;}

template<auto...Args>
requires (not Pred_0<Args...>::value) && (not Pred_1<Args...>::value)
constexpr bool fun(){return true;}

static_assert(fun<1>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwCspK4AMngMmAByPgBGmMT%2BXKQADqgKhE4MHt6%2B/kGp6Y4CYRHRLHEJZkl2mA6ZQgRMxATZPn6Btpj2RQwNTQQlUbHxibaNza25HQrjA%2BFD5SNVAJS2qF7EyOwcBJgsyQa7JgDMbkxeRAB01yfYJhoAgjPEXg4A1MrEmOgA%2Bhr3DxMAHYrI83uC3jMmI5kG80AwZphVMliG8YqhPG8AG5iLyYN7AixUMRKYEAEROoMBQIpxypAN2%2B0OmBOZwuqGul1uAOerwIHy%2Bvy4AMJAIhkMaMLhAkRyNR6MxOO8%2BMJxNopJplJFmrpIsejIO0JZp3OV2uD2IwAU3MeXwAjl48F8FG8IAxUPzPt8/qyLVbObcQCAlXjlgD4bKUWiMbQ3lQvAwIGGQV8CBsGHGScarJrHgy9oajib2Zy/dbjndbZgHU7MC63R6Bd7/qcywGK0GQ5hlgSzAA2cx913uz2Cn7C1uWhTt7Cd3Hd8My3Zy6OY%2BOJ5MWVPpt4EF7Z8l6p6SvDIH5MBRKZrUBOsifYJNhukcVa0TgBXh%2BDhaUioThuaxrEhdZNhVMxjh4UgCE0F9VgAaxAAI%2B0uAAOPspACIE%2B0kABOY4sPA/ROEkXgWAkDQNFIL8fz/DheAUEBKOg78X1IOBYBgRAQHWAhkguchKDQfY6HiSJWG2VQ0IAWmwt5gGQWEpEuMxeG%2BQgSDwdA9H4QQRDEdgpBkQRFBUdQWNIXQkgAd2IJhkk4HhX3fT8YN/TgAHkLj4/lUCoN5JL7GTJDkhS3iUsxXQ8YT6FRcwIOWXhmK0VYICQITkhEsgKAgdLMpAYApDMPg6F2YgGIgGJXJicImgATwc3hquYYhavcmJtFqZjIKEthBHchhaHq8ysBiLxgDOWh1Qa0gsBYQxgHEYbazqLE61cpFagubZIPCXY33M2g8BiWyWo8LBXL3PAyO4XhVuIdElDJPZ5sOowYNWKgDCtAA1PBMCs9zkkYaadOEURxEM0GTLUVzLP0eaUEAyx9COhjIFWVBkh6BiOCkmZ0BOMlTEsawzBou7iE0tb0c6bpMhcBh3E8No9FCeYygqPQCgyARJj8JJuZ6QYOZGaouk6%2BpZj5vQajqAQ%2BmaYXhgSaopeZ3JVf6JXFhV1YFBArYJCcjgPyo1zaP86TZPkxTJGU11cHU2LwK4BKoPe1YEEwJgsASJNSAQyRjkuPCgUkDRJDMSQ%2BwopCcKIjgSNIMiIMudC%2BxQnCUK4PsAkkLgAjwvszfM2j6MY92WJSzjUu4rz%2BOy3KYrEthOCaFgsSBKSmDhAwjDCnDLi4S4fzUohKa0pJQb0iHpChpQYfM3QipsuyGuN03qN4WjPN4i43l8t52877ve/mgeh5HyLUGi%2BJe2OMw3aS1ja6b%2BIBJym%2BMpikBj675A%2B4FRwlwSiNBaClXKpVcyTU6rTRgS1NqHUHDTR6owAg/VBquRGmNCaU0bozWekYRaP58BfBWmtcyG1kBbWmrtLorlDrHTqmdbYP5LrXUgndB6mAnpzSIeEUAVc%2BBfQUL9f6gNgb4OnuDAyc9ZDQzMj%2BZe8M3rEysMjRhaN/aY2xpwPGBACbHCJkjCwZNt4UyplovW4s5Z%2BAgK4aWSQ2alGVlzNIPMsjq35ikdxQt2auLFnTeWascjeNlj0BWcwXE6xliElmmtFb%2BJia7NYGxDYpP2pvc2nAj7EA7l3HuADz5cEHsPDQDt8Dj3vq7RKHtSBex9iMf2%2B0k4p0HhHIEhcgRAmOJHaO%2BcS40U4OXJi702I1yQDxbyH837EBbtsduskWAKCxLCLEJTLjMhmKpSpGlJ5GTBvpCQcjjIL0UToEAxxSCr3sjdDeLlS4eXrj5PyizgrLNWdiDZWz%2BQQCit/O%2BcVjhPzGa/L%2BmUZngp/qs5IyQfjrJwj8H5548nYWKuA%2BIkCqo1RanAnFrV2qdRQTfXq6CBpDRIZgUa40xB4MgrNF6rDeCkIlqtHGo9VCbV2LQwQ9CDpHROrVFhF1KYcNuvEbhvCXoCLGZ9JgP0/oAyBl%2BSC0ijmQ3kWc2GlyVHGBMSjGIVjfxY0yDjAA9PjRGJNLBmN/BYrARrwn03sYzRxwRGba05gLXxmQ3WC0yJ60WtMJbBP6G6p1obEnRK9WMMNXjYlaySV6vWBsDL3MGdvHJby3gfLWd8o0MwKlO2qSCquntva%2B0oMbVp/hB7HGOAEAIEcQEaHrVhFCGa3J0VsBXZ%2Byx4IgCDkPY4KE87gSbX2cCWEE7HAeUM7tfbjYqU7WXSuyVVh3XSM4SQQA%3D)

By turning `(not Pred_0<*>::value)` and `(not Pred_1<*>::value)` into concepts, we allow compilers to perform proper subsumption.

```C++
template<auto...Args>
requires Falsify<Pred_0, Args...>
constexpr bool fun(){return false;}

template<auto...Args>
requires Falsify<Pred_0, Args...> && Falsify<Pred_1, Args...>
constexpr bool fun(){return true;}

static_assert(fun<1>());
```

## Implementation

```C++
template<template<auto...> class Predicate, auto...Variables>
concept Falsify = not Predicate<Variables...>::value;
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKzSrgAyeAyYAHI%2BAEaYxCBmpAAOqAqETgwe3r4B0ilpjgKh4VEssfGJdpgOGUIETMQEWT5%2BgbaY9oUMdQ0ExZExcQm29Y3NOW0Ko31hA2VDZgCUtqhexMjsHASYLEkG2yYAzG7bu/uYR25MXkQAdPdH2ADUyAYKCk/KxJj4otukT2ud3uADUGngmNF6ApHiYNABBNAMDZJAhPABiYjSVAAnk8jgARJ4MVBor4/PB/C7HMHECFQzAKe63R4gEAANzEXmpVgRcPhAHoAFQi0Vi8UC/nC0VPAAqjIIHzFkoR0vF6pFKvh/NOeyYB2OQNQzNhCKmxC8Dk%2B33QAH0NPyTAB2Xnwp7up5TfWUl4CKaYVRJYhPaKoTxPTneTD4l1ULEXJ0Eo6u51Jw4phG686XI0mw7Yfnmy1km22riOl38j2e%2BqOZC%2Bhj%2BwPB0PhyPcmMWOO0JSp5MVtMZ%2BFZ/XUq43Y33eHEYAw/P874ARy8eG%2BH0xPbwuMu5LtGgB09neYLCKRTaDIbDtCeVC8DAgi2dFm%2BBDWDBv8f7icdmZ2eoN47Arch5zie06YMuq6MhiWJbjiO6lvuTwgce%2BJmAAbOY6EwZu27HLuZYHjOTIPPOp5%2BtszaXuGt73o%2BLovm%2BTwEBaPJ9nyZq1pStpMO8cQENQd6XOW%2BYPo%2B6YcMstCcP4vB%2BBwWikKgnBuNY1ieqs6zRuYhw8KQBCaJJywANa5LcGiSFwTqHBo/gaBh6FmAAHE5%2BicJIvAsBIGj7vJinKRwvAKCA%2B4GQpkmkHAsAwIgICrAQSQ3OQlBoLsdBxBErCbKoTnoQAtOhkhPMAyD1lItxmLwFJEHS6B6PwggiGI7BSDIgiKCo6jhaQuhcKQADuxBMEknA8FJMlyYZSmcAA8jciVoqgVBPDl%2BWFcVpVPOVZhPBAHhpfQwY6Vwiy8GFWjLBASCpUk6VkBQEA3XdIDAFIiQ0LQ2zEMFEDRFN0RhA0OKjbwAPMMQOIzdE2jVGFempWwggzQwtDA91WDRF4wBXLQPYg6QWAsIYwDiOjUE1OyjJTQG1Q3JselhNs0ndbQeDRENEMeFgU0sXgXncLwlPEKGSgEjsxOs0YhnLFQBiziCeCYP1M1JIw%2BMNcIojiK1GsdWoU29foxMoGplj6GzwWQMsqCohkwUcHlUzoISpiWNYZj%2BULtVU1b7SdBkLgMO4ngtHoISzKU5R6Pk6QCOMfh9THXT9JHQx9VUNQCD0Ywhzk6cdLDtTTCngzxOn0zx3oXqNCX8xl8sCiaRsEjjRwsmkH5vABStuUFUVJVlZIFW7bghAkGhumnfp0vLAgmBMFg8QPqQpmSIctwAJyHE6kgWWYkjoT5/joRvbkcB5pBebptzoVw6FORvTl34EXD%2BFv6Ed1NAVBSF0/hZdMUrpxXmklB6T1DqZTYJwBoLB2ROjykwF4BgjBbQ3rcLg5kqr4BqngOqfUNZNW1tIXWSh9bdV0IkQaw0Qat3bp3aaHA5oJRuE8JagJiCwPgYg14xNUHoPMrtfat1DoTyWGdaWkVrqoAOnEZKj1pHCKGDAuBeUeFGC4BvLg%2B4PpfR%2Bn9bqYMgb40MRDKGMMHD4wRowAgyNUZTQxljHGeMBYE3FkYUmil8DfAplTbqNNkB03xozDoU1WbsyBlzTYileb8z0kLEWmAxZE3cWEUA/8%2BBywUArJWKs1YuIIVrFqxDZB6y6opChRspauysGbMJltl42y6PbR2BBnaHAJNU92ns4je3qQ3Aumc/AQFcJXPq4cSil2jqkWOmRc4J2SNM5OEdJn539lnCucyq4DK6NnGYEy65Vw2dkeZ1c9lzCjidFYaxm6XOZnQr%2BnB2GcIQUg3hGj%2BEaBHtg8ex0p7nSMqQOeC8hjL2ZhfK%2BaCLJOjfk6aykh96FT6vQ7%2Bthf7/IAfAIB8UFpyPARlLK0COHrRYAodk9Z2TvPOFMLBY9ar1VkIQopbV5CkLKToEAhwBpDRGgLWhk1uoBSYQtVhy0YHEtJeSylo4piCIUXdCehw/kSKAXi%2B6KU5WHQ5MgJISRbQUo3raKlBAeJEuIXQXRlB9GKRMWjPSNqzGw0sdIxGNiUZo08ZgTG2MxDOL0oTCWUTeBeMLpTe2il/GBJccE5mikwkcxxJEnmdJYmCziAkpJEtUkSNlkweWitlaq3knpApzUJDFPaqyg2HLKnGFNjYOp8Bra2z9JwAUTsTZu0sB7LuXtcE%2B2XhnLogdg7HLDkHWuFyFkFAyKMqdMyJ1pz9oXdZvRZ2DqLr0BdZcRirs2eXTdyyDmXMbtclqfLP4CseWKoqJKyURildsGVEBR41QnidcR/9Z7z0XpQVu4KEhoMOIcfwdlLI%2BSA06e%2BF7/KcB/qFGeK8QCSH8JvfwTkMIb0kBvay28uCcuZocflMHAp/wuq3Sq0Gu6wdIwCoWaRnCSCAA%3D)

## Links

- [source code](../../../../conceptrodon/pagelivore/concepts/falsify.hpp)
- [unit test](../../../../tests/unit/concepts/pagelivore/falsify.test.hpp)
