<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::ModifyTypes`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-modify-types">To Index</a></p>

## Description

`Omennivore::ModifyTypes` accepts a list of `std::index_sequence`, which indicates distances between adjacent indices.
Its first layer accepts an operation and returns a function.
When invoked, the function transforms the arguments from its argument list according to the `std::index_sequence`s using the operation.
The result will be stored inside `Capsule`.

<pre><code>   std::make_index_sequence&lt;I<sub>0</sub>&gt;,
   std::make_index_sequence&lt;I<sub>1</sub>&gt;,
                    &vellip;
   std::make_index_sequence&lt;I<sub>n</sub>&gt;
-> Transf
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>m</sub>
-> Capsule
   <
             Arg<sub>0</sub>,
             Arg<sub>1</sub>,
              &vellip;
       Arg<sub>I<sub>0</sub>-1</sub>, Transf&lt;Arg<sub>I<sub>0</sub></sub>&gt;, Arg<sub>I<sub>0</sub>+1</sub>,
       Arg<sub>I<sub>1</sub>-1</sub>, Transf&lt;Arg<sub>I<sub>1</sub></sub>&gt;, Arg<sub>I<sub>1</sub>+1</sub>,
              &vellip;
       Arg<sub>I<sub>n</sub>-1</sub>, Transf&lt;Arg<sub>I<sub>n</sub></sub>&gt;, Arg<sub>I<sub>n</sub>+1</sub>,
              &vellip;
             Arg<sub>m</sub>
   ></code></pre>

## Type Signature

```Haskell
ModifyTypes
 :: typename...
 -> template<typename...> class...
 -> template<typename...>
```

## Structure

```C++
template<typename...>
struct ModifyTypes
{
    template<template<typename...> class>
    alias Road
    {
        template<typename...>
        alias Mold = RESULT;
    };
};
```

## Examples

We will apply `UnaryMinus` to elements of indices `1, 3, 5` from `Vay<0>, Vay<1>, Vay<2>, Vay<3>, Vay<4>, Vay<5>`.
To do so, we will calculate the distance from one index to its immediate next.

We will keep the first index, `1`, since it represents how many elements we must pass to reach the first target position. We subtract an additional one from the rest since we only need the number of elements separating two targets.

<pre><code>   1, 3, 5
-> std::make_index_sequence&lt;1&gt;,
   std::make_index_sequence&lt;3-1-1&gt;,
   std::make_index_container&lt;5-3-1&gt;</code></pre>

We will pass these sequences to `ModifyTypes`.

```C++
/**** Vay ****/
template<auto I>
struct Vay
{ static constexpr auto value {I}; };

/**** UnaryMinus ****/
template<typename Val>
struct UnaryMinusHelper
{
    using type = Vay<-Val::value>;
};

template<typename...Args>
using UnaryMinus = UnaryMinusHelper<Args...>::type;

/**** Capsule ****/
template<typename...>
struct Capsule;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = ModifyTypes
<
    std::make_index_sequence<1>,
    std::make_index_sequence<3-1-1>,
    std::make_index_sequence<5-3-1>
>
::Road<UnaryMinus>
::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult = Capsule<Vay<0>, Vay<-1>, Vay<2>, Vay<-3>, Vay<4>, Vay<-5>>;

/**** Result ****/
using Result = Metafunction<Vay<0>, Vay<1>, Vay<2>, Vay<3>, Vay<4>, Vay<5>>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The implementation of `ModifyTypes` is similar to that of `Omennivore::InsertValues`.
We will perform recursion over the total number of the `std::index_sequence`s.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  - Handle several `std::index_sequence`s from the front of the list;
  - Invoke itself to deal with the rest;
  - Concatenate two resolved parts.

We will use the following helper class template to concatenate two parts.

```C++
template<typename...>
struct ExtendFront {};

template<template<typename...> class Container, typename...Elements>
struct ExtendFront<Container<Elements...>>
{
    template<typename...NewElements>
    using Mold = Container<NewElements..., Elements...>;
};
```

We will use `Prefix` to enumerate arguments like in `Typelivore::Amidst`.

```C++
template<typename, size_t>
concept Prefix = true;
```

`Capsule` is used to store the result. We declare `Capsule` as follows.

```C++
template<typename...>
struct Capsule;
```

Here is a simplified version of the implementation.

```C++
template<typename...>
struct ModifyTypes {};

/**** Base Case ****/
template<auto...I>
struct ModifyTypes<std::index_sequence<I...>>
{
    template<template<typename...> class Operation>
    struct ProtoRoad
    {
        template
        <
            // We use `Prefix<I>...` to enumerate `FrontTargets`.
            Prefix<I>...FrontTargets,
            // We will transform the next argument.
            typename Target,
            typename...BackTargets
        >
        static consteval auto idyl()
        -> Capsule
        <
            FrontTargets...,
            Operation<Target>,
            BackTargets...
        >;

        template<typename...Agreements>
        using Mold = decltype(idyl<Agreements...>());
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

template<auto...I, auto...J>
struct ModifyTypes<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template<template<typename...> class Operation>
    struct ProtoRoad
    {
        template
        <
            // We use `Prefix<I>...` to enumerate `FrontTargets`.
            Prefix<I>...FrontTargets,
            // We will transform the next argument.
            typename FirstTarget,
            // We use `Prefix<J>...` to go across the distance
            // between two targets.
            Prefix<J>...MiddleTargets,
            // We will transform the next argument.
            typename SecondTarget,
            typename...BackTargets
        >
        static consteval auto idyl()
        -> Capsule
        <
            FrontTargets...,
            Operation<FirstTarget>,
            MiddleTargets...,
            Operation<SecondTarget>,
            BackTargets...
        >;

        template<typename...Agreements>
        using Mold = decltype(idyl<Agreements...>());
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

/**** Recursive Case ****/
template<auto...I, auto...J, typename...OtherSequences>
struct ModifyTypes<std::index_sequence<I...>, std::index_sequence<J...>, OtherSequences...>
{
    template<template<typename...> class Operation>
    struct ProtoRoad
    {
        template
        <
            // We use `Prefix<I>...` to enumerate `FrontTargets`.
            Prefix<I>...FrontTargets,
            // We will transform the next argument.
            typename FirstTarget,
            // We use `Prefix<J>...` to go across the distance
            // between two targets.
            Prefix<J>...MiddleTargets,
            // We will transform the next argument.
            typename SecondTarget,
            typename...BackTargets
        >
        static consteval auto idyl()
        -> ExtendFront
        <
            typename ModifyTypes<OtherSequences...>
            ::template Road<Operation>
            ::template Mold<BackTargets...>
        >
        ::template Mold
        <
            FrontTargets...,
            Operation<FirstTarget>,
            MiddleTargets...,
            Operation<SecondTarget>
        >;

        template<typename...Agreements>
        using Mold = decltype(idyl<Agreements...>());
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEEgAcSaQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJXCm2mPalDEIETMQEeT5%2BQfWNOS1tBOXRcQnJqQqt7Z0FPZODw5XV4wCUtqhexMjsHAD0AFSHR8cnp/u7JhoAggdHANQAIphprozIeJgKd8cX17dnAJOvyulxBZkCEWQ3iwdxMgTcXkctEIAE84dhQeYIQwoV4YXC3MhJugsFR0Zi/sc7spiJgaKpvkdgQRMCw0gYWQSCCiXsw2KQ7lkAF6YAD6BHJ1zQOOeBGptPpsMCDzuBGIXkwcKs11B/32dzcTDSCi89EZh2ZrPZTE58O5vNYmAAdC7JVdJuqHAajSb6FqKTcqdhVCyGOgAGLEWTm86gllsjmau08xiOl1Ot0erxe4OhiNRwSwgDsViLD39Ouu8ettrc1cTXJTfOdrsC2DuUKYCi%2BHkETAiCQF9tTbHT2HobEECkzauzctzrkjsgJvdaA%2BIBPHrMYBAU6fJbcxJdBd1PqqtDeTDtHLqimAA7lvJ7u3We7l4skY7gBZTzoJUqqu/aRBu8J3o%2BE47nuLoCk%2BUH7oegTaiCZYViClKAphPy6lSACSCbbn2TQxsCepYYCwJxheNpJnWTZpq2GLXFmXq/vgVAogAKimXwmMeqFIQGep3BYXaYN6SgkVRCY0QSTCIqg6a4TOnpymxeAcdxLzTvCxIgCAERYKoopKAAjhqMoErhCEYoeOrHtcb71rJdrUbWw7NjZHYGN2dwAPIvMQNo5K%2BZ4sXKNKoEQABKqBMOgJ5nnxyFvk5bmao5qWngSiVZW%2Buy7HcADq4kfuJJgAGwaDSdJ4KoVnovuVWqqgdyMD4CQ0bCVVLoInFtMAmAvlVGaZXlZ41fSDVtumvUEP1xCDbupC5eNdwFcV4n3nQtCqkFDAKPwxAsKqCDiZEIZ3ANHWCKNVxrWeHmOncC1LStY1rU9N5OqJyAANavUN04fW%2BoVZfMjjIB2AiTJgABuYhXQpdx4OgKK0BAKyrW%2BAC06LesapoZfdeU5SDeVzYDu7pu9JMPQFnVNASVPorTD2nr9AMDUD%2B7k9liHIdjj3pY214tk6VzALShEvnZdOpR%2BETAD%2Bf4AXcWBQsOECo%2BjBKS9Lz7QRmbaY1jgkfXx5bm%2Bh8vOe5ItXiO4v4523bpvrmAyzpTHy4rX6xfFauRTFcUJfCHtezZaGW9HVYO4aClKQK8lEOmABSKlzir7FcTxBJ6QZYaYMZZkWdsVk2QKBeGcXJmYOZby0WnUdy8lq127RHei07Xmu18DNBUzctvuF8pRagAcJRbDny2lMmcnzSpuELWUbSV76SZV1UKnV03YE1GgtW1DAdYP5U9QW83c8NGh3ez8q1fV8LKTNLqU9fChs%2Bza9bTte2GIdEgJ0CBnTuBdOU11nx33Zl9cS4Y8DEEmFTL%2BD0f4b3PtvR%2BBIM6vwzM1IgdxgCtSYMgKMvkQHiXwPMSyi98qFXiAQe8nsGCqnvK1KYS09wr1SpNXe8IcH7xdN%2BVG6B6BU0/twuhm07jbVoLtNUACjrANAeAq6i0boEGgQ9WBdwhCYGlOgZBkjHr0W%2BpzcR3CwapQhngKG0pYYI12inVqOsMZY0XnjNsBNfTE3GmTWeFNL7iJpsY08A9goCAJPAxBV9FpDVZqEn8IixEfxCbQs84Sh5uD0QYlmbYUFrXMak10i8DyC0Xl3R2nkXQR0NlYt8ftla/loP%2BOEKoNa0C1q4vWUtPaGxsqbNCoMBLlNtvHSpdExa9x8kbWpUErGNLuJPIOUYQ7xR6QbeCjFo4jKElSaK%2BjNhZDhuJQ0klsJx3nrRZxSckapxdGnIcpjxZ%2BQocQPRDcZTe1BKPdSmk866QIOgfSNcS71zLrRayjEq5ApBUXMFnzy78Mrv5N5HyIVGzdG3D6EzcXPOmV2fugUIkMCsaPYOE9Q6rWxQE08XdSnwkSWgsq3VMFTWfo1V0%2BDWrtTYGfVl784k3y0WtXhT83Av0EU6QVnCCnjTQbI%2BR%2B1AHHVOudYuED1FQMSTo6JSDr5yrysyzeVUxXYM5Xgw%2BBCiFXVIZkL4FD1Z4GoeXdJp4NoMKYYwVh7DUmJLNfwi1wiSQpKFRIt161Crr0Vf/A6Si1VgI1Wo4AGiRXjR0TkgQhiDU6vxS6IpYbLHDzyjYuxMMWSOLuS4tGbjuGePbAuMMc0i3LwjTov5udtIEleWdd54LG6YuLQ9fSHcllUvhJkkKQ61ojvSirFpBIC2cKjgyn241Z1XPnVPWlS9Ekyp5jBRJk7Inwj1bEpaCSI3BtEZgYJh6I3HtJfCTNYY8lrtJgLAM6bxl5olr0r29SzyLOaa05U6t9GdJTNrGtGy%2BlbONtgQZ1thlW1GXPGsncf1TMYt5Ql7t/11OnYs5ZbSx5rLDm4OZU4W6C12ZWQM5ELkMcOHcYMrB2TiSY2RcilEdTgkhNCcq8JpTbDSLLH2OF7gADUmAoikpcjDclkaSp%2BbOL0Mm0T2QsIKVokNoYHRZKoNIxAq13EcRqYsFhlIjOLKhvZ9w5DMGICiYRJ8vhMbxWLO4MnaCZy9I5toLmIgfgABINECkeFKQHPzK2HGrDTBIcY%2Bf0uZpMtlaN2fo55nuNTFrfOuIsgLznXMfjVkVoLbmwu0Ai%2BHPLNkR0pljsx/UhpCZmg81hnLCHVOqW8UTJrwlvxDSYFQLwOJiIdaud3apEs8tumA8N0b42chqw7VpT4mJGUfQLiwJgf0xSgrroi2iXBL3yx23tg78KjsQoJIEHGXAHtnZHrCkAu39uikO6XRuBJ/A43u6d1uct9KTwJOVkr%2BWrj6RA3rOr2zraSZY0ILwaRiiYHQAc30comOLOR6jzI6PMemjlKR1rPiCQJfhBoVm3nZOJcB9gAUlO3BmBp8z/7bO6fwkkJztE8Icb%2BAPOl%2BzLGiedPk1cYjnxiercW2NhwU63DM%2Bp/k2nfO3AM6Z1zlnvO7u6%2B5/rtwgvELC/o8JTinxsdMlU8FZAopCUJAIBAAuChHT250m4MXBABR47Rxj6XnT0RmwsBwNYtBOD%2BF4H4DgWhSCoE4MvSw1hBQbC2OVcEPBSAEE0KHtYf0AiSCdBoJIZgzAAE4y9cH8MXpIXAixFmkOHjgkheAsAkBoDQpBo%2Bx/jxwXgCgQCd%2BzzH0PpA4CwBgIgEAGwCBpEROQSgaA2R0ASFER0nBVBJAqjjCqkhCHIChlIJ0ZheDo8ICQVGeh%2BCCBEGIdgUgZCCEUCodQI/SC6C4KQe8QU0icB4GHiPKPHPOPTgPyREOfOUVAKgO4TfbfXfffQ/QvMwO4CADwZfegEzLELgFYXgYfLQNYCAJAJfNIFfMgCgCAYg0gkAYAKQMwPgOgFkRBSgWIYA2ICIQLP/XgNgpzFEPyWIbQfRYfTPJfZ8PyBgWgFEYArAWILwYAQ0ORAfbgXgLAXbIwcQN/fAWkBXE5RQ2PYuQ5FkTg8gQQBoYA5EWIIKZzDwLAYAtUPANvJQ0gE5YgWIAnJ4VQ4AZEIwHPNYKgAwYABQKTD4e8BmaPTPa/YQUQcQB/CI5/NQYAj/fQQwYwawawfQPAWIAfSANYVAMTHIRQnGYkNpUwJPSwMwHvZw4gVGT4eANYOwQQnIFwMMGYPwT/MIAcJYMYT/YobIAQFovQHopoRYUYGoXoBogQAYaYTwLoPQeohXCYqYIYDokY2YxY/oz/eYdoYYqoLouo1PbYCQAAjgSPLvYA3vGArfHfPfYAA/O4I/ZAiAXAc/TAjPHArPHwtYM6eKMYTGUgfPSQQIJ0MvQIBvDQSQMwSQKqDQfwCqMvfQTgFvUgNvQILgJ0CqLgCqJIMvWvCqfwSQKvYEiqU4t/XvfvQfd4kfAgyfQg6fcA%2BfcgygjAtfNgTgNoFgOGIsHGJgXDL8LgMvJ0VEvQ/AIgKo4FT/CI2/aI6QWIpQeIt/XQOg7/I0Tgo4k47vXgXvMA2fREO4KAi4uAvfTsXk/kwUlAtAkgjA2EcEMwN4vA0fGkxkwcBk1AdAsYI0mgyvTvGgTpBIAfCAFgt/bgjgxwoM5zPggQhwIwkQncMQiQqQzAGQuQsQWgRQzPFQ5I9Q2PTQhonQ4A/Q5AREHYTPCIFkJvWPcwywlEawnYWPOwhwzPZw1wpQdwjMpWHwvgfwwI4I0IowiUqI%2B/aU2QOI1/WPBUpI7wkoqwSwdIzI2ouPPImGTgQooFYo1IsoiohIUUmo7IsY%2BYvwCAVwdYkIMMbY5YbozIXo3IaYgoc8koHIU8ro3cpoSYjoa81op8/oRYh80YzY18/Id83878w49YTYA47A%2BE44oAkkzgfUq4nk5WPkgUovFAp4kUq0lE20j40gL4rARIX4pvRE5E/ksEosfwMvevQIcEyE/E4knvTgMkofds8fKfGfCAhfCgl0i01fdfDgNk%2BAlgBQOGKGOGRCxMSYU/YUi/MUx/SIu/CQQcp/WUkcnQEAYIJU3/JQ1UqCuijgLUiA3U6A1QfiwS4S0SmiSYM0zi0g9CwITCyksfIgqyjA9ix0xIIS1HUUESsvUUMSggUUIy6Uhg305g1g9g5zIw0M3g/gwQqMl00Q8QyQjQhM2Q%2BQlMow9MtQms5QhBHMmot/fMwsowks0wt/CswLas2wqo%2Bs3gRstw1kVs7w%2ByvwpgAIoIh8HsxwvsuSmIocpShI1S8clI0omwcwrI343IpoRQ3YPSSc6wcojUyo6osauohocY/cw8t8vQdoioFY28y8o8wY%2B85YnYn81avcl8o8uY58r846s82wNYzajYm6nak64ChQfY%2B/LS2ijUmCgKu4ASoSszMylkCyx4ySl4jC3ArCnCn4o4wikAcvJ0QIQIfwavfEjvZGosTE76kAvvWwcku0lYPPEASQfwIEuvIsDvJISQSvWoUvIkpvQIbSn6vGwmo4k/HG0kik/AtYZwrIZwSQIAA)$Done$

## Links

- [source code](../../../../conceptrodon/descend/omennivore/modify_types.hpp)
- [unit test](../../../../tests/unit/metafunctions/omennivore/modify_types.test.hpp)
