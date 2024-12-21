<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::Bind`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-bind">To Index</a></p>

## Description

`Pagelivore::Bind` accepts an operation.
Its first layer accepts a list of variables containing pegs and returns a function.
When invoked, the function replaces the pegs in the variable list with arguments at the corresponding position from its argument list and instantiates the operation with the result.

<pre><code>   Oper
-> V<sub>0</sub>, V<sub>1</sub>, ..., Peg&lt;I<sub>0</sub>&gt;, ..., Peg&lt;I<sub>1</sub>&gt;, ..., Peg&lt;I<sub>k</sub>&gt;, ..., V<sub>m</sub>
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;V<sub>0</sub>, V<sub>1</sub>, ..., Arg<sub>I<sub>0</sub>-1</sub>, ..., Arg<sub>I<sub>1</sub>-1</sub>, ..., Arg<sub>I<sub>k</sub>-1</sub>, ..., V<sub>m</sub>&gt;</code></pre>

## Type Signature

```Haskell
Bind ::   template<auto...> class...
       -> auto...
       -> template<auto...>
```

## Structure

```C++
template<template<auto...> class>
struct Bind
{
    template<auto...>
    alias Page
    {
        template<auto...>
        alias Page = RESULT;
    };
};
```

## Example

We will bind the second and the fourth parameter of `Operation` with `-2, -4` and reverse the order of the first and the third parameter.

```C++
template<auto...>
struct Operation;

template<auto...Args>
using Metafunction = Bind<Operation>
::Page<Peg<2>{}, -2, Peg<1>{}, -4>
::Page<Args...>;

using SupposedResult = Operation<3, -2, 1, -4>;

// The `nullptr` at the end has not effect.
using Result = Metafunction<1, 3, nullptr>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Bind` is a special version of `CognateTransform` as it transforms pegs into variables from another list. Hence, their implementations are very similar.

First, we will create `Peg`, which is similar to `std::placeholders::_1, std::placeholders::_2, ...` in terms of functionality.

```C++
template <size_t I>
struct Peg
{ static constexpr size_t value {I}; };
```

We will detect the pegs using the following concept.
Since we cannot specialize a concept, `Pegful` will redirect its argument to the helper class template `IsPeg`.

```C++
template<typename>
struct IsPeg
{
    static constexpr bool value
    {false};
};

template<auto I>
struct IsPeg<Peg<I>>
{
    static constexpr bool value
    {true};
};

template<typename Arg>
concept Pegful = IsPeg<Arg>::value;
```

We also need to ensure the integer stored in a peg is not zero, as we will subtract the value by one to obtain an index.
This is to conform to the behavior of `std::bind` and the placeholder objects.
Hence, we create the following concept.

```C++
template<typename Arg>
concept Nonzero = (Arg::value != 0);
```

We will pick out variables from the argument list of the finally-returned function via `Varybivore::Among` in the following helper template.
It detects and transforms the pegs by a partial specialization, which is specialized by constraints.

```C++
template<auto Variable>
static constexpr auto Hidden_v {Variable};

// This specialization will be used
// if `Pegful<decltype(Variable)> && Nonzero<decltype(Variable)> == true`.
template<auto Variable>
requires Pegful<decltype(Variable)> && Nonzero<decltype(Variable)>
static constexpr auto Hidden_v<Variable> 
{
    // `Replacements...` are the arguments of the finally-returned function
    Among<Replacements...>
    ::template Page<Variable.value - 1>
    ::value
};
```

Here is the entire implementation.

```C++
template<template<auto...> class Operation>
struct Bind
{
    template<auto...Variables>
    struct ProtoPage
    {
        template<auto...Replacements>
        struct Detail
        {
            template<auto Variable>
            static constexpr auto Hidden_v {Variable};
            
            template<auto Variable>
            requires Pegful<decltype(Variable)>
            && Nonzero<decltype(Variable)>
            static constexpr auto Hidden_v<Variable> 
            {
                Among<Replacements...>
                ::template Page<Variable.value - 1>
                ::value
            };

            using type = Operation<Hidden_v<Variables>...>;
        };

        template<auto...Agreements>
        using Page = Detail<Agreements...>::type;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEEmYAbKQADqgKhE4MHt6%2BehlZjgLhkTEs8YlcXMF2mA45QgRMxAR5Pn5Btpj2JQzNrQRl0XEJSakKLW0dBVy208MRo5XjNYEAlLaoXsTI7BzmgRHI3lgA1CaBbshT6FhUV9gmGgCCL68A9ABUv9/nykwwHOf2%2Bnw%2BBEwLDSBkhl2uWQAXpgAPoEc4ASSeHymxC8DgBQI%2BJgA7BZzlMmI5kOc0AwpphVGliBS8Mi0ecAG5iLyYS5krEkgAiV3JpJFgSsbw%2BPz%2BhOAVC8tBBf3Bb0h0NhmCubgIAE80oxWNrAs83rj8eiMQpAcBiWSPucnRSWtTaQIGUyWbFUJ4uTztW9nfyLFQxEpxaL7RKpe91VCYVSTW4mF4iJjseaCHiCdbbTr89csabM%2B8HUHnZS3XTPczzj6/dzvIHXsHSRZs7zI5Lo1HpfHNUmdfrDcw2OdXsQ7SW3nT9ml0bbFcqrkLMTaiddJ9PsCAQE2uz3%2B19QecogJkcRUCrfmrXhrE5DhwajePt6W55gF2eLwlr6vzggbc9wPPkwDAACNA2Ps4xPOVXhYARgVBO8Hy1HVUyIAA6HCADVWjwJhYnoBRSwtAkEKQkNu1jCEE3Q65MOvAAxPBiCmMjOwoxCjB1Vj2IIUt20dZ00KHBE2VRK1S2DcjFyvIhlCYYA%2BWE4UYJEp0xKfCT2WkmdW2dYhMAARy8NjMAUQDiwlIUoM0l0c3k1BFOU5NizNQynXbF0qTwGka0hL1ziY/1mxDfiOPUyV%2BRjYkKy0%2BjxJTNNUBwrDXmAYyoUYAhSIM4MvCyIwATc%2BE12UBTUCUlSdUy7K2EEBR0uxI8yzi49tOTULIoIUgQtS84hAaAR0H6pj0oAeQIBAEnyzy5InHjpzcXr%2BuGukxvOabZvYlqDOEhLzi6nUkSkjMCsrLjnNclTLiOnyHNk11/PdekgrrULQPurzgxDSjeOuHa5v23cQC6gEqpq9zzgAWnOMwnhAgMaIc1Hj2DE7dPOjyHOMsyLKsiAbNXeyjsWyqXOqtydVxh6yV86sPQ%2BlkvoDCK2KimNYo0o6sbcM6OTp378fM4yiZJwIhS4aDyeuyGqeh2mZOdHyq1ewLGU%2BwbvvbDbRponm2oc/mJpw%2BrMBypqVadIqImBaHyoV27kwtq28tBjTotot5ZV%2Bc4LAidAbzBOjBx03Ukojs2sKeWkDAUKzJsNYg/IETinIDoP7VjTGo%2B61L0vw4hCOIyybccy1nep2r6dzv7EvDgvsJwgAlL8DH2Rq8or57M6FTAWjoJ7VfLX6G8bx9m%2BvYvS/oXuJ/VgLma11nBoACTwe5GBRTkQ1noj5%2B9keG5Pv7TcGg%2By4XhvRcJ%2BVlx1LBThHTAICv%2BhoMuifVZScxkh/AwS8qAn4NFoK/d%2BBFD6YC/p5H%2Bz0/LL3eqvAa6ZN7bwYLvHUH8TTYB%2BvA0e9cCHBgBitduiYu65WajhG%2B8C9wQyVtcHBWFvrwy4LQn%2ByNmxnzbMfDGxC7YlVfk7ZOCQ04MB1OgrAmDOTYKgWXeans2o/3RrBH%2BF8W4ZSypbbu80z6CIdmVACA8h60Dqto921DY6mnoS%2BGCvCOpqNEvnDChdzYWN0RXAxpU7oAUpi7cxDUqFKNonw2CftQSqhlH8AAKtgIQMSom%2B0iZEu8xIzDHAYKcLwFwdSfgXHozqLjGJuOsQteWojU79F5veYpKVNHbkKa8bxABZQeTBFRZP6E7QODB0A6kqeI0se5GFuELG4RGJYHTCn6rDMw/VxnsKmVYGZcNJDDJAKMxpIT4rNOKsCIQXg0hFEwOgduCglTogAoM6p1xghw3meceYazWo%2By%2BJ8c4MTZqXGSBoBgSpaALmICYX5IV0QzT5K4c4CAmBWQYC5c4mAqBUAaAQWObxvHnMuU7NpLROmNHTtcZ59z/m0EBdmV5uyl4olhUoNoEA7h7gUMaGl%2BU3BYvAetI5JyzmWUuU8L%2BFgOBbFoJwfwvA/AcC0KQVAnA3DWGsBSHYexVIZJ4KQAgmhhVbAANYBEkFhDQkguAkkCBofwGgUjJDMAADhtfoTgkheAsAkBoDQpBJXStlRwXgCgQDus1VK4VpA4CwBgIgEAOwCBpDTOQSgaBoR0ASFEY0nBVA2uSLDZIkhzjAGQDSKQWEzC8FOYQEgW89D8EECIMQ7ApAyEEIoFQ6gg2kF0PMAA7qnNInAeAirFRKrVMrOCTTTDG9EqAqDnHTZm7Nub81PINWYQCHhE30BZEcGWvBA1aC2BAJACa0hJrIBQCAh7j0gGAFIeZNBwFzUoLEIdsQIitD1L23gz7mDED1JNWI2hUXvtIAm7uk0GC0Dfa2rAsQvDABTGSv13BeBYBYIYYA4hIMWUaJySyQ7GQNDTAcdVERISitbbQPAsRU7fo8FgId2Y8AusQ6QbDxAfRKAHihow5GjBaq2FQAwwAFC4TwJgDtojJXqqrcIUQ4h61SabWoId7b9CoZQAqyw%2BgKN%2BsgFsVAC4cgIdhncVcphLDWDMF6ljJcsDaYgFseoBK/AQFcLMPw8wwjLAqFUQomRsgCFcz54oOQRhebWD0PoTRFgBfmA5/ogw2ghbGNUBYQxospYS55pLEh7PKv2Nlh1HBxUeqHd66dGas05rzQWpdgFcBlo3WqjY27eNbFmkwLAiQ7OkD1ZIQIWEACcgQSSSCNWYSQvzzXJH6wVp1pAXWBC4FhZIXBkg2v6zalb/hjX%2BEG6kT1vBvW%2Bv9Rq3jIbw37sjWO2Np7z3rpTWwTgrQWCchJLDJg8dUNPP61hRb0rS1EGs5W2QNbZPSHk0oRTrbdDzK7UwHtiH%2B2FcHa271o7o1pnOJOkKxBnuvfe6cT7XBvu/ZXagNdCRLgZLME1k7Qa90HrJ0e9dcaz2M4vU9l7sMCdGCJ1wd1t7ITsQfU%2Bl937AOftfb%2B/9DhAPAdyqB8DQ6oMwbg7QBD6rkOofQ9K/AxksM4dbXh5ABHAPEd6EO8jlHX00YONK%2BjjH1UsbY5gDjWv7anf48pITImxOjkA1JkHdaweyAUy26V0OVM8dM1YDTlvbO6f0x6TgRmCD9KltH8zlmEjWZwzp8LqKcguD6Wljz5QsvzCKH53InhOiBar4l1YyXYuRdSzXuY%2BfHPxaWGXxvehKQzDb259L3eVjeZltsXYeXx%2BkaK/t4dHBse47ex9kqROfuGtq/gAHlOFs053dq0gbWOuUER7N%2Bb32jUkh2ySU1kgxvZvmHPw7thjv773edpAUbx0s9u8m1NHAns50WAFBOQaROQ18tQpgS0t9y10Agdq0ZMg8G15AIcw8dAQBghYd4c%2B0CtZ8SsR0rsJ0p1ACc1gDQCuQICkwphSdycGtAhNhms6cQ0GdaCf82d119xkBjld4icURICCAaUcds0%2BA6BBc/UIBH1W0JcxcmNpCf0/0AMmM5dBAFcIMddMBoNYMxA1dANNcuNbckNMNHBsMEM/tVB8NIRTdBBzcyMKMqM9Qbc6MS4HdeAndMgXcoQ3ceMmDPdBNhNRNxN/dgdECJBg9G1UClMMDI9jB1MbA494AE9%2BgENPhGUM9LALMDsrMt5c8utm9nBnNi9B89BS9R8wtK9%2Bg0tyjgtMte8YtegC8BAu80s8iBhFgG8x9h9mi2iaix8ctJ861Ec8CUdOBF8gCQCwDKDIRqCIA6tt9N098WtD9MB2txgutSMz8QAzBvt6D/ALVjU3V6CSRVtithifUX8A1Fiet/ABt/AbUUh%2BtJB%2BtTUhtagCtAhkcvVOBGDd1Edi0TjPizi38tgWMshnBJAgA%3D)

## Links

- [source code](../../../../conceptrodon/descend/descend/pagelivore/bind.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/bind.test.hpp)
