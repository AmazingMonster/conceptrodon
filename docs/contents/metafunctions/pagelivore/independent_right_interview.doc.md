<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::IndependentRightInterview`

## Description

`Pagelivore::IndependentRightInterview` accepts a list of predicates.
Its first layer accepts a list of variables and returns a function.
When invoked, the function first binds the variables to the end of every predicate;
then, it returns the index of the first argument that satisfies all newly formed predicates, or `-1` if it cannot find the argument.

<pre><code>   Predicates...
-> RightSides...
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> Exist (...&& Predicates&lt;Arg<sub>I</sub>, RightSides...&gt;::value) ?
   I : -1</code></pre>

## Type Signature

```Haskell
IndependentRightInterview ::   template<auto...> class...
                            -> auto...
                            -> auto...
                            -> auto
```

## Structure

```C++
template<template<auto...> class...>
struct IndependentRightInterview
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
using Metafunction = IndependentRightInterview<Equal>
::Page<Args...>;

static_assert
(Metafunction<2>::Page<0, 1, 2, 2>::value == 2);
static_assert
(Metafunction<-1>::Page<0, 1, 2, 2>::value == -1);
```

## Implementation

We will implement `IndependentRightInterview` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:** Check several parameters at the front of the list.
If a match is found, then its index is returned.
Otherwise, drop the checked parameters and call itself with the rest.

Here's a simplified version of it:

```C++
template<template<auto...> class...Predicates>
struct IndependentRightInterview
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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKxcpK4AMngMmAByPgBGmMQgAJwAzKQADqgKhE4MHt6%2BAUEZWY4CYRHRLHEJKbaY9qUMQgRMxAR5Pn6BdQ05za0E5VGx8UmpCi1tHQXdEwNDldVjAJS2qF7EyOwc5snhyN5YANQmyW4EAJ5pmAD6BMRMhAqn2CYaAIK7%2B4eYJ2fIE3QWCoLzenw%2BBEwLDSBkhp3OUJhTDhZyYXiIADosS8jgcmAoFFiMcpiJh8KJIc9kq8PhNiF4HEcAJIMLDXVmMAgAJTwwAQBBZkOIADc8JgAO5gkwAdisHyOCqOkOhsMw8LRmKxPL5wjwWCpNPeiqOdIZBCOJNQRGUTGAavliplcqNxsVpsZQgMCgQYNdjtlvr9ruVSJRbg1qCJoIdQbd9zNFuIVtQNrtgdjCqdJpajmQuIEE0wqjSxCOEaOwrEXl%2BToAtFwZQARU4WE7S5vJZ3pjMh1Xq9GoI4AMTwxAm0ZdGez9MZluttrVZxHY4IE6nmdljpj64Vc1z%2BYYheLpfLle8Ne3O6d3Z3xpM/is/kbEGWR1rOMBIBALCYAGtblkwAROgdzwlkABetyrtSN63huzpwVOeBUAeR4licl6IcaUBRmYABs5h4SSZJ4BSmBUm4y4TKQRzavyQh6uRUbUl%2BZ7VssyywVh8FHKSBAbAwRwaC2bbNh8XHcfUSgSVhWZ8QJb4Np2okyeuTYvqpfpNi2mkqZ2UqYX6vbIou4YDsOo7UWW5lCJgaCsjREZEgA8gQCDxAaunuuac4pgu8JUQQNG2fZ6A0a57ljsxhpXpumaGRme6kahkLHtZRAVlWF6Tre14JVeD73s%2Br7vtS2boF%2BP7/jcgHAaBZwQVBa7cfBuk7shKVFuhbXrjh2L4YRxHkiZFGBTRdG6vq0WsVlHE9VOcmYPxxCCcJynaeJ%2BWIVJvwdfZaGlvNGZ9RihGDaSw2UvCIUCGFtG8vRjGEtiLEgGxmBzVtcGLctglKa2G3gjlLUKjtRx7QWqUlkdsYQDD66%2BampkRR50Xw1OM3nkcYBgKcjaKejrqcV9uWboTsbyStRxmCcliJsmSPwijUUvTFIOxpj1YieT/piUD7PGjtPM8ZTgn1tz7aE%2BpxPA2pkv6ST2kK7LG4dl2CXGWGTlYu8wCklCnKeQlXhZEYFoLn8%2BOeviSAgJrvyI/5Zy6/rbCCM9p0wcrd7y%2BrOX2/2moYu8xDAEbOUm%2BEwDm3alv0/OabO6HHugsrSt%2BwA9AAVDnud5/nGdgtnudHAAKuRBAKEceeFx8xf5w3Oe10DXwMAcXjHPC9lbGklcTmCAeouZTKOeZABSE7eUc2AAI5eGIUoBtuSV5vtUOljEqCeJl57dk6TKW3jRwT77i9qwZ7yD2ZQch2HE6R2bACyS1MFQXht40ccsmyrichNgrxFFBKeEs9560AnF%2BRmScw5ozTrSHMpEbj4iUG0MEEBn4tDfh/HI8IzAvEgU7NwGgaJBGpjRPBr13qH2SPjMwnFlYryQQSeIq4PjoJflghwOCzji1elAohJDyHkPwW9LK1D8b1noRYDgqxaCcH8LwPwHAtCkFQJwNw1hrAmnWJsGsZhkg8FIAQTQMjVi/gCJIDEGhJBcGlMkDQ/gND4TwmYAAHK4/QnBJC8BYBIDQxClEqLURwXgCgQDEOMcomRpA4CwBgIgEA6wCBpHROQSgaBoR0HiJEVg2xVCuLwrWPCkgjjAGQHmKQGIzC8BIkQYgeo9D8EECIMQ7ApAyEEIoFQ6gomkF0EEcUDw0icB4LI%2BRiiTGqM4M5dEKTzSoBQvkwpxTSnlKOJUmmEAPCZPoIdfRXBli8EiVoVYEAkAZLSFksgFAIAXKuSAYAUgzB8DoEKMJEAYiTJiOEVoFwRm8G%2BcwYgFxnIxG0HZSJhiMluwIM5BgtA/m9KwDELwwBwy0FoGE7gvAsA/iMOIJFo4IV4GFORSZRY7Lom2IY8IkI5G9NoHgGIDxgUeCwJM%2B4eBfHYtIKS4gm8lCNihIYYAjKjAmNWFQAwYcABqYpxTOXZP8jpwhRDiHaU0%2BQSg1CTP6foEVKBNGWH0EysJkBVioF7jkLFtZAR41MJYawZggl8vqfqeAqw7DEucBAVw0w/BBFCOEYYVRRhFEyNkAQ/q9DFEjQwBYIwEhBC9VwgQ/QpieE6HoFNjR02DGDYsMNthJjtEzQUZNJaE2hqTZ6nRWwJBjI4Ao0ggTeDBKOEsopJSykVMsZs3AhASC0wMYcoxErVjuSYFgBIL5SDmMkMkDEKRpSSGsWYSQeF/H%2BDwokTxHBvGkF8QYjEeEuB4VcYkVxZ7/A2P8CkPCLbJnBNCeEsdUTTnxLOYk2ZqSbl3N2TktgnBWgsGFNKWsTBcQGDNlwRIGIuBWJqfgOpDSgiapaeq6Qmquk6t6boZ5gymDDOxY25trapkcBmck9ERwFllmIKB8DkG8QwbgwhjQRwtmoB2fEYddCjkSpiec7jlzdlpNuSJ%2B5IGwO1hY48xIXBiE0FoG8ygnzemAt%2BcqzTwLQXgocMq6FnI4UIsmci1F6LMXKtxSKglKj8Cki4aSrFKiKXICpcq2l9RJmMuZb8tl2wVGcu5YYvlArMBCrxaKqOgmpW2gUHKiUirGDKvQ2qtpWHZA4Z6So/D%2BrxUOqsMa3zZrZ2WsaDau1NDCtOpdfEN1ZLzU9G9X4X1rJo2BtZFWpY4aSg5A6%2BkCNjRutFpzX0EtA2xtpsrQWxN2aJtloDcW%2BYs3q0NrWBsetBy91kafZwejjGINQZFestjVjOMDrqcOg5An30TswFO0Ys76UHqPXB6x0o73SjsZIddxSgjkefbYV9xzomxISUkuZ4n/3ZNycBhjKyWAKGFHmYUsGMSqgmEhwdbrGmyAwxllV2XdUgFSIR4joydsTN6cEqjczaMoRA4j5HqP0eY/NFxnjezkjJFHaD05wmufQ8k7st6yA0hpBuGjxINx2dIIR1h15Hk1NfJ%2BcC7TauQVgohYZ7jMKTOIvs5gFFaKxBWZ5TZ/FgWcVEqc2S3pbmPM8q8/SlRvmWUXACxy%2BpIXeBhcyBF4V%2BKYvvr4NKhL8rktKMMWl1pEhMudO1TlnQpP8vGCNTYErHrVFWoLJwDOn4auWGdW211T1s9Tda36xbegg0VDm71uNA3Y3DdWz15rqamgLfyEtyveaRtJuWxmnv82Vv17W9thQda2mkep0E/bTOSlI5RxWNnI0OeXaHbsG7b6Tn3cezOxtr2QBmDgzz/wjibH%2BJ59Kc9j6aecBfRE8dc6QCSH8Eu/wrj8KJEkIkOxyQ0oXAqQ9KyQc%2Bbaj%2Bu%2Bpie61S9%2B8%2BISUBHEvKHkOQb%2BQAA%3D)

## Links

- [source code](../../../../conceptrodon/pagelivore/independent_right_interview.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/independent_right_interview.test.hpp)
