<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::ClassicPlume`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-classic-plume">To Index</a></p>

## Description

`Varybivore::ClassicPlume` accepts a list of variables.
Its first layer accepts a list of sequences and returns a function.

When invoked by an operation, the function places the variables into sequences via a process similar to pack expansion;
then, it collects the type result of each packed sequence and invokes the operation with the collection.

Check out **Examples** for more information.

<pre><code>   V
-> Transf<sub>0</sub>, Transf<sub>1</sub>, ..., Transf<sub>n</sub>
-> Oper
-> Oper&lt;Transf<sub>0</sub>&lt;V&gt;::type, Transf<sub>1</sub>&lt;V&gt;::type, ..., Transf<sub>n</sub>&lt;V&gt;::type&gt;</code></pre>

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> Transf
-> Oper
-> Oper&lt;Transf&lt;V<sub>0</sub>&gt;::type, Transf&lt;V<sub>1</sub>&gt;::type, ..., Transf&lt;V<sub>n</sub>&gt;::type&gt;</code></pre>

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> Transf<sub>0</sub>, Transf<sub>1</sub>, ..., Transf<sub>n</sub>
-> Oper
-> Oper&lt;Transf<sub>0</sub>&lt;V<sub>0</sub>&gt;::type, Transf<sub>1</sub>&lt;V<sub>1</sub>&gt;::type, ..., Transf<sub>n</sub>&lt;V<sub>n</sub>&gt;::type&gt;</code></pre>

## Type Signature

```Haskell
ClassicPlume
 :: auto... 
 -> template<auto...> class...
 -> template<template<typename...> class...>
```

## Structure

```C++
template<auto>
struct ClassicPlume
{
    template<template<auto...> class...>
    alias Rail
    {
        template<template<typename...> class>
        alias Road = RESULT;
    };
};
```

```C++
template<auto...>
struct ClassicPlume
{
    template<template<auto...> class>
    alias Rail
    {
        template<template<typename...> class>
        alias Road = RESULT;
    };
};
```

```C++
template<auto...>
struct ClassicPlume
{
    template<template<auto...> class...>
    alias Rail
    {
        template<template<typename...> class>
        alias Road = RESULT;
    };
};
```

## Examples

We will see three examples that present different use cases of `Varybivore::ClassicPlume`:

- We will pack `0` into `ZeroStar`, `OneStar` and `TwoStars`.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
/**** Transformations ****/
template<auto I>
struct ZeroStar
{ using type = std::integral_constant<int, I>; };

template<auto I>
struct OneStar
{ using type = std::integral_constant<int, I>*; };

template<auto I>
struct TwoStars
{ using type = std::integral_constant<int, I>**; };

/**** Operation ****/
template<typename...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation
<
    std::integral_constant<int, 0>,
    std::integral_constant<int, 0>*,
    std::integral_constant<int, 0>**
>;

/**** Result ****/
using Result = ClassicPlume<0>
::Rail<ZeroStar, OneStar, TwoStars>
::Road<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

- We will use `OneStar` to pack each of `0`, `1`, and `2`.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
/**** SupposedResult ****/
using SupposedResult_1 = Operation
<
    std::integral_constant<int, 0>*,
    std::integral_constant<int, 1>*,
    std::integral_constant<int, 2>*
>;

/**** Result ****/
using Result_1 = ClassicPlume<0, 1, 2>
::Rail<OneStar>
::Road<Operation>;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult_1>);
```

- We will pack `0`, `1`, and `2` into `ZeroStar`, `OneStar`, and `TwoStars` separately.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
/**** SupposedResult ****/
using SupposedResult_2 = Operation
<
    std::integral_constant<int, 0>,
    std::integral_constant<int, 1>*,
    std::integral_constant<int, 2>**
>;

/**** Result ****/
using Result_2 = ClassicPlume<0, 1, 2>
::Rail<ZeroStar, OneStar, TwoStars>
::Road<Operation>;

/**** Test ****/
static_assert(std::same_as<Result_2, SupposedResult_2>);
```

## Implementation

`Varybivore::ClassicPlume` separates cases according to the number of parameters.
The goal is to mimic the behavior of pack expansion in C++:

- If the user only provides one variable, we pack the variable in each sequence separately;

- If the user only provides one sequence, we use the sequence to pack each variable separately;

- Otherwise, the number of variables shall match the number of sequences.
We pack each variable into its corresponding sequence.

Here's the entire implementation:

```C++
template<auto...Variables>
struct ClassicPlume
{
    // Multiple Variables
    // Multiple Sequences
    template<template<auto...> class...Cosmetics>
    struct ProtoRail 
    { 
        template<template<typename...> class Operation>
        struct Detail
        {
            using type = Operation<typename Cosmetics<Variables>::type...>;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;
    };

    // Multiple Variables
    // One Sequence
    template<template<auto...> class Cosmetic>
    struct ProtoRail<Cosmetic>
    { 
        template<template<typename...> class Operation>
        struct Detail
        {
            using type = Operation<typename Cosmetic<Variables>::type...>;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;
    };

    template<template<auto...> class...Cosmetics>
    using Rail = ProtoRail<Cosmetics...>;
};

template<auto Variable>
struct ClassicPlume<Variable>
{
    // One Variable
    // Multiple Sequences
    template<template<auto...> class...Cosmetics>
    struct ProtoRail 
    { 
        template<template<typename...> class Operation>
        struct Detail
        {
            using type = Operation<typename Cosmetics<Variable>::type...>;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;
    };

    template<template<auto...> class...Cosmetics>
    using Rail = ProtoRail<Cosmetics...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/classic_plume/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/classic_plume.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/classic_plume.test.hpp)
