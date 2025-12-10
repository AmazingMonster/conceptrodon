<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::Flip`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-flip">To Index</a></p>

## Description

`Pagelivore::Flip` accepts an operation and flips its *0*th layer and the *1*th layer.

<pre><code>   <i>0</i>th Layer { <i>1</i>st Layer }
-> <i>1</i>st Layer { <i>0</i>th Layer }</code></pre>

## Type Signature

```Haskell
-- flip with Mold
Flip
 :: template<auto...> class... 
 -> typename...
 -> template<auto...>

-- flip with Page
Flip
 :: template<auto...> class... 
 -> auto...
 -> template<auto...>

-- flip with Road
Flip
 :: template<auto...> class... 
 -> template<typename...> class...
 -> template<auto...>

-- flip with Rail
Flip
 :: template<auto...> class... 
 -> template<auto...> class...
 -> template<auto...>

-- flip with Flow
Flip
 :: template<auto...> class... 
 -> template<template<typename...> class...> class...
 -> template<auto...>

-- flip with Sail
Flip
 :: template<auto...> class... 
 -> template<template<auto...> class...> class...
 -> template<auto...>

-- flip with Snow
Flip
 :: template<auto...> class... 
 -> template<template<template<typename...> class...> class...> class...
 -> template<auto...>

-- flip with Hail
Flip
 :: template<auto...> class... 
 -> template<template<template<auto...> class...> class...> class...
 -> template<auto...>

-- flip with Cool
Flip
 :: template<auto...> class... 
 -> template<template<template<template<typename...> class...> class...> class...> class...
 -> template<auto...>

-- flip with Calm
Flip
 :: template<auto...> class... 
 -> template<template<template<template<auto...> class...> class...> class...> class...
 -> template<auto...>

-- flip with Grit
Flip
 :: template<auto...> class... 
 -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
 -> template<auto...>

-- flip with Will
Flip
 :: template<auto...> class... 
 -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
 -> template<auto...>

-- flip with Glow
Flip
 :: template<auto...> class... 
 -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
 -> template<auto...>

-- flip with Dawn
Flip
 :: template<auto...> class... 
 -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
 -> template<auto...>
```

## Structure

```C++
template<template<auto...> class>
struct Flip
{
    template<typename...>
    alias Mold
    {
        template<auto...>
        alias Page = RESULT;
    };

    template<auto...>
    alias Page
    {
        template<auto...>
        alias Page = RESULT;
    };

    template<template<typename...> class...>
    alias Road
    {
        template<auto...>
        alias Page = RESULT;
    };
    
    template<template<auto...> class...>
    alias Rail
    {
        template<auto...>
        alias Page = RESULT;
    };
    
    template<template<template<typename...> class...> class...>
    alias Flow
    {
        template<auto...>
        alias Page = RESULT;
    };
    
    template<template<template<auto...> class...> class...>
    alias Sail
    {
        template<auto...>
        alias Page = RESULT;
    };
    
    template<template<template<template<typename...> class...> class...> class...>
    alias Snow
    {
        template<auto...>
        alias Page = RESULT;
    };
    
    template<template<template<template<auto...> class...> class...> class...>
    alias Hail
    {
        template<auto...>
        alias Page = RESULT;
    };
    
    template<template<template<template<template<typename...> class...> class...> class...> class...>
    alias Cool
    {
        template<auto...>
        alias Page = RESULT;
    };
    
    template<template<template<template<template<auto...> class...> class...> class...> class...>
    alias Calm
    {
        template<auto...>
        alias Page = RESULT;
    };
    
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
    alias Grit
    {
        template<auto...>
        alias Page = RESULT;
    };
    
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
    alias Will
    {
        template<auto...>
        alias Page = RESULT;
    };
    
    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
    alias Glow
    {
        template<auto...>
        alias Page = RESULT;
    };
    
    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
    alias Dawn
    {
        template<auto...>
        alias Page = RESULT;
    };
};
```

## Examples

We will flip `Operation` and its member `Mold`.

```C++
/**** Operation ****/
template<auto...>
struct Operation
{
    template<typename...>
    struct ProtoMold {};

    template<typename...Args>
    using Mold = ProtoMold<Args...>;
};

/**** SupposedResult ****/
using SupposedResult = Operation<0>
::Mold<int, int*>;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Flip<Operation>
::Mold<Args...>;

/**** Result ****/
using Result = Metafunction<int, int*>::Page<0>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

Although there are many cases to consider, the implementation for each case is straightforward.
We will implement the one where the function flips the operation and its member `Mold`.

```C++
template<template<auto...> class Operation>
struct Flip
{
    template<typename...Elements>
    struct ProtoMold 
    {
        template<auto...Agreements>
        using Page = Operation<Agreements...>
        ::template Mold<Elements...>;
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/flip/implementation.hpp)
- [Source code](../../../../conceptrodon/pagelivore/flip.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/flip.test.hpp)
