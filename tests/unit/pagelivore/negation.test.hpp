#ifndef CONCEPTRODON_PAGELIVORE_TEST_NEGATION_H
#define CONCEPTRODON_PAGELIVORE_TEST_NEGATION_H

#include <concepts>
#include <type_traits>
#include "conceptrodon/pagelivore/negation.hpp"
#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"

namespace Conceptrodon {
namespace Pagelivore {
namespace TestNegation {




/******************************************************************************************************/
template<auto...>
using PageT = std::true_type;

template<auto...>
using PageF = std::false_type;
/******************************************************************************************************/




/******************************************************************************************************/
INVALID(Negation<PageT>::Page_v<1>);
VALID(Negation<PageF>::Page_v<1>);
/******************************************************************************************************/




}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif