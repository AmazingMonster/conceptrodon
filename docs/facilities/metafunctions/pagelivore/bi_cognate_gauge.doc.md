<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::BiCognateGauge`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-bi-cognate-gauge">To Index</a></p>

## Description

`Pagelivore::BiCognateGauge` accepts an operation.
Its first layer accepts a list of transformations and returns a function.

When invoked, the function instantiates the transformations using its arguments via a process similar to pack expansion;
then, it invokes the operation by the value results collected from the instantiated transformations.

Check out **Examples** for more information.

<pre><code>   Oper
-> Transf<sub>0</sub>, Transf<sub>1</sub>, ..., Transf<sub>n</sub>
-> Arg
-> Oper&lt;Transfs<sub>0</sub>&lt;Arg&gt;::value, Transfs<sub>1</sub>&lt;Arg&gt;::value, ..., Transfs<sub>n</sub>&lt;Arg&gt;::value&gt;</code></pre>

<pre><code>   Oper
-> Transf
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;Transf&lt;Arg<sub>0</sub>&gt;::value, Transf&lt;Arg<sub>1</sub>&gt;::value, ..., Transf&lt;Arg<sub>n</sub>&gt;::value&gt;</code></pre>

<pre><code>   Oper
-> Transf<sub>0</sub>, Transf<sub>1</sub>, ..., Transf<sub>n</sub>
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;Transf<sub>0</sub>&lt;Arg<sub>0</sub>&gt;::value, Transf<sub>1</sub>&lt;Arg<sub>1</sub>&gt;::value, ..., Transf<sub>n</sub>&lt;Arg<sub>n</sub>&gt;::value&gt;</code></pre>

## Type Signature

```Haskell
BiCognateGauge
 :: template<auto...> class...
 -> template<auto...> class...
 -> template<auto...>

BiCognateGauge
 :: template<auto...> class...
 -> template<typename...> class...
 -> template<typename...>
```

## Structure

```C++
// Gauge `Rail`s
template<template<auto...> class>
struct BiCognateGauge
{
    template<template<auto...> class>
    alias Rail
    {
        template<auto>
        alias Page = RESULT;
    };
};

template<template<auto...> class>
struct BiCognateGauge
{
    template<template<auto...> class>
    alias Rail
    {
        template<auto...>
        alias Page = RESULT;
    };
};

template<template<auto...> class>
struct BiCognateGauge
{
    template<template<auto...> class...>
    alias Rail
    {
        template<auto...>
        alias Page = RESULT;
    };
};

// Gauge `Road`s
template<template<auto...> class>
struct BiCognateGauge
{
    template<template<typename...> class>
    alias Road
    {
        template<typename>
        alias Mold = RESULT;
    };
};

template<template<auto...> class>
struct BiCognateGauge
{
    template<template<typename...> class>
    alias Road
    {
        template<typename...>
        alias Mold = RESULT;
    };
};

template<template<auto...> class>
struct BiCognateGauge
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

We will see six examples that present different use cases of `Pagelivore::BiCognateGauge`:

- We will pack `0` into `AddZero`, `AddOne` and `AddTwo`.
Then, we will collect `value` members of the results to instantiate `Operation`.

```C++
/**** AddZero ****/
template<auto I>
struct AddZero 
{ 
    static constexpr auto value
    {I}; 
};

/**** AddOne ****/
template<auto I>
struct AddOne
{ 
    static constexpr auto value
    {I + 1}; 
};

/**** AddTwo ****/
template<auto I>
struct AddTwo
{ 
    static constexpr auto value
    {I + 2}; 
};

/**** Operation ****/
template<auto...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<0, 1, 2>;

/**** Result ****/
using Result 
= BiCognateGauge<Operation>
::Rail<AddZero, AddOne, AddTwo>
::Page<0>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

- We will use `AddOne` to pack each of `0`, `1`, and `2`.
Then, we will collect `value` members of the results to instantiate `Operation`.

```C++
/**** SupposedResult ****/
using SupposedResult_1 = Operation<1, 2, 3>;

/**** Result ****/
using Result_1 = BiCognateGauge<Operation>
::Rail<AddOne>
::Page<0, 1, 2>;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult_1>);
```

- We will pack `0`, `1`, and `2` into `AddZero`, `AddOne`, and `AddTwo` separately.
Then, we will collect `value` members of the results to instantiate `Operation`.

```C++
/**** SupposedResult ****/
using SupposedResult_2 = Operation<0, 2, 4>;

/**** Result ****/
using Result_2 = BiCognateGauge<Operation>
::Rail<AddZero, AddOne, AddTwo>
::Page<0, 1, 2>;

/**** Test ****/
static_assert(std::same_as<Result_2, SupposedResult_2>);
```

- We will pack `std::integral_constant<int, 0>` into `TypeAddZero`, `TypeAddOne` and `TypeAddTwo`.
Then, we will collect `value` members of the results to instantiate `Operation`.

```C++
/**** TypeAddZero ****/
template<typename Element>
struct TypeAddZero 
{ 
    static constexpr auto value
    {Element::value}; 
};

/**** TypeAddOne ****/
template<typename Element>
struct TypeAddOne
{ 
    static constexpr auto value
    {Element::value + 1}; 
};

/**** TypeAddTwo ****/
template<typename Element>
struct TypeAddTwo
{ 
    static constexpr auto value
    {Element::value + 2}; 
};

/**** SupposedResult ****/
using SupposedResult_3 = Operation<0, 1, 2>;

/**** Result ****/
using Result_3 
= BiCognateGauge<Operation>
::Road<TypeAddZero, TypeAddOne, TypeAddTwo>
::Mold<std::integral_constant<int, 0>>;

/**** Test ****/
static_assert(std::same_as<Result_3, SupposedResult_3>);
```

- We will use `TypeAddOne` to pack each of `std::integral_constant<int, 0>`, `std::integral_constant<int, 1>`, and `std::integral_constant<int, 2>`.
Then, we will collect `value` members of the results to instantiate `Operation`.

```C++
/**** SupposedResult ****/
using SupposedResult_4 = Operation<1, 2, 3>;

/**** Result ****/
using Result_4 = BiCognateGauge<Operation>
::Road<TypeAddOne>
::Mold<
    std::integral_constant<int, 0>,
    std::integral_constant<int, 1>,
    std::integral_constant<int, 2>
>;

/**** Test ****/
static_assert(std::same_as<Result_4, SupposedResult_4>);
```

- We will pack `std::integral_constant<int, 0>`, `std::integral_constant<int, 1>`, and `std::integral_constant<int, 2>` into `TypeAddZero`, `TypeAddOne`, and `TypeAddTwo` separately.
Then, we will collect `value` members of the results to instantiate `Operation`.

```C++
/**** SupposedResult ****/
using SupposedResult_5 = Operation<0, 2, 4>;

/**** Result ****/
using Result_5 = BiCognateGauge<Operation>
::Road<TypeAddZero, TypeAddOne, TypeAddTwo>
::Mold<
    std::integral_constant<int, 0>,
    std::integral_constant<int, 1>,
    std::integral_constant<int, 2>
>;

/**** Test ****/
static_assert(std::same_as<Result_5, SupposedResult_5>);
```

## Implementation

`Pagelivore::BiCognateGauge` separates cases according to the number of parameters.
The goal is to mimic the behavior of pack expansion in C++:

- If the user only provides one variable, we pack the variable in each sequence separately;

- If the user only provides one sequence, we use the sequence to pack each variable separately;

- Otherwise, the number of variables shall match the number of sequences.
We pack each variable into its corresponding sequence.

Here's the entire implementation:

```C++
template<template<auto...> class Operation>
struct BiCognateGauge
{
    template<template<auto...> class...Devices>
    struct ProtoRail
    {
        // Multiple Sequences
        // Multiple Variables
        template<auto...Variables>
        struct Detail
        {
            using type = Operation<Devices<Variables>::value...>;
        };

        // Multiple Sequences
        // One Variable
        template<auto Variable>
        struct Detail<Variable>
        {
            using type = Operation<Devices<Variable>::value...>;
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
            using type = Operation<Device<Variables>::value...>;
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
            using type = Operation<Devices<Elements>::value...>;
        };

        // Multiple Containers
        // One Element
        template<typename Element>
        struct Detail<Element>
        {
            using type = Operation<Devices<Element>::value...>;
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
            using type = Operation<Device<Elements>::value...>;
        };

        template<typename...Agreements>
        using Mold = Detail<Agreements...>::type;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/bi_cognate_gauge/implementation.hpp)
- [Source code](../../../../conceptrodon/pagelivore/bi_cognate_gauge.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/bi_cognate_gauge.test.hpp)
