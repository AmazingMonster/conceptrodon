<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::Trek`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-trek">To Index</a></p>

## Description

`Mouldivore::Trek` accepts an operation.
Its first layer accepts another operation for composition.
Then, it returns two commitment functions and twelve continuation functions.

- **Commitment**
  - **Conjuration:** When invoked, this function instantiates the first operation with the arguments. Then, it invokes the second operation using `Omennivore::Send` with the instantiated first operation as the packed vessel.
  - **Transition:** When invoked by a vessel, this function transports the conjuration function to the vessel.

- **Continuation**

  When invoked by another operation, the function returns a `Trek`
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
   Unpack(Operation<sub>n-1</sub>&lt;
       &vellip;
   Unpack(Operation<sub>1</sub>&lt;
   Unpack(Operation<sub>0</sub>&lt;
       Arguments...
   >)
   >)
       &vellip;
   >)
   ></code></pre>

## Type Signature

This function has multiple signatures.

```Haskell
-- End in Conjuration
-- Compose with Mold
Trek ::   template<typename...> class...
       -> template<typename...> class...
       -> ...
       -> template<typename...> class

-- Compose with Page
Trek ::   template<typename...> class...
       -> template<auto...> class...
       -> ...
       -> template<typename...> class

-- Compose with Road
Trek ::   template<typename...> class...
       -> template<template<typename...> class...> class...
       -> ...
       -> template<typename...> class

-- Compose with Rail
Trek ::   template<typename...> class...
       -> template<template<auto...> class...> class...
       -> ...
       -> template<typename...> class

-- Compose with Flow
Trek ::   template<typename...> class...
       -> template<template<template<typename...> class...> class...> class...
       -> ...
       -> template<typename...> class

-- Compose with Sail
Trek ::   template<typename...> class...
       -> template<template<template<auto...> class...> class...> class...
       -> ...
       -> template<typename...> class

-- Compose with Snow
Trek ::   template<typename...> class...
       -> template<template<template<template<typename...> class...> class...> class...> class...
       -> ...
       -> template<typename...> class

-- Compose with Hail
Trek ::   template<typename...> class...
       -> template<template<template<template<auto...> class...> class...> class...> class...
       -> ...
       -> template<typename...> class

-- Compose with Cool
Trek ::   template<typename...> class...
       -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
       -> ...
       -> template<typename...> class

-- Compose with Calm
Trek ::   template<typename...> class...
       -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
       -> ...
       -> template<typename...> class

-- Compose with Grit
Trek ::   template<typename...> class...
       -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
       -> ...
       -> template<typename...> class

-- Compose with Will
Trek ::   template<typename...> class...
       -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
       -> ...
       -> template<typename...> class

-- End in Transition
-- Compose with Mold
Trek ::   template<typename...> class...
       -> template<typename...> class...
       -> ...
       -> template<template<template<typename...> class...> class...>

-- Compose with Page
Trek ::   template<typename...> class...
       -> template<auto...> class...
       -> ...
       -> template<template<template<typename...> class...> class...>

-- Compose with Road
Trek ::   template<typename...> class...
       -> template<template<typename...> class...> class...
       -> ...
       -> template<template<template<typename...> class...> class...>

-- Compose with Rail
Trek ::   template<typename...> class...
       -> template<template<auto...> class...> class...
       -> ...
       -> template<template<template<typename...> class...> class...>

-- Compose with Flow
Trek ::   template<typename...> class...
       -> template<template<template<typename...> class...> class...> class...
       -> ...
       -> template<template<template<typename...> class...> class...>

-- Compose with Sail
Trek ::   template<typename...> class...
       -> template<template<template<auto...> class...> class...> class...
       -> ...
       -> template<template<template<typename...> class...> class...>

-- Compose with Snow
Trek ::   template<typename...> class...
       -> template<template<template<template<typename...> class...> class...> class...> class...
       -> ...
       -> template<template<template<typename...> class...> class...>

-- Compose with Hail
Trek ::   template<typename...> class...
       -> template<template<template<template<auto...> class...> class...> class...> class...
       -> ...
       -> template<template<template<typename...> class...> class...>

-- Compose with Cool
Trek ::   template<typename...> class...
       -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<template<typename...> class...> class...>

-- Compose with Calm
Trek ::   template<typename...> class...
       -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<template<typename...> class...> class...>

-- Compose with Grit
Trek ::   template<typename...> class...
       -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<template<typename...> class...> class...>

-- Compose with Will
Trek ::   template<typename...> class...
       -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<template<typename...> class...> class...>
```

## Structure

```C++
template<template<typename...> class>
struct Trep
{
    struct Commit
    {
        template<typename...>
        alias Mold = CONJURATION;

        template<template<template<typename...> class...> class>
        alias Flow = TRANSITION;
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

- In the first example, we will compose `OperationA<Shuttle>::Road`, `OperationB<10>::Mold`, and `OperationC<'*'>::Rail`.

```C++
template<auto...>
struct Shuttle;

template<typename...>
struct Capsule;

template<template<auto...> class...>
struct Carrier;

/**** OperationA ****//* Start */
template<template<auto...> class Sequence>
struct OperationA
{ 
    template<typename...Vay>
    struct Detail
    {
        using type = Capsule<Sequence<Vay::value>...>;
    };

    template<typename...Agreements>
    using Mold = Detail<Agreements...>::type;
};
/**** OperationA ****//* End */

/**** OperationB ****//* Start */
template<auto Multiplier>
struct OperationB
{
    template<typename...>
    struct Detail {};

    template<template<auto...> class Sequence, auto...I>
    struct Detail<Sequence<I...>>
    {
       template<auto...J>
       using Page = Sequence<Multiplier*I..., J...>;
    };

    template<typename...Agreements>
    using Mold = Carrier<Detail<Agreements>::template Page...>;
};
/**** OperationB ****//* End */

/**** OperationC ****//* Start */
template<auto Variable>
struct OperationC
{
    template<template<auto...> class...Sequences>
    struct Detail
    {
        using type = Capsule<Sequences<Variable>...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = Detail<Agreements...>::type;
};
/**** OperationC ****//* End */

/**** First Example ****//* Start */
using SupposedResult = Capsule<Shuttle<10*2, '*'>, Shuttle<10*3, '*'>>;

using Metafunction = Trek<OperationA<Shuttle>::Mold>
::Road<OperationB<10>::Mold>
::Sail<OperationC<'*'>::Rail>
::Commit;

using Result = Metafunction::Mold
<
    std::integral_constant<int, 2>,
    std::integral_constant<int, 3>
>;

static_assert(std::same_as<Result, SupposedResult>);

// The following `static_assert` shows how the operations are composed:
static_assert(std::same_as<
    Send
    <
        Send
        <
            OperationA<Shuttle>::Mold
            <
                std::integral_constant<int, 2>,
                std::integral_constant<int, 3>
            >
        >
        ::Road<OperationB<10>::Mold>
    >
    ::Sail<OperationC<'*'>::Rail>
    ,
    SupposedResult
>);
/**** First Example ****//* End */
```

- In the second example, we will transport the conjuration function to `InvokeRail`.

```C++
/**** Second Example ****//* Start */
template<template<typename...> class MoldArg>
struct InvokeMoldDetail
{
    using type = MoldArg
    <
        std::integral_constant<int, 2>,
        std::integral_constant<int, 3>
    >;
};

template<template<typename...> class...Args>
using InvokeMold = InvokeMoldDetail<Args...>::type;

using Result_1 = Metafunction::Flow<InvokeMold>;

static_assert(std::same_as<Result_1, SupposedResult>);
/**** Second Example ****//* End */
```

## Implementation

We will compose functions using `Omennivore::Send`.
For example, we can compose a `Mold` and a `Road` in the following way:

```C++
template<auto...Args>
using Metafunction = Send<Mold<Args...>>::template Flow<Road>;
```

Note that in order to succeed, `Mold<Args...>` must be a packed `Road`, meaning it is of the form `Vessel<Items...>` where `Items...` all have signature `template<typename...>`. This requirement is not checked by `Trek`.

We will implement `Trek` by performing recursion manually, meaning the function will recurse only once for every invocation of a member template.
We will showcase a simplified version that handles `Mold` and `Rail`.

We will use a simplified version of `Send` to compose operations.

```C++
template<typename PackedVessel>
struct Send {};

template<template<typename...> class Container, typename...Elements>
struct Send<Container<Elements...>>
{
    template<template<typename...> class Operation>
    struct Detail
    // Invoke `Operation` with the `Elements...`.
    { using type = Operation<Elements...>; };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};

template<template<template<auto...> class...> class Stockroom, template<auto...> class...Sequences>
struct Send<Stockroom<Sequences...>>
{
    template<template<template<auto...> class...> class Operation>
    struct Detail
    // Invoke `Operation` with the `Sequences...`.
    { using type = Operation<Sequences...>; };

    template<template<template<auto...> class...> class...Agreements>
    using Sail = Detail<Agreements...>::type;
};
```

Note that in the following code,

- `Radio` is a `Mold` and
- `Car` is a `Mold` or `Rail`.

Here is the entire implementation.

```C++
// `Radio` is a `Mold`.
template<template<typename...> class Radio>
struct Trek
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
           template<typename...Signals>
           using Mold = Send<Radio<Signals...>>::template Road<Car>;
           /**** Conjuration ****//* End */

           
           /**** Transition ****//* Start */
           // Helper function for the member template `Flow`.
           // This function transports the conjuration function `Mold` without invoking it, 
           // allowing further process by other higher-order functions.
           template<template<template<typename...> class...> class MoldVessel>
           struct Detail
           {
               // We transfer the conjuration function `Mold` to `MoldVessel`.
               using type = MoldVessel<Mold>;
           };

           template<template<template<typename...> class...> class...Agreements>
           using Flow = Detail<Agreements...>::type;
           /**** Transition ****//* End */
       };
       /**** Commitment ****//* End */

       /**** Continuation ****//* Start */
       // This function composes the conjuration function `Mold` and the `Agreements...`.
       // Note that even though `Agreements...` is variadic, it only allows a single argument.
       // This is because `Agreements...` will be used to invoke `Trek<*>::ProtoRoad`,
       // which has only one parameter `Car`.
       template<template<typename...> class...Agreements>
       using Road = Trek<Commit::template Mold>::template ProtoRoad<Agreements...>;

       // This function composes the conjuration function `Mold` and the `Agreements...`.
       // `Agreements` will be used to invoke `Trek<*>::ProtoSail.
       template<template<template<auto...> class...> class...Agreements>
       using Sail = Trek<Commit::template Mold>::template ProtoSail<Agreements...>;
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
           template<typename...Signals>
           using Mold = Send<Radio<Signals...>>::template Sail<Car>;
           /**** Conjuration ****//* End */

           /**** Transition ****//* Start */
           template<template<template<typename...> class...> class MoldVessel>
           struct Detail
           {
              using type = MoldVessel<Mold>;
           };

           template<template<template<typename...> class...> class...Agreements>
           using Flow = Detail<Agreements...>::type;
           /**** Transition ****//* End */
       };
       /**** Commitment ****//* End */

       /**** Continuation ****//* Start */
       template<template<typename...> class...Agreements>
       using Road = Trek<Commit::template Mold>::template ProtoRoad<Agreements...>;

       template<template<template<auto...> class...> class...Agreements>
       using Sail = Trek<Commit::template Mold>::template ProtoSail<Agreements...>;
       /**** Continuation ****//* End */
    };

    template<template<template<auto...> class...> class...Agreements>
    using Sail = ProtoSail<Agreements...>;
    /**** Define Sail ****//* End */
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxBJm0gAOqAqETgwe3r56KWmOAqHhUSyx8Vy2mPYFDEIETMQEWT5%2BgXaYDhl1DQRFkTFxCdIK9Y3NORUjPX0lZRIAlLaoXsTI7BwA9BsA1EJ4LEm0eDSY6NsmAGwaQq6XGttUXgydAgB0JhoAggSYBwY/Jn8bgIAE8koxWJhtsomMgANanABqmAUdkB2A%2BnxGxC8Dl2rnOAHYrISACKAqxfTE/P5MAFAmmHOmYQHAsEQtivLno7bIAyo7YeQRMMJxUjbUHg5icrnYehsQQKdGY7G4gj4hjoVlC%2Bqi4isuW/RgEBRc97%2BDEWzEmYmY7b2iW/Jn04FO/4shns6WYM08vlMAUAeXBxDpGWVXwd21VeNJmF1tDtDq22wAkgwAG6oBHnK7BuJhgR3bYAd0ICAlCChd0NCpNvqu70jDptFm2XjSRgl7PO/lJ23zoZqBvlxtN3Kt/jbNvJU%2BtzftjPdrKXzJXXshvotvP549en2AxEwRsVEc%2BUY7YWA2wASqgmGdAf24wnWQejyf6xPsCAQJKPZSnwzhS87fG6a4MuBLqri6TBeEQW7YDuAZ7n6u67EQ8LEKgqAsOKMEem4cEId%2ByGomaNwAI5eIwaxKlaXwxuqNyaqydSoFhOEsGxmDUbRKKIWerZJouUGEQRK5iayxGoIhZGodu/pBiGhYMGeUZMdsL4iomC7bCm6ZZjmdyDqpxZlgQFaWdWVxUTRzwCdyjYiUSbaXl2/69v2pnDkCdn8QplrTmSIFUnpEmQbS0FSUCMlyUpgXyWa77HnW9EYnp7nXkIOleVp8Y6W%2Bh6pWOiG/v%2BoVASFc5hZ8GwAFSNfV2wACpHnC2xNfVGyYimdw3g%2BTjFngCjbEwuYaAAsp4WrOV8EWulF4kbjK5pIQlt6DagZ6aW1mBwtatp6Q1TX5TQ4S3veZxdVszXdI0nU9cdOx3ER%2BpXNsI1jRN020LNGhNueDoLSDK0%2BqRG1vepDqaco2FEHeD4ucJenJl1gq4SwhB1p1TW3RhPSPS5MMEDieIeCwWMEMT9oo0DUYMydjUYww2grKpuONfj93qt1NOMy9VwDfg20fYYj5XFDYtHryuF5Kc2xVkegMM6roNSpuXJ7MAzC0Ol/MXp216/Y%2BfYalqQLC0Nfl4DrYiBei5ViZdSNAlDk6AarjPo0KbNDhknPdQ12zYJqRO1V7UYG2jp1tYY%2BQBzdwc8%2BH9ORymAASVQhg8TwvAwDwkJWUJsKUcSOktE0AGK0KgJZ3Crkf2imLUIF9jzPDUEqhgwCgpI0o3WbLrPs13Hf5z9M3meWyzqmERlXp9BDitHzc7GItdll2jyNEr2xJNhdGjdEILbKg1nEIrttKwAtCQWCX%2BPNSmqvFfOuJMWLe/64a6taEofFdCJtkSoiqNDJumltJ0FfnTJuqsUwAHUoSk3jlQcuQ80Aj39gIXOncA53BNsWIgk8/ogLRHNNOcD2xG27OCPKwCURoiBIQj2MDqqAVfiDT%2B6sOTgzWklCGu5krFU/PrVGqssrbBrnXPKUDExAhSqIsqf52SVSoUzZqcde7pBwUnZqodrpPUobTdh/MNEY0ptjY0gd8YGNTmYn2sgwheA5nogmD0%2BbiP0jsVu7c85dzQAcVIKJi7Dz9hzJ%2B%2BCriELFmHIedxFFpQbADMxOwIjn2QQgOk2xMAZkYJWZYwAKwJJEUkpy9wvoZgaHgQayBxSEDPgwWgp8N511GuNI29AxrEGAD4Y0jcBatTbqNL6sRRAdhsl8UppVymljoLQbYsRqEK2IfPbMky9oHSBPVR2IA4bn1QIjf6pBUmljbsgCsWTRoCGaY0qESQGiQh%2BJfV6DQG78y4UtH%2BvDAEAK5Iksc4DDaLyOXlTZ2pMaECdpXFhP4/zO32QjK6RUPxlLWpVU5vjRqRJwYE%2BWg8qxhNHgHHFBcCFT1iWceJVwAWKmSQMqMfUaXTNPB9MstAFlLImVS1An1MzrImuC7ZuzEWoBynQBlwNuHSq%2BbFeCslBF/P4QlYRqLAUMWMdQxe4qFlPlau1CFliCDQvftsWFJr3TQnhmKwqCiWVfnRTVTV5idTONcXjYOdjPFp2Ak6lynzv6el/nw/%2B5F/n2rEWnSRoK9WiqOSikqdLvxqJjszOM50oSgrcV6oxLlzHptFLsXKbiU7esZT44ZuCJ5fSHmkLGBhL7Uo0HG5FH0sAZrOEwaIqA8kMoMuqLJmp6AEqhKIJQZy4iTKlhU9pE0BrQIoVGANy5IqBqIvK35YblXoXdhlNOsNrU6uRkdZ1jijU4xLaMXmRivaaQplTfmsC4EuoEOErul7CZlrgTw70FFba60jVQyRJs8osQtm4K220bZ2z1oJC0FrmRFugW7N5rCvGMscVg91XNPVh29a/cxWiE66I9XdK9qcqHLogl/FdbJg2bsShtBhoD5F7qoZAgq0D0MthPVQh0kjPJ6uY0wtwsKU1N19Rw7jolZU0eoz%2BzW26lWhr3LSk0QKvaSOkSWWRnH5FuDU4FcqqinXqPRkRnRBds14ZvarSTDjTr3qsYIGxuHDGgS9i%2BwQbr32kfcdej5Mq13/l/YqrdhmNP2mjVdMFBq3aQuNfCmFU94NJdNS212BmI1wak5qqj0VZNxTC4xoR4a1Wng1ZpmhOrYv7UNVTBDPwzUpbhQRK1Byj12vKw65Upn4GYccAwFxvmcP6Js8e2cuWl1BdowtIrSmt0qdVYm9TlX%2BPVdyrGw9tqsvdYdn15u6MC0XRq9Z9zVJTG1Q0V1G7XNermZRCaGx93buvfw1SMw/gwh8i8FgXsbh4J0EICCIS81P7zZ2qTNUuwEDwQIPQDFYPZMhcU5Dsm6oiJJAUF4BHfqkfBfBxu4rglGJQ/Jg0YgeA4iI7qujHyGRzwfo8UY/LhEIeKXQv5ByaPof04EEBC705wrcLBmaREYggUcdfHpJ9EiaGCbNpj7HuO3Bc7WKycXtBfxVO8B6bAOWJs0%2Bm8j0XZWVuAfW4vEDeq5EJqUd%2BYz4IMWXdp6dPnDBGd%2BZzaBcx7u2xM4C/j2jMkzU48cIcKn%2BoNWaT94dT2UqTf0eTXpKXm3bQu/9TN6j7P1qc94vZNY4p5upkl2T9Utu/L5/4qyVMcG2M8fjwzObRPXgAClItaq7DCYA1YzZq8IpNMPeAI9xHqrXrk4pW8G5lxn4Xieflm9EUC4DM08pvUp9ToEFfdvm92W17vIa0NVUmy95mfvXNjfOwL13Z%2BVI1DcBf/zqdm/EPF5TrtuO90x7vxkNwcfM/I6E4kQLZ7j94W72ip5cY%2Bq8ZVaLwK79hK446ERgEa7VIf567T7QEn4RwJ4E6FYt5LaL5pTL40Lzq6pmzb6GbKIVR%2Bou6%2B4/4CAP5nb2JfDmJVx4DEAjAhyqCsCHBQgB6pySJCBeBJDyzoA3gohh5r5MBY5IFsSw4EDw6ERcAaD1RmDihgAcD1SaHojihCAKFKGsgqH1SBDbCaHaEcC9ZBSgTAYFSkq1ZbJuDu5AR%2BQGGf6/hiZfC/jxpAix5AgqG7KeGfC/idZOEMGZCsjmE6GpZkFni/hObUx46fDRqSG0DqhCZ2H%2BIZAeFTxUhAguQjDoC/hhA/CHhiAAD6mCUwggrIJR4oZguhBRBARRIAJRmAZRtAlRAg1RiRbgdR2w/gQkR%2BKo9QjgyA5RKEcQBAEAhRv4CgkIEx9EEGqRy8uwIhYhEhyuiR2A8wNOLchK/AHKdci8dwUwYxixSgjQxYCgCAbSisMiQ8qA4R7SMseKwSRRIxYY4xkxjQMxzRcxCxAYrILkYGyM%2BR6GoJ6GwJ0m9ozh8hcO7hIAhCMJ/2r8DMsxrRgg7RoYnRVR9QNRQI/RDRFoJyKJGk/xmJpROJXRvc%2BJvR/Rgxa2cCHevY9eqs3hyKvh4RVg/hGggRLWYJbJ2wIRO27uf%2BQIURlhMRtqQppJacwhoh7xmxYe1oFouxTqbBHBXB2APBfw/BXu42V26MNwmCZwOpvBXSAh3qrO3yoWIBzWf0nwPSPOeIhk6yJstuguLkAmPYQmM0TpwAYJf%2B6GGJbRHRNJPRtRgg9RjRIZFJYZ1JeJhg9J0ZAxQKvWHCs%2BYEgB8%2BdphB%2B4PSkakibpCI1uZsJZmAHpemb4hZ1BJmuWKRWx5RXA9CmReCzgIA2mNe/KpZApSRZxeA3xoCvxGJ8xbAixrIypaRzZeh6xSpKx6I6pgE5iJpAgZpupfBj%2BOaHAiwWuHAAArLwH4BwFoKQKgJwH/pYNYNGMsKsNWJ9jwKQMaieTuYsHCCAPuZIK8BoJIFwISP4BoPuRoGYBcBcGYAABzgX6CcCSC8AsASAaAaCkDHmnnnkcC8AKAgBIXPlaCLBwCwAwCIAgCzxJDwTkCUB4p0BxARCQicCqDgUXA3wXCSDbDADIDIDbBSCvBmC8CnCEAkB4BFEVD8CCAiBiDsBSAyCCCKAqDqAvmkC6AVAlihhJCcA8C7mcCHnIWaC8BoWBjwSkXqioBUDbD0WMXMWsXsWcVflmDbAQAUxJBUUvIPnzC8A4U7mkAQBICUX0BkAUAQA%2BWDDABSDqE0BpFxCYUQDRA6WkDRBhANAghqW8BxXMDEAgiBjRDaAdDPmPmBJ1iBhNKJXyVYDRBeDABEQcqYXcC8BYAsCGDADiDFUcHZV4B5JVWnmYCqAdDwTrCPltF7mnlHDRChhpUeBYAxWkz7BJWkB5LEDdpKBxh1VGBHBGA6WLBUAGDAAKCIhU4lj5jHmPkiXCCiDiCSVHUyVqAxWKX6D1UoDWDWD6B4DRCYWQCLBPHPycA3yFFPimBXmWBmCoWzWU5YAvUQCLDtD5wuCajjB%2BAVAhCiizCDAVB5CWYw25CpCWYzADDlCVDVBdBXpo2TBVAtUCA8xY1lw41TBjCeAtB6BU29AI3Y0LBLArBrDM17laUoW6WcCmUMVMUsVsUcVcW2UQC4D8XOX%2BBcCuVPlrWLBVgPiDBg2kDvmSD%2BCvAACc/ghIkgP5iQVwgFFw6t0FHAsFpA8FktrwFwXAFw4F6t4F1tn5XA%2B5mtFw2l8laFGFWFMtL5eFhFXlxFBlZF/lgVxANFbAnADQLAGYhIN840/oXYXA6trwXA35vF%2BARAwNegR1Ylp10g51Sgl18lug6hylMhSVGlB5R5MVelgdRlJlkd0dsdyECdSdKd9w9lcsTl5wn2Zg0t7leF3lndvl5FAVQ9gwDdMd8dwV6tKhfAdAzykV0V8lKVCV01K9aVGVWVDg01eVxoBVzSMVJVZVFVes01tV9VjVp5%2BAR4nQbVMVnV3VPw01/VMVQ1I1IIY16wp5k18F1VM1cQ81mAi1F9V4a1fAm121u1%2B1012dJ1EledsgF1clp5xdN1q1v1Vglgj1z18Ab1SQH1HAX1zRP191/1gNcQwNKIuDuNJNfgEArghNQQmo5NcwyNGN9%2BNNEwpAKNNQLDSNND%2BcPMjDENNQZNjNFNdNBNnDsNtgV6fD5Q4Nt5bNUtxtnN1dPNE9TdU9nFrd35dlYtGd3dktfdstpA8tD8lAFdpt5tSdP5hIzthI/5kgetv5btqFnAnt2FYD%2BFRFJFQdFFY9odtFHAkdFlLACgGYHFGYidrw7oIwad4tglWdsgOd8DUl8gBdyDOgAQpApdql1VFdaj7tnA%2BlBAhlZ89dxALAYTETUTMTcT6oHdBwXd5g/g/gJjPtnlg9zTw9wdgTIAkToh5R0T6t5RDTExVTzFc94VnBlAS9p569RVj5izm92VO9mMe9hVh9mApV5VG8VVj559y1X9NVzVt9VD8lD9yAPVz9WJA1vAb9CVn9E1lOv9j5s1gDwDy1oDnTG1TAW1O1mAe1UoMDKTcDEgCD0lmTV1OTBg6DpDNgQ1oNeDBDGwsxGD1gANulQNglVDr1AjNQUN7g0jeg8NxQTNbDxGmQJLlLmN4jrDBL%2BNPQwjxNgjcj9L/D9Nwj7L5LEjKjCgSjElhTVdxTHA3S1TLF4TkT2wIzsTzIXBot6dRcrTUtblpj5jitVjcFIAZgSdbT%2B5QFv5iFbThINtbj3N6FtgXt/db5IAkg%2B5Gt%2B54FIF6tkg6t/5WtXAgQe5/gIr7jlrNrxtPF5rZ5Hj3tuFiws1aQzgkgQAA%3D)

## Links

- [source code](../../../../conceptrodon/descend/mouldivore/trek.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/trek.test.hpp)
