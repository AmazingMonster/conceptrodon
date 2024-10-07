// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_ROADRIVORE_TRIP_H
#define CONCEPTRODON_TESTS_UNIT_ROADRIVORE_TRIP_H

#include <type_traits>
#include <utility>
#include "conceptrodon/monotony.hpp"
#include "conceptrodon/capsule.hpp"
#include "conceptrodon/roadrivore/trip.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/judgmental/equal_value.hpp"
#include "conceptrodon/omennivore/concepts/valuable.hpp"
#include "conceptrodon/emissary.hpp"
#include "conceptrodon/diplomat.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/judgmental/amenity/define_equal_value.hpp"

namespace Conceptrodon {
namespace Roadrivore {
namespace UnitTests {
namespace TestTrip {




/******************************************************************************************************/
template<template<typename...> class Warehouse>
struct TesterA
{
    template<typename...Agreements>
    using Mold = Warehouse<int, Agreements...>;

    using type = Warehouse<int>;

    static constexpr auto value {0};
};

template<>
struct TesterA<Capsule>
{
    template<typename...Agreements>
    using Mold = Capsule<void, Agreements...>;

    using type = Capsule<void>;
};


template<typename Element>
struct TesterB
{
    using type = Element*;

    template<typename, typename Target, typename...>
    struct ProtoMold
    {
        using type = std::tuple<TesterB::type, Target>;
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
};

template<typename Element>
requires Omennivore::Valuable<Element>
struct TesterC
{
    using type = TesterC;
    static constexpr auto value {Element::value + 1};
};

template<auto Variable>
struct TesterD
{
    using type = TesterD;
    static constexpr auto value {Variable + 1};

    template<auto, auto Target, auto...>
    struct ProtoPage
    {
        using type = std::index_sequence<TesterD::value, Target>;
    };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;
};
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Capsule<void>***

SAME_TYPE
(
    Trip<TesterA>
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
    Capsule<void, int, int, int, double>

SAME_TYPE
(
    Trip<TesterA>
    ::Flow<TesterA>
    ::Flow<TesterA>
    ::Flow<TesterA>
    ::Road<Capsule>
    ::Mold<double>
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_VALUE   \
    3

EQUAL_VALUE
(
    Trip<TesterA>
    ::Rail<TesterD>
    ::Rail<TesterD>
    ::SubRoad<TesterC>
    ::Road<std::tuple>
    ::value
);

#undef SUPPOSED_VALUE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    std::tuple<std::tuple<int>***, double*>

SAME_TYPE
(
    Trip<TesterA>
    ::Road<TesterB>
    ::SubRoad<TesterB>
    ::SubRoad<TesterB>
    ::Flow<Emissary>
    ::Road<std::tuple>
    ::Mold<double, double*, double**>
    ::type
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/judgmental/amenity/undef_equal_value.hpp"

#endif