<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::Skip`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-skip">To Index</a></p>

## Description

`Mouldivore::Skip` accepts an operation and sinks its *0*th layer to the bottom of the invocation order.

<pre><code>   <i>0</i>th Layer { <i>1</i>st Layer {...Last Layer {***}}}
-> <i>1</i>st Layer {...Last Layer { <i>0</i>th Layer {***}}}</code></pre>

## Type Signature

```Haskell
-- Skip to Mold
Skip
 :: template<typename...> class... 
 -> typename...
 -> ...
 -> Commitment

-- Skip to Page
Skip
 :: template<typename...> class... 
 -> auto...
 -> ...
 -> Commitment

-- Skip to Road
Skip
 :: template<typename...> class... 
 -> template<typename...> class...
 -> ...
 -> Commitment

-- Skip to Rail
Skip
 :: template<typename...> class... 
 -> template<auto...> class...
 -> ...
 -> Commitment

-- Skip to Flow
Skip
 :: template<typename...> class... 
 -> template<template<typename...> class...> class...
 -> ...
 -> Commitment

-- Skip to Sail
Skip
 :: template<typename...> class... 
 -> template<template<auto...> class...> class...
 -> ...
 -> Commitment

-- Skip to Snow
Skip
 :: template<typename...> class... 
 -> template<template<template<typename...> class...> class...> class...
 -> ...
 -> Commitment

-- Skip to Hail
Skip
 :: template<typename...> class... 
 -> template<template<template<auto...> class...> class...> class...
 -> ...
 -> Commitment

-- Skip to Cool
Skip
 :: template<typename...> class... 
 -> template<template<template<template<typename...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Skip to Calm
Skip
 :: template<typename...> class... 
 -> template<template<template<template<auto...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Skip to Grit
Skip
 :: template<typename...> class... 
 -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Skip to Will
Skip
 :: template<typename...> class... 
 -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Skip to Glow
Skip
 :: template<typename...> class... 
 -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Skip to Dawn
Skip
 :: template<typename...> class... 
 -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment
```

```Haskell
Skip
 :: Commitment
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct Skip
{
    struct Commit
    {
        template<typename...>
        alias Mold = INITIATION;
    };

    template<typename...>
    alias Mold = RECURSION;

    template<auto...>
    alias Page = RECURSION;

    template<template<typename...> class...>
    alias Road = RECURSION;

    template<template<auto...> class...>
    alias Rail = RECURSION;

    template<template<template<typename...> class...> class...>
    alias Flow = RECURSION;

    template<template<template<auto...> class...> class...>
    alias Sail = RECURSION;

    template<template<template<template<typename...> class...> class...> class...>
    alias Snow = RECURSION;

    template<template<template<template<auto...> class...> class...> class...>
    alias Hail = RECURSION;

    template<template<template<template<template<typename...> class...> class...> class...> class...>
    alias Cool = RECURSION;

    template<template<template<template<template<auto...> class...> class...> class...> class...>
    alias Calm = RECURSION;

    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
    alias Grit = RECURSION;

    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
    alias Will = RECURSION;

    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
    alias Glow = RECURSION;

    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
    alias Dawn = RECURSION;
};
```

## Examples

We will move the *0*th layer of `Operation` to the end of its invocation order.

```C++
/**** Operation ****/
template<typename...>
struct Operation
{ 
    template<typename...>
    struct ProtoMold
    {
        template<auto...>
        struct ProtoPage {};

        template<auto...Agreements>
        using Page = ProtoPage<Agreements...>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

/**** SupposedResult ****/
using SupposedResult = Operation<int>
::Mold<void>
::Page<0>;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Skip<Operation>::Mold<Args...>;

/**** Result ****/
using Result = Metafunction<void>::Page<0>::Commit::Mold<int>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The implementation of `Skip` relies on a helper function called `LoadSkip` to keep a record of user inputs.
The record will be passed to `Omennivore::Press` to invoke the previously provided operation.

We will implement `Skip` by performing recursion manually, meaning the function will recurse only once for every invocation of a member template.
We will showcase a simplified version that handles `Mold` and `Page`.

```C++
/**** Capsule ****/
template<typename...>
struct Capsule;

/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** LoadSkip ****/
// We will use `Items` to keep track of user inputs.
template<template<typename...> class Operation, typename...Items>
struct LoadSkip
{
// If `Mold` is selected, user inputs will be kept
// in a `Capsule` and placed at the end of `Items.`
// Then, we pass the extended `Items` back to `LoadSkip`,
// waiting for more inputs.
    template<typename...Elements>
    using Mold = LoadSkip<Operation, Items..., Capsule<Elements...>>;

// If `Page` is selected, user inputs will be kept
// in a `Shuttle` and placed at the end of `Items.`
// Then, we pass the extended `Items` back to `LoadSkip`,
// waiting for more inputs.
    template<auto...Variables>
    using Page = LoadSkip<Operation, Items..., Shuttle<Variables...>>;

    struct Commit
    {
        template<typename...Elements>
// When finally initiating the operation, we invoke the skipped layer.
// Then, we pass the instantiated operation and user inputs
// to Omennivore::Press for further invocations.
        using Mold = Press<Operation<Elements...>>
        ::template Mold<Items...>;
    };
};

/**** Skip ****/
template<template<typename...> class Operation>
struct Skip: public LoadSkip<Operation> {};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEEgBsGqQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJXCm2mPalDEIETMQEeT5%2BQfWNOS1tBOXRcQnJqQqt7Z0FPZODw5XV4wCUtqhexMjsHAD0AFSHR8cnp/u7JhoAggdHANQAIphprozIeJgKd8cX17dnAJOvyulxuxzubiYaQUXno3yOwIImBYaQMSJMgTcBAAni9mGwAHREjHYUGTYheBwQqEw%2BgYqzXUH/fZ3IQILwEAhwn6gpEotGYDGQjmoIkEklkggUqlsjlcwWBBkgv7ggDybAYDDwADcSOwQMpiJ8vjzrvjPmkmNs7urGFrdUa7iYAOxK3nI1FMdGYnF41iYG0vYhenIS67kykEO6G42gl1Ku6Ju58z3erG4xj%2BsVhq5Ju4RqlPVp0J2ul0Pelxv67O4WJhKO6iJQgKu5pMpgWgvNCrt59sezs%2BjPm7OBbCNgwKL4eQRMCIJUhMmsAFQQCQDeC%2BAlo2LuAgDluDbCRxDuluQAGs7vQqARxdc%2B%2B3h1miTOkYIFL3Ezm8wWo0W51oIU3znSJiGA2RGAIBRR1JMcv1LJVdhrAB1DcGF1C8AwINdGxII0FAyBh8CMZMBy9AM2CqBI9yoZNcNQIMQwEJc7gAd0IBB6IDTBVClK0kXQM8rQve820fLwslI30AwxB5AwSZi/BADsKLuABZTx0AgwQoJg4l4MVJ0HyTctK0ZEzE1U9FLKdTEELzayFWFIhYInesviETAAEcvDeTBF1svMmBFMU3z0hCfyTP9HkwYsgMxLzfP8nT32g2Cou/V07kkiJgGTDM7Pk1UmKaEAVPIpFoyYYBnPCj8MqMszFVbZC7gAJUwZBNiybUAybdhW0cyrBVsnsgv7fkKKFGSRwM8dkEnadZFAhdWLQ/NnjaNScIDGhiEmYSjzimjzyvKhiFQFhuL3XaDrEx8rOfQlX0gj9AvEvtZpfAlVTuz8xvg2yYoAuhUtW8DMXq9L5tIG1/oysaywmxNcukwq5OjAiAc%2B7t7OrO4NoiTDsNwtBiAIoiSPypy7io6paJuxjFKaViOJwm7eP4hxMCEs6xLa1dGDhtiDw8m6CNhKNYhE5NUCx407n4U8qE2O67mJ1BRCaGCHMe762AU4Myoqqaqs02htKht6YfFIHcdM%2B22rkBhJN54TLy%2BNoAyNZBsUW93laVtW11PTXtZyXWUbucradBhK3D%2B0P9Lt7BY4zczPuat1bKcyL8YdqyRqFELXPm9yp1ZHy/IYbYPseu5S9FV7dPevWnr9F7fv%2B/PSWBqVI1i%2BKhSSmvtlSvTYLhpOEhTzLEPbnKpJpjHAnkmMpxm56AxKlmcljkbqtqieGvm%2Be8wPs2A3joUZ/u%2Bb05eTPu2dCsWrG3Pi6HTvMDFK5gCNMiCK9s8xo3yhbISmMb6Yn/oAjUtsSSPwVG6V%2Bmc4yoIsmCQE2DTRYMOHcAAkvyIBs4mjwkOMCZkODATAiZOCUIqAmDoCEBePAaRyHnHWgGDitBaBL1kikAhfJPwpDlncLCzxkzBkvIzN2YcGBpA5FHK4ecfRf3TD/Nyi1xa72NjkOGBtf5EiEciT89sYoMKYSwth6CkI1gIXREwKQIFOI0BrL4dguqCThnIjWCilHsToHw%2BI4jngEFYhERuToUiQmhLCQUojDB8wMNsISXpObEUZq4kxLBdYpFYkLBgIsxaV12ncLmrxIGCOEa4u4MsZFEGiRoSxzDWFpFcR9NqbE5yOFIkHFgeo/GKPSghVRGjMxd2wPQeBZi%2B6fTARpLSRU7gtOse0zEuilJwxySnOGsTaTOSmSQhBhk4I5xuPYxxKRlA1QSW4zcm1Gi8x8UoeRwyvg8OCQGLCaRwkE0iUwJpspOR0kSZkz0qTG5RjKa4LJ1TTHinyQTQpxThKlNwhU4i7tsk1NEfUq8jTXGrLaR0tmPS8pKxIHTQZER3kPUmqmZyTcxQADU2h4CYLEegsyEILJubVZZxKbEbNKvowhwixRw2BfKIUbLiAcq5Z8RqZyhrRQHlSDwLAWCEEisjQuZEr5b00USI5MycxtRQmuBgSsIhiB3H47IIZpIMVFQIVFmssI3QUG0l4QkDDYgSALFcVrUWWnReheYggOWCT3K661ST%2BFvKUaxRptpNQ6j1OVDeXwg6q3aKHPxuoI4CGUQ3BZEDllpvtJmg02Nb5xqFKayeZ8QGPUvoyxZlshQ7MagmUyqD34ggHec5krI2kcMROosZhitFLSNkpHMMU1kgDPF4LleBkArMYa04VicG1jgXsO1q1CgR0PuNgVQrBUQBlwVQ6htDGRmECBERaXgsB2TcGgWuYSeWYNHZsshuDp3b0RlcGKAHQyMmyqMqdIGz792lFGQ0qAiAuKRn2x8YzmXwf1TFZDRB%2BWyTLEezBDcsOhSJLAzAxzf36r5bc5Z%2BHUCEaFFRmjvbdVv3OcNQ138JlGIJGxs1rbUbL07ZAteWMUOoBcTAgB1GZkcag1x499whBeDSMUXmnVaRRlwQs9TmnMjac%2BFLSt%2B63ARHCfbcqsm3C6jwFbOZWbblCg0BKQdZ78HqTikwVWtdAMIndLx8Zc1BPEGALR8tvn/MOByMstZ9a94sTHLZrSrGItz0MiO8EOmzP6bE3l2gUZMY%2BdaLF1mmIHNOZc8fTE7nUsgE1dqggaWu2Yisx5nL9xlyfD00F8MrRHDIAAPoeQSAQCAkx0DlQUP6MbZi3BFYIFKjTWn0DLZJCsekHA1i0E4P4XgfgOBaFIKgTgbhrDWHzBsLYskn08FIK1k7u21gXgCJIAkGgAAcZgzAAE5/tcH8D977XBnTOmkPtjgkheAsAkBoVIx3TvnY4LwBQIBUjPa0GsOAsAYCIBABsAgwzyCUDQCiOgCQoj%2Bk4Kob7SQAC0SRJB3GAMgTdUgCRmF4LzQgJBHN6H4IIEQYh2BSBkIIRQKh1AvdILoLgpA2LBjSJwHge2DtHc0LwVHqoOTDMZvTpnLO2cc7uFzswdwICarSFT085hAhcBWLwbHu3SAQCQBT239AyAUAgF7u3IBgBSDMHwOgJ4McQFiNr0gsRbXEGxGr3gcfmAJ9VLEbQXik%2BkAp/A1UDAdwx6wLELwwBIS8Ix9wXgWAWCGGAOIOX%2BBfaOD6pX07vEuoch2I9qzDQY%2B0DwLEYMCePBYBj1KPA8Oq%2BkD6sQWIxmni16MAPow2u1hUAMJFllHw2K72O494XwhRDiAl4f6XagY8K/0HXlAV3LD6EHxjyAaxGI604Iz6bclTCWGsGYFHs/5UsAn8IA1hPE4tnAIBXAZg/BFcwh5wlgxhFdihsgBBoC9BkCmhFhRgahegvF%2BgpgOhPAug9AwCmgBh2gsDqIcD5hpgiCChFcaChh4DsCJBQDbtthWD9BNdSBkcddOA7gjdmdWd2dOdPtLcIBcB%2Bd7cHtncns181g1wmExgQDSB3tJBAgCR/tAhIcNBJAzBJAUgNB/Akh/suCYc4cQBHcCQkhahvt/swckh/BJBgctCkgeCY9Ud0dMc5CXtccCcPcid9cOQyd/crpvdqdacOA2gWBtRnRGdAVtFSIuB/sCQuAvted8AiBAChdZBRcT9pAz8lAL85ddBQ9lcoQk8NcOBDt3C5ddcgioxUA6JBCTdEj8pkjUivsrcbc7cnQn0zBZDXdcdPcwi7cQiA8fcUADAjBkiuBUgaBitZ5KBo85cU82hE9p81i08M8s9p9c8oJ89C9G9MAS8y87VK9Hsa868G9Tsm88DW8Y8O9uokRs9e9odTsB8h91jR8dhTsJ8p9HtZ958lBF9ri8o18%2BBN8FBt9MBd88Rs9D88jxcCjZBz9ZdTtSjr9V9v8rB79PjgCX9flI539P814cTf9/8EhADPh4BQCGg8CICoC6CYCQhiJKDlgkDMgUDchmT0CuTMDmCqCSD6TwDmgCC0CGCRSyCCD2TEDbBxTeSGCZTBSOS2DNgOCnczCajeCzt%2BCWjWc2jzcUi0i3EJDMiqUHcncXd5DSBFCsBEgVDodYdSB4dAgUjdDnR/B/sIdAg9CDDnDaiUdOAvCscIS8dCdidSc/cJiIi2BOBoiTdcltRN1tQOiBRJgMipDBdFdETj9kTJd5Aij0SdBLClcVdKitStc6jOA9cScORDdEyFBky7hUyUj0yoxrdRifc%2BjAhAhBiwyRjKcfdxiuyxhkzNMRtWyRt2yRtVAWcw9FiDpliY8tiNjHtVz09M8HBs99jBBDiNjbiTjS9y9aALjq9kRrjfjq88Bm8dQaS5cniu9XjdJ3jeBPjh9sQfjx95UATeAgSF8Lzl9wTfDISapoSd898ETci8yJAUSpcizL9SzpjjA78bB8TaSzsiSS1OBdhptb8f9LA/8dcADHMaTn9cDRSXBiIJTWT0BZScCMCcgaLGKygVS5TSD8DBgaKOKBByCmCKgWClSuLFT5SFg2Kag1S7tODodtSPC9TGzmzWyCR2yrdJCsieyrSfCccFDMAlCHSqjnT4cAcCRez/AQdnDEdeznQkhvtAy%2BC0dbBvChi3sQBJB/BNDwdnREdvtJAgcuBfszA3DodAgqygyHLnKzCec7LdTwqbTZ8shnBJAgA%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/mouldivore/skip.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/skip.test.hpp)
