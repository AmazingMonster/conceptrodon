<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Roadrivore::Trip`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#roadrivore-trip">To Index</a></p>

## Description

`Roadrivore::Trip` accepts an operation.
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

This function has multiple signatures.

```Haskell
-- End in Conjuration
Trip ::   template<template<typename...> class...> class... 
       -> template<typename...> class...
       -> ...
       -> template<template<typename...> class...>
       
Trip ::   template<template<typename...> class...> class... 
       -> template<auto...> class...
       -> ...
       -> template<template<typename...> class...>
       
Trip ::   template<template<typename...> class...> class... 
       -> template<template<typename...> class...> class...
       -> ...
       -> template<template<typename...> class...>
       
Trip ::   template<template<typename...> class...> class... 
       -> template<template<auto...> class...> class...
       -> ...
       -> template<template<typename...> class...>
       
Trip ::   template<template<typename...> class...> class... 
       -> template<template<template<typename...> class...> class...> class...
       -> ...
       -> template<template<typename...> class...>
       
Trip ::   template<template<typename...> class...> class... 
       -> template<template<template<auto...> class...> class...> class...
       -> ...
       -> template<template<typename...> class...>
       
Trip ::   template<template<typename...> class...> class... 
       -> template<template<template<template<typename...> class...> class...> class...> class...
       -> ...
       -> template<template<typename...> class...>
       
Trip ::   template<template<typename...> class...> class... 
       -> template<template<template<template<auto...> class...> class...> class...> class...
       -> ...
       -> template<template<typename...> class...>
       
Trip ::   template<template<typename...> class...> class... 
       -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<typename...> class...>
       
Trip ::   template<template<typename...> class...> class... 
       -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<typename...> class...>
       
Trip ::   template<template<typename...> class...> class... 
       -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<typename...> class...>
       
Trip ::   template<template<typename...> class...> class... 
       -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<typename...> class...>

-- End in Transition
Trip ::   template<template<typename...> class...> class... 
       -> template<typename...> class...
       -> ...
       -> template<template<template<template<typename...> class...> class...> class...>
       
Trip ::   template<template<typename...> class...> class... 
       -> template<auto...> class...
       -> ...
       -> template<template<template<template<typename...> class...> class...> class...>
       
Trip ::   template<template<typename...> class...> class... 
       -> template<template<typename...> class...> class...
       -> ...
       -> template<template<template<template<typename...> class...> class...> class...>
       
Trip ::   template<template<typename...> class...> class... 
       -> template<template<auto...> class...> class...
       -> ...
       -> template<template<template<template<typename...> class...> class...> class...>
       
Trip ::   template<template<typename...> class...> class... 
       -> template<template<template<typename...> class...> class...> class...
       -> ...
       -> template<template<template<template<typename...> class...> class...> class...>
       
Trip ::   template<template<typename...> class...> class... 
       -> template<template<template<auto...> class...> class...> class...
       -> ...
       -> template<template<template<template<typename...> class...> class...> class...>
       
Trip ::   template<template<typename...> class...> class... 
       -> template<template<template<template<typename...> class...> class...> class...> class...
       -> ...
       -> template<template<template<template<typename...> class...> class...> class...>
       
Trip ::   template<template<typename...> class...> class... 
       -> template<template<template<template<auto...> class...> class...> class...> class...
       -> ...
       -> template<template<template<template<typename...> class...> class...> class...>
       
Trip ::   template<template<typename...> class...> class... 
       -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<template<template<typename...> class...> class...> class...>
       
Trip ::   template<template<typename...> class...> class... 
       -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<template<template<typename...> class...> class...> class...>
       
Trip ::   template<template<typename...> class...> class... 
       -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<template<template<typename...> class...> class...> class...>
       
Trip ::   template<template<typename...> class...> class... 
       -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<template<template<typename...> class...> class...> class...>
```

## Structure

```C++
template<template<template<typename...> class...> class>
struct Trip
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

- In the first example, we will compose `OperationA<2>::Road`, `OperationB<10>::Mold`, and `OperationC<'*'>::Rail`.

```C++
template<auto...>
struct Shuttle;

template<typename...>
struct Capsule;

/**** OperationA ****//* Start */
template<auto Variable>
struct OperationA
{ 
    template<template<typename...> class Container>
    struct Detail
    {
        using type = Container<Shuttle<Variable>>;
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};
/**** OperationA ****//* End */

/**** OperationB ****//* Start */
template<auto Multiplier>
struct OperationB
{
    template<typename>
    struct ProtoMold {};

    template
    <
       template<typename...> class Container,
       template<auto...> class Sequence,
       auto...I
    >
    struct ProtoMold<Container<Sequence<I...>>>
    {
       template<auto...J>
       using Page = Container<Sequence<Multiplier*I..., J...>>;
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
using SupposedResult = Capsule<Shuttle<10*2, '*'>>;

using Metafunction = Trip<OperationA<2>::Road>
::Road<OperationB<10>::Mold>
::Sail<OperationC<'*'>::Rail>
::Commit;

using Result = Metafunction::Road<Capsule>;

static_assert(std::same_as<Result, SupposedResult>);

// The following `static_assert` shows how the operations are composed:
static_assert(std::same_as<
    OperationC<'*'>::Rail<
    OperationB<10>::Mold<
    OperationA<2>::Road<
        Capsule
    >
    >::Page
    >,
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
    using type = RoadArg<Capsule>;
};

template<template<template<typename...> class...> class...Args>
using InvokeRoad = InvokeRoadDetail<Args...>::type;

using Result_1 = Metafunction::Snow<InvokeRoad>;

static_assert(std::same_as<Result_1, SupposedResult>);
/**** Second Example ****//* End */
```

## Implementation

Since every member template of different signatures is given a unique name, we know which member to pull out when asked for a template of a specific signature.
For example, we can compose a `Road` and a `Rail` in the following way:

```C++
template<template<typename...> class...Args>
using Metafunction = Rail<Road<Args...>::template Page>;
```

Note that

- `Rail` has signature `template<template<auto...> class...>` and
- `Page` has signature `template<auto...>`.

This means in terms of signatures, a `Rail` can always be invoked by a `Page`.

We will implement `Trip` by performing recursion manually, meaning the function will recurse only once for every invocation of a member template.
We will showcase a simplified version that handles `Mold` and `Rail`.

Note that in the following code,

- `Radio` is a `Road` and
- `Car` is a `Mold` or `Rail`.

```C++
// `Radio` is a `Road`.
template<template<template<typename...> class...> class Radio>
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
           template<template<typename...> class...Signals>
           using Road = Car<Radio<Signals...>>;
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
       // This is because `Agreements...` will be used to invoke `Trip<*>::ProtoRoad`,
       // which has only one parameter `Car`.
       template<template<typename...> class...Agreements>
       using Road = Trip<Commit::template Road>::template ProtoRoad<Agreements...>;

       // This function composes the conjuration function `Road` and the `Agreements...`.
       // `Agreements` will be used to invoke `Trip<*>::ProtoSail.
       template<template<template<auto...> class...> class...Agreements>
       using Sail = Trip<Commit::template Road>::template ProtoSail<Agreements...>;
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
           using Road = Car<Radio<Signals...>::template Page>;
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
       using Road = Trip<Commit::template Road>::template ProtoRoad<Agreements...>;

       template<template<template<auto...> class...> class...Agreements>
       using Sail = Trip<Commit::template Road>::template ProtoSail<Agreements...>;
       /**** Continuation ****//* End */
    };

    template<template<template<auto...> class...> class...Agreements>
    using Sail = ProtoSail<Agreements...>;
    /**** Define Sail ****//* End */
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMxmpK4AMngMmAByPgBGmMQSkgAcpAAOqAqETgwe3r4BQemZjgJhEdEscQlSKXaYDtlCBEzEBLk%2BfoG2mPYlDE0tBGVRsfGJtc2t7fldCpND4SOVYzUAlLaoXsTI7BwA9HsA1CYAbBoASkz4qKcah3gKh0zHZ%2BeoV7cAdCYaAIIEmBYqQMAJM/jcAKBIMwYIhgOBTFB4IIAE9UoxWJhPtiwdhDsgDAoFNjvv48QSmETDpdrrifr85sQvA5DgAVYh4VL0kwAdisf0OgsOewAVGKRYcACKYGgRanvdCHcUig4SgatJV7elC4VHW5uFq3e6PZ63ACynnQX21QshCKRcKhiJhyLRGLYJNx%2BMJjwNxDpAqFjOZBEOymIqCIbw%2BgcFvP5vx1QtF4sOHhYLEIbEESvFqsO6tDKptSeDLPTmYIJZ18erScFKbFaYE2i2iOyubF%2BcLmrr9YOLwuVycRsMiv1hrOT2ImHxqCBGUwioQ8SxfaTA4AYnhiHNSIcAO6z8JzQyOZ2Dmkjqdjw6oGLNcJPQeo9HMNjW2P1htHVkrhj7ke9wMAAbqgADWs4Tv6U4HoQCCHAQK6HDOCheLQjhGC%2BbrvjCZzfF%2B352tCsLEc6pE4Zinpkt6lLEtiQh4MAzC0AoAaJt%2BQpeJkWHRuO/iSmmhrgleNzgoxzFiPRpLYHS/gJpxybKs2DCtsQ7YCJ2Kqioc2AMIqxZ/OuNaEf2ynsoYxQdsq3bzL2pkbkcAASPTosQhxUF4DANJp/DuUhs5sMs/nwtCg5CAwqAHp%2BHGKQOf4PB5Xk%2BQwiHqQwCjpK0jwBXOqltn0SXeYVtx8UacFIZsobhGB4HhMA9wEPuxnJkcYi0FF9VJa0K7uakEY7FSMQoneAXuQgTG9QAtCQWDuZ5xXZMSLWCmRDprS6jr2ptG0UW%2BVE4jRFJEtR5I%2BqdtFUnxABqmBEj07GKYKZahtKj60Ctxx8p9OoDgA6rOBDpQoVDxIhyFoPl6mFQtKWXgqRpEPDVy3fdH34T9XE8Q1r5QQJ8oo3ddiwmVZJggpT28pK5Pcg5Oq7cioXkYzTrrUz62UR6h1nXRF3HdJXr8ySvzADOgKMAQbFk3TWNdRFUXHPjb1MHQsIi2L2aS6dIAgLjNMyw25nA1kmk2TpekGVqDlU/rsW/cpFZZhLWn5hb9m/OujYSh4gjhF4GmpWbap2YZdutWyE2PLDhVoAuSg5RDLYFR20cdqVCM3vp4NQWc6uYOLggCxjDkDpEkaAwgiKHJgIGMODmzAAhtx5wXWs4lOiUgS0eDDsg%2B6EHeDC0CN7VRSahzY/Q07AD4EsEWHP4R4liVxKI3E538ov55rRd3HBtC0IccSHOvipIzVEEb%2BynKwtrIDhpGqBlWcpCe0cB4TcgCGV48AjD4Ps5UgtExACdy0EYpEXZjtKBe13RYm5pdaSLcd6PXrNxLqfFFaCWvlycEjsCA6w2gTK0ZJCFQLDBGKMCNwTIIlgLMm8laYL11EvKOyUY7ziKHdbOeU1IByKnDdOHxM5n2Qs3Lerdd7z2/AOcRGs6HlToIfY%2Bp9EKoGArVK%2BHJcFuDvg/IgQgVa0GkfWBmW0SIs22rCJgXgiB83OggoW2JaGF1QUmdBWFDF0CwWybRsJ8FkNZrOUm2BAnbQoY/LxH0aESJ3qdW2MiHayD9vwoOuks6hxrDyamjCjJfjMQUzm8CZKIOFrEhR0s7YeIapgsEgl9FP2oW4FxbcZIJKUqmaUspgkKhdubDJVsPZfi9lKGUiwCxGL6cHQY7tfq/kjgIwqiVcqZEzAYfyYizgNOfncLA3TFRMBiKgWuJjF4AElQyV30vQBOs5RBKEPL1DefojSJVNK8IxEDbQwMsRY8xzMDS2NQPY3mjifRCX9JUnUL0IkGM%2BV%2BWsJckkZidjmNJPZMn1hhfg9ciLmH21TD7PhhV0Uh0GU9RCPz/kc32lzEpTjPgSRYlLWSBsT7Y2IT4l5IlhxiTcEyqSd8iHKCYMAF0slcn4o6U2IlydTZ5n6ZbJhFKRkWQyibQOCrpkakxYpApVL9VBNgbhEFJ0wWgvpeCm6RMHpQqejC5Wqs2V4opbLLCuMfHWrRiTahEqKaKRtpKz6hqrG/IBYU2lxTBYOMtRa6NFqWkss%2BtUgskUDw%2BMddE5p5TC5CrdO0uKRtLIaqmekpV1tskFoJTK%2BclZNalrdqHT2STfYMH9iSrVBYyXrhDX83GJrzVms%2BImtxOoU21Pxjg/xtbCBhLCiEudF5tlNMTfEoNDle3hqpTYuxg76E8yHSOu17iOVRJ8VOvBM6CG63IQum9QTYWoCiWrHNrS5L%2Burd7ZJbbUmdsbeSoUgaEzVk3WzI14Id3Ar3aapBr6k1fhTWeupj7n0xPkbm7mVaRldPGWetJ/7uSVvXb8L2youz0kbKybAQhWR5go2RsjgzuRmH8OEAkXgsCKzcLYughAUTsXpGYyD8S/gwqEAgWxBB6C20EwaopImGRAxDEJVIaFpPEZGQAeTcgHRMpKZmhyE0Cw411u6HPU6yxTTIWTafiLpwjFhjj5INXJyNMGVKPgiJCyz0KlMskzdWF134U0euQz7Tz8RYTick%2BptwpmOTmfFe%2BwLRHgPOfA9Sna8noPOLg6O8dvTkMBbQ9vOheb0QydS/R1MtnobZD03%2BgZTCtM6b6I5/TOrBlGaRmadCjhgR4Ei5UmFtWA7Ae%2Bul0NEIimjphQ0i0tBxzfSq3ku2u0EXgh7a5uB7nwsqy86/Dd26gXuaEJgAAjl4RgOxDvMOE9iM5gXj0Tz86Geblpp2CH20N/lF2rveU2mctdEqfOAYm8w7rUHPgAClR1uoaiKsVXLZDfchb9y713Nq9YwpyWgg3iAiiB9ifc0PgdVqA8q75GX%2B0HWHXl57KaFv8XqZQ1ATOX3obfQw8bOSEwtbs21htTXVv87qwINwpaMVdeO0jeLPcYgWfpCN1r2Q3AOZAy5jL93Y1UjOxjgHs3XujPeilj9Y6OWhfxnr/7OxYRy8S8lhFK2hlrc11N7X8bD309B4KcdkyiuYBNyVyR5WXQ89tqLgOEv8PC5dyM7cu5QzYFUKwYEs4OtFkGYhrwqQuHoHOHdPrXKmCqfQptaLBApObS4BoEUQRDhgA4CKRvck/VMMZ4HpgqdNLIYvW4UbfQPbgjMLiHWIT6Rj6aQP7IVhwQ19HyAdnlSdaof7yr8XsJG/N44Avy4qtl8gBxcR8dheMI%2BLNJ37vfgQCkzcAaUviviOnkcMgAA%2BnReIBAIBzHQDrBQmJ38pY3AC81MmoCwc888QC%2BtcRVgZM/h4pkJ%2BAD5OosJbhn88A38P9WgjQFAEAx5Dg8D01cpUB18Mppw7lOFFxf8ldmgX9AClBWhv8CBf8QB/82BADYRqxp8N9wQt8W9SEb9PlNsvxuCGBZ83B58BCl81cRDSCh83AR8BDb9jJ781MYQNsfdFZQl75RV1C7ZcRbsdQhAICqCoCMJuQyRYDJV48dw5hdIU8oR09Gty049lIztIZFRk9U8p4M93ZQNoFqdssdd91EFiFfhiBgB2IYUzlQJL4%2BIAsjJwdzcupLdBI%2BJwjIi8ES81DHcPZndZNqc3c%2B0gjPcQiGUMj4NfgU0YjNEJ1BIai4iFRitmkIj91CF81j8OUzCCBX8uBz9L92FsgV801YQGjIJx8n9aCMD6DP8mCWC2DMAOCRJT8eiuB9xjDc9TCViYCI83D6gBBPCHC08hdLYOB1haBOAABWXgPwDgLQUgVATgNXSwawCeTYbYKCFjHgUgAhO4s49YcCEAE4SQT4JIDQE4fwDQfwfwZIE4S4/wAATh5H0E4EkF4BYAkA0A0FIFuPuMeI4F4AUBAGxN%2BK0HWDgFgBgEQBACqlSFsXIEoFjlSDoHiEiExE4FUCSBOCmmBMOGAGQGQEOCkE%2BDMF4CXEIBIDwF/zWP4EEBEDEHYCkBkEEEUBUHUD%2BNIF0DWIPHUlSE4B4HOKuJuM0F4HxM01sTpNDFQCoEOE5O5N5P5MFOFLMEOAgHTGZPoDAS%2BNWF4FJLONIAgCQCZJZLIAoAgGDM9JAGACkCCBoAwniCJIgBiBNNIBiHCBaBRH1N4DTOYGIBRE0xiG0HqF%2BO%2BNjk1k0yHkzI1KwBiC8GAANAPiJO4F4CwBYEMGAHEGrJ3GLLwFribPuMwFUHqFsV2G%2BPCABAuI1LxxiHUjzI8CwBTKBjwAxObNIFrmICOSUGlDbKMDxyMBNPWCoAMGAAUGukGwPFs1uO%2BNlOEFEHECVJvNVLUBTK1P0HbJQGsGsH0DwBiCJMgHWBIL6CbKmh/zqVMBeMsDMDxPXI5CwD/IgHWDqBShcH0mmD8DWNCEWAqCqD0CKA1TQtwoyA1WGGwpWG6F6EaHmAIrWKQr6ELBItGGqFsCos8A6D0FPFaAYuCgkEQveJ2B4pRI4GuJxJTPxNtK5J5MkD5IFKFJBJdIgFwAlK9P8C4B9J%2BIPPWBXCuDGAQtIEBMkH8E%2BARP8B5EkA0EkDMEkDOA0EuJOARMErRNIAxJUs%2BBOC4BOCSARKSHcsuMkC4EuOMpOBEo1PxMJOJPUr%2BPJKpMDJpItPpLDIjNZPZI4BaBYBAh5CmmeApCwi4ARM%2BC4E%2BAHPwCIFgr0BvPlPvOkEfKUGfI1N0CCB1JLyzMNKEuNJCs4HNIIEtLvBtNSvSsytohyryoKruDdM4RDOOBYzMDUr9PJKDPGs9IZPDIWrGD6oyuyujIRJrz4DoFAUTOTI1JzIzKzNTPTLzILKLIcBOrLIlgrOHhTJrLrIbNYhOtbPbM7PuPwBnAaD7JTMHOHIBBOvHJ6BTOnNnJRHnN2HuKXJXO%2BPXM3MwG3PevqgPL4GPNPPPMvJOvKrvMVKqtkCfPVPuPqrfP3PAqsEsG/N/PgAAtSCAs4BAuYLAs/MgugviFgruhpvIp7OcAgFcGouCH0i4pwrWLwr6AFrFuyGFrItososGAFtloEHoqwsYvYpYryHQuYsGGluqF4q2H4tUsEuEtxNNM4GnDSoyqyoMCGvysKtdMUpKsmpUpmo0tIC0rmkoBascucryvMp5ACp5B5BhMsuBLWJNoeM4DCpJNRopOpNpPisZJWuIDZLYE4FSt5JYAUBAkFJAlys%2BGhDmDFOKslOlOVNvIVMSDLsJpfICFIEar1ObJauNtEo6riqtN6uIBYAzqzpzrzoLtDDGqBAmvMGhJdsioDPmqHsWoSqTpAGztz1f1zoRNf37vf07uBJ2vjN3EoAOvuKOrzJOv3vzMLOLOutrVusrIeswFrPrPaibO%2BLet3KhpbO7J%2Bs5o1P%2BuQBHKBsEBBqnJ/PBshsXI5Fht4HhsXCRt3JRvHqPNFQxswAvLfGxtkAqrxqrpqqJp0FrutuMBZpsGnPgtpvpv2B/w/IgosCgtNJgqlM5v/O5uQr5tQtYvyAwqFpVu4tFqIvFuYc1sltKHYZFvobovVrYpop6B5v6HmB1rVvlp4Zkc4oEZWD1o%2BIEsnObvao4HNu7uzsOCXvzudDsIUuLuUtUt9Ndvdp0q9vRJADMDyuhMuMuPMpryhJMo8uCrxMjtsHCtmoBICEuPysCoRJODhK4BhLOH8EEv8Dao8YJIirJJatFPcdNtiZ8bXITKGMkCAA%3D)

## Links

- [source code](../../../../conceptrodon/roadrivore/trip.hpp)
- [unit test](../../../../tests/unit/metafunctions/roadrivore/trip.test.hpp)
