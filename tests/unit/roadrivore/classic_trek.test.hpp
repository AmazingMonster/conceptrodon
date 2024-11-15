// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_ROADRIVORE_CLASSIC_TREK_H
#define CONCEPTRODON_TESTS_UNIT_ROADRIVORE_CLASSIC_TREK_H

#include <concepts>
#include <type_traits>
#include <utility>
#include "conceptrodon/descend/roadrivore/classic_trek.hpp"
#include "conceptrodon/monotony.hpp"
#include "conceptrodon/omennivore/send.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/judgmental/equal_value.hpp"
#include "conceptrodon/omennivore/concepts/valuable.hpp"
#include "conceptrodon/capsule.hpp"
#include "conceptrodon/shuttle.hpp"
#include "conceptrodon/reverie.hpp"
#include "conceptrodon/phantom.hpp"

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
        using type = Capsule<Containers<Monotony<I>>...>;
    };

    template<template<typename...> class...Containers>
    using Road = ProtoRoad<Containers...>;
};

template<typename...>
struct TesterB {};

template<template<typename...> class...Containers, typename...E>
struct TesterB<Containers<E>...>
{
    using type = Capsule<Containers<Monotony<2*E::value>>...>;
};

template<typename...>
struct TesterC {};

template<template<typename...> class...Container, typename...E>
struct TesterC<Container<E>...>
{
    using type = Capsule<Container<Monotony<E::value-1>>...>;
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
    using type = Reverie<IndexedContainer<E::value>::template Mold...>;
};

template<template<template<typename...> class...> class R>
struct RoadHolder
{
    using type = R<Capsule, Capsule, Capsule>::type;
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
    Reverie \
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
        IndexedContainer<2*2*2*4-1>::Mold<Monotony<2>>,   \
        IndexedContainer<2*2*2*4-1>::Mold<Monotony<2>>,   \
        IndexedContainer<2*2*2*4-1>::Mold<Monotony<2>>    \
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
        IndexedContainer<2*2*2*4-1>::Mold<Monotony<2>>,   \
        IndexedContainer<2*2*2*4-1>::Mold<Monotony<2>>,   \
        IndexedContainer<2*2*2*4-1>::Mold<Monotony<2>>    \
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
    ::Snow<RoadHolder>
    ::type
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/judgmental/amenity/undef_equal_value.hpp"

#endif