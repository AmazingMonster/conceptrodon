<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `AnyDeceive`

## Description

`Mouldivore::AnyDeceive` accepts a class template predicate and a list of elements.
It returns true if there exists an element for which the predicate evaluates to `true` and returns false if otherwise.

<pre><code>   Predicate, Elements...
-> (...||(not Predicate&lt;Elements&gt;::value))</code></pre>

## Structure

```C++
template<template<typename...> class, typename...>
concept AnyDeceive = REQUIREMENT;
```

## Examples

`AnyDeceive` turns a fold expression of a class template predicate over `||` into a concept so that it can be used for subsumption.

The following code will fail since `(...||(not Pred_0<*>::value))` and `(...||(not Pred_0<*>::value)) && (...||(not Pred_1<*>::value))` are both atomic:

```C++
template<typename...>
struct Pred_0
{
    static constexpr bool value {false};
};

template<typename...>
struct Pred_1
{
    static constexpr bool value {false};
};

template<typename...Args>
requires (...||(not Pred_0<Args>::value))
constexpr bool fun(){return false;}

template<typename...Args>
requires (...||(not Pred_0<Args>::value)) && (...||(not Pred_1<Args>::value))
constexpr bool fun(){return true;}

static_assert(fun<int>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwDspK4AMngMmAByPgBGmMT%2BXKQADqgKhE4MHt6%2B/kGp6Y4CYRHRLHEJZkl2mA6ZQgRMxATZPn6Btpj2RQwNTQQlUbHxibaNza25HQrjA%2BFD5SNVAJS2qF7EyOwcBJgsyQa7JgDMbgQAnsmMrJgAdPcn2CYaAIIzxF4OANTKxJjoAH0NM8XiYAlZXl8oV8ZkxHMgvmgGDNMKpksQvjFUJ4vgA3MReTBfMEWKhiJRggAiJwhoIC1OOtJBu32h0wJzOl2ubHut0eIPenwIPz%2BgK4IJJIOhMMa8MRAhRaIxWJx%2BO8RJJZNoFPpNIlusZEteLIOcPZpwuV2YPPuL2IwAU/NefwAjl48H8FF8ILywW4/RAGKhhb9/kCOXaHY8QCA1YTlssQUjFejMdjaF8qF4GBBE%2BC/gQNgxM%2BTzVZda9mXtTUcLVzrXdbfbHccns7MG6PZgvT6HgF/f3A8GRWHgadIy3sDG45gE8SzAA2cwL72%2B/sBoMh0UA8Xj5vR2ME2eJ17J3ZKtM4rM5vMWAtFr4ED5lqlGt6yvDIAFMBRKZrUbMOXCAhHlzRNGQ4VZaE4ABWXg/A4LRSFQTh/UsawYXWTYNTMY4eFIAhNEg1YAGsQBghdbgADgXKQYICBdJAATmOBjcP0ThJF4FgJA0DRSAQpCUI4XgFBAfjCMQyDSDgWAYEQEB1gIZIvAIchKDQfY6HiSIbk4VQaIAWkYr5gGQBEpFuMxeH%2BQgSDwdA9H4QQRDEdgpBkQRFBUdQpNIXQkgAd2IJhkk4HgoNg%2BCiOQzgAHlVJU4VUCoL4DIXYzJFM8yvkssxvQ8LT6Axcw8OWXhJK0VYICQTTkm0sgKAgOqGpAYApDMPg6F2YgxIgGIYpicImnOcLeCG5hiHOOKYm0WpJPwzS2EEOKGFoUa/KwGIvGANwxG1MbSCwFhDGAcRNq7OpcW7GLUVqVTtnw4Cuhi2g8BiEKpo8LAYqfPAeO4XhruILElEpPZTreowiNWKgDAdAA1PBMECuKrUO5zhFEcQPMx7y1BigL9FOlBrGsfR3rEyBVlQZIejEjhDJmdATkpUx0MsMwhOB4gHJu6nOm6TIXAYdxPDaPRQnmMoKj0AoMgESY/CSeWekGGWRmqLp5vqWYlb0Go6gEPpmnV4YEmqPXxdyS3%2BjNxYLdWBQsK2CRIo4OCBJi4S0qMkyzIsyQrO9XA7JK3CuHKgiYdWBBMCYLAElzUgyMkY5bhYgJJA0SQzEkBc%2BIopiOI4LjSB4vDblohcqKYqiuAXGDJC4GCWIXL2/OE0TxOjqTqvkmrFMS1T1Oa1Aip0vSOCaFhcQCQymERAwjFypjbi4W4kNsoheccpJMdcnHpDxpQCb83ROuC0Kxvdz3BN4YSEuU1SvhSr4Z7nhel9O1f183grx71WKvOY4Zgo6VWkoPFqxVR7QJGB/eeyBl7tSYlwfiNBaA9T6gNPyE0RqHTwVNGac0HCHSWowAgq11oxS2jtPatADqAyOhDIw50kL4D%2BFdG6fk7rIAeodZ60E/JvQ%2BiNb62wkJ/QBvhYGoNMDgxOqw8IoA%2B58HhgoJGKM0aMAxrIQ%2B7lj6yHxr5JCF9ibQ3ZlYSwFMYhU2TrTemnAmYEBZscNmZNObc3iLvfmydDY9BFmLHIytgii3trLFWaQFZZGtiE1WmRwma0FjrY2VtgkG21kbXosxEkWzGP0fWttTbS3Nm7NYGxXaRxLnfb2nB37EFnvPReSCf5cDXhvDQId8A7xAZHCqMdSBxwTiMZOQiy4VzXjnAIrcAgBGOLnfOzcO5CU4N3CSMMZIDyQEpJKsDAENV0mwTgM8TIsAULiBEuI2m3DZDMGy3T7J708ljNyEhDFeVPiYnQIBjikCvmFQGt9oqd3isPZKqUTlZTORcvE1zbnCggIVIB8QQHHHARsqB%2ByYFNTgQkC5yRkgAiuUxAE8LvwNMYl1TB8RsGDWGlNAh9LpqzXmmQ8ey1KFrQ2uwzA21dr7QZvhY6kMJG8A4Tra6DMt6qHursARggXrCPep9c44jfq82kUDeIciFGQ2URsuGTBEbI1RujJhB9sYGOecYwmPzzHGA8TYERdiaZ00yAzAA9MzUmHMLBcwfjzPmLrklZMCYU0J6BclyyiT0cN8TiglIdhkoWqSCmxOTSk7JdtE0RPyRMdNRS5ilFKVU52FT3JAuWQ/OpkKvjQsuXCs0Mwulh16eivusd46J0oO7cZ/g17HGODBGCOc0EaEHQxKiVbYoiVsD3CBCYU4gDTuvY4VEm64RHQuXCDES7HGBSs2dC73bWWnV3XuVVVjA3SM4SQQA)

By turning `(...||(not Pred_0<*>::value))` and `(...||(not Pred_1<*>::value))` into concepts, we allow compilers to perform proper subsumption.

```C++
template<typename...Args>
requires AnyDeceive<Pred_0, Args...>
constexpr bool fun(){return false;}

template<typename...Args>
requires AnyDeceive<Pred_0, Args...> && AnyDeceive<Pred_1, Args...>
constexpr bool fun(){return true;}

static_assert(fun<int>());
```

## Implementation

```C++
template<template<typename...> class Predicate, typename...Elements>
concept AnyDeceive = (...||(not Predicate<Elements>::value));
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwDspK4AMngMmAByPgBGmMT%2BABykAA6oCoRODB7evv5BaRmOAmER0SxxCWbJdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHASYLCkGeyYAzG57B0eYp%2BcAnimMrJgAdK%2Bn2ADUyAYKCh/KxEw%2BFEe1IHwI90ebFez2w9DYggU7xMGgAgmgGNsUgQPqiGLcACJ1TB4ABumA%2BpwJHwgMJMATc9LcEAYqBxAKBeBB1zOcP2jAISJO2BAIFJYi8mBWK1OVjRKNRAHoAFSqtXqjWKhUqtUfAAqmFmf3VWrROo1FtVptRCouhyYxzOEIezGhb2FCtmxC8Dn%2BgPQAH0NAr6XLUR8Ix9Zg6uV8BLNMKoUsQPjFUJ4PuLvBTQ1QxEp6QTZSGAkWTmHbft7Y67i6nnSPWivT72f6A1wS2HI1Gmo5kHGGAmkym0xms5LKQELHnaAXS8X5fPyyG0XarjdnVCXq9UcRgELsArAQBHLx4QF/PGE4lknluDmBjRg3f7huHtEYofJ1Pp2gfKheAwEAylOgIEJsDD/vmPJWPO8qrlW65OpCrrbs8L4HkemCnuehq4viRLbLeNwPkGz57gob6UmYABs5g0fh15EeSJFtlw5Gvu677ovGezDj%2BGYAUBIEWGBEHgt6MGFiuqLRn2AZML88QENQgE3OEBDvMBMrlhway0JwACsvB%2BBwWikKgnCMpY1hRhsWw5mYJw8KQBCaHpawANYgIZkjPBokhcAEJwaIZGi0TR1TJAZHCSLwLASBoT6meZlkcLwCggE%2BblmXppBwLAMCICAGwECkXgEOQlBoAcdDxJETycKoiQ0QAtDRkgfMAyD9lIzxmLwnJEMQeDoHo/CCCIYjsFIMiCIoKjqLlpC6OxADuxBMCknA8PpRkme5FmcAA8hV5U4qgVAfM1bUdV1PUfH1Zg0h4tX0Cm5jOSsvA5VoawQEgNUpHVZAUBAQMgyAwBSGYfB0HsxCZRAMSHTE4TNLcO28GjzDELcx0xNodQ5S5NUIgQx0MLQmPLVgMReMAbhiLOWOkFgLCGMA4i07h9Tkply2JnUFU7C5GndIdtB4DEm14x4WCHQQI0JdwvDksQaZKESHNGFLRjuWsVAGPuABqeCYGtx0uqzE3CKI4izbbC1qIdq36JzKDWNY%2BjS5lkBrKg2JZALrWzOgVKmDZlhmKl6sjVgfvAV0PRZC4DDuJ47R6KECzlJUeiFJkAhTH47GF70Qx56M7G1PUAj9JMmd5DX3TEw0cyVyMCQ13MJd6NGLSd0s3drAo9nbBIe0cMZpApbwaXXS17Wdd1vV%2Bc9EC4IQJDUV9P0G2sCCYEwWAJEn3mSCczwAJwnAEkgBWYkg0Ulhk0df%2BicHFpAJc5zw0VwGiiRr6JEAb5Lghlb40VnodNKGUsquQNvlIqAMSpnQqlVcGqA3r1UahwZoLBSQBFakwL4BgjCPWvs8Lg/lBr4GGqNcasgpoO2kE7JQLtlq6FhhtLaWMp4zznkdDgp0yoVQ%2BJdD4BCiEkLIZzSh1D/IvWwcDd6u8zDfUQblf6gMVEg0wRDd6IBpHEO%2BJzLg18uBPhoLQBGSMUbLRxhjVmTi8YEyJg4VmZMBSU2podOmDMma0BZqrNm%2BxObc3MvgQEfNDSHSFsgEWrNxYxXMlLGWGN5Y7HMkrPAKsXLq01pgbWETwigG0XwY2CgzYWytowG2zD7YzTYbIZ2S1zLcPdvrSOVhLA%2BxiInAOQd4ycFDgQcOJwCQ9OsDHeecdRpxP9snNuzgICuD7uxHOZQu4F3SEXbITdS6pD2RXXOOyW4p3rr3Q5/dW51z6B3M5w9%2B7XNyEcge8xtnPK4KPceM0BEHWWgvExsizEUIsYojQNIt7DV3j8/e2jD7H1PpQKe39f5UICgESBARgqSCfh1diQi4G2AQb9PKBViqlXOgYvR70GpsE4AQu6LAFCkn7KSCFVxZh0O3vHJhk0mkSBafNDh7SdAgBOKQXh21VYApgUCk66CLpXWZZ1Vl7LMxcodIaHEEBXqqPiLvE4mjyU6JQHS%2BItKcEJHZSkFIAZOXXwDNyggCliAsA6nDWx8R7Go3RnjFxAb8aE2Jl47B5NfE0yiZgemjNmYCxcuzCJ2TeDRLbvzeJqhhZ7GSYICWy10my1uFkxWytWaFPSMU8JusylIKNkwU25tLbW1CbbFhzS5ryDFa7SVXTjBez6ekwZFlhmDk4IqMOnso4WFmRZeZCd4Cjzub0NOGc3nZ3TkPfOZcTlZA2ccooWRt3V2WfchurQbkXJWQ8gYJ7u7jAGAej597J7rE2BPH5n9p6AtSpwKRHqWVso5dqvYsxoX0J3p9eFWi/pIpPqMJOMV0X%2BCoScE4hkwqBSSuhgIQCFV/vSqS7KB9SAX0MjfQyiRaLX0kNfYKd8uBSpiicX989OAIrg9%2BgaBH2NEbNWsdWGRnCSCAA)

## Links

- [source code](../../../../conceptrodon/mouldivore/concepts/any_deceive.hpp)
- [unit test](../../../../tests/unit/concepts/mouldivore/any_deceive.test.hpp)
