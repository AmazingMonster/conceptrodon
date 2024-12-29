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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCAArGakAA6oCoRODB7evnrJqY4CQSHhLFEx8baY9vkMQgRMxASZPn5cFVXptfUEhWGR0XEJCnUNTdmtQ109xaUDAJS2qF7EyOwcAPQAVFvbO7t722smGgCCm9sA1ACSLIn0bIJM1ec7hydn%2Bx/7r8dHxwSYNwM/xMAGY3P9AY9MKDwQDblCYUwvEQAHRo0HYc7IAwKBRolEYrE4hTnADyiWij3SGN%2BQ2IXgc5wAYrQ8IlfiYAOxWE7nPnnCHw4FgggATwpzDY%2BOwd0YBAUNN5/LpDII52UxFQRAAsp50OdfvyDdzDUb%2BYKgdCRXDLYjkah8YTsUxcfjjsBiJgAXKFSDsKazecvKkjOcAEpMOgGkEAETJFOIVIEMPdnu9gjx6L9AbNIBAFqh511tHQMJl6fljuzIJ5xyNXJjoNrOYLwvB4sYrEw0tlGcVdf5weCwCLeujcY1WtQxdLYPL90rWf9NY5nMbK5Ov3en1232352wqlYt0wzwOW53Xw5m7MIOC2K8WGjbjQDBWiXl/fMd7f3ifMOROhCFFL83h2eNKSeF5flbK1YUhNskVRJciRdTMCWzE4VUZclIOpTcTSVPlYJhMUJS7Kt/SI85sLVScdTHLkrDXJtrwHYibQREUO0lbs0WOYhgF9Kj2KDEMRxncd1U1BiSxTQT0JpDcfhY5SLwuIQvESXJMHQMNMAULxaDVaCTiHUNNO0lJdP0wzjKk3DE2qGEhnQPNgiwVQAH0lAARy8RgVn7PMZxhYICFIc5wo2JTmzAi5tUwOoqC8N8oPPE4SO48ipX4hT%2B3MiSkqYFK0vSKSWTZGFHKTBhgpAUKwQEoTKNYzd4q2cMDKMkyMuOQqurstVQTjRLktShxqTBcLIuijE8wjOgXIINyQA8zBvL8gK3ytZc4tOcCABUDN6rZvgmRxkC8tDogICBXLzBQu2u303FsnrIssnS9O64yMVmNrjg4eZaE4WJeD8DgtFIVBODcaxrBoxZllPb8eFIAhNGB%2BYAGs4kkFENAADjMMwAE4ya4WJiaJrhOU5aRQY4SReBYCQNA0UhIeh2GOF4BQQE5zGoeB0g4FgGBEBARYCESZFyEoNAbjoaJQi7ThVCJgA2ABaLXJHOYBkGQc4pBRMxeF0wgSDwNzWn4QQRDEdgpBkQRFBUdQRdIXRWgAd0TRJOB4EGwYhrGYc4UlkTltVUCoc5Nd1/XDeN02CbMc4IA8ZX6GIA1by4WZeGFrR5ggJAlcSFWyAoCAq5rkBgCkBIaGM6IBYgCII4iYJ6lFYPeF75hiFFUkIm0TAHEH0glYXUkGFoAfvawCIvGANwxFoAXuF4LAWEMYBxBXvBPUmgA3AyI42qfkVWdHwsqCPWQiRNR48LAI4IYg8DZ3fSEvsQCI1kYwAkPqyIwWN5hUAMEJAAangTAftcKQ3Rg7YQohxCu3QR7NQEdfb6EPigBGlh9B4AiALSA8xUAfnSDvHWrkRqmEsNYMwPNAE/ywJQiA8w7BT2qC4Bg7hPDNH8EIqYfQYitFyGkAQowWhJBSLIhgEiSj9HGJUfhHRhiNBEWMNoWiBCdAaKomY4wdHyL0BMExwRehqKkbw5GKwJChw4ODLmEdeaJ21nrA2RsTZm0zhAXA1t85o2LhjKB8wECYCYFgGIPDSB40kCCFEZMQQMw0JIMwkgtYc1iFrMm%2BhOAs1IGzEEXAURay4FrImZNaZa1iJIKm6StYeO9rzfmgtIki3LpLCu0sY7yzrg3POas2CcHqCwc%2BnIdZMFQqGLgZMUSVOhlbIgnC9DoKdlg6QOClB4O9roBIAcmBB13q49x3NeC82jrLZE5x47eOTgbZ0izlmrKzjnauecC4gjMBE0uosBmjOiAreuqBc79Dec3SmnM27/GIJ3bu3th79xnmi0e49J7T3/nPOUC8l4R1XuvTetBt4z33uA1Y0N8Bn0cJfHeazVC33%2BDPR%2BTNoYvzfqKD%2BNKS4/z/ujQBwClCgIPkYCBoBel8FgQoBBSCUEz22Zgl2ezZC4K9tDY5hDIHMKsKQl%2B3DqG0IEPQxhsZ9WsPYdEThV8qEGMms4CArhLGtECLY6Y6jFF5HSG6n1yjTHer4U6moFi9EKJDdUYx3RPWSKseGrIkadFBocQsJYzii7FLceHDpnBnm%2BIWSOJZKzCZZxCRsv5RcS5RNIDEuJ/RElM1KeU5ZWTOSxDJvTEE2TcnNPaTzTgXShZQLFv0pAMtY7gtBcQcZqwpkpxYAoc%2BJtz4lstEMS2%2BANm2y2bIHZaq3byAOVqnQIAQSkFOeckO2armeKjkMuOCdVCLuXau9dUIhhfMhT86IfyQSAtHSCn9Ndp0gbziAFd2kvJrrJl5DdBAvIvr2XQRFyKe591HhizDY8J78JnviwQhLl60swGvDeW8d7oypZK/lpA6VaMZdfFlyA77ssEE/b23L%2B58q/oKmeIqQFgMlcOUdMCmDwMQcgiUyr92qokOq92J78Hnt1cYEhNgjXwBNdUHeawHpWssGwm5HDbb2sSVG9IgjhFJrEegVNOQlHVH9TI6oDmNHtCMYm0RHnDFhsmHG%2BxCauj%2BusbGoo8as0KCcS7S5ubB0cETq%2Bld5xYMogQ%2BW7dJAq2Ad6dE2J8TKCuJbSAcmKIQQgliNTZpHMKuclqQOm5Q7bDdKBbMXGIBJCxDSXTTkHMiaSEplwEmZg2lMxBPFprfMell1cRbRrkdpttfmIA1IzhJBAA)

## Links

- [Example](../../../code/facilities/metafunctions/raillivore/flip/implementation.hpp)
- [Source code](../../../../conceptrodon/raillivore/flip.hpp)
- [Unit test](../../../../tests/unit/metafunctions/raillivore/flip.test.hpp)
