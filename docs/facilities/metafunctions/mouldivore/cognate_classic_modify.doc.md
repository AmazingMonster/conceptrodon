<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::CognateClassicModify`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-cognate-classic-modify">To Index</a></p>

## Description

`Mouldivore::CognateClassicModify` accepts an operation.
Its first layer accepts a transformation.
Its second layer accepts a list of indices in ascending order, which indicates positions in a list, and returns a function.
When invoked, the function transforms its arguments at positions indicated by the index list using the transformation. Then, The function instantiates the operation with the modified argument list.

<pre><code>   Oper
-> Transf
-> I<sub>0</sub>, I<sub>1</sub>, ..., I<sub>n</sub>
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>m</sub>
-> Oper
   <
                    Arg<sub>0</sub>,
                    Arg<sub>1</sub>,
                     &vellip;
       Arg<sub>I<sub>0</sub>-1</sub>, Transf&lt;Arg<sub>I<sub>0</sub></sub>&gt;::type, Arg<sub>I<sub>0</sub>+1</sub>,
       Arg<sub>I<sub>1</sub>-1</sub>, Transf&lt;Arg<sub>I<sub>1</sub></sub>&gt;::type, Arg<sub>I<sub>1</sub>+1</sub>,
                     &vellip;
       Arg<sub>I<sub>n</sub>-1</sub>, Transf&lt;Arg<sub>I<sub>n</sub></sub>&gt;::type, Arg<sub>I<sub>n</sub>+1</sub>,
                     &vellip;
                    Arg<sub>m</sub>
   ></code></pre>

## Type Signature

```Haskell
CognateClassicRemove
 :: template<typename...> class...
 -> template<typename...> class...
 -> auto...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct CognateClassicRemove
{
    template<template<typename...> class>
    alias Road
    {
        template<auto...>
        alias Page
        {
            template<typename...>
            alias Mold = RESULT;
        };
    };
};
```

## Examples

We will apply `UnaryMinus` to elements of indices `1, 3, 5` from `Vay<0>, Vay<1>, Vay<2>, Vay<3>, Vay<4>, Vay<5>` and invoke `Operation` with the result.

```C++
template<auto I>
struct Vay
{ static constexpr auto value {I}; };

template<typename Vay>
struct UnaryMinus
{
    using type = Vay<-Vay::value>;
};

template<typename...>
struct Operation;

template<typename...Args>
using Metafunction = CognateClassicModify<Operation>
::Road<UnaryMinus>
::Page<1, 3, 5>
::Mold<Args...>;

using SupposedResult = Operation<Vay<0>, Vay<-1>, Vay<2>, Vay<-3>, Vay<4>, Vay<-5>>;

using Result = Metafunction<Vay<0>, Vay<1>, Vay<2>, Vay<3>, Vay<4>, Vay<5>>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will implement `CognateClassicModify` by combining `Pagelivore::CognateSegment` and `Omennivore::ModifyTypes`.

When provided with a list of ascending indices, `Pagelivore::CognateSegment` will find the differences between the adjacent indices.

<pre><code>   I<sub>0</sub>, I<sub>1</sub>, ..., I<sub>i-1</sub>, I<sub>i</sub>, ..., I<sub>n-1</sub>, I<sub>n</sub>
-> I<sub>0</sub>, I<sub>1</sub>-I<sub>0</sub>, ..., I<sub>i</sub>-I<sub>i-1</sub>, ..., I<sub>n</sub>-I<sub>n-1</sub></code></pre>

Then, we will make `std::index_sequence` of each difference by passing the following helper class template to `Pagelivore::CognateSegment` as the operation.

```C++
template<size_t I, size_t...J>
using Detail_t = Capsule
<std::make_index_sequence<I>, std::make_index_sequence<J-1>...>;
```

We will keep the first index, <code>I<sub>0</sub></code>, since it represents how many elements we must pass to reach the first target position.
We subtract an additional one from the rest since we only need the number of elements separating two targets.

<pre><code>   I<sub>0</sub>, I<sub>1</sub>-I<sub>0</sub>, ..., I<sub>i</sub>-I<sub>i-1</sub>, ..., I<sub>n</sub>-I<sub>n-1</sub>
-> Capsule
   <
       std::index_sequence&lt;0, 1, ..., I<sub>0</sub>&gt;,
       std::index_sequence&lt;0, 1, ..., I<sub>1</sub>-I<sub>0</sub>&gt;,
                    &vellip;
       std::index_sequence&lt;0, 1, ..., I<sub>i</sub>-I<sub>i-1</sub>&gt;,
                    &vellip;
       std::index_sequence&lt;0, 1, ..., I<sub>n</sub>-I<sub>n-1</sub>&gt;
   ></code></pre>

`Capsule` is a vessel holding the results. It can be declared as follows:

```C++
template<typename...>
struct Capsule;
```

Finally, we will transfer the `std::index_sequence`s and relevant arguments to `Pagelivore::CognateSegment`.

We will use `Send` to connect operations.

```C++
template<typename...>
struct Send {};

template<template<typename...> class Container, typename...Elements>
struct Send<Container<Elements...>>
{
    template<template<typename...> class Operation>
    struct Detail
    {
        using type = Operation<Elements...>;
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};
```

Here is the entire implementation.

```C++
template<template<typename...> class Operation>
struct CognateClassicModify
{
    template<template<typename...> class Hormone>
    struct ProtoRoad
    {
        template<size_t I, size_t...J>
        using Detail_t = Capsule<std::make_index_sequence<I>, std::make_index_sequence<J-1>...>;

        template<size_t...I>
        struct ProtoPage
        {
            template<typename...Elements>
            using Mold = Send
            <
                typename Send
                <
                    typename CognateSegment<Detail_t>
                    ::template Page<I...>
                >::template Road<ClassicModifyTypes>
                ::template Road<Hormone>
                ::template Mold<Elements...>
            >
            ::template Road<Operation>;
        };

        template<auto...Agreements>
        using Page = ProtoPage<Agreements...>;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};
```

[Run this snippet on Godbolt.](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCBmABxmpAAOqAqETgwe3r56KWmOAkEh4SxRMfGJdpgOGUIETMQEWT5%2BXLaY9gUMdQ0ERWGR0bEJtvWNzTltCmN9wQOlQxUAlLaoXsTI7BzmAMzByN5YANQmO25ejrSEAJ6n2CYaAIK7%2B4eYJ2fI0%2BhYVHcPzzMewYBy8x1ObgI1ySmAA%2BgRiExCAp/k8AQB6ABU2MxR2wqgIrgAYsRZEccZj0QDCSwkgZCRCoTDmGwAHTs1GPabELwOPEE4mkwQnADsVhFABFTlY0U8aXSmAyzvL6ZhGdDGKxMOzWXcjgcmAoFEcPIIkSEyEcmZq2ezsPQ2IIUTt7k9ubyCPzCQx0CTZBDTfU5sQIfbMI6CAodf8XQCTGKAUck1bwwqlZCNSztezQpgAO5hiPO12PZNHLxpIxHACynnQHwlJtk5uiENzBYdjEjOtIeM7TujsZ2MuekulcblqdVjKnirVZyYF1Qg%2Bw%2BoMRqOQkwAEcvIxNr3F0QdQA1Bp4JgRejFgHuvn472%2BoUECFb3f7%2BduM/EC9XzBRjkhxLeMRzLFU5whI9l3ZCxMGAYIGGCYAbyeMsKyQo5lCYYB3lORs3z3EFP1g%2BCGEQowANZXtv1/a8V3HNEx2HCdHixHFMOITAaFUckcSpSdaWnZVMy1Xs0gALzhF9YyeNAiKST1lE47iGytHl5xHDEKRNJgkgULx6F47F%2BMecD02tLN6LdBEPR0vSDI0li2OxE11zSZBa3wKhrgAFQ1Y0KRMszPwsrUrK5Gy%2BTcNy8A8jA8G8vyYWNED4ylZjZVY7SLENd43FyozKWpWd0ygnUAElOTvT1osNdzPIS3z/Ihb4QBAYIsFUWElHfIiIXK%2BiZNHUDk2CmdBIg4TmTCwDVwNDcAHkYURLpOTLaqONQIgACVUCYdBE2TVLULLUaSrVE7To%2BNxDqust0XRI4AHV3grXCADYNCUri8FUfq7mjT6rVQI5GB8aI5xOT6/UEHyGhwyMTE%2B3VLrupNvu4/6XR1GGCDh4gEYUUhbrRo4Hue948zoWg1MMBR%2BGIFgrQQd4QgJI54fBwQUdLUmk1CtgjnxhHidRtGBezVkcuQABrYXMERsWjqGtHpkVWL9QEaZMAANzEDmlyOPB0GuWgICWEmywAWj1fL7PoS3lZupWrtx%2BXu3ZUXeb5iWjiWiHVrOd27ja60vb5pNpbl%2BGFcox2kxjTSXZTCbzJE21WUeYBOPDLsUO9070KrWtaHrPCjiwA5rQgY3TYhLOc6LFdzYtjKC7ShjnlRsblXO9VpozvV5sohvMFzp01uTIvgCOXb9tUpSttQOeDrOUfx493Uh00pik9MvuFyXCrDyP9kACkqsimqYrirymuSlqCHQNqOswLqesIzZ%2BpXMSn5fn037dR3J/T8Z9BrAQTN3A%2BkJoESxXGuOqftlrqwEJPJMG1F47T2gdVGx0C5gT7snCE8dTrkxeuWJQUMvrKV%2BljbAgMNDA1BgwcGK0PoaDdjHRGyMSFlgxrQs4lVsbsk4QTWO4cI5kMptTWmDB6YkCZgQFmRw2aek5hGHmEcrTp3eESPAxBpjuwkXzKRFD2H8L%2BmcC%2BwjdRAyIEcYAIMmDIFJBuJR7x8Bqz6sne6j0ogEDzGPBgVo8wgzGITTREcLEQmsfQ9k1ZjboHoO7ImvDkymKprQGmCI6YM0Uco1RHMCZcwIJEn2OjNzVAEOgIxaT%2BY6J1FHFJJC0GnTVo4ZAms5GEj1jTKCRsTZmwtsnG2Lo7L6QdkQs4dSjiiIiZ7GZvt/YrQyBCPRBi8ZcJDiAMOMyEk/GSVwyixjSZLOQYHNwW45I1K2S6UOGoTloyaUc6MUz7htxIT3DMA9JbryLK0tClYZ4lzLjsRsldaDV1rrQeu2cx5N1mi3TuZYO4fKganEKsCGmzQQUaHUfy86tOnrPbBC9SRYP2rCxuedBo73SnvZyuJtrVHWGkHWeUCqBWKhiyCp9WTlRPsec%2BvY4HsgWu44gBEPz5w2rVI0sUGqJWamcVq7UAHv2AR%2Bb%2Bs1f7PzVZ1IBvUv5WJ/n7CVUqiJxyGngghPLe52u%2BTaSWQ83JIIDqslWyYMHkuXtgkmNq7pjSmc7fBd1TFvSodEwRAMOR2JBmDNgbCqFzNjkjDQZTSZRrcEIuJrIU2RkeWGx65DMnZMRHIvJzNWZvzUcUjRiyKnrMMVwwtV1w2ULTVm2JDCmGOI5i41Ixp3EVzwF4r%2BPj0l%2BIVoExgISwkvJmV2mNrJ9lJMwCk1tpDi3SKybI%2BRjMq0qJrUU4AJSM3iwqVc6ptSJ31J%2BY05x0cxGK1DQnT1V12kazktrXpBt7HQvNiQ0Zq4HyCn9MGhtPzXJ1QVfFJVD8zjipZpKzVlrwpaNDudEllLEPnI9SWDDOysMgohM859VqCN3QBcmTDGKax1hadM29sznwpJ7JBp1bqVmoLOE2zZz7tm7OY6uw55H2PMbOe6njlyqk%2BmDncnZGpGPvL3uLLF972QEonu%2BwuQL6Ol1UhCqFgyqXwppYipYrcRoJ13ixW1aZMUOtFVvOabl8Vwo3vnQFGEV5kqXivUznnaVxls5lRlQtoSxTEMoVASRCpBWgWVWat4r6bgQBcAgDs0X7wdUllzKWeR8iSlF2gMW4upVC13HLDneX2L45fQrnpiuiFK7FtZ%2BjpicgDUmYl1pVJCHSwQTLn5E4hfpSxL5/S%2BOCpBlen0DXbLNei213jHWCC9jm6vCB1mKEYT6%2BXAbGWstuHq9vMbnduU1cPnVtbM3KnXJmzqJD0QZWpaW61pI7WNkbdk%2BgXsz2DHhW67tqs1p/Vgq9GBwQ/dOPvbKxCAHFH7kwlabRhzmFsKfmm/d6po3GLjbC9pLcPp4uXaEo6yyyXrKNcqSTirBOqtfKZ9ilzuLjSBhbJaZzhZCVDQ2sT1ebgOfBlDP2TeMZtskyZ%2Bpp18Dh5cZQQwVpG0JQKyRDC3BkDX0g5nvtiHyzFei6C8ltuKLKtS9gTLynrPh7uepdpyjPW9O%2BfLqroMMK14eYRS55Hjl8cXYEldmBuW%2BUusQRag8f7oKshopea8C2%2BQC9fKh41X5zxx//OAkLO3pch6FTb11BvA6O6OCrtXdB/Va7Rr1jUqki8erTz%2BDPFHkVHXN%2BioPk3Q9jNt5pr3vOS/Eu2ur1Sbv1eBe94JpTHz29ZXYh4YAzBCRbmABGUngfydd/z2HxaeGeMlllagRfc4V8Rmzxbh1EkpJHAFaXvAkl4Q6liSTMv7vK87fs%2BTq/j/2QAGlqNJicS7j6L/hHAQDRhmDvTmDvQQC/7XRHBnyWYkLEoAASiSjA8Idee%2BSugivYZ8Vsv%2BwWmuDOF%2BQeeWWmiMOmxKWEOE/WrgMOWYEWSQJW8Onu9u4uCmYOOmaOqos84%2BZwY%2BFebBZmA4s0PBkMaBPwGB0kKmTkj05UPosUoBogwSYgCgIMUQRwSQdUmA9YxKaaqqr8GqRqaoPCHem%2BOiyuqWkhWAwS9OAeBcXy3%2Bnot%2BzhT%2BVhNONhjAj8eqRhhqIC/UeBWemuH%2BZ0l%2B9%2BUkOo/%2BOmZYQBXgIBxo4BHIkB0BsB8BiBwy2uxKghtAmB5c9e0mt%2B%2BBhBJuqmd0NeMIdB82U0sOkWLWrB2aQRYhimKOMRNGRGdGw%2BQhbgOR8IeO7cs%2Bn%2Bk0FOM0mc/eDuJMxKIKqkXhOBbgFBSOLRfuo4JBTw4WC%2BS%2BmAcq9UcG1w6%2B1Wm%2BVuoxO%2BxoBROBB%2BqWGxc42xsGd85%2B5hwxzOGmBeiCKBCiAg84Je3q/mfqIRny0CzhN%2BYkERP%2BrIz%2Byc2R5euRno5cdsEyn4qqLATAMscIfhH8Wq0aLouqbUSJKJsIaJKeoCVsXAy6/R/x4RD%2BpS7IOaJC3xRANBF02uwOamTmLOPOExzGUxdYVROC2uKKTGfJgal69BzG/JIaWiF6UGVxy%2BcEZ%2BAhUJfRbREpRw4hhIGOOE2q%2BWopys2Aqp7wAWZwNxt8jUSU/4ABpMep2GgubxjMHx5paMlpJGZw7JHBJeaM9p7RwUVpCO2B/R7pgxgaiWfKCx5p1BmOfm9JmOE%2B5m%2BWpubeqxjhlurJzxJxduIhlBg%2BzupK5cmCvqOG8x4xrpF2s%2BjKFIZZxkWk7EPk/4kY%2BxpZ5ZXKmULwIIbw10FwdANwXWG%2Bwx/SNJ1OtktYDAS8DAtwjEFgpe9QHSXS2sqgSQxAUeRwvSe4ooFglUu8ooCZTxnGZ4HuFxNOcgzAxA1wCSLCKIY5kxemeujYg5w5twZwVsO5bUS5nxxZm5Rxg8fOqWZxDhW51ujwBM%2BcUxauVAXgIIXQqk0pWxN8iqd5bg35Q0bUBpbgB5DQx5wQFYnIbUDJEIbQRwOwvYAArJhSAE6fMQBUQVVsSkIF4EkHkLocyhMjCfrr6WcDeUQCORCBoHcL2GxQILBcSdxfRkOexbBWYIJbxRxfeTsOJQILeRCJIDJcJXxRCFbERUBA4UPv%2BAZExdecBaBTUNJhJbBVxViUJXJWcCSaZUZRCGJVZbJSJRCNJXZUpZJW4Apc5eZW4Gpe8rIZlJ%2BsgLCDoY0BAKqgoFqIFc6G4AxdpRtjRXRegNFZCncFZhwCsLQJwARbwH4BwFoKQKgJwDdJYNYKXmsBsLhECDwKQAQJoKlSsDLCAARWYKyCKGYJIHEHEARRoAAJyNUaDvRxD4XpUcCSC8AsASAaAaCkDZW5X5UcC8AKAgCTXVU5WpWkBwCwAwCIAgBrAEBJAXDkCUBoC0h0DRChBaicCqBxDvRWzvSSAOLICdJSCshmC8C6GEAkDGx6D8CCAiBiDsBSAyCCCKAqDqArWkC6BtB5iIhJCcA8BpUZVZU1V5WcALQXB7WeioBUBHCXXXW3X3WPWSDPVgEeDHX0Dzm7BcBLC8DLVaArAQBIBHXMFk0HUQCM0nUxDABSCJA0CQovaUARBI0RDBCoWw28BC2HnXALQRDaDVDLWVVHURgLQMC0DXBI1YARBeDAD5RZILXcC8BYBIlGDiBg34CcQ1Dsq625VvwsqEii3kCCAdBI1XARCIhHkeBYBI0Ih4BjV62kDsrEARCpCYCq6G3ABXBGA1UrBUAGDIQnh4D5j%2BzZWVXfXCAtb/XSAp3A1qBI0Q36CGDGDWDWD6B4ARALWQArCxZdC61WzfB4SmBFWWBmAzX%2B0/hYBl3mztCdAZAuA%2BgTCtCkCBBzAlBlC5CpDpACB92j35AZD9DD1DBTAdCy21AzCT0L1d0CA9CNCz2DAxBTAr2eAtB6Bqxb1D070SArDqHrCbDn36AI1TVI2zXY1XU3V3XAAPVHBPVmBgG4DvXk0VVU1VWR0rAsz7RDAd31WSA7CshdU7AiiSAaCSCtWfQaAEXvRdW33DWjUgA7BcCsjvRcD9VdVxAEMEWSBcAEUwPvT31g2zXzWLWAMrV02bX03bVo37UUCs2oCk2nXnUcANAsA6wihWxMAIJVhcBdWsi4NW34BECt1fWyC/XiAA2Z1KDZ1g26CJBQ26Si3w0cCZXUMzUo1sMY1Y38OCPCOiMzziOSOsiMIQAk1M3RAnBAhmAAM02rUsNs3M0cNeNDBmNCMGhGDiNcCTU82EgGL82C3C1Hl23i2oVS0y0OB20K1dhK0q1q2YAa1a1iC0C62VUG353G25Wm1L0W1I3W3IAXBbCVXBCEhDW5XO2u3XDu1bC5Ve0%2B2VX%2B2B1KAh2FNISR18Ax0KBx0J3Mh20p2KPp2A3yCqOg25UaN50R311WCWDF2l3wAV0KQZDV211grLPWBN28CoAt3Gz/gbOd1L3OAQCuCr0D0%2Bjb0LC73JBj1dC3N5Dj0MAPMj1r2XPdD73ZD91VAGV/O9BfPz2jC9C3PH2zDFBn2U2rBX3/W6P6PTVHOcBFICNCMiOBNWMSNSPf0yMkDOM4NuNAOkAgNYAxAd1DUjWkBjU7ASMIMigUMigig7CIOSC3VtCovI1zW2D0PuNMPwAsM7Xo0s2%2BPEBnVsCcD8N40sAKA6ydI6zWOqjTCvWEtyNtATNp0SAZ2yBZ1zM6DYOkBaMw163IuI00NGO7UXBHCY0YtysKtKsqtzjTDE1cOON/07A7CkuMNrUM0evs3iuBtk0gCKu0WwjKtdWwiqsECBWMy3V8B0DhMLUQAC1g1xMxO%2B2ZuS3S2y3JNcOK3K2q0m2ZOa3a25N20FNG2tP60gHm1nNg0VNVN221OO1g2NOoUtOe0/gdO8BdNB29NG39N%2BvR3YTDPx15iJ3jMKM6vKP6uzM53GsGBLOF2rPO3t2bNV2cDoitT7ON3N3RCt1nPl0XPAs93uAH2TB3PoBgtPPvOvNXv90Psz2n2PNH2L3Aub1NBPsfvr0gsn2wvvt72Qu/sgeAfzDfMX2lXX3wtDUosP3ouyt3XyuKuLkuuEhusQA/2yPEuU3U1ksUtgO6O0tjVmASPesEWdVkMTXesij9UGNot8sLVLVksQMijPXMtcBSBdVMswNcAigYM7CWuGN8uCu6MvWMe8sEeMMrD%2B1pDOCSBAA)

## Links

- [source code](../../../../conceptrodon/descend/descend/mouldivore/cognate_classic_modify.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/cognate_classic_modify.test.hpp)
