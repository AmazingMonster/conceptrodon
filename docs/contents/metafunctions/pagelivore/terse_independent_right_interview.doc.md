<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::TerseIndependentRightInterview`

<p style='text-align: right;'><a href="../../../index.md#list-examinations-1">To Index</a></p>

## Description

`Pagelivore::TerseIndependentRightInterview` accepts a list of predicates.
Its first layer accepts a list of variables and returns a function.
When invoked, the function first binds the variables to the end of every predicate;
then, it returns the index of the first argument that satisfies all newly formed predicates, or `-1` if it cannot find the argument.

`Pagelivore::TerseIndependentRightInterview` prepares fewer base cases than `Pagelivore::IndependentRightInterview`.

<pre><code>   Predicates...
-> RightSides...
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> Exist (...&& Predicates&lt;Arg<sub>I</sub>, RightSides...&gt;::value) ?
   I : -1</code></pre>

## Type Signature

```Haskell
TerseIndependentRightInterview ::   template<auto...> class...
                                        -> auto...
                                        -> auto...
                                        -> auto
```

## Structure

```C++
template<template<auto...> class...>
struct TerseIndependentRightInterview
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
using Metafunction = TerseIndependentRightInterview<Equal>
::Page<Args...>;

static_assert
(Metafunction<2>::Page<0, 1, 2, 2>::value == 2);
static_assert
(Metafunction<-1>::Page<0, 1, 2, 2>::value == -1);
```

## Implementation

We will implement `TerseIndependentRightInterview` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:** Check several parameters at the front of the list.
If a match is found, then its index is returned.
Otherwise, drop the checked parameters and call itself with the rest.

Here's a simplified version of it:

```C++
template<template<auto...> class...Predicates>
struct TerseIndependentRightInterview
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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKxcpK4AMngMmAByPgBGmMQgAJwAzKQADqgKhE4MHt6%2BAUEZWY4CYRHRLHEJKbaY9qUMQgRMxAR5Pn6BdQ05za0E5VGx8UmpCi1tHQXdEwNDldVjAJS2qF7EyOwc5snhyN5YANQmyW4EAJ5pmAD6BMRMhAqn2CYaAIK7%2B4eYJ2fIE3QWCoLzenw%2BBEwLDSBkhp3OUJhTDhZyYXiIADosS8jgcmAoFFiMcpiJh8KJIc9kq8PhNiF4HEcACrxJQASQYWGunMYBAASnhgAgCBzIcQAG54TAAdzBJgA7FYPkcVUdIdDYZh4WjMViBULhHgsFSae9VUc6QyCEcSagiMomMAtcrVQqlWbzarLYyhAYFAgwZ7XYrA0HPeqkSi3DrUETQS6w177labcQ7agHU7Q4mVW6LS1HMhcQIJphVGliEcY0dxWIvL83QBaLgKgAipwsJ3l7eS7uzOYjmu16NQRwAYnhiBN4x6c/n6YzbfbHVqzhOpwQZ3Pc4rXQntyq5oXiwxS%2BXK9Xa94G/uD27%2BwfzSZ/FZ/K2IMsjo2cYCQCAWEwADWtxZMAEToHc8JZAAXrcm7Ug%2Bj47u6SFzngVAnmeFYnLeqHmlAcZmAAbOYREkmSeAUpgVJuOuEykEc%2BrCkIRrUXG1J/le9bLMsiF4chRykgQGwMEcGgdl27YfHx/H1EoMl4XmQkiV%2BLa9pJCnbm2H6aUGbYdrpGm9nKuFBoOyKrtGI7jpO9FVtZQiYGgnIMTGRIAPIEAgrJbtu3rWkuGYrvCdEEAxjnOegDGed5U7saad67rmpk5kelGYZC572UQNZ1jes6PveKV3i%2Bz7vp%2B37Uvm6B/gBwE3KB4GQWcMFwb5/FdihHWeuhGVlthhkHgR2LEaR5HkhZNGhQxTGGsa8WcXlPGDVpu7KcQoniep%2BnScVqFyb8vXOVhlYrXOw0YqRY2khNlLwhFAhRYxgrMaxhLYhxIBcZgy17UhSmYMJG1HGpnY7eCBXdUcB1HEdJaZRWZ05hASMHoFmaWTFrLxaj26LdeRxgGApytqpuNBrxf2Fbu5M5utolmCclipumGPwljcUfQlUNhvj9YSbTT7diZkPdQdgvBp29Nk9twtU4m2mU6Lc76cZVOq11enC2rEOJuZUZuVi7zAKSUK8iaMleFkRg2iufyk76%2BJICA%2Bu/OjwVnMbptsII72XQhOtCz2fb7q7w66hi7zEMAFv7lb4TALbTr2yzy5Zp70d%2B6COsayLAD0ABURfFyXpd52ChfF8y1EEAoRwl%2BXHyV6XLdF43ENfAwBxeMc8LOVsaS1zOYJh6i1lsq51kAFIzv5RzYAAjl4YhyiG%2B5pUWx0I5WMSoJ4uXXv2bpsvbJNHDP2t9pfIuj1ZEdRzHM7xzbACygNMFQXhd40KcslOmAci5K4Xks1RTxElDKeEi9l60BnH%2BNmGcY44xzrSAslEbj4iUG0MEEA34tE/t/HI8IzAvHgR7NwGgGJBCOGYBiJDPrfVPskUmZheI6w3hggk8RNwfFwe/AhDgiFnGbKQkACCKFULoXQ0RjCSZn2bGwiwHBVi0E4P4XgfgOBaFIKgTgbhrDWAtOsTYDYzDJB4KQAgmhlGrEAgESQGINCSC4PKZIGh/AaGIkRMwAAOHx%2BhOCSF4CwCQGhKGaO0bojgvAFAgEoVYrRyjSBwFgDARAIB1gEDSOicglA0DQjoPESIrBtiqB8URRsRFJBHGAMgIsUgMRmF4BRIgxAjR6H4IIEQYh2BSBkIIRQKh1CJNILoII0oHhpE4DwFRaiNHWJ0Zwdy6JsnWlQBhMpFSqk1LqSDBxjMIAeAKfQU6ZiuDLF4AkrQqwIBIHyWkQpZAKAQHuY8kAwApC0JoLQMUsSIAxAWTEcIrQLjTN4EC5gxALjuRiNoJyCSLH5J9gQdyDBaCgpGVgGIXhgDRloLQWJ3BeBYAAkYcQmLJzwrwOKaiCyyxOXRNsCx4RISqJGbQPAMQHhQo8FgBZ9w8AhKJaQGlxBd5KFbFCQwwAOVGGsasKgBgY4ADUpTSnctyMF/ThCiHEH0zp8glBqAWWM/Q0qUAGMsPoTlsTICrFQIPHIhLGyAhJqYSw1gzCRNFW0408BVh2Cpc4CArhph%2BCCKEcIwwqijCKJkbIAgw16GKAmhgCwRgJCCIGwRAh%2BhTE8J0PQ2bGh5sGFGxYsbbCTHaAWgoWbq3ppjZmgNxitgSFmRwdRpAIm8CiUcTZlTqm1Pqfso4EBcCEBIEzcxFzLHytWN5JgWAEgflIHYyQyQMQpHlJIJxZhJBETCf4IiiQAkcCCaQEJ5iMRES4ERHxiQfF3v8M4/wKQiLdoWVEmJcS52JJuWk25GSVk5Oea8k5xS2CcFaCwcU8pGxMFxAYG2XBEgYi4I45p%2BBWntKCAa7perpAGsGcakZuhaETKYFMolHau09sWRwZZWT0RHHWVWYgsH4OIbxChtDGGNBjqOQ8k507WGXPlcku5qBjnxFyS86TwnRgwbg42HjHzEhcEod835lAAUjIhSCrVBmoUwrhQ4LVSLeSovRQsrFOK8UEq1SS6V5LtH4FJIImlhLtH0uQIyrVLL6gLI5VykFvLtjaIFUKixorxWYElaSmVCcJOKsdAoVVMoNWMC1fh3VvSiOyBI8M7R5GzVyvdVYK1IXbWrodY0Z1rrmEVc9d6%2BIvraV2p6EGvwIbORJojZyRtSw40lByP19I8bGhDcrcWvo1bxuzdzQ28tGai3zdreGqt8wVtNvbWsDYbbzlnro1%2Bzg7HOMIaQ9KkGfHHFjona06d5zxP/oXZgJdoxV1sovVetDTj5RvvlK4yQ%2B6qlBHo9%2B2wv6rlJJSekzJqy5PgaKSU6DHHtksAUOKIs4pUMYk1BMLDk7fUdNkAR/L2qismpAKkSj1GZnHfmSMqJTHVmsYwjBjHWOcd44J9aQ5CnHnTuSLOmHNypMyaeXkwXJyvrIDSGkG4uPEg3D5xg9HRG6A6f%2BYC4FUKjN6%2BhbC%2BFFnpPIusxitzmBsW4rEI54VzmyUReJZSzztKRm%2Bf88KwLbLtEhe5RccL/K2nRd4LFzI8WpVkuS/%2BvgSr0tqqy5oixuWekSAKwMo1xWdA07K8YS1Nhqv%2Bp0Y6ksnA86/ma5YL1vafVvWL4tnroaNt6EjRUVbI3U3jZTVNnbw2us5qaOt/Im3G%2Blum5mrb%2BaR9re2%2B33bR2FCtt6bRpnkSzuc%2BqZj7HNZeeTX5w9qduxnt/uuW9j7K6O0/ZAGYNDyRkj%2BA8c4sJ9/5T3s/czzgP74nzrXSASQ/gW6/gPixEiQkgiQriyQ8oXAqQbKyQa%2BvaX%2Bp%2BNiZ6TSH%2B6%2B0SyBPEIqrIOQ/%2BQAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/pagelivore/terse_independent_right_interview.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/terse_independent_right_interview.test.hpp)
