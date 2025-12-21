// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_ROADRIVORE_TRIP_H
#define CONCEPTRODON_TESTS_UNIT_ROADRIVORE_TRIP_H

#include <utility>

#include "conceptrodon/utilities/capsule.hpp"
#include "conceptrodon/utilities/vay.hpp"
#include "conceptrodon/roadrivore/trip.hpp"

#include "macaron/judgmental/same_type.hpp"
#include "macaron/judgmental/equal_value.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/judgmental/amenity/define_equal_value.hpp"

namespace Conceptrodon {
namespace Roadrivore {
namespace UnitTests {
namespace TestTrip {




/******************************************************************************************************/
template<typename...>
struct DummyContainer {};

template<auto I>
struct TesterA
{
    template<template<typename...> class Container>
    struct ProtoRoad
    {
        template<typename...Agreements>
        using Mold = Container<Vay<I>, Agreements...>;

        using type = Container<Vay<I>>;

        static constexpr auto value {I};
    };

    template<>
    struct ProtoRoad<DummyContainer>
    {
        template<typename...Agreements>
        using Mold = DummyContainer<Vay<-I>, Agreements...>;

        using type = DummyContainer<Vay<-I>>;

        static constexpr auto value {-I};
    };

    template<template<typename...> class...Containers>
    using Road = ProtoRoad<Containers...>;
};

template<typename Element>
struct TesterBHelper {};

template<template<typename...> class Container, typename...E>
struct TesterBHelper<Container<E...>>
{
    template<typename...Agreements>
    using Mold = Container<Vay<(0 +...+ (2 * E::value))>, Agreements...>;

    using type = Container<Vay<(0 +...+ (2 * E::value))>>;
    
    template<auto...I>
    using Page = Container<Vay<(0 +...+ (2 * E::value)) + (0 +...+ I)>>;

    static constexpr auto value { (0 +...+ (2 * E::value)) };

};

template<typename...Elements>
using TesterB = TesterBHelper<typename Elements::type...>;

template<typename Element>
struct TesterCHelper {};

template<template<typename...> class Container, typename...E>
struct TesterCHelper<Container<E...>>
{
    template<typename...Agreements>
    using Mold = Container<Vay<(0 +...+ (E::value - 1))>, Agreements...>;

    using type = Container<Vay<(0 +...+ (E::value - 1))>>;
    
    template<auto...I>
    using Page = Container<Vay<(0 +...+ (E::value - 1)) + (0 +...+ I)>>;

    static constexpr auto value { (0 +...+ (E::value - 1)) };

};

template<typename...Elements>
using TesterC = TesterCHelper<typename Elements::type...>;

template<template<template<typename...> class...> class R>
struct RoadVessel
{
    static constexpr auto value
    {R<Capsule>::value};
};
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Capsule<Vay<2*2*2*4>>

SAME_TYPE
(
    Trip<TesterA<4>::Road>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Commit
    ::Road<Capsule>
    ::type
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Capsule<Vay<2*4 + 2*3 + 2*2 + 2*1>, int>

SAME_TYPE
(
    Trip<TesterA<1>::Road>
    ::Flow<TesterA<2>::Road>
    ::Flow<TesterA<3>::Road>
    ::Flow<TesterA<4>::Road>
    ::Road<TesterB>
    ::Commit
    ::Road<Capsule>
    ::Mold<int>
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE  \
    Capsule<Vay<2*4 + 2*3 + 2*2 + 2*1 - 1 - 1>, int>

SAME_TYPE
(
    Trip<TesterA<1>::Road>
    ::Flow<TesterA<2>::Road>
    ::Flow<TesterA<3>::Road>
    ::Flow<TesterA<4>::Road>
    ::Road<TesterB>
    ::Road<TesterC>
    ::Road<TesterC>
    ::Commit
    ::Road<Capsule>
    ::Mold<int>
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE  \
    DummyContainer<Vay<2*4 + 2*3 + 2*2 + 2*(-1) - 1 - 1>, int>

SAME_TYPE
(
    Trip<TesterA<1>::Road>
    ::Flow<TesterA<2>::Road>
    ::Flow<TesterA<3>::Road>
    ::Flow<TesterA<4>::Road>
    ::Road<TesterB>
    ::Road<TesterC>
    ::Road<TesterC>
    ::Commit
    ::Road<DummyContainer>
    ::Mold<int>
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE  \
    Capsule<Vay<((4-1) + (3-1) + (2-1) + (1-1) - 1) * 2>, int>

SAME_TYPE
(
    Trip<TesterA<1>::Road>
    ::Flow<TesterA<2>::Road>
    ::Flow<TesterA<3>::Road>
    ::Flow<TesterA<4>::Road>
    ::Road<TesterC>
    ::Road<TesterC>
    ::Road<TesterB>
    ::Commit
    ::Road<Capsule>
    ::Mold<int>
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_VALUE  \
    ((4-1) + (3-1) + (2-1) + (1-1) - 1) * 2


EQUAL_VALUE
(
    Trip<TesterA<1>::Road>
    ::Flow<TesterA<2>::Road>
    ::Flow<TesterA<3>::Road>
    ::Flow<TesterA<4>::Road>
    ::Road<TesterC>
    ::Road<TesterC>
    ::Road<TesterB>
    ::Commit
    ::Snow<RoadVessel>
    ::value
);

#undef SUPPOSED_VALUE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/judgmental/amenity/undef_equal_value.hpp"

#endif