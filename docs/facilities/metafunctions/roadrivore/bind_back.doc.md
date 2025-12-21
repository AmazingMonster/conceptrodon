<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Roadrivore::BindBack`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#roadrivore-bind-back">To Index</a></p>

## Description

`Roadrivore::BindBack` accepts an operation.
Its first layer accepts a list of containers and returns a function.

When invoked, the function adds the containers to the end of the argument list and instantiates the operation with the result.

<pre><code>   Oper
-> Cons...
-> Args...
-> Oper&lt;Args..., Cons...&gt;</code></pre>

## Type Signature

```Haskell
BindBack
 :: template<template<typename...> class...> class... 
 -> template<typename...> class...
 -> template<template<typename...> class...>
```

## Structure

```C++
template<template<template<typename...> class...> class>
struct BindBack
{
    template<template<typename...> class...>
    alias Road
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
};
```

## Examples

We will bind `Con_0, Con_1` to the back of `Operation`.

```C++
/**** Dummy Arguments ****/
template<typename...>
struct Con_0;

template<typename...>
struct Con_1;

template<typename...>
struct Con_2;

template<typename...>
struct Con_3;

/**** Operation ****/
template<template<typename...> class...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<Con_2, Con_3, Con_0, Con_1>;

/**** Metafunction ****/
template<template<typename...> class...Args>
using Metafunction = BindBack<Operation>
::Road<Con_0, Con_1>
::Road<Args...>;

/**** Result ****/
using Result = Metafunction<Con_2, Con_3>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The key is to halt the invocation of `Operation` until the argument list is fully provided.

Here's the entire implementation:

```C++
template<template<template<typename...> class...> class Operation>
struct BindBack
{
    template<template<typename...> class...Endings>
    struct ProtoRoad
    {
        template<template<typename...> class...Containers>
        using Road = Operation<Containers..., Endings...>;
    };

    template<template<typename...> class...Endings>
    using Road = ProtoRoad<Endings...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/roadrivore/bind_back/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/roadrivore/bind_back.hpp)
- [Unit test](../../../../tests/unit/metafunctions/roadrivore/bind_back.test.hpp)
