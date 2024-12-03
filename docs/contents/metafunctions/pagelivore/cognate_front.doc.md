<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::CognateFront`

<p style='text-align: right;'><a href="../../../index.md#list-modifications-3">To Index</a></p>

## Description

`Pagelivore::CognateFront` accepts an operation.
Its first layer accepts an amount and returns a function.
When invoked, the function collects arguments of the amount from the front of its argument list and instantiates the operation with the collection.

<pre><code>   Operation
-> I
-> V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>I</sub>, ..., V<sub>n</sub>
-> Operation&lt;V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>I-1</sub>&gt;</code></pre>

## Type Signature

```Haskell
CognateFront ::   template<auto...> class...
               -> auto...
               -> template<auto...>
```

## Structure

```C++
template<template<auto...> class>
alias CognateFront
{
    template<auto>
    alias Page
    {
        template<auto...>
        alias Page = RESULT;
    };
}；
```

## Examples

We will invoke the `Operation` with the first three variables from `0, 1, 2, 2`.

```C++
template<auto...>
struct Operation;

using SupposedResult = Operation<0, 1, 2>;

using Result = CognateFront<Operation>
::Page<3>
::Page<0, 1, 2, 2>;

static_assert(std::same_as<SupposedResult, Result>);
```

## Implementation

The implementation is similar to `Varybivore::Amidst`.
We want to count variables one by one up to the desired number.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the variables to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` like when we implement `Varybivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `CognateFront` using concept expansion.

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
struct Fore {};

template<size_t...I>
struct Fore<std::index_sequence<I...>>
{
    template
    <
        template<auto...> class Operation,
        // We use `Prefix<I>...` to enumerate `Targets`.
        Prefix<I>...Targets,
        typename...
    >
    // Note that `Operation` is invoked by values
    // extracted from the template parameters.
    // This is because we will pack every item
    // of `Variables...` into `Vay`.
    static consteval auto idyl() -> Operation<Targets::value...>;
};
```

`Prefix<I>...Targets` tells compilers that this function template is only allowed when `Targets` satisfies `Prefix<Targets, I>...`
In our case, since `Prefix` always evaluates to `true`, it constrains nothing.

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`:

```C++
template<template<auto...> class Operation>
struct CognateFront
{
    template<size_t Amount>
    struct ProtoPage
    {
        template<auto...Variables>
        using Page = decltype
        (
            Fore<std::make_index_sequence<Amount>>
            ::template idyl<Operation, Vay<Variables>...>()
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGEgMykrgAyeAyYAHI%2BAEaYxCD%2BAJykAA6oCoRODB7evgGp6ZkCoeFRLLHxSbaY9o4CQgRMxAQ5Pn5cgXaYDlkNTQQlkTFxCckKjc2teR22EwNhQ%2BUjSQCUtqhexMjsHOb%2BYcjeWADUJv5uXo60hACeZ9gmGgCCewdHmKfnyOPoWFT3jxeZn2DEOXhOZzcBBuKUwAH0CMQmIQFADnoCCJgWCkDJjIUxLqhjgA1Jp4JjRehop7jYheBzHACyAlQRAYd3RAHYLMdxkxHMhjmgGONMKoUsRjgSiMcAG5iLwfEzc0nEcmUzDKgAiZx52t1gIxWJx/M152hsOYbFIUsJ1OF2xSBGOymImBoqk%2BWuOiMVBvRz0x2NxZqhMMYrDND2etPpzoAYiQldz9f4rAGnkGTXjzhkAF7wggAOhLAElqbGGYm3ZCfiAQGEsKo4UoAI6K0Gh0slosA/zRl4p57HEc%2B40hwGjz5uSdT0dZifnaWoHv3IUGBQKY4AeVhSLqDFIs7nxwA9KfjgB1D5eJSnABsGld7rwqkh5f7q8fPqJjB8cVNB8NAAFSaYBMAIVFH17YcTxdN0PXfe4e1A4hwMgo9YJPC0IzYVcsM%2BAcp3PY4IlZD4CAQfkgN3ACDxMb88C3MJZVQABrTB0GOaIbjlBVMFRAiSLFREmAcTjjioYhUBYH0EAo8dAJSJpI0xYgFBgp4pz5AUhQEUV5VoW0ZTwdAbloCAVmOABaNdaP3LJIVQ9CFHrQzFVXft/UHHU00NQNFJzKFAtDZdPOwdcmE3Hc935RyvJjX0GQ8YBmExeNpMEQ0hy0%2BcQtrPACwRY4nhYDYsoS3KR0rZ1XVZVBlCYcDj1OHK4LHYNTXxQke1VdV6FRSr2tvMJgBdJqlX8b0sEOHCWqnCB5rg6tQzrEAWCYDi4UbMUW0wdtGG2SFSvKgg%2ByI9rR3rBdANM8zIXsuKBBtZkGHq9lIT6ikBuQkt7kspaRxWbyp1TdMXgIm6grCksnmAN0sUYSDqSnEajHG8CvXg%2BrGua844YRthBA0v6vL8rlfPBwFTwAKjp%2BmGdPan6eA7AhGA%2BmmeeWmGd5rmIaBEEwQhL4BEdZHKqNTroZ60mBxqmK6PiqnnjRsahC8FI0iUdAACUBK8WhnTOb1Hvo84NBtLgbTMPsVaeNXjn1hRDeNqbjhStLMAy2QHti82B3rXHQ38akg4myFLeOa3jjMG27f8mlGgFOEoqUZoIDWhRI1Twa3A1rX0k453XZtEujfuYG0w4NZaE4ABWXg/A4LRSFQTgZ0saxeQ2LYlWBHhSAITQa7WNiQHrgAOIt738SQzE5SRJCn/wNHrxJJ/0ThJF4FgJA0S3m9b9uOF4VzLeHlua9IOBYBgRAQA2AgUkuchKDQbE6DiCJI04VRJ/vNZe8khjjAGQIKKQRYzC8E4oQEgpk9D8EECIMQ7ApAyEEIoFQ6gr6kF0NbAA7kiFInAeC1wbk3EebdODbkuC/Z0qAqDHH/oA4BoDwHR0kFA44EAPCf3oJKPYXAVi8EvloNYEAkAfxSF/MgFAIDSNkSAYAUg440CNnEVyEBohUOiGEJoNxSG8D0cwYgNxtzRG0N0S%2Bg8P5EwINuBgtBDG4KwNELwwA3BiFoK5bgvAsAbSMOIVxeA3Q9FlAJKhYpuiXB2IPMImI664OuNEJEZiPBYCoYiPAe8/GkAicQaIRctRYkMMAa4RgR5rCoAYYAChiR4EwAQ2izdB5IOEKIcQ6D2lYLUFQ/B%2BgykoGsNYfQeBoiuUgGsVATosi%2BOsj8E2pgu6WDMMfApaosCTMstUWoWQXAMHcJ4NoegQgLDKBUPQ2sijZGOdMAoGQDyDAuSMa2XQej1DmFMdouzrG9DmM84Y8Q3lfLuT8vkzRAVLGBWsBQvdtgSHIRwRupAj68BPswgBQCQFgIgVwswPDcBwMEQPERQ8qlrHkkwLA8Qdnj0kP4IsiR/CLw0PPSQj4173mSEknepA97%2BC4DPLg95J4bxFfXSQXB17%2BHvKiqhJ8z4gAvlUm%2B99JGPzoa/eRiiBE/zYJwJoLBZScmskwSK6MuCJCLEK1usCiCbMQbIFBXTpA9KUH03Bug45EKYCQvxSKUVouoRwWhz9LjHEYVKYgxrTXmsOGU6O1rbU8L4TIgRpxgRmDJWI6%2BGrdVxDfgomS6aRhGpNdZBNRgrVcEtuotSWidG4JMQYoxpAW1mIsVYhwba7FI0cc4qhbiPFeNoD4ttASynBNbvgMJjgIm%2BLtaoGJmI20JJqFQlJaSbgZJ2K3bJuTB4FKKUoEpgTymjVVTUpq9TGnNMtG29pLq0FutkL0nBrdvWDMqcsqwlgxkTPgNM2Z%2BlOALIIOgJZIzVnrLiJsyJUzfkfL8BAVw3zTmHKhZc621yDzoZw4UJ55ygV6HeQePokwwWkZqH8z5/QsOvNmP0fDTHIXEehYi9YmwEXCK3siyhuCMXlrjRasaVqbVFg0IS/ADrM2CpzRS0gVKaWUCRXygV1q2WcnXpyTkc8zAcqlfKwTnAlUqqvhI9VSAn70KLQW4g%2BqdhGrYSwBQspBSynEyGcYMCZPwPQE65BnSX0YPkB6j9OgEikF9f6shfGg0KpoVqhhTDnMgNc%2B5uUXnTTjFTSW2Rcn/AKYszfKR%2BWBF2fKyMdzWs4SecSHCbzBBU4xuAXwOgDbKBNtbh2lxg9etdusb2mS9iB0uJnZgdxnjvG%2BMHpOoJe7/GhL%2BQuqJy7kCxLXYIDdyTxnbt3VktUh7eDHuKaUoJl6SvXrqQ0ppLTH3OuCxIV9mDwv9KiwYH90GbApO2cBg8vjTx1l/dYNZ6KNmmQQzssj%2BzUOHJY2c0oJGCOPKyCx3DWQGPAqQ%2BR0FuRwU0eQxR%2BYSOOMguY1R8nbHSfYdhfCtBgaBPH04NGlgLm3Meey5iXLEAiWyaEcV8RlLMDUpGDs3lu8QBmGtf4fw9d65strRoWXnJRXGeZ6fWwyryUWbHiAKVRZZX105GYeXUruWSA0HHJJ/gmfotMzroXfHoHq/t5r3NKw1gFIyM4SQQA)

## Links

- [source code](../../../../conceptrodon/descend/pagelivore/cognate_front.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/cognate_front.test.hpp)
