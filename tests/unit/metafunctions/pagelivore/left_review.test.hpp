// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_PAGELIVORE_LEFT_REVIEW_H
#define CONCEPTRODON_TESTS_UNIT_PAGELIVORE_LEFT_REVIEW_H

#include <concepts>

#include "conceptrodon/descend/pagelivore/left_review.hpp"
#include "conceptrodon/pagelivore/negation.hpp"
#include "conceptrodon/varybivore/is_same.hpp"

#include "macaron/fragmental/sheep.hpp"
#include "macaron/fragmental/alkane.hpp"
#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"
#include "macaron/fragmental/amenity/define_alkane.hpp"

namespace Conceptrodon {
namespace Pagelivore {
namespace UnitTests {
namespace TestLeftReview {



/******************************************************************************************************/
template<auto L, auto R>
struct LessThan
{ static constexpr bool value {L < R}; };
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
VALID(LeftReview<Pagelivore::Negation<Varybivore::IsSame>::Page>::Page_v<SHEEP_SPROUT(40)>);
VALID(LeftReview<Pagelivore::Negation<Varybivore::IsSame>::Page>::Page<SHEEP_SPROUT(40)>::value);
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"
/******************************************************************************************************/





/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_zero_alkane.hpp"
VALID(LeftReview<Varybivore::IsSame>::Page_v<ALKANE_SPROUT(40)>);
#include "macaron/fragmental/amenity/instances/undef_integer_zero_alkane.hpp"
/******************************************************************************************************/





/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
INVALID(LeftReview<Pagelivore::Negation<Varybivore::IsSame>::Page>::Page_v<SHEEP_SPROUT(40), 39>);
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"
/******************************************************************************************************/





/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
VALID(LeftReview<LessThan>::Page_v<SHEEP_SPROUT(40)>);
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
INVALID(LeftReview<LessThan>::Page_v<SHEEP_SPROUT(40), 39>);
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"
#include "macaron/fragmental/amenity/undef_alkane.hpp"

#endif