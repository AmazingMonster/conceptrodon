<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::FoldRightLast`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-fold-right-last">To Index</a></p>

## Description

`Pagelivore::FoldRightLast` accepts an operation and returns a function.
When invoked, the function right-folds its argument list using the operation with the last argument as the initiator.

<pre><code>   Oper
-> Init, Arg<sub>0</sub>, Arg<sub>1</sub>..., Arg<sub>n</sub>
-> Oper&lt;Arg<sub>0</sub>,
        &vellip;
   Oper&lt;Arg<sub>n-1</sub>,
   Oper&lt;Arg<sub>n</sub>,
       Init
   &gt;::value
   &gt;::value
        &vellip;
   &gt;::value</code></pre>

## Type Signature

```Haskell
FoldRightLast
 :: template<auto...> class...
 -> auto...
 -> auto
```

## Structure

```C++
template<template<auto...> class>
struct FoldRightLast
{
    template<auto...>
    alias Page
    {
        static constexpr auto value
        {RESULT};
    };
    
    template<auto...>
    static constexpr auto Page_v
    {RESULT};
};
```

## Examples

We will right-fold 1, 3, 4 and 3 using a subtraction.
The process can be described as follows:

```C++
   1-(3-(4-3))
-> 1-(3-1)
-> 1-2
-> -1
```

```C++
/**** Subtract ****/
template<auto A, auto B>
struct Subtract
{
    static constexpr auto value
    { A - B };
};

/**** Metafunction ****/
template<auto...Args>
using Metafunction 
= FoldRightLast<Subtract>
::Page<Args...>;

/**** Test ****/
static_assert(Metafunction<1, 3, 4, 3>::value == -1);
```

## Implementation

We will implement `FoldRightLast` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  1. Right-fold several parameters;
  2. Use the result as the initiator and perform recursion to fold the rest.

Here's a simplified version of it:

```C++
template<template<auto...> class Operation>
struct FoldRightLast
{
    template<auto...Variables >
    struct ProtoPage {};

    // Base Case:

    // Fold once.
    template<auto Variable, auto Initiator>
    struct ProtoPage<Variable, Initiator>
    {
        static constexpr auto value
        { Operation<Variable, Initiator>::value };
    };

    // Fold twice.
    template<auto First, auto Second, auto Initiator>
    struct ProtoPage<First, Second, Initiator>
    {
        static constexpr auto value 
        { 
            Operation<First,
            Operation<Second,
                Initiator
            >::value
            >::value
        };
    };

    // Recursive Case:

    // Write out the last two folds, handle the first two parameters,
    // and recurse using the rest to obtain the initiator.
    template<auto First, auto Second, auto...Others>
    struct ProtoPage<First, Second, Others...>
    {
        static constexpr auto value
        {
            Operation<First,
            Operation<Second,
                FoldRightLast<Operation>
                ::template ProtoPage<Others...>
                ::value
            >::value
            >::value
        };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKzSrgAyeAyYAHI%2BAEaYxCAA7AmkAA6oCoRODB7evgHSaRmOAqHhUSyx8Um2mPbFDEIETMQEOT5%2BgTV1WY3NBKWRMXGJyQpNLW15nWN9A%2BWVIwCUtqhexMjsHAD0AFR7%2BweHR/tbJhoAgrv7ANQAkiwp9GyCTPXXB6cXV8c/x5/nZ3OBEwDwMwJMAGY3MDQa9MJC3EwvEQAHRoyHYa7IAwKBTXADyKTiryyGMBY2IXgc1wAYp50AAlPDABD9JhjQEmBJWC7XPnXGGPOEIpGotEANWaeCY0XoeLJvP5FKpBGuymIqCIyiYwEw1y5VgSABFITyAYq%2BVsttcLOy9YilCBORbrlbafTrgINijAfyBSCheCoaLUNdJcRpbLMKRriG7gxMq8SArzn7ldT1ZrUNrdQjw5H6DHbgnHEniCm/QbfX6lU1HMgsQIxphVCliLHkaGAG5iLzwl2V7kEonEEkCPNSmWF%2BOJojliHYEAgHvePVck0Qs2Djdm6uW6102joAUAdzw3r3/thQcRndpeGIYxjcaEmDQDHQz7vxdnyYXl/TVVMy1HV4ShGkHyfa5X3fT8Z1LOcK35KsB1rEkG3fZtW3bOMVz7fVUL5A0CNTGsyMJYl6gRCDHwIUhLzIvkKNHKioRggRPwYxi/R/BDk0ImsMSXPD%2B1I7iiIXYTe1E7j11NS85M3Z0xNda0GTfNYMi7e07SdC5LzdAB1CNgU9ZEBQQPUcVVAgT1DfgjwUGMEEMdB6AsvUaFo09QxSZpWEwYFH3ol03Vc65iA0x89S8DIjA8iLMDGAVQ1QaImjCBKwl/YgfRdQUwTA28iHvWivxK9iP3K1A0RRfECEsx8kL5QC1Q1EDc3AyC6Ogt8OJjerGoUWrmv1bkuJautz0bBgsLbDsSpEiaxq3cSmJHMcGGo7qQpU7jmM2hFKs4gTuMPRlmVZYJ2QIBEDtY7Blu4pcCrhNqsxzIrBriYb0X/U7GKk1cnuQyTl2kkGJMXcHgYExTVqI415P0/KA0KkVO1q85gEikFGAIBRRtisJgDVUD9QhI13o6orsdx54CZG/8lP0pGWfNS5fh%2Bf5vh2a5sFUVhHj1D5AV5rmTmU3noK8dLR2pUWLlem843OaqbRTVqhFlgh5du1mEeuGZ6xmuacLvJaXWI1MAFobTGndOTZ3cvgOa4AFlAqYKgvAYBwsneSWlbR4Vg0xtFzmIYBCf%2B85ifiz2mh9v23k5Sn3SPJkWTZDk2J1vWUyXT6EUj6Omce9mxbdgAVJLVUV85jfPAB9dklBaCBE%2B933/fHKEuBjCEY2ka4ISEmH8MhDcqZtrhFlNDhlloTh/F4PwOC0UhUE4NxrGsI3VnWNczAhHhSAITRF%2BWABrfIUQ0AAOMwzAAThfrh/Efh%2BuCSaRl44SQvAWASA0BoUg69N7bw4LwBQIAwEXw3ovUgcBYAwEQCAVYBAUjInIJQNADw6BxAiAFTgqgH4ADYbbkMkNcYAyAGxSBRGYXgmB8BzjwOgPQ/BBAiDEOwKQMhBCKBUOoRBpBdADxPKOFInAeBLxXmvS%2BW9OD4mRNg1UqAqDXDIZQ6htD6HXEYWYa4EAPAEPoO2cwp9Fi8AQVoZYEAkD4JSIQsgFAIDONcSAYAUgzB8DoEFWBEBohKOiGEZoABPWRvAwnMGIBE/E0RtBvgQWffBDN8QMFoFEsRWBoheGAIiWgtBYHcF4FgFghhgDiFyQ%2BFJeBtKlM3i2DSwJonkEELUJRtA8DRFHPEjwWAlG6zwMAsppBtLEGiOkTARoQRVJ6UYS%2BywqAGGjuKPAmATwUXXmfbhwhRDiAEfs4RaglESP0FUlAe9LD6F6bAyAyxUApHqKUm2Yx0BT1MJYawZhIGTIjFgB5EBlh2Hqc4CArhJh%2BAHiEMIgwKjDAHoUTIAhoV6BRfUOYQx4gDzBb3Bo4xWieHaHofF9RegtGxYi3FtgiXorxUS6lCw54rDWBsCQ8iOCr3AUoqB2iKFUJoXQhhkgmEmNwIQEg%2BoT5z1scs5YlkmBYHiCC0gt9JAQhRC/CECRJAaEkGYSQ5DQH%2BHIS/fQnBAGkGAafFE5CuDkIfi/b%2B5DAgfx1eQ3lYioEwLgefZZyC0GOIwWonB7jPEWOIWwTgzQWBdgSDbJgWIDDxS4C/FEXB74sLYSQDhXDZC8KOdIE5SgzliN0H4qRTAZFlK5TyiBvAoGqKweZTRArdE0OxFUwxGas0aBMWYlxFiZUQjMDYgNiCHFONQOYuIuCPGzuHcMbtRh01cDATQWggTKAhLEbEyJ7SD3xMSckhw7T0n40ydkpReSClFJKe0ipCzNib3wJFf2jSlEtOQMiTYZ8wjAn/pvHpfTImDNfbYiMYyz6TOmUoOZlSjCLNAFOvgayFAbK2Ts9p%2Byi38JLbIU5ojN6VsuUs75VhbmgeBU8l5WQ3kfK%2BTciwfym0Ao4UleAoLajgr8JCj8DLSBwrKDijF6RUXZBJXkZFEmsXwvmEirofHKXEtyDC5TBLVPMqUzMCY0mNN6f6ApsTrKFCHw5ay/%2BDa%2BWcA7UKlNPb02ZvvhK3NljZUTrsVfUgSqVWUC5da21GaDUJH8C/JIEJDXGskAPRtyjoG2H9d5hxwakCYPUQuyNRCSEcDjXolgCguwNi7M5wqYwc1SsBQWnhhyCOCPkGWkjOgQBD2rbWuRlruWKJ9SosNGitGqAK0VkrZW4TJVMUu1xo6IRecDSG7Lbi8FTYscuZAKQUjN1Ky/Zu5WCDNyGyWgJP1d2hPCfEo952ElJJSRe2dGSsk5LfZgfJhSxCPvGc%2B5DkHSDvvqV%2BsRP6/3tMA10sRoH%2BkRIg8M6D7S4MzMQwskmgbVk6kw5s7ZRJdm8Dw3ViQhGhFNfOa18jxgWN3OiLRre9GmycC2B865PzLBsa3hxoF3HNP1BcIJgzegRMIpZakOTWQhOYqyDp2l5Kej0t53i3jWmmUmZpWSmX6mVezCVyy0FFn%2BH1p65Auzh3riFeK9cbbKI9tuaq6OuVk77GKswMq4Yar/5BZAK/FEEIIT%2BE/rF0BXuEhOu9QbxLsD4EKvVSASQ/htU/wSKAh%2Bkh35cCfmYL1/8IT66bZweVU6uXMOD9nxLKXliTIyM4SQQA%3D)

## Links

- [source code](../../../../conceptrodon/pagelivore/fold_right_last.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/fold_right_last.test.hpp)
