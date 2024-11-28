// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_MOULDIVORE_CLASSIC_TREK_H
#define CONCEPTRODON_TESTS_UNIT_MOULDIVORE_CLASSIC_TREK_H

#include <concepts>
#include <type_traits>
#include <utility>
#include "conceptrodon/descend/mouldivore/classic_trek.hpp"
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
namespace Mouldivore {
namespace UnitTests {
namespace TestClassic_trek {




/******************************************************************************************************/
template<auto I>
struct TesterA
{
    template<typename...Val>
    struct ProtoMold
    {
        using type = Capsule<Shuttle<I>, Shuttle<Val::value>...>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

template<typename...>
struct TesterB {};

template<template<auto...> class...Sequences, auto...I>
struct TesterB<Sequences<I>...>
{
    using type = Capsule<Sequences<2*I>...>;
};

template<typename...>
struct TesterC {};

template<template<auto...> class...Sequences, auto...I>
struct TesterC<Sequences<I>...>
{
    using type = Capsule<Sequences<I-1>...>;
};

template<auto>
struct IndexedSequence
{
    template<auto...>
    struct ProtoPage {};

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

template<typename...>
struct TesterD {};

template<template<auto...> class...Sequences, auto...I>
struct TesterD<Sequences<I>...>
{
    using type = Carrier<IndexedSequence<I>::template Page...>;
};

template<auto I>
struct TesterE
{
    template<template<auto...> class...Sequences>
    struct ProtoRail
    {
        using type = Capsule<Sequences<I>...>;
    };

    template<template<auto...> class...Sequences>
    using Rail = ProtoRail<Sequences...>;
};

template<template<typename...> class R>
struct MoldVessel
{
    using type = R<Monotony<0>, Monotony<1>, Monotony<2>>::type;
};
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Capsule<Shuttle<2*2*2*4>, Shuttle<2*2*2*0>, Shuttle<2*2*2*1>, Shuttle<2*2*2*2>>

SAME_TYPE
(
    ClassicTrek<TesterA<4>::Mold>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Commit
    ::Mold<Monotony<0>, Monotony<1>, Monotony<2>>
    ::type
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Carrier \
    <   \
        IndexedSequence<2*2*2*4-1>::Page,   \
        IndexedSequence<2*2*2*0-1>::Page,   \
        IndexedSequence<2*2*2*1-1>::Page,   \
        IndexedSequence<2*2*2*2-1>::Page    \
    >

SAME_TYPE
(
    ClassicTrek<TesterA<4>::Mold>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Road<TesterC>
    ::Road<TesterD>
    ::Commit
    ::Mold<Monotony<0>, Monotony<1>, Monotony<2>>
    ::type
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Capsule \
    <   \
        IndexedSequence<2*2*2*4-1>::Page<2>,   \
        IndexedSequence<2*2*2*0-1>::Page<2>,   \
        IndexedSequence<2*2*2*1-1>::Page<2>,   \
        IndexedSequence<2*2*2*2-1>::Page<2>    \
    >


SAME_TYPE
(
    ClassicTrek<TesterA<4>::Mold>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Road<TesterC>
    ::Road<TesterD>
    ::Sail<TesterE<2>::Rail>
    ::Commit
    ::Mold<Monotony<0>, Monotony<1>, Monotony<2>>
    ::type
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Capsule \
    <   \
        IndexedSequence<2*2*2*4-1>::Page<2>,   \
        IndexedSequence<2*2*2*0-1>::Page<2>,   \
        IndexedSequence<2*2*2*1-1>::Page<2>,   \
        IndexedSequence<2*2*2*2-1>::Page<2>    \
    >


SAME_TYPE
(
    ClassicTrek<TesterA<4>::Mold>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Road<TesterC>
    ::Road<TesterD>
    ::Sail<TesterE<2>::Rail>
    ::Commit
    ::Flow<MoldVessel>
    ::type
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/judgmental/amenity/undef_equal_value.hpp"

#endif