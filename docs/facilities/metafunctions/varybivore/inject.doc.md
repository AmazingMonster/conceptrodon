<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Inject`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-inject">To Index</a></p>

## Description

`Varybivore::Inject` accepts a list of variables.
Its first layer accepts an index, which indicates a location in the list.
Its second layer accepts a list of new variables and returns a function.
When invoked by an operation, the function injects new variables into the location and instantiates the operation with the result.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>I-1</sub>, V<sub>I</sub>, ..., V<sub>n</sub>
-> I
-> Args...
-> Oper
-> Oper&lt;V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>I-1</sub>, Args..., V<sub>I</sub>, ..., V<sub>n</sub>&gt;</code></pre>

## Type Signature

```Haskell
Inject
 :: auto...
 -> auto...
 -> auto...
 -> template<template<auto...> class...>
```

## Structure

```C++
template<auto...>
alias Inject
{
    template<auto>
    alias Page
    {
        template<auto...>
        alias Page
        {
            template<template<auto...> class>
            alias Rail = RESULT;
        };
        
    };
}；
```

## Examples

We will inject `10, 11` into index one of `0, 1, 2`. Then, we will instantiate `Operation` with the resulting list.

```C++
template<auto...>
struct Operation;

using SupposedResult = Operation<0, 10, 11, 1, 2>;

using Result = Inject<0, 1, 2>
::Page<1>
::Page<10, 11>
::Rail<Operation>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The implementation is similar to `Varybivore::Amidst`.
We want to count variables one by one up to the desired number.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the variables to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` as in the implementation of `Varybivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `Inject` using concept expansion.

We will expand the constraint `Prefix<***>` alongside the arguments.

```C++
template<typename, auto>
concept Prefix = true;
```

We will encode value information into types by `Vay` to avoid defining the body of helper functions.

```C++
template<auto Variable>
struct Vay
{
    static constexpr auto value {Variable};
};
```

`Enrich` will help us translate `std::index_sequence` into a pack of indices.

```C++
template<typename>
struct Enrich {};

template<size_t...I>
struct Enrich<std::index_sequence<I...>>
{
    template<auto...NewVariables>
    struct ProtoPage
    { 
        template
        <
            template<auto...> class Operation,
            typename...BackArgs
        >
        static consteval auto idyl
        (
            // Expand `Prefix<I>` to count the arguments from the front.
            Prefix<I> auto...front_args,
            // Collect the rest.
            BackArgs...
        )
        -> Operation
        <
            decltype(front_args)::value...,
            NewVariables...,
            BackArgs::value...
        >;
    };

    template<auto...NewVariables>
    using Page = ProtoPage<NewVariables...>;
};
```

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`:

```C++
template<auto...Variables>
struct Inject
{
    template<size_t Index>
    struct ProtoPage
    {   
        struct Slash
        {
            template<auto...NewVariables>
            struct ProtoPage
            {
                template<template<auto...> class...Agreements>
                using Rail = decltype
                (
                    Enrich<std::make_index_sequence<Index>>
                    ::template ProtoPage<NewVariables...>
                    ::template idyl<Agreements...>(Vay<Variables>{}...)
                );
            };
        };

        template<auto...NewVariables>
        using Page = Slash::template ProtoPage<NewVariables...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEEhrBAA6oCoRODB7evgGp6ZkC4ZExLPGJXMm2mPaOAkIETMQEOT5%2BQTV1WY3NBCXRcQlJwQpNLW15nWN9A2UVIwCUtqhexMjsHAD0AFR7%2BweHRztbJhoAgrv7ANQAIpgprozIeJgK1wenF1fHv4df5zOgLMgQiyG8WGuJkCbi8jlohAAntDsEDzKCGOCvJDoW5kGN0FgqCi0d8DtdlMRMDRVB99gCCJgWCkDIzcQREY9mGxSNcmHDUCSLmhMQ8CBSqTSoYFbtcCMQvJhoVYLkCfjtrgA1JiIul7BlMllMNkw/lELXNPBMWL0IXnMYKhwW5GqgDsFmuM0cyGuIrGmFUKWIfIF1wAbmJFVD3driFabUrXbdldHk4EVYCyX9s581eSAJLM%2BhsQTGrJ6k55nPVgFVvbXbAMOPIBAVg1F41KmEcrmsLuoi4OrxOxvN1smd0TtMZoGMjsmtwZABemAA%2BgQAHRb/N2ocjpt4Fu4gkgEARLCqVdKACOitFuPzW43JMCA8Bk4u1y/csNrK7bjNVAnyiTAAHdY3jegFDtb9PXlYdxUpVAiGUJhgCVT9vwnD0gVg2C5yNNlMLw6U3Fwki8IIv9cUAp8UV9AwFHeAB5R5iDLARSHIijvx7Rg%2ByfCwmGQABrc5iGAaDiLwmCKK9Q9fQEf0I1oENzTwdBEVobi8IgHSeK2LYG0DQx0ChAA2DRKWpPBVAfElLLlVBFK8QQ5QQTA%2BQknxGAId4qGIVAWHczyAtkZ9pJ46yaXs181KArcwsEVdmkkrjIoowzrhyOoQuuKkxgi84eNgoTRPEyS6Iyr9Fn078AFp6NYhIOIYOqv1xdq8KwcE%2BOoQLktShRFlPFTFSfdLipKr8QPAy1rSgiautK4SxIkhRRsjTAqqmkiXwzWCp2VUldp/ed/1ordZogha3lkr8vAyIwKTQzzoVlJCUNe3FrvmhMFDo19jrdacTvVa58wYbRMCdXMLiozsaIFJ8bv%2B3d4KdSHoYcNEP1OhGF2XNdxUhi97rgx1EMCr70J07CsOqimEOuIRGIQLrsOW3jf0R01kausDUag8meL3KnkNQVDacZw68emkiCf/RWkaIQHsAYpgmKfc5gCpJlfOgoGZYox6ImAa4ACUmDoaVZR62g%2BK5ki9ON6bR0PdmYRPEAWCYES13PAMr0wW9nn/UmAxfN95ZK09FYlCWpf/X641ugGtxFmPvzjnnGWuDStNxHW9ZLPy1YgbVkRhIW7qByckyfWrXbw2r0yd1NgdO2XQdVRnlb51WBbm1O0aNrvv1N56k9tlm2Zz86E5p5PBb%2BxaM6BtvpKOzfM3x3OLv5jdi8wfXBEN6OJ6e83p/exfJe%2BmFj9Psv19RHft5nLNq3pOsNWwVRWAsk8nDS438QG/2uM1di9QGBtlnPvFWCVnxjzFpAtirVO4QKEF4FIaQlDoAtm8LwDs4EXEnubbBuD0iYAIUQkht8oEYJhBoXkVRWFcFYbyMw%2B0wbkkIQoYh4oQHkMtnQ8Ut8sYwwILiFh1wOHXG4WPU8SdcRcDtMoh%2Bbg2FyLUUokAVs6C4kYTAnhvdQE3AACpvCET/QcTRvQpSYgkAgEBvYKD7I43E/DBG8koXgmh3iHYolbhYDgyxaCcH8LwPwHAtCkFQJwMilhrCelWOsN6IIeCkAIJoMJywRIBEkBuDQAAOMwZgACcFSuD%2BFKSUrgrpXTSAiRwSQvAWBJBYTEuJCSOC8A2iwnJsSwmkDgLAGAiAQCrAICkOE5BKBoGZHQBIUQ%2BycFUCU8y9VzKSGuMAZAPopAbjMLwGhhASAaT0PwQQIgxDsCkDIQQigVDqGGaQXQHDQLsRSJwHg4TInRNyfEzgzE4SzPFKgKg1wNlbJ2Xsg5ciilmGuBADwSz6DBnRFwRYvAhlaGWBAJAiyUjLLIBQCAxLSUgGAFIMwfA6CMmIBtCAsQgWxAiM0REvzeDsuYMQREzFYjYyGVkxZpdmIMFoFyt5WBYheGAABWgtANrcF4FgX2RhxAyrwFSBweAwxvCBQGGGcJNhZIiIyFpcSESxHYvyjwWAgXyjwB01VpADXEFiNQ%2B4GrgAIiMLk5YVADCSU1K8UCzUYlZOucIUQ4gHkxueWoIFHz9CGGMNYaw%2Bg8CxA2pAZYqAUgwJVfVAk71TDJMsGYHpHq4xYDzRAZYdgpFZBcAwdwnh2h6DCBEQY5RhgcLwUUbIna8iDsKDAuYQxKhdBbQ0cYrRR1%2BA4c2vV87Zi9vmAO2wC7JjLp3Ru0o06JBNrSRsE9%2BgAWkG6bwXp0LNnbN2fsw5SKUW4HOZizJOLsmBuWB5JgWBEiNtIAUyQgQNwVMCE0jQkgzCSEshofw5kKmXtae0kAgQuAbnMlwcyJSKn1PMv4SQNTIPmWvUC3p/SQCDMDaMiZhKplgrmeSylGLVlsE4M0FgYZXT1SYBrZ6XAKkbiw3Es5RA61XNkLc%2BN0hE1KGTW83QdKvlMB%2Baq/5HAokUbeb00FMy4TXEhfe2FuzwTprkSJsTKK0UkoxVCEEZhv14pGYxtjCR5kUqCvZ4YFmjDCbYTQB2CRmWsrebyzl3LSCRf5YK4V0WxW%2BQlVKoFsr5WKuVdF9V6atVxPwLqxwBqVXidUCaxk0WLW1CBTau1iIHWbDic611WSPVeqUD63LZs6PBrQgoMNYFI3RZjbJ%2B58nZBJteXElTaaA0VqsJYbNub4AFqLVkEtZaZTzesNW29taNKGvzbOtdfgICuD3d29tU7%2B0zqHTAi746MiTs3celdtQ50MF6BMJdehV0wK%2B/0F7N3fu7p%2Byuhd12FjYpWGsc90OWk6ZvcCjgpnH2CfNsJ0TxS334Ek45zDLnf2kH/YBygWm2mkA6YEETMHXT%2BAqY0wIsH4Mkd0z0zg1HaPDIJQxpA0zwVeY88QDjmxuNwpYAoMMPowyY7/GMU5uOLnoGkzcuNY3HnyEU1NnQGHSBqY0381DiPKMguYxCqFqhxeS%2Bl7LzsYxbM%2BdJfjwIhPuejKJY7jFgvPfDCl7g1cMuKmrjlwQVclv5MMtC5QcLcTYvSqyXH%2BLUjEtBXFZK6V%2BXMByoVWILLbqcuasa2qnVLbitGrK8gU1lXBDVbebVzlDWnVxha7wNr3qmRdYDW73robw1DbdSNtXEhxtPK1ym3XBg5uZsWzahtq3i2cC2CebbVaa0JDrYd4Df3W1nfbQ9kIV2gdQ9IHdrI%2B/T/FCP9u7f67vu5H3Tfz7EOr8zpmHfrt4PD19qh6e2H9ytPG56acDQpW5S7hi26Mj24QDvp45Yqu74p/qYAAbDDAYtIU4dKVIbiBCBD%2BC1IkYaDJBQZ4Zs63oc62A0Y/rc75IgCSD%2BAQYNKugEElKSDVJcBlJmDkYtKBCApAF9KUEIGoYnIkHI64pE4eoZDOCSBAA%3D)

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/inject/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/inject.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/inject.test.hpp)
