<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Warehivore::Paste`

## Description

`Warehivore::Paste` is an alias template. It concatenates a variable number of packed warehouses. The first warehouse will be used to hold the result.
<pre><code>   ...Warehouse<sub><i>i</i></sub>&lt;Containers<sub><i>i</i></sub>...&gt;...
-> Warehouse<sub><i>0</i></sub>&lt;Containers<sub><i>0</i></sub>..., Containers<sub><i>1</i></sub>..., ...></code></pre>

## Type Signature

```Haskell
Paste :: template<typename...>
```

## Structure

```C++
template<typename...>
struct Paste
{
    using type = RESULT;
};
```

## Example

Here, we paste `Warehouse_0<Con_0>`,  `Warehouse_1<Con_1, Con_2>` and `Warehouse_2<Con_3>` together:

```C++
template<template<typename...> class...>
struct Warehouse_0;

template<template<typename...> class...>
struct Warehouse_1;

template<template<typename...> class...>
struct Warehouse_2;

template<typename...>
struct Con_0;

template<typename...>
struct Con_1;

template<typename...>
struct Con_2;

template<typename...>
struct Con_3;

using SupposedResult = Warehouse_0<Con_0, Con_1, Con_2, Con_3>;

using Result = Paste
<
    Warehouse_0<Con_0>, 
    Warehouse_1<Con_1, Con_2>,
    Warehouse_2<Con_3>
>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Warehivore::Paste` is implemented as a shortcut to the member `type` of [`Warehivore::TypicalPaste`](./typical_paste.doc.md).

```C++
template<typename...Args>
using Paste = TypicalPaste<Args...>::type;
```

## Links

- [source code](../../../../conceptrodon/warehivore/paste.hpp)
- [unit test](../../../../tests/unit/warehivore/paste.test.hpp)
