<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::KindredClassicFoldLeft`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-kindred-classic-fold-left">To Index</a></p>

## Description

`Typelivore::KindredClassicFoldLeft` accepts a list of elements.
Its first layer accepts an initiator and returns a function.
When invoked by an operation, the function left-folds the list using the operation and the initiator.
The type result of the operation is used for continuation.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, E<sub>2</sub>, ..., E<sub>n</sub>
-> Init
-> Oper
-> Oper&lt;
   Oper&lt;
      &vellip;
   Oper&lt;
   Oper&lt;
       Init, E<sub>0</sub>
   &gt;::type, E<sub>1</sub>
   &gt;::type, E<sub>2</sub>
      &vellip;
   &gt;::type, E<sub>n</sub>
   &gt;::type</code></pre>

## Type Signature

```Haskell
KindredClassicFoldLeft
 :: typename...
 -> typename...
 -> template<template<typename...> class...>
```

## Structure

```C++
template<typename...>
struct KindredClassicFoldLeft
{
    template<typename...>
    alias Mold
    {
        template<template<typename...> class>
        alias Road = RESULT;
    };
};
```

## Examples

We will left-fold 1, 3, 4 and 3 using subtraction.
The process can be described as follows:

```C++
   ((1-3)-4)-3
-> (-2-4)-3
-> (-6)-3
-> -9
```

```C++
/**** Subtract ****/
template<typename A, typename B>
struct Subtract
{
    using type
    = std::integral_constant<int, A::value-B::value>;
};

/**** Metafunction ****/
template<typename...Args>
using Metafunction 
= KindredClassicFoldLeft<
    std::integral_constant<int, 3>,
    std::integral_constant<int, 4>,
    std::integral_constant<int, 3>
  >::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult
= std::integral_constant<int, -9>;

/**** Result ****/
using Result = Metafunction<std::integral_constant<int, 1>>
::Road<Subtract>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will implement `KindredClassicFoldLeft` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  1. Left-fold several parameters;
  2. Use the result as the initiator and perform recursion to fold the rest.

Here's a simplified version of it:

```C++
template<typename...Elements>
struct KindredClassicFoldLeft {};

// Base Case:

// Fold once.
template<typename Element>
struct KindredClassicFoldLeft<Element>
{
    template<typename Initiator>
    struct ProtoMold
    {
        template<template<typename...> class Operation>
        struct Detail
        {
            using type 
            = Operation<Initiator, Element>::type;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

// Fold twice.
template<typename First, typename Second>
struct KindredClassicFoldLeft<First, Second>
{
    template<typename Initiator>
    struct ProtoMold
    {
        template<template<typename...> class Operation>
        struct Detail
        {
            using type 
            = Operation<
              typename Operation<
                Initiator, First
              >::type, Second
              >::type;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

// Recursive Case:

// Fold twice, handle the first two parameters,
// and recurse using the rest.
template<typename First, typename Second, typename...Others>
struct KindredClassicFoldLeft<First, Second, Others...>
{
    template<typename Initiator>
    struct ProtoMold
    {
        template<template<typename...> class Operation>
        struct Detail
        {
            using type 
            = KindredClassicFoldLeft<Others...>
            ::template Mold<
                typename Operation<
                typename Operation<
                    Initiator, First
                >::type, Second
                >::type
            >::template Road<Operation>;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxBJm0gAOqAqETgwe3r56icmOAkEh4SxRMVxxtpj2uQxCBEzEBOk%2Bflzllak1dQT5YZHRsdIKtfWNmS2Dnd2Fxf0AlLaoXsTI7BwA9ABUm1vbO7tbqyYaAIIbWwDUAJIs8fRsgkxVZ9sHx6d773svR4dHBJjXBj%2BJgAzG4CABPeKMViYAB08Owt0YBAUIOwP0GxC8DjOAGlguhiJh3AYFMlkAAxTzoAKYKgEM4mADsViZABEQVZjj9VqszhYmEozm5Bewfjy%2BVTaOgzgJlrCfn8AQ9MCCwZDoWwzoj/si0RiCFicfiGITiW5SeSpTS6QQ1Tq7nbgejuSyfmcPWclTcVWqIVDmFqLgwUg8SPrjp6zpjsQzlMRUEQALLU92e5lco5RqPewGq0G530FjWBuHwtFnZCWs4AeShxAeqQjWezHpjOLZmFqdDTrYzvdbnq8ySMXo1jMjg6jILZtfrjYEauDoaIZG1SMEaJAIH9%2BczU%2BZHOBmYHOf%2BPqBBfPeb9JZh8IVzsrlofR2ARN1glRztPQ5HwDOAAlVAmBlGczk7btaDVN8P0dBQHy3HcNU5AdD1Q7lJw9QtL3VAN73hWDME/FFmyjYdggAlNpUZYFZ3jRNUGo9AYPfYj4MQn9j3FdkMO%2BV5JWpL0AHc8HlRVryLPDNUwM4KTwYhBlIMd8K1IRMDQU1m3bBkTTNElBStalaXpNV5MUghlPUzSWJ/V1909HD82k0tLhDRww2IMjPR0s4GOTVMsMZN0grPZVcKc29VLLR9sGfQy52iBcGG81tfMgpge1C9MQpbKcPQo0ddwnPL8vAuskqqNVfynXdXIqhsqtBGr8uXDzV2U8zBhavtnW3XcrI0gQWOyg8%2BuQqE%2BIPXjuMw0qwovZzIuLaLOLiqtDNfNiSO/F15r/SigJAsC6IgrtMug0EiJ2tb%2BpQ2bSvQh6B2WlyCNha74NSs5CqooTwP8pjUyu7aOPLLiTxmk8BKAjTFmSAA3WSRSUEBxRh60RLEzBlIQQx0HoL0EFkmgLJE1AzniOoYT%2BRTSAlM58bOIlkHh2TfqJ2SiUGBVjleuqYTkhSlJUmSzms4blIFtgHxrAhicU7TDVjPECSJAyyTE60TKdNwuss8WhtNZS5YVhDwb2/sgv5u8g3cvBPO%2B3zAeYtDctqySIs9pbbZiisNrJRLGqbOz9rbZWO3OrKw%2BChz8p%2B/9RZK%2BOPXAvT1YtQyteM201VN6JzdinrPX672zld5rRvy6XZIa5Lqqr2rfaD%2BvK5jlO3JXEhOuFu1G8HJCBsNmzi967A7sm/vU/GpyjtAvP5ya9EHumo9oZj/nvaimS1visktrg5FdpajngNA2jZwynsQcPr9bomvc3bX9HSpt1bCNBo/vo55iL78hMArSlYrfFEa0%2BJPXXm8D4OwvhQO1KoVgNxZLPB5NAz4L9zDAmCFWLwWBaLSQAPqGkyqRUOmDsHeDwWqTSyx4ikMtq8bY4svARGITiFBfMt4rTFkcKWzcrCh18kIFhbC%2B7fHdgdIqKEgrgUGOgbcwQ/jvjEAQzS4xNygkUcpI424EZiC8JgAAtBYXR%2Bj8zL0hs/OacCkznSoF4BgDhUhPH2BJcKPt34fWIMAY%2Bxwf52IcU4gQJU05q3NJabO0odYN1KnIhRghMDKNoKogQ6jdZaLOMCNE9MgpxJAIoxJDZklqNqBotwGTJDZIHHkgpSSUkMDSWqDJWTQ7T3HiACubgjjeMLvqZ6jDzjCPiNkYkgFMAKC8LQBkHCjgcyGSM9AYyJlTPFKdGpCS6klMMOkwQylDEAE4%2BmQKYUsyZ0zXF%2BMTqcqZf9bG1HsY4pqbh1lKKKfUxpmjdlnC4H0va24z62TcMI1hDYHBHJfnAgAKuM85mwvjjEcMgAhhlogEAgHkhQMJkXfjcNcg28ykijPGWctEMw%2BIcDmLQTgABWXgfgOBaFIKgTgbhrDWGjAsJYslME8FIAQTQFK5gAGsQDUskLCDQAAOMwZh9n7K4NSqVkquBMiZNIKlHBJC8BYBIDQGhSD0sZcyjgvAFAgH1fyhlFLSBwFgDARAIAFgEHiF4SyFAIBoGuHQaIoQYScFUJKgAbIYwNkgzjAGQMgb54qzC8GJIQEgeB5EtH4IIEQYh2BSBkIIRQKh1BWtILoFowkGzxE4DwSlNK6UCqZZwGsrqXUMlQFQM4Abg2hvDZG6NsIzBnAgB4L19BiCMjMMCLgMxeCWq0HMCASBPXxG9WQd187F0gGAFIMwfA6C0zNRACINaIjBDqOCctvBD3MGIOCGsERtAaUtbyz1joawMFoCegtWAIheGACKWgtAzXcF4FgFghhgDiHfQpO9eAkb/sZZgVQcM/invIAkjVjLaB4AiA2S9HgsA1sNHgHVAHSBI2IBEQlnZgNGHQ0YAVcwqAGB8QANTwJgYSFV6W8tTcIUQ4gs1cdzWoGtRb9AgZQGyyw%2BgMNmsgHMVAdDUj/sMXImcphLDWDMEakjxAk3jPgHMOwkHnAQFcCMZopBAjBB6EUPoLRsgpAEKZrISR7MMEmL0EorRDPVCGA0TwTQ9AGaCd5iYlmpg2dsD5xzYwfNuesyUfTnLlgSErRwWlBqa3GtbUGkNYaI1RqkD2vtuAE3Dp5ROvltG5jE1An0CAwqQCSGBLCfZwI1UaEkHEQNerqWBv2foTgWrSA6rHbCQNXBA2Sv2cqwNYqFUtcDelgtxrTXmoq1amd9rZ2Ooba68glAV1Dt9WwTgdQWAIyZIYpg8VRxcH2bCLgEq434FXEmvQXH028ekPxpQgmC26E3SWpgZaAMpbS4a3gxr63OtdbKFtbacvXYArd%2B7Eq%2B0DoXUOkdwIzDlandarbB3oh7Y9agQdfQNpGFu1wfVNApkF0oPugt57j1IeZ5e69t6HBIcfciZ9r6a0fq/T%2Bv9SGgMgbA4y/ALNHDQZrXBhDKxeUFNQ7wdDmHj04ZWIy/DhHeUkbI0oCj4vKK0b4AxhQzHWPsaQ%2B9njmavuyAE/mxl/2RM0dU1YCTavpN1aZfJ1JnAlMEFsmyD36nNPRG01gH3%2BmKheZcKaKL5nTSxemLZ5zVQk92aqKn8LgWqgdGGH50YnmguF66KF9zAXIvF7M%2BMeouf4vzEWEl8d/XUvVqW5wLL7aw0U6R3dh7GgivPZIFj8dk7KukGq1gGIvuNWDeG3d9rTJqX7NVcCDrkhQ0tHB7Wk1thVt442/ALbTrG3E8J8QI7KxTsdpYAoBGUaEbI7zIMJ7JXXsptkB9%2B32b5A/bO46AgDAikCA7A4Vrt5g4ZZ1o7ZNpw736P7P6v4qiDBo6k4Y7RBY7Ai46m4E4YGLqX4EFDogBP7DIEIv77IEJv4EAEKqChpbp06KQM4HpHqXqs5sFXo3p3rc6k5PovpvqS6YCfrfpiAi5EZi5UZa6AYQZOKy4Fry6syIZEbK41pq5Ybgia54baa668D67kb/DG40brZm5MBMYsZsYBg24/524SAO45qAFCYgFu7GDiY2De56Z%2B5VD/qrBxJh6WAaYQ5aY6Yx6l5VAJ7uC17%2BAp6V5xZOY5CpBZ4Z6pCN4BZx5l414ZB17pEF4xaxFp4RadBJ714V4FBV5t4KCJaZqg6d5Grd70FhoP5P5nCUGwg0Ej4lbj64HrZVaYA1Zz4paL4gCyqwjAjAjUqKqSDU4aBjFMgTaLZ1EH5moWpT4iqSDUrNYqpMh6qSqSDypcDSpmALYarAi1EQ6cCT49Ht6xoLHnEH7H5zAkbJDOCSBAA%3D)$Done$

## Links

- [source code](../../../../conceptrodon/typelivore/kindred_classic_fold_left.hpp)
- [unit test](../../../../tests/unit/metafunctions/typelivore/kindred_classic_fold_left.test.hpp)
