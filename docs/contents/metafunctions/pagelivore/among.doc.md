<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::Among`

## Description

`Pagelivore::Among` accepts a list of sequences. Its first layer accepts an index and returns a function.
When invoked, the function instantiates the sequence at the index from the list with its arguments and returns the result.

<pre><code>   ...Sequence<sub><i>i</i></sub>...
-> I
-> Variables...
-> Sequence&lt;Variables...&gt;</code></pre>

## Type Signature

```Haskell
Among ::   template<auto...> class...
        -> auto...
        -> template<auto...>
```

## Structure

```C++
template<template<auto...> class...>
struct Among
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

We will pick the sequence at index `3` out of the list `Seq_0, Seq_1, Seq_2, Seq_3`.

```C++
template<auto...>
struct Seq_0;

template<auto...>
struct Seq_1;

template<auto...>
struct Seq_2;

template<auto...>
struct Seq_3;

template<auto...Args>
using Metafunction
= Among<Seq_0, Seq_1, Seq_2, Seq_3>
::Page<Args...>;

using SupposedResult = Seq_3<0, 1, 2>;

using Result = Metafunction<3>::Page<0, 1, 2>;

static_assert(std::same_as<Result, SupposedResult>);
```

Note that we must instantiate the sequence before the comparison.
This is because the function returned by `Among` is an alias template pointing to the actual sequence in the list.
It is not quite the same as the actual sequence.

```C++
template<template<auto...> class...>
struct Carrier;

// GCC compiles.
// Clang and MSVC fail.
static_assert(std::same_as<
    Carrier<Metafunction<3>:: Page>,
    Carrier<Seq_3>
>);

// Clang and MSVC compile.
// GCC fails.
static_assert(not std::same_as<
    Carrier<Metafunction<3>:: Page>,
    Carrier<Seq_3>
>);
```

However, after instantiation, both of them will converge to the same result.

## Implementation

We will implement `Among` using recursion over the requested index.

- **Base Case:** Handle several small indices directly.
- **Recursive Case:** If the index is small enough, the sequence at the index is returned. Otherwise:
  1. Drop several sequences from the front;
  2. Reduce the requested index by the same amount;
  3. Invoke `Among` by the rest of the list and the first layer by the reduced index.

A simplified version will be as follows:

```C++
template<template<auto...> class...Sequences>
struct Among {};

template<template<auto...> class First>
struct Among<First>
{
    template<size_t I>
    struct ProtoPage {};

    template<size_t I>
    requires (I==0)
    struct ProtoPage<I>
    {
        template<auto...Agreements>
        using Page = First<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

template
<
    template<auto...> class First,
    template<auto...> class Second,
    template<auto...> class...Others
>
struct Among<First, Second, Others...>
{
    template<size_t I>
    struct ProtoPage 
    {
        template<auto...Agreements>
        using Page = Among<Others...>
        ::template ProtoPage<I - 2>
        ::template Page<Agreements...>;
    };

    template<size_t I>
    requires (I==0)
    struct ProtoPage<I>
    {
        template<auto...Agreements>
        using Page = First<Agreements...>;
    };

    template<size_t I>
    requires (I==1)
    struct ProtoPage<I>
    {
        template<auto...Agreements>
        using Page = Second<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCAAbBqkAA6oCoRODB7evnrJqY4CQSHhLFEx8baY9vkMQgRMxASZPn5cFVXptfUEhWGR0XEJCnUNTdmtQ109xaUDAJS2qF7EyOwc5gDMwcjeWADUJutuyEPoWFQH2CYaAIJX1wSYLIkGDwduD08vmG9MXkQAdICLrttkwFApAf8hJgAI5eRgrBQXO5DYheBy7a4sATAfYAdiseIAIgcrDc7h9nkxXodKV8fn9UJDgaDwbsAGJ4YhDZE3VHogiY7FGN6c7kEXm3Al3Xay3Z06nfQ6pABemAA%2BoKAJKSuW7fkY5TEVBEZRMYCYfGEknrMm3G56hU0tyqjXa3Vy4iwrxczAKXYQHXrG1EjSzGVyg2Co0m1Bmi1vIOXB1ykzSlN62VOpVuX4AwHXYBex6MAhI9bJ66ZuVeVJGXbxy0HIkcrk8w6F4tsQQQoEV0kR2Vpm12wfyx5U515pkFouYEs9j2y2vBXGN/bBhvG03mnOd%2BfdsvM/u2u7Dgfkm7Zs%2BHMfXw7T4/YEEGNlioakO8T%2BkPxlPl9gv60JoAw6Cfhm46fIqDL5v8LKvr2/wAPIEAg0RIuS/Z8gQaIYliOKim2BCkLswECGBuwoWh3JPme6ZVnK94ungaqarsSZjlGW6xuuY5pna1ZZt%2B0G/rB%2B4LmWS6Ziu9a8Zu%2BEiocVHobREF6iAIDZtxO4JocWq7AAtLsZhSepmnCQ8Da7m84mHohyKnhB56OfaDFCVBzqumxHEQV6cK%2Bv6gbNs2YacThAraXG1l6VJ/Fjo6Fk5o%2Bs5dqW5aVoJuwyWuu4bi274Sh2c4SfZJ4CamxIXq5CUeTmXnulhbm7H5PpeoFQYhlw4YQVxMY6TmPlNXFamMYlMEzv8tlpaZNZ1jlFp5aRmAgegNnFXZtEuXqzmjhBTHJZN63TY1erZVZC3NpFjZralPabaOlUuXcAD0ABU70fZ9X3PS9n27AAKn6Za7J9P03G9X2Qx9YOuRsWw7E2hwgSsiSSY1FJjaJE2Slx0IwuqGhVRjtXjap1y47C6pcETV6Y7mf59pWFP4yZT20yTWNk8z6rrDT1wQ%2B9rbirs2CqKwzyWqDZ7s5OSUM5NxDAOldxnQAspgdRUF4DAOOkN4tgpwBvHjBMkSbrRLSzZuU7zjUaddHaK6Vlxs9cZ1CF4iS5Jg6AAEp%2Bl4tCCpdJu224CS7BbrMu7tbtzbs/sKIHweburmva7rAhvLb2D29F4ckVHDmxxMjjIOqgHRAQEAnBpCisBqYJvInydm573t%2BwHQcXOGrsC69S0rSLYufJL0PS/cdP7fL8GAVz4UYrmxDEHg0R889z27AA4m4bggqgTx0H6cHg5vbgGPWhjoLsqtCAAanvVBMHQJ/k3UZcV%2BCVc1wQ6B1w3n83hjiXivNehw05MC1jrao2cLgaXOkqbA4EmogNXsQY2NtJQ93XmfC%2BuIr433vnvNAh96Cvw3tvXeuwn50AhCid%2BeBy6VwaBABgJp9S/3/mwQBt4IKoLAW4CBUDM4MFgRWeBDskHAPqKA9BhxQ5YIrL3CwHB5i0E4AAVl4H4DgWhSCoE4G4aw1h9SLGWE2Mw6weCkAIJoVR8wADWIANGSH%2BBoSQXA8TrA0BojQZhYixDMAADiCfoTgkheAsAkBoBIOi9EGI4LwBQIAEi2N0ao0gcBYAwEQCARYBBEh/HIJQEhiQj7EFCA3TgqggmxAMrESQuxgDIGQJHVxZheA%2B0ICQPAf9Wj8EECIMQ7ApAyEEIoFQ6h0mkF0K0AA7sQJgiROA8DUZo7Rdj9GcCQn8QpgpUBUF2DUupDSmktLaf8MwAYPCkOiPsSxXVeBpK0PMCASBSnlOKRAD59AYjACkGYPgdAHjckoBETZERgj1AAJ4rN4JC5gxBoVIQiNoZaaTrEkMPEhBgtBYXTKwBELwwBcy0FoMk7gvAsAsEMMAcQBLfS6wAG5%2Bk2ZgVQy0/irGscEB46jpm0DwBERZSKPBYE2ThPAUTKWkBZcQCIKRMBEkeLSwVRg7HzCoAYJWd9V5zKQokRgcKxnCFEOIUZAz5BKDUJs2Z%2BhaUoGMZYfQQrkmQHmKgVG6QKUGROM2UwlhrBmHiXKleWA3UQHmHYdF6QXCgVGC0UggRgi9BKP0VouQ0gCATTkFIWaGBTD6DEcYlQY0CE6CMTwzQ9DRpERW7oKbpjptsMMRoVaxgtsmI2otEgo1mJWL2sJHAtGkDibwBJRzan1Mac01pUhLkBlwN04g9yrGzCeRq%2BYaEmBYBiJG0gTjJDrH%2BAATnWHiSQ7izCSHiD42IJ6h0RNIFEqx/xYhcFiEEk9QSP0uK4Bos9sRR2bISUklJNiNWZJyW8vJuyikUG%2BQfMpvzKlsE4PUFgTK8QGSYABesXAT3/C4G4zp%2BAiBhr0JaoZ5rpCWomTa6ZuhAULKWXCtZw6NnTISTsgpfxdgHN2BhrDOG8O4gI0Rtx1ykPlNXWYddEH0mvPedJ35Xyfn9CE9h0ERgCNcASDQIO6EwUQqhUi41CKYUorRQ4Y1WLSw4rxZswlxLSXkuNdS1Vqw9H4C9My1l0z2WcoeMa3llRNmCuFTCsVXmnkr2ldYuVCqlDKppUYNVoBFN8G1QoXVmB9WGp0dYqjZqRm0dkPRqZeimP2vVQGqwzqIsRo9V6gQPq/XBjq0GkN0Qw2svdW0MtfgICuBza0ZNRQe0ZrzdUUbSRpvpELWm4tA262ttm7W6o9bFszHGGt9tiaJgNG2%2BmvtSwB1dSHSOsdWyOCCeIJh7DuHtNicI8RjQi6yMkFXY8hTLyt2YB3f0fd/Kn0vsI%2B4vEAG8ReMkNehprRrugdsOB55GSsm5PyXstTKnoiodWBh05LAFBMtaUy8TXwhikeXb0yjshqOlZNRV21IB1ikBY8syl7Grsge2XB/ZhyCeNKJyT3YZPCMU8FBAG5yG7kbHWPJ1HSmUA47IAh9TMQSde3VGL9UEuK73YaUCwzoKIDgumRZszMqLfItRei2zB9sW4vxd5zARKSViDczKjzaWYukB8zGllFK9GBeQFykLggwsCqFSK6F0WJVxeNYlxVKXVWrkg1q80OW9UGqNTK4rwyJBlfGdayrOgWc1eME6mwjX4DNeqBS56tdOuWGDeO0NvS%2Bv7o27G4b8b9v%2BFAsd5bmaZv96m3kBb3als1tLatro63Z%2BbdbUPmte2sgHeX1Pnbp3zGDv5dzrjnA7ssEJ8T0n5PFRDA%2B8u77CvN2kG3buyg7HQcgDMIR9Y6wNG%2BI8TEz/eJP1gND9ElkdUl79D0NFT0NEgl/ET1JAT0vFz0uBWd%2BV1hON4lOAN1FN2MOkgCMCQDFd5g5VUhnBJAgA)

## Links

- [source code](../../../../conceptrodon/pagelivore/among.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/among.test.hpp)
