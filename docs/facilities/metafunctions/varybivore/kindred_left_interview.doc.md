<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::KindredLeftInterview`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-kindred-left-interview">To Index</a></p>

## Description

`Varybivore::KindredLeftInterview` accepts a list of variables.
Its first layer accepts another list of variables and returns a function.
When invoked by predicates, the function first binds the second list to the front of every predicate;
then, it returns the index of the first variable that satisfies all newly formed predicates, or `-1` if it cannot find the variable.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> Interviewers...
-> Preds...
-> (...&&Preds&lt;Interviewers..., V<sub>0</sub>&gt;::value) ? 0 : (
   (...&&Preds&lt;Interviewers..., V<sub>1</sub>&gt;::value) ? 1 : (
            &vellip;
   (...&&Preds&lt;Interviewers..., V<sub>n</sub>&gt;::value) ? n : -1
   ))</code></pre>

## Type Signature

```Haskell
KindredLeftInterview
 :: auto...
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
/**** Equal ****/
template<auto I, auto J>
struct Equal
{
    static constexpr bool value
    {I == J};
};

/**** Metafunction ****/
template<auto...Args>
using Metafunction = KindredLeftInterview<0, 1, 2, 2>
::Page<Args...>;

/**** Tests ****/
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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQBspK4AMngMmAByPgBGmMQSAMxcpAAOqAqETgwe3r7%2BQemZjgJhEdEscQlcybaY9iUMQgRMxAS5Pn6BdQ3Zza0EZVGx8UkpCi1tHfndEwNDFVVjAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimKmujMh4mAq3R%2BdXN6f/xx%2BlwuwLMiXCyG8WFuJkSbgIAE9ngB9AjEJiEBSw7Ag8zghiQrzQ2FuZATdBYKjY3G/AF0wEgv57W4ASRYqXobEETEaX0OQKZ9IBQJBBEw7IMYpJTC8RAAdArqVcJsQvA5bgBpcLoYiYdAhTBUAgswTxABu7wA7riAOxWK63R23MUSnmYaWy1AKuVKy5O24qtUEW7KYioIjKJjAd0Op0mO0g/3%2Bl0ct0klOS91wmXyxWJbC3SFMBQKb2hvV4URirH5xNJx2B9Wh8OoABKGNodfr8YsAZajmQhYEE0wqlSxD76BAIBYTAA1phkZlgBF0KiSZkAF6LgjY25msReTAwu0AWi48fusN7l%2BvNL99ed4tTUrhGbT2c93r3RZL3suwC6uKjAEDWOKxvWXiZEYtztnQMKJPcIZhkQcGdnCAFAVyoHfrWiT2g%2Bjq3vh97Js%2BmYermcqXMQwBgV2txQeEwAhlGx6wkhzYRmxJI0XRuE4iRVzEQRorkR%2Bbg5qgtwAGJ4MQEy%2Bo2wZagwOp6gaRommKxAWpg1pwnJCm7rWwkJhBT6uq%2BklfgqmnCHgWD0RZynIS2kbRgxPYMWRVlZvC4nWVJAmFgYf4KuW%2BBVh8vqPn2qpNihbYdj5cZ2nGFlxXMA5DgwI5jhOUn7oe7GZY%2B3llXFREAKxWNV9wQMstynnu5LTrOC5LngK56uucJbjusVVd25mEcNj54FQuX5eOMKVeNjpQN%2BZgBOYASRZWbo1m49lCI5HzeqQsnyYp%2BbTge3iYMsyypQtRHpbqBAbAwtwaNeJ5XsJ80LfUSi3XdPa3I9z3NRe%2BEff9cWXo1kNpVeQljf6ImkY%2B77WWj/nBXmBa/qWCqYZgwGCM5iNOkxMFoQhnFJWhvGAYT2F4z6eEEUjNrw6JFkY5RXr47RJP%2BuTLEeexiFudxnkYfzAl3mZHP3tzn5EMdxlHUVQiYGgalq7ZcoAPIEAg8Qk65qnqfqhrGqaulWiSRkTEdGta%2BgR0G0bCky2ZrNOorNlUbt%2B0C06rlcagIteaNcW%2B77WPMzjYVMxt0VB/WIc0yl82A0R33B/2lbTWKBW3EVF1HnNpMjd7d0wrVJj1Y1zWtQQU4zvOi7LqufVuANfXgRXVUVf3C2TQXo6zbDw1LYqK1rUnW0kgHTmHSrp3YOdJXXRPA8PZgT3EC9b3g7eX1D%2BNv3HiPWszROW9xVPPozytc/Vgvlt7UvCqO5rAjoNi6%2BXZvHOw1AbA33rcMGN52Yo2rv6c%2BtxL7DkLuOW%2Bj4IAoOGmbXUFstLWz0gZNwbtjae1PtXacGNWKSx2m/QOxCYFVTIYFY8tM4TPwOtjdB9CQCl2PGAMAHFQYcP9DdIB28bwiIWqAl6ZgYSWE1NqLB9ltLmltnCQhHt2HiPGgwvyFD/KLzYXHQRj5tEviYSlFhWDNrVloXQ4xXCSrvSMfdT6wJNH1nPk4k8vZJECKPlAtxH0YYiORpnKBCN/rR0YTzEKuN/z0yJqBIakFoIsUpvw0OzC3AEwSUzakCM2byxPr5Ux0S%2BZ0SSYxFJuiqbizDjxKW/F2HhLCZza4QoGS0juNgVQrAOTHm%2BIydpAyT5MluNgAAjl4MQfIDhAhjp6VkOtlYACklJoiDGMyZYhbRVz7DyfOV8kEThiKgTwxVLoRwsCyKm/DVktNtIU1xbS7gAFld5MCoF4AkvJhmXHmVRPiJMha3DeS0T53zsg1MwRpS2Sibb6RJBoI6KRbhmCOmYX005w4NNySze8oyAAqHxQIzLOCCbKlZkTFiUG0EEEBQUfK%2BQ4bIJIMVnRAJkiZUz0Jr3sZdG5YszA3QRhS5AVKSzxF3Fcel7zwXMoECSc8f8OXmLcFy7Z7LuECqQueYVFgOCrFoJwaqvA/AcC0KQVAnA3DWGsAGdYmx2Jgh4KQAgmgDWrDnCAaqkg5QaAABxmDMAATmDVwaqAb/VcBtDaaQRqOCSF4CwCQGgkVmotVajgvAFAgCRW681BrSBwFgDARAIB1gEFSLKcglA0DsjoPESIrBtiqH9QEU8ARJC3GAMgQcUg5RmF4BWIgxBHJ6H4IIEQYh2BSBkIIRQKh1AFtILoFIlp0SpE4DwQ1xrTXustZwPWsoq3BlQFNVt7bO3dt7eA310iIAeHrfQG%2Bzrli8HzVoVYEAkB1tSA2sgFAIC/v/SAYAUg0U0FoDpHNEAYj7piOEVoCIt28AQ8wYgCI9YxG0JrfNLq63YT1gwWgyHl1YBiF4YAklaC0BzdwXgWBZxGHEGR%2BSuG8Bmg%2BPu0cmtZTbBdeEMU8aLW0DwDEdEGGPBYH3WiPAyb6OkE48QE5ShHhMeAKJow7rVhUAMHRAAalaPWzwzUuoncIUQ4hZ3mYXWofdq79CGGMLayw%2BgxM5sgKsVAqRGh0dPOSDiphLDWDMBmpTo6nLwFWHYdjzgICuGmH4FIoRwjDEqKMFIRQsgCES3oLLjQFgjGqD0WLTRJjtE8J0PQMX5VlfmKlxYGXbDldy%2BMcrhX0vVGiw6rYEgd0cBNaQdNvBM23AvR2rtPa%2B13tuBAXAhASAyOSG%2B112nVhGyYFgBIjVSBeskIkOUwbEixo0JIMwgRU3VQCMG/QnBE2kGTckOUAQuABH9cGqNAQfXhqO0EYbB6s22FzatgtX7S3fvLce6tgHgPPqbWwTgrQWBmhtKeJgoUnPgODXKLgfqh34BHWOlI5mp1WekDZpQdnl26DReupgm76P9cG/9zNR7K2yluGesbbaJsY5glwbHuONCzcfX%2B59S2hXvu00Wn9qAn3xBrUBuXYvRhFiMALrgSLIPQcoHB5daGkModIAbjDWGcMOCNwRkCRGSP7vI5R6jtGjeMacyxi1%2BBdTMs43Ri1PHkB8aN4J%2Bo%2B7RPiaQ1J7YFrZPyZdUplTmA1Ou%2BYtL3TUYFCGf0sZxgRuSeWZneT2Qtml0Wpp45rTQWrCudDx5nb3nfOcH883QLLmLChZG%2BFwOUWSu1ZcGpVrwQ1IdaWJljI2WciVfyCP4o2Qh9NZq40foUwJ9Je7wv9rDWivVZa8vrf9Xyib64N1jYvXD%2B3YG3u5do3xtXrVyxAXOO/WzfmyOpbh%2Bpeg/W5gTbowdvxvu497HU7G0aqYNGNRIM7QISQFIFnTgbNYHD9QtYtMtCtE9RXWHRtZtRHYgFgK9FgBQM0QcM0e/TMCYfHBbCLcdWQUnfPOdeQSnYvHQEARIUgOnBnbdM/ZnfdVnKHU9c9XA/Awg4graYMB9ZXf9JbRIFbBAr9WXeXADWtMQ59LhZAVIVIZEIg4NZEEgggZEVQTtPgOgHXWDeDRDDDI3E3TDbDXDS3OXQjYjUjd3TACjKjMQJ3BTF3ZjSPBjNjL3LjZdP3APBTIPYTXgUPCTBECPGTUdGPXgOPDIBPcUJPLTUHPgPTdPIzEzHPKgvPCQAvedeg%2BzJgsvZzYLKvdzLvOvbIOjHYNqCvELMLeICLLjTzVfbIXvdwHfZLQfDfTrPLUfRofvfLGfHo4fVogQRfCrPIFfefPodfffXotrAYfvOYNoWfLrNYY/GdJnC/DNTgMbfggg/cIQ6sEQ5/RbPEN/EHT9T/b/bbfrf/EAENOURIRIaqCNKA1NF4m0N7IbLg2AoHPNNbXbfwaqQ7aNG0VNf1SQMNLgQNFaM/RIHYkbf46Q/rQdX4y/FEoEpTTIZwSQIAA)$Done$

## Links

- [source code](../../../../conceptrodon/varybivore/kindred_left_interview.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/kindred_left_interview.test.hpp)
