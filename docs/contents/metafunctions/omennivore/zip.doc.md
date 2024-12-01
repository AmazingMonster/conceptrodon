<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::Zip`

## Description

`Omennivore::Zip` accepts a list of packed vessels.
Its first layer accepts an operation and returns two functions.

- When invoked by an index, the function returns the cross-section of the list of packed vessels at the index.

<pre><code>   Vessel<sub>0</sub>&lt;Items<sub>0</sub>...&gt;, Vessel<sub>1</sub>&lt;Items<sub>1</sub>...&gt;, ..., Vessel<sub>n</sub>&lt;Items<sub>n</sub>...&gt;
-> Operation
-> I
-> Operation&lt;Items<sub>0</sub>...[I], Items<sub>1</sub>...[I], ..., Items<sub>n</sub>...[I]&gt;</code></pre>

- When invoked by a container, the function collects all the cross-sections and instantiates the container with the collection.
The total number of the cross-sections is aligned to the minimum length of all packed vessels.

<pre><code>   Vessel<sub>0</sub>&lt;Items<sub>0</sub>...&gt;, Vessel<sub>1</sub>&lt;Items<sub>1</sub>...&gt;, ..., Vessel<sub>n</sub>&lt;Items<sub>n</sub>...&gt;
-> Operation
-> Container
-> Container
   &lt;
        Operation&lt;Items<sub>0</sub>...[0], Items<sub>1</sub>...[0], ..., Items<sub>n</sub>...[0]&gt;
        Operation&lt;Items<sub>0</sub>...[1], Items<sub>1</sub>...[1], ..., Items<sub>n</sub>...[1]&gt;
                                    &vellip;
        Operation&lt;Items<sub>0</sub>...[m], Items<sub>1</sub>...[m], ..., Items<sub>n</sub>...[m]&gt;
   &gt;</code></pre>

## Type Signature

```Haskell
-- Cross section
-- type
Zip
 :: typename...
 -> template<typename...> class...
 -> template<auto...>

-- value
Zip
 :: typename...
 -> template<auto...> class...
 -> template<auto...>

-- Mold
Zip
 :: typename...
 -> template<template<typename...> class...> class...
 -> template<auto...>

-- Page
Zip
 :: typename...
 -> template<template<auto...> class...> class...
 -> template<auto...>

-- Road
Zip
 :: typename...
 -> template<template<template<typename...> class...> class...> class...
 -> template<auto...>

-- Rail
Zip
 :: typename...
 -> template<template<template<auto...> class...> class...> class...
 -> template<auto...>

-- Flow
Zip
 :: typename...
 -> template<template<template<template<typename...> class...> class...> class...> class...
 -> template<auto...>

-- Sail
Zip
 :: typename...
 -> template<template<template<template<auto...> class...> class...> class...> class...
 -> template<auto...>

-- Snow
Zip
 :: typename...
 -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
 -> template<auto...>

-- Hail
Zip
 :: typename...
 -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
 -> template<auto...>

-- Cool
Zip
 :: typename...
 -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
 -> template<auto...>

-- Calm
Zip
 :: typename...
 -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
 -> template<auto...>


-- Zip
-- type
Zip
 :: typename...
 -> template<typename...> class...
 -> template<template<typename...> class...>

-- value
Zip
 :: typename...
 -> template<auto...> class...
 -> template<template<typename...> class...>

-- Mold
Zip
 :: typename...
 -> template<template<typename...> class...> class...
 -> template<template<typename...> class...>

-- Page
Zip
 :: typename...
 -> template<template<auto...> class...> class...
 -> template<template<typename...> class...>

-- Road
Zip
 :: typename...
 -> template<template<template<typename...> class...> class...> class...
 -> template<template<typename...> class...>

-- Rail
Zip
 :: typename...
 -> template<template<template<auto...> class...> class...> class...
 -> template<template<typename...> class...>

-- Flow
Zip
 :: typename...
 -> template<template<template<template<typename...> class...> class...> class...> class...
 -> template<template<typename...> class...>

-- Sail
Zip
 :: typename...
 -> template<template<template<template<auto...> class...> class...> class...> class...
 -> template<template<typename...> class...>

-- Snow
Zip
 :: typename...
 -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
 -> template<template<typename...> class...>

-- Hail
Zip
 :: typename...
 -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
 -> template<template<typename...> class...>

-- Cool
Zip
 :: typename...
 -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
 -> template<template<typename...> class...>

-- Calm
Zip
 :: typename...
 -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
 -> template<template<typename...> class...>
```

## Structure

```C++
// type
template<typename...>
struct Zip
{
    template<template<typename...> class>
    alias Road
    {
        template<auto>
        alias Page = CROSS_SECTION;
        
        template<template<typename...> class>
        alias Road = ZIP;
    };
};

// value
template<typename...>
struct Zip
{
    template<template<auto...> class>
    alias Rail
    {
        template<auto>
        alias Page = CROSS_SECTION;
        
        template<template<typename...> class>
        alias Road = ZIP;
    };
};

// Mold
template<typename...>
struct Zip
{
    template<template<template<typename...> class...> class>
    alias Flow
    {
        template<auto>
        alias Page = CROSS_SECTION;
        
        template<template<typename...> class>
        alias Road = ZIP;
    };
};

// Page
template<typename...>
struct Zip
{
    template<template<template<auto...> class...> class>
    alias Sail
    {
        template<auto>
        alias Page = CROSS_SECTION;
        
        template<template<typename...> class>
        alias Road = ZIP;
    };
};

// Road
template<typename...>
struct Zip
{
    template<template<template<template<typename...> class...> class...> class>
    alias Snow
    {
        template<auto>
        alias Page = CROSS_SECTION;
        
        template<template<typename...> class>
        alias Road = ZIP;
    };
};

// Rail
template<typename...>
struct Zip
{
    template<template<template<template<auto...> class...> class...> class>
    alias Hail
    {
        template<auto>
        alias Page = CROSS_SECTION;
        
        template<template<typename...> class>
        alias Road = ZIP;
    };
};

// Flow
template<typename...>
struct Zip
{
    template<template<template<template<template<typename...> class...> class...> class...> class>
    alias Cool
    {
        template<auto>
        alias Page = CROSS_SECTION;
        
        template<template<typename...> class>
        alias Road = ZIP;
    };
};

// Sail
template<typename...>
struct Zip
{
    template<template<template<template<template<auto...> class...> class...> class...> class>
    alias Calm
    {
        template<auto>
        alias Page = CROSS_SECTION;
        
        template<template<typename...> class>
        alias Road = ZIP;
    };
};

// Snow
template<typename...>
struct Zip
{
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class>
    alias Grit
    {
        template<auto>
        alias Page = CROSS_SECTION;
        
        template<template<typename...> class>
        alias Road = ZIP;
    };
};

// Hail
template<typename...>
struct Zip
{
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class>
    alias Will
    {
        template<auto>
        alias Page = CROSS_SECTION;
        
        template<template<typename...> class>
        alias Road = ZIP;
    };
};

// Cool
template<typename...>
struct Zip
{
    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class>
    alias Glow
    {
        template<auto>
        alias Page = CROSS_SECTION;
        
        template<template<typename...> class>
        alias Road = ZIP;
    };
};

// Calm
template<typename...>
struct Zip
{
    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class>
    alias Dawn
    {
        template<auto>
        alias Page = CROSS_SECTION;
        
        template<template<typename...> class>
        alias Road = ZIP;
    };
};
```

## Examples

- We will find the cross-section of `Con_0<int, int*, int**>, Con_1<void, void*, void**>` at index 2.

```C++
template<typename...>
struct Con_0;

template<typename...>
struct Con_1;

template<typename...>
struct CrossSection_0;

using SupposedResult = CrossSection_0<int**, void**>;

using Result = Zip<Con_0<int, int*, int**>, Con_1<void, void*, void**>>
::Road<CrossSection_0>
::Page<2>;

static_assert(std::same_as<SupposedResult, Result>);
```

- We will zip together `Con_0<int, int*>, Con_1<void, void*, void**>`.

```C++
template<typename...>
struct Zipped;

using SupposedResult_1 = Zipped
<CrossSection_0<int, void>, CrossSection_0<int*, void*>>;

using Result_1 = Zip<Con_0<int, int*>, Con_1<void, void*, void**>>
::Road<CrossSection_0>
::Road<Zipped>;

static_assert(std::same_as<SupposedResult_1, Result_1>);
```

- We will zip together `Ves_0<Flow_00, Flow_01>, Ves_1<Flow_10, Flow_11>`.

```C++
template<template<template<typename...> class...> class...>
struct Flow_00;

template<template<template<typename...> class...> class...>
struct Flow_01;

template<template<template<typename...> class...> class...>
struct Flow_10;

template<template<template<typename...> class...> class...>
struct Flow_11;

template<template<template<template<typename...> class...> class...> class...>
struct Ves_0;

template<template<template<template<typename...> class...> class...> class...>
struct Ves_1;

/**** CrossSection_1 ****//**** Start ****/
template<template<template<template<typename...> class...> class...> class...>
struct CrossSectionHelper_1
{ using type = void; };

template<template<typename...> class...>
struct DummyRoad;

template
<
    template<template<template<typename...> class...> class...> class A,
    template<template<template<typename...> class...> class...> class B
>
requires std::same_as<A<DummyRoad>, Flow_00<DummyRoad>>
&& std::same_as<B<DummyRoad>, Flow_10<DummyRoad>>
struct CrossSectionHelper_1<A, B>
{ using type = int; };

template
<
    template<template<template<typename...> class...> class...> class A,
    template<template<template<typename...> class...> class...> class B
>
requires std::same_as<A<DummyRoad>, Flow_01<DummyRoad>>
&& std::same_as<B<DummyRoad>, Flow_11<DummyRoad>>
struct CrossSectionHelper_1<A, B>
{ using type = int*; };

template<template<template<template<typename...> class...> class...> class...Args>
using CrossSection_1 = CrossSectionHelper_1<Args...>::type;
/**** CrossSection_1 ****//**** End ****/

using SupposedResult_2 = Zipped<int, int*>;

using Result_2 = Zip<Ves_0<Flow_00, Flow_01>, Ves_1<Flow_10, Flow_11>>
::Cool<CrossSection_1>
::Road<Zipped>;

static_assert
(
    std::same_as
    <
        Zipped<CrossSection_1<Flow_00, Flow_10>, CrossSection_1<Flow_01, Flow_11>>,
        Zipped<int, int*>
    >
);
static_assert(std::same_as<Result_2, SupposedResult_2>);
```

## Implementation

We will implement a simplified version that picks out elements and `Flow`s.

Let us look at the case where `Omennivore::Zip` accepts a list of packed containers.
To implement the cross-section functionality, we will use `Omennivore::TypicalAmong` to pick out the element of each packed container at the given index.

```C++
template<size_t I>
struct Detail
{
    // We use the cross-section to instantiate `Operation`.
    using type = Operation
    <
        typename TypicalAmong<PackedVessels>
        // The expanded pack is `PackedVessels...`.
        // We collect every element at index I to form a cross-section.
        ::template ProtoPage<I>
        ::type...
    >;
};
```

To zip all packed containers together, we will first find the minimum length of all containers.
We will use `Omennivore::Total` and `Varybivore::Minimum` for the job.

```C++
Minimum<Total<PackedVessels>::value...>::value
```

Then, we collect all cross-sections up to the minimum length subtracted by one (since indices start from 0).

```C++
template<template<typename...> class OuterOperation>
struct Hidden
{
    template<typename...>
    struct Secret {};

    template<size_t...I>
    struct Secret<std::index_sequence<I...>>
    // We collect all cross-sections and place them into `OutContainer`.
    { using type = OuterOperation<typename Detail<I>::type...>; };

    using type = Secret
    <
        // We create a `std::index_sequence` for the minimum length.
        std::make_index_sequence
        <Minimum<Total<PackedVessels>::value...>::value>
    >
    ::type;
};
```

The case where `Omennivore::Zip` picks out a `Road` is similar.
However, we need to detect the underlying vessels of the parameter pack in the template head of `Zip` to produce partial specializations.
Hence, we create the following helper classes.

```C++
template<typename>
struct IsMoldful
{ static constexpr bool value {false}; };

template<template<typename...> class Container, typename...Elements>
struct IsMoldful<Container<Elements...>>
{ static constexpr bool value {true}; };

template<typename>
struct IsSnowful
{ static constexpr bool value {false}; };

template
<
    template<template<template<template<typename...> class...> class...> class...> class Silence,
    template<template<template<typename...> class...> class...> class...Sorrow
>
struct IsSnowful<Silence<Sorrow...>>
{ static constexpr bool value {true}; };
```

Here is the entire implementation.

```C++
template<typename...PackedVessels>
struct Zip {};

// Zip packed `Mold`s
template<typename...PackedVessels>
requires (...&&IsMoldful<PackedVessels>::value)
struct Zip<PackedVessels...>
{
    template<template<typename...> class Operation>
    struct ProtoRoad
    {
        template<size_t I>
        struct Detail
        {
            using type = Operation
            <
                typename TypicalAmong<PackedVessels>
                ::template ProtoPage<I>
                ::type...
            >;
        };

        template<auto...Agreements>
        using Page = Detail<Agreements...>::type;

        template<template<typename...> class OuterOperation>
        struct Hidden
        {
            template<typename...>
            struct Secret {};

            template<size_t...I>
            struct Secret<std::index_sequence<I...>>
            { using type = OuterOperation<typename Detail<I>::type...>; };

            using type = Secret
            <
                std::make_index_sequence
                <Minimum<Total<PackedVessels>::value...>::value>
            >
            ::type;
        };

        template<template<typename...> class...Agreements>
        using Road = Hidden<Agreements...>::type;
    };
    
    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

// Zip packed `Snow`s
template<typename...PackedVessels>
requires (...&&IsSnowful<PackedVessels>::value)
struct Zip<PackedVessels...>
{
    template<template<template<template<template<typename...> class...> class...> class...> class Operation>
    struct ProtoCool
    {
        template<size_t I>
        struct Detail
        {
            using type = Operation
            <TypicalAmong<PackedVessels>::template ProtoPage<I>::template Flow...>;
        };

        template<auto...Agreements>
        using Page = Detail<Agreements...>::type;

        template<template<typename...> class OuterOperation>
        struct Hidden
        {
            template<typename...>
            struct Secret {};

            template<size_t...I>
            struct Secret<std::index_sequence<I...>>
            { using type = OuterOperation<typename Detail<I>::type...>; };

            using type = Secret
            <
                std::make_index_sequence
                <Minimum<Total<PackedVessels>::value...>::value>
            >
            ::type;
        };

        template<template<typename...> class...Agreements>
        using Road = Hidden<Agreements...>::type;
    };
    
    template<template<template<template<template<typename...> class...> class...> class...> class...Agreements>
    using Cool = ProtoCool<Agreements...>;
};
```

[*Run this snippet on Godbolt*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwA7KSuADJ4DJgAcj4ARpjEIADMktIADqgKhE4MHt6%2BehlZjgLhkTEs8YlmABwatpj2JQxCBEzEBHk%2BfkENTTmt7QRl0XEJyam2bR1dBVxTQyMVVSC1GgCUtqhexMjsHOZJEcjeWADUJkluyAoE6FhUl9gmGgCCh8enmBdXXo60hAAnk8Xu8zEcGCcvOdLm5iIZgJgFCC3qCAPQAKixGLOABVAWlGngAG4kdggfFpPCiWivFgCYBnbEYtGg5hsBRpJh7PEEomk4jfEyBKyot4ETAsNIGCWwgh89mYAB0Kuw9DYgmRSWeb1uxC8Dl5VJpdIZFxFwoAIpdRe9xZLpUxZVd5YTFWcAGJ4Yi3FGvPUGghG6liU1GWFen0EP3C21neNnCVSmWYWFZABemAA%2BkGAJJ%2BhNnAOG5TEVBEZRMRHmqyBa1JW2gwtJx3OtwZ7N5gsJwUARy83qRZwg%2BaS9ctGybCeLQdL5dQlcRsNHOtehdjZy8WSMib5P0tnu9vob5vrjbezYdKdhTD%2BqBVStewEFksYBC1q8LW4ijMXQrHZxzhWVaplcT4vhq74Pk8IAgK6oGNnWNqgqCLbXi6CqsN8ka3KQu5ulhZxCJgaAMOgeHwYqD4APIEAgCQfqCM7Bia9LhlcOEEHhxGkeRZy0fRPrQdqKEWheCZoU6oHtngmY5mcK5TvGzFAQuIEXOJ8Ybt%2BO7wfuLGhmxwCwgJDHCdgsGSRKgFlsBS5XLmZwALRnGYMFwXyNqnshYprhJV5SWmsmdgp3bxn2A6Cgow6juOk6aUWBD6iWtlqfZbiKQl2nboyemXAenFeVaPl2n58ZWdJHbyZlZVnBFg7RSO%2BX5Vw6xKYlyWzqlf7LmFNabjl%2BH/gePECOgRVIQ2KEJRVN53g%2B4GYK%2Bmp9Tpv7qflNnzj1YHPktkEKOZJXFVNvnFb5mLYp6tAkCGDBMtirL2smgUugFbazW9L0fZhbDmWcJxMAoh0qk8AMGMD/2A8DREkGWADufrMR6N3EHdolxv533SZ9bi45RWFQxDINKmD0MkwA6u0mAINsSiMQla3Xag8P6UIcMs7CVOCrTW5Ikdp3vJN56vJdWIGbSRkPViT2vPjv2gauzGUiGktmrGJ0i/j704wrRNA9FHiCEwEQJBReuquqb4M/6SWBhLYbGVcRttKbxCwmqy1QaDIkiW8IBnGkXixACyBGvyZKwSrrEMh7VuakdqIWsL01yzrKFXO12vY3K6dfa2usEX9PvYODBv65DJdl5XpPatX0UAGpInYpDtWiaJnNgqhJdyQaEJK0VUGWLBnEwgfcgA1pg6BnMSzeNKTM153jy/y0XypV%2BTFck2TxMPijLPIqifu251DtGbCTfA40EY3fDO%2B%2B6uGtLznVy3kQoUn4WKndSB7XP7VS8r8V7ALXowQmm896QPLiqV4xBgA%2BGtn1Qs7czgU2%2BPDdoaQziYG5AgM4qAqAXAAGwaAPvfaCpCzgRA/iYUhB80aiAYHQjQ7UUEd0MDPCIpIp4kI0JSCOgoo4ElVo7FhSoNKAITEzch%2BkBEAgFOSaOhlY4cVRujNRh8niJykfGSyOtAJ/wcsghMqDcT0T4fBFhZx4bfFQLEV2kQuHRUMNQhgtxDCOCkjPFhDD0akMXros4llPIJXYWg74NJaCJgsRVM4bBKgJD4eQ6x8NCD4Lot8doCCDqBMLIWfR2NmaIzAvAxBCcS4lXXCnXyQCC5zSIAtMpB1VqDT/PpVSO03BwJydbAWiEzypzFjiAAshEPALAfDSxZKhZe797wqgbu0PATAQ5IiRnbQ0YyGATJ8BjSR382iODDqRW4mBVBpGIKPO8s8xBeCFFlMSQSTD%2BCsP4S0EA2phITAA/JfzEroFgu0eEgJR7EBBTWJZaNVn0B3jUoJhZBQEB2PdW4gKQDwiMEiWCLAIgQGBUwQEbVBb/NPJ8/%2BwtJGayGcyPE5YxDTNlmAxUGyz64npdEjW8LZk52Pm4LOq8La11LuTM4LsTaRDIFnIVnsWnHyVpsoM7K2i0FhOKt2ccvYP2eCfDcHjjkAwEGci5VyqpBmJHc4aRZgqEIfBAWV1tiUWG8oLHl9S%2BUCtAavb1oChW7xgcK%2Bu29t5nCvi3T19T87oRAZGvGfq65b2gTXf1NdyFH3eCfZWHLL7z1VZoihlTdUikSk6akhr3EShNdauS5rLX6Q7LalUEA01OpdSLYZCkFAjM8OgKgXhonMiZYK9erL7a5i7T2vtqqk7Ov1WW05lbLlnFiKgTwtzvBChFFQMQShNZttTtnWNBNi6BtFeqyV5t14PgdStTNirO3dtoL2/tarZASoSJq3Jhan7FrnSco1i6rkrrXRajdNY7apkpdSi6tLx1CAYCzKdjK3XRuPYrJi964MIfhlO/Zf7y3GqXcB6JoH7k1m3bQXdUHuXPXdRm/lL8j0%2BqY76q9SbtVBvYyGoQdBGB7Fbox1DzHUPxpFVA094mU0k3ZuCzm8qMNnyw4hl9VweP0EhNJGTCMBY/tnUc%2BdAHzlEdXSRutsYIN7ug6VDtAAtPA2DB0odenGtjSpKzICnugMNjQbbMTs9grlgyLod38%2BPDz08%2BGPvGqQ9NzKIFucntPbzlG/T1SisOaCZhiHmGIeOqLuGrjuc88lj8sFSOYC%2Bafe2/nYRFaS7m7VGMI1CdY%2BAk9Un%2BKEnhM0PqP95wACVUBMHGo8zGfzcZms/p%2Bf5zFLSYFdtO55TzSVfkGnlAC1EuuloEGw/5sJdsraGu6ZRat2JuDq15hrJjDuFILltOy0kaqHb%2BSEwk0Fvl/JBCSvbNGgm43mQtPaWrrsDR/IY6sm05sLdhItLV5lXsIVTqSw9InXMdeon8BIm2EjbeYV/Gb96AASeB7iMAOzWcndTUdtY3sKyn05708SRRT37z3EzLzNQ%2BJ7z3mJM/m2mO4sEIhYFUFmJQ/Y%2BOPZ0/TrSxambrYPBjiUxBsfdZyHKBWZwocmzzRldy8F%2Bn7tqc9%2BXe5Np8%2BjB9/J%2B2rekrRTipgU8szC/OWLzAEuNMy%2Bt1cbZuyWCwmVWIWriXLvXxS9qMrlr4cgHKyD9c%2BObseUJFUn7QXSrI%2BE85tDwbYFA5aQn/JTNBvDf0sT0nePul576SXBHKfZdp/XIJrPw6ac58fFX29034xF6Gz4gCqli/jV2hBavdPXW/dQaFrk4WfGkPg5zGLTmfquYuyV1L7vIpDggJl7LWWlM4ZU%2BdkPa%2BI8x8tZVvz9ng8z5Kzo35WMWOP5a0/rPonOMSYDVJkNqvce9fvapDwTwClMbfJCbYKaqEHWbebHXcne/Q7U3QkfSH/HrW3H5K4E7MRQrY/K7U/OJTpIxPXXAgxchfpWA1nf5f7eaXPEfTvcnJmdpSHaAugGHDvb2YVWvV1K3FHV/NHBNYmfiTHFXLbHrAvQ5M%2BMvLAZhK3OAlbOLdrUQgnM%2BC3FnNPL3MAmtLnOPBnJQkiJFAXdFF3UXcXe5T3ByaXVA2XZ1BAq1JXLHYQ9XDCdeLXJg3XFcBHQ3KzL3awtmXQ/nCwn4BjBFAndFFgR3bMQwt3D3PYL3ePNwX3SZf3dA7NLAm/HAiyM/DdaPWPBQz7HI/JDgkA6pVQrgzPZfVvLjag/aJBPInvEvTaCQsnYfKoipdgpPRHR5BvH5JvD6UonGXojXXgsTT/Pg4YoY5NEYmuWHfPLvUHHcQAzlfvVKeYlgmgtgr7AZY6N4YZZkHYmWdEWlXEJEd8ZDLY3Ys4vY3yOQ2nUdQ0I2LMVhTgtOVrKiSpXUe9O4rgTYp4o9UTBTe2OETIBQHiEQ9tWlTiTuVQVgaUb4RzN4JmIQLwNIIoaefrJEftIMTaAE4GYEhwtwGhLEPCUkEnLEdY1OIvNE2gDEgCGrZ2AQe42EGhPCfEpkwQEk7UPCD42EIkvibkjEQk1AYkjEL7VcWCQfNVMsbEkiEQkUkALpNyX2EWP9LMA2BIAgCAe3EABQLCZUrUNwBEpEzIFEikriM4VEhQdEp4J1GlK6UaMiCEqE%2BgE4746nF4unN4s%2BfzQkIfEWeExE5E9AM09ErMLgfST06eDONwLEoEqU3Exk2eAUofbADkiU6MhwWM1k/k4k4Ur48k80yk4M0Mq/Wkhgekq4OM/Ep4Dkukz4q4bkzM9APk%2BMwU7M/2EAMU52FMnEnbE%2BUU3vWEMMxMr4pUlUjodUwXTU7UoGWEfU/0wM/M%2BYU0404My0r4jtcxb0GeLuB0mEx6JfPor1Z4%2BLL/Cot0qrQ0che4h4rWfoqNHg8oj/cYsYxrd0%2B2C8jQGs68g8l/Mo1048h858s8oMC8rgK8g9G8mNF0o8iYjjRNU85GO%2BYMj8sCr85/VCu8386CtvP8m4oMK%2BUsz878/cwigY%2B87CzCk8nC0NJEZcx4jtKMrskskMwdDtQYDoJ07gnolC9CqCp8rC8iuC94zsmMgQQnRoLrZcmdWY3KM3ACbkiaYo505vQ8%2BQ3i14wCrXHwFgQEdsgi68D1booitCn8ni9/Mip8s4V4ATWqDiwy7ilS0y/ijrRsE%2BNLIcDUrUtgHUmHWES0TS7Svs9k4pS8nyvy9snVJ%2BLLHLAFWCDy7MKcq4KwK4XylgLSsKvCYCh4twZK1KgK8Kv424oStMkSsShIGi7pPCRK3TKSoafSGheSr42afS6y8Cq4vi1S/8iyqyqnJS4ixw0ixyga8y5y1cVy6Kdyyc3U%2BjbK/y4bSsoK98kKlKmawc3VSKrLaKiczy%2BKtwRKrK0K3K9KhCrgGsvapasKyi%2Bi4ShgUS2gcSk6yys4Sq/ZbwzaCsk8Tw2jIy2yzin4wYhy9qv8npG2JmS6oqxi/SUG5oG6u6mHeBbVAo/Yq6SGnIAs5i2lbAO02E0qX0g0pQAMpcswQspE8MsswQFkggIUhUskwaOcggLMQmzaGktwPCzKt8%2BoeamspMqihQMqjKw6lmRCls14WCZYjswEhimimU9stwAc0k3yYc6%2BDoUECAdqcara9NWI8nWWsWyUsG3mhCjQdmjKua5G6s2%2BAW98/m%2BGQWx%2BLq/5bWvEsmtxCmvqP0K0t40tZAHUpQUctWuK3U2m%2Bm7iP0w0/GvMum%2BU7AJ1DgTYWgTgfwXgPwDgLQUgVATgflSwawIsbYXYIUcEHgUgAgTQGOzYCeAIMwJUQIMwSQGoGofwDQAATn8DMA0GIRqCSH0E4EkF4BYAkENtICTpTrTo4F4AUBAHqCLuTpjtIDgFgBgEQBAG2AICDi4goAgDQClF42ICiCwk4FUBqGIScmIUkDOGAGQDDikCVDMF4GnkIFukBXmH4EEBEDEHYCkBkEEEUBUHUCntIF0HmHhnhDSE4B4FjvjsTuLtTs4CVxXoISIX3sPuPtPvPrOEvsJogA8E3voCuUOFal4Enq0E2AgCQA3qpGwfIEoFIa3pAGACkDMD4DoGVzHogFiEgdiAiHaEBBAd4HYeYGIEBGoliG0ClO4dIA3sgmogYFoC4d/qwFiC8GADcDEEo1EawFCKMHEFkcHDTLnjHt/vORIkx1EZoUaEgYBFiHhH4Y8CwEgaSgmVEbnmIBXSUDm3UeAABCMGLs2CoAMGAAUAbjwEwHhmxyToLqfuEBpDfukHCa/rUEgf/v0ARBQGsGsH0DwFiDHsgE2FQDSGaD0acjRXylMEzssBbt4FQEcbRiwEyc%2BT6CupcDIlmD8HmDCFNmWHGHmCKGyAECacKEyG6YYCWDGESHmDsCutYs6E8G6D0DGbBomaGcSRGYWBmCmbmGWeGDaeGYkE2AUBzr2G2c7o4AToHsgeHrOAQaPpPrPovskCvuHFwDvpwfzvWHwa8c2HomG3GFqbLskCSCVAbqSECEkA0EkGrtIQ0H8GIQbsOe7tIF7qSC4CVGIS4DbobpqBRf8EkC4H8ABeIROd/uHtHvHsLq8ZnvnuIcXr%2BBXoofXtQCwYSB3rYE4HaBYGJECCcjHkBh3C4AbqVERZTtvqICqb0HCZfvEHfpiaUDid/t0HocAaYGAe4GnrjqOYgYJegapb%2BDgbBVZfZc5YMG5d5f5eHEwbIaSUODMBeZJanqIZIbpbNbIDXqoewZABZbZaci5doYbpAoYcpIYkoFYd/t4c4dEeDf4cEeEYcFEfEbfEkekcgbkYUaUdoBUaVdIDUYRE0ZTvwEFB0exX0dUEMYlGMcEFMd/vMcscBGsf2BTrsd7rTcceccwFcczZ/FJZ8arH8cCeCbdFEdFciYkGidkFiZ/pTtlcSc8eKasEsDSYyfgGydyZyHycKbHCnesDKdTsqZJ2xSybqbBoafcFWeaZCDIgWZWE6f6eaF6YveKByDPY6b3eaAmevcfYGGmA2fKC2dGffZfY8Q6HvZGZ2b2bfrAdVfxaHs4B1fdf1YRFQaNaVA0HufwCFYuGedeZtfedwSwESFqZVdhfhd5ZBcCBxcCECBSDBaxfA/Kc4CJYntJdnoXqXupadfta3sZf2BZaQZYAUGJDDmJB5aVBTFuBvuQ/vpFdkDFaiY/vkCldHZ0GSFIHlcVdAcOeOcHuo44Bga1cIR1a454744E6E6DAwdY%2BwdQ6SCSCtYIenopedbNhY/pcSF46RKzH44bqzCM%2BVOIBYGPt9aYYDbYY4f4dDaC4EaEZEbTZjcEDjZkezcwHkcUeUb0YLozY0Zrd4BzZjN0cgYMeQCMbTZMZVZTorc4erdsbRnrYLsbcNJbY0bbZtb4F8a7aCZCb7Yk4HYleHdk/iYU4NeMBSZnfMZqYXbyc4DRHtzXdKaHq3eqfndfecAgFcBfdac/cWb6dvZ6aPfW4GYA5mcaHGZ/a29Gf27mffd2%2B/aGF/bO82bW9ai2B2H2bu5VbU9Ocg845Pu4949nkM6kluCQ8efM7wetcIcw8%2BZw9A/w9WF5Ys/8HrqxcNos8CDbqo6gZHtsGJes/WFLpAEkECCvuI%2BOskAbqI4Ba4GCBVaSDVYg7R8x9A%2BvpR8JeB5LtIEcayGcEkCAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/descend/omennivore/zip.hpp)
- [unit test](../../../../tests/unit/metafunctions/omennivore/zip.mold.test.hpp)
