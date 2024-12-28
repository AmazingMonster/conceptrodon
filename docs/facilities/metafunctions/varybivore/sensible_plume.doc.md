<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::SensiblePlume`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-sensible-plume">To Index</a></p>

## Description

`Varybivore::SensiblePlume` accepts a list of variables.
Its first layer accepts an operation and returns a function.
When invoked by sequences, the function places the variables into the sequences via a process similar to pack expansion;
then, it collects every packed sequence and instantiates the operation with the collection.

Check out **Examples** for more information.

<pre><code>   V
-> Oper
-> Transf<sub>0</sub>, Transf<sub>1</sub>, ..., Transf<sub>n</sub>
-> Oper&lt;Transf<sub>0</sub>&lt;V&gt;, Transf<sub>1</sub>&lt;V&gt;, ..., Transf<sub>n</sub>&lt;V&gt;&gt;</code></pre>

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> Oper
-> Transf
-> Oper&lt;Transf&lt;V<sub>0</sub>&gt;, Transf&lt;V<sub>1</sub>&gt;, ..., Transf&lt;V<sub>n</sub>&gt;&gt;</code></pre>

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> Oper
-> Transf<sub>0</sub>, Transf<sub>1</sub>, ..., Transf<sub>n</sub>
-> Oper&lt;Transf<sub>0</sub>&lt;V<sub>0</sub>&gt;, Transf<sub>1</sub>&lt;V<sub>1</sub>&gt;, ..., Transf<sub>n</sub>&lt;V<sub>n</sub>&gt;&gt;</code></pre>

## Type Signature

```Haskell
SensiblePlume
 :: auto... 
 -> template<typename...> class...
 -> template<template<auto...> class...>
```

## Structure

```C++
template<auto>
struct SensiblePlume
{
    template<template<typename...> class>
    alias Road
    {
        template<template<auto...> class...>
        alias Rail = RESULT;
    };
};
```

```C++
template<auto...>
struct SensiblePlume
{
    template<template<typename...> class>
    alias Road
    {
        template<template<auto...> class>
        alias Rail = RESULT;
    };
};
```

```C++
template<auto...>
struct SensiblePlume
{
    template<template<typename...> class>
    alias Road
    {
        template<template<auto...> class...>
        alias Rail = RESULT;
    };
};
```

## Examples

We will see three examples that present different use cases of `Varybivore::SensiblePlume`:

- We will pack `0` into `ZeroStar`, `OneStar` and `TwoStars`.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
/**** Transformations ****/
template<auto I>
using ZeroStar = std::integral_constant<int, I>;

template<auto I>
using OneStar = std::integral_constant<int, I>*;

template<auto I>
using TwoStars = std::integral_constant<int, I>**;

/**** Operation ****/
template<typename...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation
<
    std::integral_constant<int, 0>,
    std::integral_constant<int, 0>*,
    std::integral_constant<int, 0>**
>;

/**** Result ****/
using Result = SensiblePlume<0>
::Road<Operation>
::Rail<ZeroStar, OneStar, TwoStars>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

- We will use `OneStar` to pack each of `0`, `1`, and `2`.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
/**** SupposedResult ****/
using SupposedResult_1 = Operation
<
    std::integral_constant<int, 0>*,
    std::integral_constant<int, 1>*,
    std::integral_constant<int, 2>*
>;

/**** Result ****/
using Result_1 = SensiblePlume<0, 1, 2>
::Road<Operation>
::Rail<OneStar>;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult_1>);
```

- We will pack `0`, `1`, and `2` into `ZeroStar`, `OneStar`, and `TwoStars` separately.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
/**** SupposedResult ****/
using SupposedResult_2 = Operation
<
    std::integral_constant<int, 0>,
    std::integral_constant<int, 1>*,
    std::integral_constant<int, 2>**
>;

/**** Result ****/
using Result_2 = SensiblePlume<0, 1, 2>
::Road<Operation>
::Rail<ZeroStar, OneStar, TwoStars>;

/**** Test ****/
static_assert(std::same_as<Result_2, SupposedResult_2>);
```

## Implementation

`Varybivore::SensiblePlume` separates cases according to the number of parameters.
The goal is to mimic the behavior of pack expansion in C++:

- If the user only provides one variable, we pack the variable in each sequence separately;

- If the user only provides one sequence, we use the sequence to pack each variable separately;

- Otherwise, the number of variables shall match the number of sequences.
We pack each variable into its corresponding sequence.

Here's the entire implementation:

```C++
template<auto...Variables> 
struct SensibleClassicPlume
{
    template<template<typename...> class Operation>
    struct ProtoRoad
    {
        // Multiple Variables
        // Multiple Sequences
        template<template<auto...> class...Cosmetics>
        struct Detail
        {
            using type = Operation
            <Cosmetics<Variables>...>;
        };

        // Multiple Variables
        // One Sequence
        template<template<auto...> class Cosmetic>
        struct Detail<Cosmetic>
        {
            using type = Operation
            <Cosmetic<Variables>...>;
        };

        template<template<auto...> class...Cosmetics>
        using Rail = Detail<Cosmetics...>::type;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};


template<auto Variable>
struct SensibleClassicPlume<Variable>
{
    template<template<typename...> class Operation>
    struct ProtoRoad
    {
        // One Variable
        // Multiple Sequences
        template<template<auto...> class...Cosmetics>
        using Rail = Operation
        <Cosmetics<Variable>...>;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwA7KSuADJ4DJgAcj4ARpjEEmYapAAOqAqETgwe3r4BwemZjgLhkTEs8YlcybaY9iUMQgRMxAS5Pn5BdQ3Zza0EZdFxCUkpCi1tHfndEwNDFVVjAJS2qF7EyOwcAPQAVAeHR8cnhzsmGgCC%2B4cA1ACSLKn0bIJMjbdH51c3p3%2Bn30uF0uBEwTwMoJMAGY3EwvEQAHRIgBqrTwTFi9AU0OwwImxC8DluQkYmUxKjymGBJkCViutwZt1B4PeVJhzOerOhbgIAE9UoxWJgkQicbdkAYFApbgB5AXEd7ZHHAxm3fGEgi3ZTEVBEABKqCY6FuKsZNLpl1Vqo5ELZPLBnMhMLhiKRYolTClIo8CjYjmQ2KhuPpVoZ6qJABFMC06KbQ%2Ba46HGV5MkYmfzMCaoRHZfLFQJuT6/XgA9zUcR0eTA9gRcqoRakybAhHoRbE9aHbbuTauc74aha0HxZLpUXoyXlSHQ%2BHNVGY7RCxli6Yg%2B2zbS16GUxFgOmBVmc3KEvmGIvfeOV25y5WsTjB7j65umy3H1cnz2nfaWZ%2BXQO3UOPS9JEx39asn23NM9SYOgD1uOdoIXGEQJLBR7xAEA%2BQFVtExpF82ynJlO17L9HTtTDBTYe9h09VCkUuYBiEwMFGAIMCCIg3cDSNWDtV1VAuPQbl6MY5jBFo0VV1fIFm2wt8rg/O1f1ua8MXoSdLhnYlSTwcllEpMs0VUtlg2khtGQU7siM/cjmEo/9sGoqVc2PRp1NVTTeP1Q1jRwjcCI7b8yKsxT%2ByowDxOQ0tV385NU04hDYKPBVXKQpcL0DK9DPJO97Nky11zw6kCIs9lgu7DNbOFezHPE4SmNeVi3NindbgEnidS8o0hIY%2BqWPEus2xkqTgV%2Bf4xr2QFRtuAAxPBiAmW5sFUVhnkzL4RvGzbAWpMwoQiCUvCwLMeQzAB9AgFUINigV2/bvCO7k0AYLZUka6KgR%2BI5bgAFQVBgFH4YgWBPaV1vksq%2ByIB51I424AC0ElQfpiFgiZ0HQiJQQYsRTqeuZBG5THSGhyT8JBCHYX7EmTNhmVImR1GCHRkBMcwbHaFxgR8YIQnBGJ%2B4cT2PLgRKymoYF97Ye%2BgB3JHJmlaEczRjHBDZhUObxloCZhInqYOYXPruJKT0%2BM4RYpmyhXvPELo1ZzkqVYbDYOYkvFSIpMHQPVMAULxaE1MHLlhoQ3Y9r2fb9zVFftk9qRhRNlZZ1X2c5/6tZ5nW%2BduDQcVIBOmZVrH1dT7neYIYmc6DPY84IxPWZTzXDAztxdcr7B9bfUmiuuL7vd9/3TYOQFYb7yPYJJf6dPoPSfDtNvgXQgTuWNlKTMXhDuQRnVkeJunMB3n7ZeRsCnZ7u5vp9gOzauOZ/VOmiEgICBE4UIV74y0f/eJkP3YyT3P4ztgZYBsz6bTGpNL6JInrGiWitegg8JobTAeA7uU0f5hwAQg4ecVXa/yUOHfuBBTpcESnmVync3D52ZvXYujdtYtyzm3auVDC5qxxnQ5uusuCCxrvlMMBck5F3YVzdOZdiZmEFnHB8ZMpqYMDiPCO/tiHj20rpfSMIUi3C4OI9Si9vLLzIY7NeIAoKxhhHvZGA1UFfQvgtQOt8SzvyUG0Z%2BAjX5sHftyABxDv6hz/gQyOxCcTANPqNZBxwIHnwQHNGBy1wRrWvqA8JETrF3HQf4uRiTg5%2BPwd4swpCXJKgoSwwRbCNYiKbmI7OucSk0OEWnSpmdy5aJ4bU5OtCKn0N1hIquQtO7SNSS7TJQ9gQKMIadfJ0cJ5kmnuotwmjtG3B6cYpe5jDEFneuvMxbgt5y1aLvemkxiYyz2fNKxckkk/Uvlgm2ipkBOMfq45m7jMCeJhHk3xeD/6KKIcskJFgOCrFoJwfwvA/AcC0KQVAnBKGWGsGqdYmxMzmChDwUgBBNCAtWAAawCJIBEGgAAcZgzAAE5SVcH8ESwlXBAiBGkMCjgkheAsAkBoFI4LIXQo4LwBQIAUgYohYC0gcBYAwEQCAdYBBUjwnIJQNATw6AJCiEKTgqhCUADYAC0GrJC3GAMgZAWj8VmF4J7QgJA8Do20fwQQIgxDsCkDIQQigVDqCFaQXQ2jpYKlSJwHgQKQVgsxVCzgMp4Qys1KgKgtx1Xat1fqw1xqET5IgB4RV9AUYoq4MsXggqtCrAgEgBVqQlVkAoBAEtZaQDACkGYPgdBQTzUoLEENsQIitF5P63g7bmDEF5DKWI2hMAOG7aQBVDU6a0C7R6rAsQvDAFhLQWgfLuC8CwMDIw4hZ1zRHY4AAbj7ENmBVAjvhNsNFrNGWQtoDpBU/aPBYBDRdPArK12kEPcQWIf8oybuALeowmLVhUAMMABQyI8CYGlkecFaLbXCFEOIJ18HXVqBDV6/QhhjDWGsPoHSfLICrFQK9bIq6tVo0VqYOFlhki8FQJ%2BisWACMQFWHYPd2QXAMHcJ4ToegwgRGGJUUY2iihZAENMPwImMhiYYAsEY1QejsYEMjdoPH8jaLYw4PokxBgCcWMJ2wOmJN6DmG0OTQnqiscRVsCQgaOCgtIJyujnBY2ap1Xqg1RqpAptuBAXAFqs27RzXmoDqwECYCNKMFjpBcWSChAiUlUJ6UaEkGYSQGr2X%2BA1aS/QnBmWkFZaihEGquAasJaSmlGr/CSEpYljVjmQ3ct5fy9FQGRXiqLZKiNsqK1VszSqtgnBWgsH3YELVTBqJpi4KShEXACVmvwEQRjeh4P2qQ9IFDSg0Met0PWn1TA/Vrrsw5pzoaODhulfCW40bXPxr1R6KbM25saF8%2Bm0tmaTS7TMLm1rQrC3FtQBmhIcrK2A/e6MB7taKUpBoP7BIfKICto9b2ztY6Uf9sHcO0d76J0sSnTOyFc6F1LpXWOjdWHt2E93Vpw9q7IUnrPaCMdV6Q23tiPe3kj7tiQpfW%2BtFn7v1KF/RTncbWQNMDAxBqDMGx2rcQ46jbshUPushbtzDgGqNWEsHh2IzGiMka5pwcjTNKM4Zo1yhjVqj2EcU1p5wEBXDGe0fx8o8m9CicaE7tI0nGjmaWBp%2BoSmmhGbU5J23jQVN%2B4M6Z1TeQw8x6j5ZtYGwbM5ty/Z4NHruW3fc5N3c03ZsEt8/5pbn3UU/fzVi0g4XIuJGi4y/LhWZspcCP4UldKoSpfSzVhrWfODNYFW10VEqpWRpB315VqqODDYTSwBQ%2B6jX7oL7aCYC2AtWpW7INbCvnXyC2yrnQIAoSkH24dgN6eTuNbDd1qNMbVCz/n4v5frIFpprB2WsvUIK9D4B0D8t8r39M0QAF93ZTol9SVToV8iF78NtG14cW020O1%2B00ckCB0h090x1cdBB8cQ0idF0xBSd31yct1ud11qcD0j0PUGdkBz1mdVZr1eA2cOcudn0Kw%2BdeABcf0wQRdAM/s%2BBQNwNINoMBRYNeA5cHUJBFcXV990Mj91dsNqMbA2c9coUDd/pOAdhlZNdrBaMoVLcmN4BWNA87c/AHcuMvcXdBN/dvdihsgvcPdshE8TNjCI8Q849nDehlMdMnCNM3DeNfD5g9M3c08FBrNHVjtM8uUXMYDbg58F9bhwCEQoDi9FsSAy9gtfsC0wsIssA687NG8QAyUEQoQoR/AqUat2USjAgyte8oieVbAWtK9lgcUQBJB/AEtaVAh2VCVJAKUuBiUzB6tGUoRIjnN6imi7NTVaixiQs/tVhP1MhnBJAgA)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/sensible_plume/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/sensible_plume.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/sensible_plume.test.hpp)
