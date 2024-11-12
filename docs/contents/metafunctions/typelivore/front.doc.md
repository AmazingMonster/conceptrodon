<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Front`

## Description

`Typelivore::Front` accepts a list of elements.
Its first layer accepts an amount and returns a function.
When invoked by an operation, the function collects elements of the amount from the front of the list and instantiates the operation with the collection.

<pre><code>   Element<sub>0</sub>, Element<sub>1</sub>, ..., Element<sub>I</sub>, ..., Element<sub>n</sub>
-> I
-> Operation
-> Operation&lt;Element<sub>0</sub>, Element<sub>1</sub>, ..., Element<sub>I</sub>&gt;</code></pre>

## Type Signature

```Haskell
Front ::   typename...
        -> auto...
        -> template<template<typename...> class...>
```

## Structure

```C++
template<typename...>
alias Front
{
    template<auto>
    alias Page
    {
        template<template<typename...> class>
        alias Road = RESULT;
    };
}；
```

## Examples

We will invoke the `Operation` with the first three elements from `int, int*, int**, int**`.

```C++
template<typename...>
struct Operation;

using SupposedResult = Operation<int, int*, int**>;

using Result = Front<int, int*, int**, int**>::Page<3>::Road<Operation>;

static_assert(std::same_as<SupposedResult, Result>);
```

## Implementation

The implementation is similar to `Typelivore::Amidst`.
We want to count elements one by one up to the desired number.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the elements to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` like when we implement `Typelivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `Front` using concept expansion.

```C++
template<typename, auto>
concept Prefix = true;

template<typename>
struct Fore {};

template<size_t...I>
struct Fore<std::index_sequence<I...>>
{
    // We use `Prefix<I>...` to enumerate `Targets`.
    template<template<typename...> class Operation, Prefix<I>...Targets, typename...>
    static consteval auto idyl() -> Operation<Targets...>;
};
```

`Prefix<I>...Targets` tells compilers that this function template is only allowed when `Targets` satisfies `Prefix<Targets, I>...`
In our case, since `Prefix` always evaluates to `true`, it constrains nothing.

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`:

```C++
template<typename...Elements>
struct Front
{
    template<size_t Amount>
    struct ProtoPage
    {
        template<template<typename...> class...Agreements>
        using Road = decltype
        (
            Fore<std::make_index_sequence<Amount>>
            ::template idyl<Agreements..., Elements...>()
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIJIAnKQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCUmpCi1tHQXdEwNDldVjAJS2qF7EyOwc5oERyN5YANQmgW5ejrSEAJ6n2CYaAIK7%2B4eYJ2fIE%2BhYVHcPzzMewYBy8x1ObgI1zSmAA%2BgRiExCAp/k8AQRMCw0gYMRCoTDmGxSEcmBdUKjHmgQZg0gQjspiJgaKoPgARI4IryYU5WNFPDFYnHcs74xisYX3J4TYheBxHABiJHeJgA7FYVayeQD0ZjsUxcWcsgAvOEEAB0FoAkhTpbK6YrGRDviAQBEsKpYUoAI5c6kQy0Ws3/QKS55qgFHSMc3VCvEx/XCyHQsVsQN3I4HJgKBRHADyMMRjWJDKZeFU/rugYAKq1gJgCApiaLCZg0yGI1G5o5kBmBBNMAA3MQkslHPDoa60CDLI4AWnT%2BYS%2BpyEJrxDrDbb90CvLDmp32v58YNSYJ4sD2HobEEKPbUs5cvlxFk2vDTyj0cFCadeBN8KOjwsOsggUh%2BtpygyqBEMoTB1h2kaqruH4fgKeonqhsYismLZbhmBjZoGjzAIymKMA2oHIZGXhZEYRwAEqoEw6BskcWAHKK8HIRAnGUZGDqJs6IAsEwADWcJupgHrer6WwQoBwEEMGoa8chLoYQmY4TrQcnEZgpE3oGxKXvpm4Wnc048VGyxau%2BUaqvuu6cepJ6kkQhG6SZt7KVG1ERMA9KwcqgTspB0GBTpJHXqZQbtgeaIajZzxPAA9AAVOlGWZclAJpelVbYEIVYZdlKWZWVqUlUlgLAqC4KfAIWy0l5h6PM5ibNueZl3o84F0ouhYrnFVW%2BbRQheGkxSYOgdGYAoXi0HSpzsv1y4CBCEQEMSG2pVtgjpcGjlPCN/kzXNC0sU%2BL5nBtu0EDtY57fd22pXcLowXBZyBK9IAMUxEIrY0B0tV2eDILCWZKG0ECCQo4rg7ebhjRNmRTad82bfRs3o3c1k7hwqy0Jw/i8H4HBaKQqCcG41jWEcCjrJsypAjwpAEJo%2BOrCJAQABxmgAbIEkhmCqkiSP43OBBo/jJNz%2BicJIvAsBIGgaKQpPk5THC8AoICq2zZP46QcCwDAiAgOsBBpBc5CUGgWJ0AkUTipwqjc3zs585IRzAMgPZSGaZi8FNhAkOOej8IIIhiOwUgyIIigqOoBukLoXCkAA7oiaScDwBNEyT7MU5wuYXFbdKoFQRyu%2B7nve77Rz%2B2YRwQB49v0MQJzM8svD61oqwQEgdtpA7ZAUBAQ8jyAwBSGYfB0BixA6xAsSF7EEStNcOe8GvzDENcuaxNomAOFvpB21FuYMLQm/J1gsReMAbhiLQOvcLwWDCUY4i33gjIOHgA5ZqF0ksfC42wWYbXqIXK4sRER7w8FgQuCI8BKzfqQQBxBYgo1ZJiQwwArhGHZqsKgBhgAKAAGp4EwOnRcpMWYR2EKIcQscGEJzUIXVO%2Bg8EoBppYfQeBYg60gKsVAtIciv1nN8JaphLDWDMBrDBxBxxAOET0Y%2BjQXAMHcJ4ToegwgRGGFUUYadijZAENMPwJjMhmIYAsEYiQ052HUX0SY7QdEFEcfUZxAh%2BhtDsUYhxthXEWL0HMPxBjFjGNWPTDYWwJB5w4MTNWhdNZVzdh7L2Ps/aSADs3XAIcO67C4N3VmRDVgIEwExUY05SBc0kIEM0yRAgiw0ELSQfMVb%2BD5qkQmHAFakCVoELg/MuB825jLUZ/hJBcGloEPmyTk6a21rrUpBt%2B6mwHubUu1sx4T3bk7NgnBWgsAHCqWcTA8J4IbskM0wzybByIEo9A4dZBR2YdIVhSh2HJ10LPTOTBs5vwSUk9WvBNYl0thcI4FcSTEBOWci5mZaJcBuXc5urdh7t07oEMwJTe6G02XshINtx6oDbqMY5pzZxIunskLgqsaALQSEvFeycd4b1PuyveB8j4nzQefMil9r6Fzvg/J%2BtAX6nw/ng7%2B5N8B/0cIA1%2B9zVCgIxKfSBvTyYwLgdcBB2xybINQSzDBWClA4M/vgvyRC%2BCkIoVQmhBJT4MLeTHD5sg2FJ3Jr8rhhCZFWD4TAoRNTRGNAkVI4K/q5EKISE8lRNSnH/2cBAVwIS076IqPYvQpjGhpvSNYxo/ilieN6D44J7jLFqKTU0VxRbjFBIGHmsJgwIlZuKWsWJMdgUF0WZwWF8LzmXORais0Gg8n4Eedi4pPcymkAqVUxINTen9MGTc1pKppYqhVILMw7TpkLI1pwZZesbXGzNhbMuJKiXEAOdsY5tcWAKAHD2AcKKzRCgmEHCdodnlpxdUwt1cd5BfK9ToEAwR/mAtznLRJPbD0cAhWXaFld71e0fc%2Bo4r6bkfrpC3MlmKEjYsCHi09g98MjyveR9uIBn0TVhFh2EOHwZws9nPJli9KCsvJlym%2BLMeM8vUafAVgghU3zlZge%2Bj9n6vxZtKr%2BBr36/2cUq4BqrkBgI1YIKBycdUb31UgpRxreCmuwbgr%2B1q1m2tgva6htDnWvIAxId18cQMcPA764wvCbBBvgCIsRfZODJWdFGyw8iwWKOUcG6JXjq2aO0fkStGbDHFvzSUHIeac05DrYExNjRfFuIS6EmLeXa2toCaE8thXHGlczeV9tMTGbxJgyClJfbUNHHQy%2Bt9OHx0FKnSRtZ5TKlYEXQkldIAzA3MCIEfw/hWn0o0NNlUYyD1gqPbYFZ%2BLlicySMMuZ/gVRmFm9M7pkgNCz16YEODa2tarL7gkwOq2i63a26sDBWRnCSCAA%3D)

## Links

- [source code](../../../../conceptrodon/descend/typelivore/front.hpp)
- [unit test](../../../../tests/unit/typelivore/front.test.hpp)
