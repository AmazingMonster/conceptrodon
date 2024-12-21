<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Upend`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-upend">To Index</a></p>

## Description

`Typelivore::Upend` accepts a list of elements and returns a function.
When invoked by an operation, the function instantiates the operation with the previously provided elements but in reversed order.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>n</sub>
-> Oper
-> Oper&lt;E<sub>n</sub>, E<sub>n-1</sub>, ..., E<sub>0</sub>&gt;</code></pre>

## Type Signature

```Haskell
Upend
 :: typename...
 -> template<template<typename...> class...>
```

## Structure

```C++
template<typename...>
struct Upend
{
    template<template<typename...> class>
    alias Road = RESULT;
};
```

## Examples

We will flip `int, int*, int**, int**` and invoke `Operation` with the result.

```C++
template<typename...>
struct Operation;

using SupposedResult = Operation<int**, int**, int*, int>;

using Result = Upend<int, int*, int**, int**>
::Road<Operation>;

static_assert(std::same_as<SupposedResult, Result>);
```

## Implementation

The implementation is similar to `Typelivore::Amid`.
We will label each element by its index in the list and collect them into a roster.
When provided with an index, we instruct compilers to pull its corresponding element from the roster.

First, we need to create a label class:

```C++
template<typename Treasure, typename Key>
struct Label
{ 
    static constexpr auto idyl(Key) -> Treasure;
};
```

We can pull out the variable of a given index by asking `decltype` the return type of `idyl` if invoked by the corresponding `Key`.
For this purpose, we will convert an index into a type via `std::integral_constant`.
So, the final mapping will be as follows:

<pre><code>std::integral_constant&lt;I&gt; -> E<sub>I</sub></code></pre>

Now, we will assemble an overload set and instruct compilers to pull the elements out in reversed order. Here's the entire implementation:

```C++
template<typename...Elements>
struct Upend
{
    template<template<typename...> class, typename>
    struct Detail {};

    template<template<typename...> class Operation, size_t...I>
    struct Detail<Operation, std::index_sequence<I...>>
    // We create an overload set of `idyl` through inheritance.
    : public Label<Elements, std::integral_constant<size_t, I>>...
    {
        using Label<Elements, std::integral_constant<size_t, I>>::idyl...;
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
            )...
        >;
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements..., std::make_index_sequence<sizeof...(Elements)>>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEAf6kAA6oCoRODB7evgHBaRmOAuGRMSzxif7JdpgOWUIETMQEOT5%2BQbaY9sUMjc0EpdFxCUm2TS1teZ0KE4MRwxWj1QCUtqhexMjsHOaBEcjeWADUJoFuXo60hACeZ9gmGgCCewdHmKfnyLPoWFT3jxezwImBYKQMILObgINxSjFYHwAKsRMEwFJtMKRjjC4cw2McANKYO6BB7PWbELwOY6hJjxWiAkwAdgsp2exw5x1mTEcyGOaAYs0wqhSxGOTEuqGOeHQN1oECJNxWxwAtPdjsjUeiUWcrM9mQARXWM4Gg8E8zBQnHwtgAOnt2HobEECgB5IIlOpclx6EZLMBnOxZohlvOILBIatsJtmHttvVhzRCix1rxobJT0DFKpBGOBswTTop39TKNgT1QMznPD5shYeDFqjuIRcYTBgUCmOAHk4cQeVksRkAF6YAD6BDjAEk3VWOdnqfnCwzzj2Ev2BIOCOgQCAIlhVKOlABHLyMbZQyet0kzwMAelvxwA6h9kCiLeKGMdUAA3BK0VBMOgXIFl%2BVCnAAbBoMpyiYkHYggxAbMACDSgwCAJIQhjbPG7KciAxwpF4sTXHytL0lCjqgowBDJlyW47hEILAH2tCjgK3KCFCw5jgQWLTtepKtrhHLMhWgaBl4GRGDSdLdBRTrUbRPwMYImDMWIbECBxBBcXgI7jnxAKkgxsq0FeYniRykkRMA2LRp8Brdr264MFCAaWeJ97HFEqAgvBPIQRo3GoFQcYQJOKywRo0qdgQ6HYr5YjHAwIxiiFxyXvapDuR5nJeQA7ggeDICheCdkw/JaU0gg4bOuXHF5z7iiixzoKgNkEUwyAANbHMKKSGBkAhfr%2BYpxR8SgCkBl45fVXmIvFKLorQuZleKxzXLMoHHPwxAsCAs25V5wWhfa4XKiqxxcIOemYCFYURaqxxmFicZYhotpsnVuVYIc1oQId9UctB8qA0DWb0buqnqax7HVTpwng5Zun6bxXK3fdZ2PZdk5PVwAIlkaiNI5FxMeSsQnfZyRkWSJpbGvqiM1pG9YRo2YbRmmV7YPy7YKHGTzMZgVEujenLWdJABKAFAWcjmLkwdBQoLKIizRb10duIAsEw3VjnuwqHpgJ5nqGbgnWFlHOjRkUCdgO7WgzLz0%2BWJpPLeABUXvez7t6Ap7XuItgQiIt7fvPAHPu%2B27rwMIcXgnFCArbCkNEzoCzPs9CnMtvaM7zrmq59r0TuAhLtlCF4KSFJg6CS5gy25nLTlriX5yMV7WIdx7XeCD3qE6QJFZl1Jtn143DnHN6rhQoxvcEP33fz17M47tLgFQkXLk0273K8qOSYJAQEDKSACgIgfrrnJX1fpLX49eCtWIPyt9y2xWHBrLQnD%2BLwfgcFoUgqBOBuGsNYLkGwtgfD2DwUgBBNCfzWN1AIkhbQaEkFwJkgQND%2BA0GYcC4EzAAA4iH6E4JIXg%2B0uAaA0KQf%2BgDgEcF4AoEAtD4EAM/qQOAsAYCIBABsAghFeIUAgGgMEdAEhRARJwVQRDwIqnApIY4wBkB8ikLaMwvBa6EBIDKPQ/BBAiDEOwKQMhBCKBUOoDhpBdDXXyn2FInAeBfx/n/BBQDOBdkuEI7asj5GKOUaoq6qCzDHAgB4cR9AxQwJWLwdhWg1gQCQGIlIEiyAiJSWkkAwApAvRoCtBILCICxHcbECIzQbhON4GU5gxAbhdliNoOo7DYFiOtl2BgtBKnWKwLELwwA3BiFoCw7gvAsA6yMOIHpeAUT1F/CMwBwo6iXB2LAxi3R3HXFiH2OpHgsDuI9HgfaozSCjViHffMEzgDXCMAgtYVADDAAUAANTwJgfKq5/6wIMcIUQ4hTE/IsWodxtj9CGGMGAyw%2Bg8CxBYZANYqBU5ZBGSqH4ctTCWGsGYBho1iAygbvANYtR6jOAgK4KYfhrphAWOUSoehCiZAEBS%2Bl6RGUMCGLS0Y11iW9H6JMTw7Q9A8oaHMDlqUhVzGZdy0VNLxVcCJZA7YEgXEcF/nQ9xjDjh%2BIUUolRaiQlhNwDo6JZhAjyriXctY6FAKjAgEgkAkhAi2gAJyBCZJIdBZhJCQRweBZ1ZCOAUNIPtM1tpwJcHAkQ51RCI3%2BAwf4V14F1XWMYcw1hcC7lcN4Uk/h3jLjkEoJkqJUi2CcGaCwb8TIVQVUTNJLgzrbRcDQVo/ARA8Xbmuj8ox/zpCAqUMC6xugXr2KYI40ZKq1X0N4IwrxgjLjbXLZW6tvNwVXQbU26K4TUCRISKcU1ZhYkZo4Yk5J27UlRILaIs9WTF1VtrTk511C%2BB0BBMQIpJTrE1IqVU0gX66kNKaQ4H9bTqIdK6e43p/TBm0GGT%2B8Z4KpmAPwLMxw8z3FLOQCsn96zv7WK2Tsm4eydiAMOcc2BZyLmggQzZTNDymBPNee8z5P6u1/JMb22QQKrGAKHWC25GKrBQq2XCu1QCkVaU4Kirc6LIUWGxdO3F%2BKRNEu6M0rILgGDuAFXkKlmmxVLESNdBlvQpWpFZb0fTdLuWqZJX0SV2nKVdB6CKgYlmuXjAGKZ7kLQ3OGYVZsJV8qA2To1ZwZqFaq01oMHW9daDDWtpIHus1h74mININarAiRRO4aDSGht6CmQJqZFgyQXrFHXSnR4phth02pcSdmpAAihGXqLZI6RHBy0BJYAob8fJvz1ttCGWYLbjV6M7bIbt7GzHyH7dxnQIBggjrHc44LbiU2eLzbmdKnWlHdd68cfrDahu5i3Tuk1gRAgpczTm1r6TC3XqiSAXr1dRyHdHMdg%2Be1FHPoKW%2BygH7AF/u6bAoHAHmnAe3e0zp3SkOYD6QMoZIzYHwcmcRsZMy1NoesRhrDJycObJhQRojBy8Vkd4BRpQlzqO3OPXwR5Ly3kfNxCxibbGJAcfMbNkFC2%2BMQsxUJmFymxO9BGbeZSAmsU4oSO2gl8KnNqdJeShzehqVlDlWZooWRTPGayL5oVNneX2dyI54VAg%2BXzDVwZiVnnlfStc7Kq3QWFCKpMROtbDCws7eOHtvrA3jvxeNUl81R6ElWtRJlygKrcsgDMA2i71R0HUI0Bdpkkbk0e%2BqywthlrSDIMkP4F1/giH4OdZIZ1WC3VcGCLhwI7vp2cAtcelVmj0/1%2Bq3VtYo0hp%2BEkEAA)

## Links

- [source code](../../../../conceptrodon/descend/typelivore/upend.hpp)
- [unit test](../../../../tests/unit/metafunctions/typelivore/upend.test.hpp)
