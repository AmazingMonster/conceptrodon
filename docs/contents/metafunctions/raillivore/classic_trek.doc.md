<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Raillivore::ClassicTrek`

## Description

`Raillivore::ClassicTrek` accepts an operation.
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
ClassicTrek ::   template<template<auto...> class...> class... 
              -> template<typename...> class...
              -> ...
              -> template<template<auto...> class...>
       
ClassicTrek ::   template<template<auto...> class...> class... 
              -> template<auto...> class...
              -> ...
              -> template<template<auto...> class...>
       
ClassicTrek ::   template<template<auto...> class...> class... 
              -> template<template<typename...> class...> class...
              -> ...
              -> template<template<auto...> class...>
       
ClassicTrek ::   template<template<auto...> class...> class... 
              -> template<template<auto...> class...> class...
              -> ...
              -> template<template<auto...> class...>
       
ClassicTrek ::   template<template<auto...> class...> class... 
              -> template<template<template<typename...> class...> class...> class...
              -> ...
              -> template<template<auto...> class...>
       
ClassicTrek ::   template<template<auto...> class...> class... 
              -> template<template<template<auto...> class...> class...> class...
              -> ...
              -> template<template<auto...> class...>
       
ClassicTrek ::   template<template<auto...> class...> class... 
              -> template<template<template<template<typename...> class...> class...> class...> class...
              -> ...
              -> template<template<auto...> class...>
       
ClassicTrek ::   template<template<auto...> class...> class... 
              -> template<template<template<template<auto...> class...> class...> class...> class...
              -> ...
              -> template<template<auto...> class...>
       
ClassicTrek ::   template<template<auto...> class...> class... 
              -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
              -> ...
              -> template<template<auto...> class...>
       
ClassicTrek ::   template<template<auto...> class...> class... 
              -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
              -> ...
              -> template<template<auto...> class...>
       
ClassicTrek ::   template<template<auto...> class...> class... 
              -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
              -> ...
              -> template<template<auto...> class...>
       
ClassicTrek ::   template<template<auto...> class...> class... 
              -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
              -> ...
              -> template<template<auto...> class...>

-- End in Transition
ClassicTrek ::   template<template<auto...> class...> class... 
              -> template<typename...> class...
              -> ...
              -> template<template<template<template<auto...> class...> class...> class...>
       
ClassicTrek ::   template<template<auto...> class...> class... 
              -> template<auto...> class...
              -> ...
              -> template<template<template<template<auto...> class...> class...> class...>
       
ClassicTrek ::   template<template<auto...> class...> class... 
              -> template<template<typename...> class...> class...
              -> ...
              -> template<template<template<template<auto...> class...> class...> class...>
       
ClassicTrek ::   template<template<auto...> class...> class... 
              -> template<template<auto...> class...> class...
              -> ...
              -> template<template<template<template<auto...> class...> class...> class...>
       
ClassicTrek ::   template<template<auto...> class...> class... 
              -> template<template<template<typename...> class...> class...> class...
              -> ...
              -> template<template<template<template<auto...> class...> class...> class...>
       
ClassicTrek ::   template<template<auto...> class...> class... 
              -> template<template<template<auto...> class...> class...> class...
              -> ...
              -> template<template<template<template<auto...> class...> class...> class...>
       
ClassicTrek ::   template<template<auto...> class...> class... 
              -> template<template<template<template<typename...> class...> class...> class...> class...
              -> ...
              -> template<template<template<template<auto...> class...> class...> class...>
       
ClassicTrek ::   template<template<auto...> class...> class... 
              -> template<template<template<template<auto...> class...> class...> class...> class...
              -> ...
              -> template<template<template<template<auto...> class...> class...> class...>
       
ClassicTrek ::   template<template<auto...> class...> class... 
              -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
              -> ...
              -> template<template<template<template<auto...> class...> class...> class...>
       
ClassicTrek ::   template<template<auto...> class...> class... 
              -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
              -> ...
              -> template<template<template<template<auto...> class...> class...> class...>
       
ClassicTrek ::   template<template<auto...> class...> class... 
              -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
              -> ...
              -> template<template<template<template<auto...> class...> class...> class...>
       
ClassicTrek ::   template<template<auto...> class...> class... 
              -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
              -> ...
              -> template<template<template<template<auto...> class...> class...> class...>
```

## Structure

```C++
template<template<template<auto...> class...> class>
struct ClassicTrek
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
    struct ProtoRail
    {
        using type = Capsule<Sequences<Variable>...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
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
using SupposedResult = Capsule<Shuttle<10*2, '*'>, Shuttle_1<10*2, '*'>>;

using Metafunction = ClassicTrek<OperationA<2>::Rail>
::Road<OperationB<10>::Mold>
::Sail<OperationC<'*'>::Rail>
::Commit;

using Result = Metafunction::Rail<Shuttle, Shuttle_1>;

static_assert(std::same_as<Result, SupposedResult>);

// The following `static_assert` shows how the operations are composed:
static_assert(std::same_as<
    Send
    <
        Send<OperationA<2>::Rail<Shuttle, Shuttle_1>::type>
        ::Road<OperationB<10>::Mold>
        ::type
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

Note that in order to succeed, `Rail<Args...>` must be a packed `Road`, meaning it is of the form `Vessel<Items...>` where `Items...` all have signature `template<typename...>`. This requirement is not checked by `ClassicTrek`.

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

- `Radio` is a `Rail` and
- `Car` is a `Mold` or `Rail`.

Here is the entire implementation.

```C++
// `Radio` is a `Rail`.
template<template<template<auto...> class...> class Radio>
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
           template<template<auto...> class...Signals>
           using Rail = Send<typename Radio<Signals...>::type>
           ::template Road<Car>;
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
       // This is because `Agreements...` will be used to invoke `ClassicTrek<*>::ProtoRoad`,
       // which has only one parameter `Car`.
       template<template<typename...> class...Agreements>
       using Road = ClassicTrek<Commit::template Rail>::template ProtoRoad<Agreements...>;

       // This function composes the conjuration function `Rail` and the `Agreements...`.
       // `Agreements` will be used to invoke `ClassicTrek<*>::ProtoSail.
       template<template<template<auto...> class...> class...Agreements>
       using Sail = ClassicTrek<Commit::template Rail>::template ProtoSail<Agreements...>;
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
           using Rail = Send<typename Radio<Signals...>::type>
           ::template Sail<Car>;
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
       using Road = ClassicTrek<Commit::template Rail>::template ProtoRoad<Agreements...>;

       template<template<template<auto...> class...> class...Agreements>
       using Sail = ClassicTrek<Commit::template Rail>::template ProtoSail<Agreements...>;
       /**** Continuation ****//* End */
    };

    template<template<template<auto...> class...> class...Agreements>
    using Sail = ProtoSail<Agreements...>;
    /**** Define Sail ****//* End */
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMxmpK4AMngMmAByPgBGmMQSABzSAA6oCoRODB7evgFBaRmOAmER0SxxCVzJtpj2xQxCBEzEBDk%2BfoG19VlNLQSlUbHxSdIKza3teV3j/YPllaMAlLaoXsTI7BwA9NsA1EJ4LCm0eDSY6HsmAGwaQq43GntUXgwOWQB0JhoAggSYxwM/xM/jcBAAnilGKxMHtlExkABrC4ANUwCjsIOw3x%2B42IXgcB1cVwA7FYSQAREFWX44/6ApjA0H0k6MzAgsGQ6FsD68rF7ZAGDF7DyCJjheKkPYQqHMHm87D0NiCBRYnF4gkEIkMdAc0XNCXEDmKgGMAgKXlffzY604kxknF7J3SgGsplg11A9nMrlyzCW/mCpjCgDyUOIjKyat%2Bzr2GsJFMwBtojuduz2AEkGAA3VDIq63MPxSMCR57ADuhAQ0oQsMeJuV5oDty%2BMed9osey8GSM0q5V38FL2RYjDWNSrNFr5tv8nftVNndrbTpZXo5q7Z699MID1oFQqnHx%2BwGImFNKujP1j3fCwD2ACVUExLiCh4nkxzj6fz03p9gQCAMrejSPzztSS5/J6m7MlB7obu6TBeEQu7YPuwaHoGB4HEQSLEKgqAsFK8Hem4iHIX%2BaEYpa9wAI5eIwmyqravzxlq9w6hyTSoLh%2BEsJxmB0Qx6IoZeHapiusEkcR66SRyZGoChlEYXuQahuGJYMJesasXs77iimy57OmWa5vmjwjhpZaVgQ1Y2XWty0fRbzCXyLbiaSnY3r2QEDkOFljqCjlCcpNpzpS4G0oZ0kwQycGyaC8mKapIVKZaX5no2THYoZXl3kI%2Bm%2BbpSb6Z%2BJ4ZZOKEAUBEWgeFi6RaBvzpo897Pk4ZZ4AoexMAWGitXQjytpBsVSfFHojXJSEKRRyVJVhrX4Kgl46W4B54MgAAqp6InaDqGdsABUR0HUVNARA%2BT6XMdB27CdfStHsN3uc1tykUatx7J13W9QAsp4upuVFY3RZyso7jNWFvVpzo6coeFEI%2Bz7uWJhlptdIoESwhCNo9x23dh/SPds7kwwQ%2BKEh4LBYwQJNOijV6xozRno6K2jrBpuNHfj91ak9qNMy9fVtUtH2GC%2Br0tGWLSwmgxzpBcey1qeQ1M4zIMg4lEPodReDAMwtBZbTjO5Q%2BBWvtquo%2BmDbCm4tnG6/rIVVVy0Oq06VWSRdSOglDM4gW7aPHRjDBs6OWSczdh17NgOpExBAd0/zjOHUHW2GEU4fXdzEy88TSexumAASdThs8rzvAIzwkDWsJsBU8QuiNvWFyVgMMwH6YbQgX0vG8DTShGDAKGkrRdXZAoCKHHO9xXDC9f1KYfdZCBrFq4Smben0EFKRsF/sYi0Kgla9i8rRK3sKR4YxXUxOCeyoHZxCK7rSsALQkFgT8zw0Fq7866vA0ARNBKU05ray1lRCBXUF5ogxHUV2bsdJ6QGvndse124JydOmAA6rCMm6cqAN3HmgEO7N%2B7f3Di1VuTwiDz30rAzEbdMHXh7HeHy5sYHokxKCBeap6oYNVmBfhf8JLAPGm6UaYiNagKgWAyBVpUKzV5OlH8htUFOhNi3OghVkEplBCozKlVAIu34ZglOR09hpyHpkSuWco4xyunnARdM6r%2BwFizTG2MzQR3xg4uODVVbmJOvqcIXgOZ2LujnfxzijL7C7j3cu/dZaFHRDXCepCw6VwoZXKhA1Rax3Ho8AxFVXIaBVgLfYkQH54IQIyPYmBsyMBrGsYA1YillVUc2J4X1swtDwG1ZAUpCD3wYLQO%2BB8j5dR6qw%2Bg3ViDAB8Gacpyc4ndy6l9OIohuz2V%2BB0wxpSKx0FoHsOIXYlCXFoevPMOzVroXWltTAO1QRGLhg/VAiMAYaFIEbdM5Zu7IGrLUrqAgxkjNhCkFoMJ/hP0eFDJhTMAFSO3PKBRqVlF7MnAg50JsPmFVuRie5209SeIIB7JuvDrRkokXCeG7zLqlW/PshRNUfmrISX3cOyT5Zj1rOkqe5DEmUNuLw/JFzeXtMZSUr48KVm9WKReJeRyTmwm2Rc1An0czXN6vijIm0iXPL/ABV5RB8p0GWbGRFEiZJiM1qipRdqDxpQxReZiMSTamuOebHVhLHnEqpoQKlXpTYDUpYBT2xrUAeoZeVFUIlTHuKDiEhgYT%2B4ROjrHPmGChEgXcpatcVtuT%2BlkeiyVLrsoYJxZdQqEaPnRs6X%2BGqBd0aJjOrCXFaa/GZues2zAraDgFTTTzaJe9LFrLLhyyuX1x4ZCxgYJ%2BhTbg1vpR9LArbLhMBiKgRp5rjJalqTqegPKZbBlhH8%2BINzJYfS%2Bj1XJi8ym5qAVamKT7SIyIdeA99wpfblu0mTTUNK3lRsMvTQJHj/UEBxoOqJmbVYrRJUbEDCcgnB35ZnPGUch0wYTnm6Cr7yKfsPIcPWYg1ExJYZvBehV2KW1BoW227VAoOxI0Y6qrrMGBrZP2kNbhv2NqQx4jJ4T0MnU7U4kRzNU6DwzrY4TBMHpYYDjhuKUixq2swh%2B9T8jNPQPoVw%2BBbGE5IOKigsjaC3HMJNuwwcwbaAMP024CloVxPZvjthx9%2BbxEeekfh7TciUr2vleaLFTNNFm2s7outTKsTOyhHxju6MrHSbnh2jNTjBGuJ%2BWB6mkHZOidc8nATjhk1Ca5hh6DaWEXudw0BP0fmnWlqCwZ42rCvYvms96vVvqfYko4/8Gz0Ww1NyXd7NwgWQosqTkpyRL61MqUdcWo8zrGs/pCy1j1eK1qdaeTxnrg3qWOd67CCNUb9FLfG/GgribZChJK5HETqXkYZYCf/KrymZtvt8wtsbCD3VhaHMdkqp2GvnfMxJixLaJRceOSlxxu0Fw5qatdJHmbzEbWwEIDaeMcRBOR2J2kZh/DhEFF4LAA43BIToIQcEolfjeemsylif7CRCAQEhAg9AJvDXez511OkWds/oAAfS4Jz9WyKi0M9xEzrUpEUgKC8Bz4RtPXskVm4o%2BbkuVotGIHgeInPkP%2BSyFeKDhNM1072CiPpG7Fflp0obgQjVapziBipm1H25sfqCs5Ujv7yZahrSVYD6C3aWf7F6pgcuFckS94xDkludfW%2B9NgONoOXPPdES%2BundWS0xuW%2B5HFf2AMI0B6Ns7Ke4c1QN%2BpBoxvcsPYalX4sDROwm/k0483P0FeOBOLro0vPpfDmr1kHNweXtIuthLhBRnkweTT47i1KvJo8/V%2BhIkglnJSltRmKfA%2BIuBQEk5TYHIMxxpWy40HY/uf04AFLBbOZveEwA6zWZjyRTvtBu%2BnHiAdE/vIpTX/LyD3h3y0bkz3F3q1zx91Jj9yL1QD%2BloF1CDwv2xRaysyHDeh1z11BD31L2BwG2IjhCYCf0AKzSe3n0vy83AJz1UR%2Bxa3gLa3%2B1pXoMiylT4RH2AMRyDntwYBbzr1hwb3Rm4LcB8TK1N3b1UymgtytxiBt3VAHyEN2lBymyX3p0%2Bw%2BFfygKdGn0D1IOQI0VQLD3awj3l0VzcA0Lj2kJtxINjDnwfVdyv2z0WzwKa3v17Eo3NhwLGxYxMXYMr0EKHwEGEJh2iWx3RgADE8BiBxho5VBWAThYRW9c4cR3UvAUgUl0B7x0Qu88VjCo9OJWcCB2cSIuANADogg9gwAOADpKisQpR%2BdCihcRdQQSiyipRKjqiOA%2BEnMGoTYfpipsk54vVNsHlttuDQJQQzABtHMcQAJa1QRuCrBmiNABtmDXUAITs3AFDQR2iajQ1pjfgAJKZqZOccUsiP9Co%2BjmgBjZiS96iii6iCiijhc2CIJZhHBkBBd0J4gCAIBxh0AAIFAYRPimIHMzjt4DhUj0jMiTCaZrQlh9dVlYR%2BBaBD5j47xHg3j1pgSlBWgywFAV5ywuoCS0lUAAih45kZYCJ0iQA5DIwPivjWhfiCB/iQBAS2BgSOR3JqNkZQRd5uT5iyTxi3BJi9jbjHj6AHiBdMBnjQ1WMz9GZZj6UBSm9h8OQSiVj/o789gYt2RgMXD1iS8ti3AdjOjRSQ15TvlDIhBIT5YMiwS7Q4S/Cg4IioitRsBYjAQEi%2BCQjOCLF7gSFLh3S4jZlEjollDn0PM1c0UCMbMfh5lloB8TJrkF4ItaRR99DN40DYz4zApxTMBJSGjpSmjujaoODHdwzPNcMoz7U1C4zgBSMTYkzkR3DrMmzMAUzjM9FRt5knZjFYslcfhTiYThcLj%2BjBVnAQAtEuy2zpiBzMT6S4FGS/iASgTgwORoSu9hc6ibTzkNyP8sR4T%2BFkN/SBBAyPT4iRD7tHEOAVhaBOAABWXgPwDgLQUgVATgNwawawOMNYDYOsAnHgUgUlF8m8lYREEAe8yQD4DQSQLgEkfwDQe8jQMwa4a4MwRIRIfQTgSQXgFgCQDQL5Z81898jgXgBQEAL5YCrQFYOAWAGARAEAVeFIJCcgSgZJOgeISIGETgVQRIa4V%2Ba4SQPYYAZAZAPYKQD4MwXgC4QgEgPAf4rgGQQQEQMQdgKQJS%2BQJQNQTQHQPQcsCMFITgHgW8h8p8nSt8zgEMJCZirUVAKgPYXi/iwS4S0S8SqCswPYCASmFIDimFACpYXgKim80gCAJAdi%2BgMgCgCAcKkYYAKQIIGgD/eIciiAGIcymIcIFocEIy3gDK5gYgcEEMGIbQTABwHK0gWWRsEMUZbKkC0gLAGILwYAUiFE8i7gXgLAFgQwYAcQOq/AU8d4RpNq18zAVQUqpCLYQC8If4O8uq04GICMAqjwLAcysmI4cqxpYgTdJQRMLqowU4IwHSlYKgAweslEXXcsIsZ8wC/gZS0QcQdS26zSlQdQOq3QRSgwQ60wSwawfQPAGIciyAFYUkn%2BTgV%2BP418b6qwSwMwYizanXLAQGiAFYOwUqhoFwHUKYPwRS0ICUBYEYRSwoGxbITwDoPQImhoeYYYKoboNG3oHOLGvQVG2eHmKm%2BuGm2YSYUmvIRSzmgYPG6miQFG38zYIWrCjgR80gIi3gEihyvigSoSkSsSiSjyiAXAWSvy/wLgAKoCo6lYWsZ8EYZG0gcCyQfwD4AATn8BJEkBgrMEkFuEQuuAtvFpwtIDwq1o%2BGuC4GuESAtsSB9sgq4HvKtuuClvMpIrIoot1pApovotCsYuspYqipiuIC4rYE4BaBYGzBJFfh6iDF7C4Ato%2BC4GgukvwCIARr0CepUoeukCesUBevMt0CCH0ojxypMolrMrqpIqsoIBsvvnsqzpzrzrQkLuLtLqeC8qpN8quAJzMB1qCporCpnoitYuitXpGGHtzoLriotpKL4DoGhRSrSrqryqyvKvPoKqKpKrKvaoqsxjNGqrGXMoaqapaoNnKs6u6t6tfP6rpqGvMtGvGv%2BHKumrqHMvmsWvBGWq2FfLWrwvvs2u2swF2p/tvCOr4FOoUHOswEutlHKprvurUvrtkEbu0repACCE%2BuMC/MsD%2BoBvgGBpSFBo4HBuZMhroYsFhplvhvkvRCYdptngxvcG5uxuCB1DZsWEJvSGJsZpkaSykYJqEYaB5nkZUfprmAFvZqZoZrEd0a0bKEFu1tWHWFFpMdmsluloso4DmWztzvzpofEonugs8vVsrrnq1sXr1tIANs/koE7rdo9uLpgpJBDpJHgskHtsEsUuscjtsGjqXpCvjqQCYuTrYs3rTu4o4CzucpYAUGzDEuzCLo%2BC9HGHLo1vkurtkFrpIY0vIdetfN0H8FIDbsMvas7qsYjssqTtsqHuIBYDyYKaKZKbKa1GnuOFnvMH8H8G8djpCpXsmbXpTsyZAEKbSMF2KYtsFzGc%2BIGcEsPqSqiMoFPtfKvtqsAvOZvrRvKsqqfpqtfswEauaoPjasAu/v2rgY6siIAYEbquAeQAmrAcEAgbmv%2BugdgdWp10QcAuQfljQf2owfmZOqIJwYuqusIZqeIYkFIcEAaeboCH0G6pQC4YYaRuYdYe2GXKhusB4bfL4cRsEeZvRogFcHUdxqMZ0YUbkf0e5cpu0ekY0YEDUd5aFcaBziUY5r0dyHEb5slbFoUBFrUs6e7uIs4DsaGcKb2C2dKbZGiLVorurmme1sCp8b8aNsCdwqoeLpmfvKQtgoIpmZJF9vDp7s4Cjsop8dNvvMtvvMSBQotskAtvgutq4Badmv8FVZlvdZjuos7qktdbVdItjdAtIE2oyGcEkCAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/raillivore/classic_trek.hpp)
- [unit test](../../../../tests/unit/metafunctions/raillivore/classic_trek.test.hpp)
