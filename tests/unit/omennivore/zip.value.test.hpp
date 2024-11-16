// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ZIP_VALUE_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ZIP_VALUE_H

#include "conceptrodon/capsule.hpp"
#include "conceptrodon/shuttle.hpp"

#include "conceptrodon/descend/descend/omennivore/zip.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"
#include "macaron/fragmental/double_sheep.hpp"
#include <utility>

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"
#include "macaron/fragmental/amenity/define_double_sheep.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestZipValue {




/******************************************************************************************************/
template<size_t>
struct TesterA {};


template<size_t>
struct TesterB {};
/******************************************************************************************************/




/******************************************************************************************************/
#define DOUBLE_SHEEP_PREFIX \
    Shuttle<TesterA<
#define DOUBLE_SHEEP_MIDDLE \
    >{}, TesterB<
#define DOUBLE_SHEEP_SUFFIX \
    >{}>
#define DOUBLE_SHEEP_SEPARATOR  \
    ,

using SupposedResult = Capsule<DOUBLE_SHEEP_SPROUT(240)>;

#undef DOUBLE_SHEEP_PREFIX
#undef DOUBLE_SHEEP_MIDDLE
#undef DOUBLE_SHEEP_SUFFIX
#undef DOUBLE_SHEEP_SEPARATOR
/******************************************************************************************************/




/******************************************************************************************************/
#define SHEEP_PREFIX \
    TesterA<
#define SHEEP_SUFFIX \
    >{}
#define SHEEP_SEPARATOR  \
    ,

using ArgA = Shuttle<SHEEP_SPROUT(240)>;

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR
/******************************************************************************************************/




/******************************************************************************************************/
#define SHEEP_PREFIX \
    TesterB<
#define SHEEP_SUFFIX \
    >{}
#define SHEEP_SEPARATOR  \
    ,

using ArgB = Shuttle<SHEEP_SPROUT(300)>;

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE \
    SupposedResult

SAME_TYPE(Zip<ArgA, ArgB>::Rail<Shuttle>::Road<Capsule>);

#define SHEEP_PREFIX \
    Zip<ArgA, ArgB>::Rail<Shuttle>::Page<
#define SHEEP_SUFFIX \
    >
#define SHEEP_SEPARATOR  \
    ,

SAME_TYPE(Capsule<SHEEP_SPROUT(240)>);

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define DOUBLE_SHEEP_PREFIX \
    std::index_sequence<
#define DOUBLE_SHEEP_MIDDLE \
    ,
#define DOUBLE_SHEEP_SUFFIX \
    >
#define DOUBLE_SHEEP_SEPARATOR  \
    ,

using SupposedResult_1 = Capsule<DOUBLE_SHEEP_SPROUT(240)>;

#undef DOUBLE_SHEEP_PREFIX
#undef DOUBLE_SHEEP_MIDDLE
#undef DOUBLE_SHEEP_SUFFIX
#undef DOUBLE_SHEEP_SEPARATOR
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE \
    SupposedResult_1

SAME_TYPE
(
    Zip<std::make_index_sequence<240>,std::make_index_sequence<300>>
    ::Rail<std::index_sequence>
    ::Road<Capsule>
);

#define SHEEP_PREFIX \
    Zip<std::make_index_sequence<240>,std::make_index_sequence<300>>    \
    ::Rail<std::index_sequence> \
    ::Page<
#define SHEEP_SUFFIX \
    >
#define SHEEP_SEPARATOR  \
    ,

SAME_TYPE(Capsule<SHEEP_SPROUT(240)>);

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"
#include "macaron/fragmental/amenity/undef_double_sheep.hpp"

#endif