<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::CognateInject`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-cognate-inject">To Index</a></p>

## Description

`Pagelivore::CognateInject` accepts an operation.
Its first layer accepts an index, which indicates a location in a list.
Its second layer accepts a list of new variables and returns a function.
When invoked, the function injects new variables into the location of its argument list and instantiates the operation with the result.

<pre><code>   Oper
-> I
-> Vs...
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>, Arg<sub>I</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>, Vs..., Arg<sub>I</sub>, ..., Arg<sub>n</sub>&gt;</code></pre>

## Type Signature

```Haskell
CognateInject
 :: template<auto...> class...
 -> auto...
 -> auto...
 -> template<auto...>
```

## Structure

```C++
template<template<auto...> class>
alias CognateInject
{
    template<auto>
    alias Page
    {
        template<auto...>
        alias Page
        { 
            template<auto...>
            alias Page = RESULT;
        };
        
    };
}；
```

## Examples

We will inject `10, 11` into index one of `0, 1, 2`. Then, we will instantiate `Operation` with the resulting list.

```C++
/**** Operation ****/
template<auto...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<0, 10, 11, 1, 2>;

/**** Result ****/
using Result = CognateInject<Operation>
::Page<1>
::Page<10, 11>
::Page<0, 1, 2>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The implementation is similar to `Varybivore::Amidst`.
We want to count variables one by one up to the desired number.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the variables to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` like when we implement `Varybivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `CognateInject` using concept expansion.

We will transform variables into types so that we can avoid defining the body of the helper function `idyl`.

```C++
template<auto Variable>
struct Vay
{ static constexpr auto value {Variable}; };
```

```C++
template<typename, auto>
concept Prefix = true;

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
            // We use `Prefix<I>...` to enumerate `FrontTargets`.
            Prefix<I>...FrontTargets,
            typename...BackTargets
        >
        static consteval auto idyl() ->
        // `NewVariables...` are injected in the return type.
        // Note that `Operation` is invoked by values
        // extracted from the template parameters.
        // This is because we will pack every item
        // of `Variables...` into `Vay`.
        Operation<FrontTargets::value..., NewVariables..., BackTargets::value...>;
    };

    template<auto...NewVariables>
    using Page = ProtoPage<NewVariables...>;
};
```

`Prefix<I>...FrontTargets` tells compilers that this function template is only allowed when `FrontTargets` satisfies `Prefix<FrontTargets, I>...`
In our case, since `Prefix` always evaluates to `true`, it constrains nothing.

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`:

```C++
template<template<auto...> class Operation>
struct CognateInject
{
    template<size_t Index>
    struct ProtoPage
    {
        struct Slash
        {
            template<auto...NewVariables>
            struct ProtoPage
            {
                template<auto...Variables>
                using Page = decltype
                (
                    // Note that we use a parameter pack in the template head
                    // even though the function only allows one operation.
                    Enrich<std::make_index_sequence<Index>>
                    ::template ProtoPage<NewVariables...>
                    ::template idyl<Operation, Vay<Variables>...>()
                );
            };
        };

        template<auto...Agreements>
        using Page = Slash::template ProtoPage<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEEhrBAA6oCoRODB7evgGp6ZkC4ZExLPGJXMm2mPaOAkIETMQEOT5%2BQTV1WY3NBCXRcQlJwQpNLW15nWN9A2UVIwCUtqhexMjsHAD0AFR7%2BweHRztbJhoAgrv7ANQAIpgprozIeJgK1wenF1fHv4df5zOgLMgQiyG8WGuJkCbi8jlohAAntDsEDzKCGOCvJDoW5kGN0FgqCi0d8DtcAGpMREffYAgiYFgpAwM3FMOGoSnNPBMWL0EkXMbELwOLnIi4mADsFmuM0cyGuaAYY0wqhSxGu7KI1wAbmIvJgodKqcQeXzMFLbtCZZbraTLuTlMRMDRVLS9vTGcymKyYQREY9mGxSJqOQLzkqNikCNcnS68G7obdrgRhRbAlYJWS/jnPkCfjtrgBJJn0NiCH1Zd0nfO5us1rMOm7YBim5AIaue0s%2B9Nuf2B1jp1GC1MimMttsdqVWSVWjP2hnd31uDIAL0wAH0CAA6XdF8NCsfXCd4du4gkgEARLCqDdKACOBsxvaLu%2B3JMCw8B0qB1z/Ka9Fley1VA3yiTAAHcTTNegFHDf9ZVHUUnVQIhlCYYALQuBDpyhbCEP/RdvVZfCCKhGFfzIgiiKAtkOTfFFFQMBR3gAeUeYhKwEUhKKo/8ti2a4AHVDS8JQoQANg0ONXVxfdPwYqSU05RgfASHtJI0AAxYhZAAFWaTCCDgqT31IvjY2dWSYXk7A3x0/TDMwYyePMvj%2B0YQc3wsJhkAAawM4gjLgtz/3gqi5VPRUBBVPVaFDbU8HQRFaAgRZrgAWnCsiBM08CoO5XlYMUjRNWda4Im0TAHEwdAKoYFMEENZ0CDWBqPLM84%2BNyqJUMNAgEB9TT2PU%2BoGBMJS8HeCIdVQPzauuWIaTig0Qq6qjctVVNfIZOqqF0lhGv6wCNJSZpBwZYgFE67rBL0hApoq954lEMTDQg966His7/OuTAdQSGlCEZXiCNy1AqE06CireEr6u1CaNCpZFTNBhCRs4sbcQcwRAuCy8VswN8Q3y6HzWu3cQx8/y8echQCf1Indw/TN1r/W150bBCaJ7OiiDAyCydg7LrjEiJgFjDDDSTSzUNQdDMNxUnCvJhjPztCVZw1wFsz2a4PGAZgGSLBgqtFPMLh55creA%2Bjmc/JimBY64Ma48b1ZHYVRQNo3MBNs2CDRH9zJt888HXLdiwYG8RcPZDdLQqXQenNH/zjmMhGYhBU/Z4O2Ys0OYRAgWCtNGG4I9/O%2BPT2XE8V0KyJThuC5O5di93IW3hFiz/zFoxJcw8jkywcEPJziyIHHnu/x6vrGqGj7RfEphrjOzi2Eu1ffL8%2BqjoApdDSaph0Cn6fNoB9qEFWYAOwGw0qC8TExuuARaBpMRaFQCD3gEQ1UA4t2N1p58RPGeGEF4QAsCYPNDc15VR3kwI%2BZ4L5o6qg/F%2BYBfFLw21rvLJOMJlZl1VvbDBmCyLYNboaJKKVcSuzGiGZGuJO4VzsiQtKp8yKLG1sAjmrM%2BK8PtO5ShfNQK7nOMAZ0jJGDGW7r3DI/cFbS0CMmTOTskAgBwShOuvZxGSPLMZNWqJOb5wEVzQiwii5223LozAUjBAsNBn3CWiih64MUbiGxdiDEkO1qYnWTZ6welrM2VQrBmSGgtgEwJAI0QgjBBCJReIBBRhkZXYJes6FVkiYXNw7d3yVxrpkgQvjdaFiEF4FIaQlDoAAEpvC8LQGMkSnHXHKZU9ItU6kKAaTGGWRT3ZuA0CGKowyuDDJDGYFm9oCzXC6T0zsQIWlzMaa4n2PZ/bVUDjCfp4ZLzuJhFwXZIB9luBGdcLghzK57PwYM8Z1xJnq2Mekwsek3hNLpECSKyANxOyUC0CAECFCDh%2BRXNwyyCAhjaVUzp9TGkoi4RmDgyxaCcH8LwPwHAtCkFQJwNw1hrCylWOsaWIIeCkAIJoJFyw/IBEkNuDQAAOMwZgACcLKuD%2BEZQyrgkpJTSBRRwSQvAWBJCGRirFOKOC8HpkMilmKkWkDgLAGAiAQCrAICkOE5BKBoCZHQBIURBycFUAyiSGUJKSGuMAZACopDbjMLwWqhASBJT0PwQQIgxDsCkDIQQigVDqHlaQXQYyIKcRSJwHgyLUXospdizgrE4SapjBDa4JqzUWqtTa85dKzDXAgB4PV9ANToi4IsXgcqtDLAgEgXVKR9VkAoBAOtDaQDACkGYPgdBLr0wgLEONsQIjNERJG3gg7mDEERKxWIAdR2kF1fo1iDA35xqwLELwwBcm0FoPTbgvAsBQKMOIIN%2BBnQODwADXdWLVTVThJsMlEQGQCqxQiWInFJ0eCwHG1MeARV7tIADYgsQOn3EPcABERhKXLCoAYYACgKSvAgiNDFZL3XCFEOIH1aH/VqDjSG/QhhjD4ssPoPAsR6aQGWP/Mau6MoEiTKYSw1gzASsA6aLAFG0pdE2VkFw0dJh%2BDGWECIgxyjDDGVUoo2RPDtD0JJsacwhiVG4%2Beho4xWgybyGMuwPG1OzBE/McTth1MCb0DMFoimxOVGWAoIlGwJDRo4Gi0g4reCSrTaa81lrrW2tzfm3AzqS2kvLeSqDywj5YESFxmlkhAjbhZYEPlGhJBmEkFJDQ/gJIsv0JwIVpARWBC4NuCSXAJIMpZdyiS/hJAcoSxJFzcbJXSpALKqDiqVU1rVUmrVTaW3FsNWwTgzQWA6klBlFe4JCPnJZduIr178BEHY262QnrMPSGw0oXDQbdCdrDUwCNe7HPOdc/GjgiaNVwhfpDdNXnHb9y4DNub%2BbC31uLVCEEZgQuVoVZ1vrCRtXNtQEW4Yk2jAPZGTQRpCRe39qDeO4dc74eTunbO/9C7pFLpXSezA67N0f13WSg9hHj1YtPTxy9cab3IDvXOx9tQ42vvfYiT9mwsU/r/WSwDwGlCgeJ%2BLNrMGMLwcQ8hudaHVvevW7IHDgasU7YI5BxjVgSOvs41R6MWRaP0eUUr5jrGEjsbePAGztRdN%2BAgK4UzQno6WYWBJwoY0rekHk1kW3RmdOqYYL0CYmnBMqbGt7/oBmlNmZM770P%2BnSgh7LSsNY9mY8CuO41zgHmM2WtBxLB7s36X%2BYWyQd7hWvthdIBF4YXGBV5YKzN5Lkp/Ast5YEFLaWasNaDU12wLXQvyurR1pA6rk0A7%2B8QAbmxhuZpYAoHUCodRZ6AmMR1eeltjPFxhyXvr5CbdlzoEAwQ9sHajTlpzsa28Ju6ym674/J/T9nz2MYz2gevYSAXwIRfu%2BKtrQ/htg/P/FpAFPypG4M%2BLKG4c%2BBAG4qgFqXaUOV0lAsOWKSOI6/6CBKOmyc66OggmOiBpOOOG6W6O6c6ROR6rO%2B6eAZ6jgFOQaVONO/6dOz6vAjOw6LO36poHOvAXOIGjIfOkGb%2BgucGCGkEou/6K%2BXqEgUufqm%2BeGO%2BCuRGTGKuZGau2KGuMUnAWwF4uulgLGbmbGSURulG/uvGFu/G4e1u6AbuymLuAgTuFhDAZhZmpunugeTuHuAe6mth2mYeuQfu5mQeUeVmDmsexK/hiex%2BEqKeEBlqE%2BU%2BuoN%2BDId%2BEAAWi2BeZaFaxepeUWjmleIArK24gQgQ/gnKNWGgyQiWZWreoRUqHerW3e1KIAkg/g8WPKkoRRDKkg7KXATKZg9WAqgQIRbmnAKR1Rh%2BDqZRfRFR32iwywgGGQzgkgQAA%3D%3D%3D)$Done$

## Links

- [source code](../../../../conceptrodon/descend/pagelivore/cognate_inject.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/cognate_inject.test.hpp)
