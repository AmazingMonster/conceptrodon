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

The implementation of `RemoveValues` is similar to that of `Omennivore::Insert`. We will perform recursion over the total number of the `std::index_sequence`s.

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

We will use `Prefix` to enumerate arguments like in `Varybivore::Amidst`.

```C++
template<typename, size_t>
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
    template
    <
        // We use `Prefix<I>...` to enumerate `FrontTargets`.
        Prefix<I>...FrontTargets,
        // We drop the next argument.
        typename,
        typename...BackTargets
    >
    static consteval auto idyl()
    // Note that `Shuttle` is instantiated by values
    // extracted from the template parameters.
    // This is because we will pack every variable
    // into `Vay`.
    -> Shuttle
    <
        FrontTargets::value...,
        BackTargets::value...
    >;

    template<auto...Agreements>
    using Page = decltype(idyl<Vay<Agreements>...>());
};

template<auto...I, auto...J>
struct RemoveValues<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template
    <
        // We use `Prefix<I>...` to enumerate `FrontTargets`.
        Prefix<I>...FrontTargets,
        // We drop the next argument.
        typename,
        // We use `Prefix<J>...` to go across the distance
        // between two targets.
        Prefix<J>...MiddleTargets,
        // We drop the next argument.
        typename,
        typename...BackTargets
    >
    static consteval auto idyl()
    -> Shuttle
    <
        FrontTargets::value...,
        MiddleTargets::value...,
        BackTargets::value...
    >;

    template<auto...Agreements>
    using Page = decltype(idyl<Vay<Agreements>...>());
};

/**** Recursive Case ****/
template<auto...I, auto...J, typename...OtherSequences>
struct RemoveValues<std::index_sequence<I...>, std::index_sequence<J...>, OtherSequences...>
{
    template
    <
        // We use `Prefix<I>...` to enumerate `FrontTargets`.
        Prefix<I>...FrontTargets,
        // We drop the next argument.
        typename,
        // We use `Prefix<J>...` to go across the distance
        // between two targets.
        Prefix<J>...MiddleTargets,
        // We drop the next argument.
        typename,
        typename...BackTargets
    >
    static consteval auto idyl()
    -> ExtendFront
    <
        typename RemoveValues<OtherSequences...>
        ::template Page<BackTargets::value...>
    >
    ::template Page
    <
        FrontTargets::value...,
        MiddleTargets::value...
    >;

    template<auto...Agreements>
    using Page = decltype(idyl<Vay<Agreements>...>());
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEEv7SAA6oCoRODB7evgHBaRmOAuGRMSzxiVzJtpj2xQxCBEzEBDk%2BfkG19VlNLQSl0XEJSdIKza3teV3j/YPllaMAlLaoXsTI7BwA9ABU%2BweHR8e72yYaAIJ7BwDUACKYKa6MyHiYCjeHZ5fXJ39H3wu5yBZkCEWQ3iwNxMgTcXkctEIAE8YdhgeYwQwIV4oTC3MhxugsFRUeifocbthVARXAAxYiyT4HQE0lgpAw0vEEJFPZhsAB0gtJl3GxC8Dkp1LpDME0IA7FY5XcYVZLsDWeymJzYRqOZg8Ux4ahBfzUTcIUwFB8hJgAI5eF6YUg3Q1EE0ANRaeCYsXoCmFF1F4oIkppDHQ9NkeJt9sdeM9xG9vveJtJgTRaoVwJuOZuuq1%2BthruNgqimAA7gmk36A7mbl4MkYbsomMBMNDAncbjGHVjC24y5WvT6/SbnVWRymhemVeilbO1eTbp6kUz9izMGy9QajTcJ8mA0GJSu5xYbrNHMhzQJxphVCliC7dwA3MQO%2BUWff0EzzwJnn/Kn%2BZJXBSyjEJgNCqGupzqpumram43K8qwTrnngABemAAPoEAGaB9ikIZgRBeBQTCXYEGKhaqkCS77N2CDwgQ9DQRuW4FjubrThmgaUcGDFMd%2BQGLiB/xiV8wK/LsNwAJJbpujDNA0rGSeJakwSJ%2BYIUhjAoamM4inxEoAEqbqgz6YJ63jvB%2BAELrRon0RYlrtm4LkqZcWn9sWJoyYeRkhqZLDmZZb7vHihIgCAERYKoWFKLGfZ4jJ%2BlogZQJZpcdZedmuZ4rldY5ts2w3AA6u2DbtiYABsGjEZByWoqmtV5qgNyMD4CQFtCtWRoIAAqLRtgQ/q1aaWWFTm9WkY16Ymn1BCDcQw0KKQBWFcVZXtugDIpHmCDtpE1IustnWCONFyTTmOl8k663ZTyukCoKznIAA1ktK3rbWuYXngV74ber60E%2BRA3Hg6BIrQEBLOtm1RKgNL7VqPUaEIjEEMx%2BotXgHwRLMgjejS6A3LEq7Aw6/oTUVJV3pRTAOJgJNUAyLD7e2Xk3CkLQoTSxAKBddabf1CC4%2BDHzxKIlU3OW7blnQIPc%2B97UWcQ5PDge1M3JtERgzVGgnmN60ALRmujgn6lr%2BVa3WC2fZgI1RRTmBjvduavR9Q0OwoTthamVszsJDnZXB25FkaJoXMA4EKYI/rpXWDYRMAzatlVnY3FgEI6RAENQ/GTAorCUcx2wcdNdxMOw0Hdk155occeHXH8jJzo%2BYKABS/liiZZkWVZlMRQQ6BRTFd7xXavabMlqXOpF0XhuPCVT/2HepQGP40SH7GcgHbhuzTW31koqPTaos3YM1Gite1DCdcQ3X63bXsjfrgtXWfF/zTKi0v6tB/axKuVTOu12Y3COiGIaZ0CDv0mjdFCa0ba5k2sA6W%2BtP6wi7nNIULUwbADagzBkVowH4AJtPJBh94gEFlowPM5Y2oTBWrAwqGC3BYMvoKAAshDdA9B7YjUQZdK6KDtqgIIAdcBdMTrAGgcwh6yE2CCKunmR6t0TQe34VTIROYfo5j%2BgDG8NJgagzannaGsMtam3TAJTG3494AOfstb2vtrKuwoTcbhRI%2BF/xcQ6Nx2jCoaJ8SAZ2/sAlphoutHKTcSz8hLpgWOr8E65iTk2FsbYOxdizrQHOZiC5FzcPExJ8cOGmnTFXeytdIl0WkqZZA6wMgWRuG5E%2BEl64728hHQUrcTEmg7s6eBz1%2BQAHlxEJB7I6EpwIjyBT7qFay8c3DzzHnFZecZYQpW4nPYeo9F6rMnusths8bijIOsQCZfYBbcVPFEhuu9wmwgASI4%2BVVaqsL8tg00uC2odTYA/JGT8f6aLfgA95Fd%2BSOJWko4RQDRGoD2mMyRx0oFlxgQAwZd13HPLQW88CDVMHgv1jffBLpkBEI%2BIi0hzQkpYpKlQmhDA6EML/nI3MrD2Emk8bwzAmjoWTWeTteFYCIHSNkei1RCDxUKJdi9BmnsnGvwDjxOs%2BjrwMCBmIEx4NIbmJNmaKkYYIw/2%2Bo89xGKbhBRCgPcKsJTnjIOZc9e7ioqc3Sf2IJCqfYhL9tcpV60XV3PbG6k1%2B93GQucd61xgo%2BWFS5d4z1viZXMIicBbe8FOnNyKaiqZWtUkpzdZkzOmBs6PVzjq/JeIs2KRKalCpNdfzVMcupDSTbJSsHZO2NpTb1KAnRKCcEkJ074gEJsQiOaHJSRsVjDyFxoluS6WUniMyp1CUbZOzhDsmBUC8FiZSXa53tzictcdeaPGbu3burIhbLX9zClo62AT54sCYG9bCKyJ6JWnrCLgqIY1PpfW%2BvZH6V54kCMbLg4Hf3rX/a%2BrC761lJVhP4Y2YGf3pQDFFYNxdj3rzrq2oQXgUiFCZqZBQXgckztPQRoj6QSPvHIyGciK7%2BwaGdGYZ0kgU0iUnaRhjlHGwp14xRpjG7mgXocFkPErGbjgbY86FDHH5P%2BC4xOik/V3ghi7forClolCtAgPPBQKEdOLOo8R9AQmCDOks6iauFgOArFoJwfwvA/AcC0KQVAnB96WGsOeNYGwqqgh4KQAgmgHMrDegESQ/INAAA4zBmAAJxJeqPFuLXA5RymkE5jgkheAsAkBoVjbmPNeY4LwH2rGwvuYc6QOAsAYCIBAGsAgKR4TkEoGgNkdAEhRBQpwVQcXqrG2qpIG4wBkBXikPyMwvAmaEBIBDPQ/BBAiDEOwKQMhBCKBUOoWrpBdBcFIOWB%2BKROA8Ec851z4XPOcGGfCdrIZUBUBuENkbY2JtTZuDNswNwIAeB6/QR8GIuBLF4DVrQKwIBIG6ykXrZAKAQDhwjkAwApDsZoDkhIPsICxFu7ECILQkQXd4IT5gathmxG0MWmrIXuuouGQwWgJODtYFiF4YAblaC0B9twXgWBn1GHEGzvA4EJMWT5x5u8xb4RbBC7rOot3ESxAfmrDwWBbuUTwIV/npBVaxFow8IXwBERGHCysKgBhgAKHdG8cswzeSk%2B28IUQ4gturfkEoNQt2jv6EMMYaw1h9B4FiD7SAKx4UND58bQk5FTC%2BcsGYMrqtExYHDzDbotOsguHDFMPwx2wgRCGBUEYx3CiZAEPnvQFeGjzGGFULPEmBB9EmJ4Doeg7DZ5bxMAYxeFhl9sL36vx3ZitHr6XqoKwFABc2BIK7HAXOkFK7wcrb3hujfG5N6bMW/sQFwItkHwXwehYtysA6TAsCJEz1FyQgR%2BRJcCNljQkgzCSFqhofw1Ukv6E4Pl0ghWgQXA/I1UXA1UcWSWGW1UyQ1Qj%2B1Uy%2Bt25WlWIA1WFu9WTWMOLWj2HWSOKOwO/WbAnALQLAz4coxsTA5oBgTYXASW/IwB0u%2BARAaeK2sg627u0gnuu2PuB2ug7Gp2TA52/OC%2BS%2BK%2Bd2HAD2bW8INwL26%2BH242Fo1BtB9B/2gO8OwO0IoIZgJ%2BkOdWmBeBCQnWyOqAQOIwCh6OqWrGWOfMuO%2BOB25OxOzu9hlO1OtOzuDOikTOLOt27OnO3OvOzuguAeIuHm%2BA4ujgkut2Mu9SNIzuiuuWHmKuauSIGuWwHm2uuuIWBuRum4QRycaBVurYtu9ujujAzunubBm2HBsgXB%2B2HmvB/u5uCeVglgIeYe8AkehEWQMecenYTR1gyeq%2BqeEM7w7RTeDQue7g7eeQhe4YE%2Biw5e6Qle2QUxBepAteWQcxg%2BXezejQw%2BKxnedQ3euxcw/eDeneexuQqxY%2BfeZQZxYOqw6wc%2B9xuWIhiBnAshm%2BlBAeP2ShsW/2B%2BTBGhQB2hZ%2BpAF%2BV%2BlAC%2B/%2BgBtBL%2Bco/gSWWWgQr%2B7%2Bkgx2ohSBtgKBp%2BtW0OGBSArWT2hh%2BhxABBWwxBn2LACgz4V4z4NB/Ieo4w82jBS2I8x25RbulRLuNRvuIAwQ/Bghl2v%2Bi%2BN2B25WEhT20hr2qglJ1JtJ9JjJIYAOxhahCQQJgQIJuJ9WsOKpCOxJupwOISyARGWEdJSWWEipWEMpHBdA1hlAthHmThrOIWTpVONODgbhxhjOzOrOIRmAHOXOYg/heugRwuqRAuYu2eERB2URcusRggSuB2iRxOKRWuiYGRvAWRSgxuuR5uWpBRNuduFYJRbmIWHJG2EgVRO23utROgfJDRgeieNgKuGeHR0enA2wkUfRSeKeCQaeIxEeYxOeEArgI%2BIQsxpxk%2BNeixDQY56xJQk58xQ5Pe/QY52xDQreNxJeS51xa5vemxU%2BDxgW8%2BwprxYp7x1pNwVJNJNwZpDJBY4w/xLJR%2BwJEOoJ4JIwmeuW0JIAyW/IgQgQ/g/gL%2BXAxWAFco4BCB55FWWJqBuJkWIAkg/gD%2BmWcoxWcWkgqWXACWZg8BuWgQopZWnAb58Fwpc2UFRFMFOhSwKwqsGQzgkgQAA)$Done$

## Links

- [source code](../../../../conceptrodon/descend/omennivore/remove_values.hpp)
- [unit test](../../../../tests/unit/metafunctions/omennivore/remove_values.test.hpp)
