<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::BindBack`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-bind-back">To Index</a></p>

## Description

`Mouldivore::BindBack` accepts an operation.
Its first layer accepts a list of elements and returns a function.

When invoked, the function adds the elements to the end of the argument list and instantiates the operation with the result.

<pre><code>   Oper
-> Es...
-> Args...
-> Oper&lt;Args..., Es...&gt;</code></pre>

## Type Signature

```Haskell
BindBack
 :: template<typename...> class... 
 -> typename...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct BindBack
{
    template<typename...>
    alias Mold
    {
        template<typename...>
        alias Mold = RESULT;
    };
};
```

## Examples

We will bind `int, int*` to the back of `Operation`.

```C++
/**** Operation ****/
template<typename...>
struct Operation;

/**** Supposed Result ****/
using SupposedResult = Operation<int**, int***, int, int*>;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = BindBack<Operation>
::Mold<int, int*>
::Mold<Args...>;

/**** Result ****/
using Result = Metafunction<int**, int***>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The key is to halt the invocation of `Operation` until the argument list is fully provided.

Here's the entire implementation:

```C++
template<template<typename...> class Operation>
struct BindBack
{
    template<typename...Endings>
    struct ProtoMold
    {
        template<typename...Elements>
        using Mold = Operation<Elements..., Endings...>;
    };

    template<typename...Endings>
    using Mold = ProtoMold<Endings...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/bind_back/implementation.hpp)
- [Source code](../../../../conceptrodon/mouldivore/bind_back.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/bind_back.test.hpp)
