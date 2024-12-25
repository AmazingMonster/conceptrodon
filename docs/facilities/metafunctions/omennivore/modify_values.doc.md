<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::ModifyValues`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-modify-values">To Index</a></p>

## Description

`Omennivore::ModifyValues` accepts a list of `std::index_sequence`, which indicates distances between adjacent indices.
Its first layer accepts an operation and returns a function.
When invoked, the function transforms the arguments from its argument list according to the `std::index_sequence`s using the operation.
The result will be stored inside `Shuttle`.

<pre><code>   std::make_index_sequence&lt;I<sub>0</sub>&gt;,
   std::make_index_sequence&lt;I<sub>1</sub>&gt;,
                    &vellip;
   std::make_index_sequence&lt;I<sub>n</sub>&gt;
-> Transf
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>m</sub>
-> Shuttle
   <
             Arg<sub>0</sub>,
             Arg<sub>1</sub>,
              &vellip;
       Arg<sub>I<sub>0</sub>-1</sub>, Transf&lt;Arg<sub>I<sub>0</sub></sub>&gt;::value, Arg<sub>I<sub>0</sub>+1</sub>,
       Arg<sub>I<sub>1</sub>-1</sub>, Transf&lt;Arg<sub>I<sub>1</sub></sub>&gt;::value, Arg<sub>I<sub>1</sub>+1</sub>,
              &vellip;
       Arg<sub>I<sub>n</sub>-1</sub>, Transf&lt;Arg<sub>I<sub>n</sub></sub>&gt;::value, Arg<sub>I<sub>n</sub>+1</sub>,
              &vellip;
             Arg<sub>m</sub>
   ></code></pre>

## Type Signature

```Haskell
ModifyValues
 :: typename...
 -> template<auto...> class...
 -> template<auto...>
```

## Structure

```C++
template<typename...>
struct ModifyValues
{
    template<template<auto...> class>
    alias Rail
    {
        template<auto...>
        alias Page = RESULT;
    };
};
```

## Examples

We will apply `UnaryMinus` to variables of indices `1, 3, 5` from `0, 1, 2, 3, 4, 5`.
To do so, we will calculate the distance from one index to its immediate next.

We will keep the first index, `1`, since it represents how many variables we must pass to reach the first target position. We subtract an additional one from the rest since we only need the number of variables separating two targets.

<pre><code>   1, 3, 5
-> std::make_index_sequence&lt;1&gt;,
   std::make_index_sequence&lt;3-1-1&gt;,
   std::make_index_sequence&lt;5-3-1&gt;</code></pre>

We will pass these sequences to `ModifyValues`.

```C++
/**** UnaryMinus ****/
template<auto I>
struct UnaryMinus
{
    static constexpr auto value
    {-I};
};

/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** Metafunction ****/
template<auto...Args>
using Metafunction = ModifyValues
<
    std::make_index_sequence<1>,
    std::make_index_sequence<3-1-1>,
    std::make_index_sequence<5-3-1>
>
::Rail<UnaryMinus>
::Page<Args...>;

/**** SupposedResult ****/
using SupposedResult = Shuttle<0, -1, 2, -3, 4, -5>;

/**** Result ****/
using Result = Metafunction<0, 1, 2, 3, 4, 5>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The implementation of `ModifyValues` is similar to that of `Omennivore::InsertValues`.
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
struct ModifyValues {};

/**** Base Case ****/
template<auto...I>
struct ModifyValues<std::index_sequence<I...>>
{
    template<template<auto...> class Operation>
    struct ProtoRail
    {
        template
        <
            // We use `Prefix<I>...` to enumerate `FrontTargets`.
            Prefix<I>...FrontTargets,
            // We will transform the next argument.
            typename Target,
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
            Operation<Target::value>::value,
            BackTargets::value...
        >;

        template<auto...Agreements>
        using Page = decltype(idyl<Vay<Agreements>...>());
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

template<auto...I, auto...J>
struct ModifyValues<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template<template<auto...> class Operation>
    struct ProtoRail
    {
        template
        <
            // We use `Prefix<I>...` to enumerate `FrontTargets`.
            Prefix<I>...FrontTargets,
            // We will transform the next argument.
            typename FirstTarget,
            // We use `Prefix<J>...` to go across the distance
            // between two targets.
            Prefix<J>...MiddleTargets,
            // We will transform the next argument.
            typename SecondTarget,
            typename...BackTargets
        >
        static consteval auto idyl()
        -> Shuttle
        <
            FrontTargets::value...,
            Operation<FirstTarget::value>::value,
            MiddleTargets::value...,
            Operation<SecondTarget::value>::value,
            BackTargets::value...
        >;

        template<auto...Agreements>
        using Page = decltype(idyl<Vay<Agreements>...>());
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

/**** Recursive Case ****/
template<auto...I, auto...J, typename...OtherSequences>
struct ModifyValues<std::index_sequence<I...>, std::index_sequence<J...>, OtherSequences...>
{
    template<template<auto...> class Operation>
    struct ProtoRail
    {
        template
        <
            // We use `Prefix<I>...` to enumerate `FrontTargets`.
            Prefix<I>...FrontTargets,
            // We will transform the next argument.
            typename FirstTarget,
            // We use `Prefix<J>...` to go across the distance
            // between two targets.
            Prefix<J>...MiddleTargets,
            // We will transform the next argument.
            typename SecondTarget,
            typename...BackTargets
        >
        static consteval auto idyl()
        -> ExtendFront
        <
            typename ModifyValues<OtherSequences...>
            ::template Rail<Operation>
            ::template Page<BackTargets::value...>
        >
        ::template Page
        <
            FrontTargets::value...,
            Operation<FirstTarget::value>::value,
            MiddleTargets::value...,
            Operation<SecondTarget::value>::value
        >;

        template<auto...Agreements>
        using Page = decltype(idyl<Vay<Agreements>...>());
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEEgCcGqQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJXCm2mPalDEIETMQEeT5%2BQfWNOS1tBOXRcQnJqQqt7Z0FPZODw5XV4wCUtqhexMjsHAD0AFSHR8cnp/u7JhoAggdHANQAIphprozIeJgKd8cX17dnAJOvyulxBZkCEWQ3iwdxMgTcXkctEIAE84dhQeYIQwoV4YXC3MhJugsFR0Zi/sc7thVARXAAxYiyb5HYF0lhpAx0gkEFEvZhsAB0wvJ10mxC8DmptIZTMEsIA7FYFQ84VZrqD2ZymNz4VquZgCUxEahhYL0XcoUwFF8hJgAI5eN6YUh3Y1EM0ANTaeCYsXoClFV3FkoI0rpDHQjNkBLtjudBO9xF9/s%2BZvJgQxGqVoLuebu%2Bp1hvh7tNwqimAA7kmUwGg/m7l4skY7somMBMLDAg87nGnTji24K9WfX6A2bXTWx2mRZm1ZiVfONZT7t6USzDmzMByDUaTXcp6mgyGpWuFxY7vNHMhLQJJphVGliG79wA3MROxUWQ/0EyLwIXn%2BqoARSNxUsoxCYDQqgbucmrbtqupuLy/KsC6l54AAXpgAD6BBBmgA5pGGEFQXgMFwj2BASsW6ogiuhy9ggiIEPQsFbjuRZ7h6s5ZsG1GhkxLG/iBy5gYCEk/KC/z7HcACSO7bowrRNOx0mSRpcFiYWSEoYwaHpnOYoCVKACyGB4FQKLet4nxfkBS70eJjEWNanZuG5anXDpg6lmacnHiZYbmfgVk2U6gbwsSIAgBEWCqDhSjxgOBJyYZGJGSCObXA2Pk8ghu4lia6WWgYNp3AA8i8xA6jk9b5ieJFMkQABKTB0Lm%2BZ/nRDa5QVXE5b1eYEp1Q0Nrsux3AA6p2TadiYABsGikdBqXoumS0FqgdyMD4CRFrCS3RoIAAqbQdgQgZLeag1jfmK3kWtmZmsdBBncQF0KKQo13XcE3TZ2lZ0LQBY1QwCj8MQLAFggnaRLSbofXtgg3Vcv35npAqdu9F3fbdv2YwZwqucgADWOOYJdP0NvVQ1XngN6Efe74g6Wdx4OgKK0BAKzU/m/1RKgdIwzqh0aEIzEEKxhqbXgXwRPMgi%2BnS6B3LE64sxFfN5v9D7UUwDiYKrVBMtDBCwwW/XC2kbRoXSxAKKjd3/SdCBy%2BzXzxKIc13JWgPA3cNtkztr4JBro5Hvj42TRERBi2e13a3cAC0FoS8JhpR118JJw2r0U5dMWa5gE65/mVX7U0BIF0XH7Ftgte2XjaPo3cJPk%2BdlMKI3Trplnw1zqJTl3XlRU8YKVzAJBSmCJFfF3U2ETAK27bzd2dxYFCekQBzXOJkwaLwpP09sLP628TzvNDzT/50T9o/IVbvnFbxpXWo7wrH5gM9U5lDaLy2NqdAuw9ggkLVAQDaAEi/j/D%2B5pB531vqBB%2BflhRyVdKgwUAApQKEozIWTCnXSKbhoqxUjA%2BRKDp%2BzbFSulV0pC4oUKStQwcWD0pBm6vfJ%2B%2BVOJIUwRaK05UK41Srn/BqQVWzNQge1KB%2BNOH90trwzOLchojQUdHAGjYlBiweqoJ62ANoaC2jtBge0RHzSOnKN6ncqaJ3UfdSCq14QBWesKfONivplx1pNGavsA763BpDM2Ft4ZhnOsjAgTtW6EzYHcekeAHbWI%2BpTZurc/o%2BNmtoxay1HGPXhDg1x5pNpx2ANtA2TJyrm07PgRWND7HeLVpTP2jACyVm2lMT6UT0a6IJAUgxwpTIc3QPQAunj6npM0UDWgIMAkQxIMEuGetEbAAiV0gmfJ9KxLtIRdABdUnRI2VjM07dRlJ1pr1emjM7x0hZi%2BOOu9ua8wUanTMQkpa/gUWolRv13HJMLiAYupdxnCNqgIAk8TEk1wBXXdEPcXReLuIMkkIyPFwqBd8u6ILRFuG2QIXZNi4WwuhU3BFJzUXEt7iKT5CDQIj24WPMsE8p7f1Pr/eeY0AHLzbB2EBG9MBbw2TvTmUD4RniPsy2B594HYEvo5G%2BwE774wfigl%2B0q342jNDA1lc8fqcruJA3lYDWoyOgRK7V7Ch4OUtQxWSLV%2BWbCyKHO4HltFSW8vSjyqr0F3MZVg10MSS7CgqlU4gfZnQ6uMng4KBDrJEIJAw8hCVmEJmcXQy8BB0AxUYUmqhKa3BsN4q6YNsNQ25oHHAjh2VvnKo9fw15givhYrqmIvMjVJHgMgT9eRGKMbcOpW4BF/1fE%2B2yT05xUrsnGN2mwcxYtfmfWyWsu6Y63AuP6YKedXd9noyHf7aZoNDBzKhjDRZCNwmsqXWNANcSEmTD2YOjJWiLE5LIno/JE7inbVKW6ZAFSvhVI3nLVoKVxn/XiAQZpDBWntI8ZeoaK6%2BlmiRcMzAozt2/V3X4/dsygknruKE5ZqyEXXtxZGe94yA3HINh3P5gZqXsrpipBmt5wY3LED69mwqeZJxedgcMsoYz9uI4ctCiKY3hU%2BASYtCQw3lvYeMmKPl9UmvhE2sFLbfqKafivDsBIyW0bRbxM5GmGxaaUTp5Rd0vlpM3f8wFwp0OYuqqChg4Lb1JIuoSzMcLHNjWQyigzFLA2Cl80NNTrn4SkfxX8rzDcgvGYyoqnteYVXjy1cpCNyWtFLws7yzetBt4PP3ofNw6Wz6FPRLK6%2BXUkFiT6konhiFn7jwEWVOBZW2W6ubMvA1lF23Go6uKk%2BGWLWIIVaBGSmlgQyWlKwTknY3XOU0lpJyWJITQjXoSAQ2xiKZfUvcOQzBiAokGaYr4i3UvbTXaCNth22gnYiE2c8P1LksfvI%2BZ8bNi5dqVMnAKtWsrjbEjN9O7yFusngg1hl8n%2BJRredLRy%2B3GKmUpkwKgXgcSqQu7W1VVwPqZb1Sj1o6PMc5F5SFSysbbJ0ZBDnfGpCWBMFJrhbNlDko0PhFwdE6GGdM5Z4mtnLCCSBGTlwUX3OXsZpioz5nOFWfJpSvCfwycRdc8ykGGKnb4R3eO6dp7mUYrcsHHj4AFaaXA6pEILwaRihGztQoLwBWvJXD1Vbm3mQ7efEd2GProOEfwlSCnLgrozCuhV66aQKd/AZiSzN%2B33vnd6vj07vrRO0cY4cM2twgfg93FD3cYIdxI/R/N05GbJ1PhhkW5cnC78EgEAgKQhQaFa/EOTwQV0bvbfoHb%2BiK%2BFgOBrFoJwfwvA/AcC0KQVAnAB2WGsJeDYWx5rgh4KQAgmhB9rFJgESQgoNAAA4zBmCSEkLg/gD/764AqBU0hh8cEkLwFgEgNCpHH5P6fHBeDd1SOvifg/SBwCwAwCIAgAbAEBpCIjkCUBoAch0AJBRBoScCqD74LTJwLSSB3DADIA3hSCChmC8BGyEAkAcx6D8CCAiBiDsBSAyCCCKAqDqB/6kC6DB6Vg1RpCcA8BD4j5j4b5T6cAVSIgQFhioBUB3DIGoHoGYHYF3C4FmB3AQAeCwH0DPhYhcArC8C/5aBrAQBIAwFpBwFkAUAQB6EGEgDABSCh40AFYJDdwQCxC8GxARD3YcG8COFHYogVSxDaD8q/6r4wGsoVQMC0Aoi8FYCxBeDAAeTTLdzcC8BYCM5GDiCMH4CQSZ6hwxGT4Pj2p0guHkCCANC8HIixA1THYeBYC8HUR4BP6xGkChzECxAe5PAJHADIhGAb5rBUAGCm6egfCVgVzj6r5kHCCiDiDUFDF0FqC8HMH6CGDGDWDWD6B4CxDdyQBrCoDEQ5AxHJzEiUSmBz6WBmDv51HJhYArE8y9A%2BE5AuCRgzB%2BDB5hARAjBVBjDB7FDZACC3F6BvFNCLCjA1AXGZ4CADDTCeBdB6B2CXFAlTBDCPFLAvG2DQmfHB7zDtC/HPE1BrAKCL7bASBcEcCj6kBv68Af5iEoFoEYFYE4G75yEQC4BEEqEr7qFr7tFrCwxMBYCJDnHb6SCBCChJCBA34aCSBmCSBLQaD%2BALRJD6CcAP6kBP6BBcCCgLRcALT75JCX4LT%2BCSBn78kLSEm8Ef5f4gA/7tEAHAE6GgGCGQFGEmHKEIFsCcBtAsCvgKjJxMBvwti1CCiKmZH4BEAnGkGyAUGjHSDjFKCTGMG6Ch6sFMDsGxF4kElEl8EcACHgGIh3AiGkkSEYFWielJDel77yGKH6HKGwjghmBMmaH/4Wm2kJBQHGGoBKFjC5nmGn6pBWH2y2H2GMFuHOE1G9nHaeHeEOC5H%2BHKSBHBGhGYDhGRFiC0AxGr7xGzFJGT4pGXHpG8FZHICIg7Cr6xwFGMFFElEohlE7CT6VHVGr51ENFKBNHLlLymmdHtgKA9FVj9G5FDHBlUGhmyATEMGT5RkzFtF7FWCWCLHLHwBrEbF3icDbEZq7HzEHFHEJAnGfCQUAlNDXHuCgkFD3GRhonLCvGZDvG5A4V3HpDEU/Gwl/HgkNCQnNCIlkW0V9BQkLDUXongmMX5DkUokwkVA0VqHrCbA4mCV36JkGmcBZnkkenLxek%2BnyF0n%2BllkKmVksmkBskcmUB4mynyn5lCkKj%2BBJDX6BDCminan6mMGGm2DGnMl/7aHmlIBgFCH1m1nED2k7BOmSEsAKCvg3ivhekGiTAEF%2BnEGZrB6fkjHfk0HyDhn/k6AgDBAxlxmcHSn4k8GWX8FWnCGiGqBeU%2BV%2BUBVFiTBFmNklkJDKWBCqV2UAG6GlUGEuV1XKEArIA244T%2BVJA4SBUEA4S5Whl0CdmUDdmT4DkhH9lOGDleE%2BGjmNkBFBGjWrnTkRFRHzm5FLmJFnlxEJLrloWMFbk7m5H7l36T5Hn3ankVHJiXm8DXmNHbj3ltHVVPndG9Hvk1ERWUESA/m0GxVTEJVAVzH7E2BFFnFQVNAxG7DRQgXWCHHEnHEcxoWrEYVXEQCuBIkhD4XsWEUUUlA5Co3fE5AEXwkQmAkMWDCo1E1NDAl8VPGY28Vk3QkE0YlCVL64mpXiUZUcBiF5W%2BV3DtWChdUKUhUMkqUaFqUaVjDnF346UgDH6CiBCBD%2BDn7akv5y0KiqkWXv6cBGkml2Vb4gCSD%2BB8lX4Kgv776SCn5cCH5mB6l36BDpUa2f62VaF4n4Hq3Ema2O2b61E2FXGSBAA)$Done$

## Links

- [source code](../../../../conceptrodon/descend/omennivore/modify_values.hpp)
- [unit test](../../../../tests/unit/metafunctions/omennivore/modify_values.test.hpp)
