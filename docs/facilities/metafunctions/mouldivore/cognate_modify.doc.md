<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::CognateModify`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-cognate-modify">To Index</a></p>

## Description

`Mouldivore::CognateModify` accepts an operation.
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
       Arg<sub>I<sub>0</sub>-1</sub>, Transf&lt;Arg<sub>I<sub>0</sub></sub>&gt;, Arg<sub>I<sub>0</sub>+1</sub>,
       Arg<sub>I<sub>1</sub>-1</sub>, Transf&lt;Arg<sub>I<sub>1</sub></sub>&gt;, Arg<sub>I<sub>1</sub>+1</sub>,
                     &vellip;
       Arg<sub>I<sub>n</sub>-1</sub>, Transf&lt;Arg<sub>I<sub>n</sub></sub>&gt;, Arg<sub>I<sub>n</sub>+1</sub>,
                     &vellip;
                    Arg<sub>m</sub>
   ></code></pre>

## Type Signature

```Haskell
CognateRemove
 :: template<typename...> class...
 -> template<typename...> class...
 -> auto...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct CognateRemove
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

/**** Operation ****/
template<typename...>
struct Operation;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = CognateModify<Operation>
::Road<UnaryMinus>
::Page<1, 3, 5>
::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult = Operation<Vay<0>, Vay<-1>, Vay<2>, Vay<-3>, Vay<4>, Vay<-5>>;

/**** Result ****/
using Result = Metafunction<Vay<0>, Vay<1>, Vay<2>, Vay<3>, Vay<4>, Vay<5>>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will implement `CognateModify` by combining `Pagelivore::CognateSegment` and `Omennivore::ModifyTypes`.

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
struct CognateModify
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
                    typename Pagelivore::CognateSegment<Detail_t>
                    ::template Page<I...>
                >::template Road<Omennivore::ModifyTypes>
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

[Run this snippet on Godbolt.](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIIGBXKQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJyal2mA45QgRMxAR5Pn5Btpj2pQzNrQTl0XEJSSm2LW0dBd0K08MRo1XjtQCUtqhexMjsHAD0AFQnp2fnF0cHJhoAgsenANQAIphprozIeJgKj2fXdwel2B5wBtxu4LMgQiyG8WEeJkCbi8jlohAAnojsBDzNCGLCvPDEW5kAt0FgqFicYCzo9lMRMDRVH9TmCCJgWGkDOziQR0e9mGxSI8sgAvTAAfQIVLuaHxbwIdIZTIRgWejwIxC8mERVjuEKBR0ebiYaQUXnoLJObI5XKYPKRfIFrEwADp3TLbgstQ5jabzfRddT7rTsKp2Qx0AAxYiyK1XCHszncnWO/mMF2e71eX1hiPR2OCBEAdisxeeQf1dyTdodbhrKd56cFbo9gWwj1hTAUvw8giYyzIGubLvdruw9DYggUWc1OcVedcMdkxL7LUHxInHMYBAUY6p7ZxpYhj1PGttjbTzrYY4smGAEQYEWAM8PdzPjy8WSMjwAsp50FVdU1wHSJiGJO8HwYJ8jD3d1hS3Kdd33Q9Aj1cFy0rcFqwve1U3rXC6yYFFUBQjsux7R4hEwABHbV5WFYiiDHAA1Vo8CYWJ6FfbE7mzXNwyXQtpSRai6M%2BfC2OIDiuJ%2BMjPRMY93zPBs8OJJjSPdSDH2fHiTzPL9nzpJhgEwICqNo%2Bi9gg%2B8dNgsdhSkmTuPktCjwrNyqxDJ4AHkpyfAA3Eh2BANwDB7PBkH/fAqHRAAVdNfn%2BCEWwUNImD2R4/MYQLgpLdDE0I/CnQzG8214r0519aK8FihL3l%2BRSyw8gqaSeCxuzMk0lHjG1kzUpENLHABJWcfUVGq6sS4kyRAEAIiwVQJSUcT5WJYbXIqpr9NPVS6z24qRzK10sU7cLfh895iHtHJPQ/fjFXpVAiAAJVQJh0B2/Kvo/A6frPYl/o/U8DgOR4AHUzK/MyTAANg0elGTwVR1qxfd4Y1VBHkYHwEjwhF4eXQQ4taUzdzhjQTuU4HgcRplUfbMciYIEniDJhRSCB4HQYhsyAHc6FoDVroYBR%2BGIFgNQQMzInDR5SdxwQqduGmaZKltHlZsnOep1XdqO1tXQ65AAGstcwcndY/O7VYWG7kE7AQFkwAKxHlkjHjwdB0VoCB1i5gBaU6TTNC0dStgGkS5j9mfN5D4Ojs9Lrx/piTjrEdZVvWz2Ns3SYtuDlb1g9WqztWiqba9DduYAGW3acbZpwyf3/WhAMRdUsFhEqIC9n3iRruukMLrE/f9zyy5LFrg1%2BivHTn%2BsDbIs7u0LwfMHr8m30n5vgEeN6PvMp7Xvez6kXXzeR9QgrMInwr%2BqIkiRsYp/3QAKTG%2Bc/wwWr4umpFZrzUjJgJaK0rL4Q2uVYUgCFogOWpZCSxI36bSPOhWeD9ioL3VqOcqK9KLJ2uqnbe90qqPVjCfD6X1toR12hXGhqo3CJxBmDSGn4eoUzpsjBm2B0YaExtjBguNCEw0JsJOOM54ZF2zqeThKMkSjUZu6WO%2BddyZ2kcw3mjwBa0CFpqQwYsSCSwINLR4stFQKyQlI6R2C2CPCjHgYgCw45qPUTzVh0MCYI2VFwpEH9FEnQxkQR4wAsYZVjJRYxZl8B2zWvQj8PN4gED5hvBgGo%2BZY2mOzKx2dZFILRu6X8Xt0D0HES46Rbj%2BaC2Fvo8WRiTFmPlmzRWBBsl6xsWZaicp0DOKYcOKut4Mp5zZgXLmjdgZ20cA7OUztXZCw0p7b2vt/b0KDu2P0odAz0MBnEs8yjhnx1dGU7OBCboCGJPYxxLMVEZ16YU8kJSVGFyOXrE5RC3CdIEN0657Znmq1zuI/cWzr4z1Vn9K8pVq61w3sPMZH5d7fzbuZLutAe591oAPKFl8yJjywtbW%2Bpd0G1kwRgyuELl4UTXpimFxCDLfj3gfduaolTPVQAyjFQ8dxX2xHffFwZDT7waDsLIAUuqdV6vfIl6lX6umGi/Zi79hTtLHD5SJxAxLgL0nxUh38Yp/wajNAg6A5qwNAQgta8iyLQMNca4BprVrWV8ZarKqr1USS5agr6YKCIkvBS2cl50spXVOQwMZD1mUUM%2Brrahk9CWNiBYwnZGj3HsPhrk%2BR%2BSAl8KCTjNgwjPF7PZhTVpqs01uAUTwpRYjHm/JphUrRVS9Gi1qVLGWIDzFNMsb09pdiHFOJUTW7mLCoYpq8UjORbg/EVszfwkJ8tkDhN%2BJEx40SWixJjarBJFtkmMDSRkx5xaaalsnWOO5xTMClN6XW7RuiRYGIli20xbbGnAGaQe4G3aPmRh6YmvpZKtKDPEaMmlNMJmRUdqLdksz3ZBLRX7QOp1FyRmZkBhN661YGx1b/eqPxiQqulmqs1ex3U/rmgdfep9cNBqIRVdRjxSNFQRWfNw/z93lSAzR1W9GMGMZQ70gtBcHK9NebdJEFy%2B37JuT%2B09Dz9lPKE1RkT7yGifPTsB4GJcQXlx9Yvfp7oL7Uo403OljGkUNBRemXuiz2XQs5di9Y480EA15V5WNA1vWSt9Tgk6ayKVjn05ysZ8KGVH3Iayij58qW2bYzy6eXlFIVi8vyoQCAUQEEtMlHC2mhpsa1eNKiKWCBpdTKXflUl0SxDwEFBkc16qRTEMoVAaRxV3FSulTKZWKtVZhkpbCtwvXZe8xVMNtXRC0Aa017aznev9Y9mJkSQ3tUjfq4185vb5set1vCkq5lkupcDFHYF%2BopsSsvCaWba25VY0/WfBbeWltjZW6Ji7FkukKR63C4z22O75b2/hObGmjuxemwveZc3Lsvc%2BZd5VqrNWVTu/yOrD20ircucKa7wo8MJGIxhRzp4tvpioUyxDBYVyedsfd8buGYdkVIwTtTXGiXGVMijhYaPlORgBxhIH7k%2BW0mopGZrfWsFLxy3Dr%2B/P27HmO5ljz7nTsDdOhSiy9rMBQ/dE5Ti3FP6%2Bgl8SV15q3Aa9ku67e0bXP7RB9KxXAbhNnLU2G14650VRve6rfH7xzK25DUiI3Llou46nlhT1WDLfysG3gylHKG5qaCwOIW33Hdx%2Bs1i8qtP3hB%2Bl0L7TXqlW4KVyBQciqRfjknAF7eYbddIgL2BTcpfpwoKOwHnPwvdPh6V170N2rE90Coa7ozRkvtMo70iRCUXBu4qc9z3Wzfs/F%2Bt6vPzkXo%2BGbYUZYLCeLZJ4i1Hg5WI0/FZ53fNqJwme9Eq8FOaHhgDMHZNRYASFBetYymZZQJkz9de%2Bl5GfsuFc%2BZtwpu3W7L%2BK/G/TAO/JCDbSeL1MUSURUWVEUPAcUKUMcSdL6B3TfHvF3APc3fCGA5A90AAaVhTPAZDogcR%2BEeAgH3DMFhnMFhggAIIYUeDfnsy5nhQAAkilGApRPcADvcy1hQ34A4CDXIA94sg9p9Q9NJXR/Nl8vp4VX9TIdtXBSUNYOtz9qsQAKdHs3BZDd92x98xkGcUx94t83Bu90Vt8bN69U8QAyNODyRuD1sj97gwZhpIxIoKDRBUkxAFAsZ4hHh0oexMBAJ4UKYYFbV4EVci1g9Z8q5O88sHCsBUlJsp8oCF48C4DoFEDYCUCEiv4kjGADUjUgFFoojwF1pBCG9J4zdQUMicj8DXQiC1MPxSCvByDfgqCPQaC6CGCmCWDlk0NV8fwLCeDvth8BDmDhDRDNNgZ3cYYmVK8dMIVHh1CusasEdRtKd5EqjbCSpiDTxjD8YXozDRjnCxDM8cDVCvM9DYcPsjJW5GV1RCj%2BDbiac7C6cb40jxDEsQQ/jQQDRaRhpkxN5g1BdDR/iQQwQTs3Mc858/9V5A0U4RMgDfQQC8JJpMRG9YjZc4TW959KJ2DDEBBUwV8w1j4wtKEsCuZoCGisiECkCWl34Djhi94zjzIQ4AxcDrUQAWAmATZJQTVyjEF00fkRQeS%2BSBSJQhSwERSJ0A4uAM1OcaT6jGSRoWTyTQtFDw4hjajrEW8/0S9L4WT7iW4AJlCOcf1tkhi2kMNdcf1rYo4HTQUMNtS0R1jQpUBr88JwCdxiQziTT1Ejj2RT91p5JnTTw987CGM2UkRspoINCQpMTsM7jaMzxgyzJYy3AiSJYSTAyaYMyeMR8699CV9i4WjONozuMszh9uVsDJ8JChiZsw9biWSFC38QsWVtTk9h4ZiXc0irj544jDSCTI9rCt4V8gtT5OyI0eyx9lTM8ITISwR%2BUwxWAuQzIMtvJITWRgxcQYQ4QFiSQBA9g0gJzecng2J0RBdmysZy0IQw0rzUFxT7ZwNnZVA0hiBoMsZZltR8pRp8VA8XD%2BU5BmBiB0RClBEkpdyZdTtu02JLDUTFRQLWgIKIgvx2DegrpIDTS95B91QnykQA4EK5pfzSSM80i8TDTbg2ZYd4UULwLIKvxzIGK0KoLMLaBsLz5aL3j9jgLaQvcbyDS/VRcw1h8StaRfxN8qAvB8R%2BghLhyRKZDaLPR4UpKWgZK5KcgOSvTQDMTKNkTACIQ5oszWKmLYc5puykRUhHhghHh/BPQ5pHiB4eL/cLyT8hAvA0higQiXofgLRFQtz4VPLvLMhfL/KUVeDDL%2BDCK3ANAM5VimBMQiLFSxTYqzAErYqA5AhMqkriRJBcrkq3AA4HLUI6z3KjQ/KAxAqYLbggsIrFRvt1KmBNLGg7dDc8qkR4q0rOq3BUrsBHJeqMqeqiqcqRr8rCriRSruVyrfing4ofgarrQHyWhJkJRV4EgCAIBAEFAXR1rXw3AqqAq0cvKfL0AjqUUsQHMOBNhaBOB/BeA/AOAtBSBUBOBGFLBrARRthdgYYoQeBSACBNAbrNgTYAhJBXQNAAAOMwMwAATjhq4H8Ghqhq4GLGLGkDuo4EkF4BYAkA0A0FICepereo4F4AUBAEJqBueputIDgFgBgEQBAG2AIDSBRHIEoDQE5DoASCiBdE4FUChthgDlhkkGCWQAdikFdDMF4BCMIBIC9j0H4EEBEDEHYCkBkEEEUBUHUBptIF0FSD5mujSE4B4FuvuseuBtes4B8hRDZsVFQCoEeEFuFtFvFslohrMEoI8G5voC/NxC4HWF4Gpq0E2AgCQC5rSB5rIAoAgEjujpAGACkDMD4DoHZEcUoFiCtoqzAvRFNt4BztQp8liG0AaGpoBq5qQh8gYFoDzr1qwFiC8GABNB0Qpu4F4CwD5KMHEHrvIMaBFTbpepAUFXZHzvIEEF6CtrRFiGunAo8CwCts1DwDxvbtIBFWIFiDCteC7uADRCMGBs2CoAMBfBYm%2BD5mTieoBuVuEFG3VukGvu1rUCtoNv0EMGMGsGsH0DwFiApsgE2Ea36DboDjJA7lME%2BssDMBJvXukiwF/r9h6D6ByBcEjFmD8FSDCGWEqGqD0GKGyAEFQZwcyDwYYBGCwfGDqF6DLqaEWAIYocQYEEGDaFIbGESDqBoc8E6D0DtiYcwZYYkE2D8J2D2H4f0AtqJqttJudqFpFrFuAAlseClq9ogFwHlv9v%2BqDsBoPs2Glg%2BnGHgbBskECFdDhsCAxo0EkDMEkHhg0H8FhjhtEextxqSC4FdFhi4FhihrhtRthn8EkCRpMdhnEb1tJvJsps0ZprDsZvDuZrtvZtjvjr9r5rYE4FaBYACmLADiYBXh/C4DhtdBcaHvwCIBgaVtkFVvEA1ofqUCfr1t0BTqNtNHzvNo4AeqCZJpttiYdqdpdpkeyb3lyfychu9tQF9oSARChDMA0ZDtpuiYSYSA5rjpGajr9pQAMCMFya4EJpoBRSx0zuzoiFQrHsLvAuLtLocDHsrp3GrtrqtobqbpbtoDboBs7rfp7pevwAZH7p%2BCtuHuQBRH2ABoiHZCxpeuntnvRHnv2BeqXpXoBvXs3qUG3teefAPr4GPoUFPswHPoFDHuvvKbvs1vkGqd1perqdfv3rAasEsC/p/vgH/rPJyCAZAbVEpesEgd4FQGga9m%2Bb/oQaoecAgFcFoZCEjGYdWFYfSCIf6GFdwf6DFewbof5YGHYfyDQb5bauVaGHlfIamCGGFe4aWAqD4cDq2CEfVuadaeJo5c4CkddrFq7BybyYKcoJUeKfGZSCma0dIB0awESHgaxpxtIDxsCDyfMeLH8DhvRsCAsasb8baetbJtsDCemcifgGiZZvtoWbmeICSf2FSbdpYAUACgdgCgGZTAWFlqKYVqNVSDxdvokHvtkEfpJZ0CSFIAaZNvbotctuCY6dZpREeEdudoLaLZLbLbwgWGGdGbUeSE9YibpojqWejqzaXZWeLe8olFLbholHLYIAlFUFFtTp2YzogCzr1uObroBovdObLouZGarprrrvecwEbubrEEebHpee7qhY7r7scAHp%2BdUBHoBd4CBcnr1rBdQshcXuklhd4Hha3o5GRf3vnaPpMgxbPovtxbKfrcqabeJefrbbWffvAZsGnrgfpcAc4AOFmlZYgagYSBgZ5fgfqA1eQfcA4YKHQdFd4fFcIZKByBlalZyG1YldY/6EYfaE47VfE%2Boa1d44Vd1ZmGk64cWFE5EcEd%2BpEaxstYkZtYPbFsLeLceC3ddF3ZdarZncDuDq9Z9b0eacDbxvhtdGSH8GRr8YJuSGLA8fjetsTYpqpq9YMf8GMbRuLAJqhskERq4BhpoIccCB7facTZTeaZlt85CfCdDs2HXqyGcEkCAA%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/cognate_modify/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/descend/mouldivore/cognate_modify.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/cognate_modify.test.hpp)
