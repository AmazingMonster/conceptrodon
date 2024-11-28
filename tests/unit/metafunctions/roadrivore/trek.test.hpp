// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_ROADRIVORE_TREK_H
#define CONCEPTRODON_TESTS_UNIT_ROADRIVORE_TREK_H

#include <concepts>
#include <type_traits>
#include <utility>
#include "conceptrodon/descend/roadrivore/trek.hpp"
#include "conceptrodon/monotony.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/judgmental/equal_value.hpp"
#include "conceptrodon/capsule.hpp"
#include "conceptrodon/shuttle.hpp"
#include "conceptrodon/vehicle.hpp"
#include "conceptrodon/carrier.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/judgmental/amenity/define_equal_value.hpp"

namespace Conceptrodon {
namespace Roadrivore {
namespace UnitTests {
namespace TestTrek {




/******************************************************************************************************/
template<auto I>
struct TesterA
{
    template<template<typename...> class...Containers>
    struct Detail
    {
        using type = Capsule<Containers<Monotony<I>>...>;
    };

    template<template<typename...> class...Containers>
    using Road = Detail<Containers...>::type;
};

template<typename...>
struct TesterBHelper {};

template<template<typename...> class...Containers, typename...E>
struct TesterBHelper<Containers<E>...>
{
    using type = Capsule<Containers<Monotony<2*E::value>>...>;
};

template<typename...Agreements>
using TesterB = TesterBHelper<Agreements...>::type;

template<typename...>
struct TesterCHelper {};

template<template<typename...> class...Container, typename...E>
struct TesterCHelper<Container<E>...>
{
    using type = Capsule<Container<Monotony<E::value-1>>...>;
};

template<typename...Agreements>
using TesterC = TesterCHelper<Agreements...>::type;

template<auto>
struct IndexedContainer
{
    template<typename...>
    struct ProtoMold {};

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

template<typename...>
struct TesterDHelper {};

template<template<typename...> class...Containers, typename...E>
struct TesterDHelper<Containers<E>...>
{
    using type = Vehicle<IndexedContainer<E::value>::template Mold...>;
};

template<typename...Agreements>
using TesterD = TesterDHelper<Agreements...>::type;

template<template<template<typename...> class...> class R>
struct RoadVessel
{
    using type = R<Capsule, Capsule, Capsule>;
};
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Capsule \
    <   \
        Capsule<Monotony<2*2*2*4>>, \
        Capsule<Monotony<2*2*2*4>>, \
        Capsule<Monotony<2*2*2*4>>  \
    >

SAME_TYPE
(
    Trek<TesterA<4>::Road>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Commit
    ::Road<Capsule, Capsule, Capsule>
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
    Trek<TesterA<4>::Road>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Road<TesterC>
    ::Road<TesterD>
    ::Commit
    ::Road<Capsule, Capsule, Capsule>
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Capsule \
    <   \
        IndexedContainer<2*2*2*4-1>::Mold<Monotony<2>>,   \
        IndexedContainer<2*2*2*4-1>::Mold<Monotony<2>>,   \
        IndexedContainer<2*2*2*4-1>::Mold<Monotony<2>>    \
    >


SAME_TYPE
(
    Trek<TesterA<4>::Road>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Road<TesterC>
    ::Road<TesterD>
    ::Flow<TesterA<2>::Road>
    ::Commit
    ::Road<Capsule, Capsule, Capsule>
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Capsule \
    <   \
        IndexedContainer<2*2*2*4-1>::Mold<Monotony<2>>,   \
        IndexedContainer<2*2*2*4-1>::Mold<Monotony<2>>,   \
        IndexedContainer<2*2*2*4-1>::Mold<Monotony<2>>    \
    >


SAME_TYPE
(
    Trek<TesterA<4>::Road>
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