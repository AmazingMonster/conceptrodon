<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Roadrivore::Skip`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#roadrivore-skip">To Index</a></p>

## Description

`Roadrivore::Skip` accepts an operation and sinks its *0*th layer to the bottom of the invocation order.

<pre><code>   <i>0</i>th Layer { <i>1</i>st Layer {...Last Layer {***}}}
-> <i>1</i>st Layer {...Last Layer { <i>0</i>th Layer {***}}}</code></pre>

## Type Signature

```Haskell
-- Skip to Mold
Skip
 :: template<template<typename...> class...> class... 
 -> typename...
 -> ...
 -> Commitment

-- Skip to Page
Skip
 :: template<template<typename...> class...> class... 
 -> auto...
 -> ...
 -> Commitment

-- Skip to Road
Skip
 :: template<template<typename...> class...> class... 
 -> template<typename...> class...
 -> ...
 -> Commitment

-- Skip to Rail
Skip
 :: template<template<typename...> class...> class... 
 -> template<auto...> class...
 -> ...
 -> Commitment

-- Skip to Flow
Skip
 :: template<template<typename...> class...> class... 
 -> template<template<typename...> class...> class...
 -> ...
 -> Commitment

-- Skip to Sail
Skip
 :: template<template<typename...> class...> class... 
 -> template<template<auto...> class...> class...
 -> ...
 -> Commitment

-- Skip to Snow
Skip
 :: template<template<typename...> class...> class... 
 -> template<template<template<typename...> class...> class...> class...
 -> ...
 -> Commitment

-- Skip to Hail
Skip
 :: template<template<typename...> class...> class... 
 -> template<template<template<auto...> class...> class...> class...
 -> ...
 -> Commitment

-- Skip to Cool
Skip
 :: template<template<typename...> class...> class... 
 -> template<template<template<template<typename...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Skip to Calm
Skip
 :: template<template<typename...> class...> class... 
 -> template<template<template<template<auto...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Skip to Grit
Skip
 :: template<template<typename...> class...> class... 
 -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Skip to Will
Skip
 :: template<template<typename...> class...> class... 
 -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Skip to Glow
Skip
 :: template<template<typename...> class...> class... 
 -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Skip to Dawn
Skip
 :: template<template<typename...> class...> class... 
 -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment
```

```Haskell
Skip
 :: Commitment
 -> template<typename...>
```

## Structure

```C++
template<template<template<typename...> class...> class>
struct Skip
{
    struct Commit
    {
        template<template<typename...> class...>
        alias Road = INITIATION;
    };

    template<typename...>
    alias Mold = RECURSION;

    template<auto...>
    alias Page = RECURSION;

    template<template<typename...> class...>
    alias Road = RECURSION;

    template<template<auto...> class...>
    alias Rail = RECURSION;

    template<template<template<typename...> class...> class...>
    alias Flow = RECURSION;

    template<template<template<auto...> class...> class...>
    alias Sail = RECURSION;

    template<template<template<template<typename...> class...> class...> class...>
    alias Snow = RECURSION;

    template<template<template<template<auto...> class...> class...> class...>
    alias Hail = RECURSION;

    template<template<template<template<template<typename...> class...> class...> class...> class...>
    alias Cool = RECURSION;

    template<template<template<template<template<auto...> class...> class...> class...> class...>
    alias Calm = RECURSION;

    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
    alias Grit = RECURSION;

    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
    alias Will = RECURSION;

    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
    alias Glow = RECURSION;

    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
    alias Dawn = RECURSION;
};
```

## Examples

We will move the *0*th layer of `Operation` to the end of its invocation order.

```C++
/**** Operation ****/
template<template<typename...> class...>
struct Operation
{ 
    template<typename...>
    struct ProtoMold
    {
        template<auto...>
        struct ProtoPage {};

        template<auto...Agreements>
        using Page = ProtoPage<Agreements...>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

/**** SupposedResult ****/
using SupposedResult = Operation<std::tuple>
::Mold<void>
::Page<0>;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Skip<Operation>::Mold<Args...>;

/**** Result ****/
using Result = Metafunction<void>::Page<0>::Commit::Road<std::tuple>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The implementation of `Skip` relies on a helper function called `LoadSkip` to keep a record of user inputs.
The record will be passed to `Omennivore::Press` to invoke the previously provided operation.

We will implement `Skip` by performing recursion manually, meaning the function will recurse only once for every invocation of a member template.
We will showcase a simplified version that handles `Mold` and `Page`.

```C++
/**** Capsule ****/
template<typename...>
struct Capsule;

/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** LoadSkip ****/
// We will use `Items` to keep track of user inputs.
template<template<template<typename...> class...> class Operation, typename...Items>
struct LoadSkip
{
// If `Mold` is selected, user inputs will be kept
// in a `Capsule` and placed at the end of `Items.`
// Then, we pass the extended `Items` back to `LoadSkip`,
// waiting for more inputs.
    template<typename...Elements>
    using Mold = LoadSkip<Operation, Items..., Capsule<Elements...>>;

// If `Page` is selected, user inputs will be kept
// in a `Shuttle` and placed at the end of `Items.`
// Then, we pass the extended `Items` back to `LoadSkip`,
// waiting for more inputs.
    template<auto...Variables>
    using Page = LoadSkip<Operation, Items..., Shuttle<Variables...>>;

    struct Commit
    {
        template<template<typename...> class...Containers>
// When finally initiating the operation, we invoke the skipped layer.
// Then, we pass the instantiated operation and user inputs
// to Omennivore::Press for further invocations.
        using Road = Omennivore::Press<Operation<Containers...>>
        ::template Mold<Items...>;
    };

};

/**** Skip ****/
template<template<template<typename...> class...> class Operation>
struct Skip: public LoadSkip<Operation> {};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxBIAbGakAA6oCoRODB7evnrJqY4CQSHhLFExXPG2mPb5DEIETMQEmT5%2BXJXV6XUNBIVhkdFxCQr1jc3ZbcPdvcWlgwCUtqhexMjsHAD0AFTbO7t7%2B5vrJhoAgls7ANQAIpiJrozIeJgKF7tHp%2BcHX3vvJ8dnuwuAHk2AwGHgAG4kdggZTEZ4vN7/ZhsBSJJirYGg8FQ%2BEXEwAdisp3%2BBEwLESBjJJgAzG4CABPO4ozDAu7EJg1WnYf7DYheBwXOEI/6E4knC6Si5kilUzC0%2BlMxisTAAOnV3P%2BUoufIFBGumHqdHxRMJV1p4v%2B63WFwsTCUF1EShAotO2pllM58rdUoVWu1Uo9coVjOZKvVqu5joMCheHkETGC0VIVptABUENFWXgXgJaAyLgJWeiOWwycQLujkABrC70KgESM%2BgPSpUsiPxsmCBT%2ByWa5s6gj8wU3I20BWdxMhYgT2SMAgKCOamk8gdi1MXADq2YYUOrrIImcdJHhaIE%2BCM0vJnrJFzYJWihao0qPqHZnPSG4A7oQEC/WZgqhDhiZLoJWGLVk2EothcXipJeoasrSVxstEH7OCAQZehcACynjoLOgjzouGorha%2BJrgS5o0paA5YdSa50r2Ab0fKdJMF4RBLiu0b2i8QiYAAjl4DyYCmA7ahxXHqp2xHMf20GSrqI6Gom450gJwmiYRXYLtxPJkZRFiwfBwCtnc%2BI0ihQLvjUICYdecpCkwwBsW4sndvp5FmharpnDaABKmDIMsqQQqyTrsH57qOV68lMRJgaxdSdKIe2pHYLxsYXJOSZkBu246rcDTYYerI0MQwzgaWhqPlWtZUMQqAsP%2BhZlZVUEweZypsB2c7duJiksW24bqkC7U9oxq5Dcp%2BqjmpOlTtEOnEfppDAhNXlGcx2pwcEZmIZZKHCrGO2%2Bgl/lbjue4HkeaDEKeyQMBeB3Jay96lE%2BrVvmhXIfDaP6Hq1gHAQ4mBgfVUHWhcGaMOtX7FnxrWnl4tD6hEEHSqgQqni8/AVlQyztRcwRQqINSLmdLZpSqqEcnZDmytheG0ARdIeXpGVU5Z03Q3IDBweD4E1i8DSsvCyAMsg9BgfjFyE40mYVqTqDk%2BklOJZK9msQaY4KuNSskZGK7a0qvmUdRtFDax8VuNzNvsZxqD6Vl/FCSJDCrINXVSc7Mn9Qu3swTTvVjRN8XTdqs26wtGnu9p7MB0b3LrQb0TJ4ZQ3rprJn7d1R04yKqUjWwdPoX4jM3qyyguW5HMZwZkcwdrb0x3Q%2BubRlpt3ObWdUb32rMQ7iphqHqonMA8LknJme7aZuH4QX83t3SE9T6CnPG9g3dsZa/c0X5Pkkh8gJuEwiQKKjrJIqcw8h2qXOnNHZ8X1fvdWoCQgIJxBD0K8Oy/GHr7LaJxo5fx/vQd%2BJ9vgwJvgCS4ABJWU08Ew1H/tsX4nxYEwN%2BB/S4ARUBMHQEIaseBEjoMOAVVkP5aC0BMkhWIGgEEyh7IwrGFx9y3GlByGsX1BbKwYIkTiGsTh3zeiGcRxdR4Py3q7F20skY2V%2Bukda98IzMPJD2TO0cCFEJIWQ0Upp/oXAQc%2BEwjCWYETYTmIq1RwbrX4STQRwiLg0LoVEDhtwCAbmCBcJg%2BJGEv0vpAthhgIYGFWGBTkwNnpfXMUwlhkZGEblhgweGiNsplQuCDe4YF4kaJYKwjQFwMa8KIAEjQujiGkMSPEwa0MvyJkcJeOWLBoROKEXpIekiR49RkdgegG8tFN0lHtS8liC5VP0bUukSj6YqJMYk9U60glvzpAMlBm9lwGSttDUxFSa6uXiSTF4dhgqgQcUoARnSXhuJKayfciRvHGN8f4%2BJ4CCC/3lKE2JnpIl%2BP1Fk1wcTGEFMpsk4xqT0ngUyUeHJz0hb5JYcc0ptZynxKmTUup34ml51ae04INzOpJSZilM%2BTsIwADUGh4CYBEegwzmJjLMocpCVkLiYoMbM2yCywURnWh8r5CpqXEFpfS54XkyIH2PjNIceocrNRYIQeSRihoxVJW5O%2BJcZFRgUbGPqCY8qMuMZuTMDB5bBDEPmJxaQPwIVfDygQ0KVb7lagoGpdwwIGAZNEKG6YzXQvRLCnckxBC0tAoWR15qwn0OucIjc5SQSMBxNCeyJ08YkHlkTJWTiyblxEV1ZlFwAqELyeypNYJISpthLjfWUbFpGslSMgMLcNUL1ZgqPlXNpV90toffeuzP41IoYAnpYiNUhm1fImMDdXZly5NouVgppkgErF4eleBkActLdMutyiBBRnXAOvyWDsGUOgdsC42BVCsEpNfABeCz0YMPmYGkwRpZeCwJZekXg70KUfZsed6QR2kjHWOqdGU5GP1AUu/Uczy6GOMt0idUi%2BkgKjrBnGqAiCWJVeKLqQCKXQa6tHOE2HUCspNFYY9MqCM9OAeqNemBNnGrVVKItlHkJYaIKyhUTGWOSvw76Gjfw6LgekRGfjQyFJzzzhMrjZGcP4T45PZjQzBOGL7TKrBFwhC/tyODIKwT9RwKLXpxIBn0BGdRvqLj8GF1uGGOgbWv7IGZ3srhukUI8Bs2mmm2uCoNDLkHZcHCqlCaezQXArVEnGPEGAKxotYX6gRYcMBrju7uX7oYNyDzynV7xYblA%2BBl7rNoxA6cItZXbPsuS0wVLDnvO%2Bf80cukQWTYgA8CwJVBB7IlqIQqJzLm/1SpC5etMzwTMPqfvURwyAAD6fFogEAgENkACgVSLa0W4arAr9MpEM88Gz3I5i9w4AsWgnAACsvA/AcC0KQVAnA7aWGsDqJYKwkKvp4KQXr93zsLGrCAK7khVQaAABxmDMAATmh1wK7EPwdcAJASaQl2OCSF4CwCQGgNCkDuw9p7HBeAKBAHjv7WgFhwFgDARAIAlgEE6eQSgaAKR0GiKEFUnBVDg9iAAWliJIC4wBkBbqkKqMwvBwaEBID5vQ/BBAiDEOwKQMhBCKBUOof7pBdBtC/ByRInAeAXeu7dzQvAidAk4p0r6PP%2BeC%2BF6Li44uzAXAgF1xI7OKzmBpFwOYvAKfndIBAJArPPf0DIBQCAYevcgGAFIBINA0bp0oBEc3pAIiWuIAyI3vBM/MGz0CCI2hzm59IKzjeQIGD5nT1gCIXhgBn1oaT7gvAsAsEMMAcQ2v8AS0cOFFvD3ALBU4msH7wQyTo4e7QPAEQOTZ48FgdPQ48DY9b6QcKxAIgHZuB3owM%2BjDm4WFQAwCXKVPC/Eou7P2FfCFEOIVXt%2BNdqHT7r/QneUDWGsPoWfpPIALDfApk4D5yc2QlMFe0sDMEJ031FSwD/wgAWDOTS2cAgFcDGFaFIECCTBmAGDaFyDSAEHQJyBSAIIYGmH6DKHaHOU6BGCaE8BaD0CQJqC6EaHIIfEoMmFGHoPGFsFoLYNmD90WGWFWAkBNw4Bu3x3TyJwuDtwFyFxFzF1B1dwgFwBl292%2B391%2ByPwWEzCIQGAQNICB0kBpFVGhxpFRw0EkDMEkEYQ0Cu1iGh30E4Ex1IGx191VFiHKHB2hyR1iBB3hzMNiEkO1yJxJzJy0P%2Byp1pxD3p2t04mZ2j2anDw5y5w4AaBYAhAJD538QUUvC4Gh1VC4DByl3wCIFgPl1kCVwf2kCfyUBf2110ASH13PlzzEIkIJwt04Ct0Z04lt15zkN4jyIKKKOKXdySK93xFfTME0MDyp1D3GIjwSJjwjxQAMCMHyK4DxyT3LFJwgDT213zwaBz3X0OML2L1L3Xwr3nCrxrx70wHr0bytRbx%2B3b0727we172oIH3T2HxCjJDLwnyqHTxnznyOMXzWAexXzXx%2B0323yUF3zeP2iPz4FPwUHP0wEv2ZDL1vyqJVxqNkGfy1we0aPf0P3AKsEsB/wiHgIAKeXVmANAKsnJOsCgItxgJ82eHgEQKqGoJQLQO4IwKwKKAoOILyHSCILwJIJqH4NwKoOQNqFoIlLlOYL4OwJFImEVIFMYNVOFPYNEKEM%2B31PR3aKkM4BkP6Id1yLMnyMKLBzd1ULKMmN9xmO0NIF0KwBiAMPRxcLcIKMsIJCu2hxRxpCsJsMkDaA6Me04DCPJ2ROpzpwZyZyj2WJSLYE4HSId0KQhC3QhBtLlGGBKLULlzaBxPvzxLV3kDqKJJ0BABpFIGaMN1bzaLNxCK6LiP1FQGfFUEzIUGzIuFzIKPzP1DGLZwjydJpBdMiOD3mNHOTGTIWIGGzIs3mwHPmyHPm27JqLoB2NT3T1OOOJ%2B33KLxLwcDLyuMEBuOOI%2BPuIbyb1oGeLb3JDeIhLbzwD70hE5O11%2BNHwBKIin14BBPnwZHBOX1FWhN4FhJ3yfP3yRKnJPxcjRIvyv2xMqLLIkHxPVyrNf1rNJOMC/0pJBJpMezpIEBb3WCG2ZMgOgOiFgM5P/2VPSBcGeiVKFL6D1MlLFMIK1I4tIJlI4J5PlJYLoKyAwKYJoKmDVPYt4O6CVM4J6EkoEMQI%2BxEMEONJbMJzNM3LvF7JzLzK9CqhUNKMzR9z9wD1dPdP0LEJ9JABh1VBpBpCuwR3DNx3soJFiHB2CI0uJ1sHCNmMBxAEkCu1MORwJFx3B0kDhy4EhzMCCPRxpHUs6O8r8qcI4El08sSrMsiIWE31SGcEkCAA)$Done$

## Links

- [source code](../../../../conceptrodon/descend/roadrivore/skip.hpp)
- [unit test](../../../../tests/unit/metafunctions/roadrivore/skip.test.hpp)
