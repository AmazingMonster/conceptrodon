<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::BiCognateGauge`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-bi-cognate-gauge">To Index</a></p>

## Description

`Pagelivore::BiCognateGauge` accepts an operation.
Its first layer accepts a list of transformations and returns a function.
When invoked, the function instantiates the transformations using its arguments via a process similar to pack expansion;
then, it invokes the operation by the value results collected from the instantiated transformations.

Check out **Examples** for more information.

<pre><code>   Oper
-> Transf<sub>0</sub>, Transf<sub>1</sub>, ..., Transf<sub>n</sub>
-> Arg
-> Oper&lt;Transfs<sub>0</sub>&lt;Arg&gt;::value, Transfs<sub>1</sub>&lt;Arg&gt;::value, ..., Transfs<sub>n</sub>&lt;Arg&gt;::value&gt;</code></pre>

<pre><code>   Oper
-> Transf
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;Transf&lt;Arg<sub>0</sub>&gt;::value, Transf&lt;Arg<sub>1</sub>&gt;::value, ..., Transf&lt;Arg<sub>n</sub>&gt;::value&gt;</code></pre>

<pre><code>   Oper
-> Transf<sub>0</sub>, Transf<sub>1</sub>, ..., Transf<sub>n</sub>
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;Transf<sub>0</sub>&lt;Arg<sub>0</sub>&gt;::value, Transf<sub>1</sub>&lt;Arg<sub>1</sub>&gt;::value, ..., Transf<sub>n</sub>&lt;Arg<sub>n</sub>&gt;::value&gt;</code></pre>

## Type Signature

```Haskell
BiCognateGauge
 :: template<auto...> class...
 -> template<auto...> class...
 -> template<auto...>

BiCognateGauge
 :: template<auto...> class...
 -> template<typename...> class...
 -> template<typename...>
```

## Structure

```C++
// Gauge `Rail`s
template<template<auto...> class>
struct BiCognateGauge
{
    template<template<auto...> class>
    alias Rail
    {
        template<auto>
        alias Page = RESULT;
    };
};

template<template<auto...> class>
struct BiCognateGauge
{
    template<template<auto...> class>
    alias Rail
    {
        template<auto...>
        alias Page = RESULT;
    };
};

template<template<auto...> class>
struct BiCognateGauge
{
    template<template<auto...> class...>
    alias Rail
    {
        template<auto...>
        alias Page = RESULT;
    };
};

// Gauge `Road`s
template<template<auto...> class>
struct BiCognateGauge
{
    template<template<typename...> class>
    alias Road
    {
        template<typename>
        alias Mold = RESULT;
    };
};

template<template<auto...> class>
struct BiCognateGauge
{
    template<template<typename...> class>
    alias Road
    {
        template<typename...>
        alias Mold = RESULT;
    };
};

template<template<auto...> class>
struct BiCognateGauge
{
    template<template<typename...> class...>
    alias Road
    {
        template<typename...>
        alias Mold = RESULT;
    };
};
```

## Examples

We will see six examples that present different use cases of `Pagelivore::BiCognateGauge`:

- We will pack `0` into `AddZero`, `AddOne` and `AddTwo`.
Then, we will collect `value` members of the results to instantiate `Operation`.

```C++
template<auto I>
struct AddZero 
{ 
    static constexpr auto value
    {I}; 
};

template<auto I>
struct AddOne
{ 
    static constexpr auto value
    {I + 1}; 
};

template<auto I>
struct AddTwo
{ 
    static constexpr auto value
    {I + 2}; 
};

template<auto...>
struct Operation;

using SupposedResult = Operation<0, 1, 2>;

using Result 
= BiCognateGauge<Operation>
::Rail<AddZero, AddOne, AddTwo>
::Page<0>;

static_assert(std::same_as<Result, SupposedResult>);
```

- We will use `AddOne` to pack each of `0`, `1`, and `2`.
Then, we will collect `value` members of the results to instantiate `Operation`.

```C++
using SupposedResult_1 = Operation<1, 2, 3>;

using Result_1 = BiCognateGauge<Operation>
::Rail<AddOne>
::Page<0, 1, 2>;

static_assert(std::same_as<Result_1, SupposedResult_1>);
```

- We will pack `0`, `1`, and `2` into `AddZero`, `AddOne`, and `AddTwo` separately.
Then, we will collect `value` members of the results to instantiate `Operation`.

```C++
using SupposedResult_2 = Operation<0, 2, 4>;

using Result_2 = BiCognateGauge<Operation>
::Rail<AddZero, AddOne, AddTwo>
::Page<0, 1, 2>;

static_assert(std::same_as<Result_2, SupposedResult_2>);
```

- We will pack `std::integral_constant<int, 0>` into `TypeAddZero`, `TypeAddOne` and `TypeAddTwo`.
Then, we will collect `value` members of the results to instantiate `Operation`.

```C++
template<typename Element>
struct TypeAddZero 
{ 
    static constexpr auto value
    {Element::value}; 
};

template<typename Element>
struct TypeAddOne
{ 
    static constexpr auto value
    {Element::value + 1}; 
};

template<typename Element>
struct TypeAddTwo
{ 
    static constexpr auto value
    {Element::value + 2}; 
};

using SupposedResult_3 = Operation<0, 1, 2>;

using Result_3 
= BiCognateGauge<Operation>
::Road<TypeAddZero, TypeAddOne, TypeAddTwo>
::Mold<std::integral_constant<int, 0>>;

static_assert(std::same_as<Result_3, SupposedResult_3>);
```

- We will use `TypeAddOne` to pack each of `std::integral_constant<int, 0>`, `std::integral_constant<int, 1>`, and `std::integral_constant<int, 2>`.
Then, we will collect `value` members of the results to instantiate `Operation`.

```C++
using SupposedResult_4 = Operation<1, 2, 3>;

using Result_4 = BiCognateGauge<Operation>
::Road<TypeAddOne>
::Mold<
    std::integral_constant<int, 0>,
    std::integral_constant<int, 1>,
    std::integral_constant<int, 2>
>;

static_assert(std::same_as<Result_4, SupposedResult_4>);
```

- We will pack `std::integral_constant<int, 0>`, `std::integral_constant<int, 1>`, and `std::integral_constant<int, 2>` into `TypeAddZero`, `TypeAddOne`, and `TypeAddTwo` separately.
Then, we will collect `value` members of the results to instantiate `Operation`.

```C++
using SupposedResult_5 = Operation<0, 2, 4>;

using Result_5 = BiCognateGauge<Operation>
::Road<TypeAddZero, TypeAddOne, TypeAddTwo>
::Mold<
    std::integral_constant<int, 0>,
    std::integral_constant<int, 1>,
    std::integral_constant<int, 2>
>;

static_assert(std::same_as<Result_5, SupposedResult_5>);
```

## Implementation

`Pagelivore::BiCognateGauge` separates cases according to the number of parameters.
The goal is to mimic the behavior of pack expansion in C++:

- If the user only provides one variable, we pack the variable in each sequence separately;

- If the user only provides one sequence, we use the sequence to pack each variable separately;

- Otherwise, the number of variables shall match the number of sequences.
We pack each variable into its corresponding sequence.

Here's the entire implementation:

```C++
template<template<auto...> class Operation>
struct BiCognateGauge
{
    template<template<auto...> class...Devices>
    struct ProtoRail
    {
        // Multiple Sequences
        // Multiple Variables
        template<auto...Variables>
        struct Detail
        {
            using type = Operation<Devices<Variables>::value...>;
        };

        // Multiple Sequences
        // One Variable
        template<auto Variable>
        struct Detail<Variable>
        {
            using type = Operation<Devices<Variable>::value...>;
        };

        template<auto...Agreements>
        using Page = Detail<Agreements...>::type;
    };

    template<template<auto...> class Device>
    struct ProtoRail<Device>
    {
        // One Sequence
        // Multiple Variables
        template<auto...Variables>
        struct Detail
        {
            using type = Operation<Device<Variables>::value...>;
        };

        template<auto...Agreements>
        using Page = Detail<Agreements...>::type;
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;

    template<template<typename...> class...Devices>
    struct ProtoRoad
    {
        // Multiple Containers
        // Multiple Elements
        template<typename...Elements>
        struct Detail
        {
            using type = Operation<Devices<Elements>::value...>;
        };

        // Multiple Containers
        // One Element
        template<typename Element>
        struct Detail<Element>
        {
            using type = Operation<Devices<Element>::value...>;
        };

        template<typename...Agreements>
        using Mold = Detail<Agreements...>::type;
    };

    template<template<typename...> class Device>
    struct ProtoRoad<Device>
    {
        // One Containers
        // Multiple Elements
        template<typename...Elements>
        struct Detail
        {
            using type = Operation<Device<Elements>::value...>;
        };

        template<typename...Agreements>
        using Mold = Detail<Agreements...>::type;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwA7KSuADJ4DJgAcj4ARpjEIGYawQAOqAqETgwe3r4BaRlZAuGRMSzxicnBdpgO2UIETMQEuT5%2BQbaY9o4Cjc0EpdFxCUkptk0tbfmdCpODEcMVo9UAlLaoXsTI7BwEmCypBvsmAMxu%2B4fHmGduTF5EAHTPZ9gA1MgGCgpvAPKpCSYvQYrxMGgAgnNiF4HG8LHgPMBmPsAOL3YA3CEmQJWCFvfFvS5HIE3c5E663e5PF6nd6fJjfZ6PAAimAAbngdgpQXiCVCYQQ3spiKgiAAlJh0MHgglvbG4mWygkAemVbwAsl5aI4jpg3kJMABHLyMLnSpUqtWa7V4XVvABqzTwTFi9G5vIt5JJlIeqCZjuIztdmG5tPNFre/NhrKaUo9Svl4YjBK8mSMhIAngC5admX8AcQgdlbqyOWbzgGg27XiAQGyxCamaDTgrk9jmWcFUmlaqNVqdfR9UaTQwzfHZb3fpEHU6XfRu7KvSdzlTUDPA3PSdgF3yCNDo5hY7RbpXNzzFRbE%2BOI6mIsBM9mznn/oDgSX2ZyQyfZ8Ga3WG5gTZhi2O74u2nbSqBhIHMSy53L6TLgsAxCYAcjAEKG27Xvit7psoTAYjmeYxpKx7nEhKFoYIChAdgtYEFmpKtgS4EgVi8ZLqSFwwRSK4ITSdJfD8pafuespRoKwqiqgEpSucIk7GJLE4lBk7TgaxqmpiF49la/a2oOp7Bu6OmLjx3p8dSjxGdWYbYZGe4Cm8JFxqZynMcmOFpveDGPrm%2BavsW8kfopFY/rZdH/t4gECRB9msV29mcT6VkUahbDUUpFq4fe%2BGEU%2BzmHqRtxpVRGG0fRjFxTpCWQRx5lwclll%2BgJHxCYhyHpehmHdjlbyybQRFCiK4rFeRnVlTRsVseC3ZNdxVwWRcjHMGwtFtQyU0siFX52TpEnDdJYqoEw6Ddlebn4r21oDnqHiCJKkTECZybXfpdrYPQGUYVB82%2BYwrAxY8n2TVlSoHS5x7xSp9myn1/1DS%2BhZvsFZa7W4IPfZhtb1tFtHVW2gQdjNql6Tadr3bGT0vRGal6pj6G/Q1XH/at9NfYze3JhDRVyRjHOCGDsoXZ5KbeQ%2BeoFUjRYCO%2BaOhvzZV/rjjbTR5CZE9VTOLY1K2Ax1lFY0LYt3hqnjoENkMlRNWMVSA/0E8pxOJTpf3M7crP6619LfIVaNgwdUniidZ2o6JXPuaTfzTpTj0JDTFpveTg4M5lSXu2Setrc8Nm7Vhl0OfugpW9D6vJvDjGIwWMsgmHoVuLn2NRarjzNmXTta%2BnOss1nQOlUbEfZeL6rm5bvNkW4/fdXbDszcLmsk/V3cexny0Amz60%2B1tU%2BZYPbx9cdp1DUHMkh9bhvT2rkELy70rKgAVI/T/Py/yp38/bwACohhhbzP2/EIH4v2AU/ABs0sRmFOBET4XgsA5jcGgUcmBUg/T2tKeaq43gAElzwHXBOgdAAAtBIa5r4WDlPGOYRZkAfAEHMTAqhUjEDeJglW2l54WBwTfChs0b51XBBg302DcGOVhPg9AU5tLyh4eJJojgaGIPoYw5hrCALnRxFguUlg3hcASjw2q7EBGr0wTgvaeCCGfwAO6oDITI3c1DaEMCUUwlhQi2HqM4Vo8hZg9HX2dvwv6vc3ipwICIouX9GLiOISKfROI7H4iofIxxziVFuLUfGeUIScZqO4X4zuRjl6Z3XoDYJAtQlmNEYKT%2BkSCGSNsd2RJnJkn7GUa4ogbx3EZJxFk5ukttG6NyViPhhjAnFLYKUpWFTwnVIBOIqxNihnkIaXIppiiWkuNUdFDxPS2FeLeD4wZvD/EjOMfxVuUynLSxRi7IBj83gADE8DPUFNgVQrA7T/34X1IQXhUjpCUOgMUIZ%2BxV0CrLc4GhSA6KhT44CLsD7Au1Po/y8JETIkwGiLwGJbhXKCvnWsA0SoEOiagKF4jJFkosdY88tY8pcQ0G3fhjTkAAH1NoJAIBAOY6BawKEBmyhWQKFD9ihT8v5GRMCAsReU7Aqx8m3PvkORBFtXnvMHJ8wx3zfn/MlUK/sLKuCguRkFNwXAYVQtOIyzV4s9XagNUNVFqAkQkkxdi84uLwX4pAIS8itTIg0pAHS24kLoX7KteAyEKzWXspaFyggPKQB8rYAK24tqCAGtFdqiVUrhV2t0bSOVi9wQKq/ggJ5Kq3lXD1BqiNWrxUArTSyswRqa7BvNW8SQ4bpQItzem5tBVHXOtROiLiHra5ep9ZPYlJDKUSMiLO%2BZAag0QqhWasNcKmVRoFUoWN3LeX8oZKm6VTbM31t1ce2Fsr5Uf3uZsFoCBgmVo%2BaAr54sxU6pzfq04LaUZuBDWuy9%2BSe1fuRXmQd6LXWjurijCdZ9zgzMwFEmdETZl%2BswFChDczqV7VrCPWgoc3B7pABEfYyExAsrWYYcpbgSNQoZcBbcRbmXbo5XGhNSbMApvOI204p6P08deIWm5N68BUAIA%2B1VVa/4vutabd92bG2SB/SagDFqu0QmA3apTA6EROogyOnF0G8XSgJXBtwmG0MBrwwR5ZCaSOYDI7QCjdCmiC3OLRt49HsCkFs7WezjnnNONc9Rjz%2BbvO%2BeI4IBzhYnOUbczRwQMLzzqcjdQlju7437uTYe7jx7pD6izQ2vLgnr1P31HgVQ4nH1qurTJ2tb7Cvnt7Sy/wynwV/vbZ2jdsn0yNtazptFLqDPuqM56kz3qzMWaIchqbFKUOIapTYnDIBrO3Ai/5mLgWqHxY815nzlDMuRdI5tuLIXEs6NePt/ah2NvkdO7cDzgGsTdYjcxmNnKiMca424PrfGFPHv8CVlsHB1i0E4P4XgfgOBaFIKgTgbhrDWEjHenYWjTg8FIAQTQIP1gAGsAiSEeBoSQXBAinA0P4DQZgABs1OzAAA56f6E4JIXgLAJAaEhVDmHcOOC8AUCASFWPocg9IHAWAMBEAgE2AQVIDxyCUDQIcOgCQoiA04Koen1OAC01OlPAGQDQqQjwzC8ElYQEgeAeVmv4IIEQYh2BSBkIIRQKh1Ai9ILoM1ljCypE4DwUH4PIfY9h5wX4Dw5eClQFQN4mudd67eAbo3hPm0QA8Mr%2BgzDzDo9WLwYXWh1gQCQEr1IKuyAUAgCXsvIBgBSDMHwOg%2BxnqUFiCH2IERmgZn97wdvzBiAZl%2BLEbQdRhcY6V99KctAu8e6wLELFdxaC0AF9wXgWAWCGGAOIGfTyR94DZCGEPDC6gPF2Bj%2BzYOPe0DwLEQs/ePBYBD3uPA7OV%2BkH38QWIErWTr6MFfow2P1gqADBgAFB7Q8BMBLEXwocMdbdhBRBxAndYDXc1AQ8vd9AN8UBEdLB9Br8BdIB1hUAUFshl9tduUnxTBLBrBkheBUB39AwsA8CIB1hah6hnAIBXBpg/AzUwhFhyhKg9B/ligchPB2gBCihgQhg%2BDRgzUWDgR%2BgpgRD8gZDuhd8%2Bh5hJCRhEgZD5hOC9AqEWgNDlgtDmCUdHdA8OAIdSBucaDOBY8tddd9dDcdEU83gIBcALcs9IEuBc9McAD1gEBMBTpRgmDSB8dJBThHgABOU4QISQYnMwSQanTnfwanSI5nDgVnUgdndHR4anLganenSI%2BnfI/wEnfwaI6nKwkPXnfnQXXwkXQvSXIvaXCPeXCvKvTPNXNgTgZoFgNkQIbXJgDadMLgSIx4LgInM3fAIgegvQWA%2B3BA6QJApQFAj3XQevH3JgP3Ffcwyw6w0PDgcPWXB4N4aPFhYgPogYoY%2BkEYsYiYjQVw9PUvTPNHMwHw/PUXZojohIBXSvVADPUYXo/o7XG42vSIrgSFGgbUeOFvNvDvfvbvUgXvTvQfYfBwRE8fdCSfafGHWfefMQJfREtfDfLfXEnfeoffZfGHI/ZAE/RE8/EPK/G/Tve/XYGHJ/F/DHd/T/JQb/Eku8AAvgYA0A8AyA9eRE%2BY%2BAx3JY2QZA93GHdY9A//CgqwbApkxgggoguhTgUg%2BNcgrAiwag2HOgq3A/fAroHobIFwBgdwRQrgkIG0ww/gs1QQ4EXQl08Q7IJ06Qi01QhgeQ1oO0vQlQ1g/09Q3gzQvQnQoM7QgYb04wjYLYHYCQXY4PD3Xnc4y4wY4Y%2B8UY8YonVw9wmYtHbwvPPw0gAIoIxIEIi/TI7IsY4nQIcowIMnSQBIvXM1fYmo2wOoj4xo%2BAZomXSPX4744gLo3YXohPFgBQNkGhNkPM64OYKYjwq3OY2QBY6U53eQFY%2BUnQEAXjTY7YgPdIvY6osPVoqPGPScpTac2cjpBckkOYR4/454hINHU4d4wUr4l8svEcn8zPOsZAP5FlecyIllRc9Na8hvaE5vCAVvD3ZEhE1/RCgfIfEfDE/4ifBgKfEPPE4ABfQk1/Yk3/Nk1fckxwSkw/VQY/fYekqLC/GHJk2/DMVkx/QMTk3gbkr/A4fk//BooUgiEUiAqAiU9cqUiQGUl3Hc1A/cpU4wA0nA2IDU2HLUpxTgZUPdFUqgnnE0hg%2BAZgkM4Ea020vIe0ngsoSMj0zIN0mM0gV0r0iMow4My0tQgYd0300MgM%2BMqMty2y/QhYCypy7wxM7YMwk8tMnnWw68t4W8uch8/YJ8tw6YkgEsz8ho/wwIrAas8wuspIMY04U4fwSnEnTnAqwIAoqo9MzgWooXcssI/wKI/wenGnSIyQSIsnGIrgXjC/U4CKmwvneogvcw03SqyKgavs9Yd/TIZwSQIAA%3D)

## Links

- [source code](../../../../conceptrodon/pagelivore/bi_cognate_gauge.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/bi_cognate_gauge.test.hpp)
