#ifndef CONCEPTRODON_VARYBIVORE_TEST_IS_EQUAL_H
#define CONCEPTRODON_VARYBIVORE_TEST_IS_EQUAL_H

#include <concepts>
#include "conceptrodon/varybivore/is_equal.hpp"
#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace TestIsEqual {




/******************************************************************************************************/
VALID(IsEqual_v<0, 0>);
INVALID(IsEqual_v<0, 1>);
/******************************************************************************************************/




/******************************************************************************************************/
VALID(IsEqualTo<0>::Page_v<0>);
INVALID(IsEqualTo<0>::Page_v<1>);
/******************************************************************************************************/




}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif