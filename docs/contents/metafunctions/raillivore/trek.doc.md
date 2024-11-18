<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Raillivore::Trek`

## Description

`Raillivore::Trek` accepts an operation.
Its first layer accepts another operation.
Then, it returns two commitment functions and twelve continuation functions.

- **Commitment**
  - **Conjuration:** When invoked, the function instantiates the first operation with the arguments. Then, it invokes the second operation using `Omennivore::Send` with the instantiated first operation as the packed vessel.
  - **Transition:** When invoked by a vessel, this function transports the conjuration function to the vessel.

- **Continuation**

  When invoked by another operation, the function returns a `Trek`
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
   >)
   >)
       &vellip;
   >)
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

    template<template<auto...> class Sequence, auto I>
    struct Detail<Sequence<I>>
    {
       template<auto...J>
       using Page = Sequence<Multiplier*I, J...>;
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

Note that in the following code,

- `Radio` is a `Rail` and
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
       // This is because `Agreements...` will be used to invoke `Trek<...>::ProtoRoad`,
       // which has only one parameter `Car`.
       template<template<typename...> class...Agreements>
       using Road = Trek<Commit::template Rail>::template ProtoRoad<Agreements...>;

       // This function composes the conjuration function `Rail` and the `Agreements...`.
       // `Agreements` will be used to invoke `Trek<...>::ProtoSail.
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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxBJm0gAOqAqETgwe3r56KWmOAqHhUSyx8Vy2mPYFDEIETMQEWT5%2BgXaYDhl1DQRFkTFxCdIK9Y3NORUjPX0lZRIAlLaoXsTI7BwA9BsA1EJ4LEm0eDSY6NsmAGwaQq6XGttUXgydAgB0JhoAggSYBwY/Jn8bgIAE8koxWJhtsomMgANanABqmAUdkB2A%2BnxGxC8Dl2rnOAHYrISACKAqxfTE/P5MAFAmmHOmYQHAsEQtivLno7bIAyo7YeQRMMJxUjbUHg5icrnYehsQQKdGY7G4gj4hjoVlC%2Bqi4isuW/RgEBRc97%2BDEWzEmYmY7b2iW/Jn04FO/4shns6WYM08vlMAUAeXBxDpGWVXwd21VeNJmF1tDtDq22wAkgwAG6oBHnK7BuJhgR3bYAd0ICAlCChd0NCpNvqu70jDptFm2XjSRgl7PO/lJ23zoZqBvlxtN3Kt/jbNvJU%2BtzftjPdrKXzJXXshvotvP549en2AxEwRsVEc%2BUY7YWA2wASqgmGdAf24wnWQejyf6xPsCAQJKPZSnwzhS87fG6a4MuBLqri6TBeEQW7YDuAZ7n6u67EQ8LEKgqAsOKMEem4cEId%2ByGomaNwAI5eIwaxKlaXwxuqNyaqydSoFhOEsGxmDUbRKKIWerZJouUGEQRK5iayxGoIhZGodu/pBiGhYMGeUZMdsL4iomC7bCm6ZZjmdyDqpxZlgQFaWdWVxUTRzwCdyjYiUSbaXl2/69v2pnDkCdn8QplrTmSIFUnpEmQbS0FSUCMlyUpgXyWa77HnW9EYnp7nXkIOleVp8Y6W%2Bh6pWOiG/v%2BoVASFc5hUBXwpncN4Pk4xZ4Ao2xMLmGhNXQdxNmBUXiTFrqDdJ8GyaRCXxehTX4KgZ6aQAKkecLWraekbAAVNtm35TQ4S3veZw7ZtWy7d0jTbKdLkNVcRH6lc2xtR1XUALKeFqznhcNEVslKm6Teh93qQ6mnKNhRB3g%2BLnCXpyYnYKuEsIQdZXTtZ0YT0V0bC5oMEDieIeCwyMELj9qw%2BeUZU/pCNCtoKyqWj20Yxd6rXXD1O3d1zXzY9hiPndDTFg0UJoAcqSnNsVZHv11NU79v1xYDKEUXgwDMLQ6Vk1TWW3rlT4alqQKzS1flqxrgXouVYmHdDQLA5OgFy1GW07YjDD00OGRM6dW3bNgmrY6BzsthzVOu9t2zLYY%2BTeydLOjGzONhy7OwABJVCGDxPC8DAPCQlZQmwpRxI6g1dWnhVfZTIcpotCDPY8zw1BKoYMAoKSNO11m8gInuM03uddT1iaPRZCDLOqYRGVeT0EOK2upx1tC0KgZZdo8jTS9sSTYXR7XRCC2yoNZxBS2r0sALQkFgZ%2BDzUpqLw6Cs/a/o2xeN00q8r5E/%2B1I/IlRFUEGIdNLaV6inFs60a4h2TDsAA6lCfGMcqClx7mgD2DMW7329o1Ku9wiDDx0oAtE1dYE607NeTyBsAEojRMbQqjsn7k2qoBZhZdnRDXfiNThkluFK3NEhKaf8v6/33MVT8WtIH2l1pXOgeVwGJiBClSRZU/zskquQiOu1o7t3SAIH2GMA7HWTjAqBs4nac1pkjFGxpDF%2B2MUHWqcttHu0cAwLwjN45%2B1Zk4sx9o64N3ajggxYs8gokLr3TBXsDEhLzng3qfNA49zuCotKDYNCy05jsCIJ8kEIDpNsTAGZGCVmWMACsqSJHpKcvcZ6GYGh4GasgcUhBj4MFoEfMQq8SztU6pQ%2BgHViDAB8MaLJ4cdj12es9WIogOw2S%2BNU0qtTSx0FoNsWI7YlBnEIdPbMCzlqYFWkCNR4MT6oChp9DQpBtYphLA3ZAFYCntQEJ09pUIkgNEhD8M%2BdxgZkOpi/bh/5vSiL3GkscICLyUNto%2BPsUcVrahsQQa25cR5Wz/DbM5kMjpFQ/DUwRlVbmTKCdnZu3swkS27lWKJ/dsE5xbgk0e9x%2BaRKqfi5Z7wAUTK6hC08Y81kbKhPMnZqAnqZn2V1Q5xy3CnIhqgHKdBxlRiBbwyKaqiKfxEdq8RHLTwMX8Vs2eir1kG2lUi4mhBUWcL1r1C01r3TQnlSavFJVFSCRqoa1xOowieJbt43ajj2YwOAp6lyqrlyen%2BjKQRSUuR8pNFC3Wly8rYoubi5RSz3Xfk0fDN2cZ9pQhTQG/2gdg03QRgW0Uuxcolt8cGpeUzgkMu9s9HuaRkYGDPikq4abLnFiwIWs4TBoioBKcqgy6oCmanoNS0WAYoT3LiAs/5dS%2BlEMSZk8Nb8NWKy1bG4RB6gZCwNRpfGaonXnJdXpCmLjrGWoIKjOtic/Fy00kTEm2tb2wO9X3LBcd0Y%2BJfQ22BEaIKapIke7%2Brw9jqzEFIw10LZ4jzyixI2bgTbzTNnBzWHqfyYvLi6%2B2J6grsN/dErxgHA1ltMWRhGujY4GOfVjEDIcwPRWBcNARaFoM8bEXx/%2BxC6HANPbAsBBUIGIagZY8hRqPI9hoUJoBSiMOMNI9IokFjg6gZ3ZGnhem92QYE2Ckz8as2JtEyHWR%2Bt4WKNdao785UNGeq0fRtujG84lqDaYuWoaZMu3vSTJ9VHS0mO0%2BHaxghfWUeZkBljPnAW6fAyCgGUGxEJoQ3LZNR08rmvtsih1zJbVKPwwRS9OK7ZuAyx6thYd2NcI1dxxSu5TO6rdRZjKhrdYmty4i/LD7Cs/GKxisraaiNVfM5bFzVi3Y%2Bo8TF321Gws3tYeFjhBmkuwX3cZnVGWk0wp6wbMbjCJt6q/IS6bATK2YELTW%2BRXmaNrS07VbRJ1maYgjotbAQhFrow%2B29t7tGqRmH8GEPkXgsC9jcPBOghAQRCS%2BIZiahLGLnrxEIBA8ECD0CJYjrj22DWaQx1j%2BgAB9LguOBq7o3DGhaaP1RESSAoLwOOw1484/wgnQiWs5tRwTBnDRiB4DiJT1xPkMjnmY5dYNSPtiIkaSO1nnXNLi4EHVKq05voc8a1zuNMHeL2TolC8Tr4Vv%2BaQ/J8EeVGfM9Z24fyDl6JuHl0LxXHpsA1Zhqt5xz9NuESa9z6De3LNyevChg2dnM1ncCk58ERLvefDFypGokuQvedAkngsNQ2xS6TtSfHhDXos8cIcYX%2BpCf04HMnjIbDoEqp%2BjTn0vOYEm/1raBP27td6YD/JfEfEHLihkmmY3lfI/24N/xVkqZlQh%2B/fLAvyOABSUKHS6xhMAas8KHdrFZEX2gJejhxE2qmcUi/Pcree%2Br%2BvwLG/JUm/t2e71aBwv7PdIXIugRj%2BD6VrFTAN/n6qkv0zxiQYBzzT0exewRlV0yHsXOmA1MVlxdyaWiCVxVEr2gLcDWn83qzGiM2a2g23xRBH353ylNxDTryyxhWoXhRtxZ0IkIKdyQLd3RAAKjD8zWxwI/jwMD3S3vxD2TRs2fAkxU2q0c3UTjzDQT2ANUjcFgNCz8X%2BzdgADE8BiARh/ZVBWBDgoRc8/FusvAkhwl0AbwURi9rcmAmc6C2JMcCBsdCIuANBNozBxQwAOBNpXD0RxRidbCycKcgQHCnCXC3CPDJx1N1ddZXoCo4lesjlWRoCgIgQzAMV0UDVfx%2B0gRoCrB/CNAMUn8jZOtfxxsMDWRXD3COBki1NMRfwP1CBKdk1TD988pIj6g4k0iTtvC7CvCbC7DycZ9assR6hHBkBScUI4gCAIARh0BfwFBIQRincTDbd55dgDCjCFji90R5hRcSUoR%2BAV415Z47gpghi5ilBGhiwFAJ5ekpY15IlUBq8BA%2Bkjxe5xZtkQA0CwxhjRjGgJiCApiQAZi2A5jWQXI0MYYgRF5QSMj7iGAEi3Akj7UQAUj7duj6AuiSdMBejQjF40iM03BMjWQHDciPooUoVCiTtiigRSiQj8MUjOsowbk9IhAViJZjCGjSYqQLRNjPVXEVC1D1RsBNC/gdDwDlt1dXEbgMEzgBStDBldCZc/c%2BEdduC9cBNitPhhk6cSDDJ9kR47MqQKCZEqCFN4UR51TgBrD0S0SfCMS/Cwj2DapOD9NwMe9D0dt9xhkENdZtSERw94VvTMBdThC3wPS1EKo2dPh6jFjycmioiW1nAQA5EVN/TaTKcji8BPigFvjJjpjZiAxWQ1j99ycvDmTtkCzSZOTKpxSOgBApTBTtC5DvMOBFhaBOAABWXgPwDgLQUgVATgTAywawaMZYVYasEHHgUgFFLspsxYOEEAVsyQV4DQSQLgQkfwDQVsjQMwC4C4MwAADl3P0E4EkF4BYAkA0GuU7O7N7I4F4AUBAGuUnK0EWDgFgBgEQBAEniSHgnIEoDCToDiAiEhE4FUF3IuEvguEkG2GAGQGQG2CkFeDMF4FOEIBIDwCmIqH4EEBEDEHYCkBkEEEUBUHUCnNIF0AqBLFDCSE4B4GbLbI7M0F4GvMDHgi/PVFQCoG2BArAogqgpgrgoXLMG2AgCJiSH/N%2BTHPmF4EfKbNIAgCQD/PoDIAoAgAUsGGACkGcJoH3ziDvIgGiAYtIGiDCAaBBGot4CMuYGIBBEDGiG0A6EnPHLFjrEDA6VMpIqwGiC8GACIhXjvO4F4CwBYEMGAHEHctUPsrwBKT8u7MwFUA6HgnWHHLCB%2BBbJIqOGiFDCso8CwAMvxn2DMtIBKWIFHSUDjCCqMCOCMAYsWCoAMGAAUERGFxLHzE7PHMwuEFEHEDwvasIrUAMrIv0GCpQGsGsH0DwGiDvMgEWDuIfk4EvkmKfFMAHMsDMCvKKqFywEmogEWHaFzhcE1HGD8AqBCFFFmEGAqDyH0UyE8BaFyFSCupmAGHKEqGqC6ETkOr0F2pqFZkepLmeqmDGBuomFsETl%2BrmC4B2uHLWAWEPI4HbNIEvMYs4E4tAvAsgugtgvgsEogFwBQvEv8AhqkuqsWCrAfEGG2tIFnMkH8FeAAE5/BCRJAlzEgrh1yLhabYbjzSBTyCbXgLguALhdzabdyBb5yuBWz6aLgEaDLrzbz7yJzqrZK3y5KPyWLvzlLVLiBAK2BOAGgWAMxCRL5Op/QuwuBabXguBFykL8AiANq9B2rsKurpAeqlA%2BqSLdBnCKKLCzLaK4b6KSKmK1a2KOK9aDajbkJTbzbLb7hhLcJRLFLzgQczBJKFapznz5K46xKfyVLM7FKQBQ7DaTb1LaaHC%2BA6AfldL9KSKLKTKCqa6rKbK7KHACqnLjQXLOkDKPKvKfLNYCrArgrQruz8AjxOgoqDLYr4qfgCrkqqgDL0rMqQRsr1huy8rTz/LCq4gSrMAyqB6rxFbaq/8GqmqWqCqHbOrcLnbZBeriLuyPbBqqqlqrBLAxqJr4BpqkhZqOB5rfjFqRqVq1q4gNqUQ36XqIrnAIBXAPrjrNQwbzrSBLqagoH4H7qahYH/qqgwHah3qgajrQHc4frTqnrPrsHshcGAbehCG/qYaFAobcLfb4bEaezkaC7w6i64Ko7FyhLcbbbE6CaU7pL5gSbMAyb4gKbUquaebzalzCQJbCRVzJAWblzpaA7OA5aHzFaXz3zPz1bfzc6AKgKOA9aeKWAFAMxYKMwzbXh3QRhra8a0L7bZBHaL78L5BXab6dAAhSAvaqL/L6H/arzOBmKCBWLj4Q7iAWBjHTHzHLHrH1RY6DgxLeH/B%2BGNGM6EnFLs7NaQAzHDDScLHabSdYmRjwmIKy7tK1DKAq7uz663LxyanG77KW6kY27XLO7MBPLvLuk/Lxz%2B6Krl6ArwrR7gGSKJ7kAErp7BBZ60rxqF6l7cqhc17xyiqt6d6Kq9606%2BA6qj7MBmqpRT7HHz6JBL6CK3H%2BrPGDAH6/6bB0qtr37P6NhszH7rBVrGL1q0LgGpq8Gah9r3AcG9ATrigiGLqUGMgkGEGMg0HPqMH8GSHbrJhoXvrQbKHwaQaegkHyHIWIalgVhoasXUqGGZbmGSnIKTGzHth8mrHmR1CcabaC5zA%2BGia06hGRHKBfaJGQAzBzb/B/BWyNzlzzzuXCRBblGAmbzbB5aBGZyQBJBWy6bWzdytzabJBabVyGauBAhUr/B/GkaxXJXYbEKRWdXGWnzFgiq0hnBJAgA%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/raillivore/trek.hpp)
- [unit test](../../../../tests/unit/raillivore/trek.test.hpp)
