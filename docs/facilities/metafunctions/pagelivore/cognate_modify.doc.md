<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::CognateModify`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-cognate-modify">To Index</a></p>

## Description

`Pagelivore::CognateModify` accepts an operation.
Its first layer accepts a transformation.
Its second layer accepts a list of indices in ascending order, which indicates positions in a list, and returns a function.
When invoked, the function transforms its arguments at positions indicated by the index list using the transformation. Then, The function instantiates the operation with the modified argument list.

<pre><code>   Operation
-> Transformation
-> I<sub>0</sub>, I<sub>1</sub>, ..., I<sub>n</sub>
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>m</sub>
-> Operation
   <
                    Arg<sub>0</sub>,
                    Arg<sub>1</sub>,
                     &vellip;
       Arg<sub>I<sub>0</sub>-1</sub>, Transformation&lt;Arg<sub>I<sub>0</sub></sub>&gt;::value, Arg<sub>I<sub>0</sub>+1</sub>,
       Arg<sub>I<sub>1</sub>-1</sub>, Transformation&lt;Arg<sub>I<sub>1</sub></sub>&gt;::value, Arg<sub>I<sub>1</sub>+1</sub>,
                     &vellip;
       Arg<sub>I<sub>n</sub>-1</sub>, Transformation&lt;Arg<sub>I<sub>n</sub></sub>&gt;::value, Arg<sub>I<sub>n</sub>+1</sub>,
                     &vellip;
                    Arg<sub>m</sub>
   ></code></pre>

## Type Signature

```Haskell
CognateRemove ::   template<auto...> class...
                -> template<auto...> class...
                -> auto...
                -> template<auto...>
```

## Structure

```C++
template<template<auto...> class>
struct CognateRemove
{
    template<template<auto...> class>
    alias Rail
    {
        template<auto...>
        alias Page
        {
            template<auto...>
            alias Page = RESULT;
        };
    };
};
```

## Examples

We will apply `UnaryMinus` to variables of indices `1, 3, 5` from `0, 1, 2, 3, 4, 5` and invoke `Operation` with the result.

```C++
template<auto I>
struct UnaryMinus
{
    static constexpr auto value
    {-I};
};

template<auto...>
struct Operation;

template<auto...Args>
using Metafunction = CognateModify<Operation>
::Rail<UnaryMinus>
::Page<1, 3, 5>
::Page<Args...>;

using SupposedResult = Operation<0, -1, 2, -3, 4, -5>;

using Result = Metafunction<0, 1, 2, 3, 4, 5>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will implement `CognateModify` by combining `Pagelivore::CognateSegment` and `Omennivore::ModifyValues`.

When provided with a list of ascending indices, `Pagelivore::CognateSegment` will find the differences between the adjacent indices.

<pre><code>   I<sub>0</sub>, I<sub>1</sub>, ..., I<sub>i-1</sub>, I<sub>i</sub>, ..., I<sub>n-1</sub>, I<sub>n</sub>
-> I<sub>0</sub>, I<sub>1</sub>-I<sub>0</sub>, ..., I<sub>i</sub>-I<sub>i-1</sub>, ..., I<sub>n</sub>-I<sub>n-1</sub></code></pre>

Then, we will make `std::index_sequence` of each difference by passing the following helper class template to `Pagelivore::CognateSegment` as the operation.

```C++
template<size_t I, size_t...J>
using Detail_t = Capsule
<std::make_index_sequence<I>, std::make_index_sequence<J-1>...>;
```

We will keep the first index, <code>I<sub>0</sub></code>, since it represents how many variables we must pass to reach the first target position.
We subtract an additional one from the rest since we only need the number of variables separating two targets.

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

template<template<auto...> class Sequence, auto...Variables>
struct Send<Sequence<Variables...>>
{
    template<template<auto...> class Operation>
    struct Detail
    {
        using type = Operation<Variables...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = Detail<Agreements...>::type;
};

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
template<template<auto...> class Operation>
struct CognateModify
{
    template<template<auto...> class Hormone>
    struct ProtoRail
    {
        template<size_t I, size_t...J>
        using Detail_t = Capsule<std::make_index_sequence<I>, std::make_index_sequence<J-1>...>;

        template<size_t...I>
        struct ProtoPage
        {
            template<auto...Variables>
            using Page = Send
            <
                typename Send
                <
                    typename CognateSegment<Detail_t>
                    ::template Page<I...>
                >::template Road<ModifyValues>
                ::template ProtoRail<Hormone>
                ::template Page<Variables...>
            >
            ::template Rail<Operation>;
        };

        template<auto...Agreements>
        using Page = ProtoPage<Agreements...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};
```

[Run this snippet on Godbolt.](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIIEaZqQADqgKhE4MHt6%2BehlZjgLhkTEs8YlmABypdpgOOUIETMQEeT5%2BQbaY9iUMLW0EZdFxCUkptq3tnQVc08OjFVUgtWYAlLaoXsTI7BzmgRHI3lgA1CaBbl6OtIQAnlfYJhoAgkcnZ5iX18gKBHQWCoz1eHzMxwYpy8FyubgIDzSmAA%2BgRiExCApQe8wQB6ABUhPx52wqgIrgAYsRZOcifjcWDySw0gZyXCEUjmGwAHS87FvAHELwOElkynUwSXADsVilABErlYce8mSymGzrqrWZg4UxbqhedznudTkwFApzkJMABHLyMfakc56oiGgBqbTwTFi9CxgRe70FwoIovJDHQVNkcKttvtOuu7uInu9mAUhtBfrBJhlYPOufOWvVcbczoNvKimAA7gmkz7%2BXnzl4skZzsomMAflc5ZabXaoUXy1WPV6fYbHdXhym0xnAkqPvLFZn3gSiecALICVBEBgPWlEhkqzDM7W6/XncfJ/mBkXrhibgRPHEy84A9V4ZAmgQAzCqNLEJ2ngA3MQ7WlCxz3oLMFRnaUoNnPE6RbYhMBoVRd0Jfc3gLDV4URRhWEwR0sgALxRAh%2BTQPs0mDZQkJQ34uzRO0F2VN5l0JS0EFuAh6DQ%2BlGUPNVsJLKd/QFRiRSETiCG4uM4KXBD13wKgHndbwU14jCsKLDk8J5PkMwDcTg0UvBlNUu0LSzWVYMXViEIsM0fmLJQNP4o9CxPF1eQASUvIy1wwUyVOAlM4QBdAQBACIsFUZElBjPs4W8kT%2BSsnM8y09kBOPa5hP07ATQMc1zgAeSRdEBjrPMr2o6kiAAJQxWh0tzNL3nretMvajrWuuFqerzXFcXOAB1H5Gw7AA2DQaOQvBVCS5402m/NUHORgfASQtLmmiNBAAFTadsCCxaajW6ga81mlDFr9Q09oIQ7iGOhRSH6y6htGn4KzoWh83RBgFH4YgWHzBAfkiMknWezbBHOt5Ls63CuR%2BJ7jrei7EZ0lHDQc5AAGs0cwE73rzKqepfRx3wor8gL%2BktzjwdAHloCANlJ3NPqiTcfgIBB1R2jRJK4iCVrwC0IhfQRPXJdBzliHc6Ysjnzk%2B780SYBxMDlqhqVBvneey7a0jafDyWIVMVc%2B/aEHFxmLXiUQJvOCtvt%2B84TYJ9aAISRWhwvTH60%2BiIiEFm8723EwzpVgBaY1hekiDA7Jvrk56h6iZOyKlcwUcVfrMqtsq65M%2BzkLnjLtSMYRxHczxwmjuJhRK7tNM09%2BF4Z1sy7Mty/VDTeYAkMPRgSYMmuesbCJgBbNsO0CLssFOHSICZlm4XDrcnmuQfh7YQRfWwES2fZrvMcg5iPkx3v4SNoT%2B/ywqzVTXld8wEeD/Jhsmxnxq6HoxCd4/7NR3kPd%2B%2B8TopTPnOGyLEb55W5N5R0CCABSfkhTXkCmZEKvo3DhUitFb8cUeyxiSiJQigICFhiIfFXs%2Bw4QoKgaJNqE98x320uwzypYjR%2BifsVQuFUchfxqoAhqTV%2BosJ7pw9ucJ86DWGmNb%2BU0Zq0XmrdI%2BfIVqhw2mwCqyiM6NxJtHdu9ZrpqOuL5O6vIDHPSbtXWunMFFu1oH9DWgNgb63BucSGwYjqwwIPDBx%2BZkb4XOBSPAFtHqGPsQ4z6ijnZRxUXNBa1w0FWKNFotawA1qa2pMVA25x8BS3oSY%2BR8tiau0YPmCsa0ZgvUCQ4sxKS3BpI0dyVcTN0D0Ezq9ORjivou3dm4oGJBPEQ3VtDYA/iGm12xqEq0FF0CZxibMkJeluT1x6SrL%2B9ZKZvg/IDckdN/yhzXqzdm7c468ITjJbZqdWGXRsS9FuudeQrMRgI18Ag4ThMiaXEAOcK4ApCu8y6HSgTdMMc3YFak86lNzJ84ubgFkCCWYYl5QKc6goGpsqFLy24PJTp3OShLczwIftyN%2BH8x6iUulPZsrZ2wAKXrQFeZyN4bi3nCKlEDD7Hw2KfWc9YL7QP6jfclXkeEFVNOaAeYDqWH36vS3%2BTUAE0SAeI0Be9R4vylZfEVJK2LEnqo0XYWQfbnGcj8OkmlOF90lUgk53CUGOjmeskqBtiDRjoaFceIiTLYLUrg/BUVqGxVoaQix5DnyUNDTFYhCV6GpOjR68GXqSF9l1albM187W33cvfSVxoZUWkRUI8euz/LqrEXQCRObSVsILTqGR9yglxPGi5RJTT1HLQ0KtdaDBNp6MFk8puiSZmI27RYpa1iJRRNsSdbFPV22DJcf9QwIyQZg3GVDPxECJ09zWT8X5AJll9NVk4pRgsp0tJnRkvtodslOmQHki0BSimtESvCi95SCCVIYNU2pUKD0DRva0w04KumYB6UujqK6fpruGR47d3iJl7tHiBnqbqfgorDGe792HcaawbgurELbaUDT2dTT8RyxBOsZszc5sdjSklDOGOddy3DnuwwFJSwUg1wlTQkb1sYs0VocZFLS5xgGCfKl8hgOyBqSfYbPdscJcWkfxflO5FGerKabap5tDbZHftHVnGFrc3nnrLd864J753HQxX6F5sH6yQchZpizrzuSubzDZhT1xcNooXU57AGLyP6vbhK7hPKdWKdzMqwzzLGistwqvRjHLbxcq1eAuL6Tngn0vsK%2Bcorc1NqyuV%2B13Di1FV1bFz%2B4mEs/2k6qzsojUAyZywqqBcESuGoQsWNICgvA8RtW5QS2kj0pUMhg4Mg3hsQVK3ZFcVowyuQPJVnCnJ8LTbErN7sa20p9dsuKvNCCavP27ImgiTq3T%2B1rH6/yq30BRgzUmtw4FJzafHpIjKebosiT4aWuTxddMxv23KYm4jz71rpc1nSAD/Nwk%2B2J4ldbYFX1Yadzb53eElrldqhrYPEvAIAZD1otauu8pEpJ3C%2BrjtwP%2B/9qbj8S2WtkBiSIZBgnbfWdgegvL0FBgOy964HhBCc4SHCfn3XvvMNh39zb4qWdSqB6VEH5awciPJ9D1hv3J7w9wojjXtm3Ay%2Bp99oVZMGeY86kzpXKuLuytfvKwXjXv7T2k6gJgcs2s68p24erkD8q06RPTjH8EVz7URG%2BMQyhUBpHW5hM7FKhcimj2kWPtB4%2BJ6OxHjbE2uFhIiQCNPwYM9Z5zz8kvZEfsK6a57hHbWbmLa49OXr%2Bfk849PPZ5Bp4gtl/OBX0Q2eE/V8iY6AfdercN%2BbE3heHERZFns%2BmDvkWu%2BF6q8Xif9Ggt98lUJi2g/h9x7H3Zmvk/GiosdIf1HmZ68e7n3T8%2BC/WPikjJqI9Q%2BY8j6r9cW/NOIAOkX8%2BmE2hm4%2BAIl%2Biyq%2B9%2BneRq7OwAzA5IVowAECSe2Om%2BxYqeeOtW6uRcmuYIIiHgiBhYKBEC9%2BM%2BjamBxEpE5wjqNBqIhorS/U2uUOtaMOlBdum2DBASvIAA0vFucEhLaBEupBAGmGYJNOYJNBAHwb8G4OcCggKirIlgABKdKMCojG74Gm6OooIxx8E9bo7r5cGYEIJB6KqYyJaMrzxdjPbshf4n6j5pDcqu46qAHAHu6gHagtYB7%2B4gKB5uEHweEqbqFAiaG15o4sSfTeRhhvjqSiAAZiAKBrTxAezPzayP4zyJIhqELhpvY6jGJY7M685xha7%2BRhFYAAZ54mGK7UF4AkRaH0ENGkRMHCIVEaEBZ4Kxp5EJo%2BpJSOiMJy51qcF1E5R4ItGMH8GCHCFeCiEWjiF8iSHSGyHyGKHKHtyJb%2BFaFtZI4WKDEGFGEsRw6N5G7N6uAOGlHf6Z6/5n5uB6EeF07u71jeHbSdZuDbGRFFbW6d6mHjGEYu6E40pKrNbri0C%2B4L6VGMCuFAmo6h6ySwHr7wHEFIGYABo7hjYF7/Ep5Fo4GXZ7GiREGoAkHkjokUFir25mHYHSq4GqGjICBlEsFVp1Qda67FajFkp5o8F0GESTG8HcjMGbHNafEALzYjZFghosBMD4woi9ERqJTTp%2BgUIRQgBSkynIhykFEMIxxcB3owHHEDQ3w8GGiWJg6Vr7bVqoA2HbIP5SLd6Soo6CH1jWFzwAL2HfomYNqHpXHulekDSelBLem6ROTEmolkGjxwifFOkSZAEqbWlRrabfrCrOaxkGb1Te6i5uDonmS%2BpmkxlSaWnvF0kgwMnRl6aplgHxkfb3ZfZ6oenPFKYVk%2BHvEEnfE9QGrdyGk4kxZBHAlCme42FqoslVkWFHF6424UlK7dmA746Am5ZE4gme6k5taFmaqBGwljkdnRF0g7m7kYTwH7QpgnRJ5Gq7k7kYSZgQhfAwjzw3B3CPCpRYkeRb6mmEH%2BRyDMDEAPAdKDpkZziUFUYHJfg/h/gMyAocExy%2BQTkTlPmFrVaPb7Z7EkoA6vzPSWFvCJarhQ5UBeBQgDCimhmFhkn/4m4BaiSRTvEfltDfkRCNj8iRRVkLDnDBDnD%2BD0UgAjloWbnvCJZCBeBpBFDawmoLbBi7GkVwgaCOg6mOipDnAxwsXSByVsXt62Qk4pgjaiUL5YWtA4V4XlpuCSXnBMWyUKWOjKVRGY5UbIgZHtAQAhoKD4TWW4LCUaWT78WCXoAuWsrPCCocBbC0CcD%2BC8B%2BAcBaCkCoCcBcaWDWDPg7B7AdgQg8CkAECaB%2BVbD4wBBmDchShmCSA1A1D%2BAaAACc/gZgGgk0NQwQAVHAkgvALAEgGgklIVYVEVHAvAzcklKVoVflpAcAsAMAiAIAOwBAaQtw5AlAaAzIdACQUQ%2BEnAqgNQk0Mck0kg5wwAyA74Ug3IZgvA2shAJATMeg/AggIgYg7AUgMgggigKg6g3VpAugCwFY6IaQnAPA/lgVwVqV4VnAJUtwo1wYqAVA5wC1S1K1a1G1Rlkg215wEAHgU19Af4RwXAGwvAXVWgWwEASAk1meCN41EA2N01iQwAUgqQNArKCQzcEAsQX1sQEQ1Fr1vAtNn5DwJUsQ2gjQXVSVk1ECJUDAtADwX1WAsQXgwAxYLizc3AvAWAUpRg4gd1%2BASETQPsEtYV34pq5IDN5AggfQX19wsQ6IX5HgWAX1aIeA9VktpAPsxAsQmQmAkOMtwA9wRgqVWwVABgwACgroeAlYhcIVSVx1wgI%2B510gAd11agX1D1%2Bghgxg1g1g%2BgeAsQzckAWwCeAwEtMc4UnYpg0VlgZVvAqAVtiYWASdbMvQ/QOQLgYYcwfgCwYQEQYwlQEwCwRQ2QAg1dhQmQrdDAyw4wiQCwDQTQAgQwswngXQegA9Aww9Iw9dKwTdiwI9%2BQNd89095QvdEgWwKRuw%2Bw69%2BgH1pAzV%2BdnAwNi1y1q161m1UNZgMNuA%2B1iNiVKNyVLtWw4MPuEwpdGVkggQ3IRVgQUokgGgkguV00Gg/gk0RVu9NVdVSQXA3Ik0XAFVRVNQ8D/gkgXA/gP9k0%2B9X1rV7VIAnVLtvVA1mNQ1f1Y1FA%2BNqA8NM1c1HAbQLAAEUoMcTAT8zYXARV3IMDqt%2BARARdR1sgp14gF1odSg4dd1ugqQT1TAL1kt71HAQVWDd1rVv1I1tw5wgN0M9DjDzDporD7DnDMNcNONCQlwEImwqNBDxDBNuN5DVjEwdDDDMcOjxNRVXAklZN5slN1Nd1TN9NFtPjX5rN7NDgmt3No8vN/NgtmAwtotYgtAEtSV0t0dctYVCtHNeAytX1atyAtwBwSVIcOtd1etBtDwRtBwYVpt5tSVVtNtSg9tST08BDbtbYnt3tFYvtmtAdAjwdl18gIjt1YV4jUdzt2dVglg8did8AKdVEOQ6dmdC8Iz1ged4VhdTMKYkzZdaTzgEArg7dtdYYPdjdfd6QndAwuzxzxQOQBzqw/dfQmzgwMwHQo98wGzg99zSwM9a9/dDzZzL47QVzTdG9cV29yNED8jB931HAGjDj2jBgujHD3IfaEAN9PDJjgQyN5j3VAqpAL9WAiQpd1VtVpA9VgQ7DADUo6DUoUogQgDkgK1Cw4LODtgeDj9mLhD8AxDw1/1eNtjxAs1bAnAdDYNLACgAE74AEbD3I2oAIu13DB1EUCwnTQdEgIdsgYd/TOgSQpAkj0jb1oLn1ijP1pDANQNgrq1wror5w4r7DUrwYsNlDRjd9gQgQD9aNPVlj9rhN3LHrCNAKyAAlyIVryINr1lIMK1fAdAHjlAXjYV/jAtfjdNATbNHNITlDPNfNcbKTUTItYtcTmtiTstZTUtohStazd1WTOTmt%2BT1VYVRT1FpTJtiYlTvA1TttdTstDTrLTTHtXtPtnIHT/DSrQjqrfTEdmrsLMdOdNgetJdUzadnAuI%2BCCzudLVKzxd6zE9Fd2zVdTzS9ddq9hzHdFzbdO7h7Xd/zRzG7Q93zJ7Nz5dV77z%2B71zy9PzDz57O9m98VO91VYL2DR9pr5w5rYrErNr19srjr6LLL6Nz9mAr9eLsjhL9VZg7DTr/ghVqDjVTrUoFVCjLVnAuD%2BDmL6VIAkgUo215LXAUgRVZLP9XAUoEDgQ%2BruHbVkHaVEDO1OHh9zHrrWLVtWQzgkgQAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/descend/pagelivore/cognate_modify.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/cognate_modify.test.hpp)
