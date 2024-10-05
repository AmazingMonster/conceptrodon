// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_TEST_LEFT_REVIEW_2ND_H
#define CONCEPTRODON_PAGELIVORE_TEST_LEFT_REVIEW_2ND_H

#include <concepts>
#include "conceptrodon/descend/pagelivore/left_review.hpp"
#include "conceptrodon/pagelivore/negation.hpp"
#include "conceptrodon/varybivore/is_same.hpp"
#include "macaron/fragmental/sheep.hpp"
#include "macaron/judgmental/valid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"

namespace Conceptrodon {
namespace Pagelivore {
namespace TestLeftReview2nd {




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
VALID(LeftReview<Pagelivore::Negation<Varybivore::IsSame>::Page>::Page_v<SHEEP_SPROUT(240)>);
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"
/******************************************************************************************************/




}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"

#endif