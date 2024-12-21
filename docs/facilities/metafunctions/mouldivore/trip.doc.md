<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::Trip`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-trip">To Index</a></p>

## Description

`Mouldivore::Trip` accepts an operation.
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
-- Compose with Mold
Trip ::   template<typename...> class...
       -> template<typename...> class...
       -> ...
       -> template<typename...> class

-- Compose with Page
Trip ::   template<typename...> class...
       -> template<auto...> class...
       -> ...
       -> template<typename...> class

-- Compose with Road
Trip ::   template<typename...> class...
       -> template<template<typename...> class...> class...
       -> ...
       -> template<typename...> class

-- Compose with Rail
Trip ::   template<typename...> class...
       -> template<template<auto...> class...> class...
       -> ...
       -> template<typename...> class

-- Compose with Flow
Trip ::   template<typename...> class...
       -> template<template<template<typename...> class...> class...> class...
       -> ...
       -> template<typename...> class

-- Compose with Sail
Trip ::   template<typename...> class...
       -> template<template<template<auto...> class...> class...> class...
       -> ...
       -> template<typename...> class

-- Compose with Snow
Trip ::   template<typename...> class...
       -> template<template<template<template<typename...> class...> class...> class...> class...
       -> ...
       -> template<typename...> class

-- Compose with Hail
Trip ::   template<typename...> class...
       -> template<template<template<template<auto...> class...> class...> class...> class...
       -> ...
       -> template<typename...> class

-- Compose with Cool
Trip ::   template<typename...> class...
       -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
       -> ...
       -> template<typename...> class

-- Compose with Calm
Trip ::   template<typename...> class...
       -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
       -> ...
       -> template<typename...> class

-- Compose with Grit
Trip ::   template<typename...> class...
       -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
       -> ...
       -> template<typename...> class

-- Compose with Will
Trip ::   template<typename...> class...
       -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
       -> ...
       -> template<typename...> class

-- End in Transition
-- Compose with Mold
Trip ::   template<typename...> class...
       -> template<typename...> class...
       -> ...
       -> template<template<template<typename...> class...> class...>

-- Compose with Page
Trip ::   template<typename...> class...
       -> template<auto...> class...
       -> ...
       -> template<template<template<typename...> class...> class...>

-- Compose with Road
Trip ::   template<typename...> class...
       -> template<template<typename...> class...> class...
       -> ...
       -> template<template<template<typename...> class...> class...>

-- Compose with Rail
Trip ::   template<typename...> class...
       -> template<template<auto...> class...> class...
       -> ...
       -> template<template<template<typename...> class...> class...>

-- Compose with Flow
Trip ::   template<typename...> class...
       -> template<template<template<typename...> class...> class...> class...
       -> ...
       -> template<template<template<typename...> class...> class...>

-- Compose with Sail
Trip ::   template<typename...> class...
       -> template<template<template<auto...> class...> class...> class...
       -> ...
       -> template<template<template<typename...> class...> class...>

-- Compose with Snow
Trip ::   template<typename...> class...
       -> template<template<template<template<typename...> class...> class...> class...> class...
       -> ...
       -> template<template<template<typename...> class...> class...>

-- Compose with Hail
Trip ::   template<typename...> class...
       -> template<template<template<template<auto...> class...> class...> class...> class...
       -> ...
       -> template<template<template<typename...> class...> class...>

-- Compose with Cool
Trip ::   template<typename...> class...
       -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<template<typename...> class...> class...>

-- Compose with Calm
Trip ::   template<typename...> class...
       -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<template<typename...> class...> class...>

-- Compose with Grit
Trip ::   template<typename...> class...
       -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<template<typename...> class...> class...>

-- Compose with Will
Trip ::   template<typename...> class...
       -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<template<typename...> class...> class...>
```

## Structure

```C++
template<template<typename...> class>
struct Trip
{
    struct Commit
    {
        template<typename...>
        alias Mold = CONJURATION;

        template<template<template<typename...> class...> class>
        alias Flow = TRANSITION;
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

- In the first example, we will compose `OperationA<Capsule>::Mold`, `OperationB<10>::Mold`, and `OperationC<'*'>::Rail`.

```C++
template<typename...>
struct Capsule;

template<auto...>
struct Shuttle;

/**** OperationA ****//* Start */
template<template<typename...> class Container>
struct OperationA
{ 
    template<typename...Agreements>
    using Mold = Container<Agreements...>;
};
/**** OperationA ****//* End */

/**** OperationB ****//* Start */
template<auto Multiplier>
struct OperationB
{
    template<typename>
    struct ProtoMold {};

    template<template<typename...> class Container, typename...Elements>
    struct ProtoMold<Container<Elements...>>
    {
       template<auto...J>
       using Page
       = Shuttle<Multiplier*Elements::value..., J...>;
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
using SupposedResult = Shuttle<10*2, 10*3, '*'>;

using Metafunction = Trip<OperationA<Capsule>::Mold>
::Road<OperationB<10>::Mold>
::Sail<OperationC<'*'>::Rail>
::Commit;

using Result = Metafunction::Mold
<
    std::integral_constant<int, 2>,
    std::integral_constant<int, 3>
>;

static_assert(std::same_as<Result, SupposedResult>);

// The following `static_assert` shows how the operations are composed:
static_assert(std::same_as<
    OperationC<'*'>::Rail<
    OperationB<10>::Mold<
    OperationA<Capsule>::Mold<
        std::integral_constant<int, 2>,
        std::integral_constant<int, 3>
    >
    >::Page
    >,
    SupposedResult
>);
/**** First Example ****//* End */
```

- In the second example, we will transport the conjuration function to `InvokeMold`.

```C++
/**** Second Example ****//* Start */
template<template<typename...> class MoldArg>
struct InvokeMoldDetail
{
    using type = MoldArg
    <
        std::integral_constant<int, 2>,
        std::integral_constant<int, 3>
    >;
};

template<template<typename...> class...Args>
using InvokeMold = InvokeMoldDetail<Args...>::type;

using Result_1 = Metafunction::Flow<InvokeMold>;

static_assert(std::same_as<Result_1, SupposedResult>);
/**** Second Example ****//* End */
```

## Implementation

Since every member template of different signatures is given a unique name, we know which member to pull out when asked for a template of a specific signature.
For example, we can compose a `Mold` and a `Road` in the following way:

```C++
template<auto...Args>
using Metafunction = Road<Mold<Args...>::template Mold>;
```

Note that

- `Road` has signature `template<template<typename...> class...>` and
- `Mold` has signature `template<typename...>`.

This means in terms of signatures, a `Road` can always be invoked by a `Mold`.

We will implement `Trip` by performing recursion manually, meaning the function will recurse only once for every invocation of a member template.
We will showcase a simplified version that handles `Mold` and `Rail`.

Note that in the following code,

- `Radio` is a `Mold` and
- `Car` is a `Mold` or `Rail`.

```C++
// `Radio` is a `Mold`.
template<template<typename...> class Radio>
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
           template<typename...Signals>
           using Mold = Car<Radio<Signals...>>;
           /**** Conjuration ****//* End */

           
           /**** Transition ****//* Start */
           // Helper function for the member template `Flow`.
           // This function transports the conjuration function `Mold` without invoking it, 
           // allowing further process by other higher-order functions.
           template<template<template<typename...> class...> class MoldVessel>
           struct Detail
           {
               // We transfer the conjuration function `Mold` to `MoldVessel`.
               using type = MoldVessel<Mold>;
           };

           template<template<template<typename...> class...> class...Agreements>
           using Flow = Detail<Agreements...>::type;
           /**** Transition ****//* End */
       };
       /**** Commitment ****//* End */

       /**** Continuation ****//* Start */
       // This function composes the conjuration function `Mold` and the `Agreements...`.
       // Note that even though `Agreements...` is variadic, it only allows a single argument.
       // This is because `Agreements...` will be used to invoke `Trip<*>::ProtoRoad`,
       // which has only one parameter `Car`.
       template<template<typename...> class...Agreements>
       using Road = Trip<Commit::template Mold>::template ProtoRoad<Agreements...>;

       // This function composes the conjuration function `Mold` and the `Agreements...`.
       // `Agreements` will be used to invoke `Trip<*>::ProtoSail.
       template<template<template<auto...> class...> class...Agreements>
       using Sail = Trip<Commit::template Mold>::template ProtoSail<Agreements...>;
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
           template<typename...Signals>
           using Mold = Car<Radio<Signals...>::template Page>;
           /**** Conjuration ****//* End */

           /**** Transition ****//* Start */
           template<template<template<typename...> class...> class MoldVessel>
           struct Detail
           {
              using type = MoldVessel<Mold>;
           };

           template<template<template<typename...> class...> class...Agreements>
           using Flow = Detail<Agreements...>::type;
           /**** Transition ****//* End */
       };
       /**** Commitment ****//* End */

       /**** Continuation ****//* Start */
       template<template<typename...> class...Agreements>
       using Road = Trip<Commit::template Mold>::template ProtoRoad<Agreements...>;

       template<template<template<auto...> class...> class...Agreements>
       using Sail = Trip<Commit::template Mold>::template ProtoSail<Agreements...>;
       /**** Continuation ****//* End */
    };

    template<template<template<auto...> class...> class...Agreements>
    using Sail = ProtoSail<Agreements...>;
    /**** Define Sail ****//* End */
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGE6a4AMngMmAByPgBGmMQgAMxcpAAOqAqETgwe3r7%2ByanpAsGhESzRsQm2mPaOAkIETMQEWT5%2BUpXVGXUNBEXhUTHxiQr1jc05bcPdvSVlgwCUtqhexMjsHAD06wDUJgBsGgBKTPioexpbeApbTDv7ALKe6GcAdCYaAIIEmCxJBl8mcTcXx%2Bf0wAKBAE8koxWJhnvCAdgtsgDAorkcToi3u9hsQvA4tgAVYh4JLYkwAdisHy2tK26wAVEyGVsACKYGihLYHVDHLbMhmbFldRr89bYun07ZnNwNM4XK43M4PWhPfavGl04G/Jj/QHa0HgghQmFseGvOJIlFMNFbWXELGa2m4/EELbKYioIg844SumU6nvSV0xnMu2oFgsQhsQT85lCrYit2Cv3Bl0EjyRwipyUBnPB2mhpnhhjaZa6jJxpkJpNi/MFza3Q7HJzywzoJv2tvETDIiMpJQdhAxOH14ONgBieGIw1IWwA7r2QpNBHhdb2zhjW/trgwO6hIvUQtcm8bocw2C8x5LG4Thww54uLgwAG6oADWG/2XZ388ICC2Ahhy2HsFC8WhHCMU8TQvMF1WvLVvh1PVIXPWFzSEPBgGYWgFEdIMC0lLw0iglUOwBVk7TlQEt1OQFMOwsQFHNLFLQBQNCJvAUSzLYgKwEKtBUZLZsD3OsPgQ2lJPpbjiUMNIagYQSaxGZNxSdTjGwACSqaFiC2KgvAYBxK34fSgN7NhShiQCkNBJsJ1oVB5yvDTCNvBBLgMoyTIEgg%2BIYBQUkaK4LL7Uty0U7zjKi5VHnlP8gKWN0Qjfd8QmAC4CDnaTGzEJy/ygwzGmHfSkk9VZbUiCEti9Uqtk84BSoAWhILB9MMmKMmY6SDXXI07P6/VBpQs9TThBFLWRVFmMmq0Zq2MiADVMDRKp8M4ul0zddkj1oaS8zczapS2AB1Xt/PkqgbLCtAIr4qLOt8pS4tVeUiCbZbVrsVyCOOuliIywCTR2OJKK%2Btb9sBMjWI447KVZdjySO4M%2BtGkawWGkEhtQ8aWKm600Xx%2BabVm553mAHtvkYAg8LYlGiJIzLHOc0HKN2pg6HBCmqZjWniZAEAxqRhmQ1kgKFMrAUE1EjsUxRhGRb%2Briw0zKMCD55ThNl8T3jHIsWQ8VcGC8filOl4Ta3l5WQ22O8vKeqK0B%2BVJVsA4C7t4s3ouez74p3dt3a/D5KcwanBDJ373O2MIvQuhBdS2TAX0Yd2liapsebDvnI53LyXwaNd8GQOdCFqhhaBq/LnMVLYmfoa5iGAHwaY1G3Cztzyri86JRGI4Os/D/mEV/OhaC2aItn7jsPtSj9g%2BJUlwQZRFBY9L1UB9NUNFIfXtnnTzkAAhOrgESvy97JIGlhL59JlOV4JRtHMaBDGjRg9C5um0nzUHnONoLIDKCW82ZEhJGSQEatCCC2foteKloYEY3dJ6b0vIniAj/jTSObE4iBj3kSLuPsnb9ldqFD2AgvaPR8rFe4/tziBzCmcTBEcWKP3bidJhoch54VHrQcek9p6AVQM%2BNKC9wHL1XiAdeRAhCc1oG3Qiz8BrY3Riol%2BTAvBEGJt/ImX9CZk2YbTABwYgGZVkXQUBi8IFuCgQQRBai4FvQQULJB0jUDmKhm4Qx2DsBK3ctxI2kFTZRQtiyHW1tcwUkRrg5GyslFY2Qi/MasFtH6N/lw/%2B9NlamO5Gg0Bbit7cwyVg4mfixZhnZJyXsIDQkiTEtbHMBs2QchCL2DxWthSqV1jeTuDtqGVi8mFNIUYDDmWAmcApaD5RYCqR2JgkRUApwUbbLYABJN0Cc9z0DIb2UQSgFylWDj%2Bc4XklT7COFzNhkp4mvzUcoxJ4INFaL0TNVJC0uxZMlNtZBG8PE5kOuwpptjNa1Ktupdh3zbFjgBf9IFFDIpS3jJbLpETjo3OSZ/Z4DEcJ018aLWkOSyKgI%2BW4Wi4JsVMQFi4hxygmDAExr4mJ%2BKZKq3hQ9RF1Ztb1PBblcW8kCjmyRZ07o3S0VvwSYaCVOMMVmheT/OVtoIY/U%2Bcdb5HMubMphf9AlTNgbQlAUq9a0N4GMrhptRWTK9bMvReK25Dz9Qf1lRaEmujnU6IMcUiOxjOI5JZvOUB6rPHeKpcLS1sK%2BWBQFR0upctwWEQtWalWxZgU02jeEnlKM4XG2CRyoSwrRSotRra9FjqJpurSfCbx3qAa6pARRMBS9IERnVvYxJjj0HYFbfZSZvoMGeuHs6pWY4bV3KlShJ5qA3nyvLa8yt/bcVjhye0%2BtVjwS2K7eudtkjYFuL%2BX23mJS5plPHAE2QIQc0CVqem/5USh0aRHfau1krZSaMnQqnx7r0kHq9SqnVQNl1gx%2BTIuRRTv0Dtho07ilTWmJjkWm7l5Jb2WuxAbAUaHqwodkqtWmylMPofww0iSZg4ghBRF4LAoM3CaLoIQCE%2BFsQlrQk6/CkKmBJDAvQO9nxbUTtKR8b5QgECaIIJx5DHwmkAHk9JmyDKClF4KH3PplWWxE7qSxHlCA6LJ3ypMxBk4hiwOx73FtLV%2B7OWDvWEseMS2QnNNOgfMywo9yGkOBkk9JxSsmhUxt1nh4sun2UCEM3JkV1sbkTsWuBRwvw8AxBY/5V0WwAtmzwVSHMjHxreu%2BW4oleZXOxOucWkzTGVME3ebZ1pZA9V43hNgegmS8XK2yyg1AMMm2CDs3FwEdXuGlN/TsNLT8eOvvNAAKWrX%2BqCtL6XQsA4J4Tom3B3Ci6SWgsXiAMh6znQWBdvBlrnKNvriaE0FcQqO3GKS51gYXRpKzqp8ktba14%2BdR3EPRLc9xZLilgveevRJcTn2PMZDcNGsFDHhsfSWoXeZonGs6aBwINwBn0tFfO7x99iZMAAEcvCMFWFlhLBJA03sTYzIGY1QFCGx7j4yL8ockhhwy49A33undpIpnG6OZ3Tqrf1nJFzx71uJ/uxz4HnGhtS6zgHYYvvA/g7G2JTSpwzjdNgVQrBfi9hCwW8FS6vBJAHJgdABxVpRcp0JggImX5cA0AyMwc4bcMjiHOMAHAGSu4g/994hLMD1EdpWFd4jASy4EHrSBbGOMMsFm1xrgtCnB4RwwKwgIbeSJj9iQWe63Ah8yOCV37uOCSIF/hQWUKxPe9rabiCBrfdMH984EAMMJKAhzMMdAgsQhfEpmIAA%2BndFcBBwSd7nGYREu8NJt474ITA3faB94EAPofgg5xxHozgvB/H6iOGQD30mMQCAQEnyABQsJd901JVX7KiZ9eG%2BN5fxEcwuMeV7PwPhzkgZnEmNvs/ShGjygUAgDXA1KzGFKgInoqD2H2C7IOCANiF/ngDvnvo0IfgQO3sfqfjaOCDmDnkjoCPnh7s4sXi3hpDnsnm4Kns4k9tgYnmHjYhHuBFHo3vAkjgzEfp3jPnxHPv3vUIIEvlfqPpaOPuwnXKgVPl3pwfPoFDwYPoCMPlsKvv1t6pItNmCBpGPjmEIDfq7HfhxoPs3tgI/pakrtOMMCJOriCFrr9ghl7k0lTndB2Grhrg3NrmpODudhlpdtzoqo8O8E3PFniASKsq%2BPPGRMThJINtkrqhTvWmRL4cAP8sQcIWwdPrPpIYvrIcvlsAIdgEIZxMkeIb3twYYDIW4HIQoY1rmOvm9lxhzqNKZu%2Br/E3DdhXkDEEaIrloBm0SEY8MLl4k0SGiaFxvzpfj3lwDXn7v0g3n6uCF0Z%2BOnuXvAYgWtMgUfifmwGfuCCbroaMXOJoQbtoVsVFg/krLYZgPYWYU4ZYZymEtyhwAsLQJwAAKy8B%2BAcBaCkCoCcBI6WDWB1xLArAbjEY8CkB2JvF3ELDvggCPGSDPAaCSBcAUhxAaCPEaBmC7C7BmAAAcmJ%2BgnAkgvALAEgGgO8rx7xnxHAvACgIAO8oJWgCwcAsAMAiAIAyUSQmi5AlAzsSQdAMQYQsInAqgmJuwzUuwkgWwwAyAyAWwUgzwZgvARuhAJAeA7eiQ/AggIgYg7AbQap8gSgagmgOgeg84fESQnAPA9xTxLxBpHxnAEmmibJboqAVAWwgpwpop4pkp0pMJZgWwEAmY3J9Ad8QJcwvAtJdxpAEASAXJPJZAFAEA0ZgZIAwAUg9uNAEEMQVJEAkQ1pkQIQDQEIZpvAuZzAxAEIEmkQ2gZxoJwJzsfMEmFcBZYJpAWAkQXgwAsofCVJ3AvAWALAhgwA4gTZ%2BAPYJkKcXZ7xmAqgZxmiawwJ7BDxTZa2kQfEpZHgWA1p/keAhJ3ZpAKcxACySg7IfZRga2RgBpCwVABgwACgS0sW84umrxwJOpGp4g2psgigKg6gTZugiQBgZ5pgPxlg%2BgeAkQVJkACwYBikXZzUbeFEAFVglgZgZJe5JIWAYFEACwdgVZGQLge4YwrQpAQQrSMwAwiQA4Aq%2BFeg5Fik0w/QsQQwVQ2FtQqklFDFHQzFUwxFdFegkwowngLQPFqktF1k9FmF/xqwEgFpHAzxpApJvA5JLpQpIpYpEpUpMpPpEAuAipQZCQIZIJ55Cww4xwAwGFpAkJkgcQzwAAnHEBSJIHCWYJIPsMibsFZbiRwPiaQISQkM8LsFwLsJiVZZif5dCVwI8TZbsLJdaeSZSdSfpWCfSUyZGSyfaeyXGQmbyfyRwA0CwC%2BBSM1DcNaFBFwFZc8FwLCfKfgEQKhXoM%2BaIK%2BdIDqR%2Bfqd%2BSAPbsaWxoWVJTJXJTaRwHaQQA6bVM6TlXlQVd/MVaVeVecH6f2DGTsMRmYHpWGfSVGXNYGRyfGetQMKNflUVcmVZTbnwHQLfJmdmU2cWfmYWaQJdaWeWZWQ4NdbWTTPWZXNaS2W2R2bhNdb2f2YOe8cOdhWOdaZOdOV8NdfOdaUuSuRCGuWsO8ZuducCXuQeZgEeX9RlOeXwFeTeXeQ%2BddXVZqbkE1XqV%2Be8boPbn%2BcYNYNYMBaBfABBUkFBZwDBagXBTTYhchTEKhatAze0ExX4BAK4KxYRXuMJbMGRfkIpCLdRRkOLaRfzc9EmCLVhUrUJVxSJYJd0CrercUNxVwGJcsBJQbe5T1dFZwI3LlflYVVTdKVNbCb6VpdVQtbpaGQZaQEZe1JQFJZ5d5aVXCRSOFRSIiZII5aKYkL1TFbYHFStRGUlUgKyWlZydtcQHyWwJwDle6SwAoC%2BFKS%2BCVc8KCMMJVdpcqbVbIC%2BVqY1e%2BaTdaboM7h1aad2d1VaU2eSQNUNU6ZbVnTnXnQXUXW6LNT8PNeYHEHEMtVjclRlbGcncPYmbnQbj3vnVZT3gPbvsQCwKKcdemTOJQOde8bdY2cCYffdVWU9c2i9Q2e9ZgK2e2flF2cCb9SefDT2dOEDbzU2aDcgDORDdPgue8dDfmXDRuSSEjbwCja7OjSeZjQldjXSrjZgPeeeATRXfVVXTIIIM1WTYac7lTSgBzTYEuehYzczRsJPvBdYEhfJShcqbzeBYrYpLhe4PxeMKLegPLfRXkJLIjiwwRbLYUBrRLQw50CxbwzxYxWrZxXrZrUMKI9kARbxT0II6RYbQCZJaba3WSRbZnWKdnbnVsMvYXeuKYZpVVSQC7QbW7QlYZZgMZbEKZQub7W1aVWPY8SifCcSWPRSAFVFW3ZwLFTSe7eZY8dZY8ZiWiVZZIFZYibZVwLg5wHEJo/Jf4/FXSVJXKb41oxSak%2BCbuRmThZIEAA%3D)

## Links

- [source code](../../../../conceptrodon/mouldivore/trip.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/trip.test.hpp)
