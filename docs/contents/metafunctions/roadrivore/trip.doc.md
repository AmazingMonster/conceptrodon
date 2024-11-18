<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Roadrivore::Trip`

## Description

`Roadrivore::Trip` accepts an operation.
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
       auto I
    >
    struct ProtoMold<Container<Sequence<I>>>
    {
       template<auto...J>
       using Page = Container<Sequence<Multiplier*I, J...>>;
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

- In the second example, we will transport the conjuration function to `InvokeRail`.

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
       // This is because `Agreements...` will be used to invoke `Trip<...>::ProtoRoad`,
       // which has only one parameter `Car`.
       template<template<typename...> class...Agreements>
       using Road = Trip<Commit::template Road>::template ProtoRoad<Agreements...>;

       // This function composes the conjuration function `Road` and the `Agreements...`.
       // `Agreements` will be used to invoke `Trip<...>::ProtoSail.
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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwAbKSuADJ4DJgAcj4ARpjEIGYa/qQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJyal2mA45QgRMxAR5Pn5Btpj2pQzNrQTl0XEJSSm2LW0dBd0K08MRo1XjtQCUtqhexMjsHAD0BwDUJoEaAEpM%2BKhnGsd4CsdMp%2BcXqNd3AHQmGgCCBEwLDSBkBJn8bkBwNBmHBkKBIKYYIhBAAnmlGKxMF8ceDsMdkAYFAocT9/PjCUxiccrjc8b8/gtiF4HMcACrEPBpBkmADsVn%2BxyFxwOACpxaLjgARTA0SI0j7oY4S0VHSWDNrKg4M4Uik53NytO4PJ4vO4AWU86G%2BOuFUMRyPh0KRsJR6MxbFJeIJRKehuI9MFwqZLIIx2UxFQRHenyDQr5Ar%2BuuFYolxw8LBYhDYgmVErVxw1YdVtuTIdZGazBFLuoTNeTQtT4vTAm0OyROTz4oLRa19YbR1el2uTmNhiVBqN52exEwBNQwMymCVCAS2P7ycHADE8MQFqRjgB3OcRBaGRwuoe00fT8fHVCxFoRZ5DtEY5hsG1xhuNk5s1cMAex4PAwABuqAANZzpOAbToehAIMcBCrscs4KF4tCOEYr7uh%2BsLnD834/vaMJwiRLpkbhWJeuSPpUiSOJCHgwDMLQCiBkmP7Cl4WTYTGE7%2BFK6ZGhC163BCTEsWIDFktg9L%2BImXEpiqLYMG2xAdgIXaqmKxzYAwSolv8G61kRA4qRyhglJ2Ko9osfZmZuJwABK9BixDHFQXgMI0Wn8B5yFzmwqwBQiMJDkIDCoIeX6cUpg7/o8nneb5DBIRpDAKBkbRPIF85qe2/TJT5RV3Pxxrwch2xhhE4EQREwAPAQB4mSmJxiLQ0UNclbSrh5aSRns1KxKi96BR5CDMX1AC0JBYB5XklTkJKtUK5GOutrpOg6W2bZR77UbitGUsSNEUr6Z10dS/EAGqYMSvQcUpQrlmGMpPrQq2nPyX26oOADqc4EBlChUAkSEoWgBUaUVi2pVeirGkQCPXHdD2fQRv3cbxjVvtBgkKqj912HC5XkuCinPXyUoUzyjm6ntKJhRRTPOhtzMbVRnpHed9GXSdMnegLpJ/MAs5AowBDseT9PY91kXRacBPvUwdBwqL4s5lLZ0gCAeO07LjYWSD2RabZun6YZ2qOdTBtxX9KmVtmkvaQWlsOX8G5NpKHiCBEXiaWl5vqvZRn2217KTU8cNFWgi5KLlkOtoVnYx52ZWI7eBkQ9B5wa5gEuCILmOOYOURRkDCBIscmCgYwEPbMAiF3Pnhfa7i05JaBrR4COyAHoQ94MLQo0ddFprHDj9AzsAPiS4R4e/pHSVJfEog8bn/xiwXWvF/c8G0LQxzxMcG9KsjtWQZvHJcnCOsgBGUaoOV5ykF7JyHpNyCIVXTwCCPQ85xpFaFiQEHkYKxWIhzXa0D9oemxDzK6MlW67yeg2Hi3V%2BJKyEjfbkEInYEF1ptQm1pyREOgeGSM0ZEYQhQZLQW5MFJ00XnqZe0cUqxwXMUe6Od8rqUDsVeGGdPhZ3PihFu28257wXj%2BQcEjNb0IqnQI%2BJ8z5IVQCBOq19OR4LcPfR%2BRAhCq1oDIhsjNtqkVZjtOETAvBEH5hdRBwscR0KLmg5MGDsJGLoNg9kOi4QEPIWzOcZNsBBJ2pQp%2B3jPq0MkbvM6dtZGO1kP7ARwc9LZzDrWXkNMmHGW/OYwpXMEGySQSLOJiiZb208Y1LB4IhIGOfjQtwrj26yUScpNMMo5QhMVK7C2mTrae2/N7aUspliFmMf0kOQwPZ/T/FHQRRUkp5SyFmAwAVxHnEaS/e4WAelKiYLEVAddTFLwAJJhirgZegic5yiCUEePqm9/TGiSmaN4xjIF2lgVYyxFiWaGjsagBxfMnG%2BmEgGKpupXqRMMV878dZS7JMzM7XM6TexZIbLCghG4kUsIdmmX2/CioYtDkM56SFfkAs5gdbmpTnFfEkqxaWclDanxxiQ3xrzRIjnEm4Zl0l77EOUEwYAro5J5IJZ05sxKU5m3zAMq2zDKWjMsplU2QdFUzM1FipShTqUGuCXAvCoLTrgrBQyiFt1iaPWhc9WFKs1bsvxZSuW2E8a%2BJtejUmNDJWUyUrbKVX0jXWL%2BYCopdKSlC0cVay1MbLWtNZV9GphYoqHl8U6mJLSKlF2Fe6Dp8VjZWU1dMjJyqbY5MLYS2VC4qxazLe7MOXtkl%2BwYAHUl2rCzko3KG/5eNTUWvNV8JN7jdSprqQTXBAS62EHCeFUJ87Lw7OaUmhJwbHJ9ojdS2x9ih0MN5sO0d9qPGcuib46d%2BDZ2EL1hQxdt7glwtQNE9Wua2nyQDTWn2KT21pK7U2ilwog2JhrFu9mxqIS7pBfus1yC33Ju/Km899Sn0vtiQovNPNq2jO6RM896SAM8irRuv43sVTdgZE2Nk2AhBsnzJR8j5Ghk8jMP4CIhIvBYCVm4OxdBCCog4gycxUGEn/FhUIBAdiCD0DtkJw1xTROMmBqGYSaR0IyZI6MgA8u5QOSYyWzLDsJ4Fxwbo9yORptlSnmSsh0wkPTRGLCnAKYa%2BTUbYOqSfJEKFVmYXKdZFmmsrqfyps9Sh32XmEhwgk1JjTbgzOcgsxKj9QXiMgZcxBmlu0FMwZcfBsdE6%2BkocC%2Bhne9D80Ylk2lhjaY7MwxyPp/9gzmHad0/0JzBndVDOM8jc0GFHAgjwFFqpsK6uBxAz9DLYbITFLHbCxplpaATh%2BtV/J9s9qIohL2tz8CPMRdVt5t%2Bm6d3Ao80ITAABHLwjA9hHZYVB445ygsnsnv5sMC2rQzsEAd4bArLvXZ8ltJ7jDJW%2BaA5NlhPXoNfAAFJjvdY1UV4ruWyB%2B1Cv7V2btbT65hLktAhvEFFOcg8MP13%2BtS7k9L62duDpHfll7qbFsCQaVQ1ATPX0YffYwiblOavNjG%2B1xtzW1utfs/0NwZbMXdZO8jBLvdYiWYZKNtrOQ3COdA65zLIn92Fn%2B1jubb2xkfVS5%2B8dnKwsE3O5jwHcI5dJZS4i1bwzqeZah7B8pnOEPVM5VcHxxXMDG9K1Iirroed21F/VgQEuCPC%2Bd6Mnce4wzYFUKwEEc5OvFiGUhrwaRuHoAuPdfr3KmBqYwltGLBBpNbS4BoUUZgDxgA4KKRv8lydrcZwHpgactIocvW4AXDW4RmDxLrUJDJR/NIHwIKwEIa8j5AOzqpus0P95V1HuEjfm8cHn77mJVnda4pIxOwvmFfHmk793vwIAyZuENKXxXJGzyOGQAAfXogkAgEAFjoF1goLEb/pY3AC91NmpCwc889gD%2Bs8R1hZN/gEoUJ%2BBD4upsI7gn88BX9382hjQFAEBx5jhcCM08pUA19MoZx7kuElwf8lcWhn8AClA2gv8CAf8QA/82AAC4Qawp9cgN8m8W8yFr8vkttvwuCZ83A59%2BDF81dhCSDPYIRh9%2BCb8TI791NYRNswd4x%2BCkdVD7Y8Q7tdQhBwDKDIDMIeRyQYCpV49dwFg9IU9oR08msK048VJzsoYlRk9U9p4M8PYwMYFXccs41h0E1rpFQ/hiBgAOJYVzkwIr5%2BJAtjIIczduoLchJ%2BJQjwj8ES8VCHdPYnc5NXdNdpsB1DoAiD0ykXEwivdU0oitFJ0hJqiYjFQSsWkKiQ9YC/hj8QCX8uAz8L8OEchl9004R6ioIx9H8aD0C6CP9GDmDWDMB2DRIT8CAuiDwDDc8jDFjoDw9nCGgBA3DbC08hcrYOBNhaBOAABWXgPwDgLQUgVATgNXSwawSebYXYaCVjHgUgQha444zYCCEAQISQL4AADg0ECH8BSH8EkCBMCDOP8AAE5eR9BOBJBeAWAJANANBSAribi7iOBeAFAQBMSvitBNg4BYAYBEAQBqo0g7FyBKA440g6AEgogsROBVBoTpoATjhgBkBkBjgpAvgzBeBlxCASA8Af8uAZBBARAxB2ApApT5AlA1BNAdA9BDwNI0hOAeATjzjLiVTbjOAtM7EaSwxUAqBjh2TAhOTJBuTeT%2BTASzBjgIAMxGT6BwF3j1heBiTjjSAIAkAGSmSyAKAIAAy3SQBgApB68aBMIEgCSIBYh9TYgIhWhUQtTeAkzmBiBUQtNYhtAGgviPi44tYtNh5UzvjSAsBYgvBgBDRD4CTuBeAsAWBDBgBxByz8BZxGg656ybjMBVAGg7F9gPiIhARTjyz8dYgNIsyPAsB9TgY8A0SGzSA65iBjklAZRmyjB8cjAVTNgqADBgAFAbohtDw7MriPj%2BBpTRBxB5TLzFSVB1ByzdBJSDAdzTBHjLB9A8BYgCTIBNhiD%2Bh6zppv96l3yrBLBkheATkEhOQsBfyIBNh6hUoXADJZg/BJSwhlhKhqg9BihNU0LcLMhNURhsLxhJSkL%2BgiwCLyLeh8ymhFgSKxhEhyLFhqKpghhGKQoJBEKXi9huKkSOALisT9TcSLSOSuSeS%2BSBTHSIBcBRT3T/AuBPTPjdzNhVxrhxgELSA/jJB/Avg4T/BeRJANBJAzBJBzgNAzjAg4SBKUTSA0TFKvhAguBAggS4SgSXKzjJAuAziDLghsSoLOB8TCSVLvjSSKS/SqTjTaTgzQzmTWSOBWgWBQJeRpoXhKRsIuA4SvguAvhez8AiBYK9A7yZSbzpA7zFAHz9TdB691SS80ydTBK9TyzcSjSCATT7xzSkqUq0q6JMrsrcr7hnSuFAzThWMzBlLvTST/SRq3S6SQzZrxhurUqMqIy4Sa8%2BA6AwE4yEzyyMyUy0zSB9qsycy8yHBDqizJYSyR59TKzqzay2JDqmyWy2ybiOy6Luz9S%2ByBzARDqRzeh9SJypzUQZz9gbj5zFyPiVy1zMANyXqGpdy%2BADyjyTyzzDqSrry5TyrZBKrlSnykh9AWyUBrBrAvyfz4B/y0hALOBgKmDQKSaIKcSVzYL7oKaeg%2Bh%2BiIBXA2LMKKgmLCLrIo9PBOgBbiKsL%2BaaKOaBAqLhaChJa6LpaGLxauKWKhg2Kzw2hOKcKlKtgdg%2BKdaxyhKAqDSOAZxkrUr0rXzGosqcq8qnS5LCqxrFLJrVLSB1L5pKBGq7KHLsqTLeRfLeReRISzKATJTjbcTgqiTEayTKTqSYr6TFriAWS2BOAkquSWAFBQI%2BTQIbaYQFhhSCqxSJSFTSqsaFTcbHybjdBUg6rNSGzGqjaRLDTorTSuriAWB07M7s7c6XRrDhrgRRrzB/B/AXawrfSZqB65rYrE6QAs7c8X8c64SX886li07yqtrYzKBdqbjjqyyPjd7Tr8yLq60rrSzbrMAqyayOp6yPjnqtywbGzdwPrWbyzvrkBBy/rBAAbxzvzgbQa5zORIbeBoalw4atyEax79yxUUbMBTz3x0bZBS6JBsbBAK7qqAhCa3yGabAJz4LKbqbDhv9iaPyLBILbjmbxTWa/z2aFa/AubULZb0KQgDItayL0giLxdGHRb%2BhWHmKaHUoZb8gmGKL6KOLlbtb2KZguHVbNbxGyKeK9a5SG7mqcTOAzbO6s7jhF6vgV77bC6FKlKvTXb3bNKvbUSkhsrh6ziziTKa8ITeRXLhKWqgrbAQqprfiAgzicq/K4TAgYSuBITzhUgxz/AVHAq8TQqSTGqhSnHVGIn3HlzYz%2BjJAgA)

## Links

- [source code](../../../../conceptrodon/roadrivore/trip.hpp)
- [unit test](../../../../tests/unit/roadrivore/trip.test.hpp)
