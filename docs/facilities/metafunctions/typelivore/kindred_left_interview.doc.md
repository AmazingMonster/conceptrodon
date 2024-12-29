<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::KindredLeftInterview`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-kindred-left-interview">To Index</a></p>

## Description

`Typelivore::KindredLeftInterview` accepts a list of elements.
Its first layer accepts another list of elements and returns a function.
When invoked by predicates, the function first binds the second list to the front of every predicate;
then, it returns the index of the first element that satisfies all newly formed predicates, or `-1` if it cannot find the element.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>n</sub>
-> Interviewers...
-> Preds...
-> (...&&Preds&lt;Interviewers..., E<sub>0</sub>&gt;::value) ? 0 : (
   (...&&Preds&lt;Interviewers..., E<sub>1</sub>&gt;::value) ? 1 : (
            &vellip;
   (...&&Preds&lt;Interviewers..., E<sub>n</sub>&gt;::value) ? n : -1
   ))</code></pre>

## Type Signature

```Haskell
KindredLeftInterview
 :: typename...
 -> typename...
 -> template<typename...> class...
 -> auto
```

## Structure

```C++
template<typename...>
struct KindredLeftInterview
{
    template<typename...>
    alias Mold
    {
        template<template<typename...> class...>
        alias Road = RESULT;

        template<template<typename...> class...>
        static constexpr std::make_signed_t<size_t>
        Road_v {RESULT};
    };  
};
```

## Examples

We will find the indices of `int**` and `void` in list `int, int*, int**, int**`.

```C++
/**** Metafuntion ****/
template<typename...Args>
using Metafunction = KindredLeftInterview<int, int*, int**, int**>
::Mold<Args...>;

/**** Tests ****/
static_assert
(Metafunction<int**>::Road<std::is_same>::value == 2);
static_assert
(Metafunction<void>::Road<std::is_same>::value == -1);
```

## Implementation

We will implement `KindredLeftInterview` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:** Check several parameters at the front of the list.
If a match is found, then its index is returned.
Otherwise, drop the checked parameters and call itself with the rest.

Here's a simplified version of it:

```C++
template<typename...>
struct KindredLeftInterview
{
    template<typename...>
    struct ProtoMold
    {
        template<template<typename...> class...Predicates>
        struct ProtoRoad
        { static constexpr std::make_signed_t<size_t> value {-1}; };

        template<template<typename...> class...Agreements>
        using Road = ProtoRoad<Agreements...>;
    };

    template<typename...Args>
    using Mold = ProtoMold<Args...>;
};

template<typename First>
struct KindredLeftInterview<First>
{
    template<typename...LeftSides>
    struct ProtoMold
    {
        template<template<typename...> class...Predicates>
        struct ProtoRoad
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

        template<template<typename...> class...Agreements>
        using Road = ProtoRoad<Agreements...>;
    };

    template<typename...Args>
    using Mold = ProtoMold<Args...>;
};

template<typename First, typename Second, typename...Others>
struct KindredLeftInterview<First, Second, Others...>
{
    template<typename...LeftSides>
    struct ProtoMold
    {
        template<template<typename...> class...Predicates>
        struct ProtoRoad
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
                        ::template Mold<LeftSides...>
                        ::template Road<Predicates...>
                        ::value != -1
                    )
                    { 
                        return 2 + KindredLeftInterview<Others...>
                        ::template Mold<LeftSides...>
                        ::template Road<Predicates...>
                        ::value; 
                    }

                    else
                    { return -1; }
                }()
            };
        };

        template<template<typename...> class...Agreements>
        using Road = ProtoRoad<Agreements...>;
    };

    template<typename...Args>
    using Mold = ProtoMold<Args...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKz%2BpK4AMngMmAByPgBGmMQSZgDMpAAOqAqETgwe3r4BQemZjgJhEdEscQlcybaY9iUMQgRMxAS5Pn6BdQ3Zza0EZVGx8YkpCi1tHfndEwNDFVVjAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimKmujMh4mAq3R%2BdXN6f/xx%2BlwuwOS4WQ3iwtxMSTcBAAns8APoEYhMQgKGHYEHmJLgyGYaGw5ATdBYKhYnG/AE0wEgv57W4ASRYqXobEETEaX0OQIZtIBQJBBEwrIMIphcMRjFYmAAdArKVcJsQvA5bgBpcLoYiYdAhTBUAhMwTxABu7wA7jiAOxWK63R23EVirmYSUI57MNgKuVKy5O24qtUEW7KYioIgAWU86BBgZMdvjgadLrZbo9ovTEthnplPsVSWwtwhTAUCl94b1eFEIsxReTKaDqJDYYjRAASqgmHGHU3oXbm1yayWBBNMKpUsRm%2BgQCAWEwANaYJGZYARdAoyWZABeK4IWNuZrEXkJiYsAFouIn7jCLAPb0l7cC%2B020%2BL3bmsx%2BPdLvfLC2LUty19S5gF1UVGAIetsVfFMvEyIxbi7HsiXuNtI1QFC41hMCII5aDfUpJ9GwfO8qQDVNvwzXM/1lUDiGAGDSIQ8JgFuGNaHQNCMOjWNJUuRiK0A8irhvUSX0ud8aKlL1ZVuAAxPBiAmf1g3VLUGB1PUDSNE0RWIC1MGtWElJUg8GzEpM4OknNZPzAC5V04Q8CwZi4PU0Nw0wzje0ox1z1IwNbM/OFqLsvN/yIosSwMECFSrfBaw%2Bf1%2B2bVV1W8ztuz8tLzydIL%2BzmRxkFHBhx0nacmC8IgjxPM84Ly6z/LSlMTH8Kx/HuCBlluC9D1JOcF2XVc8HXPUt1hXd91S1qm0Cxq5pTPAqDKiqp2hRalqdKAiLMAA2cx9sSms3XrNxnKEVyPl9UhFOU1SiznY9vEwZZlkK7aAsHXUCA2Bhbg0O8yLEravvqJRPq%2B/Lfv%2BvrryfEGWu2m8eqhhMbUfZ8mqxii0pCzNXQiuiCz9GLgOEuU8MwSDBHc5GnVYpDsJ4rKsJygTwJpgjKeI7GCsxiTSIJ2i5NJwSmNmx0mfY3zWfbVBfIEoTouxEirNx0GpPC0LIvksyJjuvW2FuIRMDQLSjZJxyAHkCAQeJ6c8zVtV1fVDWNU1DKtSUDYIO6zYt9A7rth2VNV21%2BcdEX7KihVLuu%2BnA2dtmlbghaGejnXCezXXrdV2Ky0pk7kqToqW0yhXsKh/KArB5OWhKtaRUq25qtql7T02zO2uar6Co69rut6/qYsG%2BclxXNcN0mtxpsm2Ce6aqP%2B6dFbm4nDb0aW3bFQOo6S7OyUE7c277vMrFnvq97t7mmHMD%2B4gAaBxHxK11eUwhwl14t9bp1v1qu8/T7wOofOsx8PZXVPgqAO5sBA4WwFfV6N965LXvo/AGCN7xv0kh/QMX9bg/zHC3KcAC0oQDIUtTS2l3Z6S9kZEybhQ6Owjqg/uc4QocX4rCE%2BN0RJsK%2BhwnWyEOawjAXwsmi88H9iQV3MAYAYToSvJQpsH0BHL27tIpssMn63DMNCSwLstJu2cvpc0PtYTMPDvwpeq8hFE0JErHhkDE6sNsewkAnDq5iLdqdOsbitEplkZ%2BbB6j%2Bw4JUZ/WgkMwnzR%2Bg/OGyjX6C1iQ%2BNGAjxLqx7pk58UMY75PzoBQu8UqZc1ptBKW8FELsRZoo3i7Meyc3wlBXmDYskY01rgqiDjfxi0chLMu0tqlcK4vLHy3C3ADIjlknJFF%2BQCj5EcW42BVCsDZISb49IBR0i1gyDiD8mBUC8IIbIPIDhAgKX0hiktLKXBlvsloRyGAOFOXU6hJiPZmO9sZSU4R/aEMEHsO6fyDjAsBXsf0c4nGTJViJGZ1I7gABUPjQTOWcEExUaxIiLvEA8VwIBRgOU8l5AhfngsviAbxc8CCzhAHgBQq5ZQUs7meJIj50JmA%2BlkzFyBsXllxSCAlRLjkkoYJKM0qBXIUqpePeljK2DMvqmhOpV4uUWA4KsWgnB/C8D8BwLQpBUCcDcNYawQZ1ibDPMkHgpACCaA1asRcARJByg0AADjMGYAAnF6rg/h3Vuq4DaG00gtUcEkLwFgEgNAaFIHqg1RqOC8AUCAWNdr9UatIHAWAMBEAgHWAQVINVyCUDQKyOg8RIiyk4KoN1%2B0Lz7UkLcYAyBSpSDlGYXg1YiDEFcnofgggRBiHYFIGQghFAqHUBm0guguCkEtGiVInAeCau1bq%2B1hrOA2xqkW0MqBVq1vrY25trbbjtv0RADw5b6D/2tcsXg6atCrAgEgMtqQK1kAoBAN9H6QDACkGYPgdADIpogDEDdMRwitHhMu3gkHmDEHhDbGI2hzbpptWWgiNsGC0Bg9OrAMQvDADcGIaJsHSBYAXEYcQ%2BHlJobwGaD4G6JzmxqtsG1fz6gbtoHgGIaJEMeCwBu1EeAo3cF4Ix4gMQMiYEeFR4APGjD2tWFQAwTEABqVobZenIwO4QohxCjr0xOtQG7Z36EMMYU1lh9C8ZTZAVYqBUiNBTRwC8pJFGmEsNYMwCbJO9rcvAVYdh6POAgK4aYfg52hHCMMSoow51FCyAISLegkuNAWCMaoPRQtNEmO0TwnQ9AhdFf0NomX4vZbmFMQr%2BQ53VcGLFxYCXgsWq2BIVdHAdVxo3Ym24h6G1NpbW2l1F7cCEBIAYpIXB722uU6sB2PZRg9VIE6yQSQ5ReqSCGjQkgzCSH2jG/w%2B0vX6E4BG0gUbptyn2lwfabqvWBv2v4SQfqtv7R69OxNybU1zYzc%2B3NL7807uLV%2Bn9N6q1sE4K0FgZobQXiYIXJCXAvVyi4K6rt%2BAe19rnXpodhnpDGaUKZ6duhAMLqYEu8TnXuvxt4Im7dhaaq3H3f1utg2kfsRR2j11txL2oGvfEKbnKH3Kaza%2BgX76b0lu/ZL39pYjAo64LGmgtAQOUHA9O%2BD0HyPa8Q8h1DDhyOYagth3DG6CNEZI7QMj4mKOikszRg1%2BBdQvMY65g1LHkBsfI5xsNBqeN8eg4J7YBqRNiZtZJ6TSg5OO7YmL1TTANNaZ03bvHBmR2E9kCZqdBqycWaU15qwNnA/2ZW05lznB3M0s89Ziwvn6f%2BcTkFnLoqXBaVS9FrSFWliJYyMlnItWotpH7xlprWXiv1Fy2VgreRh8lcaDPnvCXbD5c76v%2BY4/KsdbWBsdrM2ztdfXV9zgbOj1NoV1z1H6ONB8/Gz2qbM3Rf/YW5gJbCQVthou1d1Hu2bT%2BC9WDSSD2wO1e0%2BwTU4B%2BzTTF2zTzQLV3Rl3B0rWrQ4Bh2PRYAUDNFKjNG5w/AmExwmwC37VkHx0zzHXkGJ1zx0BABSApypxXUP1p16y3RBz3QPXQMwOwNwLOlDH50F1vSSCSFm0fUzSByQM/VLTlxvRACwNSFSCRBwK9SRDwIICRFUEbSAzV0dg1wgyg0Q11z0KQxQzQ2NwFywxwzw2d0wEI2I1I1cxtUo0d1D14Bd3o3d2Y1UFYxFF91NH914ED343hBD2E17Qjwk3iGj1kwd2o3j3%2Bz4DUwUE02Mm00YF0xIIzwkCz3HUoLMxoILys28xLzsxbwr2yFcx2EGiLx8z83iACyYwc1b0aHb3cCHz0Bi3KAnz72KGyHX3S2yGXyqyn1KzX1aPqyGMX3ywGOKxGLn2mM3w6O3wPwUDaxHRp2PwgI4H6w4KwKPG4LrF4Pv0m1xCfz%2ByfVf3f0oE62/xAG9TlEEMCF22Vw0EEJtHu3APp0gNsF%2BxEPelWxAEkH8E2yDRtBjTdUkF9S4A9QOkPySHWI%2BKTVOIdUP07XeM3QRJ%2BNWEk0yGcEkCAA%3D%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/kindred_left_interview/implementation.hpp)
- [Source code](../../../../conceptrodon/typelivore/kindred_left_interview.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/kindred_left_interview.test.hpp)
