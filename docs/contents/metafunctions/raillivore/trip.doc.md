<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Raillivore::Trip`

## Description

`Raillivore::Trip` accepts an operation.
Its first layer accepts another operation.
Then, it returns two commitment functions and twelve continuation functions.

- **Commitment**
  - **Conjuration:** When invoked, the function instantiates the first operation with the arguments and then the second operation with the corresponding member of the result.
  - **Transition:** When invoked by a vessel, this function transports the conjuration function to the vessel.

- **Continuation**

  When invoked by another operation, the function returns a `Trip` that is instantiated by the conjuration function and whose first layer is instantiated by the new operation.

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
       // This is because `Agreements...` will be used to invoke `Trip<...>::ProtoRoad`,
       // which has only one parameter `Car`.
       template<template<typename...> class...Agreements>
       using Road = Trip<Commit::template Rail>::template ProtoRoad<Agreements...>;

       // This function composes the conjuration function `Rail` and the `Agreements...`.
       // `Agreements` will be used to invoke `Trip<...>::ProtoSail.
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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMxmpK4AMngMmAByPgBGmMQSkhqkAA6oCoRODB7evgFBaRmOAmER0SxxCVLJdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Yk1TS1teZ0KE4PhwxWj1QCUtqhexMjsHAD0uwDUJgBsGgBKTPioJxoHeAoHTEenF3Q3AHQmGgCCBJgsKQMfxM/jcfwBQMwILB/0BTGBoKYXiI71RIOwB2QBgUClRn38GKxTBxBwuV3RX2%2Bs2IXgcBwAKsQ8ClKSYAOxWH4HbkHXYAKgFfIOABFMDQIqTUJcDoK%2Bfshf0WjLdpSebzDjc3M0bncHk8bgBZTzoD6qnnguEImEQ%2BFQ0EEACeKUYrEwePRmOxDy1xApXJ51NpBAOymIqCIZylJv93PZnO%2Bap5/MFBw8LBYhDYghlgvlB0VwblZsTgbpaYzBGLarjVcT3OTAtTAm0m3hWRzArzBeVtbr%2B2e50uTh1hnQA59I%2BImExqAB6UwY4Q8TdvcT/YAYnhiLNSAcAO7T8KzQyOW0DsnD06PBhj1AxJrhR4Dx3O5hsU0xuv1w70pcMXcHncDAAG6oAA1tOmralee6EAgBwEEuBxTgoXi0I4RjPk6Lrvqcnyfl%2BFqQtCRG2tCSIomiBKesSuKokIeDAMwtAKH6CZfjyXgZJhry0Ec/jCqm2qghe1yggxTFiHR%2BLYBS/jxhxSayk2DAtsQbYCB2cr8gc2A3j2PyrtWBF9spjKGEU7ayl2cwGexin9gAEt0zrEAcVBeAw9SafwbmIdObBLH5sKQgOjlMG8eFGUmP4IPc7med5DAIepDAKGkLQPP5M6qa2vQJV5%2BU3LxOqwYhGzBuEoFgeEwB3AQu7Rd%2Bjy0LQqCwZhHktEubkpGG2wkjEDoHOGPUHHFwA9QAtCQWBuR5hVZLiTUISFZH2mtVqkVtm12lqyKoO61FEjiR2El6Z00SSvEAGqYDi3RsYp3KlsGooPrQK01iZDmHAA6tOBCpQoVDxAhSFoLl6n5QtSXnhFn1XkQ8N0HdD2Ixo%2BH2c93JcbVCHYfxgm3fddjQiVBIggpz3ssKVOsj9arbXtzMkbtbM2laFGHVR520ZdJ3SR6gt4t8wBTv8jAEKxlOM5x3F1eFdBEyKmAfdCYsS1m0tnSAIAvna1MOWZwOZJp1k6XpY5Fj9tP0z9DZCuWmZS1peZW3Zq6OypGFeBpyUWwqtk29jMUMnFDyw/laBzkoWUQ82eXtlH7bFQjI76dlNya5gkuCELUUO4ckThoDCDwgcmDAYw4MbJNA453nOtole8XAc0eBDsgu6ECNDC0MNYhtXueoHAr9CPMQwA%2BFLWNfv2v7xfFcSiFxkGnI32sF7csGtQccQHGvY7I1V4HrxojLMtCusgKG4aoJGlw3KQXuHHucXIPB5cPAIA999OKRmiuj%2BG5KCvpC6h25KzDanMWbYTfG6XmV1pKbyljLWSP08Y8SjCrS%2BLJQTOwIHrZmpJ04EmIbtEMYYIxRg1uLXOW8zr22%2BK/cO8UU6aRjoUe64NpyQzUv7AqcM06RVuKOXhDd6FN23nPPsGoN5SK3qVOgfED5HwQqgIC1Vz54OvrzPWd8iBCARrIxM0DrSWhZuzREB0BYXSQSLVEqD85PTrFguqxjlYgkEroghs4KwUNgaQt45D9aUMMagTxn1QTOObjJZh89lIeEEOEP2%2BVA66X0iHasbI6byQZtjcxRT4GujsfzJxii0GuNxgrSU0pvFUPvo/E0MTKn5yYfkz83tRTimnM0t2lsskqkMl05SPSFj5gRgMoOAw7JqgXhHIR%2BV4rZQyBmAwfkkI3Aic0nUWBeljiYDEVA1dTHqgOAASWDOXG89B458OJNOd%2By5xzQVuPFfULx04QKZtYixxEYGWPIrYhx9iZLIKEr6WW2NXqNKMenT831IG8iSf4l22YMndmyXWWFhDVxIpxt7ZJAj0m5h0li4ZyLfmwI5kCmxlFwWOPeBJZi6CVruOCXxBpE4RJDjEm4FlUkb4kOUEwYAdpZKdKpUpFMxKk7mzJUKD2IcVre3MmlM2AdFX5mDpSnGRS/kGppfSnmjKwXC3NcdL0nK0Zk2hTjWF70EXStjByFa8t8YGxViTdG5MyGSqNhxO2UqVpGrpf89aEauYgrNeU2Np1QVxtiWyuWNT8ZKy5QJVW6tWlazQcK7CCTnpqtNqSzsgzrZ6rrMGwNMrGyEO1tMzJlaCmJNlbIVJgjMW6tXGGgFYISlsDKQm94ybqlqg5f0hpvi3CEMCZYzl6J52hR2bQ3NDD8282Yb2w1u7jX7QZRauNR6R1jvtW42pUTcFMnwbOtFRCwlBIptgZdZ4IlRLoXm9pW6pVtvrR2hgaSrLauVVW11eT4xVj7ZG8x3Nh1CytUmtp0tx0cqvQ099ZC3DJo6YG7pYoJlXoyaB1kuTt0/EdrKTslIGz0mwEIekuYaNUao5S1kZh/DhCxF4LA/E3DIjoIQB0bFKSwZjWxWFQgEDIgIPQcj3xvYAHlXL%2BwTN22ZIcxPIxuh3I5cnoWwuU/EVTpGLBHE/NB6Nh7EMkiEJgAAjl4Rg2xx2OrVs6nJtaPWYS9Q0uzjnnN7R00yPTEqi3gfk9S8NWnTUnpQchlN2NJ1TIaU6kJ2GEsFudNusjUqlMqd6GpkDQyCn5eM70Mz6mlSab%2BdzA4Bo0KOEBHgeIEmgZBgOEZ6GWRINuos4awdYXPywoiUaWgY4ay5cg/1/dMX4P5gc05rymBdx1Yua59rdJRvGmhP5pbLnQTrcpue11XnVr7rg6iAAUuO7zdVRXipVntwL0IGvoWZLQFrxA%2BQXN3Fd3DVYa2tvNAN18pSKlfpQydw%2BtSxsTazdt8bn6N3fviSGqbzGUxdf9pV4rLaRkKeUtj3obgm0UtE7Vg6BxgudxiPpjBVJNvBmJ1kNwpmoN7vDZd%2BNDxnvLY2zSOkaXPqIr61Sjlvms184O24GnoW5KBqBwTqL/a5uJtPQl1DtTeIq2F8j6RWXDakYg5jxsLOBCk%2BIyVgn3tNzbmDNgVQrBATTiq4WSlaGvApG4egM491GtPekwQWTe0uAaD5EEA4YAOB8mjwrgpHKDTuY4cladN7oTm4YCw0EZgl0gGfZSPWuzQSZ6sKCMPee4dsT1h%2BkvBXWfQmj7HjgeeC8/D1nikNPxJ3%2B/QirJPTQU9F6w1JmT9P5PHkcMgAA%2BrReIBAICzHQHrBQrpZ8yzcH71C6FdxCC9z7rfjX0QrHkws6c/BWrtXxjcSfeAZ9z5aDqBQCB2oPBf3uCRqB68CD1FOGcscFwQBKRb978HoWhF8CBl8QBV82B19oQqxM82dQQm849QkKY2dPxS9oQK9Qkq9QQEDv8s9oRc80CsMjJR9g85NEVoc88HsoRqDsAX5Pw99vd5xfde9KxDICQT88tlI7dZhdIncIRXc8dPYKNlI7NIYxxHdncJ43c7JLMrELtxMbMEM%2BZroEZvgp42tBdgwLkQIz5eI9dDIxcJ1alJdiZNDtDxIg8Q948TCTcCdFDaV%2B1uc4t4NRYp5EsOV9DtEdcGlfDDCEY9cYkvDDd5Me9t8CBp8uB%2B9k9Epeg9YM1oRAiIIC8u9Gc2xQClBwCl8V819iRyYOCYjd9982DD90Jj9mFvZJCBBpChCXcm1QMOA1haBOAABWXgPwDgLQUgVATgNnSwawMeDYLYSCDjHgUgIhHolotYMCEAdoyQd4DQSQLgNkfwDQdojQMwY4Y4MwAADn2P0E4EkF4BYAkA0GSG6N6P6I4F4AUBAGSGmK0DWDgFgBgEQBAAqhSGRHIEoC4ToHiEiFdE4FUH2OOCmmOEkAOGAGQGQAOCkHeDMF4AXEIBIDwGXy4BkEEBEDEHYCkGxPkCUDUE0B0D0D3HUhSE4B4FaI6K6NJL6M4EU2RB%2BODFQCoAODBIhKhJhLhIRKWLMAOAgDTBSEBNAQmJWF4GeJaNIAgCQABPoDIAoAgAVNGGACkCCBoHQniAeIgBiAZJiHCGaAdGpN4ENOYGIAdEUxiG0DqGmMmJjm1kU37hNJmNICwBiC8GAC1FageO4F4CwBYEMGAHEDdPwCnHqGrj9N6MwFUDqGRB2EmPCD%2BDaLdM%2BxiHUktI8CwAZKBjwHOP9NIGrmIGOSUFFCDKME%2ByMFJLWCoAMGAAUBuhaz3CM26MmP4BxNEHEAJI7KJJUHUDdN0CxIMGrNMCGMsH0DwBiAeMgDWC/16D9KmiX28THKsEsDMBuOLKZCwBnIgDWFqCShcBvCmD8CxNCAWHKEqD0EKE1RPOvPSE1SGEvOWC6B6AaDmDvKxIPN6ALCfJGCqFsA/M8HaD0GPBaD/KCgkH3NGO2CguOI4E6NIGuN4FuM5PBMhOhNhPhMRMFIgFwDRPFP8C4ElKmJrLWCXEuFGD3NIHmMkH8HeAAE5/A2QkhJAzBJBThNjjgGL4LTjSBziiL3hjguBjh9iGL9iRLFiuB2imLjgkKGTbj7jHjSKZjXiPi5SviWTfjlTVTiBgS2BOBmgWBgI2QpongiRMIuAGL3guBliUT8AiBty9BezcTuzpBezFB%2ByGTdAggKSmAqT/TaSEL6S3TbjmSCBWSRoOSjKTKzKaJLLrLbLbhhTZxRTFSjgOMzASLpTXj5TUqxS/iVT8rFSQAYrTKLL1SGKw8%2BA6AQFdT9S3TzTjTTTSAmrLTrTbSHAWrHSpZnSB4GSPSvSfSWIWrAzgzQzejwy7S8AoyGTYz4y/gWrkzugGT0zMyHRsydhei8yCzJjizSzMByzxraoay%2BB6zGzmzWyWqXKuz8T3LZBPKSTByQAggRzjBrBrBJzpz4A5yUgFzOAlzICVyPr1zNz4htz7ofrXzprnAIBXBPzggbwIKrysSbySdgK8hUaHzehkaXzvz3yBgEb8aBBfyLz/zQKgLchTzAKBhcaqhoLNhYLiL4LELkLGSOBJ5jLTLzK3qETErlihT8LHKMqiLsqyLSAKK5pKAgq%2BKBLrKVi2QZK2R1i2KOLVj5LQrOAlKnjTq3jPjvjtL/jiqgSQSOAjKeSWAFBgJ4TgIrL3hIRZh7KCKMTnLZBXK7rCTHqBzejdB/BSA/KAqaSWaQqbimStK2ToriAWALaraba7aHbgwUqAQxSRb/AxbVLZS8rk7FTCrdKQBrbvdp9baGLp8E7Z8o6oSartTtxKAGrei2rXTJiG6Oq7Tur/FeqXSBrMBPTvSh4/TJixrKytqAytxprZq3T5rkAEylrBAVq0ypz1rNrcymRdreB9r5wjrKyTqM66yxULrMAWzXxrq3bbrEhPbiTvayS/a3qUAQabB0zdzfr/q9g8jVzrANyUKtyMTIbZzobDy4bjyMbqbzyyhyasbLILcgH7yIGGA6bQLugYa%2BhKaQKvyEGkpSbQHIKvzkHMaabwKyasGGaxi4LUzWaFLOBOaY7raDhi77bbQBC8KHKSARbiKpTxbJaqKZaziXrrL/B/B2itjVjLi%2BG2RRKNbQ67jbBlKcq5iQBJB2jGL2j9idiGLJAGL1jmKuBr7OB/AQ6UKtaVKXigrkTxH9HJGZGiydSsg5GgA)

## Links

- [source code](../../../../conceptrodon/raillivore/trip.hpp)
- [unit test](../../../../tests/unit/metafunctions/raillivore/trip.test.hpp)
