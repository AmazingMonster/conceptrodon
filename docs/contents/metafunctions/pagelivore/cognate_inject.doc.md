<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::CognateInject`

<p style='text-align: right;'><a href="../../../index.md#list-modifications-3">To Index</a></p>

## Description

`Pagelivore::CognateInject` accepts an operation.
Its first layer accepts an index, which indicates a location in a list.
Its second layer accepts a list of new variables and returns a function.
When invoked, the function injects new variables into the location of its argument list and instantiates the operation with the result.

<pre><code>   Operation
-> I
-> NewVariables...
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I</sub>, ..., Arg<sub>n</sub>
-> Operation&lt;Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>, NewVariables..., Arg<sub>I</sub>, ..., Arg<sub>n</sub>&gt;</code></pre>

## Type Signature

```Haskell
CognateInject ::   template<auto...> class...
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
template<auto...>
struct Operation;

using SupposedResult = Operation<0, 10, 11, 1, 2>;

using Result = CognateInject<Operation>
::Page<1>
::Page<10, 11>
::Page<0, 1, 2>;

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
struct Monotony
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
        // of `Variables...` into `Monotony`.
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
                    ::template idyl<Operation, Monotony<Variables>...>()
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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIACcGqQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCcmpCi1tHQXdEwNDldVjAJS2qF7EyOwc5oERyN5YANQmgW5ejrSEAJ6n2CYaAIK7%2B4eYJ2fIE%2BhYVHcPzzMewYBy8x1ObgI1zSmAA%2BgRiExCAp/k8AQB6ABU2MxRwAsgJUEQGNcjjjMeiAQRMCw0gZqRCmBdUEcAGqtPBMWL0VGPCbELwOfGE4m3NEAdgsRzmjmQRzQDAmmFUaWIRyZRCOADcxF53iZJeziJzuZgDQARU5Si1WgEY8lHZTETA0VRknGUp7U2n0s1nKEw5hsUjq5m8hVbNIER3O10fc1HBF621op5YnFHbAMY3IBDu7Gex7eulMBn%2B6GMVh%2B%2B5PfmC6NZnN5g1WcWWwJWVNFmklstuLIALzhBAAdGOAJK8utCxt4XMQ74gEARLCqWFKACOepBfrc47HI/%2BgRrz0lAKOF8TPd9jOZB6imAA7kaTfQUcfz5fp9GnUTUMomGAM0nkvE5JROEDQMvYsb0gqCPjcT94NAmDS13DVUAPO55QMBQFCOAB5GFEUaUgkOQi90XRI4AHV3i8JQTgANg0J0XTwVQIUnY8sJYxMWUYHwEjQ5iNAAMWIWQABVWiAggURYw84IomN2M4s5uOwA8JOk2TMHksjlIogNKzYA8LCYZAAGsZOIOSUSMy9eQomU53lAQlR1WhQ01PB0GuWgIGWI4AFpnOQqjRIfZ8OS5N9eI0dVnSOCJtEwBxMHQFKGETBB3mdAgNhykylMeCjIqiIl3gIBBS1EojhMaEw%2BLwfCIi1VArMyo5YlJLy9QcsqIuo5UEUs6ksqoSSWFy6rrxEtJWiraliAUUqKIakicghHTBFs%2Byl36zADxDaKXzizA1rHEMLOs/b9IUQ7dWOscj07IaLxtDs7WU1C%2Bww%2B8n3O013xPUCGIiYBHUA/VAgTX8iAAoCITO2KQawj9voldt3vtDMPGAZhqXHBg0qFclCz%2B3cqdvIgMewHCmDwwjiNLbaP1rJMhQJonMBJsmCDtM9fvmvtB2HI4SdXcKL2/GM/yR4CPrA96XK56MhFwhByNAlsdeQmmzgBsdUeNC7Qf1%2BC5YR/8YctqC9cclSrx9NDacwsdgbfGXncvCGjGhoD4yOLADhM%2B2KIgCPfYqqrcrqx96MYpgjkWxE2BW1PLKs7LZpd3t3jyph0Gj53IswLVGFy9ZgDzGr3ioLwQUaI4BFoUkxFoVBH3wgR3lQVnGnW32KNneczkXEAWCYLrYRXZV10wLdGC2LiGGlzGwZH5Clyp%2BXEbts5TdfS76dLlTd9F94/ICiFNrZgQQwJBg/xJCEvcuu56aC8/QOWFNlYUS%2BqrZCwCfqAOglfd2B5HjAGdDSRg8kfbgyyAHRWwdNZMyQCAPeNtFYQlgfAtgggrqHkxiAz6bYAHkUNm4Y2I5CGYAQSQn2/soboNOPDSSB9kZnEYcw%2BSZ8sanhxuA9M5IJEUzxtiI4UlLryXzBSaRkjJGFjtECV4YJYZuAjJgKMFsuy0PoVOdWLNGrs1xk8NhRwhBeDSMUTKAAlS6XhaDRk4WYraAgISpCOFwXxXAuAhiCUcMwb1wHWOcQoVx7i4ZHB5mhfm6VBZnHvk1Dmjwlz4LOFwXkWTD5uH8cE3JGT8m8LcAEkMYTyHgNcsgWETMlBtAgJPBQVYGnvjcFEmJIZbH2MyE4lxbi7j/w7BwVYtBOD%2BF4H4DgWhSCoE4IhSw1hpTrE2PqIEPBSAEE0OM1YVkAgAA4RxMUCJIMw4pJCSH8EcwIGh/BJCOfoTgkheAsAkBoVIsz5mLI4LwR6qRdlzPGaQOAsAYCIBAOsAgaQLjkEoGgWkdAEhRCrJwVQRymIhSYpII4wBkByikCOMwvBMqEBIH5PQ/BBAiDEOwKQMhBCKBUOoEFpBdBBMfIiNInAeATKmTMvZCzOAEQuHC6MqAqBHExdi3F%2BLCV%2BMkCSo4EAPDIvoGqXYXBli8GBVoVYEAkBIrSCisgFAIAmrNSAYAUgzB8DoCtR6EBYjCtiBEVo1w%2BW8HdcwYg1wCKxAFt60gSLiEEAIgwduwqsCxC8MAOhtBaCPW4LwLA08jDiHZfgZ0Dg8CVxTfM5U6ULjbG2REakkz2VXFiIif1HgsDCoRHgD5qbSCV2ILEAZ5oaSGGAFcIwezVhUAMMABQrI8BPgarM7ZNLhCiHEIyudLK1DCs5foPtKBrDWH0HgWIj1ICrAHo0FNIVvicNMCsywZhfkduNFgA9QUejJJyC4de0w/BBLCBEYYVRRhBOKNkAQH69CAcaAsEYiQgl2BfQIfoUxPCdD0DBvNcHJiDB/Ysf9th0Mgeg%2BhiDf6oOrAUOsrYEgBUcGmaQH5vA/kyqxTivFBKiXKrMKq3AFKtVbN1Tsodqwi5YESE%2Bw5khAgjiSIEK5GgLmSBYg8piSQXkcDeaQD5gQuCnK4ExI5TztP%2BEkFwR5gQmI0eFX8gFIAgVDrBZCo10LxXwotVazVaK2CcFaCwLU4oQopwOH2vxSQRyaaLfgIg97qWyDpYu6Qy6lCrvZboe13KmC8tTZR6jtGRUcDFbCi4rdpWee875xmAcuBBZC6q9VprNUnCBGYXj%2BrQX2ZcwkBFlrUAatGEVnz/mjDlaKTQNxCRnWuvZb6z1IaJv%2BsDcGttYbEGRujdmzAcaE2dxTds9Nfas3zJzS%2Bgtwri3IFLSGit9RhU1rrdcBt2x5nNtbdsjtXalA9ozf2yGNmR2AXHZOx806Q1zuiwy2LsgV1svmUljdg7L1WEsLu/d8Aj1RhyKe89cNYfWBvXRu9flLpI%2BfahvwEBXB4ZCOvQjSwAOZCA7kRDBRqclByJT7DKHGjwfaPTz9hP2cEcw5B5DuGueC/mPzojFG1gbHIzq5TmXzOcCSl5nzfmDBlYqyORKEBOPhbqxpxr/HSCCdGE%2Bqtqn1NBZk%2BKR54pxTnLMHJwzZn2UWdsFZvjILDV2aQDCiV7XWvEDc9sTz8qWAKC1HKLU5WRy%2BgmGSsLlL0CRdpQukHTL5DxYhzoEAwQUtpf5bLoVzvRWOclYV4gLAQ9h4j1HmP0Y1WdZqwkXXgR9ce7BcahvZq/ed81SAcP9jYSR6SLCWvDTy%2B4odcN1alAxvzOm16tt8/ZvJJDQtwQS2F97dW/GxNyaQ3bczXdtNeBc2OEO%2By47p223narfMq7nrbtNuNI93gz3u29szZ9tv32x0TqnYGQHKLFPCQUHZlDPNdbPaHYwbdeHGtR9ZHE9TgdERcTHa9W9BIe9fHQ9HnV9End9YXL9CnMXKndIGnRoMnMDZnYg1neoWDJoIXfIbnNnPoPnCoAXfDAYMnOYNoFnYjSXDZCXKtOXIvDgRXSvcPbUGvNCCYDjePbjPXPVA3I3YTSjM3EAMwILQIQIfwfwGTfxDQLQ8UHTJ3X5TgSzazD3A5EAQzEcEzfwcUMwHQwzRTSQDQe1KtQIQvUw/5d3A1SjUlEwujMw3w/ZdtEbV9SQIAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/pagelivore/cognate_inject.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/cognate_inject.test.hpp)
