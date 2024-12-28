<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::ClassicTrek`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-classic-trek">To Index</a></p>

## Description

`Mouldivore::ClassicTrek` accepts an operation.
Its first layer accepts another operation for composition.
Then, it returns two commitment functions and twelve continuation functions.

- **Commitment**
  - **Conjuration:** When invoked, this function instantiates the first operation with the arguments. Then, it invokes the second operation using `Omennivore::Send` with the instantiated first operation as the packed vessel.
  - **Transition:** When invoked by a vessel, this function transports the conjuration function to the vessel.

- **Continuation**

  When invoked by another operation, the function returns a `ClassicTrek`
  - that is instantiated by the conjuration function and
  - whose first layer is instantiated by the new operation.

In general, this function composes operations together in a similar fashion to `.` in Haskell.

<pre><code>   Oper<sub>0</sub>
-> Oper<sub>1</sub>
       &vellip;
-> Oper<sub>n-1</sub>
-> Oper<sub>n</sub>
-> Args...
-> Oper<sub>n</sub>&lt;
   (unpack)Oper<sub>n-1</sub>&lt;
       &vellip;
   (unpack)Oper<sub>1</sub>&lt;
   (unpack)Oper<sub>0</sub>&lt;
       Args...
   >::type
   >::type
       &vellip;
   >::type
   ></code></pre>

## Type Signature

```Haskell
-- Compose with Mold
ClassicTrek
 :: template<typename...> class...
 -> template<typename...> class...
 -> ...
 -> Commitment

-- Compose with Page
ClassicTrek
 :: template<typename...> class...
 -> template<auto...> class...
 -> ...
 -> Commitment

-- Compose with Road
ClassicTrek
 :: template<typename...> class...
 -> template<template<typename...> class...> class...
 -> ...
 -> Commitment

-- Compose with Rail
ClassicTrek
 :: template<typename...> class...
 -> template<template<auto...> class...> class...
 -> ...
 -> Commitment

-- Compose with Flow
ClassicTrek
 :: template<typename...> class...
 -> template<template<template<typename...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Sail
ClassicTrek
 :: template<typename...> class...
 -> template<template<template<auto...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Snow
ClassicTrek
 :: template<typename...> class...
 -> template<template<template<template<typename...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Hail
ClassicTrek
 :: template<typename...> class...
 -> template<template<template<template<auto...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Cool
ClassicTrek
 :: template<typename...> class...
 -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Calm
ClassicTrek
 :: template<typename...> class...
 -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Grit
ClassicTrek
 :: template<typename...> class...
 -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Will
ClassicTrek
 :: template<typename...> class...
 -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment
```

```Haskell
-- End in Conjuration
ClassicTrek
 :: Commitment
 -> template<typename...>

-- End in Transition
ClassicTrek
 :: Commitment
 -> template<template<template<typename...> class...> class...>
```

## Structure

```C++
template<template<typename...> class>
struct Trek
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

- In the first example, we will compose `oper_0<Shuttle>::Road`, `oper_1<10>::Mold`, and `oper_2<'*'>::Rail`.

```C++
/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** Capsule ****/
template<typename...>
struct Capsule;

/**** Carrier ****/
template<template<auto...> class...>
struct Carrier;

/**** Oper_0 ****/
// This operation wraps around
// each value result of the `Vals...` using the `Pack`
// and holds the result with `Capsule`.
template<template<auto...> class Pack>
struct Oper_0
{ 
    template<typename...Vals>
    struct ProtoMold
    {
        using type = Capsule<Pack<Vals::value>...>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

/**** Oper_1 ****/
// When invoked by a list of packed sequences,
// for every one of them,
// the operation creates a function
// that multiplies each value inside the sequence
// and extends the result by its arguments;
// then, the operation collects all such functions in a carrier.
template<auto Multiplier>
struct Oper_1
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

/**** Oper_2 ****/
// This operation instantiates each pack by the variable
// and collects the result using `Capsule`.
template<auto Variable>
struct Oper_2
{
    template<template<auto...> class...Packs>
    struct ProtoRail
    {
        using type = Capsule<Packs<Variable>...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

/**** SupposedResult ****/
using SupposedResult = Capsule<Shuttle<10*2, '*'>, Shuttle<10*3, '*'>>;

/**** Metafunction ****/
using Metafunction = ClassicTrek<Oper_0<Shuttle>::Mold>
::Road<Oper_1<10>::Mold>
::Sail<Oper_2<'*'>::Rail>
::Commit;

/**** Result ****/
using Result = Metafunction::Mold
<
    std::integral_constant<int, 2>,
    std::integral_constant<int, 3>
>::type;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);

// The following `static_assert` shows how the operations are composed:
static_assert(std::same_as<
    Send
    <
        Send
        <
            Oper_0<Shuttle>::Mold
            <
                std::integral_constant<int, 2>,
                std::integral_constant<int, 3>
            >::type
        >
        ::Road<Oper_1<10>::Mold>
        ::type
    >
    ::Sail<Oper_2<'*'>::Rail>
    ::type
    ,
    SupposedResult
>);
```

- In the second example, we will transport the conjuration function to `InvokeRail`.

```C++
/**** InvokeMold ****/
// This operation instantiates the `MoldArg`
// by `std::integral_constant<int, 2>, std::integral_constant<int, 3>`
// and returns its type result.
template<template<typename...> class MoldArg>
struct InvokeMoldDetail
{
    using type = MoldArg
    <
        std::integral_constant<int, 2>,
        std::integral_constant<int, 3>
    >::type;
};

template<template<typename...> class...Args>
using InvokeMold = InvokeMoldDetail<Args...>::type;

/**** Result ****/
using Result_1 = Metafunction::Flow<InvokeMold>;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult>);
```

## Implementation

We will compose functions using `Omennivore::Send`.
For example, we can compose a `Mold` and a `Road` in the following way:

```C++
template<auto...Args>
using Metafunction = Send<typename Mold<Args...>::type>::template Flow<Road>;
```

Note that in order to succeed, `Mold<Args...>::type` must be a packed `Road`, meaning it is of the form `Vessel<Items...>` where `Items...` all have signature `template<typename...>`. This requirement is not checked by `ClassicTrek`.

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

- `Radio` is a `Mold` and
- `Car` is a `Mold` or `Rail`.

Here is the entire implementation.

```C++
// `Radio` is a `Mold`.
template<template<typename...> class Radio>
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
           template<typename...Signals>
           using Mold = Send<typename Radio<Signals...>::type>::template Road<Car>;
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
       // This is because `Agreements...` will be used to invoke `ClassicTrek<*>::ProtoRoad`,
       // which has only one parameter `Car`.
       template<template<typename...> class...Agreements>
       using Road = ClassicTrek<Commit::template Mold>::template ProtoRoad<Agreements...>;

       // This function composes the conjuration function `Mold` and the `Agreements...`.
       // `Agreements` will be used to invoke `ClassicTrek<*>::ProtoSail.
       template<template<template<auto...> class...> class...Agreements>
       using Sail = ClassicTrek<Commit::template Mold>::template ProtoSail<Agreements...>;
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
           using Mold = Send<typename Radio<Signals...>::type>::template Sail<Car>;
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
       using Road = ClassicTrek<Commit::template Mold>::template ProtoRoad<Agreements...>;

       template<template<template<auto...> class...> class...Agreements>
       using Sail = ClassicTrek<Commit::template Mold>::template ProtoSail<Agreements...>;
       /**** Continuation ****//* End */
    };

    template<template<template<auto...> class...> class...Agreements>
    using Sail = ProtoSail<Agreements...>;
    /**** Define Sail ****//* End */
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKz%2BpK4AMngMmAByPgBGmMQgZgDsABykAA6oCoRODB7evgFBmdmOAmER0SxxCclpdpgOuUIETMQE%2BT5%2BgbaY9mUMLW0EFVGx8Ymptq3tnYU9CjMj4WPVE3UAlLaoXsTI7BwA9ABUp2fnF5fHhyYaAIInZwDUACKY6a6MyHiYCk/nN3ujyuIIugLutzuBEwLHSBmhJgAzG4CABPD7MNhPZRMZAAa0w6AAar87EjsJDFsQvA4nkJXE8TEkrEkXkirPdIdDYfDMEiUTC4UwEci0RjWJgAHTS8lPZAGBR/DyCJgrMhPMWMCXSyXYehsQQKcmUgjU2n0hjofnK1pq/l6mGMAgKHXGxEUznMyFPH0awW8/ncoUilHorVsV3uuUKv4AeQ%2BxGFuWN919TypNIIr0wtto3t9h0OTwAkgwAG6oAmMgBsGnj8STAhMtaeAHdCAgNQhMDWNA6Dc7XbXJfmfUyLE8vNkjBqw4zES8nvXEwN7fqnS6Ze72YzWezIaO/TzhXzRf6T4Gw5ipVvsNGmIqdXdgMRMI7DSm7mmp%2BFgE8AEqoEw6Dzouby5vyz6vu%2Bg63iAICavunpsoiHIQvcQYBmex4hphF7IkwXhEJGd7yg%2Bm4jlGZGKnSRD4sQqCoCwpBHsGp5uIRxG3vej7SvSACOXhfL8n4Zuarj8i0qD0YxLCSZggnCRRboehCXqpr6eG4ee2k4exnGoCRPHKVRMZLgmjYMJ%2BaZiVm4GqnmGk%2BoWJblpWPbNnWFmri27YEJ2/kebWAlCQw%2BzKcOh7jpO05/pqoHmQ2q7IiFSkkTuTIoWhh5aexuWBjp%2BlEYZ3HUSZpExk%2BL5vgORrbk5MW/nSDkJfZdCQdVMHlfBiGoQee59ZyQKgiNYKQsCxwljyMGWf8ZzghNo2guC41Fp5/7AU4nlPHgfxML2ACynhWpFGGFQVemXuKEalWZG34KgommpmTxuDGeDIAAKq%2BeL9WhaYTdmNARABQEgQCJy0cM/zggDa21hxxDbbtTz7Z5R20CdGgjg1%2BXYWxV3hjelEVeRr1tNZvq2diDFEIBwFRepX5ps55yvUxLCEAOc2nIWk1DO0MOHlTz20h4LCcwQwtjkzLNy4DyraLss0Q/zSxCw1ctPC562bY9LaGCBnmI9tbQ9mgsJZISTzdq%2BOPM1rPp46G13E0IeDAMwtB1apju%2Bj%2BM4Y0bC50hJopXhKAF65JHte91CFhuSPWFaDDPIib26DQ7jsKwISsrrkPPXJD2CWhr6HZ1r0ss4D32GKUheq1DgvXNXcNPAAEn0CZPFQXhhQMvckF2PZsGsxCsbyvYAGK0KgraefbfvOUWn0ICjfcD4Xpr15k7R/IFcp58rg%2Bb00AiHcd21%2BQgOxZuEFZ4k1hAsW3BZFmIc/tjOfftLbTzpAYuFP4MRURPFQIFCe69gC2wALQkCwBPM%2BAwXRvydudfGWEBSXXDq7IyZV8FmSDiSRUfRKZ%2B2pm1Rylc5bjjQTXIsAB1HsO8GAKCoPEEeR8GD51msgwu6Mr4tiIJfTGJCySnRoX7AOcU5xIkXMQ0kZDkRBzdP9ZemUkIV2XpPfC2CCaYL0Zqa8hDyKmN4pKKCNUNzkMdjIp4s956tRzA5Dq0FaokR6onLOOja6JjYTkC%2BTdS7g1hrQga6ia5s3FpLbmwSy6tyGlI3OghwheBVvNSGAssyJOSavdefx%2BEXwtiUX4XC0A8JPoXIpDBRFY1RmXQ%2BnkrFdSHNjauLlIgQJYQgYUTxMBlkYF2HYMDewtI8TKFsKMyxtDwJtZALFCDgIYLQMBn9557XTL%2BegqNiDAB8E6Je8t8koxRnEUQU4gr3E6hMkcvk6C0CeHEGK1sREP3cr2N65EPrfUwL9ZExwk4gGULTVA9MsakA6UWVs69kCdl6X8AQqzlk9nSG0CU0IJ7GwppIrWzt8URxuiTYyVV3E2PqlI%2Bx4KEpfMVD8n61oOaEGTnpJ4qj3QsrYjTCBYKwZuOsYadKWcoVPDXhvfu59aklKtgfbs3DeGnwlYPQRmNTaNLlc0m5G42lHIYWMrVH57m0Eec8y5IE3luSrMbd6X0GUAqBSCnlQgHK6rTPijB%2BisEGXMeVEl0pxnkt9nLexzq6A0ptb8/5bgYnMoQindl2BOVT0dUQUNeZkQBsFbeLRWsUmOAYOkwe8TQmMyygeXGHqCV4NumY/1BrnS2KpWDBKKbeVpzcJm2CJMc0FjZm8YGPZqXFvLoeQG/aVjNTDU3bJ5d25isKUqwuKND7ZE5gYCeTTaytvBdtLAA6QJMBiKgQZrqXLFizL0y09BZXmwfD2GF8QrkmymZs3W7VcWaUrV%2BnBHFio%2Bp9eTJGFKbKiyzK2tNjNIkA2iUyggcTMlq2hrkrW1MY1S01jLKDuaYOVILkEhDzcclhL9lWomOp3aezED7eh9ig4JQtFaXBRMo4PRjpR72niE4fCBblSd6bo0U0zlh%2BWOGFWNwIyEkdGGonPDrgEotBGZ3IeXu6n9pGTE1osbKMqbLjriOUUGihoHswQWk2mOhZng2xVnB8BKijSH8YTT2v2mjhWWfQWp79BiXZkc076ghdayUfmA8vexjjWzOIghm%2Bt8derCZk6cUV/iG74d5iXBJxHzMRI6TBiWXMnRFz5k8STuScvPBtGkjJaXEMt0y5%2BzzanCXE205VQLAqG0hZZk24C4bvm2r%2BYyvLBAk0nl06qjlcbWXbr5dFoLXa1Hlqkap7zztvV%2Bf/W1rqtj/bWbTb1ul/Wo1oZG9CMbjHE2Ta5eB1xs32vlWc9B8rshKsKeq8VjLpatE5S81g1bf71sA8sTFxtu2WryO5amm7HaYtCqg2OzAA6%2BOFfSyW5CX3hpLRGgtNm088DEEWMV1QrA4Q9gBONTHWPFvmEROEeUXgsDzjcBU/Y6QOuqXJ88IQCAiIEB2WTs6P61vdvuNTLnPP6Do4eNEpg6QFBeD5/NLklamvpRF8Zjisv5enmyhjxLiNiA/AnvzqEP29FC5a7W4XdxUNtAN/ESXgNlwAH0NCFdWqKgp4DvKF1bImWXuydiWnd5gXEnYZneB7K%2BOXtAsyoCoFwzyRIqNtMajOTdGgcT4k8u7w2Ntjo3qeFH%2BXWYb6fJl9Hvkkjltev%2B8SnTmf/mqWps7jQf1GQVsa9WyUSfva2Opq21RDULNSNT7I2z4ONcV/5A3/kPeFDwXD0JcksPPtuezup7Um3aog6anR8HA%2Br63dadm4V2WkmO4TE7rgbugRMO7LU95BIQKgNRk8Wgu1Y/x7Rfia2ShFJhV%2BEhVvyHgngGXiDAQEB7DjxHmYnd0PlQG92KVfBPE2RqTgN6SzBYGLzwDhB%2BD%2BBDzhSeEXx7HCGyAZxXQUlCn2BzzLkwFUGhEtALyLxjyeTAUID2j2QOWCzQhckCgYBYngMQKlU8H6D2mNXTBpE7BqT%2BHCFf1EGIDt2IHtj%2BxEQOmwNwPtwpWb0vy4D%2Bm%2B0718ytxAzNDshcTDToTP20XqxWw9XN1MjJlSgAJYiF2LD72MyoXkn/2oORGLCFUM13HixUJKklAACltsfR7EcRgAPIQ5HDvC3A1CY8cD394hjhfDpQWIQiV8h9LD9CVsVct9A1Dx%2B9QVB9s5h87FrN4oJ9bdDd%2BQPCj9t8JteMojmshNV8dd19lcu9O1qMGpaNjoW1SjD9oc5t7tT8y1z82ZnczAb8HgTlEUhCdo2FWhUkUD%2BlQ8AFcQ8RWCuEZkDdD0JdgDc80BjVGhnQuFmCsx7FsVNcJcq9bDiongk8DiYgJctDjMZi9CO8bDBda8LcLEG8%2Bjs4SieUNp2ocj4tR8bMYjFxJ8tdp9ti6o3AXi5k3jTxsBsjyjcifjftHiuI69Wsgcxid8ZxwTHl99QVyT%2BVj9u0JiHc2YhAvB0hSl0B/xfhi85iQ1mTWT2To8swai7j2IxcCBed2IuANBjgzAWIwAOBjhZTyQWIRSxT%2BQJTjhEQZS5SFTM4KQ19AYDoXEakuTrMDTWgjSJ8I07U3AW9JJudRT3iLsnN7h4Id1kRnddDkQJSgUnS7h4IIM3TL8zB%2BRZT5SOAgVqSKV4I0MGTng%2BTOTjcqUOSWDwdTSmAal4Iyj%2BRiiCB0B4JwhoQXwxAncKlFhDApZkR8yWIgz3QgCQScy8zBBMBCzaBiyBBSzBB%2BRKynhERPweNvFOja5fgclFc1ckxkAndyJ4gCAIBFhcyQAFAJQJzkS4yY8lSeSrY2SkzyzsANgHd8kex%2BBjV54mpPJSzHBxzJz2htoFBb5Ww/hbyuEECkpcgODzYmJWSQATQxylylB2gZz6z5zFyHwsyGoGMopkQ24wKzMQKR80wbSUo7SVSJsyidFGd6EWZZyGyCzEwWySzVjyy3AuzqzsBazUKQM5z8ymycLWyViyzOzBAWIezOsXNmjE5oLmK0wXSZtrSdDVTW9kLD9/DOKuM%2BQh9mK/SocvjkQQztSLsIz/CvFuMGpSLfQmSWSNyVz0MIR3Rdy9SKdKddd%2BZGgBAQJsAidpo5jFp9LjcOdEtSxH5MA6NjcXJ50vdnyL5SD8K5loQC8VV0A7g9ls9gCX9TyALKLmyaL2yCKiLFT0wwrGyIq8K6KKyGLuzjRawaCQJXwCBdg2EdoLj4orjlDTdcICjCSyYg4ArgAnoTDXIHKg4PDPQoN7FqiQ5KrAqxK3A25MKQBwrqKkqOyUqCAqzFTur4rsKiyBrorUqmL/C%2BzuN6S19q8jEyqASKIqrgT7F7L3I98Q5tqCQGqzD%2BMNrOM4tFtAZNLjSmpNKr87NDTF1nAQBwt%2BR9rHLBKYzEtPohy5izyPofypz/y5yFy2Alz%2BQbquA1z1KlBNz%2BTyRdKLAOAthaBOB/BeA/AOAtBSBUBOAurLBrB0wdg9gPIzBEQeBSBhsMbEatg8QAhJBJQNBJAuAkhEQNB/ANAzBqxqwzAUg0hkaOBJBeAWAJANANBSB0bMbsaOBeB59RaKatAtg4BYAYBEAQA750giJyBKASk6B4hIgJROBVAUhqxYFqxJAnhgBkBkAngpBJQzBeBCRCASA8BcyIb%2BBBARAxB2ApAZBBBFAVB1BKbSBdAIbfcZdOAeAkaUa0bNBeBJbYwiJ1bP8nhDbjbTbzbLbra6bZiIBxZ0gdasUSauANheA5bEbSAIAkBtb6AyAKAIAq6JhgApBpSaAY94h58IAYgY7SAYhwg2hURw7eAe7mBiBURYwYhtBziB7SALYBxYwVl%2B7A6sAYgvBgAOJjV59uBeAsAWBDBgBxBF68dzi8BBkN7Ma6DGgiIDgybKK%2BbMb38YhEwR6PAsAu7TQ8AhbN7SBBliAj0lA3gd6jB38jAY6tgqADBgAFAiQfhWx6x0aya3bhBRBxBvaEG/a1Au7g79Bd6UBrBrB9A8AYh59IAtgECUFOBYFZz5FTA8bLAzAJbv6DcsAiGIAtgGhJUXBLQ5g/AIbQgVgqgag9AShAk8hPAuhBGshhHRh%2BGJgIa2GBhskuG9A5HmglgpHxgEhZGlhFHNHhg1Hx4JBWHCb9gDH9Ao6xau7Jbk6jaTazaLarabbs7cBHaC7Sbi7yaQGthuxgIJgWHSAabJBERJQABOREJISQBmswSQWsVm6sIJ0x/mwWkAUmyUasLgasFIIJlINJ/wRm/wEJ6scxwOyW6WkAWWkB8u5Wiu1WhOjW2u%2Bu4gPWtgTgNoFgMsJIWBfaMiGcLgIJyULgem%2B2/AIgRhvQBBj25B6QVBpQdBwO3QaU0O9IAeyOjgVGwpiWzgeOggRO8BePFOmx%2B8bp3p/p13HO98/OxkEmswNx0uhWyus56uzWuu%2B5iYLpxuoJiUvgOgTFduzuwOoevuqe/5keseiehwKemep0Oe1ZLupelete72Ke7e3e/ezG/AV8JoE%2Bru8%2B5AS%2Bqem%2Bru%2B%2Bx%2B1EZ%2Bg4TGt%2Bj%2Bsm7%2B3%2BzAf%2B5F38cpsBpgCBqBzAGBjEKesZpBr2yZ2QNBgOzGuZrB4B6hqwSwfBwh%2BAEh1nF88hyhhcEV6wOh2Ohh5234SV3ofoXIDh9wURwoHhy0PRgRiGoRgYbRjICRgYQ1mRjVo%2BgQBR3V7hm1yVbJK1jR6YYYM10s9oV1kxhQIxr25Z1Z8W2OzgKx1Os21562o5%2Bmp4CAJx4Zi51xkujx0gLxxBSgZZgW0gIWxEXphmpIPJpIZmyQSJ02iG4NrGzgEpspymhWyppANW2prW55hp/WjgFptOlgBQMsK2ssHpyUXkRYQZ5x520Z2QcZ7ln2%2BQaZ/lnQJJ0gBZpZ%2BJoNixjZmppO1QTt7t3t/twdrMU52Ec56nREa58pqp%2Bpx5%2BpkAHtlkp3PtoJp3Pdp3TdyZr5tuygX5zGoFhesm79kFyez%2BiFwQKFhe1FzAZe1ez%2BDesmpFwB0lrew%2BjFtVwO7F3Fz%2B/FwOwlvukl1%2Bg3Cl3gKlq2WlwB%2Bl2tvgcByB6B2Bjl8drliQHl32mdjB%2BdgwYV3BsV%2B%2B5hqVsho4TChV2h%2Bh%2BIRhtV4hp1gYbVs13hyodR8RlLERgoR1k13IH12RvoW1wYLRh1pRtT511RvhmTnR2YLTwz5YaT/Rou7YXYYxizvmldop0Nl9p4Ltntog3dlA/d%2BN4eanIu5N2tzxkPdN3xvmrNoWswXpxEREQIBmiUjQCLpIdJtZkNqW2wUp9xvzvxkASQfwYJ/wFIDmoJyQIJ5m0JrgDUvmxEaO%2Bz5Lm55Zu2xLyt6rlN7%2B7IZwSQIAA%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/classic_trek/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/mouldivore/classic_trek.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/classic_trek.test.hpp)
