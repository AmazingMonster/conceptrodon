<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::EasyKindredRepack`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-easy-kindred-repack">To Index</a></p>

## Description

`Omennivore::EasyKindredRepack` accepts a list of packed vessels and returns a function.

When invoked by an operation, the function concatenates the packed vessels and instantiates the operation with the result.

<pre><code>   Vessel<sub><i>0</i></sub>&lt;Items<sub><i>0</i></sub>...&gt;, Vessel<sub><i>1</i></sub>&lt;Items<sub><i>1</i></sub>...&gt;, ..., Vessel<sub><i>n</i></sub>&lt;Items<sub><i>n</i></sub>...&gt;
-> Oper
-> Oper&lt;Items<sub><i>0</i></sub>..., Items<sub><i>1</i></sub>..., ..., Items<sub><i>n</i></sub>...></code></pre>

## Type Signature

```Haskell
KindredEasyRepack
 :: typename...
 -> template<template<typename...> class...>
 
KindredEasyRepack
 :: typename...
 -> template<template<auto...> class...>
 
KindredEasyRepack
 :: typename...
 -> template<template<template<typename...> class...> class...>
 
KindredEasyRepack
 :: typename...
 -> template<template<template<auto...> class...> class...>
```

## Structure

```C++
template<typename...>
struct KindredEasyRepack
{
    template<template<typename...> class>
    alias Road = RESULT;
};

template<typename...>
struct KindredEasyRepack
{
    template<template<auto...> class>
    alias Rail = RESULT;
};

template<typename...>
struct KindredEasyRepack
{
    template<template<template<typename...> class...> class>
    alias Flow = RESULT;
};

template<typename...>
struct KindredEasyRepack
{
    template<template<template<auto...> class...> class>
    alias Sail = RESULT;
};
```

## Examples

- We first concatenate `std::tuple<int>`,  `std::tuple<float, float*>` and `std::tuple<double>`. Then we pack the result into `Container`:

```C++
/**** NewContainer ****/
template<typename...Args>
requires (sizeof...(Args) == 4)
struct NewContainer;

/**** SupposedResult ****/
using SupposedResult_0 = NewContainer<int, float, float*, double>;

/**** Result ****/
using Result_0 = EasyKindredRepack
<
    std::tuple<int>, 
    std::tuple<float, float*>,
    std::tuple<double>
>::Road<NewContainer>;

/**** Test ****/
static_assert(std::same_as<Result_0, SupposedResult_0>);
```

- We first concatenate `std::integer_sequence<int, 0>`,  `std::index_sequence<1, 2>` and `std::index_sequence<3>`. Then we pack the result into `Sequence`:

```C++
/**** NewSequence ****/
template<std::make_signed_t<std::size_t>...Args>
requires (sizeof...(Args) == 4)
struct NewSequence;

/**** SupposedResult ****/
using SupposedResult_1 = NewSequence<0, 1, 2, 3>;

/**** Result ****/
using Result_1 = EasyKindredRepack
<
    std::integer_sequence<int, 0>, 
    std::index_sequence<1, 2>,
    std::index_sequence<3>
>::Rail<NewSequence>;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult_1>);
```

- We first concatenate `Warehouse_0<Con_0>`,  `Warehouse_1<Con_1, Con_2>` and `Warehouse_2<Con_3>`. Then we pack the result into `Warehouse`:

```C++
/**** NewWarehouse ****/
template<template<typename...> class...>
struct NewWarehouse;

/**** Warehouses ****/
template<template<typename...> class...>
struct Ware_0;

template<template<typename...> class...>
struct Ware_1;

template<template<typename...> class...>
struct Ware_2;

/**** Dummy Arguments ****/
template<typename...>
struct Con_0;

template<typename...>
struct Con_1;

template<typename...>
struct Con_2;

template<typename...>
struct Con_3;

/**** SupposedResult ****/
using SupposedResult_2 = NewWarehouse<Con_0, Con_1, Con_2, Con_3>;

/**** Result ****/
using Result_2 = EasyKindredRepack
<
    Ware_0<Con_0>, 
    Ware_1<Con_1, Con_2>,
    Ware_2<Con_3>
>::Flow<NewWarehouse>;

/**** Test ****/
static_assert(std::same_as<Result_2, SupposedResult_2>);
```

Here, we first concatenate `Stockroom_0<Seq_0>`,  `Stockroom_1<Seq_1, Seq_2>` and `Stockroom_2<Seq_3>`. Then we pack the result into `Stockroom`:

```C++
/**** NewStockroom ****/
template<template<auto...> class...>
struct NewStockroom;

/**** Stockrooms ****/
template<template<auto...> class...>
struct Stoc_0;

template<template<auto...> class...>
struct Stoc_1;

template<template<auto...> class...>
struct Stoc_2;

/**** Dummy Arguments ****/
template<auto...>
struct Seq_0;

template<auto...>
struct Seq_1;

template<auto...>
struct Seq_2;

template<auto...>
struct Seq_3;

/**** SupposedResult ****/
using SupposedResult_3 = NewStockroom<Seq_0, Seq_1, Seq_2, Seq_3>;

/**** Result ****/
using Result_3 = EasyKindredRepack
<
    Stoc_0<Seq_0>, 
    Stoc_1<Seq_1, Seq_2>,
    Stoc_2<Seq_3>
>::Sail<NewStockroom>;

/**** Test ****/
static_assert(std::same_as<Result_3, SupposedResult_3>);
```

## Implementation

We will implement `Omennivore::EasyKindredRepack` by uniting `Cotanivore::KindredRepack`, `Sequnivore::KindredRepack`, `Stockivore::KindredRepack`, and `Warehivore::KindredRepack` into one function.
To do so, we need to detect the underlying vessels of the parameter pack in the template head of `Omennivore::EasyKindredRepack` to produce partial specializations.
Hence, we create the following helper classes.

```C++
/**** IsMoldful ****/
// Detect packed `Mold`
template<typename>
struct IsMoldful
{ static constexpr bool value {false}; };

template<template<typename...> class Container, typename...Elements>
struct IsMoldful<Container<Elements...>>
{ static constexpr bool value {true}; };

/**** IsRoadful ****/
// Detect packed `Road`
template<typename>
struct IsRoadful
{ static constexpr bool value {false}; };

template
<
    template<template<typename...> class...> class Ware,
    template<typename...> class...Containers
>
struct IsRoadful<Ware<Containers...>>
{ static constexpr bool value {true}; };

/**** IsRailful ****/
// Detect packed `Rail`
template<typename>
struct IsRailful
{ static constexpr bool value {false}; };

template
<
    template<template<auto...> class...> class Stoc,
    template<auto...> class...Sequences
>
struct IsRailful<Stoc<Sequences...>>
{ static constexpr bool value {true}; };
```

We will leave the functionality of `Sequnivore::KindredRepack` to the primary template.
In this way, we won't need to test whether the underlying vessels are `std::integer_sequence`s.
Here is the entire implementation.

```C++
template<typename...Packages>
struct EasyKindredRepack
: public Sequnivore::KindredRepack<Packages...>
{};

template<typename...Packages>
requires (...&&IsMoldful<Packages>::value)
struct EasyKindredRepack<Packages...>
: public Cotanivore::KindredRepack<Packages...>
{};

template<typename...Packages>
requires (...&&IsRoadful<Packages>::value)
struct EasyKindredRepack<Packages...>
: public Warehivore::KindredRepack<Packages...>
{};

template<typename...Packages>
requires (...&&IsRailful<Packages>::value)
struct EasyKindredRepack<Packages...>
: public Stockivore::KindredRepack<Packages...>
{};
```

## Links

- [Example](../../../code/facilities/metafunctions/omennivore/easy_kindred_repack/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/omennivore/easy_kindred_repack.hpp)
- [Unit test](../../../../tests/unit/metafunctions/omennivore/easy_kindred_repack.type.test.hpp)
