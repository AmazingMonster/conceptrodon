<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::IndependentLeftInterview`

## Description

`Pagelivore::IndependentLeftInterview` accepts a list of predicates.
Its first layer accepts a list of variables and returns a function.
When invoked, the function first binds the variables to the front of every predicate;
then, it returns the index of the first argument that satisfies all newly formed predicates, or `-1` if it cannot find the argument.

<pre><code>   Predicates...
-> LeftSides...
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> Exist (...&& Predicates&lt;LeftSides..., Arg<sub>I</sub>&gt;::value) ?
   I : -1</code></pre>

## Type Signature

```Haskell
IndependentLeftInterview ::   template<auto...> class...
                           -> auto...
                           -> auto...
                           -> auto
```

## Structure

```C++
template<template<auto...> class...>
struct IndependentLeftInterview
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
using Metafunction = IndependentLeftInterview<Equal>
::Page<Args...>;

static_assert
(Metafunction<2>::Page<0, 1, 2, 2>::value == 2);
static_assert
(Metafunction<-1>::Page<0, 1, 2, 2>::value == -1);
```

## Implementation

We will implement `IndependentLeftInterview` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:** Check several parameters at the front of the list.
If a match is found, then its index is returned.
Otherwise, drop the checked parameters and call itself with the rest.

Here's a simplified version of it:

```C++
template<template<auto...> class...Predicates>
struct IndependentLeftInterview
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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKxcpK4AMngMmAByPgBGmMQgAJwAzKQADqgKhE4MHt6%2BAUEZWY4CYRHRLHEJKbaY9qUMQgRMxAR5Pn6BdQ05za0E5VGx8UmpCi1tHQXdEwNDldVjAJS2qF7EyOwc5snhyN5YANQmyW4EAJ5pmAD6BMRMhAqn2CYaAIK7%2B4eYJ2fIE3QWCoLzenw%2BBEwLDSBkhp3OUJhTDhZyYXiIADosS8jgcmAoFFiMcpiJh8KJIc9kq8PhNiF4HEcAJIMLDXVmMQaYKgEFmQ4gANzwmAA7mCTAB2KwfI6yo6Q6GwzDwtGYrEhbnCPBYKk095yo50hkEI4k1BEZRMYDKmVyyXS/UGuVGxlCAwKBBgp12qVe71OhVIlFuVWoImg23%2B533Y2m4jm1CW61%2BqOy%2B2GlqOZC4gQTTCqNLEI6ho4CsReX72gC0XElABFThYThKG8kHSnU4GlSr0agjgAxPDECYRx2pjP0xlmi1W5VnQfDgij8dpqV2yMr2VzLM5hh5gtFktl7yVjeb%2B0dzcGkz%2BKz%2BOsQZZHKs4wEgEAsJgAa1uWWAEXQO54SyAAvW4l2pS8r1XB1oPHPAqF3fdCxOM84INKBwzMAA2cxsJJMk8ApTAqTcDUeSEbUSKJUgByHEdqXfY8K2WZYoPQmCjlJAgNgYI4NEbZsGw%2BdiOPqJRRPQ9NuN459azbITJJXetHyU7160bNTFLbcU0O9LtkTnENezoxdaJLIRMDQVlzN7IkAHkCAQeJdS0l0TWnRNZ3hBcJloyzrPQWjHOc4dw0gvSnXTNNIqjbciKQyED2LEzmNPMcrwvWLlNvG8HyfF9qQzdB30/H8bj/ACgLOUDwOXDiYK0zcEMS/MUKaldMOxHC8II8lDNI8itR1GjTIY7AmPLTBWI68dpMwHjiD4gSFI0kTsug8Tfha6zkKLWbUy6jE8N60l%2BspeEhsokasX8qyBHQF5JpPGaNsytcZKWo55KbNbwQyhrZS2o4dtzJLCwOqMIEhldPKTIyQpc8K9UB1NnorI4wDAU46zkmHvTYt7zzXfHU0%2BvizBOSw4wTeH4URsLsQigHUbldG51%2BonlJbXSWYarbSevD6FtkmtBL%2B1GVMJvnUw0nS3rl2D/UV0TRIM4NQyJd5gFJKFOVcyKvCyIxTVnP5cbdfEkBAdXfjh7yzm13W2EEQkmdeeWMpV9aMttns1QxJ3MD1136tlI3wmAU3rXNmmZ2TR2deDl2CDd47IM973/oAegAKnzgvC6L7OwTzgujgAFRI1OjkLkuPjLoum/z%2Bv/q%2BBgDi8Y54WsrY0lT0cwT91ETKZWyiCOAApUd3KObAAEcvDEcVfQ3eLs128GixiVBPFLKaO3tJlzZxqes/PiFEW7EeA/eYhgAN94I5NgBZBamCoLwO8aWOWTZVxORDT5PEIUop4QLyXrQUc746aO3vmnUEmdaSZiIjcfESg2hgggG/Fon9v45HhGYJ6IBYFuA0LRIIRwzC0SIYxEAaUT7JFxmYNint15oIJPEJcHxsHvzwQ4AhZwxZ0NIeQ76NCaHEIYTjU%2BNZWEWA4KsWgnB/C8D8BwLQpBUCcDcNYawhp1ibErGYZIPBSAEE0Io1YX4AiSAxBoSQXAJTJA0P4DQOFsJmAABxeP0JwSQvAWASA0OQ9RmjtEcF4AoEA5CLEaMUaQOAsAYCIBAOsAgaR0TkEoGgaEdB4iRFYNsVQXjsJVmwpII4wBkDZikBiMwvBCJEGINqPQ/BBAiDEOwKQMhBCKBUOoeJpBdBBBFA8NInAeBKJUWoyxWjOD2XRJkk0qBEIlLKRUqpNTvp2MphADweT6D7RMVwZYvA4laFWBAJAuS0j5LIBQCAtz7kgGAFIahNBaD8miRAGIcyYjhFaBcSZvAAXMGIBceyMRtBWTiWY3JKd7IMFoMCoZWAYheGACGWgtBoncF4FgT8RhxBoqHLCvAAoSJzPzFZdE2wzHhEhMooZtA8AxAeBCjwWA5n3DwEE/FpBKXEB3koOsUJDDAFZUYSxqwqAGAfgANWFCKey7IQW9OEKIcQPT2nyCUGoOZIz9ASpQHoyw%2Bg2XRMgKsVA/cch4qrICHGphLDWDMOEoVLSdTwFWHYclzgICuGmH4IIoRwjDCqKMIomRsgCGDXoYosaGALBGAkIIfqBECH6FMTwnQ9AZsaNmwY4bFhRtsJMdouaCjporSmyNabfWGK2BIaZHBVGkDCbwCJRx1nlMqdU2puyjgQFwIQEgVNTFnPMTK1YzkmBYASI%2BUgNjJDJAxCkCUkgHFmEkNhEJ/hsKJD8RwAJpAgmmIxNhLg2EvGJC8de/wjj/ApGwh2uZESokxOnfEq5KTrlpKWVkx5zyjmFLYJwVoLABQSirEwXEBgTZcESBiLg9jGn4Gaa0oIurOnaukLq/pBqhm6GoWMpgEz8WtvbZ2%2BZHBFkZPREcVZxZiBQZg3BvEiHkOoY0MOg5dyjkTpYecmViSbmoEOfEbJTyJMCdGJB6DVZONvMSFwchnzvmUD%2BUMsFQL1W6YhVCmFDh1UIs5EilFcz0WYuxbi9VhKJUks0fgUkAjKV4s0TS5AdL1WMvqHM1l7KgVcu2Jo3l/KzFCpFZgMVRLJWR1E3Kq0CglWilVYwdVOGtXdPw7IQjgzNEkeNdKl1VhzWBatUu21jQHVOqYaVt1Hr4heqpdano/q/CBtZPG0NrI61LGjSUHIPX0gxsaP1stBa%2BgVpG1NrNtaS2pvzTNqtIby3zEW/WltawNjNtOce6j77OAsbY7B%2BDErvrcfscO0dzSJ2nJEz%2B2dmB52jCXcy0957kMOIlM%2BiUzjJA7oqUEGjH7bBfouQkpJqT0nLOkyBgpRSIOsc2SwBQApswCiQxiJUEx0Njq9W02QuGcsavy4akAqQyMUamQd2ZQyIn0eWUxxCkHUfo8x9j3HJp9myfuRO5IU7IdXPE5Jh5OS%2BdHPocgNIaQbhY8SDcbnaCUf4boJp35/zAUQv09ryF0LYWmYk4i5FqLnOYAxVisQdmBUOeJaFglZK3NUqGV5nzAq/PMs0YFjlFwQs8paRF3gUXMgxfFcShLP6%2BDypS8q9L6izFZa6RIXLfT9UFZ0JT4rxgzU2Aqz6rRdrcycGzm%2BBrlh3Vds9VRSrvr6gdZcN11begw0VCW4NpNI3E3jc2wN9rmamgrfyGtubg%2BNtt62zWgYs2FsT4G423b3SqP0/CcdtnlS0cY9LFzgaPPbvjt2A979lznuvcXa2z7IAzDIeSMkfwbjHEhNvxKG9b6GecE/bEmdy6QCSH8Ou/wLxHCRISQRIZxZICULgVIZlZIFfLtD/Y/KxY9BpN/VfSJRA1iQVFyHIX/IAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/pagelivore/independent_left_interview.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/independent_left_interview.test.hpp)
