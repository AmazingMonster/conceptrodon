// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_UNIT_TESTS_TEST_ZIP_VALUE_H
#define CONCEPTRODON_OMENNIVORE_UNIT_TESTS_TEST_ZIP_VALUE_H

#include <utility>

#include "conceptrodon/utilities/capsule.hpp"
#include "conceptrodon/utilities/shuttle.hpp"
#include "conceptrodon/metafunctions/omennivore/zip.hpp"

#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"
#include "macaron/fragmental/double_sheep.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"
#include "macaron/fragmental/amenity/define_double_sheep.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestZipValue {




/******************************************************************************************************/
template<size_t>
struct Tester_0 {};


template<size_t>
struct Tester_1 {};
/******************************************************************************************************/




/******************************************************************************************************/
#define DOUBLE_SHEEP_PREFIX \
    Shuttle<Tester_0<
#define DOUBLE_SHEEP_MIDDLE \
    >{}, Tester_1<
#define DOUBLE_SHEEP_SUFFIX \
    >{}>
#define DOUBLE_SHEEP_SEPARATOR  \
    ,

using SupposedResult = Capsule<DOUBLE_SHEEP_SPROUT(80)>;

#undef DOUBLE_SHEEP_PREFIX
#undef DOUBLE_SHEEP_MIDDLE
#undef DOUBLE_SHEEP_SUFFIX
#undef DOUBLE_SHEEP_SEPARATOR
/******************************************************************************************************/




/******************************************************************************************************/
#define SHEEP_PREFIX \
    Tester_0<
#define SHEEP_SUFFIX \
    >{}
#define SHEEP_SEPARATOR  \
    ,

using Arg_0 = Shuttle<SHEEP_SPROUT(80)>;

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR
/******************************************************************************************************/




/******************************************************************************************************/
#define SHEEP_PREFIX \
    Tester_1<
#define SHEEP_SUFFIX \
    >{}
#define SHEEP_SEPARATOR  \
    ,

using Arg_1 = Shuttle<SHEEP_SPROUT(120)>;

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE \
    SupposedResult

SAME_TYPE(Zip<Arg_0, Arg_1>::Rail<Shuttle>::Road<Capsule>);

#define SHEEP_PREFIX \
    Zip<Arg_0, Arg_1>::Rail<Shuttle>::Page<
#define SHEEP_SUFFIX \
    >
#define SHEEP_SEPARATOR  \
    ,

SAME_TYPE(Capsule<SHEEP_SPROUT(80)>);

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