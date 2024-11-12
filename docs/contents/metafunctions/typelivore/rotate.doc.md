<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Rotate`

## Description

`Typelivore::Rotate` accepts a list of elements.
Its first layer accepts an amount and returns a function.
When invoked by an operation, the function relocates elements of the given amount from the front to the end of the previously provided list and instantiates the operation with the result.

<pre><code>   Element<sub>0</sub>, Element<sub>1</sub>, ..., Element<sub>I-1</sub>, Element<sub>I</sub>, ..., Element<sub>n</sub>
-> I
-> Operation
-> Operation&lt;
       Element<sub>I</sub>, Element<sub>I+1</sub>, ..., Element<sub>n</sub>,
       Element<sub>0</sub>, Element<sub>1</sub>, ..., Element<sub>I-1</sub>
   &gt;</code></pre>

## Type Signature

```Haskell
Rotate ::   typename...
         -> auto...
         -> template<template<typename...> class...>
```

## Structure

```C++
template<typename...>
alias Rotate
{
    template<auto>
    alias Page
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
};
```

## Examples

We will rotate the first three elements from `int, int*, int**, int**` and instantiate `Operation` with the result.

```C++
template<typename...>
struct Operation;

using SupposedResult = Operation<int**, int, int*, int**>;

using Result = Rotate<int, int*, int**, int**>
::Page<3>
::Road<Operation>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The implementation is similar to `Typelivore::Amidst`.
We want to count elements one by one up to the desired number.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the elements to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` like when we implement `Typelivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `Rotate` using concept expansion.

```C++
template<typename, auto>
concept Prefix = true;

template<typename>
struct Swivel {};

template<size_t...J>
struct Swivel<std::index_sequence<J...>>
{
    template<
        template<typename...> class Operation,
        Prefix<J>...FrontTargets,
        typename...BackTargets
    >
    static constexpr auto idyl()
    // Note the position change of `FrontTargets...` and `BackTargets.`
    -> Operation<BackTargets..., FrontTargets...>;
};
```

`Prefix<I>...Targets` tells compilers that this function template is only allowed when `FrontTargets` satisfies `Prefix<FrontTargets, I>...`
In our case, since `Prefix` always evaluates to `true`, it constrains nothing.

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`:

```C++
template<typename...Elements>
struct Rotate
{
    template<size_t Amount>
    struct ProtoPage
    {
        template<template<typename...> class...Agreements>
        using Road = decltype
        (
            Swivel<std::make_index_sequence<Amount>>
            ::template idyl<Agreements..., Elements...>()
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEAQBspAAOqAqETgwe3r566ZmOAuGRMSzxiZIA7LaY9sUMQgRMxAS5Pn5BdQ3Zza0EpdFxCcm2LW0d%2BVzjA0PllSA1AJS2qF7EyOwc5oERyN5YANQmgW5ejrSEAJ6n2CYaAIK7%2B4eYJ2fICgToWFR3D2eTwImBYqQMINObgI11SjFYmFIRyYF1QAKeaAYW1SBCOymImBoqg%2BABEjgRiF5MKcrE9ASCwRDqWcYXDmGx0Y9vpSHEchAB3PAAN3qJ2qVmqJJpgPpoPBTEhZ0yAC9MAB9AgAOm1AClOdyvLyBcL6lDvugQCAIlhVGqlABHKlY5luHXazUAwL3OniwFHf3kuVMqF%2BgNhhnyxXQ2Hwtjuu5HA5MBQKI4AeThxAV2VIobD/vxhLwqiheq97oAYsRZAAVVrATAEBS5p75gOs2OYd0WJjIADWdeIDabeY%2B3seYe%2B2eQiYE30wqlSxGRqKOeHQ11oEGWo4A9LujlFUCDyQh3oUsgJEwhDA2jqgqCckhoq7X642FPHn8iGOgnxoe37Qdh0/Exn1HABaBMMwSbMBChQCB3fJt3SRV9BGAj94y9aUfSlQJaSBR4I2DFkY3ZLttWweg2EEBR9QpQ1cQAJWPBVqR9QjwyDdizTwVUNSOR4WHWQROUnRjeXxY9UGUJgG1HExfVbNtA0ZXiWR4qMOwo7DsETAwU3dR5gAJUFGBHHCVLbLxMiMI5WKYP9TjJLADg7UcwwgTzVONEVaDNH5LRYJg%2B3Va0FztTBHUYLYoWE0SCE9cdVPzS0SPYtcNwCs4TLM2iUO1JFqPMui9O3Hz/R3AjFMlXCiO49SoxRIhjNMzBSsslKA1siJgDxeT3hcvFqyIOSFNy9rOs/bVPUIpT8Pmp5dwAKjW9aNt3QFVrWmtsCEGt1q25aNtOlbjqIl4sTeD5zkuG5OVlJqXR0hE9MBA1eRgrNGnqwFevsoQvFSQpMHQZjMAULxaFxYbvrghgoQiAg1qRZG0cEFaMZRla5plJ4Af6iGoZh0kHLYqN0bXTHsdR6mcc5S1xpdQJGZARz0CheHfpwmq6SeKdHGQNVkyUNoIHNS0FAREX6LOYnoYIJEgZBjIwYVmG7mqiwOFWWhOH8Xg/A4LRSFQTg3GsawjgUdZNiGsxAh4UgCE0XXVj7AIzE1aozEkAAOf3/A0ABOfwzA0JJ/eCfWOEkXgWAkDQNFIY3TfNjheAUEAU9dk3ddIOBYBgRAQHWAhUguchKDQME6ASKIEU4VR/aSCCkkkI5gGQGcpE1MxeDBwgSHXPR%2BEEEQxHYKQZEERQVHUfPSF0GZ%2BSzVJOB4PWDaNt2zc4NMLkr3EHyOFu247rue6OPuzCOCAPDr%2Bhl12Lhll4POtFWCAkFr1J67IBQCAf8AEgGAFIMwfA6AgmINnCAsQ96xAiK0a4m9eBIOYMQa4aZYjaEwA4NBpBa4FTTAwWgqCl5YFiF4YAbgxC0GztwXgWAQpGHEJQvABIHAmkYabBc%2BCLjbGdsjeoe8rixCzFgjwWA94UjwInJhpARTEFiGrEkoJbxXCMG7VYVADDAAUAANTwJgfkMFjbO3HsIUQ4gZ5WPnmoPeK99C3hQFbSw%2Bg8CxGzpAVYqAcTZEYRBc0LlTCWGsBHXgqBlHEHXJDeAqw7D4MaC4X8Uw/AzDCBEYYFRRgzAvI0dJBQMiXgYPMEYiQZhJO4QIfokxPCdD0NUxodTBjZIWHk2Y9S8gZK6W0soFSJCJLtlsIZ%2Bgd6pz3hnM%2Brd26d27r3SQ/d764GHi/R2b8P46NWGeJyoxtykE9pIQImoQ6BGqJIDQkg/bPg0P4JIIdxlxwTiAJ2mokhcCjiHf2nz/CSC4P4M5KQ05RM4FnHOLsdGFxLj/MuR8q5AJAc/RubBOCtBYEKaoEEmAGVvDfEOmouCaj4fgIgsSLQzCsZPWx0h7FKEcUvXQkC15MA3kw7eHBDaTKXhnQ%2BFcLj3kfOizF2LcX2S4ASolGh76P3/s/E4jszDv0hfnb%2Bv9UBPwSNXYBGq5WjGFVipMRgJVcBTjQGGCQ4EIKXhglBhDbVYJwXgghijiEWVIeQveVCaF0NoAwwhLDNHbFNvgLhjgRS8MHqoARIJCEiNjqbcRkjrjSODR/WJCjnbKNUUodRrDgBaNAKqvg%2BijEmLMWyQhVKbHT1pbIBxi9TZMpcdosJVgPHiJ8Qc/xjQgkhMCCSNtET04xLiV2xJ9RknZFSe4Bp0wQi/nKbkypaQSmFLnb0gp2Ql2LCqZOmpTQJjtA3U0/dLSj07s6VObpjSqkXvaYMt%2BawNijKfbHLlIL94cGRMQDFWKcVGv6hKwlxKVmkpIAqp2yrP7u1ILsrAiQDmx3jqQROgQCVXOqIC6o1RAjXMkB3GYn6M7gtzlCoupdy7H21UihuTcODosviwBQQoZxCmA0yb4g9wPkrHrIaltbZ7yHpY2nQrzSAsrZVvJ5H6pkH3hSfIVv6mMsbYxx9i3wZW6oAZBwI0HyPqs1YAmu2nn4gFYyDNU7GQ5qk4wQEWynaXQMtZQa1psHUUOdh5p1yTCFusEB6ihIbMDUNofQxhztA1sLTaQUNU6I1734cgQRcbBCiKXkmlBqbZEZsIdmtRGi2F9ShXo%2BSZbTHmKrfxmtEg61zxE048TBhW3uJsJ2hJZsAlzk4LuSWQ7LCRLNqOrA46ehTucBAVwRTMmLofcu4pRRsjTdXYtkoc3d1jYPa05bzS%2Bj3oGfNu9Awdv7Zybu4ZL7p4ctkzyzgP6WAqdY0cazmo7NgbWZBzZKqv47MwHsxDHKUOJzMASwIgR/DB3%2BcnMH1Qo7cvTmC2wEKYPLA9ksao/csNcCkCHTDZyuC1FjoEXet3M7fdg7HAe8PQVk5R6sZRmRnCSCAA)

## Links

- [source code](../../../../conceptrodon/descend/typelivore/rotate.hpp)
- [unit test](../../../../tests/unit/typelivore/rotate.test.hpp)
