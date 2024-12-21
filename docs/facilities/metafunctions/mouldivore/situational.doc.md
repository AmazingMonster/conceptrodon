<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::Situational`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-situational">To Index</a></p>

## Description

`Mouldivore::Situational` accepts a list of predicates and returns a function.
When invoked, the function returns its first argument if the argument list satisfies all the predicates and returns its second argument if otherwise.

<pre><code>   Preds...
-> IfTrue, IfFalse, Others...
-> (...&&Preds&lt;IfTrue, IfFalse, Others...&gt;::value) ?
   IfTrue : IfFalse</code></pre>

## Type Signature

```Haskell
Situational ::   template<typename...> class...
              -> typename...
              -> typename
```

## Structure

```C++
template<template<typename...> class...>
struct Situational
{
    template<typename, typename, typename...>
    alias Mold = RESULT;
};
```

## Examples

We will create a function that returns its first argument if the sum of all its arguments is less than ten and returns its second argument if otherwise.

```C++
// `SumLessThanTen` is the predicate
// that we will pass to `Situational`.
template<typename Initiator, typename...Args>
struct SumLessThanTen
{
    static constexpr bool value
    {(Initiator::value+...+Args::value) < 10};
};

template<typename...Args>
using Metafunction = Situational<SumLessThanTen>
::Mold<Args...>;

static_assert(std::same_as<
    Metafunction
    <
        std::integral_constant<int, 1>,
        std::integral_constant<int, 2>
    >::type,
    std::integral_constant<int, 1>
>);

static_assert(std::same_as<
    Metafunction
    <
        std::integral_constant<int, 10>,
        std::integral_constant<int, 2>
    >::type,
    std::integral_constant<int, 2>
>);
```

## Implementation

We will implement `Situational` using partial template specialization, where we separate cases via constraints.

```C++
template<template<typename...> class...Predicates>
struct Situational
{
    // Primary template will only be selected
    // when no specialization is available.
    // In our case, it is when
    // (...&&Predicates<IfTrue, IfFalse, Others...>::value) evaluates to false.
    template<typename IfTrue, typename IfFalse, typename...Others>
    struct ProtoMold
    { using type = IfFalse; };

    // This partial specialization will be selected
    // if (...&&Predicates<IfTrue, IfFalse, Others...>::value) is true.
    template<typename IfTrue, typename IfFalse, typename...Others>
    requires (...&&Predicates<IfTrue, IfFalse, Others...>::value)
    struct ProtoMold<IfTrue, IfFalse, Others...> 
    { using type = IfTrue; };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxCBmXKQADqgKhE4MHt6%2BeqnpjgKh4VEssfFJdpgOmUIETMQE2T5%2BgVU1AnUNBMWRMXEJlfWNzblD3b2l5RIAlLaoXsTI7BwEmCzJBmsm/m5rG1uYO3sAnsmMrJgAdDc72ADUyAYKCjdXysSY%2BKJrCncmGgAggoCMQvA57kJCF4mIVmLQAYCTAB2KxA%2B4Y%2B4Aeix9w%2BeBYDRO932m1hmHuAHc6LR7gJaMTYvd2mt0IjMdjcZSEIx7gxUMzzsg8GI8AAvWGZe54BT3JgANyYdCY0XoV3ZmJx9wAkgw6YtHkwlKRpQRpbLuYwNRitRA3uYAGyOj5fPA/TB/XbaqgAFTBmBN3oAYmJjfcAPIEHnEV63fzYEAgRXeTAze6YZMw34kgVUUPXa0k9Zk7a7AhnC5sHW%2B/0m8vnZhV4P5usVxvXG6R6Oe7CFkFgiEfVBEACynjZ6MxKIs9y86SMJIr9x2ABFqyHaEodjOUSvt4jC1qfQgZfdkt0RbSFELL%2BLJQIqTT7kyWV9D7i8FR7nbbmYnX%2BXW%2BclPTcb0/S8AN1xbCMoziWN1XjRNM1Tc0SX9dVJwxUlDmOetKwpMDa0XBtLigzdILw9s3i7OD/kw%2B5PgARy8PBPllH91T/Z1PiA35jkIiDAyoDcwxomN7UQpMxAgmY%2B1BcEzSHUdx34mtBLI0TYPEuMHkLadZ3nYBiIpVdq3Ao5/B3ZE90sg96Ow8lcLbS43kBYBPnWRgCB7Qs5zCIyx1odBl38NclNQQK2V2NyPLYQR4P%2BWygV3fdkqBLEACosuynLcqxRFMuy%2B4fQ9bz7hy/L0ty6qKrspEzH8MIni8LAQrcNAGGWZJvLopF0txEwHQ0IQfGCD0FGPQwSoYQaNFQ2Czx4t1HP6kkEFhKkKWpWhaXPF4c2XIaoQILNMjEWaMMBBzS1OEimwYDJYRIVs7o7K5AWIYAfKBfsFMhUbxsmhhpoPVE5MlZBHgEEFMFUZJiGfVBPHuZC9NRCBdUeoh4iklNrHtSwPq%2BpDpJQ457i4DQUqSpFrNSvqruLHCy2cthXM%2B77AT8hcR0weoqC8Tq4RCtdjtOgRzt2EaWDGl4gZB%2BNEUTSLjiJhLFZpxEQQhgB9I0lEaCAQXQRMFEuPWQMLXn%2BcFjoZvo45Cw5Y3EzCNZ3LEHWOu1wRjjdk0uDuUgncxF2QDdzAPdoL3ofqX3dn9%2B4zF6jk7kTPDg/osOI6jmOGB9gg/cEAPeruWTNZ%2B%2BpHGQC2DYII2CBNkAzbYC3Hfo62mAFoXMj03YQ4xbPBEj4hPe9uPC4T4uKap%2BNM8BDlncb13h9z8fDEntxE%2BTxWHckjO5KbnPR%2Bj9f4636ed97ZL43LiwODmWhOAAVl4PwOC0UhUE4NxrGsZkFhLBMg1HgpACCaAfnMAA1iAB0/grj%2BAdFwZEAAOZ%2BABOSQKDUHPzMMiZ%2B%2BhOCSF4CwCQGgNCkHfp/b%2BHBeAKBABQ8BH8H6kDgLAGAiAQALAIMkLwBByCUDQBsOgcQIiXE4KoFBDoAC0DpJD3GAMgSGUgrhmF4K6bGeATZJH4IIEQYh2BSBkIIRQKh1DMNILoJIlJR7JE4DwR%2BL834QK/pwcMfDeFmlQF%2BSRMi5EKKURTSQqjvweGEfQBG5h/BcBmLwJhWg5gQCQEI5IIiyAUAgCktJIBgBSDMHwOgawYyUGiC46IYQiT2N4OU5gxATjhmiNoaoTDQFCLigQcMDAGQuKwNELwwA3BiE3FU0gWBCRGHEBY/Anwajyg9C42G1Q%2BErFARHJ%2BFjaB4GiKPOpHgsAuNBASEZcziDRDSJgFc6xDDAE2UYCBcwqAGC%2BgANTwJgSk4YGwjN0cIUQ4gjE/NMWoFxVj9DXJQH/Sw%2Bgtn0MgHMVA3VMj0I4NI42q5TCWGsGYahJziBaPmXC2wmB7BwhcAwdwngWh6BCGEPoZQBhJHyBkAQow/CMrSMyhgkx%2BgVCJSS2owwmiUrGHy5pAqJi0qmAy2wgrWV6G1o0bl9KKhzAUIA5YsxCEcFfpQlxND7i%2BNkfIxRyjglmG/LgQgJBlwgNiWA%2B5cweRMCwPECA0CQCSHgeg/wyJJAaEkGYSQQ0NDPwdOgrVxDSCkOiVcJBDoUHoJQVwB0z9JBcAwYg3VFiaF0IYfa5hiSOFJK4R4vhAjMmoHCaI8RHAGgsHlMiaRTBHgGAXFwdBVwuBXE/hokgWi9A/P0f86QgKlDAosbofJNimB2O4Cw9ZOqqG8Boe4nhfC6RfjrQ2ptLbrkUw7V2uaEAwmpIiTa/wZg7XxJYcWrJETy13oGFuxtTxrntspgU2gRT6EQFKRYmplS52kAA3UhpTSHAjLaV5Tp3SpmYD6QMoZyLQFjOuZMz%2B0yxVzORT21QSy1gjLWS4zZ2yiR7JWJ/Q5pCgMnLOUoS54ybn%2BXuXwJ5ChXnvM%2BYwb5sgh2GJHbIIF5jP6TrBXcjFVgoUkdhW6r%2BiLoacFRY3dFkKLDYuXbi/FMnVXErFc4CArg5VJBpSUHleQOVwiMykCzmQlXTEqLpu2XQRjCrZaKpzgq7PSoVUKnIbmfNeZVfMRYGqYlasXXqzgcpiD1sbc219baD3dotfgbG56YlxIdaQJ1LrKCOI4JG6NHb/X4PQciZE/gA1BrTVm6hnBc2MJY2wzh3DPEPsrae6tbBOB1v8SwBQ8pIbynbVcQ4IJ1Gpb7do4xvyDESAEyYsdwmdABFINO2dDjwvOOzW40tXjN0xb6wNobI2xtmmPR1tJ57/BXqa8ky796MmPviIN5IyQdbDfQTrM7etDsjsKXBEpZSKl1JGSB%2BpjTmmQcre0mDJwenwf6YMnayHeCoYmRRtHrEsPzIsYs5AyzCPD3WZ/EjOyTjkYOXi6joDaPnIY2h5jBbWNMBeW8j5XygODr%2BfxmbQmQWrdbcYVT0Lojabk3CZFWIXYSaxTiuIeKsDi5ZJkMlFK/PUvJYF8zBRMhWaZXCbXDn%2BWdFla5%2BVjm4TOZ6JKsz4wXMa/tzb0zyrNVqpC4Y/LEWdscGiywI7g2UaneAudy1aWokZfzQkx1mBnUDFk%2BswrCQO3%2BH8M/Z%2B/rKYaFT8ieNtXl31dsHm69Mx3WINjf4FBiQ/XPy4NX5ESR1n%2BG23V2hUfIFarUfn1xbeS9zBOekZwkggA%3D%3D)

## Links

- [source code](../../../../conceptrodon/mouldivore/situational.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/situational.test.hpp)
