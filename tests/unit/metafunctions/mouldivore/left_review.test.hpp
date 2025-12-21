// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_MOULDIVORE_LEFT_REVIEW_H
#define CONCEPTRODON_TESTS_UNIT_MOULDIVORE_LEFT_REVIEW_H

#include <concepts>

#include "conceptrodon/metafunctions/mouldivore/left_review.hpp"
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
namespace TestLeftReview {




/******************************************************************************************************/
template<typename L, typename R>
struct LessThan
{ static constexpr bool value {L::value < R::value}; };
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
VALID(LeftReview<Mouldivore::Negation<std::is_same>::Mold>::Mold_v<SHEEP_SPROUT(40)>);
VALID(LeftReview<Mouldivore::Negation<std::is_same>::Mold>::Mold<SHEEP_SPROUT(40)>::value);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_zero_alkane.hpp"
VALID(LeftReview<std::is_same>::Mold_v<ALKANE_SPROUT(40)>);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_zero_alkane.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
INVALID(LeftReview<Mouldivore::Negation<std::is_same>::Mold>::Mold_v<SHEEP_SPROUT(40), std::integral_constant<int, 39>>);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
VALID(LeftReview<LessThan>::Mold_v<SHEEP_SPROUT(40)>);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
INVALID(LeftReview<LessThan>::Mold_v<SHEEP_SPROUT(40),std::integral_constant<int, 39>>);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"
#include "macaron/fragmental/amenity/undef_alkane.hpp"

#endif