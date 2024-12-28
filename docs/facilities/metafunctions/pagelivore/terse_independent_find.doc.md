<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::TerseIndependentFind`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-terse-independent-find">To Index</a></p>

## Description

`Pagelivore::TerseIndependentFind` accepts a list of predicates and returns a function.
When invoked, the function returns the index of the first argument that satisfies all predicates, or `-1` if it cannot find the argument.

`Pagelivore::TerseIndependentFind` prepares fewer base cases than `Pagelivore::IndependentFind`.

<pre><code>   Preds...
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> (...&&Preds&lt;Arg<sub>0</sub>&gt;::value) ? 0 : (
   (...&&Preds&lt;Arg<sub>1</sub>&gt;::value) ? 1 : (
            &vellip;
   (...&&Preds&lt;Arg<sub>n</sub>&gt;::value) ? n : -1
   ))</code></pre>

## Type Signature

```Haskell
TerseIndependentFind
 :: template<auto...> class...
 -> auto...
 -> auto
```

## Structure

```C++
template<template<auto...> class...>
struct TerseIndependentFind
{
    template<auto...>
    alias Page
    {
        static constexpr std::make_signed_t<size_t> value
        {RESULT};
    };

    template<auto...>
    static constexpr std::make_signed_t<size_t> Page_v
    {RESULT};
};
```

## Examples

We will find the indices of `2` in list `0, 1, 2, 3` and `0, 1, 3`.

```C++
/**** IsTwo ****/
template<auto I>
struct IsTwo
: public std::bool_constant<I == 2> {};

/**** Metafunction ****/
template<auto...Args>
using Metafunction = TerseIndependentFind<IsTwo>
::Page<Args...>;

/**** Tests ****/
static_assert(Metafunction<0, 1, 2, 3>::value == 2);
static_assert(Metafunction<0, 1, 3>::value == -1);
```

## Implementation

We will implement `TerseIndependentFind` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:** Check several parameters at the front of the list.
If a match is found, then its index is returned.
Otherwise, drop the checked parameters and call itself with the rest.

Here's a simplified version of it:

```C++
template<template<auto...> class...Predicates>
struct TerseIndependentFind
{
    template<auto...>
    struct ProtoPage
    { static constexpr std::make_signed_t<size_t> value {-1}; };

    template<auto First>
    struct ProtoPage<First>
    {   
        static constexpr auto value 
        {
            []() -> std::make_signed_t<size_t>
            {
                if constexpr ((...&&Predicates<First>::value))
                { return 0; }

                else
                { return -1; }
            }()
        };
    };

    template<auto First, auto Second, auto...Others>
    struct ProtoPage<First, Second, Others...>
    {   
        static constexpr auto value 
        {
            []() -> std::make_signed_t<size_t>
            {
                if constexpr
                ((...&&Predicates<First>::value))
                { return 0; }

                else if constexpr
                ((...&&Predicates<Second>::value))
                { return 1; }

                else if constexpr
                (
                    ProtoPage<Others...>
                    ::value != -1
                )
                { 
                    return 2 + ProtoPage<Others...>
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
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKxcpK4AMngMmAByPgBGmMQgABwAbKQADqgKhE4MHt6%2BAUEZWY4CYRHRLHEJKbaY9qUMQgRMxAR5Pn6BdQ05za0E5VGx8UmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimGmujMh4mAq3R%2BdXN6f/xx%2BlwuwLMAGZwshvFhbiYwW4CABPZ4AfQIxCYhAUcOwIPMEIYUK8MLhbmQE3QWCoOLxvwB9MBIL%2Be1uAEkWGl6GxBExGl9DkDmQyAUCQQRMByDOLSeLJbzMKSmF4iAA6NU425QpgKBRqlXKYiYfCicXYsG4q4TYheBy3AAq8SUrIYWGeLsYBAAYuF0HiAOxWK63YO3WWc%2BWK5WoPU0oMhq02gi3A2oIjKJjABVx4MmAO3OaOZCagQTTCqNLEfMEdAgEAsJgAa0wKKywAi6DRpKyAC9mwQNQA3MReTCwgMAWi4ufucIsY5nYMDwOzoYl4el8KVRFu3uIE1jlxDVettpTaYzCvhu/35pBR9zc5zK6PBbwRbQDFL5crW9QtyH3ijneR4hg%2BwEgSBJj%2BFY/j3BAyy3OOGoUrW9ZNi2eBtkanbwj2fYHhBEFgc%2BhFHngVDFp%2B4rfrcUAxmYyTmMkBpGm%2B8pmm4179uatYASOyzLOBpGQXmhoEBsDC3Bos7zrSh7CRB9RKEJCk5qJmDicQkmTjJ04qYR07wfpakLku95%2BqZclHmGUqXm4v47nge4EKQtwOUImAfugrm/nqADyBAII6BHxuiibJsQqaoOmmaklxrkeV5rkBUFe4xreK4PqBJHBq%2B74ltRFZuVG/7DkBOVjmZqlQTBcEIUh5pVjWdaNs2rbtjhbh4ThFryQpxF9apwbkZRX4VsZwl0eqDFMSxxrsXFTk3tgvFlQJE2kVlYkSVJukWVZQ0hkpo4jR%2BY3EBthFTSqTGzYa82mqSiUCL6PEgHxmDrRVm3qZpklTouslXJdim0EotynQVZbjd9V0g8JZ7RRepIpY66W9YdhGrYBtxgGAcL3IhU6wxBgkkyJc7w6R21abcZiwpYEVRTFdmo2l6oZYNmPBtjI66eT5kzsDAtHWDWZc9Vv07TpgN6eThlkxLJmzkJemLgdwY2RGm5RnqlzAIaEoemaGMhl4WRGMmF6wmChOIyzpL64b3IELqHO4urwP7Z7y7XMKjJ0nc2CqKwnKjt8TL%2BxHwt%2B3crIKHaADuf7R5cWsbvZJWsgeCa2vHSeoCCIC3GkXgxLQb5NbWMSoJ4KJnS0gikqyNsLoTZgamB3tLpHdwALIaUwVBeISfKp%2Bndm%2BWqlzEMAJsgub4TALcA8tMPo85K39qOpgzqui8gjei6zcJ8nB61g78Iz3P6MqzHzLbxMnyp3lKLakobQQKvQ8jw4OSkhoVyQQ6auTBDiXmQFbYEzpoJH2r937xAIF/Qe68/4CAAUA0B4D3plVbtAycsCLAcFWLQTg/heB%2BA4FoUgqBOBuGsNYfM6xNhAXBDwUgBBNDENWA2AIkgVQaESGYMwABOERXB/CCMSFwP0fppCkI4JIXgLAJAaEAZQ6htCOC8AUCAQBnCqHENIHAWAMBEAgHWAQUuLkKAQDQByOg8RIisG2KoFI45kiSFuMAZARYpAqjMLwViRBiB4BrEEfgggRBiHYFIGQghFAqHUIY0guggiJwxGkTgPASFkIoVwmhnA/LKmsbcVAFE3HJA8V4nxfj%2BH0wgB4Bx9BKz4i4MsXgBitCrAgEgexaRHFkFsf0wZIBgBSDMHwOg4o9yUBiAUmI4RWiImybwRZzBiCIj8jEbQnkDHsPsS7PyDBaArJSVgGIXhgD2VoGDVZpAsD1iMOIc5Tk9l4AHB8ApZZPLKm2Ow8I4oFHUIrjEDEmyPBYAKeiPAKjuC8E%2BcQGuShHhPOABXIwXDVhUAMHPAAau8ROfk3T3MicIUQ4g4lksSWoApaT9CGGMAwyw%2Bg8AxF0ZAVYqA0iNF0RwccFICamEsNYMwmjEWhKwBy%2BCPR3nOAgK4aYfggihHCMMKoowiiZGyAIJVehig6oYAsEYCQgh2DlU0SY7RPCdD0OatBlr5hqsWJq2wVq9VmqtcajVprVgKGYVsCQuSODkNIBo3gWjbiVOqd43xtx/ENNwIQEgDMwTtM6Vi1YQUmBYASDK3hkgwQqhEWCORGhJBmEkMkNR/hkgiP0JwJRpAVFppVMkLgyREgiOkckfwkgJEltSOGwp2jbB6I4Vi4xZjekWJKcqcglARktOcWwTgrQWADj9OOJgmoDCWy4CIlUXABFBPwCEsJegyXRMpdIalShaUpN0JMjJTAsnwuDaG4dWjilWOVGUip7jPG7sZfGw9x6NC0SaQMlpqazAdInYYnpfTUDNPiAuuxKHoOjC1EYA9XBAE0FoDM3REB5kpPWcs%2B5FHNnbN2Q4e5hyPTHNOQUi5Vybl3PhQ8iUjKXnUPwIaP%2Bny%2BXUJ%2BcgP59zAX1AKaC8FiJIXbGoTCuF7DEXIswKi3jS9J04ozAoAlmAiUkq41eilsTb2yBpck6hT6GWYuFVYFloLpVcp5TkPlArqxCuZRYMVEaJVhK%2BZy2VDqXAug9cEF03qlhapKDkCLBrGjRddfaxo/Qpg2oKGa%2BoFr0uDGdSau17rMvKrdU6iohX2lrA2IGqrCjP0FMjdGoDOHl4HqPQI2iSaQmpvTQh7pWbMA5tGDKhRTaW2HvLX6fwIjZFggrVW/tYbGucB0eOrpRiTHmMsdY9DS6nEuLXcQFgQGWAKAHEWAc7XbITFPcmyVl7ZDXvM/E%2BQ97rM6BAGCUgL6305IbSG/JKTv1zqTOUqNp3zuXeu%2BxJMjTMODNTWCeDG2kMoARy0vbGPRgXbSGkFEV2REohuwQFEqhPFTKI46OZCylmbKo3TrZOy9kMZQ0ck5Zz%2BOYEudcsQnH2GPN44p3gAn3nCe%2BaoX54pJOCGkyk2TyyFPQtCSphF8R1OaeedpxDfBcX6cJcSxgpKntmYkBZhJ726Vfbs0ykVTm2UuZoW5ksnAdgoQc6K8V8RJVBZlalnIYX3Alb0KqirPr9XasaAlyPORkumpC2l4r%2BRSv%2B4EHluPRWBgRbmG0DPVX/U1diR%2BoHmjOAQ68Wdi7/4Yemjh91lNbSUeZtINm3NlBg3jZAKIlUYIwT%2BEkf2tRve/SduW8D1bY79HN4Lf4YtMi/RqMSJIcRXAhEMQB2CEvEaJ%2Bo%2BDYEsfpfR279IIirIzhJBAA)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/terse_independent_find/implementation.hpp)
- [Source code](../../../../conceptrodon/pagelivore/terse_independent_find.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/terse_independent_find.test.hpp)
