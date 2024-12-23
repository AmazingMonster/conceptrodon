<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::ClassicTrip`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-classic-trip">To Index</a></p>

## Description

`Mouldivore::ClassicTrip` accepts an operation.
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
 :: template<typename...> class...
 -> template<typename...> class...
 -> ...
 -> Commitment

-- Compose with Page
ClassicTrip
 :: template<typename...> class...
 -> template<auto...> class...
 -> ...
 -> Commitment

-- Compose with Road
ClassicTrip
 :: template<typename...> class...
 -> template<template<typename...> class...> class...
 -> ...
 -> Commitment

-- Compose with Rail
ClassicTrip
 :: template<typename...> class...
 -> template<template<auto...> class...> class...
 -> ...
 -> Commitment

-- Compose with Flow
ClassicTrip
 :: template<typename...> class...
 -> template<template<template<typename...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Sail
ClassicTrip
 :: template<typename...> class...
 -> template<template<template<auto...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Snow
ClassicTrip
 :: template<typename...> class...
 -> template<template<template<template<typename...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Hail
ClassicTrip
 :: template<typename...> class...
 -> template<template<template<template<auto...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Cool
ClassicTrip
 :: template<typename...> class...
 -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Calm
ClassicTrip
 :: template<typename...> class...
 -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Grit
ClassicTrip
 :: template<typename...> class...
 -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Will
ClassicTrip
 :: template<typename...> class...
 -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment
```

```Haskell
-- End in Conjuration
ClassicTrip
 :: Commitment
 -> template<typename...>

-- End in Transition
ClassicTrip
 :: Commitment
 -> template<template<template<typename...> class...> class...>
```

## Structure

```C++
template<template<typename...> class>
struct ClassicTrip
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
// This operation returns the `Container`
// via its member template `Mold`.
template<template<typename...> class Container>
struct Oper_0
{ 
    template<typename...Agreements>
    struct ProtoMold
    {
        using type = Container<Agreements...>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

/**** Oper_1 ****/
// When invoked by a packed container,
// the operation creates a function
// that multiplies each value result of the elements
// inside the container and extends the result by its arguments.
template<auto Multiplier>
struct Oper_1
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

/**** Oper_2 ****/
// This operation instantiates each pack by the variable.
template<auto Variable>
struct Oper_2
{
    template<template<auto...> class Pack>
    struct Detail
    {
        using type = Pack<Variable>;
    };

    template<template<auto...> class...Agreements>
    using Rail = Detail<Agreements...>::type;
};

/**** SupposedResult ****/
using SupposedResult = Shuttle<10*2, 10*3, '*'>;

/**** Metafunction ****/
using Metafunction = ClassicTrip<Oper_0<Capsule>::Mold>
::Road<Oper_1<10>::Mold>
::Sail<Oper_2<'*'>::Rail>
::Commit;

/**** Result ****/
using Result = Metafunction::Mold
<
    std::integral_constant<int, 2>,
    std::integral_constant<int, 3>
>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);

// The following `static_assert` shows how the operations are composed:
static_assert(std::same_as<
    Oper_2<'*'>::Rail<
    Oper_1<10>::Mold<
    Oper_0<Capsule>::Mold<
        std::integral_constant<int, 2>,
        std::integral_constant<int, 3>
    >
    >::Page
    >,
    SupposedResult
>);
```

- In the second example, we will transport the conjuration function to `InvokeMold`.

```C++
/**** InvokeMold ****/
// This operation instantiates the `MoldArg`
// by `std::integral_constant<int, 2>, std::integral_constant<int, 3>`.
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

/**** Result ****/
using Result_1 = Metafunction::Flow<InvokeMold>;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult>);
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

We will implement `ClassicTrip` by performing recursion manually, meaning the function will recurse only once for every invocation of a member template.
We will showcase a simplified version that handles `Mold` and `Rail`.

Note that in the following code,

- `Radio` is a `Mold` and
- `Car` is a `Mold` or `Rail`.

```C++
// `Radio` is a `Mold`.
template<template<typename...> class Radio>
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
           template<typename...Signals>
           using Mold = Car<typename Radio<Signals...>::type>;
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
       // This is because `Agreements...` will be used to invoke `ClassicTrip<*>::ProtoRoad`,
       // which has only one parameter `Car`.
       template<template<typename...> class...Agreements>
       using Road = ClassicTrip<Commit::template Mold>::template ProtoRoad<Agreements...>;

       // This function composes the conjuration function `Mold` and the `Agreements...`.
       // `Agreements` will be used to invoke `ClassicTrip<*>::ProtoSail.
       template<template<template<auto...> class...> class...Agreements>
       using Sail = ClassicTrip<Commit::template Mold>::template ProtoSail<Agreements...>;
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
       using Road = ClassicTrip<Commit::template Mold>::template ProtoRoad<Agreements...>;

       template<template<template<auto...> class...> class...Agreements>
       using Sail = ClassicTrip<Commit::template Mold>::template ProtoSail<Agreements...>;
       /**** Continuation ****//* End */
    };

    template<template<template<auto...> class...> class...Agreements>
    using Sail = ProtoSail<Agreements...>;
    /**** Define Sail ****//* End */
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKz%2BpK4AMngMmAByPgBGmMQgZgDMXKQADqgKhE4MHt6%2BAUEZWY4CYRHRLHEJyal2mA45QgRMxAR5Pn6Btpj2pQzNrQTlUbHxiSm2LW0dBd0K08Pho1XjtQCUtqhexMjsHAD0AFQnp2fnF6cHJhoAgsenANQAkixp9GyCTP2PZ9d3D0uQMu/1uN3uB0eJgAbBoAEpMfCoGEaR54BSPJhQ2EAWU86BRADpwQRMG8DKSTEk3KTyd9MFSaQBPNKMViYQmcqnYR7IAwKDEIpHc8ELYheByPNz8rLIAAqxDwaXBJgA7FY7o8tY9AUdHgARTA0CKPOGoRG/K7HR6DNq/UHanWQlFuVootEYrEovG0Amw4ma7W0970xnBikM6kEFlstic4lJHl8pgCqVuxPgx1iiUER7KYioIhmxGZ7VqjW3R3a3VS1AsFiET65v7W23Nh1Vx7ZyUeeuEUtV8sDztamseBjaHbfHKWk4HVuLe3Dkfz7HwxFOd2GdBr13ELfETC8uvFTA7hDxDnLzurgBieGIC1IjwA7kfwgtDI56WuhZvYZiDA7qgMQtOEmJrtGrLMGwRLXlWq5yheDDPm%2BaIMAAbqgADWR4um6AEvoQCCPAQF6kTGjyHgoXi0LmqBUKR5EgWBEQ7iiUGxgy/rwY64ahlGMYwRynJCHgwDMLQCgioGI5al4WRGI8PrsUk%2BppvugnQeypobsi1JiRJYgKPG3IgCAnEikkFZydWZy1hOU4/C2erYEBS53LxZayXJNYKoYJQzi5NqLkcHa2auAASvSssQjxUF4DCNAI8UkExR5sKscX8aSa63rQqAvnBPkrpCSHovFiXJQwpHEAFGRtBiZFHmgjl1T8CVJT83r4u6RFkdsubhFh2HhMAaIEM%2BXmjpCYgFURSkJW0F5xWkBZ7KmMRMo8hYrY8CDiStAC0JBYHFnXVSZ02kWSIaUlGt0RmGj0Ccy2lxlyia8jKplfcmqYqQAapgAq9DJla2V2BDipKhpgbQ11DiVkOrgA6ke0MBVQ8TpcebXTilF3dbivUAUQa5AyDdjFRDkPagpY0UayUJqcp%2BLA6DCPUipVk2ZDar6lSFbXTlkY0i993i3SkuccJv1Jj9n0KymJmcrcwCHmSjAENJGbI1WDNKflhUs%2BpcNMHQjLq5rTaqwm2DmZZ1nXX5dUMIFKXBW5O5hfBAtC/BY51g2BBNrOYXWt7HlgvrQeCOEXgEzVwVttHpWPOVGJEzOaBvJkIO461k7tTO2cpT1vpbu5zVrtbmBa4Ids0%2BnkSFhjCDfI8mAYYwTHbMAJEonXDc66ZAEVRhrR4BuyDPoQO0MLQ21zYVnpdmN9CYsQwA%2BNrAa046iEHRiFVxKICl4bCw%2B22PqJEbQtCPHEjwXzu5PDThl8aNKKt4PKirKmpEcMyIB8yFlQMWP0GhSCB0hC%2BA6yASIdwxAIJeC8jxpFaOyUkcV8L7h4vrUWz1pZi1luyeW30VbxmvtrXW2B4KG3GpA02UoZR/wVEqRkvYQ6OwlkeHmiZeEkLzAWIs5oCTUhoY3eWAdPKxzKsfSqXUc4nnzk1ciRcnKlyqsTDQPMALblxkPDW9cb5cgIQfaszor4mJHtJQidBH7P1fqRVA6ERpfx/gKdhADGTAMEaA0RqAhAW1oPvEcRCHokOIXdMWTAvBEAof9Juf1FaEikTrcGI5GE2lCSwrxsoOGALcNwwgQjYls0rgE0WIjwEhMtpI2xZj7ayMsaOey45HAMETs5K0rl3K%2Bx8v7Z2ciD6RKlrEsMQlyFK0oQKahTTaFZPpopJh4iWFgLESWRpNtaEyJGQfGshpjRHmYV7AZoJhxHKNMsXJdBw7zj1KnQZhyFEVTLjVCqNcsgNgMNlciKJNkQPEe6LAJydxMBiKgHu4SrEvFzB3IC9B1EtRTEeeBl5dwEVRBVL0sIESWwsXxPhMSnpRMmdSeJiTZnJKSTKDSyytTdlzEC%2BpCMhnqkDh04OjZtYPIXEMNOnZmW1j7AQP2nL9aH25fjXpc4BV2heXTcZZCPqEkMpJOh10ckqXyemNwf59JuA1cZeW5SIx5iYMASM9CDl0zjsXJO/L%2Bk%2B0uVKuyTx/Lu2yJ7PpIVBVKshiqkl5KyVvS4nSqhNL6WU05oyuSIrzaW3dVqJGbS5I5M4iw2N1Nua9QzHa/mqpBYHJFiGiZYaVXTLVdyOZKTlbzLVosxu8bsmrMeMbF8LCk1czcBk%2BtjsYytPtfZL1Htk5%2BqjoGwcxbh03m5WKsO5zXUqljjKrpPSgp%2BueeFYl0TQ2vVVSJe2daFm7JbXrdNOTmFUnUgUnxnDqSlIIOan8AiHYWT4bUrZEi%2B3NtHkrVp8Fg37ora9KlqBI2NpPbSpt57MmXrbYzNl%2BS2H/0fSUnlL7P3CPfa%2B3KrLQlW3/fWudCF10JydcuoVqbZ2lp8iBilYHJYQag/W09cHTFLMQys5DeTb3fuCURnZXHpGAcLe0p4xzbkoeoy84ZwsATAmU38cENZ7yPlzNgVQrB3hHlU0plTKm3VgmSOEPkXgsAszcK1PYaQEP0NGTWIQCAEkEE3gZ244zWOAbuCKlzbn6BAcMycNMaQaIeauCSctR6ZF%2BehjmMLEXIyKfuB01oiocaecY2GnzMG0ngxFXuTLmlUs1gAPKxQAPqok80fCqqBYpOsPAQHY7sjGwk6RbCI%2BCNBqchBhaeE0MSZWqDdYRFcoH7xy4e6tx7a3JIcqxeIhWEuSkq/EGrKp1RQgYzFubZ7RMOeHCKoFPMOV807JmyiAmuvLE0n%2B%2BDpGJNQjo6lvdTHYucbsfGnV%2BINlBIEY9o7z3hZvdXWlp4G3iBVa4A8/rjxUbIXcZ/HcW0IKYOQLhHcrVltkARzXRr8QnXIEPPSNeHyCcd1zCwWijh3h4ALpgJgiDHiT28EeaidOdqMRrr0H7AJIQfjwFZmuuPus40MZgVQpIgIoqoiDbn6PCCem3rvaR0XQMQeUnTpUtBGeaUc7cEV0PYfbcu%2BNz7c342ncB/9oc4PRkfcrft9683UkqyWxLsgTMI2cmwB8bjRusxrZZXbqpmGvj3cZAHux%2Bzg9lklem7zCTIOcgAFKtvku25QVqGT6wEwFgg7mxY4l1wz%2BIRxY%2B23Muzrwx7nzp/2RbhTEPnezbd4dn7PHs%2BM11QJs7%2Bbgdx/E2DktZX7Km7MPDwXGdFFE5LilD8LR47k67izkimPsJP22jXSeipIX0Gm%2BW7XgMp6H5taKUPjwp/m%2BHDNljqe2OWqxzb6/Pbhxpoze2rNA%2BWfYUZDPwPxiCCwLRb0dxjjGRixPyf2jSjXSRI1%2B3bQJUfgEw/xExH3tkHVZCAwgLU3siEC8DSFPHQDhEVzohn1uByUIOIPzlIPINzEL1c2L1ALcC4A0CODMGfHYKOCSGfDAA4COAEN5ghxrBxEwBaA%2BUoJ1QkKYCkNuzQyKUZFNz6yfSYHC1ohtXMnfXBHMkgWUOqy4EZHYJAR0LuHMjZQMM2zMEZAEKEI4BARQPBnMmfWC0h1CzIIi2bCizuGvQYOzVkI%2BW0N6k8mpBOwIHQHMnCFJA1jECq1ak/EEEZGiOfBsMTBgR8gWEiJAGiMwFiNoHiIEESPFWpBSMeCSHBhEKc1HRBm8LnCv2nGQCqxVniAIAgCyPMgUHZGaN1gNQYOfBoJIM8Lp25HWDcKPiPH4AfkKkZhRE/EcCaJaLaHdAUAQFXn2hNkJya36FVxalUSUEiIaIWJ6KUDaHaIiM6O6JTEZGHFv2pDsOEICScLCJ8lNyMOpBMICSB1uOq1UJKXUOS1MKH14g6JyMEDyLqgKISJXxKLcDKLSOwAyPTShmyNyPyMKPdhhOSMEGfAqJ7xZgT1TQCVz2tU/3SOHEGLoOGLohVETDGPo3cKM2BFBGcwaAEB3G0100i3qJCyZKBBMxrGeEwk/l1TqzeRQW2JnGXy/GnlJHl0m1uG3hRAR3RzmIuLBJiMhIxOKOxMmkeAROfFBLRK1OhK/F1NxJFAsQf1IQOzgIBnxEVOAFWxhlzCFI8RUg/08iT0dGu2ZgExUkdLJLcBBPVONLiNNKSNKJxP1O5CRITVDPBPRIjNhLKLxMJIJNwPHwh2tKmU7ztLtkdK1V8PbTdJFPt1ZlLNwg9NkIaT7W3gHQsiHQZJrGpLqJeT8K8NhwCMkJ0RyHMk7UZErMwB0ObJqIWEoPmL/hONaPOOyK6LYB6MZFbNhwGKIKGIYNGKFg4E2FoE4H8F4D8A4C0FIFQE4GDMsGsC7G2F2DwlqF4BfSPO3M2GwgCEkEJA0EkC4FVCSA0H8A0DMGhGhDMAAA5gL9BOBJBeAWAJANBoFDzjzTyOBeAFAQBoEHytBNg4BYAYBEAQBBo0gElyBKBc40g6B4hIh2ROBVBgLoQjpoRJBHhgBkBkBHgpBCQzBeAzxCASARc9B%2BBBARAxB2ApAZBBBFAVB1BHzSBdBUgXw6o0hOAeAdy9yDzNBeBELysEkCL6JGJqLaL6LGLmLWK3zp8IBexSL6BcENh7y1LMKkASKyKyAKAIAHLLKQBgApAuCaA6J4gUKIAYg1LSAYhwhWgmRFLeBgrmBiAmRysYhtAGgHyeBSBc4mxytF4wqpKsAYgvBgBXQH4ULuBeAsAWBDBgBxBMqHwEq8Ae4CrjzpcGgEl9gkrcjdypL9cYg6poqPAsBAroY8BoLCrSAe5iAoUlBDQSqjB9cjBbK%2BADBgAFBAZGcXwNtDykr%2BLhBRBxARL1rxK1BAqZL9BSqUBrBrB9A8AYgULIBNhGsdjOAjosjb1TALzLAzAELhrFQsBLqIBNh6hqoXAgJZg/BUhQhlhKhqg9BigfVchPBOgIbMgoaRgwbxg6h%2Bdqo2xAa9Bfr%2Bg2xEaxgEg6hFgMaCahhcasoJAfrry9hybwKOB9zSB4L1LOBHg9K6KGKmKWK2LTLcBuKrKUh1gbLHz1hNgLxERxhvrSAXzJAkhCQABOJIVUSQD8swSQWEX86EGWmmyC0gaClIQkaELgaEYCmW4Cg2/wT8/wOW6EemwKxC5C1C0gdC7c0gLC3C/Cwi5y1y8iyijgVoFgDCVUI6LEZMJSLgGWwkLgd8zi/AIgD6vi2QQSra6QHapQPaqS3QLguS9Q8K5S2m1SqSjSrShJHnZmmi1myhEOsOiO1EMyk8RyqEZIMwfmh2maiAey2uyyoily9u8YYOjymW9gvgOgHBPygKqSyK0K8KoKkK6K2K%2BKhwSelK7WNKpeQKrKnKvKqSSe4q0q8q48/AQ8RoGqwK%2Bq5ARqyelqwK9qzqpkbq/YY8vqgapK4a0azAcanesaGaqgOahapalaye9ahO4SpO2QXayS489Ow66ap6qwSwM6i6%2BAa6%2BzHIAq%2B6iIx6k6l6t6%2BID6kGBBnoPoPsiAVwIm4IICUm8G1ISG/oEhqhnIch5G/BqqgQdGmGgoFGgh5hxYeh/GqYIYEhz8Nobh6mhQSm4SnOumhmk8pmlmgy3u1iyu98x4CAbmmO%2BuvmgWjC4W5nM6SgHOrWnWsOj81UC21Ub8yQZW%2Bi1ISR222we2x2zCnC1uvCwuyaD27u4gCitgTgX2gylgBQDCFijCUOwkCMBYKOnm3i1IABzaoB0S%2BQFOsBnQEAPgzOhSwq8RvOhCzgTSggbS4u1QXx/xwJ4J0J3MGut4Ou8wJIJIJu%2Bx52tuipjutxxp8YAJ4gqrIJmWqrUpqrAppOoe3yygUe488e6Kye0ZmKuKhKhe4OJe9K1ezAbK3KuaAqpK7eyau%2Boqyqw%2B3BqSk%2Bs%2Bwai%2Btq866%2B2%2B3qxUR%2B3gZ%2B/ON%2Byaj%2BwW2aq1H%2BzAZa6Cf%2B%2BOmJiQYBsShJ/a5JyB4wDBmwdqr6xB26w4Do6B6wV69S96kXXBq6xhv6ohgG1hoG0h9AIRyh%2BG6htFuG8dLFpF7GwmvF9hphgYLh0GvGzGkl/IdFgRpYCoalrgCmnYKmllmmiRm26RwpgJtnEp8nMplRtKKplljRp80gEWnR8W1q/RxIMO6pwID89gjQap1UQ262/OzgO2tC2y58kASQfwWW/wYCgCmWyQGW78%2BWrgPg1qpITJxmpC5uwWnOjizVrJp1%2BxzYYarIZwSQIAA)

## Links

- [source code](../../../../conceptrodon/mouldivore/classic_trip.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/classic_trip.test.hpp)
