<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Plume`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-plume">To Index</a></p>

## Description

`Varybivore::Plume` accepts a list of variables.
Its first layer accepts a list of sequences and returns a function.
When invoked by an operation, the function places the variables into sequences via a process similar to pack expansion;
then, it collects every packed sequence and instantiates the operation with the collection.

Check out **Examples** for more information.

<pre><code>   V
-> Transf<sub>0</sub>, Transf<sub>1</sub>, ..., Transf<sub>n</sub>
-> Oper
-> Oper&lt;Transf<sub>0</sub>&lt;V&gt;, Transf<sub>1</sub>&lt;V&gt;, ..., Transf<sub>n</sub>&lt;V&gt;&gt;</code></pre>

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> Transf
-> Oper
-> Oper&lt;Transf&lt;V<sub>0</sub>&gt;, Transf&lt;V<sub>1</sub>&gt;, ..., Transf&lt;V<sub>n</sub>&gt;&gt;</code></pre>

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> Transf<sub>0</sub>, Transf<sub>1</sub>, ..., Transf<sub>n</sub>
-> Oper
-> Oper&lt;Transf<sub>0</sub>&lt;V<sub>0</sub>&gt;, Transf<sub>1</sub>&lt;V<sub>1</sub>&gt;, ..., Transf<sub>n</sub>&lt;V<sub>n</sub>&gt;&gt;</code></pre>

## Type Signature

```Haskell
Plume
 :: auto... 
 -> template<auto...> class...
 -> template<template<typename...> class...>
```

## Structure

```C++
template<auto>
struct Plume
{
    template<template<auto...> class...>
    alias Rail
    {
        template<template<typename...> class>
        alias Road = RESULT;
    };
};
```

```C++
template<auto...>
struct Plume
{
    template<template<auto...> class>
    alias Rail
    {
        template<template<typename...> class>
        alias Road = RESULT;
    };
};
```

```C++
template<auto...>
struct Plume
{
    template<template<auto...> class...>
    alias Rail
    {
        template<template<typename...> class>
        alias Road = RESULT;
    };
};
```

## Examples

We will see three examples that present different use cases of `Varybivore::Plume`:

- We will pack `0` into `ZeroStar`, `OneStar` and `TwoStars`.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
/**** Transformations ****/
template<auto I>
using ZeroStar = std::integral_constant<int, I>;

template<auto I>
using OneStar = std::integral_constant<int, I>*;

template<auto I>
using TwoStars = std::integral_constant<int, I>**;

/**** Operation ****/
template<typename...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation
<
    std::integral_constant<int, 0>,
    std::integral_constant<int, 0>*,
    std::integral_constant<int, 0>**
>;

/**** Result ****/
using Result = Plume<0>
::Rail<ZeroStar, OneStar, TwoStars>
::Road<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

- We will use `OneStar` to pack each of `0`, `1`, and `2`.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
/**** SupposedResult ****/
using SupposedResult_1 = Operation
<
    std::integral_constant<int, 0>*,
    std::integral_constant<int, 1>*,
    std::integral_constant<int, 2>*
>;

/**** Result ****/
using Result_1 = Plume<0, 1, 2>
::Rail<OneStar>
::Road<Operation>;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult_1>);
```

- We will pack `0`, `1`, and `2` into `ZeroStar`, `OneStar`, and `TwoStars` separately.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
/**** SupposedResult ****/
using SupposedResult_2 = Operation
<
    std::integral_constant<int, 0>,
    std::integral_constant<int, 1>*,
    std::integral_constant<int, 2>**
>;

/**** Result ****/
using Result_2 = Plume<0, 1, 2>
::Rail<ZeroStar, OneStar, TwoStars>
::Road<Operation>;

/**** Test ****/
static_assert(std::same_as<Result_2, SupposedResult_2>);
```

## Implementation

`Varybivore::Plume` separates cases according to the number of parameters.
The goal is to mimic the behavior of pack expansion in C++:

- If the user only provides one variable, we pack the variable in each sequence separately;

- If the user only provides one sequence, we use the sequence to pack each variable separately;

- Otherwise, the number of variables shall match the number of sequences.
We pack each variable into its corresponding sequence.

Here's the entire implementation:

```C++
template<auto...Variables>
struct Plume
{
    // Multiple Variables
    // Multiple Sequences
    template<template<auto...> class...Cosmetics>
    struct ProtoRail 
    { 
        template<template<typename...> class Operation>
        struct Detail
        {
            using type = Operation<Cosmetics<Variables>...>;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;
    };

    // Multiple Variables
    // One Sequence
    template<template<auto...> class Cosmetic>
    struct ProtoRail<Cosmetic>
    { 
        template<template<typename...> class Operation>
        struct Detail
        {
            using type = Operation<Cosmetic<Variables>...>;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;
    };

    template<template<auto...> class...Cosmetics>
    using Rail = ProtoRail<Cosmetics...>;
};

template<auto Variable>
struct Plume<Variable>
{
    // One Variable
    // Multiple Sequences
    template<template<auto...> class...Cosmetics>
    struct ProtoRail 
    { 
        template<template<typename...> class Operation>
        struct Detail
        {
            using type = Operation<Cosmetics<Variable>...>;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;
    };

    template<template<auto...> class...Cosmetics>
    using Rail = ProtoRail<Cosmetics...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwA7KSuADJ4DJgAcj4ARpjEEgDMAJykAA6oCoRODB7evgHBmdmOAuGRMSzxiVyptpj2ZQxCBEzEBPk%2BfkENTbmt7QQV0XEJyWkKbR1dhb1TQyNVNRMAlLaoXsTI7BwA9ABUR8cnp2fHeyYaAIKHxwDUAJIs6fRsgkzN9yeXN3fnAPOv2uV2uBEwLwM4JMSTcTC8RAAdMiAGrtPBMWL0BQw7CgqbELwOe7KAqYUEmQJWG73Wn3PZ7e4AWS8tEcr0w9zRxAxWMwOJpdIZzNZ7Po9yEmAAjl5GDsBdc6fdwZDPuTYSrXmqYXCEahkYjcfdkAYFAoDR4FGxHMgcUk8YLaQSiQQScRUEQAEpMOj3UFKykWP2OpXKiFa6Ea8NQ9VuAgAT3SjFYmANRpNTDN9wA8kniJ9crj/aGnQRCcSACKYNp0YslwN1kt0rzZIzKxOcmEVnN5gsCHWW614W067m87G4tP2mHUxVNykVmcUkNKzUxnVr7UajvMNhT7DG03m5HXYDETAQxgEO0OucllsRYD3T2oJjoP1JbtVmu0HWn8%2BXoIx6GvaIAgAmSZLiGC5QSCIbCiybJ4ByXLopiE7wYy2aRBK0qygwOyNpukZxtGW66kiyLpke9yDtWw5FiGzrEso7pej6v6wnRNqMXefpUsGfGrmRJHEbGEHJnuVH2oemYKD2CR9gwvFNvczGut%2BHGNgGVLaU2D5thJH7drminNAOWRDqYsJjuh/KTtJeJJLOqkwc5y5CXSYkbiJ4k7im%2B6yWaBr/he7zXip%2Bmtk%2BL5vsZ9yabWsKhYB177mBEmwTpi7uTcRG%2BT5qokfClEgQeGbBci3HDjejYGTFHHxaxHqoN6SVuNVtr7rBbmzqC3mwiVqCoTydm8epJJkqOaF8rxDaYTmOG2bNC2IWKnKSjKcr2SGA2kUVsZDYFFXAZ1tVMWWLpui1bW0IJOlBnptJ7S9/lSWVQXyaZ%2BbmdOK50hNiW/v9tLzZ597Re2Sbxd9SkWVa9EjjZM30A5ZVZfOgQ5X1INhgdhURn5Sa7qmjmfSFZ5hVe53g/c9XPq%2B75dgl1ZacllOpcBuIZR2GOg1jPW7QVUb44NerHUeFqWYjNNKvTt1NWxrVsx10s2lz065SCAta6C/yAgbBzAvr9wAGJ4MQUz3NgqisChPx64bTvAhSZhJBEJpeFgH5xh2AD6ZY%2BhFf0gm7HveN7OpoARmDpMHt6Ow8AAq%2BYMAo/DECwSnyQ7Nx7UNTy8fTABaCSoIMxDxVM6BgRE4JnmIfvRwsgg6nXpCF5rONgsLFHDY8ReQ9hmAV1XBA1yAdeYA3tBNwILcEG3ggdwP9oHILPei33ne3vTScAO7l9M8nM9XteCNP%2Baz83bSt7C7c70cG8m7DXy55vhMbm9pPozcE2v4WXWfwTgSi8OkEomB0Cen5KKb4FxQT0yEGAiBUCYFshhr2cyeVYSNjPpPC%2BM855p1vove%2By97gaFxKQXB49z71yvkQheS8CAd0oWvahF0J5T0ITfQwpC3APzYdgJ%2B2CnLdxNtAhQsD37yzQa6ZmpIfCxiEaCMCt0dSl3dBXDuw9tH3APkfdoNM1GMx1AA/sXcPImyTvyV078Fg2j9nJBIBAIB4IUCmJxdo3CSNFB3JB4CsiQN8WyXEqxn5O2donI4uFo7vhtnbcU799aRKBFYkBASUEhLsfAm4iDkFBNQVItkfsuAYLMoWbBbgaFcIIQw3hd8BHkKEQcDhfE8HcPqfPEhzCO5cFxK0mpdDL6Nwafwh%2BZgBkUksXlYBDxslwKOMCWRxSCClKalNWEGg%2Bkd0mSHNRKtdHTF4iYt8ZjMGALEek5OtjFlG3xG0RxziOhuNoSADxbAvE6myaU/xBSlBFNFKUsJETUkAmNiApOCALbxNtpCTkySwXguuTEzJhSFkyMhmigFPyzDlJ%2BpUkEODOHDJ4d0vhvSKFUKGfg%2BhozyWNIfv09hNLOn0uIRSshLD7h7OEevURoKYkYtydcFZQK8UKM2W4bZ9wuC7JOSAdRsJNGGLIItEe0wO4GIrsYxVpjYTmOUjMuCtxIW3PsY84cXilAvPcZ4zM3y5F%2BzMH8wJOKnW8vCc5Dg6xaCcH8LwPwHAtCkFQJwaplhrBqU2NsTsbseCkAIJoH16wADWARJCIg0AADjMGYFIKQuD%2BBzdmrggRAjSD9RwSQvAWASA0NsoNIaw0cF4AoEA2yk3Bp9aQOAsAYCIBAJsAg6QETkEoGgF4dAEhRBTJwVQ2aABsABaRdkh7jAGQMgWVmazC8EgYQEgeAa5yv4IIEQYh2BSBkIIRQKh1DdtILoOV%2B98zpE4DwX1/rA3JtDZwbMCJR2ulQFQe4C6V1ro3VundiI8UQA8FO%2BgldzBJC4KsXgXatDrAgEgSd6Rp1kAoBAPDBGQDACkC6mgbIEjtogLEX9sQIjtHjB%2B3gjHmDEHjNmWI2hMAOFY6QSd4VsK0BY4%2BrAsQvDADhLQWg7buC8CwFnIw4hxMWz444AAbvyX9mBVB8YRLsBNU8q0htoHgWI%2BZOMeCwL%2BsseA60KdINp4gsQglVmU8AczRhk3rCoAYYACgUR4EwPvUyQaE1nuEKIcQ16ot3rUL%2B59%2BhDDGGsNYfQFn22QHWKgOOuR5PLurl2UwkbLBmGbS5nkWBssQHWHYDTuQXAMHcJ4boegwgRFGNUcYcqSg5AELMPwfWsgDYYEsMYtQ%2BiNYEBXTobXChyoaw4AY0xhhdeWL12wa2ht6AWB0CbPXaj1ZjTsCQX6OABtIE23gLawNLtXeuzd26pCwfuBAXAh7kPxvQ4m3z6wECYDfOMOrpB02SCSIiFISQK0aEkGYSQi6G3%2BEXWkKtNbSB1tQ4iRdXBF3ZpSKWxd/hJBFuh4u67v6W1to7X97t2GB04aHYBsdRGSNIdnWwTg7QWCacCMupgsk2xcBSIiLgWb934CINVvQUWL2xekPFpQiXH26Bda%2Bpg76FMXauzdv9HAAMjoRPcED92IProzML0X4uNDvYQ/hpDfo3ZmF%2B5hntTP2cJHHcR1AiHxiW/I4W7ZVHwSW0oPRx97HmMCaj5x7jvH%2BNOaE1eETYmQ0SakzJuTAmlOpdU%2Bn9TK3tPyZDXpgz4IBMmd/eZyzzGbO7BDfZxzCaXNuaUB5vPj5fN8AC0FkLYXiYCblzFq9ivZAJYfSGtXKWfOlasJYTLsRau5fy/PTgRXx4lfS%2BVyrCRqs6Zy9NlbzgICuF23KzrlRJt6H680c/GRRvNEOysJbjQZstB2wt4bR/mhzef1t/bebAob/QA//Y7DYLYM7NDfQb9SnR9O7cDR7IXJ8EXMXLNd7T7aXJ3VDV3f7UgQHYHRIUHdHWtEAVILNSQQIfwFIctJIeHRHUnOA5tTgGnTtbvPtQdYdIDb3T3YgTnXYHnSDFgBQTTbdTTVAmMKYSXL7Y9WXWQeXUfG9eQZXSfHQMg0gDXLXT9GAy7H9eA/9FnYDUDVQIQkQsQiQtUK2eDX3B3BIbApIXA%2BnXtXDGwgjHg1wpDEAUQ8BP2cQlIP2SQtZEwxXOgUPWjCPENWPMTBNKI%2BPDTATZPQQVPX9DPaTMQbPJzXPFTBvRTQvLTHTR9MvZAQzSvC%2BUzXgGvKzeMevOzHkZvXgVvdzCETvHzJw/zJgQLYLULcLIfeQkfCQMfW9FQpLdQgwWfbfGwGvZfUNVfNOTgPYM%2BOfawCrW7KrY9A/UHZbZoZrVrYAjrFrMAm/R/XIe/W/XIQ41/foWbT/PYy49/P/Dba/JbG49rZ4xYR4o7c7CA2NL4qtXXKnTgMDUw0Q%2B4PwxEQIjAqXEgbAtDDDPAggrAIgi7DHOtfNREJIJIfwYtUnBtDEwIfHJg27Fg2wWnN3VYNNEASQfwKHMtQIBtbNSQQtLgXNMwCnKtJIPQ5g1tOnLDC7PdQk/XOE%2BndYFzbIZwSQIAA%3D)$Done$

## Links

- [source code](../../../../conceptrodon/varybivore/plume.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/plume.test.hpp)
