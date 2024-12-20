<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::SensibleRightInterview`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-sensible-right-interview">To Index</a></p>

## Description

`Varybivore::SensibleRightInterview` accepts a list of variables.
Its first layer accepts a list of predicates and returns a function.
When invoked, the function first binds the arguments to the end of every predicate;
then, it returns the index of the first variable that satisfies all newly formed predicates, or `-1` if it cannot find the variable.

<pre><code>   Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> Predicates...
-> RightSides...
-> Exist (...&& Predicates&lt;Arg<sub>I</sub>, RightSides...&gt;::value) ?
   I : -1</code></pre>

## Type Signature

```Haskell
SensibleRightInterview ::   auto...
                         -> template<auto...> class...
                         -> auto...
                         -> auto
```

## Structure

```C++
template<auto...>
struct SensibleRightInterview
{
    template<template<auto...> class...>
    alias Rail
    {
        template<auto...>
        alias Page = RESULT;

        template<auto...>
        static constexpr std::make_signed_t<size_t>
        Page_v {RESULT};
    };  
};
```

## Examples

We will find the indices of `2` and `-1` in list `0, 1, 2, 2`.

```C++
template<auto I, auto J>
struct Equal
{
    static constexpr bool value
    {I == J};
};

template<auto...Args>
using Metafunction = SensibleRightInterview<0, 1, 2, 2>
::Rail<Equal>::Page<Args...>;

static_assert
(Metafunction<2>::value == 2);
static_assert
(Metafunction<-1>::value == -1);
```

## Implementation

We will implement `SensibleRightInterview` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:** Check several parameters at the front of the list.
If a match is found, then its index is returned.
Otherwise, drop the checked parameters and call itself with the rest.

Here's a simplified version of it:

```C++
template<auto...>
struct SensibleRightInterview
{
    template<template<auto...> class...Predicates>
    struct ProtoRail
    {
        template<auto...>
        struct ProtoPage
        { static constexpr auto value {-1}; };

        template<auto...Agreements>
        using Page = ProtoPage<Agreements...>;
    };

    template<template<auto...> class...Predicates>
    using Rail = ProtoRail<Predicates...>;
};

template<auto First>
struct SensibleRightInterview<First>
{
    template<template<auto...> class...Predicates>
    struct ProtoRail
    {
        template<auto...RightSides>
        struct ProtoPage
        {   
            static constexpr auto value 
            {
                []() -> std::make_signed_t<size_t>
                {
                    if constexpr 
                    ((...&&Predicates<First, RightSides...>::value))
                    { return 0; }

                    else
                    { return -1; }
                }()
            };
        };

        template<auto...Agreements>
        using Page = ProtoPage<Agreements...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

template<auto First, auto Second, auto...Others>
struct SensibleRightInterview<First, Second, Others...>
{
    template<template<auto...> class...Predicates>
    struct ProtoRail
    {
        template<auto...RightSides>
        struct ProtoPage
        {   
            static constexpr auto value 
            {
                []() -> std::make_signed_t<size_t>
                {
                    if constexpr 
                    ((...&&Predicates<First, RightSides...>::value))
                    { return 0; }

                    else if constexpr 
                    ((...&&Predicates<Second, RightSides...>::value))
                    { return 1; }

                    else if constexpr
                    (
                        SensibleRightInterview<Others...>
                        ::template Rail<Predicates...>
                        ::template Page<RightSides...>
                        ::value != -1
                    )
                    { 
                        return 2 + SensibleRightInterview<Others...>
                        ::template Rail<Predicates...>
                        ::template Page<RightSides...>
                        ::value; 
                    }

                    else
                    { return -1; }
                }()
            };
        };

        template<auto...Agreements>
        using Page = ProtoPage<Agreements...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMz%2BpK4AMngMmAByPgBGmMQSZmakAA6oCoRODB7evgFBaRmOAmER0SxxCVxJtpj2xQxCBEzEBDk%2BfoG19VlNLQSlUbHxickKza3teV3j/YPllaMAlLaoXsTI7Bzm/uHI3lgA1Cb%2Bbl6OtIQAnifYJhoAgjt7B5jHp8jj6FhUt/dPjwImBYKQMQJObiY51QADo4X9HuNiF4HIchIwMjF6AAlPDABAEACSgniADc8JgAO7/EwAdisj0OTMOQJBYMwENZoKY4NOUKIcJht0O%2ByYCgUguUxEw%2BFEQIUCIezMOSJRBEOUtQRGxTDo/2VdIZSuVzK57Ih/Nh8P8d0ZJqZqtRmqIyiYwA5dvthpVzUcyBFAnGmFUKWIh0th1JYi8b0NAFouHSACInCzHWkp/xG/X2lnA7m8yHQwUPYDS4GMAgKm05%2B1eDJGDVu2P%2BJMa4ha1Cu90Q0vltiCCXWu5Z2vpzPZz15tk8jmnM2zi3F4cigziyXS2Wz6u241M%2BvhYCHHV0d5t52oE%2B0CFSmV4OWYIdCmujx7J1M0wH58186GHABieDEOMiqOuq6IMJiOJ4gSxJAsQ5JUhCgHAQQiqGmOC6Flhc5FgKK6iuucK3lu8qKsqYHtp2V5jhhU7KjhS74TCuL4sIeBYDuY4UQQyJOh2LrNtxzLekywn2rMfoBpBQIhmGEZRt4sb0bmdF7rmXoAKxWJpSYQEshxxsKXwgCALBMAA1pgAD6GTABE6DWWhpwZAAXjZzm7hpGlqd5fmHHgVDSUGcnHCp/nMlAgrmAAbLFJH3tuyFAeMpDHjB7GcdFNqmYpMZLEs4kRemabSgQ6wMIcGipuOn7qcVzJ1EoRURd6ZUVYZiZZrV4Xecm%2BktSJGYfr176vgC9Wmt%2Bi6/sxfaYBWg7kbmB6Nt2LbngJXZCac82LVW2UjkaBrDeNmHTdhF24Zah2rmKT57QOVbLfuDZHleZ5UdqurXrtZYLU9T5/Gdp2Tg8jGzagAEpQQaURuiaAMOgcPLjCADyBAIPEXGIrxapohieBYpgrGwSSCEUtSpwoalBOI8jhwY1jwGHTS9LnTOl2c9dqPCoRT4JQ%2BOPqZRF40VOvm5hDeFWixGVCBxj4vSaotbetRWiWFk0Sb697BbJobhn%2BeXKdrJqSw1JjaVbekGUZNo%2BugpnmVZtl4g5TkQm5HnK617O9RFgX68GhuDX5UXwmYcVR4LSXUzDaWk5lj6Hbl0aYAVYd9fShztcQlXVd175vgH/lNW8QeIyFoel%2BHEDRVH8WbolZGnAjAgM0nCtZcOadKZntfZ6VmDlfnhxdWmxcTQ19rlwFQVVwbxBZxpEAr/5EFQSTGVwWSlMQkz2Os4PEWmThx4/TezdC8fZsz4cZ9XU2PanF3itAzWJ/%2BX3MaHGAYAnDbAmde9pCpfy9DnEB3k86VTMMcSwBNIJE2gmxXeFMkKnEPizYcUCNKP25hfPUpxY7ylvvfPBIBz7q1fvLd%2BZDyH2h/nOSe4DzbDRLnfMutBmqsJOsPUelVgFF3YZwiBtss5jWOqpUGdUNLSxunCR6lZhYaVWkedan0LzULcEowcrNxonQnLIqa3NORXSYrLPma4Hr/X2io5kajCG0E0VtGif1%2BzKP0dmGRHCAD0AAqQJQTgm%2BP%2BAEwJAAVbAQgIlBNCY8cJwSQl1WeAwfYXgjgQnOHQa46EvymMhocQkKMiCHAAFKgTxqibAABHLwYg2ZSIdLrf0i8Q5hhiKgTwkZ060XpISM8gDymSLZkYjh8jUYPGIMAYWjiACyI8mBUC8Gkhon1N7IO3qg8miEqZuA0GlLgaVkiHDMIqUybi3C1Pqb9bApltFTJmV4uqkl7zWXuvENCjwIALOaMs1ZWQIRnJyiAE2gzWynMKuNV5yB3nik%2Bf8H5iz/kOEBacIRdzQXp3BUArgUKLAcBWLQTgmleB%2BA4FoUgqBOBuGsNYFUawNixjMP4HgpACCaEJSsCyIBNK0hhP4AAHDFWk/gRUaCFaKgAnEEYlHBJC8BYBIDQBzyWUupRwXgCgQAHI5RSwlpA4CwBgIgEAawCApHOOQSgaAQR0HiJEVgWxVDCrjDFSQhxgDIH9FIGEZheB3iIMQDieh%2BCCBEGIdgUgZCCEUCodQ%2BrSC6COZSYgTAUicB4ESklZLOVUs4Gjc4lr1SoCCi6mKbqPVep9ZIP1hwIAeDtfQMMOw8W8D1VoFYEAkC2pSPasgFAIC9v7SAYAUhkg0FoPBbVEAYh5piOEFoVxM28AXcwYgVw0YxG0JgBwK7SC2qemjBgtBl2JqwDELwwBIS0G4furA5kjDiHPUBXdjhSSPjzcGXd5wthsvCECOVlLLgxDTRujwWA828TwEq7gvAP3EE6UoJMwJDDAEuEYTlKwqAGBmQANUpmjFIjB91huEKIcQ0ayNxrUHm5N%2Bg0MoDpZYfQRNtWQBWKgFIDRtUcDjF8QBphLDWDMOqhDwbOLwBWHYN9WQXBIymH4I5oRwhDAqCMI5hRMgCEU3oLTDR5jDCqN0WTAg%2BiTE8B0PQMnUVmYmAMVTCwNO2Hs7po5sxWiGfU1UaTjLNgSGzRwUlpA1W8A1YcctlbPXevHrWuBEBcCEBIPA1lSx21YZWFjJgWAEj6VIDyyQ/gYQytpJIDQkgzCSBiiqzSMUpX6E4Aq0gSrWUwhilwGKgqpWCo65pSQXBNIypiiFvNGqtU6vZVhw1Jru1mqLVawdw7m2OrYJwFoLBSS0jjEwO6jYuBSphFwGElLA0kBDUcsjEbKPSGo0oWjibdDJFTemldgXguhfzRwQtFrziHFLeGYgG2ts7dFHtg7R2ND1sbX25tKWzBpcm/qrtPbUBNviNaodqOYcjHW5tuMoOx1Sq4Acyd07KBzsTWupd%2B6qcbq3TuvdcGD2o6PSes9lKL1XpvXepnD60PPo56%2B1FH7eMndUD%2BoE%2B6AN1DzSBsDVwINbEpdB2DbKENIcwChx96HDxTZw26BQBGqREZI0zy7FGo03dkDRhNlLHsMcw0JqwLGQPsby1xnjnB%2BMEHQIJ5jFhRNhfE%2B/KTJnbN%2BAgK4NzwQkZecWJp9I2nsiWbyAnooWQ4/OZsw0czbQU9KbDzn%2BzmfjMebz7kAvZeS8BdWOsfzeKGtBdzYm8LuPge7aPPtw7x362JaDSlttiPO2ZcwNlkYeW5VNZawd8rtJBu0lFRVqr/WRst84ON3VU2jWmvNcWjHS2HVOrW4D91hwWAKFJP6UkXf2TjADfgIN52Y3kcjRIK3sa7u250AEUgz2M1wbe2b3VQLXmxLSCnW1P3P0v0jBv23HVAbSx37RS38ARw7QNVmwPwHRtUQObVBWQBSBSGsmvylWslvwIHeRPxuzoDJ1nXnUXQ3Rp3oM3W3TfX3UPUrGPVPTzU52vTEB5zZT5yfSV14HwGlGF0/UTW/WQF/SlxJCA14DlyXUVyg2DVV3g3iA1y13511yRz4Fw0N0I2I3JTZXN1fyo2t0/zox/wMEd391YxiDd0424yyF418RMidxEzE3iAk0/Q40Lzk0jwU3zz0BUzKCMz00TwaGj30wz0c3CPczqFM0aFc2CISJ6DszmDiO82sxSIrxyMyLCOyIbwUD8yjUANX2AI4ABxYEgIvyv1gPlHgL72S1bVQIy1ICyxy0oECynxADMAO0CE0k0nK2JwlX8FpE6wqLC3X1sAmzQIKnyxAAqzay4H8CjjWKlXayjg0FpEb38CAOmM1SHy5Ub39SmM%2B3SyRxWAQwyGcEkCAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/varybivore/sensible_right_interview.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/sensible_right_interview.test.hpp)
