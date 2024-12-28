<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::IndependentRightInterview`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-independent-right-interview">To Index</a></p>

## Description

`Pagelivore::IndependentRightInterview` accepts a list of predicates.
Its first layer accepts a list of variables and returns a function.
When invoked, the function first binds the variables to the end of every predicate;
then, it returns the index of the first argument that satisfies all newly formed predicates, or `-1` if it cannot find the argument.

<pre><code>   Preds...
-> Vs...
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> (...&&Preds&lt;Arg<sub>0</sub>, Vs...&gt;::value) ? 0 : (
   (...&&Preds&lt;Arg<sub>1</sub>, Vs...&gt;::value) ? 1 : (
            &vellip;
   (...&&Preds&lt;Arg<sub>n</sub>, Vs...&gt;::value) ? n : -1
   ))</code></pre>

## Type Signature

```Haskell
IndependentRightInterview
 :: template<auto...> class...
 -> auto...
 -> auto...
 -> auto
```

## Structure

```C++
template<template<auto...> class...>
struct IndependentRightInterview
{
    template<auto...>
    alias Page
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
/**** Equal ****/
template<auto I, auto J>
struct Equal
{
    static constexpr bool value
    {I == J};
};

/**** Metafunction ****/
template<auto...Args>
using Metafunction = IndependentRightInterview<Equal>
::Page<Args...>;

/**** Tests ****/
static_assert
(Metafunction<2>::Page<0, 1, 2, 2>::value == 2);
static_assert
(Metafunction<-1>::Page<0, 1, 2, 2>::value == -1);
```

## Implementation

We will implement `IndependentRightInterview` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:** Check several parameters at the front of the list.
If a match is found, then its index is returned.
Otherwise, drop the checked parameters and call itself with the rest.

Here's a simplified version of it:

```C++
template<template<auto...> class...Predicates>
struct IndependentRightInterview
{
    template<auto...RightSides>
    struct ProtoPage
    {
        struct Slash
        {
            template<auto...>
            struct ProtoPage
            { static constexpr auto value {-1}; };

            template<auto First>
            struct ProtoPage<First>
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

            template<auto First, auto Second, auto...Others>
            struct ProtoPage<First, Second, Others...>
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
        };

        template<auto...Agreements>
        using Page = Slash::template ProtoPage<Agreements...>;
    };

    template<auto...Args>
    using Page = ProtoPage<Args...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKxcpK4AMngMmAByPgBGmMQSGmakAA6oCoRODB7evgFBaRmOAmER0SxxCVxJtpj2xQxCBEzEBDk%2BfoG19VlNLQSlUbHxickKza3teV3j/YPllaMAlLaoXsTI7BwA9ABU%2BweHR8e72yYaAIJ7BwDUACKYKa6MyHiYCjeHZ5fXJ39H3wu5yBZgAzOFkN4sDcTKC3AQAJ5PAD6BGITEIClh2GB5nBDEhXmhsLcyHG6CwVGxuJ%2B/zpAOBv12NwAkiwUvQ2IImA1PgdAUz6f9AcCCJh2QYxSSxRKeZgSUwvEQAHSq7E3SFMBQKVXK5TETD4URirGgnGXcbELwOVkMLBPO2MAgAJTwwAQBBZgniADc3gB3XEAdislxu4ZuMo5coVStQutd7uEeCwpvNFwjN0t1oIN31qCIyiYwHlYYjJhDwMzmezNqEBgUCCr1fDFdDGZb1ajkvlcMVKrVZubnYjtdz%2BcLxdLHZHrZDWeajmQGoE40wqhSxBu/dQNx9Yi8mBhIYAtFwK3dYRZj5fQe3h7PuzG%2B3GbgAxPDEcbUsuzhdWm0J1QIsSxJD8vwIH8Z1nNty1/P9R0XPBlzQBg1w3Lcdz3A8jwfBDj3bfCRxMfwrH8O4ICWG4T3VckQBAFgmAAa0wZEMmACJ0FREkMgAL1YyCh3gojy0rYSROrPAqBXNCxQwmFxIkiMoF1cwADZ1P1Q1kLlU03HA8ZSBuRMPSEFN3lUs16P3bxMCWJY8KU0TrwNAh1gYG4NCvG8aWgpyIzqJRHP82DXPc6jzzvHzFKIi9KOCmCg1vQiEIvK9fPwp8pRfIh30/Qzt1fIRMFQ9AjJ3XUAHkCAQeI0wSms0RzPNiALYCpzA/KCCM4rSqM6raq/Sz03w2DWxikdZiXGT0M3Qrcpsw8FL81KxJWkSSLIiiqJos0F3QejGJYti3U47i4T4gSoP8ucUpuiMpJmuS5oaiSVLVMwNM%2BrSjV0zqIKMkzk1TYbrJw%2BzXo2%2BcwuIDyvKitLLkhojAqPR7UNmrdkfw97lXUzSDV%2Bk0SV6gQyuMt1TPMnVB2wMHbIhiaJNCzA3Nhm5IuvRGgSZkTUZudHV2e4hsYQiBRZEoCQN7NwBrq4aJaI%2BmlrAMBYTuCLFZHBzedi%2BctYQmGPLMGFLBatrpZJOWhtpg2/2V3sud10akoy%2B6AtoILndWlzWfCs9vO5%2B64p19bEuS5G0rvBKo/vGKsplirVQuYADXFJ16pirwMiMPMpxhUENfrLUkBABPzcnUC4RTtOuQIGm8aHaP4Njt3wwT2MB2VC5iGATPoOz8JgDzksC41qWOur3uG%2BpZugVdufGSFBlaVubBVFYDkjy%2BJfl/5XymRubAAEcvDEPl9kBDuct3FlytfAApKCxyP0%2BxGDO6Fx5ZCnvXOaYlQJ4bCtkHxthZGPdWNwn4L3vDAg%2BhwbgAFlWZMCoF4AkvId6XGvm4JO3dp5QUHrnZBzQ0EYKyGPW09pniCCBl6MUxA/SYEDHCE%2BZ9aBQXopbKefcFaL1XvsG4AAVd49cL6nGBFNZCyItRKFaMCCAJDUHoIcFkEkZhsRcMnm4DQRkgg3GSAYzRIBFq4ULpAswDk55SOQDI7U8RIKXEUSgshqiBAkgDlZEA3CdF6KMoYjRXjTEQMLhFKxFgOArFoJwfwvA/AcC0KQVAnA3DWGsFmNYGxcJgh4KQAgmhIkrCYgESQyoNAAA4zBmAAJzVK4P4Cp5SuBBiDNIaJHBJC8BYIkXR8TEnJI4LwBQIBdH5ISZE0gcBYAwEQCANYBAUhKnIJQNA7I6DxEiKwLYqhylqRPGpSQNxgDIGXFIZUZheDaSIMQFMeh%2BCCBEGIdgUgZCCEUCodQ4zSC6CCP6dEKROA8CiTEuJBSkmcEqkqRZuZUDSR2Xsg5RyTkc1KSbCAHg1n0CxjkpYvAxlaBWBAJAqyUjrLIBQCAJKyUgGAFIZINBaAMOGRAGIYKYjhBaAiQFvB2XMGIAiSqMRtAlTGbk1ZddKoMFoFyr5WAYheGALg2gntuWkCwIxIw4hZWfhFXgH07wwXrhKkqLYuTwhinaYk2geAYjon5R4LAYK0R4G6dwXg%2BriAAKUA8DVwBrVGAKSsKgBg%2B4ADUAyVQdKq%2B5whRDiBeTG95agwU/P0IYYwaTLD6BtcMyAKxUApAaMMjgJ5yTq1MJYawZh%2BkepuameAKw7C6ucBAVwUw/BBFCOEIYFQRgFHSJkAQ7a9CFEHQweYwwqjdGbY0CYbRPAdD0E2txs65jdoWH22wc7h1BFmK0CdvaqiNsyZsCQwKOCxNIH03gAybjwv2Yc45pzUU3AgLgQgJBTagi4LivJgaVi1SYFgBIlFSDFMkKCZU1TQStI0JIMwkg1IaA0P4NS1T9CcE6aQbp37lRqS4Gpcp1SmlqX8JIep0G1JXrBQMoZIy/3jMJTMolcyoVLIpVSrFmy2CcBaCwH0QYTxMA1AYXOXBqnKi4GUy5%2BBrm3KCDGx58bpCJqUMmr5uhkh/KYACt157L3XvBRwSFCylQ3FhXe3ZD6RPpo5hJqTGhX0YtJVir9li8WBsmcS1AmL4jLMpT5lzIxNRGHE9UPgdAmWUFZV83lnLVVxf5YK4VDhVXiqdJK6VYK5UKqVSqt1arxTpq1Yk/ABpVH6uLYko1yATWqvNXUMF1rbWcodVsRJzrXW5I9V6zAPritD088G4sChw3MMjYwaNsglPPJU7IJNnzEmabTQGitVgs3NdzaBgtRbOCloIOgctmaLDVpvbW6mDbp0rpcHaHdwQ7QHsWP2ooWQ7ujoaI9zdy6Gh9EmAuvIu66gzt%2BwMddk6l3bv%2Bx2rda6yjg5/asdYp6EftIMzRzglmEWHJC8PcTkmymvvfdcr9P6POMYA5gIDIxQPtKwzhiTcGgz%2BGqS00E8HEPkeo182jth6P4omVM2Z8zoX%2Bc4xsrZvHiAsERSwBQPplw%2Bjxz2cYMmP11rudNuNs3XnyDU4tnQIBQSkG07poFGGL2gu5xCtjMK4Uy7lwrpXulczosC2Sr9oJf388Jd53z5KVlu6xSY5AKQUjIkV9U5EyuCDIlUAciLjK6rRbZRy/lCXU8CqFSKtLPmJVSplaVzA8rFViHy7k9VxX2u8DK7qyrhrVDGrFPV70lreDNbtQiNrTqbldfdfEXr/XNWDcY3wENo2I1RoK4prXEg5tvL1ymw3K2M2Vo2zmy7O2sjFu2HRNbVaa3xDrQavNV2Gg3fcFDvQXa4eHpHQOhob379ZE%2B1O77vRIe5Gh2/gQIOX8Q/6HdnuqDjfk9sekjs8vppbv0hjnHocrLvLnuE7iaC7kTp%2BniKTgxgShTlTiBuenTiADUsqKCKCP4A0uRshsQUGIRlztAYMrzqMv%2BmBiAJIP4FBs0kGMhuUpIHUlwJUp9ObqCFATepwGTlgebhcjQcIXQd7isB6hkM4JIEAA)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/independent_right_interview/implementation.hpp)
- [Source code](../../../../conceptrodon/pagelivore/independent_right_interview.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/independent_right_interview.test.hpp)
