<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Roadrivore::ClassicTrek`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#roadrivore-classic-trek">To Index</a></p>

## Description

`Roadrivore::ClassicTrek` accepts an operation.
Its first layer accepts another operation for composition.
Then, it returns two commitment functions and twelve continuation functions.

- **Commitment**
  - **Conjuration:** When invoked, this function instantiates the first operation with the arguments. Then, it invokes the second operation using `Omennivore::Send` with the type result of the instantiated first operation as the packed vessel.
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
   >::type)
   >::type)
       &vellip;
   >::type)
   ></code></pre>

## Type Signature

This function has multiple signatures.

```Haskell
-- End in Conjuration
ClassicTrek ::   template<template<typename...> class...> class... 
              -> template<typename...> class...
              -> ...
              -> template<template<typename...> class...>
       
ClassicTrek ::   template<template<typename...> class...> class... 
              -> template<auto...> class...
              -> ...
              -> template<template<typename...> class...>
       
ClassicTrek ::   template<template<typename...> class...> class... 
              -> template<template<typename...> class...> class...
              -> ...
              -> template<template<typename...> class...>
       
ClassicTrek ::   template<template<typename...> class...> class... 
              -> template<template<auto...> class...> class...
              -> ...
              -> template<template<typename...> class...>
       
ClassicTrek ::   template<template<typename...> class...> class... 
              -> template<template<template<typename...> class...> class...> class...
              -> ...
              -> template<template<typename...> class...>
       
ClassicTrek ::   template<template<typename...> class...> class... 
              -> template<template<template<auto...> class...> class...> class...
              -> ...
              -> template<template<typename...> class...>
       
ClassicTrek ::   template<template<typename...> class...> class... 
              -> template<template<template<template<typename...> class...> class...> class...> class...
              -> ...
              -> template<template<typename...> class...>
       
ClassicTrek ::   template<template<typename...> class...> class... 
              -> template<template<template<template<auto...> class...> class...> class...> class...
              -> ...
              -> template<template<typename...> class...>
       
ClassicTrek ::   template<template<typename...> class...> class... 
              -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
              -> ...
              -> template<template<typename...> class...>
       
ClassicTrek ::   template<template<typename...> class...> class... 
              -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
              -> ...
              -> template<template<typename...> class...>
       
ClassicTrek ::   template<template<typename...> class...> class... 
              -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
              -> ...
              -> template<template<typename...> class...>
       
ClassicTrek ::   template<template<typename...> class...> class... 
              -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
              -> ...
              -> template<template<typename...> class...>

-- End in Transition
ClassicTrek ::   template<template<typename...> class...> class... 
              -> template<typename...> class...
              -> ...
              -> template<template<template<template<typename...> class...> class...> class...>
       
ClassicTrek ::   template<template<typename...> class...> class... 
              -> template<auto...> class...
              -> ...
              -> template<template<template<template<typename...> class...> class...> class...>
       
ClassicTrek ::   template<template<typename...> class...> class... 
              -> template<template<typename...> class...> class...
              -> ...
              -> template<template<template<template<typename...> class...> class...> class...>
       
ClassicTrek ::   template<template<typename...> class...> class... 
              -> template<template<auto...> class...> class...
              -> ...
              -> template<template<template<template<typename...> class...> class...> class...>
       
ClassicTrek ::   template<template<typename...> class...> class... 
              -> template<template<template<typename...> class...> class...> class...
              -> ...
              -> template<template<template<template<typename...> class...> class...> class...>
       
ClassicTrek ::   template<template<typename...> class...> class... 
              -> template<template<template<auto...> class...> class...> class...
              -> ...
              -> template<template<template<template<typename...> class...> class...> class...>
       
ClassicTrek ::   template<template<typename...> class...> class... 
              -> template<template<template<template<typename...> class...> class...> class...> class...
              -> ...
              -> template<template<template<template<typename...> class...> class...> class...>
       
ClassicTrek ::   template<template<typename...> class...> class... 
              -> template<template<template<template<auto...> class...> class...> class...> class...
              -> ...
              -> template<template<template<template<typename...> class...> class...> class...>
       
ClassicTrek ::   template<template<typename...> class...> class... 
              -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
              -> ...
              -> template<template<template<template<typename...> class...> class...> class...>
       
ClassicTrek ::   template<template<typename...> class...> class... 
              -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
              -> ...
              -> template<template<template<template<typename...> class...> class...> class...>
       
ClassicTrek ::   template<template<typename...> class...> class... 
              -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
              -> ...
              -> template<template<template<template<typename...> class...> class...> class...>
       
ClassicTrek ::   template<template<typename...> class...> class... 
              -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
              -> ...
              -> template<template<template<template<typename...> class...> class...> class...>
```

## Structure

```C++
template<template<template<typename...> class...> class>
struct ClassicTrek
{
    struct Commit
    {
        template<template<typename...> class...>
        alias Road = CONJURATION;

        template<template<template<template<typename...> class...> class...> class>
        alias Snow = TRANSITION;
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

template<typename...>
struct Capsule;

template<typename...>
struct Capsule_1;

template<typename...>
struct Capsule_2;

template<template<auto...> class...>
struct Carrier;

/**** OperationA ****//* Start */
template<auto Variable>
struct OperationA
{ 
    template<template<typename...> class...Containers>
    struct ProtoRoad
    {
        using type = Capsule<Containers<Shuttle<Variable>>...>;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};
/**** OperationA ****//* End */

/**** OperationB ****//* Start */
template<auto Multiplier>
struct OperationB
{
    template<typename...>
    struct Detail {};

    template
    <
        template<typename...> class Container,
        template<auto...> class Sequence,
        auto...I
    >
    struct Detail<Container<Sequence<I...>>>
    {
       template<auto...J>
       using Page = Container<Sequence<Multiplier*I..., J...>>;
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
    struct Detail
    {
        using type = Capsule<Sequences<Variable>...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = Detail<Agreements...>::type;
};
/**** OperationC ****//* End */

/**** First Example ****//* Start */
using SupposedResult = Capsule<Capsule_1<Shuttle<10*2, '*'>>, Capsule_2<Shuttle<10*2, '*'>>>;

using Metafunction = ClassicTrek<OperationA<2>::Road>
::Road<OperationB<10>::Mold>
::Sail<OperationC<'*'>::Rail>
::Commit;

using Result = Metafunction::Road<Capsule_1, Capsule_2>;

static_assert(std::same_as<Result, SupposedResult>);

// The following `static_assert` shows how the operations are composed:
static_assert(std::same_as<
    Send
    <
        Send<OperationA<2>::Road<Capsule_1, Capsule_2>::type>
        ::Road<OperationB<10>::Mold>::type
    >
    ::Sail<OperationC<'*'>::Rail>
    ,
    SupposedResult
>);
/**** First Example ****//* End */
```

- In the second example, we will transport the conjuration function to `InvokeRoad`.

```C++
/**** Second Example ****//* Start */
template<template<template<typename...> class...> class RoadArg>
struct InvokeRoadDetail
{
    using type = RoadArg<Capsule_1, Capsule_2>;
};

template<template<template<typename...> class...> class...Args>
using InvokeRoad = InvokeRoadDetail<Args...>::type;

using Result_1 = Metafunction::Snow<InvokeRoad>;

static_assert(std::same_as<Result_1, SupposedResult>);
/**** Second Example ****//* End */
```

## Implementation

We will compose functions using `Omennivore::Send`.
For example, we can compose a `Road` and a `Rail` in the following way:

```C++
template<template<typename...> class...Args>
using Metafunction = Send<Road<Args...>>::template Hail<Rail>;
```

Note that in order to succeed, `Road<Args...>` must be a packed `Rail`, meaning it is of the form `Vessel<Items...>` where `Items...` all have signature `template<auto...>`. This requirement is not checked by `ClassicTrek`.

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

- `Radio` is a `Road` and
- `Car` is a `Mold` or `Rail`.

Here is the entire implementation.

```C++
// `Radio` is a `Road`.
template<template<template<typename...> class...> class Radio>
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
           template<template<typename...> class...Signals>
           using Road = Send<typename Radio<Signals...>::type>::template Road<Car>;
           /**** Conjuration ****//* End */

           
           /**** Transition ****//* Start */
           // Helper function for the member template `Snow`.
           // This function transports the conjuration function `Road` without invoking it, 
           // allowing further process by other higher-order functions.
           template<template<template<template<typename...> class...> class...> class RoadVessel>
           struct Detail
           {
               // We transfer the conjuration function `Road` to `RoadVessel`.
               using type = RoadVessel<Road>;
           };

           template<template<template<template<typename...> class...> class...> class...Agreements>
           using Snow = Detail<Agreements...>::type;
           /**** Transition ****//* End */
       };
       /**** Commitment ****//* End */

       /**** Continuation ****//* Start */
       // This function composes the conjuration function `Road` and the `Agreements...`.
       // Note that even though `Agreements...` is variadic, it only allows a single argument.
       // This is because `Agreements...` will be used to invoke `ClassicTrek<*>::ProtoRoad`,
       // which has only one parameter `Car`.
       template<template<typename...> class...Agreements>
       using Road = ClassicTrek<Commit::template Road>::template ProtoRoad<Agreements...>;

       // This function composes the conjuration function `Road` and the `Agreements...`.
       // `Agreements` will be used to invoke `ClassicTrek<*>::ProtoSail.
       template<template<template<auto...> class...> class...Agreements>
       using Sail = ClassicTrek<Commit::template Road>::template ProtoSail<Agreements...>;
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
           template<template<typename...> class...Signals>
           using Road = Send<typename Radio<Signals...>::type>::template Sail<Car>;
           /**** Conjuration ****//* End */

           /**** Transition ****//* Start */
           template<template<template<template<typename...> class...> class...> class RoadVessel>
           struct Detail
           {
              using type = RoadVessel<Road>;
           };

           template<template<template<template<typename...> class...> class...> class...Agreements>
           using Snow = Detail<Agreements...>::type;
           /**** Transition ****//* End */
       };
       /**** Commitment ****//* End */

       /**** Continuation ****//* Start */
       template<template<typename...> class...Agreements>
       using Road = ClassicTrek<Commit::template Road>::template ProtoRoad<Agreements...>;

       template<template<template<auto...> class...> class...Agreements>
       using Sail = ClassicTrek<Commit::template Road>::template ProtoSail<Agreements...>;
       /**** Continuation ****//* End */
    };

    template<template<template<auto...> class...> class...Agreements>
    using Sail = ProtoSail<Agreements...>;
    /**** Define Sail ****//* End */
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMxmpK4AMngMmAByPgBGmMQSAJwapAAOqAqETgwe3r4BQemZjgJhEdEscQlcybaY9iUMQgRMxAS5Pn6BdQ3Zza0EZVGx8UkpCi1tHfndEwNDFVVjAJS2qF7EyOwcAPQ7ANRCeCyptHg0mOj7JgBsGkKutxr7VF4MDtkAdCYaAIIEmBOBgBJn8bgIAE9UoxWJh9somMgANaXABqmAUdlB2B%2BvwmxC8DkOrmuAHYrKSACKgqx/XEAoFMEFghmnJmYUHgqEwtifPnY/bIAyY/YeQRMcLxUj7SHQ5i8vnYehsQQKbG4/GEgjEhjoTlilqS4icpWAxgEBR877%2BHE23Emcm4/bOmWAtnM8Fu4Eclnc%2BWYK0CoVMEUAeWhxCZ2XVfxd%2B01RMpmENtCdLr2%2BwAkgwAG6oFHXO7h%2BJRgRPfYAd0ICBlCDhT1NKotgbu31jLodFn2XkyRhl3Ou/kp%2B2LkcaJuV5st/Lt/i7Dupc/t7edrO9nLX7I3fthgZtguF08%2Bv2AxEwZtVMd%2BcZ74WA%2BwASqgmFdQcOkynOSezxfmzPsCAICyj6tK/AuNLLv8Xpbiy0EepuHpMF4RB7tgB4hkeQaHocRDIsQqCoCw0oIT6bhISh/7oZiVoPAAjl4jBbGqdp/Am2oPLqnLNKgeEESwXGYPRjEYqhV6dmmq5waRJEblJnLkagqFUZh%2B7BmGEalgwV5xmx%2BwfhKqYrvsGbZnmBZPKOmnllWBA1rZ9Z3HRDHvCJ/KthJZJdrefbAYOw6WeOYJOcJKm2vOVIQXSRkybBjLwXJYIKUpamhcpVrfueTbMTiRnefeQgGX5enJgZX6nplU6oYBwGRWBEVLlFYF/BmTwPi%2BTjlngCj7EwhYaE%2BL5PG2UFxdJCWeqN25yrulEpcl2FtfgqBXrpbiHngyAACpnki9qOkZOwAFTHYdxU0BEj7PlcJ2HXsp39G0%2By3R5LV3GRxp3PsXU9X1ACynh6u50XjTFXLTQq1poSloqtNpLq6co%2BFEANepGeJRnpjdoqESwhBNk9J13ThAxPTsHnwwQBJEh4LC4wQ5POuj15xizxlY2K2gbJpBPHUTD3as9GOs69/Xtctn2GK%2Bb2wxLZ6CoRRSXPsdZnsNrMs6Dms7hDWEYTReDAMwtDZQzLN5ZdL5FRxeq%2BuDcKLR1QUG0boXVdy2LVVJFs22473qg1zPq86R0ndjDCc2O2Q87dR37Nguqk5BQcdkLLMh8d%2BzbYYxRRzdfOTALZOp3GGYABL1BGLxvB8AgvCQtZwmwlTxK6o19UIDCoBWQ2myXBybQg32vO8jQypGDAKOkbTdfZ8vh1zo/DzXDB9Sj1nVus2rhGZd5fQQ0q9%2BmBxiLQXe768bQq/sqT4Ux3UxBC%2ByoPZxDKwbKsALQkFgr9L40lqH0kpNWK7oxrAImqAqaPIAyzUPPNPWsCMLe3RJieocNk66X0nQQBnkcF932AAdThJTbOVAW6zzQPPSOtc/5R1aldcsRBV5XRQViIGgdk4unNr5N8yCMRYjBGvWcoFOFkkXKBHBmsQbSPAcBf08DqKIMUZDNKfIMq/hNsXLhvZ8qdwrEVLBqYwTqKylVIC7sA6iPTqdLOE8si1zzrHeO10i4cI7PVERwt2Y4zxuaaORNnGJ0auraxYdHAMC8NzRx90C5BLccHfug9uq0NrmgE4GQMQNznhHbmKSV70MGhLBOs8ngmMqm5DQathYHEiM/YhCAmT7EwDmRgtZ1jABrKU8qGiWzPG%2BjmVoeB2rIGlIQJ%2BDBaCPxPl3bqvUdH0B6sQYAPhzRVLTok76304iiB7A5P43TTEVMrHQWg%2Bw4jdiUFcJh298x7LWhhDa21MC7TBGYxGz9UBrzuKQU2GYKyD2QDWBp3UBCTPGXCVIrRYQAlfk8P27D1ZSNkdrGBKi5pqIOVOdBN4dHeyKvczEjydr6h8QQT2bchEASAl7d5yMGHGMxaqUSAdfkbOSdXUeaTFYzzrNkheUc8nMMKc8SWWSuk/kOd8BF1S%2BplMvJ9KstBTnnN2Vc1AX1cy3L6gSzIW1iWvP/IBWlqACp0DWXGJFkCQHrkSshRSSjUrouPIyi02LtG71Nac3hOqiXPJJbTQg5LQHew9tStuxrPVlQleUyGtUQneMEOESJo9olxwToLDh4EWXA1kSDFFCijxytdSxDh5sUZFWNUItwRbQpxsxqHJM517ZXX8U49NriXpY0bZKQ4hVU38zifggeQ8OVR2%2BrPTIuMDCvxKXcStDDPpYCbVcJgMRUAtPNSZbUDTdT0B5XCUQShKwqzuTLPpszV6lWlUAq1ECbV3pgmRO1BaC0w2NCWnSlMtTwiRia0qaN9rxLZqHGmdN8b9tiRm9Wq1SWmyZlYhNOSU2E1jgOqDnDLX3rkTNNFcC%2BRHENmITRQGcW73Lbw62UD/SPjFlxZ2RGzE1RtEG70vbsFgj9sInBoSOb8ocSh06gSM3caxrYnO/Heaocg640RmHH1yfgvmh1L6HV8NQUYnKJGKZU21IYnB8HRHOm4QOXhKNWFoMEfSsK%2BmPFJwwzI29CnpJKdwwg1zyjdbKJrW61m5sO5dwMSVdj1aXWu3MdCOtydQlifsSvVNQmZOsyzZ4tO3iA0EHAwJtNLi7OpZA7IJNUSstocSxrBzWGXOecLaFnzFyyMtu9etPVfqOOkpY%2ByENzGw3BvnYNBl0amX/lqqbJzslwFJWU5N51A3i2afVn5wqjWHnNZeb7Nr3XWOUvawCH9HzI39YqoN2NlivH5cTREorknBPto8sl3LrdHPlcfRN9zjq8PTcO7NjyC26AVt/ftkLM3a0neDl2zATa2OnPizduktnGrWJurzXE6dNrYCEJtQmyPEeI47XSMw/hwhCi8FgQcbhkJ0EIBCMSfxQYvZWl%2BokQgEDIQIPQYbNO8121EqxBn2oyKpAUF4Nn2aRqOcqyW1aTABdC8wAAfS4Oz0XFWudDZ5zpmG0v6Cy7MIr0btqKKve53iXnb7iB4HiIr0JAVsjXggyTDNtO7X7FRIM1dwvNO6WtwIJqdV5w5se8ilXhu%2BQGglBEYgxHP3q966jTNgGg7GehPiqXgvhdrfFEaZibgmcs7Ty7s3bufS2mwMylLYjFcWqe4poPVX0o1Y/e6vs5Ghy7bpX1wHn3gcSLh78K3GlGi26ywlyCfeSyNC7Hbx6DvxoKX2L9IXjhTjm/fR7k3XuGDd7L1rGvDfnSYKC16x0PePIyTRmCXu2/oGvtD0aH5xdHcG6q8SISLk78kZe5mW7u/4wm7061jP4eAkL%2BWwnImYzKxet28erMD%2B9qnwAAUrVubAiMAPWC3jfoAUFIJM5CAWCPPrQIvmcPEIdGAXyNKHAeAZFuXiLpXoHlfhikDtigjL%2Bv9LQLHnGAZr5rijwmga0GbhbmCH/h3hoqGiRPCEwCgaXpAeIvdpfvIvQZ3tiubCwa%2BC3sasoVGp3pIbDtIc1FjOvhPkPjDj7qPtQjkK2jEvbq4jAc7q7jEO7hqGvv3tkG4HtFvlXqRHTqpO9sFC5JHtpt%2BnpgBmXqRj5CZjwZrqRD4UxJyPnkMnYUXloXHjoT7jQQHrep4VDO9t5t/mWoti3oITWoxhYt3skSYZpG4OYdlnEljqHAAGJ4AR7ajYCqCsCnBwiT6Fy4h%2BZeCpCKzoAPgYgL7J4RH6gp4y7y5cTM4ECs6kRcAaCHRBD7BgAcCHTLH%2BzYDSj86p5y465BRTEzGchzELHSjLGrEcDrH%2BwSJ/BKElSCpLaEoracjr5gRgi7FUqUq4iARVr6GHEaChrqElqAQA7r4uFginFrFdZtTsaaaASgaECK5lqDH4FFS/S3GjrOAgBVpbHjFcCbFjFa5vGK5zCODICy4YTxAEAQATDoCAQKCwhklZ4DGp77yHA9F9FMkL7YjLCW6JJwj8BKpnx9hPDEkbQMlKBtDlgKAIAzLKwBazyoBOECCzJyxcoZI0kOFRiknkltBUkEA0kgB0lsAMmcgeSUZn4uHFyUZgjPGchvFfH0q%2Bz4ly64ka7bHa4iEWJzbqz2nt4/FghzH/EAwekRZn5enOhAmlTWmKk5CcjgnnGQmRlhn7Bv5xhCBslqkcn4H2g2jckByhL1GNFxwtFAjtGGE5bw5YwPCUJXDNGtELIdFxJ64PrV50HB6vbey/BLL07q6mS3IoyBG%2B7fZcFhHDgoydnACjERHy54lTmEksrH4c65pLli476ZFua15qJLLEbmy9kojN7Di7mYD9kH5fhblFERYi6InMny4olokjzZBAl6KgGap7lWZEktAklikUm6n6mGly4hiciZkEDTmsm9EZlIn0w5m1ShJVkCA1nFltGVEJYcCrC0CcAACsvAfgHAWgpAqAnALhlg1g8Y6wmw9Y%2BOPApAZKOFKFqwSIIA6FNwnwAAHDcFIOhaSDcJIIkP4JxfjvoJwJILwCwBIBoCkNhbhfhRwLwAoCACkNRVoKsHALADAIgCAJvKkMhOQJQFynQPEJELCJwKoKxR/FxfsMAMgMgPsFIJ8GYLwJcIQCQHgDSbifwIICIGIOwFIDIIIIoCoOoDRaQLoLiRWJGKkJwDwKhRhVhZoLwFJaGMhJpdqKgFQPsMZTcKZZIOZZZdZZILZfsBADTKkHpbChRcsLwApShaQBAEgLpfQGQBQBAHVaMMAFIEEDQPgfELJRADELFaQDEOEK0BCBFbwANcwMQBCKGDENoJgA4CNaQGkk2KGBMsNYFVgDEF4MAGREqrJdwLwFgCwIYMAOIGtQ0bNY4C0rtbhZgKoLNchNsJReEACGhYFWcDEJGBNR4FgH1ZTMcPNS0sQGukoEmIdUYGcEYLFasFQAYMAAoKiObhWMWNhZRW5cIKIOIN5ajX5WoH1cFfoEdSgNYNYPoHgDELJZAKsAqf/JwB/NSW%2BKYERZYGYJJQDWblgOTRAKsHYOdQ%2BRAK4NMH4LiaEJKIsKMLiUULFgLXoBLY0AsCMNUD0DzQIPzFLbidzcvPzHLc3ArXMFMJ4J0HoLrYMCLfLRIFzaRVsGbQJRwJhaQBJXFZwGlSZWZRZVZTZWYAVbgI5aVf4FwOVVRZDasHWC%2BKMJzaQPRZIP4J8DxaSJIBoJIGYJIHcBoIxYkNbUJaQCJb7Z8GxTcMxYkMxVwDcOhZIFwOhTxTcHbX1VJTJXJQHTRUpapTVepYlVpY1c1cQAZWwJwK0CwDmKSB/L1MGH2DUJ8FwJ8NdfgEQGzXoKjR5RjdIFjUoDjYFboEEKFVLiNVFTbTFYFfFa3clalb3f3YPehCPYkGPRPQVUVSVdcPjmYP7ZVUpbVQrCVdpU1a/fVSAMfQPcPa1YkHMXwHQDCt1b1YFWNUNfNRAxNVNTNXNXtQtTjOaMtZMn1etZtdtcbPNQdUdSdbhfgGeB8JdX1TdXdQCPNU9fUH1W9R9RCF9dsLhb9SJQgwDUDZgCDbg3eJDXwDDXDQjUjfNXPejV5YvbINjQFbhWvfjRDQzVYJYCTWTfAJTakNTRwLTXqfTUTUzSzfEGzRiEo4rcvC4LqKrcELqFrUsOLRkJLfrfkFY%2BJgwBY2LYY40CrbY4LS430AXE4zrQXKY0bT41bQoBbV5dvbbfbXhY7T/afX/dZRfePc8BAF7dPXfb7Y/YHaQMHT/JQNvRnVnRffHaSOXaSKSP4AnUnaXVXXvZwLXfJdw8pWpRpW3TpZ/fpYZRwL3WZSwAoDmFZTmKPd6BMPZVPU5S5T5WjZ5RIKI75cvRIzoAEKQBveFXtWE7vZJZwAlQQElU/EfcQCwF0z030wM%2ByBMNfa0z7f4Okw3dVS/ScG/e3ecyAL070bLv04kLLoM8BZ04vcA11ZQGA7hdA6tZRUC7A%2BdfNYtcgytWg5gBtVtSfLtZRTg2DQw/tWdUQ/o4FaQ8gPdRQ4IFQ69aTbQ/Qz9Wbsw5Rawxkhw2DVw9c9DeIXw5gIjXKII7IPPSI%2BM%2BI7jQswYDI1ozYG9Rzco6ozsNSYTYzRYMzXFazc5foxTZ484HzSY%2B43oMLeUKbfYzY3kB4zLdkIE2rfUErU0H4yqwa70Mrd4ybdrYbSa9qza/MFa5Y%2BbRsJbX7dbeE9XVE3swc70/sG858J857SMz7X7RVRk1k6Hbk8JSAGYBff4P4OhehfHXMRoPG5xcxVU%2Bs9JbYHXU/XRSAJHWPf4MxSXfjkmzcPjpxdbf4Gsw7dm3m9bXZZm3W2Gw3asADZkM4JIEAA%3D)

## Links

- [source code](../../../../conceptrodon/descend/roadrivore/classic_trek.hpp)
- [unit test](../../../../tests/unit/metafunctions/roadrivore/classic_trek.test.hpp)
