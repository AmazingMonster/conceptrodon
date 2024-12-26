<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::KindredRightInterview`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-kindred-right-interview">To Index</a></p>

## Description

`Typelivore::KindredRightInterview` accepts a list of elements.
Its first layer accepts another list of elements and returns a function.
When invoked by predicates, the function first binds the second list to the end of every predicate;
then, it returns the index of the first element that satisfies all newly formed predicates, or `-1` if it cannot find the element.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>n</sub>
-> Interviewers...
-> Preds...
-> (...&&Preds&lt;E<sub>0</sub>, Interviewers...&gt;::value) ? 0 : (
   (...&&Preds&lt;E<sub>1</sub>, Interviewers...&gt;::value) ? 1 : (
            &vellip;
   (...&&Preds&lt;E<sub>n</sub>, Interviewers...&gt;::value) ? n : -1
   ))</code></pre>

## Type Signature

```Haskell
KindredRightInterview
 :: typename...
 -> typename...
 -> template<typename...> class...
 -> auto
```

## Structure

```C++
template<typename...>
struct KindredRightInterview
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
using Metafunction = KindredRightInterview<int, int*, int**, int**>
::Mold<Args...>;

/**** Tests ****/
static_assert
(Metafunction<int**>::Road<std::is_same>::value == 2);
static_assert
(Metafunction<void>::Road<std::is_same>::value == -1);
```

## Implementation

We will implement `KindredRightInterview` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:** Check several parameters at the front of the list.
If a match is found, then its index is returned.
Otherwise, drop the checked parameters and call itself with the rest.

Here's a simplified version of it:

```C++
template<typename...>
struct KindredRightInterview
{
    template<typename...>
    struct ProtoMold
    {
        template<template<typename...> class...Predicates>
        struct ProtoRoad
        { static constexpr auto value {-1}; };

        template<template<typename...> class...Agreements>
        using Road = ProtoRoad<Agreements...>;
    };

    template<typename...Args>
    using Mold = ProtoMold<Args...>;
};

template<typename First>
struct KindredRightInterview<First>
{
    template<typename...RightSides>
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
                    ((...&&Predicates<First, RightSides...>::value))
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
struct KindredRightInterview<First, Second, Others...>
{
    template<typename...RightSides>
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
                    ((...&&Predicates<First, RightSides...>::value))
                    { return 0; }

                    else if constexpr 
                    ((...&&Predicates<Second, RightSides...>::value))
                    { return 1; }

                    else if constexpr
                    (
                        KindredRightInterview<Others...>
                        ::template Mold<RightSides...>
                        ::template Road<Predicates...>
                        ::value != -1
                    )
                    { 
                        return 2 + KindredRightInterview<Others...>
                        ::template Mold<RightSides...>
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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKz%2BpK4AMngMmAByPgBGmMQSZgDMpAAOqAqETgwe3r4BQemZjgJhEdEscQlcybaY9iUMQgRMxAS5Pn6BdQ3Zza0EZVGx8YkpCi1tHfndEwNDFVVjAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimKmujMh4mAq3R%2BdXN6f/xx%2BlwuwOS4WQ3iwtxMSTcBAAns8APoEYhMQgKGHYEHmJLgyGYaGw5ATdBYKhYnG/AE0wEgv57W4ASRYqXobEETEaX0OQIZtIBQJBBEwrIMIphcMRjFYmAAdArKVcJsQvA5bgBpcLoYiYdAAJTwwAQBCZgniADd3gB3HEAdisV1uztuIrFXMwkoRz2YbAVcqVlxdtxVaoIt2UxFQRAAsp50CDgyYHYngy63WyPV7RZmJbDvTK/YqkthbhCmAoFP7I3q8KIRZiS6m0yHUWGI1GiPrUEwE06W9CHa2uXWywIJphVKliLcmF4iLcLWIvITkxYALRcZP3GEWQc7pKO4H9lsZ8We/M589e6W%2B%2BXF0vlyv%2By7AXWixgERvYk9pryZIxbm7XsiXuDto1QYCE1hV93w5L9/UpQ9m33XcqSDdMryzfNb1lF9iGAb8UP/cJgFuONaHQUDwNjeNJUuAiqwfNCrm3Fjj0uM9sKlH1ZVuAAxPBiAmQNQ3VLUGB1PVDWNU1zWIK1MFtWFBOEghAzXFCuLzHjC3vOUZJNIQ8CwIjfzE8NIwgii%2Bww51NN/YNtIvOEsJ0gs70QksywMZ8FRrfB6w%2BQMB1bVV1Ssrse1s0K1xdFDQrmRxkDHBgJynGc5wXJdvFXRyBwcuzQrTEx/Csfx7ggZZbnXLFW3QEAQBYJgAGtMCRTJgAidAUUlTIAC92vUpt8uKwcjzGsa8CoVL0unaFRsm50oEQswADZzDWgK6w9Rs3FUiZSCAo0jJMj4vOwRqcpXZZlgSpb4qHXUCA2Bhbg0XdUNYxalvqJR7oe8bbme16aq3Q8vqKpbtyqgGSrtA8JoKhH2Lh5zs3ddzcKLANvKfJi5VgzAP0EMyoZdEjAKg6jIsg6L6LfYn4IJpCkfslHkO%2Bor0Zw3icYYwiQopgCyJsmnO1QGz6MYi7UY5o9hTclyPL4g6CCOlW2FuIRMDQSSNex/SAHkCAQeIyYszVtV1A0TrkkUFJtSU1aOnW9fQI6TbN4TZdYlNfx53TPIVQzhDOsng0t2mpd/QrQsDhPDYunyKwJ7agojgco4lqC4bi%2ByfpdJLRz1ubMvnVBF2XPLyZbOPAehMrSsq6rau80lGuatqOqNbrethAahqFwH64bl1ptmkUMoW2uHpWxV1s29PdudoTDuO2TjNMi6rur264ehp7MBe4g3o%2BiG2K5sfgz%2BwkJ9Lqf5oPyb54DRf1uXhtJTdgQPY307t4Pl3rlfehcxpxRBqfW44M9yXw4tfF0t9bj33HI/Ygz8xoQAwQ9CSUlbayTNA7RSyk3Be3Nr7WeY9GrOXInRWEoct7nWYmAh61ClZAXprCT%2BTDcY/koQ3YBK5bhgDADCMCm5sGhTuiw2KQ5JGTUgW9Mw0JLBW0kjbUOhDLRO1hGQn2zD%2BGAzYZjQkUt6F20YSzEahjWEgBobnLhNsdoNgoQglsgiLywJkcjHcV83G33kXXI%2BJ83oSIvijbx7MW7YLYpzWesSFaLQTkrG8fN9J1Xxi%2BRmJMvzDz/CLDhIExE0Tpr2BmcFPxWOxHEpM8t0JORSbzPS%2BFBbWODJTUW8ZxbWToW4AWVS5aI3QvyAUfIji3GwKoVgbJCTfHpAKOkXMGTkWPkwKgXhBDZB5AcIEic0ktLJh0lZLR1kMAcFs4puCNF2y0Y7JSkpwjq2QYIPYR1HkHDeS8vYgZGpmL6TLZicT5l3AACofC/Nss4IJi7ICRKneI6krgQBjKs055yBAPK%2BViRqDi3AdxAHgBQHVZTYpANdVcSQDxgTMHdOJMK4WVgRSCZFqKNnooYJKC0qATKktxfiwlxK2CkvJaBYpm5aUWA4KsWgnB/C8D8BwLQpBUCcDcNYawIZ1ibFXMkHgpACCaClasFqARJByg0AADjMGYAAnDarg/hLUWq4HaO00gZUcEkLwFgEgNAaFIAqpVKqOC8AUCAf1BrFVStIHAWAMBEAgHWAQVI85yCUDQKyOg8RIiyk4KoC1a11xrUkLcYAyAUpSDlGYXgtYiDEBMnofgggRBiHYFIGQghFAqHUFG0guguCkGtGiVInAeDStlfKw1yrOBG3nCm8MqAZr5sLcW0t5boFmuURADwmb6AzlxFwZYvBI1aFWBAJAGbUhZrIBQCAl7r0gGAFIMwfA6AOzDRAGIU6YjhFaPCUdvAf3MGIPCI2MRtC60jXqjN8EjYMFoP%2B3tWAYheGAG4MQtAw3cF4FgZqRhxBIaEpBvAFoPhTsnLrec2w9WPPqFO2geAYhohAx4LAU7UR4B9dh0gpHiAxAyJgR4eHgAMaMIa1YVADCEQAGo2iNj6ADHbhCiHEO2pt8glBqCnf2/QhhjDqssPoRjYbICrFQKkRoWH1ykjEaYSw1gzBBt4/W0y8BVh2GI84CArhph%2BAHaEcIwxKijAHUULIAhfN6DC40BYIxqg9E800SY7RPCdD0B59l/Q2ixeC/FuYUxUv5AHflwYgXFghfc1qrYEhx0cDlQGqdwbbjLqLSWstFbN23AgLgQgJAVFJEPce8Tqwza9lGFVUgJrJBJDlDapIbqNCSDMJINafr/BrRtfoTgXrSA%2BoG3KNaXA1oWptc6ta/hJAOrm2tBrvbg2hvDfq8TMb43nsTXO1Nt7717pzWwTgrQWAWjtOuJgKdAJcBtXKLg5qa34DrQ2gd6mW2qekOprtWne26BfUOpgI7sO1fq4G3gwbZ3JvnLcRdzWC2tbB2RCHUPzVdZ3Vevd/WaVDajWei9qBd3xDTXennLPRjliMBDrg/qaC0HfZQL9vagN/sU/LkDYGIMOEUzBz8cGENTuQ6h9DtBMOKdw3pgjSr8C6nOaRrDSqKPICo4p2jHqlUMaY3%2B1j2wlUca43q3j/GlBCZN6RZ7kmmAybkwp7jSOVNttR7IdHPalVY902JuzVhDMu5MxN8zlnODWYINBe4qeHNOfiC5sjpmEvspcJJSL/nJI5aWKFjI4WciFb82kZvMWytxfS/URLWWUt5HbxlxoA%2BG8hdsMl2vk/5jd9yzVtYGxquHq23Vydd3OBU5XSWkXdPIfQ40F1nrdb%2BuDae5zkbmAxsJAmx6nbe3IeLbtP4G1rqkhLZW5d27QbOAPYjc92NBNJNedfnb7bNXNDgAHVdFgBQC0FKC0enc8CYWHXrFzRtWQZHGPJTePbTEAFIHHPHMdVfQnRrGdD7BdJdaA2A%2BAxA3acMbdQXa9frJII9c/U9GNbnXnG9dNRgvdMlZAVIVIJEBAm1JEJAggJEVQYtV9KXc2GXb9X9EDRXRQ0DcDSDdXHnWDeDRDM3TAFDNDDDLDPVY3fDD3HDIjS3MjXtW3e3bjR3ejRjZjeEd3djetb3XgX3ATAPfDIPTnPgKTBQWTJSeTRgRTKPVtCQWPTtTTBPHQPA5PfTezdPYzNzZVCzbILDHYDuIvSwRzYnZzcOVIkfbIavdwNvPQALcoHvJvYobIafaLbIcfPLPvTLKfco4rFo0fZLJo9LNoofXo2fKo%2BfFfBQKrNtAndfH/DgZrKguAxcWghseg4/PrA9Vgk9I1UgUbLAG/Wre/EAW1OUJIJIQIRbcXDQI4u0Y7b/YnX/WwR7dY26SbEASQfwWbF1O0P1C1SQe1LgK1daVfJISYm4kNNgjYj1ata46dEEh41YXjTIZwSQIAA%3D%3D%3D)$Done$

## Links

- [source code](../../../../conceptrodon/typelivore/kindred_right_interview.hpp)
- [unit test](../../../../tests/unit/metafunctions/typelivore/kindred_right_interview.test.hpp)
