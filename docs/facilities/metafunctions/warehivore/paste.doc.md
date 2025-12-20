<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Warehivore::Paste`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#warehivore-paste">To Index</a></p>

## Description

`Warehivore::Paste` accepts a list of packed warehouses.
It concatenates them together and uses the first warehouse to hold the result.

<pre><code>   Ware<sub><i>0</i></sub>&lt;Cons<sub><i>0</i></sub>...&gt;, Ware<sub><i>1</i></sub>&lt;Cons<sub><i>1</i></sub>...&gt;, ..., Ware<sub><i>n</i></sub>&lt;Cons<sub><i>n</i></sub>...&gt;
-> Ware<sub><i>0</i></sub>&lt;Cons<sub><i>0</i></sub>..., Cons<sub><i>1</i></sub>..., ..., Cons<sub><i>n</i></sub>...></code></pre>

## Type Signature

```Haskell
Paste
 :: template<typename...>
```

## Structure

```C++
template<typename...>
alias Paste = RESULT;
```

## Examples

Here, we paste `Warehouse_0<Con_0>`,  `Warehouse_1<Con_1, Con_2>` and `Warehouse_2<Con_3>` together:

```C++
/**** Vessels ****/
template<template<typename...> class...>
struct Warehouse_0;

template<template<typename...> class...>
struct Warehouse_1;

template<template<typename...> class...>
struct Warehouse_2;

/**** Items ****/
template<typename...>
struct Con_0;

template<typename...>
struct Con_1;

template<typename...>
struct Con_2;

template<typename...>
struct Con_3;

/**** SupposedResult ****/
using SupposedResult = Warehouse_0<Con_0, Con_1, Con_2, Con_3>;

/**** Result ****/
using Result = Paste
<
    Warehouse_0<Con_0>, 
    Warehouse_1<Con_1, Con_2>,
    Warehouse_2<Con_3>
>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Warehivore::Paste` is implemented as a shortcut to the member `type` of [`Warehivore::TypicalPaste`](./typical_paste.doc.md).

```C++
template<typename...Args>
using Paste = TypicalPaste<Args...>::type;
```

## Links

- [Example](../../../code/facilities/metafunctions/warehivore/paste/implementation.hpp)
- [Source code](../../../../conceptrodon/warehivore/paste.hpp)
- [Unit test](../../../../tests/unit/metafunctions/warehivore/paste.test.hpp)
