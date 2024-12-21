<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AnyConditional`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-any-conditional">To Index</a></p>

## Description

`Varybivore::AnyConditional` accepts two variables and returns several functions.
Check out **Examples** for more details.
Overall, `AnyConditional` yields one of the two variables according to the boolean evaluation of a condition.

<pre><code>   IfTrue, IfFalse
-> Arg
-> Arg ? IfTrue : IfFalse</code></pre>

<pre><code>   IfTrue, IfFalse
-> Arg
-> Arg::value ? IfTrue : IfFalse</code></pre>

<pre><code>   IfTrue, IfFalse
-> Preds...
-> Args...
-> (...||Preds&lt;Args...&gt;::value) ?
   IfTrue : IfFalse</code></pre>

## Type Signature

This function has multiple signatures.

```Haskell
AnyConditional :: auto... -> auto... -> auto
```

```Haskell
AnyConditional :: auto... -> typename... -> auto
```

```Haskell
AnyConditional ::   auto... 
                 -> template<typename...> class...
                 -> typename...
                 -> auto
```

```Haskell
AnyConditional ::   auto... 
                 -> template<auto...> class...
                 -> auto...
                 -> auto
```

## Structure

```C++
template<auto, auto>
struct AnyConditional
{
    template<auto...>
    alias Page
    {
        static constexpr auto value
        {RESULT};
    };

    template<typename...>
    alias Mold
    {
        static constexpr auto value
        {RESULT};
    };

    template<template<typename...> class...>
    alias Road
    {
        template<typename...>
        alias Mold
        {
            static constexpr auto value
            {RESULT};
        };
    };

    template<template<auto...> class...>
    alias Rail
    {
        template<auto...>
        alias Page
        {
            static constexpr auto value
            {RESULT};
        };
    };
};
```

## Examples

We will see four examples that present different use cases of `Varybivore::AnyConditional`:

```C++
using Select = AnyConditional<1, 0>;
```

- The template member `Page` of `Select` is a function that returns `1` if any argument can be evaluated as `true`.
Otherwise, it returns `0`.

```C++
static_assert(Select::Page<1, 2>::value == 1);
static_assert(Select::Page<0, 2>::value == 1);
static_assert(Select::Page<0, 0>::value == 0);
```

- The template member `Mold` of `Select` is a function that returns `1` if the value result of any of its arguments can be evaluated as `true`.
Otherwise, it returns `0`.

```C++
static_assert(
    Select::Mold
    <
        std::integral_constant<int, 1>, 
        std::integral_constant<int, 2>
    >::value == 1
);

static_assert(
    Select::Mold
    <
        std::integral_constant<int, 0>, 
        std::integral_constant<int, 2>
    >::value == 1
);

static_assert(
    Select::Mold
    <
        std::integral_constant<int, 0>, 
        std::integral_constant<int, 0>
    >::value == 0
);
```

- `Select::Road` accepts a list of predicates and returns a function.
When invoked, the function returns `1` if the argument list satisfies any of the predicates;
otherwise, the function returns `0`.

```C++
struct VoidInt;

template<typename...>
struct VoidTester: public std::false_type {};

template<>
struct VoidTester<void>: public std::true_type {};

template<>
struct VoidTester<VoidInt>: public std::true_type {};

template<typename...>
struct IntTester: public std::false_type {};

template<>
struct IntTester<int>: public std::true_type {};

template<>
struct IntTester<VoidInt>: public std::true_type {};

template<typename...Args>
using Metafunction = Select
::Road<VoidTester, IntTester>
::Mold<Args...>;

static_assert(Metafunction<int>::value == 1);
static_assert(Metafunction<void>::value == 1);
static_assert(Metafunction<VoidInt>::value == 1);
static_assert(Metafunction<double>::value == 0);
static_assert(Select::Road<>::Mold<>::value == 0);
```

- `Select::Rail` accepts a list of predicates and returns a function.
When invoked, the function returns `1` if the argument list satisfies any of the predicates;
otherwise, the function returns `0`.

```C++
template<auto...>
struct NonpositiveTester: public std::false_type {};

template<auto I>
requires (I <= 0 )
struct NonpositiveTester<I>: public std::true_type {};

template<auto...>
struct NonnegativeTester: public std::false_type {};

template<auto I>
requires (0 <= I)
struct NonnegativeTester<I>: public std::true_type {};

template<auto...Args>
using Metafunction_1 = Select
::Rail<NonpositiveTester, NonnegativeTester>
::Page<Args...>;

static_assert(Metafunction_1<1>::value == 1);
static_assert(Metafunction_1<-1>::value == 1);
static_assert(Metafunction_1<0>::value == 1);
static_assert(Metafunction_1<nullptr>::value == 0);
static_assert(Select::Rail<>::Page<>::value == 0);
```

## Implementation

The implementation is straightforward. [Check out this test to see how it works.](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxBIA7BqkAA6oCoRODB7evnrJqY4CQSHhLFExXPG2mPb5DEIETMQEmT5%2BXJXV6XUNBIVhkdFxCQr1jc3ZbcPdvcWlgwCUtqhexMjsHASYLIkGGyYAzG5MXkQA1ACSVAAqxF6YpCdHpxcAYmJK%2B9gmGgCCwzcOJ2%2BDAAnh4GPgamIvt8TLErD8ToiThstjtMPtDsdUB9oUiTn8vACACKYep0E6wqyxIn7eEwhFIlHbJi7A6PVDnHEMxHETAARy8eF5Ck53PxBH%2BBBOJLJtAxZy53zxlPFLLwyBOaAYw0wqkSxAeWJOADcxLcKXCLtdbrCaXsLBa7XTcYzNszWZinoq8byBULMCKIGAwGc5i7EQTiaSmHR5d6kSrJo4NVqdXqDeyTWbMBaLC83ujqbTHbToWWfuWla7USz0WysQA6JvfYC8zaMAgKeOIrypIwnZRMYA5/ZE6XR2MHCBNhuwtxzpPqgD6omGGIiqE8HwgLbbbEECjmYb2n3tlbxTLRGPZM%2B%2BxGAXZP4dVyc1AjT%2BsNp0Hw6XxtzMoxnKU4znOC71MmK5MGuBwbluJ47veh7HtgIAgKa3iFk6lY4WKl61hiBDAokjCsJgM7YPQ%2B6dt2Jy9sEwAnAAsp46AUnsY6AZObjTk2YGxG4i7IFBMFuHBwHYBAlHtgeaEYbcR44meFZ4W6V4HERJHMGwFFUR2j6fGKQlvtqGzpl%2BHIsbQ6B/rm46yhivGzgJ4FqsJq4EOum4SVJemyeh2aKSecnZiWyn0hF57Vu6dZuPhHqaaROl8SemoGAoCgzsovL4KIGwGc%2BkZStlqBEAASqgTDoM%2BlLPsqYoXmpBEacRSXkU20nUQVDVIvR/ZWWxo72UBjmgS5AlCSJnmwd527ZZguW1o%2BbidfpoHBQFmFBaezo9Yi8WxYl2ntQ2q0HrReLGamZmfpmA22XVCZwsN3FOfxgkQcuHlefBknzYt%2BUYmdnbrahm0KShIWYWFdLKkW4XPgdhFNQlrXHaDaXQZlTb/eqS20X1jEVVV7FjiV5WVdVBy43lAag6WYq4RFjU1glKOxTeKXYJjGVZTleOA0%2BRkSoSxXEKVqBlSNjNwo9%2B3s9ejZNgAag0eBMBE9DdVWeI9n2jE/iOHEvcBPFjfOE2fe50HTWJs0ITT%2BMHKrxDq5rdNc1DENKbDut%2B3LyIK/WRAzi7btaxdSJXe%2BN0ZkahsPXtdlcabb3jR9blTT9PmO4LbhhxrWug17mDbSXMM1fDvuIojQdxXXnOzqlyDpdjDa5wGBP6ycUvkkN5OSyN1P87Tbc%2B2WVeVgA9AAVHP88L1P0Kz3PlzYEIlzz0vPwrwvi84WYezBC3XhYOxbhaqsiQ0ULEWEycQhVJgAJDUCoICBC6RQgcbQnBo48qW%2BFPKeJxLgBilP/QBk0sbRAIBAR%2B1Q0KGwxL/MwHxy6jiGlwY8dJoEZVgfAp%2BDgkFDligkE4aCNrySNnaMc2CGa/CtkuGBjRCGIJAMgg45D/5UNCpg42GgcHTxAWA4YJwuCVjwUoVhz4EHPwIGhAaNUDgB2GOgNCwQNitjECuGOhhbaaPuBIk89xVEEHUSATRmBtG0F0aZfRGJDEUNoug8GNCsHQiEVAphLC4GyKIQokASjGYqKTmojRghrHEB0ddBxBwnE8OwKYsJ5iIlaOibY2JghHGCHuJQwyOt2Jg2oaTDxPwvERSkQQ/x7DgmFIxGYixVibF2MmNk%2BJuS/4fGSYUy6qTLGRJaVkgxnTEnKOKXwjiQ1IHfAqcvER4DnHeMlCcZWqA8DoDOO03a3wkYtS0mRemPwiqrPWegURGwYgnESF4TW6pxQWKoAWJciVcy2gYdCPZ85b4nLWRsi50QMTGjOeg65tzaD3PCSAEWmAXmtTeZPQBXzFS/LOQC4gGI/mbPaahMFdyNRQphXCkiCLsJIrrkdQ5XNoQnK2QQdFIA8UQoJf0p5tAlDEpHLLRFEVkU/JFgCOl6KcnTVxTc/FDy0JEtebVHlny64ooFVKIV4DAXOzOXS0F4rmWSuhTcWFMruVkt5RStGVKGx3gfIqe%2BTFoxUC8AwBw6RSYPwCdCNCxMqb5zRaqsg5xBDCtvoo1iGJLVjyfAjY5Pj8GsNtfUe1jqagitcSU/hdCKlVNjXah1TqBBApBbw6GabxEZujdIuBcamAJtzQwTFGqcUYKmcbeh4VM0VuzYm9IGJ0BLHdimyZtC/6lszr4th8iPWUwaRtJRKjC3mmLYIj5O8FliL2JWL5jdFUrNCAIXIaRjSYAZUyyFrLnmGqpMa%2BVrMOZGgVLfX0gphQnAgGcc%2B0yThhijdu3dKR92Ht9XGYKx6WUWOlfC2Vl6fgbqVk3ApJyd0MBCMANUB6j3apPY8s94GjVLt2Q3W9ioH3%2BkDBoN9xtQw0qVScBDSGUP/p1Big4d6xXgow1K/VnLSW4egyHZsSFrXd0rdWmoS4uAurkQ4d1IBe6mwQ3uxwqHfX3Bo9YujgaCkkOHKGpC9NI2MJHTG9t8ac0ieMW4YxEyi1NvTQwttEAhMmfSKJjEABaCzjbB0ttwWWghDnO0CGc1w/tVnPPDsgqOvzNbAtuAYF4WgtBr6Mcs/O6zQ7bM%2BdYRJwJMmp1g04d85L7iBEVI4AsWgnAACsvA/AcC0KQVAnB5yWGsPiJYKwRyHx4KQBRtXSsLAANYgAq5IBsGhJDlD2BoCrGgzAADZZtmAAByLf0JwSQvAWASA0AkGrdWGscF4AoEACQetaAWHAWAMBEAgCWAQG5BByCUDQFsOg0RQhkU4KoRbs2XOzckCcYAyANRSAbGYXgC1CAkA2XofgggRBiHYFIGQghFAqHUL10gug2gAHdomJE4DwMrlXquaF4PtgA8sce7JxUBUBOF9n7f2AdA/ESNswz6PAvfoAacwexsG8FO6V0gEAkDPcSK9sgFAIBi4lyAYAUgzB8DoJco7EAIik9IBEYIDRgQE94Fr5gxBgTk4iNocd3BeDPeouThgtBdcY6wBELwwBDjxaOxb0gWAWCGGAOIB3/onUHvd3V3Uz9jhrC61Y8rGOIURGiUbjwWANcSjwJtj3B7iAbiUCSb3RgIVGFJwsKgBgHzKzwJgbH5OtJ6%2BR8IUQ4gkew/kEoNQGusf6B9ygaw1h9B4AiEdyACxUDX3SO7lzajRymGa5YMwe2M%2BuywAPiACw7DyPSC4cEYxWikECMEPoJQBhtHk%2BkLfORf01GmP0Mo7Q18CC6KMTwLQ9Cr5rffnoe%2BZiH9sCMJoj/xjf6mA/yvwkBXza1WBANWw4Cq1IF2zJ04Hp2%2B1%2B3%2B0B2BzZ2fVwEhx506zmAF0LwWAQEwCqgGGX1IEG0kD2AbAAE49hYhJAxszBJBZttsKtZtKDID1tSBNs%2BcGxZsuBZtFtKDFs%2BDhsuAKtqDZsYCNd9tDtjtutC9hcrsRcbsqdjhHtpdUAuc3sPsOAGgWBjRYgXMmBMZ%2BwuBKCGwuBRtwcIQod1E2gm94cG9pAm9UdW8MddBFdccmB8cLcicoCScMcKcVCpRacHhiA9CDCjCW4fdxEzCLDSMIBOdxducKRD4zAcC5DetztRcNCkjog1CZducQBdD9CXMoijBTCuAEgaBaAVdKB1cMcDcdca9GijcTczdiEPcrcOwbc7cNdHdndXd2Ua8vcfc/c6t8BeRA8AwNdQ9kBw8a8o8NdY94934k8McU808usM8s9MAc9RiGJ5Di8hwFAy8K8q9GAa97D69EcnDZAXD0c6t3CO8C8p8rBLBe9%2B94Ah8R93xOBx9zFJ9u8Z859ogF9pjB8b8a0N93A/9t9d8ihgCj9z8T9YSz88h0hL8D9r8X8ag39T8JgAlOgf9MTZgJgf98SADGgSTD9QDlhwDsFIDoDYD6t4DiiIjjDGJTDzDRt0DrCsC%2Bd0jBcjxSACCiCYgSDo8OCuCzCxtYgxDYhYg9hJAGC/s2hmTpDbBZChSFD4AlDbt7t8iciJd3s2BOBdCmcWAFBjQNRjQuS0RhgrDMDoc7DZAHCbja97i28QA9hSBPDvDCdGT/C9tOBKc7tjgac6dzT/tLTrSTQ7SlopQEijTkjec9hBT5ClCCi8ipcsyYhrTEhEg/xTClx7SCBmEwi/slcajohVd6i6sWj7cusGy2jzcusujBAej7dxjMAncXcxAhiPcRi881hxiA8FNpiMdZj5iPdFiY8%2B8VjE8RyBdXZNjeBtiUhdjNh9iC9Mi%2BAS8Tjy9K9q8PcriEcJBbiUcW8HidBvTnjjAgSbBY8l9viah3cp5wlXjrBZ8yd58NlwSSCcT18IBXAKT4T99SSkhkSBAKTj8CggCsTn9CS79yTUSCSOhkLACESEKyTugKTJgqT4LSTaT2sIDo8mSpDWSKzoyrSbT4z8pEyMCiB%2BT%2BcMizt8DCCsBxTfCpSQAzAzC9g9gKtptxttsBLYh%2BDJCAjOAZCTs8DSCQBJAKsqCKtFs5tKDJBKDFSaCuAfTo89ggy4CDtWK%2BtICwdJLgyjKhSFgM9UhnBJAgA%3D)

## Links

- [source code](../../../../conceptrodon/varybivore/any_conditional.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/any_conditional.test.hpp)
