<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::CognateInsert`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-cognate-insert">To Index</a></p>

## Description

`Pagelivore::CognateInsert` accepts an operation.
Its first layer accepts a list of variables.
Its second layer accepts a list of indices in ascending order, which indicates positions in a list, and returns a function.
When invoked, the function inserts its arguments into their corresponding positions, which is indicated by the index list, of the previously provided variable list.
Then, The function instantiates the operation with the inserted list.

<pre><code>   Oper
-> V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>m</sub>
-> I<sub>0</sub>, I<sub>1</sub>, ..., I<sub>n</sub>
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>k</sub>
-> Oper
   <
             V<sub>0</sub>,
             V<sub>1</sub>,
              &vellip;
       V<sub>I<sub>0</sub>-1</sub>, Arg<sub>0</sub>, V<sub>I<sub>0</sub></sub>,
       V<sub>I<sub>1</sub>-1</sub>, Arg<sub>1</sub>, V<sub>I<sub>1</sub></sub>,
              &vellip;
       V<sub>I<sub>n</sub>-1</sub>, Arg<sub>n</sub>, V<sub>I<sub>n</sub></sub>,
              &vellip;
             V<sub>m</sub>
   ></code></pre>

## Type Signature

```Haskell
CognateInsert
 :: template<auto...> class...
 -> auto...
 -> auto...
 -> template<auto...>
```

## Structure

```C++
template<template<auto...> class>
struct CognateInsert
{
    template<auto...>
    alias Page
    {
        template<auto...>
        alias Page
        {
            template<auto...>
            alias Page = RESULT;
        };
    };
};
```

## Examples

We will insert `-1, -3, -5` to indices `1, 2, 3` of `0, 2, 4` and invoke `Operation` with the result.

```C++
/**** Operation ****/
template<auto...>
struct Operation;

/**** Metafunction ****/
template<auto...Args>
using Metafunction = CognateInsert<Operation>
::Page<0, 2, 4>
::Page<1, 2, 3>
::Page<Args...>;

/**** SupposedResult ****/
using SupposedResult = Operation<0, -1, 2, -3, 4, -5>;

/**** Result ****/
using Result = Metafunction<-1, -3, -5>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
```

## Implementation

We will implement `CognateInsert` by combining `Pagelivore::CognateSegment` and `Omennivore::InsertValues`.

When provided with a list of ascending indices, `Pagelivore::CognateSegment` will find the differences between the adjacent indices.

<pre><code>   I<sub>0</sub>, I<sub>1</sub>, ..., I<sub>i-1</sub>, I<sub>i</sub>, ..., I<sub>n-1</sub>, I<sub>n</sub>
-> I<sub>0</sub>, I<sub>1</sub>-I<sub>0</sub>, ..., I<sub>i</sub>-I<sub>i-1</sub>, ..., I<sub>n</sub>-I<sub>n-1</sub></code></pre>

Then, we will make `std::index_sequence` of each difference by passing the following helper class template to `Pagelivore::CognateSegment` as the operation.

```C++
template<size_t I, size_t...J>
using Detail_t = Capsule
<std::make_index_sequence<I>, std::make_index_sequence<J>...>;
```

We will keep the first index, <code>I<sub>0</sub></code>, since it represents how many variables we must pass to reach the first target position.

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

template<template<auto...> class Sequence, auto...Variables>
struct Send<Sequence<Variables...>>
{
    template<template<auto...> class Operation>
    struct Detail
    {
        using type = Operation<Variables...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = Detail<Agreements...>::type;
};

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
template<template<auto...> class Operation>
struct CognateInsert
{
    template<auto...Variables>
    struct ProtoPage
    {
        template<size_t I, size_t...J>
        using Detail_t = Capsule
        <
            std::make_index_sequence<I>,
            std::make_index_sequence<J>...
        >;
        
        struct Slash
        {
            template<size_t...I>
            struct ProtoPage
            {
                template<auto...NewVariables>
                using Page = Send
                <
                    typename Send
                    <
                        typename CognateSegment<Detail_t>
                        ::template Page<I...>
                    >::template Road<Omennivore::InsertValues>
                    ::template Page<NewVariables...>
                    ::template Page<Variables...>
                >
                ::template Rail<Operation>;
            };
        };
        
        template<auto...Agreements>
        using Page = Slash::template ProtoPage<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[Run this snippet on Godbolt.](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIIFcXKQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJyal2mA45QgRMxAR5Pn5Btpj2pQzNrQTl0XEJSSm2LW0dBd0K08MRo1XjtQCUtqhexMjsHAD0AFQnp2fnF0cHJhoAgsenANQAIphprozIeJgKj2fXdwel2B5wBtxu4LMgQiyG8WEeJkCbi8jlohAAnojsBDzNCGLCvPDEW5kAt0FgqFicYCzo9sKoCK4AGLEWR/U5gxksNIGRnEgjo97MNgAOjFVLuC2IXgcdIZzNZggRAHYrMrnoirHcIVyeUw%2BUjdbzMMSmCjUGKRVjHrCmApfkJMABHLyfTCkR5moiWgBqrTwTFi9AUEtuUplBDljIY6BZsmJjpdbuJfuIAaDP0tVMC2O1qohj0LjyN%2BpNSK9FrFUUwAHdU%2Bng6Gi48vFkjI9lExgJgEYFno9E678WW3NW6/7A8HLR765PM%2BKc5qceql9qaU8/ej2SdOZhucbTebHrOM6Hw7LN8uLI8Fvq8MgbQIFphVGliJ6jwA3MSulUWE/0CYK6BNeQEaiB1L3LSyjEJgNCqNuVw6nueoGm4ApCqw7ofkQoZoMOaSRjBcF4AhiL9gQ0pllq4LricA4ICiBD0Ihu77qWh7eguuZhpREYMUxgEQWuUFPAA8mwDAMHgn4kOwIAAJIMEobR%2Bt4PysRCwo/GkTB7I8EmMNJsmwX%2BkElmhGGMFhWaLpKfGykpKkEGprq/EBargTREJAkcjwWHaPZuIFml3BZI4VpaClng5kZOQkLk/j8xJkiAIARFgqgAPpKEmw7EgptnYnZ4L5nczbhZxqCPGOAHYZF3EFkW55EayRCdt2TWFh5XXNsWKEHoagrWaKYoBcgADWtzEMAIYlX1zUtI4D74c%2B360Dh1V4Og6K0L1zYQPtC2PAcBxyrpMYIgAbBoxHwQVVI3cW1WwXpCDFggPZYFksHoI8xTZAIVrlcdzZ3aRD05ptlpUIqBBZa0s2kEdC2nY8eR9B9PawQsnozT4jAEAowO3KDzbjVNM3E%2BKIMLesKOPAAtNaQiMQQzEmrTfXEgzzZYLCVnUHDCNU%2BsaXra60680WtUThmyNc6DFPTbN4tJVmitFtm3ma4WlXlualq3MAsF7oTc08aDrYRMAHZdj25GPPztCC9tu0QJeSLG6bklE1S%2Bbqpa6z08JpNa8BOth3rA0cQbXEit7mBm4IFu9db7YdQ7fYdm1qCZ8SifJ0TRWrqVXnmTHaENSKCketXABSMXSo5ykJa5yVIql6Uxi%2BOXOkOewFUVHpdxlve5QPI71yXJU9Vz%2BvBUeTJ4MQCyy2mc510ejr4eg68NvVhuNVzLU56g7X271c9R31C9WdplrK1TTbHbey2PspjLrZtjxu3tuuPEOgA5saN6QXT%2BiYG64NVCQ2xE9IgjxXrIHegQT6/1MiAwYI8fg75UE9hoKvSMkQayPG/BvDMJMyZFmgbA6GYpYayBFkjaWhZQGvkMBAqBsF7pIkboueBL1MBvSxugkoORsEkBEUoXejxiGkLlvQShVCc4kRgbw601cWDbXQPQJhCgFY31BmjDGDRIx4MQT8SMiMCYpyUVQp%2Bs0NaGKLPTABzMoas0EpzZx3UkQsKdg0F2w0haMMRgoMWIAJaYClsAosy9CH703v452gstHkl0WEiJUSYk%2BL6jvAQe9ax1QMco/yelKaq0ierGmuTtaQVBgvauhdfapwAenW2mdez9hScEv%2BHsmCYi9ibJOLT/aeSDiHGizYwKl16o0o%2BCdhlF1aTfdpdtuxdLPhfTqQyfbmxnt5COkFfKPAAEoNB2FkT8QUQr/GQuxKuCza50JFPXD098bJijEng4gg43QrNPvFVSSU5puFHj3bKE9kxIkKtxEeBB0BpTHpC/u0K3DTzhQZH5fzhzUytLPMqN95kIPiWvIpCjD4IPyTGRJ8sXnfM%2BsQWljZ5qLWbq1c%2BedL5c2vg0yuI4PmjRFA4lZoM373g/mtMQP8/4MyAbkkBZ0wEcOurdbhEMYWPQ0M9CxwjzEA36BI3BaCCG4zkWQg%2BdiyY0M1VDauDDBB6JKcoth4DVU2vRVqnVSCUFoINeInBUiGgFNkbWeR5DFH%2BI9Xw7ALy0k6MwE6/xxjPCY3MTjKx%2BMWlWqVuUlWeKGauNye42N9JoyxjhgzHmsTCw9PeP4%2BVpTmxAsSupUFDKEg4r2AW1lTbHhpXCuskcHamXkojfOfFls%2B39vSjtWgEARU9UDmKItpTV3HRfgtAd/Kh1Vr8TWgJAtgkOvhpktW6kcmlNJQQZl7pkmBNSdojJotz2SzFM6qh1LCnjnHXu4qkc%2BUPIigs5p5tN19TWZ0x2dbMAQD6Z7NwoGU5jLAhM0u0yjkiQqvyqqRslmjN7S2NsHT7abJgpy/OuyRn7MaqHGZdG8wahEic4KaQFBeBYncsKOGhqYSFU3firH2NCUjicx0l0uO3DvsNB%2Bx9eLsoHK4MymHaJSZ4%2BhdT1drS2ntIpvKewt7xzqgC2KimYwJlRflJExmZ48V5UWO%2BmmFnaYMLpsS7xiB3gEOB0%2BrwWh0CvoSq2xHizDU2e5hIXmGApgpT2/9gXy5YYc%2Bp4llZJ02lc3ipDftCNrNOUwOgmy/MFb2lR5ZRUB3DVmSp%2B5qEBUpZk589LOnfgeEEAVyIZBQt8eiWKbA9ACM8VPuJ9AxI2v%2Bc68Sfr5XaN2aC8loD/IGs9aKhlu0vwIuef6D50zxWAs8vmwtNZVlwseai1NgbNHJ3ofDol1T2HFuGmWyNXrzXMt4b2ch3LIXTmoCYBA7Oe3SuIfw1drElX610Zq3RPyAAVQU94xDKFQGkUKtxtIKF0vpVM6JYgyTkmZESqWS72QU/DtIiPaDI9R0uu7tXBqLxJSvBYAnZTk8p9T4k17Qz2cLMdsLjtPHsyEm4OpjHZncce4z6q17DPVS/azyM7PRBU5R1z5nBAPQK4JVMos/P3ibKFxzdXhCxdlwl2pqXFZHiy5/l%2BuXloR0mbJwjlXnOkS2/t1ixlcWrxpxC1ZK%2B2cy0KnjLxl7jxldI7V0iJ3FWQCB8I9uoDu6Pca618G8zi4od0/F8x2kHhgDMEZI6YAvs0eOat85qGLWDJne2yVU%2Bhfi%2BYFL77P3891NZAAF6JriiPPAvesoEEtDG3qvnMD%2Bf/jfXnt8u%2BD775aAA0uB5ssEXQrw0hALMZgrrmCuhAJfvY3CPHrsHBmayAAS2jGDD9O5Fhvbhnn10Zkvg5CWLcPbq7hsU2XRV65Cyg2zhG35EazYGPFaFx3x1gjSij1VzSALlB1sW4ghzLCnULGTzqzORK2JCB0QM%2B2LhQITx3Wv3JFvwIDNx8jOiUnwG7RtEME9FoAUGqniH%2BnW0wD%2BjWUgQ0HBUyj7n0xNBuitWkx6x2wU1IKwCwVp0/wW2/07gXzv2eR70XzFDHxPlMwkMYBSgRSRQhX4MngKg9AxWu0I1ny/wZ2UOH2X1XyLHXy8E31%2BG33FF3330P2P1P3PzaRCyBzv0dk23OxhSMNf3fySyOwDwF2ANcFAJ6wgOICgJMnkjgPdyfyMPj0T3QL6kwONGwICyRB8IoOz1126mhyJWe1k0WQIP/z5xCwAFlPAAd%2BxNDosyts0iDE9Dlc9RIQRuiOQfJaQFJ9wi4os0dfIeiQQwR6dY4NMq944XN1s68H8chFd0ZUAi9SwW0O9SiZi0tjMxD%2BJyNtlvEMMii58pdLD%2B8bwFCR9VCbDqibYXhJ8StfDs4hMOMjiN190FVFpEUQAWAmAJpE1kV9C0VoocwP0yYu4/iASsogSoUrNPUcwnFQYzdkSAFhtXMEAq1DsyYF5ziopbi%2BpT4DiuVOoD0zDlFicqwx0D4qim1INSNBcoiD1plPjp1b4wCewQDmSPjRduSqFBUgpViW829CZcDHi6Bh8CS2SsjSxU8n8ScviqFwdiCU9ft/tiRDIpJoD5IW125aTpSVSsDKNRxqS5xfc%2BTMjDTsjjSbM5M2SpTjoZTGQcjgd/CG94sySVNkSvSN0AFKSKjqMvsMjmx6SNlBcMSnSexiTjS/8QiZ8SjzCpimkkCcsMjQys5%2BxozL4WiwdCjlxOjRixiwQTl6RWAeQexJNCyeiJjtQoQYQ4Qs4SQBA9hCIVk%2BjxJ69xFJN/Tli3SliGMui/IajHiqAvB8RDVuynN4581Qw1lhyWhRzxzxFHZm91jW42gNTOzvMSo0pjSNAPQzAPRJBQxdzsy3BUhHhDzHhAgTyQAYyqY4z2z6IhAvA0higODzlhNIxJM1kXy3zMgPyfgONIw/Ctzmi3B9ymYLyrzGZghHhpAmZ/BKCYczkgKXY0c8s0KQLs55ymBFzGhty3BGYLzYKPRGYkK8z88nhYdLE0dxVkAEZ7QEoIAu4FAsJGKExXz3z0BPzgKPReKXYsRJkOBNhaBOB/BeA/AOAtBSBUBOBRdLBrAbxthdgHYoQeBSACBNARLNgJoAhJARQNAAAOMwMwAATjMq4H8GMqMq4GVGVGkDEo4EkF4BYAkA0H3Kkpkrko4F4AUBAH3K0ukpEtIDgFgBgEQBAG2AIDSBRHIEoDQG5DoASCiCwk4FUCMqukZiukkEeGAGQAfCkBFDMF4A4MIBIG2j0H4EEBEDEHYCkBkEEEUBUHUGCtIF0FSBrE8zSE4B4FEvEsku0tks4DEhRFisjFQCoEeAyqypyryoKseCKrMEAQ8CSvoHfFxC4HWF4CCq0E2AgCQESop3WviogCOuSsSGACkEPJoBdgSH8ogFiCGrx2YDiN6t4BesgLEliG0FMXetIESt9jEgYFoHRCGqwFiC8GAGCloCYP%2BqwD%2BKMHEDavwFgkaGuX8rapfAuUZH%2BoiEZCcpkrRFiE8ziI8CwCGsojwDcu4F4GuWIFiAAteERuADRCMG0s2CoAMFmh9G%2BBrAiyko0uquEBV3qukGFuarUCGo6v0EMGMGsGsH0DwFiH8sgE2BR36ExsZjJHIlMEUssDMG8vprTG%2BngE2HqAIr8AgFcFmD8FSDCGWEqGqD0H9QEFtpdowX6BGCdvGDqF6FMSaEWHdr9r6EDqGG9rGESDqCDs8E6D0FvDaAjtWCjvNpUr2AkH6o4AktIC8t4B8umsyuytyvysKoMuWogFwHKo2vUu2s0o5s2E%2Bn%2B3GAgF0pAEkECBFDMsCAco0EkDMEkBug0H8CujMv0E4BctIDcuSBFCui4CuiMrMtsqun8EkCsq7quhzqGp8r8oCrruCv2oioOqirGriooDOtQDWpSrSo4FaBYE/GVEZiYDW3bC4DMpFC4EMtKvwCIBNqqtkFqvEAaolqUClrat0EPK6qYB6tpszuztzuGo4FGpipREeEmoLtmtyttBfrfo/u1QgFWuOoSARChDMFrt2pCqPvOpOrPqofGCwaussv3NusZFXkoCeras%2BretptIE4fRG%2Bt%2BocH%2BsBsJmBtBvBswEhuhrEDhu4YRrluRpktRoDoxqGuxuQBRH2A0vxt6CGuJtJvRHJv2Bkqpppo0vpsZqUGZvkZtg5r4G5oUF5trAFv%2BuFoAbFsavkBAdapkvAdlvZr1qsEsCVpVrNtksIhyC1p1r7ACesENrzuNu2h%2BFCYtv6BcBjGDpCBjCTudtSFdtyFjoKFyc9pyGyd9p6FDoEEGBmAKbtvKYDsqcWFKajqmCGAyYTqWAqEjozq2B2HTq2rHqzsGravzpmqLufttlfvfsMsAUrp/uIeSDIfrtIEbqwESBboGYnqnrft7uVH8DMvssCD7oHtXs3uGc4B3sCtsbCsiuivGtOtoaZWvtvrmpYAUE/AfE/EmeNAWC/qrsqtSFcdFokHFtkElu8Z0CSFIEgegb6oGbga3pGpPomqmtUBebeY%2Ba%2BdLFxnwYvsIersCECEWf3tCsOtxYuvubJfWsiWQDfKyk%2BbMqym%2BfhlRfFroBYYevYZkt4f%2Bt4f4b%2Bu4eEcEFEbBpRokahphpkY0rkaRqMd4CUfRqSaxtUBxs0d4G0cJt4D0cgMMcprTFMbpoSAscwCsaRpseJa5q7Acb5uce4cBbquBY8bBelshYMH8YVqCeJtVvWY1oic4AOFShiYNqNoSBNqSbVrqctrSfcBqb0Ads6eTo9rETdpjaKaTYYCafjv9stqqfaBTYjf6BzYzejtabzfaaLdTt6fqtgaGe8s4GmrRfedIUxcZGxdmckU2qJb2obqEVWcoEzs2ZAHMpFAJf8GstXo8oJeVHntOdrd8tsF3vIeDlID0skH8E7rsuVA8qMskEsq4BMt3wGcCBrbzvOb3q7YGZKpnZPbncXc2HpqyGcEkCAA)

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/cognate_insert/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/descend/pagelivore/cognate_insert.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/cognate_insert.test.hpp)
