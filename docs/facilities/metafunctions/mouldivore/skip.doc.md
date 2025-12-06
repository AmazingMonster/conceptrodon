<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::Skip`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-skip">To Index</a></p>

## Description

`Mouldivore::Skip` accepts an operation and sinks its *0*th layer to the bottom of the invocation order.

<pre><code>   <i>0</i>th Layer { <i>1</i>st Layer {...Last Layer {***}}}
-> <i>1</i>st Layer {...Last Layer { <i>0</i>th Layer {***}}}</code></pre>

## Type Signature

```Haskell
-- Skip to Mold
Skip
 :: template<typename...> class... 
 -> typename...
 -> ...
 -> Commitment

-- Skip to Page
Skip
 :: template<typename...> class... 
 -> auto...
 -> ...
 -> Commitment

-- Skip to Road
Skip
 :: template<typename...> class... 
 -> template<typename...> class...
 -> ...
 -> Commitment

-- Skip to Rail
Skip
 :: template<typename...> class... 
 -> template<auto...> class...
 -> ...
 -> Commitment

-- Skip to Flow
Skip
 :: template<typename...> class... 
 -> template<template<typename...> class...> class...
 -> ...
 -> Commitment

-- Skip to Sail
Skip
 :: template<typename...> class... 
 -> template<template<auto...> class...> class...
 -> ...
 -> Commitment

-- Skip to Snow
Skip
 :: template<typename...> class... 
 -> template<template<template<typename...> class...> class...> class...
 -> ...
 -> Commitment

-- Skip to Hail
Skip
 :: template<typename...> class... 
 -> template<template<template<auto...> class...> class...> class...
 -> ...
 -> Commitment

-- Skip to Cool
Skip
 :: template<typename...> class... 
 -> template<template<template<template<typename...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Skip to Calm
Skip
 :: template<typename...> class... 
 -> template<template<template<template<auto...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Skip to Grit
Skip
 :: template<typename...> class... 
 -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Skip to Will
Skip
 :: template<typename...> class... 
 -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Skip to Glow
Skip
 :: template<typename...> class... 
 -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Skip to Dawn
Skip
 :: template<typename...> class... 
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
template<template<typename...> class>
struct Skip
{
    struct Commit
    {
        template<typename...>
        alias Mold = INITIATION;
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
template<typename...>
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
using SupposedResult = Operation<int>
::Mold<void>
::Page<0>;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Skip<Operation>::Mold<Args...>;

/**** Result ****/
using Result = Metafunction<void>::Page<0>::Commit::Mold<int>;

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
```

```C++
/**** LoadSkip ****/
// We will use `Items` to keep track of user inputs.
template<template<typename...> class Operation, typename...Items>
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
        template<typename...Elements>
        // When finally initiating the operation, we invoke the skipped layer.
        // Then, we pass the instantiated operation and user inputs
        // to Omennivore::Press for further invocations.
        using Mold = Omennivore::Press<Operation<Elements...>>
        ::template Mold<Items...>;
    };
};

/**** Skip ****/
template<template<typename...> class Operation>
struct Skip: public LoadSkip<Operation> {};
```

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/skip/implementation.hpp)
- [Source code](../../../../conceptrodon/mouldivore/skip.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/skip.test.hpp)
