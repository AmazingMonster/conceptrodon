<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::FoldLeft`

## Description

`Typelivore::FoldLeft` accepts a list of elements.
It produces a function that accepts an initiator and whose first layer accepts an operation.
The function left-folds the list using the operation and the initiator.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>..., E<sub>n</sub>
-> Initiator
-> Operation
-> Operation&lt;...
   Operation&lt;
   Operation&lt;
       Initiator, E<sub>0</sub>
   &gt;, E<sub>1</sub>
   &gt;
   ..., E<sub>n</sub>&gt;</code></pre>

## Type Signature

```Haskell
FoldLeft ::   typename...
           -> typename...
           -> template<template<typename...> class...>
```

## Structure

```C++
template<typename...>
struct FoldLeft
{
    template<typename>
    alias Mold
    {
        template<template<typename...> class>
        alias Road = RESULT;
        
        template<template<typename...> class>
        using UniRoad = RESULT;
    };
};
```

## Examples

We will left-fold 2, 3, 4 and 3 using subtraction.
The process can be described as follows:

```C++
   ((1-3)-4)-3
-> (-2-4)-3
-> (-6)-3
-> -9
```

```C++
template<typename A, typename B>
struct Subtract
{
    using type
    = std::integral_constant<int, A::value-B::value>;
};

template<typename...Args>
using Subtract_t = Subtract<Args...>::type;

template<typename...Args>
using Metafunction 
= FoldLeft<
    std::integral_constant<int, 3>,
    std::integral_constant<int, 4>,
    std::integral_constant<int, 3>
  >::Mold<Args...>;

using SupposedResult
= std::integral_constant<int, -9>;

using Result = Metafunction<std::integral_constant<int, 1>>
::Road<Subtract_t>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will implement `FoldLeft` using recursion over the number of parameters.

- **Base Case:** Handles several numbers directly.
- **Recursive Case:**
  1. Left-fold several parameters;
  2. Use the result as the initiator and perform recursion to fold the rest.

Here's a simplified version of it:

```C++
template<typename...Elements>
struct FoldLeft {};

// Base Case:

// Fold once.
template<typename Element>
struct FoldLeft<Element>
{
    template<typename Initiator>
    struct ProtoMold
    {
        template<template<typename...> class Operation>
        struct Detail
        {
            using type 
            = Operation<Initiator, Element>;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

// Fold twice.
template<typename First, typename Second>
struct FoldLeft<First, Second>
{
    template<typename Initiator>
    struct ProtoMold
    {
        template<template<typename...> class Operation>
        struct Detail
        {
            using type 
            = Operation<
              Operation<
                Initiator, First
              >, Second
              >;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

// Recursive Case:

// Fold twice, handle the first two parameters,
// and recurse using the rest.
template<typename First, typename Second, typename...Others>
struct FoldLeft<First, Second, Others...>
{
    template<typename Initiator>
    struct ProtoMold
    {
        template<template<typename...> class Operation>
        struct Detail
        {
            using type 
            = FoldLeft<Others...>
            ::template Mold<
                Operation<
                Operation<
                    Initiator, First
                >, Second
                >
            >::template Road<Operation>;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEEhoAHKQADqgKhE4MHt6%2BehlZjgLhkTEs8YnJ0naYDjlCBEzEBHk%2BfkG2mPYlDE0tBGXRcQlJqQrNre0FXLZTQxEjlWM1AJS2qF7EyOwcBJgsaQYHJoFuBACeaYysmAB0j9j0bIIKZ9gmGgCCk8ReDgA1AAxTzoUKYKgEQEmADsVlhABEzlYfl9vgcjidMGcLtdbmxAc9DowCB90X8AdDQbRwZCyedia8GZ80fD0YDOYDMccmKdzlcbsxCQBJBjZPkkck/LmAylA5TEVBEACyYI5XLhqO%2BstlPOxuP1fJxAvxwoejw%2BgOQBgUCkBAHkbsQ%2BTlpTrdZz5dDEZhmnQNZ6tYHPVyvFkjNz8TCZaHZWdEY7na6BLixRKiGQiS9SeTAtq43Dkfn0SG9YdefyLhWDaahXdHvcrTamHbG99gMRMCS3u64%2BGIsBAQAlVBMdAwwKJ33%2B2i4jtdnsEBSNj4gECCk0FzVIlGl2Oco1Vzfm9ud7vM96BVkezkDyNq2mTxOK5WoR/oefnpcry3XvdssW2rokeJp4vWhLAngxCTKQUYQZggJCPUAifv%2BPzeiCYIQlCuJQTBBBwchaAMGhN7Bge3I1sahpmncgLpo4krEH2XKYa%2BqrqpRFG3rqoGGtRx50Wwq7Xtatr2k6CQpgwrGephM5MAGlHxuyKmhveQ6bjGvGFlOSbSX0uJlnGBkukZ5wmaZDHikxmZwfhkxWaGHxEShpHOUG/4lupnJFgB3zOfxAqCWBJ4Nn%2B2Dia2v73AuF6kleN79hGQ6juOz6AopAbnPFP6idg66bgFqlAfuvHBeBBIWnF36XnJgKaYCH6ZRx77qrldWJQVAX%2BT5gU/JV4WQdBsHwdVSHuegcHDTVDoEAgCRJRSBD/ECNJ0rh5yOYRk0kdNjoLUtPVstuh6hbRCE2RmUrobx7FKpxtIhjxcZDRddbVQV0V2mZMkNbKCl%2Bkpc6%2BTCam6RpqXjTp1l%2BfpG04QybjzYtMEnZDnpFaFzUdW4nmhlJ5lupZYNxkT/2k5jcOcoxeDMQ5o1kmTLnXm5%2B0E15yVw2uG44%2BlaEo8mFmfP1ha7v1QUfdWWI0Z9p6RT9sV5fVd0pYOI5jhOCZZcDOVuCr3WRUV%2BIlTuZVopRQ3CTVhu9mrYbQy1OttR%2BX6LpePWSxLwE/AA9AAVEHwch376KB0HAAq2BCJHwdh/7IdJwHCcDYFZiBBENpeFgk5uCRuxpMu7ogdLs2At8M024CVh3ZhQheLEq1MA4pYQ7KTXFdx%2BmTOg64RAcnZiAA%2BiRkyGMjA9wd864AG5iF4mAALQWHPC8mqLwE%2B%2BV1sIe2xDAMtPxNQ3Tcug4w/Qjrp/N63uUH7FvPFZLg1lzb%2B%2BH%2B6TUqsDVBeAwDQBA6R1ojekxlKK937oITAQ9aCjwEOPQQuIp6AkCK5EMkCQADxgS6OBY9mhIPOCgyQ6CIEED7lg6BsD4EMEQZPQQcE0EO15m7e%2Bh8va%2B2%2BCfLwaQiiYHQMOTACgvC0GZoFHu5CoGD1wTQuhyCGGAiXgATjzJwpqgjhGiMyj/Zof8AEWTcJg7B1D8ET3kbtLgeYbzrgFriG%2B58CCX1UeVcejhkDDxigkAgEBMEKDuB4q8bgNEiN2g3XhmR%2BHBNER8NYKIOAbFoJwfwvA/AcC0KQVAnB8aWGsHKLYOxELmECDwUgBBNDxI2AAawCJIe4GhJBcFhIEDQ/gNBmAAGztLMMkVIiSOCSF4CwJIGhSCpPSZkjgvAFAgBGWUtJ8TSBwFgDARAIAtgEDSF4QiFAIBoCOHQBIUQ7icFUMkdpS92mSEBMAZAyBARSHuGYXg/DCAkDwH3OY/BBAiDEOwKQMhBCKBUOoeZpBdBzAAO4ujSJwHgCSkkpPKRkzgDotmbOhKgKggJTnnMudc259zalmEBBADw%2Bz6DEBhBnLgaxeBzK0BsCASA9lpAOWQHZLK2UgGAFIMwfA6AHBgpQWISLYgRBaJcWFvAxXMGIJcB0sRtD1DmSUvZzIHQMFoJK0FWBYheGAG4MQtBpncF4FgFghhgDiB1dBZVeBZ5CKRZgVQ9Qtl7BKdgvp6TaB4FiC6OVHgsBItWngIZprSAOuILECJvoLVGB9UYcpGwqAGEPgANTwJgCFUlUklK%2BcIUQ4h/n5qBWoJF4L9CWpQNYaw%2BhfXTMgBsVARccgmqXr3BMpgcmWDMOMyNxB3mOsbd0XoOQXCkRmH4OYYQlgVCqIUTI2QBCToXcUHIww51jDmHUQB/QFgru3T0O1AgBitA3aMRI2792eA6HoceZ7Z0XokBsBQ%2BTdjPv0Ai0ZSKJnYrORcq5Ny7kPOJRAXArzKVFJpXSpNGxFrjjGBAKpIBJCBHuEowIsJJD1LMJIdpGgWntKUZ%2B/pgyQDFPuO0rg7TkhKOSNR/wDT/AYfad%2B0FEypkzNKUmxZKymVrLRVs8glBOUUqOWwTgLQWCz1hEvJg0VIxcCUfcLgdTnn4EzO8vQ%2BaflFukCWpQZbQW6D5VCpgMLTXwo4Mktj4yUWCYxViqTMm5MKaHEplTdSSVktZRSqlgQzC0u4/MxlzLUDkoSMJ3Z4XfNjGc7JlsRglNcBGTQURS1hWivFXKqVpAZUSoVUqhwuW1Wkg1VqpFur9WGtoMa3L5rLXWvSfgLsDQHUmvSc611BxcueqRT6v1ErA17HSSGsNJTI3RqULGxrg4eMpqYOmzN2ahS5Z04Wv5%2BnZClpBekkzlbE1dqsJYOtsQG1IYyS2hBnB23kM7TWntfaEgDqwOdl9R7d3jvcDe2YIRSLnpWJe9Ii6%2BgHuB2u0oj7Ad3o%2B30U9bQftTpHcevdgwAfzqvYMMH97FjlCfTSzY2x30E76TZsZvBf3xdc4l9zynVMaBJeBzM/noPBYZXBzACHEgXb6QM0gQzAjKfqbCZjsImmSFw5cuY5PkWTNsFx%2BlCylmrPWeiqLonDnHI4FJvFLAFCzzubPDz2JJjqYg1pz5shdObYBfIQzu2dDkdIGZizcKSNk5/fZjZWzASYsBDrq5euDeAiN8pk30JSUxbZf5wIQXFehZQFHil6uk9jAN7w4eofh7h48cQFglz%2BXpaFRAEVoL8s5fDeX%2BVirlUlfC%2BqzV2rmuYD1Qao1JqSkNfjSNs1tq2uOtBV15AbrevQK9bwAb/rLjDeDQO8bvBJsxsOLNxNIW%2BCpoUBmrNOa1tW42xILbgL7flqdwYQ7D2bADbe5dvoJq/aQKO9YXtFP%2B2DuvzuvoX2wczrx9DuYRQl1chEdV1AD0ct1kdd14dsdYdGgFgwCgccdsc4CocMcX030/krMPd2NOB/c89dd9dDdjdjRJhGcNMSAWc49YNSB4MsBucrM%2BchkzBlNAhAh/BWkGkCMWDYQaNbMKdOBONZkqDqlJB/B0N/BkgOklFJAlEmlMMuBgg%2BlAhEVsC5d48rMnleDZcYMQsNhI0shnBJAgA)

## Links

- [source code](../../../../conceptrodon/typelivore/fold_left.hpp)
- [unit test](../../../../tests/unit/typelivore/fold_left.test.hpp)
