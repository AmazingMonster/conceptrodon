<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::BiCognateClassicPlume`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-bi-cognate-classic-plume">To Index</a></p>

## Description

`Mouldivore::BiCognateClassicPlume` accepts an operation.
Its first layer accepts a list of transformations and returns a function.

When invoked, the function instantiates the transformations using its arguments via a process similar to pack expansion;
then, it invokes the operation by the type results collected from the instantiated transformations.

Check out [**Examples**](#examples) for more information.

<pre><code>   Oper
-> Transf<sub>0</sub>, Transf<sub>1</sub>, ..., Transf<sub>n</sub>
-> Arg
-> Oper&lt;Transfs<sub>0</sub>&lt;Arg&gt;::type, Transfs<sub>1</sub>&lt;Arg&gt;::type, ..., Transfs<sub>n</sub>&lt;Arg&gt;::type&gt;</code></pre>

<pre><code>   Oper
-> Transf
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;Transf&lt;Arg<sub>0</sub>&gt;::type, Transf&lt;Arg<sub>1</sub>&gt;::type, ..., Transf&lt;Arg<sub>n</sub>&gt;::type&gt;</code></pre>

<pre><code>   Oper
-> Transf<sub>0</sub>, Transf<sub>1</sub>, ..., Transf<sub>n</sub>
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;Transf<sub>0</sub>&lt;Arg<sub>0</sub>&gt;::type, Transf<sub>1</sub>&lt;Arg<sub>1</sub>&gt;::type, ..., Transf<sub>n</sub>&lt;Arg<sub>n</sub>&gt;::type&gt;</code></pre>

## Type Signature

```Haskell
BiCognateClassicPlume
 :: template<typename...> class...
 -> template<auto...> class...
 -> template<auto...>

BiCognateClassicPlume
 :: template<typename...> class...
 -> template<typename...> class...
 -> template<typename...>
```

## Structure

```C++
// Plume `Rail`s
template<template<typename...> class>
struct BiCognateClassicPlume
{
    template<template<auto...> class>
    alias Rail
    {
        template<auto>
        alias Page = RESULT;
    };
};

template<template<typename...> class>
struct BiCognateClassicPlume
{
    template<template<auto...> class>
    alias Rail
    {
        template<auto...>
        alias Page = RESULT;
    };
};

template<template<typename...> class>
struct BiCognateClassicPlume
{
    template<template<auto...> class...>
    alias Rail
    {
        template<auto...>
        alias Page = RESULT;
    };
};

// Plume `Road`s
template<template<typename...> class>
struct BiCognateClassicPlume
{
    template<template<typename...> class>
    alias Road
    {
        template<typename>
        alias Mold = RESULT;
    };
};

template<template<typename...> class>
struct BiCognateClassicPlume
{
    template<template<typename...> class>
    alias Road
    {
        template<typename...>
        alias Mold = RESULT;
    };
};

template<template<typename...> class>
struct BiCognateClassicPlume
{
    template<template<typename...> class...>
    alias Road
    {
        template<typename...>
        alias Mold = RESULT;
    };
};
```

## Examples

We will see six examples that present different use cases of `Mouldivore::BiCognateClassicPlume`:

- We will pack `0` into `AddZero`, `AddOne` and `AddTwo`.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
/**** Vay ****/
template<auto>
struct Vay;

/**** AddZero ****/
template<auto I>
struct AddZero 
{ 
    using type = Vay<I>; 
};

/**** AddOne ****/
template<auto I>
struct AddOne
{ 
    using type = Vay<I + 1>;
};

/**** AddTwo ****/
template<auto I>
struct AddTwo
{
    using type = Vay<I + 2>;
};

/**** Operation ****/
template<typename...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<Vay<0>, Vay<1>, Vay<2>>;

/**** Result ****/
using Result 
= BiCognateClassicPlume<Operation>
::Rail<AddZero, AddOne, AddTwo>
::Page<0>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

- We will use `AddOne` to pack each of `0`, `1`, and `2`.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
/**** Supposed Result */
using SupposedResult_1 = Operation<Vay<1>, Vay<2>, Vay<3>>;

/**** Result ****/
using Result_1 = BiCognateClassicPlume<Operation>
::Rail<AddOne>
::Page<0, 1, 2>;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult_1>);
```

- We will pack `0`, `1`, and `2` into `AddZero`, `AddOne`, and `AddTwo` separately.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
/**** Supposed Result ****/
using SupposedResult_2 = Operation<Vay<0>, Vay<2>, Vay<4>>;

/**** Result ****/
using Result_2 = BiCognateClassicPlume<Operation>
::Rail<AddZero, AddOne, AddTwo>
::Page<0, 1, 2>;

/**** Test ****/
static_assert(std::same_as<Result_2, SupposedResult_2>);
```

- We will pack `std::integral_constant<int, 0>` into `TypeAddZero`, `TypeAddOne` and `TypeAddTwo`.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
/**** TypeAddZero ****/
template<typename Element>
struct TypeAddZero 
{ 
    using type = Vay<Element::value>; 
};

/**** TypeAddOne ****/
template<typename Element>
struct TypeAddOne
{ 
    using type = Vay<Element::value + 1>; 
};

/**** TypeAddTwo ****/
template<typename Element>
struct TypeAddTwo
{ 
    using type = Vay<Element::value + 2>; 
};

/**** Supposed Result ****/
using SupposedResult_3 = Operation<Vay<0>, Vay<1>, Vay<2>>;

/**** Result ****/
using Result_3 
= BiCognateClassicPlume<Operation>
::Road<TypeAddZero, TypeAddOne, TypeAddTwo>
::Mold<std::integral_constant<int, 0>>;

/**** Test ****/
static_assert(std::same_as<Result_3, SupposedResult_3>);
```

- We will use `TypeAddOne` to pack each of `std::integral_constant<int, 0>`, `std::integral_constant<int, 1>`, and `std::integral_constant<int, 2>`.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
/**** Supposed Result ****/
using SupposedResult_4 = Operation<Vay<1>, Vay<2>, Vay<3>>;

/**** Result ****/
using Result_4 = BiCognateClassicPlume<Operation>
::Road<TypeAddOne>
::Mold
<
    std::integral_constant<int, 0>,
    std::integral_constant<int, 1>,
    std::integral_constant<int, 2>
>;

/**** Test ****/
static_assert(std::same_as<Result_4, SupposedResult_4>);
```

- We will pack `std::integral_constant<int, 0>`, `std::integral_constant<int, 1>`, and `std::integral_constant<int, 2>` into `TypeAddZero`, `TypeAddOne`, and `TypeAddTwo` separately.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
/**** Supposed Result ****/
using SupposedResult_5 = Operation<Vay<0>, Vay<2>, Vay<4>>;

/**** Result ****/
using Result_5 = BiCognateClassicPlume<Operation>
::Road<TypeAddZero, TypeAddOne, TypeAddTwo>
::Mold
<
    std::integral_constant<int, 0>,
    std::integral_constant<int, 1>,
    std::integral_constant<int, 2>
>;

/**** Test ****/
static_assert(std::same_as<Result_5, SupposedResult_5>);
```

## Implementation

`Mouldivore::BiCognateClassicPlume` separates cases according to the number of parameters.
The goal is to mimic the behavior of pack expansion in C++:

- If the user only provides one element, we pack the element in each container separately;

- If the user only provides one container, we use the container to pack each element separately;

- Otherwise, the number of elements shall match the number of containers.
We pack each element into its corresponding container.

Here's the entire implementation:

```C++
template<template<typename...> class Operation>
struct BiCognateClassicPlume
{
    template<template<auto...> class...Devices>
    struct ProtoRail
    {
        // Multiple Sequences
        // Multiple Variables
        template<auto...Variables>
        struct Detail
        {
            using type = Operation<typename Devices<Variables>::type...>;
        };

        // Multiple Sequences
        // One Variables
        template<auto Variable>
        struct Detail<Variable>
        {
            using type = Operation<typename Devices<Variable>::type...>;
        };

        template<auto...Agreements>
        using Page = Detail<Agreements...>::type;
    };

    template<template<auto...> class Device>
    struct ProtoRail<Device>
    {
        // One Sequence
        // Multiple Variables
        template<auto...Variables>
        struct Detail
        {
            using type = Operation<typename Device<Variables>::type...>;
        };

        template<auto...Agreements>
        using Page = Detail<Agreements...>::type;
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;

    template<template<typename...> class...Devices>
    struct ProtoRoad
    {
        // Multiple Containers
        // Multiple Elements
        template<typename...Elements>
        struct Detail
        {
            using type = Operation<typename Devices<Elements>::type...>;
        };

        // Multiple Containers
        // One Elements
        template<typename Element>
        struct Detail<Element>
        {
            using type = Operation<typename Devices<Element>::type...>;
        };

        template<typename...Agreements>
        using Mold = Detail<Agreements...>::type;
    };

    template<template<typename...> class Device>
    struct ProtoRoad<Device>
    {
        // One Containers
        // Multiple Elements
        template<typename...Elements>
        struct Detail
        {
            using type = Operation<typename Device<Elements>::type...>;
        };

        template<typename...Agreements>
        using Mold = Detail<Agreements...>::type;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/bi_cognate_classic_plume/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/mouldivore/bi_cognate_classic_plume.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/bi_cognate_classic_plume.test.hpp)
