<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::Skip`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-skip">To Index</a></p>

## Description

`Pagelivore::Skip` accepts an operation and sinks its *0*th layer to the bottom of the invocation order.

<pre><code>   <i>0</i>th Layer { <i>1</i>st Layer {...Last Layer {***}}}
-> <i>1</i>st Layer {...Last Layer { <i>0</i>th Layer {***}}}</code></pre>

## Type Signature

This function has multiple signatures.

```Haskell
-- Skip to Mold
Skip ::   template<auto...> class... 
       -> typename...
       -> ...
       -> template<auto...>

-- Skip to Page
Skip ::   template<auto...> class... 
       -> auto...
       -> ...
       -> template<auto...>

-- Skip to Road
Skip ::   template<auto...> class... 
       -> template<typename...> class...
       -> ...
       -> template<auto...>

-- Skip to Rail
Skip ::   template<auto...> class... 
       -> template<auto...> class...
       -> ...
       -> template<auto...>

-- Skip to Flow
Skip ::   template<auto...> class... 
       -> template<template<typename...> class...> class...
       -> ...
       -> template<auto...>

-- Skip to Sail
Skip ::   template<auto...> class... 
       -> template<template<auto...> class...> class...
       -> ...
       -> template<auto...>

-- Skip to Snow
Skip ::   template<auto...> class... 
       -> template<template<template<typename...> class...> class...> class...
       -> ...
       -> template<auto...>

-- Skip to Hail
Skip ::   template<auto...> class... 
       -> template<template<template<auto...> class...> class...> class...
       -> ...
       -> template<auto...>

-- Skip to Cool
Skip ::   template<auto...> class... 
       -> template<template<template<template<typename...> class...> class...> class...> class...
       -> ...
       -> template<auto...>

-- Skip to Calm
Skip ::   template<auto...> class... 
       -> template<template<template<template<auto...> class...> class...> class...> class...
       -> ...
       -> template<auto...>

-- Skip to Grit
Skip ::   template<auto...> class... 
       -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
       -> ...
       -> template<auto...>

-- Skip to Will
Skip ::   template<auto...> class... 
       -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
       -> ...
       -> template<auto...>

-- Skip to Glow
Skip ::   template<auto...> class... 
       -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
       -> ...
       -> template<auto...>

-- Skip to Dawn
Skip ::   template<auto...> class... 
       -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
       -> ...
       -> template<auto...>
```

## Structure

```C++
template<template<auto...> class>
struct Skip
{
    struct Commit
    {
        template<auto...>
        alias Page = INITIATION;
    };

    template<typename...>
    alias Mold = RECURSION;

    template<auto...>
    alias Page = RECURSION;

    template<template<typename...> class...>
    alias Road = RECURSION;

    template<template<auto...> class...>
    alias Rail = RECURSION;

    template<template<template<typename...> class...> class...>
    alias Flow = RECURSION;

    template<template<template<auto...> class...> class...>
    alias Sail = RECURSION;

    template<template<template<template<typename...> class...> class...> class...>
    alias Snow = RECURSION;

    template<template<template<template<auto...> class...> class...> class...>
    alias Hail = RECURSION;

    template<template<template<template<template<typename...> class...> class...> class...> class...>
    alias Cool = RECURSION;

    template<template<template<template<template<auto...> class...> class...> class...> class...>
    alias Calm = RECURSION;

    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
    alias Grit = RECURSION;

    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
    alias Will = RECURSION;

    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
    alias Glow = RECURSION;

    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
    alias Dawn = RECURSION;
};
```

## Examples

We will move the *0*th layer of `Operation` to the end of its invocation order.

```C++
template<auto...>
struct Operation
{ 
    template<typename...>
    struct ProtoMold
    {
        template<auto...>
        struct ProtoPage {};

        template<auto...Agreements>
        using Page = ProtoPage<Agreements...>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

using SupposedResult = Operation<-1>
::Mold<void>
::Page<0>;

template<typename...Args>
using Metafunction = Skip<Operation>::Mold<Args...>;

using Result = Metafunction<void>::Page<0>::Commit::Page<-1>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The implementation of `Skip` relies on a helper function called `LoadSkip` to keep a record of user inputs.
The record will be passed to `Omennivore::Press` to invoke the previously provided operation.

We will implement `Skip` by performing recursion manually, meaning the function will recurse only once for every invocation of a member template.
We will showcase a simplified version that handles `Mold` and `Page`.

```C++
template<typename...>
struct Capsule;

template<auto...>
struct Shuttle;

// We will use `Items` to keep track of user inputs.
template<template<auto...> class Operation, typename...Items>
struct LoadSkip
{
// If `Mold` is selected, user inputs will be kept
// in a `Capsule` and placed at the end of `Items.`
// Then, we pass the extended `Items` back to `LoadSkip`,
// waiting for more inputs.
    template<typename...Elements>
    using Mold = LoadSkip<Operation, Items..., Capsule<Elements...>>;

// If `Page` is selected, user inputs will be kept
// in a `Shuttle` and placed at the end of `Items.`
// Then, we pass the extended `Items` back to `LoadSkip`,
// waiting for more inputs.
    template<auto...Variables>
    using Page = LoadSkip<Operation, Items..., Shuttle<Variables...>>;

    struct Commit
    {
        template<auto...Variables>
// When finally initiating the operation, we invoke the skipped layer.
// Then, we pass the instantiated operation and user inputs
// to Omennivore::Press for further invocations.
        using Page = Press<Operation<Variables...>>
        ::template Mold<Items...>;
    };

};

template<template<auto...> class Operation>
struct Skip: public LoadSkip<Operation> {};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGEgKykrgAyeAyYAHI%2BAEaYxBJSpAAOqAqETgwe3r4ByanpAqHhUSyx8VyJdpgOGUIETMQEWT5%2BXIFVNQJ1DQRFkTFxCdIK9Y3NOW22o71h/aWDFZIAlLaoXsTI7BwA9ABU%2B7sA1MrEmAoKhwe72yYaAIIEmCxJBo8mAMxuBACeSYysmEOAHk/sQmI4BB9sLc7iNiF4HMdTucYSYAOxWe6HbGHR7PV6YD5fX7/NgAOgpUJhOMOcIRBEOABFMPU6Id0VY0YyPpi7jDtttDhYmEpDqIlCBUVicXiXuDCdLsUTqTSZU85W9Pj8/sxyZT3tgxQZzocPIImLMyPzBQAVBBxQF4C4CWjfQ4CQFJBoAx7EQ5e5AAa0O9CoBDJKtVuJJuswFLJZseggUkfZBtTdMRzNZtCJiYt4WIedkjAICnjVPTivZGOthwA6o6GAA3VCBwEEe1ikjIlIMfBGXHqgmHNjzP2oKi4ruoUHgjJ1gDuhAQ08BmFUBDBDkw6H9TCDEerNK8aUH2sBH0ZwLnEL8IFlI4Asp50MXBKXy/roe8LOzq%2Bi3K/lKdw0o%2B8qpsqx5qviEGfEwXhEBWBpGiKFxCJgACOXiMJspCpjSCFIRSiafpBVagTimYMtmFq5p8GHYbhhKfKRybIT%2B0IARihynmEwDRn8abXiCcTzs4D7DvKxxMMALFuGxZYcTyNZAbydYAErVOsaTNoC4rsCBYFSW8AGfARMEavJF6xhxqEmvmlr4fcAoNoCShemCjxrocNDECM%2B5gmwvr7kGvnEKgLA%2BagnZxOWFnYjZALxopCjOZRUZJXqZJArF/nkVxGW0lu9JMiydHvqyhaVZ%2BHGkMCeVfhGFE0hyCW8WeAkXsJSJnCm0FKuZLmCo2hxhK27Y%2BWgxC9gIA5dSZgJjmU7pTrF7q3guw2HMunY%2BRuW4Ho8e4BoGR53K5dqMPVi6emhPnIl4tAMtEB7BkQvUmvwfpUOseVjS2qCiHe8UDaqWWAqJXkZCAkmwd5L60G%2BrElux37tVS21yAwp67qFgYXA0gKnMg3zIPQe7fb5f32n641A%2BJDCg0VNKw%2BB3m0XQRK5bTTVQmzJI8pBXJC/cqbswqRVQSzlkEkSRGoHZ5P3YxOEMHh7UKylqNlulUaJTGyUUjzcUFRmJVZuVXMMVhaubDVaPNdg9Um/5yncby%2BsdfxgmXu814nH1RIQzeYl3mzi0yXJDtKejLX6xH8OApz9FuK7fMGgLfyi1LIvAQB1YS8HhvZXcwCnE8ZHx9ifGDoje5XmVOZEmXFdsI7/MPoL%2Bd8nn6kuVcppMEkChPYCVw3PcRdaiXcbo/c1FDyPY85/yg9CAgiEEPQlwHJPDyLfLiGK/PsIWwyG9b/Qq8DwchzBKgTDoEIgZ4Eku/7PvrmjcutC0B1l4ABsGgACSeIUzANxKgQ47ZMDv0OmFScAC6YMCSIhZm08viH3gsfJWxoLhQ0ZvVCG8YwFPBTBRReD8n4vzfqiWs20QFThMMA%2BuLCNBjQuB0Y69VcYoLQWWHadB/6xBgXAggdYwiHCYOyYBbhh6j2vpAwwJ0DCbD3OCfa/ZVqyNAeAiMwC6xXQYDdO6Jp1oHVcHjdhZCWAQI4a9MKH12HUOfq/JI7D0quUXBaRwg4qYsBIE2ARzNjJJ2LjqI2ZJsD0HbmWTGRVa4CXrj1VxtCPGfEIXeeqtimr1Xkcva%2BnwYmVw7umcp/cLqCiYbo5QslCSQKdLSTA9geHIIBiEoRf9DiiPbEkCR20pEyPYZfAg28GkcJUf6NReNNEWO0Ugmx%2Bj2FGPtCYnaZiLgWM3FYhuwDcnsJ6W9KBui0nuM8UuXxPsAlBI6eg86YSrJH2ImSAAag0PATBoj0AoYVE8nUo5%2B2vGcuhmTNoCByfoik9VRnjKJO84gnzvlnGUhUoyVFz6mkiiwQgwtPb60wVrCkCKkU/ISd/NZvkwhiFdADdI85zwznBes26AMJodi7Aodxfw9wGG%2BHEc6l01mmP3OYrsYQRiGEcPKPcs4w4ZGkdovhdz4nbQ%2BkCduDA8CtlOLDQOX0SDU0aLTNlDMQYPP1kkwFPV9UULTsy%2BFHyvk/NRX8hOcMrKHDYZ8XJqL8VKj7iBQCN8Lrr3cR/a4MJMGEtwd%2BeyBCHWUMxekkA/ovDfLwMge%2Bj83GgvtfKyEKE2qBrFrfK45aJ5rzvjaM4gjK1lorRW/eqIzDvDCOTLwWA0xuEQnQQg3wElRuwfI2NTsYSLyyVtXuf5xbDpIafGki8TgxVQGwj27UY0vISV7JdEUiB1LkjWTkal0WZWHUSskrdMClPidXVUVqD1AqRCux9Ldy7XriRnH8/rVIhseXLGekTS7vpvb81MVqUmN2XUQb1bgr2gb9fQk9pa7hWqEF4JIKQlDoC0oohkjdJ2FrcAAWi4Ak2GsHWx4GRoVPV9SiQaErJU6Ns94x3GIMAMD9wIPlV%2BurO8PV0nc0TdgCjr4W4ca/SGq1uGnr4f9l63jXh%2BMLk%2BFRmjdHo6fEY5nEAHgWA4oIJp%2BSpGmMgUlY4ZAAB9NCcQCAQBGOgWGCgAQ2btbJ56MKMNYd3B5iRBolg8g4CsWgnB/C8D8BwLQpBUCcDcNYawtI1gbEvK2ngpAjNReCysQMIB/CSDJBoSQXA0TvA0P4DQZhAGALMAADlq/oTgkheAsAkBoDQpBIvRdixwXgCgQAdcy1oFYcBYAwEQCANYBABHkEoGgZ4dA4gRABJwVQtXAHEcAZIQ4wBkBZqkGSMwvBdyEBINRvQ/BBAiDEOwRIl35BKDUJoHQehFxgiSJwHgIWwsReezFzgQJEICJ0WtjbW2dt7cOAdswhwID6aSItv05h3hcCWLwIbwXSAQCQPNhH9AyAUAgLjxHIBgBSDMHwOgvp%2BsQGiH96I1LiDfE%2B7wBnzAmdAmiNoaomX0vzbiUCBgro/tYGiF4YA8i/79e4LwLALBDDAHEFl0g%2BASaOD0tL6LG5tKPBZ%2BQD8oXle0DwNEMETOPBYD%2B1uPArWZekD0sQaIqRMDMnl0YY3RhnsrCoAYTjry8CYEXKJSL6X7vXfEHd2QigVDqGV7oLg%2BgFcoAS5YfQJv%2BuQBWLOEGnBiOOavKYSw1gzDdYd4irAGeIArG4TDCArhxitCCP2PoJQyh6CwwUTIngWjt/yHeFvAxyi2BaTz2o0wG96Br10aYA/xyT/H93iYUweiz7b6j1Y6xNgSG%2BxwcLnW/s9cOKDzb23dv7YKzDiAuBTtI7S2jjLXuVj2ifoMKvpBcuSHeGSAAnO8NEkgiszBJBgFytAFv9GsOBmtSBWsUcyRAEuBAFatv9asED8s2hf9AF99lces%2BsBsH8ssRtxtsdJsgdEJZsidIo8clsVsOAGgWBmw0RiMZFlZBwuBv8yQuBCtjt8AiBy8LtZBw9btpB7to8ns48QAKc3th4Wcd898uteAetAdptEIdE6CGCmDUJWD2DOCOE4dKDEd2RW0zB78McRscd9D8dyDid8cQA1DGCWCydv8uAOsaBno4pKA6dlc2cGhmc7dvCOcucec9d%2BdSxBdhdldRdxdJdaBpd0s5cFcldotVdR8Nc/ttdkBEIth0swhHhDdotjdTcfCLcthotrdbd0sHcnclBXcEj%2BIvc%2BBfcFB/dA9g89cw9RAI9hCo9HtY9otdAKcDBPdC8rBU8CjK8s9%2BkMhpc88CBkZGRhji9S84hy8zh4Bq8R9Og/A69%2BwJ8E8QhZhW8Fg8g0g7xdjjjO9V8jip8GBugxhF9G9rjbiZhihB958egzjJVGhLjyhq9kst919Dc5CD9OBpFiB6DGDmDBiBI2CODCtYdr9eDDCUcTDH9SBn8sB4g39DcoCYD2Cis0R/Bv80RStJAgCtsE95D/tetbA8DTCsciCkApsZtCdrDqC2BOA6Dwc7Fmws1mwYSCQRhuCb9zsE92ibsJAujBBRDeiXt3hSApCPsZdZDftsCAdSCGQkFOTttuTeT%2BT5QAo9CFt8ckT3gUSCCsdzCjS4grCLDBgeTMMrM%2BTv8rMBSCAbMwSttKc3D/IPD6dGdfD0t/DvhOducHBgjsVQihdfCkjMAxcJcaVYjZcngEiSjZc8A1dtVVjld0jMi9cciWk/sCizdvhiirdEVyjeBKjncaj3c6jzSfdZImiA8g8dQ2iBCOihCZApSei/tdA5SoTk8i9Rj081iYtJiBBpdthHNByRiLAS8FCy9qNVjM9h9Wla9697i9B9iXi58E8O9TjNy9y%2B8MhvjJ8Ni7wniPjzyx8V8DjXiE9PimhDzl8vi7zdzfjN9btlSsDusQStTRwFAeTDgnSyRXT4SeDDVkdUd0dUT0TX8d8cSJD2D3h3h/AKtit2sUK0RECfyFDOBcDBtUSP9/Af9/Basqtv9JAiSsKuB%2BzOB3gVTfzqTTCd8jtcKqSYKCCVgHc0hnBJAgA)

## Links

- [source code](../../../../conceptrodon/descend/pagelivore/skip.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/skip.test.hpp)
