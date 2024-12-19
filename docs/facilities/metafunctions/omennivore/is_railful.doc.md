<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::IsRailful`

<p style='text-align: right;'><a href="../../../index.md#entity-examinations-1">To Index</a></p>

## Description

`Omennivore::IsRailful` accepts a type.
It returns true if the type is a packed `Rail` and returns false if otherwise.

<pre><code>   Type
-> Type == Rail&lt;Items...&gt; ? true : false</code></pre>

## Type Signature

```Haskell
IsRailful
 :: typename...
 -> auto
```

## Structure

```C++
template<typename>
struct IsRailful
{
    static constexpr bool value {RESULT};
}

template<typename>
constexpr bool IsRailful_v {RESULT};
```

## Examples

```C++
template<template<auto...> class...>
struct RailLike;

template<auto...>
struct PageLike_0;

template<auto...>
struct PageLike_1;

static_assert(IsRailful<RailLike<PageLike_0, PageLike_1>>::value);
static_assert(! IsRailful<int>::value);
```

## Implementation

```C++
template<typename>
struct IsRailful
{ static constexpr bool value {false}; };

template
<
    template<template<auto...> class...> class Stockroom,
    template<auto...> class...Sequences
>
struct IsRailful<Stockroom<Sequences...>>
{ static constexpr bool value {true}; };
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISRqkrgAyeAyYAHI%2BAEaYxCBmAOykAA6oCoRODB7evv6BaRmOAqHhUSyx8Um2mPbFDEIETMQEOT5%2BATV1WY3NBKWRMXEJyQpNLW15nWN9A%2BWVIwCUtqhexMjsHASYLCkG2yYAzG4EAJ4pjKyYR9gmGgCCY8ReDgDUAJIKAEpMdFRetDu9xMiQsrxmjmQrzQDDGmFUKWIr2iqE8rwAbmIvJhXiCLFQxEoQQARI5gklkoFA7a7fbXB5HNxA14s140vZMA7Hdl0xlMLxEAB0wpu0IMCgUwsFouQ4oUr0aqGQAGtiKiWKRmayeZzrsd%2BUKRYdsGKmBKpUJMABHbEMDYKKnGoFPF4ED7fX60f6A46KlVq1AsRmWm2Me1Sm6Rhmg8FNSHQgRwhFIlFozHeHF4gjPa6JUmHcl5ykMh4AegAVJWq9Wa6WgRWq68ACqYMby6t1ss17sdqkPHVck47DmDg2oCPG03mo23B4ut4/OihZV6qwl%2B4DvVuMcT2ePbOu17KJjATDLzAAfQ0xeB/eHvP1AvHM%2BdB7ex9P54vXBvr85eGQC8zSUFoIE%2BRcvQBRkIPPRkPzPPAVyvUgjxPBCkJ/J1jRAEB02xRYbwhACgIlOICAgMAwHdCDvUZMICBuHC8MwAiCw4ZZaE4ABWXg/A4LRSFQTgmUsaxwVWdZMzMQ4eFIAhNHY5ZlRALizEFRIzEkAAOLSuI0ABOVSNAANi0w59E4SReBYCQNECPiBKEjheAUEBAnk/j2NIOBYBgRAQFWAgUgFchKDQXY6DiCIrk4VQtOMgBaYzJFeYBkChKRBTMXhMHwIhiDwdA9H4QQRDEdgpBkQRFBUdRPNIXQuFIAB3YgmBSTgeA47jeIUwTOAAeQFYK3VQKhXjixLktS9LXkysxXggDwIvoJFzBkxZeA8rRlggJBwpSSKyAoCADqOkBgCkMw%2BDobZiFciBoj66IwmaU5Ot4F7mGIU4BuibRMAcD7SHCthBAGhhaHe%2BqsGiLxgG3WhaFc7heCwFhDGAcQYbwYhAccdFWz6%2BFAYFTZZPo2o%2BtoPBojan6PCwPrszwGzUdIQniBRJRiR2TGaaMBTlioAxgAUAA1PBMGagaLj42SSuEURxEqxWarUPrGv0TGUGsax9Fp1zIGWVAUnqFGErGdAjmJUxRMsMxHM5gqsCNiBljsfGshcBh3E8do9BCMJBgqYYmsKTIBEmPxw/SSOGDmIZ4iaz2HB6cZWn9vIU9qL2BF6FpE9D5PbAz6O9BmQvg/mMOPYkjYJG6jgeNIBzeCcib4qSlK0oyyQssW3BCBIXFpK4Ta5KF5YEEwJgsHid3SGUyRDkFfTDkSAJJE04y7K44z9IsjgrNIGyZMFYyuFM/StKvrjJC4Lj1%2BM1u%2Bqcly3Mnzzdr8vaAuGkKJ0zqrWimwTgzQWDokSAlJgpojBzX0oKLggoBK5WHi7Yqsgyoq2kGrJQGt6q6Guq1dqH0m4tzbv1DgQ0goCleGNV4ECoEwLgcABBSCUGLWWodVao9DhmAnttLyf9gFxFCqdQMPDhhMOgbKTGXB9JcECDQWgd0HpPXql9N6wMtE/T%2BgDIG7NQaMAIBDKGfVYbw0RsjYG6N%2BabAEvgPGadCYo1QaoUm2xgaU04vVGmdM3qMwcVtAqbNZKc25pgXmGMjAC1AN/PgosJZSxlnLYGitsEVVwbIdWdUBJEO1oLO2VhLAG2iG7E2ZssgWytjbYp1hHbt2doVImxsuh5z8BAVw5cmpBzKEnPQEd6g9NSHHeoRcFg526PnMuWcY7tLTjM2Y1cBkp1mbkeZld%2BgrOLo3FYawG7jyPhQt%2BnBGHEEgdA2Bcj4EKI4RoQeeUR7rXHltKepAZ5z2GIvXxJ8z6II0JIRIT9EiJEONvSQyUmqUPfrYT%2BQif7wD/oFEa4jRHEFAZsCB00WAKHRFCdEdy6RjByk8jBTUMnKyyVVeQ%2BC8k6BAOZEhHVUbkN6vVJyNCRr0PGtilKuL8UYiJbqMYXDJFHT4YcQRQtvL7XFatNF8rhj4pSCkC8hL9IXmJQQICFzko3VUXEdRz1Xo/R0aa36/18bA2MeDSG0NHGYDhgjMQNj2Z2NicE0gTivauOJh45AZNvGCCpn42m9NThBOZqE4GET0hRL5rEsI8SdqJJPMk6WstGDpKwVSiQ2Tqp0s1oywpxg9alP8RUwSVTEycFLFbXW9sLCNMEs0128APa50WZ07pczA6%2BwmWHUZRQsgjKGVkQdJdU71ALpnDZFcu0zozpOiu6yA5rOWf03ZRyFD1wqmy1%2BHKzl8teAKglwrtiiogEPfKfDXlfx2tPWe89KBNz%2BQkRBhxDhcT0g/OyX7EimUPY5TgH93LvOXokLKwKuBSH0oCxI68uDJF8YcdlIHnIPsUkfbKwH26gaw4sZYnMMjOEkEAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/omennivore/is_railful.hpp)
- [unit test](../../../../tests/unit/metafunctions/omennivore/is_railful.test.hpp)
