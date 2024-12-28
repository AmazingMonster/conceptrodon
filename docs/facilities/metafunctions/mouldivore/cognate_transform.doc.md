<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::CognateTransform`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-cognate-transform">To Index</a></p>

## Description

`Mouldivore::CognateTransform` accepts an operation.
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
 :: template<typename...> class...
 -> template<typename...> class...
 -> template<typename...> class...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct CognateTransform
{
    template<template<typename...> class...>
    alias Road
    {
        template<template<typename...> class>
        alias Road
        {
            template<typename...>
            alias Mold = RESULT;
        };
    };
};
```

## Example

We will apply `UnaryMinus` to elements whose value results are divisible by two and three in the list `Vay<1>, Vay<12>, Vay<2>, Vay<6>, Vay<15>`.

```C++
/**** Vay ****/
template<auto I>
struct Vay
{ static constexpr auto value {I}; };

/**** DivisibleByTwo ****/
template<typename Val>
struct DivisibleByTwo
{
    static constexpr bool value
    {Val::value % 2 == 0};
};

/**** DivisibleByThree ****/
template<typename Val>
struct DivisibleByThree
{
    static constexpr bool value
    {Val::value % 3 == 0};
};

/**** UnaryMinus ****/
template<typename Val>
struct UnaryMinusHelper
{
    using type = Vay<-Val::value>;
};

template<typename...Args>
using UnaryMinus = UnaryMinusHelper<Args...>::type;

/**** Operation ****/
template<typename...>
struct Operation;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = CognateTransform<Operation>
::Road<DivisibleByTwo, DivisibleByThree>
::Road<UnaryMinus>
::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult = Operation
<Vay<1>, Vay<-12>, Vay<2>, Vay<-6>, Vay<15>>;

/**** Result ****/
using Result = Metafunction
<Vay<1>, Vay<12>, Vay<2>, Vay<6>, Vay<15>>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

For every element in the list, we transform it with the second operation if it satisfies all the predicates.
We will do this using the following helper template.
It decides whether a element shall be transformed.
The selection is done by a partial specialization, which is specialized by a constraint.

```C++
template<typename Element>
struct Hidden 
{
    using type = Element;
};

// `Puberty...` are the predicates.
// This partial specialization will be selected
// if `(...&&Puberty<Element>::value) == true`.
template<typename Element>
requires (...&&Puberty<Element>::value)
struct Hidden<Element>
{
    // `Hormone` is the transformation.
    using type = Hormone<Element>;
};
```

Here is the entire implementation.

```C++
template<template<typename...> class Operation>
struct CognateTransform
{
    template<template<typename...> class...Puberty>
    struct ProtoRoad
    {
        struct Slash
        {
            template<template<typename...> class Hormone>
            struct ProtoRoad
            {
                template<typename Element>
                struct Hidden 
                {
                    using type = Element;
                };

                template<typename Element>
                requires (...&&Puberty<Element>::value)
                struct Hidden<Element>
                {
                    // `Hormone` is the transformation.
                    using type = Hormone<Element>;
                };

                template<typename...Elements>
                using Mold = Operation<typename Hidden<Elements>::type...>;
            };
        };

        template<template<typename...> class...Agreements>
        using Road = Slash::template ProtoRoad<Agreements...>;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEEhoapAAOqAqETgwe3r4BwemZjgLhkTEs8YlcybaY9iUMQgRMxAS5Pn5BdQ3Zza0EZdFxCUkpCi1tHfndEwNDFVVjAJS2qF7EyOwcAPQAVAeHR8cnhzsmGgCC%2B4cA1ACSLKn0bIJMjbdH51c3p3%2Bn30uF0uBEwTwMoJMgTcoPB70wUJhAE9UoxWJgAHRYqHYW7IAwKBS3ADyqOI72yOOBE2IXgctw8wGYoIAKuSGAp%2BMQWMCTAB2KxXW7C26w57wxFiiEI6EEFFothYjE4vEEhRK5ReKpyqlCkU0ukEW7KYioIgAJVQTHQwJFt35gsudrtBvpQgJCFtzuFDq93rtUolsrB4shsvlzEV2MCuPxTEJtwAEiQWAIZdg/f7ha6jSazahLdbM1nfXqs97A2HkajI5hbtgXowCLqneXvTmk3h0FgGPay22RaXWwP/V5MkZRfL7YEACL1xuCKGOkd2/kzpe8/sjysy6sKusNsFNlsrkXETAARy8eHPRIgSvMADYn5rtUjEYfXs2YyAQAA3MQvEwZZiwHDtEy7HsPwXb8My3Ach1Pb0dh2e1Hw0ZNuTTEx0NuPAiQIBA6wIdlORTCkBGVeDTzHCJgEnVFpznTDU0iaCj0XGMN2o8s124oEeKzHdJQjdElU/JsFBPJDaInABZTx0CYkkyQohgRJrdFO27Rh2K/KSfxAOVUQfLjAmXBC%2BXXczQJ9Kz%2BNs0UQ2lSVnKDPda1M2M1SVS5gHPDiCAMuDh2dWT6MLJSoTnd14yQIy3NBY1TQtK0bWhPyAv0rz%2BNXeybKuTNhODOEq2M/cvNVeN1SxTLMEC4LM3C25IuUvNUqLDL/Pq7LowzAqgXyx1gV%2Bf5jkBUb61UVhnjrL4RrGgFNyBMxAgifEvCwac3DQBgtlSIKWwWu4ADUmCRT4zmBYq3CYLwiAeFsOzO99CoFW45kcZA8QECZMFUVJiFuO6HoA7w6wde4%2BPM%2B0huWyaZzwP98LwWJ6AsJEWQAd1QS6DkBG7ytrW4ztoJ6SMNW5EeRzI0cwDHsdQXkBUzT68G%2B3a/oBoHYlQTxbjBoDMwdUnf0FiGzH8W4zCY6Lbg0aHhrhwqfiOKmkZRumGYQAK8b2AnEt3ImtNJ8naXpanNfRzGdfq5mLOzFovp%2BjlQW525ef58XhYFUX/0AiWpcCWXZ3lxXmes4bVbuORmGIJE5IiMc9YN0qjdEtgSbEM3Kdj1oE6ThRE3qMl7aa8d6PK5SXsRABaP3vbMpXI%2BWwmM8xWriGARqrmavP48Thhk7l/uC6HouS4SRFLi7mrlUM8qHOjg4VISNSU%2Buw2NIqvrqQp%2BlSTXxol%2BuNW5MwFoqC8PaPnmq4280qMMRn7uW2a8/L%2BvhxsmUxlmUwNkhgyLckRIfckx8uJXF/JFREltabW0ZqQdWNNUYINtumYE0C0qIlHoPMcLZfwKVoOlNwL855UgGsdFeQgvCpCKJgdA5pMAKC8LQI0d9LjNRoXQjIDCmEsLYcpMBaleTQhrtCLgOIkHiLcLXLgZgpFZ3fNCBRMZpHnTrs%2BNRSjERcH8BQ/qUdT53H4aw9hV1e4VxaswsxykP5MCvjfSkhUxEaIkYomR8iPFuLcKo7A6jlFuC0f4nREj9FmUMfDNWLJmHmPxnvCkyAAD61UEgEAgBMdAv4FDohSQZNwpi2FIO4fQxhNi2E4hAuZDgqxaCcH8LwPwHAtCkFQJwNw1hrAfXWJsCWgQeCkAIJoGpqwADWARJAYg0AADjMGYAAnPMvRMzplcD5HyaQdSOCSF4CwMYpAmktLaRwXgCgQApCGc0mppA4CwBgIgEA6wCCpHuuQSgaAnh0ASFEdEnBVDTMfLXR8khbjAGQN9KQGIzC8AYYQEgXY9D8EECIMQ7ApAyEEIoFQ6grmkF0FwUgWNySpE4DwWp9TGnDNaZwYk90XlGlQFQW4/zAXAtBeC24kKZYQA8J8%2BgQNzD9OWLwS5WhVgQCQB81IXyyAUAgFKmVIBgBSDMHwOgoJiBnIgLEKlsQIj51JbwPVcckTEliNoTADhDWkA%2BV%2BYkDBaBIipVgWIXhgC3VoLQM53BeBYBYIYYA4hcX4HPN/P8zCqX/UtfdbYAyIigi2S02gqNyTxw8FgKlJE8B7J9aQcNxBeZKBnGCANyajDDNWFQAw3cTp4EwFjQ%2BTSBlIuEKIcQ6KW1YrUFS/F%2BgA0oE6ZYfQqMzmQFWKgA62RvW10ydFUwlhrBmCOfm4gXYI1jp6JaxoLgGDuE8J0PQYQIjDEqKMAlRQsgCGmH4c9GRL0MAWCMaom7v4CH6FMfd%2BQCV2C3X0SYgxj2LDPbYf9169BzDaI%2B091RVgKB6VsCQ5KOANIOVS45zKAVApBWCiFkzuW4DhQK1aXBhWDIrasIi1pRgQDGSASQgQMTzMCBsjQkgzCSHQhofwj55n6E4Ds0gez%2BkYkfFwR80z5mrMfP4SQeimOPlQ7i45pzzlkaueK%2B5ErHl0teXKhV/KflsE4K0Fgf4%2BS1yYFVCcXB5kYi4FMmF%2BAiCrqyQSltKL23SE7UobtuLdCqqJUwElPqkMocObwY5tLnn3VuIyjDrKQVxms7Z%2BzGhbg8tQHyhI9pVpmFI6K65Wn9MJDefKzL0r%2BUoAMEYGzNQ1VsISFqnVuLjUGtza1%2BOZqLVWtzbaps9rHXOswK691YgvXWr9aW7YLSQ2/vDd6lpUbkAxutfG%2BoVLk2xFTUidN02RWrpzQM/NhbMDFv9UYMtoB1N8GrQoWt9bG3Wvc22tFXnZBdpxS0/zfby3zqsEOzbo6aOtMnb9TgM6CDpRnH9xdy6EgufXcDn9r6/AQFcGBglR7yhPr0BexoGO0h3saFBpY376i/rfaBz9N6X2NHfQB7H0HwNU7yDTiDDOT2k9g/BtFoXKVKc4PFrDVn6I2bs1M9LBHnM5aFSK8jpBKNYESMDrZAmhO2dY3yfw8z1mBDYxx2TimjmcBUxcitNzNNICefS0rxXiCGe2CZtlLAFB/m%2Bn%2BMX0oJiOcIwitzsgPOvYxfIHzn2dAgGCIF4LZK%2BPIf58bjgUX6WxaZaoZ3rv3ee/hBMdLvKKvZcFYEfL5uivlZlbbsvlW3d0KSR7%2BZSSvcECSWnrz6rGuUGay0jrTr2v6s6%2Bard1q%2BuCAGz3mbw23UevG7mybF29ukFm2GiNuKlsrdzWtxNvBNvbd25mg71rju8LO6Wui5uq1MBrXWhtNYnsB5exIN7mLQ89ojz94wg6bCA/gOO0HHJOA7EyQHQXUsCXQixXTXSB1g3JxRx3T3VZ0PV3RJ2Azx2yAJxQNKEAxxzJ16EpwGAJ2Rzp3/SQOfXZ3wKIMwKZxIzWA2AQyoK2TCzQ0Fxb1uBdzdwFiz1BBzwgClxIBlxIzl3Uwo0wCo2VyQzVxAAWQxECECH8H8FYxqA0GkL5HEyNwixN1sFUwK2WFo0kH8EYzWT5GSGmUkCWS4FmTMAUy2UCHjzUJOTUzFSQ2hVUOpTsK0NWHzUyGcEkCAA%3D%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/cognate_transformation/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/mouldivore/cognate_transform.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/cognate_transform.test.hpp)
