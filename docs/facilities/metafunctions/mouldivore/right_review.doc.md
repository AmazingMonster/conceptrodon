<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::RightReview`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-right-review">To Index</a></p>

## Description

`Mouldivore::RightReview` accepts a predicate and returns a function. When invoked, the function returns true if the predicate evaluates to true for every relative-order-reversing pair of its arguments and returns false if otherwise.

<pre><code>   Pred
-> Arg<sub>0</sub>, Arg<sub>1</sub>, Arg<sub>2</sub>, ..., Arg<sub>i</sub>, Arg<sub>i+1</sub>, ..., Arg<sub>n-1</sub>, Arg<sub>n</sub>
->   Pred&lt;Arg<sub>1</sub>, Arg<sub>0</sub>&gt;::value && Pred&lt;Arg<sub>2</sub>, Arg<sub>0</sub>&gt;::value && ... && Pred&lt;Arg<sub>i</sub>, Arg<sub>0</sub>&gt;::value && Pred&lt;Arg<sub>i+1</sub>, Arg<sub>0</sub>&gt;::value && ... && Pred&lt;Arg<sub>n-1</sub>, Arg<sub>0</sub>&gt;::value && Pred&lt;Arg<sub>n</sub>, Arg<sub>0</sub>&gt;::value
  && Pred&lt;Arg<sub>2</sub>, Arg<sub>1</sub>&gt;::value && ... && Pred&lt;Arg<sub>i</sub>, Arg<sub>1</sub>&gt;::value && Pred&lt;Arg<sub>i+1</sub>, Arg<sub>1</sub>&gt;::value && ... && Pred&lt;Arg<sub>n-1</sub>, Arg<sub>1</sub>&gt;::value && Pred&lt;Arg<sub>n</sub>, Arg<sub>1</sub>&gt;::value
              &vellip;
  && Pred&lt;Arg<sub>i+1</sub>, Arg<sub>i</sub>&gt;::value && ... && Pred&lt;Arg<sub>n-1</sub>, Arg<sub>i</sub>&gt;::value && Pred&lt;Arg<sub>n</sub>, Arg<sub>i</sub>&gt;::value
              &vellip;
  && Pred&lt;Arg<sub>n</sub>, Arg<sub>n-1</sub>&gt;::value</code></pre>

## Type Signature

```Haskell
RightReview
 :: template<typename...> class...
 -> typename...
 -> auto
```

## Structure

```C++
template<template<typename...> class>
struct RightReview
{
    template<typename...>
    alias Mold
    {
        static constexpr bool value
        {RESULT};
    };
};
```

## Example

- We will check if every relative-order-reversing pair of `Vay<0>, Vay<1>, Vay<2>, Vay<2>` satisfies `IsNoLess`.

```C++
/**** Vay ****/
template<auto I>
struct Vay
{ static constexpr auto value {I}; };

/**** IsNoeLess ****/
template<typename L, typename R>
struct IsNoLess
{
    static constexpr bool value
    { L::value >= R::value };

};

/**** Test ****/
static_assert
(
    RightReview<IsNoLess>
    ::Mold<Vay<0>, Vay<1>, Vay<2>, Vay<2>>
    ::value
);
```

- Note that the order matters when the predicate is not commutative.

```C++
/**** Test ****/
// Reverse Vay<0> and Vay<1>
static_assert
(
    ! RightReview<IsNoLess>
    ::Mold<Vay<1>, Vay<0>, Vay<2>, Vay<2>>
    ::value
);
```

## Implementation

For every element in the list, we will check if it satisfies the predicate if paired with every element behind it.
We will implement this process in two steps.

- First, when given an index, we query the predicate with the pairs consisting of the element at the index and every element behind it.

We will expand the concept `Prefix<***>` alongside the arguments to pick out the element at the index.

```C++
template<typename, auto>
concept Prefix = true;
```

`RightInspect` will help us translate `std::index_sequence` into a pack of indices.

```C++
template<typename>
struct RightInspect {};

template<size_t...I>
struct RightInspect<std::index_sequence<I...>> 
{
    template
    <
        template<typename...> class Predicate,
        typename Inspector,
        typename...RestElements
    >
    static consteval auto idyl
    (
        Prefix<I> auto...,
        Inspector,
        RestElements...
    )
    -> std::bool_constant
    <(...&&
        Predicate
        <
            typename RestElements::type,
            typename Inspector::type
        >
        ::value
    )>;
};
```

- Second, we perform the first step with every index and combine the results.

```C++
// Immediately invoked lambda.
[]<size_t...I>(std::index_sequence<I...>)
{
    return
    (...&&(
        decltype
        (
            RightInspect<std::make_index_sequence<I>>
            ::template idyl<Predicate>(std::type_identity<Elements>{}...)
        )::value
    ));
}(std::make_index_sequence<sizeof...(Elements) - 1>{})
```

Here is the entire implementation:

```C++
template<template<typename...> class Predicate>
struct RightReview
{
    template<typename...Elements>
    struct ProtoMold
    {
        static constexpr bool value
        {
            []<size_t...I>(std::index_sequence<I...>)
            {
                return
                (...&&(
                    decltype
                    (
                        RightInspect<std::make_index_sequence<I>>
                        ::template idyl<Predicate>(std::type_identity<Elements>{}...)
                    )::value
                ));
            }(std::make_index_sequence<sizeof...(Elements) - 1>{})
        }; 
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxBJcZqQADqgKhE4MHt6%2BASlpGQKh4VEssfFcibaY9o4CQgRMxATZPn6BdpgOmQ1NBMWRMXEJSQqNza25HeP9YYNlw5VmAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimMmujMh4mAq3R%2BdXN6f/xx%2BlwuwLM/jCyG8WFuJn8bi8jlohAAnrDsCDzOCGJCvNDYW5kGN0FgqGiMb8jrdlMRMDRVF9DkCCJgWMkDMz8QRkc9mGxSLcmAjUGSrmhsU8CFSaXSYf57rcCMQvJhYVYriC/gCtQcgZrbgBJVn0NiCJh1BgMnUa7U2s7k66UgBKeGACAI%2BoYCmeDktdquzKNZpVcK5PNYwfRVzGSp9ztd7s93slJgA7FYU/dVfaA2yg/j0gAvTAAfQIADoK/qRZdo15Yy63R6vV0CPmCOgQCAwlhVMWlABHZXi/H6itlsn%2BbAw9VpkG3ecKlm5jlXBeytxztcLnPs4NuUOMcNjtG3SFMBSfamYfCiZmkTdbhXcw9sA2Jlske%2Brx9PsNsMeOh8BDYMajAEAoD6ypGlxrmMZp4Mgp4CGMmAAG5iAKQq3Hg6DIrQkEQJBa5XnSI4noKRBjl%2BME/k2SafkRC6AWMIEsmBCjHt%2B87LJBAC0J5Ep20SoJ4xZinBgiQfiEDHmYABs5gKVxW5XjeebKWu%2BKMY%2BB68pgtzMcBoGCAonYHtRP5brp4Zvs2DgkGZz7aVBzmduh3gqspPGTlmM6Zv4arAhSdxxm6gGoe8ADuvpMkuu6cnFeYhs%2BenHpOp4GBeUrXghSXQbW9bxuFUUYrOyk7kl%2B4pUeFasSa4HVrBip1pK1KoEQACynjoFJZU0Y%2BcGOIh4nMqoyTELcwmeLc7nKs5qaBZZmkAKxWMt/luIWJblpWaIQIJXYMD2faYIOrx7qOFZojxGk/gtzmWTSBAbAwD0/jJV3yYphG3UtW5YJCB5vX9P39X94OhQmdmtnCB0sEwADWJbdpgvYDkOWxkT5Pm/eDj5mYlzLYbh%2BFwqpuUcpO%2B3to5zzFjhYEovidXsWSs4ZmON1g3ja7LG5YhzbjlnLN5i3g6m9zUx2IDw0j9NHajJ1ncOsN4EWqBUGOEAsyZyy3LxtxcGz6b3FzlkS6q05gxbAX2muFWU1Vf6YGOOsNTjYNeOkRi3F1tDoLK8ptZ13XM8Z4Fpeitt%2Bb5QUOraAK6pSABieDEGMtzYKorBsvp3zWgn/xAhiYIQlC%2Bmcs%2BpbEEwhAQR7BcHLcABqTDIjFIIO3uFGoAa1YFZKreojOFi3INCFIZ6o3jZhRAzQLFdplWGaWzbgWN3sBoKBEqCYMEHyfPn/qE3u1mvsE/Jn/pjr981Pr6tvqD7xepVi/O4/Dch08TVNtDzx5vVR7BH5h5FycoDIgOVDCFe0c45r3tHqAAKkBDuUZGhDWLOeJQzQQSgzXJDYqmBIojkfs/eu0E1ydj9j1OEQ98QaDRPyOhcIjaTiYW3fEZhGEtw4XCLh2MKELkgZ5S4osEGF0ThvW4QgugCADlnHO9BUHxwkScYuwUm7IIzkfa4OwDJoTiEoHhqI4QMPSoYAOzC3CsPyughCmCLxxFbFcPBC4wBgAMg2AghDiFwgfjvMhjUhEgGofiKxNj2EmLcGY7AkTOHcKsfwqOgj5zCJBKLDgqxaCcGWrwPwHAtCkFQJwDclhrBj3WJsCuYIeCkAIJoTJqwEYgGWpIMsGgAAcZgzAAE4elcGWp0jpXAUwpmkNkjgkheAsAkBoDQpB8mFOKRwXgpl5n1IKZk0gcBYAwEQCAdYBBkgInIJQNArI6BxAiOGTgqgOlyV4nJSQtxgDIEQlIMsZheA5SIMQHCeh%2BCCBEGIdgUgZCCEUCodQmzSC6C4KQSKNdkicB4FknJeSGlFM4AAeQRMcyUGtbh3IeU8l5bzDZtLMLcCAHgLn0AmpiLgyxeAbK0KsCASBznJEuWQCgEAuU8pAMAKQSQaC0GZOnSg0RMXRDCE0ZEKLeCyuYMQZE2LojaBbIq0g5z6rYoYLQBVMKsDRC8MANwYhaCmW4LwLA8MjDiGNWnFseBUIfExajLoCJti1LCMyCZhSkTRBrqqjwWBMWKjwDMm1pA3XEGEkoR49rgBIiMA01YVADDAAUM3KK2KeTasBcIUQ4gwVFshWoTFcL9CGGMNYaw%2Bg8DRFMpAVYqBkjmmtbxIksJ7imDKZYMwSy41/KwC2iAqxOjdGcBAVwkw/DwpCHMUo5Q9CpHSOaeda6CjmgGCuxY1Rag9BmFu%2BFU7zS9GaHuoYFRbAns8G0PQcEr3LpvRISdlStjvv0OihZmLllEvuY855rz3mUupbgQgJAYQ1OZXU9NqwECYCYFgeIE7SDNMkP4MsPT/BjI0JIMwkg5JzOWnJHpP7JnTICFwMsckuByQ6T04ZclWkDNw3JP9MLlmrJAOs9N2y9kcoOXik5fKBX0uuWwTgTQWCoRTLxJgGVa2Gx6WWWjhSfkkH%2BfCotwLS3SHLUoStMLdBJERUwZFNq0UcFyVxpZOLRMEqoIBklzyzw%2By4GpjT1LaXcvpTB/wKwWUCeExJuIpz%2BWoDpcMDzwr%2BnzLFRK0yEBpUwuVfK7VGXVXqs1Q4bVuqwL6sNZik1ZqLW0Ctdqu1tbHWFPwDSbobrrWadUF65k2q/U1ExUGkNyIw3bEKZG6NtS40JswEm2rYRQCbIzVmnNeaC0xr0yW0FhnZAVuhYUszNa039qsJYRtzb4Bto7ZkLtPa5T7esEO3gqAR0M3HZOmoLqZ1zofbkRdR1r0LFveuwoWQPsLvyBuzIP3V1npe9Ohgl6WhA6fVDi9MxwcHufXDnIwO0co4qB%2BjYX6mWUbs4su7nBXPAeU557z7SIP4F%2BYFplIXZuIeQ6hygNmpmkBmf4NTBGUzLR6aM/whHiOSHhcTrFKzbB8fg7NwT8BhOHPxZF8LxApPbFk6SlgChUKIVQl5ssu4xjfNp9pjsunZD6bW%2BC%2BQxmts6DyBZqzqLCcYu445o5CJbiEtUJr7Xuv9eG8lDS6L/m4iBf8HB1lWywsh55cr2P9KQA6%2BSMkYseuenFkD8WH3hm6DJalTKuVqqstF7VRqrVMbCuCGK0a%2BrmBTXmstda2pNWHWDdtc6pr7qYWeuQN6zrghuswt6/KgbEa/kjd4GNtIE2WRTbTbLzNTBs25qIfmxghaLerYkOtiFtuq15AMHt%2Bth2g1PaKWd5CnAdiCWu4O4dcRR3utbYe17fhZ1HVPUEb7r7fvbtBwIF/v9rur/hDq/tDrDl/uesen0Njk%2BvehjvAbAaAYsLjlUt%2BhMkTv%2BqTjnrcFrjrjNAHkGBnNrCbgyrBozmyszihsMOhhMhzjMr0mWP4P4MtIMqLnMiwSmIxvZiTpLmsjLlQRhiAJIMtDhiMimHMh0pIP0lwF0vJJRv4K7g5pLlHiLJRl8rwRLpQY0rGoYpkCIUAA)

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/right_review/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/mouldivore/right_review.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/right_review.test.hpp)
