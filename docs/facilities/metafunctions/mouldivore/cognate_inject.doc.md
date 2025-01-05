<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::CognateInject`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-cognate-inject">To Index</a></p>

## Description

`Mouldivore::CognateInject` accepts an operation.
Its first layer accepts an index, which indicates a location in a list.
Its second layer accepts a list of new elements and returns a function.
When invoked, the function injects new elements into the location of its argument list and instantiates the operation with the result.

<pre><code>   Oper
-> I
-> Es...
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>, Arg<sub>I</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>, Es..., Arg<sub>I</sub>, ..., Arg<sub>n</sub>&gt;</code></pre>

## Type Signature

```Haskell
CognateInject
 :: template<typename...> class...
 -> auto...
 -> typename...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
alias CognateInject
{
    template<auto>
    alias Page
    {
        template<typename...>
        alias Mold
        { 
            template<typename...>
            alias Mold = RESULT;
        };
    };
}；
```

## Examples

We will inject `double, double*` into index `1` of `int, int*, int**, int**`. Then, we will instantiate `Operation` with the resulting list.

```C++
/**** Operation ****/
template<typename...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<int, double, double*, int*, int**>;

/**** Result ****/
using Result = CognateInject<Operation>
::Page<1>
::Mold<double, double*>
::Mold<int, int*, int**>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The implementation is similar to `Typelivore::Amidst`.
We want to count elements one by one up to the desired number.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the elements to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` as in the implementation of `Typelivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `CognateInject` using concept expansion.

We will expand the constraint `Prefix<***>` alongside the arguments.

```C++
template<typename, auto>
concept Prefix = true;
```

`Enrich` will help us translate `std::index_sequence` into a pack of indices.

```C++
template<typename>
struct Enrich {};

template<size_t...I>
struct Enrich<std::index_sequence<I...>>
{
    template<typename...NewElements>
    struct ProtoMold
    { 
        template
        <
            template<typename...> class Operation,
            typename...BackTargets
        >
        static consteval auto idyl
        (
            // Expand `Prefix<I>` to count the arguments from the front.
            Prefix<I> auto...front_targets,
            // Collect the rest.
            BackTargets...
        )
        -> Operation
        <
            typename decltype(front_targets)::type...,
            NewElements...,
            typename BackTargets::type...
        >;
    };

    template<typename...NewElements>
    using Mold = ProtoMold<NewElements...>;
};
```

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`.

Note that we wrap the elements inside `std::type_identity`. This ensures we can create objects to invoke the ordinary function.

```C++
template<template<typename...> class Operation>
struct CognateInject
{
    template<size_t Index>
    struct ProtoPage
    {
        struct Slash
        {
            template<typename...NewElements>
            struct ProtoMold
            {
                template<typename...Elements>
                using Mold = decltype
                (
                    Enrich<std::make_index_sequence<Index>>
                    ::template ProtoMold<NewElements...>
                    ::template idyl<Operation>(std::type_identity<Elements>{}...)
                );
            };
        };

        template<typename...Agreements>
        using Mold = Slash::template ProtoMold<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEEhoapAAOqAqETgwe3r4BwemZjgLhkTEs8YlcybaY9iUMQgRMxAS5Pn5BdQ3Zza0EZdFxCUkpCi1tHfndEwNDFVVjAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimKmujMh4mAq3R%2BdXN6f/xx%2BlwuwLMgQiyG8WFuJkCbi8jlohAAnrDsCDzOCGJCvNDYW5kBN0FgqGiMb8jrdlMRMDRVF9DkCCJgWKkDMz8QRkc9mGxSLcmAjUGSrmhsU8CFSaXSYYF7rcCMQvJhYVYriC/gCtQcgZrbgBJVn0NiCJiNBk6jXa61ncnXSnYBjEPDIBAW21XZlGs0quFcnmsX3oq4TJUOW6O52umEAdisMfuqrtXrZPvxmQAXpgAPoEAB0Bf1Isuoa84cjLoQ6YI6BAIAiWFU2aUAEdleL8fqC3myYFg8C4yDbsOFSzUxy/dzGIHu1FMAB3bDGxgEBTFke3Uvh6moIgAWU86CHI5McZhVw3G5T7JVF8vw/xx/vV7HN85U95mG7aNukKYCk%2BAB5Z5iDNbJSCfZ9h39ac2G7CwmGQABrAAVVpgEwVdII3ddnzmRxkF/AQJkwAA3MQBSFW48HQZFaGwkcIAY%2B8dh2CNVFSQx0BhAA2DRqVpPBVE7Mk%2BIVVAiK8QQFQQTABWIYAfBXT4qGIVAWBkuTVNkHs7yg4cBLpES%2B0oohu20wRc3QzCFAgvT9NY25cgaTTbhpCZdMufSRwQ5C0IUmzv3sjdlmY24AFof2AhIwIEMLH2C58YM/W4sEhGDqDUyzJgw1dljrGDuzsrzvNuOdF2XQQFCKsKrw/QNbl81DrNXAqpyCkr717NVOtjRNAh6yDrzTScAzggtyqXFllNw4cvEyIxbgPWhuNheUd33Q98UmyrV2/Psk3VBNDuBCk7g8YBmGZfUGG0TBw2%2BEFhonNxnt9V76vGnsTL/ADbmi0DGmLLdJQuq7MBuu6HAxQd7Le9M8CzXMDQYRtZs3RUy0lDbUGUJgMMg08eqgkHbiEAwFCrRKH1h3qoPh0bYK/CaFymk0sIO6nL1JnHlqPLmcNp0rLwZj6xuZvM2Zmzm6dK%2BaImAJbD1leU0toGDaufJiBdKitXWrWsQBYJgkJzBtMCbVt2y2TtUYt3t%2B2FqCCtfH0pV3VA%2Be21nduqgt0adkcXe9ZlqNo%2Bi4QB2KGDRCAiTa55sxolcUXxKWqrJQcE27UKdfvUKBs1mn%2BuJ59TxLu16ddl7kpnAtLmAGlpozmWoPlxa%2BZVsmKaQEA3vdzaVvxBum/Zv3vvRQv7PLk6hur97BTM%2BvG8wZuOcdkd28VvGMK7nGd/ekfV7H/bJ8G46p9O%2B0bUZK07mwVRWDZOTHrOm%2BPSvzEIShOT8TFLZUjrztHqKO5pX6XFFrXL6wNMbhlAdkWeb89hky8KkIomB0AACUPheHVu6IEW8UFoIyBg7BChcGSjWv9EC0d8QRAIPydA6xYj0EYcw%2Bgex%2BT0M4dRQQBxurAMpGQih%2BCQSEOEXgqhYMfSQ3ugQfE8C4oyzrAffEXBix1i9nCJhXgWGYDYbojhGiQBaLcPQrhfCLEEH4QdS%2Bd8Di3BQh8SU4D8IumzP%2BJQbQ441jrAoQMHi1xwgkQwoh6CsE4PVmiAuFgOCrFoJwfwvA/AcC0KQVAnA3DWGsJudYmxf5gh4KQAgmg4mrCQgESQeYNAAA4zBmAAJwNK4P4WpNSuAxhjNIBJHBJC8BYGMUgKS0kZI4LwBQIAUglNSXE0gcBYAwEQCAdYBBUgInIJQNArI6AJCiIGTgqgak8XCjxSQtxgDIEIlIPMZheAYMICQGieh%2BCCBEGIdgUgZCCEUCodQMzSC6C4KQecoFUicB4PExJyTSnpM4IBBEazJSoCoLcQ5xzTnnMubca5ZhbgQA8Ns%2BgxAYSFOWLwaZWhVgQCQFs1IOyyAUAgLS%2BlIBgBSDMHwOgzJiATIgLEGFsQIitGROC3ggrmDEGRIBWIUNplFK2ezQCDBaAiv%2BVgWIXhgBuDELQCZ3BeBYGNkYcQaq8A0gcHgUiHwYUW3ugibYRT6H1BhUiWIoFJUeCwDCxUeABn6tIFa4gsQSGPCNcAJERhSmrCoAYYACgABq7x5zRRSUUl5whRDiE%2Bemn5agYWAv0IYYw2TLD6DwLECZkBVioEAdkPV4UiRrVMJYawZgRmBudFgStEBVh2DkdkFwqNph%2BCBWECIwxKijCBUULIAhh16BnY0BYIxqg9H7QIfoUxPCdD0H2i1G7JiDHHYsKdthD3zqBXMNoy7J3VF7XkrYEhIUcCSUMmFozUVHJOWci5Vyqm4ogLgB5xLMRcDJcUqNqxZJMCwIkHtpAKmSECHmBpgQukaEkGYSQfEND%2BB4g0/QnA%2BmkAGYELgeYeJcB4jUhp7SeL%2BEkC01DPE33/NGeMyZEGZlUsWdS5ZCL1mMuZUSvZbBOCtBYKRGM4UmC/gMItLgDS8zkbSfcognbnmyDeVm6QOalB5v%2BboDlIKmBgv1c%2B19wzeCjPhashEtxkWfvRWcv8CmlMqbxQSulRKSWBDMOBilsy%2BPCYSBspl6lvOjFc2y5pKQaDqwSLy/l/zxXCtFaQVLkrpWyvSwqlcSqVUwvVZq7VtBdXpcNUWk1aT8DmscFavVqnVB2uZOlp1PS0muvdciT12w0k%2Br9UUwNwalChqqwrKNfBY0JqTSm9L6btMfN07IXNfy0lGcLZG5tVhS2uu7dW2txFOANprE2ktFg23WY7cnfba791%2BAgK4C9IRUY3qWNOjIs6cjbvyB94o2Q3unr3Y0Td7QfsjruyDw9gPV1XrB3kCHcOYdPrWBsR9YHCMvuhWxzgTnv1yaLdi9z1S8VAfU75sD5LIOkGg7Bygz7iOkaUxhmM/gGmdMCJh7DjHWMjM4BxqZk35lLJWYisLIXiCie2BJjFLAFCkUIqRRTeYbwTDufgdTTygULczUtr58h9NrZ0CAYIJmzMQsx5Z99cKBNIpRaoWX8vFfK9V5KfFEX6W%2BcCAFoXNKPdEvF/70YCu0HZiVw07MrvswO901yxLlBktpMy6qopyfstyNy%2BpRVyrVU1cwBqrVOq9VFMq8avrBqzX9oaza5ryB7VtcEM6/5XXhW9e9c6QbvBhshpZONyN3Gpv4xmwuOb/qdfvIkMt75hv80m828Wltu3y23ZrY0PVOx47bdbe2hInbrVVshwOx7Q7wd6DHeUFdC7PuNGe4ugHx7L%2BXvqOupo57T9P96Ae%2BYD/b27rfwjv/b/C/X/DHBQB9D5CzbHPnDgVFR3BXW4cPFXH0CYUnDXEgCnH3bjKDTAGDUYeDHpRnEARpPMQIQIfwVpRjZIUgmMajXnazfnWwTjQLZYcpEASQfwFDDpGMZIGpSQZpLgOpMwFjHpQIKA%2BgsZLjSlZ9W5Og2FCQ5g1YQNTIZwSQIAA%3D%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/cognate_inject/implementation.hpp)
- [Source code](../../../../conceptrodon/mouldivore/cognate_inject.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/cognate_inject.test.hpp)
