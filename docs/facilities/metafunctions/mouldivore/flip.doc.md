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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEARqkAA6oCoRODB7evgHBaRmOAuGRMSzxif7JdpgOWUIETMQEOT5%2BQbaY9sUMjc0EpdFxCUm2TS1teZ0KE4MRwxWj1QCUtqhexMjsHAD0AFSHR8cnp0e7JhoAggdHANQAkiwp9GyCTL13xxfXt2f/Zx%2BV0uVwImGeBjBJkCbjBEI%2BmGhsIAnilGKxMAA6bHQ7B3ZAGBQKO4AeTRxA%2BWVxINmxC8DjuADFaHgUiCTAB2KzXO68u5wl4IpEEVHotjYzHYV6MAgKak8vm0%2BkEO7KYioIgAWU86DuIL5eq5%2BoNfIFkMRMJFaOY4uxV2AxEw4JlcsC2GNJruXgyRju2touuhABFSeTKQIkfbHc7BAoJfKrp7eSAQGaEX6dUipTHZfG3dDuYm%2BZygwX2QreWmoZbRTasdjs29ZQmDd6IsAMwG9YEQ2qNah/egs9LY3n3YFCyWy9cQX8AScgXO7thVKwXpgvudZ/PAeXgWZAhECV4sN23GgGNsUs38zPfsdQwlwwxN4cgVWLSjrRixzSCHSGTJJ9enZI0K35cFBWrL8xXrTEW0Vf9lVVdUtR1Q0rA5UsJz3A0P2FWsfztYhgFdd1wLbX1B27XtUIHTMYSuEi4xxfMcJnLDp2Be97iELwUkKTB0AAJUwBQvFoFUFxBSiOz4gT0iE0TxMkmjHwpECYQAN1QPAh1vK4U0HJEIgIUg7lM/ZqXY7ibgfTVMCaKgvEvT5vhBfCa2/W1MSY0iE1kv1HKYZzXKyNTmVZJEgI0qkDKMhi3D8lj4LYyceMOO5lIkqSt2uQLstU4Mgqclz6gjGFTPMyzcQSgMkR0vTrPSuz7gAFTE3K3z/SlkAAfSYIkEgICBZnQFMFAxAbXTcQqzLueTBJEsSctxFYCw4NZaE4fxeD8DgtFIVBODcaxrDuBQNi2DdzECHhSAITRNrWABrAJJExDQAA4zDMABOP6uGqL6vq4DkOWkbaOEkXgWAkDRkn2w7jo4XgFBAZJHoOzbSDgWAYEQEANgIFIvDMigIDQZ46ASKIMU4VQvoANgAWiZyQ7mAZBkDuKRMTMXghMIEg9L0fhBBEMR2CkGRBEUFR1Gx0hdC4UgAHcKRSTgeC2na9qeo7OBJMnSZVVAqDuRnWfZznud5j6zDuCAPGp%2BhiD1A8uBWXgsa0NYICQKmUhpsgKaDkOQGAKQzD4OgwWIdGIFiA3YgiZpkW13hU%2BYYhkRJWJtDqLH7qppsSQYWgM6VrBYi8YA3DEWh0e4XgsBYQxgHEau8EdeotLEg3MFUOoyZ2e7TO6A2WViClc48LADf/PA4Zb0h%2B%2BIWJFKDcEO5ZIwnrWKgDFIgA1PBMDVoD9vu8XhFEcQZdv%2BW1ANlX9A7lAzssfQ8FidHIDWKga8WRm4szGsGUwlhrBmGRuvYgekB4AK6D0LILgGDuE8O0PQYQFjlEqHoQomQBBTD8KrQhvQhh4NGKrWo5U%2BhzBIXoWhvR%2BgtEoSMRINCGGYLyFwgY7ClicLWJdTY2wJC6w4LtUgSNeAo0tszNmHMuY8z5o7CAuBhbu1ul7H2B81gIEwEwLAiQICvRAJIQImI/qBAhhoSQZhJBMwRv4Jmf19CcBhqQOGd1MRMy4EzL6f1QZM38JIIG1imbSINijNGGMHoH1xgTAORMTZk3IJQcObs6ZsE4M0FgWkOQsyYPiAwvouB/UxFwT6gt8BEHgeNVWt9JYP2kE/JQL8la6BjhrJgWsW4SKkTIw2HBjYkzJncc28jrYcwJB3XmFSqkaCdi7YObsPaBDMN7eJ2N/aB1QK7BI6TKb7NWaMWZRhylcGSDQSSCRE7JyVtndOmdSBPNzvnQuDgXmlxlOXSuBsa51wbrQJuLy267x2IdfAvdHD92bodIeI8wQvInlDQ609Z7InnpCn28CV73XXpvJQ2925GD3qAHZfBj4KDPhfK%2BLymn32lq02Qz9FaHS6e/fekCrDf2nv/UxR1gECFAeAnsPLoGwISPUxBgrmGoIgK4RhqscFlA4QQ9IRDsg8NIakTVFDcHqpod0IuDRuG5F1fKgQrD5hqsEUw81WC%2BFsMNfar26xRHSwGfrJWciraKJKXM8plTPpOw0XU9ZOjtl%2B30YY4xlAJGeO8RUuxHJ/B/XBoEexjiwlRN9ZwWJmMEl40JsTU2RzMm03phwPJNsWAKC0jzLSwbzSzBqZo0WjTZDNOZbLeQ7T2U6BAMEHpfSdbuMkT65GRtUlmwtqoOtDam0toRLMZZJyQ7rMCFs32ONkmVtDhkjdbsQCNoEn1Ztf0%2BqtoIH1BdrS453MoA8w6byq73TfR8ou3z9llwrlXKFmBa710bs3e64KyU4tINC01cLB7D2QKPFFghJ5KwxenbFi88UvMJVvHeZL2wJKPkwU%2B59L7WgZd2plEgWVywHa/YdXLjBfxsPy%2BAgDhUMGbrsMan8oGWBgbIuBCCBXCJNXQtBGCLXYPQQI/BZD9VZGVXqooWQ5PUOQaa61jreGaboTa9TnDxgDGU7Mfhrr5PCKumI91UNBnRM4JbRdja7iXsxDesNtSSCRp3Xo0gBijGjEFVDJNIB/qYkCIEfw1QwkI0ixyAJebp2o1sHE3dKwzGSH8FYsGHIEZfUkIDLgP0zCRKhoEKdsiC3RuehOgWSWqspfS2sdeGRnCSCAA%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/flip/implementation.hpp)
- [Source code](../../../../conceptrodon/mouldivore/flip.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/flip.test.hpp)
