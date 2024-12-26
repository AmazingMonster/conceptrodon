<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::ClassicTrek`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-classic-trek">To Index</a></p>

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
 :: template<auto...> class...
 -> template<typename...> class...
 -> ...
 -> Commitment

-- Compose with Page
ClassicTrek
 :: template<auto...> class...
 -> template<auto...> class...
 -> ...
 -> Commitment

-- Compose with Road
ClassicTrek
 :: template<auto...> class...
 -> template<template<typename...> class...> class...
 -> ...
 -> Commitment

-- Compose with Rail
ClassicTrek
 :: template<auto...> class...
 -> template<template<auto...> class...> class...
 -> ...
 -> Commitment

-- Compose with Flow
ClassicTrek
 :: template<auto...> class...
 -> template<template<template<typename...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Sail
ClassicTrek
 :: template<auto...> class...
 -> template<template<template<auto...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Snow
ClassicTrek
 :: template<auto...> class...
 -> template<template<template<template<typename...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Hail
ClassicTrek
 :: template<auto...> class...
 -> template<template<template<template<auto...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Cool
ClassicTrek
 :: template<auto...> class...
 -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Calm
ClassicTrek
 :: template<auto...> class...
 -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Grit
ClassicTrek
 :: template<auto...> class...
 -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Will
ClassicTrek
 :: template<auto...> class...
 -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment
```

```Haskell
-- End in Conjuration
ClassicTrek
 :: Commitment
 -> template<auto...>

-- End in Transition
ClassicTrek
 :: Commitment
 -> template<template<template<auto...> class...> class...>
```

## Structure

```C++
template<template<auto...> class>
struct Trek
{
    struct Commit
    {
        template<auto...>
        alias Page = CONJURATION;

        template<template<template<auto...> class...> class>
        alias Sail = TRANSITION;
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
template<template<auto...> class Sequence>
struct Oper_0
{ 
    template<auto...Variable>
    struct ProtoPage
    {
        using type = Capsule<Sequence<Variable>...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

/**** Oper_1 ****/
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
template<auto Variable>
struct Oper_2
{
    template<template<auto...> class...Sequences>
    struct ProtoRail
    {
        using type = Capsule<Sequences<Variable>...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

/**** SupposedResult ****/
using SupposedResult = Capsule<Shuttle<10*2, '*'>, Shuttle<10*3, '*'>>;

/**** Metafunction ****/
using Metafunction = ClassicTrek<Oper_0<Shuttle>::Page>
::Road<Oper_1<10>::Mold>
::Sail<Oper_2<'*'>::Rail>
::Commit;

/**** Result ****/
using Result = Metafunction::Page<2, 3>::type;

/**** Tests ****/
static_assert(std::same_as<Result, SupposedResult>);

// The following `static_assert` shows how the operations are composed:
static_assert(std::same_as<
    Send
    <
        Send<Oper_0<Shuttle>::Page<2, 3>::type>
        ::Road<Oper_1<10>::Mold>::type
    >
    ::Sail<Oper_2<'*'>::Rail>
    ::type
    ,
    SupposedResult
>);
```

- In the second example, we will transport the conjuration function to `InvokeRail`.

```C++
/**** InvokePage ****/
template<template<auto...> class PageArg>
struct InvokePageDetail
{
    using type = PageArg<2, 3>::type;
};

template<template<auto...> class...Args>
using InvokePage = InvokePageDetail<Args...>::type;

/**** Result ****/
using Result_1 = Metafunction::Sail<InvokePage>;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult>);
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
           template<auto...Signals>
           using Page = Send<typename Radio<Signals...>::type>::template Road<Car>;
           
           // Helper function for the member template `Sail`.
           // This function transports the conjuration function `Page` without invoking it, 
           // allowing further process by other higher-order functions.
           template<template<template<auto...> class...> class PageVessel>
           struct Detail
           {
               // We transfer the conjuration function `Page` to `PageVessel`.
               using type = PageVessel<Page>;
           };

           /**** Transition ****/
           template<template<template<auto...> class...> class...Agreements>
           using Sail = Detail<Agreements...>::type;
       };

       /**** Continuation ****/
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
           template<auto...Signals>
           using Page = Send<typename Radio<Signals...>::type>::template Sail<Car>;

           template<template<template<auto...> class...> class PageVessel>
           struct Detail
           {
              using type = PageVessel<Page>;
           };

           /**** Transition ****/
           template<template<template<auto...> class...> class...Agreements>
           using Sail = Detail<Agreements...>::type;
       };

       /**** Continuation ****/
       template<template<typename...> class...Agreements>
       using Road = ClassicTrek<Commit::template Page>::template ProtoRoad<Agreements...>;

       template<template<template<auto...> class...> class...Agreements>
       using Sail = ClassicTrek<Commit::template Page>::template ProtoSail<Agreements...>;
    };

    template<template<template<auto...> class...> class...Agreements>
    using Sail = ProtoSail<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKz%2BpK4AMngMmAByPgBGmMQgZgDMABykAA6oCoRODB7evgFBmdmOAmER0SxxCclpdpgOuUIETMQE%2BT5%2BgbaY9mUMLW0EFVGx8Ymptq3tnYU9CjMj4WPVE3UAlLaoXsTI7BwA9ABUp2fnF5fHhyYaAIInZwDUACKY6a6MyHiYCk/nN3ujyuIIugLutwe5yeQlc/zO4IImBY6QMSJMSTcBAAnh9mGwnsomMgANaYdAANV%2Bdgx2Ehi2IXgcMLhJgA7FY2S8MVZ7pCkSi0ZgMVjkaimOjMTi8axMAA6BW0p7IAwKP4eQRMFZkJ7SxiyhVy7D0NiCBS0%2BkERnM2EMdAijWtbUi43IxgEBSGi1JOl8jmQp6B3VioUigXiyVY3H6then3K1V/ADyH2IEtyFvuQaeDKZBFemCdtADQcOhyeAEkGAA3VBkp4mABsGhT8XTAibGieAHdCAhdQhMA3m67TR6vc25SXA%2ByLE8vNkjLrow2ki8nq20wMXSb3Z7FT6eQ2uTzIdPg4KJcKpSGr2Ho/j5QfsAmmGrDXdgMRMG6zZm7tmC7hMATwAEqoEw6CruubxFiKn7fr%2B47PiAIB6qefrckkvIQvc4ahjel6Rvhd6YkwXhEHGL4qm%2B%2B5TvGNFqjCRCksQqCoCwpAXhG15uORlHPq%2B74KrCACOXhfL8/65jargii0qCsexLDyZg4mSXR3q%2BhC/pZkGJHEbehlEbx/GoFRQmaQxiYbqm7YMP%2B2YyfmsFasWemBmWlY1nWQ6dpu9mdj2fYDn5zZiRJDD7Jpk7nrO86LiBerQbZbbbpiEUaVRR7slhOHngZvGFWGRmmRR5mCYxVnUYmH5fj%2BY7moeHkJcBMJuSlrl0PB9VIdVqHodhZ4nkNfJAqCE1gpCwLHJWgpIfZ8KnOCM2TaC4LTeWnagZBThBXgfxMMOGhEsAwqxXhpUlSZIpmRZVVgbtqDSVaeZPG4iZ4MgAAq34ksNOHZjNBY0BEYEQVBALnl5nZ8cQ%2B2HcdACynj2hdAH6VdhE8feMqxpVNlw45QbOYSbFEOBkFxbpGPZk8wMeCwLCEGOS3XOeJOvcyjPMwQHMzjTdNCwzAjaLsi1Qy1Qv01tzY7fgz3Nk8hhQbDbRBW0Q5oCiWTkk8g7flOUtC8VZHlYaQh4MAzC0E12nS4BiWEkwZ0pba9pSg%2BsqPQr8lWzb/VodGtIDaV4NU5iROHqNtMO/zdNeQAEn0qZPFQXhRQMackKFTxsGsxDcUKx1CG5nZG7H0ted9CAHWnGdNAIuppgwCiZO0fwEIOyqi%2BLWfp5nuTHad51dr2Xc7Pm4S1iSbWEFx8dA%2BWYi0KgvZLun7QG086RsdFfwxNiTyoF38T61bBsALQkFghcD43rcVw7mM3djBGiq/fHmwTtH3TZI9UjVH0Ymz9SZdXcpXIWs5F5V3LAAdSHFaQwCgqBn1Pj3BgYstxD3vlnTsI8gpEGHi7TAgCaTo2fkLICS5koYnXAA6kwDMQEOjoDShuUMK4UgQnaEv1kE5CbpLbh2ZTYfxxm/UiX8BL0Rqr/H%2Bwk5QIQanuEBDtqEgVLnQTqhYy6YiUX1KiA1g4x2lhwmO8cRaCHCF4CWCILHlhrnXXBQ9tYlF%2BLnNAmC%2B44Ibng5sBClYq1zp2fRjUJwaCfsLcskQT6IIQBKJ4mBqyMAHDsYA/YQm9TCYqJWddqxtDwLtZAXFCDHwYLQI%2BK816I0SvQZWxBgA%2BHdJEhODja5/DrnEUQC4wr3CyXucJwVaC0CeHEBKesiHT18sdD6tEvq/UwP9TExwQ4gGUOTVAlM0YaFIPYnstdkD9niX8AQFSylDnSG0WUSJC5q3hhQk2WMxHvz1I%2BP%2BcjFH9L/M1bh6jw6qzXO9T6P0/oOg4rzUOJlnZnVWYVMmJ9NkQx6ohbJMjOF7McX8ZxTdXG607t3TxWDFrYoYMQmFgS7TBObKEgZOSIl7MySilRStezDNGUOHpUFJk%2BXrLDYFCylluBWT6VC6yEWaNoC0kRTzRGiLuvI6qlk6pMu%2BfbKhTsJUpVmWqeZoLI7gsIJCni0LrzYCNcXMVRAJXIuUWabKJigxmPyi1WVMqvb4xkUqhUNLVXnj%2BVslKlrEURzcD65CaLzEtWBm8UGQ5NVCKXk8TF9dB5Nzrug7IzMDCF3QfgjZWygpYFjVBJgMRUDJKlV5Cs%2BZ4l2noPirWb4hzdgNr0omuTEbbTLg8wMrrP5yu/p6qq7ymJRzVYGUmQbrUtWgcbem0IeYs3dGzcE0tSaLr5nO2dwjSwLt7tgwRdi53Ss/vKuUltrZiDtjAwMfyR5uzkp7PGQ55Z7Qyv7K9hig4fFhWHa1kd1asLPMel%2B4jnmSIHdIpUw6FUmrIUw8dDswE6O6iBgWbDKG3qdrQwFDCgHFmYSQ70GG44jWdTuzyvCW6lCHgmyhfawOQYqkO2qCrlW2o9Ko6WfzNV0ILHBPRXzw2wuMSRx1ZHgPcMsY4BgNis50bpgxl57qnwsY%2BWG69c7/UQy1fyvVbgN3mqvCa39UKg0FsEyq4TQGxrcKUxBp5Z7oOsbUwojTXGsNtV44C7V2QQWLLBUzQ1aEw4sLNSFszGz/2hqE9VTh2YnWSZPYxmVjnB3OY%2BRltzsXVE8Y6nxqduiYtWbi%2BYiTtnVprUuCtaEAAxPAxBFhPGwKoVgqIhxCMq1VoRZ5kjhBVF4LAq43CeP2OkTjPzprQiEAgCiBA6lCKY9le4pMZtzfoOi8azw%2BLpAUF4BbR67iypU8tu466mC7f29ecjDM2jEB%2BIXRbqXT3pespln553iD3fiJtqEzxNwAH0uxPf7WlqDb2mKZSiqay01p8yA40ADBsLqwfMYpAU0tG2flOS5vmINBCZ2C249hlcfGdt7ax24KH%2BwRTo/u5j019qSOJds8l9%2BZ73PY6DHekhgaNksOKxx0r%2BVytcOBoDrgK7%2BSo6eEjfbjhUQPZenD1KxAAdcABgVN1z7Ts45V%2BA48nI8pJdAy81HI6/jU8wFxM9FZVHIYE1TtSkUaeYgrPaxD27pZLYVAAKQ861Jc96%2BNW5FHL2gCvaAPeOO7hUXFfdM%2Bpsb1npuIMne9TlrnE7cfwqICjWg9pCdie5yTj4Wq7tK8xOAm1fVTPGpHonwnyeuFs7TzrjPJXctO3zwC%2BhGye819RcR4azepv/dTADswUvLovaIXTwpMQsfaVJoDswmuUeg9n8xrLdEreadjpO/NZci%2BLz%2BTh9c5OruqXUtDpqbh58M9pI32OLOW%2Bp%2BMmBpzEO6Kc8Q/6/LuGR%2B3UlmQuz%2Br%2BY%2BpwMIXg6Qbi6AoEvw8u0%2BdwPG0BsB8BFO%2BYZOF2FOvEa2BA82vEXAGgxwZgXEYAHAxw5BtIXEeBBBIoRBxwSQZBFBVB0cdIkaf2kBSMOiJKSBfy3BrQvBZOemAWmICO8ks2%2BBS%2BoqRGPyqEFmbgEu9BiOIqIAA%2BchIA0Wq%2BIo5BlBHAqyO0wB2kqEG6v2wM6BiBQi/qCBEeKUAhTAJKMhMKmIpBTwSQImP6HBwM30vwHoSBiw6YyAAOtE8QBAEAiw6AqECgsowRd%2BFhEeNBqBuscBNhfMPoGwZhbSQ4/Awya8bUnYARjgQRIR7QQUCgCA1S%2Bsa8ucqAdkAwh034PcOsSgkRlogRsRSg7Q4RBAkRIA0RbAsRIo547scUmIi8IxYhE%2BKhVOkhdBqhAurh7hqhg0iG2Y8hSKkx8Q6uyhqy6h4W6EM6WeTwqEWhE%2Ba%2BmIuhrB4WhhBGiGRiP6LUuyLUQgSRLR8Rm6EI6RZh3WE0NWzwsIniUELWbWB2y0EBPx1WkmwMVYM8KgvOIOKWW%2BFuJqdwDSyub0MJvkI81efoJGZ%2BpOuGJCqJwAIoixHh12I%2Bv29mkYX%2BsibmDS%2B%2BfymJZIwegKzJcJZ01eeiDJX6g0N20I7xfBTs7x6udhPBviuQJxRW7JYW3xzwPhTWQihRX0HRoR3RvR/RmAgxmIIpXAiRMByR7xtIGR2EHAWwtAnA/gvAfgHAWgpAqAnAbg1g1gOYOwewfkyQPApABAmgZpWwJIAQkgcoGgKQZgZgAAnOGVwP4CGSkFwGyGyNIBaRwJILwCwBIBoDsjaXaQ6RwLwAoCADsj6baWaaQHALADAIgCAJPOkBROQJQK4nQPEJELKJwKoCkI2JfI2JIE8MAMgMgE8FIHKGYLwOSIQCQHgJEXqfwIICIGIOwFIDIIIIoCoOoCWaQLoHqd2GmOkJwDwOaZadab6faZwEmBRLWfmKgFQE8O2Z2d2b2f2YOUGVPhAIzOkE2bcp6RsLwMWVoFsBAEgI2fQGQBQBAEBRMMAFIKQTQBHvEAWRADEMeTEOEG0NiHubwMhcwMQNiEmDENoI0MWV6drGOEmOUmheuVgDEF4MAHxMMgWdwLwFgCwIYMAOIBRQ1gRXgMkvRXaZgKoI0BRAcF6eEEiMmXaVHjEGmNhR4FgMeVaHgOmQxaQMksQGWkoG8MxUYFHkYL6VsFQAYMAAoBSD8N2K2DaV6TOcIKIOIIuZZSuWoMeZufoCxSgM6ZYPoHgDEAWZAFsLUfUZwJfBEXQqYJYNYGYDmSpfdlgN5RAFsA0A/C4HaHMH4HqaECsFUDUHoCUAInkJ4F0FlVkDlaMBlRMHqfFQMEMLMHlYUGVX0JxQIJVcsJUOMAkGVUsMlXoAEe0MVS1RIHFW6fsH1foIeaQNmbwLmTeR2V2T2X2QOUOS%2BbgOOZ%2BUkFwN%2Bd6bpVsIOJBBMLFaQAGZIEkHKOGUkImRoJIGYJIM2BoP4I2OGcNSmWmSACtXKI2FwI2CkOGXGY2P4JINGcdY2KNcebmfmYWetSWf%2BZWQBdWeeXWaBeBcQC2WwJwG0CwNWGyJfEdDREuFwOGXKFwMGaOfgEQFFXoJZXOTZdIHZUoA5euboKQduRduhQeRwFaYDeubmWeQQBecfNebedNa%2BNjbjfjV2K%2BRxO%2BcBQ2MkGYGtb%2BaWVDfDfWWBWLR%2BSgAYEYDjUQXwHQDcvBYheuZhahehaQAbdhbhfhQ4EbcRe6KRRUseZRdRbRbbEbUxSxWxXafgN%2BE0NxceXxQJUiEbSJX0MeRJVJdiDJQcHafJYpV6SpWpZgBpa7cBLpXwAZUZSZWZUbWTdZQuZTbIPZWuXaXTc5TpSFVYO5RJTFb5eNrkPRYFT0cFW5RYOFeNZFZOb8PAHFXVQlRAK4B1alXaD1QXAVTRgIH3RkIVQMIPZlbVf0M0O1dVSlb0LPQ1UsFPaVdMMMGPV1U1asNPf1bsINatfdazWNSeRwJNXeT2VjSBDjXjcGU8BAItcTZLStTLRtaQFtbfJQMzamaQOmUkLjWdWyP4OGQmUkOdZdb9WzTmZwCDUWcneWVWTWbDQ2crcBYjQcCjfeSwAoNWAOdWLfUKIsITUtZOaTbIOTTnUufINTQXToE9aQAzbuQxczSfUDaeTDZebzdg7g/g4Q1eE1qLSiB%2BS/UkG/eDWWYBWg/EIrfDSAHgzAQDgQ%2BGQDkQwQADqoN2VrbBY1pQHrXaSbeRV6YY2bQRZbeCtbWRXbZgFRTRSvPRV6S7VpRHYxRxV7e3eub7cgIJQHYIEHeuSHaheHXJfdtHbwLHbrAnVpUnRI/pS7GnZgKZXiJnRQ9nRILncubQ45Qw2rcYI3R5V5R3fadXQIPRYcBEa5aFZYM3faa3dFUU%2BVZKT3UlQvXoGlc1UPXqdlQMGPd07kGva1UvfVYMPPQUIvY0yvcMAM51aM/lW1VM%2Blb1UfQoANQuaw0eezZwDeTw3g08Mo3KGow/U/TnOYK/T%2Be/Z/TtT/Y9RGXKEkEkIEGdUQRoPc2yO9dA%2BNbA7YKDbLRsP6SAJIP4EdfGWyJmSkJIFGVwKGWYADcmUkBszA3mWDX%2BczSOR82fec%2BDVsCpdkM4JIEAA)$Done$

## Links

- [source code](../../../../conceptrodon/descend/pagelivore/classic_trek.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/classic_trek.test.hpp)
