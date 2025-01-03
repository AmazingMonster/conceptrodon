<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Slice`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-slice">To Index</a></p>

## Description

`Typelivore::Slice` accepts a list of elements.

- Suppose its first layer is instantiated with an index.
In that case, it returns a function.
When invoked by an operation, the function collects all elements with indices greater than the given index from the list and instantiates the operation with the collection.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>I-1</sub>, E<sub>I</sub>, ..., E<sub>n</sub>
-> I
-> Oper
-> Oper&lt;E<sub>I</sub>, ..., E<sub>n</sub>&gt;</code></pre>

- Suppose its first layer is instantiated by two indices, which indicate a left-closed-right-open interval.
In that case, it returns a function.
When invoked by an operation, the function collects all the elements of indices within the interval from the list and instantiates the operation with the collection.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>I</sub>, ..., E<sub>J-1</sub>, ..., E<sub>n</sub>
-> I, J
-> Oper
-> Oper&lt;E<sub>I</sub>, ..., E<sub>J-1</sub>&gt;</code></pre>

## Type Signature

```Haskell
Slice
 :: typename...
 -> auto...
 -> template<template<typename...> class...>
```

## Structure

```C++
template<typename...>
alias Slice
{
    template<auto>
    alias Page
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
}；
```

```C++
template<typename...>
alias Slice
{
    template<auto, auto>
    alias Page
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
}；
```

## Examples

We will see two examples that demonstrate two different use cases.

In the first example, we will collect all elements from `int, int*, int**, int**` starting from index two.
Then, we instantiate `Operation` with the resulting list.

```C++
/**** Operation ****/
template<typename...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<int**, int**>;

/**** Result ****/
using Result = Slice<int, int*, int**, int**>
::Page<2>
::Road<Operation>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
```

In the second example, we will collect elements between indices one and three from `int, int*, int**, int**`. Then, we instantiate `Operation` with the resulting list.

```C++
/**** SupposedResult ****/
using SupposedResult_1 = Operation<int*, int**>;

/**** Result ****/
using Result_1 = Slice<int, int*, int**, int**>
::Page<1, 3>
::Road<Operation>;

/**** Test ****/
static_assert(std::same_as<SupposedResult_1, Result_1>);
```

## Implementation

The implementation is similar to `Typelivore::Amidst`.
We want to count elements one by one up to the desired index.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the elements to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` as in the implementation of `Typelivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `Slice` using concept expansion.

We will expand the constraint `Prefix<***>` alongside the arguments.

```C++
template<typename, auto>
concept Prefix = true;
```

- In the case where the second layer of `Slice` only accepts an amount, we want to remove the elements of the given amount from the front of the list.

```C++
template<typename>
struct Shear {};

template<size_t...I>
struct Shear<std::index_sequence<I...>>
{
    template
    <
        template<typename...> class Operation,
        typename...Targets
    >
    static consteval auto idyl
    (
        // Expand `Prefix<I>` to count the uwanted arguments.
        Prefix<I> auto...,
        // Collect the rest.
        Targets...
    )
    -> Operation<typename Targets::type...>;
};
```

- In the case where the second layer of `Slice` accepts two indices, we want to collect the elements between them.

```C++
template<typename, typename>
struct Incise {};

template<size_t...I, size_t...J>
struct Incise<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template<template<typename...> class Operation>
    static consteval auto idyl
    (
        // Expand `Prefix<I>` to count the uwanted arguments.
        Prefix<I> auto...,
        // Expand `Prefix<J>` to collect the proper number of arguments.
        Prefix<J> auto...targets,
        // Remove the rest.
        ...
    )
    -> Operation<typename decltype(targets)::type...>;
};
```

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`.

Note that we wrap the elements inside `std::type_identity`.
This ensures we can create objects to invoke ordinary functions.

```C++
template<typename...Elements>
struct Slice
{
    template<auto...>
    struct ProtoPage {};

    template<size_t Amount>
    struct ProtoPage<Amount>
    {
        template<template<typename...> class...Agreements>
        using Road = decltype
        (
            Shear<std::make_index_sequence<Amount>>
            ::template idyl<Agreements...>(std::type_identity<Elements>{}...)
        );
    };

    template<size_t Start, size_t End>
    requires (Start <= End)
    struct ProtoPage<Start, End>
    {   
        template<template<typename...> class...Agreements>
        using Road = decltype
        (
            Incise
            <
                std::make_index_sequence<Start>,
                std::make_index_sequence<End-Start>
            >
            ::template idyl<Agreements...>(std::type_identity<Elements>{}...)
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwA7KSuADJ4DJgAcj4ARpjEEmYAHKQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJXCm2mPalDEIETMQEeT5%2BQfWNOS1tBOXRcQlJqQqt7Z0FPZODw5XV4wCUtqhexMjsHAD0AFSHR8cnp/u7JhoAggdHANQAIphprozIeJgKd8cX17dnAJOvyulxBZgAzBFkN4sHcTOC3F5HLRCABPeHYUHmSEMaFeWHwtzISboLBUDFYv7HO7KYiYGiqb5HYEETAsNIGVmEgiol7MNikO5MJGoCnXNC454EGl0hlw8EPO4EYheTDwqzXUH/QE6w7A7V3ACS7PobEETCaTL1Wt1tvOlJu1KECEwbSt9uurJNFrVCJ5fNYvsx10mKocd2druIcMCVkCD3VDq9HJ9hKyAC9MAB9AgAOnzhrFV1DXnDkbaaYI6BAIAiWFUWaUAEdVZLCYb87mKeDgyDY6C7oOlWyU1zrkP5W4BxOh8nOb63P7GIHOxi7tCmAovgB5F7EC05UjTmdK3nLtidgAqbWAmAICmP8t7E/mjmQ64Ek0wADcxEKRXceDoKitCPhAj4Trsux3NgqhpIY6BwgAbBotL0ngqjthSKFKqgH5eIISouncXgAO6GKyiE3j4jD3l244njK6GYQihY9v%2BRCdkeDEnlBdx5I0RGYHcdKTPRVyMXc17ELedH5o%2BKyPgAtGuu4JAeAjcme/LCdJskKDWS6rj2iaavGpkglS9yGrieBKO6LIjvOWkBgKp6uUGoIluGNnvPZJj9uZ4IapZVxzqmCIZtmeYFoKUU5p2ABSRbedKvl2QuJI1nWmANs2rbbO2xnYHFVbZQw9aNpgLZvAuiXFUWAUhRO4Vcn6TkRYu2krvJ7EbludxqfuTRFi%2BrRvh%2BDBfr%2BtAcXhQEgWBEFDnxsHwRVyGobKGFYSZOFEPhhEEMRZEUZgVEyTRggKOJkloQyu3YHNXHLYOq1wQhm33TtCLJXtGi4R%2BtCCcdwlpMQqB7ncDCjNGqBUEKl1mnRr1MQ9v1rsKnH5lM%2BncRJjF8QASmyqDfsJoMiZ8eao6uPF3Ip9MqexQ0aQwLnnsJWDQkuEC43eCgrIZZ4NcFWJBSFNr3EIKLbA5oKtQuS46Z22CmrRD4mSGyqltKMt4IVZnNbOHVtW4WOoA19OpTKqBEMoTC3jGcYJmLmr04raZ4JmOZ3FcLAbIIo1DjbtJ26gDu3oS/uBwQweDk1qOe%2B13pm8rPVdn1Bhbp2VzAHSbIa/HM5eFkRh3ETqBMIh8KKtztBLqj4H05J5bEJW1YgCwTAANbZjleXVQVC4xwRccmVrBOSYOhmm8JC2gQiecF8jN29dgEBZSAS5ZkBtFooSauF9dFKBQ8naM1PM6KW7V8Ba7kse3PXs%2B3rUwEHF3vRTBFXF3SLZ4FEncCAAx2iTlrj/dAl8xphmlGHe2jsFygI/pA4uTUhxJ2finUcStuoXnXuubOa9czL0wMfe8xcJylwiMACuVca4KjuPXRuLchzNyvpJdKShUYTkJDwxiW9u5913hVXKVUaptgRMgjE%2BNp4CLKl3Xu/dRGDwkYVBE2AKpKWkZPORCddF6NnqneewFF5uFIeQ4hGJN4KJ3nvQQB8NHqxPiZM%2BF9UY32NgnCWDoWpYPNiKXO%2BcyGr2LtQ8ukdhIQPgRHRB0dgmWNFpLHx7tHR2kBPqakAAxQBkwYKqFYByYSPwpbpLOMCUp%2BxBp7jZvLT0/j074Mzr2G2rMRq30qRGLwaRijnRJgoLwDc6lXHCbQoQ3TenoH6YM6UEC2k5EJBEAghxBRLMON2R%2BaTDgV0%2BDM4ZoydkDKGRA/W6i3BLNWYIfYlzlnXMAlc/YRYayRMJGYJ5IBK7V0JPMzSE9NkGkvNTYZr4DZZk3EodoNjO4KEDGCzWbhxk9MyH03ZDdBTTIbhiTxDptRlKBJ0oQmAJSIVgoU%2BgwzcV4uZDip0EzkVTNRdKEp1wDmIsmRiggWYuDykVD89mCI1k3PWX8ml9wOX7LLrQjlXKeURllguC59zllCruWsx5k9nlxIRFwQU4J3mfPQN8mp7TMQdKstswFeTmXFnGqC8FCQCBQprDCtgcLCRsvpdKnVhyZlcqxeqDgaxaCcH8LwPwHAtCkFQJwKclhrB3AUBsLYUSIQ8FIAQTQga1g9wCJIXMGhkhmDMAATmLVwfwBbkhcECIEaQwaOCSF4CwCQGgNCkHDZG6NHBeAGTbRmiNgbSBwFgDARAIANgEDSEicglA0DsjoAkKIgZOCqGSEhJSSFJB3GAMgd8UhcxmF4OdQgJAgJ6H4IIEQYh2BSBkIIRQKh1ADtILoHVpF9xpE4DwINIaw2ZqjZwbcSIp3SnhncVd67N3bt3XcfdZhgEeHnfQaM2IuArF4P2rQawIBIDnWkBdZAKAQDwwRkAwApBmD4HQVkxADIQFiP%2B2IEQ2ioi/bwJjzBiCom3LEbQRL%2B1prncjbcDBaCsefVgWIXhgDm2BgZbgvAsDdyMOICTgD%2BN4HJvJyNuUiVIh2GmpZDR/0oliPuLjHgsD/uVHgZtCnSDk2ILEZFTxlPABREYTNawqAGGAAoAAah8Uialw1povcIUQ4hb3hYfWof9r79CGGMNYaw%2Bg8CxAMpANYkMmjyaUiSWupg42WDMJ2xzxA96ZYgGsOwGnnAQFcDMPwOqwgRBGFUMYOrijZAEE1vQ3WmiLFhnoWrDh%2Bjvz6zq0bTRkFDY6zUWwE3PBdBG%2B/Obyw0PrE2NsCQP6OChvbf%2Brt4G10bq3Tuvdeb4MQFwCelDqb0Ppq82sF01cxjVdIDmyQ4JczFvBLWjQkgzCSBQhofwSFi36E4I20gzbwRcFzEhLgSFkjFqrUhfwkhy1/aQod59Xae0gD7V5odo6cPjuA9OojJHkNLrYJwNoLBvyBCUkwQhSXYPFtzAjnT%2BAiAVerDq8LV6ovSBi0oOLz7dCUffUwT9Cm9sHY7bwLtQHJ1IjuGBiDZ32fly4FznnCHUBIYSHCCEZhHuYcHeTmnCQZ3EeN/h5DKADBGH11wNtNAG4JDowx59HGWNsdIAHrjPG%2BMOCD0J2iImxP/sk9J2TtB5NpqU0l1Tkb8B0jG1p/9unkD6aD0Z%2BtkbTPmdRJZnYkabN2bTY55zShXNp5oSTnzjsAtBZC0H4XkWb1i9kLFp9kbpeJc80Vqwlg0sZfgNltIuXOD5arIVlLJWysJAF58afvQ6t%2BAaxVSbIQKrrc6%2BkTIPXcjLYKF10/g22tLGP9N8bgx98P4ELN2/w2ptLfyM1xbCx3/zd2y22TUAPrSVyO04BO0gy3Q3D1wN3zWAVu35zN3h0t2e1IFeywESA%2B3rRhzhy50B0CH8GLRrXBCBxByxzx07U4EJ2JwHWwzJyQAnRA3t1t2IDpx2EZygxYAUG/HfG/H11zHnEmCPT51PUFzvQi2vQkD73vQl0Hx0BAHBFIFl3l2/Sh32z/Xx0A0p1AwRlUC4J4L4IEKEOlAgEQyd1N2xHBFQLoKHVw0dwIxYIcOd14J6SzH4OLSzBMKzH0LF2ox90oD90jRD3EzTRCLD340j2N2E1E3Ewz0wCkxkzECTyD1TxU0r0U3U2zw32fTzwL3syLxM3SzLwr2swqxr14DrxczZCb081sNbz80C0wGCz5C71kBF17wkIH3i0UJH2S2KxsFMyqxnznz2CyjH2sFKxV3K0q03xfx30awvx/1awqA/xPxKByH3wGxyCPwW3mOQWfwaG3zf1WIAM/yfyWNWz/1OI2xqyTR2021AM0KoI4HAwMN4LuA8MEJ9DyRu1EPuxQIwzQIwPez21wJABLVzHBHBH8ArSx1bWhMCBR0oJV2oNsCJyezoOzRAEkH8F%2B2rUCFbWSEkDLS4ELTMFx3rXBGeNRO7UxKwz20PRRIAzpKtxWDWEcyyGcEkCAA%3D)

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/slice/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/typelivore/slice.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/slice.test.hpp)
