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

[*Run this snippet on Godbolt*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISVykrgAyeAyYAHI%2BAEaYxBIArBqkAA6oCoRODB7evv6BaRmOAqHhUSyx8VxJtpj2xQxCBEzEBDk%2BfgG19VlNLQSlkTFxickKza3teV3j/YPllaMAlLaoXsTI7BwA9ABU%2BweHR8e72yYaAIJ7BwDUACKYKa6MyHiYCjeHZ5fXJ39H3wu5yBZgAzGFkN4sDcTKC3MhxugsFRYdhgeZwQxIV5obC3MRDMB3qj0WCIVDMDC4S0CQBPEmXYG/XY3AAqtKetDwADcSOwQOyUnhRLQLiwBMBPgdAcw2AoUkxNmyOXUeXyYQB2KyMy4ETAsFIGPV4ggq2WYAB0Vuw9DYggUDIu42IXgcyqFIrFEs1Vg1d1h2qBuv1hqYxrhpqe5puADE8MRxo7na6CO7hWIvUY8XGEwRHSYtcCbsWbnqDUbMHiMgAvTAAfVTAElHSWbsm3cpiKgiMomESfQX/aDA0WS2XQ%2BG3DX602WyXiJgAI5eePvG4QZugod3DRLUfF9upzvd1C9ol4zdoy6tgsWG5eDJGUsqql3WPxxPDzVDkfXschis8SYLwiCtC0LmABd9UYAgHVBK8LlbB8wklM9KVhN9jx7PtKzhCCoLtWCwNREAQEjXCRz9AN0WDcsw1wtxyOjHNxlIZ8o1YSkhEwNAGHQNimM4sCAHkCAQOI4IQw8009cUszhFiCDY7jeP4m5RPEhNiPg9FCz/Ytx0AuFpwbG5L33NsCBdDsu2w/sLNve9H0lcjXxkjM5OAPENIk7TsFIwz6JuLDTxwi8bgAWhuMwSLIlUA2/aidUQ/86MnEzZx0/SbgXZdVw%2BDcMIw3cLOkkK0IvOdi0c5Cn1cjD31zBLBySoMUoMgD6KrPBa1M8zstylcFwKzdty4PdsrK2zQvPOF%2Bvan0nJQ9j0K3G4VIEdBmqo4caIWwLJ2A0CrXwzBoPtKqlqfNC3PKsK8Mgs7CIUPzWpa3bkpa5LmVjWgSHTBgpX2QEDoY0GTU6ydwYjM0hKtVEbkhJgFBe%2BH4MRgwUb8jHkY%2BIQSC7AB3JMrJTX7/tEBhdMDVtocYyGwYZk1YbYbGkaxtHsBxjmLQAdRaTAEDWJRJIs2rJRjP7Cbc/HiCJvF%2BYXIWH3eV6PqBHbfyuQ53NFTygdOYE6cEtgSes1NBXTPXvVvd6teNpmYY41nOe5j4PEEJgwjiASWcta1bRg0XLmky3ZIlPEPeab3iDxG1zqIznHRAG4Ui8aIuWQd1VV5BdSLDjyI7hePntexlC01vbwcZOELIdtLGYbiGm6dxg4YtBH2dRjv0a7tnMe7zuB5uAA1d47FICztm2G5sFUKzFVTQh9Q%2BKguxYG4mFTxUAGtMHQG5uXHuoO%2By%2BuJ0bi/med/2e65vvXYfu%2B3bAyXUEJh0a6k0m3QL635LcGPFGdRsxS0HjpLKGsaapSvtSECqAzKXSmieCq2VbbZVpo7emLdsGwMYn7fuuNCE8wuMQYAPgg6XVbNPG4vNKSExaCkG4mBFQIBuKgKgMIABsGg34f2Ijwm4YQiDcN4X9YgAMTA8IstQmehgD5hF5HvURgoc58nzhyK2mYvI8ItDCDBJZxbk2lg1VRXJc78j/to0BFNDA2I/qiMuC1WwBQZsFe6bh5qtlkWycSojyJSI0DcQmlJUDRGjuEBRHxDBCIYLMQQeB6IH0CW/CRlNAmn2cSWAK8UDHFhoXQxGYhaClj8aDG4bAKhxFEXwwJwTCBsLEpSFo5DS4yOyWRNxtS8JkIofaNW0DqqV2SpgnBR1UBgVIa0yhkCkLOXcfZNad1ZpuCmX0xOd83rDLaj9AAsmEPALAfAGxBlg8ZYER4tESRnYkkDpL7IYIcnw1N9ELVmI4LOvFxiYFUCkYgm94GHzEF4dCaC9JZOqgkKwCQ7gQAmhCgceTvGIlIjSJgtJN5y3RT6S5EimA3MHts7xxKcqYAIOsQGKKQAEiMO8UiLAwgQDRbSPc6sSXfjhQ5TWry7Z7R%2BqybsYgTlGywSbXC39zZskFSU222yRVNxrm4OuoqCGP2HlHL24QyB11VRaEulCv7AlDtKyOshNVxDjoHfpSdIGOXecKRGAhvm/P%2BRlIF3hVpvmnBwsCEB9X2lZXeXlyVq5AlrmfUVkacHG11UPIhar43PyfnGlGo9j60EnhG6NUa8FiuIeA%2B%2BA982vzAeiO5P8LYmrhEAuw9iC35i1JZMMDqvl6hdW2HqM53Ugrct6qgvq%2BEKEDYldWTIdaNgULszw6AqBeBKV8eVua/ZmzJhOqdtAZ1zpefaz5Tq21/JuNEVAnhu3oS1FQMQSg7Yjvtjmoy%2BCb75puBqmOvtH0BwTsHJ0FazKTunbO2gprPYx0tZ%2BtWCE7XNA%2BY6uJ%2B7/lHpPdyYFZ6LCk0rNy4NOzx0KCEAwd%2BAHhW0SXTfFdboJ24fw1u8ud4d0wedQehDJSkMep9Be2gV6MNyqI4BRVyrs38dzSq99Sai0Jp5imgtbt1p0BeJgTN%2B071dQjEJtuLsROJok8Wq0st5aGpDj%2B8jeHCYAbxEIGTWIGI6ffuB7dUGW17p%2BQx49THkM%2BjQ9ezDY7/jeYXT8cd5YE7NoEIR7WPmwuAkXfevNVpezID3ugGtdQv3SQAFp4CYbKn8fKZ5paYQqOL%2B9RHrq2jwz%2BFwY3Cdi/FxL7HHSDXyuuYiZguHmC4Wu/9W64RVf3jVySpFmMgvhal9LeJusJfTfW6jfHBPRtjb3YewkngEgaEgn9IUABKqAmBbTBYM7xdM3VeJJdJB40dANIvQQiuZy16prUW3EILVMkU3nDVdklYrdbWK67vHrE2qHso6eU5ZDEjsA%2B8Tkp4xFnslhJGyklnmkV03OSdR6n7/vFiMTdBqp2vaAYegRIOfkIcUT2uy8%2BUW5uFtxupECcR7vLayOjyykqAASeAkSMHaUMvbZOVPmicWDg8P6VILlTJlt60OOo4IymBUHAPpIi7JVWAg6BSJhCwKoOsShlyyYvDZyXi0jG3bfMJWnxB6ePevqpykOO6CVXgsTgZN7SeC6Ny%2BBqiu8wG7xFz%2BXKv6VMD3nWdXPytdLhBRZ337K8QPKeSwPEArmh47cGN3rsUBu33T8hpnL2EKC5uMT1q0euMIvJ0ph91utPgVR89JnRjNvbbcmzjnVN8dPUJ5zQvcOhlZbQVmmbxHK9ie7qdNHszDHzIb8kpZ00p94lH6XG1lFe87Jy%2Bl7eBXkk8Io8TUrkXy/RYtKnv7kD6vDUa/DZrrXDOUeT8f4BtWHcgAz0Nn9uXRs/fGw/ybUDptRcU1DAAWDJTi/MPlXhJupEtpbuPkLpKiFB4J4FyjzjAveodkzidmSrjr7pdvnm7k8G5Bbitt7nCFYp5B/pvmnk/kDtNBVHNLFOUnwgMtgSXrzmMvApMjXjMnniSpjjhG5Lbsngvh3nfF3lrKwQPhTsJhAabnqOblAStjAcij%2Bs3lgE9gijgYLhVkPpsgbgrjxKLgOCwZoVgjLlaHLuynocgKLsrqriACHprtrhHpsHrjatwWDjVPMsbjTrIYQYzq3NGAIfbv5HFJDkvs7iMq7p4e7mtJ7lHjDq9vnq2FSiwIHvWPYWHjrpHgbi9m4LHkcvHiQVWinp/pQcERnkTs/tnoodHtUSSqIcwSvr7mXlDCAU/EIRdLURjpPlttPm%2BCoZzm3mBp3iESTmCivjeP3v/gJlMRIQfq0aJupuJvNhpssSQpwR0W4VdJKAgTKjPieDsfPusRsrDsvhLqFmFv8ICD9IpLPKoKwIaJSL5ucRcScBFn5rcC%2Blqh8E8VofzknPppKh7HWBoGcb8e3KRqmECVwGcT9PiOkDhjxA0CFmCWphCc%2Bl2CjCpA0MCTCTrEIF4CkIUPvOtu8HOqmE8UYviYSekMSaSbQGLmtHCZiYiVkDiXCMIvsGxLyOzvsCcXyjrCSQoGSSFvXnSQyW%2BO/nCECSCeyYIGxByfKYILyfBGxFCXiNyWpBqbsFyagDybsLDghKRHPlKRiQiQ4KyTKYaSALQW4DFBAlrPyu8OSdKEanZsgHWLjHEAQBAFSgoJxB6XBG4FSUSegIKWSWxGGfSaiIGvyS8ZcV5vsOtDxJtLcfcfQCFsyHGQCLGYmblk8AfD8XzuCeWpKnmfvLibcMGTSaGWKSKfMlWUoDWUKfSXWFwG5GWTtmGm4EyWadiTKW4MIjqezqiKqaaViRaXiAqYfLqegPqRAmiKOu8YmZGc6cDMCKKc2QQK2e2SNlKQIGyQOXKbEgQHOdgKqfudCXCBqUObOTecqQuVacad2WOSyfuZacCEaT0XiB2Xyd9DrKyE6SFjugGUoK0D6f7iAH6WwAGaZgSSGSua2RGWKa2dGRWVmccFcf%2BQgPGAfHPGmY8S6UuehU8QmSyIOsiUAc3IPn8YsZJsmiWWTHwsCTKbetMQfkWaiasXRQsWiUxRoJeaxbMYAbNlIVxeAQxW6ExVwCxVXJRcpiJdoZpmAf8d%2BpKlJQJTmSyL1hRWxcJUJcAaJVTksUZdxSsRKmTEAmyYJTMTZexQpTRUpbReJeZW6JZRpX%2BR8S%2BeaReTpfpVRbZS0YZaAU5cpToapWTD2eOQICznUEtihdRlsStG5BqdtI0dxnZdRcWSZU4idj4CwLSMadZV1LxpMRlQFQZYpWJaFRARcPJqMn5fJZlZxdldVVxTcCOKfuHg1r6f6cjPPniHcHlQVV%2BSqcYsxQNUNcaQ%2BaSC1s1pZLYVBfWH1XCFYHCINSwPlVNWxFJf2etZtSNdNQCRFV5Q0DFbQHFZeasmxKtRBo2ngZ6sealaCUzCVQprpZfJIZVS1SFbRTcLVX/mVYDYFV9cFY5RAR1QhGfmuD1dBctashNRtcNdtiOWNfxQjftcjfOTNa1vNaRItTBStejUjVtKNepUTVNWiZFa%2BQwGdRdfPtdQ2nePdW5ByU9YueVnJbguVVbg5VVT9Y5VMl%2BkYlTd5QwNuQ1CLadbFXEChT0sAAWvUR5YmQ2bSZuXWctCrU2WSXWGYDuYSeWbKUpMeaeWhSyCuerU%2BAhbrQ1JKYAu8AeXxckKjZeWeWmgoLLW4DtdtVLK2S7cnCAAcSafCVFWLX7ZcJ%2BZjW4D%2BfaZpWyE6d8YRd%2Bs2u6Z6a0MCBAKVBBfjX1WggkSStHc%2BcHdTR7Y7d7e/K2ZaaOUXaLSXT7fxWXYTL7QaXVfnelvmZOUeazYoY6DGfpsnSBV6eBQtb1YGVbcpHBdWVbahcOBwCsLQJwAkLwH4BwFoKQKgJwEqpYNYG2GsBsOhGCDwKQAQJoLPSsDvCAAkGYBaBqGYJIAABx31JAACcl9GgXCd9oI%2BgnAkgvALAEgGgyQy9q969HAvACgIAyQx9K9s9pAcAsAMAiAIAawBAacSkFAEAaABoMmxAEQnEnAqgd9XCEUXCkgNwwAyAWcUgFoZgvA%2B8hA/0qugQ/AggIgYg7AUgMgggigKg6g0DpAuggQhMBIKQnAPAc9C9S9J9a9nAMhqD7CnCBDRDJDZDFDNwVDutEAHgWD9A/yGI40vAUDWgKwEASAmDQoOj5AlAZj2DIAwAUgZgfAdAsh4DEA0QUj0QYQLQtIojvAHjzAxAtIwk0Q2giJPjpAmDhEwkDAtA3jfDWA0QXgwAbgxS4D3AvAWAKRRg4gcTq45pR8qTq9PyPEtOYTwidQUjXI0QBIATHgWAUjVkhyYTR8xAR6SgDwmTwAXIRgJ9KwVABg8tI8bwhM92y9h9zDwgIo7D0g4z3DagUjAj%2BghIKA1g1g%2BgeA0Q4DkAKwqAKQDQqTEUiIGEpgW9lgZgwDzTEiWAmzcK3Q1NLgfEUwfggQIQ3sCwIwBQ6QmQAgjzeghQXzDA8wwwVQtzotfQkwngHQegdg1NYLAwrzQLULEwbQELeQgQswrQgLVSVQKwCgu9mwEg4jHAi9pAQDvAIDNwijxDpD5DlDkg1D64uA9DujB9SwBjPTKw4k22IwNz59kgoIFoT9oIGokgGgkgt9PCGgCQXCT9X9HAP9pAf9oIXAFoXCXA79T9d9arCQAQCQgrXCJLUjIDYDEDR9PTsDCDJjSDIEqDljGDqA2jcQuDbAnALQLA3IGoEUW8SMT4XAT9FoyrhT%2BARAlzeg4zrD4gHDMzSgczfDugDjQjTAIjaThLxLpL0jHAsjIE8jmKbrHrXrBgPrfrAb64Wj5j1SGIZgrLpr0Dxjpj9rZbZA6D1jOjIArr7rEU3rdjT90ljj9JEklAbjfDfjXjYTw7ATQTITDgYTETMEUTMTUj8TiTyTtA7GYTGThI2Tq9%2BAC4eTdKfDRTyAJTaT5Agg5TfDlT1TtItTWwq9DTf9x7zTrTmA7TG7KEZrfTfYCggzmAwzUYYTYbkzEg0zsgszvDq9cbiz3TxzVglgazGz8A2zuzWQ%2BzhzW40H1gZzZLFz7OdKWzILDQ9z7gKLTzQQfEmLiwHzRQWQPzlH/z5H7z%2BHvQSLNHjHAgsL9HwL6LyLuQJHXHHHBLqw6w%2BL40srqbhrnAOb7b%2BbhIajRbFoQSfqQbJAMILLbLNbHLLCWA8QNz89crv9IAoIfrorGourGoGooIYrkgJDgQabRrtgJrhjMDcDiDyDNrTb9b2DTrWwrryjLACg3IWc3IvrFoFY4wtDSnIbTDsg4bUznD8g0bYHOgBnpACbSbYjonkjfDIDmbqYHCObvn/ngXwXoXqYmjHnOjKnoIoIVbjntbKA5XPs7nDr8QAXhJdYQXT9dYJXHpxALAJDvbzjA77jnjATo7I3gTwToTx7M7ggc7sTW7mACTSTKTa7%2BoG7N76TuTjg%2BTUjB7R7h9ZTunq9F7Xj179TEi97h9j7NJL7WTb7NbfA/TX7QzIz/70XgHkbIHCX8zyXBbxgKzsHlT1ziHeznA2wKK6Hpz5zcQlzuHNz0LothHLHLzZQCLtHDQLHfzDQ/HaLdQMLzHxHULePoLSLOPtgBPPHiLcw8LWLAnuLQn7DKbmXwDEnPnpDfnAXh8xX9E4wDLEXlX%2Bj1bRjGnXL2nhL8rf9ZgfrVXCQSQAQADVXGo79BrWXnAxrkD7LpAvLGo1DJnXAUgT9xngrXAGosroIzPZLavQvp9srNDKvLPoD1vSwKwzTGQzgkgQAA%3D%3D%3D)$Done$

## Links

- [source code](../../../../conceptrodon/descend/descend/omennivore/zip.hpp)
- [unit test](../../../../tests/unit/metafunctions/omennivore/zip.mold.test.hpp)
