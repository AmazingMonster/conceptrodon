<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::CognateRemove`

<p style='text-align: right;'><a href="../../../index.md#list-modifications-1">To Index</a></p>

## Description

`Mouldivore::CognateRemove` accepts an operation.
Its first layer accepts a list of indices in ascending order, which indicates positions in a list, and returns a function.
When invoked, the function removes its arguments at positions indicated by the index list and instantiates the operation with the arguments left.

<pre><code>   Operation
-> I<sub>0</sub>, I<sub>1</sub>, ..., I<sub>n</sub>
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>m</sub>
-> Operation
   <
            Arg<sub>0</sub>,
            Arg<sub>1</sub>,
             &vellip;
       Arg<sub>I<sub>0</sub>-1</sub>, Arg<sub>I<sub>0</sub>+1</sub>,
       Arg<sub>I<sub>1</sub>-1</sub>, Arg<sub>I<sub>1</sub>+1</sub>,
             &vellip;
       Arg<sub>I<sub>n</sub>-1</sub>, Arg<sub>I<sub>n</sub>+1</sub>,
             &vellip;
            Arg<sub>m</sub>
   ></code></pre>

## Type Signature

```Haskell
CognateRemove ::   template<typename...> class...
                -> auto...
                -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct CognateRemove
{
    template<auto...>
    alias Page
    {
        template<typename...>
        alias Mold = RESULT;
    };
};
```

## Examples

We will remove elements of indices `1, 3, 5` from `Vay<0>, Vay<-1>, Vay<2>, Vay<-3>, Vay<4>, Vay<-5>` and invoke `Operation` with the result.

```C++
template<auto I>
struct Vay
{ static constexpr auto value {I}; };

template<typename...>
struct Operation;

template<typename...Args>
using Metafunction = CognateRemove<Operation>
::Page<1, 3, 5>
::Mold<Args...>;

using SupposedResult = Operation<Vay<0>, Vay<2>, Vay<4>>;

using Result = Metafunction<Vay<0>, Vay<-1>, Vay<2>, Vay<-3>, Vay<4>, Vay<-5>>;

static_assert(std::same_as<SupposedResult, Result>);
```

## Implementation

We will implement `CognateRemove` by combining `Pagelivore::CognateSegment` and `Omennivore::RemoveTypes`.

When provided with a list of ascending indices, `Pagelivore::CognateSegment` will find the differences between the adjacent indices.

<pre><code>   I<sub>0</sub>, I<sub>1</sub>, ..., I<sub>i-1</sub>, I<sub>i</sub>, ..., I<sub>n-1</sub>, I<sub>n</sub>
-> I<sub>0</sub>, I<sub>1</sub>-I<sub>0</sub>, ..., I<sub>i</sub>-I<sub>i-1</sub>, ..., I<sub>n</sub>-I<sub>n-1</sub></code></pre>

Then, we will make `std::index_sequence` of each difference by passing the following helper class template to `Pagelivore::CognateSegment` as the operation.

```C++
template<size_t I, size_t...J>
using Detail_t = Capsule
<std::make_index_sequence<I>, std::make_index_sequence<J-1>...>;
```

We will keep the first index, <code>I<sub>0</sub></code>, since it represents how many elements we must pass to reach the first target position.
We subtract an additional one from the rest since we only need the number of elements separating two targets.

<pre><code>   I<sub>0</sub>, I<sub>1</sub>-I<sub>0</sub>, ..., I<sub>i</sub>-I<sub>i-1</sub>, ..., I<sub>n</sub>-I<sub>n-1</sub>
-> Capsule
   <
       std::index_sequence&lt;0, 1, ..., I<sub>0</sub>&gt;,
       std::index_sequence&lt;0, 1, ..., I<sub>1</sub>-I<sub>0</sub>&gt;,
                    &vellip;
       std::index_sequence&lt;0, 1, ..., I<sub>i</sub>-I<sub>i-1</sub>&gt;,
                    &vellip;
       std::index_sequence&lt;0, 1, ..., I<sub>n</sub>-I<sub>n-1</sub>&gt;
   ></code></pre>

`Capsule` is a vessel holding the results. It can be declared as follows:

```C++
template<typename...>
struct Capsule;
```

Finally, we will transfer the `std::index_sequence`s and relevant arguments to `Pagelivore::CognateSegment`.

We will use `Send` to connect operations.

```C++
template<typename...>
struct Send {};

template<template<typename...> class Container, typename...Elements>
struct Send<Container<Elements...>>
{
    template<template<typename...> class Operation>
    struct Detail
    {
        using type = Operation<Elements...>;
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};
```

Here is the entire implementation.

```C++
template<template<typename...> class Operation>
struct CognateRemove
{
    template<size_t I, size_t...J>
    using Detail_t = Capsule<std::make_index_sequence<I>, std::make_index_sequence<J-1>...>;

    template<size_t...I>
    struct ProtoPage
    {
        template<typename...Elements>
        using Mold = Send
        <
            typename Send
            <
                typename CognateSegment<Detail_t>
                ::template Page<I...>
            >::template Road<RemoveTypes>
            ::template Mold<Elements...>
        >
        ::template Road<Operation>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[Run this snippet on Godbolt.](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIGYAbBqkAA6oCoRODB7evgHBmdmOAuGRMSzxiSlpdpgOuUIETMQE%2BT5%2BQbaY9mUMLW0EFdFxCUmptq3tnYU9CjMjEWPVE3UAlLaoXsTI7BzmgRHI3lgA1CaBbl6OtIQAnlfYJhoAgkcnZ5iX18iL6CwVGerw%2BZmODFOXguVzcBAe6UwAH0CMQmIQFCD3qCAPQAKgJePO2FUBFcADFiLJzoS8TjQWSWOkDGTYfDEcw2AA6HlYt6LYheBzE0kUqmCS4AdiskoAIlcrNj3ozmUxWdcVSzMGyEYxWJgeVznudTkwFApzh5BOjImRzuy9dyedh6GxBJjAi93gKhQQRWSGOhKbJYVbWitiLCXZg3QQFIaQZ7QSZpaDzun7THVeq4brOQaeVFMAB3aOxj1et4Z85ebJGc4AWU86F%2BsstshtCVhRdLrsYccNpGJffdCaTgUVHzlCuTyqzWrZ87V2uuTFuqDH2BNBnN5yEmAAjl5GPsh2uiIaAGptPBMWL0Cugn3CkkBoPigiw/dHk8rtzX4hb3vTB415cdKxTSdq01ZdYXPDceQsTBgAiBgImAR93mrWt0POZQmGAH4rjbb9j0hP8kJQhg0KMUCuSHACgIfTcZ2xacJ1nN58UJPDiEwGhVBpQl6TnJkFw1PN9SHbIAC9kU/JN3jQcj0j9ZQ%2BIE1t7UFFdJ1xWlLSYdIFC8eghIJES3hgnMHXzFjvVRX1DOM0zdM47iCXOAAlGNUAAN0wAAVXULVpSzrL/Wz9Xs/lHOFHyWH8oKQqlGV5Q4pUuIMiwzR%2BNxcvMukGSXHN4MNABJPlnz9BKkuCxEPTcAEQBACIsFUJElB/cjYXKljFKnKCMwitMM1hUbq3THEcXOAB1H5ayI1J1P4vBVF654E1Se1UHORgfASZdLlSYNBECtpCLjExUiNLDJvTFaBI2z1DVOghzuIS6FFICbJumuafnQKl0ntBAfkiUlzgug7BFuqt7vtSS2B%2Bu77qip0uRy5AAGsPq%2B36%2BWrRY1TwZATQERZMD8sQofXc48HQB5aAgDZfoAWmNfKXPoAnrl%2B6s3rxzABx5FH4furHcYu4W6N5l4Mo%2BVHMzE2CJI5aKeTeYA%2BJjftMPFms62ARtmy0rBTgdCAGaZ2EtZ18tNxZ1mFZTdK9NE7M/zKnlyrPddDQAKSquKat8gL6pA2FmtawNMA6rqyP2XrN2kgh0Batq486w9E7/AP%2Bog1MlZGpXxqV6t/vmw2lo0R61ue7Ato0Ha9oYA60TJY6NEF6Wrpu/mMzr9brkql6eR7z6ZbFhHzkrwHgdB8G479aHYzhmf0cwaeEbn6uu6H2Eg7Ho1tqIc5gF2phkCpXcCDB858GJnry4zf74gIYtMEYe1i12mYvvXgjA%2B1wj6Nx5A2Bm6B6BCzjNve6u8gaoBBnfJekNV79kAWjJGW8B7pk3oaSWMDMSlwGkTVojgybKUptTWgtMz7W2ZqzJWHNPTORMjzEhbhcHnAngA0W3CIGAmgb3OicDJqEJEQmEh8t3YGxGmrR0BYuR2y/uWQmGYcL1ibLQFsxEH6NFoJbBhtttaqL1o7DYzs9LsVkR5IkPlkC7GyAFQyShCrhRKl7f2Ps/YXh5AHIc%2BCeQAHkUHEFIr%2BfW1VvJh2Sg1KOacM6x3jjnX8ycwLYFTunGO7Vs7dSTiAlO5xQlg3Cak8issBqQV%2BiXA2ZcDYVxmlXRa%2B8NL1xHptXkp9dr7TYB3GuvCZbXQ0JgyawC3CjzAVyQZsDuEIIXig84EMV6fRhgQUZ0FsFiMaQDPewzxmgKbi3C%2BUNr5ZAtIsx%2BrRn4NNfjNd%2Bn9v4fz/pI7hBzOlckEVAoKIjtl3N2Yg5B99llQ1WWvbhm8/l4OwQQq%2BUtJ5XWkb9YmFDyYMGoTTeC9NGaMPZsaV8YoQycIhdgmJiVw4hVhCUhIESKkxRni1CKJsdGwgkQiyplZqzqPTIyzxzL0C8y4S/dMMzRECMgcI9lUi6njlkdBTxOp1YYxUbrd03LDa4W0bowIbZzaGN1FbHFJj7bmIyU7ViU43buQMvVUmYhlBIPccVFWpVvFGgGtEoQCBbgEB5i7D24l8puuDoKYUtrRC0AdSDapNjOLyKDWfckeBiCLBDU5cN9qkGwiTSmhShchrpk0cbB0WkvU%2Br9Vw2VyZY2ZXjVinNixfG7X3MpAVHqQ7nAzZGrN1wG0ECHC2gQbb82/SLYjREpbvUEF9X%2BPtiZrFWtrQq1cdM%2B1Nr3I0IdTbDTUpTWmsNCI7XdvSNm5NjaN2tqHLujl1aC0avrA6XmbYCWBjeoqxRnbD0RqjVSsJHLGW6nVbyl1Px8KEVPbmgdm7AzzurYuxWWUeL7kDE6gNqtcxKqUfuv0yHdGphrQh%2BNRGYUZO3GaC0YZOx2iCVyMsetsMbpg9cSjEYowjhFu6%2BWI7i7LrhLxmjxpTS7mCYiDuuR1XRNlMLdEtACZF1uYWo246iI6uKaJkmAg2Oqo47B0uBGan8f4yRzjZHzSGhVWo0hGilNeVQEwbVbYpPhlk9cCzprOMAcRBa123m0M2V497EzQmLS0tPHQhCXJGJ3gfAx3DX5ykFP/DeaLIEC63oMyBxcmWV1%2BKCzuC0InDoDAkx2pzMm5N3uwkpktejCtic09cKLwEb0Ky5fpnj2W%2BOdcC4J/L5nTHaf1lV3CXkZNaTK3QY1ZjRwZM825Ni8H9I8Q8MAZgZJ9zAFjKhqyhnuvBtYcFtTRXxPttDX6Fba3MAbdjOljrnso54Dkiic4vtziyXkoHErZ3zgTdk3pyrw1ePvZRIaAA0uq6sfEjzJpAucCACYUjmGSBAUHvw3DnADpY7hY6AASkDGDPdq%2Bp4rI8hwBzZqD/qd6fP%2BrkQFt1bm1VWcU7hMDKmSKuHffmT96Qj0/tcwNh2s2QCPuZ%2BcYDntvLleuL9qbg3NwS61OcPHgICd5t81xGa5VAyk1h6IBgUNaAKF2vEc46RyOYBbGO4Z0dM4pPydqfud3A2by%2B05FXWADcxsW879DwO/Svf959sX0SPeMASdku3eTc69TJ2l/7EKgePY%2BzycHYvIc5xhxaeHvJEcpBR2jjHWPhX3uNr9wnqm6saYYLHjHFOqecRnmOmrqm4sKO512/nEy4/C9F5yhGiujqjcmzL6TdAUS6bqe1unnWaOM6umLsdWqtJh5rwLk1M2PMi8Ay7afdj2yreXLVFxYVnX3Y1EZzDm5TMFeJydys0SLtH9ibdmf5%2BmrJ%2Be4Hz/6z/HqrHeXn6HolzOwn%2BNHCwEwNjMiFHgnGkh0p6Fki1BAVAUiDAQlnnGzFwB8pPhlu/kHj7G7sKOpKgEQGzhVonrPsZnRkzv3vdEvqbHonFiXvUjPJsphoxgKiXlynzFwQjJvAfpdtdv2LCIARDqwTyiLnymQSPPSuIb8NgIPp3LZvZrCMfnEpHOngPpISBvylpkLpxtwmIRIUysoW2m4FXiTjInJj7m/oGoFvPkNtZqzgROzrxCQagNIW4A4Q3gthrnYrSAERZEtp5IFCBHGNtv4YEafplJ8JCN8GjrcHQI8HyGfnYXTJMk%2BB2k2AwO4QwE8GxBYG9uQqTGipTKoOkMQOFucDQseKlJVDYlKDYcRlfhkpkd9hYSdrIs0YouZp9PrEvtJlQF4JCAMFpE/mSGoVSnfg1pWC1J4VwEOMEOcP4HyC1FqrbH0T4QhmOkIF4OkCUJbj5OwkAZXtMWvm4NkbkU8NcBoM8EOJcUQHkbCGYHcSbDkY8dcW4JIImFYZlGOkcaZCcW2A2IMcMU0A1hcQIFcbCLcQgW8dCdcJga8Q8QIJ8S8XCSiU8YiYEMiVCR8bCN8RiXiaibCGzCseBBriiqTEiBbu0BANHAoPqDSY1LsfsVkIcSBICUOACYYs8FYhwFsLQJwP4LwH4BwFoKQKgJwFwpYNYG9jsHsEROCDwKQAQJoAKVsNjAEGYFyJKGYJIAABwGn%2BAaAACc/gZgGgyQBpwQQpHAkgvALAEgGgaQYpEpUpHAvACgIAaQap4pAppAcAsAMAiAIAOwBA6Qtw5AlAaATIdACQUQ%2BonAqgBpyQbMyQkg58yAZMUgXIZgvAluhAJADMeg/AggIgYg7AUgMgggigKg6g/ppAugCxxYaI6QnAPAgpwpop6pkpnAwStwkZfoqAVA5wKZaZGZWZOZkgeZcOHgcZ9AlRRwXAGwvAfpWgWwEASAsZvOi50ZEAO58ZiQwAUgZgfAdAZIKalAsQvZsQEQbQDwHZvAd5zAxADwwSsQ2gjQfpKpsZsYwSDAtAj5jZWAsQXgwA%2BUtARuT5pAWAEBRg4gIFMOTQAU3pjZccjQtwBwKpEQZIdpEp9wsQaIb5HgWAvZqIeATp3AvAAUxAsQ7JUm8FwA9wRg6pWwVABgGEl4eAJYhWYpKpZZwgEaVZ0ggldZagvZzZ%2Bghgxg1g1g%2BgeAsQ3pkAWwSCAwaFbMAIxEpgsplglpvASUxAgEWAylLMvQ/QuQLggYcwfgCxYQKwVQNQegJQOQAgNlzlWQrlDAowjlEwCxDQ4JgwSw7l/lfQ35zQSwPl4wiQ/lwVngXQegxM7QUVawMVWwxuuw%2BwEgXZHAIppAbpBlnAY5qZ6ZmZwA2Z5wuZZgcOuARZS5ypq5qpbFWwYM9mEwZlWpkggQXIppgQkokgGgkg%2BpqQGg/gyQpp%2BgnADppATpgQXAXIyQXA1pppBpS1/gkgXA/gvVyQ%2BVvZHpXpPpTV/pm5IZW5YZg5UZFAB5qAC5CZSZHAbQLAfkkobMTAZG9YXAppXI81EphZRAxlpZsgFZ4g1ZYlSgEljZugZ5rZRkT5OVeVBVfZHAA5EZtw5wI5oKT1L1b1poH1X1P1c5N1u5CQlw4IZgjV65AZZ1h5e5V1NNEwj1z1bMuNJ5ppXAaQNAhiCQ3pEAN5jZL5D5MFAtb5H5X5DgMFf5/YAFQFvZoF4FkF0F1FsFMYMliFEp%2BAfEKFIEvZGFjiZIMFuFfQvZhFxFDwpFBwEpFFVFKptF9FSgjFqt6EbFfAnFCg3FvFHIMFglwNIlNZ8g4NDZEpUN0lrFOlVglgClSl8AqlqkuQGlWlOqYd1g%2BlkptFxl2tKl5l4VzgEArgIVIQgYKVTlCxLlAw%2BdpduQRdflWdgVQwsw8VhQoVFlAgddywlQ0ViVcVBQtl0wwwVdaV2wmVVZ8NPZjZHpmNTNONBgeN31XIzcEAtV/1pNc1FNzVpArVWAiQZldp01s1X1g1koW1kokogQQ1kgGZCxiN%2B1tgh1lNJ18AZ14ZQ5%2B59NxAiZbAnAj1k5LACgfkZMfkn1XIWoiwBZ%2BA/1JZCx3twlEgolsg4lgdOgIAwQMN7Z1FI9u1Y9/ZF1w5o5X9mZP9f91RgDwDfoEA85xN9VgQgQq9x1gZ25RNR5L9DDi5IAf9%2BxSIADppSIJDNJxALAGZ55XNV5vNt595b5QtYj75n535EtN1/5gFwF6tmAYFEFYgitKpcFqtFtvAGt4VqFOtqgmF%2BtStht%2BFvAJtD55t5FgE1tNFCQdtmADtCFTttDHFBEbtPFxYfFXtQN0DoNcDAdklSDIdslulNghFplMd6lnAOIzUSdel7padDMGdZlAVAwVl7gDdPd9l7dqVHlpQuQ5dnlAw/diVYVtdXdCVTd2dQVfdDlHdsVww%2BdSVbdqwxd6VCpWVK5k1uVo97pRVeD5wBD/9xDy4iwNVYDJAy9K5a5a9G97VOVu9SQX1VD/gJpG1LpVDko1pGD/TnpN9vpa9nVkoeZh9XAUgppB9vVXAkoPTgQfThV%2Bzd9OV%2BZuzjzszx1WwtF2QzgkgQAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/descend/mouldivore/cognate_remove.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/cognate_remove.test.hpp)
