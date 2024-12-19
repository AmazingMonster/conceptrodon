<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::AreUnique`

<p style='text-align: right;'><a href="../../../index.md#list-examinations-2">To Index</a></p>

## Description

`Typelivore::AreUnique` accepts a list of elements. It returns true if no two elements in the list are the same and returns false if otherwise.

<pre><code>Elements... -> AreUnique ? true : false</code></pre>

## Type Signature

```Haskell
AreUnique :: typename... -> auto
```

## Structure

```C++
template<typename...>
struct AreUnique
{
    static constexpr bool value 
    {RESULT};
};
```

## Examples

We will check if `int, int*, int**, void` are unique. Then, we will append `int*` and check again.

```C++
static_assert(AreUnique<int, int*, int**, void>::value);
static_assert(! AreUnique<int, int*, int**, void, int*>::value);
```

## Implementation

`AreUnique` is implemented as a special case of `Typelivore::AreOverlapping`:

```C++
template<typename FirstElement, typename...RestElements>
struct AreUnique
{
    static constexpr bool value 
    {
        ! AreOverlapping<FirstElement>
        ::template Mold<RestElements...>
        ::value
    };
};
```

[*Run this snippet on Godbolt*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxCAAbAAcpAAOqAqETgwe3r4BaRlZAqHhUSyx8cm2mPaOAkIETMQEuT5%2BgXaYDtmNzQSlkTFxiSkKTS1t%2BZ0TA2FDFSPJAJS2qF7EyOwc5v5hyN5YANQm/m5ejrSEAJ6n2CYaAIK7%2B4eYJ2cE16mYAPoExCYhAUdwezzMewYBy8x1ObmQ43QWCooKeYIImBYqQMGLhXx%2BzDYADoSajHuNiF4HEc3ExUgovPRTlY0U8MVicZg8d9GKxMCSiQBJBgKH4OTDobD0NiCEH%2Be5PClUghHR7ETAAeQAbnEDKlUmFgGCQEdUl5oldkEdESAQPi/ngsIIbnDhaLuhjJdLGAQ5dgBWCTAB2FmPI7h60A5VHAAimCadDBEZOIaTyYj7OxTFxnx5hP5pPlafTkcp1OUxFQRAAsp50MX08GLEcvJkjEd7R8Y0ctahHcyUzHmQ3g0P/KGwQB6SdHABK3Q2mR1R0amFSIAbmc53IJfKObrFjiMUsxPtIHbzfIF8/GJ5lvrJyaV5crNbrI9TTxL4enJwSGjjBNaBMf8jgAdzoWhI1QVIjnVZBF2yc8mGQBA8EwLVDWtBASAIABaZA8E2LxCCJBtk1bLDO1ObsbRQAR8HqZhgK/b84XI786LwBRfmiJglF%2BVAUTOOj7V%2BR0fRdM4Dw9Q07x9O5SDVTUdWIPUDSMO5bS1MQvEwc8OJLQCgVoAzWO/CNlO1XU6Q0o1pJFQ8JXk2UBXPGSemPb1BEfNj5Vte0AsxLMMSOCsq1QWtaHrM4bwIFzfQDfy7R5YdWTDTimkcK00BFDFVFSYgjmiVBPB7XT3ibLieIUPlfi1Hd9J7PsYvuIMx1DZNRzS54nl/Cx%2BPeVd103YLt1zXc2H3RzZK808fKLczS2jcK32i10Zs84AEt88Mm0Mls22AC8fi7SN0FtXLGOyMQDvYpaLOq3jBsE4S3FEnlxKdRwvg290tp2%2BVzys1T1MNLSQB07wmoO5Ne0dUhYYjWl6UZLkHP%2Bz0EoUNzpsxuTvIIXbG2S%2B0eosg7xmzPAcoEcZMAKoqSrKqG9JTCwGCrc7bW435arYerGvPeHWu68cPw6wMlq3bN0bce18wFbHico9sovQM7Vsi98zmxpL7nF9LkxlnN5cvYkSWVxaMvDVXjvV/5NdfbX1t1wmccLbAAtSw2bZOaWxtlxrFct93iap7Kjly%2BnGeK0qoIdrV/b9ptOZVJ7%2Bb%2BBqJt5KatfVuE9c972fmFlrQXa4dfbFic2UD02Fb3AAxIjb0J89G4tok4qthVySjallLkBg8AARz0wNPz9iOaajun8sKuOWYq5OuqniywDAVV1WstTbPBs4W%2BINv5qJ62LKCjlZaOAvYswE/7w9sjz%2B/bSKolnqa6lx5JwAKn/gBgDJxTgAQAFWwEIUBADgF9UAXA3%2BMDergkhNCWEZxcpbFSA%2Ba2YIZ7IF%2BPxJQLQIBDxHuPOWYQCDnkob/ahgh/5l37MlVmmBlg9TwQQhQRCCAQE3tvTAw8x4TzOJQuhBBaFHBoRIkWYjf4QxYWw8cHBVi0E4AAVl4H4DgWhSCoE4G4aw1hrTrE2JVCEPBSAEE0Mo1YABrRI/giRJCSEGDQCQ1EaA0P4MwSQzAAE4/H6E4JIXgLAJCeNIFonReiOC8AUCADQljrGrDgLAGAiAQDrAIGaKhFAIBoCxHQOIEQ%2BScFUEkBIeEEiSCOMAZAVopBEjMLwCUhASCOj0PwQQIgxDsCkDIQQigVDqG0ToPQYFATrm4MooJHANGROsbozgGoLg5KOEJI45TKnVNqfUo4jSzBHAgB4Qp9Aiq7C4MsXgVjRkpKQAUg0ZzyCUAeUU%2BIwApBmD4HQDEx9KDREWdEMIzRricAsUC5gxBrgamiNoD0YLeAFPvBqBgtBQWjNIFgaIXhgC0loLQeJ0zMWYkMMAcQGL8DwUcDqQlOiGYLgxAi8gghaiLKuNEQEUKPBYEWQCPAYSiWqRKkoOMLBSVXCMMkvgBhgAKAAGroTAhqAkTKunCFEOIfpaqhlqEWboLg%2BhSUoEMZYfQeBojxMgKsGCTFCV4URDRUwlhrBmGiapYgElLUQFWF0HozgICuCmH4A1IR5jlEqHodImQmJBsjUUJigxw0jANb6pifRJieHaHoVNvRZiJuGPEFNsxY1Fv6PmxYhafUmK2BIFR6jNGLJiZsipVSal1IaZIJpRzcBtPOeYq5STbmrAQJgJgWB4jetIPYyQji/H%2BCDJIDQkgzCSH/BoNRCRAmqI4CE0gYT/BcCJAkLgyQ/FJBPWoyQXA1FzoSAsjFMS4kJMHVoFJ6SIBICyTk55%2BTUCnOKaUjgzQWBaiDHhJgUcDDti4H4okh66WMXaRdA1aqemaukNqpQuqMW6C%2BRMukCK61zIbQ%2B5ZqyLjrKoEcYDoHwOQdJfs2D8GjknMeXEE4EIzADpua%2B0gH76L/rIHk15ZyQA0bAwcUlMGuCJJoLQX58SIAAoxRCkFTLVNQphXChwTKkU%2BhRWixZWKcV4oJUyrAYqjDkp0ZS2SNLFn0oQoyollDWUYvZZy643Ltg6L5QKixQqMiYFFeKw0UqqAyvlYq5VjBVWyDQ30jDsgdUjJ0bhw1kqnVWFNeyr11qsHZDtQ6/wMYssurdXED1WA8s1DqNkFwDB3CZvyCGxr5aI0GqjcUHIzXg2FGjdkdrybauyQaMW3r2baijYYOmuYZQC3ZvG3kPrVMWhDcrWsDYNbLmzPmVE3gTbxN0ck9BpjRINDdsQ32g93HknDtHeOygRHd37tg0uoMN6gxBn8Mu1dV773RM4E%2BxJPGZmpIyV%2Bi4P6RMAbYJwYDOyWAKC1FaLUMGiScnGC0q7HSUPxY1YlgZ8gsOpbGYEfDUyeBEb242sj2SKMbIRzUpHKOezo8xyqY5f62PXf8Ld25fH7nc7edD4XomUf6nqjB34HOCHEBYNU758m4iKeUzojT6LwXAs07C%2BFRK9OCAM%2BimzmBsW4rEGZolFnxU%2Bd4LZno9mMWOYuNsCxrnt06I8yC7zvKPX%2Bd4IFkVJKrNhYFxFpgsqFWYCVSqolqGCcSCS4MkneqChQeMCamwuX4D5dtZwScNoyuWFdQd91nqc8jb9X4ANjWS1BDa2GhbnX43ZDr11hNjeK2Tbq2N/odec297W53jrtgltZtLUP%2BbXedsKGrX06nJHAccGo/LxHyPUfs9luMS7vaOM3euXd0gI6x0jEndul7IB/FEn8P4NRHir2eJv0Gao%2B2lmxNsM%2B0Hyw7EBASHBrg/iP2ASCQQYXAriBq26/gi%2BB2QOL6NisyzSAOMB7%2BX%2BqwqkmQzgkgQAA%3D)

## Links

- [source code](../../../../conceptrodon/descend/descend/typelivore/are_unique.hpp)
- [unit test](../../../../tests/unit/metafunctions/typelivore/are_unique.test.hpp)
