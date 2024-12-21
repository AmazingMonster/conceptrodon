<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Raillivore::Trek`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#raillivore-trek">To Index</a></p>

## Description

`Raillivore::Trek` accepts an operation.
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
   >
   >
       &vellip;
   >
   ></code></pre>

## Type Signature

This function has multiple signatures.

```Haskell
-- End in Conjuration
Trek ::   template<template<auto...> class...> class... 
       -> template<typename...> class...
       -> ...
       -> template<template<auto...> class...>
       
Trek ::   template<template<auto...> class...> class... 
       -> template<auto...> class...
       -> ...
       -> template<template<auto...> class...>
       
Trek ::   template<template<auto...> class...> class... 
       -> template<template<typename...> class...> class...
       -> ...
       -> template<template<auto...> class...>
       
Trek ::   template<template<auto...> class...> class... 
       -> template<template<auto...> class...> class...
       -> ...
       -> template<template<auto...> class...>
       
Trek ::   template<template<auto...> class...> class... 
       -> template<template<template<typename...> class...> class...> class...
       -> ...
       -> template<template<auto...> class...>
       
Trek ::   template<template<auto...> class...> class... 
       -> template<template<template<auto...> class...> class...> class...
       -> ...
       -> template<template<auto...> class...>
       
Trek ::   template<template<auto...> class...> class... 
       -> template<template<template<template<typename...> class...> class...> class...> class...
       -> ...
       -> template<template<auto...> class...>
       
Trek ::   template<template<auto...> class...> class... 
       -> template<template<template<template<auto...> class...> class...> class...> class...
       -> ...
       -> template<template<auto...> class...>
       
Trek ::   template<template<auto...> class...> class... 
       -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<auto...> class...>
       
Trek ::   template<template<auto...> class...> class... 
       -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<auto...> class...>
       
Trek ::   template<template<auto...> class...> class... 
       -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<auto...> class...>
       
Trek ::   template<template<auto...> class...> class... 
       -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<auto...> class...>

-- End in Transition
Trek ::   template<template<auto...> class...> class... 
       -> template<typename...> class...
       -> ...
       -> template<template<template<template<auto...> class...> class...> class...>
       
Trek ::   template<template<auto...> class...> class... 
       -> template<auto...> class...
       -> ...
       -> template<template<template<template<auto...> class...> class...> class...>
       
Trek ::   template<template<auto...> class...> class... 
       -> template<template<typename...> class...> class...
       -> ...
       -> template<template<template<template<auto...> class...> class...> class...>
       
Trek ::   template<template<auto...> class...> class... 
       -> template<template<auto...> class...> class...
       -> ...
       -> template<template<template<template<auto...> class...> class...> class...>
       
Trek ::   template<template<auto...> class...> class... 
       -> template<template<template<typename...> class...> class...> class...
       -> ...
       -> template<template<template<template<auto...> class...> class...> class...>
       
Trek ::   template<template<auto...> class...> class... 
       -> template<template<template<auto...> class...> class...> class...
       -> ...
       -> template<template<template<template<auto...> class...> class...> class...>
       
Trek ::   template<template<auto...> class...> class... 
       -> template<template<template<template<typename...> class...> class...> class...> class...
       -> ...
       -> template<template<template<template<auto...> class...> class...> class...>
       
Trek ::   template<template<auto...> class...> class... 
       -> template<template<template<template<auto...> class...> class...> class...> class...
       -> ...
       -> template<template<template<template<auto...> class...> class...> class...>
       
Trek ::   template<template<auto...> class...> class... 
       -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<template<template<auto...> class...> class...> class...>
       
Trek ::   template<template<auto...> class...> class... 
       -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<template<template<auto...> class...> class...> class...>
       
Trek ::   template<template<auto...> class...> class... 
       -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<template<template<auto...> class...> class...> class...>
       
Trek ::   template<template<auto...> class...> class... 
       -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<template<template<auto...> class...> class...> class...>
```

## Structure

```C++
template<template<template<auto...> class...> class>
struct Trek
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

template<auto...>
struct Shuttle_1;

template<typename...>
struct Capsule;

template<template<auto...> class...>
struct Carrier;

/**** OperationA ****//* Start */
template<auto Variable>
struct OperationA
{ 
    template<template<auto...> class...Sequences>
    struct Detail
    {
        using type = Capsule<Sequences<Variable>...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = Detail<Agreements...>::type;
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
using SupposedResult = Capsule<Shuttle<10*2, '*'>, Shuttle_1<10*2, '*'>>;

using Metafunction = Trek<OperationA<2>::Rail>
::Road<OperationB<10>::Mold>
::Sail<OperationC<'*'>::Rail>
::Commit;

using Result = Metafunction::Rail<Shuttle, Shuttle_1>;

static_assert(std::same_as<Result, SupposedResult>);

// The following `static_assert` shows how the operations are composed:
static_assert(std::same_as<
    Send
    <
        Send<OperationA<2>::Rail<Shuttle, Shuttle_1>>
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
template<template<template<auto...> class...> class RailArg>
struct InvokeRailDetail
{
    using type = RailArg<Shuttle, Shuttle_1>;
};

template<template<template<auto...> class...> class...Args>
using InvokeRail = InvokeRailDetail<Args...>::type;

using Result_1 = Metafunction::Hail<InvokeRail>;

static_assert(std::same_as<Result_1, SupposedResult>);
/**** Second Example ****//* End */
```

## Implementation

We will compose functions using `Omennivore::Send`.
For example, we can compose a `Rail` and a `Road` in the following way:

```C++
template<template<auto...> class...Args>
using Metafunction = Send<Rail<Args...>>::template Flow<Road>;
```

Note that in order to succeed, `Rail<Args...>` must be a packed `Road`, meaning it is of the form `Vessel<Items...>` where `Items...` all have signature `template<typename...>`. This requirement is not checked by `Trek`.

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

- `Radio` is a `Rail` and
- `Car` is a `Mold` or `Rail`.

Here is the entire implementation.

```C++
// `Radio` is a `Rail`.
template<template<template<auto...> class...> class Radio>
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
           template<template<auto...> class...Signals>
           using Rail = Send<Radio<Signals...>>::template Road<Car>;
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
       // This is because `Agreements...` will be used to invoke `Trek<*>::ProtoRoad`,
       // which has only one parameter `Car`.
       template<template<typename...> class...Agreements>
       using Road = Trek<Commit::template Rail>::template ProtoRoad<Agreements...>;

       // This function composes the conjuration function `Rail` and the `Agreements...`.
       // `Agreements` will be used to invoke `Trek<*>::ProtoSail.
       template<template<template<auto...> class...> class...Agreements>
       using Sail = Trek<Commit::template Rail>::template ProtoSail<Agreements...>;
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
           using Rail = Send<Radio<Signals...>>::template Sail<Car>;
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
       using Road = Trek<Commit::template Rail>::template ProtoRoad<Agreements...>;

       template<template<template<auto...> class...> class...Agreements>
       using Sail = Trek<Commit::template Rail>::template ProtoSail<Agreements...>;
       /**** Continuation ****//* End */
    };

    template<template<template<auto...> class...> class...Agreements>
    using Sail = ProtoSail<Agreements...>;
    /**** Define Sail ****//* End */
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMxmpK4AMngMmAByPgBGmMQSAOwAbKQADqgKhE4MHt6%2BAUEZWY4CYRHRLHEJXCm2mPalDEIETMQEeT5%2BgfWNOS1tBOVRsfFJqQqt7Z0FPZODw5XV4wCUtqhexMjsHAD0uwDUQngsabR4NJjoBybJGkKutxoHVF4MDjkAdCYaAIIEmFOBgBJn8bgIAE80oxWJgDsomMgANZXABqmAUdlB2B%2Bv0mxC8DiOrhuiSsiQAIqCrH9cQCgUwQWD6WdGZhQeCoTC2J9ediDsgDJiDh5BExwvFSAdIdDmDzedh6GxBApsbj8YSCMSGOgOaLWhLiBzFYDGAQFLzvv4cdbcSYybiDk7pYDWUzwa7gezmVy5ZhLfzBUxhQB5aHERk5NV/Z0HDVEimYA20R3O/YHACSDAAbqgUTc7mH4pGBE8DgB3QgIaUIOFPE3K80Bu7fGPO%2B0WA5eLJGaVcm7%2BCkHIsRprGpVmi1823%2BTv2qmzu1tp0sr0c1ds9e%2B2EB60CoVTz6/YDETCmlXR36x7vhYAHABKqCY11BQ8TyY5x9P56b0%2BwIBAGVvRpX552pJd/k9TdmSg90N3dJgvCIXdsH3YND0DA8jiIZFiFQVAWCleDvTcRDkL/NDMUtB4AEcvEYbZVVtP54y1B4dQ5FpUFw/CWE4zA6IYjEUMvDtUxXWCSOI9dJI5MjUBQyiML3INQ3DEsGEvWNWIOd9xRTZcDnTLNc3zJ4Rw0stKwIasbLrO5aPo95hL5FtxNJTsb17ICByHCyxzBRyhOUm050pcDaUM6SYIZODZLBeTFNUkKlMtL8z0bJicUMry7yEfTfN0pN9M/E8MsnFCAKAiLQPCxdItAv50yee9nycMs8AUA4mALDRWroJ5W0g2KpPij0RrkpCFIo5Kkqw1r8FQS8dIAFVPJE7QdQzdgAKj2naipoCIHyfa59p2/YDoGdoDgu9zmruUijTuA5Ou63qAFlPF1NyorG6LOVlHcZqwp6tOdHTlDwohH2fdyxMMtNzpFAiWEIRtbv2y7sMGW7dnciGCAJIkPBYNGCAJp0EavWNaaM5HRW0TYNMxvbseurU7sRumHr6tqlpewwX0etoyzaOE0FOTIrgOWtTyGunaYBgHEpB9DqLwYBmFoLLKdp3KHwK19tV1MEFvawLNe1kLsSqySTrhsEwZnEDFdjXb9pRhgmdHHJWYu3aDmwHU8Ygt32252mPb2g41sMEo/fO9mpk5/HI/dw4AAkGnDF43g%2BAQXhIGs4TYKp4hdEbeszkrfpp8P0xWhA3ted4mmlCMGAUDJ2i6uyBQEH2WdbguGF6/qUxe6yEA2LVwlM29XoIKU9Yz7raFoVBK17V52jlg40jwxiupiCEDlQOziFlzW5YAWhILAr5HpoLVX51lf%2Bz%2BJoSqa5vVtWqIAK6hPdEmIGjg3DjpPSA107ti2vXcOaZDgAHU4RE3jlQCu/c0De2Zu3Z%2BfsWq12eEQce%2BlQFYjrog/WPY7w%2BWNiAjEWIzYlRdm/KmdUQLsMrm6Ua39xq8Jkvw1WVpUKzSAX/QBR4yo/l1rAp0Bsa50EKtAlMYJ0qyMqoBLkNVqHRwOnHLu2RC5J0DsHM6acEFwIXK7HmDNUbozNP7bG5jQ4NUVvor2jgGBeBZqYq6Kc3FWKdI3ZuXUCGF0lsUDEJcB64N9oXCJY8iEDUFiHfuTwNGZWbBoBWPNDiRAvmghAjIDiYGzIwGsGxgDVkyTI7JrlnhvWzG0PAbVkBSkIOfBgtAz5iE3uWLqPVaH0G6sQYAPgzR5KjocJub03pxFEN2eyfx6kVUaRWOgtADhxC7Eoa4pD555hWWtTAG0wRaKhhfVAsMfoaFIHrdM5Zm7IGrCUrqAhendLhGkNosIARXyeGDKhdMP78KAn6SRh4smTggdeWhDsXyDljutPUDiCB2yrhPW2gF7ZXJhqdUq34GmiJqo82ZYS85tz9lE6WfdaxxKHvg/O7cUmT2eELWJdTiXrO%2BCCmZvUYUXinlsnZcJlkHNQK9HMxzeqnPOW4S50NUD5ToNM2MYLBExS1aRX%2BEj9XSJ5ReZiwS9mL1Vds428q0Vk0IJi3hhsBrWntV6eEyqLVEvKiqES9VTWeP1OEXx7d/FBxDlzBBYFfXuU1WuH0QN5SiNSryIV5o4UG1uYVfFNzCXqLWd6v8uikae0TEdOEGaQ2uPDfdZGJaJRHAKiGjmQS15zPCSyv2b1%2B5ZDRgYK%2BGS7hZtuWWLApbrhMBiKgCp6rjJahKTqeg9KJbBjhM8%2BIKzgVNKGWQ1JuTo1fx1SrPVibxHHtBqLE12kiaajddcj1hlqYePsbaggGNG2BPDYrHSpNyZ6wfYg/1g88GJyxoHJtH7EExugrq8ip7/6fGOFrMQcjTXwsXhPQq7FTZuHNktS2iGdY%2Bv/LiquHqnbntCtwgD8S/EgYOpWyxlHkaGITiY2jOMbrgfDpBuK4KxoiMwnBgTUihPAPIUw8BF7EFQOKjAlDcDbHULNd5fsDCxNgLUdh1hFH5GkhsWHCD%2B7Y0CKM4emDImoUWeTXm1Nknw6KKNsi1RnrNF/iqjo31eimOdxY2PCtYbLGK0jQp92T7yavrY/R/TUd7GCEDTRtmoH30BdBYZqDELgawakSm5Dit02nUKtap26KXVskdWoojxEb0Esdm4bLPquGR243wnV/GVIHks4ar1NnsqmoNhagrqKivPpKwCMrOLKtZtI7V6zNsPN2M9gGnx8WA50f8/DThUWeEmdSwhI95mDXZbTQi/rxtJusOm0a38pK5shJrZgUt9blF%2BYsZtPTDV9HnTZriaOK1sBCBWljb7n3PsMdpGYfw4RBReCwAONwSE6CEAhKJP4pnpqkpYleokQgEBIQIPQMlKO%2BN7ZNTpbHuP6AAH0uAE%2BGge7cCblqY61KRNICgvD46jYT3jwjidiPawWjHxNmdtGIHgeINPPH%2BRyFeN9uNw2o4OKiVp46Oc9Z0lLgQjVapzj%2BtzlrvOk3wYEk5RicLpMfnvfAt2Bt6HIpZ2zjnbggrOSYm4JXouVfemwPV9bb2tcap2yRVrfO4OHds0pu86HjZOdzZdkKbnoRko201ZGGuGAy4i2t97qf1JNE7LLjjliFcfXZ44M4YujQk6Z8OXPOQuFW/fv9en/oBcIPN0bB0yf/eN710Z4PSliSCWclKERGYzfV5j0743QkOQZkI%2Bt4LPf9cwYAFJwudAbBEwA6zIud9sDkJfaBl/OPEHac/eRShXz7y3fu93gub2lGbR3F5fVoEiocT1Rfi7BJPsPFW8VMDb7X61R%2B6S614CD56Z4vbZ6exp5uDOKJZy5F5E6kLu5tIxCq7qjV5wGbTBZNaTRmZtZwZ74Yjj5C5FQW4RoN50w24qZ25MCs7s4kQkGu5oGe7YjAGxhBabb4E/yEEh5ZZP7h7poOZvgyYaZ1aubaKJ5Rpd5gHFhNDwHPZBJA6ewABieAxAkwQcqgrAZwcIBeqcuIfWXgaQ0S6A94GIpehU9uTBnEOOBAeOJEXAGgO0QQBwYAHAO0nh2IUoZOjhlO1OYILhbhUonh3hHAaobCDUBsH0xUSSA2ZyHIaeoEYIZgOK2KJqAEQ6YIaeVgwRGgOKr%2BpsPWAEU2OBYI4RPhzqIAmRpRIA36hANO6aVhR%2BhUcRrQSS2R52/hThfhDhThVOURDWeIrQjgyAFO6E8QBAEAkw6AAECgsIkxrulhDuy8Rwph5hqxpe2IKwEuFKcI/AG8W8i8Tw8w4xyxSg7QZYCgM8gyssW8sSqA4BXcYyEsBE5hIAWBkYExUx7QsxBA8xIAixbAyxHI7kmG8MYIq8kJuRLxqRbg6RNRmRTuAx9A/R5OmAQxM4PWbs2ROabgeRHILhRR30cKcKZR52FRbgVRkRyJWm7kDyhkQgmx0sFhrRFMtI1oexvqniGhWhWo2AuhQIBhUBKhKensDwOC1wQpehoyhhQSvBxmUG/eJ6ImZWvw4yjO5BJkxyE8TmtI1BEefY0IhUE8mpwA9hmJGJARWJQR2mIBNOSpqOHW%2B2R44yyGBsupKIUeyK3pmA%2Bp4hn4HpWi1UnOvwLRaxVO7R8R7azgIASiGm/pdRNO5xeAvxYC/xcxCxSxwYHI2xR%2BVOfhrJ%2ByBZFM3JNUniUpAgMpwp%2BhCBq2FiHAawtAnAAArLwH4BwFoKQKgJwG4NYNYHGBsFsHWODjwKQBit2c2WsEiCAG2ZIJ8BoJILUP4BoG2RoGYMkMkGYAABy7n6CcCSC8AsASAaD3Jdk9l9kcC8AKAgD3JTlaBrBwCwAwCIAgCzxpBITkCUBRJ0DxCRCwicCqC7nJC3zJCSAHDADIDIAHBSCfBmC8BXCEAkB4DzFcAyCCAiBiDsBSCYXyBKBqCaA6B6DlgRhpCcA8AtntmdnEW9mcAhhIRflaioBUAHAgVgUQVQUwVwWLlmAHAQCkxpD/mArjkrC8CPnNmkAQBIB/n0BkAUAQByVjDABSBBA0BH7xB3kQAxB0UxDhBtAQiUW8D6XMDEAQghgxDaCYAODGWkCSyNghg9JGXTmkBYAxBeDACkQbx3ncC8BYAsCGDADiCuX4CngfAVK%2BU9mYCqA2VIQ7ATnhAAitmuXnAxARjmUeBYB0VEwnB2UVLEATpKCJiBVGDnBGDEVrBUAGDAAKCohi7lhFhdkTn8BYWiDiB4WtUEUqDqCuW6AYUGAVWmCWDWD6B4AxB3mQBrDPEvycC3xzGvjDVWCWBmBXkFWi5YCTUQBrB2A2VNAuA6gzB%2BAYWhAShLBjAYXFDGK5CeBdB6BXVNCLCjA1C9B7X9ApxHV6C7WjwcxPXlwvXzDTC3UFAYWA1DBnXPUSA7UjnbBQ2HkcAdmkCXm8DXnsWgXgWQXQWwXwX8UQC4AoWiX%2BBcDiWTmVVrC1jPhjDbWkBzmSD%2BCfAACc/giQkgy5Zgkgdw65yQDN8Nx5pAp5RNnwyQXAyQu5DNu5ItC5XAbZTNqQyN9FN5tg95pN05z5b5MlH5TF35ilylxAgFbAnAbQLA2YiQt8PUQYvYXADNnwXAS5SF%2BARAG1egXV2FHV0gXVigPVdFugQQZFDBxl1FCNtFrl15jFBAzF58bFRtJtZtaElt1tttzwglHxIlNw4OZgJNklz5slKd8lP5SludYw0dptFtqlDNLhfAdAAK2lulrlplhldl9d5lll1ltlfl9lqMZoTlvSdF7lnl3lOsdlAVQVIVPZYVb1kVdFMVcVAIdlSVDQdFaVGVEIWVOwPZuVp57dBVRVmAJVI9t4lVfANVdVDVTVdlLt7VuF7tsgntRFfVIAQQg1xgg5lgY1E18A01aQs1HA81gJi1L9Fgq1KN61aFGIH9r1o8B17gwNx1wQOof1ywl1mQ11n1SDPmCDF1EDTQHMqDWD71CwEN/1X1H1MDxDBDFQkNxN6wmwsNVDKViN8tqNxdsdpdcFCdS5Al%2BNjtadRNmdZNpAFNj8lAgdfNAt1ty5iQMtiQiQ/gkg7NEFGFjDnAt5ytWd0l6tSAn52tv5hdetQFHARtXFLACg2YsF2YVtnwXokw9tBNaFztsgrtV9%2BFt9vVPZug/gpAftFFflgdDDdFodWtLFUdxALARjJjZjFjVjWoydpwqd5g/g/gfDqt0lOdsTedOtujIApjZhFO5jDNFOUTkxITEFldmlWhlAtdPZTdLlE51TLde1dlDlXdzlvdmAHlXl/SvlE5w9ZVa9/lmhE9YDrl09yA8Vc9ggC9qV41y9q9OVoum9E5290se9ZVB9yT1VgBJ9mAjVso59Djl9Eg19ggLj3tAQ%2BgQVKAADb9W1n939uw2ZS11gQDvZIDm14D31%2B1EArguDp1FDRDaDKDpDALj1hDiDeDAgODQL4LzQKcGDANJD%2BQsDYNcLcNCgMNuFvjwdV5nAYyoTkFxjpjBweTljbI2heNDtxc8TxNEl/DgjVNIjJ5D91tCTbZG5K555CTKQB5Sjitd5D5/DtNbZjNbZu5W5DNkgDNMjzNXAHjKV/gWLKNyjKtT5gdiFSN/jSrWdawBVWQzgkgQAA%3D)

## Links

- [source code](../../../../conceptrodon/descend/raillivore/trek.hpp)
- [unit test](../../../../tests/unit/metafunctions/raillivore/trek.test.hpp)
