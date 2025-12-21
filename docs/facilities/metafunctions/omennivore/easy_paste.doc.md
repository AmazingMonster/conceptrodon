<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::EasyPaste`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-easy-paste">To Index</a></p>

## Description

`Omennivore::EasyPaste` accepts a list of packed vessels.
It concatenates them together and uses the first vessel to hold the result.

<pre><code>   Vessel<sub><i>0</i></sub>&lt;Items<sub><i>0</i></sub>...&gt;, Vessel<sub><i>1</i></sub>&lt;Items<sub><i>1</i></sub>...&gt;, ..., Vessel<sub><i>n</i></sub>&lt;Items<sub><i>n</i></sub>...&gt;
-> Vessel<sub><i>0</i></sub>&lt;Items<sub><i>0</i></sub>..., Items<sub><i>1</i></sub>..., ..., Items<sub><i>n</i></sub>...></code></pre>

## Type Signature

```Haskell
Paste
 :: template<typename...>
```

## Structure

```C++
template<typename...>
using Paste = RESULT;
```

## Examples

- We will paste `std::tuple<int>`,  `std::tuple<float, float*>` and `std::tuple<double>` together:

```C++
/**** SupposedResult ****/
using SupposedResult_0 = std::tuple<int, float, float*, double>;

/**** Result ****/
using Result_0 = EasyPaste
<
    std::tuple<int>, 
    std::tuple<float, float*>,
    std::tuple<double>
>;

/**** Test ****/
static_assert(std::same_as<Result_0, SupposedResult_0>);
```

- We will paste `std::integer_sequence<int, 0>`,  `std::index_sequence<1, 2>` and `std::index_sequence<3>` together:

```C++
/**** SupposedResult ****/
using SupposedResult_1 = std::integer_sequence<int, 0, 1, 2, 3>;

/**** Result ****/
using Result_1 = EasyPaste
<
    std::integer_sequence<int, 0>, 
    std::index_sequence<1, 2>,
    std::index_sequence<3>
>;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult_1>);
```

- We paste `Warehouse_0<Con_0>`,  `Warehouse_1<Con_1, Con_2>` and `Warehouse_2<Con_3>` together:

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
using Result_2 = EasyPaste
<
    Ware_0<Con_0>, 
    Ware_1<Con_1, Con_2>,
    Ware_2<Con_3>
>;

/**** Test ****/
static_assert(std::same_as<Result_2, SupposedResult_2>);
```

- We paste `Stockroom_0<Seq_0>`,  `Stockroom_1<Seq_1, Seq_2>` and `Stockroom_2<Seq_3>` together:

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
using Result_3 = EasyPaste
<
    Stoc_0<Seq_0>, 
    Stoc_1<Seq_1, Seq_2>,
    Stoc_2<Seq_3>
>;

/**** Test ****/
static_assert(std::same_as<Result_3, SupposedResult_3>);
```

## Implementation

`Omennivore::EasyPaste` is implemented as a shortcut to the member `type` of [`Omennivore::EasyTypicalPaste`](./easy_typical_paste.doc.md).

```C++
template<typename...Args>
using EasyPaste = EasyTypicalPaste<Args...>::type;
```

## Links

- [Example](../../../code/facilities/metafunctions/omennivore/easy_paste/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/omennivore/easy_paste.hpp)
- [Unit test](../../../../tests/unit/metafunctions/omennivore/easy_paste.test.hpp)
