<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::InsertTypes`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-insert-types">To Index</a></p>

## Description

`Omennivore::InsertTypes` accepts a list of `std::index_sequence`, which indicates distances between adjacent indices.
Its first layer accepts a list of elements and returns a function.
When invoked, the function inserts the elements to its argument list according to the `std::index_sequence`s.
The result will be stored inside `Capsule`.

<pre><code>   std::make_index_sequence&lt;I<sub>0</sub>&gt;,
   std::make_index_sequence&lt;I<sub>1</sub>&gt;,
                    &vellip;
   std::make_index_sequence&lt;I<sub>n</sub>&gt;
-> E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>k</sub>
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>m</sub>
-> Capsule
   <
             Arg<sub>0</sub>,
             Arg<sub>1</sub>,
              &vellip;
       Arg<sub>I<sub>0</sub>-1</sub>, E<sub>0</sub>, Arg<sub>I<sub>0</sub></sub>,
       Arg<sub>I<sub>1</sub>-1</sub>, E<sub>1</sub>, Arg<sub>I<sub>1</sub></sub>,
              &vellip;
       Arg<sub>I<sub>n</sub>-1</sub>, E<sub>n</sub>, Arg<sub>I<sub>n</sub></sub>,
              &vellip;
             Arg<sub>m</sub>
   ></code></pre>

## Type Signature

```Haskell
InsertTypes
 :: typename...
 -> typename...
 -> template<typename...>
```

## Structure

```C++
template<typename...>
struct InsertTypes
{
    template<typename...>
    alias Mold
    {
        template<typename...>
        alias Mold = RESULT;
    };
};
```

## Examples

We will insert `Vay<-1>, Vay<-3>, Vay<-5>` to indices `1, 2, 3` of `Vay<0>, Vay<2>, Vay<4>`.
To do so, we will calculate the distance from one index to its immediate next.
We will keep the first index, `1`, since it represents how many elements we must pass to reach the first target position.

<pre><code>   1, 2, 3
-> std::make_index_sequence&lt;1&gt;,
   std::make_index_sequence&lt;2-1&gt;,
   std::make_index_sequence&lt;3-2&gt;</code></pre>

We will pass these sequences to `InsertTypes`.

```C++

/**** Vay ****/
template<auto I>
struct Vay
{ static constexpr auto value {I}; };

/**** Capsule ****/
template<typename...>
struct Capsule;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = InsertTypes
<
    std::make_index_sequence<1>,
    std::make_index_sequence<2-1>,
    std::make_index_sequence<3-2>
>
::Mold<Vay<-1>, Vay<-3>, Vay<-5>>
::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult = Capsule<Vay<0>, Vay<-1>, Vay<2>, Vay<-3>, Vay<4>, Vay<-5>>;

/**** Result ****/
using Result = Metafunction<Vay<0>, Vay<2>, Vay<4>>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
```

## Implementation

The implementation of `InsertTypes` is similar to that of `Typelivore::Inject`. However, since now we must deal with a variadic number of indices, we will perform recursion over the total number of the `std::index_sequence`s.

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
struct InsertTypes {};

/**** Base Case ****/
template<auto...I>
struct InsertTypes<std::index_sequence<I...>>
{
    template<typename NewElement, typename...>
    struct ProtoMold
    {
        template
        <
            // We use `Prefix<I>...` to enumerate `FrontTargets`.
            Prefix<I>...FrontTargets,
            typename...BackTargets
        >
        static consteval auto idyl()
        -> Capsule
        <
            FrontTargets...,
            NewElement,
            BackTargets...
        >;

        template<typename...Agreements>
        using Mold = decltype(idyl<Agreements...>());
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

template<auto...I, auto...J>
struct InsertTypes<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template<typename FirstNewElement, typename SecondNewElement, typename...>
    struct ProtoMold
    {
        template
        <
            // We use `Prefix<I>...` to enumerate `FrontTargets`.
            Prefix<I>...FrontTargets,
            // We use `Prefix<J>...` to go across the distance
            // between two targets.
            Prefix<J>...MiddleTargets,
            typename...BackTargets
        >
        static consteval auto idyl()
        -> Capsule
        <
            FrontTargets...,
            FirstNewElement,
            MiddleTargets...,
            SecondNewElement,
            BackTargets...
        >;

        template<typename...Agreements>
        using Mold = decltype(idyl<Agreements...>());
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

/**** Recursive Case ****/
template<auto...I, auto...J, typename...OtherSequences>
struct InsertTypes<std::index_sequence<I...>, std::index_sequence<J...>, OtherSequences...>
{
    template<typename FirstNewElement, typename SecondNewElement, typename...OtherNewElements>
    struct ProtoMold
    {
        template
        <
            // We use `Prefix<I>...` to enumerate `FrontTargets`.
            Prefix<I>...FrontTargets,
            // We use `Prefix<J>...` to go across the distance
            // between two targets.
            Prefix<J>...MiddleTargets,
            typename...BackTargets
        >
        static consteval auto idyl()
        -> ExtendFront
        <
            typename InsertTypes<OtherSequences...>
            ::template Mold<OtherNewElements...>
            ::template Mold<BackTargets...>
        >
        ::template Mold
        <
            FrontTargets...,
            FirstNewElement,
            MiddleTargets...,
            SecondNewElement
        >;

        template<typename...Agreements>
        using Mold = decltype(idyl<Agreements...>());
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxBIAbACcpAAOqAqETgwe3r56KWmOAkEh4SxRMVwJtpj2BQxCBEzEBFk%2BflxVNRn1jQRFYZHRcYkKDU0tOe0jPX0lZUMAlLaoXsTI7BwA9ABUO7t7%2BwdbGyYaAILbuwDUACKYSa6MyHiYCpd7x2cXh9/7H6cn/zMAGZgshvFhLiYgW4vI5aIQAJ5Q7AA8wghhgrwQqFuZAjdBYKjI1GfPaXZTETA0VRvXZ/AiYFhJAwMnEEBH3ZhsUiXNIAL0wAH0CMSzmgMXcCOTKdTIUDrpcCMQvJgoVYzgCvltLm4mEkFF56LSdvTGcymKzoezOaxMAA6B2i04jZUOHV6g30NUk85k7CqBkMdAAMWIsmNRwBDKZLNVVo5jFtDrtTpdXjd/sDIbDgkhAHYrHnrt6NWdo%2BbLW5y7G2QmufbHUDsJcwUwFK8PIImMFojzrYm2MnsPQ2IIFKmlempZnXKHZDjOw0e8QccPGYwCApk8Sm6iCwDLofFWaa/GbYOHaFMAB3NejzdOo%2BXLxpIyXACynnQcoVi%2B7IRXaEr1vEcNy3B0eTvMDt13IF1X%2BIsS3%2BUkflQ95NTJABJGN1y7WoIz%2BLU0J%2BP4oxPC04yrOsk0bFEzjTN1MIYJQmgAFQTV4TH3RC4J9LVLgsNtMHdJQCLImMKJxJhYVQZNMInV0pSYliCHY%2B5x2hfEQBAYIsFUQUlAARxVCUcUwmCUV3DV9zOJ9q0ks8B2E4CoMEPtqIvFMrNOJ8GKlClUCIT9aHQA8jy4%2BCnzs8jWVsqLDxxML4qfDYNkuAB1YSX2EkxYg0CkqTwVQzORbc8sVVBLkYHxogoyE8rnQRWMaYBMAfPKUzi5KjwK6kSqbZNGtUlq2oUUgku6xUPIbO1BOQABrZriFah8uqix9kqmRxkBbAQRkwAA3MRLmkohLjwdAEVoCB5gmp8AFpkXdfVDVVNan0S97kqGpaVvAu1xq%2B%2BKXNAty7uSubFpGzdtyBuVLPg8HD3syt%2B3rZNTmASlcIfbzupfYJgA/L8f0uLAwX7CALqunFMex%2B9/uRG7bt4tauOLVnkJ8o8UcotGaLtOnMBxjS6O5w8CbfYLvyhBUAqCr9aax4WGYspD2fVssYso07ZIdTCeV15MACkFKnS5lOiVSOJxLSdKDTB9KMky1jMiyeTt3THYMzBjMeSjjbV7yIom3na3PYTgzwYgRhBnH3Ijy4hEwcV0Dj%2B8E6ctW1r86VAtQaWJpDuGw7hz7xcm1KMqy0TcvymUiv67Ayo0CqqoYGriDquufuh8cOqRqLesb6F5IGh1e%2BW0bAYr7qq8y59a7y4fiuhU3x5TcqzuASqmGQMN20VBBhPwKZTLhlK0qiAhr2FhhFWvSrRj%2BzrZ%2BSlecXX5uHXfC70HoX609B52WmsmSGgDVpvwSnjTaDRtq7WYgyI6tAToyXOpda6t04aPSbM9T0b0oFyjcMAo8k8X4QRIYeKOMcCDpw3DPSaR5f4EgAX3ZMDDGFJxTgINON5XIEA4Yw8BbDHRl1gojEu2tw5ZwdELEWG14qSyJtLUm5NaCU2prQJW9NoK0WZkhD6PEJEVzDo5dGsjlbyJgRLV8yiSayzzgrEK2iVa6K8gjPcHNjH8QAEopxWGkA6wldSiXQlrCSlYjb60NjJE2mdzF2gAPIEGPsQZOfsJSiwBLnS2bEbaaQIOgbSXsna%2BxdpRcytEPaFOKQ7UpGTXZr3dpcZJqT0nlMZsHGyJipFmNtJcahsc%2BGgwEVNROydU50LcmMmRSSUnRCmbjMWvlJxunlgXRWbNundVLoQ8unDLjzxrjlZeDdV5uDHt/TerczrVTYF3Bk9UNBkNGnXV%2BByP6j1KhPHMw0p6bkEZXNKC9spPM%2BW4L%2BLc247xOvvVIrx5lkzwGfV2F8jxV2vrfRgD8n5sModKQq5zIU/z/qw/5Y18X808sI8lg8FFRS2ngHa4p9rINQWdTRN1B44ObDOIMQ06XQkpdNC2zErZqReDiVp0R2n%2B06cszh2lebE2cdCaVxBFnyvxUq7WKrQrQhpeQ9xgqFXxR1RE4ShcxHELRVQ35ED/qAu6oM2hwz474uYf/TADr2H4omTwxZJrNaENMVRCOGNLEM3pU%2BJRerVEp3UQmKmGCXEiwsvozmhivE%2Bmiha6RCS5FRusYvQmcaHHrMLtCQtbidyIyMXxYivwMJXH9KwZkwkwm%2BkbXSH0aJQTghytCcUawkhLIbVcAAakwBEYlwkVh1mgy52TVlSinUiayFheRwKZQg/aqgkjEHZZVZBKp8wWHkkY/M2bSxdp2Hg16s7TihqpTNM2bpdQvS9JzZtd73xtSYFQLwGJ8KdufaA2Ry0slnFjX%2BhogHgMZFJrk626lURCpzjUkALAmDzSFCUn2DTKJcGRICu22HcOCnw87f2OIzD3WI02UjmHyN4bqQR8pOIgT3TME6J02lK1uDXTiejJHLhCehPdIEonxNuHugAVh3GLfjisq2QaDt4skQgvBJDyJgdAfjPRSk7bGrTOnUh6YM4aKUDiP34JxDJjQ0np3CYY9gHkMmeOMbE85iTUmvMyckE5pEEmFOwQ8Te3xLwrOPtjZZ9RpNYMAaAw4DI9mfNuEc/59Lnm3PeeC24QLYXg38VYi8IzPb6LbuQIKNsKkIB2wULaGrGk3Cmd0/pqL6ieRxZFE2Fm8EOCLFoJwOTvA/AcC0KQVAnBiGWGsLyZYqwcrAh4KQAgmhBuLHmiAOTkg7QaAABxmDMPEeIXA5OHYO1wPMeZpDDY4JIXgLAJAaA0KQcbk3pscF4AoEAb31sTcG6QOAsAYCIBAMsAgSRYTkEoGgJkdAFm2k4KoA7sR7qxEkJcYAyAdpSDtGYXgenCAkAunofgggRBiHYFIGQghFAqHUID0guh2jXi7kkTgPAhsjbGxtqbnBEmwmh1KVAVBLio/R5j7HuPLj47MJcCAHgEf0EPWiLg8xeAA60IsCASB4dJER2QCgEADdG5AMAKQZg%2BB0AZDHSgER%2BcRGCI0BEXPeDO%2BYMQBEiSIjaBTgD1b8P7yJIYLQN3zOsARC8MAXUtBaC/e4LwLA2GjDiEj9HAPeAgmJ8m47fxDJ3fkEENUfn8IIhd29x4LA/OlR4Ge0n0gQTiARHM7cVPwB4RGA24sKgBhgAKAnc8a8iTORF4p8IUQ4hacT4Z2ofnrP9CGGMNYaw%2Bg8ARF%2B5ARYqBR0ZET/dfEstTBzcsGYT7zfiAXRePARYdgs/OAgK4cYbRSCBB7LMQY7Q8jpAEC/3IqQv%2BDAMwAw5QHQD%2BdQowzQngrQeg9%2BKWAg3QTQIBpQX%2BtgUB/%2BkwUBKBcwGuSwKwawEgPOHAo272/OX2EuaOGOWOOOeOe2CuEAuAJOauK2mua2Peiwx8TAWAMQN0pA22kgQIdo8QQIt2GgkgZgkgeUGgcmlQ92j2pAz2QIXAdosQFQB28QV2sQu252IhsQZBzOX2P2f27BgOuuYOeuEOwuMOJuZuquoQyOHAjQLAB0eY90TALYBgb4XA8QdoKhee%2BARAV%2BRS7QE%2BVO0%2B0gs%2BSg8%2BzOug1u7Oeo7uxBpBH2vAX2QuUOsIlwYulBUuWOrY3hvh/hiuyuhuqukIwIZgbB2uQOlhdhvYthqAKugwBRluZ2b2NA6i0Qv2EAjuzOnuruReAx3uvu/uDgReweG4oe4e/OUeMeceCeReKey%2B6ek2%2BAlIKWOe/O%2BeyAsI6wq2wQDI92k25eleCI1e6wk2deDeq2zereSg7eKxhMPefA/eg%2Bw%2Bo%2BjA4%2Bsg4RNOkRsgc%2BTOk2cRS%2B3eJ%2BVglg6%2Bm%2Bt%2BU2e%2Be0nAh%2BhSx%2Bq%2BZ%2BF%2B0QwRN%2B2%2B4BCBfgT%2BQYmBb%2BQYOBaBP%2BtQBJpJGQxJYB8BtQSB0B2Qr%2BNJXQ2BH%2BoBcBGBMBEw6B0wrJqB5Qd%2Bi2hBeB92KR5BnAuR1Bnhy%2BcuRR%2B2iuTBQRFRyh1RHBpAXBPBlAxBChShvh4heYcm8QN2QIEhUhkg7QqRAu32tgJhNR5h8AlhkOIusOpuTRZRSObAnAzh0uLACgB0O0B0PhdosYIwROgRpOIRdOk%2B1OEg/x9O0RQJOgIAQIpACRnOSeyRfOhhgu1hou4uqg3pvp/pgZwZUoSurpRuSpQIKpZhwO%2Bu5Zquzp9RMQfpOmgoAZ8QgoJZgo%2BZkRtu3RDuTuLu3uQxQ5PufuAeExTRIeYeEeaxmA0eseYgixjeyxaelxyememxN%2BzOOxexRehxpezOpxruFxteV%2BNxvAdxbejITx3eNZfeTAA%2BQ%2BN4nx42q2YRU%2BfxkZgJC%2BSZoJK%2Bp%2BNg5eW%2BfBu%2BtQieGwWk4J1g5%2BaRl%2B1%2BIFd%2B1QEBLg%2BJnJr%2B7%2BxQbJ3%2BgBZJ6FAB%2BQlJvJuB2JtJHJDJcByFOJdJVJ7JPQBJUwyBxFX%2BApBBNOGZBhn24pPZlwPpfplw7ZQZFEIw8pYZLBypWuqp6pgwfB8hT2IAJ2doQIQIcmF2Zpr2yleYsQB2nFaRnAxh/2qpAhcmwh12eYr2B2kgZ2XAR2Zg%2Bh92QImZXFVptpxBhOullpklZhiwzeaQzgkgQAA%3D%3D)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/omennivore/insert_types/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/omennivore/insert_types.hpp)
- [Unit test](../../../../tests/unit/metafunctions/omennivore/insert_types.test.hpp)
