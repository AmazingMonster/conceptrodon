<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::CognateTransform`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-cognate-transform">To Index</a></p>

## Description

`Pagelivore::CognateTransform` accepts an operation.
Its first layer accepts a list of predicates.
Its second layer accepts a transformation and returns a function.
When invoked, the function transforms its arguments that satisfy all the predicates with the transformation and instantiates the first operation with the result.

<pre><code>   Oper
-> Preds...
-> Transf
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> Oper
   <
       (...&&Preds&lt;Arg<sub>0</sub>&gt;::value) ? Transf&lt;Arg<sub>0</sub>&gt; : Arg<sub>0</sub>,
       (...&&Preds&lt;Arg<sub>1</sub>&gt;::value) ? Transf&lt;Arg<sub>1</sub>&gt; : Arg<sub>1</sub>,
                                &vellip;
       (...&&Preds&lt;Arg<sub>n</sub>&gt;::value) ? Transf&lt;Arg<sub>n</sub>&gt; : Arg<sub>n</sub>
   ></code></pre>

## Type Signature

```Haskell
CognateTransform
 :: template<auto...> class...
 -> template<auto...> class...
 -> template<auto...> class...
 -> template<auto...>
```

## Structure

```C++
template<template<auto...> class>
struct CognateTransform
{
    template<template<auto...> class...>
    alias Rail
    {
        template<template<auto...> class>
        alias Rail
        {
            template<auto...>
            alias Page = RESULT;
        };
    };
};
```

## Example

We will apply `UnaryMinus` to variables divisible by two and three in the list `1, 12, 2, 6, 15`.

```C++
/**** DivisibleByTwo ****/
template<auto I>
struct DivisibleByTwo
{
    static constexpr bool value
    {I % 2 == 0};
};

/**** DivisibleByThree ****/
template<auto I>
struct DivisibleByThree
{
    static constexpr bool value
    {I % 3 == 0};
};

/**** UnaryMinus ****/
template<auto I>
struct UnaryMinus
{
    static constexpr auto value
    {-I};
};

/**** Operation ****/
template<auto...>
struct Operation;

/**** Metafunction ****/
template<auto...Args>
using Metafunction = CognateTransform<Operation>
::Rail<DivisibleByTwo, DivisibleByThree>
::Rail<UnaryMinus>
::Page<Args...>;

/**** SupposedResult ****/
using SupposedResult = Operation<1, -12, 2, -6, 15>;

/**** Result ****/
using Result = Metafunction<1, 12, 2, 6, 15>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

For every variable in the list, we transform it with the second operation if it satisfies all the predicates.
We will do this using the following helper template.
It decides whether a variable shall be transformed.
The selection is done by a partial specialization, which is specialized by a constraint.

```C++
template<auto Variable>
struct Hidden 
{
    static constexpr auto value
    {Variable};
};

// `Puberty...` are the predicates.
// This partial specialization will be selected
// if `(...&&Puberty<Variable>::value) == true`.
template<auto Variable>
requires (...&&Puberty<Variable>::value)
struct Hidden<Variable>
{
    // `Hormone` is the transformation.
    static constexpr auto value
    {Hormone<Variable>::value};
};
```

Here is the entire implementation.

```C++
template<template<auto...> class Operation>
struct CognateTransform
{
    template<template<auto...> class...Puberty>
    struct ProtoRail
    {
        struct Slash
        {
            template<template<auto...> class Hormone>
            struct ProtoRail
            {
                template<auto Variable>
                struct Hidden 
                {
                    static constexpr auto value
                    {Variable};
                };

                template<auto Variable>
                requires (...&&Puberty<Variable>::value)
                struct Hidden<Variable>
                {
                    static constexpr auto value
                    {Hormone<Variable>::value};
                };

                template<auto...Variables>
                using Page = Operation<Hidden<Variables>::value...>;
            };
        };

        template<template<auto...> class...Agreements>
        using Rail = Slash::template ProtoRail<Agreements...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIACcZqQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCcmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnhzsmGgCC%2B4cA1ACSLGn0bIJMjbdH51c3p3%2Bn30uF0uBEwTwMoJMgTcoPB70wULcTC8RAAdOiodhbsgDAoFLcAPJpBLvHKY4ETYheBy3DzAZiggAqxEMCn4xBYwJMAHYrFdbgLbrDnvDEcKIQjoci0RjAlicUw8ejUcovNUCABPcn8wWU6kEW7KYioIgAJSYdGBgtuPL5l2t1r1NKEuIQVodAtt7o91vFouhfshUpRqGVmOxuPxAAkSCwBJLsN6fQKnQajSbUObLTrk57eUnc4LA5KkSHbgA1Vp4Jixeja%2B2Fh2p25RvDoLAMG05xt5u095NzRzIbECCaYVRpYi3aWoW4ANzEXgR3f7gttleI1drCO5ABEoX3Vza9weuSvG8XETOK1Wa3W5QXG8RMABHLx4Z/4iBhswANnMv6quqWrQhuW73tgIAgAu3iYMsj6Fs2rbtowiJgXeCYIbmXrnqug54MOaAMGOE5TteMFLlhPa2jGHLxmht7bpiUEUTu%2B6BIeq48uxdpUT6l7BjKqLoduCj1ketxeFkRiGkwwCYDagS7oSxIso0iLIR2DGbhhYlyixi6YGGD4cXxeY8Vh3GnlcWECTCYIikGpZCeGCpKuilzAM%2BYKMAQemJrhknScAtxZrQinKS6ipICAxaGsaZoWrQiKed5rx%2BcZiamd2VnZUC3Z2XZM6ZRGioKMqqWYD5gj%2BUmUkRCFYURfFGZhSlXlVel5WyllvEnnlwK/P8xyAkNtzYKorDPApXyDcNAJnkCZiBBEOJeFgiluERWxpH59ZzXcu54HOeBZNuFgaoyADus6zVcRVlvc9bNkdJ1nfQF3XagXL5t2%2BGEaOoKkbcsSoJ486GUmtr3DaZj%2BLcZgRVCykaLlfUWTZPxHLcr2nXg52XQg3mfGcwIPUQDzPQQVI0rj72YJ9RNVT9nG3P9I7EUDk4g2D4WsVDvIw%2BY8OBEjSm3Kj/Xo9Z%2BXXNjcjMMQGoALIRFJJMHIC5Ozk9D5XM2CutCratiTZv0NimLRDhzJHc%2BRkM5byAC0T1Sz9GOy2NRIkh8d0gg5EpXiGmUUtT%2BoqT7ZIDVjdzK5gLRUF4DAODkGt7FrAf%2Bs5oYecQwC1Vc9UyXHCdJynAjNXSDKYMyrLspy0Le2pUcBZcUFtdCdP4x9l03aQOPHXjBOMkzmFXO3SWIobSuqwwUn1lByhySWlx591qLktHct3EIXhpMUmDoKamAKF4tAGn7Rchbv%2B%2BZIfx%2Bn%2BfzVN6SAiIlw/dO1wqQI5/v791wfwm9eIxwOKFE%2BZ8L6k0LsFcBj8DTI1uCXJgidk7qWhB/W439%2B4/3/lgoBJkQHbzAYyE%2BUDNah1JMgAA%2BmVBIBAIATHQFBBQrBMC0L0m4B%2BkD%2B43wPkfCB59MTwQ4hwVYtBOD%2BF4H4DgWhSCoE4G4aw1g2brE2ApcwgQeCkAIJoMRqwADWARJCog0AADjMGYJISRAHmLMVwbk3JpASI4JIXgLAJAaA0KQGRciFEcF4AoEA3jdGyLEaQOAsAYCIBAOsAgaQUTkEoGgJ4dAEhRDYZwVQZjfxO1/JIW4wBkDDikKiMwvBD6EBIG2PQ/BBAiDEOwKQMhBCKBUOoMJpBdAfyuiyNInAeDiMkdIvR8jOAEhRAkg0qAqC3Gybk/JhTilYJMYjCAHhUn0CnJorgyxeChK0KsCASAUlpDSWQCgEBTnnJAMAKQqQaDnwSEEiAsRRmxAiEbAZvAPmKw1ASWI2hMAOG%2BaQFJ6UCQMFoBqUZWBYheGAEiWgtAgncF4FgFghhgDiE6fgZ8Kc5wn1GeOYFKJtjaIiKCFxcjaD4xZErDwWBRnUzwB4tFpBCXEFBkoXcYIsW0qMHo1YVADD53LHgTAV1vYyO0XU4QohxDNLlW0tQozun6CxSgZRlh9D4yCZAVYqBdo5FRU7JhyNTCWGsGYPxnLNxYH1RAVYdhgWNBcAwdwnhOh6DCBEYYVRRgf2KNkAQ0w/BBsyCGhgCwRiJA/i68uTRJjtC9QUeN9RXV9GTTGgNcbbDJrDXoOYbQc1LF2WsDYWwJBDI4FInxoz/FzJyXkgpRSSmrNuBAXAVTtnLV2fsoVqwECYCYFgRITrSBGMkIEVESRAhOI0JIMwkhfxeP8L%2BJI%2BhOBuNIB4rRqJfxcF/GYpI9jfz%2BEkIAud/9fG8H8YE4JOihUROicc2JkzEmXOuVsjJbBOCtBYHObkTsmClRklwJIqIuCmIqfgIg9ramyAaYq6QyqlCqs6boVIvSmD9LRTWutt6xkcAmfElEtwZlNoWQUhU4HIPQY0J2jZZytmw0CGYPZT6wlHJOagTZCQklXL4yx0YtG7k2O8Y80ExAXlvM6b8r57KFNKwBUCkF7LwW%2BUhdC2FmB4WIrECi0FGL%2BXbDkXizNhLUVyJJcgMloLKX1FGbS2I9KNSMrM/szcbLtGcu5ZgXlmKjACtANxvgoqFDisldK0FcrkNNNQ7IFVHS5FYY1YKy1VgdUucdYa41o5OBmoIOgC12qLA2rvXatsRKDU9Ezc4CArhC0f19RUWNehg2NGa%2BkSNjRS2Brq4m/oUxU3hsG40Ybgw/WLAG8WlN%2BQxtzf63G51aiq3lpcYRhtnAqMtrAyFCDUHTGdu7fBtj/auOHKHSOsdlAa07r3ZBxd3J/BJEcYEJdK7L31s6fe2wj6DnhMiTEuJUzBPfvSZkjgAHFksAUHOYcc5DsSgmLBntNSP5xYVQllp8h0MpZ0CAYIOG8ODK3bWkZv3xkfumbM1QsP4eI%2BR/CCYTHhPnLY4ETjgOeMoHZ1s8H/PRgI/3tQpHSRqEo4INQ%2BnqG6DSdk%2B8z5StQXKf%2BYC11oLNOCG0zC3FemEVIqM%2BykzwXPOkAswSolnTbP2fZY56lvAXNuY88y7zoK/N30C/yhqz6RVyUixKqVxIZW8Cx40iQiXWn47VUT9Lxgyu6tiLl%2BR%2BXiKcB2EwrVVrLAVfkVVh18BnUZsTe6z1C2fUeuWx13rORuudZyNX9NvQBCTe6wmib2bpvtfjQW0bRau9tdzdWit6iR%2Bbcp34nbsvbhw4R/OZnoJWddrgyQc73PB2kGHaO0YE6XEPZAFY1EgRAj%2BH8IurgXiT/cmPT9qfAT/shM31O/ws6HHci8WYyQNiuAWL/OTwISfO9TgAdbjGtcpO/YAh/HnVYTlLIZwSQIAA%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/cognate_transform/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/pagelivore/cognate_transform.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/cognate_transform.test.hpp)
