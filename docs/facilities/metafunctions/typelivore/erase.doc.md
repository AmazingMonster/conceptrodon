<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Erase`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-erase">To Index</a></p>

## Description

`Typelivore::Erase` accepts a list of elements.

- Suppose its first layer is instantiated by an index.
In that case, it returns a function.
When invoked by an operation, the function removes the element at the index from the list and instantiates the operation with the result.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>I-1</sub>, E<sub>I</sub>, E<sub>I+1</sub>, ..., E<sub>n</sub>
-> I
-> Oper
-> Oper&lt;E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>I-1</sub>, E<sub>I+1</sub>, ..., E<sub>n</sub>&gt;</code></pre>

- Suppose its first layer is instantiated by two indices, which indicate a left-closed-right-open interval.
In that case, it returns a function.
When invoked by an operation, the function removes the elements of indices within the interval from the list and invokes the operation with the result.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>I-1</sub>, E<sub>I</sub>, ..., E<sub>J-1</sub>, E<sub>J</sub>, ..., E<sub>n</sub>
-> I, J
-> Oper
-> Oper&lt;E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>I-1</sub>, E<sub>J</sub>, ..., E<sub>n</sub>&gt;</code></pre>

## Type Signature

```Haskell
Erase
 :: typename...
 -> auto...
 -> template<template<typename...> class...>
```

## Structure

```C++
template<typename...>
alias Erase
{
    template<auto>
    alias Page
    {
        template<template<typename...> class>
        alias Road = RESULT;
    };
}；
```

```C++
template<typename...>
alias Erase
{
    template<auto, auto>
    alias Page
    {
        template<template<typename...> class>
        alias Road = RESULT;
    };
}；
```

## Examples

We will see two examples that demonstrate two different use cases.

In the first example, we will remove the element of index one from `int, int*, int**, int**`.
Then, we instantiate `Operation` with the resulting list.

```C++
/**** Operation ****/
template<typename...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<int, int**, int**>;

/**** Result ****/
using Result = Erase<int, int*, int**, int**>::Page<1>::Road<Operation>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
```

In the second example, we will erase elements between indices one and three from `int, int*, int**, int**`. Then, we instantiate `Operation` with the resulting list.

```C++
/**** SupposedResult ****/
using SupposedResult_1 = Operation<int, int**>;

/**** Result ****/
using Result_1 = Erase<int, int*, int**, int**>::Page<1, 3>::Road<Operation>;

/**** Test ****/
static_assert(std::same_as<SupposedResult_1, Result_1>);
```

## Implementation

The implementation is similar to `Typelivore::Amidst`.
We want to count elements one by one up to the desired number.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the elements to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` as in the implementation of `Typelivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `Erase` using concept expansion.

- In the case where the second layer of `Erase` only accepts one index, we want to remove the element at the index from the list.

```C++
template<typename, auto>
concept Prefix = true;

template<typename>
struct Ditch {};

template<size_t...I>
struct Ditch<std::index_sequence<I...>>
{
    template
    <
        template<typename...> class Operation,
        Prefix<I>...FrontTargets,
        typename,
        typename...BackTargets
    >
    static consteval auto idyl() -> Operation<FrontTargets..., BackTargets...>;
};
```

`Prefix<I>...FrontTargets` tells compilers that this function template is only allowed when `FrontTargets` satisfies `Prefix<FrontTargets, I>...`
In our case, since `Prefix` always evaluates to `true`, it constrains nothing.

- In the case where the second layer of `Erase` accepts two indices, we want to remove the elements between them.

```C++
template<typename, typename>
struct Expunge {};

template<size_t...I, size_t...J>
struct Expunge<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template
    <
        template<typename...> class Operation,
        // We use `Prefix<I>...` to reach the start of the unwanted elements.
        Prefix<I>...FrontTargets,
        // We use `Prefix<J>...` to enumerate the elements we want to erase.
        Prefix<J>...,
        typename...BackTargets
    >
    static consteval auto idyl() -> Operation<FrontTargets..., BackTargets...>;
};
```

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`:

```C++
template<typename...Elements>
struct Erase
{
    template<auto...>
    struct ProtoPage {};

    template<size_t Index>
    struct ProtoPage<Index>
    {
        template<template<typename...> class...Agreements>
        using Road = decltype
        (
            Typella::Ditch<std::make_index_sequence<Index>>
            ::template idyl<Agreements..., Elements...>()
        );
    };

    template<size_t Start, size_t End>
    requires (Start <= End)
    struct ProtoPage<Start, End>
    {
        template<template<typename...> class...Agreements>
        using Road = decltype
        (
            Typella::Expunge
            <
                std::make_index_sequence<Start>,
                // `End-Start` is the number of elements we will erase.
                std::make_index_sequence<End-Start>
            >
            ::template idyl<Agreements..., Elements...>()
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwA7KSuADJ4DJgAcj4ARpjEEmZcpAAOqAqETgwe3r4BwemZjgLhkTEs8YlcybaY9iUMQgRMxAS5Pn5BdQ3Zza0EZdFxCUkpCi1tHfndEwNDFVVjAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimKmujMh4mAq3R%2BdXN6f/xx%2BlwuwLMAGYIshvFhbiYwW4vI5aIQAJ5w7Ag8wQhhQrwwuFuZATdBYKjozG/I63ZTETA0VRfQ5AgiYFipAwsgkEFHPZhsUi3JiI1Dkq5oHFPAjU2n02Fg%2B63AjELyYOFWK4gv4A7UHIFa24ASTZ9DYgiYjUZus1OptZwp1yp90IyAQlrtVxZxvNqvh3N5rB9GKuE2VDgeztdJkCVkC9zV9s97O9BMyAC9MAB9AgAOlzBtFlxDXjDToILpTBHQIBAESwqgzSgAjiqJQSDbns%2BSwUHgdGQbcB4rWUnOVdB3K3P3x4PExyfW4/YwAx30bcoUwFJ8APLPYjm7KkKfT6V0vCqNvojsAMWIsgAKq1gJgCApD2Pj4qeUv%2BUfp4u%2BZgHYWEwyAANYPsQT4vr%2BBbjnMjjIGuAgTJgABuYiCsKtx4OgKK0BAyy3AAtKuO4JPuAgEje96Ps%2BCgdgKwFgRBUH0bmXbqr2cZgpx1p3NgqipF4RiYG6zLDnOXJfgBAr/gGBZFmGAlCSJsJ9rG8Yah6EnJvCaaZjmeYCvpWYdgAUgpSrFlKynCU%2BFZVjWDB1g2mDNq887tux3bGZW1a1pg9ZNi2WwEmZK7dgWUaceOs7Ju%2BA4Er%2BsU6ZyvrScu3nYGuBibrcZF7o0b6XB%2Btw7DstwAOqiV4SiwgAbBoNKnue8L5t2K6NYqqC3LSIGugQCCiXMbS3KgVCKkNtzCQA7oYLLoLc9SsowL6dgl07NfSF4dbm1GCCxdHFaV5VVTVdUmI1W1nmFl7sV1RBLQwPjkSyk2ictpovrcM2iXNgjdUte5KOtJUftdrVuBZu3ZsdH5yWwQEgeBtHQRtsGDvBeCIeKKHobQmGPTheEEcRpG7hRDBUbeB2o2xsO3ExKOQXREUYjxmIaRzWkOvxwOid8IJxWlC4ZYjubYCaq0KJZoY2fznMxTOqXzkKRBs7%2BilSjSqBEMoTBPmpMbcbxG3C/OJlSgazmBRjA5a9KuuoPr9ltTbrU9uO0XJcrXoi%2BbUn%2BuLnbdjlG705cwC0itggy5FG3jrVETALcABKqBMItcIKlgUKLj7A4QAX06luWel%2BSALBMKBmYBUFbkhZ57tdp7pWDtW5vYbhtAEpH0dffTAqSzHa1ZQRxfLJpYOJVzpvT0OfsW3g6ZZrc/RtMZy8Gbc2DOXbvUN3gtKfBA69Skl8o785k8bQ7Ot6wb85n0Pe/x/P3sJ77I7zgH6VB4BWUw6bg7H3TAI846t2PEnIwacM5Z0vrnWg%2BdP6F2LuOWyIk0GDiSigtuxJqxVxrhmOurl3KtnhGfdEcM27TlOpdDQu90BEUoV1PAnxBqiWepUBIY0JqfWlj9P6dACbkRBlg48%2BDK7V1ru7UhjcCSMOYZMAg%2B9SqqI/B3FWXc8K9yjmAgeDEd5S1jmzceuDJ7c3frPe0KVF4EjVqgEBejwH72gSnF2ols6Owfq7NwoDwEa0sVGE29otS2hOHqKkV4j4TB3qoVg7IBZMj4uE04QJMTgkhNCTx8JxRbFSNBN%2BKS9j5QphaQW2k7F/2/AAkOPYHYFUplPYpa8vCpCKJgdAqcPheCQWJEEbjWntIyJ07pChenn0vo0xoBIIgEAFHMg4CzBAHA4qEqkYyJn9KuIMzZfSvHYAVvCOZyyCB7FOUs7CKy9jomrB4gkXBbkgHTpnAk0zshrJ5vqO8HwpQVMLC0BCGZw4JAIBASRCgAzArjm4IQbSOldJ6UggUeyVHdgsXPMJqT/n6iEJgcUi0BIJPoNs3m2KInrLuHC4ZShEXjL6f8wZ1KEWoozFwOUCp3mUWOYIC5NzIpBMpHcVFpLdlIoIGyjlO8jluBOVcs5fK%2BVPPufCFItwwRPJeegN5ZSPkCsxVSH5sT/lY2QNCpQbRwUV0hWwaFBJmUjLpRMtlKLxVsvRBijgqxaCcH8LwPwHAtCkFQJwSclhrC3AUOsTYnjwQ8FIAQTQXrVigQCJIbMGgAAcZgzAAE5c1cH8FmzNXBAiBGkD6jgkheAsAkBoDQpAA1BpDRwXgCgQANsTYGr1pA4CwBgIgEA6wCBCXmRQCAaA2R0ASFEAMnBVCZvqkReqkhbjAGQIhKQ2YzC8E6YQEgOE9D8EECIMQ7ApAyEEIoFQ6hu2kF0CkGae5UicB4N631/qk3Bs4FuREo7eG3AXUulda6N23C3WYW4EAPBTvoMQWEcbli8C7VoVYEAkCTtSNOsg47MPYZAMAKQZg%2BB0BZMQdtEBYhftiBEVoKJX28Bo8wYgKItyxG0Pirt8bJ1fS3AwWg9G71YFiF4YAbgxC0HbdwXgWAq5GHEEJo%2BnG8CoQ%2BF%2BwK%2BLETbHjXM%2BoX7kSxD3CxjwWAv1KjwLW6TpBVPEFiCMx4cngDIiMEm1YVADDAAUAANXeDNMiAb43HuEKIcQF6gvXrUF%2Bh9%2BhDDGGsNYfQeBYjtsgKsVABTshSaIsSbOphw2WDMM2mzxAcJqdSz0ZTzgICuGmH4FIYQIjDG4dUNIGQsgCFq3oIo7WGALBGC1uwlWmjKM6%2BMZaDg%2BjKL681vQI12ieE6LNqbjXFijC4KsKNGwtgSHfRwP1jav0tsA4u5dq712bvTZBiAuB93waxOt5DrnVhDUzqMAipBU2SDBNmXNYJy0aEkGYSQjUND%2BHqrm/QnBq2kFrWCLg2Z6pcHqpm3NJb6r%2BEkIW379UDt3pbW2jtCbXO9oHehodf7ETkEoHhuDs62CcFaCwVCgQiJMDDjArgubszw6DXuogJWqwpCC6e0L0hwtKEi3e3QxGn1MBfdJ3b%2B2m28Bbb%2BkdiIANAdO%2BzlOnPucZqgzBrDcGENgjMEhon3a0MYdQLBhIVOJ22%2BN6MdcRhOdcAbTQJBCQKNUbvUxujDHSAB5Y2xjjDgg88dWnxgTX7hOifE7QSTQfZOxYU0G/AtIJuqak7z1QmmWRB905WoNBmjMohM9sIN5nLPxps3ZpQDm0/J2J%2B5g23nfP%2BaD8LkL56xeyAi7eoN0uYsuby1YSwiXkvwDSxl5CnBsuVly/FgrRWEgC7K%2B9wbE2qs1YW/kerzlptLBSN1xoo3WvFGyMftbFWd/DYGBf7fjQz434GyN/fdXbDLfKP1nbawttz1FdP08dOBjtgNV1XddcucecoMbt%2BdTcHtLdUNntMBXtEh3tK1odYcucAdAh/Bc0y0wRAdgdMdcdm1OACdO1ic%2B1B1h1R0HcacZ050OBGcQMWAFBUJEJUI9c5wJhd18B%2BdD0hdZARc%2B9L15AJch8dAQAwRSBZd5c31Ic9sQCKCOA1d/1xpAN2DODuDeDvRYloMndsNTcwQLcUMe0ycmCcNqdjC4MQAuD2kMweDc0Mw%2BCJVVAV0SNvdyNKA/cg0Q9BN41Aiw9ONI9bdeN%2BNBMM9MARMxMJMpN41U95Mq8ZMlNs81M70NNkAtMi9BA9M70y86NK8zMSta9eB697NWRm8XMrc%2BAPMO9MA/NeRu9RDe8JB%2B8r0pCotZDR84t8sbADMUt3t0tGgpMdh8Fx9rBCsVditSthiNtxtGgXBnIL8Gtf8ZtT82tz9P8uttjr8Vs/8xtegBAz4n8ljJt5hDjNjv9H9djxgf8msT8Nto1tt1tlCldDswDPDV0OCuDbgXDsx3C4DBCSBEDzCntSAXssAMDdtsCQA81swwQwR/Ai1Md61kTAhkdyCVdKDbBCcLDlgU0QBJB/AftS1Ah61M1JAC0uBs0zAcdK0wRVDcTW1kDk1lCd0cTv02TCTVgbNMhnBJAgA)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/erase/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/typelivore/erase.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/erase.test.hpp)
