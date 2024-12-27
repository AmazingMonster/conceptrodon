<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Gauge`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-gauge">To Index</a></p>

## Description

`Varybivore::Gauge` accepts a list of variables.
Its first layer accepts a list of sequences and returns a function.
When invoked by an operation, the function places the variables into the sequences via a process similar to pack expansion;
then, it collects the value result of each packed sequence and invokes the operation with the collection.

Check out **Examples** for more information.

<pre><code>   V
-> Transf<sub>0</sub>, Transf<sub>1</sub>, ..., Transf<sub>n</sub>
-> Oper
-> Oper&lt;Transfs<sub>0</sub>&lt;V&gt;::value, Transfs<sub>1</sub>&lt;V&gt;::value, ..., Transfs<sub>n</sub>&lt;V&gt;::value&gt;</code></pre>

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> Transf
-> Oper
-> Oper&lt;Transf&lt;V<sub>0</sub>&gt;::value, Transf&lt;V<sub>1</sub>&gt;::value, ..., Transf&lt;V<sub>n</sub>&gt;::value&gt;</code></pre>

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> Transf<sub>0</sub>, Transf<sub>1</sub>, ..., Transf<sub>n</sub>
-> Oper
-> Oper&lt;Transf<sub>0</sub>&lt;V<sub>0</sub>&gt;::value, Transf<sub>1</sub>&lt;V<sub>1</sub>&gt;::value, ..., Transf<sub>n</sub>&lt;V<sub>n</sub>&gt;::value&gt;</code></pre>

## Type Signature

```Haskell
Gauge
 :: auto... 
 -> template<auto...> class...
 -> template<template<auto...> class...>
```

## Structure

```C++
template<auto>
struct Gauge
{
    template<template<auto...> class...>
    alias Rail
    {
        template<template<auto...> class>
        alias Rail = RESULT;
    };
};
```

```C++
template<auto...>
struct Gauge
{
    template<template<auto...> class>
    alias Rail
    {
        template<template<auto...> class>
        alias Rail = RESULT;
    };
};
```

```C++
template<auto...>
struct Gauge
{
    template<template<auto...> class...>
    alias Rail
    {
        template<template<auto...> class>
        alias Rail = RESULT;
    };
};
```

## Examples

We will see three examples that present different use cases of `Varybivore::Gauge`:

- We will pack `0` into `AddZero`, `AddOne` and `AddTwo`.
Then, we will collect `value` members of the results to instantiate `Operation`.

```C++
/**** Transformations ****/
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

/**** Operation ****/
template<auto...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<0, 1, 2>;

/**** Result ****/
using Result 
= Gauge<0>
::Rail<AddZero, AddOne, AddTwo>
::Rail<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

- We will use `AddOne` to pack each of `0`, `1`, and `2`.
Then, we will collect `value` members of the results to instantiate `Operation`.

```C++
/**** SupposedResult ****/
using SupposedResult_1 = Operation<1, 2, 3>;

/**** Result ****/
using Result_1 = Gauge<0, 1, 2>
::Rail<AddOne>
::Rail<Operation>;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult_1>);
```

- We will pack `0`, `1`, and `2` into `AddZero`, `AddOne`, and `AddTwo` separately.
Then, we will collect `value` members of the results to instantiate `Operation`.

```C++
/**** SupposedResult ****/
using SupposedResult_2 = Operation<0, 2, 4>;

/**** Result ****/
using Result_2 = Gauge<0, 1, 2>
::Rail<AddZero, AddOne, AddTwo>
::Rail<Operation>;

/**** Test ****/
static_assert(std::same_as<Result_2, SupposedResult_2>);
```

## Implementation

`Varybivore::Gauge` separates cases according to the number of parameters.
The goal is to mimic the behavior of pack expansion in C++:

- If the user only provides one variable, we pack the variable in each sequence separately;

- If the user only provides one sequence, we use the sequence to pack each variable separately;

- Otherwise, the number of variables shall match the number of sequences.
We pack each variable into its corresponding sequence.

Here's the entire implementation:

```C++
template<auto...Variables>
struct Gauge
{
    // Multiple Variables
    // Multiple Sequences
    template<template<auto...> class...Devices>
    struct ProtoRail
    { 
        template<template<auto...> class Operation>
        struct Detail
        { 
            using type = Operation<Devices<Variables>::value...>;
        };

        template<template<auto...> class...Agreements>
        using Rail = Detail<Agreements...>::type;
    };

    // Multiple Variables
    // One Sequence
    template<template<auto...> class Device>
    struct ProtoRail<Device>
    { 
        template<template<auto...> class Operation>
        struct Detail
        { 
            using type = Operation<Device<Variables>::value...>;
        };

        template<template<auto...> class...Agreements>
        using Rail = Detail<Agreements...>::type;
    };

    template<template<auto...> class...Devices>
    using Rail = ProtoRail<Devices...>;
};

template<auto Variable>
struct Gauge<Variable>
{
    // One Variable
    // Multiple Sequences
    template<template<auto...> class...Devices>
    struct ProtoRail
    { 
        template<template<auto...> class Operation>
        struct Detail
        { 
            using type = Operation<Devices<Variable>::value...>;
        };

        template<template<auto...> class...Agreements>
        using Rail = Detail<Agreements...>::type;
    };

    template<template<auto...> class...Devices>
    using Rail = ProtoRail<Devices...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwA7KSuADJ4DJgAcj4ARpjEEgDMAGykAA6oCoRODB7evgHBmdmOAuGRMSzxiVyptpj2ZQxCBEzEBPk%2BfkENTbmt7QQV0XEJyWkKbR1dhb1TQyNVNRMAlLaoXsTI7BwA9ABUR8cnp2fHeyYaAIKHxwDUAJIs6fRsgkzN9yeXN3fnAPOv2uV2uBEwLwM4JMSTcTC8RAAdMiAGrtPBMWL0BQw7CgqbELwOe4AcXhwEwoJMgSsN3u9Puez29wAsl5aI5Xph7mjiBisZgcXSGUzWezOfR7kJMABHLyMHZC64M%2B7gyGfSmwtWvDUwuEI1DIxG4%2B7IAwKBRGgAimAAbnhFbjQSqCUSCPdlMRUEQAEpMOjOhnUiz3QMq%2BnaqGatyR3Ww%2BFI5Ems1MC33ADy6QSn1yTuF4furuJNraAfz4eDofLBfpXmyRlVAE8s6GklaM1niDmBHqbfbHbDefzsbiQCBbWJ5UanUlacqa9SrTC52Hw7HoVqITqN/rE8akthTebLcjrsBiJgIYwCDiD6uVXWIsB7n66K32yX/bQ9WeL1fBCe%2B7YGOBDNpqc4qouy5UuWopshyeBcjy6KYiOsHMumkRSrK8oMDsq7rtGhF6gmhpJgeR6pgo9x9g6mp4uWRbup63qoK%2B36wrR%2BF3uWlb3gyxGbuqO6kdOFEpmmmbZs0ebzgWTE0ZgpbftWQY0lWck1rW9bPqBLYwu2UldjJnF2nRepDqhgqjuOk6YGJeKzvx9JQU5NzOaqW5Rnqgm7mRQGURaRq/pe7w3rJWmPg27Hvopyk/ueoXXoBNl6eBq6uSu5a%2Bb5onkYeEmAVx1k8ZpUXPjFBkel6vpfr2ZmKg50HuYES5uSCNy5QayF8lZskKWSXgUhZKECrJwarqKmHcpZY3oWKCFIdKcoKtZ2VeXGMYbSJBoOYFRUNSVDGaQpLG1WWml8apEbbURt0kbt%2BX7R20m5qVWkKZ%2BF1aVdmmRTpTb6W2L3GW9bjFbebizfQNkTt49n5c1f1qW1WXIzdwl3ZjD17smx7BYl/7he9NblS%2BX6xV9HFuCFRMpQeIFgUjkGtUjBH3UJ27RnlAWFdah23sdD4A5VwNnWxdWmf2gpNe1mUwbcgJKz8oL/Ac9wAGJ4MQUz3NgqisEhKt/MrpvAlSZhJBEZpeFgrZuGgeGYOkxPHarJz3AAKl2DAKPwxAsN2vvfBcoJdUQTz9QQhLEtc6DoAAWgkqAab9LptI4yCmgIUyYKo6TEPcpH3HD8oZTSjyZanrNy51HN%2BZHpUKXH6DTVS6mrgsmfZ774L54Xxel5SvEV6Glj3FwVft6jCvhynldN9Hbr3C3nsAO6oO3IadxnDo97n/dF91Q/lxYjxjyGZhTy1M/uSbDxGUHIdHMCc9NTcCmPyZaNq1KXjpCUTA6AfSCnFM/A4wIyZCH/oA4BoCOSxS/mDDQpAJ6oKvneWuisHggIUGA421wya4LAVSYGg1hqwg0LJMc7EfzxyTl6VBLdppMPjuvTepUaGSzcEgnsmCf4e09oKd0BCu4OgAPpUQSAQCAUx0BjgUKwTAkjIbEI5Kg6BACshALUQQXEqw2b31NkrYEv9pSO3QHrA2kJuQELVsYoECszEwO0XAvBCCCFQJcUoNx4pxFcEQZ2IOeouDoNQUkGcAicHwJEaHG4RCYn%2BNiuQ6MKC0H3AwcdLhAZYTMMiNQkAtDYS8IYJEpxgjhHgOBGI5AKilAdFkQQeRIBFFsBUXqXR/iNHeJ0YkyeB4DFYPsQ4uxgiEDa0sfrQ2kpRkjMcXfbBRw/5aJ8boqpoIvErN6e4gg4izCBNenwtwaSzCoMkGUhZv81meJFok/ZVUUl6jSaEjJBSik03ocnVhrdIjfPYW87hJSLkdUWerIRutRG71qVIhpciFFKPabCTppzlmwORfo5cHB1i0E4P4XgfgOBaFIKgTgbhrDWELJsbY3JzBJB4KQAgmgsXrAANYBEkIiDQAAOMwZgACcfKuD%2BG5VyrggRAjSBxRwSQvAWASA0CgglRKSUcF4AoEAKDGWEqxaQOAsAYCIBAJsAg6QETkEoGgF4dAEhRCUZwVQXKUgAFoUiSHuMAZAWcpCIjMLwIBhASB4HkaE/gggRBiHYFIGQghFAqHUNq0guhQlry7OkTgPBsW4vxUy4lnB0wIlNe6VAVB7gOuda691nqJ4cv2RADwVr6CF1pVwVYvAtVaHWBAJAlr0jWrIBQCAPa%2B0gGAFIU5NAOQJHVRAWIObYgRHaI2dNvB53MGII2dMsRtCYAcMu0glqwqYVoEuhNWBYhDThLQWg6ruC8CwIHIw4hT3ax3Y4W0goc15x3QiXY9KIjgilUS2geBYhdnXR4LAObo54Dlbe0g77iCxG0TaB9wBgNGCZesKgBhgAKBRHgTAa8pIEvpaG4QohxBRrI7GtQOak36EMMYcllh9AgfVZAdYqAXa5BvU6uRBlTCWGsGYZVCG%2BRYHYxAdYdhX25BcAwdwnhuh6DCBEUY1RxihJKDkAQsw/BaayDphgSwxi1D6LJgQgwZhKcKKEmTDgBjTGGGp5YmnbBOb03oBYHQTMadqNJqlOwJCZo4Hi0gSreAqtLY6l1bqPVeprfcCAuAA1Nsti2ttmH1gIEwEwLAiQpOkDZZIJIiI%2BVJAlRoSQZhJApAVf4FIfL9CcBlaQOVdLEQpC4CkLlfLRUpH8JIIV5W0gRdzaq2wGqGWYd1QartRqC1moHUOxttq2CcHaCwW0gQnVMEog2LgfLERcE5X6/ARBxN6DI%2BGyj0hqNKFowm3QpyU1MDTbekLYWxsqvzSahE9xi3RfLW6lMB2jsnY0El%2BtvbG1jySGYVt03tWdu7agBtCRzWDrRzD8YoPR2CpQRO8EOtKCzoTauxde6Kfrs3du3dcGD3XiPSeolZ6L1iGvXu%2B9jGn2s5fQ599N6iVfuQD%2Bvd/7Gg5uA6BxdEHdhEug7B%2BlCGkNKBQzzp8M3sNMFw/hwjxG93XYo5Gu7sgaPxqJc9hjGHBNWBY9LyTnHuM504HxppAnmMWBE5FsTQaP0cfMw55wEBXCedCapyopm9DaeaGHjIhnmi%2BZWHZxoFmWgeZs/pwPzQrPOcj35rzGeChZ%2B83n9TyeAtbCCy25roXs0Jqi2W2L%2B3nyHeO5ypLKWLtw4y0jjt2Xcv5coCF1r7WjtVcCP4Pl4qkjVdq0N8LOaVVqqm%2B2nVerDXGsLZjlbNq7UcE2xWlgChbRZ1tG3qMUwzupaDVd2QN2TfRvkA9i3OgQBJFIK997Gba9faX3mxbItEtVQI/E/M/C/DUXWOtbHPtOHJIRHNfFHFAGAxtHfFA8YU/ABcRc/PlcRS/XZEAu7OgYnadMnIlanE9elCg2nV9PdRnQQZnHNNnYAS9TnODbnR9eXO9fnN9D9BNEXMXODCXQDXgaXMDRsOXKDPkJXXgFXZDCEDXDDZHPgHDPDAjIjLMEjXgI3CNCQU3GNF/Ojd/a3JjITe3NjeAJ3ZoG9PYOFW3YTUTBIcTf3QrezZoeTRTYvFTBTJPNzGPXIOPfw8oFzKPFPfoSzIvZTMItPXPXwszUvOPUvOI4LDYKvSNT7evZVTgUtUA0/EuCA8EKArvEgHvBArLUgHLPLcYQrKVUfEAflREJIJIfwYVIbBVJowIHrRfBvTgFfTVco4rfwMrMVQIBVLlSQQVLgHlMwNIKVJITIyLXovvZlWvX1borIibRA9YBDbIZwSQIAA%3D%3D%3D)$Done$

## Links

- [source code](../../../../conceptrodon/varybivore/gauge.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/gauge.test.hpp)
