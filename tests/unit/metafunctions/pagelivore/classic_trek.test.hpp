// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_PAGELIVORE_CLASSIC_TREK_H
#define CONCEPTRODON_TESTS_UNIT_PAGELIVORE_CLASSIC_TREK_H

#include <concepts>
#include <type_traits>
#include <utility>
#include "conceptrodon/descend/pagelivore/classic_trek.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/judgmental/equal_value.hpp"
#include "conceptrodon/capsule.hpp"
#include "conceptrodon/shuttle.hpp"
#include "conceptrodon/vehicle.hpp"
#include "conceptrodon/carrier.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/judgmental/amenity/define_equal_value.hpp"

namespace Conceptrodon {
namespace Pagelivore {
namespace UnitTests {
namespace TestClassic_trek {




/******************************************************************************************************/
template<auto I>
struct TesterA
{
    template<auto...Variables>
    struct ProtoPage
    {
        using type = Capsule<Shuttle<I>, Shuttle<Variables>...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
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

template<template<auto...> class R>
struct PageVessel
{
    using type = R<0, 1, 2>::type;
};
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Capsule<Shuttle<2*2*2*4>, Shuttle<2*2*2*0>, Shuttle<2*2*2*1>, Shuttle<2*2*2*2>>

SAME_TYPE
(
    ClassicTrek<TesterA<4>::Page>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Commit
    ::Page<0, 1, 2>
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
    ClassicTrek<TesterA<4>::Page>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Road<TesterC>
    ::Road<TesterD>
    ::Commit
    ::Page<0, 1, 2>
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
    ClassicTrek<TesterA<4>::Page>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Road<TesterC>
    ::Road<TesterD>
    ::Sail<TesterE<2>::Rail>
    ::Commit
    ::Page<0, 1, 2>
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
    ClassicTrek<TesterA<4>::Page>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Road<TesterC>
    ::Road<TesterD>
    ::Sail<TesterE<2>::Rail>
    ::Commit
    ::Sail<PageVessel>
    ::type
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/judgmental/amenity/undef_equal_value.hpp"

#endif