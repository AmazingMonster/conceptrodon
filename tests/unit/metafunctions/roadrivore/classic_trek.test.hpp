// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_ROADRIVORE_CLASSIC_TREK_H
#define CONCEPTRODON_TESTS_UNIT_ROADRIVORE_CLASSIC_TREK_H

#include <utility>

#include "conceptrodon/descend/roadrivore/classic_trek.hpp"
#include "conceptrodon/vay.hpp"

#include "macaron/judgmental/same_type.hpp"
#include "macaron/judgmental/equal_value.hpp"

#include "conceptrodon/capsule.hpp"
#include "conceptrodon/vehicle.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/judgmental/amenity/define_equal_value.hpp"

namespace Conceptrodon {
namespace Roadrivore {
namespace UnitTests {
namespace TestClassicTrek {




/******************************************************************************************************/
template<auto I>
struct TesterA
{
    template<template<typename...> class...Containers>
    struct ProtoRoad
    {
        using type = Capsule<Containers<Vay<I>>...>;
    };

    template<template<typename...> class...Containers>
    using Road = ProtoRoad<Containers...>;
};

template<typename...>
struct TesterB {};

template<template<typename...> class...Containers, typename...E>
struct TesterB<Containers<E>...>
{
    using type = Capsule<Containers<Vay<2*E::value>>...>;
};

template<typename...>
struct TesterC {};

template<template<typename...> class...Container, typename...E>
struct TesterC<Container<E>...>
{
    using type = Capsule<Container<Vay<E::value-1>>...>;
};

template<auto>
struct IndexedContainer
{
    template<typename...>
    struct ProtoMold {};

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

template<typename...>
struct TesterD {};

template<template<typename...> class...Containers, typename...E>
struct TesterD<Containers<E>...>
{
    using type = Vehicle<IndexedContainer<E::value>::template Mold...>;
};

template<template<template<typename...> class...> class R>
struct RoadVessel
{
    using type = R<Capsule, Capsule, Capsule>::type;
};
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Capsule \
    <   \
        Capsule<Vay<2*2*2*4>>, \
        Capsule<Vay<2*2*2*4>>, \
        Capsule<Vay<2*2*2*4>>  \
    >

SAME_TYPE
(
    ClassicTrek<TesterA<4>::Road>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Commit
    ::Road<Capsule, Capsule, Capsule>
    ::type
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Vehicle \
    <   \
        IndexedContainer<2*2*2*4-1>::Mold,   \
        IndexedContainer<2*2*2*4-1>::Mold,   \
        IndexedContainer<2*2*2*4-1>::Mold    \
    >

SAME_TYPE
(
    ClassicTrek<TesterA<4>::Road>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Road<TesterC>
    ::Road<TesterD>
    ::Commit
    ::Road<Capsule, Capsule, Capsule>
    ::type
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Capsule \
    <   \
        IndexedContainer<2*2*2*4-1>::Mold<Vay<2>>,   \
        IndexedContainer<2*2*2*4-1>::Mold<Vay<2>>,   \
        IndexedContainer<2*2*2*4-1>::Mold<Vay<2>>    \
    >


SAME_TYPE
(
    ClassicTrek<TesterA<4>::Road>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Road<TesterC>
    ::Road<TesterD>
    ::Flow<TesterA<2>::Road>
    ::Commit
    ::Road<Capsule, Capsule, Capsule>
    ::type
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Capsule \
    <   \
        IndexedContainer<2*2*2*4-1>::Mold<Vay<2>>,   \
        IndexedContainer<2*2*2*4-1>::Mold<Vay<2>>,   \
        IndexedContainer<2*2*2*4-1>::Mold<Vay<2>>    \
    >


SAME_TYPE
(
    ClassicTrek<TesterA<4>::Road>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Road<TesterC>
    ::Road<TesterD>
    ::Flow<TesterA<2>::Road>
    ::Commit
    ::Snow<RoadVessel>
    ::type
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/judgmental/amenity/undef_equal_value.hpp"

#endif