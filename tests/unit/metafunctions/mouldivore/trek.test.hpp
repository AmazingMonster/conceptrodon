// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_MOULDIVORE_TREK_H
#define CONCEPTRODON_TESTS_UNIT_MOULDIVORE_TREK_H

#include <utility>

#include "conceptrodon/mouldivore/trek.hpp"
#include "conceptrodon/utilities/vay.hpp"
#include "conceptrodon/utilities/capsule.hpp"
#include "conceptrodon/utilities/shuttle.hpp"
#include "conceptrodon/utilities/carrier.hpp"

#include "macaron/judgmental/same_type.hpp"
#include "macaron/judgmental/equal_value.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/judgmental/amenity/define_equal_value.hpp"

namespace Conceptrodon {
namespace Mouldivore {
namespace UnitTests {
namespace Testtrek {




/******************************************************************************************************/
template<auto I>
struct TesterA
{
    template<typename...Vay>
    struct Detail
    {
        using type = Capsule<Shuttle<I>, Shuttle<Vay::value>...>;
    };

    template<typename...Agreements>
    using Mold = Detail<Agreements...>::type;
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
    using type = R<Vay<0>, Vay<1>, Vay<2>>::type;
};
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Capsule<Shuttle<2*2*2*4>, Shuttle<2*2*2*0>, Shuttle<2*2*2*1>, Shuttle<2*2*2*2>>

SAME_TYPE
(
    Trek<TesterA<4>::Mold>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Commit
    ::Mold<Vay<0>, Vay<1>, Vay<2>>
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
    Trek<TesterA<4>::Mold>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Road<TesterC>
    ::Road<TesterD>
    ::Commit
    ::Mold<Vay<0>, Vay<1>, Vay<2>>
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
    Trek<TesterA<4>::Mold>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Road<TesterC>
    ::Road<TesterD>
    ::Sail<TesterE<2>::Rail>
    ::Commit
    ::Mold<Vay<0>, Vay<1>, Vay<2>>
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
    Trek<TesterA<4>::Mold>
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