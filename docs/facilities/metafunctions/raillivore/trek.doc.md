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

```Haskell
-- Compose with Mold
Trek
 :: template<template<auto...> class...> class...
 -> template<typename...> class...
 -> ...
 -> Commitment

-- Compose with Page
Trek
 :: template<template<auto...> class...> class...
 -> template<auto...> class...
 -> ...
 -> Commitment

-- Compose with Road
Trek
 :: template<template<auto...> class...> class...
 -> template<template<typename...> class...> class...
 -> ...
 -> Commitment

-- Compose with Rail
Trek
 :: template<template<auto...> class...> class...
 -> template<template<auto...> class...> class...
 -> ...
 -> Commitment

-- Compose with Flow
Trek
 :: template<template<auto...> class...> class...
 -> template<template<template<typename...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Sail
Trek
 :: template<template<auto...> class...> class...
 -> template<template<template<auto...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Snow
Trek
 :: template<template<auto...> class...> class...
 -> template<template<template<template<typename...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Hail
Trek
 :: template<template<auto...> class...> class...
 -> template<template<template<template<auto...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Cool
Trek
 :: template<template<auto...> class...> class...
 -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Calm
Trek
 :: template<template<auto...> class...> class...
 -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Grit
Trek
 :: template<template<auto...> class...> class...
 -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Will
Trek
 :: template<template<auto...> class...> class...
 -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment
```

```Haskell
-- End in Conjuration
Trek
 :: Commitment
 -> template<template<auto...> class...>

-- End in Transition
Trek
 :: Commitment
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
/**** Shuttles ****/
template<auto...>
struct Shuttle;

template<auto...>
struct Shuttle_1;

/**** Capsule ****/
template<typename...>
struct Capsule;

/**** Carrier ****/
template<template<auto...> class...>
struct Carrier;

/**** Oper_0 ****/
template<auto Variable>
struct Oper_0
{ 
    template<template<auto...> class...Sequences>
    struct Detail
    {
        using type = Capsule<Sequences<Variable>...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = Detail<Agreements...>::type;
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
    using Mold = Carrier<Detail<Agreements>::template Page...>;
};

/**** Oper_2 ****/
template<auto Variable>
struct Oper_2
{
    template<template<auto...> class...Sequences>
    struct Detail
    {
        using type = Capsule<Sequences<Variable>...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = Detail<Agreements...>::type;
};

/**** SupposedResult ****/
using SupposedResult = Capsule<Shuttle<10*2, '*'>, Shuttle_1<10*2, '*'>>;

using Metafunction = Trek<Oper_0<2>::Rail>
::Road<Oper_1<10>::Mold>
::Sail<Oper_2<'*'>::Rail>
::Commit;

/**** Result ****/
using Result = Metafunction::Rail<Shuttle, Shuttle_1>;

/**** Tests ****/
static_assert(std::same_as<Result, SupposedResult>);

// The following `static_assert` shows how the operations are composed:
static_assert(std::same_as<
    Send
    <
        Send<Oper_0<2>::Rail<Shuttle, Shuttle_1>>
        ::Road<Oper_1<10>::Mold>
    >
    ::Sail<Oper_2<'*'>::Rail>
    ,
    SupposedResult
>);
```

- In the second example, we will transport the conjuration function to `InvokeRail`.

```C++
/**** InvokedRail ****/
template<template<template<auto...> class...> class RailArg>
struct InvokeRailDetail
{
    using type = RailArg<Shuttle, Shuttle_1>;
};

template<template<template<auto...> class...> class...Args>
using InvokeRail = InvokeRailDetail<Args...>::type;

/**** Result ****/
using Result_1 = Metafunction::Hail<InvokeRail>;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult>);
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
           template<template<auto...> class...Signals>
           using Rail = Send<Radio<Signals...>>::template Road<Car>;
           
           // Helper function for the member template `Hail`.
           // This function transports the conjuration function `Rail` without invoking it, 
           // allowing further process by other higher-order functions.
           template<template<template<template<auto...> class...> class...> class RailVessel>
           struct Detail
           {
               // We transfer the conjuration function `Rail` to `RailVessel`.
               using type = RailVessel<Rail>;
           };

           /**** Transition ****/
           template<template<template<template<auto...> class...> class...> class...Agreements>
           using Hail = Detail<Agreements...>::type;
       };

       /**** Continuation ****/
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
           template<template<auto...> class...Signals>
           using Rail = Send<Radio<Signals...>>::template Sail<Car>;

           template<template<template<template<auto...> class...> class...> class RailVessel>
           struct Detail
           {
              using type = RailVessel<Rail>;
           };

           /**** Transition ****/
           template<template<template<template<auto...> class...> class...> class...Agreements>
           using Hail = Detail<Agreements...>::type;
       };

       /**** Continuation ****/
       template<template<typename...> class...Agreements>
       using Road = Trek<Commit::template Rail>::template ProtoRoad<Agreements...>;

       template<template<template<auto...> class...> class...Agreements>
       using Sail = Trek<Commit::template Rail>::template ProtoSail<Agreements...>;
    };

    template<template<template<auto...> class...> class...Agreements>
    using Sail = ProtoSail<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKz%2BpK4AMngMmAByPgBGmMQgZgDMZqQADqgKhE4MHt6%2BAUEZWY4CYRHRLHEJyal2mA45QgRMxAR5Pn6Btpj2pQzNrQTlUbHxiSm2LW0dBd0K08Pho1XjtQCUtqhexMjsHAD0AFQnp2fnF0cHJhoAgsenANQAIphprozIeJgKj2fXdwel2B5wBtxutwImBYaQMUJMSTcBAAnu9mGxHsomMgANaYdAANR%2BdgR2AhC2IXgcjyErkeJgA7FYGc8EVY7hCoTC4ZgEUjobCmPDESi0axMAA6KWkx7IAwKX4eQRMZZkR6ixjiqUS7D0NiCBSk8kESnU2kMdB8pUtVV83XQxgEBTao1JMkcpkQx7e9UCnl8rmC4VI1Gatgut2y%2BW/ADy72IQpyRruPseFKpBBemBttC9PoOB0eAEkGAA3VB4%2BkANg0cfiiYEJhrjwA7oQEOqEJhqxp7fqnS6axK897GRZHl4skZ1aH6Ulno86wn%2Bna9Y7ndK3Wz6Sy2RCR77uULeSK/ceA6H0ZLN9go0wFdrbsBiJgHQbk7dU5PwsBHgAlVAmHQOcF1eHM%2BSfF83wHG8QBADU9w9VkknZcE7kDf1TyPYMMPPREmC8IgI1vOV7w3YdI1IhUaSIXFiFQVAWFIQ8gxPNwCKIm87wfKVaQARy8T4fg/dMzVcPlmlQOiGJYCTMAEoTyNdd1wU9FMfVwnCzy07C2I41BiO4pTKOjRd4wbBgP1TUTMzAlVc3U70C2LMsK27Jta3MldmzbAgOz89ya34wSGD2JShwPMcJynX8NRAsz6xXRFgsU4jt0ZZDUIPTS2JygNtL0wiDK4qjjJI6NH2fV9%2B0NLdHOin8aXs%2BK7LoCCqugsq4IQlD913XqOUBEFhtBCEgSOYtuWgiy/lOMFxpGkEwTGwsPL/ICnA8x48F%2BJge3WtqIvQgr8t007WL5fTDNK67TPW/BUBEk0M0eAAVF8cT61DU3GrMaAif9AOA/4D2cjz2OILadsePaPIAWU8S0js/DSTqwi6RUvLUStMiGrJ9GzMXoogAKAyK1JR1NHl%2BjwWBYQh%2B1mk4wSp71Cdp%2BmCAPH0x251maYEbQdhmkH6tZ6nVpre7NubQxgPB1ottabs0BhTJ8UeLsX2HMXWby9HMPYorbrI7UhDwYBmFoWqVPFr8Yv/ZqEQXc1LURaXHuSi2rbK0luoKwGycRPGtwGym7b5qnnIACV6eNHioLxQv6BOSE7bs2FWYgWJ5Hto/sjydfD8XnNehBocT5OcnVBMGAUDI2l%2BALZUF4WU8rxoBH2gufPbbZM3CcscUawhmMjn7CzEWhUDbadE7aLXHjSeiwt%2BGJkUeVAAuz8vgC1gBaEgsGzjv%2BmdcfUbOg28P5K/b4xo3OIo8rTZx1/n6Mx26CJBVenxu20zPWpK1ByxdWa811gA5yAB1bsJpDAKCoPEdOLcGBC2XNXU%2B1c1o9w0OqVA3dv7Ej/sjABrNvzTjis7L%2BtAf4kndgXUO30yEZUQmhMBUczhvVriUauosOGpn1vfQ2QihFXTfjxD%2BN0JHkUgtVdc/87YUN/PnOgLVsyMLcHIzqxFuqhjYeLVhYdI4C0EOELwIs5omMLGXCuSdO4MBbmrJQTcuyoPQTNLBXccGHTwXLFBHltE1UHBoIuJdCyRC3nAhAQpHiYFLIwTs2w949iCeuEJ21fillaHgDayBmKEE3gwWgG8p4z12mmH89AYbEGAD4R0YT%2BY2PLr8aGcRRCTkCncDqwTpS91oLQR4cRooayINtVylYPLvUwJ9RERw/YgGUMTVApMkYaFINY1s5dkAdhib8AQJSindjSK0cUUJs4K0hqQvWaNhE3w1FeE2ki0nvjqhw5Rgd5bzm4TMq0jFOb%2B10jQhZOUiZbxWUDdqUFenPzYZs2xvwvGONVsUH4KC0BoLbpg%2BxKcfG5llhaAJNYXkwWHNcqOktunQoUf0wZwzOnATGYPNyPZpmzLcPMt0cElngqEPZRpVNRG3LEcbGRTzZE9IUW88WHy%2BVqOoWyv5dNCCAtYsCrl8EA48qIHK3MiISW%2BzDqmIxWV6pCrvg87GUiKpSgNYoj5qz4raohUHLRkqDRpWMfVX6rx/rdl1UzK4oNml2Krl3aGzcsj0wMNnZuHlnWrK2lgP1wEmAxFQAkgVEtiyZhiRaegriVb3m7C2LWXS8bNmhrDKWuCs3mofiKp%2BMppHWrIo8EOtsCZAMzM63V5NmGcKeBzBmjpA0s1Zuzf5hBI4QIEfmLhSoPEp34WQnO9zbniNbZI82lsxA2wvt6B1Ttvmuz5B7CS3s92euwKq3Ofbg6KyYfuSBgjhVvotRu0VW6ypGXFTQuhf9pVkMJiAg9O4B2ro%2BVQ75B1aHEL1W4WDroIOGP6qaudTkuHvQQdkLuK6yH1pEe%2Bh%2Bm7m02u/eKyq1LXmdoAR81RgzqGgf1e60lIL9FGvAWh59HDTGOAYBY5dVjIGEfuVjcMYrbWsf3ZAh1QN4qKuDlOggt7jzqpvZqoFCbIUseo2xp9g0OGiZ0iRr9ZH37meedJxRPpZXHoXIptww6VOabVUhjVoLe2aINZ6iDJqeOvo/UF0zTaTIWbC1ZvTMnw52fld8rzbVdPyI9TeOF3HDMLUWhceaXCABieBiALEeNgVQrBYTdn4ZlrL/D9zJHCHKLwWA5xuAxXsNIToPxjS4UIBAhECAFrHZyT9oWVKEx631%2BgcLjp31I28sbvWCD9cwAAfS4FN%2B4C6mBpAUF4ap/DRHievLCu47Mts7cm16jbQ7WjEG%2BNnfbxHDazZfpIp6ppMwQ1u/Edbv0lzLbwQ9mbRVHgEhyWmi7o3u0JWIP9r69IzWPZvs939vF5IhTCookDGi2r1VnUoh20GFzsW27ttiKVQrCURKD274OTzYF8%2BTTKAXL4NuG8VCjUmov2odrB9R4Eks6NgvBDjWV0vsN%2B/GVbg3pshYIXDXbjhYR3bey9P7a2PQQYO2KCTx3w5Y5zOB/zhnAus6ByNz%2B5O9jMU3UWTHUPmNuEt2xIs17%2B2R0bezgAUjZw9DssTAHcietHQk%2BTy9oIr2gd2jgu6lMxT3DPcdi%2BysKw7VHksdaA77xqCNaBfKJzd5XiIHd2o81qpgAeE%2BqSZxlrhf2zDS8hGzkHYOYgQ%2BNO96Hy2zBfWT8Fp7ZmIvkSd9F6y9vsegONRTfHjVCftrO6TuSCkKe1TcNT3Jre6eV8n9X9hJuiNm/Z5ZiVXPM8NWnLzpj4%2BoXp66sL94aWd9daeEILwaRUXoD/D8BXDfZWv/f5/87TMahYnc7MnBbJbPkLgDQI4VIR4MADgI4eA0kZicbRbegVbSA6A2A%2BAxAjgZSdbD5OGDRJFBTD6PkP7DQPkbvDVdzFSOCRNRENXTAhZHPN2OgkAe9NwOvPkHApAmgxhdg5zH7LhAA7/fhB1L/cPeKIgloJFegzRVApbFA8A9AtbAzcXLDH4J0BvBYRMZAZbMieIAgCABYdAOCBQcUAwlfUQ8PFAv/dWD/SQrmN0dYH7ZpbsfgAZGeRqDyXQxwfQwwtoLaBQBAcpTWGeFBVALyHIXaF8Jxd/EAY0PQqwpQNoEwggMwkACwtgKwvkA8U9XHREceU9RgyXSgxEagjTdzR3FQzAZQibFbNQskU/VMegnTLgyXNQtwKAlgxGRRRROCTg7gxEXgvA/gxLWjR4DZeqF/N/BwmwrmDkFw4Q6rJaJ/E4GkBoAQYCErMrPbYTK7VYy4ZaIaJ4EsIefEXnQHU3G4/vc3FtI/GhW4WpFXakc4tyWDUDDXA8KDWcahWDZ44ACSWo%2BotAxo5DPqR/GXffW4pHAfF7H9FtQE6LD5d4vEC/b5NEzAT4q/fVWpW/HqdDX6BYn/HnJwqXahGQpgOQkABjPkLE2glYjY16LQnQlofwlIow9IzI7Ilbe8M9ckrgOwuYpQRwwA0kVwlCDgTYWgTgfwXgPwDgLQUgVATgNwawawNMbYXYdyZIHgUgFTJU6UzYHEAISQCUDQAADjMDMAAE5bSuB/ArTLSuAGQGRpBZSOBJBeAWAJANB1lFTlTVSOBeAFAQB1lDStBNg4BYAYBEAQB%2B40hCJyBKAUU6B4hIhxROBVBLSqx94qxJBHhgBkBkBHgpAJQzBeB8RCASA8AzChT%2BBBARAxB2ApAZBBBFAVB1AjTSBdAhSWwEw0hOAeAZS5SFTNBeBgyYxCIkzMxUAqBHgcy8yCyiySyyzzT68IBaY0h0yLk9T1heBIzpTSAIAkA0z6AyAKAIBzzxhgApBUgaBw94gwyIAYgJzSAYhwhWhkRhzeBPzmBiBkQYwYhtAGhDT9TVZ%2BwYxikfyeysAYgvBgB2IBkwzuBeAsAWBDBgBxA4KCswK8AElULlTMBVAGhCJ9h9TwgoRPTlTI8YgExAKPAsB3yTQ8BfS0LSAEliB00lBXhMKjBI8jAJzNgqADBgAFACRvgWw6xFT9TGzhBRBxA2z5LOy1B3y%2Bz9AsKUANTLB9A8AYgwzIBNgoiz5OB95TDnZTBLBrAzAgyuLbssBDKIBNh6gHEXALRZg/AhTQhlhKhqg9BihcNchPBOgArMggqRg/LxghTXL%2BhBgZgQqCgYreh8KBB4qlgKgxgEgYrFhPK9BdC2hIqsqJAXLtS9gSr9AxzSBAzJzOBFzcz8zCzizSzyzNzcAay9ykguADyDThLNguwgJxhnLSBTTJAkgJRbSkh3SNBJAzBJAawNB/AqxbTKqvSfSQAuqJQqwuAqxLTbSXSqx/BJBHTJqqxqr3zgzQzwzeqjToy4zTyEyZzkyrybziBMy2BOBWgWBSwGR949pSJpwuBbSJQuALSqz8AiAHK9B5LmylLpAVKlA1KezdBUgByttfzRyOB5Tzqeypynq5yFylzGq7xAbgbQa8EtzGIdyLz6QNhDzhKTyzyqbdyUzrzmaLyUADAjAgaoC%2BA6BzkXy3yez/zvzfyPyvzALgLQKHAxbILHRoKSl3z4LELkLrYxaMKsKcLlT8AXxGhCL3ySKyKoQxaqLeh3y6KGLkQmL9hlTWL2L9SuKeLMA%2BLNafwGbRLy8JKpKZKxaYbFLWz4bZBVLuzlSUbNKhKrKrBdK6KnLjL2sYizKLL5xI6bK7L4gHKfh4AXKUq3KIBXA8rvKLQiqs4wreEBAC70hwr%2Bhi7/Lkq%2BgmhcrEqvKeh660rFga7oqpghgK6CqMqVha7SqdhyrurVrsaaqVS6qiaVyAbfwgaQaLTHgIB2rIbaauqeqjz1h%2BrMBBqEhhrPTvTSBfSkhgaZqGR/BbS3SkhZr5rjqcagzOArqIyGaYz4zEznrUz2aMysyOAvqVyWAFBSxSzSw56eQFhwaOq6zobZBYaA72z5BEaQ6dANrSA0ahy0LMax6LrOBpyCBZzN5Ca/6AGgGQHjwitKaYRdzV6kh17n6maKGLzWbXqQBAG39ltgHbTltQGCBltVACy%2BanzCtKAhblSRbAKxbRGgKQKwLZb/l5aYKlbMAEKkKp5UL9SNaBKbb0K8K9bM6ezDbkByKTbBAzaeyLbvzraWLbt7beBHb1YXaBK3bbq%2BAxKvbMBpK0RfboH/aJBA6OyEH1LkGubjAdKbAY6s6VT46BBUKDhTDtLrLLBbLJz7K6zM6jKW7Uq/A86PKm69AfLMqS6hTAr%2BgK6imcgO7sr0mHF0qe6c64r27fLiqcru6cmmnCqGmCnB6dSKrPTMHcbJ7CHAHHh2GJQuHF7l605zA176bbqt6d7KBMaD7fS7SJQkgkhAgZqoCNBVmGRdq77aqQzbBrqN6TSQBJB/AJrXSGR/TLTJAHSuBrSzAzrPSkhxy%2BmDnjnVrKy9mJ73m%2BrOLnychTmgA%3D%3D%3D)$Done$

## Links

- [source code](../../../../conceptrodon/descend/raillivore/trek.hpp)
- [unit test](../../../../tests/unit/metafunctions/raillivore/trek.test.hpp)
