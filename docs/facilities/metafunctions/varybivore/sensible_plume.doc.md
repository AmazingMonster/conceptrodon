<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::SensiblePlume`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-sensible-plume">To Index</a></p>

## Description

`Varybivore::SensiblePlume` accepts a list of variables.
Its first layer accepts an operation and returns a function.
When invoked by sequences, the function places the variables into the sequences via a process similar to pack expansion;
then, it collects every packed sequence and instantiates the operation with the collection.

Check out **Examples** for more information.

<pre><code>   V
-> Oper
-> Transf<sub>0</sub>, Transf<sub>1</sub>, ..., Transf<sub>n</sub>
-> Oper&lt;Transf<sub>0</sub>&lt;V&gt;, Transf<sub>1</sub>&lt;V&gt;, ..., Transf<sub>n</sub>&lt;V&gt;&gt;</code></pre>

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> Oper
-> Transf
-> Oper&lt;Transf&lt;V<sub>0</sub>&gt;, Transf&lt;V<sub>1</sub>&gt;, ..., Transf&lt;V<sub>n</sub>&gt;&gt;</code></pre>

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> Oper
-> Transf<sub>0</sub>, Transf<sub>1</sub>, ..., Transf<sub>n</sub>
-> Oper&lt;Transf<sub>0</sub>&lt;V<sub>0</sub>&gt;, Transf<sub>1</sub>&lt;V<sub>1</sub>&gt;, ..., Transf<sub>n</sub>&lt;V<sub>n</sub>&gt;&gt;</code></pre>

## Type Signature

```Haskell
SensiblePlume
 :: auto... 
 -> template<typename...> class...
 -> template<template<auto...> class...>
```

## Structure

```C++
template<auto>
struct SensiblePlume
{
    template<template<typename...> class>
    alias Road
    {
        template<template<auto...> class...>
        alias Rail = RESULT;
    };
};
```

```C++
template<auto...>
struct SensiblePlume
{
    template<template<typename...> class>
    alias Road
    {
        template<template<auto...> class>
        alias Rail = RESULT;
    };
};
```

```C++
template<auto...>
struct SensiblePlume
{
    template<template<typename...> class>
    alias Road
    {
        template<template<auto...> class...>
        alias Rail = RESULT;
    };
};
```

## Examples

We will see three examples that present different use cases of `Varybivore::SensiblePlume`:

- We will pack `0` into `ZeroStar`, `OneStar` and `TwoStars`.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
template<auto I>
using ZeroStar = std::integral_constant<int, I>;

template<auto I>
using OneStar = std::integral_constant<int, I>*;

template<auto I>
using TwoStars = std::integral_constant<int, I>**;

template<typename...>
struct Operation;

using SupposedResult = Operation
<
    std::integral_constant<int, 0>,
    std::integral_constant<int, 0>*,
    std::integral_constant<int, 0>**
>;

using Result = SensiblePlume<0>
::Road<Operation>
::Rail<ZeroStar, OneStar, TwoStars>;

static_assert(std::same_as<Result, SupposedResult>);
```

- We will use `OneStar` to pack each of `0`, `1`, and `2`.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
using SupposedResult_1 = Operation
<
    std::integral_constant<int, 0>*,
    std::integral_constant<int, 1>*,
    std::integral_constant<int, 2>*
>;

using Result_1 = SensiblePlume<0, 1, 2>
::Road<Operation>
::Rail<OneStar>;

static_assert(std::same_as<Result_1, SupposedResult_1>);
```

- We will pack `0`, `1`, and `2` into `ZeroStar`, `OneStar`, and `TwoStars` separately.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
using SupposedResult_2 = Operation
<
    std::integral_constant<int, 0>,
    std::integral_constant<int, 1>*,
    std::integral_constant<int, 2>**
>;

using Result_2 = SensiblePlume<0, 1, 2>
::Road<Operation>
::Rail<ZeroStar, OneStar, TwoStars>;

static_assert(std::same_as<Result_2, SupposedResult_2>);
```

## Implementation

`Varybivore::SensiblePlume` separates cases according to the number of parameters.
The goal is to mimic the behavior of pack expansion in C++:

- If the user only provides one variable, we pack the variable in each sequence separately;

- If the user only provides one sequence, we use the sequence to pack each variable separately;

- Otherwise, the number of variables shall match the number of sequences.
We pack each variable into its corresponding sequence.

Here's the entire implementation:

```C++
template<auto...Variables> 
struct SensibleClassicPlume
{
    template<template<typename...> class Operation>
    struct ProtoRoad
    {
        // Multiple Variables
        // Multiple Sequences
        template<template<auto...> class...Cosmetics>
        struct Detail
        {
            using type = Operation
            <Cosmetics<Variables>...>;
        };

        // Multiple Variables
        // One Sequence
        template<template<auto...> class Cosmetic>
        struct Detail<Cosmetic>
        {
            using type = Operation
            <Cosmetic<Variables>...>;
        };

        template<template<auto...> class...Cosmetics>
        using Rail = Detail<Cosmetics...>::type;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};


template<auto Variable>
struct SensibleClassicPlume<Variable>
{
    template<template<typename...> class Operation>
    struct ProtoRoad
    {
        // One Variable
        // Multiple Sequences
        template<template<auto...> class...Cosmetics>
        using Rail = Operation
        <Cosmetics<Variable>...>;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxCCSAJykAA6oCoRODB7evnppGY4CoeFRLLHxXLaY9kUMQgRMxAQ5Pn6BdpgOWQ1NBCWRMXEJyQqNza15VWN9A2UVEgCUtqhexMjsHASYLCkG2yb%2BbkxeRAB0FwBqTXhM0fQKh9gA1CYaAIJjxF4Oz0KMGXumDcBgUGWQylymDe7xMAHYrB9nsjnttdvtoUc0XsmAcsQBPFKMViYC5nJ7PZCghTPADyROIuKyTxhKOeXx%2BBGeymIqCIACVUEx0KyUfDEe82WyAPTS54AWS8tEce0wz2uxFuQMeSKlyNlCqVKvof0wAEcvIwNjrJXrUTscXi3NiMYdjqdUGSKVSmGCyR4FGxHMhHv5sKK9RzfgARTCNOgRqXixN255eDJGVGEtWHaN0hlMgQpu1ugNBvAht0arUPJ5esOHCWp%2BHRxsw4v6uWK5V4VXqm53Wu6vUG2nhU0Wq3Q4dSl24zHOh2uo4nc4Xb3U55luMVlkztlRrmx%2BO0UvpcumBv7sUIjtS9NhYBZomvfx5%2BlxQsMO9ss%2BBneXm41aDpgobYPW4b%2BE2JZwq2UHtteyJzk6yELqunrrmGlLUv654AWBd4Ppm/JMHQr55sepGnkc27BgoEEgCABDZm2M4tqxsIzqhbrcQSRLMGwEHYb69EXO8wDEJgOyMAQBEzkRT6CsK5HcryApCiKRziZJ0mCKJ5INvBHzsUZnFmbx7pEP2mogXunwEN8vz/AwgL0CCIkVpCPgLsBQJ2cmXFLvOPFBSh2YCaSmEvD6YL5p%2BdR2QeDmcqpfKoEpIpsbeiHPKO46%2BfQd4Gt2xpqv8k4MNad4WRZ6FCTF%2Bm0RWcm2nqCnPCRZG5nFjIJTlf4XqGQEDn5YYQRxv6wRxiY1aFC7MfxJL1ThYkSVJbB6YlKLtRlKk8mlGVutp60yfpLKmSZEowtKABUd33Q90rXfdAAq2BCC991PR8t0PX931meY/hhFSXhYK%2BbhoJVmApLJ/kfLVHrPAAknZ7UAFpxKgvTECpYzoIxYTbBJYgAPpQzMghukTpAo%2BdV0I3NbroXTV7vO1Y6YDjeMEATIBE5gJO0OTAiUwQ1OCLTqNhjd02M%2BiwUrkj0vhh87UvQA7tj4w0t1%2BOE4IguMsLFONFTRw06z2B3XL7w1eFS1RTCh49V%2BtsGi9oFchoCHsxmT5CF4KQFJg6D8qBRoqR%2BvXMsZRyJvr/OG0LIsuWb4sW5Lzw%2B2GpAJ7zBvE8bqdixLBC0zn1t5zOicCynpuGBnbiW5XNtx5BDN%2B4%2BHUR8qKnOa5wLUp5UJupXMKMYdRzR27bOT1RbqY7yOO05zK/PJr2tNARF0fDMwakyJcQEBAicKCSh9DeHChGrTgfB%2BkofX0aTyLO7cqe2MzxcL77X3yHYde4EFJlwKOBY%2BqwnjjXAuSci5kwbubZuWdW7V1auyGBddi4IKbpbH%2BMtUFJT5pg%2BBot05l1pmYJ4st262x2kAkB/cAR4CBO5MEI9vJj1plUZ4lC54gCnm4GeCU%2BGdWooI8ION6a%2B33hWS%2BShminxgefNgl83TP2VCAu%2BQcAHqOAXg7Ab9d7vA9l7Hhv9/Z/G0Y/QBN8NFmDAfFWOkC3D5yIcnLBpDG7kOzk8AhKJa7uJIWnLxmdy7fyoX45EAS4Em08Ygy2vDrbUMgR3cx3ddGk3sd1AezC3LDwhKPI4GguEULspPDSbohHMhEQvI4S8t5kDpBI8YtNN44x3p3GRyA5HH0UXzZRmBVFHAyWYLRD8lA2KNJk1%2BjYODLFoJwAArLwPwHAtCkFQJwFxlhrDslWOsHMZh/A8FIAQTQczlgAGsQCLMkGcDQkguBwn8BoRZGgzAADYPlmAABw/P0JwSQvAWASA0MU1Z6zNkcF4AoEAxSzlrLmaQOAsAYCIBAKsAgKRTjkEoGgXYdA4gRBJJwVQPyPkAFoPmSGeMAZAyBv53LMLwUOhASB4AJlUfgggRBiHYFIGQghFAqHUIi0gugqga0ZCkTgPB5lLJWecjZnBaSnGxVyVAVBnhkspdS2l9LGVnHsRADwBL6C4yBlwRYvAEVaGWBAJA%2BKUiErIBQCATqXUgGAFIUZNBlRxFhRAaISrohhCaPiWVvBQ3MGIPiWk0RtBdARSc/FG0CBjloBGsVWBoheGAMcWgtBYXcF4FgFghhgDiGzXgSS3QABuoElWYFUF0U4mwTkCwWWK2gzDGSxo8FgJVDk8AgpLaQBtxBoiP1jOWowPajDnOWFQAwwAFCXDwJgDWH5VknO5cIUQ4gBV7uFWoJVEr9AVpQNYaw%2BhmGwsgMsVAsMsjFopfjXMpgdmWDMJCidmosD3ogMsTo3RnAQFcJMPwVQQhhEGOUYYVQCiZAEJB/I6RkMMDmEMSo1Rag9HGC0TwbQ9AgbqDjfosH5gIdsAR1D0wCNYfg5UYD%2ByNhLABRwZZpAIW8Chdq8lVKaV0oZVII1zwIC4DZRao5VqbWLuWAgTAwphhAdINcyQ/gziJH8HCSQDyzCSA%2BWCxZHzkhdqBaQEFxyzgfK4B8n5iQfl2duVwRZ2mPncaVVCmFcLTmLuRWih1GK1U4rdR681xK2CcCaCwOtcIKVMGEpmLgiQzhcHuSy/ARB/16D3byw90hj1KFPWK3QoypVMBlSW%2BVnHFViqhaqrFpxniaueDFuLCWktPhS2l%2B54nTXOvNa8I5ZhrV%2BcRfax1qAzVxFxe66bg3hjtfiz6IwKWuDFL9dsYggbg1iujeGyNpADuxvjYmhwR3U0yQzVm9ZOa80FqLUdstFaq13ZrUmvADbi3rOba27YR3O1Kp7dEPt%2BIB2bHWcO0dJyJ1TqUDO17j5/PLqYKu9dm7t1Hbywe/lhXZAntFessrF6F2fqsJYW90RAOPufaLTgb7eYfuvd%2B39cR/2Nofbhz7YGINEamEEBg6BGMLEQ%2BhuodHUji6yCL6jpH8N9El/LgQ5HZc4ZmBMfnUGaOzEo9h9jChWP8pq1xnjyqOBteILF%2BLiXVvddS%2BljQ4nJPZeG8csbtqLmkEU8p%2BIqnzPAoCKlh5cI3NwmeZIAz1Kqhm%2B87YXznv7WBaQJi9Vc3wtEpJRwGLeqWAKDrQyutPWMRjEy1JjluXZD5bx4K%2BQxWic6ACKQCrVW5UcdN15lVIWNVapzzSvPBfnhF9SyXrkJqFsurd/4D3/mgsZ9dXiif5qQAF%2BDqTYfpNR%2BHyt9SvgdBtu7ZDWG2NR2TtxoTUmy702003aVfd/NYgntjpe3OyHpaPv1sbWKv7yA22A8Nl2usiDmDhDkOpqDDrwHDtOjsEjguhNnwCumuhuluvxNjlXrjhIPjkKvXmek3gYGTizjYCDjThsnTi5JwNKPrOTtYD%2Brxn%2Bhypzqpsrn4OBkLpLjBqUPrmLoUFkJLkhnUGriRjUDzvULRlrkIXhirgxnrkxiRmIbkNrhrhRpwbIVaisGsGxmoV2h3vVpwJbiwLnvnoXsXvOF/BJlliQG7rJuNnagpkplgH7jVhZiCmYKlv4P4Ism8o8mCu4XCPZp5rodCvHvCvJmpgkIslposj8p8okEkM8jplwIEF2v4HVpCpwHJhNjVsygEWkUEYnssBOhkM4JIEAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/varybivore/sensible__plume.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/sensible__plume.test.hpp)
