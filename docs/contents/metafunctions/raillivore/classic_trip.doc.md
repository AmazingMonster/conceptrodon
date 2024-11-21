<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Raillivore::ClassicTrip`

## Description

`Raillivore::ClassicTrip` accepts an operation.
Its first layer accepts another operation.
Then, it returns two commitment functions and twelve continuation functions.

- **Commitment**
  - **Conjuration:** When invoked, the function instantiates the first operation with the arguments and then the second operation with the corresponding member of the result.
  - **Transition:** When invoked by a vessel, this function transports the conjuration function to the vessel.

- **Continuation**

  When invoked by another operation, the function returns a `ClassicTrip` that is instantiated by the conjuration function and whose first layer is instantiated by the new operation.

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
ClassicTrip ::   template<template<auto...> class...> class... 
              -> template<typename...> class...
              -> ...
              -> template<template<auto...> class...>
       
ClassicTrip ::   template<template<auto...> class...> class... 
              -> template<auto...> class...
              -> ...
              -> template<template<auto...> class...>
       
ClassicTrip ::   template<template<auto...> class...> class... 
              -> template<template<typename...> class...> class...
              -> ...
              -> template<template<auto...> class...>
       
ClassicTrip ::   template<template<auto...> class...> class... 
              -> template<template<auto...> class...> class...
              -> ...
              -> template<template<auto...> class...>
       
ClassicTrip ::   template<template<auto...> class...> class... 
              -> template<template<template<typename...> class...> class...> class...
              -> ...
              -> template<template<auto...> class...>
       
ClassicTrip ::   template<template<auto...> class...> class... 
              -> template<template<template<auto...> class...> class...> class...
              -> ...
              -> template<template<auto...> class...>
       
ClassicTrip ::   template<template<auto...> class...> class... 
              -> template<template<template<template<typename...> class...> class...> class...> class...
              -> ...
              -> template<template<auto...> class...>
       
ClassicTrip ::   template<template<auto...> class...> class... 
              -> template<template<template<template<auto...> class...> class...> class...> class...
              -> ...
              -> template<template<auto...> class...>
       
ClassicTrip ::   template<template<auto...> class...> class... 
              -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
              -> ...
              -> template<template<auto...> class...>
       
ClassicTrip ::   template<template<auto...> class...> class... 
              -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
              -> ...
              -> template<template<auto...> class...>
       
ClassicTrip ::   template<template<auto...> class...> class... 
              -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
              -> ...
              -> template<template<auto...> class...>
       
ClassicTrip ::   template<template<auto...> class...> class... 
              -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
              -> ...
              -> template<template<auto...> class...>

-- End in Transition
ClassicTrip ::   template<template<auto...> class...> class... 
              -> template<typename...> class...
              -> ...
              -> template<template<template<template<auto...> class...> class...> class...>
       
ClassicTrip ::   template<template<auto...> class...> class... 
              -> template<auto...> class...
              -> ...
              -> template<template<template<template<auto...> class...> class...> class...>
       
ClassicTrip ::   template<template<auto...> class...> class... 
              -> template<template<typename...> class...> class...
              -> ...
              -> template<template<template<template<auto...> class...> class...> class...>
       
ClassicTrip ::   template<template<auto...> class...> class... 
              -> template<template<auto...> class...> class...
              -> ...
              -> template<template<template<template<auto...> class...> class...> class...>
       
ClassicTrip ::   template<template<auto...> class...> class... 
              -> template<template<template<typename...> class...> class...> class...
              -> ...
              -> template<template<template<template<auto...> class...> class...> class...>
       
ClassicTrip ::   template<template<auto...> class...> class... 
              -> template<template<template<auto...> class...> class...> class...
              -> ...
              -> template<template<template<template<auto...> class...> class...> class...>
       
ClassicTrip ::   template<template<auto...> class...> class... 
              -> template<template<template<template<typename...> class...> class...> class...> class...
              -> ...
              -> template<template<template<template<auto...> class...> class...> class...>
       
ClassicTrip ::   template<template<auto...> class...> class... 
              -> template<template<template<template<auto...> class...> class...> class...> class...
              -> ...
              -> template<template<template<template<auto...> class...> class...> class...>
       
ClassicTrip ::   template<template<auto...> class...> class... 
              -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
              -> ...
              -> template<template<template<template<auto...> class...> class...> class...>
       
ClassicTrip ::   template<template<auto...> class...> class... 
              -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
              -> ...
              -> template<template<template<template<auto...> class...> class...> class...>
       
ClassicTrip ::   template<template<auto...> class...> class... 
              -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
              -> ...
              -> template<template<template<template<auto...> class...> class...> class...>
       
ClassicTrip ::   template<template<auto...> class...> class... 
              -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
              -> ...
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

- In the first example, we will compose `OperationA<2>::Rail`, `OperationB<10>::Mold`, and `OperationC<'*'>::Rail`.

```C++
template<auto...>
struct Shuttle;

/**** OperationA ****//* Start */
template<auto Variable>
struct OperationA
{ 
    template<template<auto...> class Sequence>
    struct ProtoRail
    {
        using type = Sequence<Variable>;
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};
/**** OperationA ****//* End */

/**** OperationB ****//* Start */
template<auto Multiplier>
struct OperationB
{
    template<typename>
    struct ProtoMold {};

    template<template<auto...> class Sequence, auto I>
    struct ProtoMold<Sequence<I>>
    {
       template<auto...J>
       using Page = Sequence<Multiplier*I, J...>;
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

using Metafunction = ClassicTrip<OperationA<2>::Rail>
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
           template<template<auto...> class...Signals>
           using Rail = Car<typename Radio<Signals...>::type>;
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
       // This is because `Agreements...` will be used to invoke `ClassicTrip<...>::ProtoRoad`,
       // which has only one parameter `Car`.
       template<template<typename...> class...Agreements>
       using Road = ClassicTrip<Commit::template Rail>::template ProtoRoad<Agreements...>;

       // This function composes the conjuration function `Rail` and the `Agreements...`.
       // `Agreements` will be used to invoke `ClassicTrip<...>::ProtoSail.
       template<template<template<auto...> class...> class...Agreements>
       using Sail = ClassicTrip<Commit::template Rail>::template ProtoSail<Agreements...>;
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
       using Road = ClassicTrip<Commit::template Rail>::template ProtoRoad<Agreements...>;

       template<template<template<auto...> class...> class...Agreements>
       using Sail = ClassicTrip<Commit::template Rail>::template ProtoSail<Agreements...>;
       /**** Continuation ****//* End */
    };

    template<template<template<auto...> class...> class...Agreements>
    using Sail = ProtoSail<Agreements...>;
    /**** Define Sail ****//* End */
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMxmpK4AMngMmAByPgBGmMQSkhqkAA6oCoRODB7evgFBaRmOAmER0SxxCVLJdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Yk1TS1teZ0KE4PhwxWj1QCUtqhexMjsHAD0uwDUJgBsGgBKTPioJxoHeAoHTEenF3Q3AHQmGgCCBJgsKQMfxM/jcfwBQMwILB/0BTGBoKYXiI71RIOwB2QBgUClRn38GKxTBxBwuV3RX2%2Bs2IXgcBzc2IyyAAKsQ8ClKSYAOxWH4HfkHXYAKhFQoOABFMDQIqTUJcDqKhfsxf0WgrdpSBYLDjc3M0bncHk8bgBZTzoD6agXguEImEQ%2BFQ0EEACeKUYrEwePRmMZ9P1BKt/OptIIB2UxFQRDOcotfIF3N53y1AuFovpqBYLEIbEECtFyoOqrDSqDWpDdI8WcIZYTPNrKcFiozDG0m3hWXzIsLxfVDZT%2B2e50uTgNhnQQ71xDHxEwmMzhUwE4Q8S9/a1g4AYnhiLNSAcAO5z8KzQyOR1Dsmj06PBgT1AxJrhR5D13u5hsS3xxupw7MlcMPuR53AwABuqAANZzrq%2Bo3gehAIAcBArgcs4KF4tCOEYr5uh6n6nJ834/khsKQtCNpkYiyKoN6BK%2BsSuKokIeDAMwtAKBSRE/l4GTYa8tBHP44r%2BtOzq4R%2Bc5XtcoLMaxYiMfi2AgCAb5OtgIJJsRqbNh4rbtr0XZKsKBzYHefY/OuCZcY2aYigcrKGEUnaKj2czmcmWnagcAAS3TusQBxUF4DD1AIgUkEhKFsEsAUUReNzeUwbwEZZ/KDv%2B9yBcFoUMEhxCOWkLQPMhc5oHp%2BUGUFIUGTc/EGvByEbGG4TgRB4TAHcBD7qlXliLQqDwdhQUtCuAUpJG2wkjELoHFGo0HAgLGjQAtCQWABVVOW4j1cV2rtTr2raB37dCSIomidFEjitGEoyN30SS/EAGqYDi3ScR5WkVmGkpPrQPWJj1G6HAA6nOBD5QwChUPEkWlQIbYVZ2m01S8SX/TeRCXujL1vRjGiEZ9nn8jx7VIbhgnCc9r12NCdWBv4mmedy4oaZy1kpidzqkY65E83t/MHWdNEXbdDH3VdCk%2BpLeLfMAs7/IwBAcYGHNaqT2GJXQlMSpgf3QnLCu5srN3KapbNq9p6YOVDmRhS5xmmROpYcyzFtE1bdlVtmBDG4ZhZO%2B5/a2WKulYV4Hb2wWxm9i7HtpX%2Bi0PCjnZoAC6SvXD87lZHuUp2FtXo2OZklUOhuYIrghSylHODpEUbgwg8IHJgoGMJFGzAIhNzl5XJtojemWgc0eAjsg%2B6ELNDC0DNfUDUaBy8cA9CPMQwA%2BErhM/ulSeGgccSiDx0GnL3xvV7c8G0AJcQHEfE5Yy1kHHxoDIMXgLJshyoKmyAEZRqgMZLg3FIMHQ4B5FrIEQk3B4AgZ5TznCkZono/gBRgtOGu8cSIOgFtg464lPQSzuqiU%2BSsVbqQ5hrDqgCJwgmEq/HE79WTsmhN7QgZtBakiLgSdhuDwyRmjLGA28sK5nxuu7UB9ld751ymnRcxUUJlURrnLK1VOyF2SrcccWce7CL7ufLeNkdQn10WfeqdBr5zjvkhVAIFWrP3oUyJhX83A/z/kQIQ6MDGc0FnzXBvijqnWooQ8WosHoKRIVXD63El5FnRjrBxjDP4sMzD7HhR1OFvG4SpDhbjUAeMyW4CJ/dFLu23jpWQ4QI4GQdmKQOcctRu0ZuzImXNDqUTBPgtgwTrrEJMaQqJApKGynlLQvh/9qFCKNqQsRTSiIh11tKSSsZ/aOzMnHMs8zJSLNidrGpRY3L1N/JIzK0i96lwyNmAwsUUI3FyRMm8WBFkTiYDEVAbcvFeQAJJhibneeg8jSrEjnOA1ck5YK3EysaNGGiPmtLhT4qi51FJhO6Q8KcAzgwQ1DGM9xRciKA1ruU6svslYrJVAcjUHNvoZmJf2AlmCNzlJztU6O5KBjuWJvCvxiKRbIplkxFibEyE9SGfxeJAY3BSWhLJIVP99rhiYMANSpTPLzN0koll3ZVnO0pd8Hq8ybZOSjlqtlapDlaS5QE7m3K2m8x5aih1oTJYZNoLjWmqsGUCmpb9PFnr%2BT0uJoMmJqkdbUzxnTLh6lZl%2BqOFyVm0adoIttTgq1yahZBKdUQvlWbpZZqKcKy2JMYlawEqMn1BT81ytwiqrSBrIZGtynsupuqfyNKZgOIlPs/ZNrWbq4OTLw7KL2bHFtjZLXtNUhJR17x80YvVjE6h8TGSJOYaCVhBA0mQhdeiTdF47mCNBJW0W4iObjrtWmwJSLc0hOzTe2dHrolk3yaWoS9Jl0f1XW4ddu6/jbqyfK3Jz7JkiOmce6NZT0xh0qUO1lJle1ljbc0rUZ6U3tOFtO69PSZ19MiQ%2BoNT64mjMA1wwpOHikUnA57MUWyFg7IEj2nVnI40nu%2BCHRU3ZKS2WZNgIQzICycfY%2BxvtFkzD%2BHCFiLwWBBJuGRHQQgLoPqUlaeh49PxqVCAQMiAg9AWPzIAPL%2BVzsmYdFKlNJuFgcJ6I8Xk6Y9dSgz8QjNMYsEcIiKH01Xsun6IQmAACOXhGDbDndSu5vqGn1jVkMkNoyfP%2BcCwdKzbIbPKso/65jCa3NJuUxm29WH73kKJqKwjr7QsVrI1LBmSZEM/H04Z3oxnYPNuabVxzvQXMmfZXHbLWMTQYUcICPA8QPr2bq1kKrEWWlZc6cqoiIX%2BGoDNLQGh9Z0tVcyza7rvLMMPFiwFkKmB9wWc%2BcFrFdJcmLYtDJPze2gugmOwzAr4X23IfMzlgAUnO/D2FlCKugq%2B3b8XoS9cwuyWgg3iBCk%2BfuN7MznvVb1et1Nk6CG9Kmbhx7X2OoXZ1ud80wG9Gw6Y/GpMLWkYCHa41%2BDFkavNgc2T7IZL9mdd1Ztyz1mYi2YKyN1rWQ3DObLO5y9W2vMMSLNdwHeHMU0jpOW/6%2BKJvESixTGL4v9vQkS6PDnKW4eraQ9aLLr3PNizy%2BVudRXtZlr1iRo9ikzbVoTbrmn6Y6e5zcIzpr1PWPNm3LuMM2BVCsEBHODrZrdVDKEF4FIi50BnFen1nWGmtO2bcFwDQQoggHDABwIUWeKNre%2BEMk0VvTmjISR%2B5xLv6vQjMDukA9MCvKQmaCSvY3oSp9rxdj6ykgPN9GwIPnoIs8544LX%2BvlJlLrpY6KuPmEdZF6aNIxvJHE8EG09r5pp5HDIAAPoMXiAQCAsx0DKQUJ6XfKtJUz66kWSP0fY/oUwuiFYunE5zn4FfAaZMbib/fufpQLQDQFAEB54FoBos5UA%2B8oZV54Z04lBj9KQf8d898WhD8CBj8QBT82Bz9oQywW9%2B9oQh9c8sl6Y%2BciI8CGArBQR28slO9QRcDIC9VQQa9iCSN1wV818EN/1q18UskfslVODsAQEiII8o8M4Y8r9OQCRn9o15kfdZgTIA8IRg9KdGNPd5kfMyoJx/dA8V4Q8SwWcDcNtDdhdjcKtTCXVvg15htTswxPkwIn5%2BJZd%2BciIld3RQ10ZLDgBpVNNV9OdxFHcEdfhDCkdjCMMRc8s14C0C8Yk7C7ExVRlYiHD0YnDD1Iiq13Qp8F0r9t8uA59i9spehlIS1oREioIx8MsqQmgt8/999UD0DMDMBsDQR78%2Bscj9wRC78JCpD3Z1C6gBAtDFCg93de0OA1haBOAABWXgPwDgLQUgVATgPnSwawReDYLYaCUTHgUgDdWY0YtYCCEACYyQd4DQSQLgLkfwDQCYjQMwY4Y4MwAADgeP0E4EkF4BYAkA0GSBmLmIWI4F4AUBAGSB2K0DWDgFgBgEQBACahSGRHIEoFkToHiEiE9E4FUAeOOGWmOEkAOGAGQGQAOCkHeDMF4CXEIBIDwGPy4BkEEBEDEHYCkBpPkCUDUE0B0D0APHyhSE4B4DGMmOmLZPmM4D02RFhLDFQCoAOHRMxOxNxPxMJOOLMAOAgCrBSCRNQU2JWF4BBNGNIAgCQERPoDIAoAgENNGGACkCCBoEwniEBIgBiEFJiHCGaBdB5N4CdOYGIBdD0xiG0DqB2K2LTmNj02nldN2NICwBiC8GAD1CvkBO4F4CwBYEMGXh2DmPwFnHqDbnjLmMwFUDqGRB2C2PCD%2BHGPDLBxiHyi9I8CwEFIhjwA%2BITNIDbmIFeSUElGTKMDByMDZLWCoAMGAAUCekGwPAcxmK2P4FpNEHEEZMnOZJUHUHDN0GpIMB7NMGWMsH0DwBiEBMgDWAgN6HjOWiP1oXXKsEsDMF%2BJbLZCwF3IgDWFqByhcDvCmD8GpNCAWHKEqD0EKDtmyE8HaB/PSD/KGC/OWC6B6AaDmFfL0EfN6GLFApGCqFsGgoAryGpNPBaEQpigkAfLWO2FwpeI4CmNIB%2BN4D%2BKlIxKxJxLxIJKJKVIgFwHJI1P8C4C1O2N7LWBXEuFGHvNIAOMkH8HeAAE5/AuQkhJAzBJBTgrjjhhKiK3jSAPjWL3hjguBjgHjhKHj1KjiuAJjRLjhSLBS/iASgSOLdiwTIT9ToTRS4STSzTiAUS2BOBmgWBQIuRlongiRsIuBhL3guATjST8AiAby9A5y6SZzpA5zFAFzBTdAghOSmBuSEy%2BTiKBTwy/iRSCAxTZpJTXL3LPL6IfK/KArbgVSFx1SjhRMzB2KdSwSDSKqjT4TTTGrRh8qPLvKLThLU8%2BA6AUE7SHTwyPSXS3TSBhqvSfS/SHBRqgylYQyZ5BTIzozYz2JRqkyUzxBwyMz/S8BszBS8yCy/hRqSzuhBSKyqyXQay0ztS2RGytiWy2zMAOyNr2pey%2BAByhyRyxzRrwrpyGSorZAYrWSlyQAghVzjBrBrAtydz4B9yUhDzOBjy0DTzIaLyrz4gbzXpYaIKdrnAIBXAYL3y7xsLvzqTfzehCbUhgLegSbwK4KoKBhKb6aBAELPykLYLULcg3yUKBhaaqg8LNgCK2KiKSKyKhSOBV43KPKvLwbCSSqTjlSmKQqqrWLarOLSBuL1pKBUrFLlK/LTiuR9KuQLjJLpKzijKMrOBTLgS3rwSoSYS7KETWrHLUSOBXLZSWAFBQICTQJfL3hIRZggrmLKSwrZAIr/qmSgbFy5jdB/BSBErkreSRb0rfjhTbLxS8riAWAPavafa/aA6wxyqARKrzB/B/A1aLK9SGri6mr7LnaQBvao9t9fbhLt8C7d8s7sTeqbTdxKBBq5jxqwytjB7Jr/SZqUk5rQzFrMAoyYy%2Bp4ytj1quzrqIydwdq9rwyDrkBCzjrBBTryztyLqrq6zbrRqHqM5nquzXrK7%2BzFVPrMBRz3wfqw6/rEhI6WTo72S47waUBUabAKy7y4aEa9gj9f6NyLBLzyLrzKSsa9ycanz8aXy0LuaPyyh2aybqbedkGgKG0%2BbYLuhca%2BhObAKMKCGcpWa0GcKMLiH0KeasK2aqGBb1jCKyzRbjLOBJac7vaDgW7/bHR5DGLgqIpS62LtT1bNbeKdb3jQa/Ky6Jjriziviy6uQNKLbU7/jbAzK6r9iQBJAJiRKJiHjbjhLJBhKLixKuBv7OB/AU7yKrbzLQTUqSS1G7GNHtHmzbSshdGgA%3D%3D)

## Links

- [source code](../../../../conceptrodon/raillivore/classic_trip.hpp)
- [unit test](../../../../tests/unit/metafunctions/raillivore/classic_trip.test.hpp)
