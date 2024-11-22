<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::TerseIndependentCognateRightInterview`

## Description

`Pagelivore::TerseIndependentCognateRightInterview` accepts a list of predicates.
Its first layer accepts a list of variables and returns a function.
When invoked, the function first binds the variables to the end of every predicate;
then, it returns the index of the first argument that satisfies all newly formed predicates, or `-1` if it cannot find the argument.

`Pagelivore::TerseIndependentCognateRightInterview` prepares fewer base cases than `Pagelivore::IndependentCognateRightInterview`.

<pre><code>   Predicates...
-> RightSides...
-> Arguments...
-> Found ?
   index : -1</code></pre>

## Type Signature

```Haskell
TerseIndependentCognateRightInterview ::   template<auto...> class...
                                        -> auto...
                                        -> auto...
                                        -> auto
```

## Structure

```C++
template<template<auto...> class...>
struct TerseIndependentCognateRightInterview
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
template<auto I, auto J>
struct Equal
{
    static constexpr bool value
    {I == J};
};

template<auto...Args>
using Metafunction = TerseIndependentCognateRightInterview<Equal>
::Page<Args...>;

static_assert
(Metafunction<2>::Page<0, 1, 2, 2>::value == 2);
static_assert
(Metafunction<-1>::Page<0, 1, 2, 2>::value == -1);
```

## Implementation

We will implement `TerseIndependentCognateRightInterview` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:** Check several parameters at the front of the list.
If a match is found, then its index is returned.
Otherwise, drop the checked parameters and call itself with the rest.

Here's a simplified version of it:

```C++
template<template<auto...> class...Predicates>
struct TerseIndependentCognateRightInterview
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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKxcpK4AMngMmAByPgBGmMQgAJwAzKQADqgKhE4MHt6%2BAUEZWY4CYRHRLHEJKbaY9qUMQgRMxAR5Pn6BdQ05za0E5VGx8UmpCi1tHQXdEwNDldVjAJS2qF7EyOwc5snhyN5YANQmyW4EAJ5pmAD6BMRMhAqn2CYaAIK7%2B4eYJ2fIE3QWCoLzenw%2BBEwLDSBkhp3OUJhTDhZyYXiIADosS8jgcmAoFFiMcpiJh8KJIc9kq8PhNiF4HEcACrxJQASQYWGunMY7VQwGYkIASnhgAgCBzIcQAG54TAAdzBJgA7FYPkcNUdIdDYZh4WjMViRWLhHgsFSae9NUc6QyCEcSagiMomMA9erNSq1VbrZrbYyhAYFAgwb7ParQ2HfdqkSi3AbUETQR6o377naHcQnagXW7I6mNV6bS1HMhcQIJphVGliEcE0dpWIvL8vQBaLgqgAipwsJ2V3eS3vzBZjuv16NQRwAYnhiBNkz6C8X6YzHc7XXqzjO5wQF0vC6rPSn9xq5qXywxK9Xa/XG94W8eT17hyfrSZ/FZ/J2IMsjq2cYCIAgCwTAANa3FkApknc8JZAAXrcu7Ui%2Br4Ht6qFLngVAXleNYnI%2BGHWlASZmAAbOYpEkmSeAUpgVJuNuEykEcxrikIZp0Um1JAXezbLMsKGEWhRykgQGwMEcGg9n23YfIJQn1Eo8mEUWoniX%2BHaDjJyn7l2P46WGXY9gZ2mDkqBFhqOyKbvGE7TrOTF1nZQiYGgnLMQmRIAPIEAgrJ7vu/r2muOYbvCjEEMxLluegzE%2BX5c5cZaT6HoWFkFmeNE4ZC15OUQDZNg%2Bi6vs%2B6VPh%2B77fr%2B/7UsW6BASB4E3JBEToDBZzwYhAVCX26E9b6WHZVWeEmSexHYmRFFUeS1n0RFzGsaa5pJTxhX8aNumHmpxASVJWlGXJZUYYpvyDW5uG1htS7jRiFFTaSM2UvC0UCLFLGimxHGEti3EgLxmDrUdqGqZgYk7Ucmm9gd4LFf1RwnUcZ0VjlNZXQWEBoyeIW5jZ8WsklmP7qt95HGAYCnJ2GmE2GAlAyVh7UwW20SWYJyWJm2Y4/CeOJT9yVw1GxPNtJjNvv25mw/1J2i%2BGvbM1T%2B3i3TqZ6bTktLkZZl05rfWGeLWsw6mVlxp5WLvMApJQryFryV4WRGA6G5/JTgb4kgIDG782NhWc5uW2wgjfbdyEG2LA5DsenvjoaGLvMQwA28edvhMAjtus7HPrnmvvx0HoIGzrEsAPQAFRl%2BXFeV0XYKl%2BXzJ0QQChHBX1cfLXlcd2Xrcw18DAHF4xzwm5WxpI3C5glHqJ2WyHl2QAUguQVHNgACOXhiEqEbHplZbnSjtYxKgngFfew5emyzsU0cC/60Ot8S5Ptkx3HCcLsnDsALKg0wVBeH3jQZxZHOTAHIuSuF5B4AU1lFqSniLKBU8JV7r1oAuICXMc4JwJgXWkJYaI3HxEoNoYIIBfxaL/f%2BOR4RmBeGgn2bgNDMSCEcMwzFqG/X%2BpfZIlMzACQNjvfBBJ4i7g%2BCQ7%2B5CHCULOO2GhIB0H0MYaw1hMiOEUyvu2XhFgOCrFoJwfwvA/AcC0KQVAnA3DWGsDadYmwWxmGSDwUgBBNBaNWKBAIkgMQaEkFwZUyQND%2BA0GRUiZgAAcwT9CcEkLwFgEgNAMIMUYkxHBeAKBAAwxxhitGkDgLAGAiAQDrAIGkdE5BKBoGhHQeIkRWDbFUME0irZSKSCOMAZAZYpAYjMLwaiRBiBmj0PwQQIgxDsCkDIQQigVDqAyaQXQQR5QPDSJwHg2jdH6KccYzgXl0RFPtKgbCtT6mNOaa0iG7jWYQA8OU%2Bgl1bFcGWLwdJWhVgQCQGUtIFSyAUAgG8j5IBgBSBYTQWgUoUkQBiOsmI4RWgXCWbwSFzBiAXC8jEbQrl0n2LKQHAgXkGC0BhdMrAMQvDAHjLQWgKTuC8CwCBIw4gCWzjRXgaUdF1lVlcuibY9jwiQh0dM2geAYgPERR4LA6z7h4GiZS0gzLiCHyUJ2KEhhgD8qME41YVADAJwAGpynlF5bksKxnCFEOIUZAz5BKDUOs2Z%2BglUoHMZYfQAqUmQFWKgUeOQKWtkBBTUwlhrBmASTK3p5p4CrDsIy5wEBXDTD8EEUI4RhhVFGEUTI2QBCxr0MUdNDAFgjASEECNEiBD9CmJ4Toegi2NFLYMRNiwU22EmHyfIcbG3zDrfmiQ4arFbC7eEjgejSDxN4Iko4ByGlNJaW0s5RwIC4EICQNmdj7kOLVasPyTAsAJB/KQVxkhkgYhSMqSQnizCSFIrE/wpFEj9siaQaJdiMSkS4KRYJiRgkvv8F4/wKRSJDvWYk5JqTV0ZOebkl5%2BTtnFK%2BT865VS2CcFaCwaUypWxMFxAYB2XBEgYi4B4rp%2BAel9KCOaoZprpDmomVa6ZugWHzKYIsylKyB1rOmYkrZhT0RHD2XWYgyHUPobxFhnDeGNCzsue865S6eEPLVVk15qArnxBKd8xTknRhIZQ62IT/zEhcAYUCkFlBwXTPhdCw1ZnEXItRQ4Q1mLeQ4rxeswlxLSXksNdSpVdKjH4FJBI5lFKjFsuQByw13L6jrP5YK6FIrthGPFZK%2BxMq5WYAVTS5VKc5MatdAoHVCp9WMENaRk1IyKOyCo1MoxtHbWqr9VYR1UWXU7vdY0L1PquF1YDUG%2BIIaWWup6JGvw0bOSZvjZyPNyaC3pDTY0Ub02Sg5Am0sQt9RBs1rm1WvoTalsNrmGWltlbtsdsm32hQPaRnMcHcOjZHBeP8bQxhpVEMRMeNnfOnpS67mydA%2BuzAm7Rg7t5Xeh9OHPHKh/cqHxkgz2NKCNdwDthgOPMydkvJBSdkqdg5U6piG%2BNHJYAoaUZZpTYYxLqCYBGF0hv6bIMjpWjUVetSAVI9HGPLP7VdgDmyoO7Owkh/HhPiek/J/aC5amPlLuSCu5HzyFNKc%2BaU8X1y/rIDSGkG4JPEg3BF/gvHFG6BGbBRCqFiKLMm6RSitFdnFNYsc/inzmAiUkrEO5qVnnaVxapQy/zLLpnBdC1K8LvKjFRaFRcWLYremJd4MlzIqXFW0sy6Bvgmrcu6oKwY%2BxxXhkSDK%2BMy1lWdDM5q8YB1NhGthuMR6isnAi6AU65YQNI7g1fUr5tqNMby0FDG%2BgHbU3s2za762gfi3jvLYG8WpoTaNurcnzWvvh2BgbaOxUTtdy1gbF7ev3lnO2OcDuwLonDZhezVF%2B9xduwvsgaeb9/727mPA5AGYHDyRkj%2BH8V42Jr/lSvv/XvpJiOaSa6u6IAkg/gh6/gwSZEiQkgiQPiyQyoXAqQvKyQrGCSnA32N%2B/anSf%2B6BABMuqwMqWQzgkgQAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/pagelivore/terse_independent_cognate_right_interview.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/terse_independent_cognate_right_interview.test.hpp)
