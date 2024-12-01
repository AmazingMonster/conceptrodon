<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Stockivore::KindredRepack`

<p style='text-align: right;'><a href="../../../index.md#list-modifications-5">To Index</a></p>

## Description

`Stockivore::KindredRepack` accepts a list of packed stockrooms and returns a function.
When invoked by an operation, the function concatenates the packed stockrooms and instantiates the operation with the result.

<pre><code>  Stockroom<sub><i>0</i></sub>&lt;Seqs<sub><i>0</i></sub>...&gt;,Stockroom<sub><i>1</i></sub>&lt;Seqs<sub><i>1</i></sub>...&gt;, ...,Stockroom<sub><i>n</i></sub>&lt;Seqs<sub><i>n</i></sub>...&gt;
-> Operation
-> Operation&lt;Seqs<sub><i>0</i></sub>..., Seqs<sub><i>1</i></sub>..., ..., Seqs<sub><i>n</i></sub>...></code></pre>

## Type Signature

```Haskell
KindredRepack ::   typename... 
         -> template<template<auto...> class...>
```

## Structure

```C++
template<typename...>
struct KindredRepack
{
    template<template<template<auto...> class...> class>
    alias Sail = RESULT;

    template<template<template<auto...> class...> class>
    using UniSail = RESULT;
};
```

## Examples

Here, we first concatenate `Stockroom_0<Seq_0>`,  `Stockroom_1<Seq_1, Seq_2>` and `Stockroom_2<Seq_3>`. Then we pack the result into `Stockroom`:

```C++
template<template<auto...> class...>
struct Stockroom;

template<template<auto...> class...>
struct Stockroom_0;

template<template<auto...> class...>
struct Stockroom_1;

template<template<auto...> class...>
struct Stockroom_2;

template<auto...>
struct Seq_0;

template<auto...>
struct Seq_1;

template<auto...>
struct Seq_2;

template<auto...>
struct Seq_3;

using SupposedResult = Stockroom<Seq_0, Seq_1, Seq_2, Seq_3>;

using Result = KindredRepack
<
    Stockroom_0<Seq_0>, 
    Stockroom_1<Seq_1, Seq_2>,
    Stockroom_2<Seq_3>
>::Sail<Stockroom>;

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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIAAcAOykAA6oCoRODB7evgHBmdmOAuGRMSzxiam2mPZlDEIETMQE%2BT5%2BQfWNuS1tBBXRcQnJaQqt7Z2FPZODw1U14wCUtqhexMjsHASYLOkGeyaBbnsHR5gnbkxeRAB0jyfYANTIBgoKj/fPJhoAgpNiF4HC8bsRiHgEicrAC/v9zocmMdTgQAJ7pRisTDfX4AoEgggvADSEXQxEw6AASph0kxkABrF4mFJWFIAERh8PhAHoeS8LEwlGChexuQDEZdrpLkVdUfskSibndULjAq93kKvk91W8PgoXi1UIziKhUCxSC8ZUrbg8dRr9d8hJgAI5eRjbBR4wEEYGg0kMcmUml0xnXI0ms0scOu90MT1q7Delmw/4vdNWhVS%2BUXWXSrN50621X2vVaxNlz4vADymOIyNy3ozLwJoPZmFadHhzZT3ebGa82SMVoxmGZgXZNbrDYEMbdHsw2p%2B6q5AJ7HNX/z76etcrOBaVu%2BuxYrms%2Bp8dj3%2BwAp%2B0YBC9K7XA6HwENTDo48n7c7tGu19vNhBCXZ4QBAdFMU3FlOUCVNeX5GlkE2bIADcxxuJQQHFBEDyuOFTm3TNc0PXDjxVC9y1LM8DQjBlTXNf5SEIo8c0VPcTyoy9lwdLVDSISNzRsZjSKLcjOMo%2B5nXneNMEBS1hOI9ixO4yslykuNtgsBQmOfHdR2YNhvmrAgEASL18KTfFfUJEkyQpalaXpBlw34uioy3U51IXQFE0tWj6JYKxPNjBctN8msTLMxNuVZBS2PzRSEvi0S7RU6iKKrWsEhnBgmwzVsiR/D8/105lYtK5tBwiN8ILHE5JwDIMHNDZyKoza5CP7DNwUhaFguk7YfMePyQpksL7R0tMuv7YzTOIEC2vTUDwNw98u1OLL6yaX5YMI6CoNKlj90S1js2VVLnlUjKlwAzA72AvL0yq4chGKr8XiK9a3Fu%2B6H0TMDaqgjddrhAEeQAKkhqHoZ5XkoYAFWwIR4ah2GwehjHwbRrc4TMQIIneLwsHHNw0Bk9IH2TCUROO5LzpLNKuO9Aq%2BONNzzQOnCTtps6OMZiTmes0F/KjAB9DROaOo6%2Bcu9L7XhFmRfNUWuElmnpeU2WmafH0/SJJWWFFsw1e5mWdcV11xZNumzcs3WbKklXrd5zXzaF/XLeNkGca5m3Xbti2XVFwJOeet8hC8dISmDRcvFoIl6tZgTo368WRqDrh06NrOQ5Xb34TDl4aQUOOE4nWzA3skMnO5AjSoNq3U4l9V5Pr1yAqd1PM8NT3nkm5sG69txHdzu3lter6DZ2uCrIbZBRa1BICAgSZ0DAhRsQXx83GL0u/Mj6OHJL%2BPnhWGEODWWhOH8Xg/A4LRSFQTg3GsawWw2LY6rxnhSAITQL7WAyAIkh7gaEkFwFIgQND%2BA0GYAAbHAswSQkj6E4JIXgLAJAaA0KQO%2BD8n4cF4AoEAOC/73wvqQOAsAYCIBABsAg6Q7jkEoGgA4dAEhRGxJwVQSQ4EAFo4GSBeMAZAyAXhSHuGYXglJCAkDwGvTO/BBAiDEOwKQMhBCKBUOochpBdCZwAO71nSJwHgl9r633/o/Tg1Y7iMKJKgKgLweH8MEcI0R4iQFmBeBADwbD6DEGZN/FYvAyFaDWBAJArD0jsLIBQCA0TYkgGAFIMwfA6B7HmpQWIVjYgRDaGiUxvA8nMGIGiassRtCYAcEU0grCgIEGrAwWghTdFYFiF4YANxaC0GIdwXgWAWCGGAOINpeAKQODwGhPpD9MCqGqXcHYP8Ih7Cvro2geBYj1jKR4LAVjfR4Ewf00gaFiCxCyJgdsQyjAbKMP/NYVADDAAUAANShAYrKd8f5KOEKIcQ6iflaLUFY/R%2BhhkoFfpYfQmziGQDWKgCmuQ%2Bl8NXvVUwlhrBmHwacyEWBYUQDWHYapTQXCBhmH4TOYQIgjGqGMTOJQcgCHJXoBlTRFijESJnIlkyBADGmJ4LoehuVND5UMalSw6W2CmB0AVhQuXSvZbSzlhKP7bAkOYjgN9cFWIIc43hAihEiLERI7xEBcCyMCeYQIXAQm/3uWsUyTAsCJAJaQIBkhAj3AAJyBBSJIMBZhJBwOwf4OBXrUEcHQaQTB1r7hwK4HApIXqkgJv8OA/wPq4Hat0QQohJC7XkIiTQyJdC7FMPiYkgJnC2CcDaCwFCKQ%2BFMDLMOLgXr7hcFAdI/ARBcV6B%2BSo/50hAVKGBbo3QaSjFMBMf0jVWq8G8AIbYhhdwXiOJeHWhtTaW1vjbR20BPi/ExICUEwIZhbVhIoSWytCRmEJPNMesYm7G2aiMG2rgOCaDxzMtk3J%2BSym1JKQUipVSanHPqfeJpLSrHtM6d03ptTBnDNGQ/fAEzHDTKsXMhZexakrIaFYjZWyCm7J2A/A5Ryf6nPOUoK5yHqr3L4E8157zPm1IHX8tRw7ZBAp0Q/CdYK7noqsFCoj%2BL4WIoEMi1FE5hOYuxQkXFi54CEoaMS3IpL3CyopSEQMirlj0qyIyvI2mWVGbZeKjlQq1M8uaNK5lXKbMioVZZpVQr7OmflQsVzBmVWbDVTaiN86dWcA3cQetjbm2vt3e2ztGgfHmt7aem1oT7WkEdc6ygGqo0xvbWAlIGaUiQMkIGwRmcF3WMIbYfNl6i3wBLfQ%2Bxd6b3EGrTsOtbiWAKBQmIlCe7LiTG7Ra%2BR/bZCDq4xo%2BQo6%2BM6BAMEKdM6zFBcsTmmxZaHFOI60IrrPWXh9fbQNokviH2xNPYEC9jHr0nYCc167YwetR1Fvt0Wh2F7hcEek79WSIA5N0UBgDxz/vlMqcS2pEHBBQdaahzAHSuliAQ8cpDNyyMDPGepzDujsNIVw8c/DayH5Ee2WiUj%2BzISUd4NRi5dGbkMcLUxpgzy3mYA%2BZiL5vAOOqIkNxzR02QVzcE8YSFNgxMqcfpJhgfSeSrwhRiywWLF04vkcpuFvR1POAgK4Bzun0D6clay3IWv9flB85K4V/QPMFB02b3lLnKhWa8/yy37nvN27c4FhQqq1FzpW/g0LW2Xg7d6/12UkwEs9pIMli7haHWYCdWMV1aycsgDMO2wIgR/AwPAdgtPKRE3Zt91V4hpC0vuv8N6/wSR4FeskF6yBvquDBDWYEH3i7OCpejxGqR%2BfW9Vdq2sU52RnCSCAA%3D)

## Links

- [source code](../../../../conceptrodon/descend/stockivore/kindred_repack.hpp)
- [unit test](../../../../tests/unit/metafunctions/stockivore/kindred_repack.test.hpp)
