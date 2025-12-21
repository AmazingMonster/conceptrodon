// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_INSERT_VALUES_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_INSERT_VALUES_H

#include <utility>

#include "conceptrodon/metafunctions/omennivore/insert_values.hpp"
#include "conceptrodon/utilities/shuttle.hpp"

#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"
#include "macaron/fragmental/alkane.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"
#include "macaron/fragmental/amenity/define_alkane.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestInsertValues {




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
using SupposedResult = Shuttle<SHEEP_SPROUT(240)>;
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE \
    SupposedResult

#define ALKANE_PREFIX
#define ALKANE_CARBON   \
    std::make_index_sequence<1>
#define ALKANE_SUFFIX   
#define ALKANE_SEPARATOR    \
    ,

#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
SAME_TYPE
(
    InsertValues<std::make_index_sequence<0>, ALKANE_SPROUT(119)>
    ::Page<SHEEP_SPROUT(120, *2), 1, 2, 3, 4>
    ::Page<SHEEP_SPROUT(120, *2+1)>
);
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"

#undef ALKANE_PREFIX
#undef ALKANE_CARBON
#undef ALKANE_SUFFIX   
#undef ALKANE_SEPARATOR

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"
#include "macaron/fragmental/amenity/undef_alkane.hpp"

#endif