<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Find`

## Description

`Typelivore::Find` accepts a list of elements and produces a function.
When provided with predicates, the function returns the index of the first element that satisfies all predicates, or `-1` if the element is not found.
<pre><code>   Arguments...
->&nbsp;Predicates...
->&nbsp;Found&nbsp;?
   index : -1</code></pre>

## Type Signature

```Haskell
Find ::   typename...
          -> template<typename...> class...
          -> auto
```

## Structure

```C++
template<typename...>
struct Find
{
    template<template<typename...> class...>
    alias Road = RESULT;

    template<template<typename...> class...>
    static constexpr std::make_signed_t<size_t> Road_v = RESULT;
};
```

## Example

We will find the indices of `int**` and `void` in list `int`, `int*`, `int**`, `int***`.

```C++
template<typename Element>
struct IsIntDoubleStar
: public std::is_same<Element, int**> {};

template<typename Element>
struct IsVoid
: public std::is_same<Element, void> {};

template<template<typename...> class...Args>
using Metafunction = Find<int, int*, int**, int**>
::Road<Args...>;

static_assert(Metafunction<IsIntDoubleStar>::value == 2);
static_assert(Metafunction<IsVoid>::value == -1);
```

## Implementation

Each specialization of `Typelivore::Find` checks several arguments in the front of the argument list.
If a match is found, the index of the match is returned.
Otherwise, the function drops checked arguments and calls itself with the rest.

Here's a simplified version of it:

```C++
template<typename...>
struct Find
{
    template<template<typename...> class...Predicates>
    struct ProtoRoad
    { static constexpr auto value {-1}; };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

template<typename First>
struct Find<First>
{
    template<template<typename...> class...Predicates>
    struct ProtoRoad
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

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

template<typename First, typename Second, typename...Others>
struct Find<First, Second, Others...>
{
    template<template<typename...> class...Predicates>
    struct ProtoRoad
    {   
        static constexpr auto value 
        {
            []() -> std::make_signed_t<size_t>
            {
                if constexpr ((...&&Predicates<First>::value))
                { return 0; }

                else if constexpr ((...&&Predicates<First>::value))
                { return 1; }

                else if constexpr
                (
                    Find<Others...>
                    ::template ProtoRoad<Predicates...>
                    ::value != -1
                )
                { 
                    return 2 + Find<Others...>
                    ::template ProtoRoad<Predicates...>
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

```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwAnKSuADJ4DJgAcj4ARpjEIACsXKQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCcmpCi1tHQXdEwNDldVjAJS2qF7EyOwc5v4RyN5YANQm/m5ejrSEAJ6n2CYaAIK7%2B4eYJ2fIE%2BhYVHcPzyeBEwLDSBmBpzcBGuaUYrEwADokf8nhNiF4HEcAGIRdAAkwAdisTyOpKOwNB4MwkIpYKYELO0NhzDYSIRdyOByYCgUbOUxEw%2BFEwIUKMeZKOaIxBCO/NQRAASqgmHiSWTCRZJS1HMhOQIJphVGliEcmBdUEcAG5iLzvDUAWi4hIAIqdNS63fi1aTaVSaSC6QyoTC4azkf5sJyDDy2Y9gAKQYwCKKIwCJV4skYjkqVR9nbLiPLUDm8Wc4wm2IJeeH7v5ic8Ca6617Hr76dTGSGWe8ccQJmKpZicQxS25e/3U08NWmyW2g3OO8HmfC2RyuTGkfzBXhhZgU/dvVr0Zi5YrlarxeqierDxK5jq9QwDUaTWaiFabXbb1f6xK/%2BqkisJJnQgZYjntDlvhAEAWCYABrTAAH0smASJ0EQghISyAAvJDMMnS9/wladvyIsk8CoR9n2NI4oFXMwADZzAYrchXbFMxzwPt8OwaDrW8TBlmWGcyP/DUjgFAgNgYI4NDdE5GxbUSiPqJQROUn8JMwKTiBkx15I9Ui/xdUD1OIxTm0PD1LMBQjyQDP1GQc9saS7FcayjblqwRctMETKsxXTTNgGzc88wLIsS0hXz/OTVdUxs6z6wBBdXOXNhsS4iZSHJNyMqETA0BHHKmVDREkQAeQIBAEn3AFBxlYdR3HAgcoKor0Byqqar7eKDwbX9Z2c%2BdhsXUruz6zyNwRVid3YwKyQaiKzxVdTxNJMzFu1HcqOBF9TXND8BJOIySLssiTEAy6QLAiCIy1dBoNghDkLwVDBQwrC8Fwz6CI0hTBv%2B0kKN2w0aLo5FGOY2bdw4lq7j4z8hM25TxMk6TZIMxSpyMsjVPeEGiuok0IfZKHGJh%2BaznhiNEYE5HcaItHtIxp06wU10cfOjT8aOQn9T28Gmshbrar66CF2W4tz0hSmRXFkB%2BNtI4wDAU580dYTGbE690d0o4zBOSxMpHEXqrFmsJdGqWorOOW9wVpWO3dbHbKBsl8ZR0TmZ0vS2ZdznuZ1m6vaStaLOSw9UqcykXM7dLyvZe7128mLK2TBbSQzCIQpLcLT2l1ay3jPz0%2B8/5EojlsAHoACp64bxvq4BOv64AFWwIQ24b5unlbxum5bF4GAOLxjkhC46BuMUUtGtKyqObB6HTgcCGPGUAEkFA3wRnXWWJ6H6YgARAI40i8A%2BdqgkA8AUZD4UhJfYpyiICHrjlpyrrno6XBen5XgiS0t4ADVUB4AvKfc%2Bl9dTX1vvfNgj9l5JhypaMBpZIyfybJHVsc8Y6BjGnlROa5oyp2IMAOqTxs5ZgALLaSYFQLwI9GjhWFmcV%2BL9BC1w4W/LhfNOG1zFNBW2bhHhkPLglbB94dyIS8gkAgEBaEtAYUwnIkIt47wIHvC%2Bh9JgI0Vp%2BPM6sDbCRslI5AMieRyIUXQ5RDhVFnBAWgvRTtDH%2BA1lwExFgOCrFoJwJIvA/DcF4KgTgbhrDWElOsTYdozD%2BB4KQAgmhvGrDgskAkCJ/AAA4GIEn8DkjQWTcmBH8PoTgkheAsAkBoDQpBAlaFICEjgvAFAgBqYkjgWhVhwFgDARAIB1gEHPq1CgEA0CgjoAkKI8JOCqGyfaBikgjjAGQLqKQCIzC8G3EQYg4C9D8EECIMQ7ApAyEEIoFQ6gOk6D0AAd2IEwNInAeA%2BL8QEpJDTOAVQuEMo4qBKKzIYvMxZyzVmSHWbRDw4z6Aml2B43g7TOmkAgEgMZaQJlkBGai9FIBgBSDMHwOgwI%2ByUFiO82IERWjXCebwclzBiDXAqrEbQhV2nxLGenCqDBaBUquaQLAsQvDADcGIWgLSgl8pBIYYA4heX4AFHYy0e53mGkKhcbY8TX71HeVcWI9z6UeCwO8teeBKnisVcQWImRMDOklUYK4RgkmrCoAYchwC8CYBuRVZk1LTnCFEOIE5%2Bz5BKDUO83QqQDAOtMJYaw%2Bg8CxBaZAVYqA0iNDFfab46to1WEsGYepqBzU7KwIm0CPQWU5BcCOaYfhUhhAiMMKooxUjFGyAIategW2NAWCMRI4x6jloEEfdonhOh6DsAOpokxBj1sWE22wU723jCnd2xtvbVgKCiVsCQLyOD%2BNqe8xpRwAVAqWSso4azDYQFwIQEgRs4nLHhY61YNUVSjFLakyQ/gETFIJJIDQkgzCSAYtUpIDFgi%2BI4OU0glS4kIgYlwBimTAiZIQ0kSQXAkjFIYvu3ljTmmtISY6pFvTkX9O%2BRccglAsXQqmWwTgrQWCWgJPaJgnksxcECAiLgCJ6lbJILs1IQbDkBukEG85obeW6HxXch51Kd17rqcEz55GZR/NNMQRjzHWNcnY5x7jGgIWoChQkO9ZgH2EauV0lFRm0XQso6Mmz2KGNMftDp3FgQuA1JoLQIlLSICkt5bSylPqgv0sZcyhwPr2VJk5dy95/LBXCtoKKn1WBYJ2u2PUuV5bFVit46oVVwIfWaog/UnVerrgGsy/CnZpr4nmstUoG16XpU5yI86pgrr3Weu9eKoT/rjmidkOJy59SpP6ClSgcJlg40JvgMm1NOR02Zrcdm6webgmFvAUqpNZa7HOAgK4RdIQRwrqWM2zIrbcgjoKBdkoOQztzvHftydAxjvPcaEOx7vb51vZuzW37bRvvbrWBsLdHjSm7rebhzg6nNMsbYyFDjXGeO0Wvdsu9cKLOdOfZgV9iRS0QagzBzj/6CSYYJLkgDQH0M4fzZwfDbSiPdL6QMoZ9nqOTOmRwBjCyjgsAUJaXUlpkdUgmJs/A2yBO%2BuE4N31I2w0BFIDJx5QT5PQ/pxwL5gyLi/MorzxZAuhdWlF%2BxGUEBIW2ZM7sfw5mEXeKRdZ4zGKqOOehYrZAaQ0iIRF4ERCYuCAyI0wsglPnaokrJRS%2BlIWo8MqZSyqLRmOVcp5VlzAAqhUirFfEtLUqZVZa4jlpVvKVXIDVcVwQWreXlcpVVo1tWfUNatc1vPbXLN8BdQoN1HqvWMB9f1o5EghtnJDaN65JTI3GGmzYHVJaFtps4NXKCa3c35q28W%2Bbe3GiVvcP9vQdaKg9o7Zdxox3O0PZnUfvtvRB0Lr39fidX3L%2BrrHXf/IAO5hA%2Bf%2Bd9dm7jnq7pyUw4Dhz5yN2F1NxFHN3R1vVhTtyfVIBfSwAJx3WJxADME438H8CSCSH/U8wKX8AJEQ0AI%2BSaVsAI3tyElIA/TMDgy4H8EYnoMCHg0Yg0AJEh38A1yAMfUsx3Q2WILw2x2SVIHNSyGcEkCAA)

## Links

- [source code](../../../../conceptrodon/typelivore/find.hpp)
- [unit test](../../../../tests/unit/typelivore/find.test.hpp)
