<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Raillivore::Skip`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#raillivore-skip">To Index</a></p>

## Description

`Raillivore::Skip` accepts an operation and sinks its *0*th layer to the bottom of the invocation order.

<pre><code>   <i>0</i>th Layer { <i>1</i>st Layer {...Last Layer {***}}}
-> <i>1</i>st Layer {...Last Layer { <i>0</i>th Layer {***}}}</code></pre>

## Type Signature

```Haskell
-- Skip to Mold
Skip
 :: template<template<auto...> class...> class... 
 -> typename...
 -> ...
 -> Commitment

-- Skip to Page
Skip
 :: template<template<auto...> class...> class... 
 -> auto...
 -> ...
 -> Commitment

-- Skip to Road
Skip
 :: template<template<auto...> class...> class... 
 -> template<typename...> class...
 -> ...
 -> Commitment

-- Skip to Rail
Skip
 :: template<template<auto...> class...> class... 
 -> template<auto...> class...
 -> ...
 -> Commitment

-- Skip to Flow
Skip
 :: template<template<auto...> class...> class... 
 -> template<template<typename...> class...> class...
 -> ...
 -> Commitment

-- Skip to Sail
Skip
 :: template<template<auto...> class...> class... 
 -> template<template<auto...> class...> class...
 -> ...
 -> Commitment

-- Skip to Snow
Skip
 :: template<template<auto...> class...> class... 
 -> template<template<template<typename...> class...> class...> class...
 -> ...
 -> Commitment

-- Skip to Hail
Skip
 :: template<template<auto...> class...> class... 
 -> template<template<template<auto...> class...> class...> class...
 -> ...
 -> Commitment

-- Skip to Cool
Skip
 :: template<template<auto...> class...> class... 
 -> template<template<template<template<typename...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Skip to Calm
Skip
 :: template<template<auto...> class...> class... 
 -> template<template<template<template<auto...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Skip to Grit
Skip
 :: template<template<auto...> class...> class... 
 -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Skip to Will
Skip
 :: template<template<auto...> class...> class... 
 -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Skip to Glow
Skip
 :: template<template<auto...> class...> class... 
 -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Skip to Dawn
Skip
 :: template<template<auto...> class...> class... 
 -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment
```

```Haskell
Skip
 :: Commitment
 -> template<typename...>
```

## Structure

```C++
template<template<template<auto...> class...> class>
struct Skip
{
    struct Commit
    {
        template<template<auto...> class...>
        alias Rail = INITIATION;
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
template<template<auto...> class...>
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

using SupposedResult = Operation<std::index_sequence>
::Mold<void>
::Page<0>;

template<typename...Args>
using Metafunction = Skip<Operation>::Mold<Args...>;

using Result = Metafunction<void>::Page<0>::Commit::Rail<std::index_sequence>;

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
template<template<template<auto...> class...> class Operation, typename...Items>
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
        template<template<auto...> class...Sequences>
// When finally initiating the operation, we invoke the skipped layer.
// Then, we pass the instantiated operation and user inputs
// to Omennivore::Press for further invocations.
        using Rail = Press<Operation<Sequences...>>
        ::template Mold<Items...>;
    };

};

template<template<template<auto...> class...> class Operation>
struct Skip: public LoadSkip<Operation> {};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISdKuADJ4DJgAcj4ARpjEEhoArKQADqgKhE4MHt6%2B/tKp6Y4CIWGRLDFxXIm2mPZFDEIETMQE2T5%2BATV1mY3NBCUR0bHxSQpNLW25nWN9A2UVIwCUtqhexMjsHASYLMkG2yYAzG4EAJ7JjKyYANQA8hfETPVH2CYaAIJjxF4O18rEmAUCje7xMAHYrB9rtDrttdvtMEcTudLmwAHQYl4gmHXL4/AjXAAimCadGu4KsYMJR0hoI%2BAHp6dcLEwlNdREoQCDsTC4XsnoioTCkTycdC%2BQikWcLsx0ZjDth2QYgdcPIImKFYqQQYzrgAVBCxG54BTXAS0U5msLXZLNK7bYg2pjIADW13oVAIaNFYulqMwGLRau2gmBQuhWPDuII31%2BxNJtCRwY1YWISdkjAICkDWIVPopOqZAHVjQwAG6oF03AiG9kkAEKVIMfBGWE7fnba5scqxM1UWG11APJ6ZQvXADuhAQA5umFUMed23QTtd3qjOK86VbfvJh0Jd2H9RAIAlAuuAFlPOh04JM9n5a9DhZyVHwdSn9yo6eDq/jj6cd%2BiLHEwXhEDmCpKqyppCJgACOXiMBs2rrjCIFgRiwZ3vmeZRnicYkhqibHDB8GIUBbiYaG4GPq8r4Qtcm6hMAsIoru%2B73LEI7OCe7YIn8TDAORlFZtRNLklSNKfu8uoAEqYMgazpGWNwcuwUkAbxArYW4/68ppBzHH6soBg%2BkEqsmmpkGOJa4pgtqPJ2NY3DQxBjE6jxsA6K5ulQxCoCwM5mk5rlru8Yq8iixmBsJCjIWF4UsTKVyBrcwVhvFEY4Rl0axgS8aETepKpoVd7UaQdxpaJdG0glDFbsxO5HPu/yAultUigyxalhWVaBWgxANk2LYNfpNzdhUfaBUOnHPJ1E5ToFc4Lg4mDLraq5jgajDleONy2iqTnXA2Xi0ASUTOm6RB/A2pr8I6VBrMF1yhBWoj1NmunhUZVwHjNmTHoBF5XiVVEPp9u60dJTJyAwm6rd5prNDcALIKcyD0Mud3XA9LSGo6L2oG9mQfSh0IA6NRIEXQSKpXj97egqAMopJdHvrSPqAdp4Oc8BoGoNRZnQXBCEMEh4NofzGEZqGcW1d9cporTsRtcKWU4nheVU0RbgkSLGwgyJD7lUrIVg9V4OMdurFNddrVSpFP0cQ5/08fCZ7KAJQnS4bDM0eD5Nu52%2BXU8cJv0y8TMXCz2VvtHOIc6N9tJQr7zAACOxYWrMKW8xl60MuNvB9rqfp2woO%2B5HQHsxJH4fCCPPIsnJm%2ByCGuqkwyQKCdVdSQ3EtVZ8Mb4tcQgIKBBD0NH1k3JOtC0HVNwmAAbBoACScLAivsKoNcVZ2bCjyupNcP4wwySgST7wN9fie8%2BhvuCwL6NQb9zsCOV8vN%2BvOzAllbdBKgJg6AhAujwMkbkEIxyr37MvDQedrxbxNLZOoq1yon2emfC%2B8057XBiLvOyBAxyhGuEwckK83Ady7pPLehg1oGA2MuJ4i1myTVgd/FgH0V6bUNAwHae0X6HSWq4eGbCN6wNwRdbeZCNAAKASAsBsC4q6nHBqRwrYsYsBIKWc%2BIkE6B3Ip/QM2B6BlyzJGbKOcgb5zYtcWRwDQHgNDoeTI5V2H03KhQzu3ckTGIzuXXMj52ZzWgdIj2glxFILsPJJcaClCnx0aaWe888FVmSIQuaxDSGwNHuPahGgSEsP5AwkhBJBEsNQDAlebjvRcLmltXhE5%2BEHVrEI5sIiqliK3udI%2BV1YF2PkeAleSimQqIyOokgXYtEYISaFDS%2BikT9wxAANWaHgJgUR6C/0hhueq/FBI2P6Q4mmzj37XGqRicqOSCAT3Iis4gayNmAlEnmWudJsptw8CwFghB8yQNJm2eZhlb4UL5k/ZU9NdZkS2dZHh2NQhiAtBgjII5tyDhOQ03aGCerVlrAoBxFxlwGFOLEUKup6l8KdM00sMxBBrKXGadFBTlzoNCAkscV1bhlwYHgCsAJjwtRVFjHGT0CZEwEJfWqliZKERsQK3%2BbgnZcQYEiSFosnlgyzuFAOHYbjwKROclurz441yCaCE1vdgU30BSC%2B%2BLxH6mWfiqRVzw/5D1%2BAMkANovAbLwMgWxgD7EKKcX9AQdqCzmrrgyAAVDG2Ncb6Q6ljXqbAQg9SxoTdGuNWaM1vPMIcUI6MvBYF3G4UCdBCCnHMfXS1wLFkP0deHV1uVX5Kogc%2BPROqk7%2BgHurN1BJ/ioCIHq82/y%2B6grNtlXtzaB1EDCYvSBEa3ly1reOtEJdMB%2BLMZqsUli52yr8rOz2SJ12bsbYE35bN1J6WtYYjEJ7THQqjJY%2BB%2B7B2oD1cce9pUNXV0vZG94lihBeGSAUVackqEEhts60cxwxjoGPKELAqgAD6ShSJqvMceD9bgKx4GvFlflR7jgaFzKa6%2BDsU7EGAI%2BgDuzzwEQeqLeoNiBnHJDcqxmIBsPvCo2eqeHwpWAhOpBvcF4GNeCYzBnDqA8MRxAHOpEJHOOfO%2BQQY80qQ5uDgwhtpKG0N6yAue/9MxHDIGQ1BWIBAIDaZAAoK45n5XgeE5c4DoH0BOdOi8RYNIODLFoJwBIvA/AcC0KQVAnAdKWGsLiVY6xF5mEODwUgamQu%2BeWC6EACRJBog0JILgYJDiJA0GYJeS8zAAA5yv6E4JIXgLB4gaFIMF0L4WOC8AUCARrKWtDLDgLAGAiAQCrAIDo8glA0C7DoLEcIVxOCqHK0vAAtEvSQ1xgDID9VINEZheCrUICQPDeh%2BCCBEGIdgUgZCCEUCodQqXSC6C4KQccjxkicB4H5gLQXNC8Fa7cUCOjJrzaWyttbG3rhbbMNcCAnzkhTcdHmrgixeDdd86QCASAJuw/oGQCgEBMdw5AMAKQZg%2BB0AdB1iAURvukCiPC4gpw3u8Fp8wentwojaGiYz0gE3TG3AYBaanWAoheGABQueHXuC8CwCwQwwBxB3fwCjRwykJehbnPJUCmwkuhG2P5u7tA8BREePTjwWBqcxjwPVyXpBlLECiGkTAxIZdGAN0Yb7ywqAGGo0svAmBxwcWC0l47whRDiAu8H67ahqcPf0LLlA1hrD6ENx1yAywhzvU4ItuDTVTBRcsGYFrtv7lYBTxAZYUSHD/QgK4SYfhHvBE1PMYYj2CgZAELXvQrf6hzCGJULo0SejjFaJ4doegK/1F6C0HvPY%2B8zAmCP3Ij25/9Eb73iQ5fYsbHX9VjggWmvU9a9cIHy3Vvrc29lyHEBcD7fhwlxHyP3fLENEA4YZfSAZckIcNEABOQ4YJJC5ZmCSAryJBLzf4761akD1aJZohLxcBLzlbf7lbwFZZcAJC/5Lz753atbtadbJbu5o4Dbo5Db/agRjZ47%2BRY7TazYcDNAsBlhgiLakLPythcDf5ohcA5a7b4BEDF5HayCnZh7SAR5KBR53a6Ak7PYdyM4fa75fbYGcB/YjagSTR0EMFMGQSsHsGcH5LQ6UFw7kgJZmBI74Gpa9YY76HY7kH47Y4gBqGMEsFE7f5VCk6nTKyUBU53bM7NAM7W7eGs7s6c7W486Zh84C4K6YDC6i4IoS5JbS6y7y6haK4D4q7U7q4KTbBc4661DU4G5G4%2BGm6bChYW5W5Ja2725KBO4JFMQEGe4CQKA%2B5%2B4B5c7B6CHnbCGyCR63ahYSGx5u655WCWBJ5RCl5p5pLEyZ7Z57gDHWAF4/ZF54aAjwDl61AD7ODV7Ngd717NjT4LAt5pBt5ZAL514pAHHd6r4z5j6rGV4CCT7D45AnHj6D6zAXF7G2BD5bHvEvGlBr6I4rBrBb5/F6577NY/acAkLED0GMHMEGBaEcE5ZQ7X68GGGJYmEo6LBP6YAv5xBv566QHQHsG5ZgjoFggFaSBAEraPaglhacC4FdYEF9aDbDaja442HUFsCcB0Eg4cJlh%2BplhsFogIhjDcE36HaPatGh7tGXbyCiHdE6AgCHBPYvYyE74gkH6KGkEEgVIQksDckKC8nXD8nsFCkEh6GTbY4omHBokMkWHmlaismWHDC8kgbIZGnIYmnmaQkrauHk4eHU7%2BG%2BFJYBls4c4OBc4hGCBhG%2BFJGREi5i60CxFS47AJFFFS54BK48pLF3bpGa5ZG3h66hZ5HG6nCFHm73KlG8DlEO5VEu41FmF8Be4NG%2B7%2B4ygtECGSkSAdFXaynR4Kl9HGAJ5DF5GjFhbjHiqcD0jaYzH56F6xDF5LGp7943F%2BAbHuDHF6AN4/GXH7GFCZCfFd6ZC7HN5LkT4fHrlL7XGnnfGDDblfHz4PFj5D5HmVAb4AnnayFqkKEcA6l6kGlGmCkChuRX48ETII7WlmGYnYmUCyH4kgBmDsGHCHAJAJC5ZVAaCIVggIFYEta0m2B4Honpb%2BAJA/4JDlYlbf6SDf4FZ/5cCKl66HDyE4VtamE9ayE7bYVgnMUEU27Kz/SSBAA)

## Links

- [source code](../../../../conceptrodon/descend/raillivore/skip.hpp)
- [unit test](../../../../tests/unit/metafunctions/raillivore/skip.test.hpp)
