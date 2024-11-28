<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::RightReview`

## Description

`Mouldivore::RightReview` accepts a predicate and returns a function. When invoked, the function returns true if the predicate evaluates to true for every relative-order-reversing pair of its arguments and returns false if otherwise.

<pre><code>   Predicate
-> Arg<sub>0</sub>, Arg<sub>1</sub>, Arg<sub>2</sub>, ..., Arg<sub>i</sub>, Arg<sub>i+1</sub>, ..., Arg<sub>n-1</sub>, Arg<sub>n</sub>
->   Predicate&lt;Arg<sub>1</sub>, Arg<sub>0</sub>&gt; && Predicate&lt;Arg<sub>2</sub>, Arg<sub>0</sub>&gt; && ... && Predicate&lt;Arg<sub>i</sub>, Arg<sub>0</sub>&gt; && Predicate&lt;Arg<sub>i+1</sub>, Arg<sub>0</sub>&gt; && ... && Predicate&lt;Arg<sub>n-1</sub>, Arg<sub>0</sub>&gt; && Predicate&lt;Arg<sub>n</sub>, Arg<sub>0</sub>&gt;
  && Predicate&lt;Arg<sub>2</sub>, Arg<sub>1</sub>&gt; && ... && Predicate&lt;Arg<sub>i</sub>, Arg<sub>1</sub>&gt; && Predicate&lt;Arg<sub>i+1</sub>, Arg<sub>1</sub>&gt; && ... && Predicate&lt;Arg<sub>n-1</sub>, Arg<sub>1</sub>&gt; && Predicate&lt;Arg<sub>n</sub>, Arg<sub>1</sub>&gt;
              &vellip;
  && Predicate&lt;Arg<sub>i+1</sub>, Arg<sub>i</sub>&gt; && ... && Predicate&lt;Arg<sub>n-1</sub>, Arg<sub>i</sub>&gt; && Predicate&lt;Arg<sub>n</sub>, Arg<sub>i</sub>&gt;
              &vellip;
  && Predicate&lt;Arg<sub>n</sub>, Arg<sub>n-1</sub>&gt;</code></pre>

## Type Signature

```Haskell
RightReview ::   template<typename...> class...
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

- We will check if every relative-order-reversing pair of `Monotony<0>, Monotony<1>, Monotony<2>, Monotony<2>` satisfies `IsNoLess`.

```C++
template<auto I>
struct Monotony
{ static constexpr auto value {I}; };

template<typename L, typename R>
struct IsNoLess
{
    static constexpr bool value
    { L::value >= R::value };

};

static_assert
(
    RightReview<IsNoLess>
    ::Mold<Monotony<0>, Monotony<1>, Monotony<2>, Monotony<2>>
    ::value
);
```

- Note that the order matters when the predicate is not commutative.

```C++
// Reverse Monotony<0> and Monotony<1>
static_assert
(
    ! RightReview<IsNoLess>
    ::Mold<Monotony<1>, Monotony<0>, Monotony<2>, Monotony<2>>
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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxCAAHGakAA6oCoRODB7evgGp6ZkCoeFRLLHxSbaY9o4CQgRMxAQ5Pn6BdpgOWQ1NBCWRMXGJyQqNza15HeP9YYPlw0kAlLaoXsTI7Bzm/mHI3lgA1Cb%2Bbl6OtIQAnifYJhoAgjt7B5jHp8hj6FhUt/dPjwA9AAqUHAw7KYiYGiqQ5g4GA/4ETAsFIGZEnNwEK4pRisTCkQ4ZABemAA%2BgQ/o80AxNikCBCoTD3gARQ4EYheTAnKyPf4gsGHABKeGACAIAEkGApcQ44WDEY9kaj0dzTtjccw2FSHmNOXKRWLJdLZQyTAB2Kzmlk8/5IlFopgY04k8kEAB0nolOr1XgNovFUplXUpLoI6BAIDCWFUZKUAEcubS1W4JZ73X9/NhjnzLf9DgX2Q7VZjlY7nVicXi2Onbod9kwFApGZh8KJkYTIdC8KpMd6s%2BnCRrq28APIMFnnK5DqtazDpoWYMbYehsQQKHWFomNRzIesCMaYABuYkOTHOqEOeHQV1oECW%2BcLgMBhwA6m80OU5uyEG8oQovFoAhmy8DIjDPQ5%2BFodBDkwVQUn/DIBEOVAjziY4ADYNHMDCcJMLCM0eLdn0OAAVX9DhSJhkAAa0OAB3N4mjeKD8HAvBm3wjRF2XVdGGA2sCMfAsAFo6y%2BSNolQTwyRpMZDFDNwIFrMxcNUrs2ydFMeIIFcUX4hRCXHSdsVuSMT28TAHyzW1cxtfxeQBB4BVBYUAwIRcjzwTB6PlUFFQeMsS3VYstNLWd8VrLN6wMJsW00507keX1/SNTzvPou08yIwsgrC9UIprT09LXYDN0LFKGUhVAiAAWU8dBhOObKHi3Ld5N3fdpWReDiEOKTPEOCyuSarcLUctrJuOABWKxpvstxXQpdN%2B2wCAJKjBgYzjTBE0YTY%2Byi7AHxyqbC3G0azsLKECHWBhLquw5lM9PDVIgB7HsLLB9mHD7Pqev7/sLQ1AxNENMQ2lgmBo8lozgna9uTPtMyS1qgceyM8uRK8b1oTENLwdsCUOEqDKO%2B9AcepZzLEEbTqBpZrImz6LRZdbw0jKGYbJOHYwTJMDpdPBSVQKh0wgUn1yWQ4RMOLg/jza0TrRybWZ5HMVea%2BzHKarGU2HOd00lsqbPp0CwmAQ56ug1lGRq1Brca05jYUI7bKea13f5eEfd9gKXPBUil2AvyEW932I7Dvk%2BTMXZaVed4zgua4dXtFV8rcc8iEOVb/kqq2BHthgblzCxtydQmusPXqzwvIbabecbvU9hyta9pVQorA38UOYIZ01HuhR9Dk/QZCUFAiVBgiXDdS6ajrK7knqEP66TaHryymvG3uacs947n8NkhV3rk24cu07Pb5z4UOAAxPBiDGEnVFYNE3nhAKF%2BQMlGyUZp/nevTEGHljwZT7BPKeM9yoFkjI7TE9UGBFxuKcbCWZCQIKQZieWaCC6IKIMXTEZhbjoMLvg5BbgiE2VNprE%2B3JHhMwvtfQUQgugCBgtgF%2BKp34Kn5C%2BTycQlC4MwSgushgYIYLIVg4eFdv6/ziJSR4gDNZgDAG5NKoCfLgMntPJs0DDiwIavA0hAhyHYOwCQvBJjMSoPMUIyRpxKG2IkVYhxKMmq0P%2BEzDgKxaCcGmrwPwHAtCkFQJwNw1hrBEjWBsRusceCkAIJobxKwaIgGmmYd05ozCSASAkaaGgACc6SNAYQSIEXxHBJC8BYBIDQGhSCBOCaEjgvAFAgHqYkoJ3jSBwFgDARAIA1gEBSOccglBPwpDoHECI%2BJOCqASBhESGFJCHGAMgPcUh3RmF4K2QgJBrx6H4IIEQYh2BSBkIIRQKh1BdNILoLgpB6LECYCkTgPAfF%2BICUkkJnBRznBGQyUWhx5mLOWas9ZctJBbKeh4VEUy%2Bo7C4EsXgnStArAgEgCZ8KxkQCxfQeIwApDJBoEBARlBojfOiGEJoVw3m8CpcwYgVxRzRG0CGOlpBPylXHLQWltysDRC8MATOtBaBtO4LwLAUMjDiH5Q/EMeA0LiuCXBLo5wtjxLCMiCpwTLjRGeUyjwWBvkcjwDUiVpA0LECkkoFkKJDDAEuEYJJKwqAGGAAoAAahlUcmoOVHOEKIcQ5yA1XLUN8%2B5%2BgHUoAiZYfQeBohtMgCsVA9IsjipEl8E4LJTCWGsGYJpVriDXiXPAFYnRujOAgK4SYfgHkhDmGUCoeg0gZDqNkTwbQW2FHbQMJtwwHkVvbb0CYna8iDpqAq%2BoMw%2B1DHiIOmYta9DyWaLOhY87y3RM2BID5HB/ENO%2Bc04FCylkrLWRsqFZgnq4D2QiuJyKEkupWL%2BJgWB4j3lIKkyQ/h3QFP8OaSQGhJDZKwhoaaGECn6E4FU0gNT/BcHdBhLgpSCkJGQ9NSQXBpp/owge25zTWntMfV09F/SMWDP%2BaMiguLUBwvxTMtgnAmgsCPOaESTAYoOrlgU90CGVX4CIMWiMDyA0nODdIUNShw23N0MkJ5Ly6W7v3Y03gzS/nDPOChKgZ5iAsbYxxhs4EuA8b4zC2jkz8XHFjmYB9qLunkbxXEHFjn4jMdYyJQzhKClcHqSS5Ej9yWUupUyjlDKaUsrZQ4DlXL%2BI8r5cEgVQqRVio5VKh1sqEvyu6Eq75qrkDqo5Vqmo3y9UGquEarYwTTXmviVam1mA7XSsdRbF1fB3Vep9X6i1omg1nIk7IMNNzgmyajc63NVg416qTR%2B1N7aM1ZsPuN/Nha4hCdLcm6otQsguC2ku%2BtW013Noea2ooHbch1oKG2rIh2B2banQwEdLQx0XaHT0Gdja53LsXc9r7fQbsbtWOsbdSKoN7q%2BfhzgOm9Psc40Zkz7oNDXoEyQKz8HbNPtIC%2Bt9lBd0wbgzxoD5psPmnNP4YDkhlkPJUz8lptgiN2dI/AcjQyAXOfM/ChjWxmNgpYAoI8e4jzGfdKqMYOzkdCcObIMTfWLnyCk0NnQ%2BR5OvIlUp8HTTfmUcBdp7nKzef86GkLkXDIICwos%2BhHY/h0ckZ6Zi9n%2BK2d0eGPzlIKQySC4KWSY3P9dPLL4HQfzbSIAUtuWFkLFqw/MtZeyi1MXBBxe%2BYl4VYgUsWrSzKyrkqsuOBy7cvLBWLVFZ1bwUrNKKsmuLTV3gdX0gNftTKlrNu3VMA9d6nyvrGD%2Bql71iQ/XLny4jfkAwY3Y02Cm2WkJaaDycEBBJJblgC2qaLSW6b5bJ2Vr8NW3bP39voH%2B92q7Ag9uXdO/vidW3p19GP69y/q6Pvrt%2B6O87j/ZilE%2ByDhQW6zlq7wxrjgUOec%2BcBcjctIn4JZxdUckUUUMcsdhgP0Kk8cQAzAeN/B/Bpp8lMM6lUDzRSlf9VNOBCMOkMcv1zQtkicuApAClCc/0uBzRQd/B1d8DacGdd1tk8CadoCSMVgrUkI/BJAgA)

## Links

- [source code](../../../../conceptrodon/descend/mouldivore/right_review.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/right_review.test.hpp)
