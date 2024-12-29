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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEARqkAA6oCoRODB7evgHBaRmOAuGRMSzxif7JdpgOWUIETMQEOT5%2BQbaY9sUMjc0EpdFxCUm2TS1teZ0KE4MRwxWj1QCUtqhexMjsHAD0AFSHR8cnp0e7JhoAggdHANQAkiwp9GyCTL13xxfXt2f/Zx%2BV0uVwImGeBjBJkCbjBEI%2BmGhbiYXiIADoMdDsHdkAYFAo7gB5FIJD5ZLEg2bELwOO4AMVoeBSIJMAHYrNc7ly7nCXgikQQAJ4k5hsDFo7CvRgEBQUzncqk0gh3ZTEVBEACynnQdxB3N17L1%2Bu5vMhiJhKPRGKuwGImHB0tlgWwRuNdy8GSMKqYwEwusCABEiSTiGSBEibXaHYIFOK5Vc3VyQCBTQi7lraOgkZLozK487oRyE9y2QHCyz5VzU1CYUKRaxMOKc28ZfH9R6IsB09r/UHVerUBmszDm478y7AkXS%2BXriC/gCTkD53dsKpWC8/d85wvARXgWZAhFcV4sP63GgGNsUq2C7Pfsdg6TPlvrtXzcjUahx5SCNTacSn3JWdDUrHlwT5GtYWFRgG2/UDFVpftNR7NkrFZMtJz3fU3wFaDRUba1iGAJ0XVAjsvSHXsVTVZDMwjIjY0xAtMOAjCp3ve4hC8FJCkwdAACVMAULxaGVF8rnIrsuJ49I%2BME4TRKogDQ16JENHjZMhyRCICFIO4dP2CkWOBDjDnTTAmioLxL2fc4QRw2s8NgwjiPjSTzMs6z6gEKiGSZJFlLDBgNJALSYSuBjv2M7d7nkkSxLs653LixToSDDULKYKybPJGEdL0gysWTZQfXfdTmPYm4HwAFSEhLDiBWYyWQAB9Jh8QSAgIFmdBkwUBs2qdNwUt0u5pN4gShPirEVkLDg1loTh/F4PwOC0UhUE4NxrGsO4FA2LY/XMQIeFIAhNHmtYAGsAkkNENAADjMMwAE4Xq4aoHoerhWVZaRFo4SReBYCQNGSVb1s2jheAUEBknOtb5tIOBYBgRAQA2AgUlRchKDQZ46ASKIG04VQHoANgAWnJyQ7mAZBkDuKQ0TMXg%2BMIEg8F6rgZEEEQxHYKRefkJQ1Au0hdB5gB3UMUk4HgFqWlbxahwlUWx5VUCoO4yapmm6YZpm7rMO4IA8An6GIXUDy4FZeARrQ1ggJB8ZSQmyAoCBXfdkBgCkMw%2BDoMFiFhiBYnF2IImaQV5d4SPmGIQVCVibQ6gR078ZbQkGFoGPEdILBYi8YBkVoWhYe4XgsBYQxgHEfP8DteoADchPFzBVDqVEdlOnTunFxlYlDROPCwcXfzwEHK9IVviFiWSA3BWvGSMC61ioAxiIANTwTApYA1bTv4PnRHEIXj5FlR1HzyX9FrlAdssfQ8FiWHIDWVBryyCvKZ6tLTEsNYMwkNZ7EC5m3d%2BXQehZBcAwdwnh2h6DCAscolQ9CFEyAIKYfgeYYN6EMVBowea1G8n0OY2C9AkN6P0FoBCRiJGIeQhBeRGEDDoUsBhax9qbG2BIRWHBlqkAhrwKGOsKbU1pvTRmzMTYQFwBzK2x1bb2zXmsBAmAmBYESBAa6IBJCBDRC9QIf0NCSDMJIcmYN/DkxevoTgQNSAgxOmicmXByYPRet9cm/hJAfSMeTIRKtOAwzhmdNeyM0bOwxurHGntvaW2JmwTgzQWDN1ZJTJgOIDBei4C9NEXB7ps3wEQMB3Nhb8zPtIC%2Bigr7i10AHGWTA5aV34YI4RG1OBqyxqiO4WsxF61priWuTM8kFI0Kbc2btLbW0CGYO2YTEZOxdqgC2CRcZexWVM0YQyjC5K4MkGgokEih3DvneO0dY6kHOYnZOqcHCXMztKbOudxaF2LqXculzq7Lx2OtRuac8CtwrutDuXcwSXL7gDdag9h6ClHr8%2B2YCp6nVnvPJQi8a5GBXqARZfBN4KB3nvA%2BlyL4VMFlU2QNSxY3xAAHbJxhH42EHm/HRG0v4CB/n/QMACrCWGASI0B4CWVcO6AC5wEBXAUJ5sgso9D0HpEwdkZhODUgKvwSguVxDRWkJoa0ZVlDtXULmOwtBrDJj6rNfMWVHC%2BHrB4YLVpyt86iN1hIrJwzcn5PuqbeRJSZnKIWY7NRGitGUH4Q4pxeTTGsn8C9X6gQzEWN8YE51wTbChIdkjFG6NMYa3WfEomJMOApP1iwBQzdGbN09WaWYRSFFcz0KS0%2B5LhZUuvutXQwRGnNIVnYgRTrIadJiZrbWqhS3lsrdWhEswJmbPdjMwI8zM1LJQHOy2%2Ba12jArTxFqVaXotRrQQFqY6qlB2OZQU561rl51Ote25acHkrKzjnPOfzMBFxLmIT509vlYoRQXPATdHBAvbp3ZA3cIWCH7vnGF0d4XjyRZc1FC8l5Ys7OEjePoCW733iKElsgyUSApYINtdSQDBHpQ/QBT9mXwA/uyhgFddg9So7yiw/KNqCqwMKqBYq/ASrgVKkIcCTVENVUULIQm8FZFEww3jOqmG5BVVQhoxqNU2stUJpqtD1Omq4QdXhts%2B1tKCRwHW46K13D3WiQ9PrikkH9Uu1RpB1GaNGKygGEbaV5MCIEfw1RfFg186ydxKbB3Q3TfDZzN1JD%2BEMT9VkYMHqSHelwJ6ZgAkA0CAOkRabl38NZmF3LEX8sz2OTAyQQA%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/flip/implementation.hpp)
- [Source code](../../../../conceptrodon/pagelivore/flip.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/flip.test.hpp)
