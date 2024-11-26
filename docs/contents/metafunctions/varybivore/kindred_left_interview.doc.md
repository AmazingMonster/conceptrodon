<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::KindredLeftInterview`

## Description

`Varybivore::KindredLeftInterview` accepts a list of variables.
Its first layer accepts another list of variables and returns a function.
When invoked by predicates, the function first binds the second list to the front of every predicate;
then, it returns the index of the first variable that satisfies all newly formed predicates, or `-1` if it cannot find the variable.

<pre><code>   Arguments...
-> LeftSides...
-> Predicates...
-> Found ?
   index : -1</code></pre>

## Type Signature

```Haskell
KindredLeftInterview ::   auto...
                -> auto...
                -> template<auto...> class...
                -> auto
```

## Structure

```C++
template<auto...>
struct KindredLeftInterview
{
    template<auto...>
    alias Page
    {
        template<template<auto...> class...>
        alias Rail = RESULT;

        template<template<auto...> class...>
        static constexpr std::make_signed_t<size_t>
        Rail_v {RESULT};
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
using Metafunction = KindredLeftInterview<0, 1, 2, 2>
::Page<Args...>;

static_assert
(Metafunction<2>::Rail<Equal>::value == 2);
static_assert
(Metafunction<-1>::Rail<Equal>::value == -1);
```

## Implementation

We will implement `KindredLeftInterview` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:** Check several parameters at the front of the list.
If a match is found, then its index is returned.
Otherwise, drop the checked parameters and call itself with the rest.

Here's a simplified version of it:

```C++
template<auto...>
struct KindredLeftInterview
{
    template<auto...>
    struct ProtoPage
    {
        template<template<auto...> class...Predicates>
        struct ProtoRail
        { static constexpr auto value {-1}; };

        template<template<auto...> class...Agreements>
        using Rail = ProtoRail<Agreements...>;
    };

    template<auto...Args>
    using Page = ProtoPage<Args...>;
};

template<auto First>
struct KindredLeftInterview<First>
{
    template<auto...LeftSides>
    struct ProtoPage
    {
        template<template<auto...> class...Predicates>
        struct ProtoRail
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

        template<template<auto...> class...Agreements>
        using Rail = ProtoRail<Agreements...>;
    };

    template<auto...Args>
    using Page = ProtoPage<Args...>;
};

template<auto First, auto Second, auto...Others>
struct KindredLeftInterview<First, Second, Others...>
{
    template<auto...LeftSides>
    struct ProtoPage
    {
        template<template<auto...> class...Predicates>
        struct ProtoRail
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
                        KindredLeftInterview<Others...>
                        ::template Page<LeftSides...>
                        ::template Rail<Predicates...>
                        ::value != -1
                    )
                    { 
                        return 2 + KindredLeftInterview<Others...>
                        ::template Page<LeftSides...>
                        ::template Rail<Predicates...>
                        ::value; 
                    }

                    else
                    { return -1; }
                }()
            };
        };

        template<template<auto...> class...Agreements>
        using Rail = ProtoRail<Agreements...>;
    };

    template<auto...Args>
    using Page = ProtoPage<Args...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQBspK4AMngMmAByPgBGmMQSZhqkAA6oCoRODB7evv5BaRmOAmER0SxxCVxJtpj2xQxCBEzEBDk%2BfoG19VlNLQSlUbHxickKza3teV3j/YPllaMAlLaoXsTI7BzmAMzhyN5YANQmO24EAJ4pmAD6BMRMhAqn2CYaAIK7%2B4eYJ2fI43QWCoLzenw%2BBEwLBSBkhpzcTC8RAAdKjQR9xsQvA4jgBpcLoYiYdAhTBUAgASUE8QAbnhMAB3MEmADsVg%2BR05R0h0NhmHhiJRaJ2rw5XMx2IIR2UxFQRGUTGA/LFnNZ7PeXM13KhMKYcLOPN1%2BoRSNQqORLyOByYCgU5plxLwokhzxFYK14vukulsqIACVHrR3R6TmyjrNHMgrQJxphVCliEdBagjjSxF5fmqALRcVkAEVOFlDBZ26uDHsNfPhlb1/LOyfNluttvN72ARKhjAIrtFGpDXgyRiOAbofzzPrlqBHQbObY7bEEduFr1L5eLheZKu1vNrAtNreIwB7a4H4WA0sVmZ245lk4VSvh70PS4tbtXH3zG4/EJ1VfrpqOAAxPBiHGdF3glHF8QYQliVJckqUhYg6UZeFgNAghwLVNca2NBtUXg4Q8CwY8t0gqVb3lS812wrdNVwutzl/Xd/yFV9sCtAwW1RB18GdTBSL7D1yInf1AzXTU1S5CSQwjJ1owYWN40TZNU3TTM6JDWihJDD0TAAVisfS8wgJYjizS1ARAEAWCYABrW4MmACJ0DueEMgAL1uTC3U03TVTZGT/K1PAqAUpSExOPzgq5KBGzMAJzACXinVrV03EIoRiIE81SCAkCwJFay028TAliWIKYoCosiQIdYGCODRC3Xb8dKqzU6iUSqqqk2r6vM3NSxatqYvzUzuuklkS3VXTP3fcERs5Bjq2YvD92XTibRfOdME7RdwN008h2nMdRKncTZ3bXaF27Rs3xmybps3HTltYs1USfI8Dq5I7z3vK8b19VB/sfZ87pXMspq/BbXpNIh8owvLVKETA0BgpH1uRAB5AgEHiQSROg2CSTJSlqWQ%2BkmTOdDxjylG0fQPKcbx0DweZQKt1h/DkUy7LBM1ETKOB6it203TYa5zGmy4l8Uv4/nZK9HEhenSqpNVaKBeaSNwshZSkwAkqMyixatTF9rVUMgyTLMiyRXDAh0Gs2yHJuJyXLcs5PO876LfNi3NVC3W40iibgritEEqSuW0vhXmSNyhHCuwYr1PKsP/N6zA6uIBqmqGz9WoDrVOt%2BIO0YixMM90iOLSjhKY5dOPSayhPUTp1GBHQF5U9K9PNdGsM%2Btzo5BqLQuFuLjraCUI5y5jPWE2rkMIGX4KiaJEmEPJlCqbcZn8bZgeLeshiLwfM545y5c1/80/Vt%2BVWzkb6/2Nv3Te%2BNsAwFOccc3frkFVj6ZzDAAj0w8GpmBOJYPEBJN6EUQrSSm8ID6sxvsAqq98dyQnPoxK%2BL5fZT01Fgo0j8LpuBfgQ3ypti6fzrOPDBWkoZFyIUcUuYDQw1Wzv1f%2BBdmE0KYTbDOc0Hp6ShvNSqEsH57jYtLLarYrp7W7IQzUv1hyBlOirchO0lFUIhjRcRZZObSLegeL61DVGDj%2BpeTRQMQazjBjfCRhjnoAHoABUnivHeJ8a4sEHivFHAACoCW7EcbxfiPgBJ8TEzxkSYYmLhimCkGN4YAClwIiWwAARy8GIdmoiHZ6nkhXReiYYioE8GpUqBiLAUjHL/I4GSXEfhaQk7BjFuafUEmogAstnJgVAvAMAcFkU6G84Kk0QRTVCZxkijzymYRZ4FrL2LcN0tmEiMTaydDcLa8RMIfAgP05oQyRkNHhGYHuIAn5uByXkmcKcQBGwBo0swFV5pyWQHs20BywTHIGWc0ZAh4S8Kebc%2B5%2BSirPPUg068A0PkWA4CsWgnB9K8D8BwLQpBUCcDcNYaw4Y1gbEzGYHYPBSAEE0MilYdkQD6UkMiDQkguAsh2BofSGgEoBDMAADl5foTgkheAsAkBoZImLsW4o4LwBQIBkhUqxci0gcBYAwEQCANYBAUhInIJQNA0I6DxEiKwLYqheUBCzAESQRxgDICjFIZEZheCOiIMQYieh%2BCCBEGIdgUgZCCEUCodQSrSC6C4KQBkDwUicB4CitFGLqU4s4FjJEOqpSoDCuay11rbX2tHoyqBEAPCGvoFXMlXAli8EVVoFYEAkAGpSEasgFAICNubSAYAUglk0FoEhOVEAYhJpiOEFoFxY28BHcwYgFwsYxG0KjRVFKDU3SxgwWg47Q1YBiF4YACJaAzwnaQLAtkjDiC3SBRdeAaQCSTXGVGSItgUvCJCVFobaB4BiA8GdHgsBJvuHgUV3BeA3uIBUpQeYoSGGAB%2Bow1KVhUAMEeAAapTLG1xMUUq9cIUQ4h/XYaDWoJN4b9DQZQASyw%2BhP1ysgCsVAKQGhyo4FmQEv9TCWGsEkXgqBQPupIvAFYdgr3OAgK4KYfgI2hHCEMCoIwI2FEyAIcTegFMNHmMMKo3RhONAmG0TwHQ9BCeBTpuY0mFhydsLp5TEbZitHU7JqogniWbAkPGjg6LSCSu45wI42arU2rtQ6wtRwIC4EICQaB5Kq2UvgysPGTAsAJFMqQOlkgdjIgAJw7BZJIZlZhAjiv0gEDLgqODCtIKK8lyIAhcACLyjLvLasMq4PpLLQQvPJplbYeVMWlV1vVfWzVabdWtvbWWk1bBOAtBYDSFkWYmCbSHFwDLyIuBMpdfgN1HqI3YZ9Xh6QBGlBEdDboJZUamAxuA25jzHXpWpu1UiI4makzEBm3Nhb1olsrbWxoELJam1lsi%2B86t8GVUNtQKW%2BIeq20Q4ByMabs2syfa7RlrgyRe39soEO0NU6x1HtxzOudC6HBHpXV2NdG6k3bt3fuw9wHj1QbPVsbF%2BAiSjJvUx7F97kCPqPS%2BuoSaP1frHb%2B5n1b3VAYpaB8DmBIOnpg2eUHiHFQKFQ4ydDjAj27dw36g7shCMhuxad0jcH2NWEo0LmjyX6OMc4Cxx2bGKMWC4zi3jfMBNaeMy4GC1nggwXs4seT6RFPZH03kIPRQsgB4s0ZhofRJhh4k57uPuno%2Bads3p3ISeM9p9c6sdYLnK2lZu0m6VL23vzcW%2BeZbq2mUhbC26yLlaQd9bi5gBLIxktvvK5VlbzKWStZZGyyQ%2BXrURtu5wWVPWa3KtVRqrV6bodjeNaaqbr3c0sAUDSKMNIa98nGBt8LfHPWyD27rgN8gjuG50CAHYkbo0Tuu4m0Nd3hsZrCtNjfW%2Bd977SlKYtsOzakWOw0WM%2Bda4OkOLa%2BqgBZazyyAKQKQNwu%2BGWNw%2B%2BBAey6%2BB2dAmOg6w6o6M6%2BO%2BBs686i6pOEOq666m6LOmAO6e6YgdOFKJ60G56LOl67Ot6oa3OvO9O/Ob62KQu36Fwou/6EuR60u6QsujOCucGfWfASGquaGGGWup%2BOuEgeugaV%2BxGt%2BJuxgTuVGMQVudGDGWQTGriVkZunGUqbu/GtGyeWQ3u7gieegUmZQGmKmweDQvuqmUeZmbhNmdQ2m8emeBm/hPQAgQRueNmVmThURpmrhDmeeCgzmfqT%2BnmpePmn%2BNqm%2B2%2BqYv%2BLo/%2BDeEWuwzevWtabeHeSWbmPeIAZgK2OwOw%2BknKLK4q9RLIdWaRL%2Bk%2B3WCqsWKW/g%2BkmW%2BkvKCUGWkgGWbK2WXAd%2Bb6Owz%2BUqXRYBbmzqHR8xXWixpAoGGQzgkgQAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/varybivore/kindred_left_interview.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/kindred_left_interview.test.hpp)
