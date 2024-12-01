<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::ClassicTrip`

<p style='text-align: right;'><a href="../../../index.md#higher-order-modifications-2">To Index</a></p>

## Description

`Pagelivore::ClassicTrip` accepts an operation.
Its first layer accepts another operation for composition.
Then, it returns two commitment functions and twelve continuation functions.

- **Commitment**
  - **Conjuration:** When invoked, this function instantiates the first operation with the arguments and then the second operation with the corresponding member of the result.
  - **Transition:** When invoked by a vessel, this function transports the conjuration function to the vessel.

- **Continuation**

  When invoked by another operation, the function returns a `ClassicTrip`
  - that is instantiated by the conjuration function and
  - whose first layer is instantiated by the new operation.

In general, this function composes operations together in a similar fashion to `.` in Haskell.

<pre><code>   Operation<sub>0</sub>
-> Operation<sub>1</sub>
       &vellip;
-> Operation<sub>n-1</sub>
-> Operation<sub>n</sub>
-> Arguments...
-> Operation<sub>n</sub>&lt;
   Operation<sub>n-1</sub>&lt;
       &vellip;
   Operation<sub>1</sub>&lt;
   Operation<sub>0</sub>&lt;
       Arguments...
   >::Member
   >::Member
       &vellip;
   >::Member
   ></code></pre>

## Type Signature

This function has multiple signatures.

```Haskell
-- End in Conjuration
-- Compose with Mold
ClassicTrip ::   template<auto...> class...
       -> template<typename...> class...
       -> ...
       -> template<auto...> class

-- Compose with Page
ClassicTrip ::   template<auto...> class...
       -> template<auto...> class...
       -> ...
       -> template<auto...> class

-- Compose with Road
ClassicTrip ::   template<auto...> class...
       -> template<template<typename...> class...> class...
       -> ...
       -> template<auto...> class

-- Compose with Rail
ClassicTrip ::   template<auto...> class...
       -> template<template<auto...> class...> class...
       -> ...
       -> template<auto...> class

-- Compose with Flow
ClassicTrip ::   template<auto...> class...
       -> template<template<template<typename...> class...> class...> class...
       -> ...
       -> template<auto...> class

-- Compose with Sail
ClassicTrip ::   template<auto...> class...
       -> template<template<template<auto...> class...> class...> class...
       -> ...
       -> template<auto...> class

-- Compose with Snow
ClassicTrip ::   template<auto...> class...
       -> template<template<template<template<typename...> class...> class...> class...> class...
       -> ...
       -> template<auto...> class

-- Compose with Hail
ClassicTrip ::   template<auto...> class...
       -> template<template<template<template<auto...> class...> class...> class...> class...
       -> ...
       -> template<auto...> class

-- Compose with Cool
ClassicTrip ::   template<auto...> class...
       -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
       -> ...
       -> template<auto...> class

-- Compose with Calm
ClassicTrip ::   template<auto...> class...
       -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
       -> ...
       -> template<auto...> class

-- Compose with Grit
ClassicTrip ::   template<auto...> class...
       -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
       -> ...
       -> template<auto...> class

-- Compose with Will
ClassicTrip ::   template<auto...> class...
       -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
       -> ...
       -> template<auto...> class

-- End in Transition
-- Compose with Mold
ClassicTrip ::   template<auto...> class...
       -> template<typename...> class...
       -> ...
       -> template<template<template<auto...> class...> class...>

-- Compose with Page
ClassicTrip ::   template<auto...> class...
       -> template<auto...> class...
       -> ...
       -> template<template<template<auto...> class...> class...>

-- Compose with Road
ClassicTrip ::   template<auto...> class...
       -> template<template<typename...> class...> class...
       -> ...
       -> template<template<template<auto...> class...> class...>

-- Compose with Rail
ClassicTrip ::   template<auto...> class...
       -> template<template<auto...> class...> class...
       -> ...
       -> template<template<template<auto...> class...> class...>

-- Compose with Flow
ClassicTrip ::   template<auto...> class...
       -> template<template<template<typename...> class...> class...> class...
       -> ...
       -> template<template<template<auto...> class...> class...>

-- Compose with Sail
ClassicTrip ::   template<auto...> class...
       -> template<template<template<auto...> class...> class...> class...
       -> ...
       -> template<template<template<auto...> class...> class...>

-- Compose with Snow
ClassicTrip ::   template<auto...> class...
       -> template<template<template<template<typename...> class...> class...> class...> class...
       -> ...
       -> template<template<template<auto...> class...> class...>

-- Compose with Hail
ClassicTrip ::   template<auto...> class...
       -> template<template<template<template<auto...> class...> class...> class...> class...
       -> ...
       -> template<template<template<auto...> class...> class...>

-- Compose with Cool
ClassicTrip ::   template<auto...> class...
       -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<template<auto...> class...> class...>

-- Compose with Calm
ClassicTrip ::   template<auto...> class...
       -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<template<auto...> class...> class...>

-- Compose with Grit
ClassicTrip ::   template<auto...> class...
       -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<template<auto...> class...> class...>

-- Compose with Will
ClassicTrip ::   template<auto...> class...
       -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<template<auto...> class...> class...>
```

## Structure

```C++
template<template<auto...> class>
struct ClassicTrip
{
    struct Commit
    {
        template<auto...>
        alias Page = CONJURATION;

        template<template<template<auto...> class...> class>
        alias Sail = TRANSITION;

        template<template<template<auto...> class...> class>
        alias UniSail = TRANSITION;
    };

// Compose with Mold
    template<template<typename...> class>
    alias Road = RECURSION;

// Compose with Page
    template<template<auto...> class>
    alias Rail = RECURSION;

// Compose with Road
    template<template<template<typename...> class...> class>
    alias Flow = RECURSION;

// Compose with Rail
    template<template<template<auto...> class...> class>
    alias Sail = RECURSION;

// Compose with Flow
    template<template<template<template<typename...> class...> class...> class>
    alias Snow = RECURSION;

// Compose with Sail
    template<template<template<template<auto...> class...> class...> class>
    alias Hail = RECURSION;

// Compose with Snow
    template<template<template<template<template<typename...> class...> class...> class...> class>
    alias Cool = RECURSION;

// Compose with Hail
    template<template<template<template<template<auto...> class...> class...> class...> class>
    alias Calm = RECURSION;

// Compose with Cool
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class>
    alias Grit = RECURSION;

// Compose with Calm
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class>
    alias Will = RECURSION;

// Compose with Grit
    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class>
    alias Glow = RECURSION;

// Compose with Will
    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class>
    alias Dawn = RECURSION;
};
```

## Examples

We will see two examples that demonstrate conjuration and transition.

- In the first example, we will compose `OperationA<Shuttle>::Page`, `OperationB<10>::Mold`, and `OperationC<'*'>::Rail`.

```C++
template<auto...>
struct Shuttle;

/**** OperationA ****//* Start */
template<template<auto...> class Sequence>
struct OperationA
{
    template<auto...Agreements>
    struct ProtoPage
    {
        using type = Sequence<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
/**** OperationA ****//* End */

/**** OperationB ****//* Start */
template<auto Multiplier>
struct OperationB
{
    template<typename>
    struct ProtoMold {};

    template<template<auto...> class Sequence, auto...I>
    struct ProtoMold<Sequence<I...>>
    {
       template<auto...J>
       using Page = Sequence<Multiplier*I..., J...>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};
/**** OperationB ****//* End */

/**** OperationC ****//* Start */
template<auto Variable>
struct OperationC
{
    template<template<auto...> class Sequence>
    struct Detail
    {
        using type = Sequence<Variable>;
    };

    template<template<auto...> class...Agreements>
    using Rail = Detail<Agreements...>::type;
};
/**** OperationC ****//* End */

/**** First Example ****//* Start */
using SupposedResult = Shuttle<10*2, 10*3, '*'>;

using Metafunction = ClassicTrip<OperationA<Shuttle>::Page>
::Road<OperationB<10>::Mold>
::Sail<OperationC<'*'>::Rail>
::Commit;

using Result = Metafunction::Page<2, 3>;

static_assert(std::same_as<Result, SupposedResult>);

// The following `static_assert` shows how the operations are composed:
static_assert(std::same_as<
    OperationC<'*'>::Rail<
    OperationB<10>::Mold<
    OperationA<Shuttle>::Page<
        2, 3
    >::type
    >::Page
    >,
    SupposedResult
>);
/**** First Example ****//* End */
```

- In the second example, we will transport the conjuration function to `InvokeRail`.

```C++
/**** Second Example ****//* Start */
template<template<auto...> class PageArg>
struct InvokeRailDetail
{
    using type = PageArg<2, 3>;
};

template<template<auto...> class...Args>
using InvokeRail = InvokeRailDetail<Args...>::type;

using Result_1 = Metafunction::Sail<InvokeRail>;

static_assert(std::same_as<Result_1, SupposedResult>);
/**** Second Example ****//* End */
```

## Implementation

Since every member template of different signatures is given a unique name, we know which member to pull out when asked for a template of a specific signature.
For example, we can compose a `Page` and a `Road` in the following way:

```C++
template<template<auto...> class...Args>
using Metafunction = Road<Page<Args...>::template Mold>;
```

Note that

- `Road` has signature `template<template<typename...> class...>` and
- `Mold` has signature `template<typename...>`.

This means in terms of signatures, a `Road` can always be invoked by a `Mold`.

We will implement `ClassicTrip` by performing recursion manually, meaning the function will recurse only once for every invocation of a member template.
We will showcase a simplified version that handles `Mold` and `Rail`.

Note that in the following code,

- `Radio` is a `Page` and
- `Car` is a `Mold` or `Rail`.

```C++
// `Radio` is a `Page`.
template<template<auto...> class Radio>
struct ClassicTrip
{
    /**** Define Road ****//* Start */
    // `Car` is a `Mold`.
    template<template<typename...> class Car>
    struct ProtoRoad
    {
       /**** Commitment ****//* Start */
       struct Commit
       {
           /**** Conjuration ****//* Start */
           // `Radio` and `Car` are composed here.
           // First, we instantiate `Radio` and obtain a `typename`.
           // Then, we invoke `Car` with the type result of the obtained `typename`.
           template<auto...Signals>
           using Page = Car<typename Radio<Signals...>::type>;
           /**** Conjuration ****//* End */

           
           /**** Transition ****//* Start */
           // Helper function for the member template `Sail`.
           // This function transports the conjuration function `Page` without invoking it, 
           // allowing further process by other higher-order functions.
           template<template<template<auto...> class...> class PageVessel>
           struct Detail
           {
               // We transfer the conjuration function `Page` to `PageVessel`.
               using type = PageVessel<Page>;
           };

           template<template<template<auto...> class...> class...Agreements>
           using Sail = Detail<Agreements...>::type;
           /**** Transition ****//* End */
       };
       /**** Commitment ****//* End */

       /**** Continuation ****//* Start */
       // This function composes the conjuration function `Page` and the `Agreements...`.
       // Note that even though `Agreements...` is variadic, it only allows a single argument.
       // This is because `Agreements...` will be used to invoke `ClassicTrip<*>::ProtoRoad`,
       // which has only one parameter `Car`.
       template<template<typename...> class...Agreements>
       using Road = ClassicTrip<Commit::template Page>::template ProtoRoad<Agreements...>;

       // This function composes the conjuration function `Page` and the `Agreements...`.
       // `Agreements` will be used to invoke `ClassicTrip<*>::ProtoSail.
       template<template<template<auto...> class...> class...Agreements>
       using Sail = ClassicTrip<Commit::template Page>::template ProtoSail<Agreements...>;
       /**** Continuation ****//* End */
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
    /**** Define Road ****//* End */

    /**** Define Sail ****//* Start */
    // This function is the similar the `ProtoRoad` defined above.
    // It handles the case where `Car` is a `Rail`.
    template<template<template<auto...> class...> class Car>
    struct ProtoSail
    {
       /**** Commitment ****//* Start */
       struct Commit
       {
           /**** Conjuration ****//* Start */
           template<auto...Signals>
           using Page = Car<Radio<Signals...>::template Page>;
           /**** Conjuration ****//* End */

           /**** Transition ****//* Start */
           template<template<template<auto...> class...> class PageVessel>
           struct Detail
           {
              using type = PageVessel<Page>;
           };

           template<template<template<auto...> class...> class...Agreements>
           using Sail = Detail<Agreements...>::type;
           /**** Transition ****//* End */
       };
       /**** Commitment ****//* End */

       /**** Continuation ****//* Start */
       template<template<typename...> class...Agreements>
       using Road = ClassicTrip<Commit::template Page>::template ProtoRoad<Agreements...>;

       template<template<template<auto...> class...> class...Agreements>
       using Sail = ClassicTrip<Commit::template Page>::template ProtoSail<Agreements...>;
       /**** Continuation ****//* End */
    };

    template<template<template<auto...> class...> class...Agreements>
    using Sail = ProtoSail<Agreements...>;
    /**** Define Sail ****//* End */
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwArKSuADJ4DJgAcj4ARpjEEgAcGqQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJXCm2mPalDEIETMQEeT5%2BQfWNOS1tBOXRcQnJqQqt7Z0FPZODw5XV4wCUtqhexMjsHAD0uwDUJgBsGgBKTPioJxoHeAoHTEenykzAmDcAdCYaAIIEmBYaQMAJM/jcAKBII%2B4KYXiIn0RYOwB2QBgUDwuV2RP1%2Bk2IXgcBzc6KyyAAKsQ8GlcSYAOxWP4HZkHXYAKg5bIOABFMDRIgczqhLgdOWz9lyBu1RbtcSzWYcbm42jc7g8njcALKedBfOUsyHApig8GG6FgiEATzSjFYmER338KLRTAxxJVTv1zPxhIIB2UxFQRCFly9RwZYZZ7M5xNQLBYhDYglFnIlBylfvFke9BAJRI88cI2fDjN%2B8vLzOjHNjDG0m2NORTHLTGZlxfl%2B2e50uTlVhnQXeVxD7xEwqLjxUwA4QCXt7ajhwAYnhiJNSAcAO5jiLzQR4Y1jm5Y3unR4MAeoWKtCKPLsEa22th6pkVjuHckzhjrrd3BgAN1QABrQ9TiHVUN0IBADgIGdoIfA5RwULxaD9VAqGg2DL2vSIBxue8bWYJ9Tm%2BF9X2ZM0DwtOEEURIQ8GAZhaAUHFSLIrwsiMf03kPfxuXdYdTQfQix2Pa5wTohixAUB1kRAEB8JhbAwVLMiozFGs62IBsBCbcV2QObBzzbP552ZUzWXUylDBKRsxRbKZM1lVjX07AAJBobWIA4qC8BgHEbfgvJgsc2CqBJoMBI0AS7IQmDoZ8y1UhUDg/e5vN8/ydNzayMnaB5gvHWt6yadK/JKm5XnecDII2P0IgAwCImAO4CHXczOzEWhUAgzifPaGcvLSQNtjdWJLQOIMBoOBB6IGgBaEgsC8nyypyaTzIok0IUi81TR2yjYXhVAZKdVFSRO51SS494ADVMAxBoWMS1SfSJXlr1ocz6RUpK3wOAB1MdsoYBQqHCgq0CKrSSpWzKGC7SqPlPIgEe4u6Hs%2B4jzPldimrgm0jl467MHRuwLURnF/B%2B1T6W5ZTaWcitNphbaoQO1mopZ6jjqRU6XQxC6ztdaTEV%2BYBR0BRgCGYz1GfLXHONiuhCb4964s%2B8ExYlpNpYuuSFPpuWO0srSQeyHS7P0wyByzOXacN57jZjAsEwIHXdLTa3jN%2BYsqy5Dw9wYLxtPhy3JQc72XPfGaHlhkq0CBTJ7owsdIc0kPSrh1GqtPfsU67LXMElwQRe%2BLG5c7KIgyBhBjQOTA/0YDCNmAKCbkL4vdaRU80r/Np93wZB10ICaGFocbOu69UDg44B6EeYhgB8KWSMdhcUpjtUDniUR2JAv5xaLnXS%2Bq2haG3sc94HFH6qA/eSWFvAKSpGlwTZWSQADINUBDXVTlIX2hwNwzWQFBWuDwBDj1HmONIbQ7QAi8kqFU5c17kX2ltZmFoFLCUFvzUuHdj5PVfArZqv8VbElJE/Sk1ILQu0IPrdBY4KZOgYWzaKX9gzCl1JrQ%2BncT6eipgzVByVUqxwyvHCcSd8qwTTsVAK4jGwVW4n2IyBV268OPjJFBUcC4aKlsxU8EEz4XwOFfaCqBfwNXvpQ5%2BNC34fw4agJWtBV6vkwXtNhLN3HKiOrg86vNLrCwdAQ/RRCKwkPTOrchD8MRUJfrQuMrtWGc2Jh/Zm/pAxEGcRaEJJcLoOxcupAOjgg4ZzDgZIyttHb20ESZVi3iGlCTtH4oJos9ElzCcyCJZCwR8Ucb/HJ7Su6OiUrUx2fseR8giCJLhHsraVKcj7ViEzeT8jHM4uZ4dBiR3XqIzOJU0oFSyAmAwQVYIVUyT/LhqosBrIHEwWIqBG6uPXgAST9LXc89BpGp1dGOYBs5BzINuGlDUpwLjxW0QaRhWCYUeM5lRXxAShYC2RXg/inSZ65l9Bk7%2B2TWLfV9kUxJiYpabPTBHKpr5Xp%2BjoQQYshKjZqWdgIdOJVymtipUlbx3MHQSUYjLJSTKumz2JtEj0bhRIWn5VJPW8lGGpIEdTMiEyA5stsqmeZNtFntRNtZc2odNVbOlFy1SDS4Uc12j4miIyUX8MCW6RGpNHqy2EfKGlkyPpfQjMKnGoqFLkKdfdMm4JmGjOVa%2BGppYNoWvNZ4xFNrkR2paaiz4uTpaYuIaKjZvTPXq0GdrfRcqDZjN%2BhMqyZt2VGoqdqhldI6alorKqklbsyXlK9lUolLLA7Byrc2fSnLFluNjbGppbAU34KGYK4s3TZm5piWSahr83B0uSdCRV2A10HlxZw0MPDC15ICQ7YscaEXwqtbytF/jbV4OCVOzNIq8Y5qJguuJdiV0tq3ew5RLD5WeJ3U4/N%2B6j5FqPY28szae1lOrR2odLIo1CPlKeq1PKkU3uvUm29bSD0ZtdX6p9UTc2OOycBvh%2BTwMWRjKs6ZkTlbtoWbSetx6/h%2BzFGx5suJy33Wlh7Tj7H%2BMcbqT7Mw/gIhoi8FgQmbh4R0EIJaJ6uJUOJtdR6oQCB4QEHoMx34EyADynkQ5lg5ZSxZyH2aXvQ8LdMmAACOXhGDbCeh6/TCRDOMeVUpnmab714ZZB6xxFMCU%2BrdREgNuahC2fs35Fm6b7UFPg0xsZYZPN3pw9O1iETEaBsucwtwsXyPRsS6WPTBmmhGZgwxoTJXXNNAsOSwdimLXcwOJqZCjhgR4ASE57FRIXPQxyIVjzo6CJ2kxf5y52paC4QjEVxD0L43nvM2hzDV0It2Yc5gdcFnXljZ636Rxk3uFuDW1Fxz4JXnkaFdU4Lw6FvWq8wAKQfaY0VWXwuRY2xaVrKFqS0E68QNkF3ETrgewVsMCGhNIeG4%2Be02GQMdN84%2Bzih3svf0OwW%2BHwzKaFYbcV9SfWQ51fo7Wqr%2BPSs5DcPVkzjW7vNZuv3B5WmVN7YOATpobh3PJZHbT5bfNVsfei7tvMfo1bxSCxGlkoX4LvfW4L8E9OqSM8UvFsys3IfzbPZapbymHWTrS5i7phGiai41nlqdxaHzHrVzpsnNWKfktg0IiZy5Vx%2BmwKoVgwIxzGe2VUiJQgvBpEnOgM4902vkLUxppnbguAaDZGYdcse2T%2BHXGADgbI0/Y6EREzUmBWhx0US%2BmxS6LRs5yD7cS6mCCacUnJMNuI5IDPBGXgQVhwSx4/uj11ckSNuBb7kC0aeM8cA/hCjWV25J0u090sPKFyG5/zwo5wn8f1uATwcfwWehPzEcMgAA%2BsLBIBAICTHQHJBQdoD8y0lbP1q6ZA/B9D0hFCyIVjac7B%2BMc/Az7dTxjcHfT8V%2BSg7QqoCgCAU8003U%2BcqA5OAg6oo444icSgZ%2BuIAB%2B%2Bh%2B7QJ%2BBAZ%2BIAF%2BbAV%2BFoYY/eHO4IQ%2Bmev6Y%2BhBrE/ebeMeGgneOoVBjs/eFex2VeNeDiq%2B7Y6%2Bm%2BBKv6BsfBm6K%2BVUghACrEAeQeScIet%2BtITob%2BYyzuK4kwBkHuUI3uFWJOSyNuMYEWkMA47unu88PuJqpm3OmuFmK2VmiMvwi83WwuBwry/4d8Y%2BJunOGW/q0uRM1hth4IPBW%2BPs1uNOmuKWV6rSaai86WvwESjhViY%2B5CMRzh6srhmsERFuNo0%2BoqT%2BbWe%2BXA8%2BeeTABey%2BveCRwElBSqQiaBQBR%2BWBOBeBmABB4IWRKEOR64Ehj%2BMhchDsEyuhAg%2BhqhXuDuCyHAawtAnAgQvAfgHAWgpAqAnAHOlg1gM8GwWwh4ImPApABAmgwxawgEIAgQkgnwGgkgXAdI/gGggQGgZgxwxwZgSQSQ%2BgnAkgvALAEgGgqQkx0xsxHAvACgIAqQmxUxwxpAcAsAMAiAIAtUaQ8I5AlACcaQdACQUQdonAqgSQxwc0xwkgBwwAyAyABwUgnwZgvAU4hAJAeAZ%2BXAMgggIgYg7AUgVJ8gSgagWxpAuglJG4WkaQnAPAIxYxExLJXxum8IUJqE6EqJ6JmJ2JuJ%2BJBxZgBwEABY8J9AiCaxKwvAAJWgawEASAcJCJZAFAEAupypIAwAUgCeNAKECQvxEAsQLJsQEQbQlo3JvA9pzAxAloumsQ2gmADgzppACcOsumY8TpgJpAWAsQXgwAyoZ8vx3AvAWALAhgc8Ow0x%2BAo4/kjcsZ0xmAqgPp8IOw6xEQAIoxoZf2sQWk7pHgWALJuYeALxcZpAjcxAjySgvIiZRgf2RgWxawVABgwACgN0nWG4Lmkx6x/A1Jog4g9J45jJKg6goZbJ%2BgSZKA1g1g%2BgeAsQvxkAawMBTQsZc0p%2BvSpgCxlgZgnxTZVIWAW5EAawdgPpTQLg54MwfglJYQ0ySwYwlJxQBqz5eg35TQiwowNQvQ95/QDkv5lJd5cMGYgFYUwF8w0wngXQegCFQw75QFEgt5yx2wmFDxHA4xpAHxvAXxBw4pGJWJOJeJBJcpEAuApJKp/gXAapGx3ZawM4lwYwN5pAuxkg/gnwAAnP4HSJIEcWYJIKcOcccPxXhU8aQC8YxZ8McFwMcEkPxUkMpfsVwIEIJccIRQKZwD8X8SxYCVqWCdqRCcKdCQaUaYiciRwG0CwH%2BHSHNE8C6JxFwPxZ8FwIccSfgEQJeXoDOTSVOdIDOYoHOSyboAnhyUwFyXGbyfhfyaGYKZZaKQvI5c5a5QYO5Z5d5bcAqROHqUcCJmYMxRqUCeZTZfqbCYVcaQ5U5XNG5aafxbHnwHQAgtabaaGa6Y6X6T1e6Z6d6b6Q2QGVLEGePCyeGZGdGUxH6QmUmeIKGWmaBZmSyTmXmQCH6UWQ0CyWWRWZaFWSmeqVSPWesU2S2ZgG2QtU1N2XwH2QOUOSOX6UFZOXSaFbIOFcyQuSAAntlcYKuZYOuZufADuWkHuZwAedgUeQDRYGecRReeSfdCDSBXDI%2Be4EhQUK%2BeeLBcsF%2BZkD%2BRjS%2BekPjQBehXBShQ0KBQIBmBBSjU0DBWTbjbYOBYTShQ5DjZ%2BVhZsDhUxXhQRURTMZwOlQ1VlUmfiblYcfKXRf5cVYxWVaxaQOxUtJQAlbJfJZ5UcXSNpXSKcZIGJZiZSQLV8YZf8bdSCeCZCVZTVUCHqUiWwJwA5ZKSwAoH%2BHiX%2BB5Z8NCJML5fReSYFbIMFW9QyZ9fOdMboCnjFXFTyXzUlZ8ZwEKQQCKRNOhI7Vic7a7QcO7Z5V7X6AVTbcqbLf4PLSZcCTqbVQkDCYaeXYkK7UHnvlnXvjnQfsQCwJiW1ZaauJQF1dMf1SGesb3YNfeX6aNYIONSGamZgBGVGZ1LGesfNR2UdWGSuCtUjaGetcgPmVtYIDtaWRuftYdTWSdX6edUnFdR2TdSXb2W8A9ZgMOQRM9QHa9RIO9YICHZFQEEuV2ceVYIDWWdeaDeDXsKfiuSebDeeQkJeUjduXTTkGjbTW%2BRUBhXjTZAILTf%2BTkBzfBZTdBSzfkETVBfTezYzZ%2BczYMLTahZg7hQoNhXSQlfzfpRwOlU7S7W7R7TnVLX5SQLLUxeqQrUrZxarc8T9Z5f4EEBcccW8aI3SCpXpclQZbYEZeVSsDsSAJIIEAJYEEkFcfxZIPxacUJVwCniWf4LHcRfI0owlUSbI3Hd8cZZqWsE2VkM4JIEAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/pagelivore/classic_trip.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/classic_trip.test.hpp)
