<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Roadrivore::Flip`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#roadrivore-flip">To Index</a></p>

## Description

`Roadrivore::Flip` accepts an operation and flips its *0*th layer and the *1*th layer.

<pre><code>   <i>0</i>th Layer { <i>1</i>st Layer }
-> <i>1</i>st Layer { <i>0</i>th Layer }</code></pre>

## Type Signature

```Haskell
-- flip with Mold
Flip
 :: template<template<typename...> class...> class... 
 -> typename...
 -> template<template<typename...> class...>

-- flip with Page
Flip
 :: template<template<typename...> class...> class... 
 -> auto...
 -> template<template<typename...> class...>

-- flip with Road
Flip
 :: template<template<typename...> class...> class... 
 -> template<typename...> class...
 -> template<template<typename...> class...>

-- flip with Rail
Flip
 :: template<template<typename...> class...> class... 
 -> template<auto...> class...
 -> template<template<typename...> class...>

-- flip with Flow
Flip
 :: template<template<typename...> class...> class... 
 -> template<template<typename...> class...> class...
 -> template<template<typename...> class...>

-- flip with Sail
Flip
 :: template<template<typename...> class...> class... 
 -> template<template<auto...> class...> class...
 -> template<template<typename...> class...>

-- flip with Snow
Flip
 :: template<template<typename...> class...> class... 
 -> template<template<template<typename...> class...> class...> class...
 -> template<template<typename...> class...>

-- flip with Hail
Flip
 :: template<template<typename...> class...> class... 
 -> template<template<template<auto...> class...> class...> class...
 -> template<template<typename...> class...>

-- flip with Cool
Flip
 :: template<template<typename...> class...> class... 
 -> template<template<template<template<typename...> class...> class...> class...> class...
 -> template<template<typename...> class...>

-- flip with Calm
Flip
 :: template<template<typename...> class...> class... 
 -> template<template<template<template<auto...> class...> class...> class...> class...
 -> template<template<typename...> class...>

-- flip with Grit
Flip
 :: template<template<typename...> class...> class... 
 -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
 -> template<template<typename...> class...>

-- flip with Will
Flip
 :: template<template<typename...> class...> class... 
 -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
 -> template<template<typename...> class...>

-- flip with Glow
Flip
 :: template<template<typename...> class...> class... 
 -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
 -> template<template<typename...> class...>

-- flip with Dawn
Flip
 :: template<template<typename...> class...> class... 
 -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
 -> template<template<typename...> class...>
```

## Structure

```C++
template<template<template<typename...> class...> class>
struct Flip
{
    template<typename...>
    alias Mold
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };

    template<auto...>
    alias Page
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };

    template<template<typename...> class...>
    alias Road
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
    
    template<template<auto...> class...>
    alias Rail
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
    
    template<template<template<typename...> class...> class...>
    alias Flow
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
    
    template<template<template<auto...> class...> class...>
    alias Sail
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
    
    template<template<template<template<typename...> class...> class...> class...>
    alias Snow
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
    
    template<template<template<template<auto...> class...> class...> class...>
    alias Hail
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
    
    template<template<template<template<template<typename...> class...> class...> class...> class...>
    alias Cool
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
    
    template<template<template<template<template<auto...> class...> class...> class...> class...>
    alias Calm
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
    
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
    alias Grit
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
    
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
    alias Will
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
    
    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
    alias Glow
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
    
    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
    alias Dawn
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
};
```

## Examples

We will flip `Operation` and its member `Mold`.

```C++
/**** Operation ****/
template<template<typename...> class...>
struct Operation
{
    template<typename...>
    struct ProtoMold {};

    template<typename...Args>
    using Mold = ProtoMold<Args...>;
};

/**** SupposedResult ****/
using SupposedResult = Operation<std::tuple>
::Mold<int, int*>;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Flip<Operation>
::Mold<Args...>;

/**** Result ****/
using Result = Metafunction<int, int*>::Road<std::tuple>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

Although there are many cases to consider, the implementation for each case is straightforward.
We will implement the one where the function flips the operation and its member `Mold`.

```C++
template<template<template<typename...> class...> class Operation>
struct Flip
{
    template<typename...Elements>
    struct ProtoMold 
    {
        template<template<typename...> class...Agreements>
        using Road = Operation<Agreements...>
        ::template Mold<Elements...>;
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/roadrivore/flip/implementation.hpp)
- [Source code](../../../../conceptrodon/roadrivore/flip.hpp)
- [Unit test](../../../../tests/unit/metafunctions/roadrivore/flip.test.hpp)
