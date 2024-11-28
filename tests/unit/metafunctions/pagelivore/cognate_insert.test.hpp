// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_PAGELIVORE_COGNATE_INSERT_H
#define CONCEPTRODON_TESTS_UNIT_PAGELIVORE_COGNATE_INSERT_H

#include <concepts>
#include "conceptrodon/descend/descend/pagelivore/cognate_insert.hpp"
#include "conceptrodon/shuttle.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"

namespace Conceptrodon {
namespace Pagelivore {
namespace UnitTests {
namespace TestCognateInsert {




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
using SupposedResult = Shuttle<SHEEP_SPROUT(240)>;
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE \
    SupposedResult

#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
SAME_TYPE
(
    CognateInsert<Shuttle>
    ::Page<SHEEP_SPROUT(120, *2+1)>
    ::Page<SHEEP_SPROUT(120)>
    ::Page<SHEEP_SPROUT(120, *2), 1, 2, 3, 4>
);
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"

#endif