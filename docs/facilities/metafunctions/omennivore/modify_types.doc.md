<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::ModifyTypes`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-modify-types">To Index</a></p>

## Description

`Omennivore::ModifyTypes` accepts a list of `std::index_sequence`, which indicates distances between adjacent indices.
Its first layer accepts an operation and returns a function.
When invoked, the function transforms the arguments from its argument list according to the `std::index_sequence`s using the operation.
The result will be stored inside `Capsule`.

<pre><code>   std::make_index_sequence&lt;I<sub>0</sub>&gt;,
   std::make_index_sequence&lt;I<sub>1</sub>&gt;,
                    &vellip;
   std::make_index_sequence&lt;I<sub>n</sub>&gt;
-> Transf
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>m</sub>
-> Capsule
   <
             Arg<sub>0</sub>,
             Arg<sub>1</sub>,
              &vellip;
       Arg<sub>I<sub>0</sub>-1</sub>, Transf&lt;Arg<sub>I<sub>0</sub></sub>&gt;, Arg<sub>I<sub>0</sub>+1</sub>,
       Arg<sub>I<sub>1</sub>-1</sub>, Transf&lt;Arg<sub>I<sub>1</sub></sub>&gt;, Arg<sub>I<sub>1</sub>+1</sub>,
              &vellip;
       Arg<sub>I<sub>n</sub>-1</sub>, Transf&lt;Arg<sub>I<sub>n</sub></sub>&gt;, Arg<sub>I<sub>n</sub>+1</sub>,
              &vellip;
             Arg<sub>m</sub>
   ></code></pre>

## Type Signature

```Haskell
ModifyTypes ::   typename...
              -> template<typename...> class...
              -> template<typename...>
```

## Structure

```C++
template<typename...>
struct ModifyTypes
{
    template<template<typename...> class>
    alias Road
    {
        template<typename...>
        alias Mold = RESULT;
    };
};
```

## Examples

We will apply `UnaryMinus` to elements of indices `1, 3, 5` from `Vay<0>, Vay<1>, Vay<2>, Vay<3>, Vay<4>, Vay<5>`.
To do so, we will calculate the distance from one index to its immediate next.

We will keep the first index, `1`, since it represents how many elements we must pass to reach the first target position. We subtract an additional one from the rest since we only need the number of elements separating two targets.

<pre><code>   1, 3, 5
-> std::make_index_sequence&lt;1&gt;,
   std::make_index_sequence&lt;3-1-1&gt;,
   std::make_index_container&lt;5-3-1&gt;</code></pre>

We will pass these sequences to `ModifyTypes`.

```C++
template<auto I>
struct Vay
{ static constexpr auto value {I}; };

template<typename Vay>
struct UnaryMinusHelper
{
    using type = Vay<-Vay::value>;
};

template<typename...Args>
using UnaryMinus = UnaryMinusHelper<Args...>::type;

template<typename...>
struct Capsule;

template<typename...Args>
using Metafunction = ModifyTypes
<
    std::make_index_sequence<1>,
    std::make_index_sequence<3-1-1>,
    std::make_index_sequence<5-3-1>
>
::Road<UnaryMinus>
::Mold<Args...>;

using SupposedResult = Capsule<Vay<0>, Vay<-1>, Vay<2>, Vay<-3>, Vay<4>, Vay<-5>>;

using Result = Metafunction<Vay<0>, Vay<1>, Vay<2>, Vay<3>, Vay<4>, Vay<5>>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The implementation of `ModifyTypes` is similar to that of `Omennivore::InsertValues`.
We will perform recursion over the total number of the `std::index_sequence`s.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  - Handle several `std::index_sequence`s from the front of the list;
  - Invoke itself to deal with the rest;
  - Concatenate two resolved parts.

We will use the following helper class template to concatenate two parts.

```C++
template<typename...>
struct ExtendFront {};

template<template<typename...> class Container, typename...Elements>
struct ExtendFront<Container<Elements...>>
{
    template<typename...NewElements>
    using Mold = Container<NewElements..., Elements...>;
};
```

We will use `Prefix` to enumerate arguments like in `Typelivore::Amidst`.

```C++
template<typename, size_t>
concept Prefix = true;
```

`Capsule` is used to store the result. We declare `Capsule` as follows.

```C++
template<typename...>
struct Capsule;
```

Here is a simplified version of the implementation.

```C++
template<typename...>
struct ModifyTypes {};

/**** Base Case ****/
template<auto...I>
struct ModifyTypes<std::index_sequence<I...>>
{
    template<template<typename...> class Operation>
    struct ProtoRoad
    {
        template
        <
            // We use `Prefix<I>...` to enumerate `FrontTargets`.
            Prefix<I>...FrontTargets,
            // We will transform the next argument.
            typename Target,
            typename...BackTargets
        >
        static consteval auto idyl()
        -> Capsule
        <
            FrontTargets...,
            Operation<Target>,
            BackTargets...
        >;

        template<typename...Agreements>
        using Mold = decltype(idyl<Agreements...>());
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

template<auto...I, auto...J>
struct ModifyTypes<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template<template<typename...> class Operation>
    struct ProtoRoad
    {
        template
        <
            // We use `Prefix<I>...` to enumerate `FrontTargets`.
            Prefix<I>...FrontTargets,
            // We will transform the next argument.
            typename FirstTarget,
            // We use `Prefix<J>...` to go across the distance
            // between two targets.
            Prefix<J>...MiddleTargets,
            // We will transform the next argument.
            typename SecondTarget,
            typename...BackTargets
        >
        static consteval auto idyl()
        -> Capsule
        <
            FrontTargets...,
            Operation<FirstTarget>,
            MiddleTargets...,
            Operation<SecondTarget>,
            BackTargets...
        >;

        template<typename...Agreements>
        using Mold = decltype(idyl<Agreements...>());
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

/**** Recursive Case ****/
template<auto...I, auto...J, typename...OtherSequences>
struct ModifyTypes<std::index_sequence<I...>, std::index_sequence<J...>, OtherSequences...>
{
    template<template<typename...> class Operation>
    struct ProtoRoad
    {
        template
        <
            // We use `Prefix<I>...` to enumerate `FrontTargets`.
            Prefix<I>...FrontTargets,
            // We will transform the next argument.
            typename FirstTarget,
            // We use `Prefix<J>...` to go across the distance
            // between two targets.
            Prefix<J>...MiddleTargets,
            // We will transform the next argument.
            typename SecondTarget,
            typename...BackTargets
        >
        static consteval auto idyl()
        -> ExtendFront
        <
            typename ModifyTypes<OtherSequences...>
            ::template Road<Operation>
            ::template Mold<BackTargets...>
        >
        ::template Mold
        <
            FrontTargets...,
            Operation<FirstTarget>,
            MiddleTargets...,
            Operation<SecondTarget>
        >;

        template<typename...Agreements>
        using Mold = decltype(idyl<Agreements...>());
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwA7KSuADJ4DJgAcj4ARpjEIJL%2BpAAOqAqETgwe3r4BwemZjgLhkTEs8YnJtpj2JQxCBEzEBLk%2BfkG19dlNLQRl0XEJSSkKza3t%2BV3j/YMVVaMAlLaoXsTI7Bzm/hHI3lgA1Cb%2Bbl6OtIQAnifYJhoAgjt7B5jHp8jj6FhUt/dPZl2DH2XiOJzcBCuqUwAH0CMQmIQFH9Hv8APQAKixGMO2FUBFcADFiLJDtiMWj/gSWKkDATwZDocw2AA6Nkoh7jYheBy4/FEkmCY6BKyBAAiJysqMe1NpTHpp1ldMwDKhjFYmDZLNuh32TAUCkOHkEiMiZEOjPVrLZ2HobEEyP8d0eXJ5BD5BIY6GJsnBxuaEQS4NtmHtBAUWr%2BTv%2BJhF/0OCYtoblCohauZmrZUUwAHcQ2HHc6HonDl5MkZDgBZTzod5io2yU1B07ZvN2xjhrWkXHth2R6P%2BKVPcWSmOPTHYw7KYiYGiqMnYyky5PK1VMjXdzIAL1hBA5aGBmFS7uns7w85O9fhXhVg7HDwnWKNTFSCi89AXWKXDyV8tvafXa1tWjF1r15NwXzfehR2lB9ySrDA8CoK4ABU1UNclv1/VNLQzfsi1dXlq3wZC0OhQ1Y1FCU71gx8cQsfU3ggpRPwpKkVz/cEmHOVAtQASQ5Qj3WIpDUPQ8EvhAEAIiwVQYSUABHG9D3BPj8I5Sj40TbD/x0tcrUzYDsF1AwDUOAB5aEEQaDkSyEqcSSIAAlVAmHQLSE00x4SxLPTvJ8zzTg8gLEzRNFDgAdTeMs3hMAA2DRTznVTbkjBKLVQQ5GB8BI/2OBKfUEFCWmATBw3ijRtX8kLEyS88UqdLVCoIYriFK8NSGCmqwsit4czoWgLQRBgFH4YgWAtBA3kifFDhKnLBCq4sau09MNUOVr2s66qVtwjUtQY5AAGtNrK5EdpLWyQtmRxkF1ARxkwAA3MQ5p4w48HQK5aAgJYusTABaHUINfd8VQuxNwX%2BgLmtOzs2W25aVosqz5WycE4duRHkYTQ6TpKs7IwhwK7hop5iaTGlV0VNagIeYAZ1DDtC2h0ty2ABDaFrS9DiwfZLQgT7vvBenGYLfDfr%2BsnLpHMngr0xUOJw2nDJ1PUDS1UXMCZh0roTMsIg5ly3LrBzUGc1z3NOLWdfhoyYOHaih3YqnONObiiH47sPd4tkAClBLA4TENI8TTkk6SvUwOTFOUzZVPwzcCHQKSZOj%2BTMCUxh49OP31JA4ch18pXdJL/S8PZJ0TP1Q1LNymyC7soOzYttzgq8pGfL8zvLqCimSx6qK2dihK6tUBrsDSjQMqyhgcuskeNFhgnyoSpacYcs9x9OATGrZZe2rO7GccHvqBqGwxRpICaCCmw4Zvdeaw3XnG9rYQ5CTwYhxjh4/kdP4e%2BVEozmSrnVK7J0pEEOMATKTBkAkjMrfN4%2BBZgqX7qFcK8QCA5m1gwC0OZMoTHahGVmJYx7ggDnvFklZProHoHDBQf8VoAP6rQQa8JL5jRvnfB%2Bc02oLQIC/ZGb83hCEwAedAv9SGrUAoZPGDDWZ6x8jdPAd0DyPReoNH2H0vo/T%2BhTIGVcQZQXBj3SGfczEw0FC1FeEYEbSITHXay6NTif2/jYw%2Be4nRMJqjQ749DbFdgcSjeuLi3BiIkZjbxwT5GBPZBTKMzsKYKwAgZTWDNtYFiUSWA2FZqxc1NnzWgAsha0BFhk22dijKSwdjLJ295i6uxwmXGmsj8LVw1myG2WTG6JlyUbS2ptpzm1QMbK2bhunM3zs7WWSS4KTicuI9YmQnpMUYqxLCLSII8S9m9T2/tuwiK1OZJBxAxFZ0PCzUC3IiIhzEuRCSydU5RxjpnOO/41KV2wEnFOkdZIZwuTnNwecvndhOVNM5bzs6YCqRpOMO0UmIpVu09WtdUYNyLE3G5J5HKjMtu3eFljKYplMTVKG6CEwAJikA8hO9wHakgZlbKbAF5AIPsQiqQiVq0rcLvSe%2B9rEMJ8SFFh58OEjS4ZNaa0dH78OfsEkRH8v4/xXsKgKVKWIVR5ZQ/lDLp5QJgXNeBGRDRIN5ngVB8cKWHB6lgnBjB8GEMCcE7V9K/F0MwEK4Joq2EXwldfKV98ZV8OAAIrlNVFURIEJI1VCrkVsliZ486RLsmJhUWoh6BJNF7MyqU36rNDHGTxJ6b01jFEWI3oqkSocHmnHBQkc57zYW9ORlJHShwxngicWjAQqaAptpLpzcZibiHqQSS2nyA6mlvHye5cdbhgnssJvY613aG5uDcSqzxWNgnuoCUmoJq70VhKjV6KJmKQqJIaSFJFbSukVJ6RegK/Sh2FPEcUtUgtdHlLFlMr5NTpaQ1mdehMiKtlHK%2BR0qpkzdYTpfWMoZuLO3WwfX%2B%2B2ctgO0XJNhnD346IbRheGDZ6IcOka/PeZ4wJXjvDOBca4GllzTq4u9Pl/x7LVgYCMhgNxUQikOOm%2B6I0CSqFSMQHNhxNE3mFBYASszhT1NgregyhwABqYhA7YsOHIZgxArg0LngoAAEnUKyMZCU5PZhaNUpsONcZuKcAGanaBSUk7eUmMyFPkx/OB%2BNLIHhtSuQ8F92mWh6YiGWU2IXdP6bLMZ2gpnrYBfwm2tUDsXYkvLvtL5bHm7GLBmlxjGXWlpK6QFjkL7KxlSYFQLwwIGg2buWRGFMYK1pqeSAFgTAjqwjTq8wF/4uA7p2hHTr3WYS9YBe88E/gAZcFm0NzuI2us9ZeZN6F4IACsAMZuDYLhyKSyG3BRbCwZ/bIBZ0iyS9luWjwX1CC8KkIomB0CLKgu6HmeXoKnFs0Qbj4INBYwQpx379m3Dze8UDuz4IzCA5%2BwIUH23YcCCh6cSQSPgfw/BADDbUZ3P3ngzC9873/D1kq80GrdWwlw7%2B6cAHEPqeg9298yHIPofo5R24fw7PWeo%2B55j04OOBx49gummENcEgEAgBHBQGoxeOjcK9on3Z7uPYyM9xXxTbhSwsBwFYzmOAbd4H4DgWhSCoE4Auyw1h%2BNrA2LFQEPBSAEE0LrlYR0QAbbMCyQIZhJAAA4/cbY0AATk9xoOKfuUj68kLwFgEgNAaFIMb035uOC8AUCARPzuTe69IHAWAMBEAgDWAQVI5xyCUDQDSOgCQogak4KoP3cUAZxUkNA5Ad0pAsjMLwZ7hASCfT0PwQQIgxDsCkDIQQigVDqBz6QXQXBSA5gRKkTgPA9ecEN0nl3ZvODmXOGX90qAqCHEb831v7fO%2BSG74cCAHhq/0DEzsLgSxeDZ60CsCASAq%2BpBr2QCgEAP%2Bf%2BIAwAUgZgfAdABI38lAsQO%2BsQEQoWa%2BvA8BOmVw5ksQ2g4i2ejuVeYY5kDAtAVwO%2BWAsQXgwAEEbCGe3AvAWAnWRg4gc%2B%2BAM4DgeAqyVBpu0cSyBISB5AggdQO%2BlwsQCIumHgWAO%2B8IeAce1BpAqyxAsQauYooYhgwAlwRgLuKwVABgwACgKmeAuYdcxujuw%2Bwgog4gE%2Bxh0%2BagO%2BC%2B%2BgyhKA1g1g%2BgeAsQGekAKwqAx42QVBAMXwl4pgVulgZgKeshxAn0MK8AKwdgWB2QLgXoUwfgi%2BYQgYCwIwi%2BRQWQAg8Reg6RDQ8wwwiQi%2BURLBAgfQkwngHQegRRDQpRAwyR%2BRlREwbQ5R%2BQhRjReRlQqRkRtumwEgG%2BBuRuO%2Bqep%2BTeLebewAHehwXeZgt%2BuA/eT%2BDur%2BTu6hKwU0bkIwv0pA7uyQLIweQQkgGgkgvuCUGgG2cUwe%2BgnAMepAce/gXALIcUXAEewefujxG2kgXAG2uxcU2%2Bc%2Bqe6emeSxOen%2BheX%2BxeB%2B5eABQBj%2BdebAnALQLAT0gQAMTA1cFYXAweLIdxHB%2BARAoRKci%2Bxho%2BZh0gFhSgVhc%2Bug4By%2BL4SBfRW%2ByevAqe%2B%2Bpe5whwx%2BfCCJSJKJeoaJGJWJt%2B9%2Bv%2Bj%2BxwgIZgix7%2BueoJUJCQFegBqAD%2BIw8JiJAMPJoBweXAieNAxSCQGeEAsBc%2BKBiB0hhpum6BmBDgPBuBHY%2BBhBxBmApB5BYgtAVBjutByhDBpuTB0RbBO%2BnByA5wWwjuEQBI%2BupughwhVwohWwpuEhUhjush8hSgihdBKhhs6hfAWhOhehOYBhPBhJph4%2BJJsglhs%2BpulJthah/hVglgThLhERZunhD0nAPhycfhDhgRwRCQeJ4Rbh3Q0RzgEArgWRiRXo7RiwaRGQGROQzRCRaQk5uRdRHRBRfZxRjQjRw5K51RbRi545tg65M5DRcwO5nRqw6wPRL%2BFx/RPxKenAHJyp3JBgvJmJLI08EAsxuJIptx4pyxpAqxWAiQGx0eseAQGJBxgQnxgQgQ/ghxkgrei%2BDJu%2BaetgAJEpwJ8AoJJeh%2Bsp0pxAMJWw8JF%2BLACgT0d0T06JLIyo4wveOJA%2B%2BJk%2BJhY%2BEgRZU%2BZJpZOgAQS%2BK%2BtJl59Jgxe%2B4JR%2BJ%2BBFbeRFJFEm5FlF7od%2B8pQpCQn5/g35QJee3%2BMlf%2B2Fqlj%2BIAJFj2MIZFweMIklYu40reEB2p0BepcBCBumPBJpaBGBWBlp8peBBBRBjB9pZBFBzpPBbp9B0ZNBX83p4Rc%2BfpAZPBwZ/Bc%2B4ZoWUZ4hoRcZvACZChSh9BaZSlmhTA2huh%2BhTIeZsgRJhZ9FJZ1hHFj5xg7ZNgghrhGxHhDQVBaIkkVZ1gQRjJIRYRVVkRdQ/Zfgg5cRB5I56AY5qRc5xQ2QG5OR2Qg1y5VRvQ%2B5eQs501JR255Q9RrR/QG5swrQk1vRp5du21%2BuvFvxt5wlhwolpFElf44wMxNF8xX5b%2BP5f56xfRVxceZgGJ/g/gG2Qe7xCe71gQEe15jJnA/xWeP5WxgQ3e4FXAUgweYFuxXAwQ%2Bu/gAxh1SFqFfRPeANiFd1QJKwshmQzgkgQAA%3D)

## Links

- [source code](../../../../conceptrodon/descend/omennivore/modify_types.hpp)
- [unit test](../../../../tests/unit/metafunctions/omennivore/modify_types.test.hpp)
