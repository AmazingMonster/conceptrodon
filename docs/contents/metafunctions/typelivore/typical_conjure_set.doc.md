<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::TypicalConjureSet`

<p style='text-align: right;'><a href="../../../index.md#list-modifications-6">To Index</a></p>

## Description

`Typelivore::TypicalConjureSet` accepts a list of elements and returns a set that:

- contains every element in the list;
- doesn't contain repetitive elements;
- preserves the relative order of the list.

<pre><code>   Elements...
-> MakeMathematicalSet(Elements...)</code></pre>

## Type Signature

```Haskell
TypicalConjureSet :: typename... -> typename
```

## Structure

```C++
template<typename...>
struct TypicalConjureSet
{
    using type = RESULT;
};
```

## Examples

We will turn `int, int*, int**, int**` into a set.

```C++
template<typename...>
struct Capsule;

using SupposedResult = Capsule<int, int*, int**>;

using Result = TypicalConjureSet<int, int*, int**, int**>::type;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

Assuming we have smashed every element that has already appeared, the ordered collection of the elements left is the result we want.

To translate this idea into actual code, we need to implement smashing and collecting.
We do this by

1. placing each element in a capsule separately;
2. taking the element out of its capsule if it has appeared before;
3. concatenating all capsules.

We can merge 1. and 2. by:

```C++
template<auto>
concept Prefix = true;

template<Prefix<I>...FrontElements, typename Inspecting, typename...>
static consteval auto idyl() -> std::conditional_t
<
    (...||std::is_same_v<FrontElements, Inspecting>),
    Capsule<>,
    Capsule<Inspecting>
>;
```

`concept Prefix` is a technique explained in `Typelivore::Amidst`.
Namely, we use `Prefix` pack expansion to enumerate parameters.
In `std::conditional_t,` we check if `Inspecting` has appeared in `FrontElements...`.
If so, an empty `Capsule` is returned.
Otherwise, `idyl` returns a `Capsule` containing `Inspecting.`

Here is the entire implementation:

```C++
template<typename...Elements>
struct TypicalConjureSet
{
    template<typename>
    struct Detail {};

    template<size_t...I>
    struct Detail<std::index_sequence<I...>>
    {
        template<Prefix<I>...FrontElements, typename Inspecting, typename...>
        static consteval auto idyl() -> std::conditional_t
        <
            (...||std::is_same_v<FrontElements, Inspecting>),
            Capsule<>,
            Capsule<Inspecting>
        >;
    };

    template<typename>
    struct Hidden {};

    template<size_t...I>
    struct Hidden<std::index_sequence<I...>>
    {
        using type = Cotanivore::Paste
        <
            decltype
            (
                Detail<std::make_index_sequence<I>>
                ::template idyl<Elements...>()
            )...
        >;
    };

    using type = Hidden<std::make_index_sequence<sizeof...(Elements)>>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMxmpK4AMngMmAByPgBGmMQgAGxcpAAOqAqETgwe3r4BQemZjgJhEdEscQnJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlUbHxSSkKza3t%2BV3j/YMVVaMAlLaoXsTI7Bzm/uHI3lgA1Cb%2Bbl6OtIQAnifYJhoAgjt7B5jHp8jj6FhUt/dPZl2DH2XiOJzcBCuqUwAH0CMQmIQFH9Hv8CJgWKkDOjwZDocw2KRDkxzqgUQ80MDMKkCIdlMRMDRVO8ACKHeFeTAnKyox7ozHYrmnPGMViYAB0kvJ42IXgchzcTFSCi89G5/3%2BAHpNYcACpQvCiWjKJjjLl8jFYpg44VQ0VsSXi6Uc%2BX61KGsQms3HADsVh9LPVvIe2sOFlNbya1JAGotAutQohdoJbxNyAA1ph3LJERFiM7Za6DUavTa3GnM9nBLn4uSTH7/ocm4cvJkjOy7ay6UwM1mPNXwrX/DyngGg09HqGAEqYZDrTIAN0j6NSMeD/KtONRp0bzY3gtxybFjtuh32poUCpzg%2BID1Iu6b%2B4Th/xx6l/mwZ4MCkv/eaN5sB8O1fB1JWweg2EEB4FCJICRRTR1wIxRgCAsGC4KPUDxQAeQIBB4mRbc7keGU5VpN0PWNU0yz/Gtb3BJDIIIaCTw/IlaIAhiIJQtDWOwIlcPw4gFD4jUG0eZsWzbYBgLeE42QoktqPNB5JPBIDJI4vMnlORiUJYyUiT0wRePffiNObQSCJPCTm1uEAQBFcd60DYdYxDHVSxUp8y3gt9xQeYhgGRD9/lbcIZK8rtFM9ZTwUC4K%2BIcpy3ODUMYtofttHWTAhEwAg0UtA9bRAiUwO4wQQuI6CXXI4sxCynK8oK1FxNUvciufEr7SFarJNI%2BUWXyxFaF9f1XJHODOrLTIAC9YQIR0AElyX62rDiG/9aHBL4HPCLBVBhJQAEdOSpcEltE0LbKbesR0kySfMTelGTwVQLtuR0ADFiFkYyCBg2SU0OJaGAUaEHAiok/Kw1aHqbWZHGQM8BDNBcxGJUlDjwdArloCAlkOABaU9dpQAR8AaMQ4Qs26dxu%2BHmwgE8fTces3DJvAFCOsUYQXcEfr%2BiqAaJUHwdnRwjFuFZaYexVlVVRNbnvBnGYVJUVTVU4xYhyXgDh%2BG/lS9rbrHY2pvjXzMN6oCBtpAAJHGsAYMaXOchmnp2vB5rhZaDcOO3Dkd75GB2gh0D2hgDqOzBTsYTYLquvq7LatXwvbEUuy82X1NVxmsH2Jy8/hiBZbVzaRrDiOQBYJhMxhfbMEOk6zoT7WjeTtX4eS6a3hxvGuOQyq%2BIJsvmyWGyTYeo37pTib3Mk9OZMz%2BSg6d0PTjJ2v68b5vY9bxM5swVAqEdCB/oUJYO%2BSu1nLNybJwAKmfl/X81LUX91bAhF1F/36f1%2BgD/4TgBECEEYJTjnDoNcOscZNyJhhmVJ010aqFlpPLTWQoH4PCXocIQXhUhFCzDOTWtJV4YMVuCcIBAiTUMfrQwQz8Z7uVwSQ1UZD/AKXqplAQ2UGTNSoYIBhBB6HY0YaIuhj97KOVvubEizQkYwgvPEAgEAyYKF5qacEbDaA0LwQQoh6AdEFQ/FfYcHAVi0E4AAVl4H4bgvBUCcDZpYawAc1gbDkoCHgpACCaAsSsdMIBrFmHFD6MwkgAAckTrEaAAJwhI0IkSJ/h9CcEkLwFgEgNAaFIPYrQpAnEcF4AoEAuS/EcC0CsOAsAYCIBAGsAgqRzjkEoGgTEdB4iRDFJwVQkTEhE0SJIQ4wBkDIykOKMwvAsyEBIDjPQ/BBAiDEOwKQMhBCKBUOoSpOg9AAHcESrgcZYmxdj/GFM4Nhc4zTaQn0OH0gZQyRljMOBMswhwIAeA6fQYgxxvFLF4BUqppAIBIHae6H5rSIDgs6QkYAUggg0F0QRSgMRzkxHCC0K4nAfEYuYMQK42EYjaAlji3g7SmLYQYLQbFOzSBYBiF4YAipaC0FKQ4%2BlGJDDAHEHS/ADJIZLnZQUpus5zhbB8dQuo5zLgxARASjwWBznwjwFkjlS5iAxAyJgIatcjCXCMP4lYVADDBQAGp4EwHs7C%2BIyXrOEEaVZ0hFnyCUGoc5ugUgGENaYVxlh9B4BiKUyAKxUA0myOyomXx5K%2BqsJYMwBTUAauIDjTAwaCbdAltkFwUcph%2BBSKEQcCwRgpCKFkAQea9BloaPMYYCQxh1CzQIPokxPAdD0HYJtjQJgDCLXWjtPbK1jB7bWyoJaVgKA8ZsCQJyOC2Lyecop9z%2BmDOGaM8ZkhJkfNwLM35OwuAAt8UalY%2BEmBYASBmoJkh/Dijif4H0kgNCSAiYkHJ1jEhxLSRwDJpAsn%2BC4OKZIyS4mRK4IkaxkguDWLvYkBddKiklLKUenZ1S6mgoadclpFBoWoG%2BV0npHAWgsAXD6ImTAvzcteXE8UAGRWUzmRHFILrlniDWS6zZ7q6W6CCAcpUZLZ3zvyY4y5mHblUGJMQYjpHyPnnbFwajtGPlfIhfEP5gRD1AosSCsFuGVNkGwzCn5IAiMkaJrJ%2BFcSuC5KReiYSqL0WYoJXavFWKiUkocHailKEqU0vOQyplLK2V2qwHqnlWwCn8qzUK85oq5zojtVKqxdLZXyquIq8LgKU1qp8RqrVShdXcoNaAFDfBTUKAtVam1jA7XMcdRIZ1sgOPbIKdx/Q3KUDWGsAGoN8BQ3htRpwKN4cY2dfjYm5Nqb00TsbZDZwEBXBDuCFHUdixS0ZHLTkNt%2BQ1vFGyCtktmbZvdv6ItztR2W29vKP24dJ2tv5tsCOvtY760TqnasgTZz4OcAk1JsjFG5MKfFBobd9G93/MBce0gp7z2UFnT%2Bv91Gn0%2Bmgz6H0/hn2SCGSkITFzim2CQ5p1D8B0ONJuVCwz%2BG2CcCI08lgCgFzIwXPJ8UgpxjTNB/MpjsgWNOvtU1j1ARSC8aOTwD7cHE0iaaecQ4dyafDLpwzw4TPqOs9pJ83TsK1P%2BA00a7T5M8P6baRrozDPCF83kzCVXSjJNDL4HQWzpSIBorpS5pzHLXeEuJaSjlXnBA%2BdpRFzAjLmViCCxykLhWMv0rwAKxw0W6WxfFQlwQ0rkuBtS%2Bl5VWW7W5e1QV/VEVdcmqYOay11rbUctqys%2BrfO3XNd2ak71xhRs2FlVNwp/WwacE1LtWN1gE2OIm1gdvZ2Gg5uzHke7harvParethoi3q17ae6tw7DQLunZm%2Bvx7M/V%2BzFbZPgdcwV/jtWOsadB6v2CcXd9uXhwFeM%2BZ6rkHu61MHohyhk9mAz0jAzUl%2BHIAZg1G/g/g1isSkGOSIBPoyS4uwmeOpS5SkOV6PokyyOXAUgcSSOd6XAPoX6/gn2EueOhOs6UysBuOH%2BVSKwGqmQzgkgQAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/typelivore/conjure_set.hpp)
- [unit test](../../../../tests/unit/metafunctions/typelivore/typical_conjure_set.test.hpp)
