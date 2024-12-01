<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::BiHarvest`

## Description

`Omennivore::BiHarvest` accepts a list of elements.

Suppose every element has an alias member `type` and a static constexpr data member `value`. In that case, it returns two functions.

- When invoked by a container, the function collects the type results from the elements and instantiates the container with the collection.

<pre><code>   Elements...
-> Operation
-> Operation&lt;Elements::type...&gt;</code></pre>

- When invoked by a sequence, the function collects the value results from the elements and instantiates the sequence with the collection.

<pre><code>   Elements...
-> Operation
-> Operation&lt;Elements::value...&gt;</code></pre>

## Type Signature

```Haskell
-- Collect `type`
BiHarvest
 :: typename...
 -> template<template<typename...> class...>

BiHarvest
-- Collect `value`
 :: typename...
 -> template<template<auto...> class...>
```

## Structure

```C++
template<typename...>
struct BiHarvest
{
    template<template<typename...> class>
    alias Road = RESULT;

    template<template<auto...> class>
    alias Rail = RESULT;
};
```

## Example

- We will collect the type results from `Crop<0>, Crop<1>` to instantiate `Operation_0` and collect the value results from `Crop<0>, Crop<1>` to instantiate `Operation_1`.

```C++
template<int I>
struct Crop
{
    using type = std::integral_constant<int, I>;
    static constexpr int value {I};
};

template<typename...>
struct Operation_0;

template<auto...>
struct Operation_1;

template<template<typename...> class...Args>
using Metafunction_0 = BiHarvest
<
    Crop<0>,
    Crop<1>
>
::Road<Args...>;

template<template<auto...> class...Args>
using Metafunction_1 = BiHarvest
<
    Crop<0>,
    Crop<1>
>
::Rail<Args...>;

using SupposedResult_0 = Operation_0
<
    std::integral_constant<int, 0>,
    std::integral_constant<int, 1>
>;

using SupposedResult_1 = Operation_1<0, 1>;

using Result_0 = Metafunction_0<Operation_0>;
using Result_1 = Metafunction_1<Operation_1>;

static_assert(std::same_as<Result_0, SupposedResult_0>);
static_assert(std::same_as<Result_1, SupposedResult_1>);
```

- Note that the `crops` are not required to have both member `type` and `value`. In the following example, we will collect the type results from `std::type_identity<int>, std::type_identity<int*>` to instantiate `Operation_2`

```C++
template<typename...>
struct Operation_2;

template<template<typename...> class...Args>
using Metafunction_2 = BiHarvest
<
    std::type_identity<int>,
    std::type_identity<int*>
>
::Road<Args...>;

using SupposedResult_2 = Operation_2<int, int*>;

using Result_2 = Metafunction_2<Operation_2>;

static_assert(std::same_as<Result_2, SupposedResult_2>);
```

## Implementation

```C++
template<typename...Crops>
struct BiHarvest
{
    template<template<typename...> class Operation>
    struct Detail
    {
        using type = Operation<typename Crops::type...>; 
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;

    
    template<template<auto...> class Operation>
    struct Hidden
    {
        using type = Operation<Crops::value...>; 
    };

    template<template<auto...> class...Agreements>
    using Rail = Hidden<Agreements...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCAAnADMpAAOqAqETgwe3r56KWmOAkEh4SxRMQDs5baY9gUMQgRMxARZPn5c1bUZDU0ERWGR0XGJCo3NrTkdo739JWUglQCUtqhexMjsHASYLEkG2ybxbgQAnkmMrJgAdDduxKhJCofYJhoAgqPEXg4A1BZ4AAkmgA3TCjV5vEzlKzvH5wn7bXb7TCHY47PZMA5HU7nZhsG5XZ4/ZAGBQKH4AeXOxExGWeEPhP0%2B3wIPwAIphGnQGfCoTC3ozGV40kYEWdMD9DmzKdTaQJUTiLmwfncHgoQCBFQT6fELJLYbzymzDvyeXDERisWikZiUdjxXjrjciSSmGSCW9gMRMDtGAQnvEXga4cLgsAfgAlVBMdCS%2BLSjlc2ioz3e32CBTawMaxUmiFm/UC%2BEW5EK9Glo5MLxELPYYmk8lU6Jyhj04NMghfX4AvDoLCt9t8gtCkXhxVx6VNml1VGqx4a4FiLxOwmBk2FxlQ426/Ptku2ss2q1VmvOwP1t2Zm6pn1sDNtosh0eRph0Cc/Ht9xgpr23v1X1dsBzcU83eLdQMhd4AHoACo4PghDEKgiFYPgn4ABUwX9H4EOQ6DEII3Dd0hMx4mCEkvCwOM3DQBgNiSf0HxQhCfgAMTwYhRh%2BbBVFYPYJSIsD3n3K1glZABJB9mV%2BOd82hAtQ1FccpQ7dANTEzAvTEAB9WjpkEVExNIH5JLXHd22mRxkGJARRkwVQkmIH4xJ%2BRdvAlPlJKNCDwPMyC3hEu1jgdS5awhaTWSnFttI0HzhPLA9K2rVAwveCKZWbOptK4OKAoSq1AoVEL8TPOtXXda9iGAAMgzeRTwwAWU5JgqC8Oiso0d9/iBYhQXBMCjgLWSjliwNSCG%2B4klRHK1wG2qNSjGMUyqgCdVNeKjyCwqktPQCLwqq43hWh96p%2BJrGla9qMmyrrARBLD80G9thrcUbsHG57JumpjZreBbX2TI4juqsK/IhU6hC8JI8kwdAIzBLxaAIGL3yijrHrcAtRjUkANK02hdNsxoDKOIyfjej7H1U9TBE0mkCb04mCEMwRjJm2q1uIiGoZhuGEaRm6VLR66ZtetnOaEurn3hhREeRzqVPOlq2oca7RrcYWBBiiWpbDSN%2BeRrh3yVy7Va10XNYYbKdfCxorO0y9ogICBsY1BRLgdgM3BluWYuMyHodSWGfYFt7Fggyy8GQT2lGaF2CBx922E91EQ8N/2eaDvnZYF9nw7B/C0KETBaNjHi%2BPoHD4Lw/ztuC3FQtK22u0i2UsrMXK6674qVxdBsPWO37TpNlX29unq%2BuZgbMYshPgPObTez9QgThZ5mxqxufNXFRf%2B0cU415gn75pARb0GWkGm4L3XRQD3m0%2B0sxUbb66O9J1nnMEI%2BzPWm/wwfp%2Bitmqm3bqiS2j8bZpTtlHGOTt46Jw9m6VOBtH4Z0DkobOvs37YHzvyDgyxaCcAAKy8D8BwLQpBUCcExpYawTJVjrA8qRHgpACCaHwcsAA1iAIhZgrjlDMJIAAHEIohGhYi8I0AANiEYkQhHBJC8BYBIDQGhSBkIoVQjgvB1RqLYeQ/BpA4CwBgIgEAqwCBJGrOQSgaBdh0GiKES4nBVBCKkQAWikZIH4wBkDWSkFcMwvBYaEBIL2PQ/BBAiDEOwKQMhBCKBUOoAxpBdAdAAO40iSJwHgBDiGkPYZQzgFJqxWNZKgKgPxXEeK8T4vxPwAlPwgB4ex9AnLmHiFwRYvB9FaGWBAJAdikgOLIBQCAQyRkgGAFIMwfA6DbE4pQCIhSIjBCaCcHJvBVnMGICcCkERtAl30Swuxd4CAUgYLQDZKSsARC8MANwYhaDqm4LwLALBDDAHEDcjiRy8B9UKfZEu1ZNgsI0vIihtA8ARBpLsjwWBCmdjwMo15pBQTEAiEHDkHyjBQqMOw5YVADDVQAGp4EwOkpsZCWGROEKIcQcTaWJLUIUtJ%2BhPkoGsNYfQ0L1SQGWA8OoLz3HYylKYWhlgzCaPRcQJefKIDLDsH85wEBXATHaKQQIwQBilCGB0PI6QBDqtyKkQ1DBZiDBiFMGoyr6hjBaJ4NoeglVmztTMbVcw9W2HtcaqY9qLW6qtYqhhGwJB5I4CQ9RhStFVLcZ47xvj/GSECT8CAuBQntOYd01hBLlgIEwDGIYCrSDcMkPEK4CRyiSA0JIQRUjVFEKkbEfQnBFGkGUZ0q4UiuAyNiEIntRDJBcCIQkKRUaUlaJ0SAPRBKjGmIGeY0p1ixkTLaU4tgnAmgsGBOUdxTALyii4LEK4XArgUJCUQWVakOi0uiQy6QTKlAspSboWZmSmDZNeeGyNGjeBaJKZY6sPwKk/C3TuvdB7wxHpPWe1NLThltMlKRMw2bemGIXau6INjxmoFaUMMDu7XRGCPVwNRNAkbRHVBAZZKTtnrM2aQOjuz9mHIcAx05foLlXMKbc%2B5jzaDPIY%2B8z53yKH4G9KrAFKSgXIBBQx8FhSoUwvWfCzYFCkUopYeizFShsUibDLOolTBSXkspbiBjt76WxIfbIZlySKGvvZfi8VVhLA8oiPKgVDEMjCtFfGFz1gpV/plXK%2BAiqbWupcAwdwjrJiauiwG%2BY%2BrTV1F9ckFLGREtepdXUHo4xYsapy90f1HrLXOp9QV8r7rihla6SsNYoa6vyJ/dGzgoHiDbt3fuojUHj2ns6mm/Al6kOdNQ7m0g%2BbC0xGLfIttHbj01vKCOyo8Ra2SC8R0X9RTtG2GnTmgx/T51IAsWU7DmHiDrs2Fu2pLAFDAmssCaDyJRjBKG2E698S6UxIkDZhJT77M6BAIkd9n7cktojQUidxSl3lMqdd7xt37uuSe7aLizTcMIeiCN%2BIY2DtGMGRjkZZ3CdtJAPd6G2lHuxG0s95G8O5kUcWdRlZazdkMaY3sg5Rz2O4bOVx65YnMB3IeU8l5LDhO4rU2835kmwSAtUMC7Y8naYQt4Ep2FJxVOItlZp3g2msU7H0/ivHRmTMUqpRZ2Qd7rOfbs6yoHTnjBcrc0pzzlDvO2U4FBV2AXJXSuiFeuX/LOi2qizF7IGqtU1cDSa/IGQ0sGrqFlq1IfXV5YdRH51EXcslej0l71vQ0vTGaMnsN9XGFl%2Ba5DzRbX4c/ERw9lH2w0fpuGx0rpPTxuTawNN8Nc2QBmGPfEeIRCxFDtUcP8oMjx01527o/bfSuEgEkOUQJS2uBSFiIthIXAqjyPiNXv9nBO8HfDUEmfR%2BdtocWMsdFaRnCSCAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/omennivore/bi_harvest.hpp)
- [unit test](../../../../tests/unit/metafunctions/omennivore/bi_harvest.test.hpp)
