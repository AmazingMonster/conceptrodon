#ifndef CONCEPTRODON_VARYBIVORE_TEST_MAXIMUM_H
#define CONCEPTRODON_VARYBIVORE_TEST_MAXIMUM_H

#include <concepts>
#include "conceptrodon/varybivore/maximum.hpp"
#include "macaron/judgmental/equal_value.hpp"

#include "macaron/judgmental/amenity/define_equal_value.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace TestMaximum {




/******************************************************************************************************/
#define SUPPOSED_VALUE  \
    12
EQUAL_VALUE(Maximum_v<-10, 11, 12>);
EQUAL_VALUE(Maximum_v<-10.0, -9.0, -8.5, static_cast<double>(12)>);
#undef SUPPOSED_VALUE
/******************************************************************************************************/




}}}

#include "macaron/judgmental/amenity/undef_equal_value.hpp"

#endif