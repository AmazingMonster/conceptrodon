<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::BindBack`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-bind-back">To Index</a></p>

## Description

`Pagelivore::BindBack` accepts an operation.
Its first layer accepts a list of variables and returns a function.

When invoked, the function adds the variables to the end of the argument list and instantiates the operation with the result.

<pre><code>   Oper
-> Vs...
-> Args...
-> Oper&lt;Args..., Vs...&gt;</code></pre>

## Type Signature

```Haskell
BindBack
 :: template<auto...> class... 
 -> auto...
 -> template<auto...>
```

## Structure

```C++
template<template<auto...> class>
struct BindBack
{
    template<auto...>
    alias Page
    {
        template<auto...>
        alias Page = RESULT;
    };
};
```

## Examples

We will bind `-1, -2` to the back of `Operation`.

```C++
/**** Operation ****/
template<auto...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<0, 1, -1, -2>;

/**** Metafunction ****/
template<auto...Args>
using Metafunction = BindBack<Operation>
::Page<-1, -2>
::Page<Args...>;

/**** Result ****/
using Result = Metafunction<0, 1>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The key is to halt the invocation of `Operation` until the argument list is fully provided.

Here's the entire implementation:

```C++
template<template<auto...> class Operation>
struct BindBack
{
    template<auto...Endings>
    struct ProtoPage
    {
        template<auto...Variables>
        using Page = Operation<Variables..., Endings...>;
    };

    template<auto...Endings>
    using Page = ProtoPage<Endings...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/bind_back/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/pagelivore/bind_back.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/bind_back.test.hpp)
