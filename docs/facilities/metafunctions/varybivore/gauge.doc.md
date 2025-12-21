<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Gauge`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-gauge">To Index</a></p>

## Description

`Varybivore::Gauge` accepts a list of variables.
Its first layer accepts a list of sequences and returns a function.

When invoked by an operation, the function places the variables into the sequences via a process similar to pack expansion;
then, it collects the value result of each packed sequence and invokes the operation with the collection.

Check out **Examples** for more information.

<pre><code>   V
-> Transf<sub>0</sub>, Transf<sub>1</sub>, ..., Transf<sub>n</sub>
-> Oper
-> Oper&lt;Transfs<sub>0</sub>&lt;V&gt;::value, Transfs<sub>1</sub>&lt;V&gt;::value, ..., Transfs<sub>n</sub>&lt;V&gt;::value&gt;</code></pre>

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> Transf
-> Oper
-> Oper&lt;Transf&lt;V<sub>0</sub>&gt;::value, Transf&lt;V<sub>1</sub>&gt;::value, ..., Transf&lt;V<sub>n</sub>&gt;::value&gt;</code></pre>

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> Transf<sub>0</sub>, Transf<sub>1</sub>, ..., Transf<sub>n</sub>
-> Oper
-> Oper&lt;Transf<sub>0</sub>&lt;V<sub>0</sub>&gt;::value, Transf<sub>1</sub>&lt;V<sub>1</sub>&gt;::value, ..., Transf<sub>n</sub>&lt;V<sub>n</sub>&gt;::value&gt;</code></pre>

## Type Signature

```Haskell
Gauge
 :: auto... 
 -> template<auto...> class...
 -> template<template<auto...> class...>
```

## Structure

```C++
template<auto>
struct Gauge
{
    template<template<auto...> class...>
    alias Rail
    {
        template<template<auto...> class>
        alias Rail = RESULT;
    };
};
```

```C++
template<auto...>
struct Gauge
{
    template<template<auto...> class>
    alias Rail
    {
        template<template<auto...> class>
        alias Rail = RESULT;
    };
};
```

```C++
template<auto...>
struct Gauge
{
    template<template<auto...> class...>
    alias Rail
    {
        template<template<auto...> class>
        alias Rail = RESULT;
    };
};
```

## Examples

We will see three examples that present different use cases of `Varybivore::Gauge`:

- We will pack `0` into `AddZero`, `AddOne` and `AddTwo`.
Then, we will collect `value` members of the results to instantiate `Operation`.

```C++
/**** Transformations ****/
template<auto I>
struct AddZero 
{ 
    static constexpr auto value
    {I}; 
};

template<auto I>
struct AddOne
{ 
    static constexpr auto value
    {I + 1}; 
};

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
= Gauge<0>
::Rail<AddZero, AddOne, AddTwo>
::Rail<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

- We will use `AddOne` to pack each of `0`, `1`, and `2`.
Then, we will collect `value` members of the results to instantiate `Operation`.

```C++
/**** SupposedResult ****/
using SupposedResult_1 = Operation<1, 2, 3>;

/**** Result ****/
using Result_1 = Gauge<0, 1, 2>
::Rail<AddOne>
::Rail<Operation>;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult_1>);
```

- We will pack `0`, `1`, and `2` into `AddZero`, `AddOne`, and `AddTwo` separately.
Then, we will collect `value` members of the results to instantiate `Operation`.

```C++
/**** SupposedResult ****/
using SupposedResult_2 = Operation<0, 2, 4>;

/**** Result ****/
using Result_2 = Gauge<0, 1, 2>
::Rail<AddZero, AddOne, AddTwo>
::Rail<Operation>;

/**** Test ****/
static_assert(std::same_as<Result_2, SupposedResult_2>);
```

## Implementation

`Varybivore::Gauge` separates cases according to the number of parameters.
The goal is to mimic the behavior of pack expansion in C++:

- If the user only provides one variable, we pack the variable in each sequence separately;

- If the user only provides one sequence, we use the sequence to pack each variable separately;

- Otherwise, the number of variables shall match the number of sequences.
We pack each variable into its corresponding sequence.

Here's the entire implementation:

```C++
template<auto...Variables>
struct Gauge
{
    // Multiple Variables
    // Multiple Sequences
    template<template<auto...> class...Devices>
    struct ProtoRail
    { 
        template<template<auto...> class Operation>
        struct Detail
        { 
            using type = Operation<Devices<Variables>::value...>;
        };

        template<template<auto...> class...Agreements>
        using Rail = Detail<Agreements...>::type;
    };

    // Multiple Variables
    // One Sequence
    template<template<auto...> class Device>
    struct ProtoRail<Device>
    { 
        template<template<auto...> class Operation>
        struct Detail
        { 
            using type = Operation<Device<Variables>::value...>;
        };

        template<template<auto...> class...Agreements>
        using Rail = Detail<Agreements...>::type;
    };

    template<template<auto...> class...Devices>
    using Rail = ProtoRail<Devices...>;
};

template<auto Variable>
struct Gauge<Variable>
{
    // One Variable
    // Multiple Sequences
    template<template<auto...> class...Devices>
    struct ProtoRail
    { 
        template<template<auto...> class Operation>
        struct Detail
        { 
            using type = Operation<Devices<Variable>::value...>;
        };

        template<template<auto...> class...Agreements>
        using Rail = Detail<Agreements...>::type;
    };

    template<template<auto...> class...Devices>
    using Rail = ProtoRail<Devices...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/gauge/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/varybivore/gauge.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/gauge.test.hpp)
