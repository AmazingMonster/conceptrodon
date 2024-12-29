<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::Zip`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-zip">To Index</a></p>

## Description

`Omennivore::Zip` accepts a list of packed vessels.
Its first layer accepts an operation and returns two functions.

- When invoked by an index, the function returns the cross-section of the list of packed vessels at the index.

<pre><code>   Vessel<sub>0</sub>&lt;Items<sub>0</sub>...&gt;, Vessel<sub>1</sub>&lt;Items<sub>1</sub>...&gt;, ..., Vessel<sub>n</sub>&lt;Items<sub>n</sub>...&gt;
-> Oper
-> I
-> Oper&lt;Items<sub>0</sub>...[I], Items<sub>1</sub>...[I], ..., Items<sub>n</sub>...[I]&gt;</code></pre>

- When invoked by a container, the function collects all the cross-sections and instantiates the container with the collection.
The total number of the cross-sections is aligned to the minimum length of all packed vessels.

<pre><code>   Vessel<sub>0</sub>&lt;Items<sub>0</sub>...&gt;, Vessel<sub>1</sub>&lt;Items<sub>1</sub>...&gt;, ..., Vessel<sub>n</sub>&lt;Items<sub>n</sub>...&gt;
-> Oper
-> Con
-> Con
   &lt;
        Oper&lt;Items<sub>0</sub>...[0], Items<sub>1</sub>...[0], ..., Items<sub>n</sub>...[0]&gt;
        Oper&lt;Items<sub>0</sub>...[1], Items<sub>1</sub>...[1], ..., Items<sub>n</sub>...[1]&gt;
                                    &vellip;
        Oper&lt;Items<sub>0</sub>...[m], Items<sub>1</sub>...[m], ..., Items<sub>n</sub>...[m]&gt;
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
/**** Containers ****/
template<typename...>
struct Con_0;

template<typename...>
struct Con_1;

/**** CrossSection ****/
template<typename...>
struct CrossSection_0;

/**** SupposedResult ****/
using SupposedResult = CrossSection_0<int**, void**>;

/**** Result ****/
using Result = Zip<Con_0<int, int*, int**>, Con_1<void, void*, void**>>
::Road<CrossSection_0>
::Page<2>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
```

- We will zip together `Con_0<int, int*>, Con_1<void, void*, void**>`.

```C++
/**** Zipped ****/
template<typename...>
struct Zipped;

/**** SupposedResult ****/
using SupposedResult_1 = Zipped
<CrossSection_0<int, void>, CrossSection_0<int*, void*>>;

/**** Result ****/
using Result_1 = Zip<Con_0<int, int*>, Con_1<void, void*, void**>>
::Road<CrossSection_0>
::Road<Zipped>;

/**** Test ****/
static_assert(std::same_as<SupposedResult_1, Result_1>);
```

- We will zip together `Ves_0<Flow_00, Flow_01>, Ves_1<Flow_10, Flow_11>`.

```C++
/**** Flows ****/
template<template<template<typename...> class...> class...>
struct Flow_00;

template<template<template<typename...> class...> class...>
struct Flow_01;

template<template<template<typename...> class...> class...>
struct Flow_10;

template<template<template<typename...> class...> class...>
struct Flow_11;

/**** Vessels ****/
template<template<template<template<typename...> class...> class...> class...>
struct Ves_0;

template<template<template<template<typename...> class...> class...> class...>
struct Ves_1;

/**** CrossSection_1 ****/
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

/**** SupposedResult ****/
using SupposedResult_2 = Zipped<int, int*>;

/**** Result ****/
using Result_2 = Zip<Ves_0<Flow_00, Flow_01>, Ves_1<Flow_10, Flow_11>>
::Cool<CrossSection_1>
::Road<Zipped>;

/**** Tests ****/
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

[*Run this snippet on Godbolt*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwA7KSuADJ4DJgAcj4ARpjEIADMAGwAnKQADqgKhE4MHt6%2BAcHZuY4C4ZExLPGJqRl2mA75QgRMxASFPn5Btpj2FQxtHQRV0XEJyem27Z3dxX0Kc2MRE7VTDQCUtqhexMjsHAD0AFTnF5dX16fHJhoAgmcXANQAIpiZrozIeJgKL0ud0ezxuYKuwIe9yhZiSEWQ3iwLxMSTcyGW6CwVBR2Gh5jhDARXiRKLcYmAJEICBYOLxsPhiMwyNRHWITAAnrTHtDQacXgAVdlfWh4ABuJHYIEFmTwoloDxYAmAgIukOYbAUmSYhwFQoGYolyMCVm5jwImBYmQM5tJBD16swADpndh6GxBAouQ9lsQvA5dTK5QqlUarIE3iiTVCzRarUwbai7V8HS8AGJ4YjLL0%2Bv0EAOysTBoyk9OZghekzG6EvGsvc2W62YUm5ABemAA%2BnmAJJe2svHP%2B5TEVBEZRMYBMythiNJKPV2v1uMJtytjvd3u14iYACOXgz/xeEB7SRnbw0W3nNYHeaHI9QY4npOPuMefanLy8uSMdb1zLeaYzLNZyNGc51fBdY0bUkmC8IhnUdB5gC3C1GAIT0khfB4%2B0/CJlQfScTxeW9R3HJtUUQ5D3TQ%2BCcRAEAkzIudw0jPEYwbeMyLcBiU1LZZSB/ZNWCZIRmgEdB%2BO4oT4IAeQIBAEnQzDr3zINFWLVFeIIfiRLQBhxJeWT5MzGiMLxKtwJrRcoNRVdOxeZ9L37AhfUHYcSInZELNDD8v2VBi/xUws1OAUlDIUkzsDoqyOKItz71Ip8XgAWheMxaPovVIxAljTSwiD2OXWz11Mryt13fcASPFFT3PRzlOI%2BLH1RByvPfHDv386qALLLLK1A1i8ssyCOObPA2zslrBpeMq9y3Srj1PLgLy8%2Bq4vwp8NxrNrfIEgj/x0sTeuY2cBr7aLlxguDnQozAUI9TafNwojSIChr1vIpDbqohQIpyqFjrA/6I1y3k01oSlRAYFVzkhc7OLh21huXBHE3tKTnRxF4ESYBQfoxjCsYMXGIsJnGASEEhhwAd2zZzczBiHDDMqMzqR%2BG2cRgr4bRtgSex4n8ewUmBcdAB1DpMAQPYlEUxz2uVVNwapgKKeIanSXFrcpc/f5fpO7kAYG0HpQLeVguh25oRRriebIpS6f9E3VJDKc%2Br%2Bq2OcTT2bcE3nBeFgEPEEJg1jIXaHXg107rQ2mXLzJ2gqVUkg/aUPSSj769cwkAXkyLxYhFZAA31cUtzohOzaT1EM9QvHHQrKtDdyhHuVRRzrY772O9tvmibrzH%2Bf7gnB97smXgANX%2BOxSEc45jhebBVGc7U80IC0ASoYcWBeJhc%2B1ABrTB0BeUUp4GeuvM7rnOaXbnfadf2R8fvvR5FxXUCpz1W/tuPAsr9S3CT1xgMEsSsh64hKv9Fm%2BVb7QVgqgeyD1Vp3nWq1cyU1WbXy9lgriXce7PzJq/OuDxiDAB8LXB6fY54vFFkyKmHRMgvEwNqBALxUBUGRCkDQ79P40S4S8CIRBOHcPBsQAsDATBcMclQ%2Behhj4RHFIfYR0oS4SnLkKU2RYQpcMdJ5DBtZ5YM2Vl1FRIpS6Sgrlo0BjMJEaTATiX6Xk%2BxRTZs9JqbhJp9hkQKeSwiGKSI0C8KmTJUCxFTpEeRAJDACIYMsQwjgOLHwCe/MRkMAkX30TWKKmUnG1mobQrGYhaB1l8XDF4bANjEGETwgJQSqQlKZB0MhmdpG1hcVzIxpISHNNrnraBW0m7RimtbS6qB4LdPIfdSB2Edr4VemtBK5FSGTOooLd2gyeSXBeAAWQiHgFgPgLaw29qM%2BC48Oh4CYAXf4sd6a7IYPsnwzM9F9jiY4IuulliYFUJkKpoyT5iC8JONB/SvEmH8FYfwbwIDLUyaGVpXinLoDoqyDkO81ZoqnOcsRVz6D90GYixFW4CD7ChhiOibIjD/DoiwCIEBUXsgvPrOFfUYWOTdsBMy/UQZbP5COMQRyPY4MkmwW5jt%2BXFNdhstisDW5uHbng%2B%2BRCXgpxDpEMg7d8GOhrvdb%2B0JlJ8vaLQZOsg1UJHTm6XpazIHvjebKLGAgvk/KqUVAF3g9r9jGpgdh8EIA6rQkyiw2VmVCtlVCNul8u5RuFYqxg6N67DxfgQkWA8k0JqFoPCeZ9aAz0jTG/NsDUZKuTeAgORD4I8K/uGn%2B9NDViFJEAuw1jeHWswra9o7yHWxPNM6z1408yikBR61cPrnQQErYG4NgNQZdgUNszw6AqBeGKUCUN1kfZxtFZA5Ss7520EXcu55dqPmOp7b8l4sRUCeDdUC0MVAxBKA5UGp9A0r6Fo3RHEtKrTWhwklq/1stHg7rnQupdxrUSqrTtXS1Hos5Ho7faz5Z6qmXuvYO91oY6ZNgBlOo2WzZ1CAYB/MDgqZXrpFXbfVDtuwKEI8Rw9Bsg3Hq7U689qHinodvVOe9tBH04Zfc3DmcqFUFvI9G99FHy0lqk%2BmgOLwhB0B%2BJgXNwzxNieFVq1NhDpM6cdKrdWeqgPUfsrRojVMwOkgU/QQknF9Mfzg4xpy8ZEOnu%2BWxq9HGh2Yd9Nh0CuGeXgkC6ukE%2BGGzR2cwIUjTwgsxctoJjTxbHRjmQIfdAjaBiAe9MZgAWngRhUruVDOoblxhWoUtH2EXu9AASq3d0S8l1L6XeNehmhVQ8NEzApHMCkXdoHD2oga0fJrik6KccwLC5SJXSSDbS9m8BzMRMSdjZ%2B2TmbpJfDZEMJBxmGoACVUBMGqyChFdZvaus8YS5SHxU7GtyQM0FhLHodV/F1dbCQIsSLu2CiNcLHsUb/lYgbB8htzcoY9tp9FXFvUWR4sH4OXjZK%2BDRL7b5TLMsewJoZf2TnwPGZ9aOmXHuGLmV1a7IdwNuBugTiKiPGKnUJW%2B8jmnE1j2krBBIb3Nv5Dh05X%2BAAJPAmJGAnddijmBTPEs89ecZnSxL4XSt%2B%2BLkaNkvWdnghd%2BHylZeYHLDZAgyKQARCwKodsShdxKafA5xX92nt%2BRe4RNn5piCc4%2B7aW27wdfk42hhWnfT/NY/h7b3aKtmjEpO6j%2BVYvEXkpACwJgh92xG%2B%2BabncQKbPh8JaSe5jyaSojrRTmbw30pjZpyAMbUvawV6yRlL4f0McK%2Bx6J5XH741aZFlT76PPDH7cOwFAXQvbGU/x5nQWtO6%2BV4JZXvNS2EubofqttNHeKHTIMTtHvSTCJ7YO9Vj6lErXpvWYVnk88St73K0krhdGaZcNq8t%2BNhfQeQNa3NdrGNOvdYI2ZizQPz9F592XodCbHLPLabYHWbYBXjRxKBRbdTGfOA2AiXOfGTNvUtJ%2BBfVnDbV3FfK8HbOKDwTwdldBRvd9c7HnK7T3OgEXIgwPQxTqB3TArbKPZkNwSxYKUA3/R/SKSHDpaHdxZ8dpW%2BIxPpKgo/L7EZXHa6YfZfTCInWZF6UnCginJfWDUfGvOnXKYghA5vSTL9R3DnBg7nbArxZSfvLAT7Flag%2BHOrJAtZJgrXUPHXeXUQ63U7HBIqdXKvXnembXXXFcfXOiJPE3M3NPQ4S3VtDPG3Wg%2B3f8PQ53AwgQN3e%2BD3G7b3LghiP3THCIoPOg/aBw8sJg0kLI6XA3OPBPQIlPc3dPJgiPbPA5XPFgiVdgxrTg0bIdUvcvIwjHTowlMfdHTPBvBnNTbQ5nDNRfKQqZGQwlbvbfPvQXMwrpcY1ZdNXo0FTHN8afLQ5GIYrY2fFbFA5AlnFNQ44hRYwnVfJ6fAyVTfPAjzBYvfFQg/ENBXXkWLa4SEUGTSBeVQVgK0JkYLaLV4sESETZV4SDdVAEf46wvY7dYzIOdsDQd2MjYYyXGE3%2BOErgREgE84FVYcXGHSIYKLKE1vVE%2BmNwXE2jZoIYeEzE0GIQLwTIMoI%2BXbf4ZdPMf4wxOkhknIJklk2gPMLqMknICkloAQak1EQRc4ficUQXc4WkENELV4ZkhQVkqLbvXk/kwiKbCDUUhE8UwQfiCUg0wQWUjCfidE0kaU/SS004KU1AGU04OU7OEAdfZOck/E/IMUp096NwNKNHadXlf4Nk1UKjZzZAdsMmBIAgCAGPBQIScM9CNwTkxk9AJU1k/iVMvknEQNPDQEoEkE7Eg6PSL4n4%2BgKLF43M4MgLbEkrL4Y%2BSEu/P2A/IzX%2BGso%2BGkrZJM7klM9U1UnaTspQbs5Uvk9sLgAKVso7cNNwQUvEykj03UtwQRW0wXHEM0t02cnU0kQ0k%2BO09AB0tHCBf0xUns9ktfdUkcsckA7UhgMUhc/UmJAgPc7AM00UjE1ES0pc3cj8k0iBJ0l0iDNckU683U387fUkccuUw87E/kQMqLY9eMpQToaM/wkAWMtgeMyzek5MjMggEc9Ms8187AbMqsis/442BADMY%2BReEsv4ysrEki2i/MvkStQk7Y9mXY4k0Y7TdAo4mtf0HheE3UwGRnbQhs%2BffY3TMVPMfijQV8oS1im%2BRA6EzinistWwrLX%2BfirgQS19eS7BCTEY1S7i%2BbZs%2BmTS2SnM7E4bFipvHY%2BA5Emwoyg45S4y9S%2BmIBMUuSmytiuy5GAytA8SxytS5Sdy8y4inEoU90l86yny7yzYu%2BBygKxK44qA5Sac4UoYPnAYDbEc55KIr4AKS0o6Zw4S3ylE5ylK4zN4HwFgdkP8zysNQojYkSryxIhK5KiS44l4B4FTTBGKhS%2BypSwypK5yl4OcJ/VPNrGMuMnGLpUkKqlgGqv8p8oxASua6q2q0C/cukLrTrJFOiVCjsGa1EKwVEeaxaza5azS%2Bcs6jaw7R0qjNEgCjKrKhIHK8ifiE6ttY0bI6I%2B8oqzEluScmA5qvqotNq8qjqka7q4G2yuK1qwa/y9qoy0avEca8qF/KatCo6ynNaha26nfS6pWeE18twG6paisd/XazGw6hMk60m9apa/iMy3G86u6raky/0NKyKhgTK2gbKkm7qlGm1b6vKj1CU/6%2BUh4Eq2KkGxSjioapGgK7pTLQxLm9c680cgUp6/IXm/mrpUhcBFYiyvkfsnkocoMmGaEDkzCrs7C9sMwC8hktsvUrSe8x89so8823sp6O2h2rqLUwBf4G86SjQJmommSlcrNBQN6twK6sOj%2BEcgir0OiS410iK9Wt6kCtmtwcCv042gUQMiE2iuCiMzoaECAOqZCg69C1qH7R7XOqc7Wl85tAS%2BOqmEc4C1c9OwCmO6SrgNuxOx0nqwlBuxct2h6L0IirLUM%2BCyMpCg3au7G327SG2gc32rMyMDgHYWgTgfwXgPwDgLQUgVATgeVSwawfsPYA4ScWEHgUgAgTQLenYfeAISQR0DQAADjMDMDSDSC4H8E/o/q4ECECGkB3o4EkF4BYAkA0FDoPqPpPo4F4AUBAFDofsPq3tIDgFgBgEQBAD2AIDzi0goAgDQEtEU2ICiCEk4FUA/pSCShSEkBeGAGQCLikEdDMF4CPkIEpGRX7v4EEBEDEHYCkBkEEEUBUHUAwdIF0H7qpjZEyE4B4G3t3v3sfuPs4EdyIbYQ4VofocYeYdYZeHYYdogA8HIfoCqXxCWl4HQa0B2AgCQDIZlEsfIEoGcYoZAGACkDMD4DoCdxQYgFiHUdiAiA6HZCUd4FCeYGIHZGkliG0EpMidIDIaomkgYFoAiekawFiC8GADJFoF42SawDjyMHEGyf3BaFPhQeke%2BWaHZ2ScEQGHUZFFiDZFiY8CwHUecn2WSdPmIEvSUA%2BFKeABFCMEfp2CoAMGAAUHHj%2BCpjewPrvoEeEDlBEekBWYkbUHUdkf0EMGMGsGsH0DwFiBQcgB2FQEyCGBqaSgxGqlMHPssDMAQf6bESwDOZhX6EGHyBcD0gWD8H7rCDWBqDqD0DKDyAEH%2BbBZyAhYYHGBBamH7qaEApGHmE8B6D0GRaGFRdWGqEmESCRZWChcJdGHhfxYkB2AUCvsOApf0FUdIHgd4EQZeD0YYaYZYbYbftMdwB4asdvq2FsYmZ2HkkOymE%2BZfskCSEdDSCSFAY0EkDMEkC4Q0H8BmHAcgdIGgaSC4EdBSC4BSA/rSCAZSH8EkH/plZSAZfUcQeQdQfvomawdwccfwdgiIbcdIdQAsYSCobYE4A6BYFFECCSl3mxm/C4DSEdB1aPu4aIDeb0BWaEfEFEc2aUG2ekd0F8fkaYEUe4EwfAb3qtekcQa0dgh0ZZbobZdJjDYjajcPHMZcYSGRFhDMAFftYwYcacc9YbbIBIY8csZQAMCMHDa0r8b5IUkoGCekeifCeSendificSYcGSdSdQnScyfUZybyYKaKdzdIBKf2fKaPvwC3CqepVqdUHqfNEacEGaekdafafZE6aOCPp6egd3f6cGcwGGYPdwgdamfHFmfmcWeSYTbWYkA2dkC2akaPozb2fGYeasEsGOdOfgAuaufyBubuZPAQ%2BsGeaZdecF2pXOa%2BfVt%2BfcHReKEBb0jJcqWhfKHyGJayBhaGBo9BaRYGHVpxcY6xdaBWFY8RdmFGG474%2BBfJaWl2H2BpfE/zbUaLc4HLf0aYdDeVHDcjffsPB5djabe1dbbsaftIBFawESE%2BfVageSAjflcCH8DSBAaSAVaVbNcLYQc4FtbQYdewbwYIbdd7a7YoZ9aOH9YMZYAUFFCLlFFU8bGWC4fwFjcF3jdkETfWbEfkFTeg50GSFICzZzeUbpY4ALcZY0Y4BLbzHYRZaC5C7C4i44mWDrd88se06SF0/c87a9Z7fcbq6mFC4ZPbHC7SHbEi5wtUEYdHYCYnZCbCdidnYm7iYSaSd3ZXcEDXayaPcwFyfyaKRqbvv3bKefd4GPdnOqfUbqeQAad3aafAaPvvfCafe6bETfbvo/e5O/bKd/fbb4GmcA8wAWeTBA4S7A%2BTcg9S52Yy8HYOceZsFaY%2BbQ%2Buc4GOHJRw6eZeYSDeaI8%2BZ4%2BcAgFcEY6Bbxdo/7vBaGEY4J/yH44JZI5RaJYo4BfJ%2BxZE9x7Y8E7RaKGp7iU6FJ9papck5EZUby9k%2Bc44DK6YeC9C5Piq/NBq79Ri5IG05sbbfseFeYSM8oB541egZ/sdCSCSH8AAbNdgc18CANac6ZZc9sDtb062GfpAEkH8GleAcCFgY/skD/q4C/s61y6SD5%2BN6Qbl/0/Ac4aN8K8FfbZ2H6dyGcEkCAA%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/omennivore/zip/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/descend/omennivore/zip.hpp)
- [Unit test](../../../../tests/unit/metafunctions/omennivore/zip.mold.test.hpp)
