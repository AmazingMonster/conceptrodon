/**********************/
/**** Dependencies ****/
/**********************/

#include <cstddef>
#include <algorithm>
#include <array>

/**** Typelivore::TypicalAmong ****/
namespace Typelivore {

template<typename...Elements>
struct TypicalAmong {};

template<typename First>
struct TypicalAmong<First>
{
    template<size_t I>
    struct ProtoPage {};

    template<size_t I>
    requires (I==0)
    struct ProtoPage<I>
    { using type = First; };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>::type;
};

template<typename First, typename Second, typename...Others>
struct TypicalAmong<First, Second, Others...>
{
    template<size_t I>
    struct ProtoPage 
    { using type = TypicalAmong<Others...>::template ProtoPage<I - 2>::type; };

    template<size_t I>
    requires (I==0)
    struct ProtoPage<I>
    { using type = First; };

    template<size_t I>
    requires (I==1)
    struct ProtoPage<I>
    { using type = Second; };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

}

/**** Florican ****/
template<template<template<template<typename...> class...> class...> class Sorrow>
struct Florican
{
    template<template<template<typename...> class...> class...Warehouses>
    using Flow = Sorrow<Warehouses...>;
};

/**** TypicalAmong ****/
template<typename>
struct TypicalAmong {};

template<template<typename...> class Container, typename...Elements>
struct TypicalAmong<Container<Elements...>>
: public Typelivore::TypicalAmong<Elements...>
{};

template
<
    template<template<template<template<typename...> class...> class...> class...> class Vessel,
    // Extract items from a packed vessel.
    template<template<template<typename...> class...> class...> class...Flows
>
struct TypicalAmong<Vessel<Flows...>>
{
    template<auto I>
    struct ProtoPage
    {
        template<template<template<typename...> class...> class...Arguments>
        // We warp each of `Flows...` into `Florican`
        // and invoke `Typelivore::TypicalAmong`. 
        using Flow = Typelivore::TypicalAmong<Florican<Flows>...>
        ::template Page<I>
        // The `type` we obtained is an instantiated `Florican`.
        ::type
        // We call the template member `Flow` with the arguments.
        ::template Flow<Arguments...>;
    };

    template<auto...Arguments>
    using Page = ProtoPage<Arguments...>;
};

/**** Minimum ****/
template<auto...Variables>
struct Minimum
{ 
    static constexpr auto value 
    {
        []()
        {
            std::array array {Variables...};
            return std::ranges::min(array);
        }()
    }; 
};

/**** Total ****/
template<typename>
struct Total {};

template
<
    template<typename...> class Container,
    typename...Elements
>
struct Total<Container<Elements...>>
{ static constexpr size_t value = sizeof...(Elements); };

template
<
    template<template<template<template<typename...> class...> class...> class...> class Vessel,
    template<template<template<typename...> class...> class...> class...Flows
>
struct Total<Vessel<Flows...>>
{ static constexpr size_t value = sizeof...(Flows); };

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

/************************/
/**** Implementation ****/
/************************/

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

        template<template<typename...> class...Agreements>
        using Road = Hidden<Agreements...>::type;
    };
    
    template<template<template<template<template<typename...> class...> class...> class...> class...Agreements>
    using Cool = ProtoCool<Agreements...>;
};

/***********************/
/**** First Example ****/
/***********************/

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

/************************/
/**** Second Example ****/
/************************/

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

/************************/
/**** Third Example ****/
/************************/

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