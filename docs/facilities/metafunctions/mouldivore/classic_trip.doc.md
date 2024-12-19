<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::ClassicTrip`

<p style='text-align: right;'><a href="../../../index.md#higher-order-modifications">To Index</a></p>

## Description

`Mouldivore::ClassicTrip` accepts an operation.
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
ClassicTrip ::   template<typename...> class...
       -> template<typename...> class...
       -> ...
       -> template<typename...> class

-- Compose with Page
ClassicTrip ::   template<typename...> class...
       -> template<auto...> class...
       -> ...
       -> template<typename...> class

-- Compose with Road
ClassicTrip ::   template<typename...> class...
       -> template<template<typename...> class...> class...
       -> ...
       -> template<typename...> class

-- Compose with Rail
ClassicTrip ::   template<typename...> class...
       -> template<template<auto...> class...> class...
       -> ...
       -> template<typename...> class

-- Compose with Flow
ClassicTrip ::   template<typename...> class...
       -> template<template<template<typename...> class...> class...> class...
       -> ...
       -> template<typename...> class

-- Compose with Sail
ClassicTrip ::   template<typename...> class...
       -> template<template<template<auto...> class...> class...> class...
       -> ...
       -> template<typename...> class

-- Compose with Snow
ClassicTrip ::   template<typename...> class...
       -> template<template<template<template<typename...> class...> class...> class...> class...
       -> ...
       -> template<typename...> class

-- Compose with Hail
ClassicTrip ::   template<typename...> class...
       -> template<template<template<template<auto...> class...> class...> class...> class...
       -> ...
       -> template<typename...> class

-- Compose with Cool
ClassicTrip ::   template<typename...> class...
       -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
       -> ...
       -> template<typename...> class

-- Compose with Calm
ClassicTrip ::   template<typename...> class...
       -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
       -> ...
       -> template<typename...> class

-- Compose with Grit
ClassicTrip ::   template<typename...> class...
       -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
       -> ...
       -> template<typename...> class

-- Compose with Will
ClassicTrip ::   template<typename...> class...
       -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
       -> ...
       -> template<typename...> class

-- End in Transition
-- Compose with Mold
ClassicTrip ::   template<typename...> class...
       -> template<typename...> class...
       -> ...
       -> template<template<template<typename...> class...> class...>

-- Compose with Page
ClassicTrip ::   template<typename...> class...
       -> template<auto...> class...
       -> ...
       -> template<template<template<typename...> class...> class...>

-- Compose with Road
ClassicTrip ::   template<typename...> class...
       -> template<template<typename...> class...> class...
       -> ...
       -> template<template<template<typename...> class...> class...>

-- Compose with Rail
ClassicTrip ::   template<typename...> class...
       -> template<template<auto...> class...> class...
       -> ...
       -> template<template<template<typename...> class...> class...>

-- Compose with Flow
ClassicTrip ::   template<typename...> class...
       -> template<template<template<typename...> class...> class...> class...
       -> ...
       -> template<template<template<typename...> class...> class...>

-- Compose with Sail
ClassicTrip ::   template<typename...> class...
       -> template<template<template<auto...> class...> class...> class...
       -> ...
       -> template<template<template<typename...> class...> class...>

-- Compose with Snow
ClassicTrip ::   template<typename...> class...
       -> template<template<template<template<typename...> class...> class...> class...> class...
       -> ...
       -> template<template<template<typename...> class...> class...>

-- Compose with Hail
ClassicTrip ::   template<typename...> class...
       -> template<template<template<template<auto...> class...> class...> class...> class...
       -> ...
       -> template<template<template<typename...> class...> class...>

-- Compose with Cool
ClassicTrip ::   template<typename...> class...
       -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<template<typename...> class...> class...>

-- Compose with Calm
ClassicTrip ::   template<typename...> class...
       -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<template<typename...> class...> class...>

-- Compose with Grit
ClassicTrip ::   template<typename...> class...
       -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<template<typename...> class...> class...>

-- Compose with Will
ClassicTrip ::   template<typename...> class...
       -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<template<typename...> class...> class...>
```

## Structure

```C++
template<template<typename...> class>
struct ClassicTrip
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

- In the first example, we will compose `OperationA<Capsule>::Mold`, `OperationB<10>::Mold`, and `OperationC<'*'>::Rail`.

```C++
template<typename...>
struct Capsule;

template<auto...>
struct Shuttle;

/**** OperationA ****//* Start */
template<template<typename...> class Container>
struct OperationA
{ 
    template<typename...Agreements>
    struct ProtoMold
    {
        using type = Container<Agreements...>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};
/**** OperationA ****//* End */

/**** OperationB ****//* Start */
template<auto Multiplier>
struct OperationB
{
    template<typename>
    struct ProtoMold {};

    template<template<typename...> class Container, typename...Elements>
    struct ProtoMold<Container<Elements...>>
    {
       template<auto...J>
       using Page
       = Shuttle<Multiplier*Elements::value..., J...>;
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

using Metafunction = ClassicTrip<OperationA<Capsule>::Mold>
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
    OperationC<'*'>::Rail<
    OperationB<10>::Mold<
    OperationA<Capsule>::Mold<
        std::integral_constant<int, 2>,
        std::integral_constant<int, 3>
    >
    >::Page
    >,
    SupposedResult
>);
/**** First Example ****//* End */
```

- In the second example, we will transport the conjuration function to `InvokeMold`.

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

Since every member template of different signatures is given a unique name, we know which member to pull out when asked for a template of a specific signature.
For example, we can compose a `Mold` and a `Road` in the following way:

```C++
template<auto...Args>
using Metafunction = Road<Mold<Args...>::template Mold>;
```

Note that

- `Road` has signature `template<template<typename...> class...>` and
- `Mold` has signature `template<typename...>`.

This means in terms of signatures, a `Road` can always be invoked by a `Mold`.

We will implement `ClassicTrip` by performing recursion manually, meaning the function will recurse only once for every invocation of a member template.
We will showcase a simplified version that handles `Mold` and `Rail`.

Note that in the following code,

- `Radio` is a `Mold` and
- `Car` is a `Mold` or `Rail`.

```C++
// `Radio` is a `Mold`.
template<template<typename...> class Radio>
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
           template<typename...Signals>
           using Mold = Car<typename Radio<Signals...>::type>;
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
       // This is because `Agreements...` will be used to invoke `ClassicTrip<*>::ProtoRoad`,
       // which has only one parameter `Car`.
       template<template<typename...> class...Agreements>
       using Road = ClassicTrip<Commit::template Mold>::template ProtoRoad<Agreements...>;

       // This function composes the conjuration function `Mold` and the `Agreements...`.
       // `Agreements` will be used to invoke `ClassicTrip<*>::ProtoSail.
       template<template<template<auto...> class...> class...Agreements>
       using Sail = ClassicTrip<Commit::template Mold>::template ProtoSail<Agreements...>;
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
           using Mold = Car<Radio<Signals...>::template Page>;
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
       using Road = ClassicTrip<Commit::template Mold>::template ProtoRoad<Agreements...>;

       template<template<template<auto...> class...> class...Agreements>
       using Sail = ClassicTrip<Commit::template Mold>::template ProtoSail<Agreements...>;
       /**** Continuation ****//* End */
    };

    template<template<template<auto...> class...> class...Agreements>
    using Sail = ProtoSail<Agreements...>;
    /**** Define Sail ****//* End */
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwAbKSuADJ4DJgAcj4ARpjEIGYaABykAA6oCoRODB7evgHBmdmOAuGRMSzxiclpdpgOuUIETMQE%2BT5%2BQbaY9mUMLW0EFdFxCUmptq3tnYU9CjMjEWPVE3UAlLaoXsTI7BwA9IcA1CaBGgBKTPio5xoneAonTGcXALKe6PcAdCYaAEECJgWOkDMCTP43MDQeDMJDoQBPdKMViYH4YyHYE7IAwKZ7XW5Y/4AxbELwOE5uPHZZAAFWIeHSJJMAHYrICTlyTocAFT83knAAimBokROl1QNxOAt5x0FQ3aMsOJO5PNO9zcbXuj2er3un1o3wuf053JhYKYEKhFrhCIIyNRbAxf382NxTHxVO1btV3LJFIIJ2UxFQRElNz9XLZHIBau5fIFVNQLBYhDYghlAvlJ0VQblUbVAcpHlThEL3JjFfjPNlyYY2l2VtyWf5Obzyur8eObyuNycOsM6F7WuIg%2BImBxKZKmGHCAS6K7ap7ADE8MRFqQTgB3ScRRaGRxWyf3QkDi4vBjD1CxVoRF69h0o5hsX5LhOnOnzhhb3ePBgAG6oAA1ieFyjjq26EAgJwEPOsGOicE4KF4tBBqgVCwfBN53pEw73E%2BTrwia75crax72o6L7ohiQh4MAzC0AoxJmjW3JeNkRgnIa%2BH%2BEK3pjjaVFohK/Z3FCdEMWICguliIAgIRxL%2BLGbHLnWHgNk2AytnKfInNgV6doCpFnKxqmJvyJwMoYpQtrK7ZLEZcaqVyPYABJ9CixAnFQXgME0Ag%2BSQWGTmwazeeRwK9iutCoNub5mWxPZfk8Pl%2BQFDCwcQNmZO0zxwZOaCadl2m%2Bf52kGl8kHQTsQYREBwERMAjwEFuJk9mIsVQVxvntPO3npKG%2BxerEiInGG/UnAg9H9QAtCQWDeWVGUySZkXwjaIKWta0JbXaQnPmislujiNLHe6NLcV8ABqmD4n0LHOS5xZBiKd60CZVaJS56onAA6pOBDZQwChUAkIVTsVzaBctFUfFVF5EL2PG3fdH0kd9LkcU1CEomcfFXUaqN2AiPFKSpP1skKkKxmte0UZtsIM7tTM7YR1HnadnoyZiJ0eviLoAsAE4gowBDMb6mNqtjXExXF%2BP8W9TB0AiQsixm4vnfJinKe1dbWSDOSBfZekGcOBaY1TNNdhZgqlmmBAazpOZm05NvqbIEReNDmUmwqjkW09y6ftNzywy2aCglkd0Q0VjYlS24eBZVRqDoZBW9mrmCi4IPN/BjQcficURhoDCBWicmAAYwWE7MAMH3FnOea5iF6pQBbR4P2yBboQ40MLQY2dXFeonJxwD0C8xDAD4YumoXrkh6lqXxKIHFgYCwvZxrefVbQtAnPEJzr8OSP1SBG/UtzeD0oyzJQryckgCGYaoBGxoaKQNunNu03IDB5dngCEHv3Sc6Q2homBN5TU2oC5sXWvaembNhLOl5hdbmgst7NwltgLsMtmrvwVlSGkN8GRMgRPbQg2skGTjJm6ahrNJwv3DFKb4UIm473OtbYymNkqhzSuVCO05o75XgnHLSid0pww0GTC8Q4IaNywZw1uGh55JQ1BcDhYtmIXigvvQ%2Bk4T6wVQP%2BBql8SG33IQ/J%2BzDUBCGVrQNRNYEGM22htFmbiERMC8EQTm/Nd58zOhiLRudHpsXwbmBxRCr74lIXfChKYHYMLcYTNh2BklwmDKGIg9iVbsKUdorhuteEe0EF7H2ztTaGUDmqK2xSASFhcR4/aSJDqoNdOggWwSCmhMlkHCJhDIT8Vse/VWPSW4dO4UHW2wpRQrAlKwypgpXaB0LDMkUYpJy5IPn7XMAcVRmT4alJOmVUoZ2yGmAwEV4L3BGawnUWBNnDiYLEVA1cnGLxOAASSDOXK89BRGFU9JOX%2BC4RywIeKlfUFxrgqzgeaGhiDGFIs8VCbxvi0Fcy6R0rFzwIJ9KLEDQMWTX7bMLF9BetYkyUMdmLJZezhhOTYi9ZMZYCBdgpT9KllkNLxwqbsjsNSfpNPZkdWi9FGI4JMhEni0SfRuDPOJNwklJVawUjQ4MTBgAbVwfUrlMzeUSONtmKp5sDkNKlgmfWwNbLGrbHpQV5quUisRa4lpor2lYlxX4y6KM7okwJT9FlSsVaWujOyEy7Fx64xPATP1aNSZVV9HqymrJqb1Lpsit1zMRUoJoji/xPqMHdPVtosJP0Ily23EQkNH18mltzmqnWFMXIzINra32JrlnVKdTWOpLa1LUsSemOluyVnmvdkOspDBvbaQFfsrsLqs2tKIkW7FITxblvjAMxZQziHX0sffNwNKMnHlSU/daJKWGRnrdvQpaCpmLtdc0nNz70WoDXQEzpecN1SsxhE7Z0SLFkKPSe9VjDz30PAyk2xZLb3YKKQOq1U7HAzv5V2/SPbyVpsfWZJdqKX07XfZ%2BkjJa729NwWZADUS92wYcWMhtEzyZrLrBs%2BZgGx1YeMjhjNgJbaygE22Ekba7ri2dsJwTkmhM8IaWYfwERcReCwPjNwPi6CEERI9Ekua2n5seiyrU6QUL0Fw0CN9PiP0PsBCyoQCAfEEBM7xgEMyADyXkfZxnnYywO%2BH3V5s/fWXCCR9NEspG5hIHmWTslMkHHTq6yPYK3WPULQZbFkzMpy8J0bCLRNkMrSIgk3C/sQ9h9NtM8PPo9fm39SWZVfCIWlpNRXxlfsfTx2Mrn3MDE8xh8dLI%2BN1nCwnAQFh6WOu0%2BZpG7xUKODBHgYLfSWVDZ9rTCNFXl1VaSyyxrRozgRva/12LlXKv%2Bcxf4wL%2BWEhbiqy6bA9Ad5bZS1e1AdDj15ZWIVu7CGH2BvDUhsik3LM/AAFJJajTjZQWr4SWwJrZ%2Bzjm3DTbQkyWg83iC8i%2BzveSHdvD5q3MDkrGWDsybVHFjmCWHu/ePtG2VtHskvaa8Vn7q2ysSaTMtgYo3ONmsO51iLAw3BjYXYCJp76TjXU7i8xzlHSRPY57kNwUWB2%2BeZsRs7l0hCYAAI5eEYPsR75JKS1uw/9rkESct7s1zrvX7iJeMilzqqZtTicWqOxtwHpGfg1apwMmjBNjfweUR07Wjo2us4G%2BzrrCv6V9ZkzMtcG4gzYFUKwMEk4vNKkDgBrw6QZzoEuHdGbRC4cEAc%2B4rgGheRmC3BX3k/gtxgA4LyRvzGZMyswK0E5QGD0gYRPLgQDSoSGeMzq%2BSdCZfyVGVCfvDArBQgr0/cfJJ5JwbcDPxXUJG/N44E/WFdaJ8gBpaZgZhe0JEPeB3pgJyx9VWMlCQsix0DyQiMCYWYgAD6RUDyCARC/rcZgsQv4zJH9n9BBMA39aBP8BBv92UoQ/8Th/AtNk1ytZdmxkB39uYEgCAIAQCQAFA0QMCJYFVT9Wpcwc888C9jNYDsANhTM%2BFJx%2BB944ocZ7gDxHB0DMD2gdQFAEAR4pp5YM5UAo9oCp5CphElAn8SQ2Cb5CClB2gcCCAn88CCDPQERCx18EQt8W8oM981CzIZ8583AF8oNXt1DhCGBB9j0mAjNUJR8QBTCpZcCX9wDspICv9Wgf84DBB/9AClwnCwCICoCQYPDYC3B4DECqcksbEodyU3QgCg4hByDo588SCWQ3RaD6l491xFh9IU9YR09esuNXcZlNciphxk9U9J4M98xzUVdkFdMAseIARp4QtDcgwvlAIL4eJjduMB1zdEI90miWiMt79HDFDQDX9XCgiYDf9vCTgAC4i/DxiQBnDAj3DDxZjSCIiZdalkCotw9Xc6j3Ebt1di0vdp4/0AQIkOizFacCYbiuivgA8isLim1Q8nMT8qD38uBz9L9r8QAq0EQHjQIl8nNpCOD7p5DcD8C2BCCERKCZtvitxEjc9kiES0IsQMiOs6xSiBByi8i08Y8e0OAthaBOAABWXgPwDgLQUgVATgRXSwawMeHYPYE8OTHgUgAgTQEkrYYCEAckyQH4DQSQLgVkfwDQckjQMwQIQIMwFINIMkjgSQXgFgCQDQT%2Bak2k%2BkjgXgBQEAT%2Bbkmkkk0gOAWAGARAEAWqdIHxcgSgSOdIOgBIKINETgVQFIQIWaQISQE4YAZAZAE4KQH4MwXgWcQgEgPAJ/LgGQQQEQMQdgKQGM%2BQJQNQHk0gXQaM7cbKdITgHgUkikqktMnUlzHxG09CTCd0z07030/0wMoUswE4CAUsR0%2BgaBDkjYXgI0rQLYCAJAB0p0sgCgCAfs1skAYAKQavGgNCBIfUiAWINM2ICINoREXM3gRc5gYgREFzWIbQRoI0zkyODWFzAeFc400gLAWILwYALUfefU7gXgLAFgQwCeA4Wk/ACcJoauO82kzAVQRoHxA4Tk5wpU2k1HWIbKTcjwLANMoGPANU%2B80gauYgV5JQEUJ8owVHIwHkrYKgAwYABQa6ebbccLakzk/gWM0QcQRM8i5MlQdQM8jM/QZ8lAawawfQPAWIfUyALYIQgYO82aR/IZUwJkywZIXgN5BIRkLALiiALYBoDKFwK8OYPwaMsIFYKoGoPQEoI2PITwLoLSrIHS0YDSiYaM%2BSgYPMZSvQcy5oJYYy8YRIMypYKypy4Yey8KCQOS1k/YTy/QAs0gLU8SzgE4Ssr0n0v0gMoMhsiAXAcMts/wLgDsrk7CrYecG4CYWS0gfkyQfwH4AATn8FZEkBFLMEkAuElMCDyr8uVNVICC4B%2BECC4ECBSDypSCasFK4HJIKuCECrpM4D1INOSuNJ7ItN7KtNLNtKHJHOdNdI4DaBYAAlZFmleA9C4i4Dyp%2BHqp/PwCICkr0BorjKoukBosUDorTN0GryzOsNXPzI4EpICqLM4BLIIDLPGkwnmsWuWq5jWo2q2sbObIHLODkzMCSq7JNLGumsHPtOnAHJAA%2BqWtWvHLyorz4DoCgVnPnLPPXOXNXNIGxs3O3N3IcFxsPLFmPMHjTIvKvJvKYlxsfOfPEDPPfL3LwC/LTN/P/OBFxuArTLAogsRCgtfM7MZHgs5KQpQswDQoZqamwr4DwoIqIpItxoOsooTOOtkFOtTIYqSCYqwuEqsEsHYs4vgB4vSD4s4AEsUKEtYtEu1KQqkruhNt6H6FyEUvcD0sKFUqvHcs0ujO0oFw9pUoyEMoGB9tMudpZoEEssDusr6EjsGDsvUocusucpjtcvaDDscq8t2B8sSuqvut6p1KngWqWpWoMB%2Bs2uFMbNit2qBoStBpStIDSsWkoFupVNIDVP8A2pFNZC6tZHFMkFKu9OjMLv6tsEGrBpGvgDGutMmuhtBAHJdLYE4HmurJYAUAAgDIAnWp%2BDhEWFDJ2ojKjKTMOrVqTM1votpN0HryupzPvNuoLseo4GeteowmLrXo3q3p3r3qDCbJhtbLrv8AbuGtNL7P/quymvAcSE3tz3f23ryvfx/owOIBYG9NRunI3EoExtpPxtPM5NwcJr3JJsSTJpPMpswEvOvM6jvM5PpowqFvPPXBZrZrPI5uQAAu5rAJAt4D5uXMFpgpFtxvFujilowplpAdwq1QVswGIufGVtkFPokHVsEAvvOoCF1uMBtpsDApktNvNqOBAP1usDErpPtsjMdu4ojoUogFcBcpCG9qTo8r9pDoVzTuDo7UztjpdqjtToKCDpsp8bcscd9umGGDsYPAzuCdMuzrZN8qVMfrPKLtXp9PXs3pOHgd3uPByJisPvisSs7MbuboyrbtqrMA2v8H8HJKlNFI1IqdZGaoesSbHv1MNMbuyvJPyvJJSBlLyskDyvFMKq4HryVP8ELKad1KGu7NupDMae1LHsnq2CQuyGcEkCAA%3D)

## Links

- [source code](../../../../conceptrodon/mouldivore/classic_trip.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/classic_trip.test.hpp)
