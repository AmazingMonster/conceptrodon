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

The index pack within each `std::index_sequence` will be wrapped into `Prefix` to produce concept packs.
Then, we expand the concept packs alongside the arguments to reach the desired positions.

```C++
template<typename, auto>
concept Prefix = true;
```

`Capsule` is used to store the result. We declare `Capsule` as follows.

```C++
template<typename...>
struct Capsule;
```

Here is a simplified version of the implementation.

Note that we wrap the elements inside `std::type_identity`.
This ensures we can create objects to invoke the ordinary function.

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
        template<typename...BackArgs>
        static consteval auto idyl
        (
            // Expand `Prefix<I>` to reach the desired position.
            Prefix<I> auto...front_args,
            // Collect the rest arguments.
            BackArgs...
        )
        -> Capsule
        <
            typename decltype(front_args)::type...,
            NewElement,
            typename BackArgs::type...
        >;

        template<typename...Agreements>
        using Mold = decltype(idyl(std::type_identity<Agreements>{}...));
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
        template<typename...BackArgs>
        static consteval auto idyl
        (
            // Expand `Prefix<I>` to reach the position for the first new element.
            Prefix<I> auto...front_args,
            // Expand `Prefix<J>` to reach the position for the second new element.
            Prefix<J> auto...middle_args,
            // Collect the rest arguments.
            BackArgs...
        )
        -> Capsule
        <
            typename decltype(front_args)::type...,
            FirstNewElement,
            typename decltype(middle_args)::type...,
            SecondNewElement,
            typename BackArgs::type...
        >;

        template<typename...Agreements>
        using Mold = decltype(idyl(std::type_identity<Agreements>{}...));
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
        template<typename...BackArgs>
        static consteval auto idyl
        (
            // Expand `Prefix<I>` to reach the position for the first new element.
            Prefix<I> auto...front_args,
            // Expand `Prefix<J>` to reach the position for the second new element.
            Prefix<J> auto...middle_args,
            // Collect the rest arguments.
            BackArgs...
        )
        -> ExtendFront
        <
            decltype
            (
                InsertTypes<OtherSequences...>
                ::template Mold<OtherNewElements...>
                ::idyl(BackArgs{}...)
            )
        >
        ::template Mold
        <
            typename decltype(front_args)::type...,
            FirstNewElement,
            typename decltype(middle_args)::type...,
            SecondNewElement
        >;

        template<typename...Agreements>
        using Mold = decltype(idyl(std::type_identity<Agreements>{}...));
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxBIA7GakAA6oCoRODB7evnrJqY4CQSHhLFExXPG2mPb5DEIETMQEmT5%2BXJXV6XUNBIVhkdFxCQr1jc3ZbcPdvcWlgwCUtqhexMjsHAD0AFTbO7t7%2B5vrJhoAgls7ANQAIpiJrozIeJgKF7tHp%2BcHX3vvJ8d/ZgAzMFkN4sBcTIC3F5HLRCABPSHYf7/T6bC7KYiYGiqV47X4ETAsRIGQmQtwEeF3ZhsUgXJgw1BI/5oBirRIEDFYnEQwFXC4EYheTCQqynVG7C5uJiJBReeh47YEokkphkqGU6msTAAOj1zNOwyFDilMrl9FFKI%2BkuwqkJDHQADFiLJFYd/oTiaSRRqqYxtXqdQaTkavCbbfanS7BBDYlZYldLeLTp7VeqKSrveTNf62IGkRdQUwFC8PIImMFonSczTdXrsPQ2IIFMHQ%2BG7a5nbJyWX6pXiOSG0TGAQFPnAciJyi4/8LnOBZm1T6KX7a4HQpgAO5Dpuj4Pzi5eVJGC4AWU86F5/N7FZCA6hG%2B3jZHY71dJ3L/Hk7FfwTSb%2B1rfEBbwSpcACSXrDuWNRur8aLAd8vweou6Y1gG%2BpToagphpyYEMEojQACp%2Bi8Jgzn%2BgI/qB2wXBYxaYKaSiwchXpLuSDJEIGYGtthJp4QRBDEXcLZQsM6AgCAwRYKoAD6SgAI7Cmyy5gV%2BwZkT%2BB6plmvpamwFyPh%2BgjVqu6FBphJwHm2nKYqgRDnrQ6CzvOGnOQec7aWxum5nWOp0cgADWJzEMAInIqc7nzpMjjIIWAjDJgABuYj0oyFx4Og8K0G57kQDlkVzus6wXLaiSGJeJgAGwaJi2J4Ko5LcVO1UCqgFxYkwyAIAKCAMVgqRYpeuRpAIQYRQVB61TijUFhxqCBlQ0YEDJDShaQ%2BUFUVUqeNUPUMViwz0iFPifhtkX%2BUFIWvmNlkFXMZ0XAAtAW0qyvKIrjZF5IPVppn6VgoI5tQS0rVdcwSTmgbrZ9E0GVuRkENDt2wwKf0MRdwWhRDfr5jDB7MpRVrI%2B5nmoWjgYnMAWJQXuFkTUewTAGeF5XhcAO0EDGVZRAYnY3cMkZSOCLkpT1O7mFrkJoGcz3YTMNkYmcsAcTpPLmheZ6qLmA0xLMMMyeDkVXyXJ2aghsi1T2vi2pSsK/%2BLFpsuc1cXSzt6gAUjxxq4fh0SCSR5K85JDqYLJClKasjVfnSQdSaHcmYIpDzLu7Nvhb%2Bmnzqr2Zoxcjp4MQwyGc%2Bxmo3pDFCJgrLoMXNMmeXakw9ZJv2ReOWuXjWcoWr5N6hjV37gV0V4LFrIJcltCpUQ6WZdlndznl8/uVtpXlRC1VTfVM3NRorXtZgnXdQQvUXMNMH8MQe0XDQheciEm4XFUNM3Sjc6bw1UJNdgU/zXqi2yKDNaP15wr1UGVB068arci3lCT2O894dS6lfM%2B6Rr4kCvkoauFx76PxLgQF%2Br937kjgd/N2OoWAZXQPQQBCgkavwuFtTIu1j77WeJyVaJ1mwEJRv3UKuNiYHnukvZ6E5TRvQtEvb6S9frlzZlXDmfpgYANWgocGIBIZvmAXOfOt9a67joa/dWfV5FAwoegKhmAaFqI0TqAxKNK7Vz0SOOxsMjG0U6pdLG6icb6kkVOW2S9s7eTXJrS2OtB6RX1kzQ2rN2ac1njzAg4lvH80FoIYWUItbhKnORK40tZaZznHbAJKtu45wbqEsWL4ImHmPNElmkJ%2BS2Vbo5C2VSuEYW/NORWVFAI0QAEpV2WKkRKDFpRMRAimMpUIyFgVdoyQM7t64%2BUDAAeRYcQSuSdlK6xDLxH2AkhLPEDkkiSccw6JwjipaOFxY4hwudsyOsCbnrN6psy5ydrrqRnDDIJK5ZE6KLvDPByzawXAcQIGuwK65lxWXqV50QnHNhqc3ZpZs27yx%2BQIrurEyYVL8h4zGuyJrD1HvFQkE8f4zyyg9Re2LIqgPARVDe0CP5uC/lVXe09EFHxPiggQaDL4sOvgXQ6OCn67m4bDIhn9ZoLL/iDFRLiJqMrXpymVbgSGcoQQfJBwr%2BUMEFRgqukLsFblwc/LRXI6pspIT/QMZiLE0OVZtYqTCq6cmFQddhx1rZWt4V8peQj6VPQLBGTsS0HpSJDQeOJforV0voQefifsjkiTcAi95jzniNxjQVCG3dmatKhJmpFo5c1JvnGchJAbJZ5L1MG%2BhjaCo1IPAW3FDFzZ%2BLcFatxca7hKMEFYvmvkXWRUBQQMtY6Sa537ZgCAjrqEqOsT42xVqIUOjLVG/xvSQ1/KMRTMJ4tW3ziiUWo2/I50QC5rQRJyScwCywOkykbSrbVJyfGetOoZb/nxhRXdWlpn/LhTqLJx66anrqee1maLzaZKPZ%2BTp9t/1E3gghOCNpVCsBJAxSZZwEI/CJuYYEbIwQMXJKydktN07UXRAANSYPCZiUyO3sTShyrC3sLgMcROKOMtz6gxTivhQkYDL5zQuBPYUsYLDcX/bGHpqHJSvXNLh/EDsdLAZCeZdOzcVPvXtn09Ep5MD1CoF4NkME8P7t7qBgeFkz0mbMxZhwqDGkXBTURAO4ooQ5SDiwJgAVLHnITtm8kXAkQuP84F4L9zQtXPJGYR6EWJxRdOSAALQWBZxfDsnckgJHpmHUhZCScG3A8fJMlyL3HGOVcBNVirUJHoAFYCbp1K23TJV0ba7rROCrwiRciYHQIM80nI8NnqEANobI3njyk5O5/TFooSNbcBoBrtWmspewHSVbRXUs1cRE1%2BrB3VuSA20dtwLW2uGfw5cUb83mMnDPQ9jmrMnNMHM5Z9I5JVvrdO5ttw%2B2duHfJOd/xXTkx3ZooRNhT3SUrRLH7O9EkFDakR%2BSV7iN%2BuDZSMNrHSICn/A4AsWgnBmu8D8BwLQpBUCcB7ZYawtylgrHI0CHgpACCaBJwsAKIBmuSB1BoAAHGYMwABOcXXBmsi%2BF%2BUWI0gyccEkLwFgEgNAaFIFTmndOOC8AUCATXXPqck9IHAWAMBEAgCWAQRIMJyCUDQMSOgiLtScFUMLyqj1KqSAuMAZAsUpA6jMLwYbhASAZT0PwQQIgxDsCkDIQQigVDqBN6QXQbRNzEBlJwHgpPyeU%2B57TzgqyYR285KgKgFwPde5937gPFwg9mAuBADwzv6CX2I1wOYvBjdaAWBAJATvEgu7IBQCAw/R8gGAFIBINAObRANxACIReIjBAaPCXPvA1/MGIPCVZERtAeq36QJ3u5VkMFoJvtPWAIheGANKWgtADfcF4FgALRhxA34Lh6vAoyX806hxDKEgn7BCEhK405wgRDZ574eBYBF6Ch4Bq6v6kCjLEARB443Af7ABwhGDc4LBUAGChR0ZPCbirLUgn7R7CCiDiAJ5UHJ5qBF4Z76CGDGDWDWD6B4ARAG6QALCoAcjpAv6PRiSNKmCM6WBmA65oHECCw8EQALB2C/7OAQCuBjCtCkCBCVgzADBtAGpqE5ApAjQMDTD9BlDtBKG1AjBNCeAtB6CKGuYCBdCNAmElA6G2BWH6ETBWEuGzDd6LDLCrASD54cAU5a5F667V6e7e6%2B7%2B6B6C7N4QC4Dh6d7s496c74ELC9RMBYAxDyGkB86SCAg6ji6AgK4aCSBmCSDVQaDNaVTi76CcAq6kBq6AhcA6iVRcCVTC7i5y6VQC7S4lGVRhFp66766G7pEm4D6W6D7W5l727j6T4d6hBu4cANAsCJSxCPRMCFgGAnhcDi46htGAH4BEAyHiRtBUGx60HSD0FKCMFp66AJBZ456v7BGhHa68C66l624wgXCV6RG16%2B5Fh7EHFHEt5t4j4d4QhAhmBpF96m4zGLFVgLGoDt4DDAkz5S6a7z6EiFyUAr5p474b4n5El74H5H4OAn5n4jgX5X5F63736P7P4n7v6sFf4074BYiub/5F5AHIAwhrAc5gFVBF5QEwHwhwFrA06IHIEc5oEYFKBYFsmMz4F8BEEKAkFbjkGMCUGyBXHx43GyAMGp406PEsF4FiFWCWCcHcHwB8ECHxScDCFJKiHsESFSHRBnHPB2nmEOF%2BAqEOieEaEOg%2BFuF6E2HjBJCGE1ChlmH2E1BOHWFZDqHxmdDeFaGmF2EeERkpnplFCZl%2BEKAs6BF%2BFK7vHhGcAAnRE7GsGN6glC4t5JGnHQmtFwkZGkBZE5GUDBFNEtEHHlGxDNbi6xCxCAgVFVGSBtAfHF5662DjHwlTHwAzE27l4O4T6omQmu5sCcBrF14sAKCJSxSJT7E6jejDCh4nER7nGJ7UFx4SCGlJ53Emk6AgCAikDPGJBb5vGF4jEl5zEV5V6qB7kHlHknlnmcit4bmj4tmAhtmTFm5D5QUd5rlIkxCHmDYyTHni4yTgUyRAU3F0C4lL4Ek06knX4c5kXknH4oHUmCC0nX4cmYB34P5iDMkoGsmf5Slv4/7cnelp58kCmgGCAilp5ikb6SkIEyGym8DymYFEjKl4HwWEFMDEGkHalU4c6XE0EGk3nGlMGvnmlsHiE2BQFyH2k1Av7rC8yWnWCSGfHSGyE%2BmpnKGqE5n%2BAhkZmuFmHhnJkGF5DpCxl2FPx%2BmJlBnOWWFTCeW%2BHuHdBhV5l9BeVBH%2BGs5JVlk/k66Vn4UXD7mHmSZgVLiHSJGXkpGtm97tmdkDB5FK69kgAS46iAiAjNYy6Tka4NWxBdHDEZWzkG5G7tkFHNbFHy4a7C6SBS5cCi5mBDFK6AjpWfGcBlWTHBEh6dVzWzkLkLBoGpDOCSBAA%3D%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/omennivore/insert_types/implementation.hpp)
- [Source code](../../../../conceptrodon/omennivore/insert_types.hpp)
- [Unit test](../../../../tests/unit/metafunctions/omennivore/insert_types.test.hpp)
