<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::SensibleGauge`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-sensible-gauge">To Index</a></p>

## Description

`Varybivore::SensibleGauge` accepts a list of variables.
Its first layer accepts an operation and returns a function.
When invoked by sequences, the function places the variables into the sequences via a process similar to pack expansion;
then, it collects the value result of each packed sequence and invokes the operation with the collection.

Check out **Examples** for more information.

<pre><code>   V
-> Transf<sub>0</sub>, Transf<sub>1</sub>, ..., Transf<sub>n</sub>
-> Oper
-> Oper&lt;Transfs<sub>0</sub>&lt;V&gt;::value, Transfs<sub>1</sub>&lt;V&gt;::value, ..., Transfs<sub>n</sub>&lt;V&gt;::value&gt;</code></pre>

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> Transf
-> Oper
-> Oper&lt;Transf&lt;V<sub>0</sub>&gt;::value, Transf&lt;V<sub>1</sub>&gt;::value, ..., Transf&lt;V<sub>n</sub>&gt;::value&gt;</code></pre>

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> Transf<sub>0</sub>, Transf<sub>1</sub>, ..., Transf<sub>n</sub>
-> Oper
-> Oper&lt;Transf<sub>0</sub>&lt;V<sub>0</sub>&gt;::value, Transf<sub>1</sub>&lt;V<sub>1</sub>&gt;::value, ..., Transf<sub>n</sub>&lt;V<sub>n</sub>&gt;::value&gt;</code></pre>

## Type Signature

```Haskell
SensibleGauge
 :: auto... 
 -> template<auto...> class...
 -> template<template<auto...> class...>
```

## Structure

```C++
template<auto>
struct SensibleGauge
{
    template<template<auto...> class>
    alias Rail
    {
        template<template<auto...> class...>
        alias Rail = RESULT;
    };
};
```

```C++
template<auto...>
struct SensibleGauge
{
    template<template<auto...> class>
    alias Rail
    {
        template<template<auto...> class>
        alias Rail = RESULT;
    };
};
```

```C++
template<auto...>
struct SensibleGauge
{
    template<template<auto...> class>
    alias Rail
    {
        template<template<auto...> class...>
        alias Rail = RESULT;
    };
};
```

## Examples

We will see three examples that present different use cases of `Varybivore::SensibleGauge`:

- We will pack `0` into `AddZero`, `AddOne` and `AddTwo`.
Then, we will collect `value` members of the results to instantiate `Operation`.

```C++
/**** Transformations ****/
template<auto I>
struct AddZero 
{ 
    static constexpr auto value
    {I}; 
};

template<auto I>
struct AddOne
{ 
    static constexpr auto value
    {I + 1}; 
};

template<auto I>
struct AddTwo
{ 
    static constexpr auto value
    {I + 2}; 
};

/**** Operation ****/
template<auto...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<0, 1, 2>;

/**** Result ****/
using Result = SensibleGauge<0>
::Rail<Operation>
::Rail<AddZero, AddOne, AddTwo>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

- We will use `AddOne` to pack each of `0`, `1`, and `2`.
Then, we will collect `value` members of the results to instantiate `Operation`.

```C++
/**** SupposedResult ****/
using SupposedResult_1 = Operation<1, 2, 3>;

/**** Result ****/
using Result_1 = SensibleGauge<0, 1, 2>
::Rail<Operation>
::Rail<AddOne>;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult_1>);
```

- We will pack `0`, `1`, and `2` into `AddZero`, `AddOne`, and `AddTwo` separately.
Then, we will collect `value` members of the results to instantiate `Operation`.

```C++
/**** SupposedResult ****/
using SupposedResult_2 = Operation<0, 2, 4>;

/**** Result ****/
using Result_2 = SensibleGauge<0, 1, 2>
::Rail<Operation>
::Rail<AddZero, AddOne, AddTwo>;

/**** Test ****/
static_assert(std::same_as<Result_2, SupposedResult_2>);
```

## Implementation

`Varybivore::SensibleGauge` separates cases according to the number of parameters.
The goal is to mimic the behavior of pack expansion in C++:

- If the user only provides one variable, we pack the variable in each sequence separately;

- If the user only provides one sequence, we use the sequence to pack each variable separately;

- Otherwise, the number of variables shall match the number of sequences.
We pack each variable into its corresponding sequence.

Here's the entire implementation:

```C++
template<auto...Variables>
struct SensibleGauge
{
    template<template<auto...> class Operation>
    struct ProtoRail
    {
        template<template<auto...> class...Devices>
        struct Detail
        {
            using type = Operation
            <Devices<Variables>::value...>;
        };
        
        template<template<auto...> class Device>
        struct Detail<Device>
        {
            using type = Operation
            <Device<Variables>::value...>;
        };

        template<template<auto...> class...Devices>
        using Rail = Detail<Devices...>::type;
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

template<auto Variable>
struct SensibleGauge<Variable>
{
    template<template<auto...> class Operation>
    struct ProtoRail
    {
        template<template<auto...> class...Devices>
        using Rail = Operation
        <Devices<Variable>::value...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwA7KSuADJ4DJgAcj4ARpjEElwAnKQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJXCm2mPalDEIETMQEeT5%2BQfWNOS1tBOXRcQlJqQqt7Z0FPZODw5XV4wCUtqhexMjsHAD0AFSHR8cnp0e7JhoAggdHANQAkixp9GyCTE13xxfXt2f/Zx%2BV0uVwImGeBjBJgAzG4mF4iAA6ZEANTaeCYsXoChh2BBk2IXgcdyEjCyWMwAHF4cBMCCTIErNc7iy7mCIR86bD2S9OTC4QjUMjEbi7sgDAoFHcAPJpBIfHK4kGsu4EokEO7KYioIgAJSYdGVrIZTKuKpVPMhXLclr5sPhSORovFTElwoAIpgAG54bY46F45nmllq4me1qGoPBk1G4MqrxZIxsgCecruMPdMrlxAVAljcZZ/M9Pr9/LRxAxFP92BAIC9Yi8mGFSuhpoLDPdMLbcfzFvBvKh3P7Vv5DqFToDYolUuLvq5gbNcdDGvDBtoRe9c6VUfNMZ3BYTEWAKbTGaz8qavZ7sNn2zL6Mx2Nxtfr3ibE7xravhcCna/12/NlhztG1gMHAVHRFScXTdZFb0watAMPJN9TodNoUzVdDRvTc/WbANawIVMuW7H8/1NfNbXAqjrTHfDsCnV0FGFK5gGITBwUYAhEJ3ZDj1Q2h0MzLUdVQAT%2BVY9jOMEZiPy7elf3kgDrho0dBTuctK3obcrmXEkyTwClqS8Wl7wrR95wU0igI5aiwNowV6MYyVzxzS8A3zPSRL1Nd8z3Rdg1UodbIcyDnWnD1cIQnSD0Tfi1yE1zcwYQCNxLaLYU0iznzrBt3ygz9rI7JTgR3ILQJCtSwugiLkUkji3m4mLWT4u4BMS7yxN82F6uk7j6JK4r/1Km4ATG74QT%2BfY7gAMTwYhJjubBVFYF5MC%2Bc5JvG7agXpMxoQicUvCwdC3DQBhtjSJqPOU0b7gAFRzBgFH4YgWGSqUJpU%2ByqtQR4dL0q50HQAAtBI/qs9Md3mRxkDFARJkwVQ0mIO4xzuV9Gz8xkHiGiwoeBRThpBcr0dxm7dIIQliSB9BpUiSHPNaWH4eesFkdR9HMbpHcTQedNLDuLg8YJvH6W%2Byr7XU8mF0B4H7oAd1QRnoeZ31WcRjm0fU7nsYsfnrDuMwRYU8jxbuw4ks%2BL7QR%2BqXqtlqn1StxVid%2BY4SS8NJikwdBdQQrxaA1G3WqEL2fb9gOg8S2UL1dtwNFIIWk%2BNjy3Yt6b/YUQPg8265WqznPEtJZ7DPoYzTNhDQdNrcTYVjtzXYXWvurcWmwe1JPafpzAu/lpWWwo92HoQ3PDiBGHfQAfSYhICAgSZ0FrBRWEwGf/TcQug6TsPvcyX2t4IXEVkG4ftrGoEpv0870CWlaIXWm2pvPwFzav3eI8Pjbx5BUPw/3yO2cg5Ty4DHbMyV%2BRcBTknaEg834ey/iHOKbUo4EBAcXAyRkaTWkTsnI2NcQB1zcA3CBFMW7YTbsDHucDbpX3uqPb%2B%2BwJ5q2QOvJQ7QF4ECXiAFebB178kPiAne/8lCAJziA4%2Bp8M4vxOJfD290EDzVvstVa9BGFyJka/WhHsP4AMQXnK4f896iMEWYMBcc8xV2gXcSQNCRpX30T/fOyDTEYNLlgkyOCk5QPwWQwhrcSHuWbv4ih7dwZ9zppECJitlZpyHhnO49DFo20nqw2eHDF7L1Xvw2EpjhHGIPqgqeqdsAn1bBwNYtBOD%2BF4H4DgWhSCoE4G4awhsFAbC2Otcw0IeCkAIJoCpawADWARJCIg0AADjMGYZIyQuD%2BEmRMrggRAjSCqRwSQvAWASA0InOpDSmkcF4AoEAid%2Bn1IqaQOAsAYCIBABsAgaQETkEoGgZ4dAEhRFXpwVQEyABsABaP5kg7jAGQHDKQiIzC8F9oQEgeAl5QP4IIEQYh2BSBkIIRQKh1AXNILoKBCscxpE4DwSp1TakDMaZwaUCInkalQFQO4vzAXAtBeCoWYyzEQA8O8%2BgqNulcBWLwc5Wg1gQCQG8tIHyyAUAgFKmVIBgBSDMHwOgYIFqUFiFS2IEQ2jJlJbwXVzBiDJmlLEbQmAHCGtIG8xq9NaAGrxVgWIJk4S0FoCc7gvAsDvSMOIZ180rWOC9AhKlSMrUIh2L0iIYJ1kNNoIZHMpqPBYCpVTPA2zvWkFDcQWI%2B9PR%2BuAImowAy1hUAMMABQKI8CYAVrHOpvTkXCFEOIDFzbsVqCpQS/QhhjCtMsPoQyJzIBrFQFdHIXqAWLwzKYSw1gzAHNzRWLAI6IBrDsMGnILgGDuE8F0PQYQIgjCqGMKBxRsgCBmH4c9mRL0MEWKMGovQt0CAGNMfdBQoGbocP0KYQxj1LDPbYf9169DzHaI%2B09NQN0dO2BIclHAamkH2bwQ5zL/lApBWCiFXK7gQFwHCgV%2B0hUirLWsBAmAmBYESOu0gIzJDQkRMkaEqyNCSDMJIP5uz/B/NSOszZpBtk9MRH8rgfyJnJCWX8/wkh5ksb%2BShqlhzjmnL6WWq5tyJX3Lpc8uVCr%2BVfLYJwNoLAvSBABUwRiSYUiIi4OMmF%2BAiArr0M21FbbpAdqUF2vFuhVVEqYCS71iHkOoepRwWljyER3EZRh1lIKXQ2eSHZ8Z%2BHeXSv5QLaEZhhXqYueKyVqA%2BUJBefKorGWxiJeVXMxONAg4JBORAbVeLjX6pta1015rLXWuzXariDqnUNJdW6sQnqbW%2Br7QGobQbf2hq9Q0iNyAo02tjQ0KlibYjJuTKmnYDSM1Zt6bm/NShC2TaPBpitTAq01rrQ2m1bnW3os87ITtuKGl%2Bd7aWudVhB0bbXWOidCNODTq4bOgdFhF1oeXQisNo6X2/ucBAVwYGoFHoqE%2BvQF6mgo/SHepoUHljfoaK%2B5ooHP03vh00d9AH0fQfA2T/IFOIM05PYT2Dmx4NCv0BSpTeL0Msqw9Z48tn7MaHw4R5zWXSN5bFRRqjNHKCIcE8J5L7HAj%2BGSCs6EHGuNyd5wczgqmzkaeuXch59LSsGc%2Bd8jgpm2UsAUF6OGXpbNWkmI5ojCLXOyHc09zF8hvNvZ0CAaEpAAtBbJdzpDlK%2Bc0t0wyplqh7eO%2Bd67zki0eXlZlVl6EuXRWXO01b2Vrys/8rrMgb2U8XfJCnm7tBSfPPqoa1qnVerTXtbb2ai1wabV9cEANqlw3gDurG9mib/rds%2BpmyGsNeLFvLezat%2BNvANtbZ2%2BmisB3eBHYLeCM7pb8t8ErdW2t9a5SNt4A9tFEhntYsD92kPn3%2B3zt%2B8O%2BAAOmhet2Jk77C6l0JBXVhzox/SaB3T3UZ0PV3QJ2AyxxyBx1gLKEAwxyJz6DfQZwPRQJJ2p2gOfWZxx2ZxwIQ3WA53RRCxjwNw4GZWTydwxjTzBAzwlxIClzz3I1IEo2ozGDowEy2RABmURGhGhH8AWTk12QEMCAk31zQ0N1sDU3zxWGGRAEkH8GY2WUCF2QmUkDmS4CmTMEU3WWhHIKkKORl0GSj2hUkPCzI3yzWFzSyGcEkCAA%3D)$Done$

## Links

- [source code](../../../../conceptrodon/varybivore/sensible_gauge.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/sensible_gauge.test.hpp)
