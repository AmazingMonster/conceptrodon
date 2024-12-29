<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::SensibleLeftInterview`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-sensible-left-interview">To Index</a></p>

## Description

`Varybivore::SensibleLeftInterview` accepts a list of variables.
Its first layer accepts a list of predicates and returns a function.
When invoked, the function first binds the arguments to the front of every predicate;
then, it returns the index of the first variable that satisfies all newly formed predicates, or `-1` if it cannot find the variable.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> Preds...
-> Interviewers...
-> (...&&Preds&lt;Interviewers..., V<sub>0</sub>&gt;::value) ? 0 : (
   (...&&Preds&lt;Interviewers..., V<sub>1</sub>&gt;::value) ? 1 : (
            &vellip;
   (...&&Preds&lt;Interviewers..., V<sub>n</sub>&gt;::value) ? n : -1
   ))</code></pre>

## Type Signature

```Haskell
SensibleLeftInterview
 :: auto...
 -> template<auto...> class...
 -> auto...
 -> auto
```

## Structure

```C++
template<auto...>
struct SensibleLeftInterview
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
/**** Equal ****/
template<auto I, auto J>
struct Equal
{
    static constexpr bool value
    {I == J};
};

/**** Metafunction ****/
template<auto...Args>
using Metafunction = SensibleLeftInterview<0, 1, 2, 2>
::Rail<Equal>::Page<Args...>;

/**** Tests ****/
static_assert
(Metafunction<2>::value == 2);
static_assert
(Metafunction<-1>::value == -1);
```

## Implementation

We will implement `SensibleLeftInterview` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:** Check several parameters at the front of the list.
If a match is found, then its index is returned.
Otherwise, drop the checked parameters and call itself with the rest.

Here's a simplified version of it:

```C++
template<auto...>
struct SensibleLeftInterview
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
struct SensibleLeftInterview<First>
{
    template<template<auto...> class...Predicates>
    struct ProtoRail
    {
        template<auto...LeftSides>
        struct ProtoPage
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

        template<auto...Agreements>
        using Page = ProtoPage<Agreements...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

template<auto First, auto Second, auto...Others>
struct SensibleLeftInterview<First, Second, Others...>
{
    template<template<auto...> class...Predicates>
    struct ProtoRail
    {
        template<auto...LeftSides>
        struct ProtoPage
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
                        SensibleLeftInterview<Others...>
                        ::template Rail<Predicates...>
                        ::template Page<LeftSides...>
                        ::value != -1
                    )
                    { 
                        return 2 + SensibleLeftInterview<Others...>
                        ::template Rail<Predicates...>
                        ::template Page<LeftSides...>
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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMz%2BpK4AMngMmAByPgBGmMQS/lykAA6oCoRODB7evgFBaRmOAmER0SxxCVxJtpj2xQxCBEzEBDk%2BfoG19VlNLQSlUbHxickKza3teV3j/YPllaMAlLaoXsTI7BwA9ABU%2BweHR8e72yYaAIJ7BwDUACKYKa6MyHiYCjeHZ5fXJ39H3wu5yBZn84WQ3iwNxM/jcBAAnk8APoEYhMQgKGHYYHmMEMCFeKEwtzIcboLBULE4n7/WkA4G/XY3ACSLBS9DYgiYDU%2BB0BjLp/0BwIImDZBlFxKYXiIADp5VTLuNiF4HDchIwMjF6CFMFQCMzBPEAG5vADuOIA7FZLjc7TdReLuZhiY72c6pTLUPLZVibhCmAoFD7lMRMPhRKLMf5sbb7crVQQbqHUEQAEro2jA%2B3Q63ZnP2t0Sl2w6VyhUx/MFm4JtUpojKJjAF1x6sma015qOZD%2BgTjTCqFLEG5l1A3Y1iLyYXMWAC0XHbdxhFlzS/8NqBrYLRY9pa9PouwDDYsYBGjsYu1btXgyRmTTenMLuyeIqdQjebxMPx85Z59VPXKtV2XalL0LMV3UlWEdygtxR3/GN/QMIMQzDCNnXPICb3CYAbgzOhoX8Z961QfCs1hUNwzwSN3gQ7FAMuRcQMYy4YJLOCvRuAAxPBiHGRULlrJMNQYLUdT1A0jWIU1MAtWEeL4ggBPbDcczY10IOLT1y19RCAxQ%2BVKPQqMBJzISXzfMigJUoC1M03cOJ03V9SEPAsEwrczNRRMLIbB9bPtFTAs8q9Zm7XtRNFQdh1HcdJ0fEK2zzRKrztEwAFYrHSu4ICWG5Zz9MkQBAFgmAAa0wJEMmACJ0BRYkMgAL0qpTKxS1KbPa1L7TwKgIv7aLoS67qbigf8zAANnMCajOojDiWc4Q3No%2BVSG43j%2BJjYqJ28TAliWAKRpzIKwwIdYGBuDRl2AliwKOq86iUQ77pnG5TvO/KF3XG67pexdcue47LTXVSryYhjN1%2BuynVg%2BD5W/TAT0EDyoftbC7w/R8iN899/NhBGkb/Ct6NBtLgeYyHocg9j1L3HS/X04N4aPRHfxRnN0dwsjCOI1900zL8WcJpndJJq0QdA2nHLHBTxjW2KNTQBh0Hl/d5QAeQIBB4hR8yRLEzBFsNUVpPNYlZYINbFYEFWbk17W%2BLoq1SYdezYKluHRaQwMRdmmj2fjby6z50iBa3TrUbtD21dlRbXPc0zQqDpMSMx56grS4bO25aj%2BqiocR04napyGyOCwjl7AsyjKcrygrEKKkrysq6ravq2EmpaxPK4ryuC16vOBwLwGjrGhVJumv35thOPlpFtaLaxbb4v2keRpOzAzuIC6ru%2Bpjbr7gtHunAelYG4es9SsffQnyap5MmeJPjlbZStzAlfQJeQGLvaDsvsGOzvW3jcL6K596U0PvaY%2BNxT59nzsQNe3UICIPuvrPA2pDYSWNiaM2sJ7Y6ydv/EaxU2J4QFhRNCc0oyELLofEhbtpxp0fi5OeNDIFXmXrtG4YAwBPk%2Bigq8f9aFHSCgIkaQCLpmGhJYdUmp0HiX1Ng02sliT4MdsTMR3V6Ew2nFZChVF/ZsPYQWbR1N7yfmYUtdyRjjH2k4VOa6migZLgPsY4%2BTjAqAM3h9ecjjyZENXADLO4MXbOIps9aOOkCZs27gWTm5isa8zfEwtw0TTwiwAi7EJoEqZaWggw7S3pibewMrKNJyNYnxO5nwkiejUlCzZk7CG2TboCkFPyQ4NxsCqFYOyacXwGSCnpK0zp2AACOXgxC8n2ICSJY5mSqyIDcAAUgJcy4zJlZkYslX6YVc5n3gTcGIqBPBxV2tZa0zIeZ8NWeTZpdyNyDNuAAWU3kwKgXh8Q8gGaxApdMillOIMAFG8TXnNA%2BV8rIPNZGiXkZgxRUkZJyTcBoNayQbhmDWmYASxU6kbLEF/FJFwgUZMrM0mktwAAq7wzzTNOMCPZyAkQ%2B3iEpS4EAwXvM%2BQ4LIxJsVbW/vFa52MzAHQhoy5lQZWXAg5W8iFPKBDEl8QKn%2BwrnzzjFRYDgKxaCcHSrwPwHAtCkFQJwNw1hrA1jWBsR8oIeCkAIJobVKwyogHSpIWUGgAAcZgzAAE4/VcHSt6r1XBLSWmkLqjgkheAsAkBoVFhrjWmo4LwBQIBUWOqNdq0gcBYAwEQCANYBAUgynIJQNAbI6DxEiKwLYqgvUTVnBNSQNxgDIB7FIWUZheBUSIMQNyeh%2BCCBEGIdgUgZCCEUCodQ2bSC6GSGaNEKROA8B1Xqg1TqTWcHVjKUtSZUB9QbU2ltbaO0gI9VIiAHgq30GHLiLgSxeBZq0CsCASBK0pGrWQCgEBP3fpAMAKQmKaC0BNumiAMQt0xHCC0eEq7eAweYMQeE6sYjaHflm%2B1lbfzqwYLQeDc6sAxC8MAOCtBaDpu4LwLApUjDiCI7xTDeBjTvC3QOd%2BMotj2vCKKKNxraDoLRChjwWAt2ojwHG6jpBWPEGOUoB4dHgCCaME6lYVADDAoAGrmnVk8Q19rh3CFEOICdRnp1qC3Qu/QhhjAWssPodB6bIArFQCkBoVHZxkifKYSw1gzDJtkwO9y8AVh2GY84CArgph%2BGSKEcIQwKgjGSIUTIAgYt6FSw0eYwwqjdAi40CYbRPAdD0OFhVhW5gJYWMl2wRWMtjCKzlpLVQwvWs2BIddHB9WkCTbwFNNxj3Ntbe2ztl7Rq4EICQaRSQn0OrUysbWTAsAJFyqQV1kh/Cyj9f4CNGhJBmEkBNBN6UJp%2Bv0JwGNpA41JFlBNLgE0vV%2BtDRNd1QadsTV61ulNaaM3zezW%2Bgt76i17rLb%2B/9d7a1sE4C0FgxpLSziYN7O8XA/Wyi4J63t%2BB%2B2DuSEZ0dpnpDmaUJZuduhMVLqYCu6jXWet9e3RwXdJaZQ3EPYNxtw3ke4VR%2Bjz1o0b1frvTN0Vz61O5o/agW98Ry1/sl4LkYAYjCo64Ki0D4HKBQbnUhuDCHSDa5Q2hjDDhdc4dPHhgjW7iOkfI5R3XtHbMMeNfgMMPLWNUeNRx5AXHde8bqFuwTMRhPwlE1sY1EmpP2tk/JzAimHc4TFxppsCgdOyT04wXX%2BOTPjqJ7ICzs7jXk5s6p3zVgHMB%2Bc2ttzHnOBeYIJ/IiJf/OBfiMFtjLn8sVZcMrBrwRlbNcWCl9IaXsglbyIPooWR%2B%2B1fKw0PokxR%2BxY77Ppr1Xctlfqwv9fVWyhr8fasdYHW99Rrp99zg7OT2tsV9ztHGONATex9Nh9c2X3OtIEtlblAutXZu2j/blp0p%2Brhr%2BAHZHaSDJD04/a2B/Yv6A7wDA7Fr7oy4Q41p1ow7EAsCnosAKDGg9jGg87FjjBY5TbBZDqyAE7Z6TryAk7546ABCkCU7U5roXbdabpzoppM77qs5HqYHYG4H4EYRJjXpy7fozb%2BDP5i7A7IE/oVrCF3rfzIApApBIh4F%2BpIgEEEBIiqAtp8B0Dq6QbQawYoa6766oboaYYm6S64b4aEZO6YAkZkZiC27Sb270ah40ZMau5sZzqe7e7Sa%2B78a8AB5B4h7iYDoR68BR7pAx5ihx6qYA58CabJ66b6YZ5kFZ4SA55TrUFWZ0EGDF72Y2Dl6hYmruZZBUbbBFSN6WABb9ZBZzzFEz5ZBd7uCb5xZ96r4taZZD4NA95ZaT4dED5L69Ab65CL6NECBz4DADHT4jGlaNbb6JYD5tYH7jq06sHJpn5aGtpYE4Hjj8FRiCGTb9ozaPqi4A6LaYDLYjBrZRrf4gD%2BqyiBDpTBpgEJqBCWiPZfZsGcC/aZoLbrYgCSDpTbZhqWgJpeqSCBpcA%2BqTTMH%2BDrH9Y/H/avpdY9pfEbGprImv6yYZDOCSBAA%3D)

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/sensible_left_interview/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/sensible_left_interview.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/sensible_left_interview.test.hpp)
