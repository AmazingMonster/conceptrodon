// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_RAILLIVORE_TRIP_H
#define CONCEPTRODON_TESTS_UNIT_RAILLIVORE_TRIP_H

#include <type_traits>
#include <utility>
#include "conceptrodon/monotony.hpp"
#include "conceptrodon/shuttle.hpp"
#include "conceptrodon/raillivore/trip.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/judgmental/equal_value.hpp"
#include "conceptrodon/omennivore/concepts/valuable.hpp"
#include "conceptrodon/emissary.hpp"
#include "conceptrodon/diplomat.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/judgmental/amenity/define_equal_value.hpp"

namespace Conceptrodon {
namespace Raillivore {
namespace UnitTests {
namespace TestTrip {




/******************************************************************************************************/
template<template<auto...> class Stockroom>
struct TesterA
{
    template<auto...Agreements>
    using Page = Stockroom<0, Agreements...>;

    using type = Stockroom<0>;

    static constexpr auto value {0};
};

template<>
struct TesterA<Shuttle>
{
    template<auto...Agreements>
    using Page = Shuttle<'*', Agreements...>;

    using type = Shuttle<'*'>;
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
    Shuttle<'*'>***

SAME_TYPE
(
    Trip<TesterA>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Rail<Shuttle>
    ::type
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Shuttle<'*', 0, 0, 0, 10>

SAME_TYPE
(
    Trip<TesterA>
    ::Sail<TesterA>
    ::Sail<TesterA>
    ::Sail<TesterA>
    ::Rail<Shuttle>
    ::Page<10>
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
    ::SubRail<TesterD>
    ::Road<TesterC>
    ::Rail<std::index_sequence>
    ::value
);

#undef SUPPOSED_VALUE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    std::tuple<Shuttle<'*'>***, void*>

SAME_TYPE
(
    Trip<TesterA>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Flow<Emissary>
    ::Rail<Shuttle>
    ::Mold<void, void*, void**>
    ::type
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/judgmental/amenity/undef_equal_value.hpp"

#endif