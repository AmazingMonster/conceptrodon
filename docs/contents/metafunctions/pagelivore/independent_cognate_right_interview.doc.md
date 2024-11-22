<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::IndependentCognateRightInterview`

## Description

`Pagelivore::IndependentCognateRightInterview` accepts a list of predicates.
Its first layer accepts a list of variables and returns a function.
When invoked, the function first binds the variables to the end of every predicate;
then, it returns the index of the first argument that satisfies all newly formed predicates, or `-1` if it cannot find the argument.

<pre><code>   Predicates...
-> RightSides...
-> Arguments...
-> Found ?
   index : -1</code></pre>

## Type Signature

```Haskell
IndependentCognateRightInterview ::   template<auto...> class...
                                   -> auto...
                                   -> auto...
                                   -> auto
```

## Structure

```C++
template<template<auto...> class...>
struct IndependentCognateRightInterview
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
using Metafunction = IndependentCognateRightInterview<Equal>
::Page<Args...>;

static_assert
(Metafunction<2>::Page<0, 1, 2, 2>::value == 2);
static_assert
(Metafunction<-1>::Page<0, 1, 2, 2>::value == -1);
```

## Implementation

We will implement `IndependentCognateRightInterview` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:** Check several parameters at the front of the list.
If a match is found, then its index is returned.
Otherwise, drop the checked parameters and call itself with the rest.

Here's a simplified version of it:

```C++
template<template<auto...> class...Predicates>
struct IndependentCognateRightInterview
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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKxcpK4AMngMmAByPgBGmMQgAJwAzKQADqgKhE4MHt6%2BAUEZWY4CYRHRLHEJKbaY9qUMQgRMxAR5Pn6BdQ05za0E5VGx8UmpCi1tHQXdEwNDldVjAJS2qF7EyOwc5snhyN5YANQmyW4EAJ5pmAD6BMRMhAqn2CYaAIK7%2B4eYJ2fIE3QWCoLzenw%2BBEwLDSBkhp3OUJhTDhZyYXiIADosS8jgcmAoFFiMcpiJh8KJIc9kq8PhNiF4HEcAJIMLDXVmMdqoYDMSEAJTwwAQBBZkOIADc8JgAO5gkwAdisHyOKqOkOhsMw8LRmKxAqFwjwWCpNPeqqOdIZBCOJNQRGUTGAWuVqoVSrN5tVlsZQgMCgQYM9rsVgaDnvVSJRbh1qCJoJdYa99ytNuIdtQDqdocTKrdFpajmQuIEE0wqjSxCOMaO4rEXl%2BboAtFwFQARU4WE7y9vJd3ZnMRzXa9GoI4AMTwxAm8Y9Ofz9MZtvtjq1ZwnU4IM7nucVroT25Vc0LxYYpfLlerte8Df3B7d/YP5pM/is/lbEGWR0bOMBIBALCYABrW4sh5Mk7nhLIAC9bk3akH0fHd3UQuc8CoE8zwrE5bxQ80oDjMwADZzEIkkyTwClMCpNx1wmUgjn1YUhCNKi42pP8r3rZZlgQ3CkKOUkCA2Bgjg0Dsu3bD5eL4%2BolGk3C80E4SvxbXsJPk7c2w/DSgzbDsdPU3s5RwoNB2RVdoxHcdJzoqsrKETA0FZeiYyJAB5AgEHiE0DO9a0lwzFd4Vogh6Icpz0HojyvKnNjTTvXdcxMnMjwojDIXPOyiBrOsb1nR972Su8X2fd9P2/al83QP8AOAm5QIidAILOaDYK3PikIMg80PSsssK67d8OxIiSLI8lzOokL6MYw1jTijjcu4ga50UzAhOIESxLUvSpKKlDZN%2BHqnMwytlpzIaMRI0bSXGyl4XCgRIoYwUmJYwlsXYkBOMwJa9sQ1b1pE1TOx28F8o6lUDqOI6SwyiszsTCAEe3ALMws6LvLi5G5wW68jjAMBTlbFTsc9Hi/oK3dScTJSNqOMwTksVN0zR%2BEMdij74ohxNcfrcTqeDSSwe580DoF/jaZE5t%2Be7UmtPJ8HNNloyKb0lXFZ3Hs%2B2Ssyo1crF3mAUkoU5Hzkq8LIjBtFc/mJ318SQEBdd%2BVGgrOQ3jbYQR3su%2BD1afZXtfy53h11DF3mIYAzfyi3wmAa2nVt5nlyzd3I590F1bVoOAHoACoC8Lovi5zsF88Lo4ABUqIIBQjiL0uPnL4uW4Lxuwa%2BBgDi8Y54ScrY0lrmcwRD1ErKZFyrIAKRnPyjmwABHLwxDlEN91SotjrhysYlQTwcuvfs3SZW2iaOGfA9XrXjPeUfLLDiOo5nWOrYAWTWpgqC8LvGiTlk2VcJyDwPJzIzVFPESUMp4SL2XrQGcf5WZpyjljLOtICwURuPiJQbQwQQHfi0L%2BP8cjwjMC8BBbs3AaHokEem9FSGfW%2BqfZIxMzA8XVhvTBBJ4ibg%2BHgj%2BhCHDELONLT6iDKHULoXQshX1cpMOJs2NhFgOCrFoJwfwvA/AcC0KQVAnA3DWGsBadYmwGxmGSDwUgBBNDKNWIBAIkgMQaEkFweUyQND%2BA0ERQiZgAAcPj9CcEkLwFgEgNBUM0do3RHBeAKBAFQqxWjlGkDgLAGAiAQDrAIGkdE5BKBoGhHQeIkRWDbFUD4wijZCKSCOMAZARYpAYjMLwciRBiBGj0PwQQIgxDsCkDIQQigVDqESaQXQQRpQPDSJwHgKi1EaOsTozgbl0TZOtKgdCZSKlVJqXUo4DSGYQA8AU%2Bgp0zFcGWLwBJWhVgQCQPktIhSyAUAgPcx5IBgBSDMHwOgYpYkQBiAsmI4RWgXGmbwIFzBiAXDcjEbQjkEkWPyV7AgbkGC0FBSMrAMQvDAGjLQWgsTuC8CwABIw4hMWTnhXgcUVEFllkcuibYFjwiQlUSM2geAYgPChR4LACz7h4BCUS0gNLiC7yUK2KEhhgAcqMNY1YVADBRwAGpSmlG5dkYL%2BnCFEOIPpnT5BKDUAssZ%2BhpUoAMZYfQnLYmQFWKgQeORCWNkBETUwlhrBmEiaKtpxp4CrDsFS5wEBXDTD8EEUI4RhhVFGEUTI2QBBhr0MUBNDAFgjASEEQNgiBD9CmJ4Toehs2NDzYMKNixY22EmFyfI4aq3zHLRmiQAbjFbGbQEjg6jSARN4FEo4mzKnVNqfUhxBzcCEBIIzcxFzLHytWF5JgWAEgflIHYyQyQMQpHlJIJxZhJCETCf4QiiQO1BNICE8xGJCJcEIj4xIPib3%2BGcf4FIhFu0LKiTEuJs7Ek3LSbcjJKycnPNeSc4pbBOCtBYOKeUjYmC4gMFbLgiQMRcEcc0/ArT2lBANd0vV0gDWDONSM3QXyJlMCmUS2Znb5kjKicsrJ6IjjrKrMQaDsH4N4iQyhtDGgjiHNQMc%2BIU7WGXPlcku5gmHknNyS8qTbyoMwcbFxj5iQuBUJoLQX5lAAUjIhSCrV%2BmoUwrhQ4LVSLOSovRQsrFOK8UEq1SS6V5LtH4FJIImlhLtH0uQIyrVLL6gLI5VykFvLtjaIFUKixorxWYElaSmVcdxOKsdAoVVMoNWMC1bh3VvSCOyCI8M7RpGzVyvdVYK1wXbUrodY0Z1rrmHlc9d6%2BIvraV2p6EGvwIbWRJojaydNMbM3pHjY0PrI2Sg5EG0sLN9QuulvG8Wvo1bpuVrmPm2tRaVuNqG%2B2hQrbenUa7T2xZHBWPsbgwh6VeyeOOP4%2BO1pU7zlid/fOzAi7RgrrZWei9KGnHyhffKVxkg91VKCCdz9thv1XKSSk9JmTVmydA0UkpkG2PbJYAocURZxTIYxJqCYGGJ2%2Bo6bIPDeXtWFZNSAVI5HKMzI7cdj9SygNrPQlBjHWOcd44J9aATQnTnJGSDOmHNzJMC6R/Jk5X1kBpDSDcXHiQbi88wejgjPzvI6cBcCqFhmdfQthfC8zgnkVWYxa5zA2LcViAc8KpzZLwvEspR52lIyfN%2BeFQFtl2jgvcouGF/lbSou8Bi5kOLUqyVJd/XwJVaW1WZc0RYnLPSJD5YGUaorOgaeleMJamwVX/U6MdSWTgOdfxNcsF63tPq3qF6W8G0NBaCj9fQKt4bKaxtN7rR3qbO2ZudZzU0ati25uD9LW3rbAxFvbYqE285awNhtvn2ypndHODnc59jmsPOJp84e5O3Yz2f3XLex95d1GfsgDMChoX/gPHOLCUL%2BUt731r%2BiVD%2BJc7V0gEkP4Td/gfEiJEhJBEhXFkh5QuBUg2VkhaNIlOAXsT8O0mlX84D39RdVhRUshnBJAgA%3D%3D)

## Links

- [source code](../../../../conceptrodon/pagelivore/independent_cognate_right_interview.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/independent_cognate_right_interview.test.hpp)
