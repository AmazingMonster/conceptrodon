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
template<auto...>
struct Operation
{
    template<typename...>
    struct ProtoMold {};

    template<typename...Args>
    using Mold = ProtoMold<Args...>;
};

using SupposedResult = Operation<0>
::Mold<int, int*>;

template<typename...Args>
using Metafunction = Flip<Operation>
::Mold<Args...>;

using Result = Metafunction<int, int*>::Page<0>;

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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxBLSAA6oCoRODB7evnrJqY4CoeFRLLHxXLaY9vkMQgRMxASZPn6BdpgO6bX1BIWRMXEJtnUNTdnlCsM9YX0lA1wAlLaoXsTI7BwEmCyJBpsm/m6b27uY%2B25MXkQAdDf72ADUyAYKCvcA8olxTNV3JhoAghNiF4HPcAGK0PCJP7/EwAdisAPuyPuRx231OBwIAE9Psw2Dcrth6GxBApfkiUUCQQR7spiKgiABZTzoe4wlHshEczkotEnM4Xa43f7AYiYLaMAjk/zYHm8%2B5eVJGOlMYCYdn%2BAAi70%2BxG%2B6TOovFkrJhIp/wVyJAIH5GPuLNo6DOxNN0vNsv2iMtKPhWq9MPlqK26L2WNxjFYmEJrtJ0otnKVYWADtZmp19MZqEdzoOsalCg9cv83r9AYBMIA9AAqWt1%2BsNytV%2Bv3AAqmAmr3rTYBNYb/brPdhFbM/jCTy8WE1bjQDDWiXjnorALtYfOl1QRZh1NBHy%2BPwr3MpyNXmMOEfx0duS59yJ3tMzzLT8KscP9JcDx%2BDxwxZxxeKjQl/mIYAZTlL8kxVHN0zpBknydI0QMLa9i1LN9y2Hf5IJTIQvESXJMHQAAlDsvFoWl9h1Pd9R%2BA4NAtG0czOMICFIe4WOrX4P2Xf5Tz/C9AJFJCLWwh1MDqKgvDnaoYIhKEzmog0BAYkAmIOYDQK3bjMNEkiFDIijtTEiSpI6ZSDhYtiOLuG1lDVM96M9bTtzqRxkAAfSYF44gICAJnQG0FCjTyZTcPSDLY3D8JSQjwvIu55i9DhFloTgAFZeD8DgtFIVBODcaxrHuBRllWDVzH8HhSAITRksWABrEA0skK4NEkLg4X8DQ0o0MwADY%2BrMAAOIb9E4SReBYCQNA0UgspyvKOF4BQQFmmrsuS0g4FgGBEBAZYCESS5yEoNBtjoOIIijThVCGvqAFo%2Bske5gGQZB7ikK4zF4QjCBIPAAvKfhBBEMR2CkGRBEUFR1A20hdHKAB3fVEk4HgUvSzLatyzg3kuI7aVQKh7luh6npet6Ppasx7ggDxzvoYh2VHBZeHWrRFggJAzsSC6yAoCAeb5kBgCkMw%2BDoTZiBWiBomx6IwnqbE0d4BXmGIbE3mibR2nWqqzrjN4GFoZW4awaIvGAc5aFoFbuF4LAWEMYBxDNvBxQ6AA3DtscwVR2kudYqpYypschaJ9Q1jwsGxghiDwKb7dIb3iGiGKtS2Z3ISMWrFioAxQIANTwTBEb3LKquB4RRHECGq%2BhtRsYR/RnZQQrLH0PBohWyBFlQBd0jt%2B7/Mo0xLGsMwFpT%2BOsB7iBFjaMy/AgVxRj8coQmmYpShyFI0gENfd7ydJem3uYKiqTpJkP8ZKl1q/ulP/oyiGbob9fhon9mMoF9KtYJAxhwDKc1saLRJndR6z1XrvU%2BjTCAuA/pMwqqzaqudFgIEwEwLA8R56kEapIfwVwACc/g4SSDamYSQfUZppT6kQsaHAJqkCmpVK4fUuB9SGkQoaHDmpcDSiQvqIC4aLWWqtVBG1Oa7S5vtfGx0BZC0ZldNgnB6gsE9nCe6TBHgGBVFwIhVwuCtR%2BvgIgM89BV1BrXaQ9clCNzhrocWyMmCo3toA4B81eCLTxodS49wib3DURorROjnYfQMUYjQtN6a80ZszfwZh5hs1zltbmqAGZxBOoLdJsSBhBM0U8Z2%2BiuCzRoOROIMs5ZwzVkrFWpAakay1jrBwdSDZSiNibbG5tLbW1tnUx2Wd1g5XwB7Rw3s7Y5T9gHTYdSQ6pThuHSO2Jo5DLZvHROVUU5pyUBnJ2Rhs6gEkXwAuChi6l3LnUyxNdwY2NkA3WGOVHEtxzmPKwHdw5zz7gPAQQ8R7aleRPKecQZ4%2B17hfe%2BzgV4MHcJ4ZoehN5FGfkffeGRYVjFILkFFX8d630vgILoIw0Xr3BUvAlUxEXfz0BMN%2BRKqWTGxXMX%2BKx/4LAYR40BnBAnEHUZo7RhS9ERNarTBBZj4koPZnVUgGCsEDFwfMphLCDFtThAIuEnVJCUKeuUTxOMlq2HERKqR8AZEHQJlkxRl1rocDUeTFgChPbvU9voq4JwJgmMQQDCxsgrE3MhvIOxDydABFIM41x6M2VYxEbjORhNiY2uenah19wnUGNdbSOmOS%2BbxP8EkiRHNUkoEzYzc1RaBgOvwu5FN7k02eW5U9CW5TpaUCqTlBppsqptqabrVp6TDbG1NsMzAFsrZiD6UnAZ%2BzVmkBGffcZvt/bIEDrMwQocFldyWSs2O6y6lbPTpnfZyYUn5zVKckuZc8SXO9dcwYtiYZN2Dbo4w7cbAfPgF86odtKz%2BTbuPSwk8vHTwBqC3Bi9qguGhe/BFMwcUYr3tUd%2BmLqgMpfqBh%2BhKsjEtQ/i%2BlW8kXjGvrS/Dj9cOUtZSVZl4N3GRoWpy%2BN9xE2OudWm4VpiSBitzYa9BmDsGUEAQqkAZgDH%2BH8GlHq7UZrCbhJw4RNG9UrTWmgvBIBJBpWIWlIa/UiGSCIZ1UhXBAjzP8NRrxnBkmSMAd9GTJm9WceThU9IymgA%3D)

## Links

- [source code](../../../../conceptrodon/pagelivore/flip.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/flip.test.hpp)
