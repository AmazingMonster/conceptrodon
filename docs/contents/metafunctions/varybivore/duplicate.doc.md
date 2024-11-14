<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Duplicate`

## Description

`Varybivore::Duplicate` accepts an variable.
Its first layer accepts an amount and returns a function.
When invoked by an operation, the function creates copies of the variable of the amount and instantiates the operation with the result.

<pre><code>   Variable
-> N
-> Operation
-> Operation&lt;(1, Variable), ..., (N, Variable)&gt;</code></pre>

## Type Signature

```Haskell
Duplicate ::   auto...
            -> auto...
            -> template<template<auto...> class...>
```

## Structure

```C++
template<auto>
struct Duplicate
{
    template<auto>
    alias Page
    {
        template<template<auto...> class>
        alias Rail = RESULT;

        template<template<auto...> class>
        alias UniRail = RESULT;
    };
};
```

## Examples

We will instantiate `Operation` with four `0`:

```C++
template<auto...>
struct Operation;

using SupposedResult = Operation<0, 0, 0, 0>;

using Result = Duplicate<0>
::Page<4>
::Rail<Operation>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

One way to implement `Duplicate` is through recursion.
We start with an empty list, adding the variable while subtracting the required number of copies until the number reaches zero.

Our method will be different.
The goal is to generate all the copies 'simultaneously' in the sense that there are no intermediate stages.
We will achieve this by pack expansion.

We want to bundle the variable and each index from a `std::index_sequence`.
Then, we will pull out the variable from each bundle by a pack expansion over indices.

First, we need to create a `Bundle_v`:

```C++
template<auto Variable, auto>
static constexpr auto Bundle_v
{Variable};
```

The entire implementation is presented below:

```C++
template<auto Variable>
struct Duplicate
{
    template<typename>
    struct ProtoMold {};

    template<size_t...I>
    struct ProtoMold<std::index_sequence<I...>>
    {
        template<template<auto...> class Operation>
        struct Detail
        {
            using type = Operation
            <Bundle_v<Variable, I>...>;
        };

        template<template<auto...> class...Agreements>
        using Rail = Detail<Agreements...>::type;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;

    template<size_t I>
    struct ProtoPage
    : public ProtoMold<std::make_index_sequence<I>>
    {};

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEAf6kAA6oCoRODB7evgHBaRmOAuGRMSzxif7JdpgOWUIETMQEOT5%2BQbaY9sUMjc0EpdFxCUm2TS1teZ0KE4MRwxWj1QCUtqhexMjsHOaBEcjeWADUJoFuXo60hACeZ9gmGgCCewdHmKfnyLPoWFT3jxezwImBYKQMILObiYl1QxwAas08ExYvRSMcYUQAc9ZkxHMhjmgGLNMKoUsQMbDjhYvAx0PQAPoAN0BJgA7BZEcRkajMOyACJnKzPQEgsEQvnnTFwrk8%2BjYp6zYheBzHflecF4USQkUcwHHA3HMXgvGStwEG4pRisSUPZ6G45KlUEY7KYioIgAWU86FOerZgsCwqBTwdxolUIyAC9MAyCAA6RMASQVDqdqrdHtQ3to6EjBHQIBAESwqgZSgAjl5GNsoUnE/GAYE7aHDezgw6w6CTZDzuHTVDpQ37oSDAoFMcAPJW4h4rKpzsG9Mu/mYJp0fWLv0drcOrwZIxGy0fM78qczucCTe7g1Qml0xks86ylFo44p5vD5tC6%2BdgU/kV7S3fte3NbsIylWEv2wUcmHHBsnmAYhMFBRgCAUBdF33CJgGOAAlJg6E%2BM9V3XWgoUQ5DUMEBRoKLC0rQA1tbwDJjfxAs0GOtNgEKQlC2BozDjmww8c19U9XXdL0fQovjqPQ6C2KAg0OMjPAYzjd8hOXSSs2UJhgD5ZTjhAY4Ui8VEtV06Tc3zQsQBYJgAGtYxLUly0wKsazND8Hm/Yz23/INWWM1TIKIXiqIE9ChJE3D9MM4jrNQBKzUo/i0NoxMm2DILcueAB6AAqErSrKgrAWKkqABVsCEarSoqwqypaoqmpDV4GEOLwTihS46FuBVRXAgdwtQRScQIZVVWnBJLwYJSnji44hA1QpMHQPDMAULxaBdCTZtnXooQ0dFTuOc6NBykKloPXCtp2vakvVTVtTNK7/KeItUqhSQFSLAiN3OQ75uuwDFSafEGTgpQWggH4iwUG1oYw84Ht2gh0VWlJ1s27aMfuFYhQ4NZaE4fxeD8DgtFIVBODcaxrEdDYthPMxAh4UgCE0Em1icgIzHjNkzEkAAOUX/A0ABOfwzA0AA2UXgjJjhJF4FgJA0U6qZpumOF4BQQFO7nqZJ0g4FgGBEBADYCHMzGKAgNAwToBIohtThVFF%2BWAFp5ckY5gGQAkpHjMxeA2wgSDwQsuBkQQRDEdgpHj%2BQlDUHnSF0OOAHdZxSTgeFJ8nKczvXJ0ue3jlQKhji933/cD4PjlDsxjggDwXfoCk9i4FZeBNrQ1ggJBnZSV2yEdseJ5AYApDMPg6BBYhDYgWJM9iCJmhuQveE35hiBuSdYm0OoTc553osnBhaB303SCwWIvGAaFaFoQ3uF4LBHKMcR7/wZC9QmTbUzqSOolwdicwiCCFWNNrixFnIfDwWBM5TTwBrT%2BpBgHEFiOkTAq4f7AGuEYHmawqAGGAAoeEeBMA51mlTTm/AE6iHECnJhacVDqHvtnfQhhjCM0sPoPAsRDaQDWKgFIvQP4%2Bx%2BKeUwlhrBy14KgbB3IsCiIgGsWo9RnAQFcFMPwccwgLHKJUPQhRMgCAMeY9IliGBDFMaMOO2jej9EmJ4doegXENDmA4kYiRnFzGsYEgYfilgBK0SzbYEhi4cApqQHWyjOB129n7AOQcQ6SDDu3XAUce7sz7gPUhawECYCYFgRImjSD80kIEeMUtAhskkBoSQIt5Za38PLKW%2BhOBq1IBrDm8Z5ZcEVlLUWIz/CSC4P4Bp8sEll04AbI2XNSHmytiPG2ldLjkEoNPbu7s2CcGaCwJkbIfZMFgoeLgUt4xcHjDTSORA1F6HYYnVh0h2GKE4ZnXQC885MALp/WJ8TEm004BXO2lxq612Oac85lzcLXNufc9undx7d1OOzMw/cVmm2HqPVAXcEg7KdoS9FoxYVnMOHw65XBTo0D2gkVe6977723rvUgbLD7H1Pg4Dll80LX1vpnR%2Bz9X7vw5d/Phf8aYALPngYBH8HmqHASCDl0DuiZ3gYgm4yCdg0zQRgzm2DcFKAIdKnCqzyEGSoTQuhVoGG8FeSw5OHzZBfIztwkAC8DAkPkVYQR8CNHiMkVkaRsjAj8n9Yo3WqiY4gLEV0HoWQXB0mCSEOkYSzFxwsb0dNuashZqcUm%2BVAg3GtA8XkZx3RS19F8SY/xXigmVsMeMUJDbwkxPWJsaJfcelxNLvfPWGJiAnLORc6lVybl3I0Dk/ATzMUcxxYPXmpBSnlNGFUlWfSBk3JaWyGZbI2SBFaZIf2cdQV6yWcbVZFtra23tiSvZbsPYcGOY3FgCgmQEiZEiiUswI7zujrHVObzXWpw9Vwmmuhgj/MBUXftIKFkcAhVXGuI6WAfq/T%2Bv9ppZiorJRPRdgRl23oJUSyeuzCPdxAN%2BnGzJrkMn/QQaGo7/aL0ZSvSgLKaZcrvpzPjPKz78sJVfG%2Bd9ZWYCfi/MQErMFSt/vqr%2BeBAGOEVaAlVyAIHqsEJq%2B%2B2rt56tQdyI1vATV4PNb/S1eK%2BAUNtbQ%2BhHLnVJwkG6wQkGfkgGVnwlAAibBBvgCGqRnACoI2jZYJRtM43qMCyWnRfg9FppbXoYxZRG05tsXm5LGWiiFo7dmuLrjm25Fbd4st9a0udpCe4krTb22VezZEntydgWDt1sk99AdP3fuOL%2Bm5zG515MXYU3FQ8SllIqZQWJO7vU3MCIEaoLS6UaHm2yRW8yh2LNsMsldKw%2BYgEkGyMOB6uBSClvuhpXA2T9sCG1pJ%2BtRurpVuHDb7WHu7bWNgjIzhJBAA)

## Links

- [source code](../../../../conceptrodon/varybivore/duplicate.hpp)
- [unit test](../../../../tests/unit/varybivore/duplicate.test.hpp)
