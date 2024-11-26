<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::IndependentLeftInterview`

## Description

`Mouldivore::IndependentLeftInterview` accepts a list of predicates.
Its first layer accepts a list of elements and returns a function.
When invoked, the function first binds the elements to the front of every predicate;
then, it returns the index of the first argument that satisfies all newly formed predicates, or `-1` if it cannot find the argument.

<pre><code>   Predicates...
-> LeftSides...
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> Exist (...&& Predicates&lt;LeftSides..., Arg<sub>I</sub>&gt;::value) ?
   I : -1</code></pre>

## Type Signature

```Haskell
IndependentLeftInterview ::   template<typename...> class...
                           -> typename...
                           -> typename...
                           -> auto
```

## Structure

```C++
template<template<typename...> class...>
struct IndependentLeftInterview
{
    template<typename...>
    alias Mold
    {
        template<typename...>
        alias Mold = RESULT;

        template<auto...>
        static constexpr std::make_signed_t<size_t>
        Mold_v {RESULT};
    };  
};
```

## Examples

We will find the indices of `int**` and `void` in list `int, int*, int**, int**`.

```C++
template<typename...Args>
using Metafunction = IndependentLeftInterview<std::is_same>
::Mold<Args...>;

static_assert
(Metafunction<int**>::Mold<int, int*, int**, int**>::value == 2);
static_assert
(Metafunction<void>::Mold<int, int*, int**, int**>::value == -1);
```

## Implementation

We will implement `IndependentLeftInterview` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:** Check several parameters at the front of the list.
If a match is found, then its index is returned.
Otherwise, drop the checked parameters and call itself with the rest.

Here's a simplified version of it:

```C++
template<template<typename...> class...Predicates>
struct IndependentLeftInterview
{
    template<typename...LeftSides>
    struct ProtoMold
    {
        struct Slash
        {
            template<typename...>
            struct ProtoMold
            { static constexpr auto value {-1}; };

            template<typename First>
            struct ProtoMold<First>
            {   
                static constexpr auto value 
                {
                    []() -> std::make_signed_t<size_t>
                    {
                        if constexpr 
                        ((...&&Predicates<LeftSides..., First>::value))
                        { return 0; }

                        else
                        { return -1; }
                    }()
                };
            };

            template<typename First, typename Second, typename...Others>
            struct ProtoMold<First, Second, Others...>
            {   
                static constexpr auto value 
                {
                    []() -> std::make_signed_t<size_t>
                    {
                        if constexpr 
                        ((...&&Predicates<LeftSides..., First>::value))
                        { return 0; }

                        else if constexpr 
                        ((...&&Predicates<LeftSides..., Second>::value))
                        { return 1; }

                        else if constexpr
                        (
                            ProtoMold<Others...>
                            ::value != -1
                        )
                        { 
                            return 2 + ProtoMold<Others...>
                            ::value; 
                        }

                        else
                        { return -1; }
                    }()
                };
            };
        };
        
        template<typename...Agreements>
        using Mold = Slash::template ProtoMold<Agreements...>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGz%2BpK4AMngMmAByPgBGmMQgABxBAA6oCoRODB7evnppGY4CYRHRLHEJAOwAnLaY9kUMQgRMxAQ5Pn6BdQ1Zza0EJVGx8UlBCi1tHXlctpOD4cPlozUAlLaoXsTI7BzmAMzhyN5YANQm%2B24EAJ4pmAD6BMRMhAoX2CYaAIIHRyeY50uyAm6CwVHenx%2B3wImBYKQMMIuV1h8KYiMuNzuzDYADo8e9TscmAoFHiccpiJh8KIYW99h9vhNiF4HKcAJIMLBYrCCEKYKgEDkw4gANzwmAA7pCTJUrN9TgrTjC4QjMEjMYxWJgyXyBUI8Fg6QyvorTkyWQRThTUEQALKedCQ00yuUm02K82soQGBQIJ3uhUu/0B03K1Hoq63TW4/H04MhhWey3Wu0O%2BMJl1mlqOZCEgQTTCqFLEU5MLxEU4isReAEugC0XBlABELhZzpUW/tXemQ2HVeqo9iAQAxPDECYQ%2BUJj1PC1W4g21D22iOy6j8cESdu6fttuBqc700TNF4XNoBgFoslssVqveWsHw%2BB2U9p%2BBgCsVnfTYgq1OdYJEEQBAFgmAAaweDJgAidBHiRDIAC8Hk3ONHzfRUgzQ9D3TwKg8wvGEr3OLDsMVKAyXMfxKIpKlTzRTA6TcXVhANBiyVIU51wnelgLvGtVlWV9SN3U5KQILYGFODRW3bFtviE0j6iUBTsMzMSJP/Rsu1klSd2bX9dPdZtW0M4yu2lEj3T7eiByxLVOLHCYOI1IdTiETBz3QZzBy1MkAHkCAQeIjUMpN50XZdVzcLiCA49zPI4gKgvHCjUO3adM33dKn2PHN8MvYtS3LVBK2rB9ssPTCKvQkxP1qn8/wA%2Bks3QYDQIg%2B4oJguDLkQ5Ct2EjCX0s0jcPywjCsMp9yPxMwqLmmjqXoxjmP1Q12Icjd3l4sqBKmyrZVEzBxOISTpO04z5JG7ClIBMbzwKkt9p3GacUo6jKSW2kkVW1jSTxOKPIEVdsB2%2B89uumrDvU07Ti0ttLqharhNu057vzCbiGe6cIGxp8UyXNNLiS4LUuNQadzBmtTjAMALibTS8ZDQTIbfTMmZ3GHJLMc5LHC1MVyREmUtjcmKYTKm1Qu1mn0Rjn3Vu%2BXnWh46NIbGTEfF/SWeRjMOxM1mzNdPXO2NkMhOsiMXN8vEvmASlYUYAgQssrwMiMU5IsBBnvWJJAQEtgECcipE7YdthBH%2Bt643Mx8jYs9LA9s6NtVt%2B3MEdyOBsVN3wmAT2HW9/nCcFy4w4ziPnbJg2fn12OkYAegAKhb1u2/bhvIWb1vTgAFQY53Tjbzvvm79vx5bkekd%2BBhji8M4kXPHYUmdrdISTjEfJjHEvmIYAXa%2BXOPdtY6mCoLxZ8aIuOS5VwneYoV4jFSV4IIVqQDwBROq1LdgJDsu95RwhPXSEuVTz3GJEoNokIIAnxaOfS%2BWQkThAIC3baIB/5uBQRxFBTccGCBbvg1BTd0F8VrPsTsDMzCCXrmA5AECSTxE3N8WBp8EEOCQZcEUqADToMwdgtGBCiGEMEcQ0hZVvb000jQiwHB1i0E4O%2BXgfgOBaFIKgTgbhrDWDNJsbYtYzD7B4KQAgmg5HrDAiAd8kgcQaEkFwSo%2BwNDvg0HNfwZhEiJH0JwSQvAWASA0BoUgKi1EaI4LwBQIAgmmNUXI0gcBYAwEQCATYBAUjlnIJQNAcI6DxEiFqTgqhkh1n8JIU4wBkC5ikDiMwvBaJEGIAaPQ/BBAiDEOwKQMhBCKBUOoWJpBdCzAlM8FInAeDyMUcosx6jOB%2BXLOky0qA8JFP8CUspFSqk2J5hADwOT6BPUMVwVYvAYlaHWBAJA2SUi5LIBQCAVybkgGAFIMwfA6DCkiRAGI0yYjhFaNcMZvBfnMGINcPyMRtAeRicY7Jlc/IMFoAC/pWAYheGAG4MQtBIncF4FgUCRhxDIrHFCvAIoGLTMLB5csuxjEoPqNM2geAYjPFBR4LA0ynh4H8Ti0gZLiAxHSJgJssJDDAEZUYMx6wqAGH3gANXFBKPyWJAVdOEKIcQnSWnyCUGoaZgz9CipQNoyw%2BgmWRMgOsVAK8sjYrrCCemphLDWDMKEvljTDTwHWHYElzgICuGmH4WYoRFhlAqPkdImQBABvDYULIQxQ2jFmN6jhAh%2BhTE8J0PQybGhpoWKUEYCQk3zGjUWgY8aC0SC9XonYlbvEcCUcE6ZYTTgrLWeUypcMtmnAgLgQgJBeZGOOSYyV6wgpMCwAkX8pBLGSH2Diao%2BxKiSDsWYSQ/hAnvn8LUBRHBfGkH8UYnE/guD%2BESNURIJ7rFcHfAuoIITeBhIiVE4dsTzlJIuSk%2BZGS7kPP2fktgnBWgsBFJUOsTBCQGA9lwaoOIuC2LqfgBpTTZharaRq6QWqem6v6boV5wymCjJxRM%2BtUz%2BlhLmWk8spwlmlmIMB0D4GiRQZg3BjQ3bdnXP2QO6hJzJXxMuagPZ8RMn3ME5x0YQGQN1iY886oXAgk0FoB8yg3z%2BnAv%2BSq9ToLwWQocCq2FTt4WIumSitFGLaBYpVXi0VhK1H4EpBwsl2K1GUuQNSlVdKd1qMZcy/5bLdhqM5dy4xfKBVKGFfisVec%2BPSqYHKhVSrGAqtQ%2BqjpGHZBYb6Wo3DBqJWOqsCanz5qp1WsaLa%2B1FD8vOtdfEd15KLU9B9X4P1nIS3BE5OW5YhbSAFEjdkDNMwesRsaJ1sNSb6hNdzW17NfR5ijcTXMAY025shorUcjYWwa3rZ3Q2%2B9MyOC0fo2BiDoq4Ysdsd23tDSB1HN46%2B0dmBx2jCnTuvdB6YN2MqDeyojjJCrtKbMPbj7bDPtOXEhJyTUkLJE7%2BvJBSOBAdKacFgCgRS5hFNBnEqoJgIb7e65psg0NpdVZlvVIB9ikHw4R8ZdbdtNtmV%2BxZeFEdlJR2jysmPseWh2WJm5A79hDrB%2BcgTQnblZN5/skAaOUgpHuBj6o9wucQLo6Ut5SngoqZ%2BX80FmntdgohVC/Tgm4UIqRXZzAqL0WYuxcY6zBKAu4uJY58l/TXPuZ5Z5hlTKWXXH8xyxpwXeChcFRFmz0XX18BlQoeVkpEsqOMSl9pEh0vdJ1VlnQ5PcvGGNTYIrnr1HWvzJwBuQEquWBdQ%2Bt1f188zd9f6gbgb2voHm913rjQ2tt7jatrrWaJspqaMWhvvfeippW/mnvpb025Eb8eNoLfa0KGrR04jdOyOcEO0jtn6POfLW51d/tBxbsvrOQ9p7k7iNvZAGYGD%2Bx9jvhcfYwJt/KinsbWv8JIPokjunSASQ7553viJBzTVCSDVCOKLpcAU47r7CkahKcB3Yn51q1Jv5wEf5C7rB8oZDOCSBAA)

## Links

- [source code](../../../../conceptrodon/mouldivore/independent_left_interview.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/independent_left_interview.test.hpp)
