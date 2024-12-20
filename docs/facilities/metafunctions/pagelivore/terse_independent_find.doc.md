<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::TerseIndependentFind`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-terse-independent-find">To Index</a></p>

## Description

`Pagelivore::TerseIndependentFind` accepts a list of predicates and returns a function.
When invoked, the function returns the index of the first argument that satisfies all predicates, or `-1` if it cannot find the argument.

`Pagelivore::TerseIndependentFind` prepares fewer base cases than `Pagelivore::IndependentFind`.

<pre><code>   Predicates...
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> Exist (...&& Predicates&lt;Arg<sub>I</sub>&gt;::value) ?
   I : -1</code></pre>

## Type Signature

```Haskell
TerseIndependentFind ::   template<auto...> class...
                              -> auto...
                              -> auto
```

## Structure

```C++
template<template<auto...> class...>
struct TerseIndependentFind
{
    template<auto...>
    alias Page
    {
        static constexpr std::make_signed_t<size_t> value
        {RESULT};
    };

    template<auto...>
    static constexpr std::make_signed_t<size_t> Page_v
    {RESULT};
};
```

## Examples

We will find the indices of `2` in list `0, 1, 2, 3` and `0, 1, 3`.

```C++
template<auto I>
struct IsTwo
: public std::bool_constant<I == 2> {};

template<auto...Args>
using Metafunction = TerseIndependentFind<IsTwo>
::Page<Args...>;

static_assert(Metafunction<0, 1, 2, 3>::value == 2);
static_assert(Metafunction<0, 1, 3>::value == -1);
```

## Implementation

We will implement `TerseIndependentFind` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:** Check several parameters at the front of the list.
If a match is found, then its index is returned.
Otherwise, drop the checked parameters and call itself with the rest.

Here's a simplified version of it:

```C++
template<template<auto...> class...Predicates>
struct TerseIndependentFind
{
    template<auto...>
    struct ProtoPage
    { static constexpr std::make_signed_t<size_t> value {-1}; };

    template<auto First>
    struct ProtoPage<First>
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

    template<auto First, auto Second, auto...Others>
    struct ProtoPage<First, Second, Others...>
    {   
        static constexpr auto value 
        {
            []() -> std::make_signed_t<size_t>
            {
                if constexpr
                ((...&&Predicates<First>::value))
                { return 0; }

                else if constexpr
                ((...&&Predicates<Second>::value))
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

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKxcpK4AMngMmAByPgBGmMQgAOyJpAAOqAqETgwe3r4BQemZjgJhEdEscQnJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlUbHxSSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BzmAMzhyN5YANQmO24EAJ6pmAD6BMRMhAqn2CYaAIK7%2B4eYJ2fI43QWCoLzenw%2BBEwLFSBkhp3OUJhTDhZyYXiIADosS8jgcmAoFFiMcpiJh8KJIc8dq8PuNiF4HEcACrxJQASQYWGunMYBAAYuF0GCTIkrB8jhKjpDobDMPC0ZjsdSwZKjnSGQQjiTUERlExgHLxZKRRY1c1HMhcQJxphVKliGb0CAQCwmABrW6ZYARdB3eGZABetwIOIAbmIvL8TQBaLgigAip1NCaTwqNEulSJRbgVqCOAuI41B6bN9MZ2t1%2BrlZwLReVJZNxpLqtmFqtDBtdoduaO4e8UebxtFKtVo4lJn8Vn88YgSyO0ZxgOdro9Ny9Pr9Z0DweL7zHY5NI/3%2B7wVHbnftRygRPMADY7ySyXgKZgqW5ayHqc6%2B5Glksj8eo6NqSBDrAwRwaEmJyJImHwAYBkp1Eo8EIdBpogWB85xjsyYwShB4wbO%2BHQYmOEASmZFwSWmayvK6J5h%2BpBHD2QiYGgnJMbmRIAPIEAgrK7i29walqxA6qgeoGvCjFHKx7HoExvH8YWN71nuQ6muOg4Sq2z7npCXbMfRvYRgO6kEWK5mAROU4znOC7Uo6y7up6eDemSm5uNum40lZx6HtpgGnvptr2sRx7XtiZj3tFj7ksir7SXghaftg36mX%2B4X7sBmCgcQ4GQThJFpn5qFIb8wXsRexBZWOkUYneD6kvFlLwnJAhCl%2BIA/pgmWBf5opHBh%2BVHNhuGweCpUIeVRyVdaBlhf1%2B4QLVgEVhJVbwkprKqb5qGAel/ZHGAYCnPGWGraq/5LRZJw3YBw3gWYJyWKJ4mSdWbjbSpSp7ft%2B6HZGUGXUOE0gxK5Xg2hQ25ZhsbA3h90JkRgUUZZqpoyVqo0QldGKhi7zAKSUK8lSf0Sl4mRGFqVZ/Od60ffChPE2wgiEr9qZwXhlGTQA9AAVILQvCyLvNggLQvMq%2BBAKEcwtix8Esi8rgsK5NXwMAcXjHPC7GbKkMu7mCOPZj2bK7uqjJsgoTIAO6oGCIBHKkXgxLQelLiAMSoJ4NxVc0gjwmydNnUcZg4oe3OWcbiK0ai9FEu8xDAGTYKU%2BEwBHAAsrlTBUF4msNHTUuFpgHJcq4vICpyQc2/bu7OozZxJynu2c5NunIDc%2BJKK0EA580%2BeF9k8IaExQRh0xOwvIDUY7KR51mP%2BPOd93BLxAQ/e50PDgj2cY%2BjVPM/daZIfz1hy8WBwKy0Jw/i8H4HBaKQqCcG41jWGqawbFGZg7DwpACCaGvisN0ARJAYg0JILgiQdgaH8BoaKt4zAAA4UH6E4JIXgLAJAaDHo/Z%2Br8OC8AUCAMeQCn7X1IHAWAMBEAgDWAQF2BByCUDQNCOg8RIisC2KoFBt5oy3kkEcYAyBLRSAxGYXgT4iDEDwE6II/BBAiDEOwKQMhBCKBUOoShpBdBBFtg8VInAeA3zvg/YBL9ODcXRMwo4qAzx8IEUIkRYjRoQOehADwHD6AOl2FwJYvAKFaBWBAJA7DUicLIBQCAESokgGAFIMwfA6CQkLJQGIliYjhBaBcExvBsnMGIBcbiMRtBsQoQA9hrMCDcQYLQPJuisAxC8MAHMtBaCkO4LwLArojDiCaclCpeBQyvksbaNi6ItgAPCJCW%2Buj3YxAeMUjwWBLH3DwDg7ppBRnEG9koeMUJDDAHdkYYBKwqAGBTgANTwJgW23FuT5I0cIUQ4h1FKPkEoNQlj9H6GOSgD%2Blh9B4BiKQyAKxUAG2yF06MgIzqmEsNYMwhDdlyKwOC2c3RhnOAgK4KYfggihHCEMSoIxCgZCyAIAlegihUoYPMYYCQgh2BxY0CYbRPAdD0Ky3eAg%2BitEZWS5ltgOU0pZRyoViwAmrHWJsCQZiOD31IAQ3gRCjhOMEcI0R4iPFXlwIQEgL1/6BMAeclY/EmBYASFisBkgdgYgAJw7ESJIKBZhJC3jwf4W8jqMEcCwaQHB/8MS3i4LeFBjqUHhv8NA/wzrbwqssUQkhZCzWUNCXQsJDDbHolYbE1APiuE8M4C0FgoZEjRiYLiAw1MuCOoxFwSB0j8CyPkXoT5Kj3nSE%2BVon5ujdDJMMUwYx3TFXKtVVYjgNimHonsWeMtFaq01uOaNBtTaNBXm8ZE3xxql5BPOdQ8Jhad3xHzXE3xIBF2VrxEYetXAx40FoGk0hEBMm6MKbk55n7imlPKQ4Z51TeR1IaZY5prT2mdOeb045Azn74FJLvUZXTn4TOQFM55sy6iWMWcsi4qytjPw2VsgBuz9mYEOX0k5GdD2XP1AoW59zHmMGeZ2t5aie2yD7To5%2Bg7/lnMRVYYFizMWQuhdaTgcKCCdXjIJ5FqL4jorGRC7FfK/B4s5OK4InIpXkrSJShoWm6UNF0yK3lDQBWcryIS1TFnJUkoWHp2YkwuX5AlXMBzTKFWyp/t5%2BZE7k2cGYsQctlbq23szvWxtkD9WtqNf401wSQGkEtdaygirA3BobVAxI8bkg7EkB6oRQRJ0ptsGmpLmb4DZsYcw89J6oncLYKWkLLiWAKFDJaUMUXZTjBbYa9FHbZBdo4y87jvyQA7FIMO0dpj/UBd0UQmddiHHBZYG1jrXWesJXGFuhru7dg7ES4e7NF6z0xLOwkTrqRUg3G646m4vWCDd1az21JrIMlZJycU7932SllIqYBwtNSQONPg5gFpbSxBQe2TB/phGelDKQ2M3RaGMPbKw/M5%2BuHckEfWXIkjvAyMZAo0c/pNGM18CuQxu5DynnbLY6oiQnHNHfJ4zoSb/HjBApsCJ%2BAYmGhdN5kuOTlgUVqrRfI5TWLzPZBcJp1zNniXlC8xS4o2QjMGeyKZnldQ2WWa07L/l9mVfCp5WKxX5uPOm%2BlSsBQ395Uyv8xYxbQWy0bc672bblJNQQANbI41ASD0ZotZgK1IwsXzMyyAMwDadg7H8Ag6BeD4%2BJAjUm13xDyvkPNaQO1/gnX%2BBQdFR1khHWwJdVwKb8ydgu8IZwYPITFVSIz/XrPlWVi7MyM4SQQA)

## Links

- [source code](../../../../conceptrodon/pagelivore/terse_independent_find.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/terse_independent_find.test.hpp)
