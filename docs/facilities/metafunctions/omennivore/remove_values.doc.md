<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::RemoveValues`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-remove-values">To Index</a></p>

## Description

`Omennivore::RemoveValues` accepts a list of `std::index_sequence`, which indicates distances between adjacent indices and returns a function.
When invoked, the function removes arguments from its argument list according to the `std::index_sequence`s.
The result will be stored inside `Shuttle`.

<pre><code>   std::make_index_sequence&lt;I<sub>0</sub>&gt;,
   std::make_index_sequence&lt;I<sub>1</sub>&gt;,
                    &vellip;
   std::make_index_sequence&lt;I<sub>n</sub>&gt;
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>m</sub>
-> Shuttle
   <
            Arg<sub>0</sub>,
            Arg<sub>1</sub>,
              &vellip;
       Arg<sub>I<sub>0</sub>-1</sub>, Arg<sub>I<sub>0</sub>+1</sub>,
       Arg<sub>I<sub>1</sub>-1</sub>, Arg<sub>I<sub>1</sub>+1</sub>,
              &vellip;
       Arg<sub>I<sub>n</sub>-1</sub>, Arg<sub>I<sub>n</sub>+1</sub>,
              &vellip;
            Arg<sub>m</sub>
   ></code></pre>

## Type Signature

```Haskell
RemoveValues
 :: typename...
 -> template<auto...>
```

## Structure

```C++
template<typename...>
struct RemoveValues
{
    template<auto...>
    alias Page = RESULT;
};
```

## Examples

We will remove variables of indices `1, 3, 5` from `0, -1, 2, -3, 4, -5`.
To do so, we will calculate the distance from one index to its immediate next.

We will keep the first index, `1`, since it represents how many variables we must pass to reach the first target position.
We subtract an additional one from the rest since we only need the number of variables separating two targets.

<pre><code>   1, 3, 5
-> std::make_index_sequence&lt;1&gt;,
   std::make_index_sequence&lt;3-1-1&gt;,
   std::make_index_sequence&lt;5-3-1&gt;</code></pre>

We will pass these sequences to `RemoveValues`.

```C++
/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** Metafunction ****/
template<auto...Args>
using Metafunction = RemoveValues
<
    std::make_index_sequence<1>,
    std::make_index_sequence<3-1-1>,
    std::make_index_sequence<5-3-1>
>
::Page<Args...>;

/**** SupposedResult ****/
using SupposedResult = Shuttle<0, 2, 4>;

/**** Result ****/
using Result = Metafunction<0, -1, 2, -3, 4, -5>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
```

## Implementation

We will perform recursion over the total number of the `std::index_sequence`s.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  - Handle several `std::index_sequence`s from the front of the list;
  - Invoke itself to deal with the rest;
  - Concatenate two resolved parts.

We will use the following helper class template to concatenate two parts.

```C++
template<typename...>
struct ExtendFront {};

template<template<auto...> class Sequence, auto...Variables>
struct ExtendFront<Sequence<Variables...>>
{
    template<auto...NewVariables>
    using Page = Sequence<NewVariables..., Variables...>;
};
```

We will transform variables into types so that we can avoid defining the body of the helper function `idyl`.

```C++
template<auto Variable>
struct Vay
{ static constexpr auto value {Variable}; };
```

The index pack within each `std::index_sequence` will be wrapped into `Prefix` to produce concept packs.
Then, we expand the concept packs alongside the arguments to reach the items at the intended positions.

```C++
template<typename, auto>
concept Prefix = true;
```

`Shuttle` is used to store the result. We declare `Shuttle` as follows.

```C++
template<auto...>
struct Shuttle;
```

Here is a simplified version of the implementation.

```C++
template<typename...>
struct RemoveValues {};

/**** Base Case ****/
template<auto...I>
struct RemoveValues<std::index_sequence<I...>>
{
    template<typename...BackArgs>
    static consteval auto idyl
    (
        // Expand `Prefix<I>...` to reach the unwanted item.
        Prefix<I> auto...front_args,
        // Remove the next argument.
        auto,
        // Collect the rest arguments.
        BackArgs...
    )
    -> Shuttle
    <
        decltype(front_args)::value...,
        BackArgs::value...
    >;

    template<auto...Agreements>
    using Page = decltype(idyl(Vay<Agreements>{}...));
};

template<auto...I, auto...J>
struct RemoveValues<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template<typename...BackArgs>
    static consteval auto idyl
    (
        // Expand `Prefix<I>...` to reach the first unwanted item.
        Prefix<I> auto...front_args,
        // Remove the next argument.
        auto,
        // Expand `Prefix<I>...` to reach the second unwanted item.
        Prefix<J> auto...middle_args,
        // Remove the next argument.
        auto,
        // Collect the rest arguments.
        BackArgs...
    )
    -> Shuttle
    <
        decltype(front_args)::value...,
        decltype(middle_args)::value...,
        BackArgs::value...
    >;

    template<auto...Agreements>
    using Page = decltype(idyl(Vay<Agreements>{}...));
};

/**** Recursive Case ****/
template<auto...I, auto...J, typename...OtherSequences>
struct RemoveValues<std::index_sequence<I...>, std::index_sequence<J...>, OtherSequences...>
{
    template<typename...BackArgs>
    static consteval auto idyl
    (
        // Expand `Prefix<I>...` to reach the first unwanted item.
        Prefix<I> auto...front_args,
        // Remove the next argument.
        auto,
        // Expand `Prefix<I>...` to reach the second unwanted item.
        Prefix<J> auto...middle_args,
        // Remove the next argument.
        auto,
        // Collect the rest arguments.
        BackArgs...
    )
    -> ExtendFront
    <
        decltype
        (
            RemoveValues<OtherSequences...>
            ::idyl(BackArgs{}...)
        )
    >
    ::template Page
    <
        decltype(front_args)::value...,
        decltype(middle_args)::value...
    >;

    template<auto...Agreements>
    using Page = decltype(idyl<>(Vay<Agreements>{}...));
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEEkGkAA6oCoRODB7evgHBaRmOAuGRMSzxiVzJdpgOWUIETMQEOT5%2BNZj2xQyNzQSl0XEJScEKTS1teTUTAxFDFSPVgQCUtqhexMjsHAD0AFSHR8cnp/u7JhoAggdHANQAIpgprozIeJgKd8cX17dnAJOvyulxBZkCEWQ3iwdxMgTcXkctEIAE84dhQaD/vs7thVARXAAxYiyb5HYEElgpAwEuFuAgol7MNgAOjZ6NB42IXgcuPxRJJglhAHYrMKHnCrNdQZTqUxafDZTTMHSmIjUGyWei7lCmAovkJMABHLxvTCkO5qoiagBqzTwTFi9AUHOuXJ5BD5BIY6GJsjphpNZrpduIDqdn01HMCGOlotBd0TdyV8pV8KtGrZUUwAHdQ%2BHna6rkm7l4MkY7somMBMLDAg87oHTQxtnTs3n7Y7nZqLfmu5H2THJZjxcPpX9jnc7SiyYcKZgqcrVeqp52I0X3bzpyOLHdxvK8MgdQJxphVCliJaVwA3MSmkUWPvr0eBXcmF9SkET%2B7KYiYGiqLO5wygucoKvSjKMKw5pXkQRZoC2zyer%2B/54IBcINgQ3Jpp%2BWKTkICCIgQ9BAfOi6psu1qDrGVybp6BFEfQY5fjcgJsUCeH3AAkouC6ME0PSkZx7HscCIHkeBDJMtBUZDm6WEencABKC6oNemB2t4nwPu%2BEqvpi36HHcFh6rWbimUJ1wpuBGaalxG4KbyKksGpGl3p8dLjOgIAgBEWCqAA%2BkoQaIXSXGyRickgvG1wltZaYQdJrJsiZyAANZXMQwAulFJb7o4R4Iaet60LBqB3Hg6AorQCZJhAtUlomuy7HyKSGOgsIAGwaChAFheiUbdcm5V/kwyAIMmCC1l4DA5oYBIdYQC5arFjWJr1aH9TGZWalQgoEAFzTZaQDWNc1ymqepk21pE%2BKWllPj8StxZrWVJ2rWt505N0113H%2B4z3cAj2CAoz2vcZY0ZVloPsh9dwrKdAC02oMQQxEqnDdKnSWWBQlJmDUPth3QysPklaaPbY0mqVQ9lZPuVGmNDvp44vYm8WUZmLJXMAf58SDRYlmWETAJW1a1hhdy47Q%2BMQJV1UQNu8I83zbAC0O8bipqKwIyz0V6bhVmgUu6bqnZFq2WyABSDnck5l1uVpOVuF5Pl%2BWeQXGs2rbwuF1EWq7vk%2Bh7wXewlVsRUW76fnFxsUYqkHMpgmo05l2WC0m%2BWHseDDFWIZUVVVNVw/VcMludeJtT6XU9X%2BfW%2BwN7JDUQf2YGNE0EFNdw0MQAMzXNgiYItlJg69G2qFt2A7Wye2yMTx1U01LXOa5v23Z6R3AwQo9rRm71s2dLWV%2B1Nfj5Pg0aMNrft79SgIR1/fzUPFUj4vlZ15t8I29tlssiwlXoHoPPBQ%2B9wbnRXldTuN0zwbwemrbeb895vy%2Bp4H6UDW4A03vA0Gb9U7Q0ZgfBGcNkbbVRujU6WMy5JmlrLWeghgGkxAOTZObJQGvRoZBCA/90CAMwAw%2BmWlKZUMTHgumTCGawwPtGQ2B8OamyotzXmmB%2BYEByjRIW5ZRZVhrHWBsHCXhyyLorJgaJlZKJUWo6Oulta61wh%2BAyrF7gqWQJsDIV1zJKEslcOR5kzZsi4hbPxLIrYWnxknTUAB5KBxAmxmksfJO2noIGO1NM7QO7tAqh2DL7CKAcCDeSDv5T2IUfZuAjv7O4USpoxK9nEyOcYY5Jh8WEmSKVIZp3iQfLOhUTwEhKgXeWxcD6lwPuXI%2B54T4mG6mfBuMYL5X1GuNX6Pc%2B6zSfsPZab8ZluHsj/IJdCDpHRAcg5eDs14wMBlvHejUkHCLuBXCZ1cpm11QhPWZ2B5kt0WR3Lud8BAPzWYPDZLBrklm2d/Kev9uG8OAWwz6pyXKQK7uvS58DQVJluaMpMKDaBoK7v9WBQNsHopEe0/BkiSxEIPiQqeeJvS%2Bn2hQ%2BEb99EYyxYmEZ4MSzJM0qkukVSEixMQjDLUuUuWJjdkY0RLpNYPG1m/KlJYM4SpAPFMWNYmVuBZXUGWnCDn8PEYI1h2q8acOhUAo5jDmEEKVczGRscJIJV/irZR2DlWlk0eqiW9YpY6tloMrGMZjGmLcC6ixHJZU2OYrpaNhkRJzmEjiPErBqS1h%2BIm%2BNYlpTgkhNCb1bgELbBSKoqOcbGyETRiRdNRtHWc3qbRRy9EK3kL1omu4ABZTATQqAzXqAILxPjnXQyLMLCsnbu29sEpLHl7kXTSmZXDQOLAmBpT4Rk4pYc6RcHRHCvc%2BSfLLtXQFddWTQrwkCIjLgl6d2nSXSutdwdMm1LPW4fwiML3bqikWHy2iEodMjq2stQgvApEKEPFSCgvAyy8aO0WwHQPpHA58KDnpJZkKYvCDQFozAWkkNIhx2ILqQeg9Wq4sGiMod0R2rtTAe0th6HSLDdxL3YYtO%2B3DbH/D4dZoRgAKp8T0pHumHX1AkAgEBA4KGgiJgMIGwPoAgyhi0imZbolsRwNYtBOD%2BF4H4DgWhSCoE4Fqyw1g9wbC2BLcEPBSAEE0BptYaUAiSBZBoAAHGYMwABOLz1R3Nua4MKYU0gtMcEkLwFgEgNBYb0wZozHBeAKBAFhuz%2BmNOkDgLAGAiAQAbAICkRE5BKBoCpHQBIURoKcFUG5zqiNOqSDuMAZAR4pAsjMLwIehASCVT0PwQQIgxDsCkDIQQigVDqDS6QXQXBSA5mIEwFInAeCae07p%2BzhnOARMRAVz0qAqB3Gq7V%2BrjXmt3Fa2YO4EAPClfoJecwgQuArF4KlrQawIBIBKykMrZAKAQE%2B99kAwApA4ZoDLBISWICxHW7ECIzQURLd4DD5gxAUQRNiNoOoqWbMlfgREhgtB4eTawLELwwBzK4qS9wXgWBl1GHEETvAf56jqUpwZs8dREQ7BsxEAkoWDPIliPNlHHgsDrawngSLVPSDqWILERDTxafAGREYezawqAGGyjaD4OYIlMgRyN4QohxDDb6/IJQah1vTf0IYYw1hrD6DwLEJLkA1ioGLVkSniMvIYVMKZywZg4sy7DFgZ3EA1i1D7X4CArgph%2BBm2EeY5RKh6EKJkAQseU/pDTwwQYSeli2C6JjhoswM8zYjz0PoLRc/DCqLYEvnh2h6H3FXxPNeJDh4s9sdv%2BhVukFi7weLB2at1Ya01lrLmLsQFwF1u71mnu2dV2sKaTAsCJDD6QJzkhAgsi84EYLGhJBmEkN1DQ/hOpeZ72FiLIAHssk6lwTqbmvMBc6v4SQ1Rd%2BdT7%2Bt%2BLiXksL7Sze2y3e1y220K1%2B3%2B1uwqzYE4GaBYGvGFERiYB1AMArC4C8xZC4Fcw63wCIGD161kAG2N2kFNzGwt0m10BwzmwWwRxWw4B02/0m3iy23y0RDuD2yHyOwa11DQIwKwMviu1QBuwSFhHBDMHnxe3SxAMgISCKz%2ByEK%2B1uxQFQKB18yw1BwJF7koCh0myRzh31z0JRzRwxwcH1xx34jxwJ3W2J1J3J1oEpxsxpxt3pwM3wCZ0cBZ3W3ZxcQJH1x5y6HWwFyFxRBFx2AM3F0lxsxlzlyUAV2cJFlVz4A1wUC11zF10YH11NyIKGxINkDIImwM0oOtxV19ysEsAdyd3gFd3dxPE4C93yR9zt390DwSGD0%2BCqIL26CyBcB9FLxCB9Gr0WFr1Tx6D6JGKyEGOTzL0L0j0r1aAbzyGmK6IEDmMmPz2b3mNyDjzr36DWKqA702C70e0vwYP7w2w4E4JHxQJtzOz4Nc0u2nzwNEIewkMX1IGX1X0oDoPC1IEi0CAwIP2FH8C8yC0CEP2P3f0YLi04D/xS0SMyxyzyx2zkJkOIGgJ2DgOOxYAUGvCPGvHQJZGVHGBwJnx6xmyyKNxyIN3yMtxv1m3m0WypzoNOJ/02zAN2321UCxJxLxIJKJM9EEOENn0CFWGe3hI%2BwUO%2BxRMlKUNxNAwCnxK8wCn5ICi5JILoE0Ihx0IM0MMJxs11OMMxzMKENx3x0J1cMwBJzJzEHsP1ycLpzCOp0ZyL08Mm28M5z8MHj514CCLh1CLFzDEiN4GiPlwXHiJV0AKSOrBSO13SL0xswpMGwkFyNG3NwKJ0DpJUJQCaJsAF1D2qJ6Ep12FdlKOsADwHyD0qnaJd06KL2cGj16IWO2ITzKDbxm3GPTybMzyKAmNbyGKbxmIr3ry2IHOWN6FmD2Kb2HMbzLwnL7KmIOMs271CxZKYM4AO25NxLuEVMJNTABin1wJIGeMezFMAKXzbk%2BPX1Cx%2BMi28xZBFP8H8APy4GixFOFEfyhIHxhNsH/0kJ1g3xAEkH8B30C2FGizc0kF8y4A8zMC/1C0CDWzXISwANezoPa0/PONPNQul3B26MkCAA)

## Links

- [Example](../../../code/facilities/metafunctions/omennivore/remove_values/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/omennivore/remove_values.hpp)
- [Unit test](../../../../tests/unit/metafunctions/omennivore/remove_values.test.hpp)
