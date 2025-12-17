<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::SensiblePlume`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-sensible-plume">To Index</a></p>

## Description

`Typelivore::SensiblePlume` accepts a list of elements.
Its first layer accepts an operation and returns a function.

When invoked by a list of transformations, the function instantiates the transformations using its arguments via a process similar to pack expansion and invokes the operation by the instantiated transformations.

Check out **Example** for more information.

<pre><code>   E
-> Oper
-> Transf<sub>0</sub>, Transf<sub>1</sub>, ..., Transf<sub>n</sub>
-> Oper&lt;Transf<sub>0</sub>&lt;E&gt;, Transf<sub>1</sub>&lt;E&gt;, ..., Transf<sub>n</sub>&lt;E&gt;&gt;</code></pre>

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>n</sub>
-> Oper
-> Transf
-> Oper&lt;Transf&lt;E<sub>0</sub>&gt;, Transf&lt;E<sub>1</sub>&gt;, ..., Transf&lt;E<sub>n</sub>&gt;&gt;</code></pre>

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>n</sub>
-> Oper
-> Transf<sub>0</sub>, Transf<sub>1</sub>, ..., Transf<sub>n</sub>
-> Oper&lt;Transf<sub>0</sub>&lt;E<sub>0</sub>&gt;, Transf<sub>1</sub>&lt;E<sub>1</sub>&gt;, ..., Transf<sub>n</sub>&lt;E<sub>n</sub>&gt;&gt;</code></pre>

## Type Signature

```Haskell
SensiblePlume
 :: typename... 
 -> template<typename...> class...
 -> template<template<typename...> class...>
```

## Structure

```C++
template<typename>
struct SensiblePlume
{
    template<template<typename...> class>
    alias Road
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
};
```

```C++
template<typename...>
struct SensiblePlume
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
struct SensiblePlume
{
    template<template<typename...> class>
    alias Road
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
};
```

## Examples

We will see three examples that present different use cases of `Typelivore::SensiblePlume`:

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
using Result = SensiblePlume<int>
::Road<Operation>
::Road<ZeroStar, OneStar, TwoStars>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

- We will use `OneStar` to pack each of `int`, `float`, and `double`.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
/**** SupposedResult ****/
using SupposedResult_1 = Operation<int*, float*, double*>;

/**** Result ****/
using Result_1 = SensiblePlume<int, float, double>
::Road<Operation>
::Road<OneStar>;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult_1>);
```

- We will pack `int`, `float`, and `double` into `ZeroStar`, `OneStar`, and `TwoStars` separately.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
/**** SupposedResult ****/
using SupposedResult_2 = Operation<int, float*, double**>;

/**** Result ****/
using Result_2 = SensiblePlume<int, float, double>
::Road<Operation>
::Road<ZeroStar, OneStar, TwoStars>;

/**** Test ****/
static_assert(std::same_as<Result_2, SupposedResult_2>);
```

## Implementation

`Typelivore::SensiblePlume` separates cases according to the number of parameters.
The goal is to mimic the behavior of pack expansion in C++:

- If the user only provides one element, we pack the element in each container separately;

- If the user only provides one container, we use the container to pack each element separately;

- Otherwise, the number of elements shall match the number of containers.
We pack each element into its corresponding container.

Here's the entire implementation:

```C++
template<typename...Elements>
struct SensiblePlume
{
    template<template<typename...> class Operation>
    struct ProtoRoad 
    {
        // Multiple Elements
        // Multiple Containers
        template<template<typename...> class...Cosmetics>
        struct Detail
        {
            using type = Operation<Cosmetics<Elements>...>;
        };

        // Multiple Elements
        // One Container
        template<template<typename...> class Cosmetic>
        struct Detail<Cosmetic>
        {
            using type = Operation<Cosmetic<Elements>...>;
        };

        template<template<typename...> class...Cosmetics>
        using Road = Detail<Cosmetics...>::type;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

template<typename Element>
struct SensiblePlume<Element>
{
    template<template<typename...> class Operation>
    struct ProtoRoad 
    {
        // One Element
        // Multiple Containers
        template<template<typename...> class...Cosmetics>
        using Road = Operation<Cosmetics<Element>...>;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/sensible_plume/implementation.hpp)
- [Source code](../../../../conceptrodon/typelivore/sensible_plume.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/sensible_plume.test.hpp)
