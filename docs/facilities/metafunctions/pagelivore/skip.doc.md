<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::Skip`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-skip">To Index</a></p>

## Description

`Pagelivore::Skip` accepts an operation and sinks its *0*th layer to the bottom of the invocation order.

<pre><code>   <i>0</i>th Layer { <i>1</i>st Layer {...Last Layer {***}}}
-> <i>1</i>st Layer {...Last Layer { <i>0</i>th Layer {***}}}</code></pre>

## Type Signature

```Haskell
-- Skip to Mold
Skip
 :: template<auto...> class... 
 -> typename...
 -> ...
 -> Commitment

-- Skip to Page
Skip
 :: template<auto...> class... 
 -> auto...
 -> ...
 -> Commitment

-- Skip to Road
Skip
 :: template<auto...> class... 
 -> template<typename...> class...
 -> ...
 -> Commitment

-- Skip to Rail
Skip
 :: template<auto...> class... 
 -> template<auto...> class...
 -> ...
 -> Commitment

-- Skip to Flow
Skip
 :: template<auto...> class... 
 -> template<template<typename...> class...> class...
 -> ...
 -> Commitment

-- Skip to Sail
Skip
 :: template<auto...> class... 
 -> template<template<auto...> class...> class...
 -> ...
 -> Commitment

-- Skip to Snow
Skip
 :: template<auto...> class... 
 -> template<template<template<typename...> class...> class...> class...
 -> ...
 -> Commitment

-- Skip to Hail
Skip
 :: template<auto...> class... 
 -> template<template<template<auto...> class...> class...> class...
 -> ...
 -> Commitment

-- Skip to Cool
Skip
 :: template<auto...> class... 
 -> template<template<template<template<typename...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Skip to Calm
Skip
 :: template<auto...> class... 
 -> template<template<template<template<auto...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Skip to Grit
Skip
 :: template<auto...> class... 
 -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Skip to Will
Skip
 :: template<auto...> class... 
 -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Skip to Glow
Skip
 :: template<auto...> class... 
 -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Skip to Dawn
Skip
 :: template<auto...> class... 
 -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment
```

```Haskell
Skip'
 :: Commitment
 -> template<typename...>
```

## Structure

```C++
template<template<auto...> class>
struct Skip
{
    struct Commit
    {
        template<auto...>
        alias Page = INITIATION;
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
template<auto...>
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
using SupposedResult = Operation<-1>
::Mold<void>
::Page<0>;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Skip<Operation>::Mold<Args...>;

/**** Result ****/
using Result = Metafunction<void>::Page<0>::Commit::Page<-1>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The implementation of `Skip` relies on a helper function called `LoadSkip` to keep a record of user inputs.
The record will be passed to `Omennivore::Press` to invoke the previously provided operation.

We will implement `Skip` by performing recursion manually, meaning the function will recurse only once for every invocation of a member template.
We will showcase a simplified version that handles `Mold` and `Page`.

```C++
template<typename...>
struct Capsule;

template<auto...>
struct Shuttle;

// We will use `Items` to keep track of user inputs.
template<template<auto...> class Operation, typename...Items>
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
        template<auto...Variables>
// When finally initiating the operation, we invoke the skipped layer.
// Then, we pass the instantiated operation and user inputs
// to Omennivore::Press for further invocations.
        using Page = Press<Operation<Variables...>>
        ::template Mold<Items...>;
    };

};

template<template<auto...> class Operation>
struct Skip: public LoadSkip<Operation> {};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEEgBsXKQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJXCm2mPalDEIETMQEeT5%2BQfWNOS1tBOXRcQnJqQqt7Z0FPZODw5XV4wCUtqhexMjsHAD0AFSHR8cnp/u7JhoAggdHANQAIphprozIeJgKd8cX17dnAJOvyulxuxzuAHk2AwGHgAG4kdggZTET5fH6g5hsBRpJjbSHQ2EI1F3EwAdis11BBEwLDSBhpJkCbgIAE8XljMJCXsQmE0mdhQZNiF4HHcUWjQeTKVc7nK7jS6QzMEyWezGKxMAA6HUC0Hyu7C0UER6YVp0UkU8kPJky0G7XZ3CxMJR3URKEBS64GxX0vkq73y1X6g3y33K1VsjmanVagVugwKL4eQRMCIJUj2x0AFQQCS5eC%2BAlorLuAi5uN5bBpxDuuOQAGs7vQqAQ44HQwr1ZzYymaYIFCG5XqO4aCCKxU9zbRVX205FiLPZIwCApY3rAoLR9Ks3cAOoFhgIhtcgh5t0kVE4gT4IwK2l%2Bml3NhVBJlqgK8%2BoHl8nK7gDuhAIJ%2BXKYKo454jS6B1niDbtrKnZ3F4WR3lGXJMg83IJL%2BzggOG/p3AAsp46BLoIK5rrqm62qS25kjagR2qO%2BGMtuzJDqGLEqsyTBeEQ66bgmLpfEImAAI5eG8mCZqOBq8fxOp9hRHEjghcpGpOZppjOzKiRJUlkf2q4CYK1F0RYSEocAXYvKSgSYRCP5NCAeEPsq4pMMA3FuEpA4mTR1q2l6NyOgASpgyCbFkcJcu67DBT6bn%2Bip7GyWGSWMsyaE9lR2BCUmdxzumZC7gehrPG0BFnlyNDEJMMFVmab71k2VDEKgLAgWW1V1fBiE2RqbC9suA4yWpnHdjGOoQj1g5sVu40aSaU7aYZ84JIZFEmaQkKzf55kcQayERNZaF2ZhEpJodQapSF%2B6Hsep7nmgxBXhkDC3qdGVci%2B1Tvl137YfyfyOoBZ5dWBEEOJg0EtfBDp3LmjA7f%2BFbCV1V5eLQJqxLBCqoOKV5fPwtZUJsPV3BECKiE0a7XZ22WalhvLOa5SoEcRtCkcyvnGbl9N2QtCNyAwyEwzBjZfG0XKosgrLIPQ0Ek3cZPtHmtZU6gNM5HTaVyi5XGmtOqozerlFxpuBvqkFdEMUx41cSlbgC47PF8agJn5SJ4mSQw2xjf18ke4pI2rgHiGM0N02zSlC0GktRurbpPsGTzofmwKO2mwkGdmeNO565ZJ0DedhOSllk1sMzOF%2BGzj5csonnebzuemXHiEG99id0Cbe25VbLw2/n9FDwaHGu2q0ZR1qVzAKitLKXnR1WURJGlytPfMrP8/QnzFvYAP3F2iPjHBYFVJ/OCbhMGkChY1yGLXBPkfavz1wJ9ft/30P9rgkICB8QIPQb4RxgQTyDvtK4Cd/6APoD/S%2BgJEGPzBPcAAkkqBeqYmggMOMCf4SDEHAl/vcUIqAmDoCEA2PAaQcHnFKlyQCtBaCWXQkkDQqDFSDjYfjO4J5ngKl5I2f6YsNYMDSHxXWVxn7fVVBA3KXtq5NB2i/WMHDaSDjzgnUh5DKHUKlFaEGdxUEfhMGwzmpFuGFnKo0GGO0RGUzERIu4jDmHxF4c8Agu4Ih3CYKSNhn875wO4YYWGBhtjQT5BDD6/1THsM4XGNhu4kYMBRmjAq1U7iQ1eNBWJaiWBcI0HcXGQiiB%2BI0NoihVC0ixLGgjf8aZHB3mViwREDjxHGXHjIiuU9X5amwPQXeGj25ymOnecxpcKm6OqcyRyQMcg7TyebHaATv7Mn6ZgveG5TL2wRsYspjcvKxMpl8OwEUoJ2KUKI9pXwXFFK5CeNInjDHeN8bEmBBAgEqmCdEv04SfEmgya4GJbDFkJI0EkvMKTnFpK%2BIC8C2SymLKOcUpspTYmTKqTUgCDTi7NNaREa5fV0rs0ytfd2sYABqbQ8BMFiPQIZHFRnWQOeheydwMV6JmU5eZRj4k6h2u8z5qoqXEBpXSz4/lqKnwvotccxpCodRYIQFSBjxqJRJd5ORWoRVivpapBGe5IUqwiGIEsDjsi/lQl%2BblAhUkOMel1BQVSXjQQMKyBI8McyQrtbidJ54IjzEEDSqCZYbUMB8dE%2BxBKJG7lKVCRgRJEQuUusTEgKtybq3tVrGukj%2BpMo8l5Uu8aYTwiTciImJsw3CupbS%2Blkrhmhk7hq1eXNVSgv5tK4edsz4nx2X/KptCwFdJZMOrV8YFbo1mSzP8mi5ViimSAOsXg6V4GQOyshlTOVuCnTXeMO5e3BXwQQuhCDDh3GwKoVg9IH6gOIce3BZ8zCBAiArLwWA7JuDQH7DxDKZX4MUTkQd1JR3krflAudJod3AxBBSWiDth0qLA/HCDhNUBEHMSqmU/VwGgf3gLBOKI0OoBZZaKwB6ZXYZAwpGec9MAbN/Wq%2BU%2BaSMYVQ0QFlqpt50cGZKrDQZyMgmYghyuvSuP0dUsvYu4zWOEfQyRTjtH6O8f0d2v9f8vBpGKDDcKgSTTIPzUIDTWn0A6axiaVjUGZ1uAALRcFUi5DDzIER4G5gtZNTdVTgqlX2%2B4hEtJkz9tg5Bz8ROxiuMQYADH81%2BdaAFhwgHWNTMrXMgQAoHPya3hF1u8CUFntM9jID1x835fM2ymLTA4v8ic6gFzaXkQeeZF5g%2BIAPAsCVQQdzhzmS2Y3D5s92ZPh6dve/VojhkAAH1hIJAIBASY6AXIKE1JNjRbgSsCqM5kbTnwzMChWLaDgaxaCcH8LwPwHAtCkFQJwZ2lhrCGg2FsdCT6eCkA6%2Bdg7awGwBEkFqDQAAOMwZgACcQOuD%2BH%2B39rgZIyTSCOxwSQvAWASA0BoUgZ2LtXY4LwBQIBUdva0GsOAsAYCIBABsAg7TyCUDQHSOgCQoiak4KoP7SRrNJEkHcYAyA11SC1GYXgMNCAkBc3ofgggRBiHYFIGQghFAqHUO90guhUj/l5GkTgPBDvHdO5oXgmOIR8Xaf9ZnrP2ec%2B53cXnZg7gQFa2kOntZzCBC4CsXg%2BODukAgEgGn9v6BkAoBAH3DuQDACkGYPgdAaw44gLEXXpBYgmuIKyDXvAE/MCTxCWI2gzkp9IDT3eEIGAljj1gWIXhgDXyYTj7gvAsAsEMMAcQiv8Cy0cDFavF2wIRT4jsF7EQaRw4u7QPAsReRJ48FgOP448BI5r6QGKxBYibaePXoww%2BjC67WFQAwkWKUfH/LMs7L2xfCFEOIaXJ%2B5dqDj8r/QDeUDWGsPoEfOPIBrG/LTTg1m5sYVMLdywZgGOC%2BoqWAr%2BEAawpy8WzgEArgMwfgqQYQ6YSwYwqQxQ2QAgcBegaBTQiwowNQvQZy/QUwHQngXQegkBTQAw7QuBr4%2BB8w0wpBBQEwxBNBywLu6wmw2wEgWuHAJ2aOcemOdwJubOHOXOPOP21uEAuAQujuz2rur2m%2BaweY5CYw4BpAX2kggQWoQOgQMOGgkgZgkgbCGg/gSQQO%2BgnACOpASOzuWoKQSQf2QOkOSQ/gkgYOOhSQ/BiumO2OuOCh72hOJOXuZOhufEVOgeHUvu9OjOHAbQLAcIZI1mviE6d4XAQOWoXAv2Au%2BARAIBousgEu5%2B0gl%2BSg1%2Biuug4equN8KePBfB6OeunABuFOfExuLOIhQkqR6RmRhStukRDupIT6Zg8h7uhO3ufRfu4RQefuKABgRgaRXAqONA2MOclAseiuaebQyec%2BGxGeWeOec%2B%2BeK4hexezemAZeFepq1eL2deDeTeF2LehB7eceXekUNIue/eDQcew%2Bo%2BmxE%2BOwF20%2Bs%2BL2C%2BS%2BSgK%2BtxJ0m%2BfAO%2BCge%2BmAB%2BHIueJ%2BhRUuxRsgV%2BCuF2FRd%2BG%2Bf%2BVglgz%2BsQYB7%2BjyOsX%2BP%2B9keJ1ggBeuwBLmnw8AEBDQhB0BsBjB8BIQH0rBKB6QmQ6BuQ7JWBfJOBSBeB5BzJUBzQxBmBEwEplBLBoptB5B0pgpzBCwipbBEBD2XB7BcOdRAhnAQhbRZuKR1kaRGRv2Nu0huRAxzuwxihpAyhWAiQahcOVhNh6R%2BhZI/gQO0OgQBhRhbhXhGOnAvheOUJROpO5OlOAeUx0RbAnAcRZu%2BScIa6cI5pyokw2RMhIuqQyJZ%2BqJMu8gpRmJOgIAwQVR6uNetROu3hjRoRJoqAH4qgyZCgqZdw6Z6RmZJovRtOfutpgQ9pARnuYxfZGYsZ4xYwqZmm42nZ423Z42LZxRkeKxMeceOxWxL2G5me2eDguehxggxxWx9xZx5eletAVxtetItx/xteeAre8IDJiuLxPe7x5Eg%2BvA3xY%2BrIfxU%2BoqQJvAIJy%2B15a%2BkJw52%2BnksJ%2B%2Bh%2BSJBRBZEgaJsuJZN%2B5ZOJxgj%2BBJ3xxJl2pJAg1euwc2D%2B/%2BFgNJl2dJoBjJBBkpLgH0MpnJ6A3J%2BB2BOQdFzFZQGpPJFBRBgwdFXFAgVBQwHFdBKp%2BQHJ9BglFQYp7BCg2pUuNZwZDRHAQhrZ7ZnZWo3ZVpORaaTuLubuDpTpqhPB7pIAwOWogQgQ/g4ObhKO5lZIDhCll2oZtgfhIxn2IAkg/g2hUOZIKOf2kgoOXAAOZgnhcOgQtZIZWO/hBOPB/ODlPhUVH28%2BOcOQ7lQAA%3D%3D%3D)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/skip/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/pagelivore/skip.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/skip.test.hpp)
