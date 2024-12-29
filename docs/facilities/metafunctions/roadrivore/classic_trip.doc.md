<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Roadrivore::ClassicTrip`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#roadrivore-classic-trip">To Index</a></p>

## Description

`Roadrivore::ClassicTrip` accepts an operation.
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
 :: template<template<typename...> class...> class...
 -> template<typename...> class...
 -> ...
 -> Commitment

-- Compose with Page
ClassicTrip
 :: template<template<typename...> class...> class...
 -> template<auto...> class...
 -> ...
 -> Commitment

-- Compose with Road
ClassicTrip
 :: template<template<typename...> class...> class...
 -> template<template<typename...> class...> class...
 -> ...
 -> Commitment

-- Compose with Rail
ClassicTrip
 :: template<template<typename...> class...> class...
 -> template<template<auto...> class...> class...
 -> ...
 -> Commitment

-- Compose with Flow
ClassicTrip
 :: template<template<typename...> class...> class...
 -> template<template<template<typename...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Sail
ClassicTrip
 :: template<template<typename...> class...> class...
 -> template<template<template<auto...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Snow
ClassicTrip
 :: template<template<typename...> class...> class...
 -> template<template<template<template<typename...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Hail
ClassicTrip
 :: template<template<typename...> class...> class...
 -> template<template<template<template<auto...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Cool
ClassicTrip
 :: template<template<typename...> class...> class...
 -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Calm
ClassicTrip
 :: template<template<typename...> class...> class...
 -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Grit
ClassicTrip
 :: template<template<typename...> class...> class...
 -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Will
ClassicTrip
 :: template<template<typename...> class...> class...
 -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment
```

```Haskell
-- End in Conjuration
ClassicTrip'
 :: Commitment
 -> template<template<typename...> class...>

-- End in Transition
ClassicTrip'
 :: Commitment
 -> template<template<template<template<typename...> class...> class...> class...>
```

## Structure

```C++
template<template<template<typename...> class...> class>
struct ClassicTrip
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

- In the first example, we will compose `oper_0<2>::Road`, `oper_1<10>::Mold`, and `oper_2<'*'>::Rail`.

```C++
/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** Capsule ****/
template<typename...>
struct Capsule;

/**** Oper_0 ****/
template<auto Variable>
struct Oper_0
{ 
    template<template<typename...> class Container>
    struct ProtoRoad
    {
        using type = Container<Shuttle<Variable>>;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

/**** Oper_1 ****/
template<auto Multiplier>
struct Oper_1
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
using SupposedResult = Capsule<Shuttle<10*2, '*'>>;

/**** Metafunction ****/
using Metafunction = ClassicTrip<Oper_0<2>::Road>
::Road<Oper_1<10>::Mold>
::Sail<Oper_2<'*'>::Rail>
::Commit;

/**** Result ****/
using Result = Metafunction::Road<Capsule>;

/**** Tests ****/
static_assert(std::same_as<Result, SupposedResult>);

// The following `static_assert` shows how the operations are composed:
static_assert(std::same_as<
    Oper_2<'*'>::Rail<
    Oper_1<10>::Mold<
    Oper_0<2>::Road<
        Capsule
    >::type
    >::Page
    >,
    SupposedResult
>);
```

- In the second example, we will transport the conjuration function to `InvokeRoad`.

```C++
/**** InvokeRoad ****/
template<template<template<typename...> class...> class RoadArg>
struct InvokeRoadDetail
{
    using type = RoadArg<Capsule>;
};

template<template<template<typename...> class...> class...Args>
using InvokeRoad = InvokeRoadDetail<Args...>::type;

/**** Result ****/
using Result_1 = Metafunction::Snow<InvokeRoad>;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult>);
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

We will implement `ClassicTrip` by performing recursion manually, meaning the function will recurse only once for every invocation of a member template.
We will showcase a simplified version that handles `Mold` and `Rail`.

Note that in the following code,

- `Radio` is a `Road` and
- `Car` is a `Mold` or `Rail`.

```C++
// `Radio` is a `Road`.
template<template<template<typename...> class...> class Radio>
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
           template<template<typename...> class...Signals>
           using Road = Car<typename Radio<Signals...>::type>;

           /**** Transition ****/
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
       };

       /**** Continuation ****/
       // This function composes the conjuration function `Road` and the `Agreements...`.
       // Note that even though `Agreements...` is variadic, it only allows a single argument.
       // This is because `Agreements...` will be used to invoke `ClassicTrip<*>::ProtoRoad`,
       // which has only one parameter `Car`.
       template<template<typename...> class...Agreements>
       using Road = ClassicTrip<Commit::template Road>::template ProtoRoad<Agreements...>;

       // This function composes the conjuration function `Road` and the `Agreements...`.
       // `Agreements` will be used to invoke `ClassicTrip<*>::ProtoSail.
       template<template<template<auto...> class...> class...Agreements>
       using Sail = ClassicTrip<Commit::template Road>::template ProtoSail<Agreements...>;
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
           template<template<typename...> class...Signals>
           using Road = Car<Radio<Signals...>::template Page>;

           template<template<template<template<typename...> class...> class...> class RoadVessel>
           struct Detail
           {
              using type = RoadVessel<Road>;
           };

           /**** Transition ****/
           template<template<template<template<typename...> class...> class...> class...Agreements>
           using Snow = Detail<Agreements...>::type;
       };

       /**** Continuation ****/
       template<template<typename...> class...Agreements>
       using Road = ClassicTrip<Commit::template Road>::template ProtoRoad<Agreements...>;

       template<template<template<auto...> class...> class...Agreements>
       using Sail = ClassicTrip<Commit::template Road>::template ProtoSail<Agreements...>;
    };

    template<template<template<auto...> class...> class...Agreements>
    using Sail = ProtoSail<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKz%2BpK4AMngMmAByPgBGmMQgZhpmpAAOqAqETgwe3r4BQemZjgJhEdEscQlJKXaYDtlCBEzEBLk%2BfoG2mPYlDE0tBGVRsfGJybbNre35XQpTQ%2BEjlWM1AJS2qF7EyOwcAPQAVMcnp2fnJ/smGgCCRycA1ACSLKn0bIJMfQ%2BnV7f3F0BFz%2BN2ud32DxMADYNAAlJj4VDQjQPPAKB5MSEw2GoBHIgB0YIImFeBmJJgAzG5iaSvphKdSSW86QyCABPVKMViYfG8ynYB7IAwKBS8wkUgVCpgih7wxH8sHzYheBwPNzCzLIAAqxDwqTBJgA7FZbg8zQ8AYcHgARTA0CKy3HoH6XMHmi0Q5FuFrI1HozHIgCynnQBLd5ppzPJVMjZPpMY5XLYYv5go1ap9EvDZqVKoID2UxFQRBxeNN5qNJpu7vNlrVqBYLEIH3zv2z7tzqo8jcI7Yrxr7NYtp3rDG02y%2B2RdxxBQ5r%2B092IRTl9hmdXp9MIxxEwgobRUwzoQ8R5g/nEIAYnhiPNSA8AO678LzQyOOlYuHLpFbtcPVAxZpwgxD92U5Zg2DDcs5zNBcHi1Y8GDvR9UQYAA3VAAGtdw3YhfXvQgEAeAhjyIxMHh3BQvFofNUCoIiSP/QCInXGFQKTekYUJKDoNjFkYyZONWUTcCeT5CU02lUVeSEPBgGYWgFAVbi5y8TIjEdBFIQpa0M1whMwO5WUvwZGS5LEKTxWwEAQDYhUKSrM93TrHVDGKKc22UodYIACR6TliAeKgvAYBoBECkh6N3NgVgC3jiQ/IQGFQe9IOraCYIheC0UC4LQoYIjiFc9JWnRYjdzQMcJ2%2BIKQu%2BZFS1DLd8OIrZ83CdCMPCYBUQIO9HNrCExFoZKupy1pjwC1Ii12GUYjZP8yoChBZImgBaEgsACmq8tFfqzTi%2BNGVpaMjqjQ6DqEgzkzEyUNRTcSpRFe7bskjT0AANUwEUeiUtL0s7fNbUA2g9shAdPPS2CAHVdwIQqGAUKh4kivdKsK6rcrq7EnV9IgPwaz7vpBzjQfdVTRrYrSdIJr67AZBq7KrdKzSNa1KQciH3Qu/jjvOgS%2BNOwT9PY56JKem6xYs1NHosm5gB3ElGAIRSs0581yfUxLkqpm1MGBhk5YVlspYlazbPss9WfZg0IbrDxBHCLxJzCjy/qczLlvRbbvjQV4Mi%2BlGKvHdGp29qd6pxn8GGdMqP0NzBFcEKWSdtiFImLWGEC%2BB5MFQxh6K2YBCORePE%2BVlMt2y1CWjwZdkDvQg/wYWh5qG5L/QeNTgHobdgB8JWuLdga4M9v0HjiURVOwmFS%2BNiuUXw2haHH3cp5j1AUI66eNHVSS8G1XV9SpQ5%2BWswti1QBmYVIM9YPvZbkEIrP0QEFum93VIWm5YkApw1K525oLAWbERKixlmKWeSsVbYDPBrbqDUda7xFPvHUeoGTdibAQM2/N4oM1NjZHBu5z4lhxlSSBSdnrW1uLfD22Uw5hV9geUqJEg5VVDpjcO2M8RRxjiREu8sE5zz5CnIeGU44CLLopJqdBl5xAeGvIiG92qYW3kgzUqCj5uBPvg4hqAhBMDoIPABhDWQmJ5mdBkTAvBEDAXdCW4DeTkOVr9FSXcHj6LoIgjUKDD7oIbJg7BvM3qnwIUE3RHiQZkIkUIyyVC3ZWwttQ7igCUnCW5LYySEDolQJcerNxCDKQ6V0XgtwTiTYwMSaCbidZbT2l3BE6chxZzDyyl7DhYVsqx0yE2AwsU%2BEwmKZHFEWA6nOiYDEVAecjHDyePmLO0d6DMPKtKXc98Twfm9LhSuHd6oGOJhoaZ%2B0zFAJOoAqxNj7F2MspLXSuScxwzzAWIsRAIntkrLfEcGDmxK0ac0msAN6w9gIJbcGoj5yfIEMHZ2%2BVXbMyIsc1JV1RLXIcfiUy8loGgzgW9RBmY3ByhXFSdF5lnqBLOgWJgwB4wVI5mCrmCKGW81MUy4WoDLmZPZeLFF6YaZEzudBAFQM9mg3eWrGs2LKaFLeoTOmVI8E0pFYaNmlTQbOXhm5F2roxXwpZScvmurEUi05eUyWGSuVlP5a40aWt7w6yFXQA22SKE3TNomOJc4Em0rnHbWQjtoW/LPCkhFaTrrco5fiC1qswXYoKdpNU3iD5oKpF8rBoTyXyrJXGJ5F8SllMoSqiGQaDXHPOagM1JrUWRpgRDbFDSpVqJ8UmtwKbM3vgzWmrN4ThVRKNlA/NTN%2BzKq9RGRlFjzFC29NYstxry1ZN7Unflta9k6y7Q6ntgi%2B03TiZ6m2dwgT7tdnWK8N58zYFUKwN4u5D0HpvSCA0ZgKThCFF4LAWk3AVV2KkZxUawR1iEAgaxBAe6uzOVOyhtwAX/sA/Qbd/xPlMFSJRYDWqbiGrZbEiDDyuwIaQ/GWldYADy/kAD6KIQMlqnQ8d6NdxkwajQCoj8RSMGmNJCZJo6J0gPSca0cTF4j8oBYMss8TQXQQlWRetsgDERD0m4KDBAgOHWo7qWj1LGZvKVbBt2Rax3UhDci6WVyq3thjU6FdzzL6kNKU68uW6VWaYLXux4jHiDEa4AG24oG8aBioo4N4eB%2BP0aw/mFzbmWMDqOQa/TAngvZqIMGWg64BwOeHZFix3EGSBuDUi8tvHpPxBvoWijFyw0yiEJgAAjl4RguxCtgtLWKJ4byo0dli7ohLoZk1SaWLJ8rVWauHSePmip1aRMRfpbqhrvIABSlqzTYuUJS7Ccb7Z8d65V6rIVDo%2BeonqWgAXiCHCG7yO803hvusHVpibumuOhuM9xbFHXzMXw646%2BdtnYn2aHbuwjJGzAedQ8Vjeyna4xDo6Nhjf3wvth0xOqbpX0R9c27sGLypVT2pBhl0TVr1KSrjUjgbDIQeqfU1j77STtMcYFvDwz4b7tuxjcuqVGO3sbudZZV1nJt0pZ%2ByOIQXhUgHnQLCL6vmAe1oF0LkXSH8z1pw1RQ68nFMMi4BoQ4KQHhgA4IcLXdkFUU7rIGPWTB6EwpQ4943puvF70TZo0LGgGRmBCfKsE1kSmha4Crh3%2BDXtRusq8qkoWndUi1zrjgzvu2jesimrTdZpdi9djG0X1EdZG%2BaKbt3VnvSIYV6TqpTnjhwS%2BsrAHL5HDIGI5JeIBAIDzHQNZBQ3JK8q3xcn3q7jJf%2B2F23/kaxY8e13PwJeI11LIjL/vZvShWi%2BgUAgduDw5%2B2tjqgfy0L/Q7j3H7JQ9fFTNHL5P6vteCD15AI3tgzfMvcSDwyUPuv8HwjXW4dsHuvchN90/q/JHvduGD1ZEAJTHJs9cNms/9bIMsdElsQC6t3R%2BdBcu949qIDQJQ%2B9HNLQb1AQQQ/16gBBnQz0L1kMZxf10CD0704NHgng0IVEEFyNi1aCbt9NZ0eMGobhiBgBfoAUKCt4GoWdqFsd5s3E8dqYnQWC2Dk15dwdudyd89YdgFssjUEdGCI1WDMVbhsVOCqCzMpV1CsJuDjdH8RDylOc8NedHgEDWxzd8k283NU9Ld2k/AQAbUGRtDMAXdUCRwtRi9S898J8q9Wgj8T8z9MAL85UrCuA7xYCpce9kD2YOANhaBOB/BeA/AOAtBSBUBOAn9LBrBO4tgdhsIH0eBSAsEUjYiNgMIAhJB8QNAAAOMwMwAATnqK4H8BqOqK4ENENGkHiI4EkF4BYAkA0A0FIGSNSPSI4F4AUBACGOKK0A2DgFgBgEQBAFalSGsXIEoEYToHiEiG5E4FUGqKhFWihEkAeGAGQGQAeCkHxDMF4EPEIBIDwHrzCP4EEBEDEHYCkBkEEEUBUHUBKNIF0DCPvEKlSE4B4DiISKSM0F4DGII2sVWJojon2MOOONOPOMuMqP%2BwgG7FSC2N/gKLWF4BmNiNIAgCQE2PoDIAoAgApLGGACkBSBoGoniEmIgBiGhNIBiHCBaDZDBN4C5OYGIDZAIxiG0HqGKMKN9hbAI2bl5P%2BKwBiC8GAG9CXkmO4F4CwBYEMG7j2FSPwB3AaDzjVNSMwFUHqGsT2EKPCGJG6NSP2xiEKiFI8CwA5LhjwH6PVNIDzmIAmSUFtC1KMH2yMGhI2CoAMGAAUHegC3vEY2SMKJeOEFEHEE%2BITJ%2BLUA5MBP0G1JQGsGsH0DwBiEmMgA2BXz6DVNWjr0KVMCyMsCSBhO9N1CwCLIgA2DqDyhcGjhmD8DCNCCWAqCqD0CKCyAEC7MHIyGHIYGGH7LGDCLbL6AGGmE8A6D0DnMaAWCnNGASFnIWFHO3MGA3JigkFbNyN2CPP0EhOGI5LGIeGRKOJOLOIuKuKxNwHuPxIpC4EJKKJDI2GPARDGBbNIHKMkApHxHqIpE6I0EkDMEkBhA0H8ChHqPPJ6L6JAHfPxChC4ChGqPqLaKhH8EkGaLAqhEvP%2BLGImKmK/JKLmMWLJOWPhLWOpNpOIB2LYE4BaBYFQkNFWkxClHUi4HqPxC4CqNuPwCIEbL0ATLeOTOkFTKUHTP%2BN0BSGBIQz5IhI4ESJItGM4DhIIARL/CRIOLvIkj4oEqEpRGxP3DxMhAfTME/OJLmPJMsspPWJpKcrGF4vpKaKGKZJ/lZPZP%2BIFJ5L5M5O5KFJFLFIcGCqlKVhlJbg5IVKVJVIUmCs1O1PEHlOvHFLwCNI5NNPNOJGCutJ6A5PtMdLZGdN1KJN1A9MKO9N9MwH9LSq6hDL4HDMjOjNjOCskqTI%2BJktkDTL%2BNSMUqzODOrKsEsHzMLPgBLK/WyHLMrO0jGusDrLSIbMeK%2Bmmu6F6GyA7PcCXPyB7OjgPIHLCKHL6F3LSHHL6GOpnK2qyoEAXLaH2u7Lurykepuq3MmEGAupfFaA%2BrPIUBPI%2BLUo0pGJhM4BvMMtRI8suNMqqIeAgBfLEusvfLsu/NIF/M2koDUt6NIH6IpAEsgsNH8HqI6IpCgpgoIs0vBvGNsAovstJJoqQBWIYo2LcuYt2I4HYtRJYAUFQguNQn4vxDjHmBEtfMeIktkCkt6q%2BPkDksGp0FQtIGUtBPVJBqhNIu0vosRJvJ5r5oFqFpFvzAsteCsvMApApDRqotJMctNucsYvZpAH5sF2I0FvqOIyNuI1UGOL4DoF8soH8tSMCqFOCuDuFNFPFKiv8RitlPiswEVOVKGjVMKNSsDMqtIH1Kypyv%2BLyuQAtMKsEGKv%2BNKp5IqtdOquCrqv9kasDOautrDMpXaswBjLAi6qlp6okD6u%2BPlozKVoMFGtzImvtObJmrLM4H2DrxzJrIsBWsmXiEbI2uLNer6F2out7PKE3LHI1RyGeq3onP%2BtnJ6Huv6B3N3sPu2oevXL7M3r3MXLyBet%2BsWA3sPI/M2G2FPNfu6NBqvIhu9pON5v5oeDduFrpHmARqRoinNo/KJPRsxv/JxpQoaPxAtsCEgtVw0AtsNCwuprSM4HIumPRqAv8FAvaMNEGOqMkCaK4FqLMGIu6IpA1q0tpvsrUpuJwbIsotmI2G9MyGcEkCAA%3D)

## Links

- [Example](../../../code/facilities/metafunctions/roadrivore/classic_trip/implementation.hpp)
- [Source code](../../../../conceptrodon/roadrivore/classic_trip.hpp)
- [Unit test](../../../../tests/unit/metafunctions/roadrivore/classic_trip.test.hpp)
