<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::SensiblePlume`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-sensible-plume">To Index</a></p>

## Description

`Varybivore::SensiblePlume` accepts a list of variables.
Its first layer accepts an operation and returns a function.

When invoked by sequences, the function places the variables into the sequences via a process similar to pack expansion;
then, it collects every packed sequence and instantiates the operation with the collection.

Check out **Examples** for more information.

<pre><code>   V
-> Oper
-> Transf<sub>0</sub>, Transf<sub>1</sub>, ..., Transf<sub>n</sub>
-> Oper&lt;Transf<sub>0</sub>&lt;V&gt;, Transf<sub>1</sub>&lt;V&gt;, ..., Transf<sub>n</sub>&lt;V&gt;&gt;</code></pre>

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> Oper
-> Transf
-> Oper&lt;Transf&lt;V<sub>0</sub>&gt;, Transf&lt;V<sub>1</sub>&gt;, ..., Transf&lt;V<sub>n</sub>&gt;&gt;</code></pre>

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> Oper
-> Transf<sub>0</sub>, Transf<sub>1</sub>, ..., Transf<sub>n</sub>
-> Oper&lt;Transf<sub>0</sub>&lt;V<sub>0</sub>&gt;, Transf<sub>1</sub>&lt;V<sub>1</sub>&gt;, ..., Transf<sub>n</sub>&lt;V<sub>n</sub>&gt;&gt;</code></pre>

## Type Signature

```Haskell
SensiblePlume
 :: auto... 
 -> template<typename...> class...
 -> template<template<auto...> class...>
```

## Structure

```C++
template<auto>
struct SensiblePlume
{
    template<template<typename...> class>
    alias Road
    {
        template<template<auto...> class...>
        alias Rail = RESULT;
    };
};
```

```C++
template<auto...>
struct SensiblePlume
{
    template<template<typename...> class>
    alias Road
    {
        template<template<auto...> class>
        alias Rail = RESULT;
    };
};
```

```C++
template<auto...>
struct SensiblePlume
{
    template<template<typename...> class>
    alias Road
    {
        template<template<auto...> class...>
        alias Rail = RESULT;
    };
};
```

## Examples

We will see three examples that present different use cases of `Varybivore::SensiblePlume`:

- We will pack `0` into `ZeroStar`, `OneStar` and `TwoStars`.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
/**** Transformations ****/
template<auto I>
using ZeroStar = std::integral_constant<int, I>;

template<auto I>
using OneStar = std::integral_constant<int, I>*;

template<auto I>
using TwoStars = std::integral_constant<int, I>**;

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
using Result = SensiblePlume<0>
::Road<Operation>
::Rail<ZeroStar, OneStar, TwoStars>;

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
using Result_1 = SensiblePlume<0, 1, 2>
::Road<Operation>
::Rail<OneStar>;

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
using Result_2 = SensiblePlume<0, 1, 2>
::Road<Operation>
::Rail<ZeroStar, OneStar, TwoStars>;

/**** Test ****/
static_assert(std::same_as<Result_2, SupposedResult_2>);
```

## Implementation

`Varybivore::SensiblePlume` separates cases according to the number of parameters.
The goal is to mimic the behavior of pack expansion in C++:

- If the user only provides one variable, we pack the variable in each sequence separately;

- If the user only provides one sequence, we use the sequence to pack each variable separately;

- Otherwise, the number of variables shall match the number of sequences.
We pack each variable into its corresponding sequence.

Here's the entire implementation:

```C++
template<auto...Variables>
struct SensiblePlume
{
    template<template<typename...> class Operation>
    struct ProtoRoad 
    {
        template<template<auto...> class...Cosmetics>
        struct Detail
        {
            using type = Operation<Cosmetics<Variables>...>;
        };

        template<template<auto...> class Cosmetic>
        struct Detail<Cosmetic>
        {
            using type = Operation<Cosmetic<Variables>...>;
        };

        template<template<auto...> class...Cosmetics>
        using Rail = Detail<Cosmetics...>::type;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

template<auto Variable>
struct SensiblePlume<Variable>
{
    template<template<typename...> class Operation>
    struct ProtoRoad 
    {
        template<template<auto...> class...Cosmetics>
        using Rail = Operation<Cosmetics<Variable>...>;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/sensible_plume/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/varybivore/sensible_plume.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/sensible_plume.test.hpp)
