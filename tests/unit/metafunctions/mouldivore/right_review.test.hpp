// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDVORE_UNIT_TESTS_TEST_RIGHT_REVIEW_H
#define CONCEPTRODON_MOULDVORE_UNIT_TESTS_TEST_RIGHT_REVIEW_H

#include <utility>

#include "conceptrodon/metafunctions/mouldivore/right_review.hpp"
#include "conceptrodon/metafunctions/mouldivore/negation.hpp"

#include "macaron/fragmental/sheep.hpp"
#include "macaron/fragmental/alkane.hpp"
#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"
#include "macaron/fragmental/amenity/define_alkane.hpp"

namespace Conceptrodon {
namespace Mouldivore {
namespace UnitTests {
namespace TestRightReview {




/******************************************************************************************************/
template<typename L, typename R>
struct LessThan
{ static constexpr bool value {L::value < R::value}; };
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
VALID(RightReview<Mouldivore::Negation<std::is_same>::Mold>::Mold_v<SHEEP_SPROUT(40)>);
VALID(RightReview<Mouldivore::Negation<std::is_same>::Mold>::Mold<SHEEP_SPROUT(40)>::value);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_zero_alkane.hpp"
VALID(RightReview<std::is_same>::Mold_v<ALKANE_SPROUT(40)>);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_zero_alkane.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
INVALID(RightReview<Mouldivore::Negation<std::is_same>::Mold>::Mold_v<SHEEP_SPROUT(40), std::integral_constant<int, 39>>);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
INVALID(RightReview<LessThan>::Mold_v<SHEEP_SPROUT(40)>);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
VALID(RightReview<Mouldivore::Negation<LessThan>::Mold>::Mold_v<SHEEP_SPROUT(40)>);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"
#include "macaron/fragmental/amenity/undef_alkane.hpp"

#endif