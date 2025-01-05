<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::CognateRotate`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-cognate-rotate">To Index</a></p>

## Description

`Mouldivore::CognateRotate` accepts an operation.
Its first layer accepts an amount and returns a function.
When invoked, the function relocates arguments of the given amount from the front to the end of its argument list and instantiates the operation with the result.

<pre><code>   Oper
-> I
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>, Arg<sub>I</sub>, ..., Arg<sub>n</sub>
-> Oper
   &lt;
       Arg<sub>I</sub>, Arg<sub>I+1</sub>, ..., Arg<sub>n</sub>,
       Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>
   &gt;</code></pre>

## Type Signature

```Haskell
CognateRotate
 :: template<typename...> class...
 -> auto...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
alias CognateRotate
{
    template<auto>
    alias Page
    {
        template<typename...>
        alias Mold = RESULT;
    };
};
```

## Examples

We will rotate the first three elements from `int, int*, int**, int**` and instantiate `Operation` with the result.

```C++
/**** Operation ****/
template<typename...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<int**, int, int*, int**>;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = CognateRotate<Operation>
::Page<3>
::Mold<Args...>;

/**** Result ****/
using Result = Metafunction<int, int*, int**, int**>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The implementation is similar to `Typelivore::Amidst`.
We want to count elements one by one up to the desired number.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the elements to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` as in the implementation of `Typelivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `CognateRotate` using concept expansion.

We will expand the constraint `Prefix<***>` alongside the arguments.

```C++
template<typename, auto>
concept Prefix = true;
```

`Swivel` will help us translate `std::index_sequence` into a pack of indices.

```C++
template<typename>
struct Swivel {};

template<size_t...I>
struct Swivel<std::index_sequence<I...>>
{
    template
    <
        template<typename...> class Operation,
        typename...BackTargets
    >
    static constexpr auto idyl
    (
        // Expand `Prefix<I>` to count the arguments from the front.
        Prefix<I> auto...front_targets,
        // Collect the rest.
        BackTargets...
    )
    -> Operation
    <
        typename BackTargets::type...,
        typename decltype(front_targets)::type...
    >;
};
```

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`.

Note that we wrap the elements inside `std::type_identity`.
This ensures we can create objects to invoke the ordinary function.

```C++
template<template<typename...> class Operation>
struct CognateRotate
{
    template<size_t Amount>
    struct ProtoPage
    {
        template<typename...Elements>
        using Mold = decltype
        (
            Swivel<std::make_index_sequence<Amount>>
            ::template idyl<Operation>(std::type_identity<Elements>{}...)
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIAAc0gAOqAqETgwe3r4BwemZjgLhkTEs8Ykptpj2JQxCBEzEBLk%2BfkG19dlNLQRl0XEJydIKza3t%2BV3j/YMVVaMAlLaoXsTI7BwA9ABU%2BweHR8e72yYaAIJ7BwDUACKYqa6MyHiYCjeHZ5fXJ39H3wu5yBZkCEWQ3iwNxMgTcXkctEIAE8YdhgeYwQwIV4oTC3MhxugsFRUeifocbspiJgaKpPgdAQRMCxUgYmXiCEinsw2KQbkx4ahSZc0FjHgRKdTadDAncbgRiF5MDCrJdgb9/pr9oCNTcAJIs%2BhsQRMBr07XqrVW05kq4UoQAdzwADc6uabZcmYbTcrYZzuaxfWjLuNFQ4bo6XW6TAB2Kwxu4q21e1k%2BvGZABemAA%2BgQAHQFvXCi6hrzhyOu2jpgjoEAgCJYVTZpQARyVYrxeoLedJgWDQLjwJuw/lzNT7MuI5lbiHU5HKbZvrc/sYge7qJuEKYCg%2BAHknsRTdlSLO5/Kuau2N2LExkABrAAqLWAmAIClPMv7U9mjmQm4E4yYKoqTEPygo3Hg6BIlWk4jhAH5Tts2w3NgwGGOg0IAGwaFSNJ4Konakth8qoP%2BXiCPKCCYPyxDAD4jBvjcVDEKgLCUdRzGyD2sFnrhtKEX2YFEN2nGCLmz6vgoJ48XOSE3Lk9TsTc1LjNxFxnsON73k%2BtGSeuMlLB%2BAC0G77gkR4CB%2BeIIfOF48tRWmPhJb51iu3bSepGkrvZNxYBCK7UCxYkTC%2Bb5LK5F76Z5w69qqA6JoEcWWrcHjAMwTIAEqoM0TLuoyY6LhyBVpn6dlrgWG5bjuNxmYeDTFqW4apelmBZTlypqoOMkLiVbiZjmEoXCwayCMW34KmWEpUtlqDKEwL5WV10Vzj17KlQGV4FtgRoMe%2BfY2cOXiZEYNwALKeBhMJyn5tArgdNzwTJGkRk6lbVrWIAsEwd45g2QHNpgbYvEuQ0jQQvZfs9I6ucVuWQdBeK1RZDCohAhIRU82aQQxyJ4ttzK7aSg4Jt2hlPSOhmJYtCVJd1sNLgKwkFhcwDUgTgh7ZDh3HcAlLzdRV2SjNc0LbCLNs8ab7rvtVOdTTtoataOoUqhrCstRXzJdaFpqmqoLgpCAuwqKmypG%2BxZa7sNUHsjeXAqtS7eeVPb7SGE3hkj9Wy0C5K3EIXipEUmDoBl7xeLdduXEdES8/7gcZMHocKOHEqC572R4hEBD7HyWe54Iuz59nuyxQrFKna%2BTBUORDjZJHFwOxyZWbXmFy0ZzwLRydFfNNXWJmoLzU%2Bm1vXp5ZrsXHWItLoExZ1udtDoHibfAAo0tot7ls3EnKf113vM7xHgs91XNde24ecQQXRc51fxel7rdq3A%2B7wSprbtHsg2bbkorRozWdYFCBm/ntNwh8CB8jjkHEOYdbqokphYDgKxaCcH8LwPwHAtCkFQJwGclhrA3AUGsDYAtQQ8FIAQTQSCVh3gCJIPMGgkhmDMAAThYVwfwjCkhcBjDGaQKCOCSF4CwCQGgNCkAwVgnBHBeAKBAOIyhmCkGkDgLAGAiAQBrAIKkeE5BKBoBZHQBIURAycFUEkTCRlMKSBuMAZAf4pB5jMLwYOhASCQT0PwQQIgxDsCkDIQQigVDqCUaQXQXBSAOkPKkTgPBkGoPQVQ7BnBdzwh0RKVAVAbjmMsdY2x9ibiOLMA9Dwhj6CgQxFwJYvBFFaBWBAJABjUhGLIBQCATSWkgGAFIMwfA6BMmIHIiAsQkmxAiC0JEsTeBjOYMQJEu5YjaEwA4KZpADGS13AwWgkzQlYFiF4YAbgxC0DkdwXgWAvpGHELsvA1Ja6ulOVgoCyz4RbHIVnOoSTESxEPHMjwWAkkKjwCIs5pBXTEFiAnB4lzgCIiMFQlYVADCrwAGpvAdGZDB5CvHCFEOIfxOKglqCSeE/QhhjDWGsPoPAsQ5GQBWKgM22RTlGUJFdUw%2BDLBmCkeC4g2M6UQBWHYZZDQXAMHcJ4DoegwgRCGJUEYESihZAEFMPwiqMjKoYPMYYiQInCtrgIPokxJX5D1XUEVvQJgDFlQsBVtgrWqr0LMVo2r5W6qFcQzYEh4kcDQRIpJ0jskWKsTYuxDj6HFIgLgNxFSyHVIoQilYVEmBYESIK0gtDJCBDzCwwIfCNCSDMJIbCGh/CYRYfoTgQjSAiMCFwPMmEuCYSSCw7hmF/CSA4bmzC/rQnSNkfIhNSj6nqIaZotJui2kdPKSYtgnAWgsGdDGIyTBNwGBOlwFheZ61PPwEQPltYIk4p8fi6QhKlDEtCboXpUSmAxLOT6v1kjeDSNSdo%2BENxMlBtyTYrcG6t07pKaxZp5ToSgjMPG2pyix3ToSHo9pwHOl/u6ew8RNBboJCGSM0JMyJmrNw3MhZSyVmgvWQxTZ2ykl7IOUc2gJzVkXPJdcrB%2BA7mOAeUk55yBXmrI%2BQIrB3zflIn%2BVsLBQKQXkPBZCpQ0KmMxwRXwZFCg0WYAxdyVZx68V%2BLPbIIlISsHXrJfCjlVhLDUtpfABlTKAKcFZTWdllKuU8oSAe94lnugWucBAVwjqIkyvKDqvQSqGi%2BdIMF7IrrFhmp6Iah1Jq1UeYNY0K1kW7XOraPFp1KWbWBaqasdYXq8sCKfQGzg36Q1rvJYUgDDCHrRv3WButkHE2kGTamygPrq21q3QWmM/gWG8MCIW4tnbe1SM4AOhRCnVEaK0ek%2BDsHiCzq2AuvJLAFDOj/M6TdeZFzjBcXu9xh6Am4t8RIHTgSL36Z0CAYIt771xMrb6xJfaUkToyVk1Qa2NtbZ23tiUEBSkgYSI1wIzXh0qMaYh8pC3ocjE24HbM22WHZn%2B9mL7Z7%2BmYcoNhrBBGdnkPx0RkVqyyOCAozsljmB9mHOOac8hjGrmifObci1HHQlcZ46CvjXyaVCZE4CvlEneBSahcyOT8KIdIvmsp9FmKNOyBPdpk7emSW3aMxSzlNhvkCqsw0U52x0YmesNyl9vL%2BXuf1aK7z4rQv%2BblVFsLGqQuZfVcUCLOW3VOvNUlo1GW8gJat5auYnvHfpdC%2Bl1L7r8skO9U9krr2ODZO%2B5tm4yPds%2BnGHVw7sams1Ja21kY6aBFdZAKwvMgRAj%2BE4Z2sRleYzNrGy%2BibthB1QaWDQkAkh/A5p4TGMRKR2FcCYWYHtAjAgvfGzIoddSfXOKb8k6f7eVjgsyM4SQQA%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/cognate_rotate/implementation.hpp)
- [Source code](../../../../conceptrodon/mouldivore/cognate_rotate.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/cognate_rotate.test.hpp)
