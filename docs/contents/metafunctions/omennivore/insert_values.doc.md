<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::InsertValues`

## Description

`Omennivore::InsertValues` accepts a list of `std::index_sequence`, which indicates distances between adjacent indices.
Its first layer accepts a list of variables and returns a function.
When invoked, the function inserts the variables to its argument list according to the `std::index_sequence`s.
The result will be stored inside `Shuttle`.

<pre><code>   std::make_index_sequence&lt;I<sub>0</sub>&gt;,
   std::make_index_sequence&lt;I<sub>1</sub>&gt;,
                    &vellip;
   std::make_index_sequence&lt;I<sub>n</sub>&gt;
-> V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>k</sub>
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>m</sub>
-> Shuttle
   <
             Arg<sub>0</sub>,
             Arg<sub>1</sub>,
              &vellip;
       Arg<sub>I<sub>0</sub>-1</sub>, V<sub>0</sub>, Arg<sub>I<sub>0</sub></sub>,
       Arg<sub>I<sub>1</sub>-1</sub>, V<sub>1</sub>, Arg<sub>I<sub>1</sub></sub>,
              &vellip;
       Arg<sub>I<sub>n</sub>-1</sub>, V<sub>n</sub>, Arg<sub>I<sub>n</sub></sub>,
              &vellip;
             Arg<sub>m</sub>
   ></code></pre>

## Type Signature

```Haskell
InsertValues ::   typename...
               -> auto...
               -> template<auto...>
```

## Structure

```C++
template<typename...>
struct InsertValues
{
    template<auto...>
    alias Page
    {
        template<auto...>
        alias Page = RESULT;
    };
};
```

## Examples

We will insert `-1, -3, -5` to indices `1, 2, 3` of `0, 2, 4`.
To do so, we will calculate the distance from one index to its immediate next.
We will keep the first index, `1`, since it represents how many variables we must pass to reach the first target position.

<pre><code>   1, 2, 3
-> std::make_index_sequence&lt;1&gt;,
   std::make_index_sequence&lt;2-1&gt;,
   std::make_index_sequence&lt;3-2&gt;</code></pre>

We will pass these sequences to `InsertValues`.

```C++
template<auto...>
struct Shuttle;

template<auto...Args>
using Metafunction = InsertValues
<
    std::make_index_sequence<1>,
    std::make_index_sequence<2-1>,
    std::make_index_sequence<3-2>
>
::Page<-1, -3, -5>
::Page<Args...>;

using SupposedResult = Shuttle<0, -1, 2, -3, 4, -5>;

using Result = Metafunction<0, 2, 4>;

static_assert(std::same_as<SupposedResult, Result>);
```

## Implementation

The implementation of `InsertValues` is similar to that of `Varybivore::Inject`. However, since now we must deal with a variadic number of indices, we will perform recursion over the total number of the `std::index_sequence`s.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  - Handle several `std::index_sequence`s from the front of the list;
  - Invoke itself to deal with the rest;
  - Concatenate two resolved parts.

We will use the following helper class template to concatenate two parts.

```C++
template<typename...>
struct ExtendFront {};

template<template<auto...> class Sequence, auto...Variables>
struct ExtendFront<Sequence<Variables...>>
{
    template<auto...NewVariables>
    using Page = Sequence<NewVariables..., Variables...>;
};
```

We will transform variables into types so that we can avoid defining the body of the helper function `idyl`.

```C++
template<auto Variable>
struct Monotony
{ static constexpr auto value {Variable}; };
```

We will use `Prefix` to enumerate arguments like in `Varybivore::Amidst`.

```C++
template<typename, size_t>
concept Prefix = true;
```

`Shuttle` is used to store the result. We declare `Shuttle` as follows.

```C++
template<auto...>
struct Shuttle;
```

Here is a simplified version of the implementation.

```C++
template<typename...>
struct InsertValues {};

/**** Base Case ****/
template<auto...I>
struct InsertValues<std::index_sequence<I...>>
{
    template<auto NewVariable, auto...>
    struct ProtoPage
    {
        template
        <
            // We use `Prefix<I>...` to enumerate `FrontTargets`.
            Prefix<I>...FrontTargets,
            typename...BackTargets
        >
        static consteval auto idyl()
        // `NewVariable` is injected in the return type.
        // Note that `Shuttle` is instantiated by values
        // extracted from the template parameters.
        // This is because we will pack every variable
        // into `Monotony`.
        -> Shuttle
        <
            FrontTargets::value...,
            NewVariable,
            BackTargets::value...
        >;

        template<auto...Agreements>
        using Page = decltype(idyl<Monotony<Agreements>...>());
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

template<auto...I, auto...J>
struct InsertValues<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template<auto FirstNewVariable, auto SecondNewVariable, auto...>
    struct ProtoPage
    {
        template
        <
            // We use `Prefix<I>...` to enumerate `FrontTargets`.
            Prefix<I>...FrontTargets,
            // We use `Prefix<J>...` to go across the distance
            // between two targets.
            Prefix<J>...MiddleTargets,
            typename...BackTargets
        >
        static consteval auto idyl()
        -> Shuttle
        <
            FrontTargets::value...,
            FirstNewVariable,
            MiddleTargets::value...,
            SecondNewVariable,
            BackTargets::value...
        >;

        template<auto...Agreements>
        using Page = decltype(idyl<Monotony<Agreements>...>());
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

/**** Recursive Case ****/
template<auto...I, auto...J, typename...OtherSequences>
struct InsertValues<std::index_sequence<I...>, std::index_sequence<J...>, OtherSequences...>
{
    template<auto FirstNewVariable, auto SecondNewVariable, auto...OtherNewVariables>
    struct ProtoPage
    {
        template
        <
            // We use `Prefix<I>...` to enumerate `FrontTargets`.
            Prefix<I>...FrontTargets,
            // We use `Prefix<J>...` to go across the distance
            // between two targets.
            Prefix<J>...MiddleTargets,
            typename...BackTargets
        >
        static consteval auto idyl()
        -> ExtendFront
        <
            typename InsertValues<OtherSequences...>
            ::template Page<OtherNewVariables...>
            ::template Page<BackTargets::value...>
        >
        ::template Page
        <
            FrontTargets::value...,
            FirstNewVariable,
            MiddleTargets::value...,
            SecondNewVariable
        >;

        template<auto...Agreements>
        using Page = decltype(idyl<Monotony<Agreements>...>());
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxBL%2BAOykAA6oCoRODB7evgGp6ZkCoeFRLLHxXEm2mPaOAkIETMQEOT5%2BgXaYDlmNzQQlkTFxCckKTS1teZ0TA2FD5SNViQCUtqhexMjsHOb%2BYcjeWADUJv5uXo60hACeZ9gmGgCCewdHmKfnyOPoWFT3jxeZn2DEOXhOZzcBBuKUwAH0CMQmIQFADnoCAPQAKhxWOO2FUBFcADFiLJjrisRjAUSWCkDETIdDYcw2AA6Dlop7jYheBz4wkksmCU6JKyJAAiZys6OetPpTEZ53lDMwkKYl1QHLZ92OhyYCgUxyEmAAjl5GNtSMcNURtQA1Zp4JjReio/wPZ48vkEAVEhjoUmySEm82WtXnR3EZ2uzAKbUAj2AkxiwHHdPHFWKiNuW1ajkRTAAdyjMbdXIzxy8GSMx2UTGAHzOEuNZotoJzhZLTpdbu11tLvbjCaT/hlL0l0uTz2xuOOAFkBKgiAwbhTcdS5Zg6ar1ZrjoPY1zvfzFwxlwI7uixcdxoq8Mg9QJxphVCliDb9wA3MQW0UWQ96BTKUx1FEDx0xSk62ITAaFUdccU3J4syVKEYUYVhMGtDIAC94QILk0A7FJfWUGC4M%2BFtEQtKdZSeWccWNBBLgIegEKpGltwVVC8xHT1uWo/khGYghWIjCCZyggBJBglBaR1vDjdikJQnNmQw9lOSTL1BN9GS5IIBSLSNFNxXA6d6KgiwDQ%2BXMlGUzid2zPc7Q5KTj10459LiQzfzjSEfhAEAwiwVQ4SUMMO0hKS%2BK5Uy0wzVSXNQY4u0ArDP1cnVtKeSsT1IskiHrRsEvTeLnkrSskoqyqyvOUraozDEMWOAB1D5qybAA2DQyNgvBVGi%2B4Ex6zMUsYHw4mzU4eqDQQABVmkbAhUR6nUasajM%2BrgoaPW1OaCEW4hloUUgGs29TWUwbVrOQABrI6TvOjMK0au9HEfIiXx/WhMpSvB0BuWgIBWZ702amaNDSnsj1GvAjTCbRuiJdBjjCTMEA%2BGCCE2BhM3Q9bcsaiGImXD4CAQRVIeEligLhhHZKaQRnRR45ojXH7jLB44IdfREmAcTBUaoMkWAx8muNVY4UmaTCiWIeNuYh%2BaEHhtGjViUROuOIsPiLOhfpl%2B7jkwL84g5mGgI2yqIbCIhIbPC9VxMNbuYAWl1GnRKtonashbnKwOx7MBWoLOeujkzutzboejIco99zbjluh6lpDhQw78hNo5e0cJMTqrJec85eI5J5gBg7dGBW17aurMJgDrBsm38FssEOdSIABoHIUdlc7nOcvK7YQR3WwPiQdBscGuA2iXmtpKS81bUh8wKvR9rqsa0b4qW5bMiL13yFV/XlbYun69zLoxfc2XtzrVLtkACkPN5flvPkvz3TcQLgoDV9wptnDNFPi2ECDoCCiFABEV2zbEhE/c%2B/FyqJxvnmY4xI8AKwILHMsGU0EmiIugHB8c/qxWtvlaCh9m4z1TDndM1UC65zcAHJqLV2pb26r1ciA1drj05KNe2E02BIiJJDIOaca6uzoZVbaPDzjuT2hycRx104JyTqwtqHV7Iuy4f1Qa5wX6KJ1AIlKwAUoCzJIacWxx8B3iitIysENYgEF1owTMRYUoTBOoTdR6ZZH6LcIYvhbJ5wA3QPQYOK01G%2BMuphG6AtU4qJrtIzeeUmgfSfIzU2Yg/po0BsDUG0iPYeiYrTNUKT6oOIzMok6mdFL9hYemDBWDiGxmieo0JvwIkSIziAcODSqnpgIQIIhxZ0rtKTinSJvT%2BmcgqQ8C%2B89GH0KLjxO%2BbIT4jxrjlTa9day70ojY7otBO7d1oL3Jc/dj4VzXlsseE8VhT3HJWWeiyGqoPWZs6uY8Gp7J3s3Q5B8irUMHjc0%2B8YtILIgpON5kk5wACVuibAyGbY4dkPiUhUqsnMj8pIP3WU/a0sTNJsgAPIUziKGWB/kcoUI/r5RS39f5QLCjA4B8jQG3nAZA/%2BrKgFRQMZy8lmNiBUvDBC7KSDaEoOxcldBmDxitPoPi%2B2wyAxKrwes4VcQNU/PIZ5IFqAj7W2QRdWVFTmGDJ5mwrRnD/G8JGhoMaJsGCTREZwmp6cdE%2BN8fa%2BRw0lHCkOj0iZm0IbsO1jov1gSA3GKdfbMxNpkCWKNBSmx8MmZwKtU4kOri8YuM8T0n16jo1BO1J08JmBpmhsasSiObIpk9O5qkjM70HyZO%2BjktBZyQbu11ASf0gYg3NsqcsyqdavKyR8kZGlbhtWiv5dsCVLbapBVUk3Eq5x526rIWOysa7sUbpzI2pJMys6QpHfxTaB6nKiONWO/2VrPWhz6eetkNbarNMVWMy2WFGkLjCd009dSLQDL3RmNVozuxxyPPMue3MPlZS%2BRvHZjU/lHsOe3E56Eu75IueeK5oLh7fNjfcSec8XkwvzoXW9OLPlgruZvdDBzmyUOBZutwyGz4XreVRiyDFKSCY3JBOc804wrQcnCoT0mkLJmBG8cELcLhXFuHFLctHkq7ooV7MS8H1PcTo0h46eqnjofnCHJgVAvCgnqHjVj9KZ2onRKOtJECQAsCYHdeELLAGRTgecLg9wJm/w815uEPm2UCrcGYN2gWPTBe5e5zz3neW%2BepZCfwbszBxRykFI%2B5xYvWjdoEY4bsACsXI8sgs48Z8%2B%2Bd0NCC8CkNISh0CIoUF4E5hydNAXOBoIrXBrRmCKyV6QpWKt5wsuh9rnXfSsfM00KzNmsiQn68cYbxxJCJnzm25AcIDQGQgL/BQmF9vf0a819IQsZsnOtDdgiHonkcDWLQTgZXeB%2BA4FoUgqBODMMsNYW8GwthNmBDwUgBBNDPbWHdEAZWzBskSGYSQAAOFHZWNAAE54caC6ijwIr2OCSF4CwCQGh%2Bufe%2B79jgvAM79ch1957pA4CwBgIgEAGwCApEuOQSgaA6R0B1ZhTgqgUddTdl1SQxxgDIEfFINkZheBC0ICQAGeh%2BCCBEGIdgUgZCCEUCodQjPSC6EG0WJEKROA8Be29j7UOfucFJZcbnvpUBUGOKL8Xkvpey%2BOPLswxwIAeAF/QD8ewuArF4AzrQawIBIH5ykQXZAKAQAT0nkAwApDDZoCcuIGcIDRHt9EMIzQbhW94MX5gxAbikuiEjBw5fSD862aShgtAy/G6wNELwwBcy0FoBnbgvAsAeaMOITvmDkZ4DNoP77r4kVEkb3bWo9vrjRCRNXjwWB7eIjwKTofpAzbEGiFdiU25DDAGuEYKHawqAGGAAoe0eBiykpZI3jXwhRDiF1x/g3ah7em76AX4oDWDWD6B4DRAZyQBrCoAkRZCD5uw/DNimAA6WBmBU5H7RhYBQEgw1B1BZAuABhTB%2BCDYhDzBlAVB6AtZFDZCeDtBUGFC2aDAUFLB4FT4NCzDEF6BdA9AcH9DMHDCVC2CcF0F5CDZ3gtACGLCVBrAKDA7bASA24cDvakCU68DU4e5i4S5S4y5y6SAK6B64Aq5h5g6R4Q435rCYxMBYDxC4Gw6SD%2BBsiY5JCSAaCSDI49QaBlZdSY76CcDE6kCk7%2BBcBshdRcB46Y4o7hFlaSBcBlbOFdSqH27U604gD0437M5s5x4c7O484p5p6h4RDC4cDNAsBfiJBuxMB6gGC1hcCY5sghFz74BEBYHq6yBa7f7SC/5KD/7G66DDbm5MCW5D5KEqFqEO4cBO5c6XDHBu42jEBlEVFVH6i1H1GNGB7B6J6h6nDAhmBmHR5M7ZEFFxC86p6oAh4jClHlFuwrGZ6Y5cD9Y57yz56F7G6V6l6N7vHV61714M7g7N7Vyt7t725d49594D6N4j4X7j7fb4AwQ9Az727z7ICXA7Dg7L6E7fZr4b43Bb47Dfa7777g5H4n5KBn6j6X4NwZF34NiP7P5Fiv6MDv7tFf465dGyB/5G7fb9FAHX4oFWCWDgGQHwAwFwHPicCIHgLIGgFoEYFxBYFxgilsG8F%2BAQCuBcGkEBhSGUGDbUG2YakFAZBMHkGCHcG1DsEMB9CTCiEkHKm2ZWlzClCmniEiG5C2kSGOkLA6myHyE66jF27G4aFXFLHVEX5%2B5rFshOoQBGEtE7HBH7EWGkBWE2GUBKEBFBH1FuGJDxGJCJD%2BDuGSCS6DbjEpG2BpHmGM6x5ZFICc4u6nHHHEBFFsCcClHe4sAKBfiPhfh1FsiqjjBK7NGq4QKDYf4dFsl67yA9Fck6D5CDHDHW5%2BHKEBlU6O65Gu7u6tlS7tmdnHDdn1F9m%2BhB7nFbFxBxn%2BAJmVnM7x7HlJ71k3mh59LIDNZwh7lwgHn7YLGS58B0DPGUCvHfZfEd7g6AU/HIyN4AmCBAkd6wmYDd695iAQkH5Qlj74nD6T4ImKnG7ImolL6CAr7G7Yml54k77RhEm8Akmn7n5j5UmXk0kP5P4v5v4H6jmskSDsn65TkAH5A1HGAyk2Br44Gim2aD4YiBT8nWDoHqGYEAyKnQF2kEFqlEE2l6BkFOnSEMFGlZAGl6lZDamsE8H2mun0HiHmkqkOl6VCEekGkekWWKHrCbAKER6LljHJGcDzEsBtkdldk9kHmGGDkmHxlR6JnJkjC4GE7pkgBmD1H%2BD%2BBlYY6xHk4xWJB45JGBmcCpHpGVkw4gCSCJAK7ZlcBSCY5ZnOFcDJCE7%2BDLnqHpUVkx5KGK6pUrk061XQ6H554EGSBAA%3D)

## Links

- [source code](../../../../conceptrodon/descend/omennivore/insert_values.hpp)
- [unit test](../../../../tests/unit/metafunctions/omennivore/insert_values.test.hpp)
