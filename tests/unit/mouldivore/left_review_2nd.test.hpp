#ifndef CONCEPTRODON_MOULDIVORE_TEST_LEFT_REVIEW_2ND_H
#define CONCEPTRODON_MOULDIVORE_TEST_LEFT_REVIEW_2ND_H

#include <concepts>
#include "conceptrodon/descend/mouldivore/left_review.hpp"
#include "conceptrodon/mouldivore/negation.hpp"
#include "macaron/fragmental/sheep.hpp"
#include "macaron/judgmental/valid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"

namespace Conceptrodon {
namespace Mouldivore {
namespace TestLeftReview2nd {



/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
VALID(LeftReview<Mouldivore::Negation<std::is_same>::Mold>::Mold_v<SHEEP_SPROUT(240)>);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/



}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"

#endif