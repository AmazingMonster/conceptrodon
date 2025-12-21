<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::BindFront`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-bind-front">To Index</a></p>

## Description

`Mouldivore::BindFront` accepts an operation.
Its first layer accepts a list of elements and returns a function.

When invoked, the function adds the elements to the front of the argument list and instantiates the operation with the result.

<pre><code>   Oper
-> Es...
-> Args...
-> Oper&lt;Es..., Args...&gt;</code></pre>

## Type Signature

```Haskell
BindFront
 :: template<typename...> class... 
 -> typename...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct BindFront
{
    template<typename...>
    alias Page
    {
        template<typename...>
        alias Page = RESULT;
    };
};
```

## Examples

We will bind `int, int**` to the front of `Operation`.

```C++
/**** Operation ****/
template<typename...>
struct Operation;

/**** Supposed Result ****/
using SupposedResult = Operation<int, int*, int**, int***>;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = BindFront<Operation>
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
struct BindFront
{
    template<typename...Beginnings>
    struct ProtoMold
    {
        template<typename...Elements>
        using Mold = Operation<Beginnings..., Elements...>;
    };

    template<typename...Beginnings>
    using Mold = ProtoMold<Beginnings...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/bind_front/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/mouldivore/bind_front.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/bind_front.test.hpp)
