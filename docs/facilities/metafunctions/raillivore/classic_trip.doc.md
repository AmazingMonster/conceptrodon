<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Raillivore::ClassicTrip`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#raillivore-classic-trip">To Index</a></p>

## Description

`Raillivore::ClassicTrip` accepts an operation.
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

<pre><code>   Oper<sub>0</sub>
-> Oper<sub>1</sub>
       &vellip;
-> Oper<sub>n-1</sub>
-> Oper<sub>n</sub>
-> Args...
-> Oper<sub>n</sub>&lt;
   Oper<sub>n-1</sub>&lt;
       &vellip;
   Oper<sub>1</sub>&lt;
   Oper<sub>0</sub>&lt;
       Args...
   >::Member
   >::Member
       &vellip;
   >::Member
   ></code></pre>

## Type Signature

```Haskell
-- Compose with Mold
ClassicTrip
 :: template<template<auto...> class...> class...
 -> template<typename...> class...
 -> ...
 -> Commitment

-- Compose with Page
ClassicTrip
 :: template<template<auto...> class...> class...
 -> template<auto...> class...
 -> ...
 -> Commitment

-- Compose with Road
ClassicTrip
 :: template<template<auto...> class...> class...
 -> template<template<typename...> class...> class...
 -> ...
 -> Commitment

-- Compose with Rail
ClassicTrip
 :: template<template<auto...> class...> class...
 -> template<template<auto...> class...> class...
 -> ...
 -> Commitment

-- Compose with Flow
ClassicTrip
 :: template<template<auto...> class...> class...
 -> template<template<template<typename...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Sail
ClassicTrip
 :: template<template<auto...> class...> class...
 -> template<template<template<auto...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Snow
ClassicTrip
 :: template<template<auto...> class...> class...
 -> template<template<template<template<typename...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Hail
ClassicTrip
 :: template<template<auto...> class...> class...
 -> template<template<template<template<auto...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Cool
ClassicTrip
 :: template<template<auto...> class...> class...
 -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Calm
ClassicTrip
 :: template<template<auto...> class...> class...
 -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Grit
ClassicTrip
 :: template<template<auto...> class...> class...
 -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Will
ClassicTrip
 :: template<template<auto...> class...> class...
 -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment
```

```Haskell
-- End in Conjuration
ClassicTrip
 :: Commitment
 -> template<template<auto...> class...>

-- End in Transition
ClassicTrip
 :: Commitment
 -> template<template<template<template<auto...> class...> class...> class...>
```

## Structure

```C++
template<template<template<auto...> class...> class>
struct ClassicTrip
{
    struct Commit
    {
        template<template<auto...> class...>
        alias Rail = CONJURATION;

        template<template<template<template<auto...> class...> class...> class>
        alias Hail = TRANSITION;
    };

    template<template<typename...> class>
    alias Road = RECURSION;

    template<template<auto...> class>
    alias Rail = RECURSION;

    template<template<template<typename...> class...> class>
    alias Flow = RECURSION;

    template<template<template<auto...> class...> class>
    alias Sail = RECURSION;

    template<template<template<template<typename...> class...> class...> class>
    alias Snow = RECURSION;

    template<template<template<template<auto...> class...> class...> class>
    alias Hail = RECURSION;

    template<template<template<template<template<typename...> class...> class...> class...> class>
    alias Cool = RECURSION;

    template<template<template<template<template<auto...> class...> class...> class...> class>
    alias Calm = RECURSION;

    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class>
    alias Grit = RECURSION;

    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class>
    alias Will = RECURSION;

    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class>
    alias Glow = RECURSION;

    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class>
    alias Dawn = RECURSION;
};
```

## Examples

We will see two examples that demonstrate conjuration and transition.

- In the first example, we will compose `oper_0<2>::Rail`, `oper_1<10>::Mold`, and `oper_2<'*'>::Rail`.

```C++
/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** Oper_0 ****/
template<auto Variable>
struct Oper_0
{ 
    template<template<auto...> class Sequence>
    struct ProtoRail
    {
        using type = Sequence<Variable>;
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

/**** Oper_1 ****/
template<auto Multiplier>
struct Oper_1
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

/**** Oper_2 ****/
template<auto Variable>
struct Oper_2
{
    template<template<auto...> class Sequence>
    struct Detail
    {
        using type = Sequence<Variable>;
    };

    template<template<auto...> class...Agreements>
    using Rail = Detail<Agreements...>::type;
};

/**** SupposedResult ****/
using SupposedResult = Shuttle<10*2, '*'>;

/**** Metafunction ****/
using Metafunction = ClassicTrip<Oper_0<2>::Rail>
::Road<Oper_1<10>::Mold>
::Sail<Oper_2<'*'>::Rail>
::Commit;

/**** Result ****/
using Result = Metafunction::Rail<Shuttle>;

/**** Tests ****/
static_assert(std::same_as<Result, SupposedResult>);

// The following `static_assert` shows how the operations are composed:
static_assert(std::same_as<
    Oper_2<'*'>::Rail<
    Oper_1<10>::Mold<
    Oper_0<2>::Rail<
        Shuttle
    >::type
    >::Page
    >,
    SupposedResult
>);
```

- In the second example, we will transport the conjuration function to `InvokeRail`.

```C++
/**** InvokeRail ****/
template<template<template<auto...> class...> class RailArg>
struct InvokeRailDetail
{
    using type = RailArg<Shuttle>;
};

template<template<template<auto...> class...> class...Args>
using InvokeRail = InvokeRailDetail<Args...>::type;

/**** Result ****/
using Result_1 = Metafunction::Hail<InvokeRail>;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult>);
```

## Implementation

Since every member template of different signatures is given a unique name, we know which member to pull out when asked for a template of a specific signature.
For example, we can compose a `Rail` and a `Road` in the following way:

```C++
template<template<auto...> class...Args>
using Metafunction = Road<Rail<Args...>::template Mold>;
```

Note that

- `Road` has signature `template<template<typename...> class...>` and
- `Mold` has signature `template<typename...>`.

This means in terms of signatures, a `Road` can always be invoked by a `Mold`.

We will implement `ClassicTrip` by performing recursion manually, meaning the function will recurse only once for every invocation of a member template.
We will showcase a simplified version that handles `Mold` and `Rail`.

Note that in the following code,

- `Radio` is a `Rail` and
- `Car` is a `Mold` or `Rail`.

```C++
// `Radio` is a `Rail`.
template<template<template<auto...> class...> class Radio>
struct ClassicTrip
{
    /**** Define Road ****/
    // `Car` is a `Mold`.
    template<template<typename...> class Car>
    struct ProtoRoad
    {
       /**** Commitment ****/
       struct Commit
       {
           /**** Conjuration ****/
           // `Radio` and `Car` are composed here.
           // First, we instantiate `Radio` and obtain a `typename`.
           // Then, we invoke `Car` with the type result of the obtained `typename`.
           template<template<auto...> class...Signals>
           using Rail = Car<typename Radio<Signals...>::type>;

           // Helper function for the member template `Hail`.
           // This function transports the conjuration function `Rail` without invoking it, 
           // allowing further process by other higher-order functions.
           template<template<template<template<auto...> class...> class...> class RailVessel>
           struct Detail
           {
               // We transfer the conjuration function `Rail` to `RailVessel`.
               using type = RailVessel<Rail>;
           };

           /**** Transition ****/
           template<template<template<template<auto...> class...> class...> class...Agreements>
           using Hail = Detail<Agreements...>::type;
       };

       /**** Continuation ****/
       // This function composes the conjuration function `Rail` and the `Agreements...`.
       // Note that even though `Agreements...` is variadic, it only allows a single argument.
       // This is because `Agreements...` will be used to invoke `ClassicTrip<*>::ProtoRoad`,
       // which has only one parameter `Car`.
       template<template<typename...> class...Agreements>
       using Road = ClassicTrip<Commit::template Rail>::template ProtoRoad<Agreements...>;

       // This function composes the conjuration function `Rail` and the `Agreements...`.
       // `Agreements` will be used to invoke `ClassicTrip<*>::ProtoSail.
       template<template<template<auto...> class...> class...Agreements>
       using Sail = ClassicTrip<Commit::template Rail>::template ProtoSail<Agreements...>;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;

    /**** Define Sail ****/
    // This function is the similar the `ProtoRoad` defined above.
    // It handles the case where `Car` is a `Rail`.
    template<template<template<auto...> class...> class Car>
    struct ProtoSail
    {
       /**** Commitment ****/
       struct Commit
       {
           /**** Conjuration ****/
           template<template<auto...> class...Signals>
           using Rail = Car<Radio<Signals...>::template Page>;

           template<template<template<template<auto...> class...> class...> class RailVessel>
           struct Detail
           {
              using type = RailVessel<Rail>;
           };

           /**** Transition ****/
           template<template<template<template<auto...> class...> class...> class...Agreements>
           using Hail = Detail<Agreements...>::type;
       };

       /**** Continuation ****/
       template<template<typename...> class...Agreements>
       using Road = ClassicTrip<Commit::template Rail>::template ProtoRoad<Agreements...>;

       template<template<template<auto...> class...> class...Agreements>
       using Sail = ClassicTrip<Commit::template Rail>::template ProtoSail<Agreements...>;
    };

    template<template<template<auto...> class...> class...Agreements>
    using Sail = ProtoSail<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKz%2BpK4AMngMmAByPgBGmMQSAJwAzKQADqgKhE4MHt6%2BAUEZWY4CYRHRLHEJXCm2mPalDEIETMQEeT5%2BgfWNOS1tBOVRsfFJqQqt7Z0FPZODw5XV4wCUtqhexMjsHAD0AFSHR8cnp0e7JhoAggdHANQAkixp9GyCTE13xxfXt2f/Zx%2BV0uN12dxMADYNAAlJj4VCQjR3PAKO5McFQ2F0REAOhBBEwzwMBJMyTcBKJH0wpPJhJeVJpTC8RBxrNJ2DuyAMCgUrLxyQ5XKYPLusPh7JBk2IXgcdzc3KyyAAKsQ8GkQSYAOxWa53PV3P77O4AEUwNAiotQcK%2B5xB%2BoNYMRbjaiORqPRiIAsp50Li7fqKfSSWTA8TqSGAJ5pRisTB89mchVyl0C/16qUygh3ZTEVBEaFW326/VanVXe36w1y1AsFiEN5Z75p%2B0Z2UeWuEZsl7VdisG47VhjaTYfHI2w5AvsV3aOzFwpyuwzoDEaZ3ERfETCcmvFTDLhDxOO96dggBieGIk1IdwA7lvwvNBHgqSuxQuoWiGMvUDFWuE0SuBBRjGbB%2BsWU56jOdxKgeDDXneyIMAAbqgADWW5Oi6H43oQCB3AQB74cBdybgoXi0FmqBUPhhE/n%2BETLoiQHRswoFQni4EQaGDIhnSYaMsyqDxgKibCryrJCHgwDMLQCgSpxU5eFkRiikwdDgskxrJuukYsbGqnimSknSWI4n8tgIAgMx4bYKSZbHvaUEABINNGxB3FQXgMA4Y78O5BFbmwVTxPhfEvoiTlqbQYHlhBkFgjBKIeV5PkCPhxCGAoGTtKiAXbkOI6fJ53mfIiWLRdhuEbFm4Qoah4TAMiBDXg5lZgmItCoDhKmee0B7uWkubbCKMQRnceb9XcCBSf1AC0JBYO5xWpQwvKtXq3HBrSlJbZt4bbUG%2B1MiybIiUKPLCYKCqXaJIrlQAapgPINPJsVxa2Wamn%2B0UKX2pbrSedwAOpbgQGWrVQIV5WgBUZUVKWlXO2IfkQr5RY9z0VRoHFvXF%2BpKQ1RHRhpWkPU9dg0uVErJGWePgpqxp2Rqv3TgOKqZdkaVNiz9p7TSfO8Tt%2B0C86gk3edZkJhL4vXayVzAJuhKMAQcmpjz%2BPKY1kXqaSWlfVFNLy4rDaSwKlnWUzLNaozNPM7jlYDh4T4MF4o5c7aLNQYlqLLZ8aDPJkT00VuMPDnDvkI2OZUGx%2BS7ByuRuYErgiS%2Bxx5QZEeagwgHx3JgSGMDRGzAHhiKJ8nKvxh%2BSVIW0z74Mg16EONDC0GNHVde6dya/QaLEMAPjKzjU5e9NqJJXEohKRhULlybVdIjhtC0HccR3NPy6o7VaEz6uCp4MqqrqmS%2BzspZOZ5qgBZwoipDp2CN7TcgeE56iAhty3W5pG0sYEu5mHrjTizEWIDgKsTjKdK6Yk%2BRz2VqrWyLMCYqWvoxTScp96HzVDSdsdYCDmzCgSVS2IzZWQIVuC%2B%2BZCyGwVkneekDLbAk9glMeyUSpjn9ruXKhFQ6FQjmwtK0dkZIjjnlMuNCK6p2xvfBO4iTauiXivNeG98KoEQnVXe8oxIHxVFgk%2BZ8QAUNQEIKKw8%2BwgLIfzCxZJjpCUgbdU2UCLpy1kXA16ilNZ3GMTrNBmieTaKPtgmsuD8FCyIdFEhe1sy5iIF48JbhYEp0ugw%2B01sGHNnMULfmYDYwy2gc442ri1a4yQY1FBJMomXxQdQgpiT6G22uM2KsppzRblieOfYk42rQRYb7McSU8pZDrAYfyhFESGKqR%2BLALTlxMBiKgAupj4qPCzDnL89AuEh2FFuR%2Bh4VxrldElD0SMsaLNCpkwWh1LHnNFidcy9jckin2UUlsYNMwVJiQbTi/1PaOyCfWZW7TOkVg%2BtWDsBBjzfPtn2KsTsw5uwYICgGGTLnWLFnY6WEkpIyXgQDEpYTylPLcG%2BBERksWmUuiEw62YmDABsmk9WG0rEHX4hcllzKeI3NsXcjF3LZa8rEmEjGFNnl4xBfrbEDL6a0zpnqPF1lylk0xpTA2qZ6lQorKktVAMqzs1WpzBF3N1W8yZcitlIsbEPIcfc9FfKEkqzcXjPF2sV66xNJgb61TaFwIpVZYCyS/oM3peqmFshwiu0%2BIaqcpqOXWXAZamBLiU4OorHisprrfGKh0cfNwODCCUrDGE/RkTxlULJHahxQao0murdci1Nq8n8qcTictyb7R4raemjBWbAlgvzS%2BKmESyHvKMSq%2BJibK51OlXqTV9lOLRt2kyutjarU8pbSK2VHiO1oMMbEz1EiklasDVq34AJT2GqrOeS8WZsCqFYC8Lc56z1PqBBqMwyRwhci8FgDSbgYbbDSPaopIIqxCAQMyAgvdDXmrReZSUrzZSgfA/QINVYADybkAD6SIoOLsEnce6ddZnIaKSC9D8QsMam1OCOdNaUWcstZ4zAABHLwjBtitpBeMz5uNIUQTlcRV1QhmOse8vtAjqoiN0rVSko9s7cbzqOjBqWtrx04s4qmqK5SuPELHTUidsHD02zk2hzDXBEXXGg6jT05FHAvDwPEV6pHTOUanWcujsbYwcfg1mQx3paCMR7LJu2xrrmWa5cpgVQmWNscwNeJdDwvPSllL5n0NIosifY2SB4B6EE8Z7MA3DtyABSraNaE2UDSjCaD0sxZpNZiiapaD2eIPsbLrJrxFYPa5mdwWAwmuyWwBNem1PFI8X51BWkUv%2Bb3XQgz9kgsNJPfcMjxAMNmHM1cML%2BHCMxGI7lpz5GzAufSbRtlS6Isihq6JxLbzxU/Ty65ttHj5WCeE7Vsk4nny7ak91hbjD5OnY5eds6Knhuto094vW7rR3lp9RbQzKGBxCC8GkXc6BoRPRsxt9tKO0cY7IhRcpiGCAQf2lwDQ%2BwzDXjABwfYNPqbGYHJ6aHvT3YThBHi5nrRWcIs7VozB2aVsUbJEdkhA7cuWSqWSIXXAaTk/0eN16lld3S8w6LtwNO6ccH0eLkEllc3guPTcAc%2BOseGtTZjwnrqudMB55L0dxPScM7tjqp6KsNvzEcMgDDYl4gEAgJMdAlkFCxh96rIllvmqeNx4HdHkf2QrBQ8wrc/Bl5dUJoiT3B8w9KHaK6BQCBO5TS6vHVAbl4Xuk3NuAOSgg9wdHN7337QA8ECDyAEPbAw80mbEL9Xmv6di9HT35zZJ5ckMV2SYf5GNA0lFxZEAA63AOUd8hr5ES/Vr/nxV2lzZ2R304sj1HsfTcUQ1AKRPRvDRPv%2BECEDmAYbLhvXeyDHtjfX9PS%2BpbhxHjIR3uVDbCmVydGwOjiK6SY5UVw/cjm3mP%2B6i5Ud2x26mz2AmaCEBUBRkYGJOe2aSf2%2BIgOC6taSmIODaF2ZkkBwAI2eKDwv%2B6E/%2Brq1BcBUUCBZa/cDi5sfql%2BJuke2OHiJ%2BBAGGZm1uLOkczgIAzqNIDBf%2BKqtknB9wSobuHurQXuOefuLebeHemAXeZIfBAh14h%2BeO8e5%2BdkHAawtAnA/gvAfgHAWgpAqAnAS%2Blg1g3cGwWwGEb6PApAeC1hJhawqEAQkgOIGgAAHGYGYIkIkFwP4MEUEVwJqJqNIGYRwJILwCwBIBoBoKQFYTYXYRwLwAoCABkV4VoGsHALADAIgCANVGkMyOQJQBwnQPEJELGJwKoEERCLNBCJIHcMAMgMgHcFIDiGYLwHuIQCQHgEHlwDIIICIGIOwFIFMfIEoGoJoDoHoDeBlGkJwDwKYeYZYSsbYZwKhsyNUZRNRK0e0Z0d0b0f0QEethAO2GkA0f/O4SsLwEUSYaQBAEgPUfQGQBQBAD8WMMAFIFTjQBRPEPkRADEPsTEOEG0BGFsbwLCcwMQBGKhjENoPfl4R4f7A2Khq3Aid4aQFgDEF4MAM6MvPkdwLwFgCwIYMAOIESfgJuD5AXFSTYZgKoPfsyDsB4eEASIkTYU1jEBlKiR4FgPsWDHgKkdSaQAXMQHMkoKaHSUYE1kYCsWsFQAYBQfdPZjeGRlYR4fwNMaIOIPMcaYsSoOoESboJMQYOqaYI4ZYPoHgDEPkZAGsGXk0FSbNIHrrI6VYJYGYNkfKaqFgO6RAGsHYFiTkC4F%2BDMH4JMaEOECMMFDUOkJkPqgmXoMUPqosKMOmdGStAMNMJ4F0HoEWU0CWUMCmUsGMJMfMKWfkImbYFMDWRUAWRIFGS4dsF2foLsZkfsTkXcOcR0V0T0X0QMXcbgKMc8ckFwK8Z4RqWsAeHCGMJGaQH4ZIMkDiCkPERoJIGYJIFCBoP4BCIkP2UkSkSAPOTiBCFwBCEEYkDERCP4JIJESkBCIOUSTkXkQUUud4SUeUV8ZUccTUf8YCcQE0WwJwG0CwEhJqLNOiEKCpLUDiFwIEcMfgEQGGXoBaTMWadIBaYoFafsboFTusUwJsdSTsRwBYd%2BdkYcWBacSOW0WOaJKhYkOhYEXcPcTuE8eCG%2BmYIue8SUd8fxb8bUQCRJWMChcCRERkWCX/JCdCUScifCYiaQOpaieiZiQ4JpbicrPiW3PsSSWSRSbJJpbSfSYyTYcyTGWyfsZydyQSJpfyQ0PscKaKRGOKTsDYVKTKR4fKYqZgMqTZQ1BqXwNqQoLqZgPqSxJpfhaaXMURbICRcsTaSAFTvacYNYNYC6W6fAJ6QBjkD6X6ZpAGdYMGbwPMvEGGU9EVb0DGc4BAK4NmUmV%2BPmWmTmZmU0O1RmSUDkF1csA2Q0M1c0G2f1ZWf0G2cNfWa2YMFNbNbWZ2QuesJsL2WtYkfRVkTVZwKxRcV0XJf0VxRhUiBADOThYJfOSJcuaQKuYtJQLRckaQKkckFxQeZqP4IkHEckIecee%2BQxXtbkbYP%2BaJZ8cBUgFUeBXUTJVBc0RwHBZcSwAoEhH0UhGhWGJMFhbOeMXhbIARSlQseldaTYboKkJRdRdsZeTtUOUxQQCceNGccjajejZjVSJMLxQ8QJeYMkMkLdYBZ8eJc8E8VJZBSAGjajhhhjYkBhljfwaoJ0XwHQMpZQKpTYdpYSR4ZrbpViQZUEkZQSaZZgKSeSR1FSR4dZaqX5TSReA5Q1USc5cgDyW5YIB5USV5fCb5ZKaqIFbwMFYHGFaqRFYLVqTSjFXqQaYlQTclRIKlYICTWRTefoPSSgHlc6cKRGcVd6ZwLsIHmnU6RYNVbYaGeMQ1R6U1StHGe4GWQUB1egHNembmX1bXS2c3UNStd1aNX0AINWVNWNcWctR2V3QtU2eWQ2UPamSNd2RtXMbRbTT%2BftYrV0SjWjXcDLTiPLbxZdSQNdQuW8XdQ9euc9deWETiHzYEAeeThoHzZqI%2BUDQcSDfkYUXdVuf4LubEZqOkUEZIBEVwCEWYF%2BYkckHsYvSDaJbRUMQ/b%2BQBcUWsPKVkM4JIEAA)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/raillivore/classic_trip/implementation.hpp)
- [Source code](../../../../conceptrodon/raillivore/classic_trip.hpp)
- [Unit test](../../../../tests/unit/metafunctions/raillivore/classic_trip.test.hpp)
