// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_RAILLIVORE_CLASSIC_TREK_H
#define CONCEPTRODON_TESTS_UNIT_RAILLIVORE_CLASSIC_TREK_H

#include <utility>

#include "conceptrodon/raillivore/classic_trek.hpp"

#include "conceptrodon/utilities/capsule.hpp"
#include "conceptrodon/utilities/shuttle.hpp"
#include "conceptrodon/utilities/carrier.hpp"

#include "macaron/judgmental/same_type.hpp"
#include "macaron/judgmental/equal_value.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/judgmental/amenity/define_equal_value.hpp"

namespace Conceptrodon {
namespace Raillivore {
namespace UnitTests {
namespace TestClassicTrek {




/******************************************************************************************************/
template<auto I>
struct TesterA
{
    template<template<auto...> class...Sequences>
    struct ProtoRail
    {
        using type = Capsule<Sequences<I>...>;
    };

    template<template<auto...> class...Sequences>
    using Rail = ProtoRail<Sequences...>;
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

template<template<template<auto...> class...> class R>
struct RailVessel
{
    using type = R<Shuttle, Shuttle, Shuttle>::type;
};
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Capsule<Shuttle<2*2*2*4>, Shuttle<2*2*2*4>, Shuttle<2*2*2*4>>

SAME_TYPE
(
    ClassicTrek<TesterA<4>::Rail>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Commit
    ::Rail<Shuttle, Shuttle, Shuttle>
    ::type
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Carrier \
    <   \
        IndexedSequence<2*2*2*4-1>::Page,   \
        IndexedSequence<2*2*2*4-1>::Page,   \
        IndexedSequence<2*2*2*4-1>::Page    \
    >

SAME_TYPE
(
    ClassicTrek<TesterA<4>::Rail>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Road<TesterC>
    ::Road<TesterD>
    ::Commit
    ::Rail<Shuttle, Shuttle, Shuttle>
    ::type
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Capsule \
    <   \
        IndexedSequence<2*2*2*4-1>::Page<2>,   \
        IndexedSequence<2*2*2*4-1>::Page<2>,   \
        IndexedSequence<2*2*2*4-1>::Page<2>    \
    >


SAME_TYPE
(
    ClassicTrek<TesterA<4>::Rail>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Road<TesterC>
    ::Road<TesterD>
    ::Sail<TesterA<2>::Rail>
    ::Commit
    ::Rail<Shuttle, Shuttle, Shuttle>
    ::type
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Capsule \
    <   \
        IndexedSequence<2*2*2*4-1>::Page<2>,   \
        IndexedSequence<2*2*2*4-1>::Page<2>,   \
        IndexedSequence<2*2*2*4-1>::Page<2>    \
    >


SAME_TYPE
(
    ClassicTrek<TesterA<4>::Rail>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Road<TesterC>
    ::Road<TesterD>
    ::Sail<TesterA<2>::Rail>
    ::Commit
    ::Hail<RailVessel>
    ::type
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/judgmental/amenity/undef_equal_value.hpp"

#endif