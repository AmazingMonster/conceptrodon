<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Erase`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-erase">To Index</a></p>

## Description

`Varybivore::Erase` accepts a list of variables.

- Suppose its first layer is instantiated by an index.
In that case, it returns a function.
When invoked by an operation, the function removes the variable at the index from the list and instantiates the operation with the result.

<pre><code>   Variable<sub>0</sub>, Variable<sub>1</sub>, ..., Variable<sub>I</sub>, ..., Variable<sub>n</sub>
-> I
-> Operation
-> Operation&lt;Variable<sub>0</sub>, Variable<sub>1</sub>, ..., Variable<sub>I-1</sub>, Variable<sub>I+1</sub>, ..., Variable<sub>n</sub>&gt;</code></pre>

- Suppose its first layer is instantiated by two indices, which indicate a left-closed-right-open interval.
In that case, it returns a function.
When invoked by an operation, the function removes the variables of indices within the interval from the list and invokes the operation with the result.

<pre><code>   Variable<sub>0</sub>, Variable<sub>1</sub>, ..., Variable<sub>I</sub>, ..., Variable<sub>J-1</sub>, ..., Variable<sub>n</sub>
-> I, J
-> Operation
-> Operation&lt;Variable<sub>0</sub>, Variable<sub>1</sub>, ..., Variable<sub>I-1</sub>, Variable<sub>J</sub>, ..., Variable<sub>n</sub>&gt;</code></pre>

## Type Signature

```Haskell
Erase ::   auto...
        -> auto...
        -> template<template<auto...> class...>
```

## Structure

```C++
template<auto...>
alias Erase
{
    template<auto>
    alias Page
    {
        template<template<auto...> class>
        alias Rail = RESULT;
    };
}；
```

```C++
template<auto...>
alias Erase
{
    template<auto, auto>
    alias Page
    {
        template<template<auto...> class>
        alias Rail = RESULT;
    };
}；
```

## Examples

We will see two examples that demonstrate two different use cases.

In the first example, we will remove the variable of index one from `0, 1, 2, 2`.
Then, we instantiate `Operation` with the resulting list.

```C++
template<auto...>
struct Operation;

using SupposedResult = Operation<0, 2, 2>;

using Result = Erase<0, 1, 2, 2>::Page<1>::Rail<Operation>;

static_assert(std::same_as<SupposedResult, Result>);
```

In the second example, we will erase variables between indices one and three from `0, 1, 2, 2`. Then, we instantiate `Operation` with the resulting list.

```C++
using SupposedResult_1 = Operation<0, 2>;

using Result_1 = Erase<0, 1, 2, 2>::Page<1, 3>::Rail<Operation>;

static_assert(std::same_as<SupposedResult_1, Result_1>);
```

## Implementation

The implementation is similar to `Varybivore::Amidst`.
We want to count variables one by one up to the desired number.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the variables to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` like when we implement `Varybivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `Erase` using concept expansion.

We will transform variables into types so that we can avoid defining the bodies of helper functions `idyl`.

```C++
template<auto Variable>
struct Vay
{ static constexpr auto value {Variable}; };
```

- In the case where the second layer of `Erase` only accepts one index, we want to remove the variable at the index from the list.

```C++
template<typename, auto>
concept Prefix = true;

template<typename>
struct Ditch {};

template<size_t...I>
struct Ditch<std::index_sequence<I...>>
{
    template
    <
        template<auto...> class Operation,
        Prefix<I>...FrontTargets,
        typename,
        typename...BackTargets
    >
    static consteval auto idyl() -> 
    // Note that `Operation` is invoked by values
    // extracted from the template parameters.
    // This is because we will pack every item
    // of `Variables...` into `Vay`.
    Operation<FrontTargets::value..., BackTargets::value...>;
};
```

`Prefix<I>...FrontTargets` tells compilers that this function template is only allowed when `FrontTargets` satisfies `Prefix<FrontTargets, I>...`
In our case, since `Prefix` always evaluates to `true`, it constrains nothing.

- In the case where the second layer of `Erase` accepts two indices, we want to remove the variables between them.

```C++
template<typename, typename>
struct Expunge {};

template<size_t...I, size_t...J>
struct Expunge<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template
    <
        template<auto...> class Operation,
        // We use `Prefix<I>...` to reach the start of the unwanted variables.
        Prefix<I>...FrontTargets,
        // We use `Prefix<J>...` to enumerate the variables we want to erase.
        Prefix<J>...,
        typename...BackTargets
    >
    static consteval auto idyl() ->
    // Note that `Operation` is invoked by values
    // extracted from the template parameters.
    // This is because we will pack every item
    // of `Variables...` into `Vay`.
    Operation<FrontTargets::value..., BackTargets::value...>;
};
```

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`:

```C++
template<auto...Variables>
struct Erase
{
    template<auto...>
    struct ProtoPage {};

    template<size_t Index>
    struct ProtoPage<Index>
    {
        template<template<auto...> class...Agreements>
        using Rail = decltype
        (
            Ditch<std::make_index_sequence<Index>>
            ::template idyl<Agreements..., Vay<Variables>...>()
        );
    };

    template<size_t Start, size_t End>
    requires (Start <= End)
    struct ProtoPage<Start, End>
    {
        template<template<auto...> class...Agreements>
        using Rail = decltype
        (
            Expunge<std::make_index_sequence<Start>, std::make_index_sequence<End-Start>>
            ::template idyl<Agreements..., Vay<Variables>...>()
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGEgJykrgAyeAyYAHI%2BAEaYxCBmpAAOqAqETgwe3r4ByanpAqHhUSyx8Yl2mA4ZQgRMxARZPn5cgZXVArX1BEWRMXEJtnUNTTmtQ929JWUJAJS2qF7EyOwc5gDMYcjeWADUJutuXo60hACeB9gmGgCCG1s7mPuHyAoE6FhUl9d3twSYLCSBn%2BBzcTGOqF2ADV6ngmNF6N9bm9iF4HLsALICVBEBgXW4mADsFl2byYjmQuzQDDemFUSWIu3BRF2ADcxF4nkSLDDiHCEZgiQARA4k4Win4/f6A4GCw4EM5JRisTCkJkQpE3akrJIEXbKYiYGiqZ5C3YEVFyqwEv4AoHkuVuBVK5hsTUotF6oWEZAIfbE8Xra2/G7S%2B0gw5pABemAA%2BgQAHRJgCS7otnt23oIvtBb3QIBAYSwqljSgAjpyGCtQcmkwnvusrgSA7ddm3zXbZT92883N2e%2B2w13DszUHXLlSDAoFLsAPJK4jkjKkfsD/WG401y51gBixFkABV6sBMAQFCvW2vzYrlWwLzcr9eXSq6xYmMgANZH4gns%2Br55Ng%2B7ZkhSVICLS7K0OqLJ4OgZy0BAsy7AAtBO/4APTobsEQ4k8BAIOS%2BwAGwaPOcRLgIJgkbseAzmErKoB%2BmDoLs0RnGyHKYAoGFYXSFrvv8LFUPuLDmggeGdg6uxJPUKr/MQCj1pebZkYujiUYce6Hsep4KAWkGcnWapvp%2B36/npIAGZg46NhKzYikGkq2jKDqgs6t6qk%2BHlpqi6LYPSXhGFyAaEg5wZSpJEZuNGcaJimaoxfGdYAFI%2BRm/lJIFJ65u8BZFnSpaYBWjDVoctZJpcCW5YWDDFoVxVVo6yU2VctnNsGPZDq5ym9v%2BnWRY6o4tZOTDTnOC4UQw96PphuwAOpPF4SjERoBpGngqhbo247USyhrvn6%2BFPGSDS7KgVBiYtDAAO6GIJHF8vC9CKX17ZrZuZXbkmWmCGZunTVes0LbsS1ciR70baCqXbRVu2QowPjkf8l0Pfyz27NdTy3YI5rw4uShKUBa4Q5thzQ9gRmvW27mutZSYmV%2BOl/j1mo9iBeCUtSEFiNBkKwfBiEoaz7azThyP4YRVGkRN6kMFLNF0QwDFMSxbEcd4XE8bsfGLg4zG7MJqCiUdHYucjMmLmw8kvT1qmTaCP0EH9Z76ZxRm7AzzsWVZLV2XcoV%2BxFZuDRCda8mjmttTcHp%2Bfjgrtf%2BXVRUNFVR2z6bogaOKoMoTAnv6VgB45NpE6b4aOolerJrVdLC22Md6lnRC59lZU16TgE9tyVNl8OToDaCKf1o2I3TnWNzAIaAKMH%2BadXktYTALsABKTB0KauxYNs7k9xAPc9lmOaRtVLBMExsb5SW5aVqVbjV8WDad4%2B7YFknTz87QoIT1PbCCIpSZqixAwbOeJQThyepHCmqdsCIR7rMP2Xci7hR6m/XMeAYzxl2F0BoCV0GxV2NgWqdddiGgrHgQ0M4IDYL1KCA4ZpCHoHgT1Bu65s4t0dNQtUDDiHdx6v1YObkB4jlDtA0e/8Ezf0wNPP%2BxCewLyMCvNeUE6GbyqLQHefD2x700WuDKWUK4nzPnGS%2B9Ub4cOGAQSqpJDHnxMdfEqjoGHIWoY/feL8QBvxonBT%2BhxJHSLPO7IBICLiHHAQKbiMNh4wKYaXHs8Di6l0DMg0uqDhFEHHpPKRv9Z5PzbPIpe7CN5NxznnR0fjsniIbOFJBTkbjoQAFSNKac09CPwGmNIPNgIQB4mmtNuO05pLTan3CrI8Xsxw6DnE1EHcug8RFRJ%2BCwu2stA63HyVgrwSQUhKHQMvLiXh1Eb2WRkUEGg1SJF2GYKptT1l7IUAcmh6x6Fx1OWqLg5zzmXALOw0EXAvkgFXnQUExyNKtWSezZAsZRpKAaBAPMBYFAqihREtwQhNnbOYnch5aosXqMuPE5J6y0VbNSJi/Z6jYxcCOTLE5hwzmXOuSXW55KCCUo3tgF5dK3kfIZY2b5pTflqnWP8wFPi3AgrlrZBJiy6gUmRTCggcLqqIrYMi0ExKMW7JZZSnF2q/mNgJRweYtBOAAFZeB%2BA4FoUgqBOB9ksNYUkixlhcjMOsHgpACCaCNfMD8IBTVmATISMwkgAAcobTUaH8AGjQRFQ3rH0JwSQvAWASA0Gcy11rbUcF4HpM5XqrVGtIHAWAMBEAgEWAQTKBByCUDQICOgcQIgqk4KoUNRFkJEUkLsYAyBKRSATGYXgzFCAkFgnofgggRBiHYFIGQghFAqHUIW0guh3nXUXEkTgPBjVmotd6m1nBZzHGrWdC6baO1dp7X23YA6zC7AgB4Bt9BGQbC4LMXgBatDzAgEgetSRG1kAoBAf9gGQDACkIkGg6i4h6QgNEA90Qwj1DONu3gSHmDEDOLOaI2gqgFo9fW7Js4GC0FQyurA0QvDADBLQWgeluC8CwKfIw4gKPkPw3gVkXED10iqMcVYHqwj/BNSu040RFxYY8FgA9Fo8CpsY6QbjxBoikqFACQwwBThGG9fMKgBhgAKChHgTA10yKWo9ZO4QohxBzqs4utQB6136E0ygaw1h9B4GiHpSA8xUC6gyAx5CeY6GmAdZYMwWblN8iwD5xCthMD2Fli4WqowWhBFqlMfo8R3nbIKJkTwzQ9B5dlll0oAx3ntFltQtLegqs1AsWVmYlWLG1Za5MMIfRys5fmAoZ1KwJC7o4Oa0gmbeDZt2Bezt3be39skIOh9uBR2vrde%2Bz9un5jiSYFgeI8W/WSHWAmfw6xCSSA0JIENJENCmqIoEUTybSCpvdQmIiXA43%2BFDW901kguCmuO0RUbB7s25pAPm3Txay2/orSe44taQNGwAy%2B5tbBOD1BYKyQkyEmAjQUa0BMXAEzWpHUQGLE7ZDTts9IezShHMrt0IkDdTAt2MaGyNsbh6ODHqrccM9TJiDo8x9j7Ymnb3%2BHx4Th9T7EdxH2G6swH7PXg6h6Bl9cOVcDDRxj5CwujCtC4Gc6D1tKAIZXRhlDaHSBm6wzhvDDgLdEZniRsjB7KPUdo/Ri3zHNNsetfgQ01RuMMaJ6ofj/wLfCcSwe8TkmzjSdWNauTCmPXKdU0odTLGtOL3B/pvORmTNmZdBbqzFPZ1U9kA55d1r6cuZ02FqwlhPPefgH5gL4FODBfeKF9zEWotxBizx3zCWksZBS%2B4QrYwMvoCaxVvIaRZZtdn/l6fOWh%2Bcc6K18f6X6vr468UbLdWN/ZC341zr0wKu9f67O1n%2B6V0Tc14LnHS88cE40It/AJPZfuoV1%2Bn1pAts7coCGweyezF3O0JD%2B0JEJHWAu0kC7XeXZ2B1sFB0V0LR/UhyQErWrTVwR0A2R1WDRyvRYAUFZEpFZDx1lDeGHXfzHXzHeWLxs1L3nXkBp0rx0BAATUZ2Zx3UTWGxvyzSPRhz1HOj5xYEIOINIPIIdDeElxwJfU/3WG/yVz/VkLiGwOfQGBIK2VjDIP8FjAoNZQIKpzoCN3g0Q2Qywwtyt2w1w3w3tyNmI1I3I190wCoxozEA90Uy91Y3jyYw4wDx4xXT42QAE3D0EEjzEy8xjzj1kz5CT14BTzUw01Yyz1QL4AMzz1M3MyL3JwYIkDLwXRYKc3YJr2MG7xsHEzixb1lgY3QnhTr2sEi3G2i1ggH3i23z8AgFcAXxCFP331y3yHn032KwGIyGXzq0SzXwYBqyGMqwmI6CmJPz326wP26AXxOh6F6OWPfQWCWAG22NEzZyB04BELEJILZEkP%2BGkIgCWw/zfUUNQM20wG2wGHi3uxTQSDF3WHWFNUjR%2B3TS%2BMJDjUB1v04BBzBweNIH20JEHXAK4CkH8DAOOy4EJB4PWD4PG1BJQO/SGyHWBP4JzSxN/2UzSGcEkCAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/varybivore/erase.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/erase.test.hpp)
