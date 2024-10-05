#ifndef CONCEPTRODON_OMENNIVORE_TEST_TOTAL_H
#define CONCEPTRODON_OMENNIVORE_TEST_TOTAL_H

#include "conceptrodon/omennivore/total.hpp"
#include "macaron/judgmental/equal_value.hpp"
#include "conceptrodon/capsule.hpp"
#include "conceptrodon/shuttle.hpp"
#include "conceptrodon/reverie.hpp"
#include "conceptrodon/phantom.hpp"

#include "macaron/judgmental/amenity/define_equal_value.hpp"
#include <utility>

namespace Conceptrodon {
namespace Omennivore {
namespace TestTotal {

#define SUPPOSED_VALUE  \
    4

EQUAL_VALUE(Total<Capsule<int, int*, int**, int***>>::value);
EQUAL_VALUE(Total<Shuttle<0, 1, 2, 3>>::value);
EQUAL_VALUE(Total<std::index_sequence<0, 1, 2, 3>>::value);
EQUAL_VALUE(Total<Reverie<Capsule, Capsule, Capsule, Capsule>>::value);
EQUAL_VALUE(Total<Phantom<Shuttle, Shuttle, Shuttle, Shuttle>>::value);

}}}

#include "macaron/judgmental/amenity/undef_equal_value.hpp"

#endif