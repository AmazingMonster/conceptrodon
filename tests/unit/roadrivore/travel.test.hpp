// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_ROADRIVORE_TRAVEL_H
#define CONCEPTRODON_TESTS_UNIT_ROADRIVORE_TRAVEL_H

#include <concepts>
#include <type_traits>
#include <utility>
#include "conceptrodon/capsule.hpp"
#include "conceptrodon/descend/roadrivore/travel.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/judgmental/equal_value.hpp"
#include "conceptrodon/omennivore/concepts/valuable.hpp"
#include "conceptrodon/shuttle.hpp"
#include "conceptrodon/reverie.hpp"
#include "conceptrodon/phantom.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/judgmental/amenity/define_equal_value.hpp"

namespace Conceptrodon {
namespace Roadrivore {
namespace TestTravel {




/******************************************************************************************************/
template<template<typename...> class...Containers>
struct TesterA
{ 
    using type = std::tuple<Containers<int>...>;
};

template<>
struct TesterA<Capsule>
{ 
    using type = Capsule
    <
        std::integral_constant<int, 0>,
        std::integral_constant<int, 0>,
        std::integral_constant<int, 0>
    >;
};

template<typename...Elements>
struct TesterB
{
    using type = std::tuple<std::integral_constant<int, Elements::value+1> ...>;
};

template<typename...Elements>
struct TesterC
{
    using type = Shuttle<Elements::value+1 ...>;
};

template<auto...Variables>
struct TesterD
{
    using type = Shuttle<Variables+1 ...>;
};

template<typename...Elements>
struct TesterE
{ 
    template<typename Element>
    struct Detail
    {
        template<typename...Types>
        struct Hidden
        {using type = std::tuple<Element, Types...>;};
        
    };

    using type = Reverie<Detail<Elements>::template Hidden...>;
};

template<template<typename...> class...Containers>
struct TesterF
{ 
    template<typename...Elements>
    struct ProtoMold
    {
        using type = std::tuple<typename Containers<Elements...>::type...>;
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
};

template<auto...Variables>
struct TesterG
{ 
    template<auto Variable>
    struct Detail
    {
        template<auto...I>
        struct Hidden
        {using type = Shuttle<Variable, I...>;};
        
    };

    using type = Phantom<Detail<Variables>::template Hidden...>;
};

template<template<auto...> class...Sequences>
struct TesterH
{ 
    template<auto...Variables>
    struct ProtoPage
    {
        using type = std::tuple<typename Sequences<Variables...>::type...>;
    };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;
};
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    std::tuple \
    <   \
        std::integral_constant<int, 3>, \
        std::integral_constant<int, 3>, \
        std::integral_constant<int, 3>  \
    >

SAME_TYPE
(
    Travel<TesterA>
    ::Road<TesterB>
    ::SubRoad<TesterB>
    ::SubRoad<TesterB>
    ::Road<Capsule>
    ::type
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Shuttle<4, 4, 4>

SAME_TYPE
(
    Travel<TesterA>
    ::Road<TesterC>
    ::Rail<TesterD>
    ::Rail<TesterD>
    ::Rail<TesterD>
    ::Road<Capsule>
    ::type
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    std::tuple  \
    <   \
        std::tuple<std::integral_constant<int, 3>, float, double>,  \
        std::tuple<std::integral_constant<int, 3>, float, double>,  \
        std::tuple<std::integral_constant<int, 3>, float, double>   \
    >

SAME_TYPE
(
    Travel<TesterA>
    ::Road<TesterB>
    ::SubRoad<TesterB>
    ::SubRoad<TesterB>
    ::SubRoad<TesterE>
    ::Flow<TesterF>
    ::Road<Capsule>
    ::Mold<float, double>
    ::type
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    std::tuple  \
    <   \
        Shuttle<3, 10, 11>, \
        Shuttle<3, 10, 11>, \
        Shuttle<3, 10, 11>  \
    >

SAME_TYPE
(
    Travel<TesterA>
    ::Road<TesterB>
    ::SubRoad<TesterC>
    ::Rail<TesterD>
    ::Rail<TesterG>
    ::Sail<TesterH>
    ::Road<Capsule>
    ::Page<10, 11>
    ::type
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/judgmental/amenity/undef_equal_value.hpp"

#endif