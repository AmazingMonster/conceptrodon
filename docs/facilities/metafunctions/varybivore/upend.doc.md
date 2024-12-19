<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Upend`

<p style='text-align: right;'><a href="../../../index.md#list-modifications-7">To Index</a></p>

## Description

`Varybivore::Upend` accepts a list of variables and returns a function.
When invoked by an operation, the function instantiates the operation with the previously provided variables but in reversed order.

<pre><code>   Variable<sub>0</sub>, Variable<sub>1</sub>, ..., Variable<sub>n</sub>
-> Operation
-> Operation&lt;Variable<sub>n</sub>, Variable<sub>n-1</sub>, ..., Variable<sub>0</sub>&gt;</code></pre>

## Type Signature

```Haskell
Upend ::   auto...
        -> template<template<auto...> class...>
```

## Structure

```C++
template<auto...>
struct Upend
{
    template<template<auto...> class>
    alias Rail = RESULT;
};
```

## Examples

We will flip `0, 1, 2, 2` and invoke `Operation` with the result.

```C++
template<auto...>
struct Operation;

using SupposedResult = Operation<2, 2, 1, 0>;

using Result = Upend<0, 1, 2, 2>
::Rail<Operation>;

static_assert(std::same_as<SupposedResult, Result>);
```

## Implementation

The implementation is similar to `Varybivore::Amid`.
We will label each variable by its index in the list and collect them into a roster.
When provided with an index, we instruct compilers to pull its corresponding variable from the roster.

First, we need to create a label class.

```C++
template<typename Treasure, typename Key>
struct Label
{ 
    static constexpr auto idyl(Key) -> Treasure;
};
```

Note that `Label::idyl` maps its parameter type `Key` to its return type `Treasure`. We will pack each variable into a `Vay` so that we can use it as a return type:

```C++
template<auto Variable>
struct Vay
{
    static constexpr auto value {Variable};
};
```

We can pull out the variable of a given index by asking `decltype` the return type of `idyl` if invoked by the corresponding `Key`.
For this purpose, we will convert an index into a type via `std::integral_constant`.
So, the final mapping will be as follows:

<pre><code>std::integral_constant&lt;I&gt; -> Vay&lt;Variable<sub>I</sub>&gt;</code></pre>

Now, we will assemble an overload set and instruct compilers to pull the variables out in reversed order. Here's the entire implementation:

```C++
template<auto...Variables>
struct Upend
{
    template<template<auto...> class, typename>
    struct Detail {};

    template<template<auto...> class Operation, size_t...I>
    struct Detail<Operation, std::index_sequence<I...>>
    // We create an overload set of `idyl` through inheritance.
    : public Label<Vay<Variables>, std::integral_constant<size_t, I>>...
    {
        using Label<Vay<Variables>, std::integral_constant<size_t, I>>::idyl...;
        using type = Operation<
            // Note that `sizeof...(I)` is the total number of I...,
            // which is a constant.
            // We are doing pack expansion over the second I.
            // The result is a list of form:
            // sizeof...(I) - 1, sizeof...(I) - 2, ..., 0. 
            decltype(
                idyl(
                    std::integral_constant
                    <size_t, sizeof...(I) - I - 1>{}
                )
            // We pull the value result out of `Vay`.
            )::value...
        >;
    };

    template<template<auto...> class...Agreements>
    using Rail = Detail<Agreements..., std::make_index_sequence<sizeof...(Variables)>>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxBLSAA6oCoRODB7evgGkyamOAqHhUSyx8VK2mPYFDEIETMQEmT5%2BgXaYDul1DQRFkTFxCbb1jc3ZbSO9Yf2lg1IAlLaoXsTI7Bzm/mHI3lgA1Cb%2Bbl6OtIQAnofYJhoAgpvbu5gHR8gKBOhYVFc393cEmBYiQMAMObgI50SjFYzwAKsRMEwFCtMKQ9hCocw2HsANKYS7%2Ba53d7ELwOPbBJixWi/EwAdgsBzuexZe3eTEcyD2aAY70wqkSxD2TBOqD2eHQ51oEDx53mewAtFc9vDEciEYcrHd6QARTW0/6A4EczBgkVEPYANQaeCp9B%2BxIIpPJAFkBKgiAxLtqGb9WWz6pzuQI%2BQKheaxQA3MReZ70izW4i26L2ul6/xa%2B5p/Xaw1AkGmo4RgB0pcTyfoCgdtxJZIIezkmPQtN9zNZAPzJrBHeNoKLotLxeVOyRCjRGOhbGr/tr5J1mHqdAOvuzGYNt39PYL3aN2/7REHw4MCgUewA8lDiBz0mjUgAvTAAfQIg4AktPWbP6/PFzSjhe4mvARbw%2BEAQDCLBVEfJQAEdYwYNYwVfQ9CQ/FkAHp0L2AB1Z5kARE1hQYPZUEjOJaFQJh0DZBcSKoA4ADYNAlKUTCY9EEGIZZgAQcUGAQOJCEMNYhzbFkQD2RIvBTPAuUpakwTdBgPQEAk3HLO1MCrQkQPQMCwgBYAr1oR8eXZQQwXvJ8CDRd9UMJQ8xOXTN/X9LxUiMCkqSqRT3U9NSNJTLSrl0/TBEwIyxFMkN6gso4rOfWyfkJfTJVoFCXNcll3LCYB0UhON/B1c9LyAhgwT9LLXMwvYIg9Z4CAQDlGI0KzUCoQcIFfeY2I0cVT0ahqPTEPYGAGIV2r2ZDS1ISqqtZGqAHcEFk3i8FPJhg15WKXzm%2Ba9hq3DhQRPZ0FQXLJKYZAAGs9n5RJDFSAQSLIoVBponlqOQvb5pq2EBL2BFkVoet1uFPYzneOi9n4YgWBAH6qpqtqOtLLr5QVPYuFvPAH3azrusVPYzDRQc0Q0YsmQ3faWSwHYJwgRGaZY6UmZpz9QPA8LIpMsydrZ9mXjcBKbLZXHMHxtHCcx18ia4H4Vz1JzBZ65Wkawo6pNoWgOOeaNvGeIGvBBkiTmh3qlJUr1etE6mafmMD9djRy7dc5LMpZXUcz%2BV2ty7I4/b7NwS1LI9R0HW4jMwQFGAIbSiVdnLPIAJSYJdDmKn807/NxI4RGPBAUMmAz0kAWCYa6nwg/loMwODGEQ%2BLxcl4sIECysevs7AwInb2vbXXNbnQgAqUex/H9DfhH0fYWwIRYTHye7mn8eJ/XB4EKeIWeTWRI4%2BrX5A8LYOB1D1DHWdesAKvGo%2B7uJO8qELxEjyTB0GTrTjfrDOSsA2%2BjhJsTNE2M9gaHduuB%2BewP7A2/kVBsTYwQaGAWiQBZhqxgVTnQME18yrgMHuyTkj5RxxAIBAd4pcFAwiIdpNwT8X4pDftAr%2BaImEgyuJ3CwHBFi0E4AAVl4H4DgWhSCoE4G4aw1g2TLFWHGMw/geCkAIJoLhixrogF4WYYsvCACc/heEMV4f4eRvCAAcZhJAaGkDwjgkheDwy4BoJBgjhGiI4LwBQIAkFKKEVw0gcBYAwEQCAZYBApI2QoBANAQI6BxAiDCTgqgTEMQVAxSQexgDIC5FIYsZheBv0ICQCUeh%2BCCBEGIdgFQSnyCUGoZRpBdDY0WleRInAeDcL4QIuprizwnDCdDRJyTUnpMyVjSQOS9gQA8NE%2BgQpNhcHmLwbxWhFgQCQFExIMSyARPWZskAwApAkxoCDOIHiIDRDqdEMIDRzitN4Jc5gxBzhnmiNoDo3iFFRLYIIM8DBaA3J8aQLA0QvDAGDtrDx3BeBYHLkYcQAL8AIk6GRCFwj%2BQdBOOsBRBkqh1LONEK8jyPBYDqU6PA8NIWkFetEBh84YXADOEYZRiwqAGGAAoS0eBMCLQAoIhRVSyniEqbIRQKh1AAoafoQwxgJGWH0HgaIHjICLFQHvdIEKFTkIzqYSw1gzAuNekmLAiqICLHaJ0ZwEBXBjD8NjEI0wShlD0HkNIAhrVOpSC6hgfQHVzEqNULokw3XYzNTUbojRvXjT0OyUYngWhRsmBG2Y5RTXSLWBIdpHB%2BGkGcbwVxewBkpLSRkrJYyzATNwAU2Zcj5mLKZYsASVFBgmtIGoyQ/hiy6LpBYyQ5imIaH0do/QnBbGkHhvI4sDEuAMRMdokxU7eGSC4Do/wDFs1dM4O4zxiimV%2BMCas4JvSTjkEoDsmZcS2CcAaCwSMdIFSbRHJ5Lg2jixcGLKi/ARBDXFNkAKip0gqkitqeKkAJMmlMBaZCjNWac0iM4D00JZtJpXpvXe7kBhH3PtfX1SZqBplxAOHIswCzt0%2BJWWs3DGyZnHsiRR3ZyHb0Pv2dohxfA6AAmIKc85AL7nXNuaQHjjznmvIcHxz5scfl/LqUCkFYLaAQoUdCqVcLhEIreXgZFdS0XIAxXx7F1jhF4oJecIl6xhGkvJQoqlNLARKdyjullTA2Ucq5Tyvj/LRCCv/cKmpYrhG6BJuh6VOrZV4uNcq1VIZOAao%2BFqmVFg9W5oNRKLS8BTVVDUxaq1sbsi2oYOgRNjrsbOpqEG3IHqagFd9SGgNPRSvVYEGGqYxRI3BsDdlm1wweiVeTUsFYab5lDszZ0gFeb6OocY1jTDb7y0fpIAR%2BRxGlkqNIA2rA8Rm3WJHWO59li6Q6LpHSfwPbJCpOxjB1xm6vE7v8UEkJYTqOntifEjgV6hksAUJGLkkYn3FgLO8PJs2v3Y3c%2BUoYAGfN1N0IEMDEG2mDeg%2Bujg8G%2BlIbhm9j7X2ft/frDhvDVajGLeu%2BRvHD3aMzJAJ9l%2Bj5vvaMfNjohaP/1sZOZQLjwiBP/IURzoTbzRO4a%2BQQCT/yVOYGBaCsQcm%2BOKdhaZqFeBEWOA0wCrTOmKV6dxfKozJmSVJgs7wKzShaW2cZaRvgrL2Wcu5ZiNzP6PN/pkIIQDvmdA5ECygOLcqFWpZERF3knB0LkPd8F%2BL%2Bq4iGpS0qv1GW/CWry6Vu1zWk3uvyOkUrxX0jdajel81tQ2tZA6/V3PXX7Utc6zG/P8bi%2BJ8KymvrFSoPDZcZwY6LB0efb2DT37JooYQArZ%2B%2BbNaSPLPrYiNblAM1bZA8%2BoxvDeGWIcRoIxdJp1rpGxu2wW6lvzFUSASQdJiwWNSUdhi07F17e0au6x/hG%2B5vX1vjNuTV9N7cUP5br0np%2BEkEAA%3D)

## Links

- [source code](../../../../conceptrodon/descend/varybivore/upend.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/upend.test.hpp)
