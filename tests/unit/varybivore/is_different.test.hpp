#ifndef CONCEPTRODON_VARYBIVORE_TEST_IS_DIFFERENT_H
#define CONCEPTRODON_VARYBIVORE_TEST_IS_DIFFERENT_H

#include <concepts>
#include "conceptrodon/varybivore/is_different.hpp"
#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace TestIsDifferent {




/******************************************************************************************************/
INVALID(IsDifferent_v<1, 1>);
VALID(IsDifferent_v<1, 2>);
VALID(IsDifferent_v<1, static_cast<size_t>(1)>);
/******************************************************************************************************/




/******************************************************************************************************/
INVALID(IsDifferentAs<1>::Page_v<1>);
VALID(IsDifferentAs<1>::Page_v<2>);
VALID(IsDifferentAs<1>::Page_v<static_cast<size_t>(1)>);
/******************************************************************************************************/




}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif