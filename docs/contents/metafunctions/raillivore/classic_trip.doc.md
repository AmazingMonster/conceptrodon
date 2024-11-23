<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Raillivore::ClassicTrip`

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
       // This is because `Agreements...` will be used to invoke `ClassicTrip<*>::ProtoRoad`,
       // which has only one parameter `Car`.
       template<template<typename...> class...Agreements>
       using Road = ClassicTrip<Commit::template Rail>::template ProtoRoad<Agreements...>;

       // This function composes the conjuration function `Rail` and the `Agreements...`.
       // `Agreements` will be used to invoke `ClassicTrip<*>::ProtoSail.
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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMxmpK4AMngMmAByPgBGmMQSkhqkAA6oCoRODB7evgFBaRmOAmER0SxxCVLJdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Yk1TS1teZ0KE4PhwxWj1QCUtqhexMjsHAD0uwDUJgBsGgBKTPioJxoHeAoHTEenF3Q3AHQmGgCCBJgsKQMfxM/jcfwBQMwILB/0BTGBoKYXiI71RIOwB2QBgUClRn38GKxTBxBwuV3RX2%2Bs2IXgcBzc2IyyAAKsQ8ClKSYAOxWH4HfkHXYAKhFQoOABFMDQIqTUJcDqKhfsxf0WgrdpSBYLDjc3M0bncHk8bgBZTzoD6agXguEImEQ%2BFQ0EEACeKUYrEwePRmMZ9P1BKt/OptIIB2UxFQRDOcotfIF3N53y1AuFovpqBYLEIbEECtFyoOqrDSqDWpDdI8WcIZYTPNrKcFiozDG0m3hWXzIsLxfVDZT%2B2e50uTgNhnQQ71xDHxEwmMzhUwE4Q8S9/a1g4AYnhiLNSAcAO5z8KzQyOR1Dsmj06PBgT1AxJrhR5D13u5hsS3xxupw7MlcMPuR53AwABuqAANZzrq%2Bo3gehAIAcBArgcs4KF4tCOEYr5uh6n6nJ834/khsKQtCNpkYiyKoN6BK%2BsSuKokIeDAMwtAKBSRE/l4GTYa8tBHP44r%2BtOzq4R%2Bc5XtcoLMaxYiMfi2AgCAb5OtgIJJsRqbNh4rbtr0XZKsKBzYHefY/OuCZcY2aYigcrKGEUnaKj2czmcmWnagcAAS3TusQBxUF4DD1AIgUkEhKFsEsAUUReNzeUwbwEZZ/KDv%2B9yBcFoUMEhxCOWkLQPMhc5oHp%2BUGUFIUGTc/EGvByEbGG4TgRB4TAHcBD7qlXliLQqDwdhQUtCuAUpJG2wkjELoHFGo0HAgLGjQAtCQWABVVOW4j1cV2rtTr2raB37dCSIomidFEjitGEoyN30SS/EAGqYDi3ScR5WkVmGkpPrQPWJj1G6HAA6nOBD5QwChUPEkWlQIbYVZ2m01S8SX/TeRCXujL1vRjGiEZ9nn8jx7VIbhgnCc9r12NCdWBv4mmedy4oaZy1kpidzqkY65E83t/MHWdNEXbdDH3VdCk%2BpLeLfMAs7/IwBAcYGHNaqT2GJXQlMSpgf3QnLCu5srN3KapbNq9p6YOVDmRhS5xmmROpYcyzFtE1bdlVtmBDG4ZhZO%2B5/a2WKulYV4Hb2wWxm9i7HtpX%2Bi0PCjnZoAC6SvXD87lZHuUp2FtXo2OZklUOhuYIrghSylHODpEUbgwg8IHJgoGMJFGzAIhNzl5XJtojemWgc0eAjsg%2B6ELNDC0DNfUDUaBy8cA9CPMQwA%2BErhM/ulSeGgccSiDx0GnL3xvV7c8G0AJcQHEfE5Yy1kHHxoDIMXgLJshyoKmyAEZRqgMZLg3FIMHQ4B5FrIEQk3B4AgZ5TznCkZono/gBRgtOGu8cSIOgFtg464lPQSzuqiU%2BSsVbqQ5hrDqgCJwgmEq/HE79WTsmhN7QgZtBakiLgSdhuDwyRmjLGA28sK5nxuu7UB9ld751ymnRcxUUJlURrnLK1VOyF2SrcccWce7CL7ufLeNkdQn10WfeqdBr5zjvkhVAIFWrP3oUyJhX83A/z/kQIQ6MDGc0FnzXBvijqnWooQ8WosHoKRIVXD63El5FnRjrBxjDP4sMzD7HhR1OFvG4SpDhbjUAeMyW4CJ/dFLu23jpWQ4QI4GQdmKQOcctRu0ZuzImXNDqUTBPgtgwTrrEJMaQqJApKGynlLQvh/9qFCKNqQsRTSiIh11tKSSsZ/aOzMnHMs8zJSLNidrGpRY3L1N/JIzK0i96lwyNmAwsUUI3FyRMm8WBFkTiYDEVAbcvFeQAJJhibneeg8jSrEjnOA1ck5YK3EysaNGGiPmtLhT4qi51FJhO6Q8KcAzgwQ1DGM9xRciKA1ruU6svslYrJVAcjUHNvoZmJf2AlmCNzlJztU6O5KBjuWJvCvxiKRbIplkxFibEyE9SGfxeJAY3BSWhLJIVP99rhiYMANSpTPLzN0koll3ZVnO0pd8Hq8ybZOSjlqtlapDlaS5QE7m3K2m8x5aih1oTJYZNoLjWmqsGUCmpb9PFnr%2BT0uJoMmJqkdbUzxnTLh6lZl%2BqOFyVm0adoIttTgq1yahZBKdUQvlWbpZZqKcKy2JMYlawEqMn1BT81ytwiqrSBrIZGtynsupuqfyNKZgOIlPs/ZNrWbq4OTLw7KL2bHFtjZLXtNUhJR17x80YvVjE6h8TGSJOYaCVhBA0mQhdeiTdF47mCNBJW0W4iObjrtWmwJSLc0hOzTe2dHrolk3yaWoS9Jl0f1XW4ddu6/jbqyfK3Jz7JkiOmce6NZT0xh0qUO1lJle1ljbc0rUZ6U3tOFtO69PSZ19MiQ%2BoNT64mjMA1wwpOHikUnA57MUWyFg7IEj2nVnI40nu%2BCHRU3ZKS2WZNgIQzICycfY%2BxvtFkzD%2BHCFiLwWBBJuGRHQQgLoPqUlaeh49PxqVCAQMiAg9AWPzIAPL%2BVzsmYdFKlNJuFgcJ6I8Xk6Y9dSgz8QjNMYsEcIiKH01Xsun6IQmAACOXhGDbDndSu5vqGn1jVkMkNoyfP%2BcCwdKzbIbPKso/65jCa3NJuUxm29WH73kKJqKwjr7QsVrI1LBmSZEM/H04Z3oxnYPNuabVxzvQXMmfZXHbLWMTQYUcICPA8QPr2bq1kKrEWWlZc6cqoiIX%2BGoDNLQGh9Z0tVcyza7rvLMMPFiwFkKmB9wqfeJ84LWK6S5MWxaGSfm9tBdBJ8mZBXwvtuQ%2BZnLAApOd%2BHsLKEVdBV9u34vQl65hdktBBvECFA91E%2B53szJe9VvV63U2ToIb0qZuGnvfY6pdnWF3zTAb0fDpj8akwtaRgIdrjX4MWRq82BzFPshkv2Z13Vm3LPWZiLZgrI3WtZDcM5ss7nL1ba8wxIsN2gd4cxTSOk5b/r4om8RKLFMYuS/29CRLo8ucpYR6tpD1ostvc82LPL5W51Fe1mWvWJGj2KTNtWhN%2Bu6fpgZ7nNwzOmu09Y82bcu4wzYFUKwQEc4Otmt1UMoQXgUiLnQGcV6fWdYaa07ZtwXANBCiCAcMAHAhQ54o2t74QyTQ29OaMhJH7nFu/q9CMwO6QD0wK8pCZoJq9jehOn%2Bvl2PrKSA630bAgBeghz3njg9fG%2BUmUuuljoqE%2BYR1iXpo0jm8keTwQbTuvmmnkcMgAA%2BgxeIBAICzHQMpBQnp98q0lXPrqRZo%2Bx/j%2BhTC6IVi6cTnOfgV8BpkxuNv9%2Bl%2BlAWgDQFAEB54FoBos5UAB8oZV54Z04lBT9KQ/898D8Whj8CBT8QBz82BL9oQyw29B9oQR988sl6YBciICCGArBQRO8slu9QR8DoC9VQQ69SCSN1w18N8EN/1q18UslfslVuDsAQEiIo8Y8M448b9OQCRX9o15k/dZgTIg8IRQ9qdGNvd5kfMyoJxA9g8V4w8Sw2cjcNtjdRdTcKtzCXVvg15hszswxPkwIn5%2BJ5dBciIVd3RQ10ZrDgBpVNN19udxFnckdfhjCUdTCMMxc8s14C0i8YkHC7ExVRl4inD0YXDD1oiq13QZ8F0b9d8uAF9S9spehlIS1oRkioIJ8MsqQmgd8ADD90DMDsDMBcDQRH8%2Bs8j9wxCH8pCZD3ZNC6gBAdDlCQ9Pde0OA1haBOAABWXgPwDgLQUgVATgAXSwawReDYLYaCUTHgUgDdeY8YtYCCEAKYyQd4DQSQLgLkfwDQKYjQMwY4Y4MwAADieP0E4EkF4BYAkA0GSDmIWKWI4F4AUBAGSD2K0DWDgFgBgEQBACahSGRHIEoFkToHiEiE9E4FUCeOOGWmOEkAOGAGQGQAOCkHeDMF4CXEIBIDwFPy4BkEEBEDEHYCkDpPkCUDUE0B0D0APHyhSE4B4AmOmNmI5MWM4D02RHhLDFQCoAOExOxNxPxMJOJNOLMAOAgCrBSBRNQW2JWF4DBPGNIAgCQGRPoDIAoAgGNNGGACkCCBoEwniGBIgBiGFJiHCGaBdD5N4BdOYGIBdD0xiG0DqD2J2LTmNj02nndP2NICwBiC8GAD1CvmBO4F4CwBYEMGXh2AWPwFnHqDbkTIWMwFUDqGRB2B2PCD%2BEmMjPBxiHyh9I8CwGFIhjwC%2BKTNIDbmIFeSUElFTKMHByMA5LWCoAMGAAUCekGwPAczmJ2P4HpNEHEGZOnNZJUHUEjN0FpIMD7NMFWMsH0DwBiGBMgDWCgN6ETOWhP1oU3KsEsDMH%2BLbLZCwH3IgDWFqByhcDvCmD8FpNCAWHKEqD0EKDtmyE8HaD/PSAAqGB/OWC6B6AaDmHfL0GfN6GLHApGCqFsFgqAryFpNPBaGQpigkCfI2O2HwreI4BmNID%2BN4ABJlKxJxLxIJKJJJJVIgFwEpK1P8C4B1N2P7LWBXEuFGEfNICOMkH8HeAAE5/AuQkhJAzBJBTgbjjhRKSKPjSAvj2L3hjguBjgnjRKnjNKTiuApjxLjhyLhSASgSQSuL9iIToTDTYTxSESzSLTiA0S2BOBmgWBQIuRlongiRsIuBRL3guAzjyT8AiA7y9AFyGS5zpAFzFAlzhTdAghuSmBeSkyBTSKhTIyASxSCAJTZppT3LPLvL6I/KAqgrbg1SFxNSjhRMzBOK9SISjSqqTTETzTmrRhCqvLfKrTRL08%2BA6AUEHSnTIyvS3SPTSBRqfS/SAyHBxqQylYwyZ5hTozYz4z2JxqUy0zxBIyszAy8BczhSCyiy/hxqyzuhhSqyayXQ6yMzdS2Rmydi2yOzMAuytr2p%2By%2BAhyRyxyJzxrIrZymSYrZA4r2SVyQAgh1zjBrBrAdy9z4BDyUhjzOBTyMDzzoarybz4g7zXp4aoK9rnAIBXA4LPy7xcLfzaT/zehibUhQLegybIKEKYKBhqbGaBAkLvyUL4L0LcgPy0KBh6aqgCLNgiKOKSKyKKKRSOBV4PKvKfLIbiSyqzjVSWKwqar2L6ruLSBeL1pKB0rlLVKArziuRDKuQrjpLZKLiTKsrOBzLQSPrISYS4SHKkT2rnL0SOB3L5SWAFBQIiTQJ/L3hIRZgQrWLqSIrZAorAaWSQblyFjdB/BSBkrUr%2BSxbMr/jRT7LJSCriAWAvafa/aA6g6wxKqARqrzB/B/ANarKDSmrS6WrHLXaQBfaY9d9/bRLd8i798c7cT%2Bq7TdxKBhqFjJqIydjh7prAy5qUkFrwzlrMAYy4y%2BpEydjNqezbqoydw9qDrIyjrkBizTrBBzrKzdyrqbqGz7rxqnqM5Xqez3rq7BzFVvrMBxz3w/qI6AbEho62TY7OSE7IaUB0abAqyHyEaka9gT9/6tyLBrzKLbzqScaDy8aXzCa3yMLeavyyhOaKbab%2BdUGQKG0Bb4Luh8a%2BhubgKsKiGcp2aMG8KsLSHMK%2BacKOaaGhbNjiKKzxbTLOBpa87faDg27A7HRFDmLQqIpy6OLdTNbtb%2BK9bPjwaAqK6pjbiLifiK6uQtKrb07ATbALKGrDiQBJApixKpinj7jRLJBRKriJKuBf7OB/A07KKbbLLwT0qySNGHGtHdHWz7Ssh9GgA%3D%3D)

## Links

- [source code](../../../../conceptrodon/raillivore/classic_trip.hpp)
- [unit test](../../../../tests/unit/metafunctions/raillivore/classic_trip.test.hpp)
