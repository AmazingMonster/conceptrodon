<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::TypicalTurnOver`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-typical-turn-over">To Index</a></p>

## Description

`Typelivore::TypicalTurnOver` accepts a list of elements and returns a `Capsule` packed with the previously provided elements but in reversed order.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>n</sub>
-> Capsule&lt;E<sub>n</sub>, E<sub>n-1</sub>, ..., E<sub>0</sub>&gt;</code></pre>

## Type Signature

```Haskell
TypicalTurnOver
 :: typename...
 -> typename
```

## Structure

```C++
template<typename...>
struct TypicalTurnOver
{
    using type = RESULT;
};
```

## Examples

We will turn over `int, int*, int**, int**`.

```C++
/**** Capsule ****/
template<typename...>
struct Capsule;

/**** SupposedResult ****/
using SupposedResult = Capsule<int**, int**, int*, int>;

/**** Result ****/
using Result = TypicalTurnOver<int, int*, int**, int**>
::type;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
```

## Implementation

We will implement `TypicalTurnOver` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  1. Turn over several elements in the front of the list;
  2. Invoke `TypicalTurnOver` by the rest to turn them over;
  3. Switch the positions of these two flipped parts and concatenate them together.

We will use `ExtendBack` to concatenate two flipped parts.

```C++
template<typename>
struct ExtendBack {};

template<template<typename...> class Container, typename...Elements>
struct ExtendBack<Container<Elements...>>
{
    template<typename...Endings>
    using Mold = Container<Elements..., Endings...>;
};
```

Here's a simplified version of the implementation:

```C++
template<typename...>
struct Capsule;

template<typename...>
struct TypicalTurnOver {};

template<typename First>
struct TypicalTurnOver<First>
{
    using type = Capsule<First>;
};

template<typename First, typename Second>
struct TypicalTurnOver<First, Second>
{
    using type = Capsule<Second, First>;
};

template<typename First, typename Second, typename...Others>
struct TypicalTurnOver<First, Second, Others...>
{
    using type 
    = ExtendBack<typename TypicalTurnOver<Others...>::type>
    ::template Mold<Second, First>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIABsABykAA6oCoRODB7evgHBmdmOAuGRMSzxiam2mPZlDEIETMQE%2BT5%2BQfWNuS1tBBXRcQnJaQqt7Z2FPZODw1U14wCUtqhexMjsHAD0AFSHR8cnp/u7JhoAggdHANQAIpjprozIeJgKd8cX17dnAJOvyulxuxzu2FUBFcFiYyAA1t8jsDoSx0gZoSZAm4CABPF7MNgAOhJWOwoMmxC8DghUJhcMRJgA7FYmQ8sVZrqDUeimJjsaC7kK7jyMZgsTj8YxWJgSUSyXdkAYFF8PIImBEEqRBcK8QSZXLsPQ2IIFKCyRSCFSaZDoQx0LCERK1a1NcQJUbMCaCAo5RbAuSuSydULRXzxdi9dLiSSrsBiJgvYwfRbrsK7l5skY7gBZTzoO5Yh53F0ayLu7Ge72%2BkmkO5xhNJ01%2BgMc81sttcv7gtxMdIKLz0JGHFFe3n8yX6mPy1vXSnUgglvsD%2BidkHdwGbn6g/77O4ASTRxuTfNyw/OO63V4vXauYYnUcJstJs6u85pABV8XhRLQP5sGAAeQANwSQtgw7QJOXXO8xzFCVHxlO4ADE8GISZUzfK0FzuL90h/MR/2IIDQIrNxUPQghMOZaD00zCJgBFKVC0CYte37QcI3ItCMNbKD23Zfjb3vLjELYFCeIIOsxMwO4hEwNB7Uw99Fzwgi/wAkCEglCjJjreTFPQajgzTYV6OzKMWLY5dOIlAyBHQOtdKovjoOZQS3OuESEKlJ8JMo6TfKQ%2Bz7UCqdnyJQCCAQBIzVfFTcO/X8iJI7TsWc/SFIcusopi9CW0DEETKuOis0YyyQys2k7QdBkfPCxL8OSzTSIlXLYoKkAQCjTD0y6kTc3zOystC/zePJISio880N2vEdL3uSFWHRWTt1mubgXNMxAgiJUvCwFi3EU7Z0hTV8FsOJcOKHNbYKPcN6ujCLlOwml2JXCNPLBe4hC8dISkwdAACVPkHRdbvMxjfv%2BrJAZBldFyLK6PolCICEOOs0Yxu4scxwR/S%2B3c7nhsHz2BSHidB2hEdYxr1JSrSyLRvH0ZZ7Gsf2TD%2BqlNcLr3D9PnB5FLVPZAAH0mBVBICAgSZ0C6hQZQluK3GhgHgapqTKYRskVg5Dg1loTh/F4PwOC0UhUE4NxrGsO4FA2LZZPMQIeFIAhNANtZ4QCSQiQ0FIzDMABOYOuH8AOUi4JkmWkI2OEkXgWAkDQNFIM2LatjheAUEA04982DdIOBYBgRAQA2Ah0i8KSKAgNA0ToBIohlThVBSJIAFokkkO5gGQZA7ikIkzF4QHCBIPB5a4GRBBEMR2CkWf5CUNRPdIXQZ4Ad2IPtOB4Q3jdN9es8Amvq8XVAqDuduu57vuB6Hv2zDuCAPEb%2BhiELbauBWXgC60GsCASAG74U/uQSgoCm6JGAFIMwfA6DQnQpQWI69YgRDaLifevB0HMGILiQCsRtAKQLm7Bu3pAIMFoFgwupAsCxC8MAXstBaC524LwLALBDDAHELQ/ACYHB4FAmwi2mBVAKRrjsN2aMGjr1oHgWIu98EeCwOvK0eBk7sNIKRWIsMnhcKMPIowns1hUAMMABQAA1D4W9AIEmwcvee4gl78EEIoFQ6haGb30NwlAttLD6AUbnSAaxUCnVyGwzucsiymEsNYMwmdSLECnp8eAaw7AkNyC4e0Mw/AzzCJqJYYwZ4lByAIXJehSlNEWKMRIM8MmCIEAMaYnguh6AaU0ZpQxCm1PaVMDorTCj1P6TU6oxT0mO22BIQ%2BHATbpxPpwG%2BHdu6937oPYeL8IC4Anl/F2v9/4mLWDFJgWBEgQG9iASQgQiTB0CLHDQkgzCSCSKnfwSRg76E4InUgydXZEiSFwVIwco5JH8JIcOtykjzNoVnHOed3YmOLmXYBFdz41wgfXVAH9m6tw4G0FgwEmSdyYIqAw2YuDByJFwf2Y98BEGSdPRxv5F7SFcSvDx69dDwJ3nvdhMy5kZ14KfNFl9r63xWaS7hQ9KXUo0K/d%2BYCwIuzMH/BFhcgEgKxYqsgdcoGfxQGS2BYc040GprFFBaCMH4IcbgzBhDiEOAceQ5MlDqHr3oYw5hrCHGcO4bwi2/DMnCPXmIiR0IHEyPjhbeRijMEqJ2BbdRmi3Y6L0V6P1DFEVmKYBY6xmBbH2K0WypxLLl7uLXl4kA8DDV%2BLiQEmNwTzmW3CQISJ0TWKxKsJYBJQqkkpMbekhomTnAQFcBU/J9pRnLBKVkMpeRBl5IyLO6pPSxl1N6MO5o/Tx0bsaVuhYq7p22G3QuvpB7Ki9N/usTYUyr3xwFQsjgSy769yVFKilVL/av22fS7%2BrtVUAK9qQY5pzKAzO%2Bb8ylDymT%2BGDjHQIjznnguhZnTgcL86IpLuXSuF8MV6pxWwTg%2BL74sAUMBQewEP1ikmLSnZU89DFuZRIVlshy2eItroYIPL0jYP5cfGFnAz5VxrncK%2BN8SNkYo1R8Mkx5VaugX%2BwIAHMOauxTqyB8n9Xkf%2BmLSjwcxbUYIGLVQPcEFmuQRAVBtDbXWq0TZghRCSFOqxRQqhNCA2YAYUwsQ3qtG%2BsMQmjhaEg2pNoaG5AkiI2CFkbQmNSjcTxrUck5NvBU1KH0Rm4x6q%2BDmKsTYuxjAHGMYXsxstq92M6BAMEGtnbrCBNiAO5tTQ2G7DlrWrtFge2Wz7VgRrHSsmjpyaeid6Ap3FKXaUXIO6qm5DG%2Bu/rTST0FEXQt/d7Q5tnpactzb3SL1rumdep2B3738dQ0%2BkzvdSPkbuHpokhnv10pIH%2B/ZarAFHMwCcsYTb44QarZSwIgR/AR3BanAHTI6iCstmh2w8LAMrAuZIfwNzo5MlTikSQYcuCBzMFC%2BOgRTtCuh3DmZo8UOE%2Bzq9oDpFsjOEkEAA%3D)

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/turn_over/implementation.hpp)
- [Source code](../../../../conceptrodon/typelivore/turn_over.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/typical_turn_over.test.hpp)
