<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Raillivore::Flip`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#raillivore-flip">To Index</a></p>

## Description

`Raillivore::Flip` accepts an operation and flips its *0*th layer and the *1*th layer.

<pre><code>   <i>0</i>th Layer { <i>1</i>st Layer }
-> <i>1</i>st Layer { <i>0</i>th Layer }</code></pre>

## Type Signature

```Haskell
-- flip with Mold
Flip
 :: template<template<auto...> class...> class... 
 -> typename...
 -> template<template<auto...> class...>

-- flip with Page
Flip
 :: template<template<auto...> class...> class... 
 -> auto...
 -> template<template<auto...> class...>

-- flip with Road
Flip
 :: template<template<auto...> class...> class... 
 -> template<typename...> class...
 -> template<template<auto...> class...>

-- flip with Rail
Flip
 :: template<template<auto...> class...> class... 
 -> template<auto...> class...
 -> template<template<auto...> class...>

-- flip with Flow
Flip
 :: template<template<auto...> class...> class... 
 -> template<template<typename...> class...> class...
 -> template<template<auto...> class...>

-- flip with Sail
Flip
 :: template<template<auto...> class...> class... 
 -> template<template<auto...> class...> class...
 -> template<template<auto...> class...>

-- flip with Snow
Flip
 :: template<template<auto...> class...> class... 
 -> template<template<template<typename...> class...> class...> class...
 -> template<template<auto...> class...>

-- flip with Hail
Flip
 :: template<template<auto...> class...> class... 
 -> template<template<template<auto...> class...> class...> class...
 -> template<template<auto...> class...>

-- flip with Cool
Flip
 :: template<template<auto...> class...> class... 
 -> template<template<template<template<typename...> class...> class...> class...> class...
 -> template<template<auto...> class...>

-- flip with Calm
Flip
 :: template<template<auto...> class...> class... 
 -> template<template<template<template<auto...> class...> class...> class...> class...
 -> template<template<auto...> class...>

-- flip with Grit
Flip
 :: template<template<auto...> class...> class... 
 -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
 -> template<template<auto...> class...>

-- flip with Will
Flip
 :: template<template<auto...> class...> class... 
 -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
 -> template<template<auto...> class...>

-- flip with Glow
Flip
 :: template<template<auto...> class...> class... 
 -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
 -> template<template<auto...> class...>

-- flip with Dawn
Flip
 :: template<template<auto...> class...> class... 
 -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
 -> template<template<auto...> class...>
```

## Structure

```C++
template<template<template<auto...> class...> class>
struct Flip
{
    template<typename...>
    alias Mold
    {
        template<template<auto...> class...>
        alias Rail = RESULT;
    };

    template<auto...>
    alias Page
    {
        template<template<auto...> class...>
        alias Rail = RESULT;
    };

    template<template<typename...> class...>
    alias Road
    {
        template<template<auto...> class...>
        alias Rail = RESULT;
    };
    
    template<template<auto...> class...>
    alias Rail
    {
        template<template<auto...> class...>
        alias Rail = RESULT;
    };
    
    template<template<template<typename...> class...> class...>
    alias Flow
    {
        template<template<auto...> class...>
        alias Rail = RESULT;
    };
    
    template<template<template<auto...> class...> class...>
    alias Sail
    {
        template<template<auto...> class...>
        alias Rail = RESULT;
    };
    
    template<template<template<template<typename...> class...> class...> class...>
    alias Snow
    {
        template<template<auto...> class...>
        alias Rail = RESULT;
    };
    
    template<template<template<template<auto...> class...> class...> class...>
    alias Hail
    {
        template<template<auto...> class...>
        alias Rail = RESULT;
    };
    
    template<template<template<template<template<typename...> class...> class...> class...> class...>
    alias Cool
    {
        template<template<auto...> class...>
        alias Rail = RESULT;
    };
    
    template<template<template<template<template<auto...> class...> class...> class...> class...>
    alias Calm
    {
        template<template<auto...> class...>
        alias Rail = RESULT;
    };
    
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
    alias Grit
    {
        template<template<auto...> class...>
        alias Rail = RESULT;
    };
    
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
    alias Will
    {
        template<template<auto...> class...>
        alias Rail = RESULT;
    };
    
    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
    alias Glow
    {
        template<template<auto...> class...>
        alias Rail = RESULT;
    };
    
    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
    alias Dawn
    {
        template<template<auto...> class...>
        alias Rail = RESULT;
    };
};
```

## Examples

We will flip `Operation` and its member `Mold`.

```C++
/**** Operation ****/
template<template<auto...> class...>
struct Operation
{
    template<typename...>
    struct ProtoMold {};

    template<typename...Args>
    using Mold = ProtoMold<Args...>;
};

/**** SupposedResult ****/
using SupposedResult = Operation<std::index_sequence>
::Mold<int, int*>;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Flip<Operation>
::Mold<Args...>;

/**** Result ****/
using Result = Metafunction<int, int*>::Rail<std::index_sequence>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

Although there are many cases to consider, the implementation for each case is straightforward.
We will implement the one where the function flips the operation and its member `Mold`.

```C++
template<template<template<auto...> class...> class Operation>
struct Flip
{
    template<typename...Elements>
    struct ProtoMold 
    {
        template<template<auto...> class...Agreements>
        using Rail = Operation<Agreements...>
        ::template Mold<Elements...>;
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/raillivore/flip/implementation.hpp)
- [Source code](../../../../conceptrodon/raillivore/flip.hpp)
- [Unit test](../../../../tests/unit/metafunctions/raillivore/flip.test.hpp)
