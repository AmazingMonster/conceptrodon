<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::SensibleRightInterview`

## Description

`Typelivore::SensibleRightInterview` accepts a list of elements.
Its first layer accepts a list of predicates and returns a function such that when invoked, the function first binds the arguments to the back of every predicate;
then, it returns the index of the first element that satisfies all newly formed predicates or `-1` if the element is not found.
<pre><code>   Arguments...
-> Predicates...
-> RightSides
-> Found ?
   index : -1</code></pre>

## Type Signature

```Haskell
SensibleRightInterview ::   typename...
                        -> template<typename...> class...
                        -> typename...
                        -> auto
```

## Structure

```C++
template<typename...>
struct SensibleRightInterview
{
    template<template<typename...> class...>
    alias Road
    {
        template<typename...>
        alias Mold = RESULT;

        template<typename...>
        static constexpr std::make_signed_t<size_t>
        Mold_v {RESULT};
    };  
};
```

## Examples

We will find the indices of `int**` and `void` in list `int`, `int*`, `int**`, `int***`.

```C++
template<typename...Args>
using Metafunction = SensibleRightInterview<int, int*, int**, int**>
::Road<std::is_same>::Mold<Args...>;

static_assert
(Metafunction<int**>::value == 2);
static_assert
(Metafunction<void>::value == -1);
```

## Implementation

Each specialization of `Typelivore::SensibleRightInterview` checks several parameters from the front of the parameter list.
If a match is found, the index of the matching element is returned.
Otherwise, the function drops checked parameters and calls itself with the rest.

Here's a simplified version of it:

```C++
template<typename...>
struct SensibleRightInterview
{
    template<template<typename...> class...Predicates>
    struct ProtoRoad
    {
        template<typename...>
        struct ProtoMold
        { static constexpr auto value {-1}; };

        template<typename...Agreements>
        using Mold = ProtoMold<Agreements...>;
    };

    template<template<typename...> class...Predicates>
    using Road = ProtoRoad<Predicates...>;
};

template<typename First>
struct SensibleRightInterview<First>
{
    template<template<typename...> class...Predicates>
    struct ProtoRoad
    {
        template<typename...RightSides>
        struct ProtoMold
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

        template<typename...Agreements>
        using Mold = ProtoMold<Agreements...>;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

template<typename First, typename Second, typename...Others>
struct SensibleRightInterview<First, Second, Others...>
{
    template<template<typename...> class...Predicates>
    struct ProtoRoad
    {
        template<typename...RightSides>
        struct ProtoMold
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
                        ::template Road<Predicates...>
                        ::template Mold<RightSides...>
                        ::value != -1
                    )
                    { 
                        return 2 + SensibleRightInterview<Others...>
                        ::template Road<Predicates...>
                        ::template Mold<RightSides...>
                        ::value; 
                    }

                    else
                    { return -1; }
                }()
            };
        };

        template<typename...Agreements>
        using Mold = ProtoMold<Agreements...>;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwArKSuADJ4DJgAcj4ARpjEElzBAA6oCoRODB7evgGp6ZkC4ZExLPGJXMm2mPaOAkIETMQEOT5%2BQTV1WY3NBCXRcQlJwQpNLW15nWN9A2UVIwCUtqhexMjsHOb%2BEcjeWADUJv5uXo60hACex9gmGgCC27v7mEcnyGPoWFQ3d48PBEwLBSBkBxzcBEuKUYrEwADoEb8HmNiF4HAchIwMrF6AAlPDABAEACSggSADc8JgAO5/EwAdisDwOLIOgOBoMw4PZIKYYJOkOhzDYCLhNwOeyYCgUouUxEw%2BFEgIUSPurIOKLRBAOctQRFxqCY6D%2B6oZTLV6tZPM53KhMJFiP8t2ZlpZmvRuqIAFlPMaXa6zRqmo5kBKBGNMKoUsQDkwzqgDuSxF5XmaALRcBkAEWOFiO9Jz/nNJtdbKBvP5ELtwvhCPuwHlQMYBBVTpLrq8GSMBx9tHQbyzOuIetQveNJ3rjbYghljtuRfb%2BcLxf9ZY5fK5AvLNoF1dhovFkulsvlio3redFpZnYiwAOBqNA6HI4f47ccoVeCVmFnYrbC4ebNczpAFtw3W0hVhA4ADE8GIMZVXdbVMQYbE8QJIlSUBYhKRpcFYPgghVTNRdrXArd10rQV7VrP9sAlAxjwRD8z2VVV1SQ599UNP0r3zc1SzXCtNyrSCHThfFCWEPAsAvRcOIIVEPWHb1fXk1lAxZdTXRmEMw1QwEoxjOMiETZNU1XQSSMswSNMCKxAizCBFgONNxU%2BEAQBYJgAGtMAAfQyYBInQfyiJODIAC8AvCy9bNLay%2BPi108CofSIyMo4bOS1koAPMwADZzAKliv3PfC4LGUh7ww6TZIPJ1PKTbxMEWRZtJy/iDnlAg1gYA4NFzJcQKSzqWVqJQOpywMer61zMyLYbsts7NnKmjSC2A5agIA/5RpZMiqL3cTJ0wJsZ3Y0sb27Mcn09Uc1InBszunFsGvnASNuXEb1UOkS/ogmj3oYqVf1O86W0u68uzvV87pU1BX3BcHXt/X5dp2ld7gB3cxNeAiqrZY7XkxNAGHQarqJrUUAHkCAQBI5ORRStQxLE8BxTBJMwskcKpWkTgJghqtJgQKYOOmGfg966UZUiwKohX/uJ4Gj1/UrvyZvjOPupHV0SwScdEoGEW5uqfyhy0dYRscOs0rL9qt4Mv3Swzo1jeMzJah3prl5arPskxHOc1z3IIdBPO8vzAoJEKwvBKKYst33PrG9VUtdyN3fW%2BK8sRQrio18rBcq4WaqkoQZJ/d6mvMtqc5WxluswXriH6wbFqAwD/eSibXgzsmMuznvc4gfKisKou2JOUXyeqs3K/quda5a%2BuR8bvNZrbg4FrzLu9rTy0%2B4OAfwzd4gG8EiBL%2BSlC0K52qsIpfnwUlxmZfXnLPL%2B%2B8ePBKfq5zhvvFb%2BSseyPTcAvKuaM2yf2SivFMBwwBgGOIODMwDLTtTgQGJuGDBJb36mYI4lg2aoQ5uhKST8%2BZ4ROG/aWQDsG2VAZRV4SMTgAJgXFQ%2BpZmHCXAX2cEUCl50TwTwkAzUUxDVEVpTa3dHY5T7tIrqBD5pSNkfIhKBY1rr0xnbTaGNlpGypvuOsz0IZa0EtdO8t1UFcQegIp6U5mycK2nxXRcjfpK25F43GJs6IgyYnCFGzjLZWN/o%2BWxus/6OJes4mWGN9FYwAPQACo0npIyUkv4qS0kABVsBCFyekrJDwckZMySNJ4DA9heEOOCM4dArjEVAiwwG1M6zEGAFrMJXoW5MCoF4ap9R%2Bq2LvuQh%2BlDea4QFm4CIZc5kpOqgsxZJ9BBpNVJ5NhbgPIgDwAoQKsIbieVthOTpLiDH3F0l%2BfyoMEhEQeBAXpTQBlDKyOCZZRzxHmQHLYsw7VdpXOQDc6Udy/iPL6S8hwbyTjklQDJT5EjUz%2BELGgrg/yLAcGWLQTggReB%2BG4LwVAnA3DWGsBqVY6xUxmH8DwUgBBNCYuWD5EAgR6Rwn8AADgKvSfw3KNCcp5QATn8PoTgkheAsAkBoDQpB8VaFIESjgvAFAgBlfSjgWhlhwFgDARAIBVgEBSGccglA0DAjoAkKIsJOCqC5WmAqkgDjAGQKGKQcIzC8E/EQYgMk9D8EECIMQ7ApAyEEIoFQ6gNU6D0NSYgTAUicB4FinFeKGUKs4DTM4RrtSoDSragq9rHXOtdZId1BwIAeHNfQGM2w0W8HVZq0gEAkBmpSBasgFAICtvbSAYAUgzB8DoNhFVEBYhptiBEZolxE28AncwYglwaaxG0JgBwM7SBmtejTBgtBp1RtIFgWIXhgBuDELQFVBKD1AkMMAcQ%2B78DyiheSH8abIyrrOJsWlczahpouLEONC6PBYDTYpPAkrL3PuILEdImAszXqMBcIwDLlhUAMF0gAavzGmQp13%2BuEKIcQIa8PhrUGm3QXB9A3pQKSyw%2BgOYqsgMsVAKRhkXrTJ8VBphLDWDMPK1AkGfWyXgMsOwq7hkuHJpMPwFGwgREGOUYYFG0gZGGVJvQymigMDmEMSoXQxM9HGK0Tw7Q9CiahQ0Qz2mFO6ZmBMYzeQKO2f6HJ%2BYimRMUo2BIZNHBcWyrTYqg4%2BbC1OpdTvUtRCIC4EICQYhNLFj1uQ8sBmRphjOVIMyyQ/g4TCvpJIDQkgzCSAKtKwIBVBWio4OK0gkqaVwgKlwAqHLBUcoa4ESQyRhUFT8/uxVyrVV0uQ023Vzb9VZuNZ27t1arVsE4M0Fg5J6RpiYCDbsXBBVwi4HCeVXqSC%2Boo3hwNhHpDEaUKR/dugB2xvjTO7zvm5WEozWNnNaU5sLaWytu8a2NtbfLZWtt1bYt/IS1GrVLbUBVoSCart4P/vDFe4tyURg1tcBlTQWgw7KBjv3XOqd66ccLqXSutdl7N3Nm3butNh7j2ntoOe9dWBvIIc2PKh9%2Bnn0Xu26od9gJ13fuxfuv9AHLhAeZ/Wn14HaWQeg0oODjPb23kG6hpgGGsM4cvQdgjwbjuyBI5G%2BVF3KNIa41YWjf6GNpeY6xzg7Hw6cZoxYXjhKBPQOE3p8zfgICuDUzJ8mVmFhKcKKp%2Bz0nSAaeGX7xTbvhm9Ds7kEPZno%2BWZczp0zhnve2CT6UFPaKVhrE8zn/nd3/OcFjMQebi3luI8%2B%2BtzbGhy1Re9bFutA2QdJcwClxIaX%2BdVZq%2Bt/L9JAiCvpDygrRX2vdb45wPrarBvar1Qa7NUPJuWutRwObDqDgsAUOSUM5IvucjGJ6/A3q9uhvw0GiQ2uw2nb19GkVV2E0Etu6mnrj3DVnAOLm0vLAN9b534mffc8bUCtGHdtWLfweLFvRtEbZfDtU1UA6tcRZAFIFIfyPfQVfyA/AgG5MvB1QddHRmTHcdSdBdPHEgxdZdMTddUnQQcnPdFnTAI9E9M9C9WlBnG9O9FnOCNnF9fdN9ZAD9XnMkfneVQXKdEXEDcXddKXGDWXDghXEHPgNDBQTDGkbDRgXDWQQ7LXM/XXMjAIQ3Ywe3OjWIc3JjFjLIC9JJDyY3HjPjZ3ITRjKPLICTdwYPPQWTLPazdTQPLIdPMPLICPGzWofTCzPodPBPAzWYZPbwxzNPdwuI6Irw/3dzPPYNZ/CfB7Dgb/X/bfXfQA5UYAhvGLWtSAhtRlUgZLLATvbzHvEAMwdbfwIIQIfLFHflfwekRrTI9NJVWwfrcotqdLEAArOrLgfwQqcYwVerQqDQekCrfwF/SfXogY7zD1bo3rKAioyDDIZwSQIAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/typelivore/right_interview.hpp)
- [unit test](../../../../tests/unit/typelivore/right_interview.test.hpp)
