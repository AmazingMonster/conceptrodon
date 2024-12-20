<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Raillivore::Trip`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#raillivore-trip">To Index</a></p>

## Description

`Raillivore::Trip` accepts an operation.
Its first layer accepts another operation for composition.
Then, it returns two commitment functions and twelve continuation functions.

- **Commitment**
  - **Conjuration:** When invoked, this function instantiates the first operation with the arguments and then the second operation with the corresponding member of the result.
  - **Transition:** When invoked by a vessel, this function transports the conjuration function to the vessel.

- **Continuation**

  When invoked by another operation, the function returns a `Trip`
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
Trip ::   template<template<auto...> class...> class... 
       -> template<typename...> class...
       -> ...
       -> template<template<auto...> class...>
       
Trip ::   template<template<auto...> class...> class... 
       -> template<auto...> class...
       -> ...
       -> template<template<auto...> class...>
       
Trip ::   template<template<auto...> class...> class... 
       -> template<template<typename...> class...> class...
       -> ...
       -> template<template<auto...> class...>
       
Trip ::   template<template<auto...> class...> class... 
       -> template<template<auto...> class...> class...
       -> ...
       -> template<template<auto...> class...>
       
Trip ::   template<template<auto...> class...> class... 
       -> template<template<template<typename...> class...> class...> class...
       -> ...
       -> template<template<auto...> class...>
       
Trip ::   template<template<auto...> class...> class... 
       -> template<template<template<auto...> class...> class...> class...
       -> ...
       -> template<template<auto...> class...>
       
Trip ::   template<template<auto...> class...> class... 
       -> template<template<template<template<typename...> class...> class...> class...> class...
       -> ...
       -> template<template<auto...> class...>
       
Trip ::   template<template<auto...> class...> class... 
       -> template<template<template<template<auto...> class...> class...> class...> class...
       -> ...
       -> template<template<auto...> class...>
       
Trip ::   template<template<auto...> class...> class... 
       -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<auto...> class...>
       
Trip ::   template<template<auto...> class...> class... 
       -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<auto...> class...>
       
Trip ::   template<template<auto...> class...> class... 
       -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<auto...> class...>
       
Trip ::   template<template<auto...> class...> class... 
       -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<auto...> class...>

-- End in Transition
Trip ::   template<template<auto...> class...> class... 
       -> template<typename...> class...
       -> ...
       -> template<template<template<template<auto...> class...> class...> class...>
       
Trip ::   template<template<auto...> class...> class... 
       -> template<auto...> class...
       -> ...
       -> template<template<template<template<auto...> class...> class...> class...>
       
Trip ::   template<template<auto...> class...> class... 
       -> template<template<typename...> class...> class...
       -> ...
       -> template<template<template<template<auto...> class...> class...> class...>
       
Trip ::   template<template<auto...> class...> class... 
       -> template<template<auto...> class...> class...
       -> ...
       -> template<template<template<template<auto...> class...> class...> class...>
       
Trip ::   template<template<auto...> class...> class... 
       -> template<template<template<typename...> class...> class...> class...
       -> ...
       -> template<template<template<template<auto...> class...> class...> class...>
       
Trip ::   template<template<auto...> class...> class... 
       -> template<template<template<auto...> class...> class...> class...
       -> ...
       -> template<template<template<template<auto...> class...> class...> class...>
       
Trip ::   template<template<auto...> class...> class... 
       -> template<template<template<template<typename...> class...> class...> class...> class...
       -> ...
       -> template<template<template<template<auto...> class...> class...> class...>
       
Trip ::   template<template<auto...> class...> class... 
       -> template<template<template<template<auto...> class...> class...> class...> class...
       -> ...
       -> template<template<template<template<auto...> class...> class...> class...>
       
Trip ::   template<template<auto...> class...> class... 
       -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<template<template<auto...> class...> class...> class...>
       
Trip ::   template<template<auto...> class...> class... 
       -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<template<template<auto...> class...> class...> class...>
       
Trip ::   template<template<auto...> class...> class... 
       -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<template<template<auto...> class...> class...> class...>
       
Trip ::   template<template<auto...> class...> class... 
       -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<template<template<auto...> class...> class...> class...>
```

## Structure

```C++
template<template<template<auto...> class...> class>
struct Trip
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

- In the first example, we will compose `OperationA<2>::Rail`, `OperationB<10>::Mold`, and `OperationC<'*'>::Rail`.

```C++
template<auto...>
struct Shuttle;

/**** OperationA ****//* Start */
template<auto Variable>
struct OperationA
{ 
    template<template<auto...> class Sequence>
    struct Detail
    {
        using type = Sequence<Variable>;
    };

    template<template<auto...> class...Agreements>
    using Rail = Detail<Agreements...>::type;
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
using SupposedResult = Shuttle<10*2, '*'>;

using Metafunction = Trip<OperationA<2>::Rail>
::Road<OperationB<10>::Mold>
::Sail<OperationC<'*'>::Rail>
::Commit;

using Result = Metafunction::Rail<Shuttle>;

static_assert(std::same_as<Result, SupposedResult>);

// The following `static_assert` shows how the operations are composed:
static_assert(std::same_as<
    OperationC<'*'>::Rail<
    OperationB<10>::Mold<
    OperationA<2>::Rail<
        Shuttle
    >
    >::Page
    >,
    SupposedResult
>);
/**** First Example ****//* End */
```

- In the second example, we will transport the conjuration function to `InvokeRail`.

```C++
/**** Second Example ****//* Start */
template<template<template<auto...> class...> class RailArg>
struct InvokeRailDetail
{
    using type = RailArg<Shuttle>;
};

template<template<template<auto...> class...> class...Args>
using InvokeRail = InvokeRailDetail<Args...>::type;

using Result_1 = Metafunction::Hail<InvokeRail>;

static_assert(std::same_as<Result_1, SupposedResult>);
/**** Second Example ****//* End */
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

We will implement `Trip` by performing recursion manually, meaning the function will recurse only once for every invocation of a member template.
We will showcase a simplified version that handles `Mold` and `Rail`.

Note that in the following code,

- `Radio` is a `Rail` and
- `Car` is a `Mold` or `Rail`.

```C++
// `Radio` is a `Rail`.
template<template<template<auto...> class...> class Radio>
struct Trip
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
           // Then, we invoke `Car` with the resulting `typename`.
           template<template<auto...> class...Signals>
           using Rail = Car<Radio<Signals...>>;
           /**** Conjuration ****//* End */

           
           /**** Transition ****//* Start */
           // Helper function for the member template `Hail`.
           // This function transports the conjuration function `Rail` without invoking it, 
           // allowing further process by other higher-order functions.
           template<template<template<template<auto...> class...> class...> class RailVessel>
           struct Detail
           {
               // We transfer the conjuration function `Rail` to `RailVessel`.
               using type = RailVessel<Rail>;
           };

           template<template<template<template<auto...> class...> class...> class...Agreements>
           using Hail = Detail<Agreements...>::type;
           /**** Transition ****//* End */
       };
       /**** Commitment ****//* End */

       /**** Continuation ****//* Start */
       // This function composes the conjuration function `Rail` and the `Agreements...`.
       // Note that even though `Agreements...` is variadic, it only allows a single argument.
       // This is because `Agreements...` will be used to invoke `Trip<*>::ProtoRoad`,
       // which has only one parameter `Car`.
       template<template<typename...> class...Agreements>
       using Road = Trip<Commit::template Rail>::template ProtoRoad<Agreements...>;

       // This function composes the conjuration function `Rail` and the `Agreements...`.
       // `Agreements` will be used to invoke `Trip<*>::ProtoSail.
       template<template<template<auto...> class...> class...Agreements>
       using Sail = Trip<Commit::template Rail>::template ProtoSail<Agreements...>;
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
           template<template<auto...> class...Signals>
           using Rail = Car<Radio<Signals...>::template Page>;
           /**** Conjuration ****//* End */

           /**** Transition ****//* Start */
           template<template<template<template<auto...> class...> class...> class RailVessel>
           struct Detail
           {
              using type = RailVessel<Rail>;
           };

           template<template<template<template<auto...> class...> class...> class...Agreements>
           using Hail = Detail<Agreements...>::type;
           /**** Transition ****//* End */
       };
       /**** Commitment ****//* End */

       /**** Continuation ****//* Start */
       template<template<typename...> class...Agreements>
       using Road = Trip<Commit::template Rail>::template ProtoRoad<Agreements...>;

       template<template<template<auto...> class...> class...Agreements>
       using Sail = Trip<Commit::template Rail>::template ProtoSail<Agreements...>;
       /**** Continuation ****//* End */
    };

    template<template<template<auto...> class...> class...Agreements>
    using Sail = ProtoSail<Agreements...>;
    /**** Define Sail ****//* End */
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwArKSuADJ4DJgAcj4ARpjEEv5cpAAOqAqETgwe3r4BwemZjgLhkTEs8YlcybaY9iUMQgRMxAS5Pn5BdQ3Zza0EZdFxCUkpCi1tHfndEwNDFVVjAJS2qF7EyOwcAPQ7ANQmAGwaAEpM%2BKjHGvt4CvtMhyfndNcAdCYaAIIEmCypBl%2BJn8bl%2B/0BmGBoL%2BAKYQJBTC8RDeKOB2H2yAMCgUKI%2B/nRmKY2P250uaM%2BXwmxC8Dn2ABViHhUhSTAB2KzffZc/Y7ABU/N5%2BwAIpgaJESagLvsBby9oL%2Bm1pTsKdyeQdrm5WtdbvdHtcALKedDvFXcsGw%2BHQ8FwyEgggAT1SjFYmFxaIxWPumuI5M53KpNII%2B2UxFQRFOkuNfq5bI5X1V3L5Av2HhYLEIbEE0oFcv2CqDstNCYDtNT6YIRdVscrCa5Sf5KYE2g2cOy2f5ufzSprtb2TzOFyc2sM6H73uHxEwGNQ/wymFHCASrp7Cb7ADE8MQJqR9gB3KcROaCPA2/ukocnB4MUeoWItCIPfsOp3MNgm6O1usHOmLhg7/e3AwABuqAANZThqWqXruhAIPsBCLvsk4KF4tCOEYT6Os6b4nB8H6fuaEJQoRNpQoiyKoviHpEjiKJCHgwDMLQCi%2BvGn7cl4mQYS8tCHP4QoplqILnlcIL0YxYi0Xi2Dkv4cbsYmMqNgwzbEK2AjtrKfL7Ng17dt8K5VvhvZKQyhjFG2MqdpMBbKsZq4HAAEvUTrEPsVBeAwDhtvwbkIVObCVAk8EwhC/aOUwry4YZibfggdzuZ53kaQQakMAo6RtPc/nTipLaNIlXkFdcPHajBCHrEGEQgaBETALcBA7jFX4PLQtCoDBGEeW0i5uakoZbMSsT2vsYa9fs8XAL1AC0JBYG5HlFdkOLNSF1qWiRG2haRdrbZa5GoG6VGEtiR0Ep6Z3UcSPEAGqYNi9SsQpXIlkGIr3rQq3VvZ7F9gA6lOqXmVQwU5WgeVqQVi3JQwZ6RZ9l5EHDdB3Q9CMaHhbHPRxXH1c%2BEH8SS8Oo3YUKlfiwLyc9bJCpTLI/Wae22laFrM5tbNM2RSKHZR500ZdJ1Se6gu4l8wCTn8jAECxFMM1ynF1fsEV0HxAnvfDUJixLmbS2dIAgPjdNyzyplpRZGlWdpumjoW9k00bWOqvWgplhmUuabm1v6V8K7O8p6FeOpsOW/KNne5%2BfY/gl0MFWgs5KNliHg6pQeFTDyPo1eo45dcWuYJLghC9F9l9lEYaAwgcL7JgQGMPBCDrFN/Z5wXuuopeCVAa0J74MgO6EKNDC0CNYjtbuur7Lj9APMQwA%2BFLmMR3FCUJfEoicRBJwtzrRc3DBbX7PE%2Bwb9nqCATVm8aAyTJQnrIAhmGqARhc1ykL7By7vFyBwZX9wCMPg8pypFaC6X4blII%2BmLo7Rm60OawOIlhV8rpeZXSktvKWMsZL2QVtxSMqt6SMmZCCV2BB9bsyJq8fEZCmbBlDOGSMmtxb5x3mdB2796TxXuDHNsccij3XrlOZO%2BUfJJWKs8DWl4RwCObkw1uu9F69nVFvWRO8yp0F4kfE%2B8Ez7VTApfa%2BRC3B3wfkQIQ8MFEJnZsRTmu14EIm5gLC6KCRYonQYXJ6tYcH1TMSrYEAkDFQhIdQ2BFDPpUINjQkxqAfFhLcG4tu0kHYRyUh4Y8DBA4FRDjpPSttHb2zkvTR2VjbGswQS%2BF0jj%2BauJURgjx8tcYSilH42hj9n7GhBPEoWFMCkfj9iKMUU42keytjkuyPtelKX6REKcMThmhwGOHWKHDo6iLbAlHKmR0wGD8oha4US2naiwAM0cTBYioFrhYtU%2BwACSQZK7XnoInQRRIpyfyXGOKCNwEp6nEVFDGlZiksyIiU4FmoHHOKcdJVBgkfSy0dq9FppiNYfm%2BtAusKSZzlh1nMvMYdcmfgRSQlcqLsZ%2B1SSnTJOZtJdnxc9QFgKDqVNOnRBiTFMGrS8aE/B45hKDlEm4cSbK77kOUEwYAtoZI9LRauDFENU5ZK9rk1afszLpSyBbKl8zFS0oUvSmxQKdoGv2uCqFLjTWQuFp6UJJNHpwuxgi9WrxjYkuxvUxW%2BN8G3XuqTXllDJVUwUvkuMq09V2KNXA0p9iKLmqqTG5lca0E1PcXa56nLla8WaY62JnThVYSSc9FVZt1XB01dkm2YzPxBt9hitMbsswKtGYU5JyZUkB3laWmlFbayhsjaCRBFSIWxs6XU1UnKhnNICcQzFhBgms1CWiWdYV9kMI6UmhJslg32R7aChlJrLWxv3fG4dKaEyctmROwhgTp2kIiSE8m2BF2niiTExh2sMGsKlc2hsraIgZMsqWxVXaYyslplKgF%2Brt2GsZYO%2BNh7E1vuTVgx2Z74b4OfRrVdCH13dIDSbZMUzxSzIbeWlkIG2HfGdjKDsFJ6x0mwEIOkOYaNUao2MlkZh/ARExF4LAfE3BIjoIQe0rEKS7ujaxBFQgEBIgIPQcjXw/YAHlXJB3jFkzton9UHX2Ddbupy5NwoRcphIqnSMWEOB%2BSDxrxPHStUITAABHLwjAtgjodZgD6lYXWeIaR65p9mnMueZrpxk%2BmJX5uA6BzdRSINab3bZoda72UfjHahzNHmMNxKS7mp0bCyNSqUypxoamAONoMhRpSxnIbZHM%2BpvFYyxNn31KhRwAI8AJAk6lQM%2BwqtB2DeycDYb8ZILc112kUTDS0FHNWfL0XVRWeZtBhNeZHPOa8pgHcS3rmjepONuhqBJvtIFatoLUJrkfqQ1WAbW64vRoAFIjpxorUV4r8EBbW65kEzW0JMloO14gvJzsoh3Hdj9uGq3lZi0N/tbBRZJZHZyw7aH9uHdfcw99vM8tReY8mXrjRaulZI5DwrJnGhuBxRp74jWdN6diAZpDRmivZDcGZwbvbGtMvuO907J7J5jbehlp1eTrvSuPr5rCb2TvrahCFk8dPwufu5BD8ZUP2e3Z5gmuHWHkvIYaTxfBWa0dyJy7afr2OKu46ZwIcnxHvY44bBuLcQZsCqFYACKcdWFm5LPV4VIfD0CnHui1t70mCCyeZlwDQvIzA7jABwXkceN2FMRxl7hGkL03xBHj7IPsQRmAXSAe9FJ9YHKz1bhgVgQSR4L6juF%2BsX1l9J8zqEceE8cAL0X74%2BsiVge%2BGOoPaF8H6lT6s5whfMtSZk/T%2BTcxHDIAAPo0QSAQCAEx0D6wUC6RfMs3CB5QmhHcQhff%2B73y1tEyx5OR0QvwNqHVFbXFn3gBfS%2B2jagUA3ceE0OrSNQOX3Uk5px455wQAKRH9n8Ho2hV8CB18QBN82Bt8oRKxs9rcW949E9wlyYWcPxkCK8oRq9wla8sDHYcDc83B88MDMtDJJ8w85MUVecC8XtIQ6DsA34Pwj8/c5wA8B8KwDJ8QL8CslJHcJgdJXdwQPdCc7cLcGx7NwZRwXc3dp5PdtUGtYsht1dOdOdQkvhZ5OtdsgxrlgI9EeJDcDIRdR1xcnRPV4ZtDgAoRqDw8k9TDzcVcFtrEw0ls4MNDXFZ4ddOUDCL59dml/CjD4ZDcOkfCTd5N%2B998CB58uAh8R8lox900ztDDwIi9e9KQWg59t8lBIC18N8t8iQyZuC4jD9j9ODT80Jz8HY/YZCBA5DRD3ccVAMOBVhaBOBAheA/AOAtBSBUBOAWdLBrBJ51hNgIIOMeBSBSFei2jVhQIQBAhJA3gNBJAuBWR/ANBAgNAzAjgjgzAAAOA4/QTgSQXgFgCQDQDQUgHovogYjgXgBQEAa4mYrQVYOAWAGARAEASqVIJEcgSgXhOgBIKIF0TgVQA4o4aaI4SQfYYAZAZAfYKQN4MwXgecQgEgPAdfFIfgQQEQMQdgKQGQQQRQFQdQWY0gXQFIXcNSVITgHgdozo7ozQXge4xTJEP4oMVAKgfYCEqEmEuEhEpE5YswfYCAVMVIYE8BSY5YXgV4to0gCAJAIE%2BgMgCgCAFU0YYAKQGPGgNCBIJ4iAWIFk0gWICIVoe0ek3gM05gYge0RTWIbQTABwK00gOOHWRTIeS0ikrAWILwYATUNqJ47gXgLAFgQwYAcQH0zcZ0xwWuYMvozAVQZ0pEbYKYiIX4Doikv7WINSO0jwLAE01KPAC4kM0gWuYgM5JQEUcMowP7IwFk1YKgAwYABQG6drXcYzHoqY3E4QUQcQIk3s0ktQE0qk/QCMlAawawfQPAWIJ4yAVYX/RoYM6aNfPxUwYYywMwO4isxkLAeciAVYOwWM7IFwa8aYPwFIMIaZRYUYFIIoYtC8vQB8xoBYEYaoHoE8gQfMJ88YeoL8poGyN8oKD8uYKYTwToPQMCwYG898iQI8sYrYeCk4jgLom4k0%2B43kyE6E2E%2BExE5E0UiAXADE6U5IWU6Yxs1YRcC4UYQ80gBYyQfwN4AATn8FZEkFWLMEkBOC2KOGYpQrONIAuOSDeCOC4COAOOYoOPEqWK4ECFYqOHQopPuMeOeIotmPeK%2BKVJ%2BI5P%2BPVM1OIFBLYE4FaBYCAlZGmkeEJAwi4GYreC4BWLRPwCID3L0F7PxIHOkCHKUBHIpN0BjxpKYDpJDMZNQuZOUs4HZIIE5NGh5NMvMssuohsrsocpuHFJnElNVMOA4zMHIvlPeOVIyqlIBI1KKtVJAHiosusu1OYsjz4DoDAUNONIpJtItNdNartIdKdJdLLPdKlk9OHhNN9P9MDOYldLDIjKjL6PwEnG8njJNKTJTN%2BFdIzPqBNJzLzPtALO2D6OLNLKmIrKrMwBrMmrqkbL4BbLbI7K7NdPcv7MJK8tkGHPJL6P8vHIbI3KsEsBnLnPgEXNSGXM4FXOgPXKnK3J3ISD3Puj%2Bs/JhjPPcAgvyCvOvGAqWHvIyEfMRsvLSAxtfNgpAqgv/Jhh/KxsJt6G/KAvxrRtsBsl/JpvmCprvIQo2CQq4FCrQtuNZM4BnjMosqsoMGSvspWLFOIpcuyrIrlMotIGovmkoFCsEuErstWNZHktZA2MkC4phJSE5v6M4FUpePOo%2BO%2BN%2BL0sBLKpBLBI4FMoFJYAUCAkRKAlsreAhAmCcpIqxLctkA8oeuJPkB8pep0ACFIECuCoZJQo5owsit0q5LiuIBYBtrtodqdpdqDHSv%2BClPFv8DysNsKvTtVJKoMpAHtr93n0duYvnxTsXzjphPqv1K3EoGar6I6u9KmObq6tjNdL6sEAGu9OmswD9IDNHmDKmImrrJ2tDJjLmuhopMWuQFTJWsEDWuzNnM2u2qLMZH2t4EOrnBOrrLOo0ourFSuswE7JfFuq9vuokEepJP9tHKDoFuMDBpsBzIPP%2BsBt2AKM%2BusG3NZN3KxOhoXNhsaHhrpuvPKDgvRvNhyFJsgeLVRrvKAb6FppgcQYpoZvAYJvGGQbyGxugvgeqGZvGOQqzIjoio4B5oTvtv2DLudptGEKIucpIHFrZslo0qoswBosSDoqzIVpADMDsv8CCG2LWKuMEdZAkqUruL1tsDUvyvmJAEkECBYsCAON2OYskGYo2LYpqBQv8HCqkYePUreNCtRMka5sMbkfLINNPMkCAA%3D)

## Links

- [source code](../../../../conceptrodon/raillivore/trip.hpp)
- [unit test](../../../../tests/unit/metafunctions/raillivore/trip.test.hpp)
