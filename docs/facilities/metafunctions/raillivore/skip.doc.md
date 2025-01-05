<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Raillivore::Skip`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#raillivore-skip">To Index</a></p>

## Description

`Raillivore::Skip` accepts an operation and sinks its *0*th layer to the bottom of the invocation order.

<pre><code>   <i>0</i>th Layer { <i>1</i>st Layer {...Last Layer {***}}}
-> <i>1</i>st Layer {...Last Layer { <i>0</i>th Layer {***}}}</code></pre>

## Type Signature

```Haskell
-- Skip to Mold
Skip
 :: template<template<auto...> class...> class... 
 -> typename...
 -> ...
 -> Commitment

-- Skip to Page
Skip
 :: template<template<auto...> class...> class... 
 -> auto...
 -> ...
 -> Commitment

-- Skip to Road
Skip
 :: template<template<auto...> class...> class... 
 -> template<typename...> class...
 -> ...
 -> Commitment

-- Skip to Rail
Skip
 :: template<template<auto...> class...> class... 
 -> template<auto...> class...
 -> ...
 -> Commitment

-- Skip to Flow
Skip
 :: template<template<auto...> class...> class... 
 -> template<template<typename...> class...> class...
 -> ...
 -> Commitment

-- Skip to Sail
Skip
 :: template<template<auto...> class...> class... 
 -> template<template<auto...> class...> class...
 -> ...
 -> Commitment

-- Skip to Snow
Skip
 :: template<template<auto...> class...> class... 
 -> template<template<template<typename...> class...> class...> class...
 -> ...
 -> Commitment

-- Skip to Hail
Skip
 :: template<template<auto...> class...> class... 
 -> template<template<template<auto...> class...> class...> class...
 -> ...
 -> Commitment

-- Skip to Cool
Skip
 :: template<template<auto...> class...> class... 
 -> template<template<template<template<typename...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Skip to Calm
Skip
 :: template<template<auto...> class...> class... 
 -> template<template<template<template<auto...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Skip to Grit
Skip
 :: template<template<auto...> class...> class... 
 -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Skip to Will
Skip
 :: template<template<auto...> class...> class... 
 -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Skip to Glow
Skip
 :: template<template<auto...> class...> class... 
 -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Skip to Dawn
Skip
 :: template<template<auto...> class...> class... 
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
template<template<template<auto...> class...> class>
struct Skip
{
    struct Commit
    {
        template<template<auto...> class...>
        alias Rail = INITIATION;
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
template<template<auto...> class...>
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
using SupposedResult = Operation<std::index_sequence>
::Mold<void>
::Page<0>;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Skip<Operation>::Mold<Args...>;

/**** Result ****/
using Result = Metafunction<void>::Page<0>::Commit::Rail<std::index_sequence>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The implementation of `Skip` relies on a helper function called `LoadSkip` to keep a record of user inputs.
The record will be passed to `Omennivore::Press` to invoke the previously provided operation.

We will implement `Skip` by performing recursion manually, meaning the function will recurse only once for every invocation of a member template.
We will showcase a simplified version that handles `Mold` and `Page`.

```C++
// We will use `Items` to keep track of user inputs.
template<template<template<auto...> class...> class Operation, typename...Items>
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
        template<template<auto...> class...Sequences>
// When finally initiating the operation, we invoke the skipped layer.
// Then, we pass the instantiated operation and user inputs
// to Omennivore::Press for further invocations.
        using Rail = Omennivore::Press<Operation<Sequences...>>
        ::template Mold<Items...>;
    };

};

template<template<template<auto...> class...> class Operation>
struct Skip: public LoadSkip<Operation> {};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxBIAbFykAA6oCoRODB7evnrJqY4CQSHhLFExXPG2mPb5DEIETMQEmT5%2BCXaYDul1DQSFYZHRcW31jc3Zwz19xaVDAJS2qF7EyOwcAPQAVFvbO7t7G2smGgCCm9sA1AAimImujMh4mArnO4cnZ/ufu2/HR6c75zcTESCi89Be2x%2BBEwLESBmhJgAzG4CABPW7MNgAOhxSOwfwUBGIXgcgOBoPoSKsJz%2BHw25yECC8BAI4Nef2hsPhmCRQOZqBxWLxBKJJIIDKZLMpiOpv3eAIA8mwGAw8AA3EjsEDKYhPZ7sk6Yp6JJgrc5KxiqjW684mADsso5MLhTARyLRGNYmHNt2IrvSwpOhOJpJ1er%2B9tl52j505LrdKPRjC9gsDxxj52DYqumHqdFtDvtlypEfea3OFiYSnOoiUIFL6Zjce5fwzvNbGabzpb7qTRtTiOwNYMCmeHkETGC0VItPLABUENFvXhngJaKjzgJvSa/WxocRzibkABrc70KgEIUnTtNvspnHj6GCBQd6NpjNZ0nXPO0XmPychMQf6yIwBAKAO%2BKDq%2BBayms5YAOrLgwGrHt6BCLjWJC6goyQMPgRixt2rremwJTRJuVCxhhqC%2Bv6AizucADuhAIFR3qYKoRKmtC6CHqax5Xo2N5eKkBEet6SKXD60R0X4IDNsR5wALKeOgwGCKB4G4lBMq2teMZFiWNL6dGCkIiZtrItBGZmTyyJMPyEHDlWzxCJgACOXj3JgM4WRmDlEIKj6adB74xp%2B4rfpOv7Im5nneepT5gRBYVvg65wicEwCxkmllSQqtE1CA8lEdC5zKEwwB2W4wXPilumGTKDZwecABKHRLKkarerW7ANjZpU8hZ7Z%2BV2XLEby4n9tpQ7ICOY6yAB04MYhmY3A0inod6NDEISfG7rm5FHqeVDEKgLBsZuW27YJN6mXe2IPiBz6%2BUJnZTfeWIKtdL7DVBFkRTmP6JUtQHIrVyUzaQ5o/Slw2FqN0aZWJuWSeV2G/W9bZWWW5yrcEKFoRhaDENhuH4dltnnKRpQUZdNEyTUDHMehl0cVxDiYLxx2CS1C6MNDjHbi5l3YWC4oRPxsaoOjernPwB5UEs13nATqCiDU4HWXdH1sNJfpFSV41lSptBqeDz2Q0K/1YwZNstXIDAiVzfEns8DTerqyConNLsK/LyuLgeasa%2BkWuI%2BcxVU1FdC8t9Qdadb2BR0mRlvY1joWbZoU47bpmDbyAUCjNzmjgyHleQwKyvXd5xF0FlsKDXOsPZggrx9EmPY/iAOil%2BubRbycWVysiWaRB0MdzdM2hQjecZaJlOo4iUlhqOk2t/rslR4N5WVdVEOJ8KNu1zvxvejHMVuFPR%2BDintxp22drFk1w1ZwXvaeo9WLHMAuowiFE%2BMZkbZVNrxNGl9eS/3/sqK2eJ752UdM/NOEZkHGX%2BF8TBBoMFbHOAASS5AAicNQIRbB%2BHSLBXwfgrW9MxWgtAF4SViBoPBnIXzMOlucVCNxYx%2BhPHTZ2wcGCJGZOHY42d3QfxRFI%2BuJc5ouScvIsuBVGbpGhrrNuOJWEwhfDbQGARUBMHQEIY8eBEioNguWPBlETDMLAbYjQqtnjtE5ugaGgjVbCNEUxOgDCohcJuAQBiwQ662mYUCEEYIeQcMMNzAwKxeKujZnhOmDjtEsC1swhi/MGCC2FmXLa5x2Z3HAcw9J7DHGS34UQMJGgDFGJMWYhxr0WqMUnI4Ai/sWCak8SI5K0EJGJi/porE2B6CwN0T3N6IDlKqTyucepxjTHmORCog2aj8FsMFNDCJFJqpjKIXAnSkFM6nCsTY5hFUqoOKcWtaoXN3FKCEX054dC/HelQokIJuMQlMFqYyZkrJomONiYeeJLskmFNcKkspWyHHZMXLkpi%2BTnhQs4iU2p5SblVNPDUhxizGnmOYS08sbS0idJINTHpwQXm3TGvGaqsisQADUGh4CYBEegkzoIzKuRJFeCzDFLKaaswqGzynbIlIC6UbhWXEHZZyp49UTn9XCn3cUHgWAsEILPKMOspGDKZXiUuidh7eW5bjeCiL5bBDEOuTxaR/RiWomKgQeTPGE0ugoZZtxeIGFRNEXm85EXupNAUjCwRCSGEcMRXiDN1kCDrikjxNLREMRqRaFU6pNTFTXs8f2StGhBw9erWSYja4zNatFeZmarQ5u1BjOOrqGBDwrua5V2toxnwZbMs2vIJUz1funZBQ7UEv1OYMydMjHJyPmoo%2BaW8mZ6PVQyZZIBDxeE5XgZAgqGnLKbao%2Big4YIZ2apQ74tIATYFUKwOE3psEUModQmkZhETBDml4LAlk3BoCroEi1vxX3vu8F%2B3kzI6CEFRGmS9Fw1myVIQcJ059JrTsCrOhRM8gwrrg0zGk6UBkGtbnDN6gMdSoCIPY%2BGeqbyGpnUnTtmYV1kaIHyk9I7Tm11o2hn%2Bf9MCHIAxWxee8qrzOY6gPlUDeP8fqtRgs47VX52Q5/ZM39oF8YmalBeWVe3gIFWJ%2BxyI1PScHUg%2BT6C6QMi8IkXIXN2oUnFNgmZQgrM2fQHZ8WNbm28kJOgYqwQsCqAAPpKHin%2BtMxUDNuA1Hgc2Uzc3715BoY%2BpyLNKQHkrKuJDsGTqIziY4xBgAAZmWl%2BoGXOiJrRoSg9CaW13xAJF/LhWZNnouO52gDnIR/ErU8DzaMStMDK0uqLqAYvwO1Al5ESW6uau1QQYqVbY7Ih835vCHFgttrCzpFLAI5xPA62QkU/pkCBZctEAgEBlsgAUF6E7ui3BtYINDZz1mUi2Z6%2B1vEsw04cHmLQTgABWXgfgOBaFIKgTgbhrDWEzIsZYElX08FIHNkHP35jHhAP9yQWINAAA4zBmAAJwE64P93HOOuB2jtNIP7HBJC8BYBIDQGhSDA9B%2BDjgvAFAgGZ8jrQ8w4CwBgIgEAiwCB9PIJQNAsI6DRFCF6TgqgcexAALSxEkOcYAyAd1SCxGYXgXNCAkBi3ofgggRBiHYFIGQghFAqHUCj0gugEiMT9IkTgPBfsA6B5oXg7OFTMj6XTRXKu1ca61%2BcHXZhzgQE1YkGXB5zCIi4LMXgvOfukAgEgKXcf6BkAoBAbP8eQDACkGYPgdB9xc4gBEH3pAIi2uIKid3vB6/MEbwqCI2gOjI8R1L2BCoGDrlr1gCIXhgBAnoVz7gvAsAsEMMAcQDv8Be0cN1KfoOOIdWhM38gGkaeg9oHgCIfpG8eCwLXokeAGfT9IN1YgERXvXDn0YQ/RgffzCoAYQrzLHiMRUcDxHU3YQUQcQK3IA23NQWvJ3fQefFAKHSwfQI/LnSAeYGiTWTgZXHzSSUwSwawMwNnO/eVLAZAiAeYFxIqCAVwMYVoUgQIKcaYQYBIXINIAQagnIFIFghgKYAYMoSoaoLoEYJoTwFoPQcggQyYegng0QwQtgiYRobgsiMoMg2HFYCQT3DgQHFnWvdnc4YPVXdXTXbXLHKPCAXAQ3BPBHFPJHd/eYRcIxQYUg0gdHSQRELEAnREKnDQSQMwSQZhDQf7WIAnfQTgOnUgBnJPLEeIWIHHAncnWITHEndw2ILQh3dnTnbnawlHfnIXTPEXAPZkCXAvc6HPWXeXDgBoFgNUO0ZXP5eRAiLgAnLELgbHfXfAIgIgk3WQc3UA6QcApQSAh3XQMvF3YEZvdQzQ1nX3Tgf3MXZkIPJXfQ5yeoxo5oxxGPYo%2BPW0V9MwKwtPfnLPDY3PQowvXPFAAwIwBorgZnGgdrTuSgGvB3VvBoJvG/J49vTvbvHfPvUCAfIfJfTAUfcfO1KfRHWfefRfUHZfbvdUJ4WvTfZAZkVYRHYIaEffXgQ/Y/Z4s/VYUHS/a/RHO/B/JQJ/cErKd/PgL/BQH/TAP/DEHfIA7oy3Xo2QCA%2B3UHIYmAt/HAqwBAjEkg1Ar5MODArAlebkvAgg6IIg2ElAvg6E5wSgvCWQ2gvCBQmYJgjgmoJU5gmoVUxg2U8rWoGQ4Q8YfUmoboeQyQxQ6QnoJUqNC0ooKQ5PBYJYVQp0mnCY7QzgXQhY0POo7KBopo7HaPMw9orYpPXYmw0gOwrAGIRwmnUI8Ixorwu0f7AnSnREbw3wyQBISYsHTgdInnckgXYXUXcXfPE40otgTgCo0PDJNUHdNUAM7kQkVo8w43BIBkkApk63eQfotknQEAREUgEYt3afcY73VI6Y/I8UVASiVQWshQes84Rsxo5s8UdY6XXPMMxECMrIjPA4zc6ccsw4wYes6zQLFcwLNcwLec3oivO46vWvN4l4xHZ8jvLvBwL486fvQfF4yEgEsfCfWgEEmfGEcEnEmfPAFfGE9ffXVQLfJE3gFEqoWvDEk/VEbEi/eVfE3gQkx/MCl/Mkvcz/SqKk3/f/ekrorsiQZkm3PsqAwczk4weAmwPk%2BAAU9A9YZbMUywfA33QgmLaUxwsQ%2BUqg40mgugh0q09UvIdILUjU9IXU3gkSw0m08S0QqoOU1S%2B0/oaS2wI0rIGgu03oS0tU5Ql0y3cclItnL0286mRchsps4iPaUwtoylRPZPVPSM6Mhw9QhMkAQnLEREREf7UnbMpnYKu0aI6yqYjnWwDIvYtHEASQf7NwinO0JnHHSQYnLgPHMwZImnRECcmyuKxK4IjgPXGKvM0qyMu/VIZwSQIAA)

## Links

- [Example](../../../code/facilities/metafunctions/raillivore/skip/implementation.hpp)
- [Source code](../../../../conceptrodon/raillivore/skip.hpp)
- [Unit test](../../../../tests/unit/metafunctions/raillivore/skip.test.hpp)
