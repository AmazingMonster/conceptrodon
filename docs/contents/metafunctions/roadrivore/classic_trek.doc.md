<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Roadrivore::ClassicTrek`

## Description

`Roadrivore::ClassicTrek` accepts an operation.
Its first layer accepts another operation.
Then, it returns two commitment functions and twelve continuation functions.

- **Commitment**
  - **Conjuration:** When invoked, the function instantiates the first operation with the arguments. Then, it invokes the second operation using `Omennivore::Send` with the type result of the instantiated first operation as the packed vessel.
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
ClassicTrek ::   template<template<typename...> class...> class... 
              -> template<typename...> class...
              -> ...
              -> template<template<typename...> class...>
       
ClassicTrek ::   template<template<typename...> class...> class... 
              -> template<auto...> class...
              -> ...
              -> template<template<typename...> class...>
       
ClassicTrek ::   template<template<typename...> class...> class... 
              -> template<template<typename...> class...> class...
              -> ...
              -> template<template<typename...> class...>
       
ClassicTrek ::   template<template<typename...> class...> class... 
              -> template<template<auto...> class...> class...
              -> ...
              -> template<template<typename...> class...>
       
ClassicTrek ::   template<template<typename...> class...> class... 
              -> template<template<template<typename...> class...> class...> class...
              -> ...
              -> template<template<typename...> class...>
       
ClassicTrek ::   template<template<typename...> class...> class... 
              -> template<template<template<auto...> class...> class...> class...
              -> ...
              -> template<template<typename...> class...>
       
ClassicTrek ::   template<template<typename...> class...> class... 
              -> template<template<template<template<typename...> class...> class...> class...> class...
              -> ...
              -> template<template<typename...> class...>
       
ClassicTrek ::   template<template<typename...> class...> class... 
              -> template<template<template<template<auto...> class...> class...> class...> class...
              -> ...
              -> template<template<typename...> class...>
       
ClassicTrek ::   template<template<typename...> class...> class... 
              -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
              -> ...
              -> template<template<typename...> class...>
       
ClassicTrek ::   template<template<typename...> class...> class... 
              -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
              -> ...
              -> template<template<typename...> class...>
       
ClassicTrek ::   template<template<typename...> class...> class... 
              -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
              -> ...
              -> template<template<typename...> class...>
       
ClassicTrek ::   template<template<typename...> class...> class... 
              -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
              -> ...
              -> template<template<typename...> class...>

-- End in Transition
ClassicTrek ::   template<template<typename...> class...> class... 
              -> template<typename...> class...
              -> ...
              -> template<template<template<template<typename...> class...> class...> class...>
       
ClassicTrek ::   template<template<typename...> class...> class... 
              -> template<auto...> class...
              -> ...
              -> template<template<template<template<typename...> class...> class...> class...>
       
ClassicTrek ::   template<template<typename...> class...> class... 
              -> template<template<typename...> class...> class...
              -> ...
              -> template<template<template<template<typename...> class...> class...> class...>
       
ClassicTrek ::   template<template<typename...> class...> class... 
              -> template<template<auto...> class...> class...
              -> ...
              -> template<template<template<template<typename...> class...> class...> class...>
       
ClassicTrek ::   template<template<typename...> class...> class... 
              -> template<template<template<typename...> class...> class...> class...
              -> ...
              -> template<template<template<template<typename...> class...> class...> class...>
       
ClassicTrek ::   template<template<typename...> class...> class... 
              -> template<template<template<auto...> class...> class...> class...
              -> ...
              -> template<template<template<template<typename...> class...> class...> class...>
       
ClassicTrek ::   template<template<typename...> class...> class... 
              -> template<template<template<template<typename...> class...> class...> class...> class...
              -> ...
              -> template<template<template<template<typename...> class...> class...> class...>
       
ClassicTrek ::   template<template<typename...> class...> class... 
              -> template<template<template<template<auto...> class...> class...> class...> class...
              -> ...
              -> template<template<template<template<typename...> class...> class...> class...>
       
ClassicTrek ::   template<template<typename...> class...> class... 
              -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
              -> ...
              -> template<template<template<template<typename...> class...> class...> class...>
       
ClassicTrek ::   template<template<typename...> class...> class... 
              -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
              -> ...
              -> template<template<template<template<typename...> class...> class...> class...>
       
ClassicTrek ::   template<template<typename...> class...> class... 
              -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
              -> ...
              -> template<template<template<template<typename...> class...> class...> class...>
       
ClassicTrek ::   template<template<typename...> class...> class... 
              -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
              -> ...
              -> template<template<template<template<typename...> class...> class...> class...>
```

## Structure

```C++
template<template<template<typename...> class...> class>
struct ClassicTrek
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

- In the first example, we will compose `OperationA<2>::Rail`, `OperationB<10>::Mold`, and `OperationC<'*'>::Rail`.

```C++
template<auto...>
struct Shuttle;

template<typename...>
struct Capsule;

template<typename...>
struct Capsule_1;

template<typename...>
struct Capsule_2;

template<template<auto...> class...>
struct Carrier;

/**** OperationA ****//* Start */
template<auto Variable>
struct OperationA
{ 
    template<template<typename...> class...Containers>
    struct ProtoRoad
    {
        using type = Capsule<Containers<Shuttle<Variable>>...>;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};
/**** OperationA ****//* End */

/**** OperationB ****//* Start */
template<auto Multiplier>
struct OperationB
{
    template<typename...>
    struct Detail {};

    template
    <
        template<typename...> class Container,
        template<auto...> class Sequence,
        auto I
    >
    struct Detail<Container<Sequence<I>>>
    {
       template<auto...J>
       using Page = Container<Sequence<Multiplier*I, J...>>;
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
using SupposedResult = Capsule<Capsule_1<Shuttle<10*2, '*'>>, Capsule_2<Shuttle<10*2, '*'>>>;

using Metafunction = ClassicTrek<OperationA<2>::Road>
::Road<OperationB<10>::Mold>
::Sail<OperationC<'*'>::Rail>
::Commit;

using Result = Metafunction::Road<Capsule_1, Capsule_2>;

static_assert(std::same_as<Result, SupposedResult>);

// The following `static_assert` shows how the operations are composed:
static_assert(std::same_as<
    Send
    <
        Send<OperationA<2>::Road<Capsule_1, Capsule_2>::type>
        ::Road<OperationB<10>::Mold>::type
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
template<template<template<typename...> class...> class RoadArg>
struct InvokeRoadDetail
{
    using type = RoadArg<Capsule_1, Capsule_2>;
};

template<template<template<typename...> class...> class...Args>
using InvokeRoad = InvokeRoadDetail<Args...>::type;

using Result_1 = Metafunction::Snow<InvokeRoad>;

static_assert(std::same_as<Result_1, SupposedResult>);
/**** Second Example ****//* End */
```

## Implementation

We will compose functions using `Omennivore::Send`.
For example, we can compose a `Road` and a `Rail` in the following way:

```C++
template<template<typename...> class...Args>
using Metafunction = Send<Road<Args...>>::template Hail<Rail>;
```

Note that in order to succeed, `Road<Args...>` must be a packed `Rail`, meaning it is of the form `Vessel<Items...>` where `Items...` all have signature `template<auto...>`. This requirement is not checked by `ClassicTrek`.

We will implement `ClassicTrek` by performing recursion manually, meaning the function will recurse only once for every invocation of a member template.
We will showcase a simplified version that handles `Mold` and `Rail`.

Note that in the following code,

- `Radio` is a `Road` and
- `Car` is a `Mold` or `Rail`.

```C++
// Simplified `Send` function.
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


// `Radio` is a `Road`.
template<template<template<typename...> class...> class Radio>
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
           template<template<typename...> class...Signals>
           using Road = Send<typename Radio<Signals...>::type>::template Road<Car>;
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
       // This is because `Agreements...` will be used to invoke `ClassicTrek<...>::ProtoRoad`,
       // which has only one parameter `Car`.
       template<template<typename...> class...Agreements>
       using Road = ClassicTrek<Commit::template Road>::template ProtoRoad<Agreements...>;

       // This function composes the conjuration function `Road` and the `Agreements...`.
       // `Agreements` will be used to invoke `ClassicTrek<...>::ProtoSail.
       template<template<template<auto...> class...> class...Agreements>
       using Sail = ClassicTrek<Commit::template Road>::template ProtoSail<Agreements...>;
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
           using Road = Send<typename Radio<Signals...>::type>::template Sail<Car>;
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
       using Road = ClassicTrek<Commit::template Road>::template ProtoRoad<Agreements...>;

       template<template<template<auto...> class...> class...Agreements>
       using Sail = ClassicTrek<Commit::template Road>::template ProtoSail<Agreements...>;
       /**** Continuation ****//* End */
    };

    template<template<template<auto...> class...> class...Agreements>
    using Sail = ProtoSail<Agreements...>;
    /**** Define Sail ****//* End */
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwAbKSuADJ4DJgAcj4ARpjEIGaSAKykAA6oCoRODB7evnqZ2Y4C4ZExLPGJZv5mtpj2pQxCBEzEBPk%2BfkENTbmt7QTl0XEJSam2bR1dhVxTQyOV1Ul1AJS2qF7EyOwcAPT7ANRCeCzptHg0mOhHJoEaQq73GkdUXgwOuQB0JhoAggRMOcDECTP43AQAJ7pRisTBHZRMZAAaxuADVMAo7ODsH9/goCMQvA4Tq47gB2KwUgAi4KsAPxQJBTDBEOZF1ZmHBkJhcLY30FuKOyAM2KOHkETAiCVIR2hsOYAsF2HobEEClx%2BMJxNJTwY6B5kraMuIPNVwMYBAUgt%2B/jx9vxJip%2BKObvlwM5bMhntB3PZfKVmFtwtFTHFAHlYcRWbktQD3UcdSSCEcaZgTbRXe7DkcAJIMABuqDRdweUYSsYELyOAHdCAh5QgES8LerrSGHr8E%2B7nRYjl5skZ5Xy7v4aUcKzHmua1VabULHf5%2B866cunT23Ry/Tzt1zd4H4SH7SKxQvvv9gMRMJaNfH/onBxFgEcAEqoJi3cET9OZnmX69bw7RdsBAEAFX9Bl/lXekN0BX193ZBDvT3b0mC8Ihj2wU9w3PUMzxOIhUWIVBUBYOVUP9Nx0MwkCcOxW0ngARy8Rhdk1R0AWTPVnghVpUGI0iWB5ZjWM%2BLEsPvPtsy3ZCqMo3c5J5GjUCw%2Bi8JPMNI2jKsGHvRNuNTX9pSzTcjlzAti1LF4p10mt6wIRtHJbB5RLYiShS7GTKX7J9hwgscJ1smc%2BMwFj3I0h0V1pWDGTMhSkJZFClIhFS1K0yL1NtACb3bDi8TMvyXyEEzArTDMTP/K9cvnLCwIg2LoJi9c4uggFcxeV9PycGs8AUI4mDLDR30/F5u3gpL5JSn1JoPRUjzojL0oIrr8FQe9DIlM88GQAAVa8USdF0zP2AAqc7TvKmhIjfD9bgu07DkuwYOiOR7vI6h5qLNB4jj6gahoAWU8Q0vPi6aEt5eblTtbCMoldp9PdTblBIogRsNMzpLMnMHolMiWEIds3oup7CKGN79m85GiRTfGWEJghqbdbGH0TdnzLxyVtG2XSSfOsmXtTd6cY5z7hu69bfsML8vsR6XrxFMjihuI5m2vcaOfZyGdcPGH8Nwxi8GAZhaHy5n2aK27PzK/VDQDaGEVWnq%2BON03IvqvlcXquTrfttxvq1Fq2a1t0zou/GGB56dcn5x6zqObADUpuDQ97UX2fD86jn2wwSljh7BemYWqYzxNcwACUaaM3g%2BL4BDeEgmwRNgqgSD1JqGoQGFQWsxot8vjl2hB/veT5mnlGMGAUTIOn65ylaj3mJ7H%2BuGCGjH7IbLZUwiKznz%2Bgg5QHnNjjEWhe4P94OnVo50hI9j%2BtiKEjlQZziDV431YAWhILAP9Xs0G0J9ZKzUSl6KaYCZoQLmvyYMi0zzLUNgg3CftMTYkaEjNOm1jJ0BAT5fBg8jgAHUEREjzlQduC80BLxjg3QBsdOp3RrEQDed10E4jBiHNO7orYBW/GgrEOIISbyXFBHhlI1xQXwTrCGcioEQSDEghiKCVGwyyoKHKQFzZl14UOYqPdaxlVwVmCEWi8p1XAl7YOEis6XVztPHIDdC4JyTvdUu3DezNXEWLLmBMiZWjjmTNxKdWpazsZHRwDAvB8xcc9YuoTPFhyHiPfqDCG5oHOFkLEzdF7Rz5uk9eTDRrS2TgvF45jaqeQ0JrMWxwohvzIQgVkRxMCFkYE2LYwBGwVOqtozsrx/qFnaHgbqyA5SEFfgwWgL9z6936oNfR9ABrEGAD4K0tTM4pP%2Bv9eIohBwuQBH0ix1S6x0FoEceIA4lC3FYXvEshy3DbT2gdHkljUZv1QJvB4pALa5lrCPZAjZmn9QEDMqZCJ0jtHhECD%2BLxA5cK1rIhRet4HqKWpo4584sGPn0X7MqTzcI7X2pgQ6EIPAM0ID7TuojQLgV9h89GzCzFYo1JJYOfztlpLrhPTJKt57NjycvWOhS2ElNeDLXJvTAInN%2BIiupQ1Kl3l%2BvWWgFyrkHNuagP6RYHlDUJdiYlryITvLRqgEqdBNmJmRTA8BO5UoYVUqozKGKLysutDivRB8LUXIEQa7ILzSVGn8QQalEC/be3pZ3Rl5rKosplVU2GjVwl%2BMEBEGJE84mJ2TiLbhMEOXgwURDVFyjzxKo9ZxbhVsMZlRjaItw5bIrJtxhHdM10nZ3SCa4nNHiPp4zbTKE4pUs1C0SUQ4eo8eWx3%2BgvbIhMDAf3KQ8OtzDfpYHbbcJgsRUDtKtRZVMzSDT0AFQiUQSg6zq0efLQZCyN6VXlaA210D7XPsQtRR1pbS0IzNJWgytNSQxp9d5VmKaI4UsZsTEdCTc1a02uBwgFsQM8IidzYVzjSYJ1HTBnhNqX2KIWuixBgpTgmzEDopJls8U1oEXbWBQY3ySxEm7MjliGr2jDX6IdeDyWIzEfglDAh8mZow5dEJub%2BN4wcfndDAtMPQY8RI3Db6lMoRLc6z9zrBEYNMQVCjf7dRGQqng3RLNjp6Y5nw0cAiMYcMwSI5lUV8H5ukSZjuT6VOQPc2pwjyCfNqINmoxtnqLN4u7r3YxRnTENvdR7KxsJm1pwiVJpx68s1iYUxzZzfy/GUoIJBkT2b3Gp18WB2Q6bYkFawxl7W8ivOOw026hNd5f0hYPtR8cW0iWBrJQHENHGuQRvY1G8NK7RrxpqmykCjULYecUlAtK6nFuNYmxW3TWsrY%2BoJc8klPX4OhuG5x2l/WgSIjNUB8b/Sps2JK9nY05XhOydEz24D3jiuPrw7Vl9C2/MuqI8t7ROKNulQEYBuN0WmvASTddsO/bMDtq4xctLz3GSvdanYh6At8RZ12tgIQu1SZY4xxj3tjJagRFFF4LAY43AYToIQKEUkASQ2%2Bxtf9qYhAIAwgQeg02mfFvq1NribOEbpAUF4HnBaJp1bgZJIXBmRdi/oAAfS4LzqXeHvOs/l9RUX4vMBK7MGr2bDraI/dlwSYX31iB4ASGriJwVcgPigxTXNzPHVHHRCMrdEvdObQdwINqTUVyFvc/zmXS3jTSkiMQcj%2Bm6ajcxnmszodLOwgJUwXXEvetSlNBxNwHOudZ899b73/oHTYHZT40zUi3tuY%2ByigXZvMUQ9j164c7WJwJ6qi3yvR0a/tTxv7hgTuCvpbgvbnSzR%2BzO9eq76aKkjiA3F44C4Nuf2%2B%2BF0P6Ryf3S60bzinBkWCGo8D9apSWMIQDz3%2BHn7kSo%2Byiv/Pj9mm3LiV%2BWXBfeZgMtbdIfv85LZB78f188woxJdgeQv8lxy8Xsq8z95tn9vgAApYLa5A%2BJEYAFsDrSPU0ESUA9yHkJfWgFfS4BIU6PMOURA9lRzLGE/bya/JRZvFbVvX/YXGNYGWgRPRMJDVrfyKzLA9oa3W3CEExbvJgyNSiREJgDA3vGg/vU/XfMPBg/7PKQHPFdgr8DrNgkGUQy7KHbfOQifSsKfLtJ7IrNHQfSfXINwEw8mWfDxN3VhYvUZWIH3bUTfSwgQNwI6WA43d9U3ALc8V/diA/YXEQmg2A3FA%2BfhfgzPKiIIrEHkJw0vXEGQpPOQugz7N9FnTSP7ILH/VA9vYHDrEQi7WVcQ6xfQxqQwuhPIGwsfcwiOAAMTwBj1TGwFUFYAuARBnxLnxA2y8HSBVnQFfCxGX3T1iKNAz0V311Vz4k5wIG5yoi4A0FOnqCODAA4FOg2KDmwDlB12mINxEnmMWJ5GWNWLlA2K2I4B2KDhc3%2BCtkBgqlFT9W22NTcCH2gghENyG1pXxDAnrS31OI0EjXUPvDAnO3eI8LyB5EuO2J%2BLjV0zAj2zV2rVGKILKkeLaEKX%2BOZQDimL1xVz2PxOV2%2BOoMD0JFjGQCV1wgSAIAgEJHQDAgUHhGpLzxGMVyPhOAGKGPZOX1xDWDtxSQRH4DVUvmHBeApMcCpJpI6BrAUAQHmTVnCwXlQChIWUVj5WyUZLcMpNZKUA6HpIIEZJAGZLYFZJ5G8lowvy8LLlowhA%2BJ5FJJxLGzxNiMJIVwJKdLizLwHmdP9kBIhGWJBO0KGwagvzW3dHBLByHy8IhFhOuPhO4wjLdHf24SEG5K1N5KIKdHtAFODgiWaNaMTg6JBG6NH2R0DwiSeBoVuHaM6OWR6MSV8PoIIwCK/Qxn%2BFWS1zpksgeQxjCKD28lT0wInA7K7J4zdPmA9JJNuL7yN0yOSgbxvzbKW07OAHIytl7LRA73zF1W3LuhKIbVWVizYzuNRI5JVwxKeKnWcBADCz7ghC3MwF%2BMl0lJ2j1NpMNONNNP13DB5CzIIHdPTMGMzLRKZlzKqLxmrIEFrJLK6LqJ7Q4A2FoE4BSF4D8A4C0FIFQE4C8MsGsCTC2B2BbFqB4FIFDUwqQo2BRBABSECG%2BAAA5AgpAUgKRAhJAABOfwNi2ofQTgSQXgFgCQDQDQUgDCrCnCjgXgBQEAUSiirQDYOAWAGARAEAHedIDCcgSgPlOgBIKIeETgVQJi7%2Bdio4YAZAZAI4KQb4MwXgG4QgEgPARk%2BYfgQQEQMQdgKQGQQQRQFQdQSi0gXQeYWsGMdITgHgZC1C9CzQXgSSiMDCDS1MVAKgI4IywIEyyQMyiyqyyQGyo4CACldIXSuFUitYXgeSpC0gCAJAHS%2BgMgCgCAWq8YYAKQeoGgIghIGSiAWIGK0gWICIdoKEcK3gfq5gYgKECMWIbQTABwYa0gTJdsCMaZIagKrAWILwYAaiNVGS7gXgLAFgQwYAcQValomaxwdpHarCzAVQGajCPYMiiIIEFCgKy4WIGMcajwLAXqokM4Oa9pYgbdJQdMA6owS4IwGKjYKgAwdc9EG3WsCsDCsi1y4QUQcQLy5G3ytQXqoK/QQ6lAawawfQPAWIGSyADYVUoBTgb%2BBk78UwfCywMwCS/663LAUmiADYOwM63IFwA0WYPweYMIGUZYcYeYYoFLPmooLIFLJYMYRIeYTmteIWCW%2BWxoLmgQIWGWtuOWhYGYTwboPQCkjoTWlYLgDmoi3YCQSKjgNCsS3qyS1K4y0y8yyy6yswfK3ABykq/wU28qiGjYZsT8cYdm0gGiyQfwb4LiikSQDQSQZIB4DQOijivijgAS0gIS7274ZiwIBijihirgQIFISQLgFILi4IcS2KzgaS2S8iiGqqlS6qtShKzShqpq4gfStgTgdoFgQsCkb%2BQaMMYcLgDi74Lgb4K6/AIgFmvQZG9ytG6QDGpQLGgK3QeoEKjPYaq2m28u7CzgeKggRK1%2BFKrunuvunCQe4e0e14Aq5WYqu4WoMwMqmuyixSmqm%2BuqrSxqt%2B8YY%2B3ugelqji5YvgOgWFLqnqgK0awauaiB8aya6a2a3a%2BagmK0JamZXqtajaras2Oa/aw646rC/Aa8L4C63q6626oEOax6xoXq1696qET6vYLCn6oShB/6wGzAYG3B58WuqGqQhQWGzAeGxUOame1Gzy%2Be2QTG/yrCle3G8GumqwSwImkm%2BAcm9ISmjgamo02mgmhmpmhIFmrEFRvoNWvwCAVwZWkIA0Y2kWjIKW5oCxsW5oax7WhW5oJWvWuYYxxW4uZxg24uCxw24YIW2Wy2zYbYC2025Oreu2zgFZbu3u/ugwc%2Bkese92iepucwb2x%2BiqtYf2zAQOxIYO561O9O4emOikEuikCkfwWOyQdi%2BYbeySquuS2upS1S9S5u7Sr%2BtugyjgLu0ylgBQQsSywsIe74P0QkOy9Jqely2QWesR7y%2BQReqRnQAIUgNesK3aze6KgKuKpupKo%2B4gFgAZoZkZsZiZ1Ma%2B84W%2BzJ/wbJ1p1%2B659%2Blu7pkAYZwYpXUZjipXC56ko59ioBjqmPSgMBrC6Blasi8F2Bs6uaha5B5atBzAdaza8%2BHasinB0Ghhva06ohwxgK0h5AO6ihwQKhl64m2h%2Bh7663Zhsi1h7JDh0Grh5%2BvgaGvhuGhG4RuZ0RiQcRny5Z7GtZpJ4wHRmwV6tm1R9R/YBk/G%2BmiwRm2K5mpywxsmrx5oHm9wDx/myx9AXx0WuxqwzVyW6TBgXV1VgYfxw1lW/odWnx4JrWvxoYAJ21ioEJyJhQc2zy7Z223Z2J/pzKwZ4Zo4L58ZrkQkNJz2u%2BrJ325%2BvJgpygK2kppIYe/wfwFIFIGO5YjQFNtihi71iSyu2waunJ6ikAMOke/wBiwu2odNwIWoNi5O/wHZ/NqSp%2BhSq22yvNiult4t0gf67IZwSQIAA%3D)

## Links

- [source code](../../../../conceptrodon/descend/roadrivore/classic_trek.hpp)
- [unit test](../../../../tests/unit/roadrivore/classic_trek.test.hpp)
