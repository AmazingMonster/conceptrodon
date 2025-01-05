<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Stockivore::KindredRepack`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#stockivore-kindred-repack">To Index</a></p>

## Description

`Stockivore::KindredRepack` accepts a list of packed stockrooms and returns a function.
When invoked by an operation, the function concatenates the packed stockrooms and instantiates the operation with the result.

<pre><code>  Stoc<sub><i>0</i></sub>&lt;Seqs<sub><i>0</i></sub>...&gt;,Stoc<sub><i>1</i></sub>&lt;Seqs<sub><i>1</i></sub>...&gt;, ...,Stoc<sub><i>n</i></sub>&lt;Seqs<sub><i>n</i></sub>...&gt;
-> Oper
-> Oper&lt;Seqs<sub><i>0</i></sub>..., Seqs<sub><i>1</i></sub>..., ..., Seqs<sub><i>n</i></sub>...></code></pre>

## Type Signature

```Haskell
KindredRepack
 :: typename... 
 -> template<template<auto...> class...>
```

## Structure

```C++
template<typename...>
struct KindredRepack
{
    template<template<template<auto...> class...> class>
    alias Sail = RESULT;
};
```

## Examples

Here, we first concatenate `Stockroom_0<Seq_0>`,  `Stockroom_1<Seq_1, Seq_2>` and `Stockroom_2<Seq_3>`. Then we pack the result into `Stockroom`:

```C++
/**** NewVessel ****/
template<template<auto...> class...>
struct NewVessel;

/**** Vessels ****/
template<template<auto...> class...>
struct Stockroom_0;

template<template<auto...> class...>
struct Stockroom_1;

template<template<auto...> class...>
struct Stockroom_2;

/**** Items ****/
template<auto...>
struct Seq_0;

template<auto...>
struct Seq_1;

template<auto...>
struct Seq_2;

template<auto...>
struct Seq_3;

/**** SupposedResult ****/
using SupposedResult = NewVessel<Seq_0, Seq_1, Seq_2, Seq_3>;

/**** Result ****/
using Result = KindredRepack
<
    Stockroom_0<Seq_0>, 
    Stockroom_1<Seq_1, Seq_2>,
    Stockroom_2<Seq_3>
>::Sail<NewVessel>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Stockivore::KindredRepack` is implemented similarly to [`Stockivore::TypicalPaste`](./typical_paste.doc.md). Intermediate results are kept in `Carrier`. After all sequences are collected, the `Operation` will be invoked.

A simplified version will be as follows:

```C++
template<template<auto...> class...>
struct Carrier;

template<typename...>
struct KindredRepack {};

// Base Case:

template<template<template<auto...> class...> class Stockroom, template<auto...> class...Sequences>
struct KindredRepack<Stockroom<Sequences...>>
{
    template<template<template<auto...> class...> class Operation>
    struct Detail
    {
        using type = Operation<Sequences...>;
    };

    template<template<template<auto...> class...> class...Agreements>
    using Sail = Detail<Agreements...>::type;
};

// Recursive Case:

template
<
    template<template<auto...> class...> class StockroomA,
    template<template<auto...> class...> class StockroomB,
    template<auto...> class...SequenceAs, 
    template<auto...> class...SequenceBs,
    typename...Others
>
struct KindredRepack<StockroomA<SequenceAs...>, StockroomB<SequenceBs...>, Others...>
{
    template<template<template<auto...> class...> class Operation>
    struct Detail
    {
        using type = KindredRepack
        <
            Carrier<SequenceAs..., SequenceBs...>,
            Others...
        >::template Sail<Operation>;
    };

    template<template<template<auto...> class...> class...Agreements>
    using Sail = Detail<Agreements...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxBIaAKykAA6oCoRODB7evnrJqY4CQSHhLFExXPG2mPb5DEIETMQEmT5%2BXJXV6XUNBIVhkdGxCQr1jc3ZbcPdvcWlgwCUtqhexMjsHAD0AFTbO7t7%2B5vrJhoAgls7ANQAIpiJrozIeJgKF7tHp%2BcHX3vvJ8dnuwubgaxCexFeO1%2BBEwLESBmhJgAzG5obD4ZgkcCvEQAHR4pHYC7IAwKBR4nEE/7DYheBxAkFgpFWU7/T7fdnbX5si4ASTRMMY9RqEM5rI54sO/zFlwA0sF0MRMOgAEq3JjIADWIslp1RcKYCORBAAnndmGxyZTTtTaQQLnKGAqlarEuqtSYAOxWD1XJlSj7rC4WJhKelKED%2Bk569GY6MGjFGmH6w1Y3H4xGE4khsnpzMkl51VCa4ioVAsUgXOMppjY1CWjNE/PkoSYACOXgezytJxtdIdTpVas1mMLxdLLBHbY7DFWOYpGe7nuZJwuq8rSZjibR8djG53yJrafneez9ZPpIuAHk7sQDelu2uLr27Td6nR/o%2Blx/H2uvKkjJWpqYBcSJXFeN53gIk7tp2c6Uoiy6fj6fosqcj5VgmKJ7imGGYoeda5o2p6EVmpLkicwCKgKggKA%2Bv7/sAFxCEwdAgYiYGvixtCYhRVFsDRZ4gCAJp3ChfzIQhkbrIGqrIMsqQAG7AcC4aRrhLLIt%2Bq64VuyaYfhZ5EWRJH5kxRBjmWJykFp67bjh2H6bWhmkXBDYuWZRYaiWZY2DZOmpgRx5GXOLYwTOmA9hWfkOXhTkmcROKhdOqwWAo1loWuImMKwmDkpeBAINEtEadgVIEDSfbyoqg6usOyKjl545/PVU6dj2Z4Vg13ksFYLVhSlrnYBW%2BWFcQg1Sl60V2Zh/n%2BQZ8XGUF7nXtEkEMHRq7PtcmBvtxGWrl%2B%2B0/n%2BwSMVlbFgf21Uum6NmfppR0/muwLEKC0TQclEVzp1rXhalHV3U9V4FUVlqPWuBJCRhTFcZiK23jU8GIRDEnLlNem7tNmMYwecVLU2C1zrxmDUQQtELkdJ0AcxrGgdtu08ZRJP8WTgnCUBYmer6kmoQCEqQtK2wXNgqisHCwFvIL/O/FKZiIsExJeFgbFuGg4WJGTi4fICoSYAA7gAas8djalCMW6ZuAXOQTx5lRVdq64bxtVJz2uXEbpJVC8ku6ubWFY7jR4EsFZ527aHkWSwAD6Giu1GftzXjwcuaH1rleHXXjlHXBx7NfvzfjCXdltmdllHZhx9yPKot7Au%2BwHVu5mHdKhTHuf50nFM9unLdttn7cNwXxc93arcVzzfz1zjje22n9tMX3iKV4CQheIkuTOs8Xi0HaPsnFTjGr%2BvKSbwo292nTjse3Y0Exz9rbZ/f5dP0vC4T1LFyqmfO%2Bm/8B%2Bf1vH%2BdMrqb1qhqKUD0VxrlLtHWOfU24ZiikdGB/d4FtAXg/ceQ0bIoPHm4Vur9SolSEjTbiyIr7OzIaVd%2BbshYABVni7zrt3O8yAo7ZmiAQCAwx0BCQUDldh5M3Bf3Pp1NeG9BzfwIASOYccOALFoJwOIvA/AcC0KQVAnA3DWGsE%2BJYKxgLmERDwUgBBNDyIWBqEAcRJA4g0AADjMGYAAnM4rgcQHH2K4B6D00hFEcEkLwFgsQNCkFUeozRHBeAKBAKEsxaj5GkDgLAGAiAQBLAIIkbE5BKBoFhHQaIoQcqcFUPYgAbAAWjKZIC4wBkDIAuFIHEZheBKkICQPAvC2j8EECIMQ7ApAyEEIoFQ6gEmkF0G0PWt5EicB4AopRKjzEaM4JebEWS7SoCoBcUplTqm1PqY02xZgLgQA8Pk%2Bg4IjFcDmLweJWgFgQCQHkxIBSyAUAgC8t5IBgBSDMHwOg0IxqUAiMsiIwQGjGjmbwcFzBiDGkvBEbQmAHDQtIHklml4GC0CheMrAEQvDAGBLQWgMTuC8CwCwQwwBxB4rwIqBweAlJkvUZgVQKLsRrBMcEaE/j1G0DwBEW88KPBYGWeVPAwTyWkCUsQCIJ8bhUqMAKow5iFhUAMMABQBsnh6xWqokxPThCiHEIMo1Iy1DLMmfoalKAdGWH0IKmJkAFioA1ukMlFSeGgVMJYawZgImytBFgZ1EAFh2BRTUFwjoxitFIIEYIfQSgDDaLkNIAhY05BSOmhg0x%2BhlHaJGzoIwmieBaHoCNjKBBdEaHm5NBbJijDLeMWwJa62zBuYsZYqwJALI4MosJyzIk7PKVUmpdSGlNJORAXA7SrlyxuXctVCxCpMCwDEMNpArGSERDiZxiJfEaEkGYSQZSNDxDKc4/QnBAmkGCcYnEZSuBlPsc4rxZSbHuP3WUwd4zInRNiaYtVSTUlPPSes7JHyvmXKKWwTgDQWAKQ9BUpgREAJcGcTiLgdjWn4CIMGvQRq%2BmmukOapQlrxm6H%2BdMpgszyV9oHeE3gkS1mZOxBcLZI69k1KzOhzD2GNCnPOa8y5IE5ZmFuUBhJjznllhE9EHJny5PfN478txoSaA7yKiCsFEL4VothZCxFyLUXSoxYKLFOLln4sJcS0laLKXUtpeo/ADLHDMuWWyjl0I0U8qqMsgVQrIWirWOoiVUqTGyvlUoRVTnTrAY1UwLVOr9b6rRURk1AzSOyAtWM9RVGbWqt9VYB1gXQ2uvdQIT13r2LFf9YG6IwbnjwHDVUItzgICuEzW0BNRR81ZryOkbrSRs01HbSmwtVbagluG5WmoNaeiJpmBNxtpashxtW%2BNso4b9E9s7f4xjQ7OBcbHWhxiGGsN2NObO/DYnjGSfuRY0gq712UD7be%2B9mGj0ejiM4nxiJj2nskG0JjKyom2EA49x5oGkAZI2Yp6DhTikcAQ/slgCgFINIUhd9EwxcNzs6YR2QxGstDPkORvLOgQCIlIDRuj8zr39qWX%2B1ZEHNnbNUGjjHWOcfxmGEJ5TomjGIge8BsDiP3m5MFwMTH68o7Y%2BcVHXHBAo6c9I4C7TEBQXjMM/p6VuuEVIsjWi8zghLO4pc5gAlRKxD2elY55VoWKX0qLR58ZXm5I%2BelX5vlvBAvCuNCF8VoIIu8CiwqmEcXVXSb4Jq7Vuq0vSoy/0iQ2XhkU6tdTwrxh7U2DKy1jRlWGBkvWDwu1frLABuY0GzpzWXWTajZ1mNza429aTR2kbg2M0t4GzmrbFa2tTYW7Nwf8221Lf6xMGbPep9TAn/W3tXaDGL4O8ziJx21cXHR5ji4CucTK%2Bu3hkgd3F1SYeSuzAa6Bibv8R9kALicSIkRHEDxwPz1P49C%2B396/wcxLicurdEASQOIPdbxD0c9exSQNxLgRxMwH9fxRENfZjTgJdaTPtFpb/ZA8HKHBYWVVIZwSQIAA%3D%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/roadrivore/kindred_repack/implementation.hpp)
- [Source code](../../../../conceptrodon/stockivore/kindred_repack.hpp)
- [Unit test](../../../../tests/unit/metafunctions/stockivore/kindred_repack.test.hpp)
