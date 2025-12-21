<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::Flip`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-flip">To Index</a></p>

## Description

`Mouldivore::Flip` accepts an operation and flips its *0*th layer and the *1*th layer.

<pre><code>   <i>0</i>th Layer { <i>1</i>st Layer }
-> <i>1</i>st Layer { <i>0</i>th Layer }</code></pre>

## Type Signature

```Haskell
-- flip with Mold
Flip
 :: template<typename...> class... 
 -> typename...
 -> template<typename...>

-- flip with Page
Flip
 :: template<typename...> class... 
 -> auto...
 -> template<typename...>

-- flip with Road
Flip
 :: template<typename...> class... 
 -> template<typename...> class...
 -> template<typename...>

-- flip with Rail
Flip
 :: template<typename...> class... 
 -> template<auto...> class...
 -> template<typename...>

-- flip with Flow
Flip
 :: template<typename...> class... 
 -> template<template<typename...> class...> class...
 -> template<typename...>

-- flip with Sail
Flip
 :: template<typename...> class... 
 -> template<template<auto...> class...> class...
 -> template<typename...>

-- flip with Snow
Flip
 :: template<typename...> class... 
 -> template<template<template<typename...> class...> class...> class...
 -> template<typename...>

-- flip with Hail
Flip
 :: template<typename...> class... 
 -> template<template<template<auto...> class...> class...> class...
 -> template<typename...>

-- flip with Cool
Flip
 :: template<typename...> class... 
 -> template<template<template<template<typename...> class...> class...> class...> class...
 -> template<typename...>

-- flip with Calm
Flip
 :: template<typename...> class... 
 -> template<template<template<template<auto...> class...> class...> class...> class...
 -> template<typename...>

-- flip with Grit
Flip
 :: template<typename...> class... 
 -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
 -> template<typename...>

-- flip with Will
Flip
 :: template<typename...> class... 
 -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
 -> template<typename...>

-- flip with Glow
Flip
 :: template<typename...> class... 
 -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
 -> template<typename...>

-- flip with Dawn
Flip
 :: template<typename...> class... 
 -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct Flip
{
    template<typename...>
    alias Mold
    {
        template<typename...>
        alias Mold = RESULT;
    };

    template<auto...>
    alias Page
    {
        template<typename...>
        alias Mold = RESULT;
    };

    template<template<typename...> class...>
    alias Road
    {
        template<typename...>
        alias Mold = RESULT;
    };
    
    template<template<auto...> class...>
    alias Rail
    {
        template<typename...>
        alias Mold = RESULT;
    };
    
    template<template<template<typename...> class...> class...>
    alias Flow
    {
        template<typename...>
        alias Mold = RESULT;
    };
    
    template<template<template<auto...> class...> class...>
    alias Sail
    {
        template<typename...>
        alias Mold = RESULT;
    };
    
    template<template<template<template<typename...> class...> class...> class...>
    alias Snow
    {
        template<typename...>
        alias Mold = RESULT;
    };
    
    template<template<template<template<auto...> class...> class...> class...>
    alias Hail
    {
        template<typename...>
        alias Mold = RESULT;
    };
    
    template<template<template<template<template<typename...> class...> class...> class...> class...>
    alias Cool
    {
        template<typename...>
        alias Mold = RESULT;
    };
    
    template<template<template<template<template<auto...> class...> class...> class...> class...>
    alias Calm
    {
        template<typename...>
        alias Mold = RESULT;
    };
    
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
    alias Grit
    {
        template<typename...>
        alias Mold = RESULT;
    };
    
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
    alias Will
    {
        template<typename...>
        alias Mold = RESULT;
    };
    
    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
    alias Glow
    {
        template<typename...>
        alias Mold = RESULT;
    };
    
    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
    alias Dawn
    {
        template<typename...>
        alias Mold = RESULT;
    };
};
```

## Examples

We will flip `Operation` and its member `Mold`.

```C++
/**** Operation ****/
template<typename...>
struct Operation
{
    template<typename...>
    struct ProtoMold {};

    template<typename...Args>
    using Mold = ProtoMold<Args...>;
};

/**** SupposedResult *****/
using SupposedResult = Operation<void>
::Mold<int, int*>;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Flip<Operation>
::Mold<Args...>;

/**** Result ****/
using Result = Metafunction<int, int*>::Mold<void>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

Although there are many cases to consider, the implementation for each case is straightforward.
We will implement the one where the function flips the operation and its member `Mold`.

```C++
template<template<typename...> class Operation>
struct Flip
{
    template<typename...Elements>
    struct ProtoMold 
    {
        template<typename...Agreements>
        using Mold = Operation<Agreements...>
        ::template Mold<Elements...>;
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/flip/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/mouldivore/flip.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/flip.test.hpp)
