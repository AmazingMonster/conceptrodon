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

First, when given an index, we query the predicate with the pairs consisting of the element at the index and every element behind it.

```C++
template<typename, size_t>
concept Prefix = true;

template<typename>
struct RightInspect {};

template<size_t...I>
struct RightInspect<std::index_sequence<I...>> 
{
    template<template<typename...> class Predicate, Prefix<I>..., typename OnDuty, typename...RestElements>
    static consteval auto idyl()
    // We combine the results using a fold expression over `&&`.
    // The pack we are folding is `RestElements...`.
    -> std::bool_constant<(...&&Predicate<RestElements, OnDuty>::value)>;
};
```

Second, we perform the first step with every index and combine the results.

```C++
// Immediately invoked lambda.
[]<size_t...I>(std::index_sequence<I...>)
{
    return
    (...&&(
        decltype
        (
            RightInspect<std::make_index_sequence<I>>
            ::template idyl<Predicate, Elements...>()
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
                        ::template idyl<Predicate, Elements...>()
                    )::value
                ));
            }(std::make_index_sequence<sizeof...(Elements) - 1>{})
        }; 
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxCAAnABspAAOqAqETgwe3r4BaRlZAqHhUSyx8cm2mPaOAkIETMQEuT5%2BgXaYDtmNzQSlkTFxiSkKTS1t%2BZ0TA2FDFSPJAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimKmujMh4mAq3R%2BdXN6f/xx%2BlwuwLM/jCyG8WFuJn8bi8jlohAAnrDsCDzOCGJCvNDYW5kON0FgqGiMb8jrdlMRMDRVF9DkCCJgWKkDMz8QRkc9mGxSLdMgAvTAAfQIZKuaGxTwIVJpdJh/nutwIxC8mFhViuIL%2BAL1ByButuAElWfQ2IImPUGAyDTr9Q6zuTrpSAEp4YAIAjGhgKZ4OW1Oq7Ms1WjVwrk81jh9FXcZqgPuz3e33%2B2UmADsVgz901zpDbLD%2BKFooIADoK8aJZd415Ex6vT6/d1xXCiSAQGEsKoRUoAI7q6X440Vstk/zYGHarMg25zlUswsciOL9nhtyRxjR0do26QpgKT7UzD4UTM/nHunDtGj/mb3mYW4AeQY9wRyLv3K3bFHro%2BBGwc1GAIBRq3nAUmkcZA9wEcZMAANzEW4mARVBbjwdBkVoCBllnecdh2W4AHVHzQCp5hVBBHxpBQvFoEDbi8TIjGQ25%2BFodBbkwVRUhozIBFuVB4LiGEkg0cwkgkkwxLHK5wII24ABUqNuVImGQABrW4AHdH2aR92PwFi8E%2BaSND/cZAJZYCFB3GS8LnABaXd2xAaJUE8EUpXGQxWzcCAdzMSSguPU8izhCyAKAwQFH5F83y5NEO0Q7xMFwic82nXN/C1YEKTuJMvT/eD3m0wMmVXcKN0q5cNy/B8dwnPcDEPOUTzwM8YxBWt62TYrSoxGc5PnAs105ertwrKyLRAsD5x62VqVQIgAFlPHQByYSGy5wPAnyoJg31mR44hbnczxbhS9VNvAzNct2h6YQAVisJ7srcEsxVHKsJwgVyu243tMAHV51xHCs0Vw4bHvnO6bph%2BcaQIDYGHhhHbgCiGgokiA0fR%2BcsEhTc8fxjGSdJ%2BdCpTZsHGLAh0A7FgmA00UAZ7ftBy2a8Moy6GKZhjtRrDdDMNofFQo6sN%2BWmmzGuwHDyfR5ZkrEa6%2BdJ5Z0vu/HM3uP76cZ5nWYYbsgZBoc2zwYVUCoUcIBlmLlluRzbi4MkZxzKGdse3XNSnb2519nLnXAoXavvSaywd2beYDxjmOAW41o4xVlSW1b1vxaPbIhnncqD/P8sdf5DUpAAxPBiHGW5sFUVg2Ufb57WLkvnUxCEoUfcbnjFYgmEIUDY%2Bbg5bgANSYZFypBMP1xQogTWrBax4nwaLAgq0OsOuCTuQ1DLtVrusyrHM/YL50jWNBQIlQTBgg%2BT4m%2BDGr1wjthbmCT8ozf11F9VOtZUvtfO%2Bh5V6bX2pvbyx1eJnQ8rQfeqVNp3XfirVKip0RKluK6FB6otrZULsCE%2BwdtRFz2Epf8U84yQQ6iKA8SgWgglxnzKm/VMDaWHFfVAwDB6xjjh2ZOG04Tj1RHCcSE5%2BRCPxG7MRy9hFuDMGicRK84TyJ5jw8C2CNRXC1ufFuAJS53CEN0AQnFa713oBQl0ujThAmHqQxS5DH7XEIsVOISgZH4lEZOQwnEJFwikTw8ByAaGHjiOKK4jC45gDAJghsBAWFsLhIAzh985pzj4ZnQRSi3D%2BMUbIzxuT8QqOwAU5R441Hzg0SCLWHBVi0E4E9XgfgOBaFIKgTgbhrDWAFOsTYXcwQ8FIAQTQNTVgaRAE9SQZYNAAA4zBmASAkLgT0ZnTK4BmDM0g6kcEkLwFgEgNAaFIE0lpbSOC8AUCAQ5Qzmk1NIHAWAMBEAgHWAQVICJyCUDIqkOgcQIjRk4KoaZSRHJJEkLcYAyBoJSDLGYXg7UiDEAwnofgggRBiHYFIGQghFAqHUDc0guguCkG0n3VInAeC1PqY04ZrTOBPgRG82UNtbiAuBaC8FkLXaTLMBjDwrIfmnUxFwZYvBrlaFWBAJAXyBUfIgNK%2Bg8RgBSDMHwOgzIq6UGiDS6IYRmjInJbwHVzBiDIifNEbQLYDWkDIjNF8tB9X4qwNELwwA3BiFoBc7gvAsBMyMOIR1lcWx4GEp6lp3FugIm2AMsIzItktKRNEPuJqPBYBpaqPAeyvWkGEsQdyShHi%2BuAEiIwwzVhUAMMABQo9SpPh5FalFwhRDiExQ2nFagaWEv0IYYwnTLD6DwNEC5kBVioFSNaT1jkiSwnuKYSw1gzAnJzYirAQ6cI1DqNkFwJsph%2BCJSEeY5RKh6HSJka0O7j1FGtIMQ9IwiVdB6A0WY56721CDY%2B/o17hjxDvU%2Bzw7Q9A%2BRaJ%2BxY37VgKB6VsCQlKOANKOTS05LKgUgrBRCqF3KMa4EICQGE/SRWDNLasKiTAsDxDXWMyQ/gywJH8BsjQkgzCSDEhoJ6SQEj6E4Ds0gez/BcDLEkLgSRpkJFWUkCZSzqMpGObwU55zLn4ZuRKx5krnkMveRQOVqB%2BUKr%2BWwTgzQWDwQzI5JgzVu2uwSGWXjYb8AIqRUShtaLm3SFbUodt%2BLdAqpJUwMlXroOwak7Sjg9LXkIkElQRDbKwX7hYlwCzVneWae%2BQqnD/gzB4bFbc5T8q4iyuy/EaLSrFmHJoPRVxmrtW6pNVao1eqzUWocFam1wE7UOpaU6l1braAeqtT67t/q2uBp6CGml4bkCRqtTG2oNKE1JuRCm7YLT02ZoGTmvNmAC19bCKABTfAK1VprXWrNDmm0Yuc7INteKWkea7SW2dVg%2B0JtXSOsd2QJ1TqVHd%2Bdi64jLo%2BPAMDr6H1%2BAgK4Z9QQTbAaPUSk9xQch/vyNDy92RIe3vXW%2BhgfRJjw93WjoHmO5hlC/QB39eQceAYJwsKHYGIMYr89S/FCHWXIdMzFuLUyMM2ew0K9LBHSBEZI5QaDnHuMWboxmJ6CR1n%2BHo4xyQRKAsydsHJjLin4DKZeYy3LiWBU6e2Pp9lLAFDwWgvBWLZY1zjDhZz5dyLZCOdO1i%2BQrnLs6AKF5nzFL2MwfpyculqmmXhdUAbo3JuzcW9lBAPlSWRKYn8DznbWXtcKq11pkYxvUipBFKbhIIpw8iiD85tVZWIBavxTVqrWby%2BmvNZarNTXBAtZpe1117rPUDN636hb3rBuOGG/i0b42s2TbjbwGber5tpsRct3gq2MjrZZJtktO3y1MErdW1htbGD1rtydiQZ3sXO47QUAwt3e02Ee/91pL3YKcB2O2T7lgF3SaXRhP7w7cfWi3e4bHeh92E5AxeqetkGDjDlegekTi%2Bhuu%2BljqTgBoDtaPjijt%2BrYCTv%2Bj%2Bh%2BuAQAcKmsBsJBtgVsv5vBpwCysHsbpdGHmGNXPbNbilsKqKrzvziMGulssLiAPMmWP4P4E9MsnLgcpwRmIJnBgzpwLJlcrzuRk9FRmshmActMpIIslwLMkFF7v4D7tJiIfJuKtBrCkIb7mcpoSMtmq4pupIEAA%3D%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/right_review/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/mouldivore/right_review.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/right_review.test.hpp)
