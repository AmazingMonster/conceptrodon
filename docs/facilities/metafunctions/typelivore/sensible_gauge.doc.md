<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::SensibleGauge`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-sensible-gauge">To Index</a></p>

## Description

`Typelivore::SensibleGauge` accepts a list of elements.
Its first layer accepts an operation and returns a function.

When invoked by a list of transformations, the function instantiates the transformations using the elements via a process similar to pack expansion.
Then, it invokes the operation by the value results collected from the instantiated transformations.

Check out **Examples** for more information.

<pre><code>   E
-> Oper
-> Transf<sub>0</sub>, Transf<sub>1</sub>, ..., Transf<sub>n</sub>
-> Oper&lt;Transfs<sub>0</sub>&lt;E&gt;::value, Transfs<sub>1</sub>&lt;E&gt;::value, ..., Transfs<sub>n</sub>&lt;E&gt;::value&gt;</code></pre>

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>n</sub>
-> Oper
-> Transf
-> Oper&lt;Transf&lt;E<sub>0</sub>&gt;::value, Transf&lt;E<sub>1</sub>&gt;::value, ..., Transf&lt;E<sub>n</sub>&gt;::value&gt;</code></pre>

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>n</sub>
-> Oper
-> Transf<sub>0</sub>, Transf<sub>1</sub>, ..., Transf<sub>n</sub>
-> Oper&lt;Transf<sub>0</sub>&lt;E<sub>0</sub>&gt;::value, Transf<sub>1</sub>&lt;E<sub>1</sub>&gt;::value, ..., Transf<sub>n</sub>&lt;E<sub>n</sub>&gt;::value&gt;</code></pre>

## Type Signature

```Haskell
SensibleGauge
 :: typename... 
 -> template<auto...> class...
 -> template<template<typename...> class...>
```

## Structure

```C++
template<typename>
struct SensibleGauge
{
    template<template<auto...> class>
    alias Rail
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
};
```

```C++
template<typename...>
struct SensibleGauge
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
template<typename...>
struct SensibleGauge
{
    template<template<auto...> class>
    alias Rail
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
};
```

## Examples

We will see three examples that present different use cases of `Typelivore::SensibleGauge`:

- We will pack `std::integral_constant<int, 0>` into `AddZero`, `AddOne` and `AddTwo`.
Then, we will collect `value` members of the results to instantiate `Operation`.

```C++
/**** Transformations ****/
template<typename Element>
struct AddZero 
{ 
    static constexpr auto value
    {Element::value}; 
};

template<typename Element>
struct AddOne
{ 
    static constexpr auto value
    {Element::value + 1}; 
};

template<typename Element>
struct AddTwo
{ 
    static constexpr auto value
    {Element::value + 2}; 
};

/**** Operation ****/
template<auto...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<0, 1, 2>;

/**** Result ****/
using Result 
= SensibleGauge<std::integral_constant<int, 0>>
::Rail<Operation>
::Road<AddZero, AddOne, AddTwo>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

- We will use `AddOne` to pack each of `std::integral_constant<int, 0>`, `std::integral_constant<int, 1>`, and `std::integral_constant<int, 2>`.
Then, we will collect `value` members of the results to instantiate `Operation`.

```C++
/**** SupposedResult ****/
using SupposedResult_1 = Operation<1, 2, 3>;

/**** Result ****/
using Result_1 = SensibleGauge<
    std::integral_constant<int, 0>,
    std::integral_constant<int, 1>,
    std::integral_constant<int, 2>
>
::Rail<Operation>
::Road<AddOne>;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult_1>);
```

- We will pack `std::integral_constant<int, 0>`, `std::integral_constant<int, 1>`, and `std::integral_constant<int, 2>` into `AddZero`, `AddOne`, and `AddTwo` separately.
Then, we will collect `value` members of the results to instantiate `Operation`.

```C++
/**** SupposedResult ****/
using SupposedResult_2 = Operation<0, 2, 4>;

/**** Result ****/
using Result_2 = SensibleGauge<
    std::integral_constant<int, 0>,
    std::integral_constant<int, 1>,
    std::integral_constant<int, 2>
>
::Rail<Operation>
::Road<AddZero, AddOne, AddTwo>;

/**** Test ****/
static_assert(std::same_as<Result_2, SupposedResult_2>);
```

## Implementation

`Typelivore::SensibleGauge` separates cases according to the number of parameters.
The goal is to mimic the behavior of pack expansion in C++:

- If the user only provides one element, we pack the element in each container separately;

- If the user only provides one container, we use the container to pack each element separately;

- Otherwise, the number of elements shall match the number of containers.
We pack each element into its corresponding container.

Here's the entire implementation:

```C++
template<typename...Elements>
struct SensibleGauge
{
    template<template<auto...> class Operation>
    struct ProtoRail
    {
        // Multiple Elements
        // Multiple Containers
        template<template<typename...> class...Devices>
        struct Detail
        {
            using type = Operation
            <Devices<Elements>::value...>;
        };
        
        // Multiple Elements
        // One Container
        template<template<typename...> class Device>
        struct Detail<Device>
        {
            using type = Operation
            <Device<Elements>::value...>;
        };

        template<template<typename...> class...Devices>
        using Road = Detail<Devices...>::type;
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

template<typename Element>
struct SensibleGauge<Element>
{
    template<template<auto...> class Operation>
    struct ProtoRail
    {
        // One Element
        // Multiple Containers
        template<template<typename...> class...Devices>
        using Road = Operation
        <Devices<Element>::value...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/sensible_gauge/implementation.hpp)
- [Source code](../../../../conceptrodon/typelivore/sensible_gauge.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/sensible_gauge.test.hpp)
