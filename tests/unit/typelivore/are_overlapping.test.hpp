// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_TYPELIVORE_ARE_OVERLAPPING_H
#define CONCEPTRODON_TESTS_UNIT_TYPELIVORE_ARE_OVERLAPPING_H

#include <concepts>
#include <type_traits>
#include "conceptrodon/descend/typelivore/are_overlapping.hpp"
#include "conceptrodon/capsule.hpp"
#include "macaron/fragmental/sheep.hpp"
#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"

namespace Conceptrodon {
namespace Typelivore {
namespace TestAreOverlapping {




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
VALID(std::is_same_v<AreOverlapping<SHEEP_SPROUT(240)>::Mold<SHEEP_SPROUT(120)>::type, void>);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/





/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
VALID(std::is_same_v<AreOverlapping<SHEEP_SPROUT(240)>::Mold<std::integral_constant<int, 10>>::type, void>);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/





/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
INVALID(std::is_same_v<AreOverlapping<SHEEP_SPROUT(40)>::Mold<SHEEP_SPROUT(40, +40)>::type, void>);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/




}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"

#endif