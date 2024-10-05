#ifndef CONCEPTRODON_VARYBIVORE_TEST_IS_NO_GREATER_H
#define CONCEPTRODON_VARYBIVORE_TEST_IS_NO_GREATER_H

#include <concepts>
#include "conceptrodon/varybivore/is_no_greater.hpp"
#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace TestIsNoGreater {




/******************************************************************************************************/
VALID(IsNoGreater_v<0, 0>);
INVALID(IsNoGreater_v<1, 0>);
VALID(IsNoGreater_v<0, 1>);
/******************************************************************************************************/




/******************************************************************************************************/
VALID(IsNoGreaterThan<0>::Page_v<0>);
INVALID(IsNoGreaterThan<0>::Page_v<1>);
VALID(IsNoGreaterThan<1>::Page_v<0>);
/******************************************************************************************************/




}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif