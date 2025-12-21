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
/**** IsMoldful ****/
template<typename>
struct IsMoldful
{ static constexpr bool value {false}; };

template<template<typename...> class Container, typename...Elements>
struct IsMoldful<Container<Elements...>>
{ static constexpr bool value {true}; };

/**** IsSnowful ****/
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

## Links

- [Example](../../../code/facilities/metafunctions/omennivore/zip/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/omennivore/zip.hpp)
- [Unit test](../../../../tests/unit/metafunctions/omennivore/zip.mold.test.hpp)
