#ifndef CONCEPTRODON_VARYBIVORE_TEST_IS_NO_LESS_H
#define CONCEPTRODON_VARYBIVORE_TEST_IS_NO_LESS_H

#include <concepts>
#include "conceptrodon/varybivore/is_no_less.hpp"
#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace TestIsNoLess {




/******************************************************************************************************/
VALID(IsNoLess_v<0, 0>);
VALID(IsNoLess_v<1, 0>);
INVALID(IsNoLess_v<0, 1>);
/******************************************************************************************************/




/******************************************************************************************************/
VALID(IsNoLessThan<0>::Page_v<0>);
VALID(IsNoLessThan<0>::Page_v<1>);
INVALID(IsNoLessThan<1>::Page_v<0>);
/******************************************************************************************************/




}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif