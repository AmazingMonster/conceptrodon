<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Plume`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-plume">To Index</a></p>

## Description

`Typelivore::Plume` accepts a list of elements.
Its first layer accepts a list of transformations and returns a function.

When invoked by an operation, the function instantiates the transformations using its arguments via a process similar to pack expansion and invokes the operation by the instantiated transformations.

Check out **Examples** for more information.

<pre><code>   E
-> Transf<sub>0</sub>, Transf<sub>1</sub>, ..., Transf<sub>n</sub>
-> Oper
-> Oper&lt;Transf<sub>0</sub>&lt;E&gt;, Transf<sub>1</sub>&lt;E&gt;, ..., Transf<sub>n</sub>&lt;E&gt;&gt;</code></pre>

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>n</sub>
-> Transf
-> Oper
-> Oper&lt;Transf&lt;E<sub>0</sub>&gt;, Transf&lt;E<sub>1</sub>&gt;, ..., Transf&lt;E<sub>n</sub>&gt;&gt;</code></pre>

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>n</sub>
-> Transf<sub>0</sub>, Transf<sub>1</sub>, ..., Transf<sub>n</sub>
-> Oper
-> Oper&lt;Transf<sub>0</sub>&lt;E<sub>0</sub>&gt;, Transf<sub>1</sub>&lt;E<sub>1</sub>&gt;, ..., Transf<sub>n</sub>&lt;E<sub>n</sub>&gt;&gt;</code></pre>

## Type Signature

```Haskell
Plume
 :: typename... 
 -> template<typename...> class...
 -> template<template<typename...>class...>
```

## Structure

```C++
template<typename>
struct Plume
{
    template<template<typename...> class...>
    alias Road
    {
        template<template<typename...> class>
        alias Road = RESULT;
    };
};
```

```C++
template<typename...>
struct Plume
{
    template<template<typename...> class>
    alias Road
    {
        template<template<typename...> class>
        alias Road = RESULT;
    };
};
```

```C++
template<typename...>
struct Plume
{
    template<template<typename...> class...>
    alias Road
    {
        template<template<typename...> class>
        alias Road = RESULT;
    };
};
```

## Examples

We will see three examples that present different use cases of `Typelivore::Plume`:

- We will pack `int` into `ZeroStar`, `OneStar` and `TwoStars`.
Then, we will instantiate `Operation` with the results.

```C++
/**** Transformations ****/
template<typename Element>
using ZeroStar  = Element;

template<typename Element>
using OneStar = Element*;

template<typename Element>
using TwoStars = Element**;

/**** Operation ****/
template<typename...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<int, int*, int**>;

/**** Result ****/
using Result = Plume<int>
::Road<ZeroStar, OneStar, TwoStars>
::Road<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

- We will use `OneStar` to pack each of `int`, `float`, and `double`.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
/**** SupposedResult ****/
using SupposedResult_1 = Operation<int*, float*, double*>;

/**** Result ****/
using Result_1 = Plume<int, float, double>
::Road<OneStar>
::Road<Operation>;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult_1>);
```

- We will pack `int`, `float`, and `double` into `ZeroStar`, `OneStar`, and `TwoStars` separately.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
/**** SupposedResult ****/
using SupposedResult_2 = Operation<int, float*, double**>;

/**** Result ****/
using Result_2 = Plume<int, float, double>
::Road<ZeroStar, OneStar, TwoStars>
::Road<Operation>;

/**** Test ****/
static_assert(std::same_as<Result_2, SupposedResult_2>);
```

## Implementation

`Typelivore::Plume` separates cases according to the number of parameters.
The goal is to mimic the behavior of pack expansion in C++:

- If the user only provides one element, we pack the element in each container separately;

- If the user only provides one container, we use the container to pack each element separately;

- Otherwise, the number of elements shall match the number of containers.
We pack each element into its corresponding container.

Here's the entire implementation:

```C++
template<typename...Elements>
struct Plume
{
    // Multiple Elements
    // Multiple Containers
    template<template<typename...> class...Cosmetics>
    struct ProtoRoad 
    { 
        template<template<typename...> class Operation>
        struct Detail
        {
            using type = Operation<Cosmetics<Elements>...>;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;
    };

    // Multiple Elements
    // one Container
    template<template<typename...> class Cosmetic>
    struct ProtoRoad<Cosmetic>
    { 
        template<template<typename...> class Operation>
        struct Detail
        {
            using type = Operation<Cosmetic<Elements>...>;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;
    };

    template<template<typename...> class...Cosmetics>
    using Road = ProtoRoad<Cosmetics...>;
};

template<typename Element>
struct Plume<Element>
{
    // One Element
    // Multiple Containers
    template<template<typename...> class...Cosmetics>
    struct ProtoRoad 
    { 
        template<template<typename...> class Operation>
        struct Detail
        {
            using type = Operation<Cosmetics<Element>...>;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;
    };

    template<template<typename...> class...Cosmetics>
    using Road = ProtoRoad<Cosmetics...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/plume/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/typelivore/plume.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/plume.test.hpp)
