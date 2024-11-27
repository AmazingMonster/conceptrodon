<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::ClassicTrek`

## Description

`Pagelivore::ClassicTrek` accepts an operation.
Its first layer accepts another operation for composition.
Then, it returns two commitment functions and twelve continuation functions.

- **Commitment**
  - **Conjuration:** When invoked, the function instantiates the first operation with the arguments. Then, it invokes the second operation using `Omennivore::Send` with the type result of the instantiated first operation as the packed vessel.
  - **Transition:** When invoked by a vessel, this function transports the conjuration function to the vessel.

- **Continuation**

  When invoked by another operation, the function returns a `ClassicTrek`
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
ClassicTrek ::   template<auto...> class...
              -> template<typename...> class...
              -> ...
              -> template<auto...> class

-- Compose with Page
ClassicTrek ::   template<auto...> class...
              -> template<auto...> class...
              -> ...
              -> template<auto...> class

-- Compose with Road
ClassicTrek ::   template<auto...> class...
              -> template<template<typename...> class...> class...
              -> ...
              -> template<auto...> class

-- Compose with Rail
ClassicTrek ::   template<auto...> class...
              -> template<template<auto...> class...> class...
              -> ...
              -> template<auto...> class

-- Compose with Flow
ClassicTrek ::   template<auto...> class...
              -> template<template<template<typename...> class...> class...> class...
              -> ...
              -> template<auto...> class

-- Compose with Sail
ClassicTrek ::   template<auto...> class...
              -> template<template<template<auto...> class...> class...> class...
              -> ...
              -> template<auto...> class

-- Compose with Snow
ClassicTrek ::   template<auto...> class...
              -> template<template<template<template<typename...> class...> class...> class...> class...
              -> ...
              -> template<auto...> class

-- Compose with Hail
ClassicTrek ::   template<auto...> class...
              -> template<template<template<template<auto...> class...> class...> class...> class...
              -> ...
              -> template<auto...> class

-- Compose with Cool
ClassicTrek ::   template<auto...> class...
              -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
              -> ...
              -> template<auto...> class

-- Compose with Calm
ClassicTrek ::   template<auto...> class...
              -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
              -> ...
              -> template<auto...> class

-- Compose with Grit
ClassicTrek ::   template<auto...> class...
              -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
              -> ...
              -> template<auto...> class

-- Compose with Will
ClassicTrek ::   template<auto...> class...
              -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
              -> ...
              -> template<auto...> class

-- End in Transition
-- Compose with Mold
ClassicTrek ::   template<auto...> class...
              -> template<typename...> class...
              -> ...
              -> template<template<template<auto...> class...> class...>

-- Compose with Page
ClassicTrek ::   template<auto...> class...
              -> template<auto...> class...
              -> ...
              -> template<template<template<auto...> class...> class...>

-- Compose with Road
ClassicTrek ::   template<auto...> class...
              -> template<template<typename...> class...> class...
              -> ...
              -> template<template<template<auto...> class...> class...>

-- Compose with Rail
ClassicTrek ::   template<auto...> class...
              -> template<template<auto...> class...> class...
              -> ...
              -> template<template<template<auto...> class...> class...>

-- Compose with Flow
ClassicTrek ::   template<auto...> class...
              -> template<template<template<typename...> class...> class...> class...
              -> ...
              -> template<template<template<auto...> class...> class...>

-- Compose with Sail
ClassicTrek ::   template<auto...> class...
              -> template<template<template<auto...> class...> class...> class...
              -> ...
              -> template<template<template<auto...> class...> class...>

-- Compose with Snow
ClassicTrek ::   template<auto...> class...
              -> template<template<template<template<typename...> class...> class...> class...> class...
              -> ...
              -> template<template<template<auto...> class...> class...>

-- Compose with Hail
ClassicTrek ::   template<auto...> class...
              -> template<template<template<template<auto...> class...> class...> class...> class...
              -> ...
              -> template<template<template<auto...> class...> class...>

-- Compose with Cool
ClassicTrek ::   template<auto...> class...
              -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
              -> ...
              -> template<template<template<auto...> class...> class...>

-- Compose with Calm
ClassicTrek ::   template<auto...> class...
              -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
              -> ...
              -> template<template<template<auto...> class...> class...>

-- Compose with Grit
ClassicTrek ::   template<auto...> class...
              -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
              -> ...
              -> template<template<template<auto...> class...> class...>

-- Compose with Will
ClassicTrek ::   template<auto...> class...
              -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
              -> ...
              -> template<template<template<auto...> class...> class...>
```

## Structure

```C++
template<template<auto...> class>
struct Trep
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

- In the first example, we will compose `OperationA<Shuttle>::Rail`, `OperationB<10>::Mold`, and `OperationC<'*'>::Rail`.

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
    template<auto...Variable>
    struct ProtoPage
    {
        using type = Capsule<Sequence<Variable>...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
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
    struct ProtoMold
    {
        using type = Carrier<Detail<Agreements>::template Page...>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};
/**** OperationB ****//* End */

/**** OperationC ****//* Start */
template<auto Variable>
struct OperationC
{
    template<template<auto...> class...Sequences>
    struct ProtoRail
    {
        using type = Capsule<Sequences<Variable>...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};
/**** OperationC ****//* End */

/**** First Example ****//* Start */
using SupposedResult = Capsule<Shuttle<10*2, '*'>, Shuttle<10*3, '*'>>;

using Metafunction = ClassicTrek<OperationA<Shuttle>::Page>
::Road<OperationB<10>::Mold>
::Sail<OperationC<'*'>::Rail>
::Commit;

using Result = Metafunction::Page<2, 3>::type;

static_assert(std::same_as<Result, SupposedResult>);

// The following `static_assert` shows how the operations are composed:
static_assert(std::same_as<
    Send
    <
        Send<OperationA<Shuttle>::Page<2, 3>::type>
        ::Road<OperationB<10>::Mold>::type
    >
    ::Sail<OperationC<'*'>::Rail>
    ::type
    ,
    SupposedResult
>);
/**** First Example ****//* End */
```

- In the second example, we will transport the conjuration function to `InvokeRail`.

```C++
/**** Second Example ****//* Start */
template<template<auto...> class PageArg>
struct InvokePageDetail
{
    using type = PageArg<2, 3>::type;
};

template<template<auto...> class...Args>
using InvokePage = InvokePageDetail<Args...>::type;

using Result_1 = Metafunction::Sail<InvokePage>;

static_assert(std::same_as<Result_1, SupposedResult>);
/**** Second Example ****//* End */
```

## Implementation

We will compose functions using `Omennivore::Send`.
For example, we can compose a `Page` and a `Road` in the following way:

```C++
template<auto...Args>
using Metafunction = Send<typename Page<Args...>::type>::template Flow<Road>;
```

Note that in order to succeed, `Page<Args...>::type` must be a packed `Road`, meaning it is of the form `Vessel<Items...>` where `Items...` all have signature `template<typename...>`. This requirement is not checked by `ClassicTrek`.

We will implement `ClassicTrek` by performing recursion manually, meaning the function will recurse only once for every invocation of a member template.
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

- `Radio` is a `Page` and
- `Car` is a `Mold` or `Rail`.

Here is the entire implementation.

```C++
// `Radio` is a `Page`.
template<template<auto...> class Radio>
struct ClassicTrek
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
           template<auto...Signals>
           using Page = Send<typename Radio<Signals...>::type>::template Road<Car>;
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
       // This is because `Agreements...` will be used to invoke `ClassicTrek<*>::ProtoRoad`,
       // which has only one parameter `Car`.
       template<template<typename...> class...Agreements>
       using Road = ClassicTrek<Commit::template Page>::template ProtoRoad<Agreements...>;

       // This function composes the conjuration function `Page` and the `Agreements...`.
       // `Agreements` will be used to invoke `ClassicTrek<*>::ProtoSail.
       template<template<template<auto...> class...> class...Agreements>
       using Sail = ClassicTrek<Commit::template Page>::template ProtoSail<Agreements...>;
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
           using Page = Send<typename Radio<Signals...>::type>::template Sail<Car>;
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
       using Road = ClassicTrek<Commit::template Page>::template ProtoRoad<Agreements...>;

       template<template<template<auto...> class...> class...Agreements>
       using Sail = ClassicTrek<Commit::template Page>::template ProtoSail<Agreements...>;
       /**** Continuation ****//* End */
    };

    template<template<template<auto...> class...> class...Agreements>
    using Sail = ProtoSail<Agreements...>;
    /**** Define Sail ****//* End */
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGErqSuADJ4DJgAcj4ARpjEIGZcAGykAA6oCoRODB7evv6p6ZkCIWGRLDFxCcl2mA5ZQgRMxAQ5Pn5cATV1Ag1NBCUR0bHxSbaNza15HWN9A2UVI4kAlLaoXsTI7BwA9NsA1EJ4LCm0eDSY6HsmiRpCrtcae1ReDN0MAHQmGgCCBJjHBj%2BJgAzG4CABPFKMViYPbKJjIADWFwAapgFHYQdgvt8FARiF4HAdXFcAOxWUkAERBVh%2BOL%2BAKYQNBDJOTMwILBkOhbHefKxe2QBgxew8giYoVipD2EKhzF5fOw9DYggUWJxeIJRLuDHQnLFjUlxE5Sv%2BjAICj5n2B2JtOJM5Jxe2dMv%2BbOZYLdgI5LO58swVoFQqYIoA8lDiEysuqfi69prCQQ9pTMIbaE6Xbs9gBJBgAN1QyKuN3DsSjAgeewA7oQEDKELCHqaVRbAzdPrGXQ6LHsvBkjDLuVdgZS9qXI44K6Dm%2BbLfy7cCew7qYv7Z3nazvZzN%2Bzt36YYGbYLhXP3t9gMRMGbVTHvnG%2B6FgHsAEqoJiXEGjlNpznny/X1t52wEAQFlH1aW%2BZcaTXX4vV3Fk4I9HcPSYLwiEPbBjxDU8gxPA4iCRYhUFQFhpWQn03FQ9CgKwjErTuABHLxGE2NU7R%2BBNtXuUEGlQQjiJYTlGOY150Qw29uwzDdEIo8jtxkzkqNQDDaJwo9gzDCNywYW8404pNvwldN1z2LNcwLIsHnHbTKxrAg63sxsbmElixP5dspLJHsHwHMDh1HazJx0njMCY1y1NtJcqWgukTLkhDGSQhTQSUlSNIi1SrT/K8WzY7ETJ8p8hCM/zk1TIzfwvHLZwwkCwJiyDotXWLIJ%2BLMHmfd8nErPAFD2Jhiw0eFgA5Dyfniz1Eoo1KaPSl8utQW99NFE88GQAAVS9EXtR0TO2AAqQ79rKmgwhfN9LiO/bdmO3pmj2a7PPam5KONG49l6/rBoAWU8PUxrvF0JuB/cFWtTC5te3SXWW5QiKIV9308ySTMzK7RRIlhCBbB6jpu/C%2Bge7ZPJh/FEwxlgsYIEnnRRwG4wZg6joxhhtHWbTccO/G7qTR7UYZ0z9g6hbK0MD8XqaUXL0FEi0iUS4G0vDt6YF6SpsUtDlL5Q5gGYWg8pphnCrhJgRtKnU9V9OUYXm/BFp4vBdbECK6u5LE6pk86kdBKGFwg1W4yZw6WbZicsk566Dr2bBdSJmCA67fnGfRzbDAyIKI%2B58ZeeJpPA/2AAJTBaAjJ4XjeJ4SHrWE2HKWJXSmwbiroB5lYT50s3WhBPueV4M/xNO0maPrHJl1n2Yz3uK4eYbRseOyEDWJNQgsx8PoIaVDfz/raFoVAawHZ5mkVvYUiI1i%2BqicE9lQRziD2bvgEVgBaEgsHvqegstLegeSyb3Vkn/Ga4NMqzTwrPNEGJi7QwTstQyLc85dl2irdugs9gAHVYQDwYAoKg9dR5oHHmHAQZc%2B7hxnqbOeMpUCDQgeiTEANUH3n7E%2BPyn4TYjUgZiUEs91TNRQQLKC/Cf5qwAfJdWCUxEpU1mlE8sjsJZSqgBA2iDnTG2brQUq8D0ygmyso2qoE3b8NQUHY6qccFFAYJnKOMdLq5wEWSFc/sBamIplTHGV18a2Lji1VWriDShC8BzTxUceY%2BIcZ3bufVP7hzQMcdI6Jq5j1DhzGJJCKEjVFrHUeDw9G5TbBoNuLj9jhFvlghATI9iYDzIwesawn6DTyTVdyjxPp5iaHgLqyBpSEBvgwWg18xB7yrH1AaLD6D9WIMAHw5oimM32F3T6n0YiiD7E5H4Sj8ktOrHQTRMRezy2oR9fMhZ1luFWhtLanJ9ruxAHDW%2BqBEb/Q0KQQ2WYqzd2QHWCpfUBADL6bCFITQYR/Hvg8KGjCBbAz/mBf08i6J8iaTediDjjZPNKuc7Ca1NqYG2j7TGhAPaN14TaIlAC4Tw0eRdSq/4tngwam8hZUTSEVziXLRJBCBApMnuXDOGSqFiySbkzZzTPiQvmY0kVN53o1l3nsfZazLhEGORZM5FycV4rcDc0ldzKUaLmXGaFEj/5bmkdREB6V4WniRRaGBzC14aIxeqq5%2BLKaEtAp7ElwEPXEr1RVXRUrAL0uMS49GASGBBIziE463i%2BYqyERBTyRqpFcmtmDXCCjEWBpUSrNFF1Sr3IRtSgNtLRV8OcR3dGKZTqwnRdG6Osc41PSrZgGtBwSr1rCXG7eizom8vDp9UeGQsYGHvjkm4haqVI3elgGtlwmBRFQDUg1ZkkwVN1PQEeDZBQhlhB82IZzJbvU%2BgNYWLdxUNxTcm01lEZFgMzRavCvt8oq1hn6hB8bkF%2BLDQSggHi8ahOzuE1Wy0PBuupknOmJif1EOCQB26QHu3twmsAnWesc2oONrPc23FU08lrSLB2Tt9YGPqjq8i7aW4%2B0ln7ERpkYPcvDvW2N9i6OuPMenJj8GCb3SQwna98ETWCeARmhFj7sIcMwFw6BKLUFwPKh%2B1BUGmEHLXmwkcknpM6LcF6hqSmmqJtUZem9AmUJ3vE2J0T1rs12tVuokq7DtE0uqqqUjRiK0B3Y5GCxUbuMscNgmt5P7wP/q5jYxtrGk7%2BNkIEuDYWEOEz44amFMLQYBnvWJm1GGBZ5vfE6rFlzcX6l/WS70knbkUcnU85z%2BigIMqTqZwBxqRPqTkRl6zpbkUvrsywyjmj2GYoxNil1bgwNU1K%2Bycr5HPXvu01l8SIbk7M3DZGrj8WG12ORgZ%2BOv9jWNY1uaqzVrFGddtbJl09m6AFtmzVul5bm3M2rZKPr1iY0RZ2k4mCpiro/a5jidj6ILSZ3%2B790Hf2WrmGBKEIUXgsDDjcGhOghBwQSXGkA8zS0ybagQGhAg9B6uwT22l8SHEsdJkoikBQXh8fCLR3t9Hh3WsPsx1qcnTRiB4FiAT1xgUsh3k7Yh%2Bx%2B2zVaws31FyokWfk15wIVqjUlxxQZ6LlEHSF00%2B66TVnFKHm8JMspnLvX1Ojgp1TmnbgJebE5CrjnaufTYAWx5wLvjdspuAVlu1WHKHXZ15Q27ZbaN0m221dGMuGD878%2B9lqPOtJBR7ALxLQuld7G%2BtTxwJxOfGhRctUPiav0u5M8TurJl5Npi8k7uXyX6fNYx0zkUFvMDSmAdmO1Jf/Xm9CiJS3oJswLY17TPPDMUPmYAFK2bUb17D7D6%2BchT7QNPpxYj7R73yaUw%2BHdbc%2B870RBe03pbPDZ87zo30PN%2BrQPUeuB9G0N0OAb7OM%2BcicyWlzZ3vWVcoevi/m%2BK/58E7Cg8WbTtstx815T8PwNNJ1QC/dXM6thEg9vho8yxY9XsNtwkQdmZQ83BkCu1E9q9lVrdOkoh1cNQycxwY8sg3AdoPNhdb1GcIY2t3h68gD4wSCqsKoL8PN7VfIb8NMTdqcKJGCrdVdCC7cP9P0v8k0UtcDRcjsADn8mC0UHNwDKVOoqM3B5sYDc8v8EDiFshkD/Mo90YAAxPAYgPEaOVQVgE4WEePXjexdRLwFIdldAZ8dEVPDFJgSnPgoSHHAgPHCiLgDQfaMwaUMADgfaUIrEaUIQHwvwzkAI/aYEEIsIiIhcSKGCY2b6cqNJKxAbZ1IrUEUPSCHiGI9XECXTH4ECarAosggQKwUEAI25SAlFECDRTkDAzkUI8IjgW5FQnRF9ECMbQgAnNFVwufUqTIxobIso33UEYIvYYECrdzGCPEKMZAAAfWwliAIAgDxHQBAgUBhA2LYjcBcNNw3gOAcKcNONTyxCWG5yZVhH4F3n3jXgeBWMcHWM2OaErAUEXhGQfn3iSVQBqJwUmVhDZQST2OINWKOKUGaB2IID2JAAOLYCOM5E8gtmRlBC3kxOqMQL528Nx1KLuRmLcDmIWPIyMT7wZkqOLTcBzziI0EaL%2BkWKhCxOpJaLb3aNBE6JSO9V6LtVdjZJMleRMiEEuMhOuLn3tBtDuP4VcWMNMKTGwAsIBGsIj02wMOZjuEIUuBVMsImRsJznpEkNdxrzoIk1nm%2BCmSlyJHMlOVnic0Dw82NiN0k2tOAE5HJNZPAg%2BwJ2oJawtMyymRzWNntOREnw03DJUEoUfzUJDLczZNp2%2BBGLOLWK4HGKyP7WcBAFaO7xOQjJmLSJaneLWlhK2IRKRJRMwDRNBClIIHTKiIlPlnrNuIalcR1IED1NVKsL0Iiw4BWFoE4AAFZeA/AOAtBSBUBOAKDLBrB4w1gNhGwzBgQeBSACBNAByVhEQQBhzJB3gNBJAuBSRgQNBhyNAzBEhEgzAAAOG8/QTgSQXgFgCQDQF5ccyc6cjgXgBQEAF5Dcicgc0gOAWAGARAEAJeFINCcgSgNlOgWIcIGETgVQG8xIZ%2BRISQPYYAZAZAPYKQd4MwXgC4QgEgPAPYgIfgQQEQMQdgKQGQQQRQFQdQQC0gXQAIKsSMFITgHgQckcsczcqczgUMNCKCpMVAKgPYFCtCjCrCnCvC/cswPYCAMDFIeCsFFcrgJYXgACrQFYCAJAOC%2BgMgCgCAQy4YYAKQYImgOfWIX8iAKIASqIUIJocEbi3gJy5gYgcEUMKIbQWoACtcuJFsUMfpVylirAKILwYASiXeX87gXgLAFgQwYAcQcKkw/yvAGpOKyczAVQWoNCLYNc0IP4Icli04KISMLyjwLAAS/EI4Ny0gGpYgRdJQFMJKowU4IwTclYKgAwYABQFETnKsUscctcyi4QUQcQOi8axitQASti/QZKlAawawfQPAKIX8yAFYYEr%2BTgZ%2BXYz8UwOcywMwT8pqjnLATaiAFYLoIKFwXUSYdoQIXUOYIYOIAIOWSxR6vQT6oKV6uud62wYuDKnobOb6zoYGt4Hmf6hYToMGzwNoPQFY5oGG4YTS1YdYTYCQXijgUc0gD83gL8yS1C9CzC7C3C/CxSiAXAEi9S1crS9c7qlYBsd8YYa60gHcyQYEd4AATmBFJEkEPLMEkBuDPMSB5ofI4CfNIBfNXPeESCSBvJ5pvKSD3K4GHL5uSAJsEu/NsD/MZsAr0rAv0ogpEugpMrMuIEQrYE4CaBYDzFJGfgGmDAHC4B5veC4APKIvwCIAur0HGuoqmukBmqUDmpYt0GCI4o8Lcpxrxu1q/OEoIFEpvgkrtodqdqwldvds9seGUtljUquBXLMAZp0qApNstpgtMvzqMpADTsdpdosp5oCL4DoFBTsocpYo8pcoaq7q8p8r8ocAaqCvNBCoGQEoiqipiv1gasSuStSsnPwEvDqCyoEtyvyr%2BAauKuLgEvKsqvBGqq2EnLqpfPisatiBaswDarnsfG6r4D6oGqGpGoaoDsmtouDtkFmuYsnIjsWq6qOqsEsDWo2vgG2pSF2o4H2sRMOpWpOrOtiAuvRBAaBvsDuogFcHBuevQFRsBt%2BvIIRqmAKE42KElHmDRuQZBoYB5gwduvqGzmwaRvhtyCeuRv6BIbeuxoxqXI4dKrjoEqJrrozobrwuzoPKUppt9sLvpu0qZtIBZvfkoBxultlvdsPNJA1tJBPMkGFowoCHjs4B/P1tLqNvgBNsgvNtguroQqQo4DtpkpYAUDzFwrzDdveG9DxG9tprIv9tkEDrfvovkFDq/p0BAESKjq4vitjv4pYoTrNrEtTuIBYDsYcacZcbcaTDzuOALsh2BBLtvvLsseMoscyZrscccLWOcZ5rWLSY2ISYwpbpstMMoA7snN7rCrXNaf7v8qHsxhHtCvHswEiuiqGTirXNno6sPoSvSuXsQZYrXuQAKs3sEG3rKvWr3oPtqo5xPrXKaovqvo6pvsNrvtNgfswGGrlGfp8dfokHfoYsCfmpCd/uMBgZsHKqutAfAe2F2OWuOosFOsJvOrIsQa2vIbeHuvcHwaeuCDYYBp%2BsKCCgwdweIdKHYYhpQdob6GochqCmhuhdhpmAmAhYYdmFxbRpusXKxvRp4aic/M4EmUScwvsccb2AqdcfZDMOpp9qrkh00ukcNuZswFZriHZtKqUfiHduBGBGHPPKPLfIldJESHvL0d1t/P/Jkc5uHN5uHJvMvJ5skB5pPP5q4ESNKuBGpcJv0YNt0pxsIvxr4YtaMZWCaoyGcEkCAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/pagelivore/classic_trek.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/classic_trek.test.hpp)
