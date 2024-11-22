<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::TerseIndependentCognateLeftInterview`

## Description

`Pagelivore::TerseIndependentCognateLeftInterview` accepts a list of predicates.
Its first layer accepts a list of variables and returns a function.
When invoked, the function first binds the variables to the front of every predicate;
then, it returns the index of the first argument that satisfies all newly formed predicates, or `-1` if it cannot find the argument.

`Pagelivore::TerseIndependentCognateLeftInterview` prepares fewer base cases than `Pagelivore::IndependentCognateLeftInterview`.

<pre><code>   Predicates...
-> LeftSides...
-> Arguments...
-> Found ?
   index : -1</code></pre>

## Type Signature

```Haskell
TerseIndependentCognateLeftInterview ::   template<auto...> class...
                                       -> auto...
                                       -> auto...
                                       -> auto
```

## Structure

```C++
template<template<auto...> class...>
struct TerseIndependentCognateLeftInterview
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
using Metafunction = TerseIndependentCognateLeftInterview<Equal>
::Page<Args...>;

static_assert
(Metafunction<2>::Page<0, 1, 2, 2>::value == 2);
static_assert
(Metafunction<-1>::Page<0, 1, 2, 2>::value == -1);
```

## Implementation

We will implement `TerseIndependentCognateLeftInterview` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:** Check several parameters at the front of the list.
If a match is found, then its index is returned.
Otherwise, drop the checked parameters and call itself with the rest.

Here's a simplified version of it:

```C++
template<template<auto...> class...Predicates>
struct TerseIndependentCognateLeftInterview
{
    template<auto...LeftSides>
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
                        ((...&&Predicates<LeftSides..., First>::value))
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
                        ((...&&Predicates<LeftSides..., First>::value))
                        { return 0; }

                        else if constexpr 
                        ((...&&Predicates<LeftSides..., Second>::value))
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

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKxcpK4AMngMmAByPgBGmMQgAJwAzKQADqgKhE4MHt6%2BAUEZWY4CYRHRLHEJKbaY9qUMQgRMxAR5Pn6BdQ05za0E5VGx8UmpCi1tHQXdEwNDldVjAJS2qF7EyOwc5snhyN5YANQmyW4EAJ5pmAD6BMRMhAqn2CYaAIK7%2B4eYJ2fIE3QWCoLzenw%2BBEwLDSBkhp3OUJhTDhZyYXiIADosS8jgcmAoFFiMcpiJh8KJIc9kq8PhNiF4HEcACrxJQASQYWGunMY7VQwGYkJCmCoBA5kOIADc8JgAO5gkwAdisHyOaqOkOhsMw8LRmKxwtFQjwWCpNPe6qOdIZBCOJNQRGUTGAOtV6qVKotlvV1sZQgMCgQYO97uVwZD3s1SJRbj1qCJoLdEZ99xtduIDtQTpd4eTao9VpajmQuIEE0wqjSxCOcaOkrEXl%2BHoAtFwlQARU4WE6KzvJT25vNR7W69GoI4AMTwxAmia9ecL9MZ9sdzp1ZynM4Ic4X%2BeV7qTu7Vc2LpYY5cr1dr9e8TcPR49g6PlpM/is/nbEGWR2bOMBIBAFgmAAa1uLIBTJO54SyAAvW5t2pJ9nz3T1kIXPAqDPC8qxOe80MtKAEzMAA2cxiJJMk8ApTAqTcQ1hBNGiiVISdp1nakAJvRtlmWJD8JQo5SQIDYGCODQux7TsPj4/j6iUGT8ILISRJ/Nt%2B0khTdw7L9NJDDsu10jT%2BwVPCQ2HZF11jMdWK3FjayETA0E5OyxyJAB5AgEFZHdd19W0VyzNd4U3CYWIcpz0BYjyvJnBNENM70C3zBLkxPKisMhS8a2sri73nZ9HxSrS31fT9v1/alC3QACgNAm5wIidAoLOWD4J8/ie1QjrvQwjKKxwwyj0I7ESLIijyQs2j6ONU1mJs9jsE4htMB4watP3ZTiFE8T1P06SiuQuTfl6pzsOrNaF2GjEyLG0kJspeFpsYwksTCxyBHQF4ltvVaDoKjbMGErajjU7s9vBfLuqOI6jhOstMqrC68wgJGjwC7NLOi1k4vNKHk2%2BxsjjAMBTnbVTUYjXi/offcKYXTbRLME5LHTTMMfhLHYuxeLIbxtUCfXMHqfWqSIb5tUjrpxKAaB0TWwk8Goe0qneYXfTjL%2B9Wur03sDISmTzJjOMiXeYBSShXkzRkrwsiMO01z%2BMn/XxJAQEN350aCs5TfNthBBe67EI1/KtZM/L3dHfUMR9zALf99qjht8JgHtl1HdZ1cc29s3Y79ggA9BYPQ/294AHoACpK6r6ua9LsEK6r5kaPzo5q7rj4G5rrvK/biGvgYA4vGOeEnK2NJ87nMEI9Ray2RcogjgAKTnPyjmwABHLwxAVMNDzSktToR6sYlQTw62WwcPTZR3SaX4vPl1ouIUREcZ6j95iGAK2PiTu2AFlAZMCoF4AejR04shnJgDkXJXC8g8AKCy9FxTxGlHKeEG8t60DnABdm3tP4FyDgOWkRYqI3HxEoNoYIIAAJaMA0BOR4RmC%2BiAXBbgNAsSCEcMwLEmEcRALlG%2ByQyZmF4sHfeZCCTxG3B8ahgC6EOAYWceWfDWHsJBjwnhzCBGk1vq2URFgOCrFoJwfwvA/AcC0KQVAnA3DWGsFadYmwmxmGSDwUgBBNCGNWMBAIkgMQaEkFwRUyQND%2BA0CRYiZgAAcUT9CcEkLwFgEgNDsPMZY6xHBeAKBAOwjxFjDGkDgLAGAiAQDrAIGkdE5BKBoGhHQeIkRWDbFUFE4izZiKSCOMAZAJYpAYjMLwSiRBiAmj0PwQQIgxDsCkDIQQigVDqHyaQXQQRZQPDSJwHgRiTFmM8VYzgbl0SVNtKgTCLS2kdK6T0kGfimYQA8HU%2Bg50XFcGWLwPJWhVgQCQLUtI9SyAUAgL8/5IBgBSG4TQWgEpskQBiHsmI4RWgXE2bwBFzBiAXDcjEbQjk8luNqXnNyDBaDIqWVgGIXhgCxloLQbJ3BeBYCAkYcQZLpy4rwJKGieyKyOXRNsNx4RITGKWbQPAMQHgYo8FgPZ9w8BJPpaQTlxAT5KHbFCQwwBRVGE8asKgBgv4ADUZSyjctyFFszhCiHEDM8Z8glBqD2Ss/QGqUB2MsPoMV2TICrFQOPHIdLmyAlJqYSw1gzDpKVSM008BVh2HZc4CArhph%2BCCKEcIwwqijCKJkbIAhk16GKLmhgCwRgJCCHGhRAh%2BhTE8J0PQFbGjVsGOmxYWbbCTD5PkFN7b5gttLRIWNjitgDriRwUxpA0m8AyUcc57TOndN6bco4EBcCEBIMzVxbz3E6tWF5JgWAEhflID4yQyQMQpEVJIAJZhJDERSf4YiiRR0JNIEk1xGJiJcGIlExIUSv3%2BECf4FIxEJ17IyVknJ278lfJKd8spRyqmAuBU8xpbBOCtBYJKRUzYmC4gMHbLgiQMRcH8YM/AwzRlBFtZM610hbXzIdUs3Q3C1lMA2fS7ZY7dlLIyYcip6IjinJrMQTD2HcN4gI0RkjGhl0PL%2BU8jdIj3k6sKT81Ajz4jVKBep%2BTowMNYebBJsFiQuDsMhdCygcKlloqReamzGKsU4ocOaglvIiUkr2eSyl1LaXmsZRqlllj8CkgUZyullieXID5eawV9Q9mivFUiqV2xLGyvlW4pVKrMBqqZZq5OKm9XOgUEauUprGDmuo1a6ZdHZAMcWZY5jzrtUhqsO6hLXqj2%2BsaAGoNQiWthojfEKNXLvU9HjX4RNnJ82ps5CWzNZb0g5saNNxbJQchzaWOW%2Bo42m0rYbX0DtG221zBrV2%2Bth2%2B3zZHQoId0zOPjsnfsjgwnRM4bwxqkGUn/HLtXcMjdrzlPQd3Zgfdowj3CpfW%2BojATFRAcVMEyQN6OlBEe%2BB2wkGPkFKKaU8pxytPIYaU09DInLksAUJKEskpCMYm1BMMja6o1jNkDR6rFq6uOpAKkVj7Gtmjoe2Bg5CGTmYQw6T8nlPqe09tPcnT/yN3JC3Zjr5amNMApqbLp5/DkBpDSDcKniQbhS7ISTujdALOwvhYijFdmreYuxbilz6nCXEtJUFzAFKqViF8wq/zzKUsMrZaFrlSzIvRYVbF4VliEsSouMlmVIz0u8Ey5kbL6rmX5eg3wfVxXjVlfMW4yrUyJA1bmfa%2BrOhOdNeMG6mw7WY1WL9WWTgpd/z9csOGqdkbnr1/2wmpNtaCgzfQEdhbhblsD%2B7WP9bl3NtjcrU0Dte3tvz6bSP87Aw9sXYqP215awNjDt38K/nPHOAvbFxTuskvJrS9%2B%2Bu3YAOoOfOB6Dw9nHIcgDMER5IyR/BhMCSk7/RUb9UDE/TJdHXJHdY9EASQfwc9fwKJEiRISQRIYJZIRULgVIYVZIbjdJTgQHJ/UdAZEA3AsApXVYJVLIZwSQIAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/pagelivore/terse_independent_cognate_left_interview.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/terse_independent_cognate_left_interview.test.hpp)
