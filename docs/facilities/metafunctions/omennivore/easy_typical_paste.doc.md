<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::EasyTypicalPaste`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-easy-typical-paste">To Index</a></p>

## Description

`Omennivore::EasyTypicalPaste` accepts a list of packed vessels.
It concatenates them together and uses the first vessel to hold the result.

<pre><code>   Vessel<sub><i>0</i></sub>&lt;Items<sub><i>0</i></sub>...&gt;, Vessel<sub><i>1</i></sub>&lt;Items<sub><i>1</i></sub>...&gt;, ..., Vessel<sub><i>n</i></sub>&lt;Items<sub><i>n</i></sub>...&gt;
-> Vessel<sub><i>0</i></sub>&lt;Items<sub><i>0</i></sub>..., Items<sub><i>1</i></sub>..., ..., Items<sub><i>n</i></sub>...></code></pre>

## Type Signature

```Haskell
TypicalPaste
 :: typename... -> typename
```

## Structure

```C++
template<typename...>
struct TypicalPaste
{
    using type = RESULT;
};
```

## Examples

- We will paste `std::tuple<int>`,  `std::tuple<float, float*>` and `std::tuple<double>` together:

```C++
/**** SupposedResult ****/
using SupposedResult_0 = std::tuple<int, float, float*, double>;

/**** Result ****/
using Result_0 = EasyTypicalPaste
<
    std::tuple<int>, 
    std::tuple<float, float*>,
    std::tuple<double>
>::type;

/**** Test ****/
static_assert(std::same_as<Result_0, SupposedResult_0>);
```

- We will paste `std::integer_sequence<int, 0>`,  `std::index_sequence<1, 2>` and `std::index_sequence<3>` together:

```C++
/**** SupposedResult ****/
using SupposedResult_1 = std::integer_sequence<int, 0, 1, 2, 3>;

/**** Result ****/
using Result_1 = EasyTypicalPaste
<
    std::integer_sequence<int, 0>, 
    std::index_sequence<1, 2>,
    std::index_sequence<3>
>::type;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult_1>);
```

- We paste `Ware_0<Con_0>`,  `Ware_1<Con_1, Con_2>` and `Ware_2<Con_3>` together:

```C++
/**** Warehouses ****/
template<template<typename...> class...>
struct Ware_0;

template<template<typename...> class...>
struct Ware_1;

template<template<typename...> class...>
struct Ware_2;

template<typename...>
struct Con_0;

/**** Dummy Arguments ****/
template<typename...>
struct Con_1;

template<typename...>
struct Con_2;

template<typename...>
struct Con_3;

/**** SupposedResult ****/
using SupposedResult_2 = Ware_0<Con_0, Con_1, Con_2, Con_3>;

/**** Result ****/
using Result_2 = EasyTypicalPaste
<
    Ware_0<Con_0>, 
    Ware_1<Con_1, Con_2>,
    Ware_2<Con_3>
>::type;

/**** Test ****/
static_assert(std::same_as<Result_2, SupposedResult_2>);
```

- We paste `Stoc_0<Seq_0>`,  `Stoc_1<Seq_1, Seq_2>` and `Stoc_2<Seq_3>` together:

```C++
/**** Stockrooms ****/
template<template<auto...> class...>
struct Stoc_0;

template<template<auto...> class...>
struct Stoc_1;

template<template<auto...> class...>
struct Stoc_2;

/**** Arguments ****/
template<auto...>
struct Seq_0;

template<auto...>
struct Seq_1;

template<auto...>
struct Seq_2;

template<auto...>
struct Seq_3;

/**** SupposedResult ****/
using SupposedResult_3 = Stoc_0<Seq_0, Seq_1, Seq_2, Seq_3>;

/**** Result ****/
using Result_3 = EasyTypicalPaste
<
    Stoc_0<Seq_0>, 
    Stoc_1<Seq_1, Seq_2>,
    Stoc_2<Seq_3>
>::type;

/**** Test ****/
static_assert(std::same_as<Result_3, SupposedResult_3>);
```

## Implementation

We will implement `Omennivore::EasyTypicalPaste` by uniting `Cotanivore::TypicalPaste`, `Sequnivore::TypicalPaste`, `Stockivore::TypicalPaste`, and `Warehivore::TypicalPaste` into one function.
To do so, we need to detect the underlying vessels of the parameter pack in the template head of `Omennivore::EasyTypicalPaste` to produce partial specializations.
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

We will leave the functionality of `Sequnivore::TypicalPaste` to the primary template.
In this way, we won't need to test whether the underlying vessels are `std::integer_sequence`s.
Here is the entire implementation.

```C++
template<typename...Packages>
struct EasyTypicalPaste
: public Sequnivore::TypicalPaste<Packages...>
{};

template<typename...Packages>
requires (...&&IsMoldful<Packages>::value)
struct EasyTypicalPaste<Packages...>
: public Cotanivore::TypicalPaste<Packages...>
{};

template<typename...Packages>
requires (...&&IsRoadful<Packages>::value)
struct EasyTypicalPaste<Packages...>
: public Warehivore::TypicalPaste<Packages...>
{};

template<typename...Packages>
requires (...&&IsRailful<Packages>::value)
struct EasyTypicalPaste<Packages...>
: public Stockivore::TypicalPaste<Packages...>
{};
```

## Links

- [Example](../../../code/facilities/metafunctions/omennivore/easy_typical_paste/implementation.hpp)
- [Source code](../../../../conceptrodon/omennivore/easy_typical_paste.hpp)
- [Unit test](../../../../tests/unit/metafunctions/omennivore/easy_typical_paste.type.test.hpp)
