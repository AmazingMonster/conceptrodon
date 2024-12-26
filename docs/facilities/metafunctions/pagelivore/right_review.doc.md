<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::RightReview`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-right-review">To Index</a></p>

## Description

`Pagelivore::RightReview` accepts a predicate and returns a function. When invoked, the function returns true if the predicate evaluates to true for every relative-order-reversing pair of its arguments and returns false if otherwise.

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
 :: template<auto...> class...
 -> auto...
 -> auto
```

## Structure

```C++
template<template<auto...> class>
struct RightReview
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

- We will check if every relative-order-reversing pair of `0, 1, 2, 2` satisfies `IsNoLess`.

```C++
/**** IsNoLess ****/
template<auto L, auto R>
struct IsNoLess
{
    static constexpr bool value
    { L >= R };
};

/**** Test ****/
static_assert(RightReview<IsNoLess>::Page<0, 1, 2, 2>::value);
```

- Note that the order matters when the predicate is not commutative.

```C++
// Reverse 0 and 1
static_assert(! RightReview<IsNoLess>::Page<1, 0, 2, 2>::value);
```

## Implementation

For every variable in the list, we will check if it satisfies the predicate if paired with every variable behind it.
We will implement this process in two steps.

First, when given an index, we query the predicate with the pairs consisting of the variable at the index and every variable behind it.

```C++
template<typename, auto>
concept Prefix = true;

template<typename>
struct RightInspect {};

template<size_t...I>
struct RightInspect<std::index_sequence<I...>> 
{
    template<template<auto...> class Predicate, Prefix<I>..., typename OnDuty, typename...RestVariables>
    static consteval auto idyl()
    // We combine the results using a fold expression over `&&`.
    // The pack we are folding is `RestVariables...`.
    -> std::bool_constant<(...&&Predicate<RestVariables::value, OnDuty::value>::value)>;
};
```

Second, we perform the first step with every index and combine the results.

We will transform variables into types so that we can use them as parameter types in the declaration of `idyl`.

```C++
template<auto Variable>
struct Vay
{ static constexpr auto value {Variable}; };
```

```C++
// Immediately invoked lambda.
[]<size_t...I>(std::index_sequence<I...>)
{
    return
    (...&&(
        decltype
        (
            RightInspect<std::make_index_sequence<I>>
            // Note that each variable is kept inside `Vay`.
            ::template idyl<Predicate, Vay<Variables>...>()
        )::value
    ));
}(std::make_index_sequence<sizeof...(Variables) - 1>{})
```

Here is the entire implementation:

```C++
template<template<auto...> class Predicate>
struct RightReview
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
                        RightInspect<std::make_index_sequence<I>>
                        ::template idyl<Predicate, Vay<Variables>...>()
                    )::value
                ));
            }(std::make_index_sequence<sizeof...(Variables) - 1>{})
        }; 
    };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGwArKSuADJ4DJgAcj4ARpjEIAAcZqQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCcmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimGmujMh4mAq3R%2BdXN6f/xx%2BlwuwLMAGYIshvFhbiYwW4vI5aIQAJ5w7Ag8wQhhQrwwuFuZATdBYKjozG/I63ZTETA0VRfQ5AgiYFhpAwsgkEFHPZhsUi3JiI1Dkq5oHFPAjU2n02Fg%2B63AjELyYOFWK4gv57W4ANSYKMZB2ZrPZTE58KFRF1rTwTFi9FFlwmyoc1rRGoA7BZbnNHMhbuKJphVGliILhbcAG5iFWwr164i2%2B2qj33NVxtNg9XAykAvPfTVUgCSbPobEEZpyhrOhfzdaBtYOtwASnhgAgCEWGApnq6C1cWaWzar4dzeawRxirs6vK7W%2B3O93e1KTF7V5nsyDB6bzW4sgAvTAAfQIADpz0XHTO522O12e5gHATiSAQBEsKoj0oAI4qiUEotz1PckwWwWFPWzW4oMVE0ORHNxtzgglLVQID0QDAwFE%2BGlMHwUQWQFHD6QA9EgIFMdGAnW4AHkGHuREUXInlKLYIDmw%2BAgEyTegFEdaCfRaP0AwEINo1ocMrTwdAUVoCBlhBfidh2W4AHVMGEqoInUggEHU2kFC8WgCE%2BLwsiMQVbn4Wh0FuYNQw%2BLIBFuVBIwSWF/A0cx/C8kwPOAq5FOUgAVXTbjSJhkAAa1uAB3dTWnUqz8HMvBPl8jR2ImLi7R4tC/IU6CAFp0JfEBYlQTwj0DFpBAJCA0LMbzGpwvDhwJTLOJtHKPlfMSVQFWj6O5XqY0nEbvEweTQLVTFUxmjVcybecO3YyN3hi6tjSHXdELai1hTQ0CMKYLDpVwvB8MnEFrylZaCFW9bZsg6Ddt3FCgOy5NeOmgLoJu6VUCIZQmGAVVfqg1dnv4qDfQu4TuxZEMw3Kzwo1GgrobjKHMegkxAisQJMz3PBDxPIDL1AiBSvfYMv0wX9XngwDz3ReTwZxiG13Zjn%2BNpAgNgYDGef4%2BqWcaryICF4XMawKEKKl6WRYVxXMbu%2B9l2fAh0FfFgmEi48ac/H8/y2Ejpp%2By4Vel19XvUqSZIJFqLuHAU9TReFPp40iWcptnLat6HlnGlVlZ55Ypuxjn1yprWdb1g2GA/OmGf/eED0wVAqCAiBPY%2BZZbkK24uHJNdUz9qO5qzcD/c5jcKRrmDtvg97z1z76pwb0yImAakQfUuEFRpQHUGB0GCTbw6MSzWa64W6463zIEtVuAAxPBiAmW5sFUVh2XU/t54XgEG0W7UiwUKJUFCBzNq3WC9rcFDblCAUn%2BbK8lVnKVz8v6%2BsKeoWsN/TVTssjCq4k%2BpgwbpDZ%2Bcop4KmbBmeawJK6blPrcIKHFb7TkEhdI8J0lBtAgHdB6mAYoAQvlfBy6JXyj3ghoAUXABSpFuGYGhIBIER3rlqI%2BJwl5UiEI%2BAQNlt673oNgw%2BvDTgn2uMpVaCQlC3A0IKRORdrq4OQPgrCCQCAQDAGAFst57qYDWmQihv9qGgVoX3AkTClHMOYewzhaoOCrFoJwQIvA/AcC0KQVAnA3DWGsD6dYmx%2B7gh4KQAgmhXGrEiiAQIkhTwaBSGYAAnGkrggQUlJC4B6D00h3EcEkLwFgEgNAMO8b4/xHBeAKBAAw6JPjXGkDgLAGAiAQDrAIGkRE5BKBoDZHQBIUQJycFUEkfwhV/CSFuMAZA/opCnjMLwc6RBEzayYfwQQIgxDsCkDIQQigVDqGaaQXQTCYrECYGkTgPA3EeK8TEvxnBqKIl6VKTOtwJlTJmXMhZRcklmFuBADwQz6BhixFwZYvAmlaFWBAJAgy0jDLIBQCAyLUUgGAFIVINAjIKMoLEZ5sQIitBRHc3gpLmDEBRNRWI2hHxNMiYM8sBBaK0ApWcrAsQvDAEfrQWg9TuC8CwLrIw4huXryZXgVywrfHBkfIibYkSIgsiKb45EsRrm0o8FgZ5So8BlJFaQVyxBypKEeOK4AyIjAxNWFQAwwAFA6nWtRXklLDnCFEOIA52z5BKDUM8i5%2BhDDGCCZYfQeBYj1MgKsVAaRGjCsKsSAephLDWDMNUs1Gyepxp6DK5wEBXDTD8EwsIWlFijCYcUbIAhS16FrY0BYIxEhMLsIWpokx2ieE6HoDtDg%2BjdpbVUatthu0NvbcOytraJCrAUKErYc79CPNIFU3gNTvmTOmbM%2BZiygUgtwIQEgsIIkwqifa1YukmBYESHJUg8TJBglPGksEBSNCSDMJIDyGhAj%2BDSSu4ppSQBgi4KefwXB/BJDSbkoIkgsmvv8Gu55NS6kNIvc0hFHTEVdPeX09FmKIWjLYJwVoLBIwekKkwY65kuBpNPGBhV%2BB1lST0P63ZvrpD%2BuOUGs5uhUhXJuZSh5HBPHIbOTUt5PTETOSoFu35syoRhqLvRxjIKwUoohaesEZhz1wpaThwjCR%2BkYtQOC0YSmjB0a4Aw/FLIN5EpJWS2lnrqXkvpYyhwnrWWMHZQwTlzyeV8oFUKz1Yqw2St8fgWkg65XPMVcgZVnq1X1GeVqnVKI9XbF8Ya41kSzUWswFaiL3d7V8CdS6t1HqTXsZ9fsrjsgeOnN8fx0Ndr01WEjVq2N96E1Js4CmrWaaI0WCzRunNUk833oHY0FwidJ0hETiOpYNbMh1tyL2goq2Sg5GW2OmbQ6BgLYOwIfobQ9ttvHUdzbZarvnZnaOtt87F37JE2J9dLyODyZ3TRnudGGPJMPcxk9UK9OXtINe29lARMlNIGUsE9GP0ekCGk/JYJP3fvg%2BJ6pnA0ONLK20zp3SPkmaM8QYj2wyN/JYAoSM/pIz/bghMVZwONlsdkBx%2BrXqmvBpA6QQTtyRVvaeRJ15eHPlydUNT2n9PGfDk3qCszmm3JYjBGDzDrSkVK9RaT7XEKOHIDSGkI8DO0lHiZwQI8UuuN0Hs/UiAxKzluZcya53dKGVMu82ZtlHKuVRcwLy/lYhQsmvCxK7LorpWxZ6mchLSWTUpY1bwdL5KssGsTHl3gBXMhFdZCVu1GvHUg0q2Q91jBPW1b2RIBrRzA3NZ0Hzgw7WRtRpjfAeNiacjCp2C%2BDrmbs0JFzT1%2Bd9RO1zfcDdvQFaKizu2%2BthbTbdsPZWwWwdp2J2T/baPtfXb5jL/2xv/It25j3Zn495dC6NhLuhYB97KHODfOl3TqMcuWQK6Pes7T0LYXg8h6Me9RSsOZS6Sp4YIYIgQ2S8GFSYBHoUG2OG6uOtg6G%2Bm4cD6IAkggQL6eSHoFSSQkgmSXAqSSGRSYIIuOOtSGG8KImKy8Bn2P%2BmGqwZqjkfgkgQAA%3D%3D)$Done$

## Links

- [source code](../../../../conceptrodon/descend/pagelivore/right_review.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/right_review.test.hpp)
