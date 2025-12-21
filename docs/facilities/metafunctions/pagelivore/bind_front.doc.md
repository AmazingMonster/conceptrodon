<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::BindFront`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-bind-front">To Index</a></p>

## Description

`Pagelivore::BindFront` accepts an operation.
Its first layer accepts a list of variables and returns a function.
When invoked, the function adds the variables to the front of the argument list and instantiates the operation with the result.

<pre><code>   Oper
-> Vs...
-> Args...
-> Oper&lt;Vs..., Args...&gt;</code></pre>

## Type Signature

```Haskell
BindFront
 :: template<auto...> class... 
 -> auto...
 -> template<auto...>
```

## Structure

```C++
template<template<auto...> class>
struct BindFront
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

We will bind `-1, -2` to the front of `Operation`.

```C++
/**** Operation ****/
template<auto...>
struct Operation;

/**** SupposedResult */
using SupposedResult = Operation<-1, -2, 0, 1>;

/**** Metafunction ****/
template<auto...Args>
using Metafunction = BindFront<Operation>
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
struct BindFront
{
    template<auto...Beginnings>
    struct ProtoPage
    {
        template<auto...Variables>
        using Page = Operation<Beginnings..., Variables...>;
    };

    template<auto...Beginnings>
    using Page = ProtoPage<Beginnings...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/bind_front/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/pagelivore/bind_front.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/bind_front.test.hpp)
