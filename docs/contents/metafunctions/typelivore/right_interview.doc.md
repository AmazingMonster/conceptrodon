<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::RightInterview`

## Description

`Typelivore::RightInterview` accepts a list of elements.
Its first layer accepts another list of elements and returns a function.
When invoked by predicates, the function first binds the second list to the end of every predicate;
then, it returns the index of the first element that satisfies all newly formed predicates, or `-1` if it cannot find the element.
<pre><code>   Arguments...
-> RightSides
-> Predicates...
-> Found ?
   index : -1</code></pre>

## Type Signature

```Haskell
RightInterview ::   typename...
                 -> typename...
                 -> template<typename...> class...
                 -> auto
```

## Structure

```C++
template<typename...>
struct RightInterview
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

We will find the indices of `int**` and `void` in list `int`, `int*`, `int**`, `int***`.

```C++
template<typename...Args>
using Metafunction = RightInterview<int, int*, int**, int**>
::Mold<Args...>;

static_assert
(Metafunction<int**>::Road<std::is_same>::value == 2);
static_assert
(Metafunction<void>::Road<std::is_same>::value == -1);
```

## Implementation

We will implement `RightInterview` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:** Check several parameters at the front of the list.
If a match is found, then its index is returned.
Otherwise, drop the checked parameters and call itself with the rest.

Here's a simplified version of it:

```C++
template<typename...>
struct RightInterview
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
struct RightInterview<First>
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
struct RightInterview<First, Second, Others...>
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
                        RightInterview<Others...>
                        ::template Mold<RightSides...>
                        ::template Road<Predicates...>
                        ::value != -1
                    )
                    { 
                        return 2 + RightInterview<Others...>
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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKz%2BpK4AMngMmAByPgBGmMQSXEEADqgKhE4MHt6%2BASlpGQJhEdEscQlcSbaY9o4CQgRMxATZPn6B1bWZDU0ExVGx8YlBCo3Nrbkdo739peXDAJS2qF7EyOwc5gDM4cjeWADUJltuXo60hACex9gmGgCC27v7mEcnyKPoWFQ3d48PBEwLGSBkBxzcBEuyUYrEwADoEb8HqNiF4HAcAEp4YAIAgASUE8QAbnhMAB3P4mADsVgeB3pB0BwNBmHBkOhzDYCLhSPuDIOKLRBAOymIqCIAFlPOg/vzqbS%2BfyGUyQUwwScVSy2VCYVzEVtsAc9kwFApuaLMPhRICFLylQzBejReLUBjUEwZXT7UcaQLGo5kEaBKNMKpksQDkwzqgDkSxF5XvKALRcakAEWOFh9Ga2Ctl3s1atZGqBqvVEJ1nPh%2BsNxtN3PuwGImCBjAItoN%2BftXnSRkx7vQbzTIrFRDdHvBjebrcEZprma72YXD0XhfL7N11bh92IwA7ty99J74WAByltEHx2Hzsl0snu7nPM7ucpVJzeYBpa1GsrsIOADE8GIUZeUdYUsRxfFCWIElyXBQDgIIXl5VXL8i21DlYW5CDcSEPAsH3RcwJHF1z09RV6RQw8lTXYsITQ9dfz1J9awMesEQtK0i0I6j%2BWIm9XQHRc5V9SjeO9aYAyDBgQzDCMoyIWN40TcT7SoijvTU/wrH8NMIAWA4kxuP10BAEAWCYABrTAAH10mACJ0BspCTnSAAvWyXIPDTNJEhVfICg48CoaTZPDI5VMC%2BkoG5cwADZ4s4vBrUwDs3AQ0ZSExbFcPw1LYoNMy428TAFgWYSooZeUDmbAhVgYA4NEzJcV0iqKaiUCrKp9LNavqwzU1zFqfMC9N9K6pV02XEbKLfaaJtotkGLojcqwK1iTUfKcWzYWc7W9Y8%2B3HS8tmvUdBInE5tpndt1umkT30pajFp/TDmJ3Pd9qPXtTzIocSNvC97z3O6XxXOawf%2Be4XorN7XgyggstWv8hEwNAGHQJGmK3AB5AgEHiHj7mInCoMBGDSQpE4Eay1H0cxg48YJ4C7vB/zlWWjDN2wnLhDyom%2BIIVEnXOsjF3UzSYal7H1qNNjHySlKBYkoWhQBi7yM06qxJmpVJOS0LATkyNoyUkqIt1vyJq17STF0/TDOMz4zIs6y7OxRznPBdzPK%2ByqJe6pVgsN0NwutwKYsRMwEujxXuPgoDMuyyC8II9aiuUsrw4C6q%2BuIBqmqGqbWstwKOteYP0bCiNs98yOeWjxLmy4m1wTpgQGdJ1P8prDOSqztrRt9POGsGrNi6hwOlXLoKQqro3w1rzSICXwLSYJcnYKptwmcJ1nS%2B6szaLPO8Ti7/n96nzSj%2BW/tLrcOObUvq/7T7hMDjAMArwG1f7XKwec6%2Bl/r5EeBwzBHEsMnXEG9iSU3BLvFm84AGVRvsyIsJ8gZn15t3R8fsX70lQWWV4x1wSPx7ixYB18QDFQTM1ShVU5ol3wQccu9DZq9UwHVfOP8i6MIPpNN841kFTUhlrCGH5dZS05q9bmNY5abQbE2HabZlbdh%2BnfE6Z0XQkKukom6uDnzs1mo9JhHM0GMThg2B8ftDq/WlP9ASYsroPlBnmcRT17gAHoABUvi/H%2BM8X8HxviAAq2AhAhL8YEh4wT/EBI8U8BgewvCHHBGcOgVxkKfnMStGWCIPpE1sWeThTAqBeCSXUBq3917QS3uCcIiMgqCG8VlBpvjWnNO8byMyTi3AFNcR4/WyAbKbXiEhB4EAJQlLKRUzI9TOk3DMjotwzsQB4AUHZWEizqHKSHN/Mw5VIZDJGaaMZfxJnTPKQ4OZJwiSoHwts5Zqz1mbLYNsmhiZTrfxTIciwHAli0E4P4XgfhuC8FQJwNw1hrAChWGsRMZgtg8FIAQTQ/yliWQCFSOEWwAAccUqRbAJRoPFhKACcWx9CcEkLwFgEgNAaFIKCrQpAIUcF4AoEAjLUUcC0EsOAsAYCIBACsAgyQzjkEoGgYEdB4iRFhJwVQ%2BKkxxUkAcYAyBAxSDhGYXglpCAkHwnofgggRBiHYFIGQghFAqHULynQegyTECYMkTgPAAVApBWi1lnAcZnHFcKVAIUlVxRVWqjVWrJA6oOBADwMr6A10RVwBYvAeV8tIBAJA0rkiyrIBQCA2bc0gGAFIMwfA6Dk05RAGI3qYjhCaJcN1vA63MGIJcHGMRtBox5ci6Vu0CA4wYLQRt9rSBYBiF4YAbgxC0E5WCsdQJDDAHEKO/AzZrlElSt60MaMzgbGRQ0mo3qLgxGdW2jwWBvVCzwHS%2Bdm7iAxDSJgNMi6jAXCMGipYVADB7gAGqUxxhyJtVrhCiHEJak18glBqG9boLg%2Bgl0oGhZYfQeAYicsgEsVAyRKlzqTJ8K8phLDWDMCy1A97iD83gEsOw3bMguAxhMPw8HQjhAGGUIY8HUjpEqUxvQ3HCgMFmIMConQ6P1DGC0TwbQ9C0euRJmYbG5icdsJJvj8HpjNGExxioNG4XrAkB6jgwKmXerZQcENYb1WaoONq8BEBcAGsTUilNKLP1LAJh6IY%2BlSCYskFsOEFKqSSA0JIMwkg4oMv8HFMlVKOA0tIHSpFcI4pcDirisluK0v%2BEkEkClcVTOjrZRyrlbn7X8qFZmkV/qJX5sLQm%2BVbBOBNBYESKkSYmDyL7FwMlcIuBwhZfqoglHTLwcg2a8D0hIM2pg6O3QZanUuqbUZkzzLwW%2Bpq4GkKLW2sda66eHrfWBsxrjTmhNECtgHNTZ%2BjNWbUDxviJKgt92ztDB2%2B140RgetcEZTQWglbKA1tHS2htwGQdto7V2hwwG%2B1tkHcO7147J3TtoLO4DWALJvo2CytddHN1zsG6oXdgJgOHsBaOk9Z7LgXux6myjt7kX3sfUoF9mPl0nhu9%2Bpgf6ANAfneNsDFqpuyBm3all82EMfqI1YFDJ6MM%2Bew7hzg%2BGCAylOtLkjZGKNUcw2J%2BTfgICuHU8EDG2n5hcYKLx6TuQLc8cyGblTcnKk9HGNb5jevneSYd6JzTUmcju9997wzyxVgGeTXF1bZnOCRmIK19rnXPsHd6/1jQMbHPDYu8m675WPOYC8wkHz5OEtJd66Fqk/gyVUkJWFiLuXCtkc4CV7lN2BXCtFQGp79W5UKo4C11VBwWAKCJIGIkh2WSjD1fgYbRqxuyAm0LkDovYMgEpYt11YKVteqKxtsVZwDhBpjywfvg/h%2BxjH9xYUsaXu5ou1sVzab/m3ZQNfhNneX9DGH8kZINlR9kpsuPggEZWPVVctf7QmQHWtetNtMHKA9tTtbtGHe7fteHEdHHTACdKdGdOdZFDHJdFdHHICPHLdUdHdZAPdUnQkcnFlSnBtGnK9enYDJnJ9VnPAjncrPgH9BQf9ckQDRgYDAXc1CQYXa1aDMXB1SlAwKXZDGwOXajVlHDTIOdTxZ2DXSwUjcFbXAiOQp3ejQ3RjN3PQVjEoETfjS3TIY3ATSpIPDTGocTBgF3P3GTGwroBTLTJTEwjTNTAwzwxTYwnTYPBQfTC1TfevdbDgQ/Y/IfEfc/G0S/dPEgTPe/dzUgTzLAAvIzYvEAMwXrLYLYQIULH7ElLYKkdLUIn1dlWwUrB/MqXzEAMLFLLgS7OKS7MlVLaODQKkOLLYLfBvCo6oozXVMo4rMrPlJYe9dIZwSQIAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/typelivore/right_interview.hpp)
- [unit test](../../../../tests/unit/typelivore/right_interview.test.hpp)
