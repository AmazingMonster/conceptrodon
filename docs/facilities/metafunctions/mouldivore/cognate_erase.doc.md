<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::CognateErase`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-cognate-erase">To Index</a></p>

## Description

`Mouldivore::CognateErase` accepts an operation.

- Suppose its first layer is instantiated by an index.
In that case, it returns a function.
When invoked, the function removes the argument at the index from its argument list and instantiates the operation with the result.

<pre><code>   Oper
-> I
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>, Arg<sub>I</sub>, Arg<sub>I+1</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>, Arg<sub>I+1</sub>, ..., Arg<sub>n</sub>&gt;</code></pre>

- Suppose its first layer is instantiated by two indices, which indicate a left-closed-right-open interval.
In that case, it returns a function.
When invoked, the function removes the arguments of indices within the interval from its argument list and invokes the operation with the result.

<pre><code>   Oper
-> I, J
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>, Arg<sub>I</sub>, ..., Arg<sub>J-1</sub>, Arg<sub>J</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>, Arg<sub>J</sub>, ..., Arg<sub>n</sub>&gt;</code></pre>

## Type Signature

```Haskell
CognateErase
 :: template<typename...> class...
 -> auto...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
alias CognateErase
{
    template<auto>
    alias Page
    {
        template<typename...>
        alias Mold = RESULT;
    };
}；
```

```C++
template<template<typename...> class>
alias CognateErase
{
    template<auto, auto>
    alias Page
    {
        template<typename...>
        alias Mold = RESULT;
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

/**** Metafunction ****/
template<typename...Args>
using Metafunction = CognateErase<Operation>
::Page<1>
::Mold<Args...>;

/**** Result ****/
using Result = Metafunction<int, int*, int**, int**>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
```

In the second example, we will erase elements between indices one and three from `int, int*, int**, int**`. Then, we instantiate `Operation` with the resulting list.

```C++
/**** SupposedResult ****/
using SupposedResult_1 = Operation<int, int**>;

/**** Metafunction ****/
template<typename...Args>
using Metafunction_1 = CognateErase<Operation>
::Page<1, 3>
::Mold<Args...>;

/**** Result ****/
using Result_1 = Metafunction_1<int, int*, int**, int**>;

/**** Test ****/
static_assert(std::same_as<SupposedResult_1, Result_1>);
```

## Implementation

The implementation is similar to `Typelivore::Amidst`.
We want to count elements one by one up to the desired number.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the elements to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` as in the implementation of `Typelivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `CognateErase` using concept expansion.

We will expand the constraint `Prefix<***>` alongside the arguments.

```C++
template<typename, auto>
concept Prefix = true;
```

- In the case where the first layer of `CognateErase` only accepts one index, we want to remove the element at the index from the list.

```C++
template<typename>
struct Ditch {};

template<size_t...I>
struct Ditch<std::index_sequence<I...>>
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
        // Remove the next.
        auto,
        // Collect the rest.
        BackTargets...
    )
    -> Operation
    <
        typename decltype(front_targets)::type...,
        typename BackTargets::type...
    >;
};
```

- In the case where the first layer of `CognateErase` accepts two indices, we want to remove the elements between them.

```C++
template<typename, typename>
struct Expunge {};

template<size_t...I, size_t...J>
struct Expunge<std::index_sequence<I...>, std::index_sequence<J...>>
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
        // Expand `Prefix<J>` to count the unwanted arguments.
        Prefix<J> auto...,
        // Collect the rest.
        BackTargets...
    )
    -> Operation
    <
        typename decltype(front_targets)::type...,
        typename BackTargets::type...
    >;
};
```

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`.

Note that we wrap the elements inside `std::type_identity`.
This ensures we can create objects to invoke ordinary functions.

```C++
template<template<typename...> class Operation>
struct CognateErase
{
    template<size_t...>
    struct ProtoPage {};

    template<size_t Index>
    struct ProtoPage<Index>
    {
        template<typename...Elements>
        using Mold = decltype
        (
            Ditch<std::make_index_sequence<Index>>
            ::template idyl<Operation>(std::type_identity<Elements>{}...)
        );
    };

    template<size_t Start, size_t End>
    requires (Start <= End)
    struct ProtoPage<Start, End>
    {
        template<typename...Elements>
        using Mold = decltype
        (
            Expunge
            <
                std::make_index_sequence<Start>,
                std::make_index_sequence<End-Start>
            >
            ::template idyl<Operation>(std::type_identity<Elements>{}...)
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwA7KSuADJ4DJgAcj4ARpjEEv4AzKQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJXCm2mPalDEIETMQEeT5%2BQfWNOS1tBOXRcQlJqQqt7Z0FPZODw5XV4wCUtqhexMjsHAD0AFSHR8cnp/u7JhoAggdHANQAIphprozIeJgKd8cX17dnAJOvyulxBZmSEWQ3iwdxMyTcBAAni8APoEYhMQgKOHYUHmCEMKFeGFwtxeRy0QiInF48GQ6GYWHw5CTdBYKg066g/77O7KYiYGiqb5HYEETAsNIGcWkpEvZhsUh3Jjk1Ccq5oQnPAh8gVCpkPO7oryYOFWLl/QFWoHc453ACSkvobEETCaIsOwJ51sBwNt9wehGQCA951B4qdbtN8LljFY0dx10mxC8DkeQZDJkCVkCDzNeOuEalUdJWQAXpg0QA6Gv29XJ1M6wMEYOlgjoEAgCJYVQopQARxNWtJ9prVZpyUTIOzoLuc6NEuLMuu86Zblnq/nRel0YRyLjbDHOLuUKYCi%2BAHkXhimqQN5ujfuFZgxxYmMgANYAFTawEwBGxFd53VVd5kcZATwESZMAANzEZVVTuPB0ERWh7zuCB0NXXZdjubBVDSQx0FhAA2DR%2BUFPBVBHGkyKNVBIK8QQjQQRlfx8RgALuKhiFQFgWMZHjZHHICHwooUaMnBCiDHITBDRX9/wUO9RM3HC7gAJQlVAYMZAhWLuSJVAIESrgfOcVSIFSzPM9S8kaAS7gFSZTPMu430/H9iD/ACj1UlZ0IAWmPK8EjdHJ0NJLCtyfeM7iwKFY2oXj5KmHyFBWTtYzHay3NjZ93Pfb9FIArL9z8my5wnc1pzzZIav9Q48IIpi/1DMVFx3WVYsVR95XjetjTTfC0laxksxzOqGsLTqS3hctKxM2slQW6sawAKUGlNhpaoxd1ZTtu0wXsByHbYRyPScVvbQ6GB7PtMEHN5d3Wy7cUnPEZ1U7cS1UqLVNXH6ZRjHqXxrY9T3PO5QpvHJcvM/L41fIqvPSyKPtUsC8AgzVoLg2hpIY5DUPQzCAfndSRqI0jyL1KjJNxOiiEY5j9LY7yOMEL4hP4tnuJSkzorncT6fhOspMs1BZIFhTvKU%2BGH0pgjqZMMiReo%2BFNo%2BpmGLQJidT5piAHdDHFYj2JdXyhd1SiNbcLXsEJnLrbszwHL55zBfJucPOKuXfPB/ygpC69woEdH129vqD0ZBLaCSuSCFl9LMpAbKawVzdEbYQrPJKhQypeCrV2qz6poLG47Q8YBmHFbAMSUdrw1m4GERb3ds7B8cpMhy9Q6aLbGzuava5wBvTS5L7KoXSNW9Wpbu6nUChp1flUCIZQmDaias3Li1p6B/a8ArNEHTu46QPnBs0zXjet93e1z41pfgKnvL2%2B6/rDxrbBnU47EMbT1XF4LIRg7gAFlPDEThIaOOsZrZkyAeZZsrZ5o3RACwJgH5KxHROo9M6D8n4Thfm5OcWV25IRQmheEMMw4MBxBAA6ad9womQpxKkpJf4Sn/jSGcuYxwBSjgFeqkVcz5n3oDD%2B81j6LTuAMdoK0ZGn2wHdS%2Bc4BSDjwM5DC8idRRWSIaFR6BBHT2vqvXid8/ykl0UqIxajYRvwRlIvcX8u5cMtgAkhm4QERGABAqBBp4qYESvuBB1tVwjTGuE4C8JokPiYZg7BrCn4PSesOeEuicSZ1IVfdBiScEpNOs9Thd1AqZMATkqqFTKnkNnoyYm1C3C0IHpORh6DYysKwIIDh8J3E8I%2Bnwh4AjrbCJqiXMRIiJFbmcZLMcVxgACm4VzexPiwGb23gY3U69UDrN3PMxZHi3riNqscxqPoARejtAAMS0ZMZqrApSMh%2BGc85pw/RcjpISBka5NTbDSABdUZzob9xyE3GadTP4xyOUmFewKwotOmpXe4QgvBpGKJgdAWkFBeHjmCq4qy/EorRZkDFWKcV6M2c0iK8IIgECVLSw49LBCHFLvvHkED/xMCoExBwoLnngqXB3UGczvKeNBASjlrRuWEndDA4eqAa5RnrmeXcVLw6AM7Ls0kXB1SdkgbQdApIriiqOZMkElp7hktxfy/FoC/FWopYacBnLpW8vVW4WlTKCD7C9YypCzL9isvNUipqX5Pg6htVjZAKIzxKHaG0jsIAFDxhjQAtwRL0WYs%2BOSpUDqcSjIrt6V5NoLVNSEMEgQxF8IPPoHiotxbRSFrtBmklWbsXWsbdcCVLalBtvJSiLggS1X0JpYIX1gaPpmqBc6qVPL3Q2sPpC58IrgBiq7XayVXK505AHYEkeSrx6kmHbqkAWr4RcCVMkE9%2BrDXwmNau01iL2UOrxRKh1u65Uzq3TKndOrR10v9d68d46g1ArDXcyNrRwKprjQQBNnZk1sFTdY1Fmb30Xs0tm%2BOA781mg4GsWgnB/C8D8BwLQpBUCcHXJYawdwFAbC2ONcEPBSAEE0PhtYH4AiSCrBoAAHGYMwABOITtR%2BN8a4IEQI0hCMcEkLwFgEgNAaFIKR8jlGOC8ALiptjZH8OkDgLAGAiAQAbAIKNOlFAIBoElHQBIUR4ycFUHxkigUSKSDuMAZAEEpBVjMLwDFhASDIT0PwQQIgxDsCkDIQQigVDqD06QXQF6jYYjSJwHgBGiMkfYxRzgF5yQWbuKgKgdxnOufc557zdxfNmAwh4Wz9BiCwmYysXgumtBrAgEgGzaQ7NkCs71/rIBgBSDMHwOg4piAFwgLEXLsQIhtERBl3gC3mDEERBeWI2hgm6ZYzZy2F4GC0GW4lrAsQvDADcGIWgBduC8CwJgow4gztaN23gXSd3yPHWCeSHYLHaUNFy5SWIGINseCwLl9EeBFP3dILpYgsQSVPCe8ASkRh2NrCoAYVdAA1D4RtQqkZY2F4QohxDRdJ3FtQuXkv6EMMYaw1h9B4FiAXSAaxUD/JyHdwKrIYGmBo5YMw6mEfEDYeziAaw7DvecBAVwMw/AXrCBEEYVQxgXuKNkAQiu9Ba6aIsUYNReiy%2BaFMDonguh6Bl26s3CxVdLA17Yc3uuL3zHaIb9XNRpcMe2BILLHBiOqdyxpsrLm3Mea8z5njdWIC4CC81/EXA2uscx2sViTAsCJCl6QLjkhkhViE8kaTGhJBmEkGRDQ/gSJCf0JweTpBFPJC4FWEiXASJ8aExJki/hJC1CLyRYPiWNNaZADpzHBnjPddM4V8k5BKBDaaw5tgnA2gsBgoEQKTATwGDAVwITVYW/ffwEQcXHYL2k4ixT6QVOlA08S7ocbqWmDpfuwHoPaneAaYK%2BZ8kxXSvlYR474M41YH5H71Z8R9ZNYtbJBmAp4db6bT6L4JDz7WaQHDanhGD75cAqY0DxwJAzZzaJZrZLYrakAkEbZbY7YOBkEHacRHYna5bnaXbXa0C3ZkGPYM4vbkb4ACi8qfa5Y/bIB/ZkGA6ybkYg5g6IgQ47DkbQ6w4sYI5I5KAo5cG%2BIT7Y5bwKD46YCE7yhkGX7k5RY36yDU4JbkaP704Y6C5WCWAs5s7wCc7c5QScB87tgC5M7C6i4JBn6fCOEm624uB3Su4hB3Se7LCa6ZDa65CW4FCRElA5DhFO425NC6IhEpH9Dm5JHG7u4W75BK7O724VBG7%2B7rCbB%2B7J516B45bD6cBh4VYeaYF%2BL76H68YYTx6n4wHJ7tZp6kAZ5Z6UAB4N5N4H6l6BD%2BBCZSbJBl4V595D7qacCj7j56ZdZT5IBmYWaoHIHEDL47Br6VYsAKAwQQQwQtE7iTABYn7Bbn4xZk6RYSAmGxZ37mE6AgCpDP6v6ZZVEf4h75az46glZlYHFHEnFnFRh3IQANZQEJAwHJDwET5IHoFNZbFIljDHFoooinFCYojnFJyqDuYTb4HTaUBEHkYUGnYsbklUG7a0F8SHbHanY8GYAXZXY3Z3YsacHPayEPZvb8F%2BGJZCEiFw5iHA6s5SEyFQ7i4KG8BKHI4ShqEY4rF8A47aEE5E4GGyBX7GG3FmG05vFWGM5C42Ag6S5OFNB3a7AHQ2HWAi5f5i4S7%2BEZFy4K6xEFEq7FFe565RFNAhH66JEO4lFu4NCm5pGunW7Bm266LZHW4u5hlu5ZEBmemVH0blFRbv41ELEcBAkeaHHHF3BYlVi4ntFXGJ6tY9ErHp6YCZ5jA56ybDEgDCZVjJDJD%2BD%2BCl44EaDNmBAd7zFf6LG2Bj6p4Vm54gCSD%2BCF6SaBDKZ8aSCiZcACZmCD6ybJAZl9maZDmdYB7%2Ba9l5brkIErBrAI5ZDOCSBAA)

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/cognate_erase/implementation.hpp)
- [Source code](../../../../conceptrodon/mouldivore/cognate_erase.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/cognate_erase.test.hpp)
