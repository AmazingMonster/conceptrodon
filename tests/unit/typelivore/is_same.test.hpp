#ifndef CONCEPTRODON_TYPELIVORE_TEST_IS_SAME_H
#define CONCEPTRODON_TYPELIVORE_TEST_IS_SAME_H

#include <concepts>
#include <type_traits>
#include "conceptrodon/typelivore/is_same.hpp"
#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"

namespace Conceptrodon {
namespace Typelivore {
namespace TestIsSame {

VALID(IsSameAs<int>::Mold_v<int>);
INVALID(IsSameAs<int>::Mold_v<float>);

}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif