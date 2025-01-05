<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::CognateRotate`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-cognate-rotate">To Index</a></p>

## Description

`Pagelivore::CognateRotate` accepts an operation.
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
 :: template<auto...> class...
 -> auto...
 -> template<auto...>
```

## Structure

```C++
template<template<auto...> class>
alias CognateRotate
{
    template<auto>
    alias Page
    {
        template<auto...>
        alias Page = RESULT;
    };
};
```

## Examples

We will rotate the first three variables from `0, 1, 2, 2` and instantiate `Operation` with the result.

```C++
/**** Operation ****/
template<auto...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<2, 0, 1, 2>;

/**** Metafunction ****/
template<auto...Args>
using Metafunction = CognateRotate<Operation>
::Page<3>
::Page<Args...>;

/**** Result ****/
using Result = Metafunction<0, 1, 2, 2>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The implementation is similar to `Varybivore::Amidst`.
We want to count variables one by one up to the desired number.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the variables to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` as in the implementation of `Varybivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `CognateRotate` using concept expansion.

We will expand the constraint `Prefix<***>` alongside the arguments.

```C++
template<typename, auto>
concept Prefix = true;
```

We will encode value information into types by `Vay` to avoid defining the body of helper functions.

```C++
template<auto Variable>
struct Vay
{
    static constexpr auto value {Variable};
};
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
        template<auto...> class Operation,
        typename...BackArgs
    >
    static constexpr auto idyl
    (
        // Expand `Prefix<I>` to count the arguments from the front.
        Prefix<I> auto...front_args,
        // Collect the rest.
        BackArgs...
    )
    -> Operation
    <
        BackArgs::value...,
        decltype(front_args)::value...
    >;
};
```

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`:

```C++
template<template<auto...> class Operation>
struct CognateRotate
{
    template<size_t Amount>
    struct ProtoPage
    {
        
        template<auto...Variables>
        using Page = decltype
        (
            Swivel<std::make_index_sequence<Amount>>
            ::template idyl<Operation>(Vay<Variables>{}...)
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIACcGqQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCcmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimGmujMh4mAq3R%2BdXN6f/xx%2BlwuwLMgQiyG8WFuJkCbi8jlohAAnrDsCDzOCGJCvNDYW5kBN0FgqGiMb8jrdlMRMDRVF9DkCCJgWGkDMz8QRkc9mGxSLcmAjUGSrmhsU8CFSaXSYYF7rcCMQvJhYVYriC/ntbgA1JjIhkHJkstlMDlwwVEHWtPBMWL0EWXCZKhxW1HqgDsFluc0cyFuYommFUaWIAqFtwAbmJlTDPbriDa7Sr3fdVbHU4E1cCKQDc98NZSAJKs%2BhsQSmnIGs4FvO1oE1g63IQAdzwEfqVaNJdNKrhXJ5rF76KuTq8LpbbY7Jk904zWZBzO7ZrcWQAXpgAPoEAB0u8LDtH49b7do%2BKJIBAESwqg3SgAjsrxfjC7vt2TAsPgTOrrdfwrjeyKo/n%2B%2BIgn%2B4H/kuvZuBaqCvmi/oGAonwAPLPMQFYCKQYEQb%2B/aMIOr4WEwyAANaXMQwAKDhv4OuBPp4H6AbMsGoawbceDoMip7Ab%2BEA0RBOw7Lc2DBoY6AwgAbBo1K0ngqjPmS0kKqg/rrIICoIJgAqUT4jAEJ8VDEKgLCadpRmyG%2BvEQbJdKKR%2BYZEK%2BFmCBurRUdh1ngUJtx5A0Zm3DSExWZcuG/sRZEUVR8HWcsAkALQIWhCSYQwAmgV5f4ReRlEKBeUbeJgr6eaFYVYJC%2BHUMZrnuQoyz5dGRW7ulH6qhiKZteqOaNh4wDMMyABKqAtMynYLgBPachNy6wfBDmQkwyG3MlGGNAeipjpKvX9ZgQ0jUBX5ZuBi4msua6bpKlwsOpBB0X%2Bh6StSw2oMoTDAAd4HTkdYUCcd03QbNu7xom9DUa1mW/l4WRGFSb3abC8rlbQ%2BG/X%2B/EQxBE4nmeBDoBeLBMKRm5XkGt6YA%2BrzQVdN3vp%2BYUQReJ2ARxXGnnCK2pWiEC6qicLA7aoNkjOKavnFGNxZm6UdZLXWlXh/34oD26XMANIsvpYN03%2BUMRMAsPvbK8pPUQr3vfiKtq2WBlzeiMtfnO5LXLWgINlqomsGy2n5t1zvVrLmIQlC8NwmKWxpAZDqu8t6GpWNVxM5N5pCjbIIPdHKVrXbUdCF4aTFJg6ADR8XjI3Hlw6zDOd55kBdFwoJeSgj6erTk%2BJmPyqS3Fw/JmO%2B84%2B7cACymAtFQXjYo0ZcJzNye7lFmsghXevD6P48OJWTfbT2e2J24HOZ5%2BF6m9BgQOkfcPm7lKdZwPdcN2XS%2B3HfpdNyvTBjxPrdwp33e3O3f990dpqW4AAVD4kpvaOhGoxNyyEEgEAgOeEAChBywPxM/Ag/Iq750LsXZGaIJYWA4KsWgnB/C8D8BwLQpBUCcDcNYaw3p1ibHhmCHgpACCaGIasUiARJDbg0AADjMGYJISQuD%2BCEYIrg7p3TSFIRwSQvAWASA0KkSh1DaEcF4HlVInCqHENIHAWAMBEAgHWAQNICJyCUDQKyOgCQoiDk4KoQRkl4qSUkLcYAyA/RSG3GYXgBdCAkE4nofgggRBiHYFIGQghFAqHUAY0guhu7NgwmkTgPASFkIoVwmhnAUIIisZKVAVBbiuPcZ47xviu78LMLcCAHh7H0FDJiLgyxeD6K0KsCASA7FpAcWQCgEABlDJAMAKQ7caDIwSHlCAsR8mxAiK0ZEWTeDLOYMQZEKFYjaEwA4dZpA7FWxQgwWgazklYFiF4YAMFaC0DytwXgWACZGHEFcvANJ17tiedQoMByETbHYREZkCjqFIliBhbZHgsD5MVHgFRzzSDtmILEGujw3nACREYLhqwqAGCotqd4zZkqUPYRE4QohxCxMpQktQ%2BTUn6EMMYBhlh9B4FiHlSAqxUDhxyE8%2BKRIEamEsNYMwmjUUJiwNyiAqw7AHMaC4Bg7hPCdD0GECIwwqijG7sUbIAhph%2BD1ZkA1DAFgjESN3BV68BD9CmGqgo1r6iKr6JMQYWrFi6tsO6o1eg5htAtTqq18rmFbAkDkjg5DSAaN4FoipbiPFeJ8X4%2BpjTcAhLaWwzpHC8WrC0kwLAiQ5WkF4ZIQI24kiBDkRoSQZhJDSQ0P4SSSR9CcCUaQFRgQuDbkklwSSgikjSMkv4SQEiq2SRjfkrROiQB6LxUY0xfTzHFOsSMsZrSnFsE4K0FgEZ3TxSYIhFlXckjbh7f8/ARBpXhNkFEml0g6VKAZck3Q7d0lMEyc8yN0bY0FI4EUyxCJbhlITVUrxC0YZcDPRexpzTBmtJhGCMwObumGOXRuhINjRkmQQ6MSDkzxGpBmcyYg8zFnJM2aso5VHtm7P2Yc5FJz9JnIufk65tz7mPKOa8llHzqH4G%2BY4X5%2BSAXICBUc0F9R8mQuhciWF2xqEIqRew1F6KlCYr47rBdBK3oKGJZgUlPIjmUvvTEx9sh6VJOoW%2B5luLRVWHZZC2VvL%2BUCEFcKuUDnxWSoSNKj48B5UuttX4CArg/Xd01RUS1eh9WNAi%2BkU1jQg1LGdb0O1vrHXGp6K6jL8xPUxetZl/I2WA0eui8GiNawNjho6W2qNeTknxsqUm49UGYMCPTVekgSHu2obzaQAtRbKCRo7V2s9tb3T%2BCSLIwIdaG1jqnU1zgs750GN6UupAFiSnYcw8QLd2xd3VJYAoCMfoIzQe3IBCYQTus3u7qZ6l5m4nyGfdZnQIBggfq/dk%2Brv7p2FNXaU8pqhjunfO5d67komm4aGb1wI/X1tGP6bD1pu3UejDO3nDcF2kgbihxuUHj66CkfI0slZ2yaMU52XsxVRzmOCFY5cgTmAbl3LENx5FvH3mKZeV811InkliYk8iqT4LeCydWQp%2BFCYVO8DUxilkWncVI900SklZKTN3qexICz8S3uMs%2B3Z1lYqnOcpczQtzDAnk7HPN5ywEq41Ss4gFnlOWQvKtVSVjVKqUverizkBLAeygFcq2l3LTRivqvDyF%2B15XtWpZ9QMBLZW/chuqywqrCj/vLY4BUsHZ3IyQ57BMLrmbesdK6QNobowS0KLGyAUR25AiBH8JIsdaiW/ugHUtzRK3bBztzetnhIBJD%2BErTI90ajBGSHEVwYRZhJ0KMCI1vv2ih89MjYE3vcb%2B9oeWKsVFWRnCSCAA%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/cognate_rotate/implementation.hpp)
- [Source code](../../../../conceptrodon/pagelivore/cognate_rotate.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/cognate_rotate.test.hpp)
