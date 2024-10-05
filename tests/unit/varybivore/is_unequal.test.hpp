#ifndef CONCEPTRODON_VARYBIVORE_TEST_IS_UNEQUAL_H
#define CONCEPTRODON_VARYBIVORE_TEST_IS_UNEQUAL_H

#include <concepts>
#include "conceptrodon/varybivore/is_unequal.hpp"
#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace TestIsUnequal {




/******************************************************************************************************/
INVALID(IsUnequal_v<0, 0>);
VALID(IsUnequal_v<0, 1>);
/******************************************************************************************************/




/******************************************************************************************************/
INVALID(IsUnequalTo<0>::Page_v<0>);
VALID(IsUnequalTo<0>::Page_v<1>);
/******************************************************************************************************/




}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif