<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::Conceal`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-conceal">To Index</a></p>

## Description

`Pagelivore::Conceal` accepts an operation and returns a function.
When invoked, the function instantiates the operation with the arguments and returns the result using alias member `type`.
Overall, `Conceal` turns an operation into its `Typical` counterpart.

<pre><code>   Oper
-> Args...
-> struct { using type=Oper&lt;Args...&gt;; }</code></pre>

## Type Signature

```Haskell
Conceal
 :: template<auto...> class... 
 -> auto...
 -> typename
```

## Structure

```C++
template<template<auto...> class>
struct Conceal
{
    template<auto...>
    alias Page
    {
        using type = RESULT;
    };
};
```

## Examples

We will conceal `Operation`.

```C++
/**** Operation ****/
template<auto...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<0, 1, 2, 3>;

/**** Metafunction ****/
template<auto...Args>
using Metafunction = Conceal<Operation>
::Page<Args...>;

/**** Result ****/
using Result = Metafunction<0, 1, 2, 3>::type;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

Here's the entire implementation of `Pagelivore::Conceal`:

```C++
template<template<auto...> class Operation>
struct Conceal
{
    template<auto...Variables>
    struct ProtoPage
    { using type = Operation<Variables...>; };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIIEAHKQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCUmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnhzsmGgCC%2B4cA1ACSLGn0bIJMjbdH51c3p3%2Bn30uF0uBEwTwMoJMgTcoPB70wULcTC8RAAdOiodhbsgDAoFLcAPJpBLvHKY4ETYheBy3DwMLZiYEmADsViutw5t1hz3hiORaPRADVWngmLF6ApyezOZTqQRbspiKgiMomMAEdKOSyLLcvFkjFyAJ7E25QgAihOJxFJAkRwuIovFmAU6NR5MCOpZZqhbKBmq5YJ5kOh/NQrvtjolUsunN1%2BuACrVmFNgQtiuVqFV6rtIrFEtd7t9Xp9TJ%2B/z%2BgN%2Be1u2FUrGeya%2BwKr5bOpaBZkCERxXiwKbcaHpmDSBElgWw7arlpJHybV25EIRIZRYYx44pBCpNKJM7JHsnR1uQi8aWKmHQACVnV5aPK55c9REE8fT5lz1eFDf5ebp9bGoiNFIW4uCAswgMCQsDzuABZTAWioLx6VnNt50DRc%2BRXV1LmIYAxwnK5HwNWD4MQhwchTC06QZWhER3P893wy4QBALMlzcbDcILdd9yuZtDw/L9PhQh941uATbwo25iKYBCkL3NxAOA0DwMxZiCGNJcizLO4ABVnTvYS5kcZAAH0mDxBICAgCZ0GYhRWEwMyxzccSCCAl8z0va9b0xZYfQ4VZaE4fxeD8DgtFIVBODcaxrFuBR1k2ZNzECHhSAITQAtWABrAJJFRDRkjMMwAE4Sq4fxCuSLhmWZaQgo4SReBYCQNEAsKIqijheAUEBAIy8KAtIOBYBgRAQHWAg0hRchKDQJ46ASKIHM4VRkgANgAWnWyRbmAZBkGA/KzF4c9CBIPBbJA/hBBEMR2CkGRBEUFR1EG0hdBAgB3a00k4HhAuC0LMsizgCRRab5VQKhbjWradr2g6jtRMxbggDwFvoYhTU7Lhll4AatFWCAkHmtJFrICgIDJimQGAKQwJoW8El6iBYhB2IIlaQ1/t4TnmGIQ0CVibRMAcXnSHm14CAJBhaB596sFiLxgCRWhaF67heCwFhDGAcRFbwYgxccAA3Z0QcwVQxZRbY0oiUEGoi2g8Fia1BY8LAQc3PAWq10hzeIWI3zNME9ZdoxMtWKgDFwwU8EwL6dzCtKbuEURxEetOXrUEHPv0PWUFiyx9Fd3rIFWVARxyTXNps81TEsawzE6wOHSwcuIFWOwTZyFwGHcTxOj0MIImGKpRhA4psgEaY/CnzIZ4YBYRkSECe7IgR%2BimIeCnX%2Bpe63yZBjHxZJ9sY%2B570OY2hXie1%2B7xKtgkQGOBC0gOt4LrYY27bdv2w6UgUZo1wOdbGKU8YEyjqsBAmAmBYESF3UguVJCBFRCVQIdUNCSDMJIdabV/DrRKvoTgTVSAtVSqidaXB1rJBKtVda/hJAVQwetD%2BIMuo9T6ulKOw0xokwmhDGaVMaZY2WmwTgrQWCm2ZJtJg2IDAGi4CVVEXACqnXwEQdueg053UztIbOShc7vV0GBH6TA/pa1fu/T%2BoMODgymiiW40Mf7w12jiPWwEVFqI0GjDG5MsY40CGYfGPDBrE1JqgTGCRZrUyiQE0YHijDKK4IBJmoJiCs3Zu9fm3MJa5MFsLUW4t/ZS0YDLOWCsIpKxVmrDWEsdbh22NUo2vdzaawilbG2oIJYO3qCDF2btuae2aQTB0fs0qB2DkoUOusjAR1AOEvgscFDx0TsnCWuiM4PQMbIHOb0IqmILpHRuVgS6DM7pXauAha711TKc5urcEjtwthXHoh8/AQFcFfECo8Kirz0NPRoPz0iL0aHfJY%2B9ehHwGCCjejRt4n3%2Bffa%2Bl9d7zwvvMU%2BAK8ZrA2M/XFDUbEcM4K4v%2BCjPHKNUQVEBmiSBBMgWEomMC4EIMoK/MhFCVHYOZP4EqtVAg4Lwcw9h71OG2G4YTIaI1xqTUhrE0RS0VocCkQjFgChTaHVNlSxcEwNFgMujo2QeidlPXkEYg5OgkikHMZYgGJC37AzFWDIRUMYaqDVRqrVOr4QTD8fEimQTAihKlRElAAasYKojaMTVp4TLapKiZXVBATIeoMXQDJWSOZc0FvknNQsRYmwlmUwQst5YgxqarMQ9T/aNPmaM0g%2BBjZkXaZba2yBba9MEP096gz3aGhGd7cZEspkhzDvMp8vCY5qlWQnJOxIU68C2fdCQuznoWrztaxRxhi42AufAK5jRNY7BskXJulgW5fzbpdV5SD4V9y%2BQPEFfzx6QtBSUHIIKgU5Ahefe9MKd75Axf%2Bpox9f1r0xYB4e68wPYpRbihK%2BKHrWKdZ1Ulabbjqs1bcBNqJk20rAQykN0DSCwPgaMJBDVOUgFKqiQIgR/CVWYW1ejzJaGirQ91CV/USMoP8OgmqzI2rJEkOVLgRUzBsIaoEVDX9OBQPCa/E6HG5NcdDasQOWRnCSCAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/pagelivore/conceal.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/conceal.test.hpp)
