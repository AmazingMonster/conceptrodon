<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::LeftReview`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-left-review">To Index</a></p>

## Description

`Pagelivore::LeftReview` accepts a predicate and returns a function. When invoked, the function returns true if the predicate evaluates to true for every relative-order-preserving pair of its arguments and returns false if otherwise.

<pre><code>   Pred
-> Arg<sub>0</sub>, Arg<sub>1</sub>, Arg<sub>2</sub>, ..., Arg<sub>i</sub>, Arg<sub>i+1</sub>, ..., Arg<sub>n-1</sub>, Arg<sub>n</sub>
->   Pred&lt;Arg<sub>0</sub>, Arg<sub>1</sub>&gt;::value && Pred&lt;Arg<sub>0</sub>, Arg<sub>2</sub>&gt;::value && ... && Pred&lt;Arg<sub>0</sub>, Arg<sub>i</sub>&gt;::value && Pred&lt;Arg<sub>0</sub>, Arg<sub>i+1</sub>&gt;::value && ... && Pred&lt;Arg<sub>0</sub>, Arg<sub>n-1</sub>&gt;::value && Pred&lt;Arg<sub>0</sub>, Arg<sub>n</sub>&gt;::value
  && Pred&lt;Arg<sub>1</sub>, Arg<sub>2</sub>&gt;::value && ... && Pred&lt;Arg<sub>1</sub>, Arg<sub>i</sub>&gt;::value && Pred&lt;Arg<sub>1</sub>, Arg<sub>i+1</sub>&gt;::value && ... && Pred&lt;Arg<sub>1</sub>, Arg<sub>n-1</sub>&gt;::value && Pred&lt;Arg<sub>1</sub>, Arg<sub>n</sub>&gt;::value
              &vellip;
  && Pred&lt;Arg<sub>i</sub>, Arg<sub>i+1</sub>&gt;::value && ... && Pred&lt;Arg<sub>i</sub>, Arg<sub>n-1</sub>&gt;::value && Pred&lt;Arg<sub>i</sub>, Arg<sub>n</sub>&gt;::value
              &vellip;
  && Pred&lt;Arg<sub>n-1</sub>, Arg<sub>n</sub>&gt;::value</code></pre>

## Type Signature

```Haskell
LeftReview
 :: template<auto...> class...
 -> auto...
 -> auto
```

## Structure

```C++
template<template<auto...> class>
struct LeftReview
{
    template<auto...>
    alias Page
    {
        static constexpr bool value
        {RESULT};
    };
};
```

## Example

- We will check if every relative-order-preserving pair of `0, 1, 2, 2` satisfies `IsNoGreater`.

```C++
/**** IsNoGreater ****/
template<auto L, auto R>
struct IsNoGreater
{
    static constexpr bool value
    { L<= R };
};

/**** Test ****/
static_assert(LeftReview<IsNoGreater>::Page<0, 1, 2, 2>::value);
```

- Note that the order matters when the predicate is not commutative.

```C++
// Reverse 0 and 1
static_assert(! LeftReview<IsNoGreater>::Page<1, 0, 2, 2>::value);
```

## Implementation

For every variable in the list, we will check if it satisfies the predicate if paired with every variable behind it.
We will implement this process in two steps.

- First, when given an index, we query the predicate with the pairs consisting of the variable at the index and every variable behind it.

We will expand the constraint `Prefix<***>` alongside the arguments to pick out the variable at the index.

```C++
template<typename, auto>
concept Prefix = true;
```

`LeftInspect` will help us translate `std::index_sequence` into a pack of indices.

```C++
template<typename>
struct LeftInspect {};

template<size_t...I>
struct LeftInspect<std::index_sequence<I...>> 
{
    template
    <
        template<auto...> class Predicate,
        typename Inspector,
        typename...RestArgs
    >
    static consteval auto idyl
    (
        Prefix<I> auto...,
        Inspector,
        RestArgs...
    )
    -> std::bool_constant
    <(...&&
        Predicate
        <
            Inspector::value,
            RestArgs::value
        >
        ::value
    )>;
};
```

- Second, we perform the first step with every index and combine the results.

We will encode value information into types by `Vay` to avoid defining the body of helper functions.

```C++
template<auto Variable>
struct Vay
{
    static constexpr auto value {Variable};
};
```

```C++
[]<size_t...I>(std::index_sequence<I...>)
{
    return
    (...&&(
        decltype
        (
            LeftInspect<std::make_index_sequence<I>>
            ::template idyl<Predicate>(Vay<Variables>{}...)
        )::value
    ));
}(std::make_index_sequence<sizeof...(Variables) - 1>{})
```

Here is the entire implementation:

```C++
template<template<auto...> class Predicate>
struct LeftReview
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr bool value
        {
            []<size_t...I>(std::index_sequence<I...>)
            {
                return
                (...&&(
                    decltype
                    (
                        LeftInspect<std::make_index_sequence<I>>
                        ::template idyl<Predicate>(Vay<Variables>{}...)
                    )::value
                ));
            }(std::make_index_sequence<sizeof...(Variables) - 1>{})
        }; 
    };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGwA7KSuADJ4DJgAcj4ARpjEIACc/qQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCcmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimGmujMh4mAq3R%2BdXN6f/xx%2BlwuwLMAGYIshvFhbiYwW4vI5aIQAJ5w7Ag8wQhhQrwwuFuZATdBYKjozG/I63ZTETA0VRfQ5AgiYFhpAwsgkEFHPZhsUi3JiI1Dkq5oHFPAjU2n02Fg%2B63AjELyYOFWK4gv57W4ANSYKMZB2ZrPZTE58KFRF1rTwTFi9FFlwmyoc1rRGsCFluc0cyFu4ommFUaWIguFtwAbmIVbDPXriLb7arAvc1bHU2D1cDKQDc99NVSAJJs%2BhsQRmnKGs4FvO1oEglkls2q%2BHc3msFsYq7Oryu0J0giFhgKZ6ukye8cZrMNk0cltuLIAL0wAH0CAA6TeFx09vsDocjzAOAnEkAgCJYVQrpQARxVEoJhc36/JYOwsI9Wdu38Vs%2BbIJ/OU3AAwCf0bU1zTcS1UGfdF/QMBRPhpTB8FEFlSBA0DFR5RgO1uA9RyIMhMNAttcLYZ8ACUPgIS5iGABQSMdQCfTwP0AxZKNaDDK08HQFFaBIiASMA5D6UfODoOfDCriw78CKPIiZMuOTbmoiY6IY2DZJ/ZYSIAWjg08QFiVBPBXDjDAIJj4QgWCzH8cxHJ0rDkNQ/8XNAgkRLkhSHBIM8uJVZTVMA9TaPohRAujVVPMA5i5Oi7xYpU3TX2nFM1QpS5wLnLk/0gqTNzgqEmEQ6UULY/83xBXcpX7KgCGoiN3gAd0xCdPNy6qoOFZ940TehGJqzy6ulVAiGUJhgBS%2BLOtSrDWPYgRA2DUNTM8SMYp879xy/ULdoAVisQ6MwXPBlzXZ9tzfCBjIvINr0wO9XnnJ9irfPS4rkvadtC2kCA2Bg/tUuziocpzhO%2Bg7AKwKEyJBmGoYWmGDoawdh0Ik8CHQM8WCYABrVcHqvW97y2CSapGlHUdUs9upZW4%2BIEgk3Kq81sAgPU0XhAa7SG8kJxTZ8vpp2nv2WJKVURrDlj0zMZfTO6cbxwniYYS8npeh94SXTBUCoZ8uZtfmPmWW59NuLhBasFNRdUyc0yYzKFY1LqCvnIr1z5pNhq7FGvCyIxqWmzA5QVGkJtQKaZoJH2htgqmMqnbKtVrU4gS1W4ADE8GICZbmwVRWHZMP8xzdP/nrCvtULBQolQABxWlm1Dcuco9gloNuUIBW7yidyVXspTrhvm8wVuOv278lv9FaWTW24Nu4oLZp/Pae%2B8%2BU1PTLKPRTt3ripAAVGiqyBJaVzKpQ2ggdHmrax966bluWWIdEzxj%2BcNAFLgBTMf%2BH8QCr3ltOGulcTiZypEII8Ah0CF2LiWMuTIawQIzqnHYalMARgSEoW4GhBQaytrVFovor6IQSAQCAYAwA9wHA/TA7V4SjxfhPN%2BQCv4Ej/vg/%2BgC3xS0wKAjgqxaCcEOrwPwHAtCkFQJwYClhrDenWJsMOWIeCkAIJoYRqwCYgEOpIdcGgAAcZgzBJCSFwQ6xijFcECIEaQoiOCSF4CwCQGgf6SOkbIjgvAoo/00VI4RpA4CwBgIgEA6wCBpEROQSgaA2R0ASFEDsnBVBGP8PpfwkhbjAGQH6KQ64zC8EqkRPieh%2BCCBEGIdgUgZCCEUCodQgTSC6D/q1YgTA0icB4CIsREitEyM4AAeURNEqUBtbhpIyVknJeSrYGLMLcCAHgEn0FDGo5YvAAlaFWBAJA8S0iJLIBQCAByjkgGAFIABNBaBvyihAWIAzYgRFaCibpvBnnMGICiIZsRtCKXeaQeJZYCBDIYLQN5zSsCxC8MAKCtBaBRW4LwLA%2BMjDiChXnRSeAcFIukUGI8iJtjqIiCyRx0jkSxA6d8jwWABlKjwK45FpAcHEFMkoR4aLgDIiMFo1YVADAMR1G1IZvJAUVOEKIcQtSJUNLUAM1p%2BhDDGGsNYfQeBYhRUgKsVAaRGhIv0sSOE9xTAKMsGYLxrKExYC1RAVYdhsXOAgK4aYfg/5hAiMMKoow/7FGyAIV1eg/WNAWCMRIf8HUOD6JMdonhOh6EjY0fobRQ3evDbYGNgaI0xtTUsLg9rlFbAkL0jg4jSCeN4N4yZ6TMnZNyfkhZSzcCEBILCcE%2Batl8tWAgCeWBEh2tILoyQYJ1xJDBPYjQkgzCSH8O4w6/gkj6E4M40griwRcHXP4Lg/gjFJBsf4fRlix2pArYMnxtgQD%2BL5cEsJeyImjJiScs5azklsE4K0FgEZAj6SYPBZVVskjrg3fi/ApTcZ/wlVU6V0hZVKHlc03QAD2mdPeSWstp7vEjKiYiW4Eypm1r/cHLggHgNLJWYctZbawRmE2Ro69d7n0JFiac1AqzRilSMMRrgP8bl3MoI85pnzXmAqE9835/yHCAuBYwUF4LIXSOhbC%2BFiLAWouVRihTWKo24oGQS5ARLAWkvqAMyl1KUS0u2NIhlTL1GsvZZgTl6mIigECfywVChhWMNFYwcVsgoM1Jg7IOVTTpGIaVby01VhLDqs1fAHVeqcgGqNfKSL1gLWVqtXxD4cWeiOr8M6jWWaQga1zT69ImR/W5DjQUX1FWQ2esWGVxN0aBhFeawIZNgwGthoTZm6rbqM3zG62m4tawNhFvzUu0t/TmlVvwzMjjwAANAcMU20DraNmdtc923towB2OJXWuwDk7AiHSSHYsEU6Z2SD/hhzgvjL10dcze%2BAd7IljOY4x4gr7tgfpmSwBQEY/QRmI%2BuOcExinreteUvzUqAt1PkHBkLOgQBglIMhrpyK0Mza8cMh94yqCTP%2B4D4HoPwdSmWaxijCQqNglo9soJDGqdHM%2B8ztZwDkBpDSCuEHSQVzk5XKoLJfA6B8YeU8l53yROS5%2BX8gFzLpOCDBRCgZim4ViBU8ytT6LLMoq044HTzS9MGeZUZ8lvBTOvIs/ShMNneB2cyA51kTneXPYFdNDzIqxXMsg3DiQgX6lI4Vaj8LKqzU2Epba%2BL%2BrOA7FPKl81lqEjWuy9q3LUanUuv63oD1FQeu1ZKDkIrwacilfTe1pofX8gDYr51svvXWvZ%2BzUNvPI3JsKELTU7H5aBlzeJ0DyMZPmwFwgM2oiVGO1PZ2TtpgfbKAlsOyAMx64wRgkOlYm77jV%2BBB3T32b92L1Xu24OkAkhDqjtsYEdxRjJAWK4CYhyU2wQ48rQfhncsptFL37j897/VisqyGcEkCAA%3D%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/left_review/implementation.hpp)
- [Source code](../../../../conceptrodon/pagelivore/left_review.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/left_review.test.hpp)
