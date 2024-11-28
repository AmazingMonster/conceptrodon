// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_PAGELIVORE_TREK_H
#define CONCEPTRODON_TESTS_UNIT_PAGELIVORE_TREK_H

#include <concepts>
#include <type_traits>
#include <utility>
#include "conceptrodon/descend/pagelivore/trek.hpp"
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
namespace TestTrek {




/******************************************************************************************************/
template<auto I>
struct TesterA
{
    template<auto...Variables>
    struct Detail
    {
        using type = Capsule<Shuttle<I>, Shuttle<Variables>...>;
    };

    template<auto...Agreements>
    using Page = Detail<Agreements...>::type;
};

template<typename...>
struct TesterBHelper {};

template<template<auto...> class...Sequences, auto...I>
struct TesterBHelper<Sequences<I>...>
{
    using type = Capsule<Sequences<2*I>...>;
};

template<typename...Agreements>
using TesterB = TesterBHelper<Agreements...>::type;

template<typename...>
struct TesterCHelper {};

template<template<auto...> class...Sequences, auto...I>
struct TesterCHelper<Sequences<I>...>
{
    using type = Capsule<Sequences<I-1>...>;
};

template<typename...Agreements>
using TesterC = TesterCHelper<Agreements...>::type;

template<auto>
struct IndexedSequence
{
    template<auto...>
    struct ProtoPage {};

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

template<typename...>
struct TesterDHelper {};

template<template<auto...> class...Sequences, auto...I>
struct TesterDHelper<Sequences<I>...>
{
    using type = Carrier<IndexedSequence<I>::template Page...>;
};

template<typename...Agreements>
using TesterD = TesterDHelper<Agreements...>::type;

template<auto I>
struct TesterE
{
    template<template<auto...> class...Sequences>
    struct Detail
    {
        using type = Capsule<Sequences<I>...>;
    };

    template<template<auto...> class...Sequences>
    using Rail = Detail<Sequences...>::type;
};

template<template<auto...> class R>
struct PageVessel
{
    using type = R<0, 1, 2>;
};
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Capsule<Shuttle<2*2*2*4>, Shuttle<2*2*2*0>, Shuttle<2*2*2*1>, Shuttle<2*2*2*2>>

SAME_TYPE
(
    Trek<TesterA<4>::Page>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Commit
    ::Page<0, 1, 2>
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
    Trek<TesterA<4>::Page>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Road<TesterC>
    ::Road<TesterD>
    ::Commit
    ::Page<0, 1, 2>
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
    Trek<TesterA<4>::Page>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Road<TesterC>
    ::Road<TesterD>
    ::Sail<TesterE<2>::Rail>
    ::Commit
    ::Page<0, 1, 2>
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
    Trek<TesterA<4>::Page>
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