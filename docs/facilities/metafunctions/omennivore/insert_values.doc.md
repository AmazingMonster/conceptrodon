<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::InsertValues`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-insert-values">To Index</a></p>

## Description

`Omennivore::InsertValues` accepts a list of `std::index_sequence`, which indicates distances between adjacent indices.
Its first layer accepts a list of variables and returns a function.
When invoked, the function inserts the variables to its argument list according to the `std::index_sequence`s.
The result will be stored inside `Shuttle`.

<pre><code>   std::make_index_sequence&lt;I<sub>0</sub>&gt;,
   std::make_index_sequence&lt;I<sub>1</sub>&gt;,
                    &vellip;
   std::make_index_sequence&lt;I<sub>n</sub>&gt;
-> V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>k</sub>
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>m</sub>
-> Shuttle
   <
             Arg<sub>0</sub>,
             Arg<sub>1</sub>,
              &vellip;
       Arg<sub>I<sub>0</sub>-1</sub>, V<sub>0</sub>, Arg<sub>I<sub>0</sub></sub>,
       Arg<sub>I<sub>1</sub>-1</sub>, V<sub>1</sub>, Arg<sub>I<sub>1</sub></sub>,
              &vellip;
       Arg<sub>I<sub>n</sub>-1</sub>, V<sub>n</sub>, Arg<sub>I<sub>n</sub></sub>,
              &vellip;
             Arg<sub>m</sub>
   ></code></pre>

## Type Signature

```Haskell
InsertValues
 :: typename...
 -> auto...
 -> template<auto...>
```

## Structure

```C++
template<typename...>
struct InsertValues
{
    template<auto...>
    alias Page
    {
        template<auto...>
        alias Page = RESULT;
    };
};
```

## Examples

We will insert `-1, -3, -5` to indices `1, 2, 3` of `0, 2, 4`.
To do so, we will calculate the distance from one index to its immediate next.
We will keep the first index, `1`, since it represents how many variables we must pass to reach the first target position.

<pre><code>   1, 2, 3
-> std::make_index_sequence&lt;1&gt;,
   std::make_index_sequence&lt;2-1&gt;,
   std::make_index_sequence&lt;3-2&gt;</code></pre>

We will pass these sequences to `InsertValues`.

```C++
/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** Metafunction ****/
template<auto...Args>
using Metafunction = InsertValues
<
    std::make_index_sequence<1>,
    std::make_index_sequence<2-1>,
    std::make_index_sequence<3-2>
>
::Page<-1, -3, -5>
::Page<Args...>;

/**** SupposedResult ****/
using SupposedResult = Shuttle<0, -1, 2, -3, 4, -5>;

/**** Result ****/
using Result = Metafunction<0, 2, 4>;

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
Then, we expand the concept packs alongside the arguments to reach the desired positions.

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
struct InsertValues {};

/**** Base Case ****/
template<auto...I>
struct InsertValues<std::index_sequence<I...>>
{
    template<auto NewVariable, auto...>
    struct ProtoPage
    {
        template<typename...BackArgs>
        static consteval auto idyl
        (
            // Expand `Prefix<I>` to reach the desired position.
            Prefix<I> auto...front_args,
            // Collect the rest arguments.
            BackArgs...
        )
        -> Shuttle
        <
            decltype(front_args)::value...,
            NewVariable,
            BackArgs::value...
        >;

        template<auto...Agreements>
        using Page = decltype(idyl(Vay<Agreements>{}...));
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

template<auto...I, auto...J>
struct InsertValues<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template<auto FirstNewVariable, auto SecondNewVariable, auto...>
    struct ProtoPage
    {
        template<typename...BackArgs>
        static consteval auto idyl
        (
            // Expand `Prefix<I>` to reach the position for the first new variable.
            Prefix<I> auto...front_args,
            // Expand `Prefix<J>` to reach the position for the second new variable.
            Prefix<J> auto...middle_args,
            // Collect the rest arguments.
            BackArgs...
        )
        -> Shuttle
        <
            decltype(front_args)::value...,
            FirstNewVariable,
            decltype(middle_args)::value...,
            SecondNewVariable,
            BackArgs::value...
        >;

        template<auto...Agreements>
        using Page = decltype(idyl(Vay<Agreements>{}...));
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

/**** Recursive Case ****/
template<auto...I, auto...J, typename...OtherSequences>
struct InsertValues<std::index_sequence<I...>, std::index_sequence<J...>, OtherSequences...>
{
    template<auto FirstNewVariable, auto SecondNewVariable, auto...OtherNewVariables>
    struct ProtoPage
    {
        template<typename...BackArgs>
        static consteval auto idyl
        (
            // Expand `Prefix<I>` to reach the position for the first new variable.
            Prefix<I> auto...front_args,
            // Expand `Prefix<J>` to reach the position for the second new variable.
            Prefix<J> auto...middle_args,
            // Collect the rest arguments.
            BackArgs...
        )
        -> ExtendFront
        <
            decltype
            (
                InsertValues<OtherSequences...>
                ::template Page<OtherNewVariables...>
                ::idyl(BackArgs{}...)
            )
        >
        ::template Page
        <
            decltype(front_args)::value...,
            FirstNewVariable,
            decltype(middle_args)::value...,
            SecondNewVariable
        >;

        template<auto...Agreements>
        using Page = decltype(idyl(Vay<Agreements>{}...));
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGEgJykrgAyeAyYAHI%2BAEaYxCAArKQADqgKhE4MHt6%2BASlpGQKh4VEssfFJdpgOmUIETMQE2T5%2BXIFVNQJ1DQTFkTFxibb1jc25bcM9faXliQCUtqhexMjsHAD0AFTbO7t7%2B5vrJhoAgls7ANQAIpjJrozIeJgKF7tHp%2BcHX3vvJ8d/ZgAzGFkN4sBcTIC3F5HLRCABPSHYf7/T6bC7KYiYGiqV47X4ETAsZIGQmQtwEeF3ZhsUgXJgw1BI/5oBirZIEDFYnEQwFXC4EYheTCQqynVG7C5CBAwgj0PHbAlEklMMlQhlEAB02uZpwUgq8DilMoIcpFgLFfw%2BkoAakx4QrDv9CcTSea3BrUBc7cQ8ExovRdSd9UKjXbEeKAOwWC761V4ZAXVn6zCqZLEemMi4ANzEwoh0Z9foDIsjV1FBfLFpR1su2FUhIY6AAYsRZI6la7Ve7KdTWJhtZqgyHDZz642W23BAWrGXRTWTi6VWqKcq3eTPYOkUmDAoXkJMABHYVszB0zfaov%2B%2BgKYcGo3j1yt2Tkg/Hh7uq8lhRbwHIv8otG/wXCBAprt2G6MoOESYAA7l%2BN5BqBFxeOkRgYkwwCYLy/JvieqzkjB8ENMWN6DnSCHPL%2B/6WiYc7VuKtbfMx%2BISpcACSrpEow9SOAIHZsSxLG/M64Err2jD9tR/wjka7EMEojR2t4zwznRVa0Ux6IWEwSgXB6elvKJXYrhemrsXeoacvJikEMpwq3lC%2BroCAIBhFgqgAPpKO%2Bp7kux0kAVGlrIUu67qlmRGUeeUE6kFJzIbJnKYqgRDKJhIqnMhdEhchoFhRBUISTSA7ajpyAANYnMQwCOciWV5SBcaOImyaErmtCZkQFx4Og8K0MBjUXBAg1DaB6zrBc9bJIY6AQgAbBomLYngqj%2Bcyi0Cl6WJMMgCACgg2FYOkWJzak6R8QwQ4NWNIHLTi61/l1qCDlQU4EJ5DS1aQo23RN%2BmePYnIEIdFxYvq9I1T4PE/r9Y3lVVNU/jqN15XMcOgQAtNu0qyoGqPZVCGONVgoISdQ72fUjcyuR1wrkcTeVRSR15nozyEI9VtW03mpXXQlQ3MgxVoC41BWmbFmonMAWLcYIdWM6hYTABhWE4RcpO0OTvX9RA4bktLstsPLzJAWWg5zOjwvZfRmmi2BJnumZhuYHLBAK6jSvoelauQvyKVpRlBsy67xvu4FtG2wu4tO5L7ExVq2oAFKWaOFw2XEdm845bjOa57mpt5R74e6AVxdgdJ525TaFz5JfkkngX1X8QGozHkHdc2eDEPqzO%2BqzCdegerLoH3pFns90mo0lXKpagPuZfbOWM%2B3RVUpJbCDpzSNIUNzUJkmAgph1z09X1A0E6BI2X41/3TbNC1Ldyq2Pcim3dTte0Hdh52FAwFz8AzCDbCNAe6cnCLBHMLMSz81uqBe6L8oQWSemZN6sgqbfXZuNSa98myPwQWtKEKcALv22pgXa%2B1gEXF/pdABJBv6xmqAIOaECoH9xgVgu6z9CFuGIdgSe2oWC9XQPQDBCgfo3zyv9bIQMGHg05F9aG8tYFwIuNvWqW5JHo0kdjJ6uNTT43toTNwnCNbVC1uvCm6CvoKBpiAOmfMJFGKGl3MBY8B6mM1uTIR6ARGYDEXYhxDNJHIWHsw9xJYnGqLUbtRG3N7G800c4kCQs7ZjVXh6SWLs3Ye2SShNCKsF7qy8ZYnWtA9b2mDkbGGptZxXAtlbXKKSo6MXthk52Iccm7xAl7QpGV1YB3nkHKE2Sw7IyHABYW6l5ytLRBcAAStUZY6RszYQMthIypx2lx0HoOJOdJipSW1AAeWAcQPCH5ckzwzkpbO5Iq4Fy8nXD8/lqKVwIC5auHki6%2BQIkQt5FxTmHXOcXS5U8W5NIdsuWOndu69zgtFU%2BYSmwRPoLsk5ZzUXPG6bGe8yU2yBywr9ZekiMmHM3mVWJXNcljX3q1I%2B7UxCnzKYza%2BeTkJ3zTA/Ewi0CGvx5RoLaYNyFfyoTQzIdCgGg1ARDVhuZ2H0BUXAvlSDtyoMpjYqJqjOUzTwQKlVvCNqCo/iKyhoNxX8UAQwpQI8LhyugYq0xBq%2BECM1D4vxYitVwOkYDaowNQbyMhsAJR4dTHqPGYzbReTdH8MfE2Z8ghGbkk8eYiSpi2XROQjcrOKkc5AriBc08Eb4qZtAq5GOqt3T5uIFi4tzdS0gXzufCA4bl7m21FG6JnbBYlqGuWsS2EF5JqJiE0CJS7hWMEAEnmKlgnstAq4%2BFxEFVs1HSBcdmAIDutETYwJiTtRetusi0eCKHWLzGqkhc6SB0dxetqUZNTe2NV6ZW4pqbSnNv1iMzpYzanqQaTMpeLSRahRvRFROUsf2PvraBF9RS/az0Je6B9yjy6AemVMrSQknRaSmqoVgJINmsSw0JES4ogQgjBNhckrJ2TuyDIJdE%2BizQCS2WBzJEHU5GmY4GTDZxJQAFlMD1CoF4NktDNmLnY87He8UX1CZE2Jzo/8EPZvsti8UI77ZVxYEwCq/jHk/PrlCLgSJD06b0wZmuTzQV%2BShGYTGpm/zmY%2Ba5XT%2BnPKGeeXZtwgJMZmAY/FVyQ6oSObpJjQE4WEhBmC8Mtw1KI4LjmUILwyRzqYHQIshQXgtasZOC%2BlLaW0gZayzlzkCGePug0OFrgdIzDhcixcaQFxMbRcmXbOZpXcuSZfV18rfILgKaYKJ8TmRyTVYuPVprl7ZmSgACrPE5JJuln09yZwgFXBQ/ZVuvlS%2BlzLzwyt0j60iRp/wOALFoJwBIvA/AcC0KQVAnATGWGsLGJYKxqNAh4KQAgmgLsLAqokSQmoNAAA4zBmH8P4LgCRwdg64JGSM0grscEkLwFgEgNDVbuw9p7HBeAKBANVv792LukDgLAGAiAQBLAIMkGE5BKBoGJHQOIER%2BycFUGD%2BamN5qSAuMAZAiYpCajMLwDLhASC9T0PwQQIgxDsCkDIQQigVDqDJ6QXQtXYLECYMkTgPBLvXdu/9x7nBjkwgZ5yVAVALjc95/zwXwuLii7MMNDwrP6AZnMICLgcxeCk60AsCASAWfJDZ2QCgEBw%2BR5AMAKQ9WaBaziETiA0QzfRDCA0eEhveBZ%2BYMQeExzojaD9Xn0gLOw7HIYLQXPmusDRC8MAD0tBaBE%2B4LwLAumjDiAb93P1eBVkd4e6mJZhIK9hEJKjh7cJoh66Lx4LAZvBR4Ex530gqziDRGKzcHvwA4RGH%2BwsKgBhao2ieLBY51IK9y%2BEKIcQyu79q7UGb7X%2BhDDGGsNYfQeBohE8gAWFQA5EyA70xmcj9lMFe0sDMDxy319GOngAWA6EuhcCbDGFaCCCbGmAGHiFqwtSyE8BaD0AIJwLKEGFqxQNqBGCaCIPGFsEwCBmoKmDCH6HILwMmFGDoMwLjEaDINmH90WGWFWAkGNw4Bu1IFx14Hx3tx5z5wFyFxFxB3dwgFwClx92%2BwD1%2B2PwWEOiYCwHiAgEBxAEkEBE1H8EBGRw0EkDMEkEWg0ASHmkCFR3R1IExz901Hmi4HmjB38AR3mgSEkFhwsPmkkLN3x0J2J20LJxD2p1D1pyt0Z2j1j29w5zYE4AaBYGzEjExiYB3E/1d38E1C4FBwl3wCIAQNl1kAV0f2kGfyUFf0110Hq1131zzzEIkKkPNw4Et3pxhAuFt1kMdwF1BAKLaGKNBw91QC9ziAhCBDMC0KD3J3iJSLiCZxj2mIj29xQAMCMDaC4Gq2T0JB7koAz01wLxzwrwuKLxLzLwcAryrx4hrzrzN0b2b1b3bwr270/z7we3wCxBqGHzNzH2QBhDWB%2Byn0YLNznwX3hCXzWAe1X3Xx%2By3x3yUD3x%2BOVmPz4DPwUAvzgmv0YFv2qIfyVzqNkBfw1we2aI/yPygKsEsF/3/yQMexAKPk4HAI%2BUgO/xgLgLiAQOeBZKoOcAgFcAwL0BCFYJmAoPyAukyHFPwIKEun4JlOFIYG6C4JyB4MYMHy6BoJVI4N4NoK1L0CNINNEKEM%2BwtNR06PCM4CGPkPyPQnGJKMFVUPKPoV9390Dx0NID0IMMoDENcPcKKOsMjASH8CR0BBsLsKCLCM1wiNsCiKWNiPgHiLp2t3WNWJrU5w4EyKdxYAUGzETGzHGLdH1DKPUJl1qzvxqLJJV3kAaKpJ0BAEi1aIN07w6NNwTIt0SJtzt1UALKLJLLLO7AhggE9y2NmN90BEWOxJWM2MjyzMXO2OLLS08lLP8E8nLI%2BkHLqLoGOLTzOIe2uPrx%2B1PNuPLw30eMEGePrz%2BMwCbxbzEE%2BI32%2BN7wRK7wH0BMFM1xBLBMn0EChM1xhJz3hJX19GRN4FRN3yJExKPxiJxMwjxMv0JLux%2B1rNJIkHJNVybLf1bNpK/2gJsDnwAKMNZMug73WDznpOsFgOkPgN6kFMAIYKYJFLFO4IlOwKlNwJIKVPlM4sVLlKKB4vYNNJ1OUw1ONOIMoIksuikvNMoJoIVM4N6FEoEOQI%2BxEMEJtO7Lx3tL3IuELOLJzFHMJHHLUIqLmL9znJiN0PIQDPIpcIxxACh01EBEBASDhyCOxw8sjB8PjP0oJyTJJ19KB0kASHMMR0jGxzB0kBhy4AhzMFCNR0BD0ukM4B9Lsv0E4HF0CoyuCpTIWC33SGcEkCAA)

## Links

- [Example](../../../code/facilities/metafunctions/omennivore/insert_values/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/omennivore/insert_values.hpp)
- [Unit test](../../../../tests/unit/metafunctions/omennivore/insert_values.test.hpp)
