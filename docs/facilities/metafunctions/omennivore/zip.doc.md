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

[*Run this snippet on Godbolt*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwA7KSuADJ4DJgAcj4ARpjEIADMAGwAnKQADqgKhE4MHt6%2BAcHZuY4C4ZExLPGJqRl2mA75QgRMxASFPn5Btpj2FQxtHQRV0XEJyem27Z3dxX0Kc2MRE7VTDQCUtqhexMjsHAD0AFTnF5dX16fHJhoAgmcXANQAIpiZrozIeJgKL0ud0ezxuYKuwIe9yhZiSEWQ3iwLxMSTcyGW6CwVBR2Gh5jhDARXiRKLcxEMwH%2BOLxsPhiMwyNRHXJAE9qY9oaDTi8ACosr60PAANxI7BAfMyeFEtAeLAEwEBF0hzDYCkyTEOvP5A2FouRgSsHMeBEwLEyBhNpII2pVmAAdA7sPQ2IIFOyHstiF4HFrJdLZfL9VZAm8UYaocbTeamJbUdavraXgAxPDEZbuz3egi%2BqViANGUkptMEd0mA3Ql6Vl4ms0WzCk3IAL0wAH1swBJd1Vl6Zn3KYioIjKJiUoNl0NJcMVqs16OxtxN1sdrtV4iYACOXlT/xeEE7SQnbw0W2nld72f7g9Qw8ppP3uMe3bLFheXlyRmr2sZb2TqfTk/1Ccp0fGcozrUkmC8IgHTtB5gDXU1GAIN0kgfB5uzfCIFRvBkUR/S8hxHetUTghCXWQmCcRAEB42IqcQzDPFI1rGNiLcWjEyLZZSE/BNWAZIRmgEdAeI4/iYIAeQIBAEhQtDzxzf05QLVEuIIHjBLQBgRJeKSZLTSjULxcsQMrWdwNRRc2xee9Tx7AgvT7AdCNHOzn1fd8FVo79FLzZTgFJPTZMM7BqPM1iXgI68iLvF4AFoXjMKiaO1MNAMYo10NAlj5ys5cjNMl4103bcAT3PC8OPOyFKinC7xXSt3Mwj9vLw39izS8cMojLKzLA1iGzwZtrNswriq3Ncyv3Q8uBPQqauc6Lb1RUbeqDDysN43CDxeTThM6hjJyYtbwvnSDoIdUjMEQ10Go2j8cJ82qYpI%2BDrvIhQQu6rqjsyrrMq5ZNaBIXMGEVc5IVOtioatfr5xhuMbXEh0cReBEmAUT6UdQtGDExkLcYxgEhBIAcAHcMwcrMgZB0QGGM8NuwR9i4eh1mrSRtgCfR/HsewQnebtAB1DpMAQPYlDkuzmoVJNgbJnySeIcnSRFtdxbff4vt%2BqFDuAp5Ll8mV/PB25oWZsS2EpxzswlXNjcDZ8fv1i32cRviub5gWAQ8QQmDWMgtttGCnRu5Drepu2lPlUlffaAPSVDj7tbQkAXkyLxYkFZBfR1EU12oqO/Jj1Ek6QrG7VLcs9eOmGOVROzXZytnm9h1v3cYZHK5xnmK9R3vubxvue6Hl4ADV/jsUg7OOY4XmwVQHI1bNCFNAEqAHFgXiYdONQAa0wdAXiFSeBkrwqm7nFur45j37S9geH6HweiZguXUDJt16/kqmfSLh2VJuAnpjAYhZ5bD1xAVXWjNso3yZFBVANk7oLSvHVQqTtCpMzdizduOC4HsU5vfbu/NH7EO9jBB4xBgA%2BHLndbss8XhCwZGTDomQXiYA1AgF4qAqDIhSBod%2Bn9KL8JeBEIgfCBHA2IKDEw/C7L0LnoYI%2BEQRQHwkRKPOopC78ntvmAK/C7TIkwVWGWNMFZtQ0YKfOYp/56LAbTQw9jP44i%2BsYysYVWaRRem4Va3YFG8hkhI2isiNAvDJgyVAsR46RGUQCQwoiGDLEMI4ViR8Qnv2kXTEJ581rdjCqlNxLwGFMLRmIWg1ZAlQxeGwDYxAJGCJCWEwgXDpIMg6NQ5O8iqweObmY0klCOnl21jAxqNdMpYNwedVAFCqE0NulAjCnkvGuR2s9ZabgBlzIonzb6YyeqAwALIRDwCwHwptIbYKmTBMeHQ8BMCzlSKBCkjkMBOT4BmRi1pJMcDnLSyxMCqEyHUqZx8xBeFwugkyuSqwmH8FYfwbwIBzWhaMkZfjuwYmosyJgLJt7KxxUGG50j7n0D7ns9F6K1wEH2GDTFIByRGH%2BNRFgEQIDYpZCeHWFLAJIrcnrT5ztjqAx5IOMQ5zzbYMtsRH%2BNteSivKU7PZErW71zcI3SVhCX6YxeHHf2kQyCN01Y6Z0tDv7QgUiK9otBY6yD1QkROJrXQpw%2Bd8qUaMBD/MBXUvKoLvDbR/IuHhMEIBl1dJyl8grMp1yhA3C%2Bkr424ItkashpD%2B7Pyfq/DN2rgFT3VYmhN%2BCpVaogeQrNFdBFfxjTKyO8rSQ5tAapcBzqOQGnsjGN1fyTRep7ENJcvrwU%2BUDVQYNFbw3pR1pyQ27YFAHM8OgKgXhylAmVYWwhEcfTTtnbQedi6XXtB%2Be6xJXagUvFiKgTw/bcIGioGIJQztx0uwLRZAhd9i06ttQHUSybQ3hyeb/DsM650LutaiXVCdS6Ou2cQquL5XW/I9ceupZ6L1CjBVeiwVN6z8sjfsqdCghAMA/sB8VzFV133XQBgjRHd0ttg/ujtCGAUnuQ%2BU1Dfqgw3toHe7DSrSPgVVXmwtT6Bpxg1a%2BstxbJNlt2nQH4mBp5xvzUpsjndPYpvTepzNmnBZKxVmax4Clp1UbJsB0kQhZOEjYrpj%2BzboFtoPZ2pjSHz2sbQ0GTD96cOTvBD55dIIp21jDu2gQJGDa%2BfC5CFdz6i0OmHMgA%2B6B61cYoy8AAWngNhiqgJCrnulth6p4uHwkVu9AITK1JvE3aOLCWktS0eONUqu5KJmBSOYFIm6gO7tRNVw%2BtXkpsfBcihSeXSQ9cS6fLjrjoGCei2J1TRC01E10l8ckQxkH/siotAASqgJgpXIVoomfgn1viKUKQ%2BPHa1hSMEor8aY1qO0JIreC/TQpT5Y23e5VKo2djuv716xNurn2KU9Kvpt1B3jTvcvRfkr4lE3swqMlyilXnCnMyuZdN6YcgfctMY9NqF3/YgY2Vj5OfNYd0WOl94T8Nk2Le1RJKCCQnsJBe3QqsCkAASeBMSMC6ai/nfiKvzam9DjnG3NJUrHLx4HfVcF5RglD6HClJeYBLJZAg6BqIRCwKoFsShNxybvLZsXqL7peS/G1RnJpiAs9W/kW%2B833hq6J/VVCFPhkPqp6b%2B7ludqq5LAjxqH3Td%2BLpSwJgB8Ww64Bfrjc4LLOC%2B5aSF5byWCkktWIUb/3xsgOS%2B7kAA2FsF6L%2Bz9FZe/EU%2B6snmX1PlPRbpyPLTV1scV9MTtvbPlue8/pq9MiQzycpS%2BNXmF5KYWKaE4mxvJCNMt4%2Bnddvu20mrO20v/ppOB/QYnTLhheXd6FbSfw4zZWosiZfSL2LOe%2BtQIa5NJrKMWttaM4RkzXW3Bjev6FQvaGhsbZG39g/WrKbG7I7WbevM/S%2BBvSrenEtVNJvQWGA5bVnNbBZcXWVKKDwTwPlQ7WBZ9E7Cvc7F3OgQXEAn3JZB7H8O3NnIPRkNwWxfybPQAwHZKKpNZNie8UHOsMxYZEg2vCldHBBChDfeZNCXHJZfHHaQnYgvvd6TfFg1KCdNHGnaGafb2XSJnW3Z7FA0Qs7DbbvLAV7W7UgsXYXYOHZGglXZoKXLLb6Gg5mBXB0JXblSw5AKlBsTXbXbSWPA3BPQ4Y3HZVAsXJqcgv3SgjQqglA8/RMKQ4nDgofYvSBCNPgsXX3L4RWKwtXJPRHNVGgjFDwkACPKPGPPXHwo3XI7I1PU5dPVETPYnD/ZgkvNDEKaiUvQI6HCvPJeIkfcvZIoXZQx3Mw7TCuOfWhNoxZTaDvZfH8fQvnGQ7HZoro5HUZbLdBCfMAyfDY9YqAi/IYqTXYiTTHfvEQ6WJZTAhVFfK8M49fI4qDakbfFY3DcLHzSEQGNSeeVQVgc0BkPzMLJ4sESLfzV4MDfVAEH40wruFLX2FsDQWwh4cEtTSEgQFsLgWEwGMkHIfDZoIYULeEhI81DbdEzGTSIYaE1Ew2IQLwTIMoQ%2BLbf4RdbMH40xCkqknIGkuk2gbMNqQkzEloJEmE1EMRc4HiEUHnc4O4/WQGWkhQek0Ldvdkzknaf/NwKE/ktwMRHiQUjUwQMU1CHiKElE1EEUnSI004YU1AUU04O41OEASY2OAcIkrE/IUkqBaiOqVEJKJHCUw2Hkf4BkpUfE9tZAFsImBIAgCAOlBQfiYMlCNwZk6k9AKU%2BkniRMjknEcNIVP4547zc4XaISbSd4z4%2BgULLkTMiEDM14PLL4I%2BMEubQYlLSsw%2BMk14OM1khM%2BU2UpZFspQNs6Ujk5EnyBs/bGNZU%2B0nkkk1U9U4%2Bc00rXUnVUc4kp0ic7Us00Uq0psnMlMv0iGaEOU3sggfstqJUlU0kScwUnEPUpEg0twI0lc9AU0qci0tcx4aiW00Decx0vk90F8tfVEQc8U8snMn05YULODaMpQTocM/IyMtgaMszSk%2BMzc5E5M%2BU5EtM9c0ssswEwChAVMI%2BBeQs74/0rCjCn47M7kCtHE/o0TKfaA%2BA2AjTFLQRaE/kx9cA%2BGWsiEuivYxi%2BWaEg01izYiAjihErig46DAzDbJirgFi2uKivBbYus0S/Y8Sj0SS3irgfigC7kWrSiti6%2BLYiA1QuAmfLTGAqbBSYBZ0gSgy9ivSgYzikyhApSsy8w1S2VSyzSgGQ2bkhcy83SwS2ygKlQ2ixy%2Bi0y5yv9WVHyj8hgTnAYFbVC2jc3LaHyI0g6B40/QKhShy0tFS87HwFgFkV86ygaATNYoSuyjuRS0K7iuil4B4BTE6OS3E2qmq6TKcG/ePRrCMqMjGfpUkN4Aqoqn87AHiJijQVUwalgQq18yBNCNrNreyLXEAaC1sPq1EKwVEKamakasa9Syaoa2ayE983k2K%2BKhIVCkiHiTa%2Ba1tVI/1BJdXJIjKvjUq4cmbCqoK%2BykStq5SxAhqj6rKz67Kn63KlyoYl4DqtCW/HcHqmC9ajZAaw63asxPipG6a4avbJ8mEVrFrJa6iVa2Cja9GnarG2cqSq87azGmcua/EqKk6oYOK2gBKq8hqyGmDZKigx6y0gCVHOE5q5qoyhiiK36gZIHUxaK06g8naSWxm864gS6jZKhCBKvRQ347kLstkvcjszaTWns%2BklsMwAcjLKsk8wQLUggHmxIrSl4TcnWj8RCo2w8jLOtf4Z0twcajQPaj%2BNG2cjypxZEr21GjS7G6iK4t8jE3yhgS66018twP8z0m2oC5CEC%2BjIMkMzoaECAaqKC3qytd7HI27BOkcyOmKxWz272smQO88uc0uqWq88argSu5Eg0uaxq7lYu087Uu6d0dMiSwMsC0MyC5awmhGx2jSeC1sx2tCycDgHYWgTgfwXgPwDgLQUgVATgNVSwawHsPYA4XCWEHgUgAgTQOenYPeAISQO0DQAADjMDMDSDSC4H8Fvpvq4ECECGkAXo4EkF4BYAkAmtIBXrXo3o4F4AUBAC9pPtXrntIDgFgBgEQBAD2AIAznUgoAgDQDNFk2ICiH4k4FUBvpSDihSEkBeGAGQBzikDtDMF4EPkIBBi1ybv4EEBEDEHYCkBkEEEUBUHUBgdIF0CbrJnJEyE4B4HnsXuXtPvXs4GtzQe4V4UIeIdIfIcoZeGoaNogA8GwfoDqXxFml4Gga0B2AgCQCwclF0fIEoHMZwZAGACkDMD4DoBtwgYgFiGkdiAiA6BZDEd4E8eYGIBZAkliG0CxN8dICwfIgkgYFoB8f4awFiC8GADcDKQge4F4CwAjyMHEHie3BaBPjSbXoBWaCZ3CbEQGGkcFFiHJECY8CwGkYchOXCZPmIDPSUA%2BCyeAEFCMFPp2CoAMGAAUDHj%2BDJhZxXqPpYeEGlA4ekEmZ4bUGkcEf0ApBQGsGsH0DwFiAgcgB2FQEyCGDSbigxDwlMG3ssDMBAZaekSwG2aRX6EGHyBcG0gWD8CbrCDWBqDqD0DKDyAEBee%2BZyF%2BYYHGE%2BamCbqaFOpGHmE8B6D0AhaGChdWGqEmESHBZWH%2BbRdGBBZRYkB2AUD3sOFxf0EkaAekdAZeCUZIbIYoaoavs0dwAYb0cPq2EMd6Z2Bkj2ymDuYvskCSDtDSCSE/o0EkDMEkH4Q0H8BmG/t/tIH/qSC4DtBSC4BSBvrSDfpSH8EkGfoFZSFJf4dAfAcgePt6bgcQdMeQagjQascwdQB0YSDwbYE4A6BYCFECDih3nRg/C4DSDtAVaKfwCIGub0EmbYfEE4bmaUAWf4d0EceEaYFEfSYkY4CXr1ZAdkctaggUYpaIapcJi9Z9b9d3G0YsYSGRFhDMBZeNZgZMbMdtZLbIAwZsd0ZQAMCMG9ekqcY5NkkoHcf4f8e8fCf7cCeCdCYcHCciaQmidiekYSaSZSdoC43CcyYpBybXvwDXHyaZX4eKeQFKfSfIEEAqf4aqZqZZDqaODXsaf/v3ZabacwA6ZXawhNf6ZHCGZGbGfCZDemYkFmdkHmb4bXpjeWZ6dOasEsA2a2fgF2f2fyEOeOYPFA%2BsAud4FQCuZ5yZR2fuZiqefcBheKDee0mxdqQBfKHyAxayEBaGCI6%2BfBYGBisRfI/hdaBWGo7BdmFGEY5Y4%2BZxdml2H2EJd4%2B/pTeAZQ84GzeUbIc9YVG9d9evt3AZcDbLflcraMbPtIA5awESDuelb/uSB9eFcCH8DSA/qSBFbFa1dTdE7AdsCNdU5MbNaQBQatcbbrZwYdaOGdZUZYAUCFBziFBk7rGWDoYDcYeDdkFDZma4fkEjYA50GSFIDjYTfEeJeTakf1fTdQczZ4Qpa858784C9YmAq0dc90aU6SBU5NfNabYSGteq8SF86pJbH87SBbEC/3NUFIc7ZcZ7Y8a8cCcHb66CZCbCf3YncECnbibXcwESeSdSaXdNBXYvYybyccAKekZ3b3aPvKe/rXpPe8fPYaekWvaPtvdZIfeyaferb4AGbfcwFGYTE/fC%2B/fDb/Zi8Wfi9beMDWfA6qdueg4Oc4GOExUQ/OcuYSGuYw7uaY%2BcAgFcHI/eeReI6bp%2BaGHI5R/yFY9Raw8hfRbw9eex4Ra48R5o/Y%2BhaKHx6SU6Ex6Jfxf444aTeE7JbE467Ie898%2BPgK5NCK4U5ICU4MareMfZY4U08oCTZlf/ofrtCSCSH8Bfq1Ymul8CBVcs5kes4gagbZdIB5f8H5ffsCAmpvskCfq4DvpaxS6SDS7Tes7s6TdoZV4NYF7U5adyGcEkCAA%3D%3D)$Done$

## Links

- [source code](../../../../conceptrodon/descend/descend/omennivore/zip.hpp)
- [unit test](../../../../tests/unit/metafunctions/omennivore/zip.mold.test.hpp)
