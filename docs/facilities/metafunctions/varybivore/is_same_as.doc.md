<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::IsSameAs`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-is-same-as">To Index</a></p>

## Description

`Varybivore::IsSameAs` accepts a variable and returns a function.
When invoked by an argument, the function returns true if the argument is the same as the variable and returns false if otherwise.

<pre><code>   Target
-> Variable
-> Variable `same as` Target ?
   true : false</code></pre>

## Type Signature

```Haskell
IsSameAs
 :: auto...
 -> auto...
 -> auto
```

## Structure

```C++
template<auto>
struct IsSameAs
{
    template<auto>
    alias Page
    {
        static constexpr bool value
        {RESULT};
    };

    template<auto>
    static constexpr bool Page_v 
    {RESULT};
};
```

## Examples

```C++
/**** Metafunction ****/
template<auto...Args>
using Metafunction = IsSameAs<1>
::Page<Args...>;

/**** Tests ****/
static_assert(!Metafunction<1.0>::value);
static_assert(Metafunction<1>::value);
```

## Implementation

We will use partial template specialization to detect if the two arguments are identical.

If two arguments are identical, the compiler will select the partial specialization instead of the primary template.

```C++
template<auto Target>
struct IsSameAs
{
    template<auto Variable>
    struct ProtoPage
    { static constexpr bool value {false}; };

    // This partial specialization will be chosen
    // if `Variable` is deduced as `Target`.
    template<>
    struct ProtoPage<Target>
    { static constexpr bool value {true}; };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Args>
    static constexpr auto Page_v 
    {ProtoPage<Args...>::value};
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwAnKSuADJ4DJgAcj4ARpjEAQDspAAOqAqETgwe3r4BwemZjgLhkTEs8Yn%2BKXaYDtlCBEzEBLk%2BfkG2mPYlDE0tBGXRcQnJts2t7fldCpNDESOVYzUAlLaoXsTI7BwA9ABUR8cnp2fHeyYaAIKHxwDUAJIsqfRsgkx99yeXN3fnAPOv2uV2uBEwLwM4JM/jcTC8RHuABUWsBMAQYdhQXNiF4HE8FEJWJhrgpQSYklYbvcafdwZDPpgYXCEah7gA1Fp4JixeiY0G0%2B44vEEe7KYioIjKJhogW0ikWIXNRzIe5oBhzTCqVLEe6xVCee4ANzEXkw9wVVDESgpABEYYq7Q7ydTaXs9siEHgFPdUoNubQhal6gG8AAvT7Ze4AdzogfiaoQGUYcpp7vueCoFoAbBpOcRubymbmMz6sOg8Zh0PcmD6TLmUcQ0RjcwA6VN0iGvRnM/mumnC/HiyWoaWy2GN5t966ChVKyOq9Wa7W6/WGk3ec0Kgi4plJe3%2BR37503Dv07vQ2Hwoit2/XYDETAQxgEMn%2BLH9%2B5eTJGMUyrf%2BLaYoSlK/7Mvej7PoICi3u274niCn7nlCTJXqysHXE2b4fjOtJzAuaoCMuOo1qyf5ogA%2BkaFqfgqw6geObiYcAMG3piIAgBuZpOoe5LHrxp5/ICALAv8Bz3NgqisK85o/KCYnCRcLq3Cc9wALLokwVBeAwDQCN8Sk3MhPZoTed5YdO34RMA6madpulfDCQGPISxKksyXDThxY6oUxWGwfyAmISpDxIpgcw%2BnJNz4SqFG1korQQGAYAac09l6QwHmtho7GcaamCrAhMV4MgcUKAlBAQKlWk6RlHm5VxBUOhw6y0JwACsvB%2BBwWikKgnBuNY1hCps2xbmY/g8KQBCaC16wANYgO1kjZQAHGYZiBIEXDtRoq2rVwSRJNIbUcJIvAsBIGgaKQ3W9f1HC8AoIA3TNPUtaQcCwDAiAgJsBCpAi5CUGgLx0AkUTEpwqirdmAC02aSPcwDIKqUitmYvBVoQJB4Ogej8IIIhiOwUgyIIigqOo72kLoXCkNGxBMKknA8K1HVdbNfWcAA8gigOiqgWYw/DiPI6j9zo2Y9wQB4YP0Lq5iTasvBvVo6wQEgoOpODZAUBA2u6yAwBSGYfB0OCxDPRAsRc7EEQtAAnqzvD28wxCOzzsTaPUb1TaD7wEDzDC0M7NNYLEXjAHCtC0M93C8FgLCGMA4jh3gj4NEa4Vc1q9QIrsU0ROCp29bQeCxEzHseFgXM7ngl0J6Q2fEPqSi2hCKfl0Ys3rFQBgseyeCYNGPPBt1U2E8IojiGTU%2BU2oXN0/oKcoENlj6BXz2QOsqCpH08dw3M6BOaYljWGY90twWWDbxA6x1BlLgMO4ngdHoYSLBUVR6EUWQCNMPw9M/59GGN/MY9NH59AGFMN%2B%2BRIE9F9o0eYYDRiJEgfMQBeh8KtFQcsdBD9Ro7AkOzDgnVbpcwevcEWCMkYozRitaWEBcA40VhNLgKtpq93WAgTATAsCJHvqQRakh/CtkCDUSQGhJBmEkLmDQ7VszBFOudUgl1JqtmzFwbMq1AgHWzMtHaEjswUJpg9J6L0uHvQ1j9TWf1%2BZA31obBWkM2CcBaCwI0SQ4ZMDVAYX8XBAiti4NlLG%2BAiA3wJrIYms9pDzyUIvGmugzaM2Zi7Uh5C7q8AenzAGCJ7hC2obDWhfiU6SyCSEjQMs5Y6wVhaCaZhOFqw%2BnY5xCRgYG1QPLMYyB/Em22jdGgtBLbW1tjTN2TsXakAmR7L2PsHBTIDi%2BYOocuYRyjjHOOUyk5d12L1fAmdHDZ3jr1POyAC5TOLj0Lm5dK5Oxrns1WBZG5TRbm3TAHdk5GG7qAaxfAB4KCHiPMejAplTxiaTOJsgF7U16sklePcz5WA3rcu%2Bu997ZEPsfU%2B68LCX2ydfPGOcd7dF6NkZ%2Br88hAJCC/PBP9gEZH/jkOB1KQHZDpRA0lSCBAwLaCy7BiCMq8o5egiYgwsEYMGCKkhGwtjEI4foDmpj7qcCKaLJGvSymBOCdlGWLCIn1OVqrbhpBeH8LGEIlRF0CjZUkEkdqgQjr%2BBkXIyQ9Msnc0erYSxzSbHwDsf9AWHS2nEFcbsDxYsWAKCNKqI02qUJzDCawvGUSiYz0heTeQCTYU6ACAzJmLME4ZM5mY3mDjBbC0jdG2N8bGRzGqV02pCRDX%2BCab3T6WtG262DV2hWnFkCpFSFRQJFEE0EAoqoRG5thkJFGXbB2HspkzM9t7X2iyumBxWWHfZmBI7RzEFspuOzvmPNIAcpBxzc6qHzuCS5ghrk01uVXR2Dy67PKmW85Mnyu7WXbf3GUgLh6j3HmC6J6aJBQoptmpeea%2Blr3Piire8B0UH04HsY%2B8HkV4qvgkG%2BxKhFQPJRAVwEqaXoGlQy4o2RSNstKF/NBAqyU8swfyhBTH%2BgoPo/g7BLGqU8alVx%2BlhC5Wk2Lcq7JqrJ1IyjTG40tbwT1uYeEkghqOHGusTwvhAjKCkNUZdTarZ/D%2BHartN110jNJB0eJz1FjXompEe1cRh0kjXVWpIbaXB1pmBMadfwJaVVet9aQzG1nzFWPVusFumRnCSCAA)$Done$

## Links

- [source code](../../../../conceptrodon/varybivore/is_same_as.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/is_same_as.test.hpp)
